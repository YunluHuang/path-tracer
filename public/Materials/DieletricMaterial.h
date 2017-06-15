#pragma once

#include "Material.h"
#include "Random.h"

class DieletricMaterial: public Material {
private:
  Color color;
  float n;
  Random *randGen;

  void computePossibility(float& ft, float& fr, bool inside);

public:
  DieletricMaterial();
  void setIndex(const float n);

  virtual void setColor(const Color &c);
  virtual void generateSample(const Intersection &hit, const vec3 &in,
    Color &col, vec3 &out);
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out);
};
