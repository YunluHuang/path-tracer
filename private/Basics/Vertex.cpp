#include "Vertex.h"

Vertex::Vertex() {
  norm = vec3(0);
  hasNorm = 0;
}

void Vertex::set(const vec3 &pos, const vec3 &norm, const vec3 &tCoord) {
  this->pos = pos;
  if(norm.x == 0.0f && norm.y == 0.0f && norm.z == 0.0f) hasNorm = false;
  this->norm = norm;
  this->tCoord = tCoord;
}
