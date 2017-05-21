#pragma once

#include <stdint.h>
#include <float.h>

class Random {
private:
  uint64_t seed;
  uint64_t num;
  bool xHalf;

public:
  Random();
  Random(bool enableRandomSeed);

  float next();
};
