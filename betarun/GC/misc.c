/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: misc.c,v $, rel: %R%, date: $Date: 1992-08-19 11:57:50 $, SID: $Revision: 1.12 $
 * by Lars Bak.
 */

#include "beta.h"
#include "misc.h"

#ifdef macintosh
#include <CursorCtl.h>
#endif macintosh

long isObject( theObj)
  ref(Object) theObj;
{ 
  /* check that the GCAttr of the object is valid. */
  if( inBetaHeap(theObj->Proto) ) return FALSE;
  if( theObj->Proto == 0 ) return FALSE;
#ifdef AO_Area
  if( inAOA(theObj) && (isStatic(theObj->GCAttr) || (theObj->GCAttr == 0)) ) 
    return TRUE;
#endif
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
#ifdef sparc
    /* For the SPARC inBetaHeap also checkes alignment constraints */
    if ((unsigned)theObj % 8 != 0)
      return FALSE;
#endif
  if( inIOA( theObj)) return TRUE;
#ifdef AO_Area
  if( inAOA( theObj)) return TRUE;
#endif
#ifdef LVR_Area
  if( inLVRA( theObj)) return TRUE;
#endif
  return FALSE;
}

long ObjectType(aObj)
  ref(Object) aObj;
{
  if( isSpecialProtoType(aObj->Proto)){
     switch( (int) aObj->Proto){
       case (int) ComponentPTValue:   return ComponentType; 
       case (int) StackObjectPTValue: return StackObjectType;
       case (int) WordRepPTValue:     return WordRepType;    
       case (int) DoubleRepPTValue:   return DoubleRepType;    
       case (int) ByteRepPTValue:     return ByteRepType;    
       case (int) ValRepPTValue:      return ValRepType;    
       case (int) RefRepPTValue:      return RefRepType;    
       case (int) StructurePTValue:   return StructureType; 
     }
  }else return ItemType;
}

void Claim( expr, message)
  int  expr;
  ptr(char) message;
{
  if( expr == 0 ){
    fprintf( output,"Assumption (%s) failed!\n", message);
    fprintf( output,"IOA: %X, IOATop: %X\n", IOA, IOATop);
    BetaExit(0);
  }
}

#ifdef macintosh
extern int StandAlone;
InitTheCursor()   { if(StandAlone == 0) InitCursorCtl(0); }
RotateTheCursor() { if(StandAlone == 0) RotateCursor(32); }
#endif
