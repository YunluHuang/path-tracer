#pragma once

#include "Object.h"
#include "Triangle.h"
#include <vector>
#include <algorithm>

class AABBox {
private:
  vec3 vmin;
  vec3 vmax;
  std::vector<Triangle *> tris;
  AABBox *left;
  AABBox *right;

  bool boxIntersect(const Ray &ray, Intersection &hit);

public:

  AABBox();
  AABBox(Triangle *triangles, int numTriangles);
  ~AABBox();

  int getNumTris();
  vec3 getVmin();
  vec3 getVmax();

  bool intersect(const Ray &ray, Intersection &hit);
  void addTri(Triangle *tri);
  bool split(int axis);
};
