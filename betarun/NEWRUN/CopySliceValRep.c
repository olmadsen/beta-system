/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

void CopySVR1(struct ValRep *theRep,
	      struct Item *theItem,
	      unsigned offset, /* in longs */
	      unsigned low,
	      unsigned high,
	      long *SP
	      )
{
  struct ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR1++);

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
    
    DEBUG_LVRA(fprintf(output, "CopySVR1 allocates in LVRA\n"));
    
    newRep = (struct ValRep *)LVRAAlloc(ByteRepPTValue, range);
    
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
		     "CopySVR1: lvra structure ok"));
    /* Make the LVRA-cycle: theCell -> newRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theItem + offset);
    *(struct ValRep **)((long *)theItem + offset) = newRep;
  } else{
    /* Allocate in IOA/AOA */
    size  = ByteRepSize(range);
    
    push(theItem);
    push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopySVR1 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAalloc failed\n"));
    }
    if (newRep) {
      newRep->GCAttr = 0; /* In AOA */
    } else {
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
    pop(theRep);
    pop(theItem);
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = ByteRepPTValue;
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
  }
  
  /* Copy the body part of the repetition. */
  { /* Since the slice may start on any byte we copy it byte by byte */
    unsigned char *newBody= (unsigned char *)newRep->Body;
    unsigned char *oldBody= (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
    for (i=0;  i<range; ++i){
      *(unsigned char *)((unsigned)newBody+i) 
	= *(unsigned char *)((unsigned)oldBody+i);
    }
    /* Null termination */
    *(unsigned char *)((unsigned)newBody+range) = 0;
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)newRep);

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR1 */

void CopySVR2(struct ValRep *theRep,
	      struct Item *theItem,
	      unsigned offset, /* in longs */
	      unsigned low,
	      unsigned high,
	      long *SP
	      )
{
  struct ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR2++);

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
    
    DEBUG_LVRA(fprintf(output, "CopySVR2 allocates in LVRA\n"));
    
    newRep = (struct ValRep *)LVRAAlloc(ShortRepPTValue, range);
    
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
		     "CopySVR2: lvra structure ok"));
    /* Make the LVRA-cycle: theCell -> newRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theItem + offset);
    *(struct ValRep **)((long *)theItem + offset) = newRep;
  } else{
    /* Allocate in IOA/AOA */
    size  = ShortRepSize(range);
    
    push(theItem);
    push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopySVR2 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAalloc failed\n"));
    }
    if (newRep) {
      newRep->GCAttr = 0; /* In AOA */
    } else {
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
    pop(theRep);
    pop(theItem);
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = ShortRepPTValue;
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
  }
  
  /* Copy the body part of the repetition. */
  { /* Since the slice may start on any word we copy it word by word */
    short *newBody=(short *)newRep->Body;
    short *oldBody=(short *)((unsigned)theRep->Body+2*(low-theRep->LowBorder));
    for (i = 0;  i < range; ++i){
      *(short *)((unsigned)newBody+2*i) = *(short *)((unsigned)oldBody+2*i);
    }
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)newRep);
  
  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR2 */


void CopySVR4(struct ValRep *theRep,
	      struct Item *theItem,
	      unsigned offset, /* in longs */
	      unsigned low,
	      unsigned high,
	      long *SP
	      )
{
  struct ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR4++);

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
    
    DEBUG_LVRA(fprintf(output, "CopySVR4 allocates in LVRA\n"));
    
    newRep = (struct ValRep *)LVRAAlloc(LongRepPTValue, range);
    
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
		     "CopySVR4: lvra structure ok"));
    /* Make the LVRA-cycle: theCell -> newRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theItem + offset);
    *(struct ValRep **)((long *)theItem + offset) = newRep;
  } else{
    /* Allocate in IOA/AOA */
    size  = LongRepSize(range);
    
    push(theItem);
    push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopySVR4 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAalloc failed\n"));
    }
    if (newRep) {
      newRep->GCAttr = 0; /* In AOA */
    } else {
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
    pop(theRep);
    pop(theItem);
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = LongRepPTValue;
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
  }
  
  /* Copy the body part of the repetition. */
  for (i = 0; i < range; ++i){
    newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
  }  
  
  AssignReference((long *)theItem + offset, (struct Item *)newRep);

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR4 */


void CopySVR8(struct ValRep *theRep,
	      struct Item *theItem,
	      unsigned offset, /* in longs */
	      unsigned low,
	      unsigned high,
	      long *SP
	      )
{
  struct ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR8++);

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
    
    DEBUG_LVRA(fprintf(output, "CopySVR8 allocates in LVRA\n"));
    
    newRep = (struct ValRep *)LVRAAlloc(DoubleRepPTValue, range);
    
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
		     "CopySVR8: lvra structure ok"));
    /* Make the LVRA-cycle: theCell -> newRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theItem + offset);
    *(struct ValRep **)((long *)theItem + offset) = newRep;
  } else{
    /* Allocate in IOA/AOA */
    size  = DoubleRepSize(range);
    
    push(theItem);
    push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopySVR8 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!theRep) fprintf(output, "AOAalloc failed\n"));
    }
    if (newRep) {
      newRep->GCAttr = 0; /* In AOA */
    } else {
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
    pop(theRep);
    pop(theItem);
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = DoubleRepPTValue;
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
  }
  
  /* Copy the body part of the repetition. */
  { double *newBody=(double*)newRep->Body;
    double *oldBody=(double*)((unsigned)theRep->Body+8*(low-theRep->LowBorder));
    for (i = 0;  i < range; ++i){
      *(double *)((unsigned)newBody+8*i) = *(double *)((unsigned)oldBody+8*i);
    }
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)newRep);

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR8 */



void CopySVRI(struct ObjectRep *theRep,
	      struct Item *theItem,
	      unsigned offset, /* in longs */
	      unsigned low,
	      unsigned high,
	      long *SP
	      )
{
  struct ObjectRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVRI++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of an Object Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
    BetaError(RepLowRangeErr, GetThis(SP), SP, 0);
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
    BetaError(RepHighRangeErr, GetThis(SP), SP, 0);
  
  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  size = DynObjectRepSize(range);
  push(theRep); 
  push(theItem);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "CopySVRI allocates in AOA\n"));
    newRep = (struct ObjectRep *)AOAalloc(size, SP);
    DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
  } 
  if (newRep){
    newRep->GCAttr = 0; /* In AOA */
  } else {
    newRep = (struct ObjectRep *)IOAalloc(size, SP);
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
  }
  pop(theItem);
  pop(theRep);
  
  newRep->Proto = DynItemRepPTValue;
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = 1;
  newRep->HighBorder = range;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  newRep->iProto = theRep->iProto;

  /* Copy the body part of the repetition. */
  for (i = 0; i < range; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i+low-theRep->LowBorder]);
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)newRep);

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVRI */


void CopySVRC(struct ObjectRep *theRep,
	      struct Item *theItem,
	      unsigned offset, /* in longs */
	      unsigned low,
	      unsigned high,
	      long *SP
	      )
{
  struct ObjectRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVRC++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of an Object Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) 
    BetaError(RepLowRangeErr, GetThis(SP), SP, 0);
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) 
    BetaError(RepHighRangeErr, GetThis(SP), SP, 0);
  
  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  size = DynObjectRepSize(range);
  push(theRep); 
  push(theItem);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "CopySVRC allocates in AOA\n"));
    newRep = (struct ObjectRep *)AOAalloc(size, SP);
    DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
  } 
  if (newRep){
    newRep->GCAttr = 0; /* In AOA */
  } else {
    newRep = (struct ObjectRep *)IOAalloc(size, SP);
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
  }
  pop(theItem);
  pop(theRep);
  
  newRep->Proto = DynCompRepPTValue;
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = 1;
  newRep->HighBorder = range;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  newRep->iProto = theRep->iProto;

  /* Copy the body part of the repetition. */
  for (i = 0; i < range; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i+low-theRep->LowBorder]);
  }
  
  AssignReference((long *)theItem + offset, (struct Item *)newRep);

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVRC */


