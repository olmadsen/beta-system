#include "beta.h"
#include "PStore.h"
#include "PException.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "crossStoreTable.h"

void pexport_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL FUNCTION DECLARATIONS */
static void processReferenceToStoreReference(REFERENCEACTIONARGSTYPE);

/* LOCAL VARIABLES */
static StoreID currentStore;
static Object *currentObj;

/* */
static void processReferenceToStoreReference(REFERENCEACTIONARGSTYPE)
{
  char GCAttr;
  StoreID store;
  u_long offset, distanceToPart;
  Object *theObj, *realObj;
  void *puid;  /* puid of referred object */
  
  theObj = *theCell;
  if (inPIT(theObj)) {
    puid = (void *)theObj;
    referenceLookup(getPUID(puid), 
		    &GCAttr, 
		    &store, 
		    &offset);
    
    Claim(compareStoreID(store, currentStore), "??");
    
    *theCell = (Object *)offset;
  } else {
    Object *dummy;
    
    realObj = getRealObject(theObj);
    distanceToPart = (u_long)theObj - (u_long)realObj;
    
    Claim(inAOA(realObj), "Where is theObj ?");
    Claim(AOAISPERSISTENT(realObj), "Reference from persistent to non-persistent obj?");
    
    puid = (void *)(realObj -> GCAttr);
    objectLookup(getPUID(puid), 
		 &GCAttr, 
		 &store, 
		 &offset,
		 &dummy);

    Claim(dummy == realObj, "Table mismatch ?");
    
    if (compareStoreID(store, currentStore)) {
      /* the reference is simply replaced by the offset of the referred object */
      *theCell = (Object *)(offset + distanceToPart);
    } else {
      /* We create a proxy for this object */
      setCurrentCrossStoreTable(currentStore);
      
      Claim(compareStoreID(getCurrentCrossStoreTable(), currentStore), "??");
      
      *theCell = (Object *)newStoreProxy(store, offset + distanceToPart);

#ifdef RTDEBUG
      INFO_PERSISTENCE(fprintf(output, "[ CrossReference: (%s, %d) -> (%s, %d, %d) ]\n",
			       ProtoTypeName(GETPROTO(currentObj)),
			       (int)(currentStore),
			       ProtoTypeName(GETPROTO(theObj)),
			       (int)(store),
			       (int)(offset + distanceToPart)));
#endif /* RTDEBUG */
      Claim((u_long)*theCell != ILLEGALSTOREID, "??");
    }
  }
}

/* Exports the object to 'store' */
void exportObject(Object *theObj, StoreID store)
{
  currentStore = store;
  currentObj = theObj;

  scanObject(theObj,
	     processReferenceToStoreReference,
	     TRUE);

}


#endif /* PERSIST */
