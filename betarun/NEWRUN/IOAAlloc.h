
/* Allocation in IOA heap */

INLINE void *IOAalloc(unsigned size, long *SP)
{
  register char *p;
  
  /*fprintf(output, "IOAalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAalloc: (IOATop&7)==0"));
  
  while ((char *)IOATop+size > (char *)IOALimit) {
    doGC(SP, GetThis(SP), size / 4);
  }
  
  p = (char *)IOATop;
  IOATopOff += size;
 
  return p;
}

INLINE void *IOAcalloc(unsigned size, long *SP)
{
  register char *p;
  
  /*fprintf(output, "IOACalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOACalloc: size>0"));
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAcalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAcalloc: (IOATop&7)==0"));
  
  while ((char *) IOATop+size > (char *)IOALimit) {
    doGC(SP, GetThis(SP), size / 4);
  }
  
  p = (char *)IOATop;
  IOATopOff += size;
  
  long_clear(p, size);
  DEBUG_CODE(zero_check(p, size));
  
  return p;
}
