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
extern long StandAlone;
void InitTheCursor()   { if(StandAlone == 0) InitCursorCtl(0); }
void RotateTheCursor() { if(StandAlone == 0) SpinCursor(32); }
void RotateTheCursorBack() { if(StandAlone == 0) SpinCursor(-32); }
#endif
