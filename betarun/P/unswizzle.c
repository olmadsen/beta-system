#include "beta.h"
#include "referenceTable.h"
#include "objectTable.h"
#include "PException.h"
#include "crossStoreTable.h"
#include "PImport.h"

/* */
void unswizzle_dummy()
{
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */
static Object *lookUpReferenceEntry(StoreID store, u_long offset);
static void originReferenceAction(Object **theCell);
static void getOriginChain(Object *theObj);

/* FUNCTIONS */

/* Given the indirect proxy 'ip', it is checked if the object is in
   memory. If so the reference to the object is returned. If not the
   object is retrieved. */

Object *unswizzleReference(void *ip)
{
  char GCAttr;
  StoreID store;
  u_long offset;
  u_long inx;
  
  inx = getPUID(ip);
  referenceLookup(inx,
		  &GCAttr,
		  &store,
		  &offset);
  
  Claim(GCAttr == ENTRYALIVE, "Reference to dead entry");
  
  return lookUpReferenceEntry(store, offset);
}

static Object *lookUpReferenceEntry(StoreID store, u_long offset) 
{
  u_long distanceToPart;
  u_long inx;
  Object *theStoreObj, *theRealStoreObj, *theRealObj;
  if (!isCrossStoreReference(offset)) {
    /* Check if this object has been retrieved allready */
    if ((inx = indexLookupOT(store, offset)) != -1) {
      char _GCAttr;
      StoreID _store;
      u_long _offset;
      
      objectLookup(inx,
		   &_GCAttr,
		   &_store,
		   &_offset,
		   &theRealObj);
      
      Claim(_GCAttr == ENTRYALIVE, "Lookup on dead object");
      Claim(store == _store, "Table mismatch");
      Claim((offset >= _offset) && (offset < _offset + 4*ObjectSize(theRealObj)),
	    "Table mismatch");
      
      distanceToPart = offset - _offset;
      
    } else {
      setCurrentObjectStore(store);
      theStoreObj = lookupStoreObject(store, offset);
      
      Claim(theStoreObj != NULL, "Could not look up store object");
      
      theRealStoreObj = getRealObject(theStoreObj);
      distanceToPart = (u_long)theStoreObj - (u_long)theRealStoreObj;
      /* The object is not in memory */
      theRealObj = AOAallocate(4*ObjectSize(theRealStoreObj));
      memcpy(theRealObj, theRealStoreObj, 4*ObjectSize(theRealStoreObj));
      importStoreObject(theRealObj, store);
      inx = insertObject(ENTRYALIVE,
			 store,
			 offset - distanceToPart,
			 theRealObj);
      theRealObj -> GCAttr = PERSISTENTMARK(inx);

#ifdef RTDEBUG
      INFO_PERSISTENCE(fprintf(output, "[ Importing object (%d, %d) %s]\n",
			       (int)store,
			       (int)offset,
			       ProtoTypeName(GETPROTO(theRealObj))));
#endif /* RTDEBUG */
      
      /* get the origin chain of the object */
      objectAction = getOriginChain;
      scanObject(theRealObj,
		 NULL,
		 TRUE);
      objectAction = NULL;
    }
    Claim(inAOA(theRealObj),"Where is theRealObj ?");
    return (Object *)((u_long)theRealObj + distanceToPart);
  } else {
    StoreProxy *sp;
    setCurrentCrossStoreTable(store);
    sp = lookupStoreProxy(offset);
    
    Claim(sp != ILLEGALSTOREPROXY, "Could not lookup store proxy");
    
    return lookUpReferenceEntry(sp -> store, sp -> offset);
  }
}

static void originReferenceAction(Object **theCell)
{
  Object *theOrigin;
  
  if ((theOrigin = *theCell)) {
    Object *absAddr;
    
    if (inPIT((void *)theOrigin)) {
      absAddr = unswizzleReference((void *)theOrigin);
      /* Insert absolute reference in origin */
      *theCell = absAddr;
    }
  } 
}

static void getOriginChain(Object *theObj)
{
  scanOrigins(theObj, originReferenceAction);
}

#endif /* PERSIST */
