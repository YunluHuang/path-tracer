#include "Color.h"

Color::Color() {
  r = g = b = 1.0;
}

Color::Color(float r, float g, float b) {
  set(r, g, b);
}

////////////////////////////////////////////////////////////////////////////////

void Color::set(float r, float g, float b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

void Color::set(const Color& color) {
  set(color.r, color.g, color.b);
}

////////////////////////////////////////////////////////////////////////////////

int Color::toInt() {
  int ri = (r < 0) ? 0 : ((r >= 1.0) ? 255 : int(r*256.0f));
  int gi = (g < 0) ? 0 : ((g >= 1.0) ? 255 : int(g*256.0f));
  int bi = (b < 0) ? 0 : ((b >= 1.0) ? 255 : int(b*256.0f));
  return (ri << 16) | (gi << 8) | bi;
}

void Color::fromInt(int c) {
  float r = ((c >> 16) & 0xff) / 255.0f;
  float g = ((c >> 8) & 0xff) / 255.0f;
  float b = (c & 0xff) / 255.0f;
  set(r, g, b);
}

////////////////////////////////////////////////////////////////////////////////
// static colors
////////////////////////////////////////////////////////////////////////////////
Color Color::WHITE(1.0,1.0,1.0);
Color Color::GREY(0.25,0.25,0.25);
Color Color::BLACK(0.0,0.0,0.0);
Color Color::RED(1.0,0.0,0.0);
Color Color::YELLOW(1.0,1.0,0.0);
Color Color::BLUE(0.0,0.0,1.0);
Color Color::GREEN(0.0,0.75,0.0);

////////////////////////////////////////////////////////////////////////////////

Color & Color::operator*=(const Color &c) {
  const Color originC = *this;
  *this = originC * c;
  return *this;
}

Color & Color::operator*=(const float s) {
  const Color originC = *this;
  *this = originC * s;
  return *this;
}

Color & Color::operator/=(const Color &c) {
  const Color originC = *this;
  *this = originC / c;
  return *this;
}

Color & Color::operator/=(const float s) {
  const Color originC = *this;
  *this = originC / s;
  return *this;
}

Color & Color::operator+=(const Color &c) {
  const Color originC = *this;
  *this = originC + c;
  return *this;
}

Color & Color::operator-=(const Color &c) {
  const Color originC = *this;
  *this = originC - c;
  return *this;
}

Color operator*(const Color &c, const float s) {
  Color rt;
  rt.r = c.r * s;
  rt.g = c.g * s;
  rt.b = c.b * s;
  return rt;
}

Color operator*(const float s, const Color &c){
  return c * s;
}

Color operator*(const Color &lc, const Color &rc) {
  return Color(lc.r * rc.r, lc.g * rc.g, lc.b * rc.b);
}

Color operator/(const Color &c, const float s) {
  return c * (1 / s);
}

Color operator/(const Color &lc, const Color &rc) {
  return Color(lc.r / rc.r, lc.g / rc.g, lc.b / rc.b);
}


Color operator+(const Color &lc, const Color& rc) {
  return Color(lc.r + rc.r, lc.g + rc.g, lc.b + rc.b);
}

Color operator-(const Color &lc, const Color &rc) {
  return Color(lc.r - rc.r, lc.g - rc.g, lc.b - rc.b);
}
