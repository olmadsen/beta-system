#ifndef _CROSSSTORETABLE_H_
#define _CROSSSTORETABLE_H_

#include "objectStore.h"

StoreID createCrossStoreTable(StoreID store);
StoreID getCurrentCrossStoreTable();
int saveCurrentCrossStoreTable();
int setCurrentCrossStoreTable(StoreID store);
u_long newStoreProxy(StoreID store,
		     u_long offset);
StoreProxy *lookupStoreProxy(u_long inx);

#define isCrossStoreReference(inx) ((inx) % 2 == 1)
#endif /* _CROSSSTORETABLE_H_ */
