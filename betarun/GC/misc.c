/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * misc.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#ifdef macintosh
#include <CursorCtl.h>
#endif /* macintosh */

#ifdef RTDEBUG
void Illegal()
{ 
  /* used to break in! */
}
#endif

long isObject( theObj)
  ref(Object) theObj;
{ 
#if defined(sparc) || defined(hppa) || defined(crts)
    /* For the SPARC isObject also checks alignment constraints */
    if (((unsigned)theObj & 7) != 0)
      return FALSE;
#endif /* defined(sparc) || defined(hppa) || defined(crts) */
  /* Check that theObj is non-negative */
  if (isNegativeProto(theObj) || theObj == NULL) return FALSE;

  /* check that the GCAttr of the object is valid. */
  if( inBetaHeap((ref(Object))(theObj->Proto)) ) return FALSE;

  if( theObj->Proto == 0 ) return FALSE;

  if( inAOA(theObj) && ((isStatic(theObj->GCAttr)) || (theObj->GCAttr == 0)) ) 
    return TRUE;
  if( (isStatic(theObj->GCAttr)) || isAutonomous(theObj->GCAttr) ){
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
#if defined(sparc) || defined(hppa) || defined(crts)
    /* For the SPARC inBetaHeap also checkes alignment constraints */
    if (((unsigned)theObj & 7) != 0)
      return FALSE;
#endif /* defined(sparc) || defined(hppa) || defined(crts) */
  if (isNegativeProto(theObj) || theObj == NULL) return FALSE;
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
    default: 
      fprintf(output, "ObjectType: unknown object\n");
      fflush(output);
      return 0;
    }
  }
  else return ItemType;
}

void Claim( expr, message)
  long  expr;
  ptr(char) message;
{
  if( expr == 0 ){
    fprintf(output, "Assumption (%s) failed!\n", message);
    fprintf(output,
	    "IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
	    (int)IOA, (int)IOATop, (int)IOALimit);
    fprintf(output,
	    "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	    (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
#ifdef RTDEBUG
    Illegal(); /* Usefull to break in */
#endif
    BetaExit(0);
  }
}

#ifdef macintosh
long gcRotateCursor=0;
void InitTheCursor()   { if(StandAlone == 0 || gcRotateCursor) InitCursorCtl(0); }
void RotateTheCursor() { if(StandAlone == 0 || gcRotateCursor) SpinCursor(32); }
void RotateTheCursorBack() { if(StandAlone == 0 || gcRotateCursor) SpinCursor(-32); }
#endif /* macintosh */


/* Only used in debug version, but declared unconditionally in Declaration.run */
void NotifyRTDebug() 
{
#ifdef RTDEBUG
  Notify("RTS: Runtime routines perform consistency checks on registers.");
#endif /* RTDEBUG */
}

/* Only used in debug version, but declared unconditionally in Declaration.run */
long CkP0;
ref(Object) CkP1;
ref(Object) CkP2;
ref(Object) CkP3;
ref(Object) CkP4;
ref(Object) CkP5;

#ifdef RTDEBUG
#if defined(mc68020)||defined(nti)||defined(linux)
static void RegError(long pc, char *reg, ref(Object) value)
{
  fprintf(output, "\nIllegal value for GC register at PC=0x%x: %s=0x%x\n", 
	  (int)pc, reg, (int)value);
  Illegal();
}

static long CheckCell(theCell)
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
#endif /* defined(mc68020)||defined(nti)||defined(linux) */
#endif /* RTDEBUG */

/* Only used in debug version, but declared unconditionally in Declaration.run */
void CheckRegisters()
{
#ifdef RTDEBUG
#if (defined(linux) || defined(nti))
  extern ref(Object) a2;
  extern ref(Object) a3;
  extern ref(Object) a4;
  long pc = CkP0 - 5; /* sizeof(call) = 1+4 bytes */
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
#endif /* (defined(linux) || defined(nti)) */
#ifdef mc68020
  long pc = CkP0;
  ref(Object) a0 = CkP1;
  ref(Object) a1 = CkP2;
  ref(Object) a2 = CkP3;
  ref(Object) a3 = CkP4;
  ref(Object) a4 = CkP5;
  if (!CheckCell(a0)) RegError(pc, "a0", a0);
  if (!CheckCell(a1)) RegError(pc, "a1", a1);
  if (!CheckCell(a2)) RegError(pc, "a2", a2);
  if (!CheckCell(a3)) RegError(pc, "a3", a3);
  if (!CheckCell(a4)) RegError(pc, "a4", a4);
#endif /* mc68020*/
#endif /* RTDEBUG */
}
