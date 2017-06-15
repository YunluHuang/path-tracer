#include "DirectLight.h"

DirectLight::DirectLight() {
  direction = vec3();
}

void DirectLight::setDirection(const vec3 &dir) {
  direction = normalize(dir);
}

vec3 DirectLight::getDirection() {
  return direction;
}

float DirectLight::computeIntensity(const vec3 &pos, const vec3 &norm, vec3& dir, float& dis) {
  float cosi = dot(normalize(-direction), norm);
  float Li = intensity * fmax(cosi, 0);

  dir = normalize(-direction);
  vec3 lightPos = pos - (1000000.0f * direction);
  dis = length(lightPos - pos);
  return Li;
}

// vec3 DirectLight::computeToLightDir(const vec3 &pos) {
//   return normalize(-direction);
// }
//
// float DirectLight::computeToLightDis(const vec3 &pos) {
//   vec3 lightPos = pos - (1000000.0f * direction);
//   float dis = length(lightPos - pos);
//   return dis;
// }
