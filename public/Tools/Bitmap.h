#pragma once

class Bitmap {
private:
  int xRes;
  int yRes;
  int* pixel;

public:
  Bitmap(int x, int y);
  ~Bitmap();

  int getXRes() const;
  int getYRes() const;
  int& getPixel(int x, int y);
  
  void setPixel(int x, int y, int pix);

  bool saveBMP(const char* filename);
};
