#include "beta.h"
#include "referenceTable.h"
#include "objectTable.h"
#include "PException.h"
#include "PImport.h"

void pimport_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL VARIABLES */
static StoreID currentStore;

/* LOCAL FUNCTION DECLARATIONS */
static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE);

/* FUNCTIONS */
static void storeReferenceToProcessReference(REFERENCEACTIONARGSTYPE)
{
  u_long inx; 
  
  if ((inx = indexLookupRT(currentStore, (u_long)*theCell)) == -1) { 
    inx = insertReference(ENTRYALIVE,
			  currentStore,
			  (u_long)*theCell);
  }
  
  *theCell = (Object *)newPUID(inx);
  
  /* The referred object itself is not retreived */
  
}

void importStoreObject(Object *theObj, StoreID store)
{
  void (*temp)(Object *theObj);

  /* Scan references, and turn into PUID's */
  currentStore = store;
  temp = objectAction; objectAction = NULL;
  scanObject(theObj,
	     storeReferenceToProcessReference,
	     TRUE);
  objectAction = temp;
}

#endif /* PERSIST */
