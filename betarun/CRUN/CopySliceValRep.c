/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopySliceValRep.c,v $, rel: %R%, date: $Date: 1992-06-08 23:55:47 $, SID: $Revision: 1.3 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(CopySliceValRep, "
	mov	%l7, %o3
	ba	_CCopySliceValRep
	mov	%l6, %o4
");

ref(ValRep) CCopySliceValRep(ref(ValRep) theRep,
				ref(Item) theItem,
				unsigned offset, /* i ints */
				unsigned low,
				unsigned high
			    )
{
    register unsigned size;
    register int i;
    register ref(ValRep) newRep;
    
    /* Copy a slice of a Value Repetition. */
    
    /* stack[12] -> theRep; */
    /* Check that low and high usable. */
    if (low  < theRep->LowBorder)
      BetaError(-6, theItem);
    if (high > theRep->HighBorder)
      BetaError(-7, theItem);
    
    /* Calculate the range of the new repetition. */
    size = high - low + 1;
    if (size < 0)
      size = 0;
    
    /* size is now converted to the range of the resulting repetition. */
    
    newRep = cast(ValRep) IOAalloc(headsize(ValRep) + size*4);
    
    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = cast(ProtoType) -3;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = size;
    
    /* Copy the body part of the repetition. */
    
    for (i = 0; i < size; ++i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    
    /* stack[8] -> theItem;
     * stack[4] -> offset
     */
    
    (casthandle(ValRep)theItem)[offset] = newRep;
    if (!inIOA(theItem))
      CheckReferenceAssignment((int *)theItem + offset);
    
    return cast(ValRep) 12; /* What? Why 12?? */
}


