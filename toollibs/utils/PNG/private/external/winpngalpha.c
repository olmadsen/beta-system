/* The following are inspired by an  article by Feng Yuan at
 * http://www.fengyuan.com/article/alphablend.html
 */

#include <png.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "betapng.h"



int ReadPNGalpha(char *name, HBITMAP *phbmp, int *width, int *height)
{
  int result;
  BetaImage image;
  
  void *pBits = NULL;
  char *src;
  char *dst;
  char r, g, b, a;
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
      dst[0] = b;
      dst[1] = g;
      dst[2] = r;
      dst[3] = a;
      src += 4;
      dst += 4;
    }
  }
  /* Return the bitmap */
  *phbmp = hBmp;
  return 0;
}

void AlphaDraw(HDC hDC, int x, int y, int width, int height, HBITMAP hBmp)
{
  HDC     hMemDC = CreateCompatibleDC(hDC);
  HGDIOBJ hOld   = SelectObject(hMemDC, hBmp);
  BLENDFUNCTION pixelblend = { AC_SRC_OVER, 0, 255, 0x1 };
  AlphaBlend(hDC, x, y+height, width, height, hMemDC, 0, 0, width, height, pixelblend); // blend with per-pixel alpha
  SelectObject(hMemDC, hOld);
  DeleteObject(hMemDC);
}

