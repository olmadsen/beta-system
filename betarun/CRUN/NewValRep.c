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
  
  DEBUG_CODE(NumNewVR1++);
  Ck(theObj);
  SaveVar(theObj);
  
#ifdef hppa
  range = (long)getR2Reg();
  pushReference(getThisReg());
  setThisReg(theObj);
  setD0Reg(offset * 4);
  setD1Reg(range)
#endif /* hppa */

#ifdef sparc
  CAlloVR1(theObj, 0, offset*4, 0, 0, range);
#else /* sparc */
  AlloVR1(theObj, offset*4, range);
#endif /* sparc */
  
  RestoreVar(theObj);

#ifdef hppa
  setThisReg(popReference());
#endif
} /* NewVR1 */

ParamObjOffRange(NewVR2)
{
  GCable_Entry();
  
  DEBUG_CODE(NumNewVR2++);
  Ck(theObj);
  SaveVar(theObj);
  
#ifdef hppa
  range = (long)getR2Reg();
  pushReference(getThisReg());
  setThisReg(theObj);
  setD0Reg(offset * 4);
  setD1Reg(range)
#endif /* hppa */

#ifdef sparc
  CAlloVR2(theObj, 0, offset*4, 0, 0, range);
#else /* sparc */
  AlloVR2(theObj, offset*4, range);
#endif /* sparc */
  
  RestoreVar(theObj);

#ifdef hppa
  setThisReg(popReference());
#endif
} /* NewVR2 */

ParamObjOffRange(NewVR4)
{
  GCable_Entry();
  
  DEBUG_CODE(NumNewVR4++);
  Ck(theObj);
  SaveVar(theObj);
  
#ifdef hppa
  range = (long)getR2Reg();
  pushReference(getThisReg());
  setThisReg(theObj);
  setD0Reg(offset * 4);
  setD1Reg(range)
#endif /* hppa */

#ifdef sparc
  CAlloVR4(theObj, 0, offset*4, 0, 0, range);
#else /* sparc */
  AlloVR4(theObj, offset*4, range);
#endif /* sparc */
  
  RestoreVar(theObj);

#ifdef hppa
  setThisReg(popReference());
#endif
} /* NewVR4 */

ParamObjOffRange(NewVR8)
{
  GCable_Entry();
  
  DEBUG_CODE(NumNewVR8++);
  Ck(theObj);
  SaveVar(theObj);
  
#ifdef hppa
  range = (long)getR2Reg();
  pushReference(getThisReg());
  setThisReg(theObj);
  setD0Reg(offset * 4);
  setD1Reg(range)
#endif /* hppa */

#ifdef sparc
  CAlloVR8(theObj, 0, offset*4, 0, 0, range);
#else /* sparc */
  AlloVR8(theObj, offset*4, range);
#endif /* sparc */
  
  RestoreVar(theObj);

#ifdef hppa
  setThisReg(popReference());
#endif
} /* NewVR8 */


/****** Object Repetitions *******/

#define REP ((struct ObjectRep *)theRep)

#ifdef hppa
#define SetObjOriginProtoOffRange() \
  setD1Reg(range);                  \
  setOriginReg(REP->iOrigin);       \
  setCallReg(REP->iProto);          \
  setThisReg(theObj);               \
  setD0Reg(4*offset);
#else
#define SetObjOriginProtoOffRange() 
#endif

ParamObjOffRange(NewVRI)
{
  DeclReference1(struct ValRep *, theRep);
  GCable_Entry();
  
  DEBUG_CODE(NumNewVRI++);
  Ck(theObj);
  theRep = (casthandle(ValRep)theObj)[offset];
  SaveVar(theObj);
  
#ifdef hppa
  range = (long)getR2Reg();
  pushReference(getThisReg());
  setThisReg(theObj);
  setD0Reg(offset * 4);
  setD1Reg(range);
#endif /* hppa */

#ifdef sparc
  CAlloVRI(REP->iOrigin, theObj, 4*offset, range, 0, REP->iProto);
#else /* sparc */
  SetObjOriginProtoOffRange();
  AlloVRI(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
#endif /* sparc */
  
  RestoreVar(theObj);

#ifdef hppa
  setThisReg(popReference());
#endif
} /* NewVRI */


ParamObjOffRange(NewVRC)
{
  DeclReference1(struct ValRep *, theRep);
  GCable_Entry();
  
  DEBUG_CODE(NumNewVRC++);
  Ck(theObj);
  theRep = (casthandle(ValRep)theObj)[offset];
  SaveVar(theObj);
  
#ifdef hppa
  range = (long)getR2Reg();
  pushReference(getThisReg());
  setThisReg(theObj);
  setD0Reg(offset * 4);
  setD1Reg(range);
#endif /* hppa */

#ifdef sparc
  CAlloVRC(REP->iOrigin, theObj, 4*offset, range, 0, REP->iProto);
#else /* sparc */
  SetObjOriginProtoOffRange();
  AlloVRC(REP->iOrigin, theObj, 4*offset, REP->iProto, range);
#endif /* sparc */
  
  RestoreVar(theObj);

#ifdef hppa
  setThisReg(popReference());
#endif
} /* NewVRC */

