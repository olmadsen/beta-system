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
#define DynItemRepPTValue      ((struct ProtoType *) -10)
#define DynCompRepPTValue      ((struct ProtoType *) -11)
#ifdef STATIC_OBJECT_REPETITIONS
#define StatItemRepPTValue     ((struct ProtoType *) -12)
#define StatCompRepPTValue     ((struct ProtoType *) -13)
#endif /* STATIC_OBJECT_REPETITIONS */

#ifdef STATIC_OBJECT_REPETITIONS
#define MaxPTValue             -1
#define MinPTValue             -13
#else /* STATIC_OBJECT_REPETITIONS */
#define MaxPTValue             -1
#define MinPTValue             -11
#endif /* STATIC_OBJECT_REPETITIONS */

#ifdef UseRefStack
/* Used to mark external activation part on reference stack */
#define ExternalMarker	       -10
#endif

#define IOAMaxAge             128

#define MAXCTEXTPOOL	     1000

#if defined (UseRefStack) || defined(NEWRUN)
#define REFSTACKSIZE         1000
#endif

#define LARGE_REP_SIZE	     256

#define MAXINT (signed long)0x7fffffff
#define MININT (signed long)0x80000000

#ifdef NEWRUN
#define CALLBACKMARK 4
#define IOAMAXSIZE           (IOASize/8)
#endif
