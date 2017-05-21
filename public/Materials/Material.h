#pragma once

#include "Intersection.h"

#define PI 3.1415926f

class Material {
public:
  virtual void setColor(const Color &c) = 0;
  virtual void computeReflectance(Color &col, const vec3 &in, vec3 &out,
    const Intersection &hit) = 0;
  virtual Color getRefelction() = 0;
};
