#include "PStore.h"
#include "misc.h"
#include "PSfile.h"
#include "PStoreServer.h"
#include "proto.h"

void pstore_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

/* LOCAL CONSTANTS */

#define INITIALBLOCKSINSTORE 0x800

#define storeSize(PStore) (PStore -> headerSize + PStore -> maxNumBlocks * PStore -> blockSize)
#define blockContainingOffset(offset) (offset / (currentPStore -> blockSize))
#define blockOffset(offset) (offset % (currentPStore -> blockSize))
#define endOfBlock(blockNum) ((currentPStore -> blockSize) * (blockNum + 1))

typedef struct PStoreHeader {
  unsigned long headerSize;        /* Size in bytes of this header */
  unsigned long maxNumBlocks;      /* This store holds a max of so many blocks */
  unsigned long blockSize;         /* Size of each block in bytes */
  
  unsigned long storeID;           /* ID of this store */

  nameMapEntry nameMap[MAXNAMES];
  unsigned long topBlock;          
  unsigned long nextFree;          /* Offset to next free byte within
				      the top block */

  unsigned long crossTop;          /* Offset to next free byte for
				      holding cross store proxies,
				      grows downwards. */
  unsigned long startMarkers[1];   /* */
} PStoreHeader;

/* LOCAL VARIABLES */
static PStoreHeader *currentPStore = NULL;
static int currentFd = -1;
static char *currentBlock = NULL;
static unsigned long currentBlockStart = -1, currentBlockEnd = -1;
static unsigned long touched = 0;

/* LOCAL FUNCTION DECLARATIONS */
static void markStartBlock(unsigned long blockNo);
static unsigned long isStartBlock(unsigned long blockNo);
static void saveCurrentBlock(void);
static unsigned long ensureBlock(unsigned long blockNo);

/* FUNCTIONS FOR HANDLING STARTMARKERS */
#define sizeOfStartMarkers(entries) ((entries / (sizeof(unsigned long) * 8)) + 1)

void getNameMap(void **nameMap)
{
  *nameMap = &(currentPStore -> nameMap[0]);
}

unsigned long getCurrentStoreID(void)
{
  return currentPStore -> storeID;
}

static void markStartBlock(unsigned long blockNo)
{
  unsigned long word, bit, pattern;
  
  word = blockNo / 32;
  bit = blockNo % 32;
  
  pattern = currentPStore -> startMarkers[word];
  pattern = pattern | (1 << bit);
  currentPStore -> startMarkers[word] = pattern;
}

static unsigned long isStartBlock(unsigned long blockNo)
{
  unsigned long word, bit, pattern;
  
  word = blockNo / 32;
  bit = blockNo % 32;
  
  pattern = currentPStore -> startMarkers[word];
  return ((pattern & (1 << bit)) > 0);
}
  
/* FUNCTIONS FOR HANDLING CURRENT LOADED BLOCK */
static void saveCurrentBlock(void)
{
  if (currentPStore) {
    if (touched) {
      windTo(currentFd, currentPStore -> headerSize + currentBlockStart * currentPStore -> blockSize);
      writeSome(currentFd, 
		currentBlock, 
		(currentBlockEnd - currentBlockStart + 1) * currentPStore -> blockSize);
    }
  }
}

static unsigned long ensureBlock(unsigned long blockNo)
{
  unsigned long delta, blockStart, blockEnd;
  
  Claim(blockNo < currentPStore -> maxNumBlocks, "ensureBlock: blockNo oub");
  
  delta = 0;
  while (!isStartBlock(blockNo)) {
    Claim(blockNo != -1, "ensureBlock: blockNo oub");
    delta++;
    blockNo--;
  }
  
  blockStart = blockNo - delta;
  blockEnd = blockNo;
  
  if (!((blockStart == currentBlockStart) && (blockEnd == currentBlockEnd))) {
    if (currentBlock) {
      saveCurrentBlock();
      free(currentBlock);
      currentBlock = NULL;
    }
    
    currentBlock = (char *)malloc(sizeof(char)*((delta + 1) * currentPStore -> blockSize));
    windTo(currentFd, currentPStore -> headerSize + blockStart * currentPStore -> blockSize);
    readSome(currentFd, currentBlock, ((delta + 1) * currentPStore -> blockSize));
    currentBlockStart = blockStart;
    currentBlockEnd = blockEnd;
    touched = 0;
  }
  
  return delta;
}

/* FUNCTIONS */
int createPStore(unsigned long storeID)
{
  char *file_name;
  unsigned long headerSize;
  
  if (currentPStore) {
    saveCurrentStore();
    free(currentPStore);
    currentPStore = NULL;
  }

  /* Creates a new store on disk */
  headerSize = 
    sizeof(struct PStoreHeader) + 
    sizeof(unsigned long) * (sizeOfStartMarkers(INITIALBLOCKSINSTORE) - 1);

  currentPStore = (PStoreHeader *)calloc(headerSize, 1);
  
  currentPStore -> headerSize = headerSize;
  currentPStore -> maxNumBlocks = INITIALBLOCKSINSTORE;
  currentPStore -> storeID = storeID;
  currentPStore -> topBlock = 0;
  /* We do not want any zero offsets, as this might produce none
     references other places */
  currentPStore -> nextFree = 8;
  
  markStartBlock(currentPStore -> topBlock);
  
  if ((file_name = objectStoreName(storeID))) {
    if ((currentFd = open(file_name,O_RDWR | O_CREAT
#ifdef nti
			  | _O_BINARY
#endif
			  , S_IWRITE | S_IREAD))<0) {
      perror("createObjectStore");
      return -1;
    } else {
      currentPStore -> blockSize = preferredBufferSize(currentFd);
      currentPStore -> crossTop = storeSize(currentPStore);
      writeSome(currentFd, currentPStore, currentPStore -> headerSize);
      return storeID;
    }
  } else {
    return -1;
  }
  return storeID;
}
  
void saveCurrentStore(void)
{
  if (currentPStore) {
    saveCurrentBlock();
    Rewind(currentFd);
    writeSome(currentFd, currentPStore, currentPStore -> headerSize);
  }
}

void closeCurrentStore(void)
{
  close(currentFd);
  currentFd = -1;
  if (currentPStore) {
    free(currentPStore);
    currentPStore = NULL;
  }
}

int setCurrentPStore(unsigned long storeID)
{
  char *file_name;
  /* Assuming that the store has been created */
  
  if (currentPStore) {
    if (compareStoreID(storeID, currentPStore -> storeID)) {
      return 1;
    } else {
      saveCurrentStore();
      close(currentFd);
      currentFd = -1;
      free(currentPStore);
      currentPStore = NULL;
    }
  }
  
  if ((file_name = objectStoreName(storeID))) {
    if ((currentFd = open(file_name,O_RDWR 
#ifdef nti
		   | _O_BINARY
#endif /* nti */
		   ))<0) {
      perror("setCurrentPStore");
      Claim(FALSE, "setCurrentPStore: Failed");
      return 0;
    } else {
      unsigned long headerSize;
      
      readLong(currentFd, &headerSize);
      currentPStore = (PStoreHeader *)malloc(headerSize);
      Rewind(currentFd);
      readSome(currentFd, currentPStore, headerSize);
    }
  } else {
    return 0;
  }
  return 1;
}

static void realloStore(void)
{
  if (currentPStore -> crossTop == storeSize(currentPStore)) {
    /* No cross store references has been added, so the store can be
       enlarged without any copying. */
    fprintf(output, "realloStore: NIY");
    BetaExit(1);
    
  } else {
    fprintf(output, "realloStore: NIY");
    BetaExit(1);
  }
}

StoreProxy *allocateObject(unsigned long size)
{
  StoreProxy *sp = (StoreProxy *)malloc(sizeof(struct StoreProxy));
  sp -> storeID = currentPStore -> storeID;
  
  if (currentPStore) {
    if (size + currentPStore -> nextFree < currentPStore -> blockSize) {
      /* There is still room in the last block */
      sp -> offset = 
	(currentPStore -> topBlock * currentPStore -> blockSize) + currentPStore -> nextFree;
      
      currentPStore -> nextFree += size;
      
    } else {
      unsigned long blocks, bytes;
      
      blocks = size / currentPStore -> blockSize;
      bytes = size % currentPStore -> blockSize;
      
      currentPStore -> topBlock += 1;
      markStartBlock(currentPStore -> topBlock);
      
      sp -> offset = (currentPStore -> topBlock * currentPStore -> blockSize);
      
      currentPStore -> topBlock += blocks;
      currentPStore -> nextFree = bytes;
      
      /* The new object requires the allocation of 'blocks' new
         blocks. We need to check if there is still space in the
         store. */
      
      while (endOfBlock(currentPStore -> topBlock) >=  currentPStore -> crossTop) {
	realloStore();
      }
    }
  } else {
    return NULL;
  }
  return sp;
}

void printObjectStoreStatistics(void)
{
  ;
}

Object *lookupStoreObject(unsigned long storeID, unsigned long offset)
{
  if (currentPStore) {
    if (compareStoreID(storeID, currentPStore -> storeID)) {
      if (blockContainingOffset(offset) < currentPStore -> maxNumBlocks) {
	if (blockOffset(offset) < currentPStore -> blockSize) {
	  unsigned long delta;
	  
	  delta = ensureBlock(blockContainingOffset(offset));
	  
	  return (Object *)((unsigned long)currentBlock + 
			    (unsigned long)blockOffset(offset) +
			    delta * (currentPStore -> blockSize));
	}
      }
    }
  }
  return NULL;
}

int setStoreObject(unsigned long storeID, unsigned long offset, Object *theObj)
{
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  if (currentPStore) {
    if (compareStoreID(storeID, currentPStore -> storeID)) {
      if (blockContainingOffset(offset) < currentPStore -> maxNumBlocks) {
	if (blockOffset(offset) < currentPStore -> blockSize) {
	  Object *ObjectInStore;
	  unsigned long delta;
	  
	  delta = ensureBlock(blockContainingOffset(offset));
	  
	  Claim(delta == 0, "setStoreObject: Unexpected delta");
	  
	  ObjectInStore = (Object *)((unsigned long)currentBlock + 
				     (unsigned long)blockOffset(offset) +
				     delta * (currentPStore -> blockSize));
	  
	  memcpy(ObjectInStore, 
		 theObj, 
		 ObjectSize(theObj)*4);
	  
	  touched = 1;
	  /* Handle prototype */
	  exportProtoTypes(ObjectInStore);
	  return 1;
	}
      }
    }
  }
  return -1;
}

unsigned long newPProxy(unsigned long storeID,
			unsigned long offset)
{
  Claim(FALSE, "newPProxy: NIY");
  return 0;
}

StoreProxy *lookupStoreProxy(unsigned long inx)
{
  Claim(FALSE, "newPProxy: NIY");
  return NULL;
}

int compareStoreID(unsigned long a, unsigned long b)
{
  return a == b;
}

#endif /* PERSIST */
