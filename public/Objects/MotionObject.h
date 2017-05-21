#pragma once

#include "Object.h"
#include "InstanceObject.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>

class MotionObject: public Object {
private:
  Object *child;
  Material *mtl;
  std::vector<mat4> startMtxs;
  std::vector<mat4> endMtxs;
  std::vector<char> motions;

  mat4 lerp(float t, int idx);
  mat4 slerp(float t, int idx);

public:
  MotionObject(Object& obj);

  void setChild(Object& obj);
  void setMaterial(Material* mtl);
  void addMotion(mat4& startMtx, mat4& endMtx, char motion);

  virtual bool intersect(const Ray& ray, Intersection& hit);
};
