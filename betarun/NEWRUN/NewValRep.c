/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

void NewVR1(struct Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  struct ValRep * theRep;
  
  DEBUG_CODE(NumNewVR1++);
  Ck(theObj);
  theRep = ((struct ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR1(theObj, offset*4, range, SP);
} /* NewVR1 */

void NewVR2(struct Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  struct ValRep * theRep;
  
  DEBUG_CODE(NumNewVR2++);
  Ck(theObj);
  theRep = ((struct ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR2(theObj, offset*4, range, SP);
} /* NewVR2 */

void NewVR4(struct Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  struct ValRep * theRep;
  
  DEBUG_CODE(NumNewVR4++);
  Ck(theObj);
  theRep = ((struct ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR4(theObj, offset*4, range, SP);
} /* NewVR4 */

void NewVR8(struct Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  struct ValRep * theRep;
  
  DEBUG_CODE(NumNewVR8++);
  Ck(theObj);
  theRep = ((struct ValRep **)theObj)[offset];
  Ck(theRep);
  AlloVR8(theObj, offset*4, range, SP);
} /* NewVR8 */

void NewVRI(struct Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  struct ObjectRep * theRep;
  
  DEBUG_CODE(NumNewVRI++);
  Ck(theObj);
  theRep = ((struct ObjectRep **)theObj)[offset];
  Ck(theRep);
  AlloVRI(theRep->iOrigin, theRep->iProto, theObj, 4*offset, range, SP);
} /* NewVRI */

void NewVRC(struct Object *theObj, 
	    long offset /* in longs */,
	    long range,
	    long *SP)
{
  struct ObjectRep * theRep;
  
  DEBUG_CODE(NumNewVRC++);
  Ck(theObj);
  theRep = ((struct ObjectRep **)theObj)[offset];
  Ck(theRep);
  AlloVRC(theRep->iOrigin, theRep->iProto, theObj, 4*offset, range, SP);
} /* NewVRC */

