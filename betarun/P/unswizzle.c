#include "beta.h"
#include "referenceTable.h"
#include "objectTable.h"
#include "PException.h"
#include "crossStoreTable.h"
#include "PImport.h"
#include "proto.h"
#include "unswizzle.h"
#include "transitObjectTable.h"

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
static void originReferenceAction(Object **theCell);
static void getOriginChain(Object *theObj);
static Object *loadObject(BlockID store, u_long offset);

/* FUNCTIONS */

/* Given the indirect proxy 'ip', it is checked if the object is in
   memory. If so the reference to the object is returned. If not the
   object is retrieved. */

Object *unswizzleReference(void *ip)
{
  char GCAttr;
  BlockID store;
  u_long offset;
  u_long inx;
  Array *IOAclients;
  Array *AOAclients;
  
  inx = getPUID(ip);
  referenceLookup(inx,
		  &GCAttr,
		  &store,
		  &offset,
		  &IOAclients,
		  &AOAclients);
  
  Claim(GCAttr == ENTRYALIVE, "Reference to dead entry");
  Claim(!isCrossStoreReference(offset), "Unhandled crossStoreReference");
  
  return lookUpReferenceEntry(store, offset);
}

Object *lookUpReferenceEntry(BlockID store, u_long offset)
{
  Object *theObj;
  
  if ((theObj = indexLookupTOT(store, offset)) != NULL) {
    return theObj;
  } else {
    return loadObject(store, offset);
  }
}

static Object *loadObject(BlockID store, u_long offset)
{
  u_long size, distanceToPart;
  Object *theStoreObj, *theRealStoreObj, *theRealObj;

  setCurrentObjectStore(store);
  theStoreObj = lookupStoreObject(store, offset);
  
  Claim(theStoreObj != NULL, "Could not look up store object");
  
  theRealStoreObj = getRealObject(theStoreObj);
  distanceToPart = (u_long)theStoreObj - (u_long)theRealStoreObj;
  
  if (distanceToPart) {
    Object *theRealObj;
    
    theRealObj = lookUpReferenceEntry(store, offset - distanceToPart);
    return (Object *)((u_long)theRealObj + distanceToPart);
  } else {
    size = 4*StoreObjectSize(theRealStoreObj);
    theRealObj = AOAallocate(size);
    memcpy(theRealObj, theRealStoreObj, size);
    importProtoTypes(theRealObj);
    importStoreObject(theRealObj, store, offset);
#ifdef RTDEBUG
    INFO_PERSISTENCE(fprintf(output, "[ Importing object (%d, %d) %s]\n",
			     (int)store,
			     (int)offset,
			     ProtoTypeName(GETPROTO(theRealObj))));
#endif /* RTDEBUG */
    /* get the origin chain of the object */
    { 
      void (*temp)(Object *theObj);
      temp = objectAction; 
      objectAction = getOriginChain;
      scanObject(theRealObj,
		 NULL,
		 TRUE);
      objectAction = temp;
    }
    return theRealObj;
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

void registerRebinder(Object *theRebinder)
{
  rebinderItem = (long *)theRebinder;
}

#endif /* PERSIST */
