#include "PStore.h"
#include "misc.h"
#include "PSfile.h"
#include "PStoreServer.h"
#include "proto.h"
#include "crossStoreReferences.h"

#ifdef PERSIST

#ifdef nti
#include <io.h>
#include <direct.h>
#endif

/* LOCAL CONSTANTS */

#define INITIALBLOCKSINSTORE 0x800

#define storeSize(PStore) (PStore -> headerSize + PStore -> maxNumBlocks * PStore -> blockSize)
#define blockContainingOffset(offset) (offset / (currentPStore -> blockSize))
#define blockOffset(offset) (offset % (currentPStore -> blockSize))
#define endOfBlock(blockNum) ((currentPStore -> blockSize) * (blockNum + 1))

#define WRITESOME(a,b,c) {                                        \
                           currentPStore -> numberOfUpdates += 1; \
			   writeSome(a,b,c);                      \
			 }
/* LOCAL VARIABLES */
static unsigned long currentStoreID = -1; /* The context local ID of
					     the store currrently loaded */
static int currentFd = -1;
static char *currentBlock = NULL;
static unsigned long currentBlockStart = -1, currentBlockEnd = -1;
static unsigned long touched = 0;
static StoreProxy sp;

/* GLOBAL VARIABLES */
PStoreHeader *currentPStore = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static void markStartBlock(PStoreHeader *PStore, unsigned long blockNo);
static unsigned long isStartBlock(unsigned long blockNo);
static void saveCurrentBlock(void);
static unsigned long ensureBlock(unsigned long blockNo);
static void insertReferredStore(char *host, char *path, PStoreHeader *storeHeader);

/* FUNCTIONS FOR HANDLING NAMING STORES */
static void insertReferredStore(char *host, char *path, PStoreHeader *storeHeader)
{
  if (storeHeader -> referredStores.top < storeHeader -> referredStores.size) {
    storeLocation *theLocation;
    
    theLocation = &(storeHeader -> referredStores.locations[storeHeader -> referredStores.top]);
    if (host) {
      if (strlen(host) < MAXHOSTNAMELENGTH) {
	sprintf(&(theLocation -> host[0]), "%s", host);
      } else {
	fprintf(output, "insertReferredStore: Host name too long (%s). Only %d characters allowed\n", host, MAXHOSTNAMELENGTH);
	BetaExit(1);
      }
    } else {
      fprintf(output, "insertReferredStore: NULL host name\n");
      BetaExit(1);
    }
    
    if (path) {
      if (strlen(path) < MAXPATHNAMELENGTH) {
	sprintf(&(theLocation -> path[0]), "%s", path);
      } else {
	fprintf(output, "insertReferredStore: Path name too long (%s). Only %d characters allowed\n", path, MAXPATHNAMELENGTH);
	BetaExit(1);
      }
    } else {
      fprintf(output, "insertReferredStore: NULL path name\n");
      BetaExit(1);
    }
    
    /* New store inserted */
    storeHeader -> referredStores.top = storeHeader -> referredStores.top + 1;
    
  } else {
    fprintf(output, "insertReferredStore: Out of space to hold referred stores.\n  Only %d referred stores allowed.\n  Reallocation needed but not implemented\n", (int)(storeHeader -> referredStores.size));
    BetaExit(1);
  }
}

static unsigned long lookupReferredStore(char *host, char *path, PStoreHeader *storeHeader)
{
  unsigned long count;

  if (path) {
    if (strlen(path) >= MAXPATHNAMELENGTH) {
      fprintf(output, "lookupReferredStore: Path name too long (%s). Only %d characters allowed\n", path, MAXPATHNAMELENGTH);
      BetaExit(1);
    }
  } else {
    fprintf(output, "lookupReferredStore: NULL path name\n");
    BetaExit(1);
  }
  
  for (count = 0; count < storeHeader -> referredStores.top; count++) {
    storeLocation *theLocation;
    
    theLocation = &(storeHeader -> referredStores.locations[count]);
    if (strcmp(&(theLocation -> path[0]), path) == 0) { 
      return count + 1;
    }
  }
  return -1;
}

/* FUNCTIONS FOR HANDLING ROOT NAMES */
unsigned long getRootOffset(unsigned long storeID, 
			    char *name)
{
  unsigned long count;
  nameMapEntry *current;
  
  Claim(currentPStore != NULL, "getRootName: currentPStore is NULL");
  if (currentStoreID == storeID) {
    for (count = 0; count < MAXNAMES; count++) {
      current = &(currentPStore -> nameMap[count]);
      if (strcmp(name, &(current -> name[0])) == 0) {
	return current -> offset;
      }
    }
    return -1;
  } else {
    setCurrentPStore(storeID);
    return getRootOffset(storeID, name);
  }
}

void insertRoot(unsigned long storeID, 
		char *name, 
		unsigned long offset)
{
  unsigned long count;
  nameMapEntry *current;
  
  Claim(currentPStore != NULL, "getRootName: currentPStore is NULL");
  if (currentStoreID == storeID) {
    for (count = 0; count < MAXNAMES; count++) {
      current = &(currentPStore -> nameMap[count]);
      if (current -> name[0] == '\0') {
	if (strlen(name) < MAXNAMELENGTH) {
	  sprintf(&(current -> name[0]), "%s", name);
	  current -> offset = offset;
	  return;
	} else {
	  fprintf(output, "insertRoot: Name too long (%s), only %d characters allowed\n",
		  name,
		  (int)(MAXNAMELENGTH));
	  BetaExit(1);
	}
      } else {    
	if (strcmp(name, &(current -> name[0])) == 0) {
	  current -> offset = offset;
	  return;
	}
      }
    }
    
    fprintf(output, "insertRoot: Too many root names, only %d allowed\n", 
	    (int)(MAXNAMES));
    BetaExit(1);
  } else {
    setCurrentPStore(storeID);
    insertRoot(storeID, name, offset);
  }
}

/* FUNCTIONS FOR HANDLING STARTMARKERS */
#define sizeOfStartMarkers(entries) ((entries / (sizeof(unsigned long) * 8)) + 1)

static void markStartBlock(PStoreHeader *PStore, unsigned long blockNo)
{
  unsigned long word, bit, pattern;
  
  word = blockNo / 32;
  bit = blockNo % 32;
  
  pattern = PStore -> startMarkers[word];
  pattern = pattern | (1 << bit);
  PStore -> startMarkers[word] = pattern;
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
      WRITESOME(currentFd, 
		currentBlock, 
		(currentBlockEnd - currentBlockStart + 1) * currentPStore -> blockSize);
    }
  }
}

static unsigned long ensureBlock(unsigned long blockNo)
{
  static unsigned long currentBlockSize = 0;
  unsigned long delta, blockStart, blockEnd;
  unsigned long size;

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
    size = (delta + 1) * currentPStore->blockSize;
    if (currentBlock) {
      saveCurrentBlock();
      if (currentBlockSize < size) {
	free(currentBlock);
	currentBlock = NULL;
      }
    }
    if (!currentBlock) {
      currentBlock = (char *)malloc(size);
      memset(currentBlock, 0, size);
      currentBlockSize = size;
    }
    windTo(currentFd, currentPStore->headerSize + 
	   blockStart * currentPStore->blockSize);
    readSome(currentFd, currentBlock, (delta + 1) * currentPStore->blockSize);
    currentBlockStart = blockStart;
    currentBlockEnd = blockEnd;
    touched = 0;
  }
  return delta;
}

/* FUNCTIONS */
static PStoreHeader *newStore(char *host, char *path)
{
  PStoreHeader *new;
  unsigned long headerSize;
  char *file_name;

  headerSize = 
    sizeof(struct PStoreHeader) + 
    sizeof(unsigned long) * (sizeOfStartMarkers(INITIALBLOCKSINSTORE) - 1);
  
  new = (PStoreHeader *)calloc(headerSize, 1);

  /* The static parts of a store header are the 'referredStores' and
     the 'nameMap', the latter containing the root names into this
     store. Both have now been allocated. */
  new -> numberOfUpdates = 0;
  new -> referredStores.size = INITIALNUMLOCATIONS;
  
  new->protoNames.size = INITIALPROTONAMEBUFFERSIZE;
  new->protoNames.top = 0;
  memset(new->protoNames.names, 0, new->protoNames.size);

  new -> headerSize = headerSize;
  new -> maxNumBlocks = INITIALBLOCKSINSTORE;
  /* new -> blockSize will be set below */
  /* new -> topBlock is implicitly set to 0 */
  /* We do not want any zero offsets, as this might produce none
     references other places */
  new -> nextFree = 8;
  /* new -> crossStoreTop will be set below */
  markStartBlock(new, new -> topBlock);
  
  /* To allow objects in this store to refer to other objects in the
     same store the name of the store must be inserted in the list of
     referred stores */
  insertReferredStore(host, path, new);
  
  /* The file is created. For now only 'path' is used. */
  if ((file_name = path)) {
    /* Create directory */
    if (!isDir(file_name)) {
      if (mkdir(file_name
#ifdef UNIX
		, S_IFDIR | S_IREAD | S_IWRITE | S_IEXEC 
#endif
		) < 0) 
	{
	  perror("newStore");
	  free(new);
	  return NULL;
	} 
    }
    if ((currentFd = open(DBname(file_name),O_RDWR | O_CREAT
#ifdef nti
			  | _O_BINARY
#endif
			  , S_IWRITE | S_IREAD))<0) {
      perror("newStore");
      free(new);
      return NULL;
    } else {
      new -> blockSize = preferredBufferSize(currentFd);
      new -> crossStoreTop = storeSize(new);
      /* Ensure that the offset of the next proxy is 8 byte alligned
	 (more comments regarding this issue is available below in
	 'newPProxy') */
      while(new -> crossStoreTop % MAXTYPE != 0) {
	new -> crossStoreTop = new -> crossStoreTop - 1;
      }
    }
  } else {
    free(new);
    return NULL;
  }
  return new;
}

int createPStore(char *host, char *path)
{
  if (currentPStore) {
    saveCurrentStore();
    closeCurrentStore();
  }
  /* Creates a new store on disk */
  if ((currentPStore = newStore(host, path))) {
    /* We have an open store and we should notify the store manager so
       he might give it a context local id. */
    currentStoreID = registerNewStore(host, path);
    
    /* The file on disk is updated */
    WRITESOME(currentFd, currentPStore, currentPStore -> headerSize);
    
    return currentStoreID;
  } else {
    return 0;
  }
}
  
void saveCurrentStore(void)
{
  saveStore(currentStoreID);
}

void closeCurrentStore(void)
{
  closeStore(currentStoreID);
}

void saveStore(unsigned long storeID)
{
  /* Updates information on disk */
  if (currentPStore) {
    if (currentStoreID == storeID) {
      saveCurrentBlock();
      Rewind(currentFd);
      WRITESOME(currentFd, currentPStore, currentPStore -> headerSize);
    }
  }
}

void closeStore(unsigned long storeID)
{
  if (storeID == currentStoreID) {
    close(currentFd);
    currentFd = -1;
    currentBlock = NULL;
    currentBlockStart = -1;
    currentBlockEnd = -1;
    touched = 0;
    if (currentPStore) {
      free(currentPStore);
      currentPStore = NULL;
      currentStoreID = -1;
    }
  }
}

OURINLINE int setCurrentPStore(unsigned long storeID)
{
  storeLocation *sl;
  
  if (currentPStore) {
    if (currentStoreID == storeID) {
      return 1;
    } else {
      saveCurrentStore();
      closeCurrentStore();
    }
  }
  
  if (storeIsOpen(storeID)) {
    if ((sl = IDToName(storeID))) {
      if ((currentFd = open(DBname(sl -> path), O_RDWR 
#ifdef nti
			    | _O_BINARY
#endif /* nti */
			    )) < 0) {
	perror("setCurrentPStore");
	Claim(FALSE, "setCurrentPStore: Failed");
	return 0;
      } else {
	unsigned long headerSize;
	
	readLong(currentFd, &headerSize);
	currentPStore = (PStoreHeader *)malloc(headerSize);
	Rewind(currentFd);
	readSome(currentFd, currentPStore, headerSize);
	currentStoreID = storeID;
      }
    } else {
      fprintf(output, "setCurrentPStore: Failed to look up store id (%d)\n", (int)(storeID));
      return 0;
    }
  } else {
    /* The store is not open. This is an error at this point. */
    fprintf(output, "setCurrentPStore: Attempting access to closed store\n");
    fflush(output);
    return 0;
  }
  return 1;
}

StoreProxy *allocateObject(unsigned long storeID,
			   unsigned long size)
{
  /* Allocates an object in the store with context local store id
     eq. storeID */
  
  if (storeIsOpen(storeID)) {
    if (currentPStore) {
      if (storeID == currentStoreID) {
	sp.storeID = currentStoreID;
	if (size + currentPStore -> nextFree < currentPStore -> blockSize) {
	  /* There is still room in the last block */
	  sp.offset = 
	    (currentPStore -> topBlock * currentPStore -> blockSize) + currentPStore -> nextFree;
	  /* The offset does not include the store header */
	  currentPStore -> nextFree += size;
	  
	} else {
	  unsigned long blocks, bytes;
	  
	  blocks = size / currentPStore -> blockSize;
	  bytes = size % currentPStore -> blockSize;
	  
	  currentPStore -> topBlock += 1;
	  markStartBlock(currentPStore, currentPStore -> topBlock);
	  
	  sp.offset = (currentPStore -> topBlock * currentPStore -> blockSize);
	  
	  currentPStore -> topBlock += blocks;
	  currentPStore -> nextFree = bytes;
	}
      } else {
	setCurrentPStore(storeID);
	return allocateObject(storeID, size);
      }
    } else {
      return NULL;
    }
    return &sp;
  } else {
    storeLocation *sl;
    
    sl = IDToName(storeID);
    
    fprintf(output, 
	    "allocateObject: Trying to allocate new object in store\n"
	    "  that has been closed. Please defer closing of store\n\n"
	    "    [%s]\n\n"
	    "  until a later time. The update has been forced, even though\n"
	    "  store is closed.\n",
	    &(sl -> path[0]));
    markStoreAsOpen(storeID);
    return allocateObject(storeID, size);
  }
}

void printObjectStoreStatistics(void)
{
  ;
}

Object *lookupStoreObject(unsigned long storeID, 
			  unsigned long offset)
{
  if (currentPStore) {
    if (storeID == currentStoreID) {
      if (blockContainingOffset(offset) < currentPStore -> maxNumBlocks) {
	if (blockOffset(offset) < currentPStore -> blockSize) {
	  unsigned long delta;
	  
	  delta = ensureBlock(blockContainingOffset(offset));
	  
	  return (Object *)((unsigned long)currentBlock + 
			    (unsigned long)blockOffset(offset) +
			    delta * (currentPStore -> blockSize));
	} else {
	  Claim(FALSE, "lookupStoreObject: Illegal offset");
	  return NULL;
	}
      } else {
	Claim(FALSE, "lookupStoreObject: Illegal offset");
	return NULL;
      }
    } else {
      setCurrentPStore(storeID);
      return lookupStoreObject(storeID, offset);
    }
  }
  return NULL;
}

int setStoreObject(unsigned long storeID, 
		   unsigned long offset, 
		   Object *theObj)
{
  Claim(theObj == getRealObject(theObj), "Unexpected part object");
  
  if (currentPStore) {
    if (storeID == currentStoreID) {
      if (blockContainingOffset(offset) < currentPStore -> maxNumBlocks) {
	if (blockOffset(offset) < currentPStore -> blockSize) {
	  Object *ObjectInStore;
	  unsigned long delta;
	  
	  delta = ensureBlock(blockContainingOffset(offset));
	  
	  Claim(delta == 0, "setStoreObject: Unexpected delta");
	  
	  ObjectInStore = (Object *)((unsigned long)currentBlock + 
				     (unsigned long)blockOffset(offset) +
				     delta * (currentPStore -> blockSize));
	  
	  Claim((long)blockOffset(offset)+ObjectSize(theObj)*4
		< (long)currentPStore->blockSize, 
		"Object is too large, it spans into the next block");

	  memcpy(ObjectInStore, 
		 theObj, 
		 ObjectSize(theObj)*4);
	  
	  touched = 1;
	  /* Handle prototype */
	  exportProtoTypes(ObjectInStore);
	  return 1;
	} else{
	  Claim(FALSE, "setStoreObject: Illegal offset");
	  return -1;
	}
      } else {
	Claim(FALSE, "setStoreObject: Illegal offset");
	return -1;
      }
    } else {
      /* Change store */
      Claim(FALSE, "setStoreObject: NIY");
      return -1;
    }
  }
  return -1;
}

unsigned long newPProxy(unsigned long storeContainingProxy,
			unsigned long storeID,
			unsigned long offset)
{
  unsigned long insertPoint, storeLocalID;
  storeLocation *sl;
  
  /* This function will return an offset to a proxy object in the
     current store. In order to distinguish such references from
     normal references the reference is tagged. Normal references are
     all divisible by 8 since the smallet beta object is 8 bytes long
     and larger objects have sizes that are multiples of 8. Proxies
     themselves are 2 unsigned long integers. Currently this is also 8
     bytes. This gives us the option of tagging references in 7
     different kinds of ways. Currently only two are used: Special
     object references and cross store references. */
  
  Claim(currentPStore != NULL, "newPProxy: currentPStore not set");
  Claim(storeID != currentStoreID, "newPProxy: creating proxy into self");
  Claim(sizeof(struct StoreProxy) % MAXTYPE == 0, "newPProxy: Illegal size of struct proxy");
  
  if (storeContainingProxy == currentStoreID) {
    /* An object in the current store is referring an object in another
       store and we need to create a proxy for this reference. */
    
    /* First the storeID must be translated into an offset in the
       referredStores array */
    sl = IDToName(storeID);
    if ((storeLocalID = lookupReferredStore(sl -> host, sl -> path, currentPStore)) != -1) {
      /* Check if there is room enough for the proxy */
      insertPoint = currentPStore -> crossStoreTop - sizeof(struct StoreProxy);
      if (insertPoint > (currentPStore -> topBlock + 1) * currentPStore -> blockSize) {
	Claim(currentFd != -1, "newPProxy: currentFd uninitialized");
	windTo(currentFd, insertPoint);
	WRITESOME(currentFd, &storeLocalID, sizeof(unsigned long));
	WRITESOME(currentFd, &offset, sizeof(unsigned long));
	currentPStore -> crossStoreTop = insertPoint;
	
	Claim(insertPoint % MAXTYPE == 0, 
	      "newPProxy: Illegal proxy offset");
	insertPoint += CROSSSTORETYPE;
	Claim(isCrossStoreReference(currentStoreID, 
				    insertPoint), 
	      "newPProxy: Illegal cross store ref created");
	
	return insertPoint;
      } else {
	/* Realloc needed */
	fprintf(output, "newPProxy: Reallocation of store needed but not implemented\n");
	BetaExit(1);
      }
    } else {
      /* This is the first time that a proxy to 'sl' is to be inserted
         in this store. Thus we must register 'sl' as a store referred
         from this store. */
      insertReferredStore(sl -> host, sl -> path, currentPStore);
      return newPProxy(storeContainingProxy,
		       storeID,
		       offset);
    }
  } else {
    setCurrentPStore(storeID);
    return newPProxy(storeContainingProxy,
		     storeID,
		     offset);
  }
  return -1;
}

unsigned long getNumberOfUpdates(unsigned long host_r, 
				 unsigned long path_r)
{
  unsigned long storeID, num = 0;
  char *host, *path;
  
  Claim(host_r != 0, "getNumberOfUpdates: host is NULL");
  Claim(path_r != 0, "getNumberOfUpdates: host is NULL");
  
  host = getBetaText(host_r);
  path = getBetaText(path_r);
  
  if ((storeID = nameToID(host, path)) != -1) {
    if (currentStoreID == storeID) {
      num = currentPStore -> numberOfUpdates;
    } else {
      setCurrentPStore(storeID);
      return getNumberOfUpdates(host_r, path_r);
    }
  } else {
    fprintf(output, "getNumberOfUpdates: Could not get storeId for %s, %s\n", host, path);
    BetaExit(1);
  }
  free(host); free(path);
  return num;
}
 
StoreProxy *lookupStoreProxy(unsigned long storeID, 
			     unsigned long inx)
{
  char *host, *path;
 
  /* 'storeID'

     Is the context local store ID of the store containing the proxy.
     
     'inx'
     
     Is the offset of the proxy in the store.
  */
  
  Claim(currentPStore != NULL, "lookupStoreProxy: currentPStore not set");
  Claim(isCrossStoreReference(storeID, inx), 
	"lookupStoreProxy: inx is not a cross store ref");
  /* Remove the cross store tag */
  inx = inx - CROSSSTORETYPE;
  if (currentStoreID == storeID) {
    windTo(currentFd, inx);
    readSome(currentFd, &sp, sizeof(struct StoreProxy));
    
    /* Translate the local store id into a context local ID */
    path = &(currentPStore -> referredStores.locations[sp.storeID - 1].path[0]);
    host = &(currentPStore -> referredStores.locations[sp.storeID - 1].host[0]);
    
    sp.storeID = nameToID(host, path);
    return &sp;
  } else {
    setCurrentPStore(storeID);
    return lookupStoreProxy(storeID, inx);
  }
}

#endif /* PERSIST */
