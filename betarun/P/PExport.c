#include "beta.h"

#ifdef PERSIST
#include "PException.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "specialObjectsTable.h"
#include "storageblock.h"
#include "pit.h"

/* LOCAL FUNCTION DECLARATIONS */
static void refhandler(REFERENCEACTIONARGSTYPE);

/* LOCAL TYPES */
typedef struct objinfo
{
   Object *buffer;
   /* The object that is currently being exported.
    */
   u_long size;
   /* size of the buffer */
   CAStorage *store;
   /* The store in which it resides.
     */
   /* som profiling info follows */
   u_long refsfollowed;
   u_long refs;
} Objinfo;

/* LOCAL VARIABLES */
/* We need to know some particulars about the object that is currently
 * being exported. Unfortunately this info cannot be passed as
 * arguments to the object scanner, since that is also used many other
 * places, places where it would be unacceptable to pass such extra
 * arguments around. It follows that we have to make a global variable
 * holding the said info, eventhough we hate and despise global
 * variables even more.
 */
static Objinfo current = {0, 0, 0, 0, 0};

/* 'refhandler' is called for each reference in the object that is
 * being exported.
 */
static void refhandler(REFERENCEACTIONARGSTYPE)
{
   CAStorage *store;
   unsigned long offset, distanceToPart;
   Object *theObj, *realObj;
   
   theObj = *theCell;

   /* The tagging of the reType is currently not used */
   refType = NORMALREFERENCE;
   
   if (inPIT(theObj)) {
      RefInfo *refInfo;
      refInfo = (RefInfo *)PITlookup(theObj);
      store = refInfo -> store;
      offset = refInfo -> offset;
      distanceToPart = 0;        
   } else {
      realObj = getRealObject(theObj);
      distanceToPart = (unsigned long)theObj - (unsigned long)realObj;
      Claim(inAOA(realObj), "Where is the object?");
      if (AOAISPERSISTENT(realObj)) {
         ObjInfo *objInfo;
         objInfo = (ObjInfo *)GETOI(realObj -> GCAttr);
         store = objInfo -> store;
         offset = objInfo -> offset;
      } else {
         unsigned long tag;
         
         tag = getTag(realObj);
         
         Claim(tag < 0xFF, "Tag not found or tag too big");
         Claim(distanceToPart < 0xFFFF, "distanceToPart too big");
            
         *theCell = (Object *)(((tag << 24 ) | (distanceToPart << 8) | SPECIALREFERENCE) + 1);
         return;
      }
   }
    
   if (store == current.store) {
      if (!isOutReference(offset)) {
         /* the reference is simply replaced by the offset of the
          * referred object. One is added in order to distinquish none
          * references from zero offsets (which are possible)
          */
         *theCell = (Object *)(((offset + distanceToPart) | refType) + 1);
      } else {
         /* cross block reference */
         Claim(FALSE, "PExport: cross block references not implemented yet");
      }
   } else {
      /* cross block reference */
      Claim(FALSE, "PExport: cross block references not implemented yet");
   }

   Claim(*theCell != NULL, "Assigning NULL to cell");
}

extern void EndianconvertFromStore(Object *obj);

void extendBufferSize(u_long size)
{
   if (current.buffer) {
      free(current.buffer);
   }
   current.buffer = (Object *)malloc(sizeof(char)*size);
   current.size = size;
}

/* Exports the object to 'store' */
Object *exportObject(Object *theObj, CAStorage *store, u_long size)
{
   if (current.size < size) {
      extendBufferSize(size);
   }
   current.store = store;
   memcpy(current.buffer, theObj, size);
   scanObject(current.buffer, refhandler, NULL, TRUE);
#ifdef PSENDIAN
   EndianconvertFromStore(theObj);
#endif
   return current.buffer;
}
#endif /* PERSIST */
