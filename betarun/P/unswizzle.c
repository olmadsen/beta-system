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
#include "misc.h"
#include "../C/dot.h"

/* */
#ifdef PERSIST
#define MAXPERSISTENTBYTES 2048 * Kb

/* LOCAL VARIABLES */
static unsigned long loadedBytes = 0;
static unsigned long forceAOACompaction = 0;

/* GLOBAL VARIABLES */
int betaenvHandle; 
int programHandle;

/* LOCAL FUNCTION DECLARATIONS */
static Object *loadObject(unsigned long store, unsigned long offset, unsigned long inx);
static Object *storeNotOpen(unsigned long store, 
			    unsigned long offset, 
			    unsigned long inx);

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
    Claim(indexLookupOT(store, offset) == -1, 
	  "lookUpReferenceEntry: Object in Object Table but referred indirectly!");
    return loadObject(store, offset, inx);
  }
}

#ifdef PSENDIAN
static void EndianconvertFromStoreProc(REFERENCEACTIONARGSTYPE)
{
  *theCell = (Object*)ntohl((unsigned long)*theCell);
}

void EndianconvertFromStore(Object *obj)
{
  ProtoType * theProto;
  
  theProto = GETPROTO(obj);

  if (!isSpecialProtoType(theProto)) {
    unsigned char *ebits, b, do_int16, do_real64;
    unsigned long offset, pos;
    short * refs_ofs;
    short *ptr;
    int numbytes;
    GCEntry *tab =
      (GCEntry *) ((char *) theProto + theProto->GCTabOff);

    /* Handle all reference fields in obj: */
    scanObject(obj, EndianconvertFromStoreProc, NULL, TRUE);
    /* Skip part-object table: */
    for (;tab->StaticOff; ++tab) {
      ;
    }
    /* Skip dynrefs : */
    for (refs_ofs = (short *)&tab->StaticOff+1; *refs_ofs; refs_ofs++) {
      ;
    }

    /* Handle all longs: */
    ebits = (unsigned char*) (refs_ofs + 1);
    b = *ebits++;
    do_int16  = (b & 0x80);
    do_real64 = (b & 0x40);

    if (b & 0x3f) { /* Any longs in the first 8 words? */
      offset = 2;
      while (b & 0x3f) { /* Any longs in the first 8 words? */
	if (b & 0x20) {
	  *((unsigned long*)obj+offset) = ntohl(*((unsigned long*)obj+offset));
	}
	b *= 2;
	offset++;
      }
    }
    pos = 8;
    
    numbytes = ((ObjectSize(obj)-1) / 8);
    while (numbytes--) {
      b = *ebits++;
      if (b) {
	offset = pos;
	while (b) {
	  if (b & 0x80) {
	    *((unsigned long*)obj+offset) = ntohl(*((unsigned long*)obj+offset));
	  }
	  offset++;
	  b *= 2;
	}
      }
      pos += 8;
    }
    
    if ((unsigned long)ebits & 1) {
      ebits++;
    }

    ptr = (short*)ebits;
    if (do_int16) {
      while (*ptr) {
	*(unsigned short*)((char*)obj+*ptr) = ntohs(*(unsigned short*)((char*)obj+*ptr));
	ptr++;
      }
      ptr++;
    }

    if (do_real64) {
      while (*ptr) {
	unsigned long x = ntohl(*(unsigned long*)((char*)obj+*ptr));
	*(unsigned long*)((char*)obj+*ptr) = 
	  ntohl(*(unsigned long*)((char*)obj+*ptr+4));
	*(unsigned long*)((char*)obj+*ptr+4) = x;
	ptr++;
      }
    }
  } else {
    switch (SwitchProto(theProto)) {
    case SwitchProto(LongRepPTValue):     
      {
	unsigned long *pointer;
	long offset, offsetTop;
              
	offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
	offsetTop = offset + 4 * ((ValRep*)(obj))->HighBorder;

	while (offset < offsetTop) {
	  pointer = (unsigned long *)((char*)obj + offset);
	  *pointer = ntohl(*pointer);
	  offset += 4;
	}
	break;
      }

    case SwitchProto(DoubleRepPTValue):
      {
	unsigned long *pointer, x;
	long offset, offsetTop;
	
	offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
	offsetTop = offset + 8 * ((ValRep*)(obj))->HighBorder;
	
	while (offset < offsetTop) {
	  pointer = (unsigned long*)((char*)obj + offset);
	  x = ntohl(*pointer);
	  *pointer = ntohl(*(pointer+1));
	  *(pointer+1) = x;
	  offset += 8;
	}
	break;
      }
    case SwitchProto(ShortRepPTValue):
      {
	unsigned short *pointer;
	long offset, offsetTop;
              
	offset =  (char*)(&((ValRep*)(obj))->Body[0]) - (char*)obj;
	offsetTop = offset + 2 * ((ValRep*)(obj))->HighBorder;
	
	while (offset < offsetTop) {
	  pointer = (unsigned short*)((char*)obj + offset);
	  *pointer = ntohs(*pointer);
	  offset += 2;
	}
	break;
      }
    }
  }
}
#endif /* PSENDIAN */


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
    
    if (distanceToPart == 0) {
      size = 4*StoreObjectSize(theRealStoreObj);
      forceAOAAllocation = TRUE; /* The following allocation must not fail*/
      theRealObj = AOAallocate(2*size);
      loadedBytes += 2*size;
      if (loadedBytes > MAXPERSISTENTBYTES) {
	loadedBytes = 0;
	forceAOACompaction = TRUE;
	DEBUG_CODE(fprintf(output, "Max persistent bytes exceeded\n"));
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
#ifdef PSENDIAN
      EndianconvertFromStore(theRealObj);
#endif
      importStoreObject(theRealObj, store, offset, inx);
      
      Claim(ObjectSize(((Object*)((char*)theRealObj+size)))
	    == ObjectSize(theRealObj), "Claim");
      INFO_PERSISTENCE(objectsLoaded++);
      return theRealObj;
    } else {
      Object *theRealObj;
      
      theRealObj = lookUpReferenceEntry(store, offset - distanceToPart, -1);
      return (Object *)((unsigned long)theRealObj + distanceToPart);
    }
  } else {
    /* The store that we are trying to access is not open. We call user
       code in order to have this done */
    return storeNotOpen(store, offset, inx);
  }
}

static Object *storeNotOpen(unsigned long store, 
			    unsigned long offset, 
			    unsigned long inx)
{
  storeLocation *sl;
  
  if ((sl = IDToName(store))) {
    if (callOpenCrossStoreC) {
      callOpenCrossStoreC(&(sl -> host[0]), &(sl -> path[0]));
      if (storeIsOpen(store)) {
	setCurrentPStore(store);
	return loadObject(store, offset, inx);
      } else {
	fprintf(output, 
		"storeNotOpen: User function 'openpstore' failed to open store\n");
	BetaExit(1);
      }
    } else {
      fprintf(output, "storeNotOpen: Store is not initialized\n");
      BetaExit(1);
    }
  } else {
    fprintf(output, "storeNotOpen: Unknown store id (%d)\n", (int)store);
    BetaExit(1);
  }
  return NULL;
}

/* If the implementation of the UNKNOWNTAG in virtualobjectstore.bet is
   changed then the define below should be changed accordingly.  */
#define UNKNOWNTAG 0

Object *handleSpecialReference(unsigned long specRef)
{
  unsigned long tag, distanceToPart;
  Object *target = NULL;
  
  Claim(isSpecialReference(specRef), "handleSpecialReference: Is not special reference");
  
  tag = specRef >> 24;
  distanceToPart = (specRef & 0x00FFFF00) >> 8;
  
  /* Below we reenter BETA code while we are in the midst of loading
     an object. While in BETA code additional object loads might be
     issued, and GCs, both IOAGC amd AOAGC, might occur. While it
     should be possible to support all these events only an IOAGC is
     legal at this point in time. */
  
  if (tag == BETAENVOBJ) {
    target = DOThandleLookup(betaenvHandle);
  } else if (tag == PRGOBJ) {
    target = DOThandleLookup(programHandle);
  } else {
    BETAREENTERED = TRUE;
    if (callRebinderC) {
      target = callRebinderC(tag, UNKNOWNTAG);
      BETAREENTERED = FALSE;
    } else {
      fprintf(output, "handleSpecialReference: Store is not initialized");
      BetaExit(1);
    }
  }
  if (target) {
    target = (Object *)((unsigned long)getRealObject(target) + distanceToPart);
  } else {
    fprintf(output, 
	    "handleSpecialReference: User code failed to rebind\n"
	    "reference to special object tagged %d. Make sure\n"
	    "the 'rebindSpecialReference' virtual has been implemented\n"
	    "correctly.\n", (int)tag);
    BetaExit(1);
  }
  return target;
}

void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long objectTag, 
						  unsigned long typeTag))
{
  callRebinderC = rebinderFunc;
}

void registerOpenCrossStoreFunc(void (*openCrossStoreFunc)(char *host, 
							   char *path))
{
  callOpenCrossStoreC = openCrossStoreFunc;
}

void registerBETAENVandPROGRAM(Component *theProgram)
{
  Object *betaenvObj, *programObj;
  programObj = (Object *)ComponentItem(theProgram);
  betaenvObj = *(Object **)((unsigned long)programObj + 0x8);

  DOTinit();

  /* */
  if ((betaenvHandle = DOThandleInsert(betaenvObj, (void (*)(int handle))0, TRUE)) == -1) {
    fprintf(output, "registerBETAENVandPROGRAM: Failed to insert betaenvObj in dot!");
    BetaExit(1);
  }
  
  if ((programHandle = DOThandleInsert(programObj, (void (*)(int handle))0, TRUE)) == -1) {
    fprintf(output, "registerBETAENVandPROGRAM: Failed to insert programObj in dot!");
    BetaExit(1);
  }
  
  markSpecialObject(BETAENVOBJ, betaenvObj);
  markSpecialObject(PRGOBJ, programObj);
}
#else
void registerBETAENVandPROGRAM(Component *theProgram)
{
  return;
}
#endif /* PERSIST */
