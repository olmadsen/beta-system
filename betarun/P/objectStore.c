#include "objectStore.h"
#include "PStoreServer.h"
#include "PSfile.h"
#include "PStore.h"
#include "crossStoreTable.h"

void os_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL TYPES */

typedef struct ObjectStore {
  u_long maxSize;        /* Space allocated for this store in bytes */
  u_long nextFree;       /* Offset of the next free entry in bytes */
  u_long lookupCount;    /* Number of times this block has been requested */
  StoreID store;         /* The id of the store belonging to this
			    ObjectStore */
  Object body[1];        /* The objects. */
} ObjectStore;

/* LOCAL VARIABLES */

static ObjectStore *currentTable = NULL;   /* The current table loaded */

#define BLOCKSINSTORE 1

/* LOCAL FUNCTION DECLARATIONS */
static int createObjectStore(StoreID store, u_long minSize);

/* IMPEMENTATION */
static int createObjectStore(StoreID store, u_long minSize)
{
  char *file_name;
  int fd;
  ObjectStore *newTable;
  u_long storeSize;
  
  /* Object stores are the smallest unit of data that this process can
     access in the store. If an object saved in a certain object store
     A is retrieved, the entire object store is retrieved. If objects
     used together are placed in the same object store, chances are
     that the object store containg a needed object has been loaded
     already. The size of the object store is some multiplum of the
     preferred buffer size (on UNIX 8192 bytes). If objects larger
     than the size of object stores are saved, a larger store is
     created anyway. */
  
  if ((file_name = objectStoreName(store))) {
    if ((fd = open(file_name,O_RDWR | O_CREAT, S_IWRITE | S_IREAD))<0) {
      perror("createObjectStore");
      return ILLEGALSTOREID;
    } else {
      storeSize = preferredBufferSize(file_name) * BLOCKSINSTORE;
      
      while(storeSize < minSize) {
	storeSize = storeSize * 2;
      }
      
      newTable = (ObjectStore *)calloc(storeSize, 1);
      newTable -> maxSize = storeSize;
      newTable -> nextFree = (u_long)&(newTable -> body[0]) - (u_long)newTable;
      newTable -> lookupCount = 0;
      newTable -> store = store;
      
      writeSome(fd, newTable, newTable -> maxSize);
      close(fd);
      
      Claim(currentTable == NULL, "What is currentTable ?");
      currentTable = newTable;
      return store;
      
    }
  } else {
    return ILLEGALSTOREID;
  }
  
  return ILLEGALSTOREID;
}

int saveCurrentObjectStore()
{
  if (currentTable) {
    char *file_name;
    int fd;
    
    if ((file_name = objectStoreName(currentTable -> store))) {
      if ((fd = open(file_name,O_RDWR))<0) {
	perror("saveCurrentObjectStore");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      } else {
	writeSome(fd, currentTable, currentTable -> maxSize);
	close(fd);
	INFO_PERSISTENCE(fprintf(output,"[saveCurrentObjectStore(%d): used %d (%d) (%d%%)]\n", 
				 (int)(currentTable -> store),
				 (int)(currentTable -> nextFree),
				 (int)(currentTable -> maxSize),
				 (int)(currentTable -> nextFree * 100 / currentTable -> maxSize)));
      }
    } else {
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
  } else {
    return 0;
  }
  
  return 1;
}

int setCurrentObjectStore(StoreID store)
{
  char *file_name;
  int fd;
  
  if (currentTable) {
    if (compareStoreID(store, currentTable -> store)) {
      return 1;
    } else {
      saveCurrentObjectStore();
      free(currentTable);
      currentTable = NULL;
    }
  }
  
  if ((file_name = objectStoreName(store))) {
    if ((fd = open(file_name,O_RDWR))<0) {
      perror("setCurrentObjectStore");
      return 0;
    } else {
      u_long maxSize;
      
      readLong(fd, &maxSize);
      currentTable = (ObjectStore *)calloc(maxSize, 1);
      Rewind(fd);
      readSome(fd, currentTable, maxSize);
      close(fd);
      INFO_PERSISTENCE(fprintf(output,"[setCurrentObjectStore(%d): used %d (%d) (%d%%)]\n", 
			       (int)(currentTable -> store),
			       (int)(currentTable -> nextFree),
			       (int)(currentTable -> maxSize),
			       (int)(currentTable -> nextFree * 100 / currentTable -> maxSize)));
      
      INFO_PERSISTENCE(numSL++);
    }
  } else {
    return 0;
  }
  return 1;
}

/* Allocates and inserts space for a new object in the current store */
StoreProxy *newStoreObject(Object *theObj)
{
  u_long size;
  
  Claim(theObj == getRealObject(theObj), "Trying to insert part object");
  
  size = 4*ObjectSize(theObj);
  
  if (currentTable) {
    if (size + currentTable -> nextFree < currentTable -> maxSize) {
      Object *nextObject;
      StoreProxy *sp = (StoreProxy *)malloc(sizeof(struct StoreProxy));
      
      Claim(theObj == getRealObject(theObj), "Unexpected part object");

      nextObject = (Object *)((u_long)currentTable + currentTable -> nextFree);
      memcpy(nextObject, theObj, size);
      sp -> store = currentTable -> store;
      sp -> offset = currentTable -> nextFree;
      currentTable -> nextFree += size;
      
      return sp;
    } 
    saveCurrentObjectStore();
    free(currentTable);
    currentTable = NULL;
  }
  
  /* There are no current store, or there is no room at the in. */
  
  {
    StoreID store;
    
    store = getNextStoreId();
    createObjectStore(store, size);
    createCrossStoreTable(store);
    
    return newStoreObject(theObj);
  }
}

Object *lookupStoreObject(StoreID store, u_long offset)
{
  if (currentTable) {
    if (compareStoreID(store, currentTable -> store)) {
      if (offset < currentTable -> nextFree) {
	currentTable -> lookupCount += 1;
	return (Object *)((u_long)currentTable + (u_long)offset);
      }
    }
  }
  
  return NULL;
}

/* Updates the Object in the current table */
int setStoreObject(StoreID store, u_long offset, Object *theObj)
{
  if (currentTable) {
    if (offset < currentTable -> nextFree) {
      Object *ObjectInStore;

      Claim(theObj == getRealObject(theObj), "Unexpected part object");
      ObjectInStore = (Object *)((u_long)currentTable + offset);
      memcpy(ObjectInStore, theObj, ObjectSize(theObj)*4);
      
      return 1;
    }
  }
  return 0;
}

#endif /* PERSIST */
