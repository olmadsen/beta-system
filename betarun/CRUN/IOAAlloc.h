
/* Allocation in IOA heap */
/* GC/PerformGC.c: Not declared in function.h, doGC should only be 
 * called from IOA(c)lloc or DoGC.
 */
#ifdef MT
extern struct Object *doGC(unsigned long);
#else
extern void doGC();
#endif

 
#ifdef __GNUC__
static __inline__
#endif
char *IOAalloc(unsigned size)
{
  register char *p;
  
  /*GCable_Entry();*/
  
  /*fprintf(output, "IOAalloc: IOATop=0x%x, size=0x%x\n", GLOBAL_IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
#if (defined(sparc) || defined(hppa))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)GLOBAL_IOATop&7)==0 , "IOAalloc: (GLOBAL_IOATop&7)==0"));
#endif
  
#ifdef MT
  /* Manipulate thread specific IOA */
  if ((char *)IOATop+size >= (char *)IOALimit){
    return (char *)doGC(size);
  }
  p = (char *)IOATop;
  IOATop = (long*)((long)IOATop + size);
  DEBUG_CODE(zero_check(p, size));
  return p;
#else /* MT */

  while ((char *)GLOBAL_IOATop+size >= (char *)GLOBAL_IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  } 

  p = (char *)GLOBAL_IOATop;
#ifdef hppa
  GLOBAL_IOATop = (long*)((long)GLOBAL_IOATop+size);
#endif
#ifdef sparc
  IOATopOff += size;
#endif

  DEBUG_CODE(zero_check(p, size));

  return p;
#endif /* MT */
}

