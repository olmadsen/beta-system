#ifndef _REFERENCETABLE_H_
#define _REFERENCETABLE_H_
#include "beta.h"
#include "storageblock.h"

typedef struct Array {
  unsigned long *theCells;
  unsigned short top;
  unsigned short max;
} Array;

/* References to persistent objects are actually references to runtime
 * info objects. The reference is tagged to ensure a bus error if
 * dereferenced.
 */

typedef struct _RefInfo {
#ifdef COM
   long *vtbl;
#else /* !COM */
   ProtoType *Proto;     
#endif /* COM */
   u_long     GCAttr;       /* The GC attribute            */
   CAStorage *store;        /* The store in which the referredobject is saved */
   u_long     offset;       /* The byte offset in the store of the referred object */  
   Array     *AOAcells;     /* List of cells in AOA containing ip to this ref info obj */
   Object    *objInTransit; /* See comment LLL in 'unswizzle.c' */
   void      *ip;           /* The proxy corresponding to this reference info object */
   u_long    bytesize;
} RefInfo;

void initReferenceTable(void);
void *referenceInfo(CAStorage *store, u_long offset);
void *lookupReferenceInfo(CAStorage *store, u_long offset);
void updateOtherReferences(CAStorage *store, u_long offset, u_long bytesize,
                           Object *obj);
void referenceCheck(Object **theCell);
void referenceAlive(void *ip, RefInfo *refInfo);
void newAOAcell(void *ip, Object **theCell);
void clearAOAclients(void);
void RTEndGC(void);
void RTStartGC(void);

/* Arrays */
Array *newArray(void);
void Aappend(Array *array, unsigned long theCell);

#endif /* _REFERENCETABLE_H_ */
