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
  
  screen = DefaultScreen(display);
  visual = DefaultVisual(display, screen);
  cmap = DefaultColormap(display, screen);
  
  BetaInitColor(display, cmap);
  
  error = BetaReadPNGToBetaImage(name, &image);
  
  if (error == 0) {
    BetaImageToXImage(display, &image, ximage);
    if(!truecolor) {
      free(image.data);
    }
    if(image.palette) {
      free(image.palette);
    }
  }
  return error;
}

