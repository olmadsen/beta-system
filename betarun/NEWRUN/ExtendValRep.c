/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#define REP    ((struct ObjectRep *)theRep)
#define NEWREP ((struct ObjectRep *)newRep)

void ExtVR(struct Object *theObj,
	   unsigned offset, /* in longs */
	   long add /* What to extend the range with */, 
	   long *SP
	   )
{
    struct ValRep * theRep;
    struct ValRep * newRep;
    long range; /* range of old repetition */
    long newRange; /* Range of new repetition */
    long copyRange; /* Number of LONGS to copy from old rep */
    long i;
    long size; /* size of new repetition */
    
    DEBUG_CODE(NumExtVR++);

    Ck(theObj);
    newRep = (struct ValRep *)0;
    theRep = *(struct ValRep **)((long *) theObj + offset);
    range = theRep->HighBorder;
    newRange = range + add; /* Range of new repetition */
    
    if (newRange < 0) newRange = 0;

    if (isValRep(theRep)){
      copyRange = (DispatchValRepBodySize(theRep->Proto, (add < 0) ? newRange : range))>>2;
      size = DispatchValRepSize(theRep->Proto, newRange);
      
      if (newRange > LARGE_REP_SIZE) 
	newRep = LVRACAlloc(theRep->Proto, newRange);
      if (newRep) {
	/* LVRA allocation succeeded */
	/* Recalculate theRep, it may have been moved by LVRACompaction */
	theRep = *(struct ValRep **)((long *) theObj + offset);
	DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
			 newRep->HighBorder==newRange &&
			 newRep->LowBorder==1, 
			 "ExtendValRep: lvra structure ok"));
	
	/* Make the LVRA-cycle: theCell -> theRep.GCAttr */
	newRep->GCAttr = (long) ((long *) theObj + offset);
	*(struct ValRep **)((long *) theObj + offset) = newRep;
	
	/* Copy old rep */
	for (i = 0; i < copyRange; ++i)
	  newRep->Body[i] = theRep->Body[i];
	
	return;
      }
      
    } else {
      copyRange = 
	(DispatchObjectRepSize(theRep->Proto, 
			       (add < 0) ? newRange : range,
			       REP->iProto) - headsize(ObjectRep)) >> 2;
      size = DispatchObjectRepSize(theRep->Proto, newRange, REP->iProto);
    }

    /* NOT REACHED if LVRAcalloc successfully called */

    /* Allocate and nullify new repetition: There is a little overhead here;
     * only extension needs to be nullified
     */
    
    Protect2(theObj, theRep, newRep = (struct ValRep *)IOAcalloc(size, SP));
    
    Ck(theRep);
    
    /* Assign structural part of new repetition */
    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = theRep->LowBorder;
    newRep->HighBorder = newRange;

    /* Assign into theObj */
    AssignReference((long *) theObj + offset, (struct Item *)newRep);
    
    if (isValRep(theRep)){
      /* Copy contents of old rep to new rep */
      for (i = 0; i < copyRange; ++i)
	newRep->Body[i] = theRep->Body[i];
    } else {
      /* Object Rep */

      /* Copy contents of old rep to new rep */
      for (i = 0; i < copyRange; ++i){
	NEWREP->Body[i] = REP->Body[i];
	/* No need to use AssignReference: NEWREP is in IOA */
      }

      NEWREP->iProto = REP->iProto;
      NEWREP->iOrigin = REP->iOrigin;

      if (add>0){
	/* Allocate/Initialize new extra elements */

	switch((long)theRep->Proto){
	case (long) DynItemRepPTValue:
	  while(--add>=0){
	    struct Item *item;
	    Protect2(theRep, newRep,
		     item = AlloI((struct Object *)REP->iOrigin, REP->iProto, SP));
	    AssignReference((long *)((long)&NEWREP->Body + (range+add)*4), 
			    item);
	  }
	  break;
	case (long) DynCompRepPTValue:
	  while(--add>=0){
	    struct Component *comp;
	    Protect2(theRep, newRep,
		     comp = AlloC((struct Object *)REP->iOrigin, REP->iProto, SP));
	    AssignReference((long *)((long)&NEWREP->Body + (range+add)*4), 
			    (struct Item *)comp);
	  }
	  break;
	}
      }
    }
  }

