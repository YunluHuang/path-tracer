#pragma once

#include "Material.h"

class DispersionMaterial: public Material {
private:
  Color color;
  float B;
  float C;
  Random *randGen;

  float getDispersionCol(Color& col);

public:
  DispersionMaterial();
  void setIndex(const float B, const float C);

  virtual void setColor(const Color &c);
  virtual void generateSample(const Intersection &hit, Ray &in,
    Color &col, vec3 &out);
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out);
};
