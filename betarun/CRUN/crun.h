/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#ifndef _CRUN_H_
#define _CRUN_H_

#ifndef hppa
extern struct Component* CAlloC();
extern struct Item    * CAlloI();
#endif
extern ref(ValRep) 	AlloVR();
extern ref(ValRep)      LVRACAlloc();
extern ref(ValRep)      LVRAAlloc();
extern ref(RefRep)	AlloRR();
extern ref(StackObject) AlloSO() asm("AlloSO");
extern void		CopyT() asm("CopyT");
extern void		CopySRR() asm("CopySRR");
extern void		CopySVR() asm("CopySVR");
extern ref(Structure)	AlloS() asm("AlloS");
extern ref(Structure)	ThisS() asm("ThisS");
extern void		DoGC() asm("DoGC");
extern ref(Item)	AlloSI() asm("AlloSI");
extern ref(Component)	AlloSC() asm("AlloSC");
extern void             Return() asm ("Return");
extern void             RefNone() asm("RefNone");
extern void             AttBC() asm("AttBC");
extern void             CopyRR() asm("CopyRR");
extern void             CopyVR() asm("CopyVR");
extern void             BetaError();
extern void             ChkRA() asm("ChkRA");
extern ref(Component)   Susp() asm("Susp");
extern char	      * IOAalloc();
extern char	      * IOAcalloc();

static inline void
AssignReference(long *theCell, ref(Item) newObject)
{
  *(struct Item **)theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(theCell);
}

static inline
long_clear(char *p, unsigned bytesize)
{
  register long i;
#ifdef RTDEBUG
  if (bytesize&3)
    fprintf(stderr, "What! bytesize&3 != 0\n");
#endif
  for (i = bytesize-4; i >= 0; i -= 4)
    *(long *)(p+i) = 0;	/* Ugly Hacks Work Fast */
}

static inline void
setup_item(ref(Item) theItem,
	   ref(ProtoType) prototype,
	   ref(Object) origin
	   )
{
    register ref(GCEntry) initTab;
  
    theItem->Proto = prototype;
    theItem->GCAttr = 1; /* Set item age to 1 */

    /* Initialize the body part of the item, according to the genTable. */

    initTab = cast(GCEntry) ((char *)prototype + prototype->GCTabOff);

    /* initTab is now pointing to the static GCTable.
     * This table has zero or more elements terminated with a zero word.
     * Each element looks like:
     *   WORD  Offset in the generated object, where this static object begins.
     *   WORD  Signed distance to inclosing object.
     *   LONG  ProtoType of this static object.
     */

    for (; initTab->StaticOff; ++initTab) {
	register ref(PartObject) po;
	
	po = cast(PartObject) ((long *)theItem + initTab->StaticOff);
	po->Proto = initTab->Proto;
	po->OrigOff = initTab->OrigOff;
    }

  ((long *)theItem)[prototype->OriginOff] = (long) origin;
}

#ifdef RTDEBUG
  /* Consistency checks - Checks for valid references */
# ifdef hppa
  static char __CkString[80];
#  define Ck(r) \
   { sprintf(__CkString, "%s: %d: Ck failed: %s (0x%x)", __FILE__, __LINE__, #r, r); \
     if(r) Claim(inIOA(r) || inAOA(r) || inLVRA(r) || isLazyRef(r), __CkString); }
# else
/*#  define Ck(r) \
 *  if(r) Claim(inIOA(r) || inAOA(r) || inLVRA(r), __FILE__":" #r ": none or inside IOA, AOA, or LVRA")
 */
extern void CCk(ref(Object) r); /* Easier to debug a function call - PA */
#define Ck(r) CCk(cast(Object)r)
# endif
#else
#define Ck(r)
#endif

#endif
