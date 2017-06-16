#pragma once

#include "Material.h"

class LambertMaterial: public Material {
private:
  Random rand;
  Color diffuse;

public:
  LambertMaterial();

  virtual void setColor(const Color &c);
  virtual void generateSample(const Intersection &hit, Ray &in,
    Color &col, vec3 &out);
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out);
  // virtual bool hasEmission();

};
