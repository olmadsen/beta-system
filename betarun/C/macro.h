#ifndef BETARUN_C_MACRO_H
#define BETARUN_C_MACRO_H 1

#include "define.h"

/* macros */

/* define DMALLOC to 1 to use dmalloc library - requires manual link
 * with /users/beta/GNU/dmalloc-3.2.1/libdmalloc.a before -lc
 */
#undef DMALLOC


#define FREE(ptr) free(ptr)
#define REALLOC(src,size) realloc(src,size)
#ifdef RTDEBUG
#  if defined(sparc) || defined(sgi) || defined(hppa)
     /* debug: 64 bit alignment because of the reals */
#    ifdef MT
#      define MALLOC(size) MT_malloc(size)
#    else
#      define MALLOC(size) memset((void *)memalign(8, (size)), 0, (size))
#    endif
#  else
     /* debug: No alignment required */
#    if defined(nti) || defined(macosx)
#      define MALLOC(size) calloc(size, 1)
#    else
#      define MALLOC(size) memset((void *)memalign(8, (size)), 0, (size))
#    endif
#  endif
#else
#  if defined(sparc) || defined(sgi) || defined(hppa)
     /* non-debug: 64 bit alignment because of the reals */
#    define MALLOC(size) memalign(8, (size))
#  else
     /* non-debug: No alignment required */
#    if defined(nti) || defined(macosx)
#      define MALLOC(size) malloc(size)
#    else
#      define MALLOC(size) memalign(8, (size))
#    endif
#  endif
#endif

#ifndef bMAX
# define bMAX(a, b) ((a) < (b) ? (b) : (a))
# define bMIN(a, b) ((a) > (b) ? (b) : (a))
#endif

/* Split memory up into sectors of a rather large size.  Some
 * OSs (Linux, probably SGI) have some administrative overhead (0.1% for
 * Linux) of RAM needed to manage a large mmapping, so shouldn't be too
 * big.
 *
 * For each sector we keep track of the AOA blocks in that sector.
 * We must allocate at least 1 sector-size at a time to ensure
 * that we never have more than two blocks in a sector.
 */

/*
 * Sector  Table size Table-size (2 pointers per entry)
 * 16M     256                   2k
 * 8M      512                   4k
 * 4M      1024                  8k
 * 2M      2048                  16k
 */

#ifdef RTDEBUG_not_right_now_i_need_to_debug_the_normal_aoa
#define SECTOR_BITS (2+10) /* Force frequent AOAGc */
#else
#define SECTOR_BITS (2+10+10)  /* 4 Mbyte */
#endif

#define SECTOR_SIZE (1 << SECTOR_BITS)
#define SECTOR_MASK (SECTOR_SIZE-1)
#define SECTOR_ROUND_DOWN(a) (((unsigned long)(a)) & ~SECTOR_MASK)
#define SECTOR_ROUND_UP(a) (((unsigned long)((a) + SECTOR_SIZE)) & ~SECTOR_MASK)
#define SECTOR_INDEX(a) (((unsigned long)(a)) >> SECTOR_BITS)
#define SECTOR_COUNT (1 << (32 - SECTOR_BITS))

#define inBlock( theB, addr) (((BlockStart( theB)) <= (long *) addr) \
                            && ((long *) addr < theB->limit) ) 
#define inBlockUnused( theB, addr) ((theB->top <= (long *) addr) \
			    && ((long *) addr < theB->limit) )



#if 0
#define INFO_ALLOC(size) fprintf(output, "alloc: 0x%x at: %s: %d\n",size, __FILE__, __LINE__)
#else
#define INFO_ALLOC(size)
#endif

#ifdef DMALLOC
/* #include "/users/beta/GNU/dmalloc-3.2.1/include/dmalloc.h" */
extern long mcheck_line;
extern int dmalloc_verify(int);
#define MCHECK() mcheck_line=__LINE__; dmalloc_verify(0); mcheck_line=0
#else
#define MCHECK()
#endif

#ifdef intel_we_cant_use_this_code_before_we_can_patch_it_away_at_runtim
#define beta_prefetch(x)     asm ("prefetch 0(%0)" :: "r" (x))
#define beta_prefetch512(x)     asm ("prefetch 512(%0)" :: "r" (x))
#define beta_prefetchw512(x)     asm ("prefetch 512(%0)" :: "r" (x))
#else
#define beta_prefetch(x)
#define beta_prefetch512(x)
#define beta_prefetchw512(x)
#endif

/*
 * The type of the program counter
 */

#ifdef intel
  typedef unsigned char *pc_t;
#else
  typedef long *pc_t;
#endif

/* macro to be used to declare global variables (including static ones)
 * outside data.gen. 
 */
#define GLOBAL(var) var

/* Macros to access prototypes, that are displaced as COM objects.
 * DISP_OFF is defined in constant.h
 * COM is defined in define.h
 */
#ifdef COM

/* convert vtbl to prototype */
#define V2P(vtbl)                 ((ProtoType*)(((long)(vtbl))-DISP_OFF))
/* convert prototype to vtbl */
#define P2V(proto)                ((long*)(((long)(proto))+DISP_OFF))
/* Get real prototype from an object */
#define GETPROTO(obj)             V2P((obj)->vtbl)
/* Set vtbl in an object */
#define SETPROTO(obj, proto)      ((obj)->vtbl = P2V(proto))
/* Get a field from an unadjusted prototype pointer in an object */
#define OBJPROTOFIELD(obj,field)  (V2P((obj)->vtbl)->field)

#else /* !COM */

#define GETPROTO(obj)             ((obj)->Proto)
#define SETPROTO(obj, proto)      ((obj)->Proto = (proto))
#define OBJPROTOFIELD(obj,field)  ((obj)->Proto->field)

#endif /* COM */

#if defined (MAC)
#define Notify(s1)           CPrompt(s1, "","","")
#define Notify2(s1,s2)       CPrompt(s1, s2, "", "")
#define Notify3(s1,s2,s3)    CPrompt(s1, s2, s3, 0)
#define Notify4(s1,s2,s3,s4) CPrompt(s1, s2, s3, s4)

#define MakeMPWFile(path)          \
/* Set file type and creator to make xxx.dump an MPW file */ \
do {                               \
  FInfo fn;                        \
  OSErr err;                       \
  Str255 fname;                    \
  sprintf((char*)fname, "%c%s", strlen(path), path); \
  err = GetFInfo(fname, 0, &fn);   \
  if (err != noErr) break;         \
  fn.fdType = 'TEXT';              \
  fn.fdCreator = 'MPS ';           \
  err = SetFInfo(fname, 0, &fn);   \
  if (err != noErr) break;         \
} while (0)

#else /* not macintosh */
#ifdef nti
#define Notify(s1)           NotifyFunc(s1)
#define Notify2(s1,s2)       do { char x[1000]; sprintf(x, "%s\n%s", s1, s2); Notify(x); } while (0)
#else
#define Notify(s1)           fprintf(output, "%s\n", s1);
#define Notify2(s1,s2)       fprintf(output, "%s\n%s\n", s1, s2);
#define Notify3(s1,s2,s3)    fprintf(output, "%s\n%s\n%s\n", s1, s2, s3);
#define Notify4(s1,s2,s3,s4) fprintf(output, "%s\n%s\n%s\n%s\n", s1, s2, s3, s4);
#endif
#endif

/* Cast ProtoType to constant - advantage to use chars, since they
 * will fit in a gcc jump table.
 */
#define SwitchProto(proto)      ((signed char) ((int)(proto)))

#if defined(sparc) || defined(NEWRUN)
#ifdef MT
#define inIOA(x)     ((x) && ((unsigned long)(gIOA) <= (unsigned long)(x) && (unsigned long)(x)< (unsigned long)(gIOATop)))
#else
#define inIOA(x)     (((unsigned long)(x) - (unsigned long)(IOA)) < (unsigned long)(IOATopOff))
#endif /* MT */
#else
#define inIOA(x)     (((unsigned long)IOA <= (unsigned long)(x)) && ((unsigned long)(x) < (unsigned long)IOATop))
#endif /* sparc || newrun */
     
#define inToSpace(x) (((unsigned long)ToSpace <= (unsigned long)(x)) && ((unsigned long)(x) < (unsigned long)ToSpaceTop)) 
#define inToSpaceArea(x) (((unsigned long)ToSpace <= (unsigned long)(x)) && ((unsigned long)(x) < (unsigned long)ToSpaceLimit)) 
#ifdef USEMMAP
#define inAOA(x)     (((BlockStart(AOABaseBlock)) <= (long *)(x)) \
                              && ((long *)(x) < AOABaseBlock->top) )
#else
#define inAOA(x)     SectorBasedInAOA((Object *)(x))
#endif /* USEMMAP */
#define inAOAUnused(x) SectorBasedInAOAUnused((Object *)(x))
     
#if 0
    /* too slow */
#define isSpecialProtoType(x) (((long)(MinPTValue) <= (long)(x)) && \
                               ((long)(x) <= (long)(MaxPTValue)))
#endif

#define isSpecialProtoType(x)  \
    (((unsigned long)((long)(x) - (unsigned long)MinPTValue)) <= \
     ((unsigned long)((unsigned long)MaxPTValue - (unsigned long)MinPTValue)))

#if 0
    /* too slow */
#define isNotSpecialProtoType(x) (((long)(MinPTValue) > (long)(x)) || \
                                  ((long)(x) > (long)(MaxPTValue)))
#endif

#define isNotSpecialProtoType(x) (!isSpecialProtoType((x)))
	                        

#define isNegativeRef(x) ((long)(x) < 0)
#define isPositiveRef(x) ((long)(x) > 0)

/* AOAGC values for GCAttr.  Legal values are DEAD, FREE or link to
 * another object.  Also LINKEND is legal, and is alive.
 * Please note that GCAttr==0 is illegal as none of the above is zero...
 */
#define AOAISDEAD(obj)       ((obj)->GCAttr == DEADOBJECT)
#define AOAISFREE(obj)       ((obj)->GCAttr == FREECHUNK)
#define AOAISALIVE(obj)      ((unsigned long)((obj)->GCAttr) >=  LISTEND)

#ifdef PERSIST
#define PERSISTENTTAG        1
#define PUTOI(objInfo)       ((u_long)objInfo | PERSISTENTTAG)
#define GETOI(objInfo)       ((u_long)objInfo & ~PERSISTENTTAG)
#define inPIT(ip)            (((void *)(ip) < PITLimit) && ((void *)(ip) >= PIT))
#define AOAISPERSISTENT(obj) ((((obj)->GCAttr) > LISTEND) && (((obj)->GCAttr) & PERSISTENTTAG))
#define IOAISPERSISTENT(obj) (((obj)->GCAttr) == IOAPersist)
#endif /* PERSIST */
#define isLink(gcattr)       ((unsigned long)(gcattr) > LISTEND)
#define isEnd(gcattr)        ((gcattr) == LISTEND)

#ifdef PERSIST
#define isAutonomous(gc)   ((IOAMinAge <= (gc)) && ((gc) <= IOAPersist))
#define isForward(gc)      (!isStatic(gc) && (unsigned long)(gc) > IOAPersist)
#else 
#define isAutonomous(gc)   ((IOAMinAge <= (gc)) && ((gc) <= IOAMaxAge))
#define isForward(gc)      (!isStatic(gc) && (unsigned long)(gc) > IOAMaxAge)
#endif /* PERSIST */
#define isStatic(gc)       ((-0xFFFF <= (gc)) && ((gc) <= -1))

#define isValRep(x)      (((long)(DoubleRepPTValue) <= (long)(GETPROTO(x)))\
			  && ((long)(GETPROTO(x)) <= (long)(LongRepPTValue)))
#define isObjectRep(x)   (((long)(DynCompRepPTValue) <= (long)(GETPROTO(x)))\
			  && ((long)(GETPROTO(x)) <= (long)(DynItemRepPTValue)))

#define isStackObject(x) ((long)(GETPROTO(x)) == (long)(StackObjectPTValue))
#define isComponent(x)   ((long)(GETPROTO(x)) == (long)(ComponentPTValue))

#define ComponentItem(x) ((Item *) (((long)(x)) + headsize(Component)))

#define ItemSize(proto)          (4*((proto)->Size))
#define ComponentSize(proto)     (headsize(Component)+4*((proto)->Size))

/*** Object sizes in BYTES ****/

/* Objects must be multiples of 8 bytes because of reals */
#define ObjectAlign(numbytes)     ((unsigned long)(((unsigned)(numbytes)+7) & (unsigned)~7))
#define ObjectAlignDown(numbytes) ((unsigned long)(((unsigned)(numbytes))   & (unsigned)~7))
#define LongAlign(numbytes)       ((unsigned long)(((unsigned)(numbytes)+3) & (unsigned)~3))
#define LongAlignDown(numbytes)   ((unsigned long)(((unsigned)(numbytes))   & (unsigned)~3))

/* It is INTENTIONAL that we use of LongAlign instead of ObjectAlign below.
 * This meens that RepSize <> RepBodySize + HeadSize (the latter may be 4 less). 
 */
#define ByteRepBodySize(range)   LongAlign((range)+1) /* +1 for NULL termination */
#define ShortRepBodySize(range)  LongAlign(2*(range))
#define LongRepBodySize(range)   ((range)*4)
#define DoubleRepBodySize(range) ((range)*8)
#define RefRepBodySize(range)    ((range)*4)

#define StructureSize          ObjectAlign(headsize(Structure))
#define RefRepSize(range)      ObjectAlign((range)*4 + headsize(RefRep))
#define DynObjectRepSize(range)ObjectAlign((range)*4 + headsize(ObjectRep))
#define LongRepSize(range)     ObjectAlign(LongRepBodySize(range) + headsize(ValRep))
#define ByteRepSize(range)     ObjectAlign(ByteRepBodySize(range) + headsize(ValRep))
#define ShortRepSize(range)    ObjectAlign(ShortRepBodySize(range) + headsize(ValRep))
#define DoubleRepSize(range)   ObjectAlign(DoubleRepBodySize(range) + headsize(ValRep))
#define DopartObjectSize(size) ObjectAlign((size) + headsize(DopartObject))

#if defined(MT) || defined(NEWRUN)
/* size is number of BYTES */
#define StackObjectSize(size)  ObjectAlign((size) + headsize(StackObject))
#else
#define StackObjectSize(size)  ObjectAlign(4*(size) + headsize(StackObject))
#endif

/* Generic ValRepSize */

/* This is really just for value repetitions, but we are a little defensive,
 * so just in case, we default to the size of a pointer if we don't recognise
 * the prototype.
 */

/* DispatchRepSize works for both value repetitions and reference repetitions */
#define DispatchRepSize(proto, range)			                \
(((long)(proto) == (long)(ByteRepPTValue)) ? ByteRepSize(range) :		\
 (((long)(proto) == (long)(ShortRepPTValue))   ? ShortRepSize(range)  :		\
  (((long)(proto) == (long)(DoubleRepPTValue)) ? DoubleRepSize(range) :    	\
   LongRepSize(range))))

/* DispatchRepBodySize works for both value repetitions and reference repetitions
 * Notice that these values are only 4 aligned, NOT ObjectAlign'ed (8).
 */
#define DispatchRepBodySize(proto, range)			                \
(((long)(proto) == (long)(ByteRepPTValue)) ? ByteRepBodySize(range) :      	\
 (((long)(proto) == (long)(ShortRepPTValue))   ? ShortRepBodySize(range)  : 	\
  (((long)(proto) == (long)(DoubleRepPTValue)) ? DoubleRepBodySize(range) :	\
   LongRepBodySize(range))))

#define Offset(x,y) (((long) (x)) + ((long) (y)))
/* Example:
   Item *aItem

   theStaticObject = (Object *) Offset( aItem, 25);
*/

#define toKb(x) ( (long) (x)/1024)
#define areaSizeInKb( from, to) ( ( ( (long) to ) - ( (long) from) ) / 1024)
#define areaSize( from, to) ( ( ( (long) to ) - ( (long) from) ) )

#define BlockStart(theB) ((long *) Offset( theB, sizeof(Block)))
#define BlockNumBytes(theB) ((unsigned long)theB->limit - (unsigned long)BlockStart(theB))

/*
 * GetDistanceToEnclosingObject:
 *  Find the offset (negative) to the most inclosing object e.g.
 *  the offset to the autonomous object in which theObj reside. 
 */

#define GetDistanceToEnclosingObject(theObj, Distance)         \
{                                                              \
  long           _GCAttribute;                                 \
  Object *_theObj=theObj;                               \
  Distance = 0;                                                \
  _GCAttribute = _theObj->GCAttr;                            \
  while(isStatic(_GCAttribute)){                                   \
    Distance += _GCAttribute*4;                                  \
    _theObj = (Object *) Offset(_theObj, _GCAttribute*4); \
    _GCAttribute = _theObj->GCAttr;                          \
  }                                                            \
}
#ifdef PERSIST
#define GetDistanceToEnclosingStoreObject(theObj, Distance)         \
{                                                              \
  long           _GCAttribute;                                 \
  Object *_theObj=theObj;                               \
  Distance = 0;                                                \
  _GCAttribute = ntohl(_theObj->GCAttr);                            \
  while(isStatic(_GCAttribute)){                                   \
    Distance += _GCAttribute*4;                                  \
    _theObj = (Object *) Offset(_theObj, _GCAttribute*4); \
    _GCAttribute = _theObj->GCAttr;                          \
  }                                                            \
}
#endif /* PERSIST */

/* NameOfGroupMacro:
 *  return the groupName corresponding to the group_header
 *  given as parameter. 
 */
#define NameOfGroupMacro(groupheader) (groupheader)->group_name

#define EnclosingComponent(item) \
 ((Component *)((long)(item)-headsize(Component)))

#define IsComponentItem(item) \
(item && \
 (((Item *)(item))->GCAttr == -((long)(headsize(Component)/sizeof(long)))) && \
 ((long)GETPROTO(EnclosingComponent(item))==(long)(ComponentPTValue)))

/* Safe way to save AOAroots references */

#if 0
#define TRACE_SAVE_AOA_ROOT()                              \
  DEBUG_AOA(fprintf(output,                                \
                    "saveAOAroot: *0x%x=0x%x\n",           \
                    (int)(AOArootsPtr-1),                  \
                    (int)(cell)))
#else
#define TRACE_SAVE_AOA_ROOT()
#endif

#ifdef RTDEBUG
#define saveAOAroot(cell) saveAOArootDebug(cell)
#else
#define saveAOAroot(cell)				              \
  { if ((ToSpaceTop == AOArootsPtr) || (tempAOAroots==AOArootsPtr)) { \
       tempAOArootsAlloc();                                           \
    }                                                                 \
    TRACE_SAVE_AOA_ROOT();                                            \
    *--AOArootsPtr = (long) (cell);                                   \
  }
#endif

/* FIXME: isProto and isData should be eliminated */
#define isProto(x) 1
#define isData(x) 1

#ifdef sparc
extern unsigned long *start __asm__("_start");
extern unsigned long etext;
#define isCode(addr) ( ((unsigned long)&start <= (unsigned long)(addr)) &&  \
                       ((unsigned long)(addr) < (unsigned long)&etext) )
#endif /* sparc */

#ifdef hppa
extern long *etext;
#define isCode(addr) ( /*((unsigned long)0 <= (unsigned long)(addr)) &&*/  \
                       ((unsigned long)(addr) < (unsigned long)&etext) )
#endif /* hppa */

#ifndef isCode
#define isCode(addr) 0
#endif

#ifdef ppcmac
#define G_Part(proto) ( (proto->GenPart) ? *(pc_t *)proto->GenPart : 0)
#else
#define G_Part(proto) (pc_t) proto->GenPart
#endif /* ppcmac */

#ifdef RTDEBUG
extern long isObject(void *obj);
extern void zero_check(char *p, long bytesize);
extern void CkReg(char *func,long value, char *reg);
extern void CCk(void *r, char *fname, int lineno, char* ref);
#define Ck(r) CCk(r, __FILE__, __LINE__, #r)
extern void CClaim(long cond, char *description, char *fname, int lineno);
#define Claim(r,t) CClaim(r, t, __FILE__, __LINE__)
#define ILLEGAL Illegal(__FILE__, __LINE__)
#else /* !RTDEBUG */

#define isObject(obj) 1 /* assumed always true */
#define CkReg(func,value,reg) {/*empty*/}
#define Ck(r) {/*empty*/}
#define Claim(cond,string) {/*empty*/}
#define ILLEGAL {/*empty*/}

#endif /* RTDEBUG */

#if defined(NEWRUN) || defined(intel)
/* FIXME: push should do boundary check and realloc if needed */
#define push(v) /* printf("push: RefSP=0x%x\n", RefSP); */ *RefSP++ = (Object *) v
#define pop(v)  /* printf("pop: RefSP=0x%x\n", RefSP); */  v = (void *) *--RefSP

#define SaveVar(v)    push(v)
#define RestoreVar(v) pop(v)
#define RestoreIntVar(v) v = (int) *--RefSP
#endif /* NEWRUN || (RTVALHALLA && intel) */

#ifdef NEWRUN

#define AssignReference(theCell, newObject)                                  \
  *(Item **)(theCell) = (Item *)(newObject);                   \
  if (!inIOA((Item *)(theCell)) && inIOA((Item *)(newObject))) \
    AOAtoIOAInsert((Object **)theCell)

#define setup_item(theItem, proto, origin )                                     \
{                                                                               \
   register GCEntry *initTab;                                                   \
                                                                                \
   SETPROTO(((Item *)(theItem)), ((ProtoType *)(proto)));                       \
   if (inIOA(theItem)) {                                                        \
      if (IOAMinAge!=0) ((Item *)(theItem))->GCAttr = IOAMinAge; /* Set item age to IOAMinAge */  \
   } else {                                                                     \
      ((Item *)(theItem))->GCAttr = 0; /* Set item age to 0 */                  \
   }                                                                            \
   /* Initialize the body part of the item, according to the genTable. */       \
                                                                                \
   initTab = (GCEntry *)((char *)(proto)+((ProtoType *)(proto))->GCTabOff);     \
                                                                                \
   /* initTab is now pointing to the static GCTable.                            \
    * This table has zero or more elements terminated with a zero word.         \
    * Each element looks like:                                                  \
    *   WORD  Offset in the generated object, where this static object begins   \
    *   WORD  Signed distance to inclosing object.                              \
    *   LONG  ProtoType of this static object.                                  \
    */                                                                          \
                                                                                \
   for (; initTab->StaticOff; ++initTab) {                                      \
      register PartObject *po;                                                  \
      po = (PartObject *)(((long *)(theItem)) + initTab->StaticOff);            \
      SETPROTO(po,initTab->Proto);                                              \
      po->OrigOff = initTab->OrigOff;                                           \
   }                                                                            \
                                                                                \
   /* Assign origin into theItem. Since theItem may now be allocaed directly in \
    * AOA, it is necessary to use AssignReference.                              \
    */                                                                          \
   AssignReference(((long*)(theItem))+((ProtoType*)(proto))->OriginOff,         \
                   (origin));                                                   \
}


/* Call address "entry" with "current" as first and "item" as second argument */
#define CallBetaEntry(entry, current, item) \
  (* (void (*)(void *, void *))(entry)) ((void *)current, (void *)item)

/* Call Gpart with 4 as first parameter, and item as second argument */
#define CallGPart(gpart, item, SP) \
   CallB(GENMARK, (Object*)(item), (long)gpart, (long)SP)

#ifdef sgi

#define GetPC(SP) ((pc_t)((*((long*)(SP)+PC_OFF))))
#define GetDyn(SP) (*((long*)(SP)-DYN_OFF))
#define GetSPbeta(SP) (*((long *)(SP)))

typedef union FormatI
{
  unsigned long raw;
  struct inst { 
    unsigned long opc: 6;
    unsigned long rs: 5;
    unsigned long rt: 5;
    signed   long offset: 16;
  } instr;
} FormatI;

#define GetSPoff(SPoff, codeAddr)                              \
{ FormatI addiu;                                               \
  addiu.raw = *((long *)codeAddr+3);                           \
  /* Get the stack size allocated for this frame */            \
  SPoff = -addiu.instr.offset;                                 \
}
#endif /* sgi */

#ifdef ppcmac

#define GetPC(SP)     (*((pc_t*)(SP)+PC_OFF))
#define GetDyn(SP) (*((long*)(SP)-DYN_OFF))
#define GetSPbeta(SP) (*((long *)(SP)+6))

typedef union FormatI
{
  unsigned long raw;
  struct inst { 
    unsigned long opc: 6;
    unsigned long s: 5;
    unsigned long a: 5;
    signed   long d: 16;
  } instr;
} FormatI;

#define GetSPoff(SPoff, codeAddr)                              \
{ FormatI stwu;                                                \
  stwu.raw = *((long *)codeAddr+2);                            \
  /* Get the stack size allocated for this frame */            \
  SPoff = -stwu.instr.d;                                       \
}
#endif /* ppcmac */


#ifdef macosx

#define GetPC(SP)     ((pc_t)*((long*)(SP)+PC_OFF))
#define GetDyn(SP) (*((long*)(SP)-DYN_OFF))
#define GetSPbeta(SP) (*((long *)(SP)+6))

typedef union FormatI
{
  unsigned long raw;
  struct inst { 
    unsigned long opc: 6;
    unsigned long s: 5;
    unsigned long a: 5;
    signed   long d: 16;
  } instr;
} FormatI;

#define GetSPoff(SPoff, codeAddr)                              \
{ FormatI stwu;                                                \
  stwu.raw = *((long *)codeAddr+2);                            \
  /* Get the stack size allocated for this frame */            \
  SPoff = -stwu.instr.d;                                       \
}
#endif /* macosx */


#define comppush(v) *CompSP++ = (long) v
#define comppop(v)  v = *--CompSP

#define Protect(var, code)				\
  push(var);						\
  { code; }						\
  pop(var)

#define Protect2(v1, v2, code)				\
  push(v1); push(v2);					\
  { code; }						\
  pop(v2); pop(v1)

#endif /* NEWRUN */


/* check for break instr. - compare debugger/private/external/coreaccess.h*/
#if defined(sparc) || defined(hppa) || defined(ppcmac) || defined(macosx)
#define IS_BREAK_INST(x) (x==0x00000000)
#endif

#ifdef sgi
/* break   0x0,0x28   (was: BREAK 80?) */
#define IS_BREAK_INST(x) (x==0x00000a0d) /* big-endian */
#endif

#ifdef intel
/* int 3 - hex 0xcc */ 
#define IS_BREAK_INST(x) (x==0xcc)
#endif

#endif /* BETARUN_C_MACRO_H */
