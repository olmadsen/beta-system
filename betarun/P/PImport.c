#include "beta.h"

#ifdef PERSIST
#include "referenceTable.h"
#include "objectTable.h"
#include "transitObjectTable.h"
#include "PException.h"
#include "PImport.h"
#include "unswizzle.h"
#include "storageblock.h"
#include "pit.h"

/* LOCAL TYPES */
typedef struct objinfo 
{
    Object *obj;          /* The object that is currently being imported.
                           */
    CAStorage *store;     /* The store in which it resides.
                           */
    unsigned long offset; /* The offset of the object in the store.
                           */
    unsigned long inx;    /* The index of the object in some table ??
                           */
    u_long follow;
} Objinfo;
    
/* LOCAL VARIABLES */
/* We need to know some particulars about the object that is currently
 * being imported. Unfortunately this info cannot be passed as
 * arguments to the object scanner, since that is also used many other
 * places, places where it would be unacceptable to pass such extra
 * arguments around. It follows that we have to make a global variable
 * holding the said info, eventhough we hate and despise global
 * variables.
 */
static Objinfo current;
static u_long prefetch;

/* LOCAL FUNCTION DECLARATIONS */
/* 'refhandler' is called for each reference in the object that is
 * being imported
 */
static void refhandler(REFERENCEACTIONARGSTYPE);

/* FUNCTIONS */
void PIstart(void)
{
   prefetch = 0;
}

void PIend(void)
{
   fprintf(stderr, "prefetch: %d\n", (int)prefetch);
}

static void refhandler(REFERENCEACTIONARGSTYPE)
{
   u_long offset;
   /* '*theCell' is either an offset in the object area to another
    * object in the same storage block, or it might be an offset
    * within the out references area.
    */
    
   /* When this reference was exported one (1) was added to it's
    * value, in order to distinquish zero offsets from none
    * references.
    */
   offset = (u_long)(*theCell) - 1;
   if (!isOutReference(offset)) {
      CAStorage *store;
      store = current.store;
      if (!isSpecialReference(offset)) {            
         /* First check if the object is in memory already */
         ObjInfo *objInfo;
         if ((objInfo = lookupObjectInfo(store, offset)) == NULL) {
            /* The referred object is not in memory */

            /* Check if it is referred from somewhere else */
            void *ip;
            
            if ((ip = lookupReferenceInfo(store, offset)) == NULL) {
               /* The referred object is not referred from elsewhere */
               
               /* Create a new reference info object and refer it indirectly */
               ip = referenceInfo(store, offset);
            } else {
               /* The referred object is referred from somewhere else
                  and we use the same reference info object */
               ;
            }
            *theCell = (Object *)ip;
            newAOAcell(ip, theCell);
            
         } else {
            /* The object is in memory already. Note that the object
             * info returned above is the object info of the enclosing
             * object
             */
            *theCell = (Object *)((unsigned long)(objInfo -> theObj) +
                                  (offset - objInfo -> offset));
         }
      } else {
         if (inIOA(*theCell = handleSpecialReference(offset))) {
            AOAtoIOAInsert( theCell);
         }
      }
   } else {
      /* Cross store reference, currently not implemented */
      ;
   }
}

static void updateTransitObjectTable(Object *theObj)
{
   unsigned long distanceToPart;

   /* We are importing an object and must insert a notification in the
    * transit objects table that this particular object has been
    * imported. This goes for the object itself as well as for any
    * static part objects of the object. This function is called by
    * 'scanObject' for the object itself and all its static parts.
    */
  
   distanceToPart = (unsigned long)theObj - (unsigned long)current.obj;
    
   insertObjectInTransit(current.store, current.offset + distanceToPart, theObj);
    
   if (distanceToPart == 0) {
      theObj -> GCAttr = (u_long)PUTOI(objectInfo(FLAG_INSTORE,
                                                  current.store,
                                                  current.offset,
                                                  theObj));
   }
}

void importStoreObject(Object *theObj,
                       CAStorage *store,
                       u_long offset,
                       u_long inx,
                       u_long follow)
{
   /* 'theObj' 
    *
    * Is an object in store format. This means that all references
    * within 'theObj' to objects in the same store as 'theObj' are
    * implemented as offsets. References to objects in other stores can
    * be identified as such and are implemented as offsets to a proxy
    * object. The task of 'importStoreObject' is to translate all
    * references in 'theObj' to in memory format.
    *
    * 'store' 
    *
    * Is the context local store id of the store holding 'theObj'.
    *
    * 'offset'
    *
    * Is the offset of 'theObj' in the store.
    *
    * 'inx'
    *
    * Is passed to enable some optimization that is so clever that I
    * cannot remember what it is about. It has got nothing to do with
    * the basic actions of importing an object.
    */
  
   Claim(theObj == getRealObject(theObj), "Unexpected part object");
   Claim(inAOA(theObj), "Where is theObj?");
  
   current.obj = theObj;
   current.store = store;
   current.offset = offset;
   current.inx = inx;
   current.follow = follow;
   if (follow < FOLLOWDEPTH) {
      /* We are loading an object that has been forced into
       * memory. This is because it is either an origin or offline
       * allocated object, or a prefetched object. Such objects are
       * referred directly and should not be inserted in the transit
       * object table, but directly into the object table.
       */
      theObj -> GCAttr = (u_long)PUTOI(objectInfo(FLAG_INSTORE, 
                                                  store,
                                                  offset,
                                                  theObj));
      scanObject(theObj, refhandler, NULL, TRUE);
   } else {
      scanObject(theObj, refhandler, updateTransitObjectTable, TRUE);
   }
}

#endif /* PERSIST */
