/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: objectsize.c,v $, rel: %R%, date: $Date: 1992-08-19 11:57:05 $, SID: $Revision: 1.12 $
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
      return RefRepSize(toRefRep(theObj)->HighBorder) >> 2;

    case (int) ComponentPTValue:
      return ComponentSize(ComponentItem(theObj)->Proto->Size) >> 2;

    case (int) StackObjectPTValue:
      return StackObjectSize(toStackObject(theObj)->ObjectSize);

    case (int) StructurePTValue:
      return StructureSize >> 2;
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return theProto->Size;
}
