#include "MotionObject.h"

#include <iostream>

MotionObject::MotionObject(Object& obj) {
  child = &obj;
}

void MotionObject::setChild(Object& obj) {
  child = &obj;
}

void MotionObject::setMaterial(Material* mtl) {
  this->mtl = mtl;
}


void MotionObject::addMotion(mat4& startMtx, mat4& endMtx, char motion) {
  startMtxs.push_back(startMtx);
  endMtxs.push_back(endMtx);
  motions.push_back(motion);
}

bool MotionObject::intersect(const Ray& ray, Intersection& hit) {

  float t = ray.t;
  mat4 mtx = mat4(1.0);
  for(int i = 0; i < motions.size(); i++) {
    switch(motions[i]) {
      case 't':
        mtx = lerp(t, i) * mtx;
        break;
      case 'r':
        mtx = slerp(t, i) * mtx;
        break;
      default:
        break;
    }
  }
  mat4 inverseMtx = inverse(mtx);
  Ray newRay;
  newRay.t = t;
  newRay.org = vec3(inverseMtx * vec4(ray.org, 1));
  newRay.dir = vec3(inverseMtx * vec4(ray.dir, 1));

  if(child->intersect(newRay, hit) == false) return false;

  hit.pos = vec3( mtx * vec4(hit.pos, 1));
  hit.norm = vec3( mtx * vec4(hit.norm, 0));
  hit.hitDis = distance(ray.org, hit.pos);
  hit.mtl = mtl;
  return true;
}

////////////////////////////////////////////////////////////////////////////////

mat4 MotionObject::lerp(float t, int idx) {
  mat4 mtx = (1 - t) * startMtxs[idx] + t * endMtxs[idx];
  return mtx;
}

mat4 MotionObject::slerp(float t, int idx) {
  glm::fquat a = toQuat(startMtxs[idx]);
  glm::fquat b = toQuat(endMtxs[idx]);
  glm::fquat q = glm::fquat();
  q = glm::slerp(a, b, t);
  mat4 mtx = toMat4(q);
  return mtx;
}

////////////////////////////////////////////////////////////////////////////////
