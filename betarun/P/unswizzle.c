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

/* LOCAL FUNCTION DECLARATIONS */
static void getSpecialRefs(REFERENCEACTIONARGSTYPE);
static Object *loadObject(unsigned long store, u_long offset);
static void getSpecialRefs(REFERENCEACTIONARGSTYPE);

/* FUNCTIONS */

/* Given the indirect proxy 'ip', it is checked if the object is in
   memory. If so the reference to the object is returned. If not the
   object is retrieved. */

Object *unswizzleReference(void *ip)
{
  char GCAttr;
  unsigned long store;
  unsigned long offset;
  unsigned long inx;
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

Object *lookUpReferenceEntry(unsigned long store, unsigned long offset)
{
  Object *theObj;
  
  if ((theObj = indexLookupTOT(store, offset)) != NULL) {
    return theObj;
  } else {
    return loadObject(store, offset);
  }
}

static Object *loadObject(unsigned long store, unsigned long offset)
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
    
    theRealObj = lookUpReferenceEntry(store, offset - distanceToPart);
    return (Object *)((unsigned long)theRealObj + distanceToPart);
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

    /* Some types of references are not ref-none checked before they
       are used. These types are,
       
       * Origin references
       * Offline allocated part objects
       * Repetitions
       
       If the object we just loaded contains such references they need
       to be unswizzled as well.
    */
    
    scanObject(theRealObj,
	       getSpecialRefs,
	       NULL,
	       TRUE);
    return theRealObj;
  }
}

static void getSpecialRefs(REFERENCEACTIONARGSTYPE)
{
  if (refType == REFTYPE_DYNAMIC) {
    return;
  } else {
    Object *theObj;
    
    if ((theObj = *theCell)) {
      if (inPIT((void *)theObj)) {
	Object *absAddr;
	
	absAddr = unswizzleReference((void *)theObj);
	/* Insert absolute reference in theCell */
	*theCell = absAddr;
	Claim(*theCell != NULL, "Assigning NULL");
      }
    } 
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
