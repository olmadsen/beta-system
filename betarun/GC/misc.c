/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: misc.c,v $, rel: %R%, date: $Date: 1991-02-11 14:28:06 $, SID: $Revision: 1.3 $
 * by Lars Bak.
 */

#include "beta.h"

BetaExit( number )
     int number;
{
  InfoS_End();
#ifdef apollo
  AsmExit( number );
#else
  exit( number );
#endif
}

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
     switch( (long) aObj->Proto){
       case ComponentPTValue:   return ComponentType;   break;
       case StackObjectPTValue: return StackObjectType; break;
       case ValRepPTValue:      return ValRepType;      break;
       case RefRepPTValue:      return RefRepType;      break;
       case StructurePTValue:   return StructureType;   break;
     }
  }else return ItemType;
}

BetaError(errorNo, theObj)
  int errorNo;
  ref(Object) theObj;
{
  if( errorNo < 0 ){
    StackEnd = (ptr(long)) &theObj; StackEnd++;     
    DisplayBetaStack( errorNo, theObj);  
  }
  BetaExit(-1);
}

Claim( expr, message)
  int  expr;
  ptr(char) message;
{
  if( expr == 0 ){
    fprintf( output,"Assumption (%s) failed!\n", message);
    BetaExit(-1);
  }
}


