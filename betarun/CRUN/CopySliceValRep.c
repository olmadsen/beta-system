#ifdef hppa
#undef RTDEBUG /* Sorry. The new gcc complains about getR2Reg()  */
#endif

/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
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
	ba	"CPREF"CopySVR
	mov	%l6, %o4
");

#ifdef hppa
#  define CCopySVR CopySVR
#endif

void CCopySVR(ref(ValRep) theRep,
	      ref(Item) theItem,
	      unsigned offset, /* in ints */
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
    if (low < theRep->LowBorder) 
      BetaError(RepLowRangeErr, cast(Object)theItem);
    if (high > theRep->HighBorder) 
      BetaError(RepHighRangeErr, cast(Object)theItem);
    
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
	    for (i = 0;  i < high; ++i)
	      *(unsigned char *)((unsigned)newBody+i) = *(unsigned char *)((unsigned)oldBody+i);
	    *(unsigned char *)((unsigned)newBody+high) = 0
	      /* Null termination */;
	    break;
	}
      case (long) WordRepPTValue:
	{ /* Since the slice may start on any word we copy it word by word */
	    short *newBody= (short *)newRep->Body;
	    short *oldBody= (short *)((unsigned)theRep->Body+2*(low-theRep->LowBorder));
	    for (i = 0;  i < high; ++i)
	      *(short *)((unsigned)newBody+2*i) = *(short *)((unsigned)oldBody+2*i);
	    break;
	}
      case (long) ValRepPTValue:
	for (i = 0; i < high; ++i){
	  newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
	}
	break;
      case (long) DoubleRepPTValue:
	{   double *newBody= (double *)newRep->Body;
	    double *oldBody= (double *)((unsigned)theRep->Body+8*(low-theRep->LowBorder));
	    for (i = 0;  i < high; ++i)
	      *(double *)((unsigned)newBody+8*i) = *(double *)((unsigned)oldBody+8*i);
	    break;
	}
	break;
      default:
	fprintf(output, "CopySliceValRep: wrong prototype\n");
	exit(1);
    }
        
    AssignReference((long *)theItem + offset, cast(Item) newRep);
}


