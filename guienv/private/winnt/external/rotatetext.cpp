#include <windows.h>
#include <Winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>                    // for trigonometry functions

extern "C" 
{
  HFONT MyCreateFont_ext( int angle, int height,int weight,bool italic,char *faceName,
			  HDC hdc)
  { 
    LOGFONT lf; 
    HFONT hfont; 
 
    
    // Specify a font typeface name and weight and height. 

    lstrcpy(lf.lfFaceName, faceName); 
    lf.lfWeight = weight; 
    lf.lfHeight = -1*(height);

    lf.lfItalic = italic;
    lf.lfQuality = ANTIALIASED_QUALITY;

    lf.lfEscapement = angle; 
    lf.lfOrientation = angle; 
    lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
    lf.lfClipPrecision = CLIP_LH_ANGLES;
 
    hfont = CreateFontIndirect(&lf); 

    return (hfont); 
  } 

  void drawRotatedText_ext1 (char *theText,int angle,
			    int height,int weight,bool italic,char *faceName,
			    HDC hdc)
  {
    HFONT hfnt, hfntPrev;
    int x, y;
  
    // Allocate memory for a LOGFONT structure.
  
    PLOGFONT plf = (PLOGFONT) LocalAlloc(LPTR, sizeof(LOGFONT));
    if (!plf) {
      return;
    }
  
    // Specify a font typeface name and weight and height.
  
    lstrcpy(plf->lfFaceName, faceName);
    plf->lfWeight = weight;
    plf->lfHeight = -1*(height);
  
    plf->lfItalic = italic;
    plf->lfQuality = ANTIALIASED_QUALITY;
  
    plf->lfEscapement = angle;
    plf->lfOrientation = angle;
    plf->lfOutPrecision = OUT_TT_ONLY_PRECIS;
    plf->lfClipPrecision = CLIP_LH_ANGLES;
    hfnt = CreateFontIndirect(plf);
  
    hfntPrev = (HFONT)SelectObject(hdc, hfnt);
  
    UINT prevTextAlign = GetTextAlign(hdc);
    SetTextAlign(hdc,TA_BASELINE|TA_LEFT|TA_NOUPDATECP);
  
    int inx = 0;
    SIZE size;
    GetTextExtentPoint32(hdc,theText,strlen(theText),&size);
    int strHeight = size.cy;
  
    POINT start;
    GetCurrentPositionEx(hdc, &start);
    x = start.x; y = start.y;
    int ox = x;
    int oy = y;
  
    angle = angle/10;
    if (angle<0)
      angle = 360 + angle;
    double A = (((angle) * 3.14159265358979323846)/180) +
      1.57079632679489661923;
  
  
    double deltaX = cos(A) * strHeight;
    double deltaY = sin(A) * strHeight;
  
    char * tempText = (char*)malloc(strlen(theText)+1);
    if (!tempText) {
      goto cleanup;
    }
  
    while (*theText)
      {
	if (*theText == '\n')
	  {
	    tempText[inx++] = '\0';
	    TextOut(hdc, x, y,
		    tempText, lstrlen(tempText));
	    inx = 0;
	    theText++;
          
	    if ((angle==0) || (angle==360))
	      {
		y = y + strHeight;
	      }
	    else if (angle==90)
	      {
		x = x + strHeight;
	      }
	    else if (angle==180)
	      {
		y = y - strHeight;
	      }
	    else if (angle==270)
	      {
		x = x - strHeight;
	      }
	    else if ((0 < angle) && (angle < 90))
	      {
		x = x + abs((int)deltaX);
		y = y + abs((int)deltaY);
	      }
	    else if ((90 < angle) && (angle < 180))
	      {
		x = x + abs((int)deltaX);
		y = y - abs((int)deltaY);
	      }
	    else if ((180 < angle) && (angle < 270))
	      {
		x = x - abs((int)deltaX);
		y = y - abs((int)deltaY);
	      }
	    else if ((270 < angle) && (angle < 360))
	      {
		x = x - abs((int)deltaX);
		y = y + abs((int)deltaY);
	      }
          
	    MoveToEx(hdc,x,y,NULL);
	  }
	else
	  {
	    tempText[inx++] = *theText++;
	  }
      }
    tempText[inx++] = '\0';
    TextOut(hdc, x, y,
	    tempText, lstrlen(tempText));
  
    MoveToEx(hdc,ox,oy,NULL);
  
    SetTextAlign(hdc,prevTextAlign);
    SelectObject(hdc, hfntPrev);
  
  cleanup:
    if (hfnt)
      DeleteObject(hfnt);
  
    // Free the memory allocated for the LOGFONT structure.
    if (plf)
      LocalFree((LOCALHANDLE) plf);
  
    //Free memory allocated for tempText;
    if (tempText)
      free(tempText);
  
  }
}
