/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: crun.h,v $, rel: %R%, date: $Date: 1992-06-06 04:06:48 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */


#ifndef _CRUN_H_
#define _CRUN_H_

#define asmlabel(label, code) \
  asm(".text;.align 4;.global " #label ";" #label ":" code)

extern ref(Item) 	AllocateItem() asm ("AllocateItem");
extern ref(Component) 	AllocateComponent() asm ("AllocateComponent");
extern ref(ValRep) 	AllocateValRep();
extern char 	      * LVRAAlloc();
extern ref(RefRep)	AllocateRefRep();
extern ref(StackObject) AllocateStackObject() asm ("AllocateStackObject");
extern ref(ValRep)	CopyText() asm ("CopyText");
extern ref(ValRep)	CopyCtext() asm ("CopyCtext");
extern ref(RefRep)	CopySliceRefRep() asm ("CopySliceRefRep");
extern ref(ValRep)	CopySliceValRep() asm ("CopySliceValRep");
extern ref(Structure)	AllocateStruc() asm("AllocateStruc");
extern ref(Structure)	ThisStruc() asm("ThisStruc");
extern ref(Item)	AllocateStrucItem() asm("AllocateStrucItem");
extern ref(Component)	AllocateStrucComponent() asm("AllocateStrucComponent");
extern int eqStruc() 	asm("eqStruc");
extern int neStruc() 	asm("neStruc");
extern int ltStruc() 	asm("ltStruc");
extern int gtStruc() 	asm("gtStruc");
extern int leStruc() 	asm("leStruc");
extern int geStruc() 	asm("geStruc");
extern void Return() 	asm ("Return");
extern void PerformGC();
extern void ReferenceIsNone() asm("ReferenceIsNone");
extern void AttachBasicComponent() asm("AttachBasicComponent");
extern void CopyValRep() asm("CopyValRep");
extern void BetaError();
extern void CheckReferenceAssignment() asm("CheckReferenceAssignment");
extern void Suspend() asm("Suspend");

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
    PerformGC(size);
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
    PerformGC(size);
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
