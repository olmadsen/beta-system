/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: objectsize.c,v $, rel: %R%, date: $Date: 1992-06-08 15:17:24 $, SID: $Revision: 1.7 $
 * by Lars Bak
 */
#include "beta.h"

/* ObjectSize returns the size of an object in number of LONGS. */
long ObjectSize(theObj)
  ref(Object) theObj;
{ 
  ref(ProtoType) theProto = theObj->Proto;

  if( (long) theProto < 0 ){
    switch((long) theProto){
    case ByteRepPTValue:
      /* BodySize= ((Range+1+3)/4): One byte extra for \0 in strings and multiple of 4 */
      return (headsize(ValRep) + (toValRep(theObj)->HighBorder+4)) >> 2;
    case ValRepPTValue:
      return (headsize(ValRep)>>2) + toValRep(theObj)->HighBorder;
    case RefRepPTValue:
      return (headsize(RefRep)>>2) + toRefRep(theObj)->HighBorder;
    case ComponentPTValue:
      return (headsize(Component)>>2)
	+ (ComponentItem(theObj)->Proto->Size + 1);
    case StackObjectPTValue:
      return (headsize(StackObject)>>2)
	+ toStackObject(theObj)->ObjectSize;
    case StructurePTValue:
      return (headsize(Structure)>>2);
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return (theProto->Size + 1);
}
