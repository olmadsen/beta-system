#include <png.h>
#include <windows.h>
#include <stdio.h>
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

int betaImage2Mask(BetaImage *src, BetaImage *dst)
{
  unsigned char a;
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

  src_row = src->data;
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
    src_row += src->rowbytes;
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
  

  result = BetaReadPNG(name, &image);

  printf("aaa\n");
  
  if(result != 0) {
    return result;
  }
  
  *width = image.width;
  *height = image.height;

  printf("bbb\n");
  
  result = betaImage2RGB(&image, &rgb);


  printf("...\n");
  if (result != 0) {
    return result;
  }

  betaImage2DIB(&rgb, phbmp);
  
  if(image.alpha) {
    printf("creating mask\n");
    betaImage2Mask(&image, &mask);
    *hmask = CreateBitmap(mask.width, mask.height, 1, 1, mask.data);
  }  
  return result;
}


int readPNG1(char *name, HBITMAP *phbmp, int *width, int *height, int *depth)
{
  HDC hdc;
  HDC hdcmem;
  
  HBITMAP hbmp;
  
  BetaImage image;
  UINT start;
  UINT num;
  BITMAPINFO bmi;
  UINT uUsage;
  int result;
  

  result = BetaReadPNGToBetaImage(name, &image);

  printf("read = %d\n", result);

  *width = image.width;
  *height = image.height;

  hdc = GetDC(NULL);

  if(!hdc) {
    printf("failed to get dc\n");
  }
  

  
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = image.width;
  bmi.bmiHeader.biHeight = -image.height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;
 
  
  *phbmp = CreateDIBitmap(hdc, (LPBITMAPINFOHEADER) &bmi, CBM_INIT, image.data, &bmi, DIB_RGB_COLORS);
  if(!(*phbmp)) {
    result = GetLastError();
  }
  ReleaseDC(NULL, hdc);
  return result;
}
