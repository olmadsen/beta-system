/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopyValRep.c,v 1.20 1992-11-06 16:55:14 beta Exp $
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
    if (range > LARGE_REP_SIZE){
      /* newRep should go into LVRA. If LVRAAlloc causes an LVRACompaction
       * the value of theRep may be wrong after LVRAAlloc: this is the case
       * if the repetition pointed to by theRep was moved. To prevent this,
       * the cell actually referencing the repetition is remembered. This cell
       * will be updated if the repetition is moved.
       */
      long *cycleCell  = (long *) theRep->GCAttr; /* Cell that references the repetition */
      
      DEBUG_LVRA(fprintf(output, "CopyValRep allocates in LVRA\n"));
		
      newRep = LVRAAlloc(theRep->Proto, range);
      /* update theRep, it may have been moved by LVRACompaction */
      theRep = cast(ValRep) *cycleCell;
    }
    if (newRep) {
	/* Make the LVRA-cycle of the new repetition */
	newRep->GCAttr = (long) ((long *) theObj + offset);
    }
    else
#endif
      {
	  Protect2(theObj, theRep,
		   newRep = cast(ValRep) IOAalloc(size);
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

