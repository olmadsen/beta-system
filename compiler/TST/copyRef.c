#include <stdio.h>
#include <stdarg.h>

#ifdef nti
# define STDCALL _stdcall
#else
# define STDCALL
#endif


#define test 0

void copyRef(long *source, long *dest)
{
   *dest = *source;
}

