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
static unsigned long currentStore;
static Object *theRealObj;
static unsigned long currentOffset;
static unsigned long currentInx;

/* LOCAL FUNCTION DECLARATIONS */
static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE);
static Object *importReference(unsigned long store, unsigned long offset, Object **theCell);
static Object *updateReferenceTable(unsigned long store, unsigned long offset, Object **theCell);
static void getOriginOfflineObject(Object **theCell);

/* FUNCTIONS */
static void getOriginOfflineObject(Object **theCell)
{
  Object *theObj;
  
  theObj = *theCell;
  if (inPIT((void *)theObj)) {
    Object *absAddr;
    unsigned long _currentStore;
    Object *_theRealObj;
    unsigned long _currentOffset;
    unsigned long _currentInx;
    
    _currentStore = currentStore;
    _theRealObj = theRealObj;
    _currentOffset = currentOffset;
    _currentInx = currentInx;
    
    absAddr = unswizzleReference((void *)theObj);
    
    currentStore = _currentStore;
    theRealObj = _theRealObj;
    currentOffset = _currentOffset;
    currentInx = _currentInx;
    
    /* Insert absolute reference in theCell */
    *theCell = absAddr;
    Claim(*theCell != NULL, "Assigning NULL");
  } 
}

static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE)
{
  unsigned long offset;
  
  offset = (unsigned long)*theCell;
  *theCell = importReference(currentStore, offset, theCell);
  
  Claim(*theCell != NULL, "Assigning NULL");
  
  /* theCell is in AOA. The reference returned by 'importReference'
     may be in IOA if the rebinder is called */
  if (isSpecialReference(offset)) {
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

static Object *importReference(unsigned long store, unsigned long offset, Object **theCell)
{
  StoreProxy *sp;
  unsigned long inxOT;
  unsigned short OTGCAttr;
  unsigned long OTstore;
  unsigned long OToffset;
  Object *theRealObj;
  
  if (!isCrossStoreReference(offset)) {
    if (!isSpecialReference(offset)) {
      if ((inxOT = indexLookupOT(store, offset)) != -1) {
	objectLookup(inxOT,
		     &OTGCAttr,
		     &OTstore,
		     &OToffset,
		     &theRealObj);
	
	Claim(OTGCAttr == ENTRYALIVE, "Lookup on dead object");
	Claim(store == OTstore, "Table mismatch");
	Claim((offset >= OToffset) && (offset < OToffset + 4*ObjectSize(theRealObj)),
	      "Table mismatch");
	
	return (Object *)((unsigned long)theRealObj + (offset - OToffset));
      } else {
	/* */
	return updateReferenceTable(store, offset, theCell);
      }
    } else {
      return handleSpecialReference(offset);
    }
  } else {
    setCurrentPStore(currentStore);
    sp = lookupStoreProxy(offset);
    return importReference(sp -> storeID, sp -> offset, theCell);
  }
}

static Object *updateReferenceTable(unsigned long store, unsigned long offset, Object **theCell)
{
  unsigned long inxRT;
  
  if ((inxRT = indexLookupRT(store, offset)) == -1) { 
    inxRT = insertReference(ENTRYALIVE,
			    store,
			    offset);
  }
  newAOAclient(inxRT, theCell);
  return (Object *)newPUID(inxRT);
} 

static void updateTransitObjectTable(Object *theObj)
{
  unsigned long distanceToPart;
  distanceToPart = (unsigned long)theObj - (unsigned long)theRealObj;
  insertObjectInTransit(currentStore,
			currentOffset + distanceToPart,
			theObj);
  if (distanceToPart == 0) {
    if (currentInx != -1) {
      theObj -> GCAttr = currentInx + 1;
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
  DEBUG_CODE(fflush(output));
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  Claim(inAOA(theObj), "Where is theObj?");
  
  theRealObj = theObj;
  /* Scan references, and turn into PUID's */
  currentStore = store;
  currentOffset = offset;
  currentInx = inx;

  scanObject(theObj,
	     storeReferenceToProcessReference,
	     updateTransitObjectTable,
	     TRUE);
}

#endif /* PERSIST */
