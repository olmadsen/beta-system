/* macroes */

/* define DMALLOC to 1 to use dmalloc library - requires manual link
 * with /users/beta/GNU/dmalloc-3.1.3/lib/libdmalloc.a before -lc
 */
#undef DMALLOC 

#if defined(macintosh) || defined(MAC)
#  define MALLOC(size) NewPtr(size)
#  define REALLOC(src,size) 0
#  define FREE(ptr) DisposPtr((Ptr)ptr)
#else
#  define FREE(ptr) free(ptr)
#  define REALLOC(src,size) realloc(src,size)
#  ifdef RTDEBUG
#    ifdef sparc
       /* 64 bit alignment because of the reals */
#      define MALLOC(size) memset((void *)memalign(64, (size)), 0, (size))
#    else
#      define MALLOC(size) calloc(size,1)
#    endif
#  else
#    ifdef sparc
       /* 64 bit alignment because of the reals */
#      define MALLOC(size) memalign(64, (size))
#    else
#      define MALLOC(size) malloc(size)
#    endif
#  endif
#endif

#if 0
#define INFO_ALLOC(size) fprintf(output, "alloc: 0x%x at: %s: %d\n",size, __FILE__, __LINE__)
#else
#define INFO_ALLOC(size)
#endif

#ifdef DMALLOC
#include "/users/beta/GNU/dmalloc-3.1.3/include/dmalloc.h"
extern long mcheck_line;
#define MCHECK() mcheck_line=__LINE__; dmalloc_verify(0); mcheck_line=0
#else
#define MCHECK()
#endif

#ifdef sparc
register long    *IOA       asm("%g6");
register unsigned IOATopOff asm("%g7");
#define           IOATop    ((long *) ((long)IOA+IOATopOff))

#else
/* not sparc */
#ifdef RUN
/* RUN: all are declared as variables */
#else
/* Not sparc, not RUN */
#define IOA           _IOA.start
#define IOALimit      _IOA.limit
#define IOASize       _IOA.size
#define IOATopOff     _IOA.topoff
#define IOATop        ((long *) ((long)IOA+IOATopOff))
#endif /* RUN */
#endif /* sparc */

#ifdef RTLAZY
#define isLazyRef(ref) ((lastDangler <= ((int)(ref))) && (((int)(ref)) < -101))
#else
#define isLazyRef(ref) 0
#endif

#if defined(macintosh) || defined (MAC)
#define Notify(s1)           CPrompt(s1, "","","")
#define Notify2(s1,s2)       CPrompt(s1, s2, "", "")
#define Notify3(s1,s2,s3)    CPrompt(s1, s2, s3, 0)
#define Notify4(s1,s2,s3,s4) CPrompt(s1, s2, s3, s4)
#else /* not macintosh */
#ifdef nti
#include <windows.h>
#define Notify(s1)           MessageBox(GetActiveWindow(),s1,"BETA Runtime Notification",MB_OK);
#define Notify2(s1,s2)       do { char x[1000]; sprintf(x, "%s\n%s", s1, s2); Notify(x); } while (0)
#else
#define Notify(s1)           fprintf(output, "%s\n", s1);
#define Notify2(s1,s2)       fprintf(output, "%s\n%s\n", s1, s2);
#define Notify3(s1,s2,s3)    fprintf(output, "%s\n%s\n%s\n", s1, s2, s3);
#define Notify4(s1,s2,s3,s4) fprintf(output, "%s\n%s\n%s\n%s\n", s1, s2, s3, s4);
#endif
#endif



#if defined(sparc) || defined(NEWRUN)
#define inIOA(x)     (((unsigned)(x) - (unsigned)(IOA)) < (unsigned)(IOATopOff))
#else
#define inIOA(x)     (((long)IOA <= (long)(x)) && ((long)(x) < (long)IOATop))
#endif

#define inHeap(x)    (inIOA(x) || inLVRA(x))
#define inToSpace(x) (((long)ToSpace <= (long)(x)) && ((long)(x) < (long)ToSpaceTop)) 
#define inAOA(x)     inArea(AOABaseBlock, (struct Object *)(x))

#define isSpecialProtoType(x) ((MinPTValue <= (long)(x)) && ((long)(x) <= MaxPTValue))

#define isNegativeRef(x) ((long)(x) < 0)
#define isPositiveRef(x) ((long)(x) > 0)

#define isAutonomous(x)   ((1 <= (x)) && ((x) <= 2048))
#define isStatic(x)       (-0xFFFF <= (x)) && ((x) <= -1)
#define isForward(x)      ((x) > 2048 )

#define isValRep(x)      (((long)DoubleRepPTValue <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)ValRepPTValue))
#ifdef STATIC_OBJECT_REPETITIONS
#define isObjectRep(x)   (((long)StatCompRepPTValue <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)DynItemRepPTValue))
#else /* STATIC_OBJECT_REPETITIONS */
#define isObjectRep(x)   (((long)DynCompRepPTValue <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)DynItemRepPTValue))
#endif /* STATIC_OBJECT_REPETITIONS */

#define isStackObject(x) ((x)->Proto == StackObjectPTValue)
#define isComponent(x)   ((x)->Proto == ComponentPTValue)

#define ComponentItem(x) ((ref(Item)) (((long)(x)) + headsize(Component)))

#define ItemSize(proto)          (4*((proto)->Size))
#define ComponentSize(proto)     (headsize(Component)+4*((proto)->Size))

/* Object sizes in BYTES */
#define ByteRepBodySize(range)   ((((range)+4)/4)*4)
#define WordRepBodySize(range)   (((2*(range)+3)/4)*4)
#define ValRepBodySize(range)    ((range)*4)
#define DoubleRepBodySize(range) ((range)*8)
#ifdef STATIC_OBJECT_REPETITIONS
#define StatItemRepSize(range, proto) \
      (((range)*4*((proto)->Size)) + headsize(ObjectRep))
#define StatCompRepSize(range, proto) \
      (((range)*(headsize(Component)+4*((proto)->Size))) + headsize(ObjectRep))
#endif /* STATIC_OBJECT_REPETITIONS */

#if defined(sparc) || defined(hppa) || defined(crts) || defined(NEWRUN)
/* Objects must be multiples of 8 bytes because of reals */
# define StructureSize          ((headsize(Structure)+7) & ~7)
# define RefRepSize(range)      (((range)*4 + headsize(RefRep)+7) & ~7)
# define DynObjectRepSize(range)(((range)*4 + headsize(ObjectRep)+7) & ~7)
# define ValRepSize(range)      (((ValRepBodySize(range) + headsize(ValRep))+7) & ~7)
# define ByteRepSize(range)     ((ByteRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define WordRepSize(range)     ((WordRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define DoubleRepSize(range)   ((DoubleRepBodySize(range) + headsize(ValRep)+7) & ~7)
#ifdef NEWRUN
/* See Suspend.c: it is number of BYTES */
# define StackObjectSize(size)  (((size) + headsize(StackObject) +7) & ~7)
#else
# define StackObjectSize(size)  ((4*(size) + headsize(StackObject) +7) & ~7)
#endif
# define DopartObjectSize(size) (((size) + headsize(DopartObject) +7) & ~7)
#else
# define StructureSize          headsize(Structure)
# define RefRepSize(range)      ((range)*4 + headsize(RefRep))
# define DynObjectRepSize(range)((range)*4 + headsize(ObjectRep))
# define ValRepSize(range)      (ValRepBodySize(range) + headsize(ValRep))
# define ByteRepSize(range)     (ByteRepBodySize(range) + headsize(ValRep))
# define WordRepSize(range)     (WordRepBodySize(range) + headsize(ValRep))
# define DoubleRepSize(range)   (DoubleRepBodySize(range) + headsize(ValRep))
# define StackObjectSize(size)  (4*(size) + headsize(StackObject))
# define DopartObjectSize(size) ((size) + headsize(DopartObject))
#endif

#define toObject(x)      ((ref(Object))      x)
#define toItem(x)        ((ref(Item))        x)
#define toComponent(x)   ((ref(Component))   x)
#define toStackObject(x) ((ref(StackObject)) x)
#define toValRep(x)      ((ref(ValRep))      x)
#define toRefRep(x)      ((ref(RefRep))      x)
#define toStructure(x)   ((ref(Structure))   x)

#define Coerce(x,y) ((struct y *) x)
/* Example:
   struct Item   *aItem;
   struct Object *aObj;

   aItem = Coerce(aObj,Item);
*/

#define Offset(x,y) (((long) (x)) + ((long) (y)))
/* Example:
   struct Item *aItem

   theStaticObject = (struct Object *) Offset( aItem, 25);
*/

#define toKb(x) ( (long) (x)/1024)
#define areaSizeInKb( from, to) ( ( ( (long) to ) - ( (long) from) ) / 1024)
#define areaSize( from, to) ( ( ( (long) to ) - ( (long) from) ) )

#define BlockStart( theB) ((ptr(long)) Offset( theB, sizeof(struct Block)))
#define LVRABlockStart( theB) ((ptr(long)) Offset( theB, sizeof(struct LVRABlock)))

/* MACRO_CopyBlock copy from address src to address dst a block
 * of length = len bytes. (Used to be longs!!)
 */
#define MACRO_CopyBlock( src, dst, len) \
{ long *XXe=((long *) dst)+len,*XXs=((long *) src),*XXd=((long *) dst);\
  while(XXd < XXe) *XXd++ = *XXs++;\
}

/* MACRO_ScanBlock traverse the block, and for each element 
 * code is called, thisCell refers the element in question.
 */
#define MACRO_ScanBlock( block, code) \
{ long *thisCell=(long *)((long)block + sizeof(struct Block)), *XXe=block->top;\
  while( thisCell < XXe){  code;  thisCell++; }\
}

#ifndef __GNUC__
#define long_clear(p, bytesize)                                     \
{                                                                   \
  register long i;                                                  \
  DEBUG_CODE(if ((bytesize)&3)                                      \
	     fprintf(stderr, "long_clear: bytesize&3 != 0\n"));     \
  for (i = (long)(bytesize)/4-1; i >= 0; i--) {                     \
    *((long *)(p)+i) = 0;                                           \
  }                                                                 \
}
#endif

/*
 * GetDistanceToEnclosingObject:
 *  Find the offset (negative) to the most inclosing object e.g.
 *  the offset to the autonomous object in which theObj reside. 
 */

#define GetDistanceToEnclosingObject(theObj, Distance)         \
{                                                              \
  long           _GCAttribute;                                 \
  struct Object *_theObj=theObj;                               \
  Distance = 0;                                                \
  _GCAttribute = _theObj->GCAttr*4;                            \
  while( _GCAttribute < 0 ){                                   \
    Distance += _GCAttribute;                                  \
    _theObj = (struct Object *) Offset(_theObj, _GCAttribute); \
    _GCAttribute = _theObj->GCAttr*4;                          \
  }                                                            \
}

/* NameOfGroupMacro:
 *  return the groupName corresponding to the group_header
 *  given as parameter. 
 */
#if (defined(crts) || defined(NEWRUN))
#define NameOfGroupMacro(groupheader) (groupheader)->group_id
#else
#define NameOfGroupMacro(groupheader)\
  ((char *) &((groupheader)->protoTable[((groupheader)->protoTable[0]) + 1]))
#endif

#define EnclosingComponent(item) \
 ((struct Component *)((long)(item)-headsize(Component)))

#define IsComponentItem(item) \
(item && \
 (((struct Item *)(item))->GCAttr == -(headsize(Component)/sizeof(long))) && \
 (EnclosingComponent(item)->Proto==ComponentPTValue))

/* Generic ValRepSize */

#define DispatchValRepSize(proto, range)			\
(((proto) == ByteRepPTValue) ? ByteRepSize(range) :		\
 (((proto) == ValRepPTValue)   ? ValRepSize(range)  :		\
  (((proto) == DoubleRepPTValue) ? DoubleRepSize(range) :	\
   WordRepSize(range))))

#define DispatchValRepBodySize(proto, range)			\
(((proto) == ByteRepPTValue) ? ByteRepBodySize(range) :		\
 (((proto) == ValRepPTValue)   ? ValRepBodySize(range)  :	\
  (((proto) == DoubleRepPTValue) ? DoubleRepBodySize(range) :	\
   WordRepBodySize(range))))

#ifdef STATIC_OBJECT_REPETITIONS

#define DispatchObjectRepSize(proto, range, iproto)		         \
((((proto) == DynItemRepPTValue) ||                                      \
 (((proto) == DynCompRepPTValue)) ? DynObjectRepSize(range) :	         \
  (((proto) == StatItemRepPTValue)  ? StatItemRepSize(range, iproto)  :	 \
   StatCompRepSize(range, iproto))))

#else /* STATIC_OBJECT_REPETITIONS */

#define DispatchObjectRepSize(proto, range, iproto)                      \
  DynObjectRepSize(range)

#endif /* STATIC_OBJECT_REPETITIONS */

/* Safe way to save AOAroots references */
#define saveAOAroot(cell)				   \
  { if (ToSpaceTop == AOArootsPtr) tempAOArootsAlloc();    \
    DEBUG_AOA(fprintf(output,                              \
                      "saveAOAroot: *0x%x=0x%x\n",         \
                      AOArootsPtr-1,                       \
                      (long)(cell)));                      \
    *--AOArootsPtr = (long) (cell);                        \
  }
#ifdef NEWRUN
#define BETA_DATA1_ADDR &BETA_DATA
#else
#define BETA_DATA1_ADDR &BETA_data1
#endif

#define isData(addr) (((long)BETA_DATA1_ADDR <= (long)(addr)) && \
		      ((long)(addr) < (long)&BETA_end) )

#if (defined(sparc) || defined(hppa) || defined(crts))
#define isProto(addr) (isSpecialProtoType(addr) || \
		       (isData(addr) && (((int)(addr) & 3) == 0)))
#else
#define isProto(addr) (isSpecialProtoType(addr) || (isData(addr)))
#endif

#ifdef crts
#define isCode(addr) ((GetBetaCodeStart()<=(long)(addr)) && \
                     ((long)(addr)<=GetBetaCodeEnd()))
#else

#ifdef sparc

#ifdef sun4s
extern long *start asm("_start");
#else
extern long *start asm("start");
#endif
extern long *etext;
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
#endif

/* inline version of memcpy; works only for 4 byte aligned */
#define MEMCPY(dst,src,bytesize)            \
{  register long i;                         \
   for (i = (bytesize)-4; i >= 0; i -= 4)     \
       *(long *)(((char *)(dst))+i) = *(long *)(((char *)(src))+i); \
}

#ifdef macintosh
#define JUMP_TABLE(addr) (*(long *)(((long)(addr))+2))
#define G_Part(proto) (long) JUMP_TABLE(proto->GenPart)
#else
#ifdef __powerc
#define G_Part(proto) ((long) *(long*)proto->GenPart)
#else
#define G_Part(proto) (long) proto->GenPart
#endif
#endif

#ifdef RTDEBUG
  /* Consistency checks - Checks for valid references */

#define CkReg(func, value, reg)                                              \
{ struct Object *theObj = (struct Object *)(value);                          \
  if (theObj && /* Cleared registers are ok */                               \
      !isLazystruct theObj *&&                                               \
      !isProto(theObj) && /* e.g. AlloI is called with proto in ref. reg. */ \
      !isCode(theObj) && /* e.g. at INNER a ref. reg contains code addr */   \
      !(inBetaHeap(theObj) && isObject(theObj))){                            \
    fprintf(output,                                                          \
	    "%s: ***Illegal reference register %s: 0x%x\n",                  \
	    func, reg, (int)theObj);                                         \
    Illegal();								     \
   }								             \
}

extern void CCk(void *r, char *fname, int lineno, char* ref);
#define Ck(r) CCk(r, __FILE__, __LINE__, #r)

#else /* RTDEBUG */

#define CkReg(func, value, reg)
#define Ck(r)
#define Claim(cond, string)

#endif /* RTDEBUG */

#ifdef NEWRUN

#define AssignReference(theCell, newObject)                                  \
  *(struct Item **)(theCell) = (struct Item *)(newObject);                   \
  if (!inIOA((struct Item *)(theCell)) && inIOA((struct Item *)(newObject))) \
    AOAtoIOAInsert((struct Object **)theCell)

#define setup_item(theItem, proto, origin )                                     \
{                                                                               \
   register struct GCEntry *initTab;                                            \
                                                                                \
   ((struct Item *)(theItem))->Proto = ((struct ProtoType *)(proto));           \
   if (inIOA(theItem))                                                          \
      ((struct Item *)(theItem))->GCAttr = 1; /* Set item age to 1 */           \
   else                                                                         \
      ((struct Item *)(theItem))->GCAttr = 0; /* Set item age to 0 */           \
                                                                                \
   /* Initialize the body part of the item, according to the genTable. */       \
                                                                                \
   initTab = (struct GCEntry *)((char *)(proto)+((struct ProtoType *)(proto))->GCTabOff); \
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
      register struct PartObject *po;                                           \
      po = (struct PartObject *)(((long *)(theItem)) + initTab->StaticOff);     \
      po->Proto = initTab->Proto;                                               \
      po->OrigOff = initTab->OrigOff;                                           \
   }                                                                            \
                                                                                \
   /* Assign origin into theItem. Since theItem may now be allocaed directly in \
    * AOA, it is necessary to use AssignReference.                              \
    */                                                                          \
   AssignReference(((long*)(theItem))+((struct ProtoType*)(proto))->OriginOff,  \
                   (origin));                                                   \
}


/* Call address "entry" with "current" as first and "item" as second argument */
#define CallBetaEntry(entry, current, item) \
  (* (void (*)(void *, void *))(entry)) ((void *)current, (void *)item)

/* Call Gpart with this as first parameter, and item as second argument */
#define CallGPart(gpart, this, item, SP)      \
*++GenSP = (long *) SP;                       \
*++GenSP = (long *) GetSP();                  \
(* (void (*)(void *, void *))((long)(gpart)-8)) ((void *)this, (void *)item); \
GenSP -= 2;                                   \

#ifdef RTDEBUG
#define zero_check(p, bytesize)                         \
{                                                       \
  register long i;                                      \
  if (bytesize&3)                                       \
    fprintf(output, "zero_check: bytesize&3 != 0\n");   \
  for (i = (long)(bytesize)/4-1; i >= 0; i--)           \
    if (*((long *)(p)+i) != 0) {                        \
      fprintf(output, "zero_check failed\n");           \
      Illegal();                                        \
    }                                                   \
}
#endif

#ifdef sgi
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
  addiu.raw = *((long *)codeAddr+SP_ALLOC_OFF);                \
  /* Get the stack size allocated for this frame */            \
  SPoff = -addiu.instr.offset;                                 \
}
#endif

#define push(v) /* printf("push: RefSP=0x%x\n", RefSP); */ *RefSP++ = (struct Object *) v
#define pop(v)  /* printf("pop: RefSP=0x%x\n", RefSP); */  v = (void *) *--RefSP

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

#endif
