#include <stdlib.h>
#include <math.h>
#include "betadither.h"

static void BetaSwapBig(BetaImage *image)
{
  unsigned char *row;
  unsigned char *pixel;

  int i, j;

  unsigned char r, g, b, a;

  row = image->data;

  for(j = 0; j < image->height; j++) {
    pixel = row;
    for(i = 0; i < image->width; i++) {
      r = pixel[0];
      g = pixel[1];
      b = pixel[2];
      a = pixel[3];

      
      pixel[0] = a;
      pixel[1] = b;
      pixel[2] = g; 
      pixel[3] = r;

      pixel += 4;
    }
    row += image->rowbytes;
  }
}

static void BetaSwapLittle(BetaImage *image)
{
  unsigned char *row;
  unsigned char *pixel;

  int i, j;

  unsigned char r, g, b, a;

  row = image->data;

  for(j = 0; j < image->height; j++) {
    pixel = row;
    for(i = 0; i < image->width; i++) {
      r = pixel[0];
      g = pixel[1];
      b = pixel[2];
      a = pixel[3];


      pixel[0] = b;
      pixel[1] = g;
      pixel[2] = r;
      pixel[3] = a;
      pixel += 4;
    }
    row += image->rowbytes;
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
  return comp;
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
  while (index < width) {
    
    row[index].red = error[index].red + ((src[index] & 0xFF000000) >> 24);
    row[index].green = error[index].green + ((src[index] & 0x00FF0000) >> 16);
    row[index].blue = error[index].blue + ((src[index] & 0x0000FF00) >> 8);
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

static void BetaDitherRow(long width, Color *thisrow, unsigned char *src, Color *nextrow, int odd)
{
  long x;
  Color error;
  Color actual;
  
  if (odd) {
    x = width - 1;
    while (x >= 0) {
      fsclamp(&thisrow[x]);
      
      src[x] = BetaAllocColor(&thisrow[x], &actual);
      
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
      
      src[x] = BetaAllocColor(&thisrow[x], &actual);
      
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

void BetaDitherImage (BetaImage *image)
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
    BetaDitherRow(image->width, thisrow, row, nextrow, index & 1);
    index++;
    row += image->rowbytes;
  }
  free(thisrow);
  free(nextrow);
}

void BetaDitherImage24To8 (BetaImage *image, BetaImage *image8)
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
    BetaAddRow24(image->width, thisrow, nextrow, (long *)srcrow);
    BetaFillRow(image->width, nextrow, &empty);
    BetaDitherRow(image->width, thisrow, row, nextrow, index & 1);
    index++;
    row += image8->rowbytes;
    srcrow += image->rowbytes;
  }

  free(thisrow);
  free(nextrow);
}

void BetaTranslateImage(BetaImage *image)
{
  unsigned char *row;
  int i, j;
  Color actual;

  row = image->data;
  for (i = 0; i < image->height; i++) {
    for (j = 0; j < image->width; j++) {
      row[j] = BetaAllocColor(&(image->palette[row[j]]), &actual);
    }
    row += image->rowbytes;
  }
}

void BetaCopyImage(BetaImage *src, BetaImage *dst)
{
  unsigned char *row;
  unsigned long *srcrow;
  int i, j;
  Color actual;
  Color color;

  
  row = dst->data;
  srcrow = src->data;
  for (i = 0; i < src->height; i++) {
    for (j = 0; j < src->width; j++) {
      
      color.red = (srcrow[j] & 0x00FF0000) >> 16;
      color.green =  (srcrow[j] & 0x0000FF00) >> 8;
      color.blue =  (srcrow[j] & 0x000000FF);
      row[j] = BetaAllocColor(&color, &actual);
    }
    row += dst->rowbytes;
    srcrow += (src->rowbytes >> 2);
  }
}




int BetaImageToXImage8(Display *display, BetaImage *image, XImage **ximage)
{
  BetaImage image8;

  BetaCreateImage(&image8, image->width, image->height, 8, NULL); 
  if(image->pixel_size == 8) {
    memcpy(image8.data, image->data, image->height * image->rowbytes);
    image8.palette = image->palette;
    image8.palette_size = image->palette_size;
    BetaDitherImage(&image8);
  }
  else {
    BetaDitherImage24To8(image, &image8);
  }
  (*ximage) = XCreateImage
    (display, 
     DefaultVisual(display, DefaultScreen(display)), 
     image8.pixel_size, ZPixmap, 0, 
     image8.data, image8.width, image8.height, 32, image8.rowbytes);
  return 0;
}

int BetaImageToXImage24(Display *display, BetaImage *image, XImage **ximage)
{

  Visual *visual;
  int  byte_order;
  
  visual = DefaultVisual(display, DefaultScreen(display));
  byte_order = ImageByteOrder(display);
  
  if(byte_order == LSBFirst) {
    BetaSwapLittle(image);
  } else {
    BetaSwapBig(image);
  }
  
  (*ximage) = XCreateImage
    (display, 
     DefaultVisual(display, DefaultScreen(display)), 
     image->pixel_size, ZPixmap, 0, 
     image->data, image->width, image->height, 32, image->rowbytes);
}

int BetaImageToXImage(Display *display, BetaImage *image, XImage **ximage)
{
 
  int displayDepth;

  displayDepth = XDefaultDepth(display,DefaultScreen(display));

  if (displayDepth == 8 ) {
    BetaImageToXImage8(display,image,ximage);
  } else {
    BetaImageToXImage24(display,image,ximage);
  }
  return 0;
}

static int levels = 50;


int InsideMandelbrotSet(double x, double y)
{
  double xx, yy, px, py;
  int count;
  double norm;
  
  xx = x;
  yy = y;
  norm = sqrt(xx*xx + yy*yy);
  
  count = 0;
  while ((count != levels) && (norm < 2.0)) {
    px = xx*xx;
    py = yy*yy;
    norm = sqrt(px + py);
    yy = 2*xx*yy + y;
    xx = px - py + x;
    
    count++;
  }
  return count;
}


double TranslateCoord(long x, long o, double oo, long unit)
{
  return ((x - o) * (1.0 / unit) + oo);
}

long MakeColor(long red, long green, long blue)
{
  return (red << 16) | (green << 8) | blue;
}

long max(long x, long y)
{
  if (x > y)
    return x;
  else
    return y;
}

long min(long x, long y)
{
  if (x < y)
    return x;
  else
    return y;
}



void MandelbrotImage(Display* display, XImage **ximage)
{
  Colormap cmap;
  int screen;
  Visual *visual;
  int x, y;
  double xx, yy;
  int width, height;
  int inside;
  BetaImage image;
  unsigned char *row;

  Color insideColor, outsideColor, ignore;
  long red, green, blue;

  insideColor.red = 0;
  insideColor.green = 0;
  insideColor.blue = 0;
  
  outsideColor.red = 255;
  outsideColor.green = 255;
  outsideColor.blue = 255;
  
  width = 600;
  height = 600;
  screen = DefaultScreen(display);
  visual = DefaultVisual(display, screen);
  cmap = DefaultColormap(display, screen);
  
  BetaInitColor(display, cmap);

  BetaCreateImage(&image, width, height, 32, NULL);
  image.pixel_size = 24;
  row = image.data;
  
  for (y = 0; y < height; y++) {
    yy = TranslateCoord(height - y, height / 2, 0, 150);
    for (x = 0; x < width; x++) {
      xx = TranslateCoord(x, width / 2, 0, 150);
      inside = InsideMandelbrotSet(xx, yy);

      if (inside == levels) {
	((long *) row)[x] = 0;
      }
      else { 
	if (inside < 10) {
	  red = 255;
	  blue = 0;
	  green = 0;
	}
	else {
	  red = 255;
	  green = (inside - 10) * 255 /(levels - 10);
	  blue = 0;
	}
	((long *) row)[x] = MakeColor(red, green, blue);
      }
    }
    row += image.rowbytes;
  }
  BetaImageToXImage(display, &image, ximage);
  return;
}

