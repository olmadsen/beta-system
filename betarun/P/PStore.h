#ifndef _PSTORE_H_
#define _PSTORE_H_
#include "beta.h"

#define MAXNAMELENGTH     100
#define MAXNAMES          10
#define MAXHOSTNAMELENGTH 128
#define MAXPATHNAMELENGTH 256
#define INITIALNUMLOCATIONS 2

typedef struct StoreProxy {
  unsigned long storeID;     /* Store in which to find referred object */
  unsigned long offset;      /* Offset in store of object */
} StoreProxy;

typedef struct nameMapEntry {
  char name[MAXNAMELENGTH];
  unsigned long offset;
} nameMapEntry;

typedef struct storeLocation { /* Identifies locations of stores */
  char host[MAXHOSTNAMELENGTH];
  char path[MAXPATHNAMELENGTH];
  unsigned long open;
} storeLocation;

typedef struct storeIDMap { /* Maps store ID's to file locations */
  unsigned long top;
  unsigned long size;
  storeLocation locations[INITIALNUMLOCATIONS];  /* Can be extended */
} storeIDMap;

typedef struct PStoreHeader {
  unsigned long headerSize;        /* Size in bytes of this header */

  /* Number of updates performed to this store (used by shared
     persistentstore) */
  unsigned long numberOfUpdates;

  /* Naming stores referred from this store */
  storeIDMap referredStores;

  /* Root names */
  nameMapEntry nameMap[MAXNAMES];
  
  /* Blocks in this store */
  unsigned long maxNumBlocks;      /* This store holds a max of so many blocks */
  unsigned long blockSize;         /* Size of each block in bytes */
  unsigned long topBlock;          
  unsigned long nextFree;          /* Offset to next free byte within
				      the top block */
  
  /* Cross store references are implemented through proxies. Space are
     reserved for proxies at the other end of the store. The proxy
     insertion point grows downwards. When proxies and objects meet it's
     time for a reallocation.  */
  
  unsigned long crossStoreTop;

  /* To handle objects spanning several blocks. If an object starts at
     the beginning of a block this block is marked using vector below */
  unsigned long startMarkers[1];   /* */
  
} PStoreHeader;

/* Different types of references in the store */
#define NORMALTYPE       0
#define SPECIALTYPE      1
#define CROSSSTORETYPE   2
#define MAXTYPE          8

#define isNormalReference(inx)            ((inx) % MAXTYPE == NORMALTYPE)
#define isSpecialReference(inx)           ((inx) % MAXTYPE == SPECIALTYPE)
#define isCrossStoreReference(store, inx) ((inx) % MAXTYPE == CROSSSTORETYPE)
#define isIllegalReference(inx)           (((inx) % MAXTYPE > CROSSSTORETYPE) && ((inx) % MAXTYPE < MAXTYPE))

int createPStore(char *host, char *path);
int setCurrentPStore(unsigned long storeID);
StoreProxy *allocateObject(unsigned long storeID,
			   unsigned long size);
Object *lookupStoreObject(unsigned long storeID, 
			  unsigned long offset);
int setStoreObject(unsigned long storeID, 
		   unsigned long offset, 
		   Object *theObj);
unsigned long newPProxy(unsigned long storeContainingProxy,
			unsigned long storeID,
			unsigned long offset);
StoreProxy *lookupStoreProxy(unsigned long storeID, 
			     unsigned long inx);
void printObjectStoreStatistics(void);
void saveCurrentStore(void);
void closeCurrentStore(void);
void closeStore(unsigned long storeID);
void saveStore(unsigned long storeID);
unsigned long getRootOffset(unsigned long storeID, 
			    char *name);
void insertRoot(unsigned long storeID, 
		char *name, 
		unsigned long offset);
unsigned long getNumberOfUpdates(unsigned long host_r, 
				 unsigned long path_r);

#endif /* _PSTORE_H_ */




