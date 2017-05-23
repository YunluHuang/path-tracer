#include "FresnelMetalMaterial.h"

#include <iostream>

void FresnelMetalMaterial::setColor(const Color &c) {
  metalColor = c;
  n = 0.617;
  k = 2.63;
}

void FresnelMetalMaterial::generateSample(const Intersection &hit, const vec3 &in,
  Color &col, vec3 &out) {
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

Color FresnelMetalMaterial::computeReflectance(const Intersection &hit, const vec3 &in,
  const vec3 &out) {
  return Color::BLACK;
}
