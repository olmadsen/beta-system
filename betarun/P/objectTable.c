#include "beta.h"

#ifdef PERSIST
#include "objectTable.h"
#include "transitObjectTable.h"
#include "storageblock.h"
#include "PException.h"
#include "PExport.h"
#include "specialObjectsTable.h"
#include "storagemanager.h"
#include "proto.h"
#include "pit.h"

/* LOCAL TYPES */
#define NULLPOINTER 0xFFFFFFFF
#define RECURSION 1

/* LOCAL DEFINITIONS */
#define SIZEOFPROTOANDGCATTRIBUTE 8

/* LOCAL VARIABLES */
/* Contains the info set of all persistent objects currently in
 * memory. The key to search into this table is the (store, offset)
 * pair of the object.
 */
static Trie *loadedObjects = 0;
static int newPersistentObjectInIOA = 0;
#if RECURSION
static Object *head, *tail, *last;
#endif /* RECURSION */

/* GLOBAL VARIABLES */

int AllowLazyFetch = 0; /* Must be set using setAllowLazyFetch */

/* used from psbody.bet */
void setAllowLazyFetch(int val)
{
  AllowLazyFetch = val; 
}

/* LOCAL FUNCTION DECLARATIONS */
static void objhandler(Object *theObj);
static void insertObjectAndParts(CAStorage *store,
                                 u_long  offset,
                                 Object *theObj,
                                 ObjInfo *objInfo);
static u_long allocateStorage(CAStorage *store, Object *realObj, u_long nb);
static void markReachableObjects(REFERENCEACTIONARGSTYPE);
static void visitOffsetsFuncP1(contentsBox *cb);
static void visitStoresFuncP1(contentsBox *cb);
static void markOfflineAndOriginObjectsAlive(REFERENCEACTIONARGSTYPE);
static void visitOffsetsFuncP5_1(contentsBox *cb);
static void visitStoresFuncP5_1(contentsBox *cb);
static void updateObjectInStore(Object *theObj,
				unsigned long objSize,
				CAStorage *store, 
				unsigned long offset,
				unsigned short Flags);
static void visitOffsetsFuncP5_2(contentsBox *cb);
static void visitStoresFuncP5_2(contentsBox *cb);
static void freeObjectCopy(Object *obj);
static void freeOffsetsFunc(u_long contents);
static void freeStoresFunc(u_long contents);
static void freeStores(u_long contents);
static void visitStoresFuncP3(contentsBox *cb);
static void visitOffsetsFuncP3(contentsBox *cb);

/* FUNCTIONS */
void initLoadedObjects(void)
{
    loadedObjects = TInit();
    initTransitObjectTable();
}

/* For a justification of the local variables below see comment in
 * 'PExport.h' */
static CAStorage *currentStore;
static u_long currentOffset;
static Object *theRealObj;
static ObjInfo *currentInfo;

/* Functions 'insertStoreOffset', 'insertObject', 'objhandler' and
 * 'insertObjectAndParts' are used in conjunction to insert an object
 * and its parts into the set of loaded objects */
void insertStoreOffset(CAStorage *store, 
		       u_long offset, 
		       u_long info,
		       Trie **loadedObjects)
{
   Trie *loadedObjectsOFbefore, *loadedObjectsOFafter;
    
   /* Check if store is member */
   if ((loadedObjectsOFbefore =
        loadedObjectsOFafter =
        (Trie *)TILookup((u_long)store, *loadedObjects)) == NULL) {
      /* insert new table for store */
      loadedObjectsOFafter = TInit();
   }
    
   /* insert offset in loadedObjectsOF */
   TInsert(offset + 1, info, &loadedObjectsOFafter, offset + 1);
    
   /* */
   if (loadedObjectsOFbefore == loadedObjectsOFafter) {
      return;
   } else {
      TInsert((u_long)store,
              (unsigned long)loadedObjectsOFafter,
              loadedObjects,
              (u_long)store);
   }
}

void insertObject(CAStorage *store, u_long offset, ObjInfo *objInfo)
{
    insertStoreOffset(store, offset, (u_long)objInfo, &loadedObjects);
}

static void objhandler(Object *theObj)
{
    u_long distanceToPart;
    distanceToPart = (u_long)theObj - (u_long)theRealObj;
    insertObject(currentStore,
                 currentOffset + distanceToPart,
                 currentInfo);
}

static void insertObjectAndParts(CAStorage *store,
                                 u_long  offset,
                                 Object *theObj,
                                 ObjInfo *objInfo)
{  
    currentInfo = objInfo;
    currentStore = store;
    currentOffset = offset;
    theRealObj = theObj;
    
    scanObject(theObj,
               NULL,
               objhandler,
               TRUE);

}

ObjInfo *objectInfo(unsigned short flags,
                    CAStorage *store,
                    unsigned long offset,
                    Object *theObj)
{
    ObjInfo *objInfo;
    Claim(theObj == getRealObject(theObj), "Unexpected part object");

    /* Only one object info object is created per object */
    
    objInfo = (ObjInfo *)AOAallocate(sizeof(struct _ObjInfo), TRUE);
    SETPROTO(objInfo, ObjInfoPTValue);
    
    objInfo -> flags = flags;
    objInfo -> store = store;
    objInfo -> offset = offset;
    objInfo -> theObj = theObj;
    
    /* register the object and the part objects in the set of loaded
     * objects to enable mapping from (store, offset) pairs to object
     * info.
     */
    insertObjectAndParts(store, offset, theObj, objInfo);
    
    return objInfo;
}
 
/* Returns object info of object identified by (store, offset) */
ObjInfo *lookupObjectInfo(CAStorage *store, u_long offset)
{
    Trie *stores;
    
    /* Check if store is member of 'loadedObjects' */
    if ((stores = (Trie *)TILookup((u_long)store, loadedObjects))) {
        ObjInfo *objInfo;
        if ((objInfo = (ObjInfo *)TILookup(offset + 1, stores))) {
            return objInfo;
        }
    }
    return NULL;
}

void objectAlive(Object *theObj)
{
   ObjInfo *objInfo;

   objInfo = (ObjInfo *)(GETOI(theObj -> GCAttr));
   
   /* Marks the object info object in AOA as alive */
   objInfo -> GCAttr = LISTEND;

   if (objInfo -> flags & FLAG_INSTORE) {
      Object *objcopy;
      
      /* Marks the object copy in AOA as alive */
      objcopy = (Object*)((char*)theObj+4*ObjectSize(theObj));
      
      objcopy -> GCAttr = LISTEND;
   }   
}

u_long objectIsDead(Object *theObj)
{
   return (((ObjInfo *)(GETOI(theObj -> GCAttr))) -> GCAttr == DEADOBJECT);
}

/* Phases:
 *
 * The set of all persistent objects currently in memory is registered
 * in the set 'loadedObjects'. A reference to the object info of all
 * persistent objects is inserted in the GC attribute. At each AOAGc
 * the following phases are completed in order to keep this set
 * updated:
 *
 * - IOAGc #1,
 *
 *   The first IOAGc will copy all new persistent object in IOA to
 *   AOA. This is used to handle new objects created by user code.
 *
 * - Update peristent objects graph
 *
 *   The set of persistent objects is scanned and all object info for
 *   new persistent objects that have become reachable is inserted in
 *   the set as well. Only objects in AOA can point to their object
 *   info through their GC attribute. This is because IOAGc uses the
 *   GC attribute when the object is in IOA. For this reason all new
 *   persistent objects in IOA are forced to AOA. If they are in IOA
 *   they are marked so that the ensuing IOAGc will force them to AOA.
 *
 *   The object will look alive to AOAGc since its GCattribute is a
 *   pointer. The object info object looks DEAD.
 *
 * - IOAGc #2
 *
 *   This IOAGc will move all new persistent objects in IOA to
 *   AOA. Still all persistent object look alive and their object info
 *   objects look DEAD.
 *
 *  - AOAGc start
 *
 *   Apart from doing normal AOAGc this GC will also mark all
 *   persistent objects that are referred by transient objects. This
 *   is done by marking the object info object alive. Such objects
 *   will be retained in memory.
 *
 *  - Retain additional objects.
 *
 *    The set of persistent objects is scanned and some additional
 *    persistent object may be marked alive even though they are not
 *    referrred from any transient objects. To be explained, only
 *    relevant for BETA.
 *
 *  - Swizzle references.
 *
 *    The set of persistent objects is scanned and all references to
 *    dead persistent objects are swizzled.
 *
 *  - Remove dead objects
 *
 *    Handled at the final sweep of AOAGc. All persistent objects whos
 *    info object is marked alive is retained in memory and the info
 *    object is marked DEAD.
 *
 *    Persistent objects who's info object is marked as DEAD are
 *    updated to the store and both the object itself and its info
 *    object is reclaimed.
 */
 
/**************************************************************************/
/* Phase one: Update graph of persistent objects  (find transitive closure) */
/**************************************************************************/

static CAStorage *currentStoreID = NULL;

void setCurrentStoreID(CAStorage *ID)
{
   currentStoreID = ID;
}

static u_long allocateStorage(CAStorage *store, Object *realObj, u_long nb)
{
    /* We cannot save component objects. Rather they should be
     * registered as special objects
     */
   Claim(getRealObject(realObj) == realObj, "Unexpected part object");
   
    if (isComponent(realObj)) {
        fprintf(output,
                "allocateStorage: Saving component (register it as special object)\n");
    }
    
    return SBOBJcreate(store, (char *)realObj, nb);
}

void markObject(Object *obj, int follow)
{
   Object *realObj;
   
   if (!inPIT((void *)obj)) {
      realObj = getRealObject(obj);
      if ((IOAActive && inToSpace(realObj)) ||
          (!IOAActive && inIOA(realObj)))
      {
         if (!IOAISPERSISTENT(realObj)) {
            unsigned long offset;
            /* We have encountered a new persistent object in IOA. It
             * cannot be made persistent all at once since it needs to
             * be moved to AOA first. In order to force a move to AOA
             * we insert in the GC field of the object an indication
             * to the IOA collector that it should force this object
             * into IOA at the next IOA GC. But we still insert the
             * object in the object table. The object table entry will
             * point to the object in IOA. This reference must be
             * redirected when the object is moved to AOA.
             */
            
            offset = allocateStorage(currentStoreID,
                                     realObj,
                                     (u_long)4*ObjectSize(realObj));
            
            realObj -> GCAttr = IOAPersist;

            objectInfo(FLAG_INMEM,
                       currentStoreID,
                       offset,
                       realObj);

            newPersistentObjectInIOA = 1;

            if (follow) {
               scanObject(realObj,
                          markReachableObjects,
                          NULL,
                          TRUE);
            }
         }
      } else {
         Claim(inAOA(realObj), "markReachableObjects: Where is theObj?");
         if (!AOAISPERSISTENT(realObj)) {
            if (!(realObj -> GCAttr == AOASPECIAL)) {
               /* We have encountered a new persistent object in AOA, and
                  we can now proceed to allocate space for it in the store
                  and in the object table. */
               u_long offset;
               
               offset = allocateStorage(currentStoreID,
                                        realObj,
                                        (u_long)4*ObjectSize(realObj));
               
               realObj -> GCAttr = (u_long)PUTOI(objectInfo(FLAG_INMEM,
                                                            currentStoreID,
                                                            offset,
                                                            realObj));
               
               /* The flag FLAG_INMEM indicates that this object has no copy of
                * itself following it as is the case with objects loaded from the
                * store. This copy is created in order to check if the object has
                * been changed while loaded. If not there is no need to save it
                * back onto the store when it becomes unreachable from this
                * context.
                */
               
               if (follow) {
                  scanObject(realObj,
                             markReachableObjects,
                             NULL,
                             TRUE);
               }
            }
         }
      }
   }
}

static void markReachableObjects(REFERENCEACTIONARGSTYPE)
{
  markObject(*theCell, 1);
}

#if RECURSION
static void appendObject(Object *obj)
{
  if (head == NULL) {
    last = head = obj;
  } else {
    last -> GCAttr = (u_long)obj;
    last = obj;
  }
  last -> GCAttr = NULLPOINTER;
}

static void collectPersistentObjects(REFERENCEACTIONARGSTYPE)
{
  if (!inPIT((void *)*theCell)) {
    Object *realObj;

    realObj = getRealObject(*theCell);
    if (realObj -> GCAttr < IOAPersist) {

      /* The object might be in IOA or AOA. In either case it is not
       * in the list, nor is it persistent */      
      
      if ((IOAActive && inToSpace(realObj)) ||
	  (!IOAActive && inIOA(realObj))) {
	/* The object is in IOA and cannot be persistent, nor is it in the list */
	appendObject(realObj);
      } else {
	Claim(inAOA(realObj), "markReachableObjects: Where is theObj?");	
	
	if (!(realObj -> GCAttr == AOASPECIAL)) {	    
	  /* We have encountered a new persistent object in AOA,
	   * that must be in the list */
	  appendObject(realObj);
	}
      }
    }
  }
}
#endif /* RECURSION */

static void visitOffsetsFuncP1(contentsBox *cb)
{
    ObjInfo *current;
    
    current = (ObjInfo *)(cb -> contents);
    setCurrentStoreID(current -> store);

    Claim(inAOA(current -> theObj), "The object should have been moved");
    Claim(GETOI(current -> theObj -> GCAttr) == (u_long)current, "Unlinked object info");
    
#if RECURSION
    scanObject(current -> theObj,
               collectPersistentObjects,
               NULL,
               TRUE);
#else
    scanObject(current -> theObj,
               markReachableObjects,
               NULL,
               TRUE);    
#endif    

    /* Objects from the current table are scanned right now and
     * inserted in the new table. The new objects not in the old table
     * will be insert by 'objectInfo' when a new info object is
     * created for them.
     */
    insertObjectAndParts(current -> store,
                         current -> offset,
                         current -> theObj,
                         current);
}

static void visitStoresFuncP1(contentsBox *cb)
{
    TIVisit((Trie *)(cb -> contents), visitOffsetsFuncP1);
}

static void freeStores(u_long contents)
{
    TIFree((Trie *)contents, NULL);
}

void phaseOne(void)
{
  Trie *oldTable;
  
  if ((oldTable = loadedObjects)) {
    loadedObjects = TInit();
      
#if RECURSION
    /* Initialize list of new persistent object */
    head = tail = last = NULL;
#endif /* RECURSION */
      
    TIVisit(oldTable, visitStoresFuncP1);
      
#if RECURSION
    if (head) {
      tail = head;
      while (tail != (Object *)NULLPOINTER) {
	scanObject(tail,
		   collectPersistentObjects,
		   NULL,
		   TRUE);
	tail = (Object *)(tail -> GCAttr);
      }
	
      tail = head;
      while (tail != (Object *)NULLPOINTER) {
	static Object *current;
	current = tail;
	  
	tail = (Object *)(tail -> GCAttr);
	current -> GCAttr = 0;
	  
	markObject(current, 0);
      }
    }
#endif /* RECURSION */
      
    TIFree(oldTable, freeStores);
  }
}

/**************************************************************************/
/* Phase two: IOAGc, moves persistent objects in IOA to AOA               */
/**************************************************************************/

/**************************************************************************/
/* Phase three: updates set of loaded objects                             */
/**************************************************************************/

static void visitOffsetsFuncP3(contentsBox *cb)
{
   ObjInfo *current;
   
   current = (ObjInfo *)(cb -> contents);
   if (inIOA(current -> theObj)) {
      /* Redirect object reference to the object that has now
       *  been moved to AOA.
       */
      Claim(inAOA((Object *)(current -> theObj -> GCAttr)), "Where is theObj?");
      
      current -> theObj = (Object *)(current -> theObj -> GCAttr);
      current -> theObj -> GCAttr = (u_long)PUTOI((u_long)current);
   }
}

static void visitStoresFuncP3(contentsBox *cb)
{
   TIVisit((Trie *)(cb -> contents), visitOffsetsFuncP3);
}

void phaseThree(void)
{
   if (newPersistentObjectInIOA) {
      TIVisit(loadedObjects, visitStoresFuncP3);
      newPersistentObjectInIOA = 0;
   }
}

/**************************************************************************/
/* Phase four: AOAGc, marks persistent objects transiently referred       */
/**************************************************************************/

/**************************************************************************/
/* Phase five: removes unreferred persistent objects                      */
/**************************************************************************/

static void markOfflineAndOriginObjectsAlive(REFERENCEACTIONARGSTYPE)
{
   Object *theRealObj;
    
   if (!inPIT(*theCell)) {
      if (refType == REFTYPE_DYNAMIC) {
         return;
      } else {
         theRealObj = getRealObject(*theCell);
         Claim(inAOA(theRealObj), "Where is the object");

         if (AOAISPERSISTENT(theRealObj)) {
	   Claim(AllowLazyFetch, "AllowLazyFetch not set but should be!");
	   if (refType != REFTYPE_DYNAMIC) {
               /* this is a persistent object referred through a non
                * dynamic reference. It must be kept alive no matter
                * what
                */
               
               if (objectIsDead(theRealObj)) {
                  objectAlive(theRealObj);
                  scanObject(theRealObj,
                             markOfflineAndOriginObjectsAlive,
                             NULL,
                             TRUE);
               }  
            }
         } else {
            /* Origin is special object and not in persistent set */
            ;
         }
      }
   }
}


static void visitOffsetsFuncP5_1(contentsBox *cb)
{
   ObjInfo *current;
   current = (ObjInfo *)(cb -> contents);
   if (!AllowLazyFetch) {
     objectAlive(current ->theObj);
   } else if (AOAISALIVE((Object *)current)) {
      /* The object info object is alive, thus the object itself is
       * alive and we scan its origins */
      
      /* handle origin and offline allocated objects */

      scanObject(current ->theObj,
                 markOfflineAndOriginObjectsAlive,
                 NULL,
                 TRUE);
   }
}

static void visitStoresFuncP5_1(contentsBox *cb)
{
  TIVisit((Trie *)(cb -> contents), visitOffsetsFuncP5_1);
}

void handlePersistentCell(REFERENCEACTIONARGSTYPE)
{
   Object *realObj, *theObj;
   ObjInfo *objInfo;
   void *ip;
   RefInfo *refInfo;
   
   theObj = *theCell;
    
   if (inPIT((void *)theObj)) {
      /* The reference is in proper format already */
      ip = theObj;
      refInfo = PITlookup(ip);   
      refInfo -> objInTransit = NULL;
      referenceAlive(ip, refInfo);
      newAOAcell(theObj, theCell);
      return;
   } else {
      /* The persistent cell refers an object directly */
      u_long distanceToPart;
        
      realObj = getRealObject(theObj);
      distanceToPart = (unsigned long)theObj - (unsigned long)realObj;
        
      if (inToSpace(realObj)) {
         /* Special object in IOA */
         Claim(FALSE, "Special object in IOA");
      } else {
         Claim(inAOA(realObj), "Where is the object?");
         if (AOAISPERSISTENT(realObj)) {
            /* The referred object is in AOA and is persistent */
            objInfo = (ObjInfo *)GETOI(realObj -> GCAttr);
            if (AOAISDEAD(objInfo)) {
               Claim(refType == REFTYPE_DYNAMIC,
                     "handlePersistentCell: Illegal referencetype");   
               
               /* The referred object will be removed so we need to
                  unswizzle the reference to it. */

               if ((ip = lookupReferenceInfo(objInfo -> store,
                                             objInfo -> offset + distanceToPart)) == NULL) {
                  /* Create a new reference info object and refer it indirectly */
                  ip = referenceInfo(objInfo -> store,
                                     objInfo -> offset + distanceToPart);

               }
               *theCell = (Object *)ip;
               refInfo = PITlookup(ip);
               refInfo -> objInTransit = NULL;
               refInfo -> GCAttr = LISTEND; /* Marks the reference info object alive */
               newAOAcell(ip, theCell);
               
            } else {
               /* This reference is kept in absolute format since the
                * referred object is not removed from memory for some
                * reason.
                */
               Claim(AOAISALIVE(objInfo), "What is GC mark ?");
            }
         } else {
            /* Special object in AOA */
            ;
         }
      }
   }
}

static void updateObjectInStore(Object *theObj,
				unsigned long objSize,
				CAStorage *store, 
				unsigned long offset,
				unsigned short Flags)
{
   char *storeObj;

   Claim(theObj == getRealObject(theObj), "Exporting part object");
   
   storeObj = (char *)exportObject(theObj, store, objSize);
    
   if (Flags & FLAG_INSTORE) {
      Object *objcopy;
        
      objcopy = (Object*)((char*)theObj+objSize);
      /* We compare the objects disregarding the protypes and
         GCattribute values */
      if (memcmp(storeObj + SIZEOFPROTOANDGCATTRIBUTE, 
                 (char *)(objcopy) + SIZEOFPROTOANDGCATTRIBUTE, 
                 objSize - SIZEOFPROTOANDGCATTRIBUTE)) {
         SBOBJsave(store, storeObj, offset, objSize);
      }
   } else {
      SBOBJsave(store, storeObj, offset, objSize);
   }
}

static void visitOffsetsFuncP5_2(contentsBox *cb)
{
    ObjInfo *current;
    
    current = (ObjInfo *)(cb -> contents);

    if (current->flags & FLAG_SAVED) {
      return; /* Saved already, no point in doing it again so soon */
    }

    if (AllowLazyFetch) {
      if (AOAISDEAD(current)) {
	/* The object info object is dead */
	/* The persistent object will be removed */
	;
      } else if (AOAISALIVE(current)) {
	/* The object info object is alive, thus the object is alive */
	/* Handle references from live to dead persistent objects */
	scanObject(current -> theObj,
		   handlePersistentCell,
		   NULL,
		   TRUE);
      } else {
	Claim(FALSE, "What is the GC attr?");
      }
    }
    
    /* Whether the object is removed or not we update it in the store */
    updateObjectInStore(current -> theObj,
                        4*ObjectSize(current -> theObj),
                        current -> store,
                        current -> offset,
                        (u_short)(current -> flags));   
    current->flags |= FLAG_SAVED;
}

static void visitStoresFuncP5_2(contentsBox *cb)
{
    TIVisit((Trie *)(cb -> contents), visitOffsetsFuncP5_2);
}

void phaseFive()
{
   /* All objects in the ObjectTable who's object info object is DEAD
      are no longer referred from this process and can be updated in
      the store and released. */
  
   /* References from live persistent objects to DEAD persistent
    * objects must be unswizzled.
    */
  
   /* BETA issue: If an object is alive and kept in memory we cannot
      move its origin or any references from within the object to
      offline allocated objects, so we have to mark the origin alive
      as well as offline allocated objects referred from within the
      object. This is done first by the first 'TIVisit' below */
   
  if (loadedObjects) {
    TIVisit(loadedObjects, visitStoresFuncP5_1);
    
    /* All references from live persistent objects to dead ones are
     * swizzled. This is done by the next 'TIVisit' below */
    
    TIVisit(loadedObjects, visitStoresFuncP5_2);
    
    /* At this point all persistent objects in AOA whos object infor
     * object is marked as DEAD can be removed along with their object
     * info object. The GCAttribute of the object info object for live
     * persistent objects are reset to DEAD to prepare for the next
     * AOAGc.
     */
    
    /* mark dead objects dead and clean up tables */
    OTEndGC();
    RTEndGC();
    SOEndGC();
    SMGC();
  }
}

/**************************************************************************/
/* End GC:                                                                */
/**************************************************************************/
static void freeObjectCopy(Object *obj)
{
    Object *objcopy;
    unsigned long objSize;
    
    objSize = 4*ObjectSize(obj);
    objcopy = (Object *)((char *)(obj) + objSize);
    objcopy -> GCAttr = DEADOBJECT;
}

static void freeOffsetsFunc(u_long contents)
{
   ObjInfo *current;
    
   current = (ObjInfo *)contents;
   if (AOAISALIVE(current)) {
      if (!SBstat(current -> store)) {
         /* store is closed */
         /* Object is marked as alive, but not persistent */
         current -> theObj -> GCAttr = LISTEND;
         current -> GCAttr = DEADOBJECT;
         if (current -> flags & FLAG_INSTORE) {
            freeObjectCopy(current -> theObj);
         }
      } else {
         insertObjectAndParts(current -> store,
                              current -> offset,
                              current -> theObj,
                              current);
      }
   } else {
      current -> theObj -> GCAttr = DEADOBJECT;
      if (current -> flags & FLAG_INSTORE) {
         freeObjectCopy(current -> theObj);
      }
      current -> GCAttr = DEADOBJECT;
   }
   current -> flags &= (~FLAG_SAVED & FLAG_ALLMASK);
}

static void freeStoresFunc(u_long contents)
{
   TIFree((Trie *)contents, freeOffsetsFunc);
}

void OTEndGC(void)
{
   Trie *oldTable;

   /* Moves all object from the old table to a new one and frees the
    * old one.
    */
   if ((oldTable = loadedObjects)) {
     loadedObjects = TInit();
     
     TIFree(oldTable, freeStoresFunc);
   }
}

/**************************************************************************/
/* Close:                                                                 */
/**************************************************************************/
static CAStorage *storeToClose;

static void visitOffsetsFuncPC(contentsBox *cb)
{
   ObjInfo *current;
   
   current = (ObjInfo *)(cb -> contents);
   
   if (current -> store == storeToClose)
   {
      current -> theObj -> GCAttr = DEADOBJECT;
      current -> GCAttr = DEADOBJECT;
      if (current -> flags & FLAG_INSTORE) {
         freeObjectCopy(current -> theObj);
      }
   }
   else
   {
      /* Move object to new list */
      insertObjectAndParts(current -> store,
                           current -> offset,
                           current -> theObj,
                           current);
   }
}

static void visitStoresFuncPC(contentsBox *cb)
{
   TIVisit((Trie *)(cb -> contents), visitOffsetsFuncPC);
}

void closeStore(CAStorage *store)
{
   Trie *oldTable;
   
   if ((oldTable = loadedObjects)) {
      loadedObjects = TInit();
      
      storeToClose = store;
      
      TIVisit(loadedObjects, visitStoresFuncPC);
      TIFree(oldTable, freeStores);
   }
}

#endif /* PERSIST */
