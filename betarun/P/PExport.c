#include "beta.h"
#include "PStore.h"
#include "PException.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "specialObjectsTable.h"
#include "PStore.h"

#ifdef PERSIST

/* LOCAL FUNCTION DECLARATIONS */
static void processReferenceToStoreReference(REFERENCEACTIONARGSTYPE);

/* LOCAL VARIABLES */
static unsigned long storeOfEnclosingObject;
static Object *enclosingObject;

/* */
static void processReferenceToStoreReference(REFERENCEACTIONARGSTYPE)
{
  unsigned short GCAttr;
  unsigned long storeOfReferredObject;
  unsigned long offsetOfReferredObject, distanceToPart;
  Object *theObj, *realObj;
  void *puid;  /* puid of referred object */
  Array *IOAclients;
  Array *AOAclients;
  
  theObj = *theCell;
  if (inPIT(theObj)) {
    puid = (void *)theObj;
    referenceLookup(getPUID(puid), 
		    &GCAttr, 
		    &storeOfReferredObject, 
		    &offsetOfReferredObject,
		    &IOAclients,
		    &AOAclients);
    
    distanceToPart = 0;
    
  } else {
    Object *dummy;
    
    realObj = getRealObject(theObj);
    distanceToPart = (unsigned long)theObj - (unsigned long)realObj;
    
    if (AOAISPERSISTENT(realObj)) {
      Claim(inAOA(realObj), "Where is theObj ?");
      
      puid = (void *)(realObj -> GCAttr);
      objectLookup(getPUID(puid), 
		   &GCAttr, 
		   &storeOfReferredObject, 
		   &offsetOfReferredObject,
		   &dummy);
      
      Claim(dummy == realObj, "Table mismatch ?");
    } else {
      unsigned long tag;
      
      tag = getTag(realObj);
      
      Claim(tag < 0xFF, "Tag not found or tag too big");
      Claim(distanceToPart < 0xFFFF, "distanceToPart too big");
      
      *theCell = (Object *)((tag << 24 ) | (distanceToPart << 8) | SPECIALTYPE);
      Claim(*theCell != NULL, "Assigning NULL");
      return;
    }
  }

  if (storeOfReferredObject == storeOfEnclosingObject) {
    /* the reference is simply replaced by the offset of the referred object */
    *theCell = (Object *)(offsetOfReferredObject + distanceToPart);
    Claim(*theCell != NULL, "Assigning NULL to cell");
    
  } else {
    /* We create a proxy for this object */
    *theCell = (Object *)newPProxy(storeOfEnclosingObject,
				   storeOfReferredObject,
				   offsetOfReferredObject + distanceToPart);
    Claim(*theCell != NULL, "Assigning NULL");
    
#ifdef RTDEBUG
    if (!inPIT(theObj)) {
      INFO_PERSISTENCE(fprintf(output, "[ CrossReference: (%s, %d) -> (%s, %d, %d) ]\n",
			       ProtoTypeName(GETPROTO(enclosingObject)),
			       (int)(storeOfEnclosingObject),
			       ProtoTypeName(GETPROTO(theObj)),
			       (int)(storeOfReferredObject),
			       (int)(offsetOfReferredObject + distanceToPart)));
    } else {
      INFO_PERSISTENCE(fprintf(output, "[ CrossReference: (%s, %d) -> (%s, %d, %d) ]\n",
			       ProtoTypeName(GETPROTO(enclosingObject)),
			       (int)(storeOfEnclosingObject),
			       "Unknown",
			       (int)(storeOfReferredObject),
			       (int)(offsetOfReferredObject + distanceToPart)));
      
    }
#endif /* RTDEBUG */
  }
}

extern void checkOrigins(Object *theObj, void *generic);

/* Exports the object to 'store' */
void exportObject(Object *theObj, unsigned long store)
{
  storeOfEnclosingObject = store;
  enclosingObject = theObj;
  
  scanObject(theObj,
	     processReferenceToStoreReference,
	     NULL,
	     TRUE);
}


#endif /* PERSIST */
