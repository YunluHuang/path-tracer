#pragma once

#include "Light.h"

class PointLight: public Light {
private:
  vec3 position;

public:
  PointLight();

  void setPosition(const vec3& pos);

  virtual float computeIntensity(const vec3 &pos, const vec3 &norm);
  virtual vec3 computeToLightDir(const vec3 &pos);
  virtual float computeToLightDis(const vec3 &pos);
};
