/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $Id: CopySliceValRep.c,v 1.24 1993-02-19 09:40:18 datpete Exp $
 * by Peter Andersen and Tommy Thorn.
 */

#ifdef hppa
register long _dummy8 asm("%r15"); /* really tmp data 1 */
register long _dummy9 asm("%r16"); /* really tmp data 2 */
#endif

#define GCable_Module

#include "beta.h"
#include "crun.h"

asmlabel(CopySVR, "
	mov	%l7, %o3
	ba	_CCopySVR
	mov	%l6, %o4
");

#ifdef hppa
#  define CCopySVR CopySVR
#endif

void CCopySVR(ref(ValRep) theRep,
	      ref(Item) theItem,
	      unsigned offset, /* i ints */
	      unsigned low,
	      long      high
	      )
{
    DeclReference1(struct ValRep *, newRep);
    register long i;
    
    GCable_Entry();

#ifdef sparc
    ClearCParams(); /* OK here: is not called from RT */
#endif


#ifdef hppa
  low = (unsigned) getR2Reg();
  high = (unsigned) getR1Reg();
#endif
    
    Ck(theItem); Ck(theRep);
    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if (low < theRep->LowBorder) BetaError(RepLowRangeErr, theItem);
    if (high > theRep->HighBorder) BetaError(RepHighRangeErr, theItem);
    
    /* Calculate the range of the new repetition. */
    high =  (high - low) + 1;
    if (high < 0) high = 0;

    /* LVRA missing */
    
    Protect2(theRep,theItem,newRep = cast(ValRep) IOAalloc(DispatchValRepSize(theRep->Proto, high)));
    
    Ck(theRep); Ck(theItem);

    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = high;
    
    /* Copy the body part of the repetition. */
    switch ( (long) theRep->Proto){
      case (long) ByteRepPTValue:
	{ /* Since the slice may start on any byte we copy it byte by byte */
	    unsigned char *newBody= (unsigned char *)newRep->Body;
	    unsigned char *oldBody= (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
	    for (i = 0;  i < high; ++(unsigned char *)i)
	      *(unsigned char *)((unsigned)newBody+i) = *(unsigned char *)((unsigned)oldBody+i);
	    *(unsigned char *)((unsigned)newBody+high) = 0
	      /* Null termination */;
	    break;
	}
      case (long) WordRepPTValue:
	{ /* Since the slice may start on any word we copy it word by word */
	    short *newBody= (short *)newRep->Body;
	    short *oldBody= (short *)((unsigned)theRep->Body+(low-theRep->LowBorder));
	    for (i = 0;  i < high; ++(short *)i)
	      *(short *)((unsigned)newBody+i) = *(short *)((unsigned)oldBody+i);
	    break;
	}
      case (long) ValRepPTValue:
	for (i = 0; i < high; ++(long *)i)
	  newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
	break;
      case (long) DoubleRepPTValue:
	for (i = 0; i < high; ++(long *)i){
	    newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
	    newRep->Body[2*i] = theRep->Body[2*i+low-theRep->LowBorder];
	}
	break;
      default:
	fprintf(output, "CopySliceValRep: wrong prototype\n");
	exit(1);
    }
    
    /* stack[8] -> theItem;
     * stack[4] -> offset
     */
    
    AssignReference((long *)theItem + offset, cast(Item) newRep);
}


