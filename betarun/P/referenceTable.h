#ifndef _REFERENCETABLE_H_
#define _REFERENCETABLE_H_
#include "beta.h"

typedef struct Array {
  unsigned long *theCells;
  unsigned short top;
  unsigned short max;
} Array;

unsigned long insertReference(unsigned short GCAttr,
			      unsigned long store,
			      unsigned long offset);
void referenceLookup(unsigned long inx,
		     unsigned short *GCAttr,
		     unsigned long *store,
		     unsigned long *offset,
		     Array **IOAclients,
		     Array **AOAclients);
unsigned long indexLookupRT(unsigned long store, unsigned long offset);
void RTStartGC(void);
void referenceAlive(void *ip);
void RTEndGC(void);
void initReferenceTable(void);
void newAOAclient(unsigned long inx, Object **theCell);
void newIOAclient(unsigned long inx, Object **theCell);
void clearAOAclients(void);
void clearIOAclients(void);
void setObjInTransit(unsigned long inx, Object *theObj);
Object *getObjInTransit(unsigned long inx);

#endif /* _REFERENCETABLE_H_ */
