/* This i part of a opengl interface for beta 
   Flemming Gram, gram@mjolner.dk 
   */

#include <stdio.h>

#if 0
#ifndef nti
extern long glwMDrawingAreaWidgetClass;
#endif
#endif


long FloatToLong(float c)
{ 
   return (long) (c);
}

double FloatToReal(float c)
{
	return (double) c;
}

/*-----C-function definitions -----*/
#ifdef nti
#include <windows.h>
#else
#define WINGDIAPI 
#define APIENTRY
#endif

WINGDIAPI void APIENTRY glClearIndex( float c );
WINGDIAPI void APIENTRY glClearColor(float red,float green,float blue,float alpha);
WINGDIAPI void APIENTRY glPointSize(float size);
WINGDIAPI void APIENTRY glLineWidth(float width );
WINGDIAPI void APIENTRY glPolygonOffset(float,float);
WINGDIAPI void APIENTRY glClearAccum( float red, float green, float blue,float alpha );
WINGDIAPI void APIENTRY glAccum( int op, float value );
WINGDIAPI void APIENTRY glFrumstum(double left,double right,double bottom,double top,double near_,double far_);
WINGDIAPI void APIENTRY glVertex4d(double,double,double,double); 
WINGDIAPI void APIENTRY glColor4f(float,float,float,float);
WINGDIAPI void APIENTRY glColor4d(double,double,double,double);
WINGDIAPI void APIENTRY glTexCoord1f(float);
WINGDIAPI void APIENTRY glTexCoord4d(double,double,double,double);
WINGDIAPI void APIENTRY glRasterPos4d(double,double,double,double);
WINGDIAPI void APIENTRY glRectd(double,double,double,double);
WINGDIAPI void APIENTRY glLightf(int,int,float);
WINGDIAPI void APIENTRY glLightfv(int,int,float*);
WINGDIAPI void APIENTRY glLightModelf(int,float);
WINGDIAPI void APIENTRY glLightModelfv(int,float*);
WINGDIAPI void APIENTRY glMaterialf(int face,int pname, float param );
WINGDIAPI void APIENTRY glMaterialfv(int,int,float*);
WINGDIAPI void APIENTRY glPixelZoom(float,float);
WINGDIAPI void APIENTRY glPixelStoref(int,float);
WINGDIAPI void APIENTRY glBitmap(int,int,float,float,float,float,char*);
WINGDIAPI void APIENTRY glTexEnvf(int,int,float);
WINGDIAPI void APIENTRY glTexParameterf(int,int,float);
WINGDIAPI void APIENTRY glMap2d( int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, double* points );
WINGDIAPI void APIENTRY glMapGrid2d(int,double,double,int,double,double);
WINGDIAPI void APIENTRY glFogf(int,float);
WINGDIAPI void APIENTRY glPassThrough(float);
WINGDIAPI void APIENTRY glBlendColorEXT(float,float,float,float);
WINGDIAPI void APIENTRY glPolygonOffsetEXT(float,float);
/*WINGDIAPI void APIENTRY glPointParameterfEXT(int,float);*/
WINGDIAPI void APIENTRY glOrtho(double,double,double,double,double,double);
WINGDIAPI void APIENTRY glFrustum(double,double,double,double,double,double);
WINGDIAPI void APIENTRY glRotated(double,double,double,double);
WINGDIAPI void APIENTRY glPixelTransferf(unsigned int,float);
/*GLU prototypes */
WINGDIAPI void APIENTRY gluLookAt(double,double,double,double,double,double,double,double,double);

WINGDIAPI void APIENTRY gluOrtho2D(double,double,double,double);
WINGDIAPI void APIENTRY gluPerspective(double,double,double,double);
WINGDIAPI void APIENTRY gluPickMatrix(double,double,double,double,int*);
WINGDIAPI void APIENTRY gluCylinder(void*,double,double,double,int,int);
WINGDIAPI void APIENTRY gluPartialDisk(void*,double,double,int,int,double,double);
WINGDIAPI void APIENTRY gluNurbsProperty(void*,int,float);

/*----------HELPERS-------------*/
#if 0
#ifndef nti
long openGLWidgetClass(void) 
{
  return glwMDrawingAreaWidgetClass;
}
#endif
#endif

#ifdef nti

void printPixelFormat (PIXELFORMATDESCRIPTOR *pfd)
{

       /* print the table header */
       printf("   visual  x  bf lv rg d st  r  g  b a  ax dp st accum buffs  ms \n");
       printf(" id dep cl sp sz l  ci b ro sz sz sz sz bf th cl  r  g  b  a ns b\n");
       printf("-----------------------------------------------------------------\n");
       /* print out the information for this pixel format */

       /* print out the information for this pixel format */
	printf("0x%02x ", 1);

	printf("%2d ", pfd->cColorBits);
	if(pfd->dwFlags & PFD_DRAW_TO_WINDOW)      printf("wn ");
	else if(pfd->dwFlags & PFD_DRAW_TO_BITMAP) printf("bm ");
	else printf(".  ");

	/* should find transparent pixel from LAYERPLANEDESCRIPTOR */
	printf(" . "); 

	printf("%2d ", pfd->cColorBits);

	/* bReserved field indicates number of over/underlays */
	if(pfd->bReserved) printf(" %d ", pfd->bReserved);
	else printf(" . "); 

	printf(" %c ", pfd->iPixelType == PFD_TYPE_RGBA ? 'r' : 'c');

	printf("%c ", pfd->dwFlags & PFD_DOUBLEBUFFER ? 'y' : '.');

	printf(" %c ", pfd->dwFlags & PFD_STEREO ? 'y' : '.');

	if(pfd->cRedBits)        printf("%2d ", pfd->cRedBits);
	else printf(" . ");

	if(pfd->cGreenBits)      printf("%2d ", pfd->cGreenBits);
	else printf(" . ");

	if(pfd->cBlueBits)       printf("%2d ", pfd->cBlueBits);
	else printf(" . ");

	if(pfd->cAlphaBits)      printf("%2d ", pfd->cAlphaBits);
	else printf(" . ");

	if(pfd->cAuxBuffers)     printf("%2d ", pfd->cAuxBuffers);
	else printf(" . ");

	if(pfd->cDepthBits)      printf("%2d ", pfd->cDepthBits);
	else printf(" . ");

	if(pfd->cStencilBits)    printf("%2d ", pfd->cStencilBits);
	else printf(" . ");

	if(pfd->cAccumRedBits)   printf("%2d ", pfd->cAccumRedBits);
	else printf(" . ");

	if(pfd->cAccumGreenBits) printf("%2d ", pfd->cAccumGreenBits);
	else printf(" . ");

	if(pfd->cAccumBlueBits)  printf("%2d ", pfd->cAccumBlueBits);
	else printf(" . ");

	if(pfd->cAccumAlphaBits) printf("%2d ", pfd->cAccumAlphaBits);
	else printf(" . ");

	/* no multisample in Win32 */
	printf(" . .\n");
	
}



int setPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR* ppfd;
	int formatindex;

	PIXELFORMATDESCRIPTOR pfd = { 
	  sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
	  1,                     // version number 
	  PFD_DRAW_TO_WINDOW |   // support window 
	  PFD_SUPPORT_OPENGL |   // support OpenGL 
	  PFD_DOUBLEBUFFER,      // double buffered 
	  PFD_TYPE_RGBA,         // RGBA type 
	  32,                    // 24-bit color depth 
	  0, 0, 0, 0, 0, 0,      // color bits ignored 
	  0,                     // no alpha buffer 
	  0,                     // shift bit ignored 
	  0,                     // no accumulation buffer 
	  0, 0, 0, 0,            // accum bits ignored 
	  24,                    // 32-bit z-buffer 
	  4,                     // 8 bit stencil buffer requested
	  0,                     // no auxiliary buffer 
	  PFD_MAIN_PLANE,        // main layer     
	  0,                     // reserved 
	  0, 0, 0                // layer masks ignored 
	}; 

	pfd.cColorBits = GetDeviceCaps(hdc,BITSPIXEL);
	ppfd=&pfd;

        
        formatindex=ChoosePixelFormat(hdc,ppfd);

	if (0==SetPixelFormat(hdc,formatindex,ppfd)) {
		return 0;
	};
	return 1;
}

#define SETPIXELFORMATOVERLAY_NO_OVERLAYS    -1
#define SETPIXELFORMATOVERLAY_FORMAT_FAILED  -2
#define SETPIXELFORMATOVERLAY_PALETTE_FAILED -3

#define NORMAL 1
#define OVERLAY 2

int checkPixelFormat(HDC hDC, int pf, PIXELFORMATDESCRIPTOR *pfd)
{
    LAYERPLANEDESCRIPTOR  lpd;
    
    if (pfd->dwFlags & PFD_GENERIC_FORMAT) {
    	/* are not hardware accelerated */
    	return 0;
    }


    if (!(pfd->dwFlags & PFD_SUPPORT_OPENGL)) {
    	/* Does not support opengl */
    	return 0;
    }
    
    if (!(pfd->dwFlags & PFD_DRAW_TO_WINDOW)) {
    	/* Does not support drawing to a window */
    	return 0;
    }
    
    if (!(pfd->dwFlags & PFD_DOUBLEBUFFER)) {
    	/* Does not support double-buffering */
    	return 0;
    }
    
    if (pfd->iPixelType != PFD_TYPE_RGBA) {
       /* runs in indexed mode */
       return 0;
    };
    
    if (pfd->cDepthBits < 16) {
       /* not enough depth  */
       return 0;
    };
    
    if (pfd->cStencilBits < 4) {
       /* not enough stencil  */
       return 0; 
    };
    
    if (pfd->bReserved == 0) {
       /* Has no overlay planes */
       return NORMAL;
    }
    
    wglDescribeLayerPlane(hDC, pf, 1, sizeof(LAYERPLANEDESCRIPTOR), &lpd);

    if (!(lpd.dwFlags & LPD_SUPPORT_OPENGL)) {
       /* does not support opengl */
       return NORMAL;
    }

    return OVERLAY;
}



int setPixelFormatOverlay1(HDC hDC, BYTE type, DWORD flags, int nEntries, COLORREF *crEntries)
{
    int pf, maxpf, ne;
    PIXELFORMATDESCRIPTOR pfd;
    LAYERPLANEDESCRIPTOR  lpd;		/* layer plane descriptor */

    /* get the maximum number of pixel formats */
    maxpf = DescribePixelFormat(hDC, 0, 0, NULL);
    
    /* find an overlay layer descriptor */
    for(pf = 0; pf < maxpf; pf++) {
        DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	/* the bReserved field of the PIXELFORMATDESCRIPTOR contains the
	   number of overlay/underlay planes */
	if (pfd.bReserved > 0) {
	  /* aha! This format has overlays/underlays */
	  wglDescribeLayerPlane(hDC, pf, 1,
				sizeof(LAYERPLANEDESCRIPTOR), &lpd);
	  if (lpd.dwFlags & LPD_SUPPORT_OPENGL &&
	      lpd.dwFlags & flags)
	    {
	      
	      goto found;
	    }
	}
    }
    /* couldn't find any overlay/underlay planes */
    return SETPIXELFORMATOVERLAY_NO_OVERLAYS;

found:
    /* now get the "normal" pixel format descriptor for the layer */
    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    /* set the pixel format */
    if(SetPixelFormat(hDC, pf, &pfd) == FALSE) {
        return SETPIXELFORMATOVERLAY_FORMAT_FAILED;
    }
    
    /* set up the layer palette */
#if 0
    fprintf(stderr, "setPixelFormatOverlay: Number of overlay plane color bits: %d\n", pfd.cColorBits);
#endif

    ne = wglSetLayerPaletteEntries(hDC, 1, 0, nEntries, crEntries);
    if (ne<nEntries){
      return SETPIXELFORMATOVERLAY_PALETTE_FAILED;
    }

    /* realize the palette */
    wglRealizeLayerPalette(hDC, 1, TRUE);

    return pf;
}    


int forcePixelFormat(HDC hDC, int pf, int nEntries, COLORREF *crEntries)
{
   PIXELFORMATDESCRIPTOR pfd;
   LAYERPLANEDESCRIPTOR  lpd;		/* layer plane descriptor */
   
   
   DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
   
   if (pfd.bReserved > 0) {
	  /* aha! This format has overlays/underlays */
	  wglDescribeLayerPlane(hDC, pf, 1,
				sizeof(LAYERPLANEDESCRIPTOR), &lpd);
	  if (lpd.dwFlags & LPD_SUPPORT_OPENGL)
	    {
	       DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    	       /*printPixelFormat(&pfd);*/
    	       SetPixelFormat(hDC, pf, &pfd);
    	       wglSetLayerPaletteEntries(hDC, 1, 0, nEntries, crEntries);
    	       wglRealizeLayerPalette(hDC, 1, TRUE);
    	       return OVERLAY;
	    }
   }
   
   
   
   DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
   /*printPixelFormat(&pfd);*/
   SetPixelFormat(hDC, pf, &pfd);
   return NORMAL;
}


int setPixelFormatOverlay(HDC hDC, BYTE type, DWORD flags, int nEntries, COLORREF *crEntries)
{
    int pf, maxpf, ne;
    PIXELFORMATDESCRIPTOR pfd;
    LAYERPLANEDESCRIPTOR  lpd;		/* layer plane descriptor */
    int status = 0;
    int bestoverlay = 0;
    int bestnormal = 0;
    
    /* get the maximum number of pixel formats */
    maxpf = DescribePixelFormat(hDC, 0, 0, NULL);
    
    
    /* find an overlay layer descriptor */
    for(pf = 1; pf <= maxpf; pf++) {
        DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
        status = checkPixelFormat(hDC, pf, &pfd);
        switch (status) {
          case OVERLAY:
             bestoverlay = pf;
             goto found;
          case NORMAL:
             if(bestnormal == 0) {
                bestnormal = pf;
             }
             break;
        };
    }

found:
    if (bestoverlay != 0) {
    	DescribePixelFormat(hDC, bestoverlay, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    	/*printPixelFormat(&pfd);*/
    	SetPixelFormat(hDC, bestoverlay, &pfd);
    	ne = wglSetLayerPaletteEntries(hDC, 1, 0, nEntries, crEntries);
    	wglRealizeLayerPalette(hDC, 1, TRUE);
    	return OVERLAY;
    }
    if (bestnormal != 0) {
    	DescribePixelFormat(hDC, bestnormal, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    	/*printPixelFormat(&pfd);*/
    	SetPixelFormat(hDC, bestnormal, &pfd);
    	return NORMAL;
    }
    
    return -1;
    
}



#endif /* nti */
/*----------WRAPPERS------------*/
/* wrap double to float */

wrapglClearIndex(double c)
{
  glClearIndex((float)c);
}

wrapglClearColor(double r, double g, double b, double a)
{
  glClearColor((float)r, (float)g, (float)b, (float)a);
}

wrapglColor4f(double r, double g, double b, double a)
{
  glColor4f((float)r, (float)g, (float)b, (float)a);
}

wrapglPointSize(double size)
{
  glPointSize((float)size);
}

wrapglLineWidth(double width)
{
  glLineWidth((float)width);
}

wrapglPolygonOffset(double factor,double units)
{
  glPolygonOffset((float)factor,(float)units);
}

wrapglAccum(int op,double value)
{
  glAccum(op,(float)value);
}

wrapglTexCoord1f(double s)
{
  glTexCoord1f((float)s);
}

wrapglLightf(int light,int pname,double param)
{
  glLightf(light,pname,(float)param);
}

wrapglLightfv(int light,int pname,int param)
{
  float fparam[4];
  double* dparam;
  dparam=(double*)param;
  fparam[0]=(float)dparam[0];
  fparam[1]=(float)dparam[1];
  fparam[2]=(float)dparam[2];
  fparam[3]=(float)dparam[3];

  glLightfv(light,pname,fparam);
}

wrapglLightModelfv(int light,int param)
{
  float fparam[3];
  double* dparam;
  dparam=(double*)param;
  fparam[0]=(float)dparam[0];
  fparam[1]=(float)dparam[1];
  fparam[2]=(float)dparam[2];

  glLightModelfv(light,fparam);
}

wrapglLightModelf(int pname,double param)
{
  glLightModelf(pname,(float)param);
}

wrapglMaterialf(int face,int pname,double param)
{
  glMaterialf(face,pname,(float)param);
}

wrapglMaterialfv(int face,int pname,int param)
{
  float fparam[4];
  double* dparam;
  dparam=(double*)param;
  fparam[0]=(float)dparam[0];
  fparam[1]=(float)dparam[1];
  fparam[2]=(float)dparam[2];
  fparam[3]=(float)dparam[3];

  glMaterialfv(face,pname,fparam);
}

wrapglPixelZoom(double xf,double yf)
{
  glPixelZoom((float)xf,(float)yf);
}

wrapglPixelStoref(int pname,double param)
{
  glPixelStoref(pname,(float)param);
}

wrapglPixelTransferf(int pname,double param)
{
  glPixelTransferf(pname,(float)param);
}

wrapglTexEnvf(int target,int pname,double param)
{
  glTexEnvf(target,pname,(float)param);
}

wrapglTexParameterf(int target,int pname,double param)
{
  glTexParameterf(target,pname,(float)param);
}

wrapglFogf(int pname,double param)
{
  glFogf(pname,(float)param);
}

wrapglPassThrough(double token)
{
  glPassThrough((float)token);
}

/* these aren't supported at all platforms. 

wrapglPolygonOffsetEXT(double factor,double bias)
{
  glPolygonOffsetEXT((float)factor,(float)bias);
}

wrapglPointParameterfEXT(int pname,double param)
{
  glPointParameterfEXT(pname,(float)param);
}
*/


/* GLU-routines */

void wrapgluNurbsProperty(int qobj,int property,double value)
{
  gluNurbsProperty((void*)qobj,property,(float)value);
}


