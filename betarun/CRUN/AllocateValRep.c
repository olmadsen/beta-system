/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

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

    do {
      Ck(theObj);
      Size = ByteRepSize(range);

      if (range > LARGE_REP_SIZE || Size>IOAMAXSIZE) {
        theRep = (ValRep *) LVRACAlloc(ByteRepPTValue, range);
        if (theRep) {
	  Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
	  *(ValRep **)((char *)theObj + offset) = theRep;
	  return;
        }
      }

      Protect(theObj, theRep = (ValRep *) IOATryAlloc(Size));
      if (theRep) {
	SETPROTO(theRep,ByteRepPTValue);
	if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
	theRep->LowBorder = 1;
	theRep->HighBorder = range;
	
	AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
	
	Ck(theObj); Ck(theRep);
      }
    } while (!theRep);
}

ParamThisOffRange(AlloVR2)
{
  DeclReference1(ValRep *, theRep);
  register unsigned Size;
  FetchThisOffRange();

  DEBUG_CODE(NumAlloVR2++);
  if (range < 0) range = 0;

  do {
    Ck(theObj);
    Size = ShortRepSize(range);

    if (range > LARGE_REP_SIZE|| Size>IOAMAXSIZE) {
      theRep = (ValRep *) LVRACAlloc(ShortRepPTValue, range);
      if (theRep) {
	Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
	*(ValRep **)((char *)theObj + offset) = theRep;
	return;
      }
    }

    Protect(theObj, theRep = (ValRep *) IOATryAlloc(Size));
    
    if (theRep) {
      SETPROTO(theRep,ShortRepPTValue);
      if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      theRep->LowBorder = 1;
      theRep->HighBorder = range;
      
      AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
      Ck(theObj); Ck(theRep);
    }
  } while (!theRep);

}

ParamThisOffRange(AlloVR4)
{
  DeclReference1(ValRep *, theRep);
  register unsigned Size;
  FetchThisOffRange();

  DEBUG_CODE(NumAlloVR4++);
  if (range < 0) range = 0;

  do {
    Ck(theObj);
    Size = LongRepSize(range);

    if (range > LARGE_REP_SIZE|| Size>IOAMAXSIZE) {
      theRep = (ValRep *) LVRACAlloc(LongRepPTValue, range);
      if (theRep) {
	Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
	*(ValRep **)((char *)theObj + offset) = theRep;
	return;
      }
    }

    Protect(theObj, theRep = (ValRep *) IOATryAlloc(Size));
    
    if (theRep) {
      SETPROTO(theRep,LongRepPTValue);
      if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      theRep->LowBorder = 1;
      theRep->HighBorder = range;
      
      AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
      Ck(theObj); Ck(theRep);
    }
  } while (!theRep);
}

ParamThisOffRange(AlloVR8)
{
  DeclReference1(ValRep *, theRep);
  register unsigned Size;
  FetchThisOffRange();

  DEBUG_CODE(NumAlloVR8++);
  if (range < 0) range = 0;

  do {
    Ck(theObj);
    Size= DoubleRepSize(range);

    if (range > LARGE_REP_SIZE|| Size>IOAMAXSIZE) {
      theRep = (ValRep *) LVRACAlloc(DoubleRepPTValue, range);
      if (theRep) {
	Claim(theRep->HighBorder==range&&theRep->LowBorder==1, "LVRA structure ok");
	*(ValRep **)((char *)theObj + offset) = theRep;
	return;
      }
    }

    Protect(theObj, theRep = (ValRep *) IOATryAlloc(Size));
    
    if (theRep) {
      SETPROTO(theRep,DoubleRepPTValue);
      if (IOAMinAge!=0) theRep->GCAttr = IOAMinAge;
      theRep->LowBorder = 1;
      theRep->HighBorder = range;
      
      AssignReference((long *)((char *)theObj + offset), (Item *) theRep);
      Ck(theObj); Ck(theRep);
    }
  } while (!theRep);
}
