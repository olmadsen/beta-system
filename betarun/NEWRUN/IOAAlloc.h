
/* Allocation in IOA heap */
/* GC/PerformGC.c: Not declared in function.h, doGC should only be 
 * called from IOA(c)lloc or DoGC.
 */
#ifndef NEWRUN
extern void doGC();
#endif

INLINE void AssignReference(long *theCell, struct Item *newObject)
{
  *(struct Item **)theCell = newObject;

  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert((struct Object **)theCell);
}

INLINE void long_clear(char *p, unsigned bytesize)
{
  register long i;
#ifdef RTDEBUG
  if (bytesize&3)
    fprintf(stderr, "What! bytesize&3 != 0\n");
#endif
  for (i = bytesize-4; i >= 0; i -= 4)
    *(long *)(p+i) = 0;	/* Ugly Hacks Work Fast */
}

INLINE void zero_check(char *p, unsigned bytesize)
{
  register long i;
#ifdef RTDEBUG
  if (bytesize&3)
    fprintf(output, "What! bytesize&3 != 0\n");
#endif
  for (i = bytesize-4; i >= 0; i -= 4)
    if (*(long *)(p+i) != 0) fprintf(output, "zero_check failed\n");	
}

INLINE void *IOAalloc(unsigned size, long *SP)
{
  register char *p;
  
  /*fprintf(output, "IOAalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOAalloc: size>0"));
#if (defined(sparc) || defined(hppa) || defined(crts))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAalloc: (IOATop&7)==0"));
#endif
  
  while ((char *)IOATop+size > (char *)IOALimit) {
    doGC(SP, GetThis(SP), size / 4);
  }
  
  p = (char *)IOATop;
#ifdef hppa
  /* setIOATopoffReg(getIOATopoffReg() + size); */
  IOATop = (long*)((long)IOATop+size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef NEWRUN
  IOATopOff += size;
#endif
#if defined(crts) 
  IOATop = (long*)((long)IOATop+size);
#endif
  
  return p;
}

INLINE void *IOAcalloc(unsigned size, long *SP)
{
  register char *p;
  
  /*fprintf(output, "IOACalloc: IOATop=0x%x, size=0x%x\n", IOATop, size);*/
  
  DEBUG_CODE(Claim(size>0, "IOACalloc: size>0"));
#if (defined(sparc) || defined(hppa) || defined(crts))
  DEBUG_CODE(Claim( ((long)size&7)==0 , "IOAcalloc: (size&7)==0"));
  DEBUG_CODE(Claim( ((long)IOATop&7)==0 , "IOAcalloc: (IOATop&7)==0"));
#endif
  
  while ((char *) IOATop+size > (char *)IOALimit) {
    doGC(SP, GetThis(SP), size / 4);
  }
  
  p = (char *)IOATop;
#ifdef hppa
  /*setIOATopoffReg(getIOATopoffReg() + size);*/
  IOATop = (long*)((long)IOATop+size);
#endif
#ifdef sparc
  IOATopoff += size;
#endif
#ifdef NEWRUN
  IOATopOff += size;
#endif
#if defined(crts)
  IOATop = (long*)((long)IOATop+size);
#endif
  
  long_clear(p, size);
#ifdef RTDEBUG
  zero_check(p, size);
#endif
  
  return p;
}


INLINE void setup_item(struct Item *theItem,
		       struct ProtoType *prototype,
		       struct Object *origin
		       )
{
    register struct GCEntry *initTab;
  
    theItem->Proto = prototype;
    theItem->GCAttr = 1; /* Set item age to 1 */

    /* Initialize the body part of the item, according to the genTable. */

    initTab = (struct GCEntry *)((char *)prototype + prototype->GCTabOff);

    /* initTab is now pointing to the static GCTable.
     * This table has zero or more elements terminated with a zero word.
     * Each element looks like:
     *   WORD  Offset in the generated object, where this static object begins.
     *   WORD  Signed distance to inclosing object.
     *   LONG  ProtoType of this static object.
     */

    for (; initTab->StaticOff; ++initTab) {
	register struct PartObject *po;
	
	po = (struct PartObject *)((long *)theItem + initTab->StaticOff);
	po->Proto = initTab->Proto;
	po->OrigOff = initTab->OrigOff;

	/*
	if ( (long)po->Proto == -1)
	  printf("\nsetup_item: component: 0x%08x\n", po);
        */
    }

  ((long *)theItem)[prototype->OriginOff] = (long) origin;
}
