/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

void CCopySVR1(ValRep *theRep,
	       Item *theItem,
	       unsigned offset, /* in longs */
	       unsigned low,
	       unsigned high,
	       long *SP
	       )
{
  ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR1++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of a Value Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
  }
  
  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  while (1) {
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      /* newRep allocated in AOA */
      newRep = (ValRep *)LVRAAlloc(ByteRepPTValue, range);
      if (newRep) {
	*(ValRep **)((long *)theItem + offset) = newRep;
	break;
      }
    } 
    
    /* Allocate in IOA */
    size  = ByteRepSize(range);
    
    push(theItem);
    push(theRep); 
    newRep = (ValRep *)IOATryAlloc(size, SP);
    pop(theRep);
    pop(theItem);
    if (newRep) {
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      /* Initialize the structual part of the repetition. */
      SETPROTO(newRep, ByteRepPTValue);
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
      
      AssignReference((long *)theItem + offset, (Item *)newRep);
      break;
    }
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

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR1 */

void CCopySVR2(ValRep *theRep,
	       Item *theItem,
	       unsigned offset, /* in longs */
	       unsigned low,
	       unsigned high,
	       long *SP
	       )
{
  ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR2++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of a Value Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
  }
  
  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  while (1) {
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      newRep = (ValRep *)LVRAAlloc(ShortRepPTValue, range);
      if (newRep) {
	*(ValRep **)((long *)theItem + offset) = newRep;
	break;
      }
    } 

    /* Allocate in IOA */
    size  = ShortRepSize(range);
    
    push(theItem);
    push(theRep); 
    newRep = (ValRep *)IOATryAlloc(size, SP);
    pop(theRep);
    pop(theItem);
    if (newRep) {
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      /* Initialize the structual part of the repetition. */
      SETPROTO(newRep, ShortRepPTValue);
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
      
      AssignReference((long *)theItem + offset, (Item *)newRep);
      break;
    }
  }
  
  /* Copy the body part of the repetition. */
  { /* Since the slice may start on any word we copy it word by word */
      short *newBody=(short *)newRep->Body;
      short *oldBody=(short *)((unsigned)theRep->Body+2*(low-theRep->LowBorder));
      for (i = 0;  i < range; ++i){
          *(short *)((unsigned)newBody+2*i) = *(short *)((unsigned)oldBody+2*i);
      }
  }
  
  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR2 */


void CCopySVR4(ValRep *theRep,
	       Item *theItem,
	       unsigned offset, /* in longs */
	       unsigned low,
	       unsigned high,
	       long *SP
	       )
{
  ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR4++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of a Value Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
  }

  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  while (1) {
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      newRep = (ValRep *)LVRAAlloc(LongRepPTValue, range);
      if (newRep) {
	*(ValRep **)((long *)theItem + offset) = newRep;
	break;
      }
    } 
    
    /* Allocate in IOA */
    size  = LongRepSize(range);
    
    push(theItem);
    push(theRep);
    newRep = (ValRep *)IOATryAlloc(size, SP);
    pop(theRep);
    pop(theItem);
    if (newRep) {
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      
      /* Initialize the structual part of the repetition. */
      SETPROTO(newRep, LongRepPTValue);
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
      
      AssignReference((long *)theItem + offset, (Item *)newRep);
      break;
    }
  }
  
  /* Copy the body part of the repetition. */
  for (i = 0; i < range; ++i){
    newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
  }  

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR4 */


void CCopySVR8(ValRep *theRep,
	       Item *theItem,
	       unsigned offset, /* in longs */
	       unsigned low,
	       unsigned high,
	       long *SP
	       )
 {
  ValRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVR8++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of a Value Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
  }

  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  while (1) {
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      newRep = (ValRep *)LVRAAlloc(DoubleRepPTValue, range);
      if (newRep) {
	*(ValRep **)((long *)theItem + offset) = newRep;
	break;
      }
    } 

    /* Allocate in IOA */
    size  = DoubleRepSize(range);
    
    push(theItem);
    push(theRep);
    newRep = (ValRep *)IOATryAlloc(size, SP);
    pop(theRep);
    pop(theItem);
    if (newRep) {
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      
      /* Initialize the structual part of the repetition. */
      SETPROTO(newRep, DoubleRepPTValue);
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
      
      AssignReference((long *)theItem + offset, (Item *)newRep);
      break;
    }
  }
  
  /* Copy the body part of the repetition. */
  {
      double *newBody=(double*)newRep->Body;
      double *oldBody=(double*)((unsigned)theRep->Body+8*(low-theRep->LowBorder));
      for (i = 0;  i < range; ++i) {
          *(double *)((unsigned)newBody+8*i) = *(double *)((unsigned)oldBody+8*i);
      }
  }

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVR8 */


void CCopySVRI(ObjectRep *theRep,
	       Item *theItem,
	       unsigned offset, /* in longs */
	       unsigned low,
	       unsigned high,
	       long *SP
	       )
{
  ObjectRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVRI++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of an Object Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
  }
 
  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  size = DynObjectRepSize(range);
  push(theRep); 
  push(theItem);
  do {
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopySVRI allocates in AOA\n"));
      newRep = (ObjectRep *)AOAalloc(size);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
    } 
    if (!newRep){
      newRep = (ObjectRep *)IOATryAlloc(size, SP);
      if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
  } while (!newRep);
  pop(theItem);
  pop(theRep);
  
  SETPROTO(newRep, DynItemRepPTValue);
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = 1;
  newRep->HighBorder = range;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  newRep->iProto = theRep->iProto;

  /* Copy the body part of the repetition. */
  for (i = 0; i < range; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i+low-theRep->LowBorder]);
  }
  
  AssignReference((long *)theItem + offset, (Item *)newRep);

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVRI */

void CCopySVRC(ObjectRep *theRep,
	       Item *theItem,
	       unsigned offset, /* in longs */
	       unsigned low,
	       unsigned high,
	       long *SP
	       )
{
  ObjectRep *newRep=0;
  register long i, size, range;
  
  DEBUG_CODE(NumCopySVRC++);

  Ck(theItem); Ck(theRep);

  /* Copy a slice of an Object Repetition. */
  
  /* Check that low and high are usable. */
  if ( (low < theRep->LowBorder) /* || (theRep->HighBorder < low) */ ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepLowRangeErr, 0, SP, 0);
  }
  if ( /* (high < theRep->LowBorder) || */ (theRep->HighBorder < high) ) {
    SubRangeErrLow = low;
    SubRangeErrHigh = high;
    RangeMax = theRep->HighBorder;
    BetaError(RepHighRangeErr, 0, SP, 0);
  }

  /* Calculate the range of the new repetition. */
  range =  (high - low) + 1;
  if (range < 0) range = 0;

  size = DynObjectRepSize(range);
  push(theRep); 
  push(theItem);

  do {
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopySVRC allocates in AOA\n"));
      newRep = (ObjectRep *)AOAalloc(size);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
    } 
    if (!newRep){
      newRep = (ObjectRep *)IOATryAlloc(size, SP);
      if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
  } while (!newRep);
  pop(theItem);
  pop(theRep);
  
  SETPROTO(newRep, DynCompRepPTValue);
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = 1;
  newRep->HighBorder = range;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  newRep->iProto = theRep->iProto;

  /* Copy the body part of the repetition. */
  for (i = 0; i < range; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i+low-theRep->LowBorder]);
  }
  
  AssignReference((long *)theItem + offset, (Item *)newRep);

  Ck(theRep); Ck(theItem); Ck(newRep);

} /* CopySVRC */


