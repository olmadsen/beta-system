#include "beta.h"
#include "referenceTable.h"
#include "objectTable.h"
#include "transitObjectTable.h"
#include "PException.h"
#include "PImport.h"
#include "unswizzle.h"
#include "PStore.h"

void pimport_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL VARIABLES */
static unsigned long storeOfEnclosingObject;
static Object *theRealObj;
static unsigned long offsetOfEnclosingObject;
static unsigned long inxOfEnclosingObject;

/* LOCAL FUNCTION DECLARATIONS */
static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE);
static Object *updateReferenceTable(unsigned long storeOfReferredObject, 
				    unsigned long offsetOfReferredObject, 
				    Object **theCell);
static void getOriginOfflineObject(Object **theCell);

/* FUNCTIONS */
static void getOriginOfflineObject(Object **theCell)
{
  Object *theObj;
  
  /* This function forces a load of all objects referred from the
     loaded object through a reference that is not ref none
     checked. These are origin objects and static part objects
     allocated offline. */

  theObj = *theCell;
  if (inPIT((void *)theObj)) {
    Object *absAddr;
    unsigned long _storeOfEnclosingObject;
    Object *_theRealObj;
    unsigned long _offsetOfEnclosingObject;
    unsigned long _inxOfEnclosingObject;
    
    _storeOfEnclosingObject = storeOfEnclosingObject;
    _theRealObj = theRealObj;
    _offsetOfEnclosingObject = offsetOfEnclosingObject;
    _inxOfEnclosingObject = inxOfEnclosingObject;
    
    absAddr = unswizzleReference((void *)theObj);
    
    storeOfEnclosingObject = _storeOfEnclosingObject;
    theRealObj = _theRealObj;
    offsetOfEnclosingObject = _offsetOfEnclosingObject;
    inxOfEnclosingObject = _inxOfEnclosingObject;
    
    /* Insert absolute reference in theCell */
    *theCell = absAddr;
    Claim(*theCell != NULL, "Assigning NULL");
  } 
}

static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE)
{
  unsigned long offsetOfReferredObject;
  
  offsetOfReferredObject = (unsigned long)*theCell;
  *theCell = importReference(storeOfEnclosingObject, 
			     offsetOfReferredObject, 
			     theCell);
  
  Claim(*theCell != NULL, "Assigning NULL");
  
  /* theCell is in AOA. The reference returned by 'importReference'
     may be in IOA if the rebinder is called */
  if (isSpecialReference(offsetOfReferredObject)) {
    if (inIOA(*theCell)) {
      AOAtoIOAInsert( theCell);
    }
  } else {
    /* This is not a special reference. If refType is ORIGIN or
       OFFLINE we must fetch the tartget */
    
    if (refType != REFTYPE_DYNAMIC) {
      getOriginOfflineObject(theCell);
    }
  }
}

Object *importReference(unsigned long storeOfReferredObject, 
			unsigned long offsetOfReferredObject, 
			Object **theCell)
{
  StoreProxy *sp;
  unsigned long inxOT;
  unsigned short OTGCAttr;
  unsigned long OTstore;
  unsigned long OToffset;
  Object *theRealObj;
  
  if (!isCrossStoreReference(storeOfReferredObject, offsetOfReferredObject)) {
    if (!isSpecialReference(offsetOfReferredObject)) {
      if ((inxOT = indexLookupOT(storeOfReferredObject, 
				 offsetOfReferredObject)) != -1) {
	/* The object is in memory allready */
	
	objectLookup(inxOT,
		     &OTGCAttr,
		     &OTstore,
		     &OToffset,
		     &theRealObj);
	
	Claim(OTGCAttr == ENTRYALIVE, "Lookup on dead object");
	Claim(storeOfReferredObject == OTstore, "Table mismatch");
	Claim((offsetOfReferredObject >= OToffset) && (offsetOfReferredObject < OToffset + 4*ObjectSize(theRealObj)),
	      "Table mismatch");
	
	return (Object *)((unsigned long)theRealObj + (offsetOfReferredObject - OToffset));
      } else {
	/* The object is not in memory allready */
	return updateReferenceTable(storeOfReferredObject, 
				    offsetOfReferredObject, 
				    theCell);
      }
    } else {
      return handleSpecialReference(offsetOfReferredObject);
    }
  } else {
    /* The referred object is in reality a proxy object. We will now
       lookup the proxy object and retreive the actual store and ofset
       of the referred object. */
    
    sp = lookupStoreProxy(storeOfReferredObject, offsetOfReferredObject);
    return importReference(sp -> storeID, sp -> offset, theCell);
  }
}

static Object *updateReferenceTable(unsigned long storeOfReferredObject, 
				    unsigned long offsetOfReferredObject, 
				    Object **theCell)
{
  unsigned long inxRT;
  
  if ((inxRT = indexLookupRT(storeOfReferredObject, 
			     offsetOfReferredObject)) == -1) { 
    /* There is no entry for this object in the reference table */
    inxRT = insertReference(ENTRYALIVE,
			    storeOfReferredObject,
			    offsetOfReferredObject);
  }
  if (theCell) {
    newAOAclient(inxRT, theCell);
  }
  return (Object *)newPUID(inxRT);
} 

static void updateTransitObjectTable(Object *theObj)
{
  unsigned long distanceToPart;

  /* We are importing an object and must insert a notification in the
     transit objects table that this particular object has been
     imported. This goes for the object itself as well as for any
     static part objects of the object. This function is called by
     'scanObject' for the object itself and all its static parts. */
  
  distanceToPart = (unsigned long)theObj - (unsigned long)theRealObj;
  
  insertObjectInTransit(storeOfEnclosingObject,
			offsetOfEnclosingObject + distanceToPart,
			theObj);

  if (distanceToPart == 0) {
    if (inxOfEnclosingObject != -1) {
      theObj -> GCAttr = inxOfEnclosingObject + 1;
    } else {
      theObj -> GCAttr = 0;
    }
  }
}

void importStoreObject(Object *theObj, 
		       unsigned long store, 
		       unsigned long offset, 
		       unsigned long inx)
{
  /* 'theObj' 

     Is an object in store format. This means that all references
     within 'theObj' to objects in the same store as 'theObj' are
     implemented as offsets. References to objects in other stores can
     be identified as such and are implemented as offsets to a proxy
     object. The tast of 'importStoreObject' is to translate all
     references in 'theObj' to in memory format.
     
     'store' 

     Is the context local store id of the store holding 'theObj'.

     'offset'

     Is the offset of 'theObj' in the store.

     'inx'

     Is passed to enable some optimization that is so clever that I
     cannot remember what it is about. It has got nothing to do with
     the basic actions of importing an object.
  */
  
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  Claim(inAOA(theObj), "Where is theObj?");
  
  theRealObj = theObj;
  /* Scan references, and turn into PUID's */
  storeOfEnclosingObject = store;
  offsetOfEnclosingObject = offset;
  inxOfEnclosingObject = inx;

  scanObject(theObj,
	     storeReferenceToProcessReference,
	     updateTransitObjectTable,
	     TRUE);
}

#endif /* PERSIST */
