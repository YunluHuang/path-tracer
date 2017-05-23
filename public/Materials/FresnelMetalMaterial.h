#pragma once

#include "Material.h"

class FresnelMetalMaterial: public Material {
private:
  float n;
  float k;
  Color metalColor;

public:
  virtual void setColor(const Color &c);
  virtual void generateSample(const Intersection &hit, const vec3 &in,
    Color &col, vec3 &out);
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out);
};
