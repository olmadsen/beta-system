/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-93 Mjolner Informatics Aps.
 * objectsize.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */
#include "beta.h"

/* ObjectSize returns the size of an object in number of LONGS. */
long ObjectSize(theObj)
  ref(Object) theObj;
{ 
  ref(ProtoType) theProto = theObj->Proto;

  if( isNegativeProto(theProto) ){
    switch((long) theProto){
    case (long) WordRepPTValue:
      return WordRepSize(toValRep(theObj)->HighBorder) >> 2;

    case (long) ByteRepPTValue:
      return ByteRepSize(toValRep(theObj)->HighBorder) >> 2;

    case (long) DoubleRepPTValue:
      return DoubleRepSize(toValRep(theObj)->HighBorder) >> 2;

    case (long) ValRepPTValue:
      return ValRepSize(toValRep(theObj)->HighBorder) >> 2;

    case (long) RefRepPTValue:
      return RefRepSize(toRefRep(theObj)->HighBorder) >> 2;

    case (long) ComponentPTValue:
      return ComponentSize(ComponentItem(theObj)->Proto->Size) >> 2;

    case (long) StackObjectPTValue:
      return StackObjectSize(toStackObject(theObj)->BodySize) >> 2;

    case (long) StructurePTValue:
      return StructureSize >> 2;

    case (long) DopartObjectPTValue:
      return DopartObjectSize((cast(DopartObject)(theObj))->Size) >> 2;
#ifdef RTDEBUG
    default:
      fprintf(stderr, 
	      "ObjectSize: Error: Unknown ProtoType %d for object 0x%08x\n",
	      theProto, 
	      theObj);
      return 0;
#endif
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return theProto->Size;
}
