/* Header signatutes for various resources */
#define BFT_ICON   0x4349   /* 'IC' */
#define BFT_BITMAP 0x4d42   /* 'BM' */
#define BFT_CURSOR 0x5450   /* 'PT' */

/* macro to determine if resource is a DIB */
#define ISDIB(bft) ((bft) == BFT_BITMAP)

/* Macro to align given value to the closest DWORD (unsigned long ) */
#define ALIGNULONG(i)   ((i+3)/4*4)

/* Macro to determine to round off the given value to the closest byte */
#define WIDTHBYTES(i)   ((i+31)/32*4)

#define PALVERSION      0x300
#define MAXPALETTE      256       /* max. # supported palette entries */

typedef struct tagBITMAPINFOHEADER_EXT{ 
  DWORD  biSize; 
  LONG   biWidth; 
  LONG   biHeight; 
  WORD   biPlanes; 
  WORD   biBitCount;
  DWORD  biCompression; 
  DWORD  biSizeImage; 
  LONG   biXPelsPerMeter; 
  LONG   biYPelsPerMeter; 
  DWORD  biClrUsed; 
  DWORD  biClrImportant; 
  HBITMAP hBitmap;
} BITMAPINFOHEADER_EXT;

/*****************************************************/
/* make new sizeof structs to cover dword alignment  */
/*****************************************************/

#define SIZEOF_BITMAPFILEHEADER_PACKED  (   \
    sizeof(WORD) +      /* bfType      */   \
    sizeof(DWORD) +     /* bfSize      */   \
    sizeof(WORD) +      /* bfReserved1 */   \
    sizeof(WORD) +      /* bfReserved2 */   \
    sizeof(DWORD))      /* bfOffBits   */

     /* error codes */
#define BITMAP_OK 1
#define ERR_OPEN_FILE 2
#define ERR_READ_DI_BITMAPINFO 3
#define ERR_REALLOCATE_HDIB 4
#define ERR_READING_BITMAP_FROM_DIB 5
#define ERR_NO_RETURN_BUFFER 6
