#include "InstanceObject.h"

InstanceObject::InstanceObject(Object& obj) {
  child = &obj;
};

void InstanceObject::setChild(Object& obj) {
  child = &obj;
}

void InstanceObject::setMatrix(mat4& mtx) {
  matrix = mtx;
  inverseMat = inverse(matrix);
}

bool InstanceObject::intersect(const Ray& ray, Intersection& hit) {
  Ray newRay;
  newRay.t = ray.t;
  newRay.org = vec3(inverseMat * vec4(ray.org, 1) );
  newRay.dir = vec3(inverseMat * vec4(ray.dir, 0));

  if(child->intersect(newRay, hit) == false) return false;

  hit.pos = vec3( matrix * vec4(hit.pos, 1));
  hit.norm = vec3( matrix * vec4(hit.norm, 0));
  hit.hitDis = distance(ray.org, hit.pos);
  if(mtl != 0) hit.mtl = mtl;

  return true;
}

void InstanceObject::setMaterial(Material* mtl) {
  this->mtl = mtl;
}
