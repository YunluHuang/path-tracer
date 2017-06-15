#include "PointLight.h"

PointLight::PointLight() {
  position = vec3(0.0f, 0.0f, 0.0f);
}

void PointLight::setPosition(const vec3 &pos) {
  position = pos;
}

// float PointLight::computeIntensity(const vec3 &pos, const vec3 &norm) {
//   vec3 toLight = position - pos;
//   float bright = intensity / (length(toLight) * length(toLight));
//   float cosi = dot(normalize(toLight), norm);
//   float Li = bright * fmax(cosi, 0);
//   return Li;
// }

float PointLight::computeIntensity(const vec3& pos, const vec3& norm, vec3& dir, float& dis) {
  vec3 toLight = position - pos;
  float bright = intensity / (length(toLight) * length(toLight));
  float cosi = dot(normalize(toLight), norm);
  float Li = bright * fmax(cosi, 0);

  dir = normalize(toLight);
  dis = length(toLight);
  return Li;
}
//
// vec3 PointLight::computeToLightDir(const vec3 &pos) {
//   vec3 toLight = position - pos;
//   toLight = normalize(toLight);
//   return toLight;
// }
//
// float PointLight::computeToLightDis(const vec3 &pos) {
//   return length(position - pos);
// }
