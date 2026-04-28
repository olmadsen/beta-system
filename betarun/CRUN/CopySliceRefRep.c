/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#ifdef hppa
register long _dummy8 __asm__("%r15"); /* really tmp data 1 */
register long _dummy9 __asm__("%r16"); /* really tmp data 2 */
#endif

#include "beta.h"
#include "crun.h"

ParamRepObjOffLowHigh(CopySRR)
{
    DeclReference1(RefRep *, newRep);
    register long range;
    register long i;
    unsigned long size;
    
    FetchRepObjOffLowHigh();

    DEBUG_CODE(NumCopySRR++);

    Ck(theObj); Ck(theRep);
    newRep=NULL;

    /* Check that low and high usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepLowRangeErr, (Object *)theObj);
    }
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ){
      SubRangeErrLow = low;
      SubRangeErrHigh = high;
      RangeMax = theRep->HighBorder;
      BetaError(RepHighRangeErr, (Object *)theObj);
    }
    
    /* Calculate the range of the new repetition. */
    range = high - low + 1;
    if (range < 0) range = 0;
    
    /* range is now converted to the range of the resulting repetition. */
    
    push(theObj);
    push(theRep);
    size = RefRepSize(range);
    do {
      if (range>LARGE_REP_SIZE || size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyRR allocates in AOA\n"));
	newRep = (RefRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      }
      if (!newRep) {
	newRep = (RefRep *)IOATryAlloc(size);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!newRep);
    pop(theRep);
    pop(theObj);
    
    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    SETPROTO(newRep,RefRepPTValue);
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy the body part of the repetition. */
    for (i = 0; i < range; ++i){
      AssignReference(&newRep->Body[i], (Item*)theRep->Body[i+low-theRep->LowBorder]);
    }
    
    AssignReference((long *)theObj + offset, (Item *) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);
}


