/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */


#ifndef _CRUN_H_
#define _CRUN_H_

extern void             Return();

#ifdef sparc
/* Functions used to call RT routines directly from C.
 * Needed because %i1 in calling regwin is destroyed by (C)AlloC
 */
extern struct Item      *SPARC_AlloI(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4);
extern struct Component *SPARC_AlloC(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4);
struct Item *SPARC_AlloSI(struct Structure *s, int i1, int i2, int i3, int i4);
/* binding of entry names */

#ifndef __svr4__
extern void 		CinitT() __asm__("CinitT");
extern ref(StackObject) AlloSO() __asm__("AlloSO");
extern ref(Item)	CopyT() __asm__("CopyT");
extern void		CopySRR() __asm__("CopySRR");
extern void		CopySVR() __asm__("CopySVR");
extern ref(Structure)	AlloS() __asm__("AlloS");
extern ref(Structure)	ThisS() __asm__("ThisS");
extern ref(Structure)	ObjS() __asm__("ObjS");
extern void		DoGC() __asm__("DoGC");
extern ref(Item)	AlloSI() __asm__("AlloSI");
extern ref(Component)	AlloSC() __asm__("AlloSC");
extern void             RefNone() __asm__("RefNone");
extern void             AttBC() __asm__("AttBC");
extern void             CopyRR() __asm__("CopyRR");
extern void             CopyVR() __asm__("CopyVR");
extern void             ChkRA() __asm__("ChkRA");
extern ref(Component)   Susp() __asm__("Susp");

extern long 		 eqS() __asm__("eqS"); 
extern long              neS() __asm__("neS");
extern long              gtS() __asm__("gtS");
extern long              leS() __asm__("leS");
extern long              geS() __asm__("geS");
extern long              ltS() __asm__("ltS");
#else
extern ref(StackObject) AlloSO(unsigned size);
extern long 		 eqS(); 
extern long              neS();
extern long              gtS();
extern long              leS();
extern long              geS();
extern long              ltS();
#endif
#endif /* sparc */

#ifdef hppa
extern long 		 eqS() __asm__("eqS"); 
extern long              neS() __asm__("neS");
extern long              gtS() __asm__("gtS");
extern long              leS() __asm__("leS");
extern long              geS() __asm__("geS");
extern long              ltS() __asm__("ltS");
#endif

#ifdef MAC
static void 
#else
static __inline__ void 
#endif
AssignReference(long *theCell, ref(Item) newObject)
{
  *(struct Item **)theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(casthandle(Object)theCell);
}

/* inline version of memcpy; works only for 4 byte aligned */
#define MEMCPY(dst,src,bytesize)            \
{  register long i;                         \
   for (i = (bytesize)-4; i >= 0; i -= 4)     \
       *(long *)(((char *)(dst))+i) = *(long *)(((char *)(src))+i); \
}

#ifdef RTDEBUG
extern void zero_check(char *p, unsigned bytesize);
#endif

#ifdef __GNUC__
static __inline__ void 
#else
static void 
#endif
setup_item(ref(Item) theItem,
	   ref(ProtoType) prototype,
	   ref(Object) origin
	   )
{
    register ref(GCEntry) initTab;
  
    theItem->Proto = prototype;
    if (IOAMinAge!=0) theItem->GCAttr = IOAMinAge; /* Set item age to IOAMinAge */

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

	/*
	if ( (long)po->Proto == -1)
	  printf("\nsetup_item: component: 0x%08x\n", po);
        */
    }

  ((long *)theItem)[prototype->OriginOff] = (long) origin;
}

#endif /* __GNUC__ */

#ifdef __GNUC__
#include "IOAAlloc.h"
#else
extern char	       *IOAalloc();
#endif
