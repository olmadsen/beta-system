/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: objectsize.c,v $, rel: %R%, date: $Date: 1992-07-21 17:19:47 $, SID: $Revision: 1.10 $
 * by Lars Bak
 */
#include "beta.h"

/* ObjectSize returns the size of an object in number of LONGS. */
long ObjectSize(theObj)
  ref(Object) theObj;
{ 
  ref(ProtoType) theProto = theObj->Proto;

  if( (long) theProto < 0 ){
    switch((int) theProto){
    case (int) WordRepPTValue:
      return WordRepSize(toValRep(theObj)->HighBorder) >> 2;
    case (int) ByteRepPTValue:
      return ByteRepSize(toValRep(theObj)->HighBorder) >> 2;
    case (int) DoubleRepPTValue:
      return DoubleRepSize(toValRep(theObj)->HighBorder) >> 2;
    case (int) ValRepPTValue:
      return ValRepSize(toValRep(theObj)->HighBorder) >> 2;
    case (int) RefRepPTValue:
      return (headsize(RefRep)>>2) + toRefRep(theObj)->HighBorder;
    case (int) ComponentPTValue:
      return (headsize(Component)>>2)
	+ (ComponentItem(theObj)->Proto->Size + 1);
    case (int) StackObjectPTValue:
      return (headsize(StackObject)>>2)
	+ toStackObject(theObj)->ObjectSize;
    case (int) StructurePTValue:
      return (headsize(Structure)>>2);
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return (theProto->Size + 1);
}
