#include "specialObjectsTable.h"
#include "beta.h"
#include "sequenceTable.h"
#include "trie.h"

#ifdef PERSIST
/* LOCAL TYPES */
typedef struct SOTEntry { /* Special Object Table Entry */
  unsigned long tag;             /* Tag for the object */       
  Object *theObj;         /* The special object in memory */       
} SOTEntry;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the objectTable */

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Trie *SOTags = NULL;

/* FUNCTIONS */
static int isFree(void *entry)
{
  Claim(entry != NULL, "isFree: entry is NULL");
  return (((SOTEntry *)entry) -> theObj == 0);
}

static void Free(void *entry)
{
  Claim(entry != NULL, "Free: entry is NULL");
  free((SOTEntry *)entry);
}

void initSpecialObjectTable(void)
{
  currentTable = STInit(INITIALTABLELENGTH, isFree, Free, sizeof(SOTEntry));
}

void destroySpecialObjectTable(void)
{
    if (currentTable) {
        STFree(&currentTable);
    }
}

unsigned long SOTSize(void)
{
  return STSize(currentTable);
}

unsigned long insertSpecialObject(unsigned long tag, Object *theObj)
{
  unsigned long inx;
  SOTEntry newEntry;
  
  if (currentTable) {
    Claim(theObj == getRealObject(theObj), "Unexpected part object");
    Claim(inAOA(theObj), "insertSpecialObject: Where is theObj");
    
    newEntry.tag = tag;
    newEntry.theObj = theObj;
    
    inx = STInsert(&currentTable, &newEntry);
    return inx;
  } else {
    initSpecialObjectTable();
    return insertSpecialObject(tag, theObj);
  }
}

void SOStartGC(void)
{
  unsigned long inx, maxIndex;
  SOTEntry *entry;

  if (currentTable) {
    maxIndex = STSize(currentTable);
    for (inx = 0; inx < maxIndex; inx++) {
      entry = STLookup(currentTable, inx);
      if (entry -> theObj) {
	Claim(inAOA(entry -> theObj), "unmarkSpecialObjects: Where is the object?");
	
	entry -> theObj -> GCAttr = DEADOBJECT;
      }
    }
  }
}

void SOEndGC(void)
{
  unsigned long inx, maxIndex;
  SOTEntry *entry;

  if (currentTable) {
    maxIndex = STSize(currentTable);
    for (inx = 0; inx < maxIndex; inx++) {
      entry = STLookup(currentTable, inx);
      if (entry -> theObj) {
	if (entry -> theObj -> GCAttr == DEADOBJECT) {
	  Claim(inAOA(entry -> theObj), "GCspecialObjectsTable: Where is the object?");
	  entry -> theObj = NULL;
	}
      }
    }
  }
}

void remarkSpecialObjects(void)
{
  unsigned long inx, maxIndex;
  SOTEntry *entry;
  
  if (currentTable) {
    maxIndex = STSize(currentTable);
    for (inx = 0; inx < maxIndex; inx++) {
      entry = STLookup(currentTable, inx);
      if (entry -> theObj) {
	Claim(inAOA(entry -> theObj), "GCspecialObjectsTable: Where is the object?");
	
	entry -> theObj -> GCAttr = AOASPECIAL;
      }
    }
  }
}

/* 'getTagForObject' and 'getTag' should be only one function. This is
 *  just a stupid implementation that will be fixed.
 */
unsigned long getTag(Object *theObj)
{
  unsigned long inx, maxIndex;
  SOTEntry *entry;
  
  if (currentTable) {
    maxIndex = STSize(currentTable);
    for (inx = 0; inx < maxIndex; inx++) {
      entry = STLookup(currentTable, inx);
      if (entry -> theObj == theObj) {
	Claim(inAOA(entry -> theObj), "GCspecialObjectsTable: Where is the object?");
	return entry -> tag;
      }
    }
  }
  return -1;
}

void saveTagForObject(Object *realObj, unsigned long tag)
{
  if (SOTags) {
    TInsert((unsigned long)realObj, tag, &SOTags, (unsigned long)realObj);
  } else {
    SOTags = TInit();
    saveTagForObject(realObj, tag);
  }
}

unsigned long getTagForObject(Object *theObj)
{
  unsigned long tag;

  Claim(SOTags != NULL, "getTagForObject: Where are SOTags?");
  
  tag = (unsigned long)TILookup((unsigned long)theObj, SOTags);
  Claim(tag > 0, "getTagForObject: Could not get tag for object");
  
  return tag;
}

void freeSOTags(void)
{
  if (SOTags) {
    TIFree(SOTags, (void (*)(unsigned long))0);
    SOTags = NULL;
  }
}

#endif /* PERSIST */
