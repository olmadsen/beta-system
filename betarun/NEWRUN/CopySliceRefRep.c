/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

/* Copy a slice of a Reference Repetition.*/

void CopySRR(struct RefRep *theRep,
	     struct Item *theItem,
	     unsigned offset, /* i ints */
	     unsigned low,
	     unsigned high,
	     long *SP
	     )
{
    struct RefRep *newRep;
    register long range;
    register long i;
    
    DEBUG_CODE(NumCopySRR++);

    Ck(theItem); Ck(theRep);
    
    /* Check that low and high are usable. */
    if (low < theRep->LowBorder) 
      BetaError(RepLowRangeErr, GetThis(SP), SP);
    if (high > theRep->HighBorder) 
      BetaError(RepHighRangeErr, GetThis(SP), SP);
    
    /* Calculate the range of the new repetition. */
    range = high - low + 1;
    if (range < 0) range = 0;
    
    /* range is now converted to the range of the resulting repetition. */
    
    Protect2(theItem, theRep, 
	     newRep = (struct RefRep *) IOAalloc(RefRepSize(range), SP));
    
    Ck(theRep); Ck(theItem);

    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    
    /* Copy the body part of the repetition. */
    
    for (i = 0; i < range; ++i)
      /* AssignReference not needed:
       * only needed when dest may be in aoa and src may be in ioa.
       */
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder]; 
    
    AssignReference((long *)theItem + offset, (struct Item *)newRep);
}


