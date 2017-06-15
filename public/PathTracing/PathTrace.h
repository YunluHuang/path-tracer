#pragma once

#include "Ray.h"
#include "Scene.h"
#include "Material.h"
#include "Intersection.h"

class PathTrace{
private:
  Scene* scene;

  int maxDepth;
  int primaryRays;
  int secondaryRays;
  int shadowRays;

  // bool isBlocked(Intersection& hit, Light* light, float time);
  bool isBlocked(Intersection& hit, const vec3& toLight, const float lightDis, float time);

public:
  PathTrace(Scene& scene);

  bool traceRay(Ray& ray, Intersection& hit, int depth=1);

};
