#ifdef hppa
#undef RTDEBUG /* Sorry. The new gcc complains about getR2Reg()  */
#endif

/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#define REP ((struct ObjectRep *)theRep)
#define NEWREP ((struct ObjectRep *)newRep)

#ifdef hppa
register long _dummy8 asm("%r15"); /* really tmp data 1 */
register long _dummy9 asm("%r16"); /* really tmp data 2 */
#endif

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef sparc
asmlabel(CopySVR, "
	mov	%l7, %o3
	ba	"CPREF"CopySVR
	mov	%l6, %o4
");
#else
#define CCopySVR CopySVR
#endif

void CCopySVR(ref(ValRep) theRep,
	      ref(Item) theItem,
	      unsigned offset, /* in ints */
	      unsigned low,
	      long      high
	      )
{
    DeclReference1(struct ValRep *, newRep);
    register long i, size, range;
    
    GCable_Entry();

#ifdef hppa
  low = (unsigned) getR2Reg();
  high = (unsigned) getR1Reg();
#endif
    
    DEBUG_CODE(NumCopySVR++);
    Ck(theItem); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, cast(Object)theItem);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
       BetaError(RepHighRangeErr, cast(Object)theItem);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    switch(SwitchProto(theRep->Proto)){
    case SwitchProto(ByteRepPTValue):
      size = ByteRepSize(range); break;
    case SwitchProto(LongRepPTValue):
      size = LongRepSize(range); break;
    case SwitchProto(DoubleRepPTValue):
      size = DoubleRepSize(range); break;
    case SwitchProto(ShortRepPTValue):
      size = ShortRepSize(range); break;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      size = DynObjectRepSize(range); break;
    default:
      fprintf(output, "CopySliceValRep: unknown repetition\n");
      size=0;
    }

    /* LVRA missing */
    
    Protect2(theRep,theItem,newRep = cast(ValRep) IOAalloc(size));
    
    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;

    if (isObjectRep(theRep)){
      NEWREP->iOrigin = REP->iOrigin;
      NEWREP->iProto = REP->iProto;
    }

    /* Copy the body part of the repetition. */
    switch (SwitchProto(theRep->Proto)){
      case SwitchProto(ByteRepPTValue):
	{ /* Since the slice may start on any byte we copy it byte by byte */
	    unsigned char *newBody= (unsigned char *)newRep->Body;
	    unsigned char *oldBody= (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
	    for (i = 0;  i < range; ++i)
	      *(unsigned char *)((unsigned)newBody+i) = *(unsigned char *)((unsigned)oldBody+i);
	    *(unsigned char *)((unsigned)newBody+range) = 0
	      /* Null termination */;
	}
	break;
      case SwitchProto(ShortRepPTValue):
	{ /* Since the slice may start on any word we copy it word by word */
	    short *newBody= (short *)newRep->Body;
	    short *oldBody= (short *)((unsigned)theRep->Body+2*(low-theRep->LowBorder));
	    for (i = 0;  i < range; ++i)
	      *(short *)((unsigned)newBody+2*i) = *(short *)((unsigned)oldBody+2*i);
	}
	break;
      case SwitchProto(LongRepPTValue):
	for (i = 0; i < range; ++i){
	  newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
	}
	break;
      case SwitchProto(DoubleRepPTValue):
	{   double *newBody= (double *)newRep->Body;
	    double *oldBody= (double *)((unsigned)theRep->Body+8*(low-theRep->LowBorder));
	    for (i = 0;  i < range; ++i)
	      *(double *)((unsigned)newBody+8*i) = *(double *)((unsigned)oldBody+8*i);
	  }
	break;
      case SwitchProto(DynItemRepPTValue):
      case SwitchProto(DynCompRepPTValue):
	for (i = 0; i < range; ++i){
	  NEWREP->Body[i] = REP->Body[i+low-theRep->LowBorder];
	  /* No need to use AssignReference: NEWREP is in IOA */
	}
	break;

      default:
	Notify("CopySliceValRep: wrong prototype");
	BetaExit(1);
    }
        
    AssignReference((long *)theItem + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theItem);

}


