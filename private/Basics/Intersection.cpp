#include "Intersection.h"

Intersection::Intersection() {
  hitDis = 1e10;
  mtl = 0;
}

void Intersection::computeTangents() {
  tangentU = cross(vec3(0.0f, 1.0f, 0.0f), norm);
  if(length(tangentU) < 0.0001f)
    tangentU = cross(vec3(1.0f, 0.0f, 0.0f), norm);
  tangentU = normalize(tangentU);
  tangentV = normalize(cross(tangentU, norm));
}
