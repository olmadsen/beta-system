
/* Allocation in IOA heap */
/* NOTICE: doGC should only be called from IOAlloc or DoGC.
 */
 
#ifdef __GNUC__
static __inline__
#endif
char *IOAalloc(unsigned size)
{
  register char *p;
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)GLOBAL_IOATop&7)==0 , "IOAalloc: (GLOBAL_IOATop&7)==0"));
  
#ifdef MT
  /* Manipulate thread specific IOA */
  if ((do_unconditional_gc && (DoUGC)) || ((char *)IOATop+size > (char *)IOALimit)){
    return (char *)doGC(size);
  }
  p = (char *)IOATop;
  IOATop = (long*)((long)IOATop + size);
  DEBUG_CODE(zero_check(p, size));
  return p;
#else /* MT */

  if (do_unconditional_gc && (DoUGC) && ActiveComponent /* don't do this before AttBC */){
    ReqObjectSize = size / 4;
    doGC();
  }
  while ((char *)GLOBAL_IOATop+size > (char *)GLOBAL_IOALimit) {
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

#ifdef __GNUC__
static __inline__
#endif
char *IOAallocToSP(unsigned size, long *SP, pc_t PC)
{
  register char *p;
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)GLOBAL_IOATop&7)==0 , "IOAalloc: (GLOBAL_IOATop&7)==0"));
  
#ifdef MT
  /* Manipulate thread specific IOA */
  if ((do_unconditional_gc && (DoUGC)) || ((char *)IOATop+size > (char *)IOALimit)){
    return (char *)doGCtoSP(size, SP, PC);
  }
  p = (char *)IOATop;
  IOATop = (long*)((long)IOATop + size);
  DEBUG_CODE(zero_check(p, size));
  return p;
#else /* MT */

  if (do_unconditional_gc && (DoUGC) && ActiveComponent /* don't do this before AttBC */){
    ReqObjectSize = size / 4;
    doGCtoSP(SP, PC);
  }
  while ((char *)GLOBAL_IOATop+size > (char *)GLOBAL_IOALimit) {
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

#ifdef __GNUC__
static __inline__
#endif
char *IOATryAlloc(unsigned size)
{
  register char *p = NULL;
  
  DEBUG_CODE(Claim(size>0, "IOATryAlloc: size>0"));
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOATryAlloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)GLOBAL_IOATop&7)==0 , "IOATryAlloc: (GLOBAL_IOATop&7)==0"));
  
  if (do_unconditional_gc && (DoUGC) && ActiveComponent /* don't do this before AttBC */){
    ReqObjectSize = size / 4;
    doGC();
  }
  if ((char *)GLOBAL_IOATop+size > (char *)GLOBAL_IOALimit) {
    ReqObjectSize = size / 4;
    doGC();
  } 

  if ((char *)GLOBAL_IOATop+size <= (char *)GLOBAL_IOALimit) {
    p = (char *)GLOBAL_IOATop;
#ifdef hppa
    GLOBAL_IOATop = (long*)((long)GLOBAL_IOATop+size);
#endif
#ifdef sparc
    IOATopOff += size;
#endif
    DEBUG_CODE(zero_check(p, size));
  }

  return p;
}
