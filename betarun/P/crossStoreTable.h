#ifndef _CROSSSTORETABLE_H_
#define _CROSSSTORETABLE_H_

#include "objectStore.h"

BlockID createCrossStoreTable(BlockID store);
BlockID getCurrentCrossStoreTable();
int saveCurrentCrossStoreTable();
int setCurrentCrossStoreTable(BlockID store);
u_long newStoreProxy(BlockID store,
		     u_long offset);
StoreProxy *lookupStoreProxy(u_long inx);
void printCrossStoreStatistics(void);

#define isCrossStoreReference(inx) ((inx) % 2 == 1)
#endif /* _CROSSSTORETABLE_H_ */
