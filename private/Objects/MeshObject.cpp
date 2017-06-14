#include "MeshObject.h"
#include "LambertMaterial.h"
#include "glm/glm.hpp"

#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

////////////////////////////////////////////////////////////////////////////////

MeshObject::MeshObject() {
	numVertexes = 0;
	numTriangles = 0;

	vertexes = 0;
	triangles = 0;
}

////////////////////////////////////////////////////////////////////////////////

MeshObject::~MeshObject() {
	if(vertexes != 0) {
		delete []vertexes;
		vertexes = 0;
	}
	if(numTriangles != 0) {
		delete []triangles;
		triangles = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////

bool MeshObject::intersect(const Ray &ray, Intersection &hit) {
	bool success = false;
	for(int i = 0; i < numTriangles; i++)
		if(triangles[i].intersect(ray, hit)){
			success = true;
		}
	return success;
}

Triangle * MeshObject::getTriangles() {
	return triangles;
}

int MeshObject::getNumTriangles() {
	return numTriangles;
}

////////////////////////////////////////////////////////////////////////////////

void MeshObject::makeBox(float x, float y, float z, Material *mtl) {
	// Allocate arrays
	numVertexes = 24;
	numTriangles = 12;
	vertexes = new Vertex[numVertexes];
	triangles = new Triangle[numTriangles];
	if(mtl == nullptr) mtl = new LambertMaterial;

	x *= 0.5f;
	y *= 0.5f;
	z *= 0.5f;

	// Corners
	glm::vec3 p000(-x, -y, -z);
	glm::vec3 p001(-x, -y, z);
	glm::vec3 p010(-x, y, -z);
	glm::vec3 p011(-x, y, z);
	glm::vec3 p100(x, -y, -z);
	glm::vec3 p101(x, -y, z);
	glm::vec3 p110(x, y, -z);
	glm::vec3 p111(x, y, z);

	// Tex coords
	glm::vec3 t00(0.0f, 0.0f, 0.0f);
	glm::vec3 t01(0.0f, 1.0f, 0.0f);
	glm::vec3 t10(1.0f, 0.0f, 0.0f);
	glm::vec3 t11(1.0f, 1.0f, 0.0f);

	// Axis vectors
	glm::vec3 xAxis(1, 0, 0);
	glm::vec3 yAxis(0, 1, 0);
	glm::vec3 zAxis(0, 0, 1);

	// Right
	vertexes[0].set(p101, xAxis, t00);
	vertexes[1].set(p100, xAxis, t10);
	vertexes[2].set(p110, xAxis, t11);
	vertexes[3].set(p111, xAxis, t01);
	triangles[0].init(&vertexes[0], &vertexes[1], &vertexes[2], mtl);
	triangles[1].init(&vertexes[0], &vertexes[2], &vertexes[3], mtl);

	// Left
	vertexes[4].set(p000, -xAxis, t00);
	vertexes[5].set(p001, -xAxis, t10);
	vertexes[6].set(p011, -xAxis, t11);
	vertexes[7].set(p010, -xAxis, t01);
	triangles[2].init(&vertexes[4], &vertexes[5], &vertexes[6], mtl);
	triangles[3].init(&vertexes[4], &vertexes[6], &vertexes[7], mtl);

	// Top
	vertexes[8].set(p011, yAxis, t00);
	vertexes[9].set(p111, yAxis, t10);
	vertexes[10].set(p110, yAxis, t11);
	vertexes[11].set(p010, yAxis, t01);
	triangles[4].init(&vertexes[8], &vertexes[9], &vertexes[10], mtl);
	triangles[5].init(&vertexes[8], &vertexes[10], &vertexes[11], mtl);

	// Bottom
	vertexes[12].set(p000, -yAxis, t00);
	vertexes[13].set(p100, -yAxis, t10);
	vertexes[14].set(p101, -yAxis, t11);
	vertexes[15].set(p001, -yAxis, t01);
	triangles[6].init(&vertexes[12], &vertexes[13], &vertexes[14], mtl);
	triangles[7].init(&vertexes[12], &vertexes[14], &vertexes[15], mtl);

	// Front
	vertexes[16].set(p001, zAxis, t00);
	vertexes[17].set(p101, zAxis, t10);
	vertexes[18].set(p111, zAxis, t11);
	vertexes[19].set(p011, zAxis, t01);
	triangles[8].init(&vertexes[16], &vertexes[17], &vertexes[18], mtl);
	triangles[9].init(&vertexes[16], &vertexes[18], &vertexes[19], mtl);

	// Back
	vertexes[20].set(p100, -zAxis, t00);
	vertexes[21].set(p000, -zAxis, t10);
	vertexes[22].set(p010, -zAxis, t11);
	vertexes[23].set(p110, -zAxis, t01);
	triangles[10].init(&vertexes[20], &vertexes[21], &vertexes[22], mtl);
	triangles[11].init(&vertexes[20], &vertexes[22], &vertexes[23], mtl);
}

////////////////////////////////////////////////////////////////////////////////

bool MeshObject::loadPLY(const char *filename, Material *mtl) {
	// Open file
	FILE *f = fopen(filename,"r");
	if(f == 0) {
		printf("ERROR: MeshObject::LoadPLY()- Can't open '%s'\n",filename);
		return false;
	}

	// Read header
	char tmp[256];
	int numverts = 0, numtris = 0;
	int posprop = -99, normprop = -99;
	int props = 0;
	while(1) {
		fgets(tmp,256,f);
		if(strncmp(tmp,"element vertex",14) == 0)
			numverts = atoi(&tmp[14]);
		if(strncmp(tmp,"element face",12) == 0)
			numtris = atoi(&tmp[12]);
		if(strncmp(tmp,"property",8) == 0) {
			int len = strlen(tmp);
			if(strncmp(&tmp[len-3], " x", 2) == 0) posprop = props;
			if(strncmp(&tmp[len-3], "nx", 2) == 0) normprop = props;
			props++;
		}
		if(strcmp(tmp,"end_header\n") == 0) break;
	}
	if(posprop == -1) {
		printf("ERROR: MeshObject::LoadPLY()- No vertex positions found\n");
		fclose(f);
		return false;
	}

	// Read verts
	int i = 0;
	if(numverts > 0) {
		numVertexes = numverts;
		vertexes = new Vertex[numVertexes];

		for(i = 0; i < numVertexes; i++) {
			fgets(tmp, 256, f);
			char *pch = strtok(tmp," ");
			int prop = 0;
			while(pch) {
				if(prop == posprop) vertexes[i].pos.x = float(atof(pch));
				if(prop == posprop + 1) vertexes[i].pos.y = float(atof(pch));
				if(prop == posprop + 2) vertexes[i].pos.z = float(atof(pch));
				if(prop == normprop) vertexes[i].norm.x = float(atof(pch));
				if(prop == normprop + 1) vertexes[i].norm.y = float(atof(pch));
				if(prop == normprop + 2) vertexes[i].norm.z = float(atof(pch));
				pch = strtok(0," ");
				prop++;
			}
		}
	}

	// Read tris
	if(numtris > 0) {
		if(mtl == 0) mtl = new LambertMaterial;
		numTriangles = numtris;
		triangles = new Triangle[numtris];
		for(i = 0; i < numtris; i++) {
			int count,i0,i1,i2;
			fscanf(f, "%d %d %d %d\n", &count, &i0, &i1, &i2);
			if(count != 3) {
				printf("ERROR: MeshObject::LoadPLY()- Only triangles are supported\n");
				fclose(f);
				return false;
			}
			triangles[i].init(&vertexes[i0], &vertexes[i1], &vertexes[i2], mtl);
		}
	}

	// Smooth
	if(normprop < 0) smooth();

	// Close file
	fclose(f);
	printf("Loaded %d triangles from file '%s'\n",numtris,filename);
	return true;
}

void MeshObject::smooth() {
	int i,j;
	for(i = 0; i < numVertexes; i++) {
		vertexes[i].norm = vec3(0);
	}
	for(i = 0; i < numTriangles; i++) {
		Triangle &tri = triangles[i];
		vec3 e1 = tri.getVertice(1)->pos - tri.getVertice(0)->pos;
		vec3 e2 = tri.getVertice(2)->pos - tri.getVertice(0)->pos;
		vec3 cross = glm::cross(e1,e2);
		for(j = 0; j < 3; j++)
			tri.getVertice(j)->norm += cross;
	}
	for(i = 0; i < numVertexes; i++)
		vertexes[i].norm = glm::normalize(vertexes[i].norm);
}
