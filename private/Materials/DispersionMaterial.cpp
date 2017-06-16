#include "DispersionMaterial.h"

#include <iostream>

DispersionMaterial::DispersionMaterial() {
  randGen = new Random(true);
}

float DispersionMaterial::getDispersionCol(Color& col) {
  float pick = randGen->next();
  if(pick < 0.16f) {
    Color c = Color(1.0f, 0.0f, 0.0f);
    col *= c;
    return 0.69f;
  } else if(pick < 0.33f) {
    Color c = Color(1.0f, 237.0f / 255.0f, 0.0f);
    col *= c;
    return 0.615f;
  } else if(pick < 0.5f) {
    Color c = Color(1.0f, 1.0f, 0.0f);
    col *= c;
    return 0.58f;
  } else if(pick < 0.67f) {
    Color c = Color(0.0f, 1.0f, 0.0f);
    col *= c;
    return 0.505f;
  } else if(pick < 0.83f) {
    Color c = Color(0.0f, 1.0f, 1.0f);
    col *= c;
    return 0.49f;
  } else {
    Color c = Color(118.0f / 255.0f, 0.0f, 237.0f / 255.0f);
    col *= c;
    return 0.415f;
  }
}

void DispersionMaterial::setIndex(const float B, const float C) {
  this->B = B;
  this->C = C;
}

void DispersionMaterial::setColor(const Color &c) {
  color = c;
}

void DispersionMaterial::generateSample(const Intersection &hit, Ray &in,
  Color &col, vec3 &out) {

    col = color;

    vec3 d = -in.dir;
    vec3 norm = hit.norm;

    float nt, ni;

    if(dot(d, norm) < 0.0f) {
      // std::cout << "inside: ior = " << in.ior << std::endl;
      norm = -hit.norm;
      ni = in.ior;
      nt = 1.0f;
    } else {
      float waveLength = getDispersionCol(col);
      in.ior = B + C / (waveLength * waveLength);
      nt = in.ior;
      ni = 1.0f;
    }

    vec3 r = 2 * dot(d, norm) * norm - d;
    vec3 z = ni / nt * (dot(d, norm) * norm - d);
    if(length(z) > 1.0f) {
      // std::cout << "internal refelction" << std::endl;
      out = r;
      return;
    } else {
      vec3 t = z - (float)sqrt(1 - length(z) * length(z)) * norm;

      float rpar = (nt * dot(norm, d) + ni * dot(norm, t)) / (nt * dot(norm, d) - ni * dot(norm, t));
      float rperp = (ni * dot(norm, d) + nt * dot(norm, t)) / (ni * dot(norm, d)- nt * dot(norm, t));
      float ft = 1.0f - 0.5f * (rpar * rpar + rperp * rperp);

      float pick = randGen->next();
      if(pick < ft) {
        // std::cout << "transmission" << std::endl;
        out = t;
      } else {
        // std::cout << "refelction" << std::endl;
        out = r;
      }
    }
}

Color DispersionMaterial::computeReflectance(const Intersection &hit, const vec3 &in,
  const vec3 &out) {
    // float ni = 1.0f;
    // float nt = n;
    // vec3 d = in;
    // vec3 norm = hit.norm;
    //
    // if(dot(d, norm) < 0.0f) {
    //   norm = -hit.norm;
    //   ni = n;
    //   nt = 1.0f;
    // }
    //
    // vec3 r = 2 * dot(d, norm) * norm - d;
    // vec3 z = ni / nt * (dot(d, norm) * norm - d);
    // if(length(z) > 1.0f) {
    //   return Color::BLACK;
    // } else {
    //   vec3 t = z - (float)sqrt(1 - length(z) * length(z)) * norm;
    //
    //   float rpar = (nt * dot(norm, d) + ni * dot(norm, t)) / (nt * dot(norm, d) - ni * dot(norm, t));
    //   float rperp = (ni * dot(norm, d) + nt * dot(norm, t)) / (ni * dot(norm, d)- nt * dot(norm, t));
    //   float ft = 1.0f - 0.5f * (rpar * rpar + rperp * rperp);
    //
    //   float pick = randGen->next();
    //   if(pick < ft) {
    //     return Color::WHITE;
    //   } else {
    //     return Color::BLACK;
    //   }
    // }
    return Color::BLACK;
}
