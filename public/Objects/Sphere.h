#pragma once

#include "Object.h"

class Sphere: public Object {
private:
  vec3 pos;
  float r;
  Material* mtl;

public:

  void init(const vec3& position, float radius, Material* material);
  virtual bool intersect(const Ray& ray, Intersection& hit);

};
