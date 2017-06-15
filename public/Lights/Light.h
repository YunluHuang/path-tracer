#pragma once

#include "Color.h"
#include "Intersection.h"

#include "glm/glm.hpp"

typedef glm::vec3 vec3;

class Light {
protected:
  Color baseColor;
  float intensity;

public:
  Light();

  void setBaseColor(const Color &color);
  void setIntensity(float i);

  Color getBaseColor();
  float getIntensity();

  virtual float computeIntensity(const vec3& pos, const vec3& norm, vec3& dir, float& dis)= 0;
};
