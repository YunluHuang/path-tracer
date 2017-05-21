#include "Triangle.h"

#include <iostream>
Triangle::Triangle() {}

void Triangle::init(Vertex* v0, Vertex* v1, Vertex* v2, Material* m) {
  vertices[0] = v0;
  vertices[1] = v1;
  vertices[2] = v2;
  material = m;
}

Vertex* Triangle::getVertice(int idx) {
  return vertices[idx];
}

vec3 Triangle::computeCenter() {
  vec3 a = vertices[0]->pos;
  vec3 b = vertices[1]->pos;
  vec3 c = vertices[2]->pos;
  return (a + b + c)/3.0f;
}

bool Triangle::intersect(const Ray& ray, Intersection& hit) {
  vec3 a = vertices[0]->pos;
  vec3 b = vertices[1]->pos;
  vec3 c = vertices[2]->pos;

  vec3 d = ray.dir;
  vec3 p = ray.org;

  float dM = dot(-d, cross(b-a, c-a));

  if(dM == 0.0f) return false;

  float t = dot((p-a), cross(b-a, c-a)) / dM;

  if(t > 0.001f) {
    float al = dot(-d, cross(p-a, c-a)) / dM;
    float be =  dot(-d, cross(b-a, p-a)) / dM;
    vec3 hitPos = p + t * d;
    float hitDis = length(hitPos - p);
    if( al > 0 && al < 1 &&
        be > 0 && be < 1 &&
        (al+be) < 1) {

      if(hitDis < hit.hitDis) {
        hit.hitDis = hitDis;
        hit.pos = hitPos;
        if(vertices[0]->norm != vec3(0) || vertices[1]->norm != vec3(0) ||
           vertices[2]->norm != vec3(0)) {
          hit.norm = (1 - al - be)*vertices[0]->norm + al*vertices[1]->norm +
                     be*vertices[2]->norm;
        } else {
          hit.norm = normalize(cross(b-a, c-a));
        }
        hit.mtl = material;
        return true;
      }
    }
  }
  return false;
}
