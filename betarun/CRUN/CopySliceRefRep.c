/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#ifdef hppa
register long _dummy8 __asm__("%r15"); /* really tmp data 1 */
register long _dummy9 __asm__("%r16"); /* really tmp data 2 */
#endif

#include "beta.h"
#include "crun.h"

ParamRepObjOffLowHigh(CopySRR)
{
    DeclReference1(struct RefRep *, newRep);
    register long range;
    register long i;
    
    GCable_Entry();

    FetchRepObjOffLowHigh();

    DEBUG_CODE(NumCopySRR++);

    Ck(theObj); Ck(theRep);
    /* Copy a slice of a Reference Repetition.
     * stack on entry [return(0),offset(4),Item(8),ValRep(12),...]
     * and registers DataReg1=low, DataReg2=high.
     */
    
    /* Check that low and high usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theObj);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
      BetaError(RepHighRangeErr, cast(Object)theObj);
    
    /* Calculate the range of the new repetition. */
    range = high - low + 1;
    if (range < 0) range = 0;
    
    /* range is now converted to the range of the resulting repetition. */
    
    Protect2(theObj, theRep, newRep = cast(RefRep) IOAalloc(RefRepSize(range)));
    
    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = RefRepPTValue;
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy the body part of the repetition. */
    
    for (i = 0; i < range; ++i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder]; /* AssignReference? */
    
    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}


