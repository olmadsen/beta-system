
void Rothstein(char *roth, int p, int q)
{
  int i = 0;
  int increment = q;

  while(i < q - 1) {
    increment += p;
    if(increment > q) {
      roth[i] = 1;
      increment -= q;
    }
    else {
      roth[i] = 0;
    }
    i++;
  }
  roth[i] = 0;
}

#include <math.h>


unsigned char clamp(double value)
{
  if (value > 254.0) {
    return 255;
  }
  else {
    return (unsigned char) (value + 0.5);
  }
}

void WeimanExpansionOut(unsigned char *src, long src_width, long src_height,
                        unsigned char *dst, long dst_width, long dst_height,
                        int p, int q) 
{
  int n;
  int k;
  char *roth;

  unsigned long *buffer;
  
  int i, j, s;
  int targetWidth;
  int sourceCol;
  
  n = src_height;
  k = src_width;


  
  
  targetWidth = ceil((double) (k * p)/ (double) q);

  buffer = (unsigned long *) malloc(4 * sizeof(unsigned long) * targetWidth);

  roth = (char *) malloc(p);
  Rothstein(roth, q, p);

  for (s = 0; s < n; s++) {
    for (i = 0; i < (4 * targetWidth); i++) {
      buffer[i] = 0;
    }
    for (i = 0; i < p; i++) {
      /* i is an implicit permutation of roth */
      sourceCol = 0;
      for (j = 0; j < targetWidth; j++) {
        if (roth[(j + i) % p] == 1) {
          buffer[j * 4] += src[s * (k*4) + (sourceCol * 4)];
          buffer[j * 4 + 1] += src[s * (k*4) + (sourceCol * 4) + 1];
          buffer[j * 4 + 2] += src[s * (k*4) + (sourceCol * 4) + 2];
          buffer[j * 4 + 3] += src[s * (k*4) + (sourceCol * 4) + 3];
          sourceCol++;
        }
      }
    }
    for (i = 0; i < (4 * targetWidth); i++) {
      dst[s * (dst_width * 4) + i] = clamp(buffer[i] / (double) q);
    }
  }
  
  free(buffer);
  free(roth);
}

void WeimanExpansionOutVert(unsigned char *src, long src_width, long src_height,
                        unsigned char *dst, long dst_width, long dst_height,
                        int p, int q) 
{
  int n;
  int k;
  char *roth;

  unsigned long *buffer;
  
  int i, j, s;
  int targetHeight;
  int sourceRow;
  
  n = src_height;
  k = src_width;

  targetHeight= ceil((double) (n * p)/ (double) q);

  
  buffer = (unsigned long *) malloc(4 * sizeof(unsigned long) * targetHeight);

  roth = (char *) malloc(p);
  Rothstein(roth, q, p);

  for (s = 0; s < k; s++) {
    for (i = 0; i < (4 * targetHeight); i++) {
      buffer[i] = 0;
    }
    for (i = 0; i < p; i++) {
      /* i is an implicit permutation of roth */
      sourceRow = 0;
      for (j = 0; j < targetHeight; j++) {
        if (roth[(j + i) % p] == 1) {
          buffer[j * 4] += src[sourceRow*k*4 + s*4];
          buffer[j * 4 + 1] += src[sourceRow*k*4 + s*4 + 1];
          buffer[j * 4 + 2] += src[sourceRow*k*4 + s*4 + 2];
          buffer[j * 4 + 3] += src[sourceRow*k*4 + s*4 + 3];
          sourceRow++;
        }
      }
    }
    for (i = 0; i <  targetHeight; i++) {
      dst[i * dst_width*4 + (s*4)] = clamp(buffer[i*4] / (double) q);
      dst[i * dst_width*4 + (s*4) + 1] = clamp(buffer[i*4 + 1] / (double) q);
      dst[i * dst_width*4 + (s*4) + 2] = clamp(buffer[i*4 + 2] / (double) q);
      dst[i * dst_width*4 + (s*4) + 3] = clamp(buffer[i*4 + 3] / (double) q);
    }
  }

  free(buffer);
  free(roth);
}


void WeimanExpansionIn(unsigned char *src, long src_width, long src_height,
                       unsigned char *dst, long dst_width, long dst_height,
                       int p, int q)
{
  int n;
  int k;
  char *roth;

  unsigned long *buffer;
  
  int i, j, s;
  int targetWidth;
  int destCol;
  
  n = src_height;
  k = src_width;


  
  
  targetWidth = ceil((double) (k * p)/ (double) q);

  buffer = (unsigned long *) malloc(4 * sizeof(unsigned long) * targetWidth);

  roth = (char *) malloc(q);
  
  Rothstein(roth, p, q);

  for (s = 0; s < n; s++) {
    for (i = 0; i < (4 * targetWidth); i++) {
      buffer[i] = 0;
    }
    for (i = 0; i < q; i++) {
      /* i is an implicit permutation of roth */
      destCol = 0;
      for (j = 0; j < k; j++) {
        if (roth[(j + i) % q] == 1) {
          buffer[destCol * 4] += src[s * (k*4) + (j * 4)];
          buffer[destCol * 4 + 1] += src[s * (k*4) + (j * 4) + 1];
          buffer[destCol * 4 + 2] += src[s * (k*4) + (j * 4) + 2];
          buffer[destCol * 4 + 3] += src[s * (k*4) + (j * 4) + 3];
          destCol++;
        }
      }
    }
    for (i = 0; i < (4 * targetWidth); i++) {
      dst[s * (dst_width * 4) + i] = clamp(buffer[i] / (double) q);
    }
  }
  
  free(buffer);
  free(roth);
}

void WeimanExpansionInVert(unsigned char *src, long src_width, long src_height,
                       unsigned char *dst, long dst_width, long dst_height,
                       int p, int q)
{
  int n;
  int k;
  char *roth;

  unsigned long *buffer;
  
  int i, j, s;
  int targetHeight;
  int destRow;
  
  n = src_height;
  k = src_width;


  
  
  targetHeight = ceil((double) (n * p)/ (double) q);

  buffer = (unsigned long *) malloc(4 * sizeof(unsigned long) * targetHeight);

  roth = (char *) malloc(q);
  
  Rothstein(roth, p, q);

  for (s = 0; s < k; s++) {
    for (i = 0; i < (4 * targetHeight); i++) {
      buffer[i] = 0;
    }
    for (i = 0; i < q; i++) {
      /* i is an implicit permutation of roth */
      destRow = 0;
      for (j = 0; j < n; j++) {
        if (roth[(j + i) % q] == 1) {
          buffer[destRow * 4] += src[j*k*4 + s*4];
          buffer[destRow * 4 + 1] += src[j*k*4 + s*4 + 1];
          buffer[destRow * 4 + 2] += src[j*k*4 + s*4 + 2];
          buffer[destRow * 4 + 3] += src[j*k*4 + s*4 + 3];
          destRow++;
        }
      }
    }
    for (i = 0; i < targetHeight; i++) {
      dst[i * dst_width*4 + (s*4)] = clamp(buffer[i*4] / (double) q);
      dst[i * dst_width*4 + (s*4) + 1] = clamp(buffer[i*4 + 1] / (double) q);
      dst[i * dst_width*4 + (s*4) + 2] = clamp(buffer[i*4 + 2] / (double) q);
      dst[i * dst_width*4 + (s*4) + 3] = clamp(buffer[i*4 + 3] / (double) q);
    }
  }
  
  free(buffer);
  free(roth);
}

