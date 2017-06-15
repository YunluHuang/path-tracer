#include "DieletricMaterial.h"

#include <iostream>

DieletricMaterial::DieletricMaterial() {
  randGen = new Random(true);
}

void DieletricMaterial::setIndex(const float n) {
  this->n = n;
}

void DieletricMaterial::setColor(const Color &c) {
  color = c;
}

void DieletricMaterial::generateSample(const Intersection &hit, const vec3 &in,
  Color &col, vec3 &out) {

    col = color;

    float ni = 1.0f;
    float nt = n;
    vec3 d = in;
    vec3 norm = hit.norm;
    bool isInside = false;

    if(dot(d, norm) < 0.0f) {
      //std::cout << "inside" << std::endl;
      isInside = true;
      norm = -hit.norm;
      ni = n;
      nt = 1.0f;
    }

    vec3 r = 2 * dot(d, norm) * norm - d;
    vec3 z = ni / nt * (dot(d, norm) * norm - d);
    if(length(z) > 1.0f) {
      if(!isInside) std::cout << "reflect" << std::endl;
      out = r;
      return;
    } else {
      vec3 t = z - (float)sqrt(1 - length(z) * length(z)) * norm;

      float rpar = (nt * dot(norm, d) + ni * dot(norm, t)) / (nt * dot(norm, d) - ni * dot(norm, t));
      float rperp = (ni * dot(norm, d) + nt * dot(norm, t)) / (ni * dot(norm, d)- nt * dot(norm, t));
      float ft = 1.0f - 0.5f * (rpar * rpar + rperp * rperp);

      float pick = randGen->next();
      //std::cout << pick << std::endl;
      if(dot(norm, d) < cosf(80.0f / 180.0f * PI)) {
        //std::cout << "flat: ft = " << ft << ", pick = " << pick << std::endl;
      }
      if(pick < ft) {
        //std::cout << "transmission" << std::endl;
        out = t;
      } else {
        //std::cout << "reflection" << std::endl;
        out = r;
      }
    }
}

Color DieletricMaterial::computeReflectance(const Intersection &hit, const vec3 &in,
  const vec3 &out) {
    return Color::BLACK;
}

////////////////////////////////////////////////////////////////////////////////
