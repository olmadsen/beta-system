#ifndef _CROSSSTORETABLE_H_
#define _CROSSSTORETABLE_H_

#include "objectStore.h"

BlockID createCrossStoreTable(BlockID store);
BlockID getCurrentCrossStoreTable();
int saveCurrentCrossStoreTable();
int setCurrentCrossStoreTable(BlockID store);
unsigned long newStoreProxy(BlockID store,
		     unsigned long offset);
StoreProxy *lookupStoreProxy(unsigned long inx);

#endif /* _CROSSSTORETABLE_H_ */
