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

  hit.computeTangents();

  if(hit.mtl->hasEmission()) {
    vec3 dummy;
    hit.shade = hit.mtl->computeReflectance(hit, dummy, dummy);
    return true;
  }

  for(int i = 0; i < scene->getNumLights(); i++) {
    Light* light = scene->getLight(i);

    if(isBlocked(hit, light, time)) continue;

    directLight = light->computeIntensity(hit.pos, hit.norm) * (light->getBaseColor());
    vec3 lightDir = light->computeToLightDir(hit.pos);
    hit.shade += directLight * hit.mtl->computeReflectance(hit, lightDir, -ray.dir);
  }

  if(depth == maxDepth) return true;

  Color outColor;
  vec3 outDir;
  vec3 inDir = normalize(-ray.dir);
  hit.mtl->generateSample(hit, inDir, outColor, outDir);

  Intersection newHit;
  Ray newRay;
  newRay.org = hit.pos + 0.001f * outDir;
  newRay.dir = outDir;
  newRay.t = time;
  traceRay(newRay, newHit, depth + 1);
  indirectColor = newHit.shade * outColor;

  hit.shade += indirectColor;

  return true;
}

bool PathTrace::isBlocked(Intersection& hit, Light* light, float time) {
  Ray shadowRay;
  vec3 dir = light->computeToLightDir(hit.pos);
  shadowRay.org = hit.pos + 0.001f * dir;
  shadowRay.dir = dir;
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
