/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: ExtendRefRep.c,v $, rel: %R%, date: $Date: 1992-08-27 15:47:45 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(ExtRR, "
	ba	_CExtRR
	mov	%l7, %o2
");

void CExtRR(ref(Object) theObj,
	    unsigned offset, /* in longs */
	    long add
	    )
{
    DeclReference1(struct RefRep *theRep);
    DeclReference2(struct RefRep *newRep);
    
    long newRange, copyRange, i;
    
    GCable_Entry();
    
    Ck(theObj);
    theRep = *casthandle(RefRep) ((long *) theObj + offset);
    newRange = theRep->HighBorder + add;
    copyRange = (add < 0) ? newRange : theRep->HighBorder;
    
    if (newRange < 0)
      newRange = 0;
    
    newRep = cast(RefRep) IOAcalloc(RefRepSize(newRange));
   
    ForceVolatileRef(theObj);
    Ck(theObj);

    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = newRange;
    
    for (i = 0; i < copyRange; ++i)
      newRep->Body[i] = theRep->Body[i];
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

