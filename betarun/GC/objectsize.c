/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: objectsize.c,v $, rel: %R%, date: $Date: 1992-06-02 15:25:06 $, SID: $Revision: 1.3 $
 * by Lars Bak
 */
#include "beta.h"

/* ObjectSize returns the size of an object in number of longs. */
long ObjectSize(theObj)
  ref(Object) theObj;
{ 
  ref(ProtoType) theProto = theObj->Proto;

  if( (long) theProto < 0 ){
    switch((long) theProto){
    case ByteRepPTValue:
      printf("OOOPS: objectsize of ByteRep\n");
      return ValRepStructSize + toValRep(theObj)->HighBorder/4;
    case ValRepPTValue:
      return ValRepStructSize + toValRep(theObj)->HighBorder;
    case RefRepPTValue:
      return RefRepStructSize + toRefRep(theObj)->HighBorder;
    case ComponentPTValue:
      return ComponentStructSize
	+ ComponentItem(theObj)->Proto->Size + 1;
    case StackObjectPTValue:
      return StackObjectStructSize
	+ toStackObject(theObj)->ObjectSize;
    case StructurePTValue:
      return StructureStructSize;
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return theProto->Size + 1;
}
