/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

ParamObjOffRange(NewVR1)
{
  GCable_Entry();
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR1++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR1(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR1(offset*4, range, theObj);
#endif
#ifdef crts
  AlloVR1(theObj, offset*4, range);
#endif

} /* NewVR1 */

ParamObjOffRange(NewVR2)
{
  GCable_Entry();
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR2++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR2(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR2(offset*4, range, theObj);
#endif
#ifdef crts
  AlloVR2(theObj, offset*4, range);
#endif

} /* NewVR2 */

ParamObjOffRange(NewVR4)
{
  GCable_Entry();
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR4++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR4(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR4(offset*4, range, theObj);
#endif
#ifdef crts
  AlloVR4(theObj, offset*4, range);
#endif

} /* NewVR4 */

ParamObjOffRange(NewVR8)
{
  GCable_Entry();
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVR8++);
  Ck(theObj);
  
#ifdef sparc
  CAlloVR8(theObj, 0, offset*4, 0, 0, range);
#endif
#ifdef hppa
  CAlloVR8(offset*4, range, theObj);
#endif
#ifdef crts
  AlloVR8(theObj, offset*4, range);
#endif

} /* NewVR8 */


/****** Object Repetitions *******/

ParamObjOffRange(NewVRI)
{
  DeclReference1(struct ObjectRep *, theRep);
  GCable_Entry();
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVRI++);
  Ck(theObj);
  theRep = (casthandle(ObjectRep)theObj)[offset];
  
#ifdef sparc
  CAlloVRI(theRep->iOrigin, theObj, 4*offset, range, 0, theRep->iProto);
#endif
#ifdef hppa
  CAlloVRI(theRep->iOrigin, theObj, 4*offset, range, theRep->iProto);
#endif
#ifdef crts
  AlloVRI(theRep->iOrigin, theObj, 4*offset, range, theRep->iProto);
#endif
  
} /* NewVRI */

ParamObjOffRange(NewVRC)
{
  DeclReference1(struct ObjectRep *, theRep);
  GCable_Entry();
  FetchObjOffRange();
  
  DEBUG_CODE(NumNewVRC++);
  Ck(theObj);
  theRep = (casthandle(ObjectRep)theObj)[offset];
  
#ifdef sparc
  CAlloVRC(theRep->iOrigin, theObj, 4*offset, range, 0, theRep->iProto);
#endif
#ifdef hppa
  CAlloVRC(theRep->iOrigin, theObj, 4*offset, range, theRep->iProto);
#endif
#ifdef crts
  AlloVRC(theRep->iOrigin, theObj, 4*offset, range, theRep->iProto);
#endif
  
} /* NewVRC */



