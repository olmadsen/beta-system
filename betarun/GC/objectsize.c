/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991 Mjolner Informatics Aps.
 * Mod: $RCSfile: objectsize.c,v $, rel: %R%, date: $Date: 1992-06-03 09:57:14 $, SID: $Revision: 1.4 $
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
      printf("OOOPS: objectsize of ByteRep\n");
      return ValRepStructSize + toValRep(theObj)->HighBorder;
    case ValRepPTValue:
      return ValRepStructSize + toValRep(theObj)->HighBorder*4;
    case RefRepPTValue:
      return RefRepStructSize + toRefRep(theObj)->HighBorder*4;
    case ComponentPTValue:
      return ComponentStructSize
	+ (ComponentItem(theObj)->Proto->Size + 1)*4;
    case StackObjectPTValue:
      return StackObjectStructSize
	+ toStackObject(theObj)->ObjectSize*4;
    case StructurePTValue:
      return StructureStructSize;
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return (theProto->Size + 1)*4;
}
