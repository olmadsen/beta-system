#include "beta.h"

void sto_dummy() {
  USE();
}

#ifdef PERSIST
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#ifdef RTINFO
extern u_long numPersistentBlocks;
extern u_long numObjects;
extern u_long sizeOfObjects;
#endif /* RTINFO */

extern void (*objectAction)(Object *theObj);

#define SMALLTEXTSIZE 512

/* TYPES */
typedef struct _rootMapCell {
  char name[SMALLTEXTSIZE];
  /* proxy attributes */
  void *dummy;               /* ? */
  long GCAttr;
  long id;                   /* Id of block in store */
  long offset;               /* Offset of object in block */
} rootMapCell;

void unswizzleOrigins(Block *b);

static long nextStoreId = 1;
static char *storeOfProcess = "st1";
static int permission;

void putName(char *name,   
	     void *dummy,
	     long GCAttr,
	     long id,    
	     long offset)
{
  rootMapCell *nameMap;
  u_long size;
  char file_name[SMALLTEXTSIZE];
  int fd;
  int nb;
  
  if (permission == S_IWRITE) {
    
    /* Loads the name map of this store and extendes it with the new
     * name */
    
    sprintf(file_name, "%s/nameMap.info", getStoreOfProcess());
    if ((fd = open(file_name,O_RDWR))<0) {
      perror("putName");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
    
    if ((nb = read(fd, &size, sizeof(u_long))) < 0) {
      perror("putName");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
    
    if (nb != sizeof(u_long)) {
      fprintf(output, "putName: Could not load size of name map\n");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
    
    nameMap = (rootMapCell *)calloc(size, 1);
    
    if ((nb = read(fd, nameMap, size)) < 0) {
      perror("getName");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
    
    if (nb != size) {
      fprintf(output, "getName: Could not load name map\n");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
    
    /* Search if name is their allready */
    { 
      u_long count;
      u_long found = FALSE;
      
      for (count=0; count< size / sizeof(struct _rootMapCell); count++) {
	if (strcmp(nameMap[count].name, name) == 0) {
	  /* replace existing name */
	  nameMap[count].dummy = dummy;
	  nameMap[count].GCAttr = GCAttr;
	  nameMap[count].id = id;
	  nameMap[count].offset = offset;
	  found = TRUE;
	  break;
	}
      }
      
      if (!found) {
	rootMapCell new;

	memset(&new, 0, sizeof(struct _rootMapCell));

	if (lseek(fd, 0, SEEK_SET) < 0) {
	  perror("putName");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
	
	size += sizeof(struct _rootMapCell);
	
	if ((nb = write(fd, &size, sizeof(u_long))) < 0) {
	  perror("putName");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
	
	if (nb != sizeof(u_long)) {
	  fprintf(output, "putName: Could not write new size of name map\n");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
	
	/* Append new mapping */
	sprintf(&new.name[0], "%s", name);
	new.dummy = dummy;
	new.GCAttr = GCAttr;
	new.id = id;
	new.offset = offset;
	
	/* write new mapping to store */
	if (lseek(fd, sizeof(u_long) + size - sizeof(struct _rootMapCell), SEEK_SET) < 0) {
	  perror("putName");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
	
	if ((nb = write(fd, &new, sizeof(struct _rootMapCell))) < 0) {
	  perror("putName");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
      } else {
	/* name was their and have been replaced */

	if (lseek(fd, sizeof(u_long), SEEK_SET) < 0) {
	  perror("putName");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}

	if ((nb = write(fd, nameMap, size)) < 0) {
	  perror("putName");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
	
	if (nb != size) {
	  fprintf(output, "putName: Could not append to name map\n");
	  DEBUG_CODE(Illegal());
	  BetaExit(1);
	}
      }
    }
    
    free(nameMap);
    close(fd);
  }
}

void getName(char *name,   
	     void **dummy,
	     long *GCAttr,
	     long *id,    
	     long *offset)
{
  rootMapCell *nameMap;
  u_long size;
  char file_name[SMALLTEXTSIZE];
  int fd;
  int nb;
  
  /* Gets the proxy info associated with 'name'. */
  
  sprintf(file_name, "%s/nameMap.info", getStoreOfProcess());
  if ((fd = open(file_name,O_RDWR))<0) {
    perror("getName");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if ((nb = read(fd, &size, sizeof(u_long))) < 0) {
    perror("getName");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "getName: Could not load size of name map\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  nameMap = (rootMapCell *)calloc(size, 1);
  
  if ((nb = read(fd, nameMap, size)) < 0) {
    perror("getName");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != size) {
    fprintf(output, "getName: Could not load name map\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  *dummy = (void *)-1;
  *GCAttr = -1;
  *id = -1;
  *offset = -1;
  
  { 
    u_long count;
    
    for (count=0; count< size / sizeof(struct _rootMapCell); count++) {
      if (strcmp(nameMap[count].name, name) == 0) {
	*dummy = nameMap[count].dummy;
	*GCAttr = nameMap[count].GCAttr;
	*id = nameMap[count].id;
	*offset = nameMap[count].offset;
	break;
      }
    }
  }
  
  close(fd);
  
  return;
}

void _create(char *name) 
{
  char file_name[SMALLTEXTSIZE];
  int fd;
  int nb;
  u_long size;
  
  /* Create directory for store */
  if (mkdir(name, S_IFDIR | S_IREAD | S_IWRITE | S_IEXEC) < 0) {
    perror("create");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  storeOfProcess = strdup(name);
  permission = S_IWRITE;

  /* create empty name map */
  
  sprintf(file_name, "%s/nameMap.info", getStoreOfProcess());
  if ((fd = open(file_name,O_RDWR | O_CREAT, S_IWRITE | S_IREAD))<0) {
    perror("create");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  size = 0;
  
  if ((nb = write(fd, &size, sizeof(u_long))) < 0) {
    perror("create");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "create: Could not save size of name map\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  close(fd);
  
  return;
}

long isDir(char *name) 
{
  int fd;
  
  if ((fd = open(name,O_RDWR))<0) {
    switch(errno) {
    case EISDIR:
      return 1;
      break;
    default:
      return 0;
      break;
    }
  } else {
    close(fd);
    return 0;
  }
  return 0;
}

long _openRead(char *name) 
{
  long returnCode = 0;
  
  if (isDir(name)) {
    returnCode = 1;
    storeOfProcess = strdup(name);
    permission = S_IREAD;
  } else {
    /* Does not exist */
    returnCode = 2;
  }
  
  return returnCode;
}

long _openWrite(char *name) 
{
  long returnCode = 0;
  
  if (isDir(name)) {
    returnCode = 1;
    storeOfProcess = strdup(name);
    permission = S_IWRITE;
  } else {
    /* Does not exist */
    returnCode = 2;
  }
  
  return returnCode;
}

long unknownStore(char *storeName) 
{
  return (strcmp(storeName, UNKNOWNSTORE) == 0);
}

long unknownId(long id) 
{
  return (id == UNKNOWNID);
}

long getNextStoreId(void) 
{
  return nextStoreId++;
}

char *getStoreOfProcess(void) 
{
  return storeOfProcess;
}

static void *proxyList;
static u_long *proxyMap;

#define PROXYNUMBEROFFSET 1

static void saveProxyInCell(Object **theCell) 
{
  *theCell = (Object *)(appendProxyToList((long) *theCell, &proxyList) + PROXYNUMBEROFFSET);
  Claim((long)*theCell > 0, "Illegal local proxy created");

}

static void remapProxyInCell(Object **theCell) 
{
  if ((long)*theCell - PROXYNUMBEROFFSET < proxyMap[0]) {
    *theCell = (Object *)proxyMap[(long)*theCell - PROXYNUMBEROFFSET + 1];
    
  } else {
    fprintf(output, "remapProxyInCell: Illegal local proxy (0x%X)\n", (int)*theCell);
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

static void ensureStoreDirectory(void) 
{
  ;
}

static void saveProxyAction(Object *theObj, void *generic)
{
  
  theObj -> GCAttr = appendProxyToList(theObj -> GCAttr, &proxyList) + PROXYNUMBEROFFSET;
  
  scanObject(theObj,
	     saveProxyInCell,
	     TRUE);
}

void savePersistentAOABlock(Block *b) 
{
  /* All references are proxies. They should be 'normalized' and the
   * correspondind proxy should be looked up and be saved together
   * with this block. */
  
  if (permission == S_IWRITE) {
    proxyList = initProxyList();
    
    b -> next = NULL;
    
    foreachObjectInBlocks(b,
			  saveProxyAction,
			  NULL);
    
    removeProxyMovedMark();
    
    /* Write block in the store, overwriting any existing version of the
     * block. */
    
    { 
      int fd;
      u_long nb, size;
      char file_name[SMALLTEXTSIZE];
      
      ensureStoreDirectory();
      
      sprintf(file_name, "%s/Block%ld.ps", getStoreOfProcess(), b -> id);
      if ((fd = open(file_name,O_RDWR | O_CREAT, S_IWRITE | S_IREAD))<0) {
	perror("savePersistentAOABlock");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      
      /* First we write the proxies */
      size = sizeOfProxyList(proxyList);
      
      if ((nb = write(fd, &size, sizeof(u_long))) < 0) {
	perror("savePersistentAOABlock");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      
      if (nb != sizeof(u_long)) {
	fprintf(output, "savePersistentAOABlock: Could not write size of proxy list\n");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      
      INFO_PERSISTENTSTORE(fprintf(output,"[ Block %d: Saving proxylist of size 0x%X bytes]\n", 
				   (int)b -> id,
				   (int)sizeOfProxyList(proxyList)));
      
      if ((nb = write(fd, proxyList, sizeOfProxyList(proxyList))) < 0) {
	perror("savePersistentAOABlock");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      
      if (nb != sizeOfProxyList(proxyList)) {
	fprintf(output, "savePersistentAOABlock: Could not write entire proxy list\n");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      
      freeProxyList(proxyList);
      proxyList = NULL;
      
      /* Then we write the block itself. */
      b -> top = (long *) ((long) b -> top - (long) b);
      b -> limit = (long *)((long) b -> limit - (long) b);
      size = (long) b -> limit;
      
      if ((nb = write(fd, &size, sizeof(u_long))) < 0) {
	perror("savePersistentAOABlock");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      
      if (nb != sizeof(u_long)) {
	fprintf(output, "savePersistentAOABlock: Could not write size of block\n");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      
      INFO_PERSISTENTSTORE(fprintf(output,"[ Saving block %d ", (int)b ->id));
      if ((nb = write(fd, b, size)) < 0) {
	perror("savePersistentAOABlock");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }
      INFO_PERSISTENTSTORE(fprintf(output,"]\n"));
      
      if (nb != size) {
	fprintf(output, "savePersistentAOABlock: Could not write size of block\n");
	DEBUG_CODE(Illegal());
	BetaExit(1);
      }

      memset(b, 0, size);

      close(fd);
    }
  }
}

static void reMapProxyAction(Object *theObj, void *generic) 
{
  if (theObj -> GCAttr - PROXYNUMBEROFFSET < proxyMap[0]) {
    theObj -> GCAttr = proxyMap[theObj -> GCAttr - PROXYNUMBEROFFSET + 1];
    
  } else {
    fprintf(output, "remapProxyInCell: Illegal local proxy (0x%X)\n", (int)(theObj -> GCAttr));
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  scanObject(theObj,
	     remapProxyInCell,
	     TRUE);
  
  INFO_PERSISTENTSTORE(numObjects+=1);
}

Block *loadPersistentAOABlock(long id) 
{
  int fd;
  u_long nb;
  char file_name[SMALLTEXTSIZE];
  u_long size;
  Block *b;
  
  sprintf(file_name, "%s/Block%ld.ps", getStoreOfProcess(), id);
  if ((fd = open(file_name,O_RDWR)) < 0) {
    perror("loadPersistentAOABlock");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  /* First we load the proxies */
  if ((nb = read(fd, &size, sizeof(u_long))) < 0) {
    perror("loadPersistentAOABlock");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "loadPersistentAOABlock: Could not load size of proxy list\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  proxyList = (void *)calloc(size, 1);

  INFO_PERSISTENTSTORE(fprintf(output,"[ Block %d: Loading proxylist of size 0x%X bytes]\n", 
			       (int)id,
			       (int)size));
  
  if ((nb = read(fd, proxyList, size)) < 0) {
    perror("loadPersistentAOABlock");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != size) {
    fprintf(output, "loadPersistentAOABlock: Could not load proxy list\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }

  if ((nb = read(fd, &size, sizeof(u_long))) < 0) {
    perror("loadPersistentAOABlock");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "loadPersistentAOABlock: Could not load size of block list\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }

  b = (Block *)malloc(size);  
  
  INFO_PERSISTENTSTORE(fprintf(output,"[ Loading block %d ", (int)id));
  if ((nb = read(fd, b, size)) < 0) {
    perror("loadPersistentAOABlock");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  INFO_PERSISTENTSTORE(fprintf(output,"]\n"));
  
  if (nb != size) {
    fprintf(output, "loadPersistentAOABlock: Could not load block\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }

  b -> top = (long *)((long)b + (long) b -> top);
  b -> limit = (long *)((long)b + (long) b -> limit);
  
  close(fd);
  
  proxyMap = appendProxiesToProcess(proxyList);
  
  free(proxyList);
  proxyList = NULL;
  
  INFO_PERSISTENTSTORE(numPersistentBlocks+=1);

  foreachObjectInBlocks(b,
			reMapProxyAction,
			NULL);
  free(proxyMap);
  proxyMap = NULL;
  
  return b;
}

static void noReferenceAction(Object **theCell) 
{ 
  ;
}

static void unswizzleOriginAction(Object *theObj, void *generic) 
{
  
  scanObject(theObj,
	     noReferenceAction,
	     TRUE);
  
}

static void unswizzleOriginObjectAction(Object *theObj)
{
  Object **theCell;
  long originOffset;
  Object *origin;
  void *dummy;
  u_long id;
  u_long offset;
  
  if ((origin = getOrigin(theObj, &originOffset))) {
    theCell = (Object **)((long)theObj + originOffset);
    
    if (inProxy((long)*theCell)) {
      getProxyAttributes((long)*theCell, &dummy, &id, &offset);
      
      *theCell = lookUpObject(dummy, id, offset);
      
      /* This reference cannot possibly be into IOA or AOA. So no tabled
	 need to be updated */
    }
  }
}

void unswizzleOrigins(Block *b) 
{
  Block *temp;
  
  temp = b -> next;
  b -> next = NULL;
  
  objectAction = unswizzleOriginObjectAction;
  
  foreachObjectInBlocks(b,
			unswizzleOriginAction,
			NULL);
  
  objectAction = NULL;
  
  b -> next = temp;
}

void dummy(void) 
{
  if (0) {
    USE();
  }
}

#endif /* PERSIST */

