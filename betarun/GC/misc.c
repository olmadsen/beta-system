/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * misc.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"

#ifdef macintosh
#include <CursorCtl.h>
#endif macintosh

long isObject( theObj)
  ref(Object) theObj;
{ 
#if defined(sparc) || defined(hppa)
    /* For the SPARC isObject also checks alignment constraints */
    if (((unsigned)theObj & 7) != 0)
      return FALSE;
#endif
  /* Check that theObj is non-negative */
  if ((long) theObj <= 0) return FALSE;

  /* check that the GCAttr of the object is valid. */
  if( inBetaHeap(theObj->Proto) ) return FALSE;

  if( theObj->Proto == 0 ) return FALSE;

  if( inAOA(theObj) && (isStatic(theObj->GCAttr) || (theObj->GCAttr == 0)) ) 
    return TRUE;
  if( isStatic(theObj->GCAttr) || isAutonomous(theObj->GCAttr) ){
    return TRUE;
  }else{
    if( inToSpace(theObj->GCAttr) || inAOA(theObj->GCAttr) ){
      return TRUE;
    }else return FALSE;
  }
}

long inBetaHeap( theObj)
  ref(Object) theObj;
{ 
#if defined(sparc) || defined(hppa)
    /* For the SPARC inBetaHeap also checkes alignment constraints */
    if (((unsigned)theObj & 7) != 0)
      return FALSE;
#endif
  if ((long) theObj <= 0) return FALSE;
  if (inIOA( theObj)) return TRUE;
  if (inAOA( theObj)) return TRUE;
  if (inLVRA( theObj)) return TRUE;
  return FALSE;
}

long ObjectType(aObj)
  ref(Object) aObj;
{
  if( isSpecialProtoType(aObj->Proto)){
     switch( (long) aObj->Proto){
       case (long) ComponentPTValue:   return ComponentType; 
       case (long) StackObjectPTValue: return StackObjectType;
       case (long) WordRepPTValue:     return WordRepType;    
       case (long) DoubleRepPTValue:   return DoubleRepType;    
       case (long) ByteRepPTValue:     return ByteRepType;    
       case (long) ValRepPTValue:      return ValRepType;    
       case (long) RefRepPTValue:      return RefRepType;    
       case (long) StructurePTValue:   return StructureType; 
       case (long) DopartObjectPTValue:      return DopartType; 
     }
  }else return ItemType;
}

void Claim( expr, message)
  long  expr;
  ptr(char) message;
{
  if( expr == 0 ){
    fprintf( output,"Assumption (%s) failed!\n", message);
    fprintf( output,"IOA: 0x%X, IOATop: 0x%X, ToSpace: 0x%X\n", IOA, IOATop, ToSpace);
    BetaExit(0);
  }
}

#ifdef macintosh
long gcRotateCursor=0;
void InitTheCursor()   { if(StandAlone == 0 || gcRotateCursor) InitCursorCtl(0); }
void RotateTheCursor() { if(StandAlone == 0 || gcRotateCursor) SpinCursor(32); }
void RotateTheCursorBack() { if(StandAlone == 0 || gcRotateCursor) SpinCursor(-32); }
#endif


#ifdef RTDEBUG

void NotifyRTDebug()
{
  fprintf(output, "RTS: Runtime routines perform consistency checks on registers.\n");
}

long CkP0;
ref(Object) CkP1;
ref(Object) CkP2;
ref(Object) CkP3;
ref(Object) CkP4;
ref(Object) CkP5;

void RegError(long pc, char *reg, ref(Object) value)
{
  fprintf(output, "\nIllegal value for GC register at PC=0x%x: %s=0x%x\n", 
	  pc, reg, value);
}

long CheckCell(theCell)
    ref(Object) theCell;
{
  if(theCell) {
    if (inBetaHeap(theCell)) {
      if (isObject(theCell) || isValRep(theCell)) 
	return TRUE;
      return FALSE;
    }
  }
  return TRUE;
}

#if (defined(linux) || defined(nti))
void CheckRegisters()
{
  extern ref(Object) a2; /*asm("a2");*/
  extern ref(Object) a3; /*asm("a3");*/
  extern ref(Object) a4; /*asm("a4");*/
  long pc = CkP0;
  ref(Object) ebp = CkP1;
  ref(Object) esi = CkP2;
  ref(Object) edx = CkP3;
  ref(Object) edi = CkP4;
  if (!CheckCell(a2)) RegError(pc, "_a2", a2);
  if (!CheckCell(a3)) RegError(pc, "_a3", a3);
  if (!CheckCell(a4)) RegError(pc, "_a4", a4);
  if (!CheckCell(ebp)) RegError(pc, "ebp", ebp);
  if (!CheckCell(esi)) RegError(pc, "esi", esi);
  if (!CheckCell(edx)) RegError(pc, "edx", edx);
  if (!CheckCell(edi)) RegError(pc, "edi", edi);
}
#endif /* linux & nti */

#ifdef mc68020
void CheckRegisters()
{
  long pc = CkP0;
  ref(Object) a0 = CkP1;
  ref(Object) a1 = CkP2;
  ref(Object) a2 = CkP3;
  ref(Object) a3 = CkP4;
  ref(Object) a3 = CkP5;
  if (!CheckCell(a0)) RegError(pc, "a0", a0);
  if (!CheckCell(a1)) RegError(pc, "a1", a1);
  if (!CheckCell(a2)) RegError(pc, "a2", a2);
  if (!CheckCell(a3)) RegError(pc, "a3", a3);
  if (!CheckCell(a4)) RegError(pc, "a4", a4);
}
#endif /* mc68020*/

 
#endif /* RTDEBUG */
