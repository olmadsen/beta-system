#include <stdlib.h>
#include <math.h>
#include "betaimage.h"


void inv_cmap (int colors,
	       unsigned char  *colormap[3], 
	       int bits,
	       unsigned long * dist_buf, 
	       unsigned char  *rgbmap );







void MakeGrayMap(BetaPalette *palette)
{
  int index;
  for (index = 0; index < 32; index++) {
    palette->colormap[index].red = index * 255 / 32;
    palette->colormap[index].green = index * 255 / 32;
    palette->colormap[index].blue = index * 255 / 32;
  }
  palette->ncolors = 32;
}


void MakeRedMap(BetaPalette *palette)
{
  int index;
  for (index = 0; index < 32; index++) {
    palette->colormap[index].red = 255;
    palette->colormap[index].green = index * 255/ 32;
    palette->colormap[index].blue = 0;
  }
  palette->colormap[32].red = 0;
  palette->colormap[32].green = 0;
  palette->colormap[32].blue = 0;
  palette->colormap[32].red = 255;
  palette->colormap[32].green = 255;
  palette->colormap[32].blue = 255;
  palette->ncolors = 34;
  
}

void MakeColorMap(BetaPalette *palette)
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
	palette->colormap[index].red = red << 5;
	palette->colormap[index].green = green << 5;
	palette->colormap[index].blue = blue << 6;
	index++;
	blue++;
      }
      green++;
    }
    red++;
  }
  palette->ncolors = 256;
}

void MakeColorMap5(BetaPalette *palette)
{
  int red = 0;
  int green = 0;
  int blue = 0;
  int index = 0;

  palette->colormap[0].red = 0;
  palette->colormap[0].green = 0;
  palette->colormap[0].blue = 0;

  palette->colormap[1].red = 255;
  palette->colormap[1].green = 255;
  palette->colormap[1].blue = 255;

  palette->colormap[2].red = 255;
  palette->colormap[2].green = 0;
  palette->colormap[2].blue = 0;

  palette->colormap[3].red = 0;
  palette->colormap[3].green = 255;
  palette->colormap[3].blue = 0;

  palette->colormap[4].red = 0;
  palette->colormap[4].green = 0;
  palette->colormap[4].blue = 255;

  palette->colormap[2].red = 255;
  palette->colormap[2].green = 0;
  palette->colormap[2].blue = 255;
  
  palette->colormap[3].red = 0;
  palette->colormap[3].green = 255;
  palette->colormap[3].blue = 255;

  palette->colormap[4].red = 255;
  palette->colormap[4].green = 255;
  palette->colormap[4].blue = 0;

  palette->ncolors = 5;
}



void MakeColorMap1(BetaPalette *palette)
{
    double N;
    int i;
    int levelsq, levelsc;
    
    int levels = 6;
    
    palette->ncolors = 216;


    levelsq = levels*levels;	/* squared */
    levelsc = levels*levelsq;	/* and cubed */

    N = 255.0 / (levels - 1);    /* Get size of each step */

    /* 
     * Set up the color map entries.
     */
    for(i = 0; i < levelsc; i++) {
	palette->colormap[i].red = (int)(0.5 + (i%levels) * N);
	palette->colormap[i].green = (int)(0.5 + ((i/levels)%levels) * N);
	palette->colormap[i].blue = (int)(0.5 + ((i/levelsq)%levels) * N);
    }
    palette->special_set = 0;
}

void BetaInitRGBmap(BetaPalette *palette)
{
  unsigned char *colormap[3];
  unsigned long *dist_buf;
  long index = 0;

  colormap[0] = malloc(palette->ncolors);
  colormap[1] = malloc(palette->ncolors);
  colormap[2] = malloc(palette->ncolors);
  index = 0;
  while(index < palette->ncolors) {
    (colormap[0])[index] = palette->colormap[index].red;
    (colormap[1])[index] = palette->colormap[index].green;
    (colormap[2])[index] = palette->colormap[index].blue;
    index++;
  }
  dist_buf = malloc(32768 * 4);
  inv_cmap(palette->ncolors, colormap, 5, dist_buf, palette->rgbmap);
  free(dist_buf);
  free(colormap[0]);
  free(colormap[1]);
  free(colormap[2]);
  
}





long BetaAllocColor (BetaPalette *palette, Color *color, Color* actual)
{
  long red;
  long green;
  long blue;
  long index;

  red = color->red;
  green = color->green;
  blue = color->blue;

  if(palette->special_set) {
    if(red == palette->special.red
       && green == palette->special.green
       && blue == palette->special.blue)
      {
        actual->red = red;
        actual->green = green;
        actual->blue = blue;
        return 0;
      }
  }
  
  red = red >> 3;
  green = green >> 3;
  blue = blue >> 3;
  index = (red << 10) | (green << 5) | blue;
  
  actual->red = palette->colormap[palette->rgbmap[index]].red;
  actual->green = palette->colormap[palette->rgbmap[index]].green;
  actual->blue = palette->colormap[palette->rgbmap[index]].blue;

  if(palette->special_set) {
    return (1 + palette->xpixel[palette->rgbmap[index]]);
  } else {
    return  palette->xpixel[palette->rgbmap[index]];
  }
  
}



int BetaCreateImage(BetaImage *image, 
		    long width, 
		    long height,
		    long pixel_size,
		    void *data)
{
  image->width = width;
  image->height = height;
  image->pixel_size = pixel_size;
  image->rowbytes = ((((pixel_size * width) >> 3) + 3) >> 2) << 2;
  if (data) {
    image->data = data;
  }
  else {
    image->data = malloc(height * image->rowbytes);
  }
  image->palette = NULL;
  return 0;
}

/* Dithering support */

static int  fserrmap[512];   /* -255 .. 0 .. +255 */

static int FSError(int comp)
{
  return fserrmap[256 + comp];
}

static void fsclamp(Color *color)
{
  int r2, g2, b2, k, d;
  
  r2 = color->red;
  g2 = color->green;
  b2 = color->blue;
  
  if (r2<0 || g2<0 || b2<0) {   /* are there any negatives in RGB? */
    if (r2<g2) { if (r2<b2) k = 0; else k = 2; }
    else { if (g2<b2) k = 1; else k = 2; }
    
    switch (k) {
    case 0:  g2 -= r2;  b2 -= r2;  d = (abs(r2) * 3) / 2;    /* RED */
      r2 = 0;  
      g2 = (g2>d) ? g2 - d : 0;
      b2 = (b2>d) ? b2 - d : 0;
      break;
      
    case 1:  r2 -= g2;  b2 -= g2;  d = (abs(g2) * 3) / 2;    /* GREEN */
      r2 = (r2>d) ? r2 - d : 0;
      g2 = 0;  
      b2 = (b2>d) ? b2 - d : 0;
      break;
      
    case 2:  r2 -= b2;  g2 -= b2;  d = (abs(b2) * 3) / 2;    /* BLUE */
      r2 = (r2>d) ? r2 - d : 0;
      g2 = (g2>d) ? g2 - d : 0;
      b2 = 0;  
      break;
    }
  }
  
  if (r2>255 || g2>255 || b2>255) {   /* any overflows in RGB? */
    if (r2>g2) { if (r2>b2) k = 0; else k = 2; }
    else { if (g2>b2) k = 1; else k = 2; }
    
    switch (k) {
    case 0:   g2 = (g2*255)/r2;  b2 = (b2*255)/r2;  r2=255;  break;
    case 1:   r2 = (r2*255)/g2;  b2 = (b2*255)/g2;  g2=255;  break;
    case 2:   r2 = (r2*255)/b2;  g2 = (g2*255)/b2;  b2=255;  break;
    }
  }
  color->red = r2;
  color->green = g2;
  color->blue = b2;
}


static long clamp (long x, long bot, long top)
{
  if (x < bot) {
    return bot;
  }
  else
    if (x > top) {
      return top;
    }
    else
      return x;
}

static void BetaAddRow(long width,  Color *row, Color *error, unsigned char *src, Color *palette)
{
  long index = 0;
  while (index < width) {
    row[index].red = error[index].red + palette[src[index]].red;
    row[index].green = error[index].green + palette[src[index]].green;
    row[index].blue = error[index].blue + palette[src[index]].blue;
    index++;
  }
}

static void BetaAddRow24(long width,  Color *row, Color *error, unsigned long *src)
{
  long index = 0;

  unsigned char *pixel = (unsigned char *) src;


  while (index < width) {
    row[index].red = error[index].red + pixel[index * 4];
    row[index].green = error[index].green + pixel[index * 4 + 1];
    row[index].blue = error[index].blue + pixel[index * 4 + 2];
    index++;
  }
}


static void BetaFillRow(long width, Color *row, Color *fill)
{
  long index = 0;
  while (index < width) {
    row[index] = *fill;
    index++;
  }
}

static void BetaDitherRow(BetaPalette *palette, long width, Color *thisrow, 
			  unsigned char *src, Color *nextrow, int odd)
{
  long x;
  Color error;
  Color actual;
  
  if (odd) {
    x = width - 1;
    while (x >= 0) {
      fsclamp(&thisrow[x]);
      
      src[x] = BetaAllocColor(palette, &thisrow[x], &actual);
      
      error.red = FSError((thisrow[x].red - actual.red));
      error.green = FSError((thisrow[x].green - actual.green));
      error.blue = FSError((thisrow[x].blue - actual.blue));
      
      if (x > 0) {
	thisrow[x - 1].red += (error.red * 7)/  16;
	thisrow[x - 1].green += (error.green * 7)/ 16;
	thisrow[x - 1].blue += (error.blue * 7) /  16;
	
	nextrow[x - 1].red += error.red /16;
	nextrow[x - 1].green += error.green /16;
	nextrow[x - 1].blue += error.blue /16;
      }
      nextrow[x].red += (error.red * 5)/16;
      nextrow[x].green += (error.green * 5)/16;
      nextrow[x].blue += (error.blue * 5)/16;
      if (x < width - 1) {
	nextrow[x + 1].red += (error.red * 3)/16;
	nextrow[x + 1].green += (error.green * 3)/16;
	nextrow[x + 1].blue += (error.blue * 3)/16;
      }
      x--;
    } 
  }
  else {
    x = 0;
    while (x < width) {
      fsclamp(&thisrow[x]);
      
      src[x] = BetaAllocColor(palette, &thisrow[x], &actual);
      
      error.red = FSError((thisrow[x].red - actual.red));
      error.green = FSError((thisrow[x].green - actual.green));
      error.blue = FSError((thisrow[x].blue - actual.blue));
      
      if (x < width-1) {
	thisrow[x + 1].red += (error.red * 7)/  16;
	thisrow[x + 1].green += (error.green * 7)/ 16;
	thisrow[x + 1].blue += (error.blue * 7)/  16;
	
	nextrow[x + 1].red += error.red/16;
	nextrow[x + 1].green += error.green/16;
	nextrow[x + 1].blue += error.blue/16;
      }
      nextrow[x].red += (error.red  * 5)/16;
      nextrow[x].green += (error.green * 5)/16;
      nextrow[x].blue += (error.blue * 5)/16;
      if (x > 0) {
	nextrow[x - 1].red += (error.red * 3)/16;
	nextrow[x - 1].green += (error.green * 3)/16;
	nextrow[x - 1].blue += (error.blue * 3)/16;
      }
      x++;
    }
  }
}

void BetaDitherImage (BetaPalette *palette, BetaImage *image)
{
  Color *thisrow;
  Color *nextrow;
  long index;
  Color empty = {0, 0, 0};
  unsigned char *row;
  int i, j;

   /* compute somewhat non-linear floyd-steinberg error mapping table 
    * This code is copied from XV and the purpose is to adjust
    * for gamma-correction problems.
    */
  for (i=j=0; i<=0x40; i++,j++) 
    { fserrmap[256+i] = j;  fserrmap[256-i] = -j; }
  for (     ; i<0x80; i++, j += !(i&1) ? 1 : 0) 
    { fserrmap[256+i] = j;  fserrmap[256-i] = -j; }
  for (     ; i<=0xff; i++) 
    { fserrmap[256+i] = j;  fserrmap[256-i] = -j; }

  
  thisrow = malloc(image->width * sizeof(Color));
  nextrow = malloc(image->width * sizeof(Color));
  
  BetaFillRow(image->width, nextrow, &empty);
  
  row = image->data;
  index = 0;
  while (index < image->height) {
    BetaAddRow(image->width, thisrow, nextrow, row, image->palette);
    BetaFillRow(image->width, nextrow, &empty);
    BetaDitherRow(palette, image->width, thisrow, row, nextrow, index & 1);
    index++;
    row += image->rowbytes;
  }
  free(thisrow);
  free(nextrow);
}

void BetaDitherImage24To8 (BetaPalette *palette, BetaImage *image, BetaImage *image8)
{
  Color *thisrow;
  Color *nextrow;
  long index;
  int i, j;
  Color empty = {0, 0, 0};
  unsigned char *row;
  unsigned char *srcrow;


  /* compute somewhat non-linear floyd-steinberg error mapping table */
  for (i=j=0; i<=0x40; i++,j++) 
    { fserrmap[256+i] = j;  fserrmap[256-i] = -j; }
  for (     ; i<0x80; i++, j += !(i&1) ? 1 : 0) 
    { fserrmap[256+i] = j;  fserrmap[256-i] = -j; }
  for (     ; i<=0xff; i++) 
    { fserrmap[256+i] = j;  fserrmap[256-i] = -j; }


  thisrow = malloc(image->width * sizeof(Color));
  nextrow = malloc(image->width * sizeof(Color));
  
  BetaFillRow(image->width, nextrow, &empty);
  
  row = image8->data;
  srcrow = image->data;
  index = 0;
  while (index < image->height) {
    BetaAddRow24(image->width, thisrow, nextrow, (unsigned long *)srcrow);
    BetaFillRow(image->width, nextrow, &empty);
    BetaDitherRow(palette, image->width, thisrow, row, nextrow, index & 1);
    index++;
    row += image8->rowbytes;
    srcrow += image->rowbytes;
  }

  free(thisrow);
  free(nextrow);
}

void BetaTranslateImage(BetaImage *image, BetaPalette *palette)
{
  unsigned char *row;
  int i, j;
  Color actual;

  row = image->data;
  for (i = 0; i < image->height; i++) {
    for (j = 0; j < image->width; j++) {
      row[j] = BetaAllocColor(palette, &(image->palette[row[j]]), &actual);
    }
    row += image->rowbytes;
  }
}

