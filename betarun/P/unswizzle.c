#include "beta.h"
#include "referenceTable.h"
#include "objectTable.h"
#include "PException.h"
#include "PImport.h"
#include "proto.h"
#include "unswizzle.h"
#include "transitObjectTable.h"
#include "PStore.h"
#include "crossStoreReferences.h"

/* */
void unswizzle_dummy()
{
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST
#define MAXPERSISTENTBYTES 2048 * Kb

/* LOCAL VARIABLES */
static unsigned long loadedBytes = 0;
static unsigned long forceAOACompaction = 0;

/* IMPORTS */
extern PStoreHeader *currentPStore;

/* LOCAL FUNCTION DECLARATIONS */
static Object *loadObject(unsigned long store, u_long offset, unsigned long inx);

/* FUNCTIONS */

/* Given the indirect proxy 'ip', it is checked if the object is in
   memory. If so the reference to the object is returned. If not the
   object is retrieved. */
void showUnswizzleStatistics(void)
{
  ;
}

Object *unswizzleReference(void *ip)
{
  unsigned short GCAttr;
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
    
    if ((theObj = lookUpReferenceEntry(store, offset, inx))) {
      setObjInTransit(inx, theObj);
    }
    /* 'lookUpReferenceEntry' might return NULL (currently only if the
       store from which we are trying to load is closed). This should
       be handled by the proxy traphandler as a fatal error. */
    return theObj;
  }
}

Object *lookUpReferenceEntry(unsigned long store, unsigned long offset, unsigned long inx)
{
  Object *theObj;
  
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

  if (storeIsOpen(store)) {
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
      loadedBytes += 2*size;
      if (loadedBytes > MAXPERSISTENTBYTES) {
	loadedBytes = 0;
	forceAOACompaction = TRUE;
	DEBUG_CODE(fprintf(output, "Max persistent bytes exceeded\n"))
	  }
      if (forceAOACompaction) {
	DEBUG_CODE(fprintf(output, "Requesting GC at next allocation\n"));
	/* Request GC at next IOAAllocation */
	AOANeedCompaction = TRUE;
	forceAOACompaction = FALSE;
#if defined(NEWRUN) || defined(sparc)
	IOATopOff = (char *)IOALimit  - (char *) IOA;
#else
	IOATop = IOALimit;
#endif
      }
      memcpy(theRealObj, theRealStoreObj, size);
      importProtoTypes(theRealObj);
      
      /* A copy of the object is save after the object it self. This
	 copy is still in store format apart from the prototypes which
	 are in in memory format. */
      memcpy((char*)theRealObj+size, theRealObj, size);
      /* The copy is marked as a persistent object. This marking is only
	 used to indicate to the GC'er that it should not free the space
	 taken up by the object. */
      ((Object*)((char*)theRealObj+size))->GCAttr = (long)newPUID(0);
      
      /* The real object is imported */
      importStoreObject(theRealObj, store, offset, inx);
      
      Claim(ObjectSize(((Object*)((char*)theRealObj+size)))
	    == ObjectSize(theRealObj), "Claim");
      INFO_PERSISTENCE(objectsLoaded++);
      return theRealObj;
    }
  } else {
    return NULL;
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
