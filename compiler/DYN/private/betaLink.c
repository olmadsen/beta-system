#include <stdio.h>
#include <stdlib.h>

#if defined(MAC)
#  define MALLOC(size) NewPtr(size)
#  define REALLOC(src,size) 0
#  define FREE(ptr) DisposPtr((Ptr)ptr)
#else
#  define FREE(ptr) free(ptr)
#  define REALLOC(src,size) realloc(src,size)
#  if defined(sparc) || defined(sgi) || defined(hppa)
     /* 64 bit alignment because of the reals */
#    define MALLOC(size) memalign(8, (size))
#  else
#    define MALLOC(size) malloc(size)
#  endif
#endif

void * allocateImage(long numbytes)
{ 
  return MALLOC(numbytes);
}
long * loadObject(long *bufAdr, long numbytes)
{ 
  long * start; 
  int i;

  start = (long *)MALLOC(numbytes);
  if (!start) printf("Alloc failure in loadObject\n");
  for (i=0; i < (numbytes / 4); i++) 
    start[i] = bufAdr[i];
  return start;
}
