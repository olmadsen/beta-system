#define Kb                1024
#define Mb             Kb * Kb

/* Heap is the structure of IOA and ToSpace heaps */

typedef struct Heap {
  long *start;
  long topoff; 
  long *limit;
  unsigned long size;
} Heap;

#ifdef NEWRUN
#define IOA           _IOA.start
#define IOALimit      _IOA.limit
#define IOASize       _IOA.size
#define IOATopOff     _IOA.topoff
#define IOATop        ((long *) ((long)IOA+IOATopOff))
#endif /* NEWRUN */

#ifdef sparc
#define IOATop        ((long *) ((long)IOA+IOATopOff))
#endif

#ifdef mac68k

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

#else /* mac68k */

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

#endif /* mac68k */


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
