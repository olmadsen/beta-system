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

int saveCurrentObjectStore();
int setCurrentObjectStore(BlockID store);
StoreProxy *newStoreObject(Object *theObj);
Object *lookupStoreObject(BlockID store, u_long offset);
int setStoreObject(BlockID store, u_long offset, Object *theObj);
void printObjectStoreStatistics(void);

#endif /* _OBJECTSTORE_H_ */
