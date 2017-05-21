#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>

class Scene {
private:
  std::vector<Object*> objects;
  std::vector<Light*> lights;
  Color skyColor;

public:
  Scene();

  void addObject(Object &object);
  void addLight(Light &light);
  void setSkyColor(const Color sky);

  int getNumLights();
  Light* getLight(int i);
  Color getSkyColor();

  bool intersect(const Ray& ray, Intersection& hit);

};
