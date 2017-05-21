#include "LambertMaterial.h"

#include <iostream>

LambertMaterial::LambertMaterial() {
  rand = Random(true);
}

void LambertMaterial::setColor(const Color& c) {
  diffuse = c;
}

void LambertMaterial::computeReflectance(Color &col, const vec3 &in, vec3 &out,
  const Intersection &hit) {

  float s = rand.next();
  float t = rand.next();
  float u = 2 * PI * s;
  float v = sqrt(1 - t);

  vec3 norm = hit.norm;
  vec3 u_ = normalize(cross(norm, norm + vec3(1.0f, 0.0f, 0.0f)));
  vec3 v_ = normalize(cross(norm, u_));

  out = v * cosf(u) * u_ + (float)sqrt(t) * norm + v * sinf(u) * v_;

  col.set(diffuse);
}

Color LambertMaterial::getRefelction() {
  return diffuse;
}
