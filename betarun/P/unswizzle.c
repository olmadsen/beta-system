#include "beta.h"
#include "referenceTable.h"
#include "objectTable.h"
#include "PException.h"
#include "PImport.h"
#include "proto.h"
#include "unswizzle.h"
#include "transitObjectTable.h"
#include "PStore.h"

/* */
void unswizzle_dummy()
{
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL VARIABLES */
static unsigned long lookups = 0;

/* LOCAL FUNCTION DECLARATIONS */
static Object *loadObject(unsigned long store, u_long offset, unsigned long inx);

/* FUNCTIONS */

/* Given the indirect proxy 'ip', it is checked if the object is in
   memory. If so the reference to the object is returned. If not the
   object is retrieved. */
void showUnswizzleStatistics(void)
{
  INFO_PERSISTENCE(fprintf(output, "[Unswizzle: lookups = 0x%X]\n", (int)lookups));
}

Object *unswizzleReference(void *ip)
{
  char GCAttr;
  unsigned long store;
  unsigned long offset;
  unsigned long inx;
  Array *IOAclients;
  Array *AOAclients;
  Object *theObj;
  
  inx = getPUID(ip);
  
  if ((theObj = getObjInTransit(inx))) {
    return theObj;
  } else {
    referenceLookup(inx,
		    &GCAttr,
		    &store,
		    &offset,
		    &IOAclients,
		    &AOAclients);
    
    Claim(GCAttr == ENTRYALIVE, "Reference to dead entry");
    Claim(!isCrossStoreReference(offset), "Unhandled crossStoreReference");
    
    theObj = lookUpReferenceEntry(store, offset, inx);
    setObjInTransit(inx, theObj);
    return theObj;
  }
}

Object *lookUpReferenceEntry(unsigned long store, unsigned long offset, unsigned long inx)
{
  Object *theObj;
  
  INFO_PERSISTENCE(lookups++);
  
  if ((theObj = indexLookupTOT(store, offset)) != NULL) {
    return theObj;
  } else {
    return loadObject(store, offset, inx);
  }
}

static Object *loadObject(unsigned long store, unsigned long offset, unsigned long inx)
{
  unsigned long size, distanceToPart;
  Object *theStoreObj, *theRealStoreObj, *theRealObj;

  setCurrentPStore(store);
  theStoreObj = lookupStoreObject(store, offset);
  
  Claim(theStoreObj != NULL, "Could not look up store object");
  
  theRealStoreObj = getRealObject(theStoreObj);
  distanceToPart = (unsigned long)theStoreObj - (unsigned long)theRealStoreObj;
  
  if (distanceToPart) {
    Object *theRealObj;
    
    theRealObj = lookUpReferenceEntry(store, offset - distanceToPart, -1);
    return (Object *)((unsigned long)theRealObj + distanceToPart);
  } else {
    size = 4*StoreObjectSize(theRealStoreObj);
    theRealObj = AOAallocate(2*size);
    if (AOANeedCompaction) {
      fprintf(output, "Requesting GC at next allocation\n");
      /* Request GC at next IOAAllocation */
#if defined(NEWRUN) || defined(sparc)
      IOATopOff = (char *)IOALimit  - (char *) IOA;
#else
      IOATop = IOALimit;
#endif
    }
    memcpy(theRealObj, theRealStoreObj, size);
    importProtoTypes(theRealObj);
    importStoreObject(theRealObj, store, offset, inx);
    memcpy((char*)theRealObj+size, theRealObj, size);
    ((Object*)((char*)theRealObj+size))->GCAttr = newPUID(0);
    Claim(ObjectSize(((Object*)((char*)theRealObj+size)))
	  == ObjectSize(theRealObj), "Claim");
#ifdef RTDEBUG
    INFO_PERSISTENCE(fprintf(output, "[ Importing object (%d, %d) %s]\n",
			     (int)store,
			     (int)offset,
			     ProtoTypeName(GETPROTO(theRealObj))));
#endif /* RTDEBUG */
    return theRealObj;
  }
}

/* If the implementation of the UNKNOWNTAG in virtualobjectstore.bet is
   changed then the define below should be changed accordingly.  */
#define UNKNOWNTAG 0

void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long objectTag, unsigned long typeTag))
{
  callRebinderC = rebinderFunc;
}

Object *handleSpecialReference(unsigned long specRef)
{
  unsigned long tag, distanceToPart;
  Object *target;
  
  Claim(isSpecialReference(specRef), "handleSpecialReference: Is not special reference");
  
  tag = specRef >> 24;
  distanceToPart = (specRef & 0x00FFFF00) >> 8;
  
  /* Below we reenter BETA code while we are in the midst of loading
     an object. While in BETA code additional object loads might be
     issued, and GCs, both IOAGC amd AOAGC, might occur. While it
     should be possible to support all these events only an IOAGC is
     legal at this point in time. */

  BETAREENTERED = TRUE;
  target = callRebinderC(tag, UNKNOWNTAG);
  BETAREENTERED = FALSE;
  
  target = (Object *)((unsigned long)getRealObject(target) + distanceToPart);

  return target;
}

#endif /* PERSIST */
