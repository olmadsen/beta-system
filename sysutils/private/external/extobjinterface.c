/* 
 * assignRef
 * =========
 * Assign a reference taking care of updating the gc tables. 
 */


#ifdef sparc
  register long *IOA asm("%g6");
  register unsigned IOATopoff asm("%g7");
# define IOATop ((long *) ((char *)IOA+IOATopoff))

#else /* sparc */

#ifdef sgi

extern struct Heap {
  long *start;
  long topoff; 
  long *limit;
  unsigned long size;
} _IOA;

#define IOA         _IOA.start
#define IOATopOff   _IOA.topoff
#define IOATop      ((long *) ((long)IOA+IOATopOff))

#else /* sgi */
  /* neither sparc nor sgi */
  extern long *IOA;
  extern long *IOATop;

#endif /* sgi */

#endif /* sparc */

#define inIOA(x) (((long) IOA <= (long) x) && ((long) x < (long) IOATop))

extern void AOAtoIOAInsert(long *cell);

void assignRef(long *theCell, long *newObject)
{
  *(long **) theCell = newObject;

  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(theCell);
}


/* 
 * extGetCstring
 * =============   */

char* extGetCstring (char *s)
{ return s; }
