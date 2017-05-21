#pragma once

#include "Color.h"
#include "glm/glm.hpp"

typedef glm::vec3 vec3;

class Material;

class Intersection {
public:
  float hitDis;
  vec3 pos;
  vec3 norm;
  Material* mtl;
  Color shade;

public:
  Intersection();
};
