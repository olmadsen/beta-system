/* constants */

/* -- Prototype constants */
#define ComponentPTValue       ((struct ProtoType *) -1)
#define StackObjectPTValue     ((struct ProtoType *) -2)
#define StructurePTValue       ((struct ProtoType *) -3)
#define RefRepPTValue          ((struct ProtoType *) -4)
#define ValRepPTValue          ((struct ProtoType *) -5)
#define ByteRepPTValue         ((struct ProtoType *) -6)
#define WordRepPTValue         ((struct ProtoType *) -7)
#define DoubleRepPTValue       ((struct ProtoType *) -8)
#define DopartObjectPTValue    ((struct ProtoType *) -9)
#define StatItemRepPTValue     ((struct ProtoType *) -10)
#define StatCompRepPTValue     ((struct ProtoType *) -11)
#define DynItemRepPTValue      ((struct ProtoType *) -12)
#define DynCompRepPTValue      ((struct ProtoType *) -13)

#define MaxPTValue             -1
#define MinPTValue             -13

#ifdef UseRefStack
/* Used to mark external activation part on reference stack */
#define ExternalMarker	       -10
#endif

#define IOAMaxAge             128

#define MAXCTEXTPOOL	     1000

#define LARGE_REP_SIZE	     256
