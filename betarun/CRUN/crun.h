/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: crun.h,v $, rel: %R%, date: $Date: 1992-08-01 20:17:14 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */


#ifndef _CRUN_H_
#define _CRUN_H_

#define asmlabel(label, code) \
  asm(".text;.align 4;.global " #label ";" #label ":" code)

extern ref(Item) 	AlloI() asm ("AlloI");
extern ref(Component) 	AlloC() asm ("AlloC");
extern ref(ValRep) 	AlloVR();
extern char 	      * LVRAAlloc();
extern char 	      * LVRAByteAlloc();
extern ref(RefRep)	AlloRR();
extern ref(StackObject) AlloSO() asm ("AlloSO");
extern ref(ValRep)	CopyT() asm ("CopyT");
extern ref(RefRep)	CopySRR() asm ("CopySRR");
extern ref(ValRep)	CopySVR() asm ("CopySVR");
extern ref(Structure)	AlloS() asm("AlloS");
extern ref(Structure)	ThisS() asm("ThisS");
extern ref(Item)	AlloSI() asm("AlloSI");
extern ref(Component)	AlloSC() asm("AlloSC");
/* The following not capitalized to avoid loosing the ones starting with L */
extern int 		EqS() asm("eqS"); 
extern int              NeS() asm("neS");
extern int              LtS() asm("ltS");
extern int              GtS() asm("gtS");
extern int              LeS() asm("leS");
extern int              GeS() asm("geS");
extern void             Return() asm ("Return");
extern void             DoGC();
extern void             RefNone() asm("RefNone");
extern void             AttBC() asm("AttBC");
extern void             CopyRR() asm("CopyRR");
extern void             CopyVR() asm("CopyVR");
extern void             BetaError();
extern void             ChkRA() asm("ChkRA");
extern ref(Component)   Susp() asm("Susp");

static inline long DispatchValRepSize(ref(ValRep) theRep, unsigned range)
{
  switch ( (int) (theRep)->Proto){
  case (int) ByteRepPTValue:   return ByteRepSize(range);
  case (int) WordRepPTValue:   return WordRepSize(range);
  case (int) ValRepPTValue:    return ValRepSize(range);
  case (int) DoubleRepPTValue: return ByteRepSize(range);
  }
}

static inline long DispatchValRepBodySize(ref(ValRep) theRep, unsigned range)
{
  switch ( (int) (theRep)->Proto){
  case (int) ByteRepPTValue:   return ByteRepBodySize(range);
  case (int) WordRepPTValue:   return WordRepBodySize(range);
  case (int) ValRepPTValue:    return ValRepBodySize(range);
  case (int) DoubleRepPTValue: return ByteRepBodySize(range);
  }
}

static inline void
AssignReference(long *theCell, ref(Item) newObject)
{
  *(casthandle(Item)theCell) = newObject;
  if (!inIOA(theCell)) ChkRA(casthandle(Item)theCell);
}

static inline void
int_clear(char *p, unsigned size)
{
  register int i;
  if (size&3)
    fprintf(stderr, "What! size&3 != 0\n");
  for (i = size-4; i >= 0; i -= 4)
    *(int *)(p+i) = 0;	/* Ugly Hacks Work Fast */
}

static inline char *
IOAalloc(unsigned size)
{
  register char *p;

  while ((char *)IOATop+size > (char *)IOALimit) {
    DoGC(size);
  }

  p = (char *)IOATop;
  IOATopoff += size;

  return p;
}

static inline char *
IOAcalloc(unsigned size)
{
  register char *p;

  while ((char *) IOATop+size > (char *)IOALimit) {
    DoGC(size);
  }

  p = (char *)IOATop;
  IOATopoff += size;

  int_clear(p, size);
  return p;
}

static inline void
setup_item(ref(Item) theItem,
	   ref(ProtoType) prototype,
	   ref(Object) origin
	   )
{
    register ref(GCEntry) initTab;
  
    theItem->Proto = prototype;
    theItem->GCAttr = -1;

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
	
	po = cast(PartObject) ((int *)theItem + initTab->StaticOff);
	po->Proto = initTab->Proto;
	po->OrigOff = initTab->OrigOff;
    }

  ((int *)theItem)[prototype->OriginOff] = (int) origin;
}

#endif
