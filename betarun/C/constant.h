/* constants */

#define BETARUN_ID "5.4" /* Must match debugger/processCommCodes.bet */

/* Prototype constants */

#define ComponentPTValue       ((ProtoType *) -1)
#define StackObjectPTValue     ((ProtoType *) -2)
#define StructurePTValue       ((ProtoType *) -3)
#define RefRepPTValue          ((ProtoType *) -4)
#define LongRepPTValue         ((ProtoType *) -5)
#define ByteRepPTValue         ((ProtoType *) -6)
#define ShortRepPTValue        ((ProtoType *) -7)
#define DoubleRepPTValue       ((ProtoType *) -8)
#define DopartObjectPTValue    ((ProtoType *) -9)
#define DynItemRepPTValue      ((ProtoType *) -10)
#define DynCompRepPTValue      ((ProtoType *) -11)
#ifdef PERSIST
#define ObjInfoPTValue         ((ProtoType *) -12)
#define RefInfoPTValue         ((ProtoType *) -13)
#endif /* PERSIST */

#define MaxPTValue             ((ProtoType *) -1)
#ifdef PERSIST
#define MinPTValue             ((ProtoType *) -13)
#else
#define MinPTValue             ((ProtoType *) -11)
#endif /* PERSIST */

#ifdef UseRefStack
/* Used to mark external activation part on reference stack */
#define ExternalMarker	       -10
#endif

/* GCAttribute values in AOA */
#define DEADOBJECT           0
#define FREECHUNK            1
#define AOASPECIAL           2
#define LISTEND              3       
#define AOAMAXGCTAG          LISTEND

/* GCAttribute values in IOA */
#define IOAMinAge            0
#define IOAMaxAge            128
#ifdef PERSIST               
#define IOASpecial           IOAMaxAge + 1
#define IOAPersist           IOAMaxAge + 2
#endif /* PERSIST */
#define IOAMAXSIZE           (IOASize/8)
#define MMAPPageSize         65536
#define MMAPMaxSize          (1024*1024*1024)
#define AOAMAXSIZE           MMAPMaxSize
#define MAXCTEXTPOOL	     1000
#ifdef PERSIST
#define PERSIST_MAXENTRIES   0x160000
#else
#define PERSIST_MAXENTRIES   0
#endif

#if defined (UseRefStack) || defined(NEWRUN) || ((defined(PERSIST) || defined(RTVALHALLA)) && (defined(intel) || defined(sparc)))
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
#ifdef ppcmac
#define DYN_OFF 1 /* FIXME: should be -1 and ADDED when used!!! */
#define PC_OFF 2
#endif

#ifdef macosx
#define DYN_OFF 1 /* FIXME: (Copied from macoppc) should be -1 and ADDED when used!!! */
#define PC_OFF 2
#endif

#endif /* NEWRUN */

/* Offset to TopMpart field in prototypes */
#define DISP_OFF ((long)(sizeof(struct _ProtoType)-4))

/* Reference types */
#define REFTYPE_DYNAMIC  0
#define REFTYPE_OFFLINE  1
#define REFTYPE_ORIGIN   2

/* Possible values of the stacktype:
 *
 * These constants are replicated in ~debugger/processCommCodes.bet. 
*/
#define CS_PROCESSORSTACK  1  /* component stack on processor stack. */
#define CS_ACTIVECOMPONENT 2  /* component is the currently active.  */
#define CS_STACKOBJ        3  /* component stack in stack object.    */
#define CS_NOSTACK         4  /* component has no stack.             */
