/* constants */

#define BETARUN_ID "5.0" /* Must match debugger/processCommCodes.bet */

/* Prototype constants */

#define ComponentPTValue       ((ProtoType *) -1)
#define StackObjectPTValue     ((ProtoType *) -2)
#define StructurePTValue       ((ProtoType *) -3)
#define RefRepPTValue          ((ProtoType *) -4)
#define LongRepPTValue          ((ProtoType *) -5)
#define ByteRepPTValue         ((ProtoType *) -6)
#define ShortRepPTValue         ((ProtoType *) -7)
#define DoubleRepPTValue       ((ProtoType *) -8)
#define DopartObjectPTValue    ((ProtoType *) -9)
#define DynItemRepPTValue      ((ProtoType *) -10)
#define DynCompRepPTValue      ((ProtoType *) -11)

#define MaxPTValue             ((ProtoType *) -1)
#define MinPTValue             ((ProtoType *) -11)

#ifdef UseRefStack
/* Used to mark external activation part on reference stack */
#define ExternalMarker	       -10
#endif

#define IOAMinAge            0
#define IOAMaxAge            128
#ifdef PERSIST               
#define IOAPersist           IOAMaxAge + 1
#endif /* PERSIST */
#define IOAMAXSIZE           (IOASize/8)
#define MMAPPageSize         65536
#define MMAPMaxSize          (1024*1024*1024)
#define AOAMaxSize           (768*1024*1024)
#define MAXCTEXTPOOL	     1000

#if defined (UseRefStack) || defined(NEWRUN) || (defined(RTVALHALLA) && (defined(intel) || defined(sparc)))
#define REFSTACKSIZE         1000
#endif

#define LARGE_REP_SIZE	     256

#ifndef MAXINT
#define MAXINT (signed long)0x7fffffff
#endif
#ifndef MININT
#define MININT (signed long)0x80000000
#endif

#ifdef NEWRUN
/* Special "dyn" mark used after callback */
#define CALLBACKMARK ((Object *)4)
/* Special "dyn" mark used after Gparts */
#define GENMARK      ((Object *)8)

/* Offset for dyn and PC on stack frame */
#ifdef sgi
#define DYN_OFF 2 /* FIXME: should be -2 and ADDED when used!!! */
#define PC_OFF -1
#endif
#ifdef macppc
#define DYN_OFF 1 /* FIXME: should be -1 and ADDED when used!!! */
#define PC_OFF 2
#endif

#endif /* NEWRUN */

/* Offset to TopMpart field in prototypes */
#define DISP_OFF (sizeof(ProtoType)-4)
