/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: crun.h,v $, rel: %R%, date: $Date: 1992-08-22 02:08:59 $, SID: $Revision: 1.10 $
 * by Peter Andersen and Tommy Thorn.
 */


#ifndef _CRUN_H_
#define _CRUN_H_

extern void	      * CAlloC();
extern void	      * CAlloI();
extern ref(ValRep) 	AlloVR();
extern char 	      * LVRAAlloc();
extern char 	      * LVRAByteAlloc();
extern ref(RefRep)	AlloRR();
extern ref(StackObject) AlloSO() asm ("AlloSO");
extern void		CopyT() asm ("CopyT");
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
extern char	      * IOAalloc();
extern char	      * IOAcalloc();

/*
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
*/

static inline void
CCheckRefAsgn(handle(Object) theObjHandle)
{
  /* The Assignment *theObjHandle = theObj has just been
   * done. We know the theObjHandle is in AOA, now check if
   * *theObjHandle(==theObj) is in IOA.
   */
   
  if (inIOA(*theObjHandle))
    /* Remember this target cell. */
    AOAtoIOAInsert(theObjHandle);
}

static inline void
AssignReference(long *theCell, ref(Item) newObject)
{
  *(struct Item **)theCell = newObject;
  if (! inIOA(theCell) && inIOA(newObject))
    AOAtoIOAInsert(theCell);
}

static inline
int_clear(char *p, unsigned size)
{
  register int i;
  if (size&3)
    fprintf(stderr, "What! size&3 != 0\n");
  for (i = size-4; i >= 0; i -= 4)
    *(int *)(p+i) = 0;	/* Ugly Hacks Work Fast */
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
	
	po = cast(PartObject) ((int *)theItem + initTab->StaticOff);
	po->Proto = initTab->Proto;
	po->OrigOff = initTab->OrigOff;
    }

  ((int *)theItem)[prototype->OriginOff] = (int) origin;
}

#ifdef DEBUG_IOA
/* Consistency checks - Checks for valid references */
#define Ck(r) \
  (r && Claim(inIOA(r) || inAOA(r) || inLVRA(r), \
	      #r ": none or inside IOA, AOA, or LVRA"))

#else
#define Ck(r)
#endif

#endif
