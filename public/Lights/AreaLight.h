#pragma once

#include "Light.h"
#include "Triangle.h"
#include "Random.h"

class AreaLight: public Light {
  private:
    Triangle * t0;
    Triangle * t1;
    float area;
    Random *randGen;

    vec3 sampleLight();

  public:
    AreaLight();
    void setAreaTris(Triangle* t0, Triangle* t1);

    virtual float computeIntensity(const vec3& pos, const vec3& norm, vec3&dir, float& dis);
    // virtual vec3 computeToLightDir(const vec3 &pos);
    // virtual float computeToLightDis(const vec3 &pos);
};
