/* macroes */

/* define DMALLOC to 1 to use dmalloc library - requires manual link
 * with /users/beta/GNU/dmalloc-3.2.1/libdmalloc.a before -lc
 */
#undef DMALLOC

#if defined(MAC)
#  define MALLOC(size) NewPtr(size)
#  define REALLOC(src,size) 0
#  define FREE(ptr) DisposPtr((Ptr)ptr)
#else
#  define FREE(ptr) free(ptr)
#  define REALLOC(src,size) realloc(src,size)
#  ifdef RTDEBUG
#    ifdef sparc
       /* 64 bit alignment because of the reals */
#      ifdef MT
#        define MALLOC(size) MT_malloc(size)
#      else
#        define MALLOC(size) memset((void *)memalign(8, (size)), 0, (size))
#      endif
#    else
#      define MALLOC(size) calloc(size,1)
#    endif
#  else
#    ifdef sparc
       /* 64 bit alignment because of the reals */
#      define MALLOC(size) memalign(8, (size))
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
/* #include "/users/beta/GNU/dmalloc-3.2.1/include/dmalloc.h" */
extern long mcheck_line;
extern int dmalloc_verify(int);
#define MCHECK() mcheck_line=__LINE__; dmalloc_verify(0); mcheck_line=0
#else
#define MCHECK()
#endif

/* macro to be used to declare global variables (including static ones)
 * outside data.gen. 
 */
#define GLOBAL(var) var

#ifdef RTLAZY
#define isLazyRef(ref) ((lastDangler <= ((int)(ref))) && (((int)(ref)) < -101))
#else
#define isLazyRef(ref) 0
#endif

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
#define Notify(s1)           MessageBox(GetActiveWindow(),s1,"BETA Runtime Notification",MB_OK);
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
#define inIOA(x)     ((x) && ((unsigned)(gIOA) <= (unsigned)(x) && (unsigned)(x)< (unsigned)(gIOATop)))
#else
#define inIOA(x)     (((unsigned)(x) - (unsigned)(IOA)) < (unsigned)(IOATopOff))
#endif /* MT */
#else
#define inIOA(x)     (((long)IOA <= (long)(x)) && ((long)(x) < (long)IOATop))
#endif /* sparc || newrun */

#define inHeap(x)    (inIOA(x) || inLVRA(x))
#define inToSpace(x) (((long)ToSpace <= (long)(x)) && ((long)(x) < (long)ToSpaceTop)) 
#define inAOA(x)     inArea(AOABaseBlock, (struct Object *)(x))

#define isSpecialProtoType(x) (((long)(MinPTValue) <= (long)(x)) && \
                               ((long)(x) <= (long)(MaxPTValue)))

#define isNegativeRef(x) ((long)(x) < 0)
#define isPositiveRef(x) ((long)(x) > 0)


#define isAutonomous(gc)   ((IOAMinAge <= (gc)) && ((gc) <= IOAMaxAge))
#define isStatic(gc)       (-0xFFFF <= (gc)) && ((gc) <= -1)
#define isForward(gc)      ((gc) > IOAMaxAge )

#define isValRep(x)      (((long)(DoubleRepPTValue) <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)(LongRepPTValue)))
#define isObjectRep(x)   (((long)(DynCompRepPTValue) <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)(DynItemRepPTValue)))

#define isStackObject(x) ((long)((x)->Proto) == (long)(StackObjectPTValue))
#define isComponent(x)   ((long)((x)->Proto) == (long)(ComponentPTValue))

#define ComponentItem(x) ((ref(Item)) (((long)(x)) + headsize(Component)))

#define ItemSize(proto)          (4*((proto)->Size))
#define ComponentSize(proto)     (headsize(Component)+4*((proto)->Size))

/*** Object sizes in BYTES ****/

#if defined(sparc) || defined(hppa) || defined(NEWRUN)
/* Objects must be multiples of 8 bytes because of reals */
#define ObjectAlign(numbytes)     (unsigned long)(((numbytes)+7) & ~7)
#define ObjectAlignDown(numbytes) (unsigned long)(((numbytes))   & ~7)
#else
#define ObjectAlign(numbytes)     (unsigned long)(numbytes)
#define ObjectAlignDown(numbytes) (unsigned long)(numbytes)
#endif

#define ByteRepBodySize(range)   ((((range)+4)/4)*4)
#define ShortRepBodySize(range)  (((2*(range)+3)/4)*4)
#define LongRepBodySize(range)   ((range)*4)
#define DoubleRepBodySize(range) ((range)*8)

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

#define DispatchValRepSize(proto, range)			                \
(((long)(proto) == (long)(ByteRepPTValue)) ? ByteRepSize(range) :		\
 (((long)(proto) == (long)(LongRepPTValue))   ? LongRepSize(range)  :		\
  (((long)(proto) == (long)(DoubleRepPTValue)) ? DoubleRepSize(range) :    	\
   ShortRepSize(range))))

#define DispatchValRepBodySize(proto, range)			                \
(((long)(proto) == (long)(ByteRepPTValue)) ? ByteRepBodySize(range) :      	\
 (((long)(proto) == (long)(LongRepPTValue))   ? LongRepBodySize(range)  : 	\
  (((long)(proto) == (long)(DoubleRepPTValue)) ? DoubleRepBodySize(range) :	\
   ShortRepBodySize(range))))

/**** Cast operations ****/

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
#define NameOfGroupMacro(groupheader) (groupheader)->group_name

#define EnclosingComponent(item) \
 ((struct Component *)((long)(item)-headsize(Component)))

#define IsComponentItem(item) \
(item && \
 (((struct Item *)(item))->GCAttr == -((long)(headsize(Component)/sizeof(long)))) && \
 ((long)(EnclosingComponent(item)->Proto)==(long)(ComponentPTValue)))

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

#define saveAOAroot(cell)				   \
  { if (ToSpaceTop == AOArootsPtr) tempAOArootsAlloc();    \
    TRACE_SAVE_AOA_ROOT();                                 \
    *--AOArootsPtr = (long) (cell);                        \
  }

#define BETA_DATA1_ADDR &BETA_DATA

/* cannot say anything about data segments order in general.
 * on unix, probably _edata and _end could be used.
 */
#define isData(addr) 1 

#if (defined(sparc) || defined(hppa))
#define isProto(addr) (isSpecialProtoType(addr) || \
		       (isData(addr) && (((int)(addr) & 3) == 0)))
#else
#define isProto(addr) (isSpecialProtoType(addr) || (isData(addr)))
#endif

#ifdef sparc
extern long *start __asm__("_start");
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

/* inline version of memcpy; works only for 4 byte aligned */
#define MEMCPY(dst,src,bytesize)            \
{  register long i;                         \
   for (i = (bytesize)-4; i >= 0; i -= 4)     \
       *(long *)(((char *)(dst))+i) = *(long *)(((char *)(src))+i); \
}

#ifdef macppc
#define G_Part(proto) ( (proto->GenPart) ? *(long*)proto->GenPart : 0)
#else
#define G_Part(proto) (long) proto->GenPart
#endif

#ifdef RTDEBUG
  /* Consistency checks - Checks for valid references */

#define CkReg(func,value,reg)                                              \
{ struct Object *theObj = (struct Object *)(value);                          \
  if (theObj && /* Cleared registers are ok */                               \
      !isLazyRef(theObj) &&                                                  \
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

#define CkReg(func,value,reg) {/*empty*/}
#define Ck(r) {/*empty*/}
#define Claim(cond,string) {/*empty*/}

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
      if (IOAMinAge!=0) ((struct Item *)(theItem))->GCAttr = IOAMinAge; /* Set item age to IOAMinAge */           \
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

/* Call Gpart with 4 as first parameter, and item as second argument */
#define CallGPart(gpart, item, SP) \
   CallB(GENMARK, (struct Object*)(item), (long)gpart, (long)SP)

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

#define GetPC(SP) (*((long*)(SP)-1))
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
#endif

#ifdef macppc

#define GetPC(SP)     (*((long*)(SP)+2))
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
#endif

#define push(v) /* printf("push: RefSP=0x%x\n", RefSP); */ *RefSP++ = (struct Object *) v
#define pop(v)  /* printf("pop: RefSP=0x%x\n", RefSP); */  v = (void *) *--RefSP

#define SaveVar(v)    push(v)
#define RestoreVar(v) pop(v)

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
