#pragma once

#include "Material.h"
#include "Random.h"

class DieletricMaterial: public Material {
private:
  Color color;
  float n;
  Random *randGen;

public:
  DieletricMaterial();
  void setIndex(const float n);

  virtual void setColor(const Color &c);
  virtual void generateSample(const Intersection &hit, Ray &in,
    Color &col, vec3 &out);
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out);
};
