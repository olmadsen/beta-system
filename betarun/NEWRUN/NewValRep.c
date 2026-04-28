/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void NewVR1(Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  ValRep * theRep;
  
  DEBUG_CODE(NumNewVR1++);
  Ck(theObj);
  theRep = ((ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR1(offset*4, range, theObj, SP);
} /* NewVR1 */

void NewVR2(Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  ValRep * theRep;
  
  DEBUG_CODE(NumNewVR2++);
  Ck(theObj);
  theRep = ((ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR2(offset*4, range, theObj, SP);
} /* NewVR2 */

void NewVR4(Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  ValRep * theRep;
  
  DEBUG_CODE(NumNewVR4++);
  Ck(theObj);
  theRep = ((ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR4(offset*4, range, theObj, SP);
} /* NewVR4 */

void NewVR8(Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  ValRep * theRep;
  
  DEBUG_CODE(NumNewVR8++);
  Ck(theObj);
  theRep = ((ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR8(offset*4, range, theObj, SP);
} /* NewVR8 */

void NewVRI(Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  ObjectRep * theRep;
  
  DEBUG_CODE(NumNewVRI++);
  Ck(theObj);
  theRep = ((ObjectRep **)theObj)[offset];
  Ck(theRep);
  AlloVRI(theRep->iOrigin, theRep->iProto, offset*4, range, theObj, SP);
} /* NewVRI */

void NewVRC(Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  ObjectRep * theRep;
  
  DEBUG_CODE(NumNewVRC++);
  Ck(theObj);
  theRep = ((ObjectRep **)theObj)[offset];
  Ck(theRep);
  AlloVRC(theRep->iOrigin, theRep->iProto, offset*4, range, theObj, SP);
} /* NewVRC */

