#include "betadither.h"
#include "betapng.h"
#include <stdlib.h>

#define SWAP 1

static void SetBit(unsigned char *data, unsigned long n)
{
  unsigned long byte;
  unsigned long bit;
  unsigned char *ptr;
  unsigned char mask;
  
  byte = n >> 3;
  bit = n & 7;
  bit = bit;
  
  mask = 1 << bit;

  ptr = data + byte;
  *ptr = *ptr | mask;
  return;
}


int betaImage2Mask(BetaImage *src, BetaImage *dst)
{
  unsigned char a;
  unsigned char *data;
  unsigned char *src_row;
  unsigned char *dst_row;
  unsigned char *src_pixel;
  unsigned char *dst_pixel;
  int i, j;

  
  dst->width = src->width;
  dst->height = src->height;
  dst->rowbytes = (src->width + 7) >> 3;

  dst->data = malloc(dst->rowbytes * dst->height);

  if(dst->data == NULL) {
    return 1;
  }

  data = dst->data;
  for(i = 0; i < dst->rowbytes * dst->height; i++) {
    data[i] = 0;
  }

  src_row = src->data;
  dst_row = dst->data;
  for(j = 0; j < src->height; j++) {
    src_pixel = src_row;
    dst_pixel = dst_row;
    for(i = 0; i < src->width; i++) {
      a = src_pixel[3];
      src_pixel += 4;
      if (a > 200)
        SetBit(dst_row, i);
    }
    src_row += src->rowbytes;
    dst_row += dst->rowbytes;
  }
  return 0;
}



int readPNG(Display *display, char *name, XImage **ximage, Pixmap *xmask)
{
  Colormap cmap;
  
  int screen;
  Visual *visual;
  Drawable defaultdrawable;
  BetaImage image;
  BetaImage mask;
  
  int error;
  int byte_order;
  static initialized=0;
  
  screen = DefaultScreen(display);
  visual = DefaultVisual(display, screen);
  defaultdrawable = DefaultRootWindow(display);
  cmap = DefaultColormap(display, screen);

    
  if (!initialized) {
    BetaInitColor(display, cmap);
    initialized=1;
  };
  

  
  error = BetaReadPNG(name, &image, 1);

  if(error != 0) {
    return error;
  }


  if(image.alpha) {
    betaImage2Mask(&image, &mask);
    *xmask = XCreateBitmapFromData(display, defaultdrawable, mask.data, mask.width, mask.height);
  }

  
  
  
  if (error == 0) {
    BetaImageToXImage(display, &image, ximage);
  }
  return error;
}
