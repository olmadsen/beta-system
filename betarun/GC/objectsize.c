/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1991-94 Mjolner Informatics Aps.
 * objectsize.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

/* ObjectSize returns the size of an object in number of LONGS. */
long ObjectSize(theObj)
  ref(Object) theObj;
{ 
  ref(ProtoType) theProto = theObj->Proto;

  if( isSpecialProtoType(theProto) ){
    switch(SwitchProto(theProto)){
    case SwitchProto(ShortRepPTValue):
      return ShortRepSize(toValRep(theObj)->HighBorder) >> 2;

    case SwitchProto(ByteRepPTValue):
      return ByteRepSize(toValRep(theObj)->HighBorder) >> 2;

    case SwitchProto(DoubleRepPTValue):
      return DoubleRepSize(toValRep(theObj)->HighBorder) >> 2;

    case SwitchProto(LongRepPTValue):
      return LongRepSize(toValRep(theObj)->HighBorder) >> 2;

    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      return DynObjectRepSize(((struct ObjectRep *)theObj)->HighBorder) >> 2;
      
    case SwitchProto(RefRepPTValue):
      return RefRepSize(toRefRep(theObj)->HighBorder) >> 2;

    case SwitchProto(ComponentPTValue):
      return ComponentSize(ComponentItem(theObj)->Proto) >> 2;

    case SwitchProto(StackObjectPTValue):
      return StackObjectSize(toStackObject(theObj)->BodySize) >> 2;

    case SwitchProto(StructurePTValue):
      return StructureSize >> 2;

    case SwitchProto(DopartObjectPTValue):
      return DopartObjectSize((cast(DopartObject)(theObj))->Size) >> 2;
    default:
#ifdef RTDEBUG
      fprintf(stderr, 
	      "ObjectSize: Error: Unknown ProtoType %d for object 0x%08x\n",
	      (int)theProto, 
	      (int)theObj);
#endif
      return 0;
    }
  }else
    /* This is an item, so find the size in the protoType. */
    return theProto->Size;
}
