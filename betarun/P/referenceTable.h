#ifndef _REFERENCETABLE_H_
#define _REFERENCETABLE_H_
#include "objectStore.h"

typedef struct Array {
  u_long *theCells;
  u_short top;
  u_short max;
} Array;

u_long insertReference(char GCAttr,
		       BlockID store,
		       u_long offset);
void referenceLookup(u_long inx,
		     char *GCAttr,
		     BlockID *store,
		     u_long *offset,
		     Array **IOAclients,
		     Array **AOAclients);
u_long indexLookupRT(BlockID store, u_long offset);
void RTStartGC(void);
void referenceAlive(void *ip);
void RTEndGC(void);
void initReferenceTable(void);
void newAOAclient(u_long inx, Object **theCell);
void newIOAclient(u_long inx, Object **theCell);
void clearAOAclients(void);
void clearIOAclients(void);

#endif /* _REFERENCETABLE_H_ */
