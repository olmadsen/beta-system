/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: objectsize.c,v $, rel: %R%, date: $Date: 1992-07-20 16:31:51 $, SID: $Revision: 1.9 $
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
      /* BodySize= ((Range+3)/4): multiple of 4 */
      return (headsize(ValRep) + (toValRep(theObj)->HighBorder+3)) >> 2;
    case (int) ByteRepPTValue:
      /* BodySize= ((Range+1+3)/4): One byte extra for \0 in strings and multiple of 4 */
      return (headsize(ValRep) + (toValRep(theObj)->HighBorder+4)) >> 2;
    case (int) DoubleRepPTValue:
      /* BodySize= ((2*Range+3)/4): two bytes for each and multiple of 4 */
      return (headsize(ValRep) + (2*toValRep(theObj)->HighBorder+3)) >> 2;
    case (int) ValRepPTValue:
      return (headsize(ValRep)>>2) + toValRep(theObj)->HighBorder;
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
