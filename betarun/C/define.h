/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * define.h
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

#define RTINFO  /* Include support for runtime info */
#define RTLAZY  /* Include support for lazy fetch */
#ifdef RTDEBUG
#if (!defined(nti) && !defined(MAC))
#define RTVALHALLA
#endif
#endif

#ifdef MT
#define _REEENTRANT 1
#endif

#define BETARUN_ID "3.0"

/******* Define specific machine types *********/
#ifdef sun
#  ifdef sparc
#    ifdef __svr4__
#      define sun4s
#    else
#      define sun4
#    endif
#  endif
#endif

#ifdef hpux
#if defined(hppa)
#define hpux9pa
#else
#define hpux9mc
#endif
#endif

/************* Macintosh defines ***************
 *  mac68k is for Motorola 680x0 macintosh platforms (used to be "macintosh")
 *  macppc is for PowerPC macintosh platforms (native and crts)
 *  MAC    is for all macintosh platforms. Defined by -D MAC for C compiler
 */
 
#ifdef MAC
#ifdef __powerc

#define macppc
#define ppcmac /* alias */
#ifdef RTVALHALLA
#undef RTVALHALLA
#endif

#else

#define mac68k

#endif /* __powerc */
#endif /* MAC */

/********* Definition of RUN, CRUN, NEWRUN *********/

#if defined(linux) || defined(nti) || defined(macintosh) || defined(hpux9mc)
#define RUN 1
#endif

#if defined(sparc) || defined(hppa)
#define CRUN 1
#endif

#if defined(sgi) || defined(macppc)
#undef RUN
#define NEWRUN 1
#endif

/********** Machine specific definitions **********/
#ifdef linux
#define intel
#define UNIX 1
#endif

#ifdef sgi
#define UNIX 1
#endif

#ifdef hpux9mc
#define UNIX 1
#endif

#ifdef hpux
#define UNIX 1
#ifdef hppa
#define UseRefStack 1
#endif
#endif

#ifdef sparc
#define UNIX 1
#endif

#ifdef nti 
#define intel 1
#endif

#ifdef crts
#undef sparc
#undef hppa
#undef NEWRUN
#undef CRUN
#undef RUN
#define UseRefStack
#endif

/******** Misc. *******/
#define FALSE	0
#define TRUE	1

#ifdef __GNUC__
#define INLINE static __inline__ 
#else 
#define INLINE 
#endif

#ifdef NEWRUN
/* Only CopyCT may cause large repetitions in IOA: ignored */
#undef CHECK_LVRA_IN_IOA
#else
#define CHECK_LVRA_IN_IOA
#endif

#if (defined(crts) || defined(NEWRUN))
#undef KEEP_STACKOBJ_IN_IOA
#else
#define KEEP_STACKOBJ_IN_IOA
#endif

#define ptr(x)    x *
#define ref(x)    struct x *
#define handle(x) struct x **
#define cast(x) (struct x *)
#define casthandle(x) (struct x **)

/* headsize *only* works on heap objects. They should
 * all include a Body element
 */  

#define headsize(x) (sizeof(struct x) - sizeof(long))

/********* Debug macros *******/
#ifdef RTDEBUG
#  define DEBUG_MT(code)  if( DebugMT )  { code; }
#  define DEBUG_IOA(code)  if( DebugIOA )  { code; }
#  define CHECK_HEAP(code)  if( CheckHeap )  { code; }
#  define DEBUG_ALLOI(code)  if( DebugAlloI )  { code; }
#  define DEBUG_CBFA(code) if( DebugCBFA )  { code; }
#  define DEBUG_AOA(code)  if( DebugAOA )  { code; }
#  define DEBUG_LVRA(code) if( DebugLVRA ) { code; }
#  define DEBUG_CODE(code)  code;
#  define DEBUG_STACK(code) if( DebugStack ) { code; }
#  define DEBUG_VALHALLA(code) if( DebugValhalla ) { code; }
#else
#  define DEBUG_IOA(code)
#  define DEBUG_MT(code)
#  define CHECK_HEAP(code)
#  define DEBUG_ALLOI(code)
#  define DEBUG_CBFA(code)
#  define DEBUG_AOA(code)
#  define DEBUG_LVRA(code)
#  define DEBUG_CODE(code)
#  define DEBUG_STACK(code)
#  define DEBUG_VALHALLA(code)
#endif

#ifdef RTINFO
#  define INFO( code)      if( Info0    ){ code; }
#  define INFO_IOA( code)  if( InfoIOA  ){ code; }
#  define INFO_AOA( code)  if( InfoAOA  ){ code; }
#  define INFO_LVRA( code) if( InfoLVRA ){ code; }
#  define INFO_CBFA( code) if( InfoCBFA ){ code; }
#  define INFO_DOT( code)  if( InfoDOT  ){ code; }
#  define INFO_LVRA_ALLOC( code) if( InfoLVRAAlloc ){ code; }
#  define INFO_CODE( code) code;
#else
#  define INFO( code)
#  define INFO_IOA( code)
#  define INFO_AOA( code)
#  define INFO_LVRA( code)
#  define INFO_LVRA_ALLOC( code)
#  define INFO_CODE( code)
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
