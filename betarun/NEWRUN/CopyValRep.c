/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */


#include "beta.h"
#include "crun.h"

void CopyVR1(struct ValRep *theRep,
	     struct Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    struct ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR1++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = ByteRepSize(range);
    
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      newRep = LVRAAlloc(ByteRepPTValue, range);
    } else {
      /* Allocate newRep in IOA */
      push(theObj);
      push(theRep);
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      pop(theRep);
      pop(theObj);
      
      newRep->Proto = ByteRepPTValue;
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (struct Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR1 */

void CopyVR2(struct ValRep *theRep,
	     struct Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    struct ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR2++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = ShortRepSize(range);
    
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      newRep = LVRAAlloc(ShortRepPTValue, range);
    } else {
      /* Allocate newRep in IOA */
      push(theObj);
      push(theRep);
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      pop(theRep);
      pop(theObj);
      
      newRep->Proto = ShortRepPTValue;
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (struct Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR2 */

void CopyVR4(struct ValRep *theRep,
	     struct Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    struct ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR2++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = LongRepSize(range);
    
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE) {
      newRep = LVRAAlloc(LongRepPTValue, range);
    } else {
      /* Allocate newRep in IOA */
      push(theObj);
      push(theRep);
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      pop(theRep);
      pop(theObj);
      
      newRep->Proto = LongRepPTValue;
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (struct Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR4 */

void CopyVR8(struct ValRep *theRep,
	     struct Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    struct ValRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVR8++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = DoubleRepSize(range);
    
    if (range > LARGE_REP_SIZE || size>IOAMAXSIZE){
      newRep = LVRAAlloc(DoubleRepPTValue, range);
    } else {
      /* Allocate newRep in IOA */
      push(theObj);
      push(theRep);
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
      pop(theRep);
      pop(theObj);
      
      newRep->Proto = DoubleRepPTValue;
      /* newRep->GCAttr set above */
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }

    size -= headsize(ValRep); /* adjust size to be bodysize */

    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, (struct Item *)newRep);
    
    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVR8 */



void CopyVRI(struct ObjectRep *theRep,
	     struct Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    struct ObjectRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVRI++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = DynObjectRepSize(range);
      
    push(theObj);
    push(theRep); 
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopyVRI allocates in AOA\n"));
      newRep = (struct ObjectRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
    } else {
      newRep = (struct ObjectRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
    pop(theRep);
    pop(theObj);
      
    newRep->Proto = DynItemRepPTValue;
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
        
    AssignReference((long *)theObj + offset, (struct Item *)newRep);

    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVRI */


void CopyVRC(struct ObjectRep *theRep,
	     struct Object *theObj,
	     unsigned offset /* in longs */,
	     long *SP
	     )
{
    struct ObjectRep * newRep=0;
    register unsigned long range, i, size;
   
    DEBUG_CODE(NumCopyVRC++);

    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;

    size = DynObjectRepSize(range);
      
    push(theObj);
    push(theRep); 
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "CopyVRC allocates in AOA\n"));
      newRep = (struct ObjectRep *)AOAalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
    } else {
      newRep = (struct ObjectRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge; /* In IOA */
    }
    pop(theRep);
    pop(theObj);
      
    newRep->Proto = DynCompRepPTValue;
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
        
    AssignReference((long *)theObj + offset, (struct Item *)newRep);

    Ck(theObj); Ck(theRep); Ck(newRep);

} /* CopyVRI */
