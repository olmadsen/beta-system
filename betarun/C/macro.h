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

#define isValRep(x)      (((long) (x)->Proto) == ValRepPTValue)
#define isByteRep(x)     (((long) (x)->Proto) == ByteRepPTValue)
#define isStackObject(x) (((long) (x)->Proto) == StackObjectPTValue)
#define isComponent(x)   (((long) (x)->Proto) == ComponentPTValue)
#define ComponentItem(x) ((ref(Item)) (((long) x) + 24))

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
