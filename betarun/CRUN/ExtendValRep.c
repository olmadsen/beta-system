/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#ifdef hppa
/* to keep Gcc's grappy little hand off this */
register long _dummyx asm("r16");
#endif

#include "beta.h"
#include "crun.h"

ParamObjOffRange(ExtVR1)
{
  DeclReference1(struct ValRep *, theRep);
  DeclReference2(struct ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  GCable_Entry();
  
#ifdef hppa
  add = (long) getR2Reg();
#endif
  
  DEBUG_CODE(NumExtVR1++);
  Ck(theObj);
  
  newRep = (struct ValRep *)0;
  theRep = *casthandle(ValRep) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (ByteRepBodySize((add < 0) ? newRange : oldRange))>>2;
  size = ByteRepSize(newRange);
  
  if (newRange > LARGE_REP_SIZE) {
    newRep = LVRACAlloc(ByteRepPTValue, newRange);
  }
  if (newRep) {
    /* LVRA allocation succeeded */
    /* Recalculate theRep, it may have been moved by LVRACompaction */
    theRep = *casthandle(ValRep) ((long *) theObj + offset);
    DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		     newRep->HighBorder==newRange &&
		     newRep->LowBorder==1, 
		     "ExtendValRep: lvra structure ok"));
    
    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theObj + offset);
    *casthandle(ValRep) ((long *) theObj + offset) = newRep;
    
    /* Copy old rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    }
    return;
  } /* End LVRA allocation */
  
  /* NOT REACHED if LVRAcalloc successfully called */
  
  /* Allocate new repetition in IOA */
  
  Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  newRep->Proto = ByteRepPTValue;
  newRep->GCAttr = 1;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, cast(Item) newRep);
  
  /* Copy contents of old rep to new rep as longs */
  for (i = 0; i < copyRange; ++i){
    newRep->Body[i] = theRep->Body[i];
  }
  
  Ck(theRep); Ck(newRep); Ck(theObj);
  
  return;
}

ParamObjOffRange(ExtVR2)
{
  DeclReference1(struct ValRep *, theRep);
  DeclReference2(struct ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  GCable_Entry();
  
#ifdef hppa
  add = (long) getR2Reg();
#endif
  
  DEBUG_CODE(NumExtVR2++);
  Ck(theObj);
  
  newRep = (struct ValRep *)0;
  theRep = *casthandle(ValRep) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (ShortRepBodySize((add < 0) ? newRange : oldRange))>>2;
  size = ShortRepSize(newRange);
  
  if (newRange > LARGE_REP_SIZE) {
    newRep = LVRACAlloc(ShortRepPTValue, newRange);
  }
  if (newRep) {
    /* LVRA allocation succeeded */
    /* Recalculate theRep, it may have been moved by LVRACompaction */
    theRep = *casthandle(ValRep) ((long *) theObj + offset);
    DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		     newRep->HighBorder==newRange &&
		     newRep->LowBorder==1, 
		     "ExtendValRep: lvra structure ok"));
    
    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theObj + offset);
    *casthandle(ValRep) ((long *) theObj + offset) = newRep;
    
    /* Copy old rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    }
    return;
  } /* End LVRA allocation */
  
  /* NOT REACHED if LVRAcalloc successfully called */
  
  /* Allocate new repetition in IOA */
  
  Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  newRep->Proto = ShortRepPTValue;
  newRep->GCAttr = 1;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, cast(Item) newRep);
  
  /* Copy contents of old rep to new rep as longs */
  for (i = 0; i < copyRange; ++i){
    newRep->Body[i] = theRep->Body[i];
  }
  
  Ck(theRep); Ck(newRep); Ck(theObj);
  
  return;
}

ParamObjOffRange(ExtVR4)
{
  DeclReference1(struct ValRep *, theRep);
  DeclReference2(struct ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  GCable_Entry();
  
#ifdef hppa
  add = (long) getR2Reg();
#endif
  
  DEBUG_CODE(NumExtVR4++);
  Ck(theObj);
  
  newRep = (struct ValRep *)0;
  theRep = *casthandle(ValRep) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (ValRepBodySize((add < 0) ? newRange : oldRange))>>2;
  size = LongRepSize(newRange);
  
  if (newRange > LARGE_REP_SIZE) {
    newRep = LVRACAlloc(LongRepPTValue, newRange);
  }
  if (newRep) {
    /* LVRA allocation succeeded */
    /* Recalculate theRep, it may have been moved by LVRACompaction */
    theRep = *casthandle(ValRep) ((long *) theObj + offset);
    DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		     newRep->HighBorder==newRange &&
		     newRep->LowBorder==1, 
		     "ExtendValRep: lvra structure ok"));
    
    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theObj + offset);
    *casthandle(ValRep) ((long *) theObj + offset) = newRep;
    
    /* Copy old rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    }
    return;
  } /* End LVRA allocation */
  
  /* NOT REACHED if LVRAcalloc successfully called */
  
  /* Allocate new repetition in IOA */
  
  Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  newRep->Proto = LongRepPTValue;
  newRep->GCAttr = 1;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, cast(Item) newRep);
  
  /* Copy contents of old rep to new rep as longs */
  for (i = 0; i < copyRange; ++i){
    newRep->Body[i] = theRep->Body[i];
  }
  
  Ck(theRep); Ck(newRep); Ck(theObj);
  
  return;
}

ParamObjOffRange(ExtVR8)
{
  DeclReference1(struct ValRep *, theRep);
  DeclReference2(struct ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  GCable_Entry();
  
#ifdef hppa
  add = (long) getR2Reg();
#endif
  
  DEBUG_CODE(NumExtVR8++);
  Ck(theObj);
  
  newRep = (struct ValRep *)0;
  theRep = *casthandle(ValRep) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (DoubleRepBodySize((add < 0) ? newRange : oldRange))>>2;
  size = DoubleRepSize(newRange);
  
  if (newRange > LARGE_REP_SIZE) {
    newRep = LVRACAlloc(DoubleRepPTValue, newRange);
  }
  if (newRep) {
    /* LVRA allocation succeeded */
    /* Recalculate theRep, it may have been moved by LVRACompaction */
    theRep = *casthandle(ValRep) ((long *) theObj + offset);
    DEBUG_CODE(Claim(newRep->Proto==theRep->Proto &&
		     newRep->HighBorder==newRange &&
		     newRep->LowBorder==1, 
		     "ExtendValRep: lvra structure ok"));
    
    /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
    newRep->GCAttr = (long) ((long *) theObj + offset);
    *casthandle(ValRep) ((long *) theObj + offset) = newRep;
    
    /* Copy old rep */
    for (i = 0; i < copyRange; ++i){
      newRep->Body[i] = theRep->Body[i];
    }
    return;
  } /* End LVRA allocation */
  
  /* NOT REACHED if LVRAcalloc successfully called */
  
  /* Allocate new repetition in IOA */
  
  Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  newRep->Proto = DoubleRepPTValue;
  newRep->GCAttr = 1;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  
  /* Assign into theObj */
  AssignReference((long *) theObj + offset, cast(Item) newRep);
  
  /* Copy contents of old rep to new rep as longs */
  for (i = 0; i < copyRange; ++i){
    newRep->Body[i] = theRep->Body[i];
  }
  
  Ck(theRep); Ck(newRep); Ck(theObj);
  
  return;
}

/****** Object Repetitions *******/

#define REP    ((struct ObjectRep *)theRep)
#define NEWREP ((struct ObjectRep *)newRep)

ParamObjOffRange(ExtVRI)
{
  DeclReference1(struct ValRep *, theRep);
  DeclReference2(struct ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  GCable_Entry();

#ifdef hppa
  add = (long) getR2Reg();
#endif

  DEBUG_CODE(NumExtVRI++);
  Ck(theObj);

  newRep = (struct ValRep *)0;
  theRep = *casthandle(ValRep) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;

  copyRange = (DynObjectRepSize((add < 0) ? newRange : oldRange)
	       - headsize(ObjectRep)) >> 2;
  size = DynObjectRepSize(newRange);

  /* Allocate new repetition */
  
  Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  newRep->Proto = DynItemRepPTValue;
  newRep->GCAttr = 1;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  NEWREP->iProto = REP->iProto;
  NEWREP->iOrigin = REP->iOrigin;

  /* Assign into theObj */
  AssignReference((long *) theObj + offset, cast(Item) newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
    NEWREP->Body[i] = REP->Body[i];
    /* No need to use AssignReference: NEWREP is in IOA */
  }

  if (add>0){
    /* Allocate/Initialize new extra elements */

    while(--add>=0){
      struct Item *item;
#ifdef sparc
      Protect2(theRep, newRep,
	       item = SPARC_AlloI(cast(Object) REP->iOrigin, 0, REP->iProto, 0, 0));
#endif
#ifdef hppa
      Protect2(theRep, newRep,
	       item = CAlloI(cast(Object) REP->iOrigin, REP->iProto));
#endif
#ifdef crts
      Protect2(theRep, newRep,
	       item = AlloI(cast(Object) REP->iOrigin, REP->iProto));
#endif
      AssignReference((long *)((long)&NEWREP->Body + (oldRange+add)*4), item);
    }
  }
  Ck(theRep); Ck(newRep); Ck(theObj);
}

ParamObjOffRange(ExtVRC)
{
  DeclReference1(struct ValRep *, theRep);
  DeclReference2(struct ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  GCable_Entry();

#ifdef hppa
  add = (long) getR2Reg();
#endif

  DEBUG_CODE(NumExtVRC++);
  Ck(theObj);

  newRep = (struct ValRep *)0;
  theRep = *casthandle(ValRep) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;

  copyRange = (DynObjectRepSize((add < 0) ? newRange : oldRange) 
	       - headsize(ObjectRep)) >> 2;
  size = DynObjectRepSize(newRange);

  /* Allocate new repetition */
  
  Protect2(theObj, theRep, newRep = cast(ValRep) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  newRep->Proto = DynCompRepPTValue;
  newRep->GCAttr = 1;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  NEWREP->iProto = REP->iProto;
  NEWREP->iOrigin = REP->iOrigin;

  /* Assign into theObj */
  AssignReference((long *) theObj + offset, cast(Item) newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
    NEWREP->Body[i] = REP->Body[i];
    /* No need to use AssignReference: NEWREP is in IOA */
  }

  if (add>0){
    /* Allocate/Initialize new extra elements */

    while(--add>=0){
      struct Component *comp;
#ifdef sparc
      Protect2(theRep, newRep,
	       comp = SPARC_AlloC(cast(Object) REP->iOrigin, 0, REP->iProto, 0, 0));
#endif
#ifdef hppa
      Protect2(theRep, newRep,
	       comp = CAlloC(cast(Object) REP->iOrigin, REP->iProto));
#endif
#ifdef crts
      Protect2(theRep, newRep,
	       comp = AlloC(cast(Object) REP->iOrigin, REP->iProto));
#endif
      AssignReference((long *)((long)&NEWREP->Body + (oldRange+add)*4), (struct Item *)comp);
    }
  }
  Ck(theRep); Ck(newRep); Ck(theObj);
}
