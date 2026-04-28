/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void ExtVR1(Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    ValRep * theRep;
    ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR1++);

    Ck(theObj);
    theRep = *(ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = (ByteRepBodySize((add < 0) ? newRange : oldRange))>>2;
    size = ByteRepSize(newRange);
      
    while (1) {
      if (newRange > LARGE_REP_SIZE || size>IOAMAXSIZE){
	newRep = LVRAXAlloc(ByteRepPTValue, oldRange, newRange);
	if (newRep) {
	  *(ValRep **)((long *) theObj + offset) = newRep;
	  
	  /* Copy old rep */
	  for (i = 0; i < copyRange; ++i){
	    newRep->Body[i] = theRep->Body[i];
	  }
	  return;
	}
      }

      /* Allocate new repetition in IOA */
      push(theObj);
      newRep = (ValRep *)IOATryAlloc(size, SP);
      pop(theObj);
      if (newRep) {
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	
	/* Reload theRep - may have been moved in IOAGc */
	theRep = *(ValRep **)((long *) theObj + offset);
	
	/* Assign structural part of new repetition */
	SETPROTO(newRep, ByteRepPTValue);
	/* newRep->GCAttr set above if in IOA */
	newRep->LowBorder = theRep->LowBorder;
	newRep->HighBorder = newRange;
	
	/* Assign into theObj */
	AssignReference((long *) theObj + offset, (Item *)newRep);
	
	/* Copy contents of old rep to new rep */
	for (i = 0; i < copyRange; ++i){
	  newRep->Body[i] = theRep->Body[i];
	} 
	
	Ck(theObj); Ck(theRep); Ck(newRep);
	return;
      }
    }
} /* ExtVR1 */

void ExtVR2(Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    ValRep * theRep;
    ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR2++);

    Ck(theObj);
    theRep = *(ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = (ShortRepBodySize((add < 0) ? newRange : oldRange))>>2;
    size = ShortRepSize(newRange);
      
    while (1) {
      if (newRange > LARGE_REP_SIZE || size>IOAMAXSIZE){
	newRep = LVRAXAlloc(ShortRepPTValue, oldRange, newRange);
	if (newRep) {
	  *(ValRep **)((long *) theObj + offset) = newRep;
	  
	  /* Copy old rep */
	  for (i = 0; i < copyRange; ++i){
	    newRep->Body[i] = theRep->Body[i];
	  }
	  return;
	}
      }
      
      /* Allocate new repetition */
      push(theObj);
      newRep = (ValRep *)IOATryAlloc(size, SP);
      pop(theObj);
      if (newRep) {
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	
	/* Reload theRep - may have been moved in IOAGc */
	theRep = *(ValRep **)((long *) theObj + offset);
	
	/* Assign structural part of new repetition */
	SETPROTO(newRep, ShortRepPTValue);
	/* newRep->GCAttr set above if in IOA */
	newRep->LowBorder = theRep->LowBorder;
	newRep->HighBorder = newRange;
	
	/* Assign into theObj */
	AssignReference((long *) theObj + offset, (Item *)newRep);
	
	/* Copy contents of old rep to new rep */
	for (i = 0; i < copyRange; ++i){
	  newRep->Body[i] = theRep->Body[i];
	} 
	
	Ck(theObj); Ck(theRep); Ck(newRep);
	return;
      }
    }
} /* ExtVR2 */

void ExtVR4(Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    ValRep * theRep;
    ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR4++);

    Ck(theObj);
    theRep = *(ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = LongRepBodySize((add < 0) ? newRange : oldRange) >>2;
    size = LongRepSize(newRange);
      
    while(1) {
      if (newRange > LARGE_REP_SIZE || size>IOAMAXSIZE){
	newRep = LVRAXAlloc(LongRepPTValue, oldRange, newRange);
	if (newRep) {
	  *(ValRep **)((long *) theObj + offset) = newRep;
	  
	  /* Copy old rep */
	  for (i = 0; i < copyRange; ++i){
	    newRep->Body[i] = theRep->Body[i];
	  }
	  return;
	}
      }
      
      /* Allocate new repetition */
      push(theObj);
      newRep = (ValRep *)IOATryAlloc(size, SP);
      pop(theObj);
      if (newRep) {
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	
	/* Reload theRep - may have been moved in IOAGc */
	theRep = *(ValRep **)((long *) theObj + offset);
	
	/* Assign structural part of new repetition */
	SETPROTO(newRep, LongRepPTValue);
	/* newRep->GCAttr set above if in IOA */
	newRep->LowBorder = theRep->LowBorder;
	newRep->HighBorder = newRange;
	
	/* Assign into theObj */
	AssignReference((long *) theObj + offset, (Item *)newRep);
	
	/* Copy contents of old rep to new rep */
	for (i = 0; i < copyRange; ++i){
	  newRep->Body[i] = theRep->Body[i];
	} 
	
	Ck(theObj); Ck(theRep); Ck(newRep);
	return;
      }
    }
} /* ExtVR4 */

void ExtVR8(Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
    ValRep * theRep;
    ValRep * newRep=NULL;
    long oldRange; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR8++);

    Ck(theObj);
    theRep = *(ValRep **)((long *) theObj + offset);
    Ck(theRep);
    oldRange = theRep->HighBorder;
    newRange = oldRange + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    copyRange = (DoubleRepBodySize((add < 0) ? newRange : oldRange))>>2;
    size = DoubleRepSize(newRange);
      
    while(1) {
      if (newRange > LARGE_REP_SIZE || size>IOAMAXSIZE){
	newRep = LVRAXAlloc(DoubleRepPTValue, oldRange, newRange);
	if (newRep) {
	  *(ValRep **)((long *) theObj + offset) = newRep;
	  
	  /* Copy old rep */
	  for (i = 0; i < copyRange; ++i){
	    newRep->Body[i] = theRep->Body[i];
	  }
	  return;
	}
      }
      
      /* Allocate new repetition */
      push(theObj);
      newRep = (ValRep *)IOATryAlloc(size, SP);
      pop(theObj);
      if (newRep) {
	if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
	
	/* Reload theRep - may have been moved in IOAGc */
	theRep = *(ValRep **)((long *) theObj + offset);
	
	/* Assign structural part of new repetition */
	SETPROTO(newRep, DoubleRepPTValue);
	/* newRep->GCAttr set above if in IOA */
	newRep->LowBorder = theRep->LowBorder;
	newRep->HighBorder = newRange;
	
	/* Assign into theObj */
	AssignReference((long *) theObj + offset, (Item *)newRep);
	
	/* Copy contents of old rep to new rep */
	for (i = 0; i < copyRange; ++i){
	  newRep->Body[i] = theRep->Body[i];
	} 
	
	Ck(theObj); Ck(theRep); Ck(newRep);
	return;
      }
    }
} /* ExtVR8 */


void ExtVRI(Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
  ObjectRep * theRep;
  ObjectRep * newRep=NULL;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  DEBUG_CODE(NumExtVRI++);
  
  Ck(theObj);
  theRep = *(ObjectRep **)((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (DynObjectRepSize((add < 0) ? newRange : oldRange)
	       - headsize(ObjectRep))>> 2;
  size = DynObjectRepSize(newRange);
  
  /* Allocate new repetition */
  push(theObj);
  do {
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "ExtVRI allocates in AOA\n"));
      newRep = (ObjectRep *)AOAcalloc(size);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
    } 
    if (!newRep){
      newRep = (ObjectRep *)IOATryAlloc(size, SP);
      if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    }
  } while (!newRep);
  pop(theObj);
  
  /* Reload theRep - may have been moved in IOAGc */
  theRep = *(ObjectRep **)((long *) theObj + offset);
  
  /* Assign structural part of new repetition */
  SETPROTO(newRep, DynItemRepPTValue);
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  newRep->iProto = theRep->iProto;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, (Item *)newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i]);
  }
  
  if (add>0){
    /* Allocate and Initialize new extra elements */
    while(--add>=0){
      Item *item;
      push(theRep);
      push(newRep);
      item = AlloI((Object *)theRep->iOrigin, theRep->iProto, SP);
      pop(newRep);
      pop(theRep);
      AssignReference((long *)((long)&newRep->Body + (oldRange+add)*4), item);
    }
  }
  
  Ck(theRep); Ck(newRep);
} /* ExtVRI */


void ExtVRC(Object *theObj,
	    unsigned offset, /* in longs */
	    long add /* What to extend the range with */, 
	    long *SP
	    )
{
  ObjectRep * theRep;
  ObjectRep * newRep=NULL;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  DEBUG_CODE(NumExtVRC++);
  
  Ck(theObj);
  theRep = *(ObjectRep **)((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (DynObjectRepSize((add < 0) ? newRange : oldRange) 
	       - headsize(ObjectRep))>> 2;
  size = DynObjectRepSize(newRange);
  
  /* Allocate new repetition */
  push(theObj);
  do {
    if (size>IOAMAXSIZE){
      DEBUG_AOA(fprintf(output, "ExtVRC allocates in AOA\n"));
      newRep = (ObjectRep *)AOAcalloc(size);
      DEBUG_AOA(if (!newRep) fprintf(output, "AOAcalloc failed\n"));
    } 
    if (!newRep){
      newRep = (ObjectRep *)IOATryAlloc(size, SP);
      if (newRep && IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
    }
  } while (!newRep);
  pop(theObj);
  
  /* Reload theRep - may have been moved in IOAGc */
  theRep = *(ObjectRep **)((long *) theObj + offset);
  
  /* Assign structural part of new repetition */
  SETPROTO(newRep, DynCompRepPTValue);
  /* newRep->GCAttr set above if in IOA */
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  newRep->iProto = theRep->iProto;
  AssignReference(&newRep->iOrigin, theRep->iOrigin);
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, (Item *)newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
    AssignReference(&newRep->Body[i], theRep->Body[i]);
  }

  if (add>0){
    /* Allocate and Initialize new extra elements */
    while(--add>=0){
      Component *comp;
      push(theRep);
      push(newRep);
      comp = AlloC((Object *)theRep->iOrigin, theRep->iProto, SP);
      pop(newRep);
      pop(theRep);
      AssignReference((long *)((long)&newRep->Body + (oldRange+add)*4), (Item *)comp);
    }
  }
  
  Ck(theRep); Ck(newRep);
} /* ExtVRC */

