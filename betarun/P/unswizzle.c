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

/* If the implementation of the UNKNOWNTAG in virtualobjectstore.bet is
   changed then the define below should be changed accordingly.  */
#define UNKNOWNTAG 0

void registerRebinderFunc(Object *(*rebinderFunc)(u_long objectTag, u_long typeTag))
{
  callRebinderC = rebinderFunc;
}

Object *handleSpecialReference(u_long specRef)
{
  u_long tag, distanceToPart;
  Object *target;
  void (*temp)(Object *theObj);
  
  Claim(isSpecialReference(specRef), "handleSpecialReference: Is not special reference");
  
  tag = specRef >> 24;
  distanceToPart = (specRef & 0x00FFFF00) >> 8;
  
  /* Below we reenter BETA code while we are in the midst of loading
     an object. While in BETA code additional object loads might be
     issued, and GCs, both IOAGC amd AOAGC, might occur. While it
     should be possible to support all these events only an IOAGC is
     legal at this point in time. */

  temp = objectAction;
  objectAction = NULL;
  BETAREENTERED = TRUE;
  target = callRebinderC(tag, UNKNOWNTAG);
  BETAREENTERED = FALSE;
  objectAction = temp;
  
  target = (Object *)((u_long)getRealObject(target) + distanceToPart);

  return target;
}

#endif /* PERSIST */
