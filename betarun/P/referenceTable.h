#ifndef _REFERENCETABLE_H_
#define _REFERENCETABLE_H_
#include "objectStore.h"

u_long insertReference(char GCAttr,
		       StoreID store,
		       u_long offset);
void referenceLookup(u_long inx,
		     char *GCAttr,
		     StoreID *store,
		     u_long *offset);
u_long indexLookupRT(StoreID store, u_long offset);
void RTStartGC(void);
void referenceAlive(void *ip);
void RTEndGC(void);
void initReferenceTable(void);

#endif /* _REFERENCETABLE_H_ */
