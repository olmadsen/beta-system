/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopySliceRefRep.c,v $, rel: %R%, date: $Date: 1992-07-21 17:18:22 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(CopySRR, "
	mov	%l7, %o3
	ba	_CCopySRR
	mov	%l6, %o4
");

void CCopySRR(ref(RefRep) theRep,
		      ref(Item) theItem,
		      unsigned offset, /* i ints */
		      unsigned low,
		      unsigned high
		      )
{
    register unsigned size;
    register int i;
    register ref(RefRep) newRep;

    /* Copy a slice of a Reference Repetition.
     * stack on entry [return(0),offset(4),Item(8),ValRep(12),...]
     * and registers DataReg1=low, DataReg2=high.
     */

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
    
    newRep = cast(RefRep) IOAalloc(headsize(RefRep) + size*4);
    
    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = size;
    
    /* Copy the body part of the repetition. */
    
    for (i = 0; i < size; ++i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    
    /* stack[8] -> theItem;
     * stack[4] -> offset
     */
    
    AssignReference((long *)theItem + offset, cast(Item) newRep);
}


