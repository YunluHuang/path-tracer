#pragma once

#include "Object.h"

typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4 mat4;

class InstanceObject: public Object {
private:
  mat4 matrix;
  mat4 inverseMat;
  Object* child;
  Material* mtl;

public:
  InstanceObject(Object& obj);

  void setChild(Object& obj);
  void setMatrix(mat4& mtx);

  virtual bool intersect(const Ray& ray, Intersection& hit);

  void setMaterial(Material *mtl);
};
