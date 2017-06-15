#include "MeshObject.h"
#include "InstanceObject.h"
#include "MotionObject.h"
#include "Sphere.h"
#include "Triangle.h"

#include "Camera.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "AreaLight.h"
#include "Scene.h"
#include "AABBTree.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "Vertex.h"
#include "Triangle.h"
#include "LambertMaterial.h"
#include "FresnelMetalMaterial.h"
#include "AshikhminMaterial.h"
#include "EmissionMaterial.h"
#include "DieletricMaterial.h"

#include "Random.h"

#include <iostream>

using namespace std;

void project1();
void project2();
void project3();
void project4();
void randomGeneratorTest();
void messup();
void sphereTest();
void room();

int main() {
	room();
	// project3();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

void randomGeneratorTest() {
	Random rand1 = Random(true);
	Random rand2 = Random(true);
	for(int i=0; i<3; i++) {
		float num1 = rand1.next();
		float num2 = rand2.next();
		printf("%f, %f\n", num1, num2);
	}
	//printf("average of 10000 samples is %f\n", sum/10000.0f);
}

////////////////////////////////////////////////////////////////////////////////

void project1() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));

	// Create boxes
	MeshObject box1;
	box1.makeBox(5.0f,0.1f,5.0f);
	scn.addObject(box1);

	std::cout<<"box1"<<std::endl;
	Material* orange = new LambertMaterial();
	orange->setColor(Color(0.8f, 0.5f, 0.4f));
	MeshObject box2;
	box2.makeBox(1.0f,1.0f,1.0f, orange);

	std::cout<<"inst1"<<std::endl;
	InstanceObject inst1(box2);
	glm::mat4x4 mtx=glm::rotate(glm::mat4(),0.5f,glm::vec3(1,0,0));
	mtx[3][1]=1.0f;
	inst1.setMatrix(mtx);
	scn.addObject(inst1);

	std::cout<<"inst2"<<std::endl;
	InstanceObject inst2(box2);
	mtx=glm::rotate(glm::mat4(),1.0f,glm::vec3(0,1,0));
	mtx[3]=glm::vec4(-1,0,1,1);
	inst2.setMatrix(mtx);
	scn.addObject(inst2);

	// Create lights
	std::cout<<"direction"<<std::endl;

	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(0.5f);
	sunlgt.setDirection(glm::vec3(-0.5f, -1.0f, -0.5f));
	scn.addLight(sunlgt);

	std::cout<<"point"<<std::endl;

	PointLight redlgt;
	redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.setIntensity(2.0f);
	redlgt.setPosition(glm::vec3(2.0f, 2.0f, 0.0f));
	scn.addLight(redlgt);

	// Create camera
	std::cout<<"cam"<<std::endl;

	Camera cam;
	cam.lookAt(glm::vec3(2.0f,2.0f,5.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0,1,0));
	cam.setResolution(800,600);
	cam.setFOV(40.0f);
	cam.setAspect(1.33f);
	cam.setSuperSample(1,1);

	// Render image
	cam.render(scn);
	cam.saveBitmap("project1.bmp");
}

////////////////////////////////////////////////////////////////////////////////
void project2() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.8f, 1.0f));
	// Create ground
	MeshObject ground;
	ground.makeBox(5.0f,0.1f,5.0f);
	scn.addObject(ground);

	// MeshObject b;
	// b.makeBox(0.1f,0.5f,0.1f);
	// //scn.addObject(box);
	// InstanceObject inst(b);
	// glm::mat4x4 mtx=glm::translate(glm::mat4(),glm::vec3(0,0.3f,0));
	// mtx[3]=glm::vec4(-0.05f,0.0f,-0.1f,1.0f);
	// inst.setMatrix(mtx);
	// scn.addObject(inst);

	//Create dragon
	MeshObject dragon;
	dragon.loadPLY("ply/dragon.ply", nullptr);
	dragon.smooth();
	AABBTree tree;
	tree.construct(dragon);
	scn.addObject(tree);

	//Create instance
	InstanceObject inst(tree);
	glm::mat4x4 mtx=glm::rotate(glm::mat4(),(float)M_PI,glm::vec3(0,1,0));
	mtx[3]=glm::vec4(-0.05f,0.0f,-0.1f,1.0f);
	inst.setMatrix(mtx);
	scn.addObject(inst);

	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(1.0f);
	sunlgt.setDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.addLight(sunlgt);

	PointLight redlgt;
	redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.setIntensity(0.02f);
	redlgt.setPosition(glm::vec3(-0.2f, 0.2f, 0.2f));
	scn.addLight(redlgt);

	PointLight bluelgt;
	bluelgt.setBaseColor(Color(0.2f, 0.2f, 1.0f));
	bluelgt.setIntensity(0.02f);
	bluelgt.setPosition(glm::vec3(0.1f, 0.1f, 0.3f));
	scn.addLight(bluelgt);

	// Create camera
	Camera cam;
	cam.lookAt(glm::vec3(-0.1f,0.1f,0.2f),glm::vec3(-0.05f,0.12f,0.0f), glm::vec3(0,1.0f,0));
	cam.setFOV(40.0f);
	cam.setAspect(1.33f);
	cam.setResolution(800,600);

	// Render image
	cam.render(scn);
	cam.saveBitmap("project2.bmp");
}

////////////////////////////////////////////////////////////////////////////////
void project3() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f,0.9f,1.0f));

	// Create ground
	LambertMaterial groundMtl;
	groundMtl.setColor(Color(0.25f,0.25f,0.25f));
	MeshObject ground;
	ground.makeBox(2.0f,0.11f,2.0f,&groundMtl);
	scn.addObject(ground);

	// Load dragon mesh
	MeshObject dragon;
	dragon.loadPLY("ply/dragon.ply", 0);

	// Create box tree
	AABBTree tree;
	tree.construct(dragon);

	// Materials
	LambertMaterial white;
	white.setColor(Color(0.7f,0.7f,0.7f));
	LambertMaterial red;
	red.setColor(Color(0.7f,0.1f,0.1f));
	FresnelMetalMaterial metal;
	metal.setColor(Color(0.95f,0.64f,0.54f));

	const int numDragons=4;
	Material *mtl[numDragons]={&white,&metal,&red,&white};
	// Create dragon instances
	glm::mat4 mtx;
	for(int i=0;i<numDragons;i++) {
		InstanceObject *inst=new InstanceObject(tree);
		mtx[3]=glm::vec4(0.0f,0.0f,0.3f*(float(i)/float(numDragons-1)-0.5f),1.0f);
		inst->setMatrix(mtx);
		inst->setMaterial(mtl[i]);
		scn.addObject(*inst);
	}
	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(1.0f);
	sunlgt.setDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.addLight(sunlgt);

	// Create camera
	Camera cam;
	cam.setResolution(640,480);
	cam.setAspect(1.33f);
	cam.lookAt(glm::vec3(-0.5f,0.25f,-0.2f),glm::vec3(0.0f,0.15f,0.0f),glm::vec3(0, 1.0f, 0));
	cam.setFOV(40.0f);
	cam.setSuperSample(2, 2);
	//cam.setDOF(0.05f, 0.42f);
	cam.setJitter(true);
	cam.setShirley(true);

	// Render image
	cam.render(scn);
	cam.saveBitmap("project3.bmp");
}

////////////////////////////////////////////////////////////////////////////////

void project4() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));

	// Materials
	const int nummtls = 4;
	AshikhminMaterial mtl[nummtls];

	// Diffuse
	mtl[0].setSpecularLevel(0.0f);
	mtl[0].setDiffuseLevel(1.0f);
	mtl[0].setDiffuseColor(Color(0.7f, 0.7f, 0.7f));

	// Roughened copper
	mtl[1].setDiffuseLevel(0.0f);
	mtl[1].setSpecularLevel(1.0f);
	mtl[1].setSpecularColor(Color(0.9f, 0.6f, 0.5f));
	mtl[1].setRoughness(100.0f, 100.0f);
	// Anisotropic gold
	mtl[2].setDiffuseLevel(0.0f);
	mtl[2].setSpecularLevel(1.0f);
	mtl[2].setSpecularColor(Color(0.95f, 0.7f, 0.3f));
	mtl[2].setRoughness(1.0f, 1000.0f);
	// Red plastic
	mtl[3].setDiffuseColor(Color(1.0f, 0.1f, 0.1f));
	mtl[3].setDiffuseLevel(0.8f);
	mtl[3].setSpecularLevel(0.2f);
	mtl[3].setSpecularColor(Color(1.0f, 1.0f, 1.0f));
	mtl[3].setRoughness(1000.0f, 1000.0f);

	// Load dragon mesh
	MeshObject dragon;
	dragon.loadPLY("ply/dragon.ply", 0);

	// Create box tree
	AABBTree tree;
	tree.construct(dragon);

	// Create dragon instances
	glm::mat4 mtx;
	for(int i = 0; i < 4; i++) {
		InstanceObject *inst = new InstanceObject(tree);
		mtx[3]=glm::vec4(0.0f, 0.0f, -0.1f*float(i), 1.0f);
		inst->setMatrix(mtx);
		inst->setMaterial(&mtl[i]);
		scn.addObject(*inst);
	}

	// Create ground
	LambertMaterial lambert;
	lambert.setColor(Color(0.3f, 0.3f, 0.35f));
	MeshObject ground;
	ground.makeBox(2.0f,0.11f,2.0f,&lambert);
	scn.addObject(ground);

	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(1.0f);
	sunlgt.setDirection(glm::vec3 (2.0f, -3.0f, -2.0f));
	scn.addLight(sunlgt);

	// Create camera
	Camera cam;
	cam.lookAt(glm::vec3(-0.5f, 0.25f, -0.2f), glm::vec3(0.0f, 0.15f, -0.15f), vec3(0.0f, 1.0f, 0.0f));
	cam.setFOV(40.0f);
	cam.setAspect(1.33f);
	cam.setResolution(800, 600);
	cam.setSuperSample(10,10);
	cam.setJitter(true);
	cam.setShirley(true);

	// Render image
	cam.render(scn);
	cam.saveBitmap("project4.bmp");

}

////////////////////////////////////////////////////////////////////////////////
void motionTest() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));

	// Create ground
	LambertMaterial groundMtl;
	groundMtl.setColor(Color(0.25f,0.25f,0.25f));
	MeshObject ground;
	ground.makeBox(2.0f,0.11f,2.0f,&groundMtl);
	scn.addObject(ground);

	// Load dragon mesh
	MeshObject dragon;
	dragon.loadPLY("ply/dragon.ply", 0);

	// Create box tree
	AABBTree tree;
	tree.construct(dragon);

	// Materials
	LambertMaterial white;
	white.setColor(Color(0.7f,0.7f,0.7f));
	LambertMaterial red;
	red.setColor(Color(0.7f,0.1f,0.1f));

	//add stable instanceObject
	glm::mat4 mtx1;
	mtx1[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	InstanceObject inst1 = InstanceObject(tree);
	inst1.setMatrix(mtx1);
	inst1.setMaterial(&white);
	scn.addObject(inst1);

	//add big circle rotate motionObject
	glm::mat4 mtx2;
	mtx2[3] = glm::vec4(0.0f, 0.0f, 0.15f, 1.0f);
	InstanceObject inst2 = InstanceObject(tree);
	inst2.setMatrix(mtx2);
	inst2.setMaterial(&red);
	MotionObject mot1 = MotionObject(inst2);
	glm::mat4 motion1 = glm::rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 motion2 = glm::rotate(45.0f, vec3(0.0f, 1.0f, 0.0f));
	mot1.addMotion(motion1, motion2, 'r');
	scn.addObject(mot1);

	//add inplace circle motionObject
	MotionObject mot2 = MotionObject(tree);
	glm::mat4 motion3 = glm::rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 motion4 = glm::rotate(45.0f, vec3(0.0f, 1.0f, 0.0f));
	mot2.addMotion(motion3, motion4, 'r');
	glm::mat4 mtx3;
	mtx3[3] = glm::vec4(0.0f, 0.0f, 0.15f, 1.0f);
	InstanceObject inst3 = InstanceObject(mot2);
	inst3.setMatrix(mtx3);
	inst3.setMaterial(&red);
	scn.addObject(inst3);

	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(1.0f);
	sunlgt.setDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.addLight(sunlgt);

	// Create camera
	Camera cam;
	cam.setResolution(640,480);
	cam.setAspect(1.33f);
	cam.lookAt(glm::vec3(-0.5f,0.25f,-0.2f),glm::vec3(0.0f,0.15f,0.0f),glm::vec3(0, 1.0f, 0));
	cam.setFOV(40.0f);
	cam.setSuperSample(1,1);
	//cam.setDOF(0.01f, 0.45f);
	cam.setJitter(true);
	cam.setShirley(true);

	// Render image
	cam.render(scn);
	cam.saveBitmap("motion.bmp");
}

void DOFTest() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f,0.9f,1.0f));

	// Create ground
	LambertMaterial groundMtl;
	groundMtl.setColor(Color(0.25f,0.25f,0.25f));
	MeshObject ground;
	ground.makeBox(2.0f,0.11f,2.0f,&groundMtl);
	scn.addObject(ground);

	// Load dragon mesh
	MeshObject dragon;
	dragon.loadPLY("ply/dragon.ply", 0);

	// Create box tree
	AABBTree tree;
	tree.construct(dragon);

	// Materials
	LambertMaterial white;
	white.setColor(Color(0.7f,0.7f,0.7f));
	LambertMaterial red;
	red.setColor(Color(0.7f,0.1f,0.1f));
	FresnelMetalMaterial metal;
	metal.setColor(Color(0.95f,0.64f,0.54f));

	const int numDragons=4;
	Material *mtl[numDragons]={&white,&metal,&red,&white};
	// Create dragon instances
	glm::mat4 mtx;
	for(int i=0;i<numDragons;i++) {
		InstanceObject *inst=new InstanceObject(tree);
		mtx[3]=glm::vec4(0.0f,0.0f,0.3f*(float(i)/float(numDragons-1)-0.5f),1.0f);
		inst->setMatrix(mtx);
		inst->setMaterial(mtl[i]);
		scn.addObject(*inst);
	}
	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(1.0f);
	sunlgt.setDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.addLight(sunlgt);

	// Create camera
	Camera cam;
	cam.setResolution(640,480);
	cam.setAspect(1.33f);
	cam.lookAt(glm::vec3(-0.5f,0.25f,-0.2f),glm::vec3(0.0f,0.15f,0.0f),glm::vec3(0, 1.0f, 0));
	cam.setFOV(40.0f);
	cam.setSuperSample(2, 2);
	//cam.setDOF(0.05f, 0.42f);
	cam.setJitter(true);
	cam.setShirley(true);

	// Render image
	cam.render(scn);
	cam.saveBitmap("project3.bmp");
}
////////////////////////////////////////////////////////////////////////////////
void sphereTest() {
	// Create scene
	Scene scn;
	// scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
	scn.setSkyColor(Color(0.71f, 0.8f, 0.8f));


	// Create ground
	LambertMaterial groundMtl;
	groundMtl.setColor(Color(0.5f, 0.5f, 0.5f));
	MeshObject ground;
	ground.makeBox(2.0f, 0.1f, 2.0f, &groundMtl);
	scn.addObject(ground);

	// Materials
	LambertMaterial white;
	white.setColor(Color(0.7f,0.7f,0.7f));
	LambertMaterial pink;
	pink.setColor(Color(1.0f,0.59f,0.8f));
	EmissionMaterial areaLight;
	areaLight.setColor(Color(8.0f, 8.0f, 8.0f));

	DieletricMaterial glass;
	glass.setColor(Color(0.4f, 0.6f, 0.6f));
	glass.setIndex(1.7f);

	Sphere s1;
	vec3 center1 = vec3(0.0f, 0.115f, 0.2f);
	s1.init(center1, 0.06f, &glass);
	scn.addObject(s1);

	// Triangle light1;
	// Triangle light2;
	// Vertex v0, v1, v2, v3;
	// vec3 pos0 = vec3(-0.1f, 0.28f, 0.19f);
	// vec3 pos1 = vec3(0.1f, 0.28f, 0.19f);
	// vec3 pos2 = vec3(0.1f, 0.28f, 0.21f);
	// vec3 pos3 = vec3(-0.1f, 0.28f, 0.21f);
	// vec3 norm = vec3(0.0f, -1.0f, 0.0f);
	// vec3 tCoord = vec3(0.0f, 0.0f, 0.0f);
	// v0.set(pos0, norm, tCoord);
	// v1.set(pos1, norm, tCoord);
	// v2.set(pos2, norm, tCoord);
	// v3.set(pos3, norm, tCoord);
	// light1.init(&v0, &v1, &v2, &areaLight);
	// light2.init(&v2, &v3, &v0, &areaLight);
	// scn.addObject(light1);
	// scn.addObject(light2);

	Triangle t0;
	Triangle t1;
	Vertex v0, v1, v2, v3;
	vec3 pos0 = vec3(-0.1f, 0.485f, -0.1f);
	vec3 pos1 = vec3(0.1f, 0.485f, -0.1f);
	vec3 pos2 = vec3(0.1f, 0.485f, 0.1f);
	vec3 pos3 = vec3(-0.1f, 0.485f, 0.1f);
	vec3 norm = vec3(0.0f, -1.0f, 0.0f);
	vec3 tCoord = vec3(0.0f, 0.0f, 0.0f);
	v0.set(pos0, norm, tCoord);
	v1.set(pos1, norm, tCoord);
	v2.set(pos2, norm, tCoord);
	v3.set(pos3, norm, tCoord);
	t0.init(&v0, &v1, &v2, 0);
	t1.init(&v2, &v3, &v0, 0);

	AreaLight sqrlight;
	sqrlight.setBaseColor(Color(0.9f, 1.0f, 1.0f));
	sqrlight.setIntensity(0.3f);
	sqrlight.setAreaTris(&t0, &t1);
	scn.addLight(sqrlight);

	// Sphere light;
	// vec3 center2 = vec3(0.0f, 0.27f, 0.2f);
	// light.init(center2, 0.01f, &areaLight);
	// scn.addObject(light);

	// // Create lights
	// DirectLight sunlgt;
	// sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	// sunlgt.setIntensity(1.0f);
	// sunlgt.setDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	// scn.addLight(sunlgt);

	// Create camera
	Camera cam;
	cam.setResolution(640,480);
	cam.setAspect(1.33f);
	cam.lookAt(glm::vec3(0.0f, 0.15f, -0.2f),glm::vec3(0.0f,0.15f,0.0f),glm::vec3(0, 1.0f, 0));
	cam.setFOV(40.0f);
	cam.setSuperSample(3,3);
	//cam.setDOF(0.01f, 0.45f);
	cam.setJitter(true);
	cam.setShirley(true);

	// Render image
	cam.render(scn);
	cam.saveBitmap("sphere_glass.bmp");
}

////////////////////////////////////////////////////////////////////////////////
void room() {

	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.9f, 0.9f, 0.9f));

	///
	LambertMaterial white;
	white.setColor(Color(0.9f, 0.9f, 0.9f));

	LambertMaterial red;
	red.setColor(Color(0.9f, 0.1f, 0.1f));

	LambertMaterial green;
	green.setColor(Color(0.1f, 0.9f, 0.1f));

	LambertMaterial blue;
	blue.setColor(Color(0.1f, 0.1f, 0.9f));

	DieletricMaterial glass;
	glass.setColor(Color(0.9f, 0.9f, 0.9f));
	glass.setIndex(1.8f);

	///
	MeshObject fb;
	fb.makeBox(1.0f, 1.0f, 0.01f, &white);

	mat4 mtx0 = mat4(1.0f);
	InstanceObject front = InstanceObject(fb);
	mtx0[3]=glm::vec4(0.0f, 0.0f, 0.5f, 1.0f);
	front.setMatrix(mtx0);

	mat4 mtx1 = mat4(1.0f);
	InstanceObject back = InstanceObject(fb);
	mtx1[3]=glm::vec4(0.0f, 0.0f, -0.5f, 1.0f);
	back.setMatrix(mtx1);
	//back.setMaterial(&blue);

	///
	MeshObject td;
	td.makeBox(1.0f, 0.01f, 1.0f, &white);

	mat4 mtx2 = mat4(1.0f);
	InstanceObject top = InstanceObject(td);
	mtx2[3]=glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
	top.setMatrix(mtx2);

	mat4 mtx3 = mat4(1.0f);
	InstanceObject bottom = InstanceObject(td);
	mtx3[3]=glm::vec4(0.0f, -0.5f, 0.0f, 1.0f);
	bottom.setMatrix(mtx3);
	//bottom.setMaterial(&red);

	///
	MeshObject rl;
	rl.makeBox(0.01f, 1.0f, 1.0f, 0);

	mat4 mtx4 = mat4(1.0f);
	InstanceObject right = InstanceObject(rl);
	mtx4[3]=glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
	right.setMatrix(mtx4);
	right.setMaterial(&green);

	mat4 mtx5 = mat4(1.0f);
	InstanceObject left = InstanceObject(rl);
	mtx5[3]=glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f);
	left.setMatrix(mtx5);
	left.setMaterial(&red);

	///
	//scn.addObject(front);
	scn.addObject(back);
	scn.addObject(top);
	scn.addObject(bottom);
	scn.addObject(right);
	scn.addObject(left);

	///
	Sphere s1;
	vec3 center1 = vec3(-0.1f, -0.3f, -0.1f);
	s1.init(center1, 0.2f, &glass);
	scn.addObject(s1);

	// MeshObject window;
	// window.makeBox(0.5f, 0.5f, 0.01f, &glass);
	// InstanceObject windowInstance = InstanceObject(window);
	// glm::mat4 windowMtx=glm::rotate(glm::mat4(),(float)M_PI / -2.2f,glm::vec3(1,0,0));
	// windowMtx[3] = vec4(0.0f, -0.3f, 0.0f, 1.0f);
	// windowInstance.setMatrix(windowMtx);
	// scn.addObject(windowInstance);


	///
	Triangle t0;
	Triangle t1;
	Vertex v0, v1, v2, v3;
	vec3 pos0 = vec3(-0.1f, 0.485f, -0.1f);
	vec3 pos1 = vec3(0.1f, 0.485f, -0.1f);
	vec3 pos2 = vec3(0.1f, 0.485f, 0.1f);
	vec3 pos3 = vec3(-0.1f, 0.485f, 0.1f);
	vec3 norm = vec3(0.0f, -1.0f, 0.0f);
	vec3 tCoord = vec3(0.0f, 0.0f, 0.0f);
	v0.set(pos0, norm, tCoord);
	v1.set(pos1, norm, tCoord);
	v2.set(pos2, norm, tCoord);
	v3.set(pos3, norm, tCoord);
	t0.init(&v0, &v1, &v2, 0);
	t1.init(&v2, &v3, &v0, 0);

	AreaLight sqrlight;
	sqrlight.setBaseColor(Color(0.9f, 1.0f, 1.0f));
	sqrlight.setIntensity(0.3f);
	sqrlight.setAreaTris(&t0, &t1);
	scn.addLight(sqrlight);

	///
	Camera cam;
	cam.setResolution(512, 512);
	cam.setAspect(1.0f);
	cam.lookAt(glm::vec3(0.0f, 0.0f, 1.8f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0, 1.0f, 0));
	cam.setFOV(40.0f);
	cam.setSuperSample(5, 5);
	//cam.setDOF(0.01f, 0.45f);
	cam.setJitter(true);
	cam.setShirley(true);

	// Render image
	cam.render(scn);
	cam.saveBitmap("room_plane.bmp");
}
