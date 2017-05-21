#include "Vertex.h"

Vertex::Vertex() {
  norm = vec3(0);
}

void Vertex::set(const vec3 &pos, const vec3 &norm, const vec3 &tCoord) {
  this->pos = pos;
  this->norm = norm;
  this->tCoord = tCoord;
}
