#ifdef sun4
#define MOTIF12
#endif

#ifdef sun4s
#define MOTIF12
#endif

#ifdef hpux9pa
#define MOTIF12
#endif

#ifdef linux
#define MOTIF12
#endif

#include <sys/time.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Xm/Text.h>
#include <Xm/TextP.h>
#include <Xm/Protocols.h>

#include "black.c"
#include "white.c"
#include "gray.c"
#include "light_gray.c"
#include "dark_gray.c"



#ifdef MOTIF12
#include <Xm/TextStrSoP.h>
#include <Xm/ManagerP.h>
#else
#include <Xm/TextSrcP.h>
#endif

long startsecs;

void inittickcount (void) {
  struct timeval tv;
  struct timezone tz;
  int ignore;
  ignore = gettimeofday(&tv,&tz);
  startsecs = tv.tv_sec;
}

long tickcount (void) {
  struct timeval tv;
  struct timezone tz;
  long t;
  int ignore;
  ignore = gettimeofday(&tv,&tz);
  t = tv.tv_sec - startsecs;
  t = t * 1000000;
  t = t + tv.tv_usec;
  t = t * 60;
  t = t/1000000;
  return t;
}

void getfontinfo (XFontStruct *font,long *ascent,long *descent) {
  *ascent = font->ascent;
  *descent = font->descent;
}

long getcharinfo (XFontStruct *font) {
  return (font->max_bounds.rbearing - font->min_bounds.lbearing);
}

long gettextwidth (void *buffer,long nchars,XFontStruct *font) {
  int dir;
  int ascent,descent;
  XCharStruct overall;
  XTextExtents(font,buffer,nchars,&dir,&ascent,&descent,&overall);
  return (font->max_bounds.lbearing + overall.width);
}



Boolean getselection (XmTextWidget w,XmTextPosition *left,XmTextPosition *right) {
  XmTextSource source;
  
  Boolean result;
  
  source = w->text.source;
  result = source->GetSelection (source,left,right);
  return result;
}


Pixmap getwhite(Display *display,Drawable root)
{
  return XCreateBitmapFromData(display,root,white_bits,white_width,white_height);
}

Pixmap getgray(Display *display,Drawable root)
{
  return XCreateBitmapFromData(display,root,gray_bits,gray_width,gray_height);
}

Pixmap getlightgray(Display *display,Drawable root)
{
  return XCreateBitmapFromData(display,root,light_gray_bits,light_gray_width,light_gray_height);
}

Pixmap getdarkgray(Display *display,Drawable root)
{
  return XCreateBitmapFromData(display,root,flipped_gray_bits,flipped_gray_width,flipped_gray_height);
}

Pixmap getblack(Display *display,Drawable root)
{
  return XCreateBitmapFromData(display,root,black_bits,black_width,black_height);
}

GC GetTopShadowGC(XmManagerWidget w)
{
  return w->manager.top_shadow_GC;
}

GC GetBottomShadowGC(XmManagerWidget w)
{
  return w->manager.bottom_shadow_GC;
}

void SetWindowDeleteAction (Widget shell, XtCallbackProc callback)
{
  Atom WM_DELETE_WINDOW;
  
  WM_DELETE_WINDOW = XInternAtom(XtDisplay(shell), "WM_DELETE_WINDOW", False);
  XmAddWMProtocolCallback(shell, WM_DELETE_WINDOW, callback, 0);
}
