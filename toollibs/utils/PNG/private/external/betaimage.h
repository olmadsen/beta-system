#ifndef _BETAIMAGE_H
#define _BETAIMAGE_H

#include "betacolor.h"

typedef struct BetaImage {
  long width;
  long height;
  long rowbytes;
  long pixel_size;
  long palette_size;
  Color *palette;
  void *data;
} BetaImage;


int BetaCreateImage(BetaImage *image, 
		    long width, 
		    long height,
		    long pixel_size,
		    void *data);

int BetaImageToXImage(Display *display, BetaImage *image, XImage **ximage);


void BetaDitherImage (BetaImage *image);
void BetaOrderedDitherImage (BetaImage *image);
void BetaDitherImage24To8 (BetaImage *image, BetaImage *image8);

#endif
