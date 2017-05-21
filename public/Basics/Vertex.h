#pragma once

#include "glm/glm.hpp"

typedef glm::vec3 vec3;

class Vertex {
public:
  vec3 pos;
  vec3 norm;
  vec3 tCoord;

public:
  Vertex();
  void set(const vec3 &pos, const vec3 &norm, const vec3 &tCoord);
};
