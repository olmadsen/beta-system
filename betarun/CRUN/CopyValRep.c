/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamRepObjOff(CopyVR1)
{
    DeclReference1(struct ValRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();

    FetchRepObjOff();

    DEBUG_CODE(NumCopyVR1++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
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
	 * the cell actually referencing the repetition is remembered. 
	 * This cell will be updated if the repetition is moved.
	 */
	cycleCell = (long *) theRep->GCAttr; /* Cell that references the repetition */
      }
      
      DEBUG_LVRA(fprintf(output, "CopyValRep allocates in LVRA\n"));
      
      newRep = LVRAAlloc(ByteRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = cast(ValRep) *cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate in IOA */
      Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
      newRep->Proto = ByteRepPTValue;
      newRep->GCAttr = IOAMinAge;
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }
    
    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOff(CopyVR2)
{
    DeclReference1(struct ValRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR2++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
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
	 * the cell actually referencing the repetition is remembered. 
	 * This cell will be updated if the repetition is moved.
	 */
	cycleCell = (long *) theRep->GCAttr; /* Cell that references the repetition */
      }
      
      DEBUG_LVRA(fprintf(output, "CopyValRep allocates in LVRA\n"));
      
      newRep = LVRAAlloc(ShortRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = cast(ValRep) *cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate in IOA */
      Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
      newRep->Proto = ShortRepPTValue;
      newRep->GCAttr = IOAMinAge;
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }
    
    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOff(CopyVR4)
{
    DeclReference1(struct ValRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR4++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
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
	 * the cell actually referencing the repetition is remembered. 
	 * This cell will be updated if the repetition is moved.
	 */
	cycleCell = (long *) theRep->GCAttr; /* Cell that references the repetition */
      }
      
      DEBUG_LVRA(fprintf(output, "CopyValRep allocates in LVRA\n"));
      
      newRep = LVRAAlloc(LongRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = cast(ValRep) *cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate in IOA */
      Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
      newRep->Proto = LongRepPTValue;
      newRep->GCAttr = IOAMinAge;
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }
    
    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamRepObjOff(CopyVR8)
{
    DeclReference1(struct ValRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();
    FetchRepObjOff();
    
    DEBUG_CODE(NumCopyVR8++);

    Ck(theRep); Ck(theObj);
    newRep = NULL;
    
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
	 * the cell actually referencing the repetition is remembered. 
	 * This cell will be updated if the repetition is moved.
	 */
	cycleCell = (long *) theRep->GCAttr; /* Cell that references the repetition */
      }
      
      DEBUG_LVRA(fprintf(output, "CopyValRep allocates in LVRA\n"));
      
      newRep = LVRAAlloc(DoubleRepPTValue, range);
      if (cycleCell) {
	/* theRep was in LVRA. Since it may have been moved by
	 * LVRACompaction, we update it.
	 */
	theRep = cast(ValRep) *cycleCell;
      }
    }
    if (newRep) {
      /* Make the LVRA-cycle of the new repetition */
      newRep->GCAttr = (long) ((long *) theObj + offset);
    } else {
      /* Allocate in IOA */
      Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
      newRep->Proto = DoubleRepPTValue;
      newRep->GCAttr = IOAMinAge;
      newRep->LowBorder = 1;
      newRep->HighBorder = range;
    }
    
    size -= headsize(ValRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
    }

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);

}

ParamORepObjOff(CopyVRI)
{
    DeclReference1(struct ObjectRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();
    FetchORepObjOff();
    
    DEBUG_CODE(NumCopyVRI++);
    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;
    size = DynObjectRepSize(range);
    
    Protect2(theObj, theRep, newRep = cast(ObjectRep) IOAalloc(size));
    
    newRep->Proto = DynItemRepPTValue;
    newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    newRep->iOrigin = theRep->iOrigin;
    newRep->iProto = theRep->iProto;
    
    size -= headsize(ObjectRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
      /* No need to use AssignReference: newRep is in IOA */
    }

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);
}

ParamORepObjOff(CopyVRC)
{
    DeclReference1(struct ObjectRep *, newRep);
    register unsigned range, i, size;
    
    GCable_Entry();
    FetchORepObjOff();
    
    DEBUG_CODE(NumCopyVRC++);
    Ck(theRep); Ck(theObj);
    
    range = theRep->HighBorder;
    size = DynObjectRepSize(range);
    
    Protect2(theObj, theRep, newRep = cast(ObjectRep) IOAalloc(size));
    
    newRep->Proto = DynCompRepPTValue;
    newRep->GCAttr = IOAMinAge;
    newRep->LowBorder = 1;
    newRep->HighBorder = range;
    newRep->iOrigin = theRep->iOrigin;
    newRep->iProto = theRep->iProto;
    
    size -= headsize(ObjectRep); /* adjust size to be bodysize */
    
    /* Copy theRep to newRep. Copy the whole body as longs */
    for (i = 0; i < size/4; ++i){
      newRep->Body[i] = theRep->Body[i];
      /* No need to use AssignReference: newRep is in IOA */
    }

    AssignReference((long *)theObj + offset, cast(Item) newRep);

    Ck(newRep); Ck(theRep); Ck(theObj);
}
