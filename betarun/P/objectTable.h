#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "beta.h"

unsigned long insertObject(unsigned short GCAttr,
			   unsigned short Flags,
			   unsigned long store,
			   unsigned long offset,
			   Object *theObj);
void objectLookup(unsigned long inx,
		  unsigned short *GCAttr,
		  unsigned long *store,
		  unsigned long *offset,
		  Object **theObj);
unsigned long indexLookupOT(unsigned long store, unsigned long offset);
void OTCheck(void (*checkAction)(Object *theObj, void *generic));
void OTStartGC(void);
void objectAlive(Object *theObj);
void OTEndGC(void);
void flushDelayedEntries(void);
void updatePersistentObjects(void);
void removeUnusedObjects(void);
void initObjectTable(void);
unsigned long OTSize(void);
void insertStoreOffsetOT(unsigned long store, unsigned long offset, unsigned long inx);

#define ENTRYDEAD         0     
#define ENTRYALIVE        1     
#define POTENTIALLYDEAD   3     
#define DELAYEDENTRYALIVE 4     

#define FLAG_INSTORE      1

#endif /* _OBJECTTABLE_H_ */
