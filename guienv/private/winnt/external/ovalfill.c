#include <windows.h>

typedef unsigned int Uint32;
typedef int Sint32;

static unsigned char bits[255];

static HBITMAP bitmap = NULL;
static HBITMAP prev_bitmap;
static HDC hdc;
static unsigned char *data;
static int width;
static int height;
static int rowbytes;

static unsigned char *stencil = 0;

static int limit;



int number_of_bits_set( Uint32 a )
{
    if(!a) return 0;
    if(a & 1) return 1 + number_of_bits_set(a >> 1);
    return(number_of_bits_set(a >> 1));
}


static int red;
static int green;
static int blue;

void ovalpen(double r, double g, double b)
{
  blue = 0xFF * r;
  green = 0xFF * g;
  red = 0xFF * b;
}


static init_bits(void)
{
   Uint32 i;
   
   for(i = 0; i < 256; i++) {
      bits[i] = number_of_bits_set(i);
   }
}

void fill_oval(int x, int y, int owidth, int oheight)
{
  unsigned char *data_ptr;
  
  int value;
  int gray;

  int i, j;
  int minor;

  unsigned long color;
  
  unsigned char *stencil_ptr;
   

  if(owidth >= limit || oheight >= limit) {
    return;
  }

  color = blue | (green << 8) | (red << 16);
  
  Ellipse(hdc, 0, 0, owidth * 8, oheight * 8);

  stencil_ptr = stencil;
  data_ptr = data;
  
  for(j = 0; j < oheight; j++) {
    for(minor = 0; minor < 8; minor++) {
      for(i = 0; i < owidth; i++) {
        value = data_ptr[i];
        data_ptr[i] = 0;
        stencil_ptr[i] += bits[value];
      }
      data_ptr += limit;
    }
    stencil_ptr += limit;
  }
  
  stencil_ptr = stencil;
  
  
  for(j = 0; j < oheight; j++) {
    for(i = 0; i < owidth; i++) {
      value = stencil_ptr[i];
      stencil_ptr[i] = 0;
      if(value != 0) {
        if (value == 64) {
          plotpixel(x + i, y + j, color);
        } else {
          gray = (value * 0xFF) / 64;
          blend_pixel(x + i, y + j, gray, color);
        }
      }
    }
    stencil_ptr+= limit;
  }
  
}

void oval_limit(int size)
{
  
  unsigned char *stencil_ptr;
  int i, j;
  
  limit = size;


  if(stencil) {
    free(stencil);
    stencil = NULL;
  }
  if(bitmap) {
    SelectObject(hdc, prev_bitmap);
    DeleteObject(bitmap);
    bitmap = NULL;
  }
  
  stencil = (unsigned char *) malloc(limit * limit);
  stencil_ptr = stencil;
  
   
  for (j = 0; j < limit; j++) {
    for(i = 0; i < limit; i++) {
      *stencil_ptr = 0;
      stencil_ptr++;
    }
  }

  data = NULL;
  
  {
    BITMAPINFO bmp = { { sizeof(BITMAPINFOHEADER), limit*8, -limit*8, 1, 1 } };
    bitmap = CreateDIBSection(NULL, & bmp, DIB_RGB_COLORS, &data, NULL, 0);

    prev_bitmap = SelectObject(hdc, bitmap);
  }
  
  
}


void init_ovals(void)
{
  HDC screen;
 

  init_bits();

  screen = GetDC(NULL);
  hdc = CreateCompatibleDC(screen);

  oval_limit(96);
  return;
}

