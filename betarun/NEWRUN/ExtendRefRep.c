/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */
#include "beta.h"
#include "crun.h"

void ExtRR(struct Object *theObj,
	   unsigned offset, /* in longs */
	   long add,
	   long *SP
	   )
{
    struct RefRep * theRep;
    struct RefRep * newRep;
    long newRange, copyRange, i;
    
    DEBUG_CODE(NumExtRR++);
    
    Ck(theObj);
    theRep = *(struct RefRep **)((long *) theObj + offset);
    newRange = theRep->HighBorder + add;
    copyRange = (add < 0) ? newRange : theRep->HighBorder;
    
    if (newRange < 0) newRange = 0;

    Protect2(theRep, theObj,
	     newRep = (struct RefRep *)IOAcalloc(RefRepSize(newRange), SP));
   
    Ck(theObj);

    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i)
      /* AssignReference not needed:
       * only needed when dest may be in aoa and src may be in ioa.
       */
      newRep->Body[i] = theRep->Body[i];
    
    AssignReference((long *)theObj + offset, (struct Item *)newRep);
}

