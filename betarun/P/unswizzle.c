#include "beta.h"

#ifdef PERSIST
#include "referenceTable.h"
#include "objectTable.h"
#include "PException.h"
#include "PImport.h"
#include "proto.h"
#include "unswizzle.h"
#include "transitObjectTable.h"
#include "misc.h"
#include "storageblock.h"
#include "dot.h"
#include "pit.h"

/* */
/* #define DEBUG_PERSISTENCE */
#define MAXPERSISTENTBYTES 2048 * Kb

/* LOCAL VARIABLES */
static unsigned long loadedBytes = 0;
static unsigned long forceAOACompaction = 0;

/* GLOBAL VARIABLES */
int betaenvHandle; 
int programHandle;
u_long speciallookup;

/* Externals, used to initialize persistence handling */
extern void SMinit(void);

/* LOCAL FUNCTION DECLARATIONS */
Object *USloadObject(CAStorage *store,
                     unsigned long offset, 
                     unsigned long inx,
                     u_long forced);

/* FUNCTIONS */
void USstart(void)
{
   speciallookup = 0;
}

void USend(void)
{
   fprintf(stderr, "special: %d\n", (int)speciallookup);
}

/* Given the indirect proxy 'ip', it is checked if the object is in
   memory. If so the reference to the object is returned. If not the
   object is retrieved. */
void showUnswizzleStatistics(void)
{
   ;
}

Object *unswizzleReference(void *ip)
{
   RefInfo *refInfo;
   
   refInfo = PITlookup(ip);

   if (refInfo -> objInTransit) {
      Claim(AOAISPERSISTENT(refInfo -> objInTransit), "Object not persistent?");
      
      return refInfo -> objInTransit;
   } else {
      if (!isOutReference(refInfo -> offset)) {
         if (!isSpecialReference(refInfo -> offset)) {
            refInfo -> objInTransit = USloadObject(refInfo -> store, refInfo -> offset, -1, 0);
            return refInfo -> objInTransit;
         } else {
            /* handle special reference */
            perror("unswizzleReference: unbound special reference");
            return NULL;
         }
      } else {
         /* handle cross store offset */
         /* Open referred store, not implemented yet */
         perror("unswizzleReference: out reference binding not implemented yet");
         return NULL;
      }
   }
}

Object *USloadObject(CAStorage *store,
                     unsigned long offset,
                     unsigned long inx,
                     u_long forced)
{
   unsigned long size, distanceToPart;
   unsigned long enclosing;
   Object *theRealObj;
   
   enclosing = SBOBJlookup(store, offset, &size);
   Claim(enclosing, "Could not look up store object");

   distanceToPart = offset - enclosing;
   
   theRealObj = AOAallocate(2*size, TRUE);
   loadedBytes += 2*size;
   if (AllowLazyFetch && loadedBytes > MAXPERSISTENTBYTES) {
      loadedBytes = 0;
      forceAOACompaction = TRUE;
      DEBUG_CODE(fprintf(output, "Max persistent bytes exceeded\n"));
   }
   if (forceAOACompaction) {
      DEBUG_CODE(fprintf(output, "Requesting GC at next allocation\n"));
      /* Request GC at next IOAAllocation */
      AOANeedCompaction = TRUE;
      forceAOACompaction = FALSE;
      /* force IOA GC at next allocation by setting top=limit */
#if defined(NEWRUN) || defined(sparc)
      IOATopOff = (char *)IOALimit  - (char *) IOA;
#else
      IOATop = IOALimit;
#endif
   }

   SBOBJload(store, enclosing, theRealObj, size);
   
   /* The real object is imported - change from disk format to in-memory/heap format */
   importStoreObject(theRealObj, store, offset, inx, forced);
   
   /* A copy/shadow of the object is saved after the object itself. */
   memcpy((char*)theRealObj+size, theRealObj, size);
   
   /* The shadow copy is marked as alive. This marking is only used to
      indicate to the GC'er that it should not free the space taken
      up by the object. */
   ((Object*)((char*)theRealObj+size))->GCAttr = LISTEND;
   
   INFO_PERSISTENCE(objectsLoaded++);
#ifdef DEBUG_PERSISTENCE
   fprintf(output, "USloadObject: new persistent object (obj = 0x%X) (enc = 0x%X) (dist = 0x%X)\n", 
	   (int)((u_long)theRealObj + distanceToPart), 
	   (int)theRealObj, 
	   (int)distanceToPart);
#endif /* DEBUG_PERSISTENCE */
   return (Object *)((u_long)theRealObj + distanceToPart);
}

Object *handleSpecialReference(unsigned long specRef)
{
   unsigned long tag, distanceToPart;
   Object *target = NULL;
  
   Claim(isSpecialReference(specRef),
         "handleSpecialReference: Is not special reference");
  
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
         target = callRebinderC(tag);
         BETAREENTERED = FALSE;
         speciallookup++;
      } else {
         fprintf(output,
                 "handleSpecialReference: Store is not initialized");
         BetaExit(1);
      }
   }
   if (target) {
      target = (Object *)((unsigned long)getRealObject(target)
                          + distanceToPart);
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

static u_long initialized = 0;

void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long tag))
{
   if (initialized == 0) 
   {
      /* This method is called from PS.init. This means that we can
       * initialize the persistent handling from here, thus avoiding
       * allocating memory for persistence handling if it is not
       * needed. Of cource there should be a seperate function for
       * initializing the persistence handling, but this is left for
       * later. */
      SMinit();
      initLoadedObjects();
      initReferenceTable();
      initialized = 1;
   }
   callRebinderC = rebinderFunc;
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
  
   markSpecialObject(betaenvObj, BETAENVOBJ);
   markSpecialObject(programObj, PRGOBJ);
}
#endif /* PERSIST */
