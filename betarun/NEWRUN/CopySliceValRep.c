/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

#define REP ((struct ObjectRep *)theRep)
#define NEWREP ((struct ObjectRep *)newRep)

void CopySVR(struct ValRep *theRep,
	     struct Item *theItem,
	     unsigned offset, /* in ints */
	     unsigned low,
	     unsigned high,
	     long *SP
	     )
{
    struct ValRep *newRep;
    register long i, size, range;
    
    DEBUG_CODE(NumCopySVR++);

    Ck(theItem); Ck(theRep);
    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if (low < theRep->LowBorder) 
      BetaError(RepLowRangeErr, GetThis(SP), SP);
    if (high > theRep->HighBorder) 
      BetaError(RepHighRangeErr, GetThis(SP), SP);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    switch((long)theRep->Proto){
    case (long) ByteRepPTValue:
      size = ByteRepSize(range); break;
    case (long) ValRepPTValue:
      size = ValRepSize(range); break;
    case (long) DoubleRepPTValue:
      size = DoubleRepSize(range); break;
    case (long) WordRepPTValue:
      size = WordRepSize(range); break;
    case (long) DynItemRepPTValue:
    case (long) DynCompRepPTValue:
      size = DynObjectRepSize(range); break;
#ifdef STATIC_OBJECT_REPETITIONS
    case (long) StatItemRepPTValue:
      size = StatItemRepSize(range, REP->iProto); break;
    case (long) StatCompRepPTValue:
      size = StatCompRepSize(range, REP->iProto); break;
#endif /* STATIC_OBJECT_REPETITIONS */
    default:
      fprintf(output, "CopySliceValRep: unknown repetition\n");
      size=0;
    }

    /* LVRA missing */
    
    Protect2(theRep,theItem,newRep = (struct ValRep *)IOAalloc(size, SP));
    
    Ck(theRep); Ck(theItem);

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
    switch ( (long) theRep->Proto){
      case (long) ByteRepPTValue:
	{ /* Since the slice may start on any byte we copy it byte by byte */
	    unsigned char *newBody= (unsigned char *)newRep->Body;
	    unsigned char *oldBody= (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
	    for (i = 0;  i < range; ++i)
	      *(unsigned char *)((unsigned)newBody+i) = *(unsigned char *)((unsigned)oldBody+i);
	    *(unsigned char *)((unsigned)newBody+range) = 0
	      /* Null termination */;
	}
	break;
      case (long) WordRepPTValue:
	{ /* Since the slice may start on any word we copy it word by word */
	    short *newBody= (short *)newRep->Body;
	    short *oldBody= (short *)((unsigned)theRep->Body+2*(low-theRep->LowBorder));
	    for (i = 0;  i < range; ++i)
	      *(short *)((unsigned)newBody+2*i) = *(short *)((unsigned)oldBody+2*i);
	}
	break;
      case (long) ValRepPTValue:
	for (i = 0; i < range; ++i){
	  newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
	}
	break;
      case (long) DoubleRepPTValue:
	{   double *newBody= (double *)newRep->Body;
	    double *oldBody= (double *)((unsigned)theRep->Body+8*(low-theRep->LowBorder));
	    for (i = 0;  i < range; ++i)
	      *(double *)((unsigned)newBody+8*i) = *(double *)((unsigned)oldBody+8*i);
	  }
	break;
      case (long) DynItemRepPTValue:
      case (long) DynCompRepPTValue:
	for (i = 0; i < range; ++i){
	  NEWREP->Body[i] = REP->Body[i+low-theRep->LowBorder];
	  /* No need to use AssignReference: NEWREP is in IOA */
	}
	break;
#ifdef STATIC_OBJECT_REPETITIONS
      case (long) StatItemRepPTValue:
	/* copy as longs */
	for (i = 0; i < range*ItemSize(REP->iProto)/4; ++i)
	  NEWREP->Body[i] 
	    = REP->Body[i+(low-theRep->LowBorder)*ItemSize(REP->iProto)/4];
	break;
      case (long) StatCompRepPTValue:
	/* copy as longs */
	for (i = 0; i < range*ComponentSize(REP->iProto)/4; ++i)
	  NEWREP->Body[i] 
	    = REP->Body[i+(low-theRep->LowBorder)*ComponentSize(REP->iProto)/4];
	break;
#endif /* STATIC_OBJECT_REPETITIONS */

      default:
	Notify("CopySliceValRep: wrong prototype");
	exit(1);
    }
        
    AssignReference((long *)theItem + offset, (struct Item *)newRep);
}


