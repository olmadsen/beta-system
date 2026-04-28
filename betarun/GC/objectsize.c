/*
 * BETA RUNTIME SYSTEM, Copyright (C) Aarhus University
 * objectsize.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */
#include "beta.h"

#ifdef PERSIST
#include "objectTable.h"
#include "referenceTable.h"
#endif /* PERSIST */

/* ObjectSize returns the size of an object in number of LONGS. */
long ObjectSize(Object * theObj)
{ 
   ProtoType * theProto = GETPROTO(theObj);
    
   if (isNotSpecialProtoType(theProto)) {
      /* This is an item, so find the size in the protoType. */
      return theProto->Size;
   } else {
      switch(SwitchProto(theProto)){
        case SwitchProto(ShortRepPTValue):
           return ShortRepSize(((ValRep*)theObj)->HighBorder) >> 2;
        case SwitchProto(ByteRepPTValue):
           return ByteRepSize(((ValRep*)theObj)->HighBorder) >> 2;
        case SwitchProto(DoubleRepPTValue):
           return DoubleRepSize(((ValRep*)theObj)->HighBorder) >> 2;
        case SwitchProto(LongRepPTValue):
           return LongRepSize(((ValRep*)theObj)->HighBorder) >> 2;
        case SwitchProto(DynItemRepPTValue):
        case SwitchProto(DynCompRepPTValue):
           return DynObjectRepSize(((ObjectRep *)theObj)->HighBorder) >> 2;
        case SwitchProto(RefRepPTValue):
           return RefRepSize(((RefRep*)theObj)->HighBorder) >> 2;
        case SwitchProto(ComponentPTValue):
           return ComponentSize(GETPROTO(ComponentItem(theObj))) >> 2;
        case SwitchProto(StackObjectPTValue):
           return StackObjectSize(((StackObject*)theObj)->BodySize) >> 2;
        case SwitchProto(StructurePTValue):
           return StructureSize >> 2;
        case SwitchProto(DopartObjectPTValue):
           return DopartObjectSize(((DopartObject *)(theObj))->Size) >> 2;
#ifdef PERSIST
        case SwitchProto(ObjInfoPTValue):
           return sizeof(struct _ObjInfo) >> 2;
        case SwitchProto(RefInfoPTValue):
           return sizeof(struct _RefInfo) >> 2;
#endif /* PERSIST */
        default:
           DEBUG_CODE(
              fprintf(stderr, 
                      "ObjectSize: Error: Unknown ProtoType %d for object 0x%08x\n",
                      (int)theProto, 
                      (int)theObj);
              );
      }
   }
   return 0;
}
