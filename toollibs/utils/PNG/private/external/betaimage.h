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



typedef struct BetaPalette {
  Color colormap[256];
  long ncolors;
  unsigned char rgbmap[32768];
  unsigned char xpixel[256];
  int special_set;
  Color special;
} BetaPalette;


int BetaCreateImage(BetaImage *image, 
		    long width, 
		    long height,
		    long pixel_size,
		    void *data);

long BetaAllocColor (BetaPalette *palette, Color *color, Color* actual);
void BetaDitherImage (BetaPalette *palette, BetaImage *image);

void BetaDitherImage24To8 (BetaPalette *palette, 
			   BetaImage *image, 
			   BetaImage *image8);

void MakeColorMap1(BetaPalette *palette);
void BetaInitRGBmap(BetaPalette *palette);

#endif
