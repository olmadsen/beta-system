/* This i part of a opengl interface for beta 
   Flemming Gram, gram@mjolner.dk 
   */

#ifndef nti
extern long glwMDrawingAreaWidgetClass;
#endif

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
#ifndef nti
long openGLWidgetClass(void) 
{
  return glwMDrawingAreaWidgetClass;
}
#endif

#ifdef nti
int setPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR* ppfd;
	int formatindex;
	PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	24,
	0,0,0,0,0,0,
	0,
	0,
	0,
	0,0,0,0,
	32,
	0,
	0,
	PFD_MAIN_PLANE,
	0,
	0,0,0
	};

	pfd.cColorBits = GetDeviceCaps(hdc,BITSPIXEL);
	printf("colorbits: %d\n",pfd.cColorBits);
	ppfd=&pfd;

    formatindex=ChoosePixelFormat(hdc,ppfd);
	printf("pixelformatindex: %d\n",formatindex);

	if (0==SetPixelFormat(hdc,formatindex,ppfd)) {
		printf("setpixelformat error!\n");
		return 0;
	};
	return 1;
}
#endif
/*----------WRAPPERS------------*/
/*mostly wrap double to float, and double limits (3) */

double wrapleft,wrapright,wrapbottom;
double wrapangle,wrapx,wrapy;
double wrapred,wrapgreen;
double first,second,third;
double wcx,wcy,wcz;

wrapset3double(double one,double two,double three)
{
  first=one;
  second=two;
  third=three;
}

wrapglClearIndex(double index)
{
  glClearIndex((float)index);
}


wrapglClearColorfirst(double red,double green)
{
  wrapred=red;
  wrapgreen=green;
}

wrapglClearColorsecond(double blue,double alpha)
{
  glClearColor((float)wrapred,(float)wrapgreen,(float)blue,(float)alpha);
}

wrapglOrthofirst(double left,double right,double bottom)
{
  wrapleft=left;
  wrapright=right;
  wrapbottom=bottom;
}

wrapglOrthosecond(double top,double near_,double far_)
{
  glOrtho(wrapleft,wrapright,wrapbottom,top,near_,far_);
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
  /*
  glPolygonOffset((float)factor,(float)units);
  */
}


wrapglClearAccumfirst(double red,double green)
{
  wrapred=red;
  wrapgreen=green;
}

wrapglClearAccumsecond(double blue,double alpha)
{
  glClearAccum((float)wrapred,(float)wrapgreen,(float)blue,(float)alpha);
}

wrapglAccum(int op,double value)
{
  glAccum(op,(float)value);
}


wrapglFrustumfirst(double left,double right,double bottom)
{
  wrapleft=left;
  wrapright=right;
  wrapbottom=bottom;
}

wrapglFrustumsecond(double top,double near_,double far_)
{
  glFrustum(wrapleft,wrapright,wrapbottom,top,near_,far_);
}

wrapglRotatedfirst(double angle,double x)
{
  wrapangle=angle;
  wrapx=x;
}

wrapglRotatedsecond(double y,double z)
{
  glRotated(wrapangle,wrapx,y,z);
}


wrapglVertex4d(double w)
{
  glVertex4d(first,second,third,w);
}

wrapglColor4d(double alpha)
{
  glColor4d(first,second,third,alpha);
}

wrapglTexCoord1f(double s)
{
  glTexCoord1f((float)s);
}


wrapglTexCoord4d(double q)
{
  glTexCoord4d(first,second,third,q);
}

wrapglRasterPos4d(double w)
{
  glRasterPos4d(first,second,third,w);
}

wrapglRectd(double y2)
{
  glRectd(first,second,third,y2);
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


wrapglBitmap(int width,int height,double ymove,int bitmap)
{
  glBitmap(width,height,first,second,third,ymove,(char*)bitmap);
}


wrapglTexEnvf(int target,int pname,double param)
{
  glTexEnvf(target,pname,(float)param);
}

wrapglTexParameterf(int target,int pname,double param)
{
  glTexParameterf(target,pname,(float)param);
}

wrapglMap2d(double v2,int target,int ustride,int uorder,int vstride,int vorder,int points)
{
  glMap2d(target,first,second,ustride,uorder,third,v2,vstride,vorder,(double*)points);
}

wrapglMapGrid2d(double v2,int un,int vn)
{
  glMapGrid2d(un,first,second,vn,third,v2);
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
wrapglBlendColorEXT(double alpha)
{
  glBlendColorEXT((float)first,(float)second,(float)third,(float)alpha);
}


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

void wrapgluLookAt1(double cx,double cy,double cz)
{
  wcx=cx;
  wcy=cy;
  wcz=cz;
}

void wrapgluLookAt2(double upx,double upy,double upz)
{
  gluLookAt(first,second,third,wcx,wcy,wcz,upx,upy,upz);
}

void wrapgluOrtho2D(double top)
{
  gluOrtho2D(first,second,third,top);
}

void wrapgluPerspective(double zFar)
{
  gluPerspective(first,second,third,zFar);
}

void wrapgluPickMatrix(double height,int viewport)
{
  gluPickMatrix(first,second,third,height,(int*)viewport);
}


void wrapgluCylinder(int qobj,int slices,int stacks)
{
  gluCylinder((void*)qobj,first,second,third,slices,stacks);
}

void wrapgluPartialDisk(double sweep,int qobj,int slices,int loops)
{
  gluPartialDisk((void*)qobj,first,second,slices,loops,third,sweep);
}

void wrapgluNurbsProperty(int qobj,int property,double value)
{
  gluNurbsProperty((void*)qobj,property,(float)value);
}


