#pragma once

#include "Object.h"
#include "Triangle.h"

class MeshObject:public Object {
private:
  int numVertexes, numTriangles;
  Vertex *vertexes;
  Triangle *triangles;

public:
	MeshObject();
	~MeshObject();

	virtual bool intersect(const Ray &ray,Intersection &hit);
  Triangle * getTriangles();
  int getNumTriangles();

	void makeBox(float x, float y, float z, Material *mtl=0);
  bool loadPLY(const char *filename, Material *mtl);
  void smooth();
};
