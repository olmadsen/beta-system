#include "specialObjectsTable.h"
#include "beta.h"
#include "sequenceTable.h"
#include "trie.h"

void sobjt_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST
/* LOCAL TYPES */
typedef struct SOTEntry { /* Special Object Table Entry */
  u_long tag;             /* Tag for the object */       
  Object *theObj;         /* The special object in memory */       
} SOTEntry;

/* LOCAL DEFINITIONS */
#define INITIALTABLELENGTH 128 /* Initial size of the objectTable */

/* LOCAL VARIABLES */
static sequenceTable *currentTable = NULL;
static Node *SOTags = NULL;

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

u_long SOTSize(void)
{
  return STSize(currentTable);
}

u_long insertSpecialObject(u_long tag, Object *theObj)
{
  SOTEntry *newEntry;
  u_long inx;
  
  if (currentTable) {
    Claim(theObj == getRealObject(theObj), "Unexpected part object");
    
    newEntry = (SOTEntry *)malloc(sizeof(SOTEntry));
    newEntry -> tag = tag;
    newEntry -> theObj = theObj;
    
    inx = STInsert(&currentTable, newEntry);
    theObj -> GCAttr = AOASpecial;
    
    return inx;
  } else {
    initSpecialObjectTable();
    return insertSpecialObject(tag, theObj);
  }
}

void unmarkSpecialObjects(void)
{
  u_long inx, maxIndex;
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

void GCspecialObjectsTable(void)
{
  u_long inx, maxIndex;
  SOTEntry *entry;

  if (currentTable) {
    maxIndex = STSize(currentTable);
    for (inx = 0; inx < maxIndex; inx++) {
      entry = STLookup(currentTable, inx);
      if (entry -> theObj -> GCAttr == DEADOBJECT) {
	Claim(inAOA(entry -> theObj), "GCspecialObjectsTable: Where is the object?");
	entry -> theObj = NULL;
      }
    }
  }
}

void remarkSpecialObjects(void)
{
  u_long inx, maxIndex;
  SOTEntry *entry;
  
  if (currentTable) {
    maxIndex = STSize(currentTable);
    for (inx = 0; inx < maxIndex; inx++) {
      entry = STLookup(currentTable, inx);
      if (entry -> theObj -> GCAttr == DEADOBJECT) {
	Claim(inAOA(entry -> theObj), "GCspecialObjectsTable: Where is the object?");
	entry -> theObj -> GCAttr = AOASpecial;
      }
    }
  }
}

void saveTagForObject(Object *realObj, u_long tag)
{
  if (SOTags) {
    TInsert((u_long)realObj, (void *)tag, SOTags, (u_long)realObj);
  } else {
    SOTags = TInit();
    saveTagForObject(realObj, tag);
  }
}

u_long getTagForObject(Object *theObj)
{
  u_long tag;

  Claim(SOTags != NULL, "getTagForObject: Where are SOTags?");
  
  tag = (u_long)TILookup((u_long)theObj, SOTags);
  Claim(tag > 0, "getTagForObject: Could not get tag for object");
  
  return tag;
}

static void freeFunc(void *tag)
{
  ;
}

void freeSOTags(void)
{
  if (SOTags) {
    TIFree(SOTags, freeFunc);
  }
}

#endif /* PERSIST */
