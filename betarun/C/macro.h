/* macroes */

/* define DMALLOC to 1 to use dmalloc library - requires manual link
 * with /users/beta/GNU/dmalloc-3.2.1/libdmalloc.a before -lc
 */
#undef DMALLOC

#if defined(MAC)
#  define MALLOC(size) Newsize *
#  define REALLOC(src,size) \
     fprintf(output, "Error: REALLOC called\n!")); \
     fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__)
#  define FREE(ptr) DisposPtr((Ptr)ptr)
#else
   /* UNIX or Windows */
#  define FREE(ptr) free(ptr)
#  define REALLOC(src,size) realloc(src,size)
#  ifdef RTDEBUG
#    if defined(sparc) || defined(sgi) || defined(hppa)
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
#    if defined(sparc) || defined(sgi) || defined(hppa)
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

#define inHeap(x)    inIOA(x)
#define inToSpace(x) (((long)ToSpace <= (long)(x)) && ((long)(x) < (long)ToSpaceTop)) 
#define inAOA(x)     inArea(AOABaseBlock, (Object *)(x))
#define inAOAUnused(x) inAreaUnused(AOABaseBlock, (Object *)(x))

#define isSpecialProtoType(x) (((long)(MinPTValue) <= (long)(x)) && \
                               ((long)(x) <= (long)(MaxPTValue)))

#define isNotSpecialProtoType(x) (((long)(MinPTValue) > (long)(x)) || \
                                  ((long)(x) > (long)(MaxPTValue)))

#define isNegativeRef(x) ((long)(x) < 0)
#define isPositiveRef(x) ((long)(x) > 0)

/* AOAGC values for GCAttr.  Legal values are DEAD, FREE or link to
 * another object.  Also LINKEND is legal, and is alive.
 * Please note that GCAttr==0 is illegal as none of the above is zero...
 */
#define AOAISDEAD(obj)  (obj->GCAttr == DEADOBJECT)
#define AOAISFREE(obj)  (obj->GCAttr == FREECHUNK)
#define AOAISALIVE(obj) (obj->GCAttr >=  LISTEND)
#define isLink(gcattr) (gcattr > LISTEND)
#define isEnd(gcattr) (gcattr == LISTEND)

#if defined(LIN)
#define isAutonomous(gc)   ((IOAMinAge <= (gc)) && ((gc) <= IOAMaxAge + 1))
#else /* LIN */
#define isAutonomous(gc)   ((IOAMinAge <= (gc)) && ((gc) <= IOAMaxAge))
#endif /* LIN */

#define isStatic(gc)       (-0xFFFF <= (gc)) && ((gc) <= -1)

#if defined(LIN)
#define isForward(gc)      ((gc) > IOAMaxAge + 1)
#else /* LIN */
#define isForward(gc)      ((gc) > IOAMaxAge )
#endif /* LIN */

#define isValRep(x)      (((long)(DoubleRepPTValue) <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)(LongRepPTValue)))
#define isObjectRep(x)   (((long)(DynCompRepPTValue) <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)(DynItemRepPTValue)))

#define isStackObject(x) ((long)((x)->Proto) == (long)(StackObjectPTValue))
#define isComponent(x)   ((long)((x)->Proto) == (long)(ComponentPTValue))

#define ComponentItem(x) ((Item *) (((long)(x)) + headsize(Component)))

#define ItemSize(proto)          (4*((proto)->Size))
#define ComponentSize(proto)     (headsize(Component)+4*((proto)->Size))

/*** Object sizes in BYTES ****/

/* Objects must be multiples of 8 bytes because of reals */
#define ObjectAlign(numbytes)     (unsigned long)(((numbytes)+7) & ~7)
#define ObjectAlignDown(numbytes) (unsigned long)(((numbytes))   & ~7)

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
{ long *thisCell=(long *)((long)block + sizeof(Block)), *XXe=block->top;\
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
  Object *_theObj=theObj;                               \
  Distance = 0;                                                \
  _GCAttribute = _theObj->GCAttr*4;                            \
  while( _GCAttribute < 0 ){                                   \
    Distance += _GCAttribute;                                  \
    _theObj = (Object *) Offset(_theObj, _GCAttribute); \
    _GCAttribute = _theObj->GCAttr*4;                          \
  }                                                            \
}

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

#define saveAOAroot(cell)				              \
  { if ((ToSpaceTop == AOArootsPtr) || (tempAOAroots==AOArootsPtr)) { \
       tempAOArootsAlloc();                                           \
    }                                                                 \
    TRACE_SAVE_AOA_ROOT();                                            \
    *--AOArootsPtr = (long) (cell);                                   \
  }

/* FIXME: isProto could be defined to IsPrototypeOfProcess
 * in DEBUG runtime system.
 * This is too expensive in non-debug.
 * But isProto is not used in non-debug situations a lot of places,
 * apparently only in sparc stack traversal.
 * These should be eliminated (i.e. isProto only defined in RTDEBUG).
 */

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
#endif /* macppc */

#ifdef RTDEBUG
  /* Consistency checks */

#define zero_check(p, bytesize)                         \
{                                                       \
  register long i;                                      \
  if (bytesize&3)                                       \
    fprintf(output, "zero_check: bytesize&3 != 0\n");   \
  for (i = (long)(bytesize)/4-1; i >= 0; i--)           \
    if (*((long *)(p)+i) != 0) {                        \
      fprintf(output,                                   \
              "%s: %d: zero_check(0x%x, %d) failed\n",  \
              __FILE__,                                 \
              __LINE__,                                 \
              (int)p,                                   \
              bytesize);                                \
      Illegal();                                        \
    }                                                   \
}

#define CkReg(func,value,reg)                                              \
{ Object *theObj = (Object *)(value);                          \
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

#if defined(NEWRUN) || (defined(RTVALHALLA) && defined(intel))
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
   register GCEntry *initTab;                                            \
                                                                                \
   ((Item *)(theItem))->Proto = ((ProtoType *)(proto));           \
   if (inIOA(theItem))                                                          \
      if (IOAMinAge!=0) ((Item *)(theItem))->GCAttr = IOAMinAge; /* Set item age to IOAMinAge */           \
   else                                                                         \
      ((Item *)(theItem))->GCAttr = 0; /* Set item age to 0 */           \
                                                                                \
   /* Initialize the body part of the item, according to the genTable. */       \
                                                                                \
   initTab = (GCEntry *)((char *)(proto)+((ProtoType *)(proto))->GCTabOff); \
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
      register PartObject *po;                                           \
      po = (PartObject *)(((long *)(theItem)) + initTab->StaticOff);     \
      po->Proto = initTab->Proto;                                               \
      po->OrigOff = initTab->OrigOff;                                           \
   }                                                                            \
                                                                                \
   /* Assign origin into theItem. Since theItem may now be allocaed directly in \
    * AOA, it is necessary to use AssignReference.                              \
    */                                                                          \
   AssignReference(((long*)(theItem))+((ProtoType*)(proto))->OriginOff,  \
                   (origin));                                                   \
}


/* Call address "entry" with "current" as first and "item" as second argument */
#define CallBetaEntry(entry, current, item) \
  (* (void (*)(void *, void *))(entry)) ((void *)current, (void *)item)

/* Call Gpart with 4 as first parameter, and item as second argument */
#define CallGPart(gpart, item, SP) \
   CallB(GENMARK, (Object*)(item), (long)gpart, (long)SP)

#ifdef sgi

#define GetPC(SP) (*((long*)(SP)+PC_OFF))
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

#ifdef macppc

#define GetPC(SP)     (*((long*)(SP)+PC_OFF))
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
#endif /* macppc */

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
