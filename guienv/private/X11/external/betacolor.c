#include <stdlib.h>
#include <math.h>
#include "betacolor.h"


static int gammascreen[256];
static int gammafile[256];
static unsigned char xpixel[256];

static int truecolor;


void inv_cmap (int colors,
	       unsigned char  *colormap[3], 
	       int bits,
	       unsigned long * dist_buf, 
	       unsigned char  *rgbmap );

static unsigned char rgbmap[32768];
static Color stdcolormap[256];




long ScreenGamma(long comp)
{
  return gammascreen[comp];
}

long FileGamma(long comp)
{
  return gammafile[comp];
}

void MakeGrayMap(Color *rgbmap, int *colors)
{
  int index;
  for (index = 0; index < 32; index++) {
    rgbmap[index].red = index * 255 / 32;
    rgbmap[index].green = index * 255 / 32;
    rgbmap[index].blue = index * 255 / 32;
    printf("%d\n", index * 255 / 32);
  }
  *colors = 32;
}


void MakeRedMap(Color *rgbmap, int *colors)
{
  int index;
  for (index = 0; index < 32; index++) {
    rgbmap[index].red = 255;
    rgbmap[index].green = index * 255/ 32;
    rgbmap[index].blue = 0;
  }
  rgbmap[32].red = 0;
  rgbmap[32].green = 0;
  rgbmap[32].blue = 0;
  rgbmap[32].red = 255;
  rgbmap[32].green = 255;
  rgbmap[32].blue = 255;
  *colors = 34;
  
}

void MakeColorMap(Color *rgbmap, int *colors)
{
  int red = 0;
  int green = 0;
  int blue = 0;
  int index = 0;

  while (red < 8) {
    green = 0;
    while (green < 8) {
      blue = 0;
      while (blue < 4) {
	rgbmap[index].red = red << 5;
	rgbmap[index].green = green << 5;
	rgbmap[index].blue = blue << 6;
	index++;
	blue++;
      }
      green++;
    }
    red++;
  }
  *colors = 256;
}

void MakeColorMap5(Color *rgbmap, int *colors)
{
  int red = 0;
  int green = 0;
  int blue = 0;
  int index = 0;

  rgbmap[0].red = 0;
  rgbmap[0].green = 0;
  rgbmap[0].blue = 0;

  rgbmap[1].red = 255;
  rgbmap[1].green = 255;
  rgbmap[1].blue = 255;

  rgbmap[2].red = 255;
  rgbmap[2].green = 0;
  rgbmap[2].blue = 0;

  rgbmap[3].red = 0;
  rgbmap[3].green = 255;
  rgbmap[3].blue = 0;

  rgbmap[4].red = 0;
  rgbmap[4].green = 0;
  rgbmap[4].blue = 255;

  rgbmap[2].red = 255;
  rgbmap[2].green = 0;
  rgbmap[2].blue = 255;
  
  rgbmap[3].red = 0;
  rgbmap[3].green = 255;
  rgbmap[3].blue = 255;

  rgbmap[4].red = 255;
  rgbmap[4].green = 255;
  rgbmap[4].blue = 0;

  *colors = 5;
}



void MakeColorMap1(Color *rgbmap, int *colors)
{
    double N;
    int i;
    int levelsq, levelsc;
    
    int levels = 6;
    
    *colors = 216;


    levelsq = levels*levels;	/* squared */
    levelsc = levels*levelsq;	/* and cubed */

    N = 255.0 / (levels - 1);    /* Get size of each step */

    /* 
     * Set up the color map entries.
     */
    for(i = 0; i < levelsc; i++) {
	rgbmap[i].red = (int)(0.5 + (i%levels) * N);
	rgbmap[i].green = (int)(0.5 + ((i/levels)%levels) * N);
	rgbmap[i].blue = (int)(0.5 + ((i/levelsq)%levels) * N);
    }
}

Status BetaAllocateColormap(Display *display, Colormap cmap, 
			    int colors, Color *colormap)
{
  XColor color;
  Status result = 1;
  int index = 0;
 
  while ((index < colors) && result) {
    color.red = colormap[index].red << 8;
    color.green = colormap[index].green << 8;
    color.blue = colormap[index].blue << 8;
    result = XAllocColor(display, cmap, &color);
    if (result) {
      xpixel[index] = color.pixel;
    }
    index++;
  }
  return result;
}

void GetXColorMap(Display *display, Colormap cmap, Color *colormap)
{
  long index;
  XColor map[256];
  
  index = 0;
  while (index < 256) {
    map[index].pixel = index;
    index++;
  }
  XQueryColors(display, cmap, map, 256);
  index = 0;
  while (index < 256) {
    colormap[index].red = map[index].red >> 8;
    colormap[index].green = map[index].green >> 8;
    colormap[index].blue = map[index].blue >> 8;
    xpixel[index] = index;
    index++;
  }
}

void BetaInitColor(Display *display, Colormap cmap)
{
  unsigned char *colormap[3];
  long index = 0;
  int colors;
  int i;
  unsigned long *dist_buf;
  Status result;
  double gamma;

  Visual *visual;

  visual = DefaultVisual(display, DefaultScreen(display));    

  switch(visual->class) {
  case PseudoColor:
    truecolor = 0;
    break;
  case TrueColor:
  case DirectColor:
    truecolor = 1;
    break;
  }
  
  if(!truecolor) {
    
    gamma = 2.2;
    
    for ( i = 0; i < 256; i++ )
      gammascreen[i] = (int)(0.5 + 255 * pow( i / 255.0, 1.0/gamma ));
    
    gamma = 1.0 / 2.2;
    
    for ( i = 0; i < 256; i++ )
      gammafile[i] = (int)(0.5 + 255 * pow( i / 255.0, 1.0/gamma ));
    
    MakeColorMap1(stdcolormap, &colors);
    
    /*  result = BetaAllocateColormap(display, cmap, colors, stdcolormap); */
    result = 0;

    if (!result) {
      colors = 256;
      GetXColorMap(display, cmap, stdcolormap);
    }
    
    colormap[0] = malloc(colors);
    colormap[1] = malloc(colors);
    colormap[2] = malloc(colors);
    index = 0;
    while(index < colors) {
      (colormap[0])[index] = stdcolormap[index].red;
      (colormap[1])[index] = stdcolormap[index].green;
      (colormap[2])[index] = stdcolormap[index].blue;
      index++;
    }
    dist_buf = malloc(32768 * 4);
    inv_cmap(colors, colormap, 5, dist_buf, rgbmap);
    free(dist_buf);
    free(colormap[0]);
    free(colormap[1]);
    free(colormap[2]);
  }
}




long BetaAllocColor (Color *color, Color* actual)
{
  long red;
  long green;
  long blue;
  long index;

  red = color->red;
  green = color->green;
  blue = color->blue;
  
  if (truecolor) {
    return (red << 16) | (green << 8) | blue;
  }
  else {
    red = red >> 3;
    green = green >> 3;
    blue = blue >> 3;
    index = (red << 10) | (green << 5) | blue;
    
    actual->red = stdcolormap[rgbmap[index]].red;
    actual->green = stdcolormap[rgbmap[index]].green;
    actual->blue = stdcolormap[rgbmap[index]].blue;
    return xpixel[rgbmap[index]];
  }
}

long BetaAllocColor1 (Color *color, Color* actual)
{
  long red;
  long green;
  long blue;
  long index = 0;
  
  red = ScreenGamma(color->red);
  green = ScreenGamma(color->green);
  blue = ScreenGamma(color->blue);

  red = red >> 3;
  green = green >> 3;
  blue = blue >> 3;
  index = (red << 10) | (green << 5) | blue;
  
  actual->red = FileGamma(stdcolormap[rgbmap[index]].red);
  actual->green = FileGamma(stdcolormap[rgbmap[index]].green);
  actual->blue = FileGamma(stdcolormap[rgbmap[index]].blue);
  return xpixel[rgbmap[index]];
}
