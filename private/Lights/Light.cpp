#include "Light.h"

Light::Light() {
  intensity = 1.0;
  baseColor = Color::WHITE;
}

void Light::setBaseColor(const Color& color) {
  baseColor = color;
}

void Light::setIntensity(float i) {
  intensity = i;
}

Color Light::getBaseColor() {
  return baseColor;
}

float Light::getIntensity() {
  return intensity;
}
