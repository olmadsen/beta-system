/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#include "beta.h"
#include "crun.h"

#define REP ((struct ObjectRep *)theRep)
#define NEWREP ((struct ObjectRep *)newRep)

void CopyVR(struct ValRep *theRep,
	    struct Object *theObj,
	    unsigned offset /* in longs */,
	    long *SP
	    )
{
    struct ValRep * newRep;
    register unsigned range, i, size;
   
    DEBUG_CODE(NumCopyVR++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
    range = theRep->HighBorder;

    if (isValRep(theRep)){
      size = DispatchValRepSize(theRep->Proto,range);
      
      if (range > LARGE_REP_SIZE){
	/* newRep should go into LVRA */
	long *cycleCell  = 0;
	
	if (!inIOA(theRep)) {
	  /* theRep is in LVRA (it cannot be in AOA, cf. NewCopyObject). 
	   * If LVRAAlloc causes an LVRACompaction
	   * the value of theRep may be wrong after LVRAAlloc: this is the case
	   * if the repetition pointed to by theRep was moved. To prevent this,
	   * the cell actually referencing the repetition is remembered. This 
	   * cell will be updated if the repetition is moved.
	   */
	  cycleCell = (long *)theRep->GCAttr; /* Cell that references theRep */
	}
	
	DEBUG_LVRA(fprintf(output, "CopyValRep allocates in LVRA\n"));
	
	newRep = LVRAAlloc(theRep->Proto, range);
	if (cycleCell) {
	  /* theRep was in LVRA. Since it may have been moved by
	   * LVRACompaction, we update it.
	   */
	  theRep = (struct ValRep *)*cycleCell;
	}
      }
      if (newRep) {
	/* Make the LVRA-cycle of the new repetition */
	newRep->GCAttr = (long) ((long *) theObj + offset);
      }
      else
	{
	  Protect2(theObj, theRep,
		   newRep = (struct ValRep *)IOAalloc(size, SP));
	  
	  Ck(theObj);
	  newRep->Proto = theRep->Proto;
	  newRep->GCAttr = 1;
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}

      size -= headsize(ValRep); /* adjust size to be bodysize */

      /* Copy theRep to newRep. Copy the whole body as longs */
      for (i = 0; i < size/4; ++i)
	newRep->Body[i] = theRep->Body[i];

    } else {
      /* object-repetition */
      size = DispatchObjectRepSize(theRep->Proto, range, REP->iProto);

      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVR allocates in AOA\n"));
	newRep = (struct ValRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      } 
      if (!newRep){
	Protect2(theObj, theRep, newRep = (struct ValRep *)IOAalloc(size, SP));
	newRep->GCAttr = 1;
      }
      
      Ck(theObj);
      newRep->Proto = theRep->Proto;
      /* newRep->GCAttr set above if in IOA */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
      AssignReference(&NEWREP->iOrigin, REP->iOrigin);
      NEWREP->iProto = REP->iProto;

      size -= headsize(ObjectRep); /* adjust size to be bodysize */

      /* Copy theRep to newRep. Copy the whole body as longs */
      for (i = 0; i < size/4; ++i){
	AssignReference(&NEWREP->Body[i], REP->Body[i]);
      }
    }
        
    AssignReference((long *)theObj + offset, (struct Item *)newRep);
}

