#define Kb                1024
#define Mb             Kb * Kb

/* Heap is the structure of IOA and ToSpace heaps */

typedef struct Heap {
  long *start;
  long topoff; 
  long *limit;
  unsigned long size;
} Heap;

#ifdef macintosh

#ifndef DEFAULT_IOASIZE
#define DEFAULT_IOASIZE  200 * Kb
#endif

#ifndef DEFAULT_AOASIZE
#define DEFAULT_AOASIZE  200 * Kb
#endif

#ifndef DEFAULT_LVRASIZE
#define DEFAULT_LVRASIZE 200 * Kb
#endif

#ifndef DEFAULT_AOAMINFREE
#define DEFAULT_AOAMINFREE     50 * Kb  
#endif

#ifndef DEFAULT_LVRAMINFREE
#define DEFAULT_LVRAMINFREE    50 * Kb 
#endif

#else /* macintosh */

#ifndef DEFAULT_IOASIZE
#define DEFAULT_IOASIZE  512 * Kb
#endif

#ifndef DEFAULT_AOASIZE
#define DEFAULT_AOASIZE  512 * Kb
#endif

#ifndef DEFAULT_LVRASIZE
#define DEFAULT_LVRASIZE 512 * Kb
#endif

#ifndef DEFAULT_AOAMINFREE
#define DEFAULT_AOAMINFREE     100 * Kb   /* Less on Macintosh? */
#endif

#ifndef DEFAULT_LVRAMINFREE
#define DEFAULT_LVRAMINFREE    200 * Kb   /* Less on Macintosh? */
#endif

#endif /* macintosh */


#ifndef DEFAULT_CBFASIZE
#define DEFAULT_CBFASIZE   1 * Kb
#endif

#ifndef DEFAULT_IOAPERCENTAGE
#define DEFAULT_IOAPERCENTAGE  10
#endif

#ifndef DEFAULT_AOAPERCENTAGE
#define DEFAULT_AOAPERCENTAGE  0
#endif

#ifndef DEFAULT_LVRAPERCENTAGE
#define DEFAULT_LVRAPERCENTAGE 0
#endif
