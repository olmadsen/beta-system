#define Kb                1024
#define Mb             (Kb * Kb)

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

/* Sparc Heap:
 *    
 *    IOA:
 *       .
 *       IOA+IOATopoff: First available byte
 *       .
 *    IOALimit: First not available byte
 */

#ifndef MT
#define IOATop        ((long *) ((long)IOA+IOATopOff))
#endif
#endif

#ifndef DEFAULT_IOASIZE
#define DEFAULT_IOASIZE  64 * Kb
#endif

#ifndef DEFAULT_AOAMINFREE
#ifdef PERSIST
#define DEFAULT_AOAMINFREE     4096 * Kb
#else
#define DEFAULT_AOAMINFREE     1024 * Kb
#endif /* PERSIST */
#endif

#ifndef DEFAULT_CBFASIZE
#define DEFAULT_CBFASIZE   1 * Kb
#endif

#ifndef DEFAULT_IOAPERCENTAGE
#define DEFAULT_IOAPERCENTAGE  10
#endif

#ifndef DEFAULT_AOAPERCENTAGE
#define DEFAULT_AOAPERCENTAGE  10
#endif

#ifndef AOAINCREMENT
#define AOAINCREMENT  10
#endif

