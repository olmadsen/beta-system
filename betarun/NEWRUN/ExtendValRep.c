/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void ExtVR1(struct Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    struct ValRep * theRep;
    struct ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR1++);

    Ck(theObj);
    theRep = *(struct ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = (ByteRepBodySize((add < 0) ? newRange : oldRange))>>2;
    size = ByteRepSize(newRange);
      
    if (newRange > LARGE_REP_SIZE){
      newRep = LVRAXAlloc(ByteRepPTValue, oldRange, newRange);
    }
    if (newRep) {
      /* LVRA allocation succeeded */
      /* Recalculate theRep, it may have been moved by LVRACompaction */
      theRep = *(struct ValRep **)((long *) theObj + offset);
      DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		       newRep->HighBorder==newRange &&
		       newRep->LowBorder==1, 
		       "ExtVR1: lvra structure ok"));
	
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      newRep->GCAttr = (long) ((long *) theObj + offset);
      *(struct ValRep **)((long *) theObj + offset) = newRep;
	
      /* Copy old rep */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      return;
    } /* LVRA */
      
    /* NOT REACHED if LVRAXAlloc successfully called */

    /* Allocate new repetition */
    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "ExtVR1 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
    } 
    if (!newRep){
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    }
    pop(theObj);

    /* Reload theRep - may have been moved in IOAGc */
    theRep = *(struct ValRep **)((long *) theObj + offset);

    /* Assign structural part of new repetition */
    newRep->Proto = ByteRepPTValue;
    /* newRep->GCAttr set above if in IOA */
    newRep->LowBorder = theRep->LowBorder;
    newRep->HighBorder = newRange;

    /* Assign into theObj */
    AssignReference((long *) theObj + offset, (struct Item *)newRep);
    
    /* Copy contents of old rep to new rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    } 
    
    Ck(theObj); Ck(theRep); Ck(newRep);
} /* ExtVR1 */

void ExtVR2(struct Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    struct ValRep * theRep;
    struct ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR2++);

    Ck(theObj);
    theRep = *(struct ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = (ShortRepBodySize((add < 0) ? newRange : oldRange))>>2;
    size = ShortRepSize(newRange);
      
    if (newRange > LARGE_REP_SIZE){
      newRep = LVRAXAlloc(ShortRepPTValue, oldRange, newRange);
    }
    if (newRep) {
      /* LVRA allocation succeeded */
      /* Recalculate theRep, it may have been moved by LVRACompaction */
      theRep = *(struct ValRep **)((long *) theObj + offset);
      DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		       newRep->HighBorder==newRange &&
		       newRep->LowBorder==1, 
		       "ExtVR2: lvra structure ok"));
	
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      newRep->GCAttr = (long) ((long *) theObj + offset);
      *(struct ValRep **)((long *) theObj + offset) = newRep;
	
      /* Copy old rep */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      return;
    } /* LVRA */
      
    /* NOT REACHED if LVRAXAlloc successfully called */

    /* Allocate new repetition */
    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "ExtVR2 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
    } 
    if (!newRep){
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    }
    pop(theObj);

    /* Reload theRep - may have been moved in IOAGc */
    theRep = *(struct ValRep **)((long *) theObj + offset);

    /* Assign structural part of new repetition */
    newRep->Proto = ShortRepPTValue;
    /* newRep->GCAttr set above if in IOA */
    newRep->LowBorder = theRep->LowBorder;
    newRep->HighBorder = newRange;

    /* Assign into theObj */
    AssignReference((long *) theObj + offset, (struct Item *)newRep);
    
    /* Copy contents of old rep to new rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    } 
    
    Ck(theObj); Ck(theRep); Ck(newRep);
} /* ExtVR2 */

void ExtVR4(struct Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    struct ValRep * theRep;
    struct ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR4++);

    Ck(theObj);
    theRep = *(struct ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = LongRepBodySize((add < 0) ? newRange : oldRange) >>2;
    size = LongRepSize(newRange);
      
    if (newRange > LARGE_REP_SIZE){
      newRep = LVRAXAlloc(LongRepPTValue, oldRange, newRange);
    }
    if (newRep) {
      /* LVRA allocation succeeded */
      /* Recalculate theRep, it may have been moved by LVRACompaction */
      theRep = *(struct ValRep **)((long *) theObj + offset);
      DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		       newRep->HighBorder==newRange &&
		       newRep->LowBorder==1, 
		       "ExtVR4: lvra structure ok"));
	
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      newRep->GCAttr = (long) ((long *) theObj + offset);
      *(struct ValRep **)((long *) theObj + offset) = newRep;
	
      /* Copy old rep */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      return;
    } /* LVRA */
      
    /* NOT REACHED if LVRAXAlloc successfully called */

    /* Allocate new repetition */
    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "ExtVR4 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
    } 
    if (!newRep){
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    }
    pop(theObj);

    /* Reload theRep - may have been moved in IOAGc */
    theRep = *(struct ValRep **)((long *) theObj + offset);

    /* Assign structural part of new repetition */
    newRep->Proto = LongRepPTValue;
    /* newRep->GCAttr set above if in IOA */
    newRep->LowBorder = theRep->LowBorder;
    newRep->HighBorder = newRange;

    /* Assign into theObj */
    AssignReference((long *) theObj + offset, (struct Item *)newRep);
    
    /* Copy contents of old rep to new rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    } 
    
    Ck(theObj); Ck(theRep); Ck(newRep);
} /* ExtVR4 */

void ExtVR8(struct Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    struct ValRep * theRep;
    struct ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR8++);

    Ck(theObj);
    theRep = *(struct ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = (DoubleRepBodySize((add < 0) ? newRange : oldRange))>>2;
    size = DoubleRepSize(newRange);
      
    if (newRange > LARGE_REP_SIZE){
      newRep = LVRAXAlloc(DoubleRepPTValue, oldRange, newRange);
    }
    if (newRep) {
      /* LVRA allocation succeeded */
      /* Recalculate theRep, it may have been moved by LVRACompaction */
      theRep = *(struct ValRep **)((long *) theObj + offset);
      DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		       newRep->HighBorder==newRange &&
		       newRep->LowBorder==1, 
		       "ExtVR8: lvra structure ok"));
	
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      newRep->GCAttr = (long) ((long *) theObj + offset);
      *(struct ValRep **)((long *) theObj + offset) = newRep;
	
      /* Copy old rep */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      return;
    } /* LVRA */
      
    /* NOT REACHED if LVRAXAlloc successfully called */

    /* Allocate new repetition */
    push(theObj);
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "ExtVR8 allocates in AOA\n"));
      newRep = (struct ValRep *)AOAcalloc(size, SP);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
    } 
    if (!newRep){
      newRep = (struct ValRep *)IOAalloc(size, SP);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    }
    pop(theObj);

    /* Reload theRep - may have been moved in IOAGc */
    theRep = *(struct ValRep **)((long *) theObj + offset);

    /* Assign structural part of new repetition */
    newRep->Proto = DoubleRepPTValue;
    /* newRep->GCAttr set above if in IOA */
    newRep->LowBorder = theRep->LowBorder;
    newRep->HighBorder = newRange;

    /* Assign into theObj */
    AssignReference((long *) theObj + offset, (struct Item *)newRep);
    
    /* Copy contents of old rep to new rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    } 
    
    Ck(theObj); Ck(theRep); Ck(newRep);
} /* ExtVR8 */


void ExtVRI(struct Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
  struct ObjectRep * theRep;
  struct ObjectRep * newRep=NULL;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  DEBUG_CODE(NumExtVRI++);
  
  Ck(theObj);
  theRep = *(struct ObjectRep **)((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = DynObjectRepSize((add < 0) ? newRange : oldRange) >> 2;
  size = DynObjectRepSize(newRange);
  
  /* Allocate new repetition */
  push(theObj);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "ExtVRI allocates in AOA\n"));
    newRep = (struct ObjectRep *)AOAcalloc(size, SP);
    DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
  } 
  if (!newRep){
    newRep = (struct ObjectRep *)IOAalloc(size, SP);
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
  }
  pop(theObj);
  
  /* Reload theRep - may have been moved in IOAGc */
  theRep = *(struct ObjectRep **)((long *) theObj + offset);
  
  /* Assign structural part of new repetition */
  newRep->Proto = DynItemRepPTValue;
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  newRep->iProto = theRep->iProto;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, (struct Item *)newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i]);
  }
  
  if (add>0){
    /* Allocate and Initialize new extra elements */
    while(--add>=0){
      struct Item *item;
      push(theRep);
      push(newRep);
      item = AlloI((struct Object *)theRep->iOrigin, theRep->iProto, SP);
      pop(newRep);
      pop(theRep);
      AssignReference((long *)((long)&newRep->Body + (oldRange+add)*4), item);
    }
  }
  
  Ck(theObj); Ck(theRep); Ck(newRep);
} /* ExtVRI */


void ExtVRC(struct Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
  struct ObjectRep * theRep;
  struct ObjectRep * newRep=NULL;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  DEBUG_CODE(NumExtVRC++);
  
  Ck(theObj);
  theRep = *(struct ObjectRep **)((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = DynObjectRepSize((add < 0) ? newRange : oldRange) >> 2;
  size = DynObjectRepSize(newRange);
  
  /* Allocate new repetition */
  push(theObj);
  if (size>IOAMAXSIZE){
    DEBUG_AOA(fprintf(output, "ExtVRC allocates in AOA\n"));
    newRep = (struct ObjectRep *)AOAcalloc(size, SP);
    DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
  } 
  if (!newRep){
    newRep = (struct ObjectRep *)IOAalloc(size, SP);
    if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
  }
  pop(theObj);
  
  /* Reload theRep - may have been moved in IOAGc */
  theRep = *(struct ObjectRep **)((long *) theObj + offset);
  
  /* Assign structural part of new repetition */
  newRep->Proto = DynCompRepPTValue;
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  newRep->iProto = theRep->iProto;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, (struct Item *)newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i]);
  }
  
  if (add>0){
    /* Allocate and Initialize new extra elements */
    while(--add>=0){
      struct Component *comp;
      push(theRep);
      push(newRep);
      comp = AlloC((struct Object *)theRep->iOrigin, theRep->iProto, SP);
      pop(newRep);
      pop(theRep);
      AssignReference((long *)((long)&newRep->Body + (oldRange+add)*4), (struct Item *)comp);
    }
  }
  
  Ck(theObj); Ck(theRep); Ck(newRep);
} /* ExtVRC */

