/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-93 Mjolner Informatics Aps.
 * define.h
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn
 */

#define FALSE	0
#define TRUE	1

/* Machines supported 
 * sun3       'sun3'        is defined.
 * sun4       'sparc'       is defined.
 * hp         'hpux'        is defined.
 * dx200      'DX200'       is defined.
 * macintosh  'macintosh'   is defined.
 * apollo     'apollo'      is defined.
 */

#define ptr(x)    x *
#define ref(x)    struct x *
#define handle(x) struct x **
#define cast(x) (struct x *)
#define casthandle(x) (struct x **)

#ifdef RTLAZY
#define isLazyRef(ref) ((lastDangler <= ((int) ref)) && (((int) ref) < -20))
#else
#define isLazyRef(ref) 0
#endif

/* headsize *only* works on heap objects. They should
 * all include a Body element
 */  

#define headsize(x) (sizeof(struct x) - sizeof(long))

#ifdef linux
#  define UNIX
#endif

#ifdef hpux
#  define UNIX
#endif

#ifdef apollo
#  define UNIX
#endif

#ifdef sun
#  define UNIX
#  ifndef sparc
#    define sun3
#  endif
#endif

#ifdef RTDEBUG
#  define DEBUG_IOA( code)  if( DebugIOA )  { code; }
#  define DEBUG_CBFA( code) if( DebugCBFA )  { code; }
#  define DEBUG_AOA( code)  if( DebugAOA )  { code; }
#  define DEBUG_LVRA( code) if( DebugLVRA ) { code; }
#  define DEBUG_CODE( code)  code;
#  define DEBUG_STACK( code) if( DebugStack ) { code; }
#else
#  define DEBUG_IOA( code)
#  define DEBUG_CBFA( code)
#  define DEBUG_AOA( code)
#  define DEBUG_LVRA( code)
#  define DEBUG_CODE( code)
#  define DEBUG_STACK( code)
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
