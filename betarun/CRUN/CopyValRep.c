/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
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

#ifdef sparc
    ClearCParams(); /* OK here: is not called from RT */
#endif
    
    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;
    size = DispatchValRepSize(theRep->Proto,range);

    if (range > LARGE_REP_SIZE){
      /* newRep should go into LVRA */
      long *cycleCell  = 0;

      if (!inIOA(theRep)) {
	/* theRep is in LVRA (it cannot be in AOA, cf. NewCopyObject). 
	 * If LVRAAlloc causes an LVRACompaction
	 * the value of theRep may be wrong after LVRAAlloc: this is the case
	 * if the repetition pointed to by theRep was moved. To prevent this,
	 * the cell actually referencing the repetition is remembered. This cell
	 * will be updated if the repetition is moved.
	 */
	cycleCell = (long *) theRep->GCAttr; /* Cell that references the repetition */
      }
      
      DEBUG_LVRA(fprintf(output, "CopyValRep allocates in LVRA\n"));
		
      newRep = LVRAAlloc(theRep->Proto, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = cast(ValRep) *cycleCell;
      }
    }
    if (newRep) {
	/* Make the LVRA-cycle of the new repetition */
	newRep->GCAttr = (long) ((long *) theObj + offset);
    }
    else
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

