#include <windows.h>
#include "ijl.h"


int ReadJPGFileToDib(char *path, BITMAPINFOHEADER **dib)
{
  IJLERR jerr;
  long width;
  long height;
  long nchannels;
  long dib_line_width;
  long dib_pad_bytes;
  long wholeimagesize;

  char *buffer;
  BITMAPINFOHEADER *bmih;

  JPEG_CORE_PROPERTIES jcprops;

  buffer = NULL;
  bmih = NULL;
  
  jerr = ijlInit(&jcprops);
  
  if (jerr != IJL_OK) {
    return 1;
  }

  jcprops.JPGFile = path;

  jerr = ijlRead(&jcprops, IJL_JFILE_READPARAMS);

  if (jerr != IJL_OK) {
    ijlFree(&jcprops);
    return 1;
  }

  width = jcprops.JPGWidth;
  height = jcprops.JPGHeight;
  nchannels = 3;

  dib_line_width = width * nchannels;
  dib_pad_bytes = IJL_DIB_PAD_BYTES(width, nchannels);

  wholeimagesize = (dib_line_width + dib_pad_bytes) * height;

  buffer = (char *) malloc(sizeof(BITMAPINFOHEADER) + wholeimagesize);

  if(buffer == NULL) {
    ijlFree(&jcprops);
    return 1;
  }

  bmih = (BITMAPINFOHEADER *) buffer;

  bmih->biSize = sizeof(BITMAPINFOHEADER);
  bmih->biWidth = width;
  bmih->biHeight = height;
  bmih->biPlanes = 1;
  bmih->biBitCount = 24;
  bmih->biCompression = BI_RGB;
  bmih->biSizeImage = 0;
  bmih->biXPelsPerMeter = 0;
  bmih->biYPelsPerMeter = 0;
  bmih->biClrUsed = 0;
  bmih->biClrImportant = 0;

  jcprops.DIBWidth = width;
  jcprops.DIBHeight = -height;
  jcprops.DIBChannels = nchannels;
  jcprops.DIBColor = IJL_BGR;
  jcprops.DIBPadBytes = dib_pad_bytes;
  jcprops.DIBBytes = buffer + sizeof(BITMAPINFOHEADER);

  switch(jcprops.JPGChannels) {
  case 1:
    jcprops.JPGColor = IJL_G;
    break;
  case 3:
    jcprops.JPGColor = IJL_YCBCR;
    break;
  default:
    jcprops.DIBColor = (IJL_COLOR)IJL_OTHER;
    jcprops.JPGColor = (IJL_COLOR)IJL_OTHER;
    break;
  }

  jerr = ijlRead(&jcprops, IJL_JFILE_READWHOLEIMAGE);
  
  if (jerr != IJL_OK) {
    free(buffer);
    ijlFree(&jcprops);
    return 1;
  }

  *dib = bmih;
  return 0;

}



int ReadJPGtoDibSection(char *name, HBITMAP *hbmp, char **pixels, long *width, long *height)
{
  BITMAPINFOHEADER *bmih;

  int err;
  void *pBits;
  int i;
  unsigned char *src;
  unsigned char *dst;
  unsigned char r;
  unsigned char g;
  unsigned char b;

  
  
  err = ReadJPGFileToDib(name, &bmih);

  if (err != 0) {
    return 1;
  }

  bmih->biBitCount = 32;
  *hbmp = CreateDIBSection(NULL, (BITMAPINFO *) bmih, DIB_RGB_COLORS, &pBits, NULL, 0);

  src = ((unsigned char *) bmih) + sizeof(BITMAPINFOHEADER);
  dst = (unsigned char *) pBits;
  *pixels = pBits;
  
  for(i = 0; i < (bmih->biWidth) * (bmih->biHeight); i++) {

    r = src[0];
    g = src[1];
    b = src[2];

    dst[0] = r;
    dst[1] = g;
    dst[2] = b;
    src += 3;
    dst += 4;
  }

  *width = bmih->biWidth;
  *height = bmih->biHeight;
  
  free(bmih);

  
  return 0;
}

int WriteDIBtoJPGFile(char *path, BITMAPINFOHEADER *bmih, long quality)
{
  IJLERR jerr;
  long dib_pad_bytes;

  JPEG_CORE_PROPERTIES jcprops;

  jerr = ijlInit(&jcprops);
  if(jerr != IJL_OK) {
    return 1;
  }

  dib_pad_bytes = IJL_DIB_PAD_BYTES(bmih->biWidth, 3);

  jcprops.DIBWidth = bmih->biWidth;
  jcprops.DIBHeight = -bmih->biHeight;
  jcprops.DIBBytes = ((unsigned char *) bmih + sizeof(BITMAPINFOHEADER));
  jcprops.DIBChannels = 3;
  jcprops.DIBColor = IJL_BGR;

  jcprops.JPGFile = path;

  jcprops.JPGWidth = bmih->biWidth;
  jcprops.JPGHeight = bmih->biHeight;

  jcprops.JPGChannels = 3;
  jcprops.JPGColor = IJL_YCBCR;
  jcprops.JPGSubsampling = IJL_411;
  jcprops.jquality = quality;

  jerr = ijlWrite(&jcprops, IJL_JFILE_WRITEWHOLEIMAGE);

  ijlFree(&jcprops);

  if (jerr != IJL_OK) {
    return 1;
  }

  return 0;
  
  
}

int WriteDIBSectionToJPGFile(char *name,
                             unsigned char *pixels, long width, long height,
                             long left, long top, long right, long bottom,
                             long chan, long quality)
{
  long dib_line_width;
  long nchannels;
  long dib_pad_bytes;
  long wholeimagesize;
  char *buffer;
  BITMAPINFOHEADER *bmih;
  int i;
  int j;
  
  unsigned char *src;
  unsigned char *dst;
  unsigned char *row;
  unsigned char r;
  unsigned char g;
  unsigned char b;
  
 
  buffer = NULL;
  bmih = NULL;
  
  nchannels = 3;
  dib_line_width = (right - left) * nchannels;
  dib_pad_bytes = IJL_DIB_PAD_BYTES((right - left), nchannels);

  wholeimagesize = (dib_line_width + dib_pad_bytes) * (bottom - top);

  buffer = (char *) malloc(sizeof(BITMAPINFOHEADER) + wholeimagesize);
  if(buffer == NULL) {
    return 1;
  }

  bmih = (BITMAPINFOHEADER *) buffer;
  
  bmih->biSize = sizeof(BITMAPINFOHEADER);
  bmih->biWidth = (right - left);
  bmih->biHeight = (bottom - top);
  bmih->biPlanes = 1;
  bmih->biBitCount = 24;
  bmih->biCompression = BI_RGB;
  bmih->biSizeImage = 0;
  bmih->biXPelsPerMeter = 0;
  bmih->biYPelsPerMeter = 0;
  bmih->biClrUsed = 0;
  bmih->biClrImportant = 0;

  row = pixels;
  dst = ((unsigned char *) bmih) + sizeof(BITMAPINFOHEADER);

  for (j = 0; j < bmih->biHeight; j++) {
    src = row + left * chan;
    for(i = 0; i < bmih->biWidth; i++) {
      r = src[0];
      g = src[1];
      b = src[2];
      dst[0] = r;
      dst[1] = g;
      dst[2] = b;
      src += chan;
      dst += 3;
    }
    row += width * chan;
  }
  WriteDIBtoJPGFile(name, bmih, quality);
  
  free(buffer);
  return 0;
}

