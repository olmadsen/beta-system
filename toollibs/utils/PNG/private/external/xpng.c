#include "betaimage.h"
#include "betapng.h"
#include <stdlib.h>
#include <X11/Xlib.h>

#define SWAP 1

typedef unsigned int Uint32;
typedef int Sint32;


/*
 * How many 1 bits are there in the Uint32.
 * Low performance, do not call often.
 */
static int number_of_bits_set( Uint32 a )
{
    if(!a) return 0;
    if(a & 1) return 1 + number_of_bits_set(a >> 1);
    return(number_of_bits_set(a >> 1));
}


/*
 * How many 0 bits are there at least significant end of Uint32.
 * Low performance, do not call often.
 */
static int free_bits_at_bottom( Uint32 a )
{
      /* assume char is 8 bits */
    if(!a) return sizeof(Uint32) * 8;
    if(((Sint32)a) & 1l) return 0;
    return 1 + free_bits_at_bottom ( a >> 1);
}


BetaPalette stdcolormap;
static int truecolor;

static unsigned long r_pix[256];
static unsigned long g_pix[256];
static unsigned long b_pix[256];

static void InitMakePixel
(unsigned long Rmask, unsigned long Gmask, unsigned long Bmask)
{
  int i;
  static int initialized = 0;

  if(!initialized) {
    for ( i=0; i<256; ++i ) {
      r_pix[i] = i >> (8 - number_of_bits_set(Rmask));
      r_pix[i] <<= free_bits_at_bottom(Rmask);
      g_pix[i] = i >> (8 - number_of_bits_set(Gmask));
      g_pix[i] <<= free_bits_at_bottom(Gmask);
      b_pix[i] = i >> (8 - number_of_bits_set(Bmask));
      b_pix[i] <<= free_bits_at_bottom(Bmask);
    }
    initialized = 1;
  }
}

unsigned long MakePixel
(unsigned char red, unsigned char green, unsigned char blue)
{
  return r_pix[red] | g_pix[green] | b_pix[blue];
}


Status BetaAllocateColormap(Display *display, Colormap cmap, BetaPalette *palette)
{
  XColor color;
  Status result = 1;
  int index = 0;
 
  while ((index < palette->ncolors) && result) {
    color.red = palette->colormap[index].red << 8;
    color.green = palette->colormap[index].green << 8;
    color.blue = palette->colormap[index].blue << 8;
    result = XAllocColor(display, cmap, &color);
    if (result) {
      palette->xpixel[index] = color.pixel;
    }
    index++;
  }
  return result;
}

void GetXColorMap(Display *display, Colormap cmap, BetaPalette *palette)
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
    palette->colormap[index].red = map[index].red >> 8;
    palette->colormap[index].green = map[index].green >> 8;
    palette->colormap[index].blue = map[index].blue >> 8;
    palette->xpixel[index] = index;
    index++;
  }
  palette->ncolors = 256;
  return;
}

void BetaInitColor(Display *display)
{
  static int initialized = 0;
  
  int i;
  
  double gamma;

  Colormap cmap;
  Visual *visual;
  Status result;

  if(initialized)
    return;

  initialized = 1;

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
    MakeColorMap1(&stdcolormap);
    
    cmap = DefaultColormap(display, DefaultScreen(display));
    result = BetaAllocateColormap(display, cmap, &stdcolormap);

    if (!result) {
      GetXColorMap(display, cmap, &stdcolormap);
    }
    
    BetaInitRGBmap(&stdcolormap);

  } else {
    InitMakePixel(visual->red_mask, visual->green_mask, visual->blue_mask);
  }
}


long AllocColor(Display *display, XColor *xcolor)
{
  Color color;
  Color actual;
  long  pixel;

  BetaInitColor(display);

  color.red = xcolor->red >> 8;
  color.green = xcolor->green >> 8;
  color.blue = xcolor->blue >> 8;
  
  if(truecolor) {
    pixel = MakePixel(color.red, color.green, color.blue);
  } else {
    pixel = BetaAllocColor(&stdcolormap, &color, &actual);
  }
  xcolor->pixel = pixel;
  return pixel;
}


int YAllocColor(Display *display, Colormap cmap, XColor *xcolor)
{
  long pixel;
  pixel = AllocColor(display, xcolor);
  return 1;
}



static int BetaImageToXImage8(Display *display, BetaImage *image, XImage **ximage)
{
  BetaImage image8;

  BetaCreateImage(&image8, image->width, image->height, 8, NULL); 
  if(image->pixel_size == 8) {
    memcpy(image8.data, image->data, image->height * image->rowbytes);
    image8.palette = image->palette;
    image8.palette_size = image->palette_size;
    BetaDitherImage(&stdcolormap, &image8);
  }
  else {
    printf("beta dither image\n");
    BetaDitherImage24To8(&stdcolormap, image, &image8);
  }
  (*ximage) = XCreateImage
    (display, 
     DefaultVisual(display, DefaultScreen(display)), 
     image8.pixel_size, ZPixmap, 0, 
     image8.data, image8.width, image8.height, 32, image8.rowbytes);
  return 0;
}


static int BetaImageToXImage24(Display *display, BetaImage *image, XImage **ximage)
{

  Visual *visual;
  XImage *im;
  int depth;
  unsigned char *row;
  unsigned char *pixel;
  int i, j;
  unsigned char r, g, b, a;

  
  visual = DefaultVisual(display, DefaultScreen(display));


  depth = DefaultDepth(display, DefaultScreen(display));

  im = XCreateImage
    (display, visual, depth, ZPixmap,0, 0,
     image->width, image->height, 32, 0);


  
  im->data = (char *) malloc(image->height * im->bytes_per_line);

  row = image->data;
  for (j = 0; j < image->height; j++) {
    pixel = row;
    for(i = 0; i < image->width; i++) {
      r = pixel[0];
      g = pixel[1];
      b = pixel[2];
      a = pixel[3];
      XPutPixel(im, i, j, MakePixel(r, g, b));
      pixel+=4;
    }
    row+=image->rowbytes;
  }
  *ximage = im;
  return 0;
}

static int BetaImageToXImage(Display *display, BetaImage *image, XImage **ximage)
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


static int betaImage2Mask(BetaImage *src, BetaImage *dst)
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
  
  int screen;
  Visual *visual;
  Drawable defaultdrawable;
  BetaImage image;
  BetaImage mask;
  
  int error;
  int byte_order;
  
  screen = DefaultScreen(display);
  visual = DefaultVisual(display, screen);
  defaultdrawable = DefaultRootWindow(display);

    
  BetaInitColor(display);
  

  
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
