#include <png.h>
#include <windows.h>
#include <stdio.h>



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
  int i, j;

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
