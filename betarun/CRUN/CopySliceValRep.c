/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopySliceValRep.c,v $, rel: %R%, date: $Date: 1992-07-20 11:48:53 $, SID: $Revision: 1.6 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(CopySVR, "
	mov	%l7, %o3
	ba	_CCopySVR
	mov	%l6, %o4
");

void CCopySVR(ref(ValRep) theRep,
		      ref(Item) theItem,
		      unsigned offset, /* i ints */
		      unsigned low,
		      unsigned high
		      )
{
    register unsigned BodySize;
    register int i;
    register char *b;
    register ref(ValRep) newRep;
    
    /* Copy a slice of a Value Repetition. */
    
    /* stack[12] -> theRep; */
    /* Check that low and high usable. */
    if (low  < theRep->LowBorder)
      BetaError(-6, theItem);
    if (high > theRep->HighBorder)
      BetaError(-7, theItem);
    
    /* Calculate the range of the new repetition. */
    high =  high - low + 1;
    if (high < 0) high = 0;

    BodySize = (theRep->Proto==ByteRepPTValue) ? ((high+4)/4)*4 : high*4;
      
    newRep = cast(ValRep) IOAalloc(headsize(ValRep) + BodySize);
    
    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = high;
    
    /* Copy the body part of the repetition. */
    switch (theRep->Proto){
    case ByteRepPTValue:
      /* Since the slice may start on any byte we copy it byte by byte */
      for (i = 0; i < high; ++i)
	newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
      break;
    default:
      for (b = 0; b < high; ++b)
	newRep->Body[b] = theRep->Body[b+low-theRep->LowBorder];
      break;
    }
    
    /* stack[8] -> theItem;
     * stack[4] -> offset
     */
    
    (casthandle(ValRep)theItem)[offset] = newRep;
    if (!inIOA(theItem))
      CheckReferenceAssignment((int *)theItem + offset);
}


