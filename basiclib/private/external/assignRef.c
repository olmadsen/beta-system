/* assignRef.c
 *
 * Assign a reference taking care of updating the gc tables.
 *
 */


#if !(defined(sparc) || defined(hppa))
  extern long *IOA;
  extern long *IOATop;
# define inIOA(x) (((long) IOA <= (long) x) && ((long) x < (long) IOATop))
#endif

#ifdef sparc
  register long *IOA asm("%g6");
  register unsigned IOATopoff asm("%g7");
# define IOATop ((long *) ((char *)IOA+IOATopoff))
# define inIOA(x) (((long) IOA <= (long) x) && ((long) x < (long) IOATop))
#endif

#ifdef hppa
register int _dummy4 asm("%r17"); /* really IOAbot */
register int _dummy5 asm("%r18"); /* really IOAsize */

static inline long *getIOAReg()
{     
  long *res; 
  asm volatile ("COPY\t%%r17, %0" : "=r" (res)); 
  return res;
}

static inline unsigned getIOATopoffReg()
{     
  unsigned res; 
  asm volatile ("COPY\t%%r18, %0" : "=r" (res)); 
  return res;
}

# define inIOA(x) (((unsigned) x - (unsigned) getIOAReg()) < (unsigned) getIOATopoffReg())
#endif

extern void AOAtoIOAInsert(long *cell);

void assignRef(long *theCell, long *newObject)
{
  *(long **) theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(theCell);
}
