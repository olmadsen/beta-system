/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

/* parameters:
 *   primreg1 = off
 *   primreg2 = range, 
 *   primreg3 = this (SGI/PPC)
 *   primreg4 = SP, (SGI/PPC)
 */

ParamThisOffRange(AlloVR1)
{
    DeclReference1(ValRep *, theRep);
    register unsigned Size;
    FetchThisOffRange();
  
    if (range < 0) range = 0;

    DEBUG_CODE(NumAlloVR1++);

    Ck(theObj);
    Size = ByteRepSize(range);

    if (range > LARGE_REP_SIZE) {
        theRep = (ValRep *) LVRACAlloc(ByteRepPTValue, range);
        if (theRep) {
            Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
            *(ValRep **)((char *)theObj + offset) = theRep;
            return;
        }
    }

    Protect(theObj, theRep = (ValRep *) IOAalloc(Size));

    SETPROTO(theRep,ByteRepPTValue);
    if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
    theRep->LowBorder = 1;
    theRep->HighBorder = range;
  
    AssignReference((long *)((char *)theObj + offset), (Item *) theRep);

    Ck(theObj); Ck(theRep);
}

ParamThisOffRange(AlloVR2)
{
  DeclReference1(ValRep *, theRep);
  register unsigned Size;
  FetchThisOffRange();

  DEBUG_CODE(NumAlloVR2++);
  Ck(theObj);

  if (range < 0) range = 0;

  Size = ShortRepSize(range);

  if (range > LARGE_REP_SIZE) {
    theRep = (ValRep *) LVRACAlloc(ShortRepPTValue, range);
    if (theRep) {
      Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
      *(ValRep **)((char *)theObj + offset) = theRep;
      return;
    }
  }

  Protect(theObj, theRep = (ValRep *) IOAalloc(Size));

  SETPROTO(theRep,ShortRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;
  
  AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
  Ck(theObj); Ck(theRep);
}

ParamThisOffRange(AlloVR4)
{
  DeclReference1(ValRep *, theRep);
  register unsigned Size;
  FetchThisOffRange();

  DEBUG_CODE(NumAlloVR4++);
  Ck(theObj);

  if (range < 0)
    range = 0;

  Size = LongRepSize(range);

  if (range > LARGE_REP_SIZE) {
    theRep = (ValRep *) LVRACAlloc(LongRepPTValue, range);
    if (theRep) {
      Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
      *(ValRep **)((char *)theObj + offset) = theRep;
      return;
    }
  }

  Protect(theObj, theRep = (ValRep *) IOAalloc(Size));
  
  SETPROTO(theRep,LongRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;

  AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
  Ck(theObj); Ck(theRep);
}

ParamThisOffRange(AlloVR8)
{
  DeclReference1(ValRep *, theRep);
  register unsigned Size;
  FetchThisOffRange();

  DEBUG_CODE(NumAlloVR8++);
  Ck(theObj);

  if (range < 0)
    range = 0;

  Size= DoubleRepSize(range);

  if (range > LARGE_REP_SIZE) {
    theRep = (ValRep *) LVRACAlloc(DoubleRepPTValue, range);
    if (theRep) {
      Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
      *(ValRep **)((char *)theObj + offset) = theRep;
      return;
    }
  }

  Protect(theObj, theRep = (ValRep *) IOAalloc(Size));

  SETPROTO(theRep,DoubleRepPTValue);
  if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;

  AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
  Ck(theObj); Ck(theRep);
}

#endif /* MT */
