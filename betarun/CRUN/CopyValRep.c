/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopyValRep.c,v 1.15 1992-10-08 11:00:43 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

void CopyVR(ref(ValRep) theRep,
	    ref(Object) theObj,
	    unsigned offset /* i ints */
	    )
{
    DeclReference1(struct ValRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();
    
    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;
    size = DispatchValRepSize(theRep->Proto,range);

#ifdef LVR_Area
    if (range > LARGE_REP_SIZE) newRep = LVRAAlloc(theRep->Proto, range);
    if (newRep) {
	/* Make the LVRA-cycle: theCell -> newRep.Age */
	newRep->GCAttr = (int) ((int *) theObj + offset);
    }
    else
#endif
      {
	  Protect2(theObj, theRep,
		   newRep = cast(ValRep) IOAcalloc(size);
		   );
	  
	  Ck(theObj);
	  newRep->Proto = theRep->Proto;
	  newRep->GCAttr = 1;
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
      }
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < (size-headsize(ValRep))/4; ++i)
      newRep->Body[i] = theRep->Body[i];
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);
}

