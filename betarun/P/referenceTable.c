#include "beta.h"

#ifdef PERSIST
#include "referenceTable.h"
#include "PException.h"
#include "objectTable.h"
#include "sequenceTable.h"
#include "trie.h"
#include "proto.h"
#include "transitObjectTable.h"
#include "storageblock.h"
#include "pit.h"

/* LOCAL TYPES */

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the ReferenceTable */

/* LOCAL MACROS */

/* LOCAL VARIABLES */
static Trie *loadedObjectsST;

/* LOCAL FUNCTION DECLARATIONS */
static void Arealloc(Array *array);

/* FUNCTIONS */
void initReferenceTable(void)
{
   /* Allocate indirection table */
   PITalloc();
   
#ifdef UNIX
   initProxyTrapHandler();
#endif
   loadedObjectsST = TInit();
   initProtoHandling();
}

/* 'referenceInfo' is used to create new reference info objects. It is
 * called when ever the need for a new indirect reference arises. This
 * happens in two cases. The first case is when an object is
 * imported. All persistent objects referred from the imported object
 * are referred through proxies. The second case is when a persistent
 * object is removed, then all references to the removed object are
 * turned into indirect references.
 *
 * The function returns an indirect reference.
 *
 */
void *referenceInfo(CAStorage *store, u_long offset)
{
   RefInfo *refInfo;
   void *ip;
   
   refInfo = (RefInfo *)AOAallocate(sizeof(struct _RefInfo), TRUE);
   SETPROTO(((Object *)refInfo), ((long)RefInfoPTValue));
   
   refInfo -> store = store;
   refInfo -> offset = offset;
   refInfo -> AOAcells = newArray();
   refInfo -> objInTransit = NULL;
   
   /* Insert reference info in map */
   ip = PITinsert(refInfo);

   /* Insert (store, offset) in loadedObjectsST */
   insertStoreOffset(store, offset, (u_long)ip, &loadedObjectsST);
   
   /* Insert reference info in map */
   return ip;
}

/* 'lookupReferenceInfo' returns an indirect reference.
 */
void *lookupReferenceInfo(CAStorage *store, u_long offset)
{
   Trie *stores;
   
   /* Check if store is member of 'loadedObjects' */
   if ((stores = (Trie *)TILookup((u_long)store, loadedObjectsST))) {
      void *ip;
      if ((ip = (void *)TILookup(offset + 1, stores))) {
         return ip;
      }
   }
   return NULL;
}

void newAOAcell(void *ip, Object **theCell)
{
   RefInfo *refInfo;
   
   refInfo = PITlookup(ip);   
   
   Aappend(refInfo -> AOAcells, (unsigned long)theCell);
}

/* Called from IOAGc and AOAGc */
void referenceCheck(Object **theCell)
{
   RefInfo *refInfo;
   void *ip;

   ip = *theCell;
   refInfo = PITlookup(ip);   
   
   if (refInfo -> objInTransit) {
      *theCell = refInfo -> objInTransit;
      objectAlive(getRealObject(*theCell));
      if (refInfo -> AOAcells -> top) {
         redirectAOACells(refInfo -> AOAcells, ip, refInfo -> objInTransit);
         refInfo -> AOAcells -> top = 0;
      }

   } else {
      referenceAlive(ip, refInfo);
      if (inAOA(theCell)) {
         newAOAcell(*theCell, theCell);
      }
   }
}

void referenceAlive(void *ip, RefInfo *refInfo)
{     
   if (refInfo -> GCAttr == DEADOBJECT) {
      /* This reference info object is marked alive and
       * reinserted into the set of live indirect references.
       */
      refInfo -> GCAttr = LISTEND; /* Marks the reference info as alive */
      
      /* Reinsert the indirect reference */
      insertStoreOffset(refInfo -> store,
                        refInfo -> offset,
                        (u_long)ip,
                        &loadedObjectsST);     
   } else {
      /* The reference info object has already been reinserted and
       * marked alive */
      ;
   }
}

/* 'freeLoadedObjectsOF' and 'RTstartGC' are used in conjunction.
 */
static void freeReferenceObject(unsigned long contents)
{
   RefInfo *refInfo;
   void *ip;

   ip = (void *)contents;
   refInfo = PITlookup(ip);   
   
   refInfo -> AOAcells -> top = 0;
}
   
static void freeReferenceObjects(unsigned long contents)
{
   TIFree((Trie *)contents, freeReferenceObject);
}

void RTStartGC(void)
{
   /* Free the current 'loadedObjectsST' */
  if (loadedObjectsST) {
    TIFree(loadedObjectsST, freeReferenceObjects);
    loadedObjectsST = TInit();
  }
}

void RTEndGC(void)
{  
   ;
}

/* Arrays */
Array *newArray(void)
{
  return (Array *)calloc(1, sizeof(struct Array));
}

static void Arealloc(Array *array)
{
  unsigned long *new;
  unsigned short newMax;
  
  newMax = 2*array -> max + 1;
  new = (unsigned long *)malloc(sizeof(unsigned long)*newMax);
  if (array -> theCells) {
    memcpy(new, array -> theCells, array -> max * sizeof(unsigned long));
    free(array -> theCells);
    array -> theCells = 0;
  }
  array -> theCells = new;
  array -> max = newMax;
}

void Aappend(Array *array, unsigned long theCell)
{
  if (array -> top < array -> max) {
    array -> theCells[array -> top] = theCell;
    array -> top = array -> top + 1;
  } else {
    Arealloc(array);
    Aappend(array, theCell);
  }
}
#endif /* PERSIST */

#if 0 /* was: RUN  now in CHKRA.run */
void CheckForNewAOAclient(Object **theCell)
{
#ifdef PERSIST
  if (inPIT((void *)*theCell)) {
    newAOAcell(*theCell, theCell);
  }
#endif /* PERSIST */
}
#endif /* RUN */

