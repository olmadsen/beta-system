#include <X11/Xlib.h>
#include "stripes1.x11"
#include "stripes2.x11"
#include "stripes3.x11"
#include "stripes4.x11"
#include "stripes5.x11"
#include "stripes6.x11"
#include "stripes7.x11"
#include "stripes8.x11"

Pixmap getStripes1(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes1_bits,stripes1_width,stripes1_height);
}

Pixmap getStripes2(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes2_bits,stripes2_width,stripes2_height);
}

Pixmap getStripes3(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes3_bits,stripes3_width,stripes3_height);
}

Pixmap getStripes4(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes4_bits,stripes4_width,stripes4_height);
}

Pixmap getStripes5(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes5_bits,stripes5_width,stripes5_height);
}

Pixmap getStripes6(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes6_bits,stripes6_width,stripes6_height);
}

Pixmap getStripes7(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes7_bits,stripes7_width,stripes7_height);
}

Pixmap getStripes8(Display *display)
{
  return XCreateBitmapFromData(display,DefaultRootWindow(display),
			       stripes8_bits,stripes8_width,stripes8_height);
}
