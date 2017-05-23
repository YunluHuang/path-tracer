#pragma once

#include "Intersection.h"
#include "Random.h"

#define PI 3.1415926f

class Material {
public:
  virtual void setColor(const Color &c) = 0;
  virtual void generateSample(const Intersection &hit, const vec3 &in,
    Color &col, vec3 &out) = 0;
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out) = 0;
};
