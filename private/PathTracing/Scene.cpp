#include "Scene.h"

#include <iostream>

Scene::Scene() {
  skyColor.set(0.2f, 0.2f, 0.5f);
}

void Scene::addObject(Object& obj) {
  objects.push_back(&obj);
}

void Scene::addLight(Light& light) {
  lights.push_back(&light);
}

void Scene::setSkyColor(const Color skyColor) {
  this->skyColor = skyColor;
}

///////////////////////
// Getters
///////////////////////
int Scene::getNumLights() {
  return lights.size();
}

Light* Scene::getLight(int i) {
  // * here dereference the light pointer
  return lights[i];
}

Color Scene::getSkyColor() {
  return skyColor;
}

bool Scene::intersect(const Ray& ray, Intersection& hit) {
  bool success = false;
  for(unsigned int i=0; i < objects.size(); i++) {
    if(objects[i]->intersect(ray, hit)) success = true;
  }
  return success;
}
