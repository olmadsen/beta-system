#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include "loadbitmapfile.h"

#ifdef nti_gnu /* These are missing from the GNU include-files currently! */
 typedef BITMAPFILEHEADER FAR *LPBITMAPFILEHEADER;
 typedef BITMAPCOREHEADER FAR *LPBITMAPCOREHEADER;
#endif

HBITMAP BitmapFromDib (HANDLE );
HANDLE ReadDibBitmapInfo (HFILE);
BOOL DibInfo (HANDLE,LPBITMAPINFOHEADER);

HBRUSH myCreatePatternBrush (HBITMAP hBitmap)
{
  return CreatePatternBrush(hBitmap);
}

HBITMAP getGray(HDC hdcLocal)
{
  HANDLE hloc;
  LPBITMAPINFO pbmi;
  HBITMAP hbm;
  
  BYTE aBits[] = {   0x00, 0x00, 0x00, 0x00,    /* bottom row */
		     0x00, 0x00, 0x00, 0x00 };  /* top row    */
  
  RGBQUAD argbq[] = {{ 170, 170, 170, 0 },        
		       { 170, 170, 170, 0 },
		     { 170, 170, 170, 0 },
		     { 170, 170, 170, 0 },
		     { 170, 170, 170, 0 },
		     { 170, 170, 170, 0 },
		     { 170, 170, 170, 0 },
		     { 170, 170, 170, 0 }
		   };    
  
  hloc = LocalAlloc(LMEM_ZEROINIT | LMEM_MOVEABLE,
		    sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 2));
  pbmi = (LPBITMAPINFO) LocalLock(hloc);
  
  pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  pbmi->bmiHeader.biWidth = 8;
  pbmi->bmiHeader.biHeight = 8;
  pbmi->bmiHeader.biPlanes = 1;
  
  pbmi->bmiHeader.biBitCount = 1;
  pbmi->bmiHeader.biCompression = BI_RGB;
  
  memcpy(pbmi->bmiColors, argbq, sizeof(RGBQUAD) * 2 );
  
  hbm = CreateDIBitmap(hdcLocal, (BITMAPINFOHEADER FAR*) pbmi, CBM_INIT,
		       aBits, pbmi, DIB_RGB_COLORS);
  if (hbm==NULL)
    printf("getGray failed! \n");
  LocalFree(hloc);

  return hbm;
}
HBITMAP getLightGray(HDC hdcLocal)
{
  HANDLE hloc;
  LPBITMAPINFO pbmi;
  HBITMAP hbm;
  
  BYTE aBits[] = {   0x00, 0x00, 0x00, 0x00,    /* bottom row */
		     0x00, 0x00, 0x00, 0x00 };  /* top row    */
  
  RGBQUAD argbq[] = {{ 192, 192, 192, 0 },        
		       { 192, 192, 192, 0 },
		       { 192, 192, 192, 0 },
		       { 192, 192, 192, 0 },
		       { 192, 192, 192, 0 },
		       { 192, 192, 192, 0 },
		       { 192, 192, 192, 0 },
		       { 192, 192, 192, 0 }
		   };  
  
  hloc = LocalAlloc(LMEM_ZEROINIT | LMEM_MOVEABLE,
		    sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 2));
  pbmi = (LPBITMAPINFO) LocalLock(hloc);
  
  pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  pbmi->bmiHeader.biWidth = 8;
  pbmi->bmiHeader.biHeight = 8;
  pbmi->bmiHeader.biPlanes = 1;
  
  pbmi->bmiHeader.biBitCount = 1;
  pbmi->bmiHeader.biCompression = BI_RGB;
  
  memcpy(pbmi->bmiColors, argbq, sizeof(RGBQUAD) * 2);
  
  hbm = CreateDIBitmap(hdcLocal, (BITMAPINFOHEADER FAR*) pbmi, CBM_INIT,
		       aBits, pbmi, DIB_RGB_COLORS);
  LocalFree(hloc);

  if (hbm==NULL)
    printf("getGray failed! \n");

  return hbm;
}

HBITMAP getDarkGray(HDC hdcLocal)
{
  HANDLE hloc;
  LPBITMAPINFO pbmi;
  HBITMAP hbm;
  
  BYTE aBits[] = {   0x00, 0x00, 0x00, 0x00,    /* bottom row */
		     0x00, 0x00, 0x00, 0x00 };  /* top row    */
  
  RGBQUAD argbq[] = {{ 128, 128, 128, 0 },        
		       { 128, 128, 128, 0 },
		       { 128, 128, 128, 0 },
		       { 128, 128, 128, 0 },
		       { 128, 128, 128, 0 },
		       { 128, 128, 128, 0 },
		       { 128, 128, 128, 0 },
		       { 128, 128, 128, 0 }
		   };     
  
  hloc = LocalAlloc(LMEM_ZEROINIT | LMEM_MOVEABLE,
		    sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 2));
  pbmi = (LPBITMAPINFO) LocalLock(hloc);
  
  pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  pbmi->bmiHeader.biWidth = 8;
  pbmi->bmiHeader.biHeight = 8;
  pbmi->bmiHeader.biPlanes = 1;
  
  pbmi->bmiHeader.biBitCount = 1;
  pbmi->bmiHeader.biCompression = BI_RGB;
  
  memcpy(pbmi->bmiColors, argbq, sizeof(RGBQUAD) * 2);
  
  hbm = CreateDIBitmap(hdcLocal, (BITMAPINFOHEADER FAR*) pbmi, CBM_INIT,
		       aBits, pbmi, DIB_RGB_COLORS);
  LocalFree(hloc);

  if (hbm==NULL)
    printf("getGray failed! \n");

  return hbm;
}
HBITMAP getWhite(HDC hdcLocal)
{
  HANDLE hloc;
  LPBITMAPINFO pbmi;
  HBITMAP hbm;
  
  BYTE aBits[] = {   0x00, 0x00, 0x00, 0x00,    /* bottom row */
		     0x00, 0x00, 0x00, 0x00 };  /* top row    */
  
  RGBQUAD argbq[] = {{ 255, 255, 255, 0 },      
		       { 255, 255, 255, 0 },
		       { 255, 255, 255, 0 },
		       { 255, 255, 255, 0 },
		       { 255, 255, 255, 0 },
		       { 255, 255, 255, 0 },
		       { 255, 255, 255, 0 },
		       { 255, 255, 255, 0 }
		   };    
  
  hloc = LocalAlloc(LMEM_ZEROINIT | LMEM_MOVEABLE,
		    sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 2));
  pbmi = (LPBITMAPINFO) LocalLock(hloc);
  
  pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  pbmi->bmiHeader.biWidth = 8;
  pbmi->bmiHeader.biHeight = 8;
  pbmi->bmiHeader.biPlanes = 1;
  
  pbmi->bmiHeader.biBitCount = 1;
  pbmi->bmiHeader.biCompression = BI_RGB;
  
  memcpy(pbmi->bmiColors, argbq, sizeof(RGBQUAD) * 2);
  
  hbm = CreateDIBitmap(hdcLocal, (BITMAPINFOHEADER FAR*) pbmi, CBM_INIT,
		       aBits, pbmi, DIB_RGB_COLORS);
  LocalFree(hloc);

  if (hbm==NULL)
    printf("getGray failed! \n");

  return hbm;
}
HBITMAP getBlack(HDC hdcLocal)
{
  HANDLE hloc;
  LPBITMAPINFO pbmi;
  HBITMAP hbm;
  
  BYTE aBits[] = {   0x00, 0x00, 0x00, 0x00,    /* bottom row */
		     0x00, 0x00, 0x00, 0x00 };  /* top row    */
  
  RGBQUAD argbq[] = {{ 0, 0, 0, 0 },       
		       { 0, 0, 0, 0 },
		       { 0, 0, 0, 0 },
		       { 0, 0, 0, 0 },
		       { 0, 0, 0, 0 },
		       { 0, 0, 0, 0 },
		       { 0, 0, 0, 0 },
		       { 0, 0, 0, 0 }
		   };    
  
  hloc = LocalAlloc(LMEM_ZEROINIT | LMEM_MOVEABLE,
		    sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 2));
  pbmi = (LPBITMAPINFO) LocalLock(hloc);
  
  pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  pbmi->bmiHeader.biWidth = 8;
  pbmi->bmiHeader.biHeight = 8;
  pbmi->bmiHeader.biPlanes = 1;
  
  pbmi->bmiHeader.biBitCount = 1;
  pbmi->bmiHeader.biCompression = BI_RGB;
  
  memcpy(pbmi->bmiColors, argbq, sizeof(RGBQUAD) * 2);
  
  hbm = CreateDIBitmap(hdcLocal, (BITMAPINFOHEADER FAR*) pbmi, CBM_INIT,
		       aBits, pbmi, DIB_RGB_COLORS);
  LocalFree(hloc);

  if (hbm==NULL)
    printf("getGray failed! \n");

  return hbm;
  
}


/* Usage:
 *
 * (#
 *    loadBitmapFile: external
 *    (# filename: [1]@char;
 *       hbitmap: @integer;
 *    enter filename
 *    do 'LoadBitmapFile'->callC
 *    exit hbitmap
 *    #)
 *
 *    loadDIBitmapFile: external
 *    (# hdc: @integer;
 *       filename: [1]@char;
 *       hbitmap: @integer;
 *    enter (hdc,filename)
 *    do 'LoadDIBitmapFile'->callC
 *    exit hbitmap
 *    #)
 *
 * do '~beta/images/image.bmp'->expandToFullPath
 *       ->loadBitmapFile->DeleteObject;
 *    '~beta/images/image.bmp'->expandToFullPath
 *       ->loadBitmapFile->DeleteObject
 * #)
 *
 */
void ReadBitMapFileHeaderandConvertToDwordAlign(
						HFILE fh, 
						LPBITMAPFILEHEADER pbf, LPDWORD lpdwoff)
{
        DWORD off;

        off = _llseek(fh, 0L, (UINT) SEEK_CUR);
        *lpdwoff = off;

/*              BITMAPFILEHEADER STRUCUTURE is as follows 
 *              BITMAPFILEHEADER
 *              WORD    bfType 
 >          ....                  <     add WORD if packed here!
 *              DWORD   bfSize 
 *              WORD    bfReserved1
 *              WORD    bfReserved2
 *              DWORD   bfOffBits 
 *                      This is the packed format, unpacked adds a WORD after bfType
 */

        /* read in bfType*/
        _lread(fh, (LPSTR) &pbf->bfType, sizeof(WORD));
        /* read in last 3 dwords*/
        _lread(fh, (LPSTR) &pbf->bfSize, sizeof(DWORD) * 3);

}

WORD DibNumColors (VOID FAR * pv)
{
    INT                 bits;
    LPBITMAPINFOHEADER  lpbi;
    LPBITMAPCOREHEADER  lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    /*  With the BITMAPINFO format headers, the size of the palette
     *  is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *  is dependent on the bits per pixel ( = 2 raised to the power of
     *  bits/pixel).
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else
        bits = lpbc->bcBitCount;

    switch (bits){
        case 1:
                return 2;
        case 4:
                return 16;
        case 8:
                return 256;
        default:
                /* A 24 bitcount DIB has no color table */
                return 0;
    }
}
 
WORD PaletteSize (void * pv)
{
    LPBITMAPINFOHEADER lpbi;
    WORD               NumColors;

    lpbi      = (LPBITMAPINFOHEADER)pv;
    NumColors = DibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return (WORD)(NumColors * sizeof(RGBTRIPLE));
    else
        return (WORD)(NumColors * sizeof(RGBQUAD));
}

BOOL isBMPfile (LPSTR szFile)
{
  DWORD               off;
  HFILE               fh;
  OFSTRUCT            of;
  BITMAPFILEHEADER    bf;
  BITMAPINFOHEADER    bi;
  
  /* Open the file */
  fh = OpenFile(szFile, &of, (UINT)OF_READ);
  if (fh == -1)
    return FALSE;
  
#ifdef FIXDWORDALIGNMENT
  /* Reset file pointer and read file header */
  off = _llseek(fh, 0L, (UINT)SEEK_CUR);
  if ((SIZEOF_BITMAPFILEHEADER_PACKED)  != _lread(fh, (LPSTR)&bf, (UINT)sizeof (SIZEOF_BITMAPFILEHEADER_PACKED)))
    {
      _lclose(fh);
      return FALSE;
    }
#else
  ReadBitMapFileHeaderandConvertToDwordAlign(fh, &bf, &off);
  /* at this point we have read the file into bf*/
#endif
  
  /* Do we have a RC HEADER? */
  if (!ISDIB (bf.bfType)) 
    {    
      bf.bfOffBits = 0L;               
      _llseek(fh, off, (UINT)SEEK_SET); /*seek back to beginning of file*/
    }
  if (sizeof(bi) != _lread(fh, (LPSTR)&bi, (UINT)sizeof(bi)))
    {
      _lclose(fh);
      return FALSE;
    };

  _lclose(fh);

  switch ((INT)bi.biSize)
    {
    case sizeof (BITMAPINFOHEADER):
      break;
      
    case sizeof (BITMAPCOREHEADER):
      break;
      
    default:
      /* Not a DIB! */
      return FALSE;
    }
  
  return TRUE;
}

UINT LoadDIBitmapFile (LPSTR szFile, BITMAPINFOHEADER_EXT * lpBIHExt)
{
    HFILE               fh;
    BITMAPINFOHEADER    bi;
    LPBITMAPINFOHEADER  lpbi;
    DWORD               dwLen = 0;
    DWORD               dwBits;
    HANDLE              hdib;
    HANDLE              h;
    OFSTRUCT            of;
    char                str[255];
    HBITMAP             hbm = NULL;

    if (!lpBIHExt)
      return ERR_NO_RETURN_BUFFER;
    
    /* Open the file and read the DIB information */
    fh = OpenFile(szFile, &of, (UINT)OF_READ);
    if (fh == -1)
      {
	return ERR_OPEN_FILE;
      }
    
    hdib = ReadDibBitmapInfo(fh);
    if (!hdib)
      {
	return ERR_READ_DI_BITMAPINFO;
      }
    
    DibInfo(hdib,&bi);

    /* Calculate the memory needed to hold the DIB */
    dwBits = bi.biSizeImage;
    dwLen  = bi.biSize + (DWORD)PaletteSize (&bi) + dwBits;

    /* Record widht, height and depth. */
    lpBIHExt->biWidth = bi.biWidth;
    lpBIHExt->biHeight = bi.biHeight;
    lpBIHExt->biBitCount = bi.biBitCount;

    /* Try to increase the size of the bitmap info. buffer to hold the DIB */
    h = GlobalReAlloc(hdib, dwLen, GHND);
    if (!h)
      {
        GlobalFree(hdib);
        hdib = NULL;
	return ERR_REALLOCATE_HDIB;
      }
    else
      hdib = h;
    
    /* Read in the bits */
    if (hdib)
      {
        lpbi = (VOID FAR *)GlobalLock(hdib);
        _lread(fh, (LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi), dwBits);
        GlobalUnlock(hdib);
      }    
    _lclose(fh);
    
    hbm = BitmapFromDib(hdib);
    if (!hbm)
      {
	hbm = NULL;
	return ERR_READING_BITMAP_FROM_DIB;
      }
    
    lpBIHExt->hBitmap = hbm;
    lpBIHExt->hDib    = hdib;

    return BITMAP_OK;
}

BOOL DibInfo (
    HANDLE hbi,
    LPBITMAPINFOHEADER lpbi)
{
    if (hbi){
        *lpbi = *(LPBITMAPINFOHEADER)GlobalLock (hbi);

        /* fill in the default fields */
        if (lpbi->biSize != sizeof (BITMAPCOREHEADER)){
            if (lpbi->biSizeImage == 0L)
                                lpbi->biSizeImage = WIDTHBYTES(lpbi->biWidth*lpbi->biBitCount) * lpbi->biHeight;

            if (lpbi->biClrUsed == 0L)
                                lpbi->biClrUsed = DibNumColors (lpbi);
    }
        GlobalUnlock (hbi);
        return TRUE;
    }
    return FALSE;
}


HBITMAP BitmapFromDib (HANDLE hdib)
{
    LPBITMAPINFOHEADER  lpbi;
    HDC                 hdc;
    HBITMAP             hbm;

    if (!hdib)
        return NULL;

    lpbi = (VOID FAR *)GlobalLock(hdib);

    if (!lpbi)
        return NULL;

    hdc = GetDC(NULL);
    hbm = CreateDIBitmap(hdc,
                (LPBITMAPINFOHEADER)lpbi,
                (LONG)CBM_INIT,
                (LPSTR)lpbi + lpbi->biSize + PaletteSize(lpbi),
                (LPBITMAPINFO)lpbi,
                DIB_RGB_COLORS );

    ReleaseDC(NULL,hdc);
    GlobalUnlock(hdib);

    return hbm;
}


HANDLE ReadDibBitmapInfo (HFILE fh)
{
    DWORD     off;
    HANDLE    hbi = NULL;
    INT       size;
    INT       i;
    WORD      nNumColors;

    RGBQUAD FAR       *pRgb;
    BITMAPINFOHEADER   bi;
    BITMAPCOREHEADER   bc;
    LPBITMAPINFOHEADER lpbi;
    BITMAPFILEHEADER   bf;
    DWORD              dwWidth = 0;
    DWORD              dwHeight = 0;
    WORD               wPlanes, wBitCount;

    if (fh == -1)
        return NULL;
#ifdef FIXDWORDALIGNMENT
    /* Reset file pointer and read file header */
    off = _llseek(fh, 0L, (UINT)SEEK_CUR);
    if ((SIZEOF_BITMAPFILEHEADER_PACKED)  != _lread(fh, (LPSTR)&bf, (UINT)sizeof (SIZEOF_BITMAPFILEHEADER_PACKED)))
        return FALSE;
#else
        ReadBitMapFileHeaderandConvertToDwordAlign(fh, &bf, &off);
        /* at this point we have read the file into bf*/
#endif

    /* Do we have a RC HEADER? */
    if (!ISDIB (bf.bfType)) {    
        bf.bfOffBits = 0L;               
                _llseek(fh, off, (UINT)SEEK_SET); /*seek back to beginning of file*/
    }
    if (sizeof (bi) != _lread(fh, (LPSTR)&bi, (UINT)sizeof(bi)))
        return FALSE;

    nNumColors = DibNumColors (&bi);

    /* Check the nature (BITMAPINFO or BITMAPCORE) of the info. block
     * and extract the field information accordingly. If a BITMAPCOREHEADER,
     * transfer it's field information to a BITMAPINFOHEADER-style block
     */
    switch (size = (INT)bi.biSize){
        case sizeof (BITMAPINFOHEADER):
            break;

        case sizeof (BITMAPCOREHEADER):

            bc = *(BITMAPCOREHEADER*)&bi;

            dwWidth   = (DWORD)bc.bcWidth;
            dwHeight  = (DWORD)bc.bcHeight;
            wPlanes   = bc.bcPlanes;
            wBitCount = bc.bcBitCount;

	    bi.biSize           = sizeof(BITMAPINFOHEADER);
            bi.biWidth              = dwWidth;
            bi.biHeight             = dwHeight;
            bi.biPlanes             = wPlanes;
            bi.biBitCount           = wBitCount;

            bi.biCompression        = BI_RGB;
            bi.biSizeImage          = 0;
            bi.biXPelsPerMeter      = 0;
            bi.biYPelsPerMeter      = 0;
            bi.biClrUsed            = nNumColors;
            bi.biClrImportant       = nNumColors;

            _llseek(fh, (LONG)sizeof (BITMAPCOREHEADER) - sizeof (BITMAPINFOHEADER), (UINT)SEEK_CUR);
            break;

        default:
	  /* Not a DIB! */
	  return NULL;
    }

    /*  Fill in some default values if they are zero */
    if (bi.biSizeImage == 0){
        bi.biSizeImage = WIDTHBYTES ((DWORD)bi.biWidth * bi.biBitCount)
                         * bi.biHeight;
    }
    if (bi.biClrUsed == 0)
        bi.biClrUsed = DibNumColors(&bi);

    /* Allocate for the BITMAPINFO structure and the color table. */
    hbi = GlobalAlloc (GHND, (LONG)bi.biSize + nNumColors * sizeof(RGBQUAD));
    if (!hbi)
        return NULL;
    lpbi = (VOID FAR *)GlobalLock (hbi);
    *lpbi = bi;

    /* Get a pointer to the color table */
    pRgb = (RGBQUAD FAR *)((LPSTR)lpbi + bi.biSize);
    if (nNumColors){
        if (size == sizeof(BITMAPCOREHEADER)){
            /* Convert a old color table (3 byte RGBTRIPLEs) to a new
             * color table (4 byte RGBQUADs)
             */
            _lread(fh, (LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBTRIPLE));

            for (i = nNumColors - 1; i >= 0; i--){
                RGBQUAD rgb;

                rgb.rgbRed      = ((RGBTRIPLE FAR *)pRgb)[i].rgbtRed;
                rgb.rgbBlue     = ((RGBTRIPLE FAR *)pRgb)[i].rgbtBlue;
                rgb.rgbGreen    = ((RGBTRIPLE FAR *)pRgb)[i].rgbtGreen;
                rgb.rgbReserved = (BYTE)0;

                pRgb[i] = rgb;
            }
        }
        else
            _lread(fh, (LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBQUAD));
    }

    if (bf.bfOffBits != 0L){
        _llseek(fh, off + bf.bfOffBits, (UINT)SEEK_SET);
        }
    GlobalUnlock(hbi);
    return hbi;
}
 

 


void DrawTransparentBitmap(HWND hwnd, HBITMAP hBitmap, short xStart,
                           short yStart, int xDestPos, int yDestPos, COLORREF cTransparentColor)
{
   BITMAP     bm;
   COLORREF   cColor;
   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC        hdc, hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
   POINT      ptSize;

   hdc = GetDC ( hwnd );

   hdcTemp = CreateCompatibleDC(hdc);
   SelectObject(hdcTemp, hBitmap);   // Select the bitmap

   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device
                                     // to logical points

   // Create some DCs to hold temporary data.
   hdcBack   = CreateCompatibleDC(hdc);
   hdcObject = CreateCompatibleDC(hdc);
   hdcMem    = CreateCompatibleDC(hdc);
   hdcSave   = CreateCompatibleDC(hdc);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC

   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   bmBackOld   = SelectObject(hdcBack, bmAndBack);
   bmObjectOld = SelectObject(hdcObject, bmAndObject);
   bmMemOld    = SelectObject(hdcMem, bmAndMem);
   bmSaveOld   = SelectObject(hdcSave, bmSave);

   // Set proper mapping mode.
   SetMapMode(hdcTemp, GetMapMode(hdc));


   // Save the bitmap sent here, because it will be overwritten.
   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   cColor = SetBkColor(hdcTemp, cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt()
   // from the source bitmap to a monochrome bitmap.
   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
          SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   SetBkColor(hdcTemp, cColor);


   // Create the inverse of the object mask.
   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
          NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xDestPos, yDestPos,
          SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);


   // Copy the destination to the screen.
   BitBlt(hdc, xDestPos, yDestPos, ptSize.x, ptSize.y, hdcMem, xStart, yStart,
          SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   // Delete the memory bitmaps.
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));

   // Delete the memory DCs.
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);

   DeleteDC(hdcObject);
   DeleteDC(hdcSave);
   DeleteDC(hdcTemp);

   ReleaseDC(hwnd,hdc);
 }


/* BOOL drawBitmap( HWND hwnd, HBITMAP hBitmap, int xSrcPos, int ySrcPos, 
                 int xDestPos, int yDestPos)
{
  HDC hdc, hdcMem;
  BITMAP bm;

  if (!hBitmap)
    return (FALSE );
  hdc = GetDC ( hwnd );
  SetBkColor(hdc,GetSysColor(COLOR_WINDOW));
  hdcMem = CreateCompatibleDC( hdc );
  SelectObject ( hdcMem, hBitmap );
  SetMapMode( hdcMem, GetMapMode( hdc ) );
  GetObject( hBitmap, sizeof(BITMAP), (LPSTR) &bm );
  BitBlt( hdc, xDestPos, yDestPos, bm.bmWidth, bm.bmHeight, 
          hdcMem, xSrcPos, ySrcPos, SRCCOPY );
  ReleaseDC( hwnd, hdc);
  DeleteDC( hdcMem );
  return( TRUE );
} */

BOOL drawBitmap (HWND hwnd, HBITMAP hbm, INT x, INT y,  
                 INT xDestPos, INT yDestPos)
{
    HDC       hdcBits;
    HDC       hdc;
    BITMAP    bm;
    BOOL      f;

    hdc = GetDC ( hwnd );

    if (!hdc || !hbm)
        return FALSE;

    hdcBits = CreateCompatibleDC(hdc);
    GetObject(hbm,sizeof(BITMAP),(LPSTR)&bm);
    SelectObject(hdcBits,hbm);
    f = BitBlt(hdc,xDestPos,yDestPos,bm.bmWidth,bm.bmHeight,hdcBits,x,y,SRCCOPY);
    DeleteDC(hdcBits);
    ReleaseDC( hwnd, hdc);

    return f;
}


/* BOOL zoomBitmap( HWND hwnd, HBITMAP hBitmap, int xSrcPos, int ySrcPos, int width, int height,
                 int xDestPos, int yDestPos, int zoomFactor)
{ HDC hdc, hdcMem;
  BITMAP bm;

  if (!hBitmap)
    return (FALSE );
  hdc = GetDC ( hwnd );
  SetBkColor(hdc,GetSysColor(COLOR_WINDOW));
  hdcMem = CreateCompatibleDC( hdc );
  SelectObject ( hdcMem, hBitmap );
  SetMapMode( hdcMem, GetMapMode( hdc ) );
  GetObject( hBitmap, sizeof(BITMAP), (LPSTR) &bm );
  StretchBlt( hdc, xDestPos, yDestPos, 
	     width * zoomFactor, height * zoomFactor, 
	     hdcMem, xSrcPos, ySrcPos, width, height, SRCCOPY );
  ReleaseDC( hwnd, hdc);
  DeleteDC( hdcMem );
  return( TRUE );
} */

BOOL zoomBitmap( HDC hdc, HBITMAP hBitmap, int xSrcPos, int ySrcPos, int width, int height,
                 int xDestPos, int yDestPos, int zoomFactor)
{ HDC hdcMem;
  BITMAP bm;

  if (!hBitmap)
    return (FALSE );
  /* SetBkColor(hdc,GetSysColor(COLOR_WINDOW)); */
  hdcMem = CreateCompatibleDC( hdc );
  SelectObject ( hdcMem, hBitmap );
  SetMapMode( hdcMem, GetMapMode( hdc ) );
  GetObject( hBitmap, sizeof(BITMAP), (LPSTR) &bm );
  StretchBlt( hdc, xDestPos, yDestPos, 
	     width * zoomFactor, height * zoomFactor, 
	     hdcMem, xSrcPos, ySrcPos, width, height, SRCCOPY );
  DeleteDC( hdcMem );
  return( TRUE );
} 

int bitMapGetWidth( HBITMAP hBitmap )
{
  BITMAP bm;

  GetObject( hBitmap, sizeof(BITMAP), (LPSTR) &bm );
  return ( bm.bmWidth );
}
 
int bitMapGetHeight( HBITMAP hBitmap )
{
  BITMAP bm;

  GetObject( hBitmap, sizeof(BITMAP), (LPSTR) &bm );
  return ( bm.bmHeight );
}

int iconGetWidth ( HICON hIcon )
{ ICONINFO IconInfo;
  BITMAP bm;

  if (GetIconInfo( hIcon, &IconInfo))
    {
      GetObject( IconInfo.hbmMask, sizeof(BITMAP), &bm);
      DeleteObject(IconInfo.hbmMask);
      DeleteObject(IconInfo.hbmColor);
      return (bm.bmWidth);
    }
  else 
    return 0;
}


/*
int main(int argc, char **argv)
{
  HBITMAP hbm;
  while (--argc) {
    printf("\n%s\n",*++argv);
    hbm = loadBitmapFile(*argv);
    if (!hbm)
      printf("Load failed\n");
    else {
      printf("Loaded OK\n");
      DeleteObject(hbm);
    }
    hbm = loadDIBitmapFile(*argv);
    if (!hbm)
      printf("Load failed\n");
    else {
      printf("Loaded OK\n");
      DeleteObject(hbm);
    }
  }
  return 0;
}
*/
