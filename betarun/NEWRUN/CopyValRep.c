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
    
    if (range > LARGE_REP_SIZE){
      /* newRep should go into LVRA */
      long *cycleCell  = 0;
      
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
      
      DEBUG_LVRA(fprintf(output, "CopyVR1 allocates in LVRA\n"));
      
      newRep = LVRAAlloc(ByteRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = (struct ValRep *)*cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate newRep in IOA/AOA */
      push(theObj);
      push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVR1 allocates in AOA\n"));
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
    
    if (range > LARGE_REP_SIZE){
      /* newRep should go into LVRA */
      long *cycleCell  = 0;
      
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
      
      DEBUG_LVRA(fprintf(output, "CopyVR2 allocates in LVRA\n"));
      
      newRep = LVRAAlloc(ShortRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = (struct ValRep *)*cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate newRep in IOA/AOA */
      push(theObj);
      push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVR2 allocates in AOA\n"));
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
    
    if (range > LARGE_REP_SIZE){
      /* newRep should go into LVRA */
      long *cycleCell  = 0;
      
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
      
      DEBUG_LVRA(fprintf(output, "CopyVR2 allocates in LVRA\n"));
      
      newRep = LVRAAlloc(LongRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = (struct ValRep *)*cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate newRep in IOA/AOA */
      push(theObj);
      push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVR4 allocates in AOA\n"));
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
    
    if (range > LARGE_REP_SIZE){
      /* newRep should go into LVRA */
      long *cycleCell  = 0;
      
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
      
      DEBUG_LVRA(fprintf(output, "CopyVR8 allocates in LVRA\n"));
      
      newRep = LVRAAlloc(DoubleRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = (struct ValRep *)*cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate newRep in IOA/AOA */
      push(theObj);
      push(theRep); /* Is NOT is LVRA and may thus not cause LVRA cycle problems */
      if (size>IOAMAXSIZE){
	DEBUG_AOA(fprintf(output, "CopyVR8 allocates in AOA\n"));
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
      if (newRep) newRep->GCAttr = 0;
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
    } 
    if (newRep){
      newRep->GCAttr = 0; /* In AOA */
    } else {
      newRep = (struct ObjectRep *)IOAalloc(size, SP);
      newRep->GCAttr = 1; /* In IOA */
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
      if (newRep) newRep->GCAttr = 0;
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAalloc failed\n"));
    } 
    if (newRep){
      newRep->GCAttr = 0; /* In AOA */
    } else {
      newRep = (struct ObjectRep *)IOAalloc(size, SP);
      newRep->GCAttr = 1; /* In IOA */
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
