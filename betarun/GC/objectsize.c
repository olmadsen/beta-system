/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: objectsize.c,v $, rel: %R%, date: $Date: 1992-06-03 15:10:47 $, SID: $Revision: 1.5 $
 * by Lars Bak
 */
#include "beta.h"

/* ObjectSize returns the size of an object in number of BYTES (used to be longs). */
long ObjectSize(theObj)
  ref(Object) theObj;
{ 
  ref(ProtoType) theProto = theObj->Proto;

  if( (long) theProto < 0 ){
    switch((long) theProto){
    case ByteRepPTValue:
      return headsize(ValRep) + toValRep(theObj)->HighBorder;
    case ValRepPTValue:
      return headsize(ValRep) + toValRep(theObj)->HighBorder*4;
    case RefRepPTValue:
      return headsize(RefRep) + toRefRep(theObj)->HighBorder*4;
    case ComponentPTValue:
      return headsize(Component)
	+ (ComponentItem(theObj)->Proto->Size + 1)*4;
    case StackObjectPTValue:
      return headsize(StackObject)
	+ toStackObject(theObj)->ObjectSize*4;
    case StructurePTValue:
      return headsize(Structure);
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return (theProto->Size + 1)*4;
}
