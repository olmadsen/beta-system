/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopyRefRep.c,v 1.6 1992-09-03 12:55:50 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void CopyRR(ref(ValRep) theRep,
	    ref(Object) theObj,
	    unsigned offset /* i ints */
	    )
{
    DeclReference1(struct RefRep *, newRep);
    register unsigned range, i;
    
    GCable_Entry();
    
    
    Ck(theRep);Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    Protect2(theObj, theRep,
	     newRep = cast(RefRep) IOAcalloc(RefRepSize(range)));
    
    Ck(theRep); Ck(theObj);

    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy theRep to newRep */
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i];	/* Beautiful! */
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

