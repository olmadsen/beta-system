#include <Carbon/Carbon.h>


void CGContextSelectFontGlue (
   CGContextRef context,
   const char * name,
   double size,
   CGTextEncoding textEncoding
   ) 
{
  CGContextSelectFont(context, name, (float) size, textEncoding);
}


void CGContextShowTextAtPointGlue (
   CGContextRef context,
   double x,
   double y,
   const char * bytes,
   size_t length
   )
{
  CGContextShowTextAtPoint(context, (float) x, (float) y, bytes, length);
}
