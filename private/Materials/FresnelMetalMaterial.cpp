#include "FresnelMetalMaterial.h"

#include <iostream>

void FresnelMetalMaterial::setColor(const Color &c) {
  metalColor = c;
  n = 0.617;
  k = 2.63;
}

void FresnelMetalMaterial::computeReflectance(Color &col, const vec3 &in,
  vec3 &out, const Intersection &hit) {
  //for indentation
  out = 2 * std::abs(dot(in, hit.norm)) * hit.norm - in;
  float nd = std::abs(dot(hit.norm, in));
  float nk = (n * n + k * k);
  float r1 = ((nk * nd * nd) - 2 * n * nd + 1) /
             ((nk * nd * nd) + 2 * n * nd + 1);
  float r2 = (nk + nd * nd - 2 * n * nd) /
             (nk + nd * nd + 2 * n * nd);
  float fr = 0.5f * (r1 + r2);

  if(dot(in, hit.norm) <= 0) fr = 0.0;

  col.set(metalColor);
}

Color FresnelMetalMaterial::getRefelction() {
  return Color::BLACK;
}
