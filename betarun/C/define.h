/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * define.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

#ifndef BETA_DEFINE_H
#define BETA_DEFINE_H

#ifdef MT
# define _REEENTRANT 1
# define MT_CODE(code) code
# define IOATopInTSD 1 /* Should match define i BetaRun.bet! */
# define OURSEMAIMPL 1
#else
# define MT_CODE(code)
#endif

/* Make allocation routines collect statistics about prototypes of 
   allocated objects */
/*#define PROTO_STATISTICS 1*/

/* COM prototypes */
#define COM 1 /* RUN: must match define in Declaration.run */
/*#undef COM*/

#ifndef do_unconditional_gc
# ifdef RTDEBUG
/* Trigger unconditional GC at every allocation.
 * MT: Should match define i BetaRun.bet!
 * RUN: Should match define in Declaration.run
 */
#   define do_unconditional_gc 0 /*1*/ 
# else /* RTDEBUG */
#   define do_unconditional_gc 0
# endif /* RTDEBUG */
#endif /* do_unconditional_gc */

#define RTINFO  /* Include support for runtime info */
# ifdef RTDEBUG
# ifndef RTVALHALLA
#   define RTVALHALLA
# endif
#endif

/******* Define specific machine types *********/
#ifdef sun
#  ifdef sparc
#    ifdef __svr4__
#      define sun4s
#    endif
#  endif
#endif

#ifdef i386
#  ifdef __svr4__
#    define x86sol
#  endif
#endif

#ifdef hpux
# ifdef hppa
#   define hpux9pa
# endif
#endif

/************* Macintosh defines ***************
 *  ppcmac is for PowerPC macintosh platforms (native)
 *  MAC    is for all macintosh platforms. Defined by -D MAC for C compiler
 */
 
#ifdef MAC
#ifdef powerc
#define OLDROUTINENAMES 1
#define ppcmac
typedef unsigned long u_long;
typedef unsigned short u_short;
#define ppcmac /* alias */
#endif /* powerc */
#endif /* MAC */

/********** Machine specific definitions **********/
#ifdef linux
#define intel 1
#define UNIX 1
#endif

#ifdef x86sol
#define intel 1
#define UNIX 1
#endif

#ifdef sgi
#define UNIX 1
#define RISC 1
#endif

#ifdef macosx
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

#ifdef MAC
#define PERSIST
#endif

#ifdef intel
#define RUN 1
#endif

#if defined(sparc) || defined(hppa)
#define CRUN 1
#endif

#if defined(sgi) || defined(ppcmac) || defined(macosx)
#undef RUN
#define NEWRUN 1
#endif

/* New persistence */
#if defined(sparc) || defined(intel) || defined(sgi) || defined(macosx)
#define PERSIST
/* #define DEBUGPERSISTENCE */
/* #define USEMMAP  uses to mych RAM */
#endif /* sparc || intel || defined(sgi) */

/* Endianess */
#ifdef intel
#define PSENDIAN
#endif

/* #define RTLAZY    Include support for lazy fetch */

/* #ifndef RTLAZY */
#define MMAPANYADDR 1 /* If set to 1, allow mmap at any address. Otherwise,
		       * mmap is only allowed to return in the positive
		       * region of the address space.
		       */

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
#define NON_LINUX_CODE(code)
#else
#define LINUX_CODE(code)
#define NON_LINUX_CODE(code) code;
#endif
#ifdef nti
#define NTI_CODE(code) code;
#else
#define NTI_CODE(code)
#endif
#ifdef NEWRUN
#define NEWRUN_CODE(code) code;
#define NOTNEWRUN_CODE(code)
#else
#define NEWRUN_CODE(code)
#define NOTNEWRUN_CODE(code) code;
#endif

/* headsize *only* works on heap objects. They should
 * all include a Body element
 */  

#define headsize(x) (sizeof(x) - sizeof(long))

#define DETAILEDSTAT /* only define when not measuring time! */
#ifdef DETAILEDSTAT
#  define DETAILEDSTAT_AOA(code)  if (StatAOA) { code; }
#else
#  define DETAILEDSTAT_AOA(code)
#endif

/********* Debug macros *******/
#ifdef RTDEBUG
#ifdef MT
#  define DEBUG_MT(code)  \
     if( DebugMT )  { code; /* fflush(output); */ }
#else
#  define DEBUG_MT(code)
#endif
#  define DEBUG_IOA(code)  \
     if( DebugIOA )  { code; /* fflush(output); */ }
#  define CHECK_HEAP(code)  \
     if( CheckHeap )  { code; /* fflush(output); */ }
#  define DEBUG_ALLOI(code)  \
     if( DebugAlloI )  { code; /* fflush(output); */ }
#  define DEBUG_CBFA(code) \
     if( DebugCBFA )  { code; /* fflush(output); */ }
#  define DEBUG_AOA(code)  \
     if( DebugAOA )  { code; /* fflush(output); */ }
#  define DEBUG_AOAtoIOA(code)  \
     if( DebugAOAtoIOA )  { code; /* fflush(output); */ }
#  define DEBUG_CODE(code)  code;
#  define DEBUG_STACK(code) \
     if( DebugStack ) { code; /* fflush(output); */ }
#  define DEBUG_STACKOBJ(code) \
     if( DebugStackObj ) { code; /* fflush(output); */ }
#  define DEBUG_VALHALLA(code) \
     if( DebugValhalla ) { code; /* fflush(output); */ }
#  define DEBUG_STRONGISOBJECT(code)  \
     if( DebugStrongIsObject )  { code; fflush(output); }
#  define TRACE_VALHALLACOMM(code) \
     if( TraceValhallaComm ) { code; }
#  define DEBUG_SOCKETS(code) \
     if( DebugSockets ) { code; /* fflush(output); */ }
#  define DEBUG_LABELS(code) \
     if( DebugLabels ) { code; /* fflush(output); */ }
#  define TRACE_GROUP(code) \
     if (TraceGroup) { code; fflush(output); } 
#  define TRACE_DUMP(code) \
     if (TraceDump) { code; fflush(output); }
#  define TRACE_CODEENTRY(code) \
     if (TraceCodeentry){ code; fflush(output); }
#  define TRACE_NUMVARS() \
     if (TraceNumVars){ PrintNumVars(); fflush(output); }
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
#  define TRACE_VALHALLACOMM(code)
#  define DEBUG_STRONGISOBJECT(code)
#  define DEBUG_SOCKETS(code)
#  define DEBUG_LABELS(code)
#  define TRACE_GROUP(code)
#  define TRACE_DUMP(code)
#  define TRACE_CODEENTRY(code)
#  define TRACE_NUMVARS()
#endif

#ifdef ALLOC_TRACE
#  define ALLOC_TRACE_CODE(code) code
#else
#  define ALLOC_TRACE_CODE(code)
#endif

#ifdef RTINFO
#  define TIME_IOA(code)  if (timeIOA ) { code; }
#  define TIME_AOA(code)  if (timeAOA ) { code; }
#  define INFO(code)      if (Info0   ) { code; }
#  define INFO_IOA(code)  if (InfoIOA ) { code; }
#  define INFO_AOA(code)  if (InfoAOA ) { code; }
#  define INFO_AOAUSE(code)  if (InfoAOAUse ) { code; }
#  define INFO_PERSISTENCE(code) if (InfoPersistence ) { code; }
#  define INFO_VARS(code) if (InfoVars ) { code; }
#  define STAT_AOA(code)  if (StatAOA ) { code; }
#  define INFO_CBFA(code) if (InfoCBFA) { code; }
#  define INFO_DOT(code)  if (InfoDOT ) { code; }
#  define INFO_LABELS(code) if(InfoLabels) { code; }
#  define INFO_CODE(code) code;
#  define INFO_HEAP_USAGE(code) if (InfoHeapUsage) { code; }
#else
#  define TIME_IOA(code)
#  define TIME_AOA(code)
#  define INFO(code)
#  define INFO_IOA(code)
#  define INFO_AOA(code)
#  define INFO_PROXY(code)
#  define INFO_PERSISTENCE(code)
#  define INFO_VARS(code)
#  define STAT_AOA(code)
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

/* Unconditional property stuff */
#  define TRACE_FINDACTIVATION(code) \
     if (TraceFindActivation) { code; fflush(output); }

#ifdef PROTO_STATISTICS
#  define TRACE_PROTOSTATISTICS(code) \
     if (ProtoStatistics) { code; fflush(output); }
#else
#  define TRACE_PROTOSTATISTICS(code) 
#endif /* PROTO_STATISTICS */

#define REFERENCEACTIONARGSTYPE Object **theCell, long refType
#define REFERENCEACTIONARGS theCell

#endif /* BETA_DEFINE_H */

