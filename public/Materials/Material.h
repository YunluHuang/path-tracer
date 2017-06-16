#pragma once

#include "Intersection.h"
#include "Random.h"
#include "Ray.h"

#define PI 3.1415926f

class Material {
public:
  virtual void setColor(const Color &c) = 0;
  virtual void generateSample(const Intersection &hit, Ray &in,
    Color &col, vec3 &out) = 0;
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out) = 0;
  virtual bool hasEmission() {
    return false;
  };
};
