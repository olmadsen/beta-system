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
	     unsigned offset, /* in longs */
	     unsigned low,
	     unsigned high,
	     long *SP
	     )
{
    struct ValRep *newRep=0;
    register long i, size, range;
    
    DEBUG_CODE(NumCopySVR++);

    Ck(theItem); Ck(theRep);

    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
      BetaError(RepLowRangeErr, GetThis(SP), SP, 0);
    if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
      BetaError(RepHighRangeErr, GetThis(SP), SP, 0);
    
    /* Calculate the range of the new repetition. */
    range =  (high - low) + 1;
    if (range < 0) range = 0;

    if (isValRep(theRep)){
      if (range > LARGE_REP_SIZE) {
	/* Allocate in LVRA */
	long *cycleCell = 0;
	
	if (!inIOA(theRep)) {
	  /* theRep is in LVRA (it cannot be in AOA, cf. NewCopyObject). 
	   * If LVRAAlloc causes an LVRACompaction
	   * the value of theRep may be wrong after LVRAAlloc: this is the case
	   * if the repetition pointed to by theRep was moved. To prevent this,
	   * the cell actually referencing the repetition is remembered. This 
	   * cell will be updated if the repetition is moved.
	   */
	  cycleCell = (long *)theRep->GCAttr; /* Cell that references theRep */
	}
	
	DEBUG_LVRA(fprintf(output, "CopySVR allocates in LVRA\n"));
	
	newRep = (struct ValRep *)LVRAAlloc(theRep->Proto, range);
	
	if (cycleCell) {
	  /* theRep was in LVRA. Since it may have been moved by
	   * LVRACompaction, we update it.
	   */
	  theRep = (struct ValRep *)*cycleCell;
	}
      }
      
      if (newRep) {
	/* newRep allocated in LVRA */
	DEBUG_CODE(Claim(newRep->HighBorder==range&&newRep->LowBorder==1, 
			 "CopySVR: lvra structure ok"));
	/* Make the LVRA-cycle: theCell -> newRep.GCAttr */
	newRep->GCAttr = (long) ((long *) theItem + offset);
	*(struct ValRep **)((long *)theItem + offset) = newRep;
      } else{
	/* Allocate in IOA/AOA */
	size  = DispatchValRepSize(theRep->Proto, range);

	push(theItem);
	push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
	if (size>IOAMAXSIZE){
	  DEBUG_AOA(fprintf(output, "CopySVR allocates in AOA\n"));
	  newRep = (struct ValRep *)AOAalloc(size, SP);
	  DEBUG_AOA(if (!theRep) fprintf(output, "AOAalloc failed\n"));
	}
	if (newRep) {
	  newRep->GCAttr = 0; /* In AOA */
	} else {
	  newRep = (struct ValRep *)IOAalloc(size, SP);
	  newRep->GCAttr = 1; /* In IOA */
	}
	pop(theRep);
	pop(theItem);
	
	/* Initialize the structual part of the repetition. */
	newRep->Proto = theRep->Proto;
	/* newRep->GCAttr set above */
	newRep->LowBorder = 1;
	newRep->HighBorder = range;
      }
    } else {
      /* Object rep */
      size = DispatchObjectRepSize(theRep->Proto, range, REP->iProto);
      push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
      push(theItem);
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopySVR allocates in AOA\n"));
	newRep = (struct ValRep *)AOAalloc(size, SP);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      } 
      if (newRep){
	newRep->GCAttr = 0; /* In AOA */
      } else {
	newRep = (struct ValRep *)IOAalloc(size, SP);
	newRep->GCAttr = 1; /* In IOA */
      }
      pop(theItem);
      pop(theRep);

      newRep->Proto = theRep->Proto;
      /* newRep->GCAttr set above if in IOA */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
      AssignReference(&NEWREP->iOrigin, REP->iOrigin);
      NEWREP->iProto = REP->iProto;
    }

    /* Copy the body part of the repetition. */
    switch(SwitchProto(theRep->Proto)){
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
      case SwitchProto(WordRepPTValue):
	{ /* Since the slice may start on any word we copy it word by word */
	    short *newBody= (short *)newRep->Body;
	    short *oldBody= (short *)((unsigned)theRep->Body+2*(low-theRep->LowBorder));
	    for (i = 0;  i < range; ++i)
	      *(short *)((unsigned)newBody+2*i) = *(short *)((unsigned)oldBody+2*i);
	}
	break;
      case SwitchProto(ValRepPTValue):
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
	  AssignReference(&NEWREP->Body[i], REP->Body[i+low-theRep->LowBorder]);
	}
	break;
#ifdef RTDEBUG
      default:
	Notify("CopySliceValRep: wrong prototype");
	BetaExit(1);
#endif
    }
        
    AssignReference((long *)theItem + offset, (struct Item *)newRep);

    Ck(theRep); Ck(theItem); Ck(newRep);

}


