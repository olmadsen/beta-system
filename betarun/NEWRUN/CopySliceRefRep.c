/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

/* Copy a slice of a Reference Repetition.*/

void CCopySRR(RefRep *theRep,
	      Item *theItem,
	      unsigned offset, /* i ints */
	      unsigned low,
	      unsigned high,
	      long *SP
	      )
{
    RefRep *newRep=0;
    register long range;
    register long i;
    unsigned long size;
    
    DEBUG_CODE(NumCopySRR++);

    Ck(theItem); Ck(theRep);
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, 0, SP, 0);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, 0, SP, 0);
    }
    
    /* Calculate the range of the new repetition. */
    range = high - low + 1;
    if (range < 0) range = 0;
    
    /* range is now converted to the range of the resulting repetition. */
    
    push(theItem);
    push(theRep);
    size = RefRepSize(range);
    do {
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopySRR allocates in AOA\n"));
	newRep = (RefRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      }
      if (!newRep) {
	newRep = (RefRep *)IOATryAlloc(size, SP);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!newRep);
    pop(theRep);
    pop(theItem);
    
    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    SETPROTO(newRep, RefRepPTValue);
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy the body part of the repetition. */
    for (i = 0; i < range; ++i){
      AssignReference(&newRep->Body[i], theRep->Body[i+low-theRep->LowBorder]);
    }
    
    AssignReference((long *)theItem + offset, (Item *)newRep);

    Ck(theRep); Ck(theItem); Ck(newRep); 
}


