/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */


#ifndef _CRUN_H_
#define _CRUN_H_

extern void             Return();
extern void             BetaError();

#ifdef crts
extern struct Component*AlloC();
extern struct Item     *AlloI();
#endif

#ifdef sparc
/* Functions used to call RT routines directly from C.
 * Needed because %i1 in calling regwin is destroyed by (C)AlloC
 */
extern struct Item      *SPARC_AlloI(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4);
extern struct Component *SPARC_AlloC(struct Object *origin, int i1, struct ProtoType *proto, int i3, int i4);
struct Item *SPARC_AlloSI(struct Structure *s, int i1, int i2, int i3, int i4);
/* binding of entry names */

#ifndef __svr4__
extern void 		CinitT() asm("CinitT");
extern ref(StackObject) AlloSO() asm("AlloSO");
extern void		CopyT() asm("CopyT");
extern void		CopySRR() asm("CopySRR");
extern void		CopySVR() asm("CopySVR");
extern ref(Structure)	AlloS() asm("AlloS");
extern ref(Structure)	ThisS() asm("ThisS");
extern ref(Structure)	ObjS() asm("ObjS");
extern void		DoGC() asm("DoGC");
extern ref(Item)	AlloSI() asm("AlloSI");
extern ref(Component)	AlloSC() asm("AlloSC");
extern void             RefNone() asm("RefNone");
extern void             AttBC() asm("AttBC");
extern void             CopyRR() asm("CopyRR");
extern void             CopyVR() asm("CopyVR");
extern void             ChkRA() asm("ChkRA");
extern ref(Component)   Susp() asm("Susp");

extern long 		 eqS() asm("eqS"); 
extern long              neS() asm("neS");
extern long              gtS() asm("gtS");
extern long              leS() asm("leS");
extern long              geS() asm("geS");
extern long              ltS() asm("ltS");
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
extern long 		 eqS() asm("eqS"); 
extern long              neS() asm("neS");
extern long              gtS() asm("gtS");
extern long              leS() asm("leS");
extern long              geS() asm("geS");
extern long              ltS() asm("ltS");
#endif

#ifdef crts
extern long 		 eqS(struct Structure *, struct Structure *);
extern long              neS(struct Structure *, struct Structure *);
extern long              gtS(struct Structure *, struct Structure *);
extern long              leS(struct Structure *, struct Structure *);
extern long              geS(struct Structure *, struct Structure *);
extern long              ltS(struct Structure *, struct Structure *);
#endif

#ifdef MAC
static void 
#else
static inline void 
#endif
AssignReference(long *theCell, ref(Item) newObject)
{
  *(struct Item **)theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(casthandle(Object)theCell);
}

#ifdef __GNUC__
static inline void 
#else
static  void 
#endif
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

/* inline version of memcpy; works only for 4 byte aligned */
#define MEMCPY(dst,src,bytesize)            \
{  register long i;                         \
   for (i = (bytesize)-4; i >= 0; i -= 4)     \
       *(long *)(((char *)(dst))+i) = *(long *)(((char *)(src))+i); \
}

#ifdef __GNUC__
static inline void 
#else
static void 
#endif
zero_check(char *p, unsigned bytesize)
{
  register long i;
#ifdef RTDEBUG
  if (bytesize&3)
    fprintf(output, "What! bytesize&3 != 0\n");
#endif
  for (i = bytesize-4; i >= 0; i -= 4)
    if (*(long *)(p+i) != 0) fprintf(output, "zero_check failed\n");	
}

#ifdef __GNUC__
static inline void 
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

	/*
	if ( (long)po->Proto == -1)
	  printf("\nsetup_item: component: 0x%08x\n", po);
        */
    }

  ((long *)theItem)[prototype->OriginOff] = (long) origin;
}

#endif

#ifdef __GNUC__
#include "IOAAlloc.h"
#else
extern char	       *IOAalloc();
extern char	       *IOAcalloc();
#endif
