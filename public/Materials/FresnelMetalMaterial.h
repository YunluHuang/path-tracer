#pragma once

#include "Material.h"

class FresnelMetalMaterial: public Material {
private:
  float n;
  float k;
  Color metalColor;

public:
  virtual void setColor(const Color &c);
  virtual void computeReflectance(Color &col, const vec3 &in, vec3 &out,
    const Intersection &hit);
  virtual Color getRefelction();
};
