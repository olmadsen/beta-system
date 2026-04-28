/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

#ifndef MT

ParamObjOffRange(NewVR1)
{
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR1++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR1(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR1(offset*4, range, theObj);
#endif

} /* NewVR1 */

ParamObjOffRange(NewVR2)
{
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR2++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR2(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR2(offset*4, range, theObj);
#endif

} /* NewVR2 */

ParamObjOffRange(NewVR4)
{
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR4++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR4(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR4(offset*4, range, theObj);
#endif

} /* NewVR4 */

ParamObjOffRange(NewVR8)
{
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR8++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR8(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR8(offset*4, range, theObj);
#endif

} /* NewVR8 */

#endif /* MT */


/****** Object Repetitions *******/

ParamObjOffRange(NewVRI)
{
  DeclReference1(ObjectRep *, theRep);
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVRI++);
  Ck(theObj);
  theRep = ((ObjectRep **)theObj)[offset];
  
#ifdef sparc
  CAlloVRI(theRep->iOrigin, theObj, 4*offset, range, 0, theRep->iProto);
#endif
#ifdef hppa
  CAlloVRI(theRep->iOrigin, theObj, 4*offset, range, theRep->iProto);
#endif
  
} /* NewVRI */

ParamObjOffRange(NewVRC)
{
  DeclReference1(ObjectRep *, theRep);
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVRC++);
  Ck(theObj);
  theRep = ((ObjectRep **)theObj)[offset];
  
#ifdef sparc
  CAlloVRC(theRep->iOrigin, theObj, 4*offset, range, 0, theRep->iProto);
#endif
#ifdef hppa
  CAlloVRC(theRep->iOrigin, theObj, 4*offset, range, theRep->iProto);
#endif
  
} /* NewVRC */
