#include "beta.h"
#include "PStore.h"
#include "PException.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "specialObjectsTable.h"
#include "PStore.h"

void pexport_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL FUNCTION DECLARATIONS */
static void processReferenceToStoreReference(REFERENCEACTIONARGSTYPE);

/* LOCAL VARIABLES */
static unsigned long currentStore;
static Object *currentObj;

/* */
static void processReferenceToStoreReference(REFERENCEACTIONARGSTYPE)
{
  char GCAttr;
  unsigned long store;
  unsigned long offset, distanceToPart;
  Object *theObj, *realObj;
  void *puid;  /* puid of referred object */
  Array *IOAclients;
  Array *AOAclients;
  
  theObj = *theCell;
  if (inPIT(theObj)) {
    puid = (void *)theObj;
    referenceLookup(getPUID(puid), 
		    &GCAttr, 
		    &store, 
		    &offset,
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
		   &store, 
		   &offset,
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

  if (compareStoreID(store, currentStore)) {
    /* the reference is simply replaced by the offset of the referred object */
    *theCell = (Object *)(offset + distanceToPart);
    Claim(*theCell != NULL, "Assigning NULL to cell");

  } else {
    /* We create a proxy for this object */
    setCurrentPStore(currentStore);
    
    *theCell = (Object *)newPProxy(store, offset + distanceToPart);
    Claim(*theCell != NULL, "Assigning NULL");
    
#ifdef RTDEBUG
    if (!inPIT(theObj)) {
      INFO_PERSISTENCE(fprintf(output, "[ CrossReference: (%s, %d) -> (%s, %d, %d) ]\n",
			       ProtoTypeName(GETPROTO(currentObj)),
			       (int)(currentStore),
			       ProtoTypeName(GETPROTO(theObj)),
			       (int)(store),
			       (int)(offset + distanceToPart)));
    } else {
      INFO_PERSISTENCE(fprintf(output, "[ CrossReference: (%s, %d) -> (%s, %d, %d) ]\n",
			       ProtoTypeName(GETPROTO(currentObj)),
			       (int)(currentStore),
			       "Unknown",
			       (int)(store),
			       (int)(offset + distanceToPart)));
      
    }
#endif /* RTDEBUG */
    Claim((unsigned long)*theCell != 0, "??");
  }
}

extern void checkOrigins(Object *theObj, void *generic);

/* Exports the object to 'store' */
void exportObject(Object *theObj, unsigned long store)
{
  currentStore = store;
  currentObj = theObj;
  
  scanObject(theObj,
	     processReferenceToStoreReference,
	     NULL,
	     TRUE);
}


#endif /* PERSIST */
