#include "AreaLight.h"

AreaLight::AreaLight() {
  randGen = new Random(true);
}

void AreaLight::setAreaTris(Triangle* t0, Triangle* t1) {
  this->t0 = t0;
  this->t1 = t1;
  vec3 v0, v1, v2, v3, v4, v5;
  v0 = t0->getVertice(0)->pos;
  v1 = t0->getVertice(1)->pos;
  v2 = t0->getVertice(2)->pos;
  v3 = t1->getVertice(0)->pos;
  v4 = t1->getVertice(1)->pos;
  v5 = t1->getVertice(2)->pos;
  area = 0.5f * length(cross(v1 - v0, v2 - v0)) + 0.5f * length(cross(v5 - v3, v4 - v3));
}

vec3 AreaLight::sampleLight(){
  float u = randGen->next();
  float s = randGen->next();
  float t = randGen->next();
  float alpha = sqrt(s) * t;
  float beta = 1 - sqrt(s);
  vec3 v0, v1, v2;
  if(u < 0.5f) {
    v0 = t0->getVertice(0)->pos;
    v1 = t0->getVertice(1)->pos;
    v2 = t0->getVertice(2)->pos;
  } else {
    v0 = t1->getVertice(0)->pos;
    v1 = t1->getVertice(1)->pos;
    v2 = t1->getVertice(2)->pos;
  }
  return v0 + alpha * (v1 - v0) + beta * (v2 - v0);
}

float AreaLight::computeIntensity(const vec3& pos, const vec3& norm, vec3& dir, float& dis) {
  vec3 position = sampleLight();
  vec3 toLight = position - pos;
  float bright = intensity / (length(toLight) * length(toLight));
  float cosi = dot(normalize(toLight), norm);
  float Li = bright * fmax(cosi, 0);

  dir = normalize(toLight);
  dis = length(toLight);
  return Li;
}
//
// vec3 AreaLight::computeToLightDir(const vec3 &pos) {
//   vec3 toLight = position - pos;
//   toLight = normalize(toLight);
//   return toLight;
// }
//
// float AreaLight::computeToLightDis(const vec3 &pos) {
//   return length(position - pos);
// }
