/* macroes */

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
#define Notify(s1)           fprintf(output, "%s\n", s1);
#define Notify2(s1,s2)       fprintf(output, "%s\n%s\n", s1, s2);
#define Notify3(s1,s2,s3)    fprintf(output, "%s\n%s\n%s\n", s1, s2, s3);
#define Notify4(s1,s2,s3,s4) fprintf(output, "%s\n%s\n%s\n%s\n", s1, s2, s3, s4);
#endif

#define inHeap(x)    (inIOA(x) || inLVRA(x))
#define inIOA(x)     (((long)IOA <= (long)(x)) && ((long)(x) < (long)IOATop))
#define inToSpace(x) (((long)ToSpace <= (long)(x)) && ((long)(x) < (long)ToSpaceTop)) 
#define inAOA(x)     inArea(AOABaseBlock, (struct Object *)(x))

#define isSpecialProtoType(x) ((MinPTValue <= (long)(x)) \
                              && ((long)(x) <= MaxPTValue))

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

#if defined(sparc) || defined(hppa) || defined(crts)
/* Objects must be multiples of 8 bytes because of reals */
# define StructureSize          ((headsize(Structure)+7) & ~7)
# define RefRepSize(range)      (((range)*4 + headsize(RefRep)+7) & ~7)
# define DynObjectRepSize(range)(((range)*4 + headsize(ObjectRep)+7) & ~7)
# define ValRepSize(range)      (((ValRepBodySize(range) + headsize(ValRep))+7) & ~7)
# define ByteRepSize(range)     ((ByteRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define WordRepSize(range)     ((WordRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define DoubleRepSize(range)   ((DoubleRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define StackObjectSize(size)  ((4*(size) + headsize(StackObject) +7) & ~7)
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

/* MACRO_CopyBlock copy from address src to address dst a block
 * of length = len bytes. (Used to be longs!!)
 */
#define MACRO_CopyBlock( src, dst, len) \
{ long *XXe=((long *) dst)+len,*XXs=((long *) src),*XXd=((long *) dst);\
  while(XXd < XXe) *XXd++ = *XXs++;\
}

#define MACRO_TraverseObject( obj, reffunc, objfunc )\
{\
}

#define MACRO_TraverseObjectFlat( obj, reffunc, objfunc )\
{\
}

/* MACRO_ScanRepetition traverse the rep, and for each element 
 * code is called, thisCell refers the element in question.
 */
#define MACRO_ScanRepetition( rep, code) \
{ long *thisCell=(long *)&rep->Body[0], *XXe=((long *) rep)->HighBorder;\
  while( thisCell < XXe){  code;  thisCell++; }\
}

/* MACRO_ScanBlock traverse the block, and for each element 
 * code is called, thisCell refers the element in question.
 */
#define MACRO_ScanBlock( block, code) \
{ long *thisCell=(long *)( (long) block + sizeof(struct Block)), *XXe=block->top;\
  while( thisCell < XXe){  code;  thisCell++; }\
}

#define MACRO_DistanceToEnclosing( obj, variable)\
{ struct Object *XXobj=(struct Object *)obj;\
  while(XXobj->GCAttr<0)\
    XXobj=(struct Object *) ((long)XXobj + XXobj->GCAttr*4);\
  variable=(long)obj - (long)XXobj;\
}

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
#define saveAOAroot(cell)				        \
  ((ToSpaceTop == AOArootsPtr)?tempAOArootsAlloc(): (void) 0,	\
   *--AOArootsPtr = (long) (cell))

#ifdef mc68020
# ifdef sun
# define asmemptylabel(label) \
   __asm__(".globl " #label ";" #label ":" )
# endif

#if 0
# ifdef hpux
# define asmemptylabel(label) \
   __asm__("global " #label ";" #label ":" )
# endif
#else
# define asmemptylabel(label)
#endif

# ifdef macintosh
# define asmemptylabel(label)
# endif
#else
# if defined(linux) || defined(nti)
# define asmemptylabel(label)
# else
# if defined(sparc) || defined(hppa)
  /* See sparcdep.h/snakedep.h */
# else
# define asmlabel(label, code)
# define asmemptylabel(label)
# define asmcomment(text)
# endif
# endif
#endif

#define isData(addr) (((long)&BETA_data1 <= (long)(addr)) && \
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
