#include "Random.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

Random::Random() {
  seed = UINT64_C(0x1234567812345678);
  num = seed;
  xHalf = true;
}

Random::Random(bool enableRandomSeed){
  long long int t = time(0)*time(0) + rand();
  seed = t;
  num = seed;
  xHalf = true;
}

float Random::next() {
  float rtNum = 0;
  if(xHalf) {
    xHalf = false;
    num ^= (num >> 21);
    num ^= (num << 35);
    num ^= (num >> 4);
    rtNum = (float)(num >> 32)/UINT32_MAX;
  } else {
    rtNum = (float)(num << 32 >> 32)/UINT32_MAX;
    xHalf = true;
  }
  return rtNum;
}
