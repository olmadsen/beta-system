#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "beta.h"
#include "objectStore.h"

u_long insertObject(char GCAttr,
		    StoreID store,
		    u_long offset,
		    Object *theObj);
void objectLookup(u_long inx,
		  char *GCAttr,
		  StoreID *store,
		  u_long *offset,
		  Object **theObj);
u_long indexLookupOT(StoreID store, u_long offset);
void OTStartGC(void);
void objectAlive(Object *theObj);
void OTEndGC(void);
void flushDelayedEntries(void);
void updatePersistentObjects(void);
void removeUnusedObjects(void);
void initObjectTable(void);
u_long OTSize(void);

#define ENTRYDEAD         0     
#define ENTRYALIVE        1     
#define POTENTIALLYDEAD   3     
#define DELAYEDENTRYALIVE 4     

#endif /* _OBJECTTABLE_H_ */
