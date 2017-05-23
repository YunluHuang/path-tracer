#include "Bitmap.h"

#include <stdio.h>
#include <iostream>

struct BitmapHeader {
  int FileSize;
  int Reserved;
  int StartAddress;
  int HeaderSize;
  short Width;
  short Height;
  short ColorPlanes;
  short BitsPerPixel;
};

Bitmap::Bitmap(int x, int y) {
  xRes = x;
  yRes = y;
  pixel = new int[xRes * yRes];
}

int Bitmap::getXRes() const {
  return xRes;
}

int Bitmap::getYRes() const {
  return yRes;
}

int& Bitmap::getPixel(int x, int y) {
  return pixel[y*xRes + x];
}

void Bitmap::setPixel(int x, int y, int pix) {
  pixel[x+y*xRes] = pix;
}

bool Bitmap::saveBMP(const char* filename) {
  BitmapHeader head;
  head.FileSize = sizeof(BitmapHeader) + 2 + xRes*yRes*sizeof(int);
  head.Reserved = 0;
  head.StartAddress=sizeof(BitmapHeader)+2;

	head.HeaderSize=12;
	head.Width=xRes;
	head.Height=yRes;
	head.ColorPlanes=1;
	head.BitsPerPixel=32;

  // for(int i = 0; i < xRes * yRes; i++) {
  //   fprintf(stderr, "%i\n", pixel[i]);
  // }

	FILE *f=0;
	f = fopen(filename,"wb");
	if(f==0) {
		printf("Can't open '%s'\n",filename);
		return false;
	}
	short magic=19778;
	fwrite(&magic,sizeof(short),1,f);
	fwrite(&head,sizeof(BitmapHeader),1,f);
  //std::cout<<"bitmap"<<std::endl;
  //for(int i = 0; i<xRes*yRes; i++) std::cout<<pixel[i]<<std::endl;
	fwrite(pixel,sizeof(int),xRes*yRes,f);
	fclose(f);
	return true;
}

Bitmap::~Bitmap() {
  if(pixel != 0) {
    delete []pixel;
    pixel = 0;
  }
}
