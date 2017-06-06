#pragma once

#include "Material.h"

class EmissionMaterial: public Material {
private:
  Color emission;

public:
  virtual void setColor(const Color &c);
  virtual void generateSample(const Intersection &hit, const vec3 &in,
    Color &col, vec3 &out){};
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out);
  virtual bool hasEmission();

};
