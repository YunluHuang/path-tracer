#include "AshikhminMaterial.h"
#include <iostream>

AshikhminMaterial::AshikhminMaterial() {
  rand = Random(true);
  specularLvl = 0.0f;
  diffuseLvl = 0.0f;
  diffuse = Color::BLACK;
  specular = Color::BLACK;
  nu = 0;
  nv = 0;
}

void AshikhminMaterial::setColor(const Color &c) {
  return;
}

void AshikhminMaterial::generateSample(const Intersection &hit, const vec3 &in,
  Color &col, vec3 &out) {
      // generate k1
      float i = rand.next();
      if(i < specularLvl / (specularLvl + diffuseLvl)) {
      float s = rand.next();
      float t = rand.next();
      float phi = atan(sqrt((nu + 1) / (nv + 1)) * tanf(PI * s / 2.0f));
      if(s >= 0.25 && s < 0.5) {
        phi = PI - phi;
      } else if(s >= 0.5 && s < 0.75) {
        phi = PI + phi;
      } else if(s >= 0.75 && s < 1) {
        phi = 2 * PI - phi;
      }
      float cosTheta = (float) pow(1.0f - t, 1.0f / (nu * cosf(phi) * cosf(phi) + nv * sinf(phi) * sinf(phi) + 1));
      float sinTheta = (float) sqrt(1 - cosTheta * cosTheta);

      vec3 x = hit.tangentU;
      vec3 y = hit.tangentV;
      vec3 n = hit.norm;
      vec3 h = cosTheta * n + sinTheta * (cosf(phi) * x + sinf(phi) * y);

      float pk2 = 0.0f;
      float ph = 0.0f;
      h = normalize(h);
      vec3 k2 = -in + 2.0f * dot(in, h) * h;
      if(dot(n, k2) > 0.0f) {
        ph = sqrt((nu + 1) * (nv + 1)) / (2 * PI) * pow(dot(n, h), nu * cos(phi) * cos(phi) + nv * sin(phi) * sin(phi));
        pk2 = ph / (4 * dot(in, h));
        out = normalize(k2);
      }
      float nh = dot(n, h);
      col = (specular * pk2 * specularLvl + diffuse * diffuseLvl) / (1 + pk2);
    }
    // fprintf(stderr, "nh = %f, ph = %f, pk2 = %f\n", nh, ph, pk2);
    // float s = rand.next();
    // float t = rand.next();
    // float u = 2 * PI * s;
    // float v = sqrt(1 - t);
    //
    // vec3 norm = hit.norm;
    // vec3 u_ = hit.tangentU;
    // vec3 v_ = hit.tangentV;
    //
    // out = v * cosf(u) * u_ + (float)sqrt(t) * norm + v * sinf(u) * v_;
}

Color AshikhminMaterial::computeReflectance(const Intersection &hit, const vec3 &in,
  const vec3 &out) {

    // fprintf(stderr, "computeRelectance\n");

    vec3 k1 = normalize(in);
    vec3 k2 = normalize(out);
    vec3 h = normalize(k1 + k2);
    vec3 n = hit.norm;
    vec3 u = hit.tangentU;
    vec3 v = hit.tangentV;

    //compute ps
    float nh = dot(n, h);
    float hu = dot(h, u);
    float hv = dot(h, v);
    float hk = dot(h, k1);
    float kh = dot(k1, h);
    float nk1 = dot(n, k1);
    float nk2 = dot(n, k2);

    Color ps;
    if (nh <= 0.0f) {
      ps = Color::BLACK;
    }
    else {
      float psCache1 = (float) sqrt((nu + 1) * (nv + 1)) / (8);
      float psCache2 = pow(nh, (nu * hu * hu + nv * hv * hv) / (1 - nh * nh));
      float psCache3 = hk * fmax(nk1, nk2);
      float fkh = specularLvl + diffuseLvl * pow((1 - kh), 5);
      ps = psCache1 * psCache2 / psCache3 * specular;
    }

    //compute pd
    float pdCache1 = 1 - pow(1 - nk1 / 2.0f, 5);
    float pdCache2 = 1 - pow(1 - nk2 / 2.0f, 5);

    Color pd = (28 * diffuseLvl / (23)) * diffuseLvl * pdCache1 * pdCache2 * diffuse;

    return ps + pd;
}

void AshikhminMaterial::setSpecularLevel(float slvl) {
  specularLvl = slvl;
}

void AshikhminMaterial::setDiffuseLevel(float dlvl) {
  diffuseLvl = dlvl;
}

void AshikhminMaterial::setSpecularColor(Color sCol) {
  specular = sCol;
}

void AshikhminMaterial::setDiffuseColor(Color dCol) {
  diffuse = dCol;
}

void AshikhminMaterial::setRoughness(float nu, float nv) {
  this->nu = nu;
  this->nv = nv;
}
