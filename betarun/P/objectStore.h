#ifndef _OBJECTSTORE_H_
#define _OBJECTSTORE_H_
#include "beta.h"
typedef u_long StoreID;

typedef struct StoreProxy {
  StoreID store;     /* Store in which to find referred object */
  u_long offset;     /* Offset in store of object */
} StoreProxy;

#define ILLEGALSTOREPROXY NULL
#define ILLEGALSTOREID 0

int saveCurrentObjectStore();
int setCurrentObjectStore(StoreID store);
StoreProxy *newStoreObject(Object *theObj);
Object *lookupStoreObject(StoreID store, u_long offset);
int setStoreObject(StoreID store, u_long offset, Object *theObj);

#endif /* _OBJECTSTORE_H_ */
