/* macroes */

#define inHeap(x)	(inIOA(x) || inLVRA(x))
#define inIOA(x)       (((long) IOA <= (long) x) && ((long) x < (long) IOATop))
#define inToSpace(x)   (((long) ToSpace <= (long) x) && ((long) x < (long) ToSpaceTop)) 
#define inAOA(x)       inArea( AOABaseBlock, x)


#define isSpecialProtoType(x) ((MinPTValue <= (long) x) \
                              && ( (long) x <= MaxPTValue))

#define isAutonomous(x)   ((1 <= x)  && ( x <= 2048))
#define isStatic(x)       (  -0xFFFF <= x) && ( x <= -1)
#define isForward(x)      ( x > 2048 )

#define isValRep(x)      (((long)DoubleRepPTValue <= (long)((x)->Proto))\
			  && ((long)((x)->Proto) <= (long)ValRepPTValue))

#define isStackObject(x) ((x)->Proto == StackObjectPTValue)
#define isComponent(x)   ((x)->Proto == ComponentPTValue)

#define ComponentItem(x) ((ref(Item)) (((long) x) + headsize(Component)))

/* Object sizes in BYTES */
#define ByteRepBodySize(range)   ((((range)+4)/4)*4)
#define WordRepBodySize(range)   (((2*(range)+3)/4)*4)
#define ValRepBodySize(range)    ((range)*4)
#define DoubleRepBodySize(range) ((range)*8)

#if defined(sparc) || defined(hppa)
/* Objects must be multiples of 8 bytes because of reals */
# define ComponentSize(size)   ((4*(size) + headsize(Component) +7) & ~7)
# define StructureSize         ((headsize(Structure)+7) & ~7)
# define RefRepSize(range)     (((range)*4 + headsize(RefRep)+7) & ~7)
# define ValRepSize(range)     (((ValRepBodySize(range) + headsize(ValRep))+7) & ~7)
# define ByteRepSize(range)    ((ByteRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define WordRepSize(range)    ((WordRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define DoubleRepSize(range)  ((DoubleRepBodySize(range) + headsize(ValRep)+7) & ~7)
# define StackObjectSize(size) ((4*(size) + headsize(StackObject)+7) & ~7)
#else
# define ComponentSize(size)   (4*(size) + headsize(Component))
# define StructureSize         headsize(Structure)
# define RefRepSize(range)     ((range)*4 + headsize(RefRep))
# define ValRepSize(range)     (ValRepBodySize(range) + headsize(ValRep))
# define ByteRepSize(range)    (ByteRepBodySize(range) + headsize(ValRep))
# define WordRepSize(range)    (WordRepBodySize(range) + headsize(ValRep))
# define DoubleRepSize(range)  (DoubleRepBodySize(range) + headsize(ValRep))
# define StackObjectSize(size) (4*(size) + headsize(StackObject))
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

#ifdef macintosh
#  define MALLOC(size) NewPtr(size)
#  define FREE(ptr) DisposPtr((Ptr)ptr)
#else
#  define FREE(ptr) free(ptr)
#  ifdef RTDEBUG
#    ifdef sparc
       /* 64 bit alignment because of the reals */
#      define MALLOC(size) memset(memalign(64, (size)), 0, (size))
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
