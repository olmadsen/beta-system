#include "crossStoreTable.h"
#include "PStoreServer.h"
#include "PSfile.h"
#include "PStore.h"

void cst_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef nti
#include <unistd.h>
#endif
#include <errno.h>

/* Cross store references are handled by introducing proxy references
   at the store level. If an object in store A refers an object in
   store B, a proxy object will be created in store A. This proxy
   object will contain enough information to identify the referred
   object in store B. The proxy object in store A, will be placed in a
   special file. The reference from A to B will be replaced by a
   reference from A to the proxy object in A. Such a reference is
   called a store proxy reference. References to objects in the same
   store are simply byt offsets to the object in the store. In order
   to distinguish between in-store references and cross store
   references, cross store references are unaligned. */

/* LOCAL TYPES */

typedef struct crossStoreTable {
  unsigned long length;         /* Antries allocated in this table */
  unsigned long nextFree;       /* Index of the next free entry */
  BlockID store;         /* The id of the store belonging to this
			    StoreProxyTable */
  StoreProxy body[1];    /* The proxies */
} crossStoreTable;

/* LOCAL VARIABLES */

/* To achive effeciency we load an entire table into memory at a time */
static crossStoreTable *currentTable = NULL;   /* The current table loaded */

/* LOCAL FUNCTIONS */

/* LOCAL DEFINES */
#define MAP(inx) (MAXTYPE*inx  + CROSSSTORETYPE)     /* Turn inx into a cross store reference */
#define UNMAP(inx) ((inx - CROSSSTORETYPE)/MAXTYPE)  /* get the original value of inx */

#define tableSizeLength(length) (2*sizeof(unsigned long) + sizeof(BlockID) + length*sizeof(StoreProxy))
#define tableSize(table) tableSizeLength(table -> length)

/* FUNCTIONS */
  
BlockID createCrossStoreTable(BlockID store)
{
  char *file_name;
  int fd;
  crossStoreTable *newTable=(crossStoreTable *)calloc(sizeof(struct crossStoreTable), 1);

  newTable -> length = 1;
  newTable -> nextFree = 0;
  newTable -> store = store;
  
  if ((file_name = crossStoreTableName(store))) {
#ifdef nti
    if ((fd = open(file_name,O_RDWR | O_CREAT | _O_BINARY,
		   S_IWRITE | S_IREAD))<0) {
#endif
#ifdef UNIX
    if ((fd = open(file_name,O_RDWR | O_CREAT,
		   S_IWRITE | S_IREAD))<0) {
#endif
      perror("createCrossStoreTable");
      return ILLEGALBlockID;
    } else {
      writeSome(fd, newTable, tableSize(newTable));
      close(fd);
      if (currentTable) {
	saveCurrentCrossStoreTable();
	free(currentTable);
	currentTable = NULL;
      }
      currentTable = newTable;
      return store;
    }
  } else {
    return ILLEGALBlockID;
  }
  return ILLEGALBlockID;
}

BlockID getCurrentCrossStoreTable()
{
  if (currentTable) {
    return currentTable -> store;
  }
  
  return ILLEGALBlockID;
}

int saveCurrentCrossStoreTable()
{
  if (currentTable) {
    char *file_name;
    int fd;
    
    if ((file_name = crossStoreTableName(currentTable -> store))) {
#ifdef nti
      if ((fd = open(file_name,O_RDWR | _O_BINARY))<0) {
#endif
#ifdef UNIX
      if ((fd = open(file_name,O_RDWR))<0) {
#endif
	perror("saveCurrentCrossStoreTable");
	return 0;
      } else {
	writeSome(fd, currentTable, tableSize(currentTable));
	close(fd);
      }
    } else {
      return 0;
    }
  } else {
    return 0;
  }
  return 1;
}

int setCurrentCrossStoreTable(BlockID store)
{
  char *file_name;
  int fd;
  
  if (currentTable) {
    if (compareBlockID(store, currentTable -> store)) {
      return 1;
    } else {
      saveCurrentCrossStoreTable();
      free(currentTable);
      currentTable = NULL;
    }
  }
  
  if ((file_name = crossStoreTableName(store))) {
#ifdef nti
    if ((fd = open(file_name,O_RDWR | _O_BINARY))<0) {
#endif
#ifdef UNIX
    if ((fd = open(file_name,O_RDWR))<0) {
#endif
      perror("setCurrentCrossStoreTable");
      return 0;
    } else {
      unsigned long length;
      
      readLong(fd, &length);
      currentTable = (crossStoreTable *)calloc(tableSizeLength(length), 1);
      Rewind(fd);
      readSome(fd, currentTable, tableSizeLength(length));
      close(fd);
      INFO_PERSISTENCE(numCSL++);
    }
  } else {
    return 0;
  }
  return 1;
}

#ifdef RTINFO
void printCrossStoreStatistics(void)
{
  fprintf(output, "[ numCSL: 0x%X]\n", (int)numCSL);
}
#else
void printCrossStoreStatistics(void)
{
  ;
}
#endif /* RTINFO */

/* Allocates and inserts space for a new cross store reference in the
   current store. It checks for duplicates. */
unsigned long newStoreProxy(BlockID store,
		     unsigned long offset)
{
  if (currentTable) {
    unsigned long count;
    /* Check if a proxy to the same object is present allready */
    
    for (count = 0; count < currentTable -> nextFree; count++) {
      if (currentTable -> body[count].offset == offset) {
	if (compareBlockID(store, 
			   currentTable -> body[count].store)) {

	  Claim(isCrossStoreReference(MAP(count)), "newStoreProxy: Could not generate new proxy");

	  return MAP(count);
	}
      }
    }
    
    if (currentTable -> nextFree < currentTable -> length) {
      unsigned long nextFree;
      
      nextFree = currentTable -> nextFree;
      
      currentTable -> body[nextFree].store = store;
      currentTable -> body[nextFree].offset = offset;
      currentTable -> nextFree++;
      
      Claim(isCrossStoreReference(MAP(nextFree)), "newStoreProxy: Could not generate new proxy");

      return MAP(nextFree);
      
    } else {
      crossStoreTable *newTable;
      
      newTable = (crossStoreTable *)calloc(tableSizeLength((currentTable -> length) * 2), 1);
      memcpy(newTable, currentTable, tableSize(currentTable));
      newTable -> length = (currentTable -> length) * 2;
      free(currentTable);
      currentTable = newTable;
      
      return newStoreProxy(store, offset);
    }
  } else {
    return ILLEGALBlockID;
  }
}

/* Looks up the proxy object in the current table */
StoreProxy *lookupStoreProxy(unsigned long inx) 
{
  if (currentTable) {
    if (UNMAP(inx) < currentTable -> nextFree) {
      return &(currentTable -> body[UNMAP(inx)]);
    }
  }
  return ILLEGALSTOREPROXY;
}

#endif /* PERSIST */
