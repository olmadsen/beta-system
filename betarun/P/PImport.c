#include "beta.h"
#include "referenceTable.h"
#include "objectTable.h"
#include "transitObjectTable.h"
#include "PException.h"
#include "PImport.h"
#include "crossStoreTable.h"
#include "unswizzle.h"

void pimport_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL VARIABLES */
static BlockID currentStore;
static Object *theRealObj;
static unsigned long currentOffset;

/* LOCAL FUNCTION DECLARATIONS */
static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE);
static Object *importReference(BlockID store, unsigned long offset, Object **theCell);
static Object *updateReferenceTable(BlockID store, unsigned long offset, Object **theCell);

/* FUNCTIONS */
static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE)
{
  *theCell = importReference(currentStore, (unsigned long)*theCell, theCell);

  /* theCell is in AOA. The reference returned by 'importReference'
     may be in IOA if the rebinder is called */
  
  if (inIOA(*theCell)) {
    AOAtoIOAInsert( theCell);
  }
}

static Object *importReference(BlockID store, unsigned long offset, Object **theCell)
{
  StoreProxy *sp;
  unsigned long inxOT;
  char OTGCAttr;
  BlockID OTstore;
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
    setCurrentCrossStoreTable(currentStore);
    sp = lookupStoreProxy(offset);
    return importReference(sp -> store, sp -> offset, theCell);
  }
}

static Object *updateReferenceTable(BlockID store, unsigned long offset, Object **theCell)
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
}

void importStoreObject(Object *theObj, BlockID store, unsigned long offset)
{
  void (*temp)(Object *theObj);
  
  DEBUG_CODE(fflush(output));
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  Claim(inAOA(theObj), "Where is theObj?");

  theRealObj = theObj;
  /* Scan references, and turn into PUID's */
  currentStore = store;
  currentOffset = offset;
  temp = objectAction; 
  objectAction = updateTransitObjectTable;
  
  scanObject(theObj,
	     storeReferenceToProcessReference,
	     TRUE);
  
  objectAction = temp;
}

#endif /* PERSIST */
