/* This i part of a opengl interface for beta 
   Flemming Gram, gram@mjolner.dk 
   */

extern long glwMDrawingAreaWidgetClass;

/*-----C-function definitions -----*/
void glClearIndex( float c );
void glClearColor(float red,float green,float blue,float alpha);
void glPointSize(float size);
void glLineWidth(float width );
void glPolygonOffset(float,float);
void glClearAccum( float red, float green, float blue,float alpha );
void glAccum( int op, float value );
void glFrumstum(double left,double right,double bottom,double top,double near,double far);
void glVertex4d(double,double,double,double); 
void glColor4d(double,double,double,double);
void glTexCoord1f(float);
void glTexCoord4d(double,double,double,double);
void glRasterPos4d(double,double,double,double);
void glRectd(double,double,double,double);
void glLightf(int,int,float);
void glLightfv(int,int,float*);
void glLightModelf(int,float);
void glLightModelfv(int,float*);
void glMaterialf(int face,int pname, float param );
void glMaterialfv(int,int,float*);
void glPixelZoom(float,float);
void glPixelStoref(int,float);
void glBitmap(int,int,float,float,float,float,int);
void glTexEnvf(int,int,float);
void glTexParameterf(int,int,float);
void glMap2d( int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, int points );
void glMapGrid2d(int,double,double,int,double,double);
void glFogf(int,float);
void glPassThrough(float);
void glBlendColorEXT(float,float,float,float);
void glPolygonOffsetEXT(float,float);
/*void glPointParameterfEXT(int,float);*/

/*----------HELPERS-------------*/
long openGLWidgetClass(void) 
{
  return glwMDrawingAreaWidgetClass;
}


/*----------WRAPPERS------------*/
/*mostly wrap double to float, and double limits (3) */

double wrapleft,wrapright,wrapbottom;
double wrapangle,wrapx,wrapy;
double wrapred,wrapgreen;
double first,second,third;

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

wrapglOrthosecond(double top,double near,double far)
{
  glOrtho(wrapleft,wrapright,wrapbottom,top,near,far);
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

wrapglFrustumsecond(double top,double near,double far)
{
  glFrustum(wrapleft,wrapright,wrapbottom,top,near,far);
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
  glBitmap(width,height,first,second,third,ymove,bitmap);
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
  glMap2d(target,first,second,ustride,uorder,third,v2,vstride,vorder,points);
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

wrapglBlendColorEXT(double alpha)
{
  glBlendColorEXT((float)first,(float)second,(float)third,(float)alpha);
}

/* these aren't supported on sun 
wrapglPolygonOffsetEXT(double factor,double bias)
{
  glPolygonOffsetEXT((float)factor,(float)bias);
}

wrapglPointParameterfEXT(int pname,double param)
{
  glPointParameterfEXT(pname,(float)param);
}
*/
