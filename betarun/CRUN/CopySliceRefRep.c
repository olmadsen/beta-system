/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopySliceRefRep.c,v 1.20 1992-10-22 14:16:33 beta Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#ifdef hppa
register int _dummy8 asm("%r15"); /* really tmp data 1 */
register int _dummy9 asm("%r16"); /* really tmp data 2 */
#endif

#include "beta.h"
#include "crun.h"

asmlabel(CopySRR, "
	mov	%l7, %o3
	ba	_CCopySRR
	mov	%l6, %o4
");

#ifdef hppa
#  define CCopySRR CopySRR
#endif

void CCopySRR(ref(RefRep) theRep,
	      ref(Item) theItem,
	      unsigned offset, /* i ints */
	      unsigned low,
	      unsigned high
	      )
{
    DeclReference1(struct RefRep *, newRep);
    register int size;
    register int i;
    
    GCable_Entry();

#ifdef hppa
    low = (unsigned) getR2Reg();
    high = (unsigned) getR1Reg();
#endif
    
    Ck(theItem); Ck(theRep);
    /* Copy a slice of a Reference Repetition.
     * stack on entry [return(0),offset(4),Item(8),ValRep(12),...]
     * and registers DataReg1=low, DataReg2=high.
     */
    
    /* stack[12] -> theRep; */
    /* Check that low and high usable. */
    if (low < theRep->LowBorder) BetaError(RepLowRangeErr, theItem);
    if (high > theRep->HighBorder) BetaError(RepHighRangeErr, theItem);
    
    /* Calculate the range of the new repetition. */
    size = high - low + 1;
    if (size < 0) size = 0;
    
    /* size is now converted to the range of the resulting repetition. */
    
    Protect2(theItem, theRep, newRep = cast(RefRep) IOAalloc(RefRepSize(size)));
    
    Ck(theRep); Ck(theItem);

    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = RefRepPTValue;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = size;
    
    /* Copy the body part of the repetition. */
    
    for (i = 0; i < size; ++i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    
    AssignReference((long *)theItem + offset, cast(Item) newRep);
}


