#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "beta.h"
#include "objectStore.h"

u_long insertObject(char GCAttr,
		    BlockID store,
		    u_long offset,
		    Object *theObj);
void objectLookup(u_long inx,
		  char *GCAttr,
		  BlockID *store,
		  u_long *offset,
		  Object **theObj);
u_long indexLookupOT(BlockID store, u_long offset);
void OTCheck(void (*checkAction)(Object *theObj, void *generic));
void OTStartGC(void);
void objectAlive(Object *theObj);
void OTEndGC(void);
void flushDelayedEntries(void);
void updatePersistentObjects(void);
void removeUnusedObjects(void);
void initObjectTable(void);
u_long OTSize(void);
void insertStoreOffsetOT(BlockID store, u_long offset, u_long inx);

#define ENTRYDEAD         0     
#define ENTRYALIVE        1     
#define POTENTIALLYDEAD   3     
#define DELAYEDENTRYALIVE 4     

#endif /* _OBJECTTABLE_H_ */
