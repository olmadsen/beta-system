/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * define.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

#ifdef MT
# define _REEENTRANT 1
# define MT_CODE(code) code
# define IOATopInTSD 1 /* Should match define i BetaRun.bet! */
# define OURSEMAIMPL 1
#else
# define MT_CODE(code)
#endif

/* COM prototypes */
/* #define COM 1 */ /* RUN: must match define in Declaration.run */
#undef COM

#ifdef RTDEBUG
/* Trigger unconditional GC at every allocation.
 * MT: Should match define i BetaRun.bet!
 * RUN: Should match define in Declaration.run
 */
#define do_unconditional_gc 0 /*1*/ 
#else
#define do_unconditional_gc 0
#endif

#define RTINFO  /* Include support for runtime info */
#define RTLAZY  /* Include support for lazy fetch */
#ifdef RTDEBUG
#if (!defined(MAC) && !defined(hppa))
#define RTVALHALLA
#endif
#endif

/* No need for interpretItem - only used for Jawahar's interpreter */
#undef INTERPRETER

/******* Define specific machine types *********/
#ifdef sun
#  ifdef sparc
#    ifdef __svr4__
#      define sun4s
#    endif
#  endif
#endif

#ifdef hpux
#ifdef hppa
#define hpux9pa
#endif
#endif

/************* Macintosh defines ***************
 *  macppc is for PowerPC macintosh platforms (native)
 *  MAC    is for all macintosh platforms. Defined by -D MAC for C compiler
 */
 
#ifdef MAC
#ifdef __powerc

#define macppc
#define ppcmac /* alias */
#ifdef RTVALHALLA
#undef RTVALHALLA
#endif
#endif /* __powerc */
#endif /* MAC */

/********** Machine specific definitions **********/
#ifdef linux
#define intel 1
#define UNIX 1
#endif

#ifdef sgi
#define UNIX 1
#define RISC 1
#endif

#ifdef hppa
#define UNIX 1
#define RISC 1
#define UseRefStack 1
#endif

#ifdef sparc
#define UNIX 1
#define RISC 1
#endif

#ifdef nti 
#define intel 1
#endif

/********* Definition of RUN, CRUN, NEWRUN *********/

#ifdef intel
#define RUN 1
#endif

#if defined(sparc) || defined(hppa)
#define CRUN 1
#endif

#if defined(sgi) || defined(macppc)
#undef RUN
#define NEWRUN 1
#endif

/******** Misc. *******/
#define FALSE	0
#define TRUE	1

#ifdef __GNUC__
#define INLINE static __inline__ 
#else 
#define INLINE 
#endif

/******* Machinedep shorthands ********/
#ifdef MAC
#define MAC_CODE(code) code;
#else
#define MAC_CODE(code)
#endif
#ifdef ppcmac
#define PPCMAC_CODE(code) code;
#else
#define PPCMAC_CODE(code)
#endif
#ifdef sun4s
#define SUN4S_CODE(code) code;
#else
#define SUN4S_CODE(code)
#endif
#ifdef sparc
#define SPARC_CODE(code) code;
#else
#define SPARC_CODE(code)
#endif
#ifdef intel
#define INTEL_CODE(code) code;
#else
#define INTEL_CODE(code)
#endif
#ifdef hppa
#define HPPA_CODE(code) code;
#else
#define HPPA_CODE(code)
#endif
#ifdef linux
#define LINUX_CODE(code) code;
#else
#define LINUX_CODE(code)
#endif
#ifdef nti
#define NTI_CODE(code) code;
#else
#define NTI_CODE(code)
#endif


/* headsize *only* works on heap objects. They should
 * all include a Body element
 */  

#define headsize(x) (sizeof(x) - sizeof(long))

#undef RTSTAT /* only set when measuring! */
#ifdef RTSTAT
#  define STAT_AOA(code)  if (StatAOA ) { code; }
#else
#  define STAT_AOA(code)
#endif

/********* Debug macros *******/
#ifdef RTDEBUG
#ifdef MT
#  define DEBUG_MT(code)  if( DebugMT )  { code; }
#else
#  define DEBUG_MT(code)
#endif
#  define DEBUG_IOA(code)  if( DebugIOA )  { code; }
#  define CHECK_HEAP(code)  if( CheckHeap )  { code; }
#  define DEBUG_ALLOI(code)  if( DebugAlloI )  { code; }
#  define DEBUG_CBFA(code) if( DebugCBFA )  { code; }
#  define DEBUG_AOA(code)  if( DebugAOA )  { code; }
#  define DEBUG_AOAtoIOA(code)  if( DebugAOAtoIOA )  { code; }
#  define DEBUG_LIN(code) if( DebugLIN ) { code; }
#  define DEBUG_CODE(code)  code;
#  define DEBUG_STACK(code) if( DebugStack ) { code; }
#  define DEBUG_STACKOBJ(code) if( DebugStackObj ) { code; }
#  define DEBUG_VALHALLA(code) if( DebugValhalla ) { code; }
#  define DEBUG_SOCKETS(code) if( DebugSockets ) { code; }
#  define DEBUG_LAZY(code) if( DebugLazy ) { code; }
#  define DEBUG_LABELS(code) if( DebugLabels ) { code; }
#  define TRACE_GROUP(code) \
     if (TraceGroup) { code; fflush(output); } 
#  define TRACE_DUMP(code) \
     if (TraceDump) { code; fflush(output); }
#  define TRACE_CODEENTRY(code) \
     if (TraceCodeentry){ code; fflush(output); }
#else
#  define DEBUG_IOA(code)
#  define DEBUG_MT(code)
#  define CHECK_HEAP(code)
#  define DEBUG_ALLOI(code)
#  define DEBUG_CBFA(code)
#  define DEBUG_AOA(code)
#  define DEBUG_AOAtoIOA(code)
#  define DEBUG_LIN(code)
#  define DEBUG_CODE(code)
#  define DEBUG_STACK(code)
#  define DEBUG_STACKOBJ(code)
#  define DEBUG_VALHALLA(code)
#  define DEBUG_SOCKETS(code)
#  define DEBUG_LAZY(code)
#  define DEBUG_LABELS(code)
#  define TRACE_GROUP(code)
#  define TRACE_DUMP(code)
#  define TRACE_CODEENTRY(code)
#endif

#ifdef RTINFO
#  define INFO(code)      if (Info0   ) { code; }
#  define INFO_IOA(code)  if (InfoIOA ) { code; }
#  define INFO_AOA(code)  if (InfoAOA ) { code; }
#  define INFO_CBFA(code) if (InfoCBFA) { code; }
#  define INFO_DOT(code)  if (InfoDOT ) { code; }
#  define INFO_LABELS(code) if(InfoLabels) { code; }
#  define INFO_CODE(code) code;
#  define INFO_HEAP_USAGE(code) if (InfoHeapUsage) { code; }
#else
#  define INFO(code)
#  define INFO_IOA(code)
#  define INFO_AOA(code)
#  define INFO_LABELS(code)
#  define INFO_CODE(code)
#  define INFO_HEAP_USAGE(code) 
#endif


#ifdef STATISTICS
#  define InfoS_Start() if( isStatRecordOn ) StatRecordStart()
#  define InfoS_LabA()  if( isStatRecordOn ) StatRecordLabA()
#  define InfoS_LabB()  if( isStatRecordOn ) StatRecordLabB()
#  define InfoS_End()   if( isStatRecordOn ) StatRecordEnd()
#else
#  define InfoS_Start()
#  define InfoS_LabA() 
#  define InfoS_LabB() 
#  define InfoS_End()
#endif


#define DEADOBJECT 1
#define FREECHUNK 2
#define LISTEND 3

#define REFERENCEACTIONARGSTYPE Object **theCell
#define REFERENCEACTIONARGS theCell

#define UNKNOWNSTORE "AOA"
#define UNKNOWNID 0
