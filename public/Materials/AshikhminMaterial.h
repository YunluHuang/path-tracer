#pragma once

#include "Material.h"

class AshikhminMaterial: public Material {
private:
  Random rand;
  float diffuseLvl;
  float specularLvl;
  Color diffuse;
  Color specular;
  float nu;
  float nv;


public:
  AshikhminMaterial();

  virtual void setColor(const Color &c);
  virtual void generateSample(const Intersection &hit, const vec3 &in,
    Color &col, vec3 &out);
  virtual Color computeReflectance(const Intersection &hit, const vec3 &in,
    const vec3 &out);

  void setSpecularLevel(float slvl);
  void setDiffuseLevel(float dlvl);
  void setSpecularColor(Color spCol);
  void setDiffuseColor(Color dCol);
  void setRoughness(float nu, float nv);
};
