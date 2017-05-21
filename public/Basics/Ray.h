#pragma once

#include <glm/glm.hpp>

typedef glm::vec3 vec3;

class Ray {
public:
  vec3 org;
  vec3 dir;
  float t;
};
