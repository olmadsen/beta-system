#ifdef hppa
#undef RTDEBUG /* Sorry. The new gcc complains about getR2Reg() */
#endif

/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define GCable_Module

#ifdef hppa
register long _dummy8 asm("%r15"); /* really tmp data 1 */
register long _dummy9 asm("%r16"); /* really tmp data 2 */
#endif

#include "beta.h"
#include "crun.h"

asmlabel(CopySRR, "
	mov	%l7, %o3
	ba	"CPREF"CopySRR
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
    register long size;
    register long i;
    
    GCable_Entry();

#ifdef sparc
    ClearCParams(); /* OK here: is not called from RT */
#endif

#ifdef hppa
    low =  (unsigned) getR2Reg(); 
    high = (unsigned) getR1Reg();
#endif
    
    Ck(theItem); Ck(theRep);
    /* Copy a slice of a Reference Repetition.
     * stack on entry [return(0),offset(4),Item(8),ValRep(12),...]
     * and registers DataReg1=low, DataReg2=high.
     */
    
    /* stack[12] -> theRep; */
    /* Check that low and high usable. */
    if (low < theRep->LowBorder) 
      BetaError(RepLowRangeErr, cast(Object)theItem);
    if (high > theRep->HighBorder) 
      BetaError(RepHighRangeErr, cast(Object)theItem);
    
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


