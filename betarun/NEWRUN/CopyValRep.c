/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */


#include "beta.h"
#include "crun.h"

void CopyVR1(ValRep *theRep,
	     Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR1++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = ByteRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
	newRep = LVRAAlloc(ByteRepPTValue, range);
      } 
      if (!newRep) {
	/* Allocate newRep in IOA */
	push(theObj);
	push(theRep);
	newRep = (ValRep *)IOATryAlloc(size, SP);
	pop(theRep);
	pop(theObj);
	if (newRep) {
	  if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
	  
	  SETPROTO(newRep, ByteRepPTValue);
	  /* newRep->GCAttr set above */
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	  break;
	}
      }
    } while (!newRep);

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR1 */

void CopyVR2(ValRep *theRep,
	     Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR2++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = ShortRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
	newRep = LVRAAlloc(ShortRepPTValue, range);
      } 
      if (!newRep) {
	/* Allocate newRep in IOA */
	push(theObj);
	push(theRep);
	newRep = (ValRep *)IOATryAlloc(size, SP);
	pop(theRep);
	pop(theObj);
	if (newRep) {
	  if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
	  
	  SETPROTO(newRep, ShortRepPTValue);
	  /* newRep->GCAttr set above */
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}
      }
    } while (!newRep);

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR2 */

void CopyVR4(ValRep *theRep,
	     Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR2++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = LongRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
	newRep = LVRAAlloc(LongRepPTValue, range);
      } 
      if (!newRep) {
	/* Allocate newRep in IOA */
	push(theObj);
	push(theRep);
	newRep = (ValRep *)IOATryAlloc(size, SP);
	pop(theRep);
	pop(theObj);
	if (newRep) {
	  if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
	  
	  SETPROTO(newRep, LongRepPTValue);
	  /* newRep->GCAttr set above */
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}
      }
    } while (!newRep);

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR4 */

void CopyVR8(ValRep *theRep,
	     Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR8++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = DoubleRepSize(range);
    
    do {
      if (range > LARGE_REP_SIZE || size>IOAMAXSIZE){
	newRep = LVRAAlloc(DoubleRepPTValue, range);
      } 
      if (!newRep) {
	/* Allocate newRep in IOA */
	push(theObj);
	push(theRep);
	newRep = (ValRep *)IOATryAlloc(size, SP);
	pop(theRep);
	pop(theObj);
	if (newRep) {
	  if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
	  
	  SETPROTO(newRep, DoubleRepPTValue);
	  /* newRep->GCAttr set above */
	  newRep->LowBorder = 1;
	  newRep->HighBorder = range;
	}
      }
    } while (!newRep);

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR8 */



void CopyVRI(ObjectRep *theRep,
	     Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    ObjectRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVRI++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = DynObjectRepSize(range);
      
    push(theObj);
    push(theRep); 
    do {
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVRI allocates in AOA\n"));
	newRep = (ObjectRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      } 
      if (!newRep) {
	newRep = (ObjectRep *)IOATryAlloc(size, SP);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!newRep);
    pop(theRep);
    pop(theObj);
      
    SETPROTO(newRep, DynItemRepPTValue);
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    AssignReference(&newRep->iOrigin, theRep->iOrigin);
    newRep->iProto = theRep->iProto;

    size -= headsize(ObjectRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      AssignReference(&newRep->Body[i], theRep->Body[i]);
    }
        
    AssignReference((long *)theObj + offset, (Item *)newRep);

    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVRI */


void CopyVRC(ObjectRep *theRep,
	     Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    ObjectRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVRC++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = DynObjectRepSize(range);
      
    push(theObj);
    push(theRep); 
    do {
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVRC allocates in AOA\n"));
	newRep = (ObjectRep *)AOAalloc(size);
	DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
      } 
      if (!newRep) {
	newRep = (ObjectRep *)IOATryAlloc(size, SP);
	if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      }
    } while (!newRep);
    pop(theRep);
    pop(theObj);
      
    SETPROTO(newRep, DynCompRepPTValue);
    /* newRep->GCAttr set above */
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    AssignReference(&newRep->iOrigin, theRep->iOrigin);
    newRep->iProto = theRep->iProto;

    size -= headsize(ObjectRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      AssignReference(&newRep->Body[i], theRep->Body[i]);
    }
        
    AssignReference((long *)theObj + offset, (Item *)newRep);

    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVRI */
