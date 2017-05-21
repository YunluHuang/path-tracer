#pragma once

#include "Light.h"

class DirectLight: public Light {
private:
 vec3 direction;

public:
 DirectLight();

  void setDirection(const vec3& dir);
  vec3 getDirection();

  virtual float computeIntensity(const vec3& pos, const vec3& norm);
  virtual vec3 computeToLightDir(const vec3& pos);
  virtual float computeToLightDis(const vec3 &pos);
};
