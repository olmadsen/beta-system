#ifndef _CROSSSTOREREFERENCES_H_
#define _CROSSSTOREREFERENCES_H_

#include "PStore.h"

unsigned long registerNewStore(char *host, char *path);
unsigned long nameToID(char *host, char *path);
storeLocation *IDToName(unsigned long id);
void markStoreAsOpen(unsigned long storeID);
unsigned long storeIsOpen(unsigned long storeID);
void markStoreAsClosed(unsigned long storeID);

#endif /* _CROSSSTOREREFERENCES_H_ */
