#pragma once

#include "Material.h"
#include "Random.h"

class LambertMaterial: public Material {
private:
  Random rand;
  Color diffuse;

public:
  LambertMaterial();

  virtual void setColor(const Color &c);
  virtual void computeReflectance(Color &col, const vec3 &in, vec3 &out,
    const Intersection &hit);
  virtual Color getRefelction();
};
