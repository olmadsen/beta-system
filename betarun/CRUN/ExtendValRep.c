/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#ifdef hppa
/* to keep Gcc's grappy little hand off this */
register long _dummyx __asm__("r16");
#endif

#include "beta.h"
#include "crun.h"

ParamObjOffRange(ExtVR1)
{
  DeclReference1(ValRep *, theRep);
  DeclReference2(ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  
  FetchObjOffRange();
  
  DEBUG_CODE(NumExtVR1++);
  Ck(theObj);
  
  newRep = (ValRep *)0;
  theRep = *(ValRep **) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (ByteRepBodySize((add < 0) ? newRange : oldRange))>>2;
  
  while (1) {
    if (newRange > LARGE_REP_SIZE) {
      newRep = LVRAXAlloc(ByteRepPTValue, oldRange, newRange);
      if (newRep) {
	*(ValRep **) ((long *) theObj + offset) = newRep;
	
	/* Copy old rep */
	for (i = 0; i < copyRange; ++i){
          newRep->Body[i] = theRep->Body[i];
	}
	Ck(theRep); Ck(newRep); Ck(theObj);
	return;
      }
    }
    
    /* Allocate new repetition in IOA */
    { 
      long size; /* size of new repetition */
      size = ByteRepSize(newRange);
      Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
    }

    if (newRep) {
      /* Assign structural part of new repetition */
      SETPROTO(newRep,ByteRepPTValue);
      
      if (IOAMinAge!=0) {
	newRep->GCAttr = IOAMinAge;
      }
      
      newRep->LowBorder = theRep->LowBorder;
      newRep->HighBorder = newRange;
      
      /* Assign into theObj */
      AssignReference((long *) theObj + offset, (Item *) newRep);
      
      /* Copy contents of old rep to new rep as longs */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      Ck(theRep); Ck(newRep); Ck(theObj);
      return;
    }
  } 
}

ParamObjOffRange(ExtVR2)
{
  DeclReference1(ValRep *, theRep);
  DeclReference2(ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  
  FetchObjOffRange();
  
  DEBUG_CODE(NumExtVR2++);
  Ck(theObj);
  
  newRep = (ValRep *)0;
  theRep = *(ValRep **) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (ShortRepBodySize((add < 0) ? newRange : oldRange))>>2;
  
  while (1) {
    if (newRange > LARGE_REP_SIZE) {
      newRep = LVRAXAlloc(ShortRepPTValue, oldRange, newRange);
      if (newRep) {
	*(ValRep **) ((long *) theObj + offset) = newRep;
	/* Copy old rep */
	for (i = 0; i < copyRange; ++i){
          newRep->Body[i] = theRep->Body[i];
	}
	Ck(theRep); Ck(newRep); Ck(theObj);
	return;
      }
    }

    /* Allocate new repetition in IOA */
    {
      long size; /* size of new repetition */
      size = ShortRepSize(newRange);
      Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
    }

    if (newRep) {
      /* Assign structural part of new repetition */
      SETPROTO(newRep,ShortRepPTValue);
      if (IOAMinAge!=0) {
	newRep->GCAttr = IOAMinAge;
      }
      newRep->LowBorder = theRep->LowBorder;
      newRep->HighBorder = newRange;
      
      /* Assign into theObj */
      AssignReference((long *) theObj + offset, (Item *) newRep);
      
      /* Copy contents of old rep to new rep as longs */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      Ck(theRep); Ck(newRep); Ck(theObj);
      return;
    }
  }
}

ParamObjOffRange(ExtVR4)
{
  DeclReference1(ValRep *, theRep);
  DeclReference2(ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  
  FetchObjOffRange();
  
  DEBUG_CODE(NumExtVR4++);
  Ck(theObj);

  newRep = (ValRep *)0;
  theRep = *(ValRep **) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */

#ifdef RTDEBUG
  if (oldRange<0) fprintf(output, "ExtVR4: negative oldRange %d\n", (int)oldRange);
  if (add<0) fprintf(output, "ExtVR4: negative add %d\n", (int)add);
#endif
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (LongRepBodySize((add < 0) ? newRange : oldRange))>>2;
  
  while (1) {
    if (newRange > LARGE_REP_SIZE) {
      newRep = LVRAXAlloc(LongRepPTValue, oldRange, newRange);
      if (newRep) {
	*(ValRep **) ((long *) theObj + offset) = newRep;
	
	/* Copy old rep */
	for (i = 0; i < copyRange; ++i){
	  newRep->Body[i] = theRep->Body[i];
	}
	Ck(theRep); Ck(newRep); Ck(theObj);
	return;
      }
    }
    
    /* Allocate new repetition in IOA */
    {
      long size; /* size of new repetition */
      size = LongRepSize(newRange);
      Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
    }

    if (newRep) {
      /* Assign structural part of new repetition */
      SETPROTO(newRep,LongRepPTValue);
      if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
      newRep->LowBorder = theRep->LowBorder;
      newRep->HighBorder = newRange;
      
      /* Assign into theObj */
      AssignReference((long *) theObj + offset, (Item *) newRep);
      
      /* Copy contents of old rep to new rep as longs */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      Ck(theRep); Ck(newRep); Ck(theObj);
      return;
    }
  }
}

ParamObjOffRange(ExtVR8)
{
  DeclReference1(ValRep *, theRep);
  DeclReference2(ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  
  FetchObjOffRange();
  
  DEBUG_CODE(NumExtVR8++);
  Ck(theObj);
  
  newRep = (ValRep *)0;
  theRep = *(ValRep **) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;
  
  copyRange = (DoubleRepBodySize((add < 0) ? newRange : oldRange))>>2;
  
  while (1) {
    if (newRange > LARGE_REP_SIZE) {
      newRep = LVRAXAlloc(DoubleRepPTValue, oldRange, newRange);
      if (newRep) {
	*(ValRep **) ((long *) theObj + offset) = newRep;
	/* Copy old rep */
	for (i = 0; i < copyRange; ++i){
          newRep->Body[i] = theRep->Body[i];
	}
	Ck(theRep); Ck(newRep); Ck(theObj);
	return;
      }
    }

    /* Allocate new repetition in IOA */
    {
      long size; /* size of new repetition */
      size = DoubleRepSize(newRange);
      Protect2(theObj, theRep, newRep = (ValRep *) IOATryAlloc(size));
    }

    if (newRep) {
      /* Assign structural part of new repetition */
      SETPROTO(newRep,DoubleRepPTValue);
      if (IOAMinAge!=0) {
	newRep->GCAttr = IOAMinAge;
      }
      newRep->LowBorder = theRep->LowBorder;
      newRep->HighBorder = newRange;
      
      /* Assign into theObj */
      AssignReference((long *) theObj + offset, (Item *) newRep);
      
      /* Copy contents of old rep to new rep as longs */
      for (i = 0; i < copyRange; ++i){
	newRep->Body[i] = theRep->Body[i];
      }
      Ck(theRep); Ck(newRep); Ck(theObj);
      return;
    }
  }
}

/****** Object Repetitions *******/

#define REP    ((ObjectRep *)theRep)
#define NEWREP ((ObjectRep *)newRep)

ParamObjOffRange(ExtVRI)
{
  DeclReference1(ValRep *, theRep);
  DeclReference2(ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  FetchObjOffRange();

  DEBUG_CODE(NumExtVRI++);
  Ck(theObj);

  newRep = (ValRep *)0;
  theRep = *(ValRep **) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;

  copyRange = (DynObjectRepSize((add < 0) ? newRange : oldRange)
	       - headsize(ObjectRep)) >> 2;
  size = DynObjectRepSize(newRange);

  /* Allocate new repetition */
  
  /* FIXME: AOA alloc missing */

  Protect2(theObj, theRep, newRep = (ValRep *) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  SETPROTO(newRep,DynItemRepPTValue);
  if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  NEWREP->iProto = REP->iProto;
  NEWREP->iOrigin = REP->iOrigin;

  /* Assign into theObj */
  AssignReference((long *) theObj + offset, (Item *) newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
#ifdef MT
    AssignReference((long*)&NEWREP->Body[i], (Item *)REP->Body[i]);
#else
    NEWREP->Body[i] = REP->Body[i];
    /* No need to use AssignReference: NEWREP is in IOA */
#endif
  }

  if (add>0){
    /* Allocate/Initialize new extra elements */

    while(--add>=0){
      Item *item;
#ifdef sparc
#ifdef MT
      Protect2(theRep, newRep,
	       item = (Item *)
	              CallVEntry((void (*)())REP->iProto,REP->iOrigin));
#else
      Protect2(theRep, newRep,
	       item = OAlloI((Object *) REP->iOrigin, 0, REP->iProto, 0, 0));
#endif /* MT */
#endif
#ifdef hppa
      Protect2(theRep, newRep,
	       item = CAlloI((Object *) REP->iOrigin, REP->iProto));
#endif
      AssignReference((long *)((long)&NEWREP->Body + (oldRange+add)*4), item);
    }
  }
  Ck(theRep); Ck(newRep); Ck(theObj);
}

ParamObjOffRange(ExtVRC)
{
  DeclReference1(ValRep *, theRep);
  DeclReference2(ValRep *, newRep);
  long add = range;
  long oldRange; /* range of old repetition */
  long newRange; /* Range of new repetition */
  long copyRange; /* Number of LONGS to copy from old rep */
  long i;
  long size; /* size of new repetition */
  
  FetchObjOffRange();

  DEBUG_CODE(NumExtVRC++);
  Ck(theObj);

  newRep = (ValRep *)0;
  theRep = *(ValRep **) ((long *) theObj + offset);
  oldRange = theRep->HighBorder;
  newRange = oldRange + add; /* Range of new repetition */
  
  if (newRange < 0) newRange = 0;

  copyRange = (DynObjectRepSize((add < 0) ? newRange : oldRange) 
	       - headsize(ObjectRep)) >> 2;
  size = DynObjectRepSize(newRange);

  /* Allocate new repetition */
  
  /* FIXME: AOA alloc missing */

  Protect2(theObj, theRep, newRep = (ValRep *) IOAalloc(size));
  
  /* Assign structural part of new repetition */
  SETPROTO(newRep,DynCompRepPTValue);
  if (IOAMinAge!=0) newRep->GCAttr = IOAMinAge;
  newRep->LowBorder = theRep->LowBorder;
  newRep->HighBorder = newRange;
  NEWREP->iProto = REP->iProto;
  NEWREP->iOrigin = REP->iOrigin;

  /* Assign into theObj */
  AssignReference((long *) theObj + offset, (Item *) newRep);
  
  /* Copy contents of old rep to new rep */
  for (i = 0; i < copyRange; ++i){
#ifdef MT
    AssignReference((long*)&NEWREP->Body[i], (Item *)REP->Body[i]);
#else
    NEWREP->Body[i] = REP->Body[i];
    /* No need to use AssignReference: NEWREP is in IOA */
#endif
  }

  if (add>0){
    /* Allocate/Initialize new extra elements */

    while(--add>=0){
      Component *comp;

#ifdef sparc
#ifdef MT
      Protect2(theRep, newRep,
	       comp = CallAlloC(REP->iProto, REP->iOrigin));
#else
      Protect2(theRep, newRep,
	       comp = OAlloC((Object *) REP->iOrigin, 0, REP->iProto, 0, 0));
#endif /* MT */
#endif
#ifdef hppa
      Protect2(theRep, newRep,
	       comp = CAlloC((Object *) REP->iOrigin, REP->iProto));
#endif

      AssignReference((long *)((long)&NEWREP->Body + (oldRange+add)*4), 
		      (Item *)comp);
    }
  }
  Ck(theRep); Ck(newRep); Ck(theObj);
}
