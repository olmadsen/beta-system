#include "objectStore.h"
#include "PStoreServer.h"
#include "PSfile.h"
#include "PStore.h"
#include "crossStoreTable.h"
#include "proto.h"

void os_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL TYPES */

typedef struct ObjectStore {
  unsigned long maxSize;        /* Space allocated for this store in bytes */
  unsigned long nextFree;       /* Offset of the next free entry in bytes */
  unsigned long lookupCount;    /* Number of times this block has been requested */
  BlockID store;         /* The id of the store belonging to this
			    ObjectStore */
  Object body[1];        /* The objects. */
} ObjectStore;

/* LOCAL VARIABLES */

static ObjectStore *currentTable = NULL;   /* The current table loaded */

#define BLOCKSINSTORE 1

/* LOCAL FUNCTION DECLARATIONS */
static int createObjectStore(BlockID store, unsigned long minSize);

/* IMPEMENTATION */
static int createObjectStore(BlockID store, unsigned long minSize)
{
  char *file_name;
  int fd;
  ObjectStore *newTable;
  unsigned long storeSize;
  
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
    if ((fd = open(file_name,O_RDWR | O_CREAT | _O_BINARY,
		   S_IWRITE | S_IREAD))<0) {
      perror("createObjectStore");
      
      return ILLEGALBlockID;
    } else {
      storeSize = preferredBufferSize(file_name) * BLOCKSINSTORE;
      
      while(storeSize < minSize) {
	storeSize = storeSize * 2;
      }
      
      newTable = (ObjectStore *)calloc(storeSize, 1);
      newTable -> maxSize = storeSize;
      newTable -> nextFree = (unsigned long)&(newTable -> body[0]) - (unsigned long)newTable;
      newTable -> lookupCount = 0;
      newTable -> store = store;
      
      writeSome(fd, newTable, newTable -> maxSize);
      close(fd);
      
      Claim(currentTable == NULL, "What is currentTable ?");
      currentTable = newTable;
      
      return store;
    }
  } else {
    return ILLEGALBlockID;
  }
  
  return ILLEGALBlockID;
}

int saveCurrentObjectStore()
{
  if (currentTable) {
    char *file_name;
    int fd;
    
    if ((file_name = objectStoreName(currentTable -> store))) {
      if ((fd = open(file_name,O_RDWR | _O_BINARY))<0) {
	perror("saveCurrentObjectStore");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      } else {
	writeSome(fd, currentTable, currentTable -> maxSize);
	close(fd);
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

int setCurrentObjectStore(BlockID store)
{
  char *file_name;
  int fd;

  if (currentTable) {
    if (compareBlockID(store, currentTable -> store)) {
      return 1;
    } else {
      saveCurrentObjectStore();
      free(currentTable);
      currentTable = NULL;
    }
  }
  
  if ((file_name = objectStoreName(store))) {
    if ((fd = open(file_name,O_RDWR | _O_BINARY))<0) {
      perror("setCurrentObjectStore");
      return 0;
    } else {
      unsigned long maxSize;
      
      readLong(fd, &maxSize);
      currentTable = (ObjectStore *)calloc(maxSize, 1);
      Rewind(fd);
      readSome(fd, currentTable, maxSize);
      close(fd);
      INFO_PERSISTENCE(numSL++);
    }
  } else {
    return 0;
  }
  
  return 1;
}

#ifdef RTINFO
void printObjectStoreStatistics(void)
{
  fprintf(output, "[ numSL: 0x%X]\n", (int)numSL);
}
#else
void printObjectStoreStatistics(void)
{
  ;
}
#endif /* RTINFO */

/* Allocates and inserts space for a new object in the current store */
StoreProxy *newStoreObject(Object *theObj)
{
  unsigned long size;
  
  Claim(theObj == getRealObject(theObj), "Trying to insert part object");
  
  size = 4*ObjectSize(theObj);
  
  if (currentTable) {
    if (size + currentTable -> nextFree < currentTable -> maxSize) {
      Object *nextObject;
      StoreProxy *sp = (StoreProxy *)malloc(sizeof(struct StoreProxy));
      
      Claim(theObj == getRealObject(theObj), "Unexpected part object");
      
      nextObject = (Object *)((unsigned long)currentTable + currentTable -> nextFree);
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
    BlockID store;
    
    store = getNextBlockID();
    createObjectStore(store, size);
    createCrossStoreTable(store);
    return newStoreObject(theObj);
  }
}

Object *lookupStoreObject(BlockID store, unsigned long offset)
{
  if (currentTable) {
    if (compareBlockID(store, currentTable -> store)) {
      if (offset < currentTable -> nextFree) {
	currentTable -> lookupCount += 1;
	return (Object *)((unsigned long)currentTable + (unsigned long)offset);
      }
    }
  }
  
  return NULL;
}

/* Updates the Object in the current table */
int setStoreObject(BlockID store, unsigned long offset, Object *theObj)
{
  if (currentTable) {
    if (offset < currentTable -> nextFree) {
      Object *ObjectInStore;
      
      Claim(theObj == getRealObject(theObj), "Unexpected part object");
      ObjectInStore = (Object *)((unsigned long)currentTable + offset);
      memcpy(ObjectInStore, theObj, ObjectSize(theObj)*4);
      
      /* Handle prototype */
      exportProtoTypes(ObjectInStore);
      
      return 1;
    }
  }
  
  return 0;
}

#endif /* PERSIST */
