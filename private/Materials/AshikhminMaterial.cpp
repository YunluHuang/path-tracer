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

void AshikhminMaterial::generateSample(const Intersection &hit, Ray &in,
  Color &col, vec3 &out) {
      // generate k1
      float i = rand.next();
      float s = rand.next();
      float t = rand.next();
      if(i < specularLvl / (specularLvl + diffuseLvl)) {
        float phi = atan(sqrt((nu + 1.0f) / (nv + 1.0f)) * tanf(PI * s / 2.0f));
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

        h = normalize(h);
        vec3 k2 = in.dir + 2.0f * dot(-in.dir, h) * h;
        out = normalize(k2);
        if(dot(n, k2) < 0.0f) {
          col = Color::BLACK;
        } else {
          float phh = (sqrt((nu + 1.0f) * (nv + 1.0f)) / 2.0f) * pow(dot(n, h), nu * cosf(phi) * cosf(phi) + nv * sinf(phi) * sinf(phi));
          float pk2 = phh / (4.0f * dot(-in.dir, h));
          col = specular * specularLvl;
        }
      } else {
        float u = 2 * PI * s;
        float v = sqrt(1 - t);

        vec3 norm = hit.norm;
        vec3 u_ = hit.tangentU;
        vec3 v_ = hit.tangentV;

        out = v * cosf(u) * u_ + (float)sqrt(t) * norm + v * sinf(u) * v_;
        col = diffuse * diffuseLvl;
      }

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
    float nk1 = dot(n, k1);
    float nk2 = dot(n, k2);

    Color ps;
    if (nh <= 0.0f) {
      ps = Color::BLACK;
    }
    else {
      float psCache1 = (float) sqrt((nu + 1) * (nv + 1)) / 8.0f;
      float psCache2 = pow(nh, (nu * hu * hu + nv * hv * hv) / (1 - nh * nh));
      float psCache3 = hk * fmax(nk1, nk2);
      float fkh = specularLvl + (1.0f - specularLvl) * pow((1 - hk), 5);
      ps = psCache1 * psCache2 / psCache3 * fkh * specular;
    }

    //compute pd
    float pdCache1 = 1 - pow(1 - nk1 / 2.0f, 5);
    float pdCache2 = 1 - pow(1 - nk2 / 2.0f, 5);

    Color pd = (28 * diffuseLvl / (23.0f)) * (1.0f - specularLvl) * pdCache1 * pdCache2 * diffuse;

    return ps + pd;
}

void AshikhminMaterial::setSpecularLevel(float slvl) {
  specularLvl = slvl;
}

void AshikhminMaterial::setDiffuseLevel(float dlvl) {
  diffuseLvl = dlvl;
}

void AshikhminMaterial::setSpecularColor(Color spCol) {
  specular = spCol;
}

void AshikhminMaterial::setDiffuseColor(Color dCol) {
  diffuse = dCol;
}

void AshikhminMaterial::setRoughness(float nu, float nv) {
  this->nu = nu;
  this->nv = nv;
}
