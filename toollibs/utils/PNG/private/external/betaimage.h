#ifndef _BETAIMAGE_H
#define _BETAIMAGE_H


typedef struct Color {
  long red;
  long green;
  long blue;
} Color;


typedef struct BetaImage {
  long width;
  long height;
  long rowbytes;
  long pixel_size;
  long palette_size;
  Color *palette;
  void *data;
  int alpha;
} BetaImage;






#endif
