#include "LambertMaterial.h"

#include <iostream>

LambertMaterial::LambertMaterial() {
  rand = Random(true);
}

void LambertMaterial::setColor(const Color& c) {
  diffuse = c;
}

void LambertMaterial::generateSample(const Intersection &hit, Ray &in,
  Color &col, vec3 &out) {

  float s = rand.next();
  float t = rand.next();
  float u = 2 * PI * s;
  float v = sqrt(1 - t);

  vec3 norm = hit.norm;
  vec3 u_ = hit.tangentU;
  vec3 v_ = hit.tangentV;

  out = v * cosf(u) * u_ + (float)sqrt(t) * norm + v * sinf(u) * v_;

  col.set(diffuse);
}

Color LambertMaterial::computeReflectance(const Intersection &hit, const vec3 &in,
  const vec3 &out) {
  return diffuse;
}
