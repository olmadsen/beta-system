#ifndef _BETADITHER_H
#define _BETADITHER_H
#include <X11/Xlib.h>

#include "betaimage.h"


/**********************************************************************
  BetaInitColor
 
  Initialize beta color support. Call this operation before
  any call to BetaAllocColor.
  
  arguments:
  
  display   -  The display connection.
  cmap      -  The cmap used in the application.

  If the display is 8-bit, a standard colormap is allocated with 216 
  entries. If this fails, the current content of the X colormap
  is used instead.

  An inverse color table is build for fast lookup of RGB colors.
  
  Subsequent calls to BetaAllocColor returns the closest match
  in the color table using the inverse color table.

  If the display is TrueColor or DirectColor, this routine
  does nothing.
  
 **********************************************************************/

void BetaInitColor(Display *display, Colormap cmap);


/**********************************************************************
  BetaAllocColor

  Returns an X pixel value for the specified color.

  Arguments:

  color   -  the desired RGB color.
  actual  -  the actual values of the closest match,

  Returns:

  The best pixel value for the specified color.

  If the display is 8-bit, the color is found in a pre-allocated
  palette using an inverse color table for fast lookup. The pixel
  value will be an index. 

  If the display is TrueColor or DirectColor a precise pixel value
  is computed instead.
**********************************************************************/

int BetaCreateImage(BetaImage *image, 
		    long width, 
		    long height,
		    long pixel_size,
		    void *data);

int BetaImageToXImage(Display *display, BetaImage *image, XImage **ximage);

long BetaAllocColor (Color *color, Color* actual);

void BetaDitherImage (BetaImage *image);
void BetaOrderedDitherImage (BetaImage *image);
void BetaDitherImage24To8 (BetaImage *image, BetaImage *image8);

#endif
