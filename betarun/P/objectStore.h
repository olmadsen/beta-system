#ifndef _OBJECTSTORE_H_
#define _OBJECTSTORE_H_
#include "beta.h"
typedef u_long BlockID;

typedef struct StoreProxy {
  BlockID store;     /* Store in which to find referred object */
  u_long offset;     /* Offset in store of object */
} StoreProxy;

#define ILLEGALSTOREPROXY NULL
#define ILLEGALBlockID 0

/* Different types of references in the store */
#define NORMALTYPE       0
#define CROSSSTORETYPE   1
#define SPECIALTYPE      2
#define MAXTYPE          8

#define isNormalReference(inx)     ((inx) % MAXTYPE == NORMALTYPE)
#define isCrossStoreReference(inx) ((inx) % MAXTYPE == CROSSSTORETYPE)
#define isSpecialReference(inx)    ((inx) % MAXTYPE == SPECIALTYPE)
#define isIllegalReference(inx)    (((inx) % MAXTYPE > SPECIALTYPE) && ((inx) % MAXTYPE < MAXTYPE))

int saveCurrentObjectStore();
int setCurrentObjectStore(BlockID store);
StoreProxy *newStoreObject(Object *theObj);
Object *lookupStoreObject(BlockID store, u_long offset);
int setStoreObject(BlockID store, u_long offset, Object *theObj);
void printObjectStoreStatistics(void);

#endif /* _OBJECTSTORE_H_ */
