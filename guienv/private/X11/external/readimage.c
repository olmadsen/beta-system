#include <stdlib.h>
#include <X11/Xlib.h>
#include "betapng.h"


int BetaReadPNGFileToXImage(Display *display, char *name, XImage **ximage)
{
  Colormap cmap;
  int screen;
  Visual *visual;
  BetaImage image;
  int error;
  int byte_order;
  static initialized=0;
  
  screen = DefaultScreen(display);
  visual = DefaultVisual(display, screen);
  cmap = DefaultColormap(display, screen);
  byte_order = ImageByteOrder(display);

  if (!initialized) {
    BetaInitColor(display, cmap);
    initialized=1;
  };
  
  if(byte_order == LSBFirst) {
    BetaSetByteSwap(1);
    error = BetaReadPNGToBetaImage(name, &image, 2);
  }
  else {
    error = BetaReadPNGToBetaImage(name, &image, 1);
  }
  
  if (error == 0) {
    BetaImageToXImage(display, &image, ximage);
    if(image.palette) {
      free(image.palette);
    }
  }
  return error;
}

