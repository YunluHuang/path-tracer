#include "Sphere.h"
#include "LambertMaterial.h"

#include <iostream>

void Sphere::init(const vec3& position, float radius, Material* material) {
  pos = position;
  r = radius;
  if(mtl == nullptr) mtl = new LambertMaterial();
  mtl = material;
}

bool Sphere::intersect(const Ray& ray, Intersection& hit) {
  vec3 o = ray.org;
  vec3 d = ray.dir;
  vec3 p = pos;
  float b = 2 * dot(d, (o - p));
  float c = length(o - p) * length(o - p) - r * r;
  float delta = b * b - 4 * c;

  if(delta <= 0) return false;

  float t0 = (-b + sqrt(delta)) / 2;
  float t1 = (-b - sqrt(delta)) / 2;

  if(t0 < 0 && t1 < 0) return false;

  float t;
  if(t0 < t1) {
    t = t0 < 0 ? t1 : t0;
  } else {
    t = t1 < 0 ? t0 : t1;
  }

  if(hit.hitDis > t) {
    hit.hitDis = t;
    hit.pos = o + d * t;
    hit.norm = normalize(hit.pos - p);
    hit.mtl = mtl;
    return true;
  }
  return false;
}
