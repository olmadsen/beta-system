
/* Allocation in IOA heap */
/* GC/PerformGC.c: Not declared in function.h, doGC should only be 
 * called from IOA(c)lloc or DoGC.
 */
#ifdef MT
extern struct Object *doGC(unsigned);
#else
extern void doGC();
#endif

 
#ifdef __GNUC__
static inline 
#endif
char *IOAalloc(unsigned size)
{
  register char *p;
  
  /*GCable_Entry();*/
  
  /*fprintf(output, "IOAalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
#if (defined(sparc) || defined(hppa) || defined(crts))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAalloc: (IOATop&7)==0"));
#endif
  
#ifdef MT
  if ((char *)IOATop+size > (char *)IOALimit){
    return (char *)doGC(size);
  }
#else /* MT */
  while ((char *)IOATop+size > (char *)IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  } 
#endif /* MT */
 
  p = (char *)IOATop;
#ifdef hppa
  /* setIOATopoffReg(getIOATopoffReg() + size); */
  IOATop = (long*)((long)IOATop+size);
#endif
#ifdef sparc
  IOATopOff += size;
#endif
#ifdef crts
  IOATop = (long*)((long)IOATop+size);
#endif
  return p;
}


#ifdef __GNUC__
static inline 
#endif
char *IOAcalloc(unsigned size)
{
  register char *p;
  
  /*GCable_Entry();*/
  
  /*fprintf(output, "IOACalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOACalloc: size>0"));
#if (defined(sparc) || defined(hppa) || defined(crts))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAcalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAcalloc: (IOATop&7)==0"));
#endif
  
#ifdef MT
  if ((char *)IOATop+size > (char *)IOALimit){
    return (char *)doGC(size);
  }
#else /* MT */
  while ((char *)IOATop+size > (char *)IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  } 
#endif /* MT */
  
  p = (char *)IOATop;
#ifdef hppa
  /*setIOATopoffReg(getIOATopoffReg() + size);*/
  IOATop = (long*)((long)IOATop+size);
#endif
#ifdef sparc
  IOATopOff += size;
#endif
#ifdef crts
  IOATop = (long*)((long)IOATop+size);
#endif
  
#ifndef MT
  /* Not needed anymore since IOA is cleared after IOAGc.
   * YES still needed. The memset solution turned out to
   * be slower or at best marginally faster than using 
   * long_clear.
   */
  long_clear(p, size);
#endif

#ifdef RTDEBUG
  zero_check(p, size);
#endif
  
  return p;
}
