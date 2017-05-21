#pragma once

#include "Ray.h"
#include "Intersection.h"

class Object {
public:
  virtual ~Object() {};

  virtual bool intersect(const Ray &ray, Intersection &hit) = 0;
};
