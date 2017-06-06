#include "EmissionMaterial.h"

void EmissionMaterial::setColor(const Color &c) {
  emission = c;
}

// void EmissionMaterial::generateSample(const Intersection &hit, const vec3 &in,
//   Color &col, vec3 &out) {}

Color EmissionMaterial::computeReflectance(const Intersection &hit, const vec3 &in,
  const vec3 &out) {
    return emission;
}

bool EmissionMaterial::hasEmission() {
  return true;
}
