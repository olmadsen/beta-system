/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopyValRep.c,v 1.16 1992-10-19 09:16:14 beta Exp $
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
       * we temporary set the LVRA cycle to be from tmpRep, and remember the
       * cell that actually references the repetition. After LVRAAlloc, the
       * original LVRACycle is restored.
       */
      long oldGC  = theRep->GCAttr; /* Cell that references the repetition */
      ref(ValRep) tmpRep = theRep;  /* Local variable need to take address */
      
      DEBUG_LVRA(fprintf(output, "CopyValRep in LVRA\n"));

      tmpRep->GCAttr = (long)&tmpRep; 
      /* tmpRep will be updated if the repetition is moved by an 
       * LVRACompaction 
       */
				
      newRep = LVRAAlloc(tmpRep->Proto, range);
      /* update theRep */
      theRep = tmpRep;
      /* restore original LVRA cycle of theRep */
      theRep->GCAttr = oldGC;
    }
    if (newRep) {
	/* Make the LVRA-cycle of the new repetition */
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

