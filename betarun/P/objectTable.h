#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "beta.h"
#include "storageblock.h"
#include "referenceTable.h"

/* Persistent objects contain, in their GCAttribute, a reference to a
 * runtime object containing some information on the persistent
 * object.  */
typedef struct _ObjInfo {
#ifdef COM
   long *vtbl;
#else /* !COM */
   ProtoType *Proto;     
#endif /* COM */
   u_long     GCAttr;       /* The GC attribute            */
   u_long     flags;        /* Misc. flags for this entry. */
   CAStorage *store;        /* The store in which this object is saved */
   u_long     offset;       /* The byte offset in the store of the object */  
   Object    *theObj;       /* The object in memory */
} ObjInfo;

void initLoadedObjects(void);
void insertStoreOffset(CAStorage *store, u_long offset, u_long info, Trie **loadedObjects);
ObjInfo *objectInfo(u_short flags,
                    CAStorage *store,
                    u_long offset,
                    Object *theObj);
ObjInfo *lookupObjectInfo(CAStorage *store, u_long offset);
void markObject(Object *obj, int follow);
void objectAlive(Object *theObj);
u_long objectIsDead(Object *theObj);
void setCurrentStoreID(CAStorage *ID);
void phaseOne(void);
void handlePersistentCell(REFERENCEACTIONARGSTYPE);
void phaseThree(void);
void phaseFive(void);
void OTEndGC(void);
void insertObject(CAStorage *store, u_long offset, ObjInfo *objInfo);
void closeStore(CAStorage *store);

#define FLAG_INSTORE      1
#define FLAG_INMEM        0

#endif /* _OBJECTTABLE_H_ */

