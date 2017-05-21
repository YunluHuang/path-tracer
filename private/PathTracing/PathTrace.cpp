#include "PathTrace.h"

#include <iostream>

PathTrace::PathTrace(Scene& scene) {
  this->scene = &scene;
  maxDepth = 10;
}

bool PathTrace::traceRay(Ray& ray, Intersection& hit, int depth) {
  float time = ray.t;

  hit.shade = Color::BLACK;
  Color directLight = Color::BLACK;
  Color indirectColor = Color::BLACK;

  if(scene->intersect(ray, hit) == false) {
    hit.shade = scene->getSkyColor();
    return false;
  }

  for(int i = 0; i < scene->getNumLights(); i++) {
    Light* light = scene->getLight(i);

    if(isBlocked(hit, light, time)) continue;

    directLight += (light->computeIntensity(hit.pos, hit.norm) * light->getBaseColor());
  }

  hit.shade += directLight * hit.mtl->getRefelction();

  if(depth == maxDepth) return true;

  Color outColor;
  vec3 outDir;
  vec3 inDir = normalize(-ray.dir);
  hit.mtl->computeReflectance(outColor, inDir, outDir, hit);

  Intersection newHit;
  Ray newRay;
  newRay.org = hit.pos;
  newRay.dir = outDir;
  newRay.t = time;
  traceRay(newRay, newHit, depth + 1);
  indirectColor = newHit.shade * outColor;

  hit.shade += indirectColor;

  return true;
}

bool PathTrace::isBlocked(Intersection& hit, Light* light, float time) {
  Ray shadowRay;
  shadowRay.org = hit.pos;
  shadowRay.dir = light->computeToLightDir(hit.pos);
  shadowRay.t = time;

  Intersection shadowHit;
  if(scene->intersect(shadowRay, shadowHit)) {
    float lightDis = light->computeToLightDis(hit.pos);
    if( 0 < shadowHit.hitDis && shadowHit.hitDis < lightDis) {
        return true;
    }
  }
  return false;
}
