#include <png.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "betapng.h"

static void SetBit(unsigned char *data, unsigned long n)
{
  unsigned long byte;
  unsigned long bit;
  unsigned char *ptr;
  unsigned char mask;
  
  byte = n >> 3;
  bit = n & 7;
  bit = 7 - bit;
  
  mask = 1 << bit;

  ptr = data + byte;
  *ptr = *ptr | mask;
  return;
}



void getPixels1(HDC hdc, HBITMAP hbm, BITMAP *bitmap, unsigned char **data)
{
  int result;
  int width, height;
  int i, j;
  
  unsigned char red, green, blue;

  unsigned char *row;
  unsigned  char *pixel;
  unsigned long col;
  
  width = bitmap->bmWidth;
  height = bitmap->bmHeight;

  row = *data;
  
  for (j = 0;j < height; j++) {
    pixel = row;
    for (i = 0;i < width; i++) {
      col = GetPixel(hdc, i, j);

      if(col == CLR_INVALID) {
        red = 255;
        green = 255;
        blue = 0;
      } else {
        red = GetRValue(col);
        green = GetGValue(col);
        blue = GetBValue(col);
      };
      pixel[0] = blue;
      pixel[1] = green;
      pixel[2] = red;
      pixel += 3;
    }
    row += bitmap->bmWidthBytes;
  }
}

void getPixels(HDC hdc, HBITMAP hbm, BITMAP *bitmap, unsigned char **data)
{
  int result;
  UINT start;
  UINT num;
  BITMAPINFO bmi;
  UINT uUsage;

  start = 0;
  num = bitmap->bmHeight;
  uUsage = DIB_RGB_COLORS;
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = bitmap->bmWidth;
  bmi.bmiHeader.biHeight = -bitmap->bmHeight;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;
  result = GetDIBits(hdc, hbm, start, num, *data, &bmi, uUsage);
  return;
}



void write_bmp_to_png(HDC hdc, HBITMAP hbmp, char *file_name)
{
  BITMAP bitmap;
  int result;

  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **rows;
  unsigned char *image;
  long k; 
  png_color_8 sig_bit;
  
  unsigned char *data;
  unsigned char *line1;
  unsigned char *line2;
  long bytesize;
  
  result = GetObject((HGDIOBJ) hbmp, sizeof(BITMAP), (void *) &bitmap);

  if(!result) {
    return;
  }
  
  bitmap.bmWidthBytes = ((bitmap.bmWidth*3 + 3) >> 2 << 2);

  bytesize = bitmap.bmHeight * bitmap.bmWidthBytes;

  data = bitmap.bmBits;
  
  data = (unsigned char *) malloc(bytesize);

  
  if(!data) {
    return;
  }
  getPixels(hdc, hbmp, &bitmap, &data);
  fp = fopen(file_name, "wb");

  if(!fp) {
    free(data);
    return;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(!png_ptr) {
    fclose(fp);
    free(data);
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);

  if(!info_ptr) {
    fclose(fp);
    free(data);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    fclose(fp);
    free(data);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }


  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, bitmap.bmWidth, bitmap.bmHeight, 8,
               PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);
  png_set_bgr(png_ptr);
  
  
  rows = (unsigned char **) malloc(bitmap.bmHeight * sizeof(unsigned char *));
  image = data;
  for(k = 0; k < bitmap.bmHeight; k++) {
    rows[k] = image;
    image += bitmap.bmWidthBytes;
  }

  png_write_image(png_ptr, rows);
  png_write_end(png_ptr, info_ptr);
  
  fclose(fp);
  free(data);
  free(rows);
  png_destroy_write_struct(&png_ptr, NULL);
  return;
}

int betaImage2RGB(BetaImage *src, BetaImage *dst)
{
  unsigned char r, g, b, a;
  unsigned char *src_row;
  unsigned char *dst_row;
  unsigned char *src_pixel;
  unsigned char *dst_pixel;
  int i, j;

  dst->width = src->width;
  dst->height = src->height;
  dst->rowbytes = (((dst->width * 3) + 3) >> 2) << 2;
  dst->data = malloc(dst->rowbytes * dst->height);
  if(dst->data == NULL) {
    return 1;
  }

  src_row = src->data;
  dst_row = dst->data;
  for(j = 0; j < src->height; j++) {
    src_pixel = src_row;
    dst_pixel = dst_row;
    for(i = 0; i < src->width; i++) {
      r = src_pixel[0];
      g = src_pixel[1];
      b = src_pixel[2];
      a = src_pixel[3];
      dst_pixel[0] = b;
      dst_pixel[1] = g;
      dst_pixel[2] = r;
      src_pixel += 4;
      dst_pixel += 3; 
    }
    src_row += src->rowbytes;
    dst_row += dst->rowbytes;
  }
  return 0;
}

HBITMAP BetaCreateBitmap(HDC hdc, void **pixels, int width, int height)
{
  void *pBits = NULL;
  HBITMAP hBmp;
  {
    BITMAPINFO bmp = { { sizeof(BITMAPINFOHEADER), width, height, 1, 32 } };
    hBmp = CreateDIBSection(NULL, & bmp, DIB_RGB_COLORS, & pBits, NULL, 0);
  }
  *pixels = pBits;
  return hBmp;
}



void write_dib_to_png(HDC hdc, HBITMAP hbmp, char *file_name)
{
  BITMAP bitmap;
  int result;

  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **rows;
  unsigned char *image;
  long k; 
  png_color_8 sig_bit;
  
  unsigned char *data;
  unsigned char *line1;
  unsigned char *line2;
  
  result = GetObject((HGDIOBJ) hbmp, sizeof(BITMAP), (void *) &bitmap);

  if(!result) {
    return;
  }


  
  data = bitmap.bmBits;

  
  if(!data) {
    return;
  }
  fp = fopen(file_name, "wb");

  if(!fp) {
    return;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(!png_ptr) {
    fclose(fp);
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);

  if(!info_ptr) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }


  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, bitmap.bmWidth, bitmap.bmHeight, 8,
               PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);
  png_set_bgr(png_ptr);

  {
    int i;
    int j;
    unsigned char *row;
    unsigned char *pixel;

    row = data;
    for(i = 0; i < bitmap.bmHeight; i++) {
      pixel = row;
      for(j = 0; j < bitmap.bmWidth; j++) {
        pixel[3] = 255;
        pixel += 4;
      }
      row += bitmap.bmWidthBytes;
    }
  }
    
  rows = (unsigned char **) malloc(bitmap.bmHeight * sizeof(unsigned char *));
  image = data;
  for(k = 0; k < bitmap.bmHeight; k++) {
    rows[bitmap.bmHeight - k - 1] = image;
    image += bitmap.bmWidthBytes;
  }

  png_write_image(png_ptr, rows);
  png_write_end(png_ptr, info_ptr);
  
  fclose(fp);
  free(rows);
  png_destroy_write_struct(&png_ptr, NULL);
  return;
}

void write_pixels_to_png(HBITMAP hbmp, int width, int height, char *file_name)
{

  BITMAP bitmap;
  int result;

  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **rows;
  unsigned char *image;
  long k; 
  png_color_8 sig_bit;
  
  unsigned char *data;
  unsigned char *line1;
  unsigned char *line2;
  

  result = GetObject((HGDIOBJ) hbmp, sizeof(BITMAP), (void *) &bitmap);
  
  if(!result) {
    return;
  }
  

  
  data = bitmap.bmBits;
  
  

  
  if(!data) {
    return;
  }
  fp = fopen(file_name, "wb");

  if(!fp) {
    return;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(!png_ptr) {
    fclose(fp);
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);

  if(!info_ptr) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }


  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, width, height, 8,
               PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);
  png_set_bgr(png_ptr);

  {
    int i;
    int j;
    unsigned char *row;
    unsigned char *pixel;

    row = data;
    for(i = 0; i < height; i++) {
      pixel = row;
      for(j = 0; j < width; j++) {
        pixel[3] = 255;
        pixel += 4;
      }
      row += bitmap.bmWidthBytes;
    }
  }
    
  rows = (unsigned char **) malloc(height * sizeof(unsigned char *));
  image = data;
  for(k = 0; k < height; k++) {
    rows[k] = image;
    image += bitmap.bmWidthBytes;
  }

  png_write_image(png_ptr, rows);
  png_write_end(png_ptr, info_ptr);
  
  fclose(fp);
  free(rows);
  png_destroy_write_struct(&png_ptr, NULL);
  return;
}

void write_pixels_to_png_area(HBITMAP hbmp, int x, int y, int width, int height, char *file_name)
{

  BITMAP bitmap;
  int result;

  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **rows;
  unsigned char *image;
  long k; 
  png_color_8 sig_bit;
  
  unsigned char *data;
  unsigned char *line1;
  unsigned char *line2;
  

  result = GetObject((HGDIOBJ) hbmp, sizeof(BITMAP), (void *) &bitmap);
  
  if(!result) {
    return;
  }
  

  
  data = bitmap.bmBits;
  
  

  
  if(!data) {
    return;
  }
  fp = fopen(file_name, "wb");

  if(!fp) {
    return;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(!png_ptr) {
    fclose(fp);
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);

  if(!info_ptr) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }


  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, width, height, 8,
               PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);
  png_set_bgr(png_ptr);

  {
    int i;
    int j;
    unsigned char *row;
    unsigned char *pixel;

    row = data + (bitmap.bmWidthBytes * y) + x*4;
    for(i = 0; i < height; i++) {
      pixel = row;
      for(j = 0; j < width; j++) {
        pixel[3] = 255;
        pixel += 4;
      }
      row += bitmap.bmWidthBytes;
    }
  }
    
  rows = (unsigned char **) malloc(height * sizeof(unsigned char *));
  image = data + (bitmap.bmWidthBytes * y) + x*4;
  for(k = 0; k < height; k++) {
    rows[k] = image;
    image += bitmap.bmWidthBytes;
  }

  png_write_image(png_ptr, rows);
  png_write_end(png_ptr, info_ptr);
  
  fclose(fp);
  free(rows);
  png_destroy_write_struct(&png_ptr, NULL);
  return;
}

void write_pixels_to_png_area_rgb(HBITMAP hbmp, int x, int y, int width, int height, char *file_name,
                                  int transparent, int t_red, int t_green, int t_blue)
{

  BITMAP bitmap;
  int result;

  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **rows;
  unsigned char *image;
  long k; 
  png_color_8 sig_bit;

  png_color_16 t_color;
  
  
  unsigned char *data;
  unsigned char *line1;
  unsigned char *line2;
  

  result = GetObject((HGDIOBJ) hbmp, sizeof(BITMAP), (void *) &bitmap);
  
  if(!result) {
    return;
  }
  

  
  data = bitmap.bmBits;
  
  

  
  if(!data) {
    return;
  }
  fp = fopen(file_name, "wb");

  if(!fp) {
    return;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(!png_ptr) {
    fclose(fp);
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);

  if(!info_ptr) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }


  png_init_io(png_ptr, fp);
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);
  
  png_set_IHDR(png_ptr, info_ptr, width, height, 8,
               PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  if(transparent) {
    t_color.red = t_red;
    t_color.green = t_green;
    t_color.blue = t_blue;
    png_set_tRNS(png_ptr, info_ptr, NULL, 0, &t_color);
  }

  
  png_write_info(png_ptr, info_ptr);
  png_set_filler(png_ptr, 0, PNG_FILLER_AFTER);
  png_set_bgr(png_ptr);
  
  
  {
    int i;
    int j;
    unsigned char *row;
    unsigned char *pixel;

    row = data + (bitmap.bmWidthBytes * y) + x*4;
    for(i = 0; i < height; i++) {
      pixel = row;
      for(j = 0; j < width; j++) {
        pixel[3] = 255;
        pixel += 4;
      }
      row += bitmap.bmWidthBytes;
    }
  }
    
  rows = (unsigned char **) malloc(height * sizeof(unsigned char *));
  image = data + (bitmap.bmWidthBytes * y) + x*4;
  for(k = 0; k < height; k++) {
    rows[k] = image;
    image += bitmap.bmWidthBytes;
  }

  png_write_image(png_ptr, rows);
  png_write_end(png_ptr, info_ptr);
  
  fclose(fp);
  free(rows);
  png_destroy_write_struct(&png_ptr, NULL);
  return;
}

static BetaPalette std;


static void InitPalette(void)
{
  static initialized = 0;
  int i;
  
  if(initialized) {
    return;
  }
  initialized = 1;

  MakeColorMap1(&std);
  BetaInitRGBmap(&std);
  for(i = 0; i < std.ncolors; i++) {
    std.xpixel[i] = i;
  }
  return;
}

void DibsectionToImage8(HBITMAP hbmp, int x, int y, int width, int height,
                        BetaImage *image8,
                        int transparent, int t_red, int t_green, int t_blue)
{
  BetaImage image;
  BITMAP bitmap;
  int result;
  unsigned char *data;

  InitPalette();

  if(transparent) {
    std.special.red = t_red;
    std.special.green = t_green;
    std.special.blue = t_blue;
    std.special_set = 1;
  } else {
    std.special_set = 0;
  }
  
  result = GetObject((HGDIOBJ) hbmp, sizeof(BITMAP), (void *) &bitmap);
  
  if(!result) {
    return;
  }
  data = bitmap.bmBits;
  
  BetaCreateImage(&image, width, height, 32, NULL);
  
  {
    int i;
    int j;
    unsigned char *row;
    unsigned char *pixel;

    unsigned char *dst_row;
    unsigned char *dst_pixel;

    row = data + (bitmap.bmWidthBytes * y) + x*4;
    dst_row = (unsigned char *) image.data;
    
    for(i = 0; i < height; i++) {
      pixel = row;
      dst_pixel = dst_row;
      
      for(j = 0; j < width; j++) {
        dst_pixel[0] = pixel[2];
        dst_pixel[1] = pixel[1];
        dst_pixel[2] = pixel[0];
        pixel += 4;
        dst_pixel += 4;
      }
      row += bitmap.bmWidthBytes;
      dst_row += image.rowbytes;
    }
  }

  BetaDitherImage24To8(&std, &image, image8);
  free(image.data);
  image8->palette_size = std.ncolors;
  image8->palette = std.colormap;
  return;
}


void write_pixels_to_png_area_indexed
(HBITMAP hbmp, int x, int y, int width, int height,
 char *file_name, int transparent, int t_red, int t_green, int t_blue)
{


  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **rows;
  unsigned char *image;
  long k;
  int i;
  png_color_8 sig_bit;
  
  unsigned char *data;
  unsigned char *line1;
  unsigned char *line2;
  png_colorp palette;
  
  BetaImage image8;

  
  fp = fopen(file_name, "wb");

  if(!fp) {
    return;
  }

  
  BetaCreateImage(&image8, width, height, 8, NULL);

  DibsectionToImage8(hbmp, x, y, width, height, &image8, transparent, t_red, t_green, t_blue);
  
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(!png_ptr) {
    fclose(fp);
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);

  if(!info_ptr) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }


  png_init_io(png_ptr, fp);
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);
  
  png_set_IHDR(png_ptr, info_ptr, width, height, 8,
               3, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  if(transparent) {
    png_byte index;
    
    palette = (png_colorp)malloc((std.ncolors+1) * sizeof (png_color));
    /* ... set palette colors ... */
    for(i = 0; i < std.ncolors; i++) {
      palette[i].red = std.colormap[i].red;
      palette[i].green = std.colormap[i].green;
      palette[i].blue = std.colormap[i].blue;
    }
    palette[std.ncolors].red = std.special.red;
    palette[std.ncolors].green = std.special.green;
    palette[std.ncolors].blue = std.special.blue;
    index = std.ncolors;
    png_set_PLTE(png_ptr, info_ptr, palette, std.ncolors+1);
    png_set_tRNS(png_ptr, info_ptr, &index, 1, NULL);
    
  } else {
    palette = (png_colorp)malloc(std.ncolors * sizeof (png_color));
    /* ... set palette colors ... */
    for(i = 0; i < std.ncolors; i++) {
      palette[i].red = std.colormap[i].red;
      palette[i].green = std.colormap[i].green;
      palette[i].blue = std.colormap[i].blue;
    }
    png_set_PLTE(png_ptr, info_ptr, palette, std.ncolors);
  }
  
   

  
  png_write_info(png_ptr, info_ptr);
  
  rows = (unsigned char **) malloc(height * sizeof(unsigned char *));
  image = image8.data;
  
  for(k = 0; k < height; k++) {
    rows[k] = image;
    image += image8.rowbytes;
  }

  png_write_image(png_ptr, rows);
  png_write_end(png_ptr, info_ptr);
  
  fclose(fp);
  free(rows);
  free(palette);
  png_destroy_write_struct(&png_ptr, NULL);
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
  dst->rowbytes = ((((src->width + 7) >> 3) + 1) >> 1) << 1;

  dst->data = malloc(dst->rowbytes * dst->height);

  if(dst->data == NULL) {
    return 1;
  }

  data = dst->data;
  for(i = 0; i < dst->rowbytes * dst->height; i++) {
    data[i] = 0;
  }
  

  src_row = src->data;
  src_row += (src->height-1) * src->rowbytes;
  
  dst_row = dst->data;
  for(j = 0; j < src->height; j++) {
    src_pixel = src_row;
    dst_pixel = dst_row;
    for(i = 0; i < src->width; i++) {
      a = src_pixel[3];
      src_pixel += 4;
      if (a < 200)
        SetBit(dst_row, i);
    }
    src_row -= src->rowbytes;
    dst_row += dst->rowbytes;
  }
  return 0;
}


int betaImage2DIB(BetaImage *image, HBITMAP *phbmp)
{
  BITMAPINFO bmi;
  HDC hdc;
  int result = 0;
  int i, j;
  
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = image->width;
  bmi.bmiHeader.biHeight = -image->height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;

  hdc = GetDC(NULL);

  if(!hdc) {
    result = GetLastError();
    return result;
  }
  
  *phbmp = CreateDIBitmap(hdc, (LPBITMAPINFOHEADER) &bmi, CBM_INIT, image->data, &bmi, DIB_RGB_COLORS);
  
  
  if(!(*phbmp)) {
    result = GetLastError();
  }

  ReleaseDC(NULL, hdc);
  
  return result;
}



int readPNG(char *name, HBITMAP *phbmp, int *width, int *height, HBITMAP *hmask)
{
  BetaImage image;
  BetaImage rgb;
  BetaImage mask;
  
  int result;

  BITMAPINFO bmi;
  HDC hdc;
  

  result = BetaReadPNG(name, &image, 1);

  
  if(result != 0) {
    return result;
  }
  
  *width = image.width;
  *height = image.height;

  
  result = betaImage2RGB(&image, &rgb);


  if (result != 0) {
    return result;
  }

  betaImage2DIB(&rgb, phbmp);
  
  if(image.alpha) {
    betaImage2Mask(&image, &mask);
    *hmask = CreateBitmap(mask.width, mask.height, 1, 1, mask.data);
  }  
  return result;
}


void TransferRedPixels(unsigned char *src,
                       int srcrowbytes,
                       unsigned char *dst,
                       int dstrowbytes,
                       int x, int y,
                       int width, int height, int winwidth, int winheight)
{
  unsigned char *srcrow;
  unsigned char *dstrow;
  unsigned char *srcpixel;
  unsigned char *dstpixel;

  int xx;
  int yy;

  int a;
  
  int i;
  int j;

  
  yy = y;
  
  srcrow = src += srcrowbytes * (height - 1);
  dstrow = dst + (dstrowbytes * y) + 4 * x;
  
  for (i = 0; i < height; i++) {
    srcpixel = srcrow;
    dstpixel = dstrow;
    if(yy >= 0 && yy < winheight) {
      xx = x;
      for(j = 0; j < width; j++) {
        if (xx >= 0 && xx < winwidth) {
          a = srcpixel[3];
          dstpixel[0] = srcpixel[0] + ((255 - a) * dstpixel[0] / 0xFF);
          dstpixel[1] = srcpixel[1] + ((255 - a) * dstpixel[1] / 0xFF);
          dstpixel[2] = srcpixel[2] + ((255 - a) * dstpixel[2] / 0xFF);
        }
        srcpixel += 4;
        dstpixel += 4;
        xx++;
      }
    }
    yy++;
    srcrow -= srcrowbytes;
    dstrow += dstrowbytes;
  }
}


void TransferRaster(HDC hDC, int x, int y, int width, int height, HBITMAP hBmp)
{
  HDC     hMemDC = CreateCompatibleDC(hDC);
  HGDIOBJ hOld   = SelectObject(hMemDC, hBmp);
  BitBlt(hDC, x, y, width, height, hMemDC, 0, 0, SRCCOPY);
  SelectObject(hMemDC, hOld);
  DeleteObject(hMemDC);
}

int ReadPNGalpha(char *name, HBITMAP *phbmp, void **pixels, int *width, int *height, HBITMAP *hmask)
{
  int result;
  BetaImage image;
  BetaImage mask;
  
  void *pBits = NULL;
  unsigned char *src;
  unsigned char *dst;
  unsigned char  r, g, b, a;
  int i;
  
  HBITMAP hBmp;


  
  result = BetaReadPNG(name, &image, 2);
  if(result != 0) {
    return result;
  }
  
  *width = image.width;
  *height = image.height;
  
  {
    BITMAPINFO bmp = { { sizeof(BITMAPINFOHEADER), image.width, image.height, 1, 32 } };
    hBmp = CreateDIBSection(NULL, & bmp, DIB_RGB_COLORS, & pBits, NULL, 0);

    src = (char *) image.data;
    dst = (char *) pBits;
    for(i = 0; i < image.width * image.height; i++) {
      r = src[0];
      g = src[1];
      b = src[2];
      a = src[3];
      dst[0] = b * a / 0xFF;
      dst[1] = g * a / 0xFF;
      dst[2] = r * a / 0xFF;
      dst[3] = a;
      src += 4;
      dst += 4;
    }
  }
  if(image.alpha) {
    betaImage2Mask(&image, &mask);
    *hmask = CreateBitmap(mask.width, mask.height, 1, 1, mask.data);
  }

  
  /* Return the bitmap */
  *phbmp = hBmp;
  *pixels = pBits;
  return 0;
}
