#ifndef _PSTORE_H_
#define _PSTORE_H_
#include "beta.h"

#define MAXNAMELENGTH 100
#define MAXNAMES      10

typedef struct StoreProxy {
  unsigned long storeID;     /* Store in which to find referred object */
  unsigned long offset;      /* Offset in store of object */
} StoreProxy;

typedef struct nameMapEntry {
  char name[MAXNAMELENGTH];
  unsigned long offset;
} nameMapEntry;

#define ILLEGALSTOREPROXY NULL
#define ILLEGALStoreID 0

/* Different types of references in the store */
#define NORMALTYPE       0
#define CROSSSTORETYPE   1
#define SPECIALTYPE      2
#define MAXTYPE          8

#define isNormalReference(inx)     ((inx) % MAXTYPE == NORMALTYPE)
#define isCrossStoreReference(inx) ((inx) % MAXTYPE == CROSSSTORETYPE)
#define isSpecialReference(inx)    ((inx) % MAXTYPE == SPECIALTYPE)
#define isIllegalReference(inx)    (((inx) % MAXTYPE > SPECIALTYPE) && ((inx) % MAXTYPE < MAXTYPE))

int createPStore(unsigned long storeID);
int setCurrentPStore(unsigned long storeID);
StoreProxy *allocateObject(unsigned long size);
Object *lookupStoreObject(unsigned long storeID, unsigned long offset);
int setStoreObject(unsigned long storeID, unsigned long offset, Object *theObj);
unsigned long newPProxy(unsigned long storeID,
			unsigned long offset);
StoreProxy *lookupStoreProxy(unsigned long inx);
void printObjectStoreStatistics(void);
int compareStoreID(unsigned long a, unsigned long b);
void getNameMap(void **nameMap);
void saveCurrentStore(void);
unsigned long getCurrentStoreID(void);
void closeCurrentStore(void);

#endif /* _PSTORE_H_ */




