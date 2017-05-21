#pragma once

class Color {
public:
  float r, g, b;

  static Color WHITE, GREY, BLACK;
  static Color RED, YELLOW, BLUE, GREEN;

public:
  Color();
  Color(float r, float g, float b);

  void set(float r, float g, float b);
  void set(const Color &color);

  int toInt();
  void fromInt(int c);

  Color & operator*=(const Color &c);
  Color & operator*=(const float s);
  Color & operator/=(const Color &c);
  Color & operator/=(const float s);
  Color & operator+=(const Color &c);
  Color & operator-=(const Color &c);

};

Color operator*(const Color &c, const float s);
Color operator*(const float s, const Color &c);
Color operator*(const Color &lc, const Color &rc);

Color operator/(const Color &c, const float s);
Color operator/(const Color &lc, const Color &rc);

Color operator+(const Color &lc, const Color &rc);
Color operator-(const Color &lc, const Color &rc);
