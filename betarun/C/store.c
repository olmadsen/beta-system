#include "beta.h"

void sto_dummy()
{
#ifdef sparc
  USE();
#endif /* sparc */
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

/* MACROS */
#define SMALLTEXTSIZE 512
#define PROXYNUMBEROFFSET 1

/* LOCAL VARIABLES */
static void *proxyList;
static u_long *proxyMap;
static long nextStoreId = 1;
static char *storeOfProcess = "st1";
static int permission;

/* TYPES */
typedef struct _rootMapCell {
  char name[SMALLTEXTSIZE];
  /* proxy attributes */
  void *dummy;               /* ? */
  long GCAttr;
  long id;                   /* Id of block in store */
  long offset;               /* Offset of object in block */
} rootMapCell;

/* LOCAL FUNTION DECLARATIONS */

static void readLong(int fd, u_long *n);
static void readSome(int fd, void *buffer, u_long size);
static void Rewind(int fd);
static void writeLong(int fd, u_long *n);
static void windTo(int fd, u_long pos);
static void writeSome(int fd, void *buffer, u_long size);
static void saveProxyInCell(Object **theCell);
static void remapProxyInCell(Object **theCell);
static void ensureStoreDirectory(void);
static void saveProxyAction(Object *theObj, void *generic);
static void reMapProxyAction(Object *theObj, void *generic);
static void noReferenceAction(Object **theCell);
static void unswizzleOriginAction(Object *theObj, void *generic);
static void unswizzleOriginObjectAction(Object *theObj);
static long isDir(char *name);

/* readLong: reads a long from fd. */
static void readLong(int fd, u_long *n) 
{
  int nb;
  
  if ((nb = read(fd, n, sizeof(u_long))) < 0) {
    perror("readLong");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "readLong: Could not read long\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* readSome: reads size bytes into buffer from fd. */
static void readSome(int fd, void *buffer, u_long size) 
{
  int nb;
  
  if ((nb = read(fd, buffer, size)) < 0) {
    perror("readSome");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != size) {
    fprintf(output, "readSome: Could not read\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* Rewind: goes to the beginning of the file. */
static void Rewind(int fd)
{
  if (lseek(fd, 0, SEEK_SET) < 0) {
    perror("Rewind");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* writeLong: writes a long to fd. */
static void writeLong(int fd, u_long *n)
{
  int nb;
  
  if ((nb = write(fd, n, sizeof(u_long))) < 0) {
    perror("writeLong");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (nb != sizeof(u_long)) {
    fprintf(output, "putName: Could not write long\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* windTo: Goes to position pos in fd. */
static void windTo(int fd, u_long pos) 
{
  if (lseek(fd, pos, SEEK_SET) < 0) {
    perror("windTo");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* writeSome: writes size bytes from buffer onto fd. */
static void writeSome(int fd, void *buffer, u_long size)
{
  int nb;
  
  if ((nb = write(fd, buffer, size)) < 0) {
    perror("writeSome");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
}

/* putName: Maps name to proxy ip. */
void putName(Object *ip, char *name)
{
  rootMapCell *nameMap;
  u_long size;
  char file_name[SMALLTEXTSIZE];
  int fd;
  void *dummy;
  long GCAttr = 0;
  u_long id;  
  u_long offset;

  if (inProxy((long)ip)) {
    getProxyAttributes((long)ip, &dummy, &id, &offset);
  } else {
    fprintf(output, "putName: Reference not proxy\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  if (permission == S_IWRITE) {
    
    /* Loads the name map of this store and extendes it with the new
     * name */
    
    sprintf(file_name, "%s/nameMap.info", getStoreOfProcess());
    if ((fd = open(file_name,O_RDWR))<0) {
      perror("putName");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
    
    readLong(fd, &size);
    
    nameMap = (rootMapCell *)calloc(size, 1);
    
    readSome(fd, (void *)nameMap, size);
    
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
	
	Rewind(fd);
	
	size += sizeof(struct _rootMapCell);
	
	writeLong(fd, &size);
	
	/* Append new mapping */
	sprintf(&new.name[0], "%s", name);
	new.dummy = dummy;
	new.GCAttr = GCAttr;
	new.id = id;
	new.offset = offset;
	
	/* write new mapping to store */
	windTo(fd, sizeof(u_long) + size - sizeof(struct _rootMapCell));
	
	writeSome(fd, (void *)&new, sizeof(struct _rootMapCell));
	
      } else {
	/* name was their and have been replaced */

	windTo(fd, sizeof(u_long));
	
	writeSome(fd, (void *)nameMap, size);
	
      }
    }
    
    free(nameMap);
    close(fd);
  }
}

/* getName: Given a name the attributes of the proxy is returned. */
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
  
  /* Gets the proxy info associated with 'name'. */
  
  sprintf(file_name, "%s/nameMap.info", getStoreOfProcess());
  if ((fd = open(file_name,O_RDWR))<0) {
    perror("getName");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  
  readLong(fd, &size);
  
  nameMap = (rootMapCell *)calloc(size, 1);
  
  readSome(fd, (void *)nameMap, size);
  
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

/* create: Creates an initial persistent store. */
void _create(char *name) 
{
  char file_name[SMALLTEXTSIZE];
  int fd;
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
  
  writeLong(fd, &size);
  
  close(fd);
  
  return;
}

/* isDir: Returns true if name is a directory. */
static long isDir(char *name) 
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

/* openRead: Opens a store for read access. */
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

/* openWrite: Opens a store for write access. */
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

/* unknownStore: */
long unknownStore(char *storeName) 
{
  return (strcmp(storeName, UNKNOWNSTORE) == 0);
}

/* unknownId: */
long unknownId(long id) 
{
  return (id == UNKNOWNID);
}

/* getNextStoreId: */
long getNextStoreId(void) 
{
  return nextStoreId++;
}

/* getStoreOfProcess: */
char *getStoreOfProcess(void) 
{
  return storeOfProcess;
}

/* saveProxyInCell: Before export all proxies in the exported objects
   are 'normalized' in the sense that they are given id's. These id's
   are indices in a table containing the proxy objects
   themselves. This table is saved a long with the
   block. 'appendProxyToList' appends the proxy object to the table
   and returns the index. */
static void saveProxyInCell(Object **theCell) 
{
  *theCell = (Object *)(appendProxyToList((long) *theCell, &proxyList) + PROXYNUMBEROFFSET);
  Claim((long)*theCell > 0, "Illegal local proxy created");

}

/* remapProxyInCell: The proxy objects saved a long with a block is
   reinstroduced to this context. The global variable 'proxyMap' was
   created by 'appendProxiesToProcess' and maps the normalized proxies
   to their in-memory proxy.
   */
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

/* ensureStoreDirectory: Is supposed to check the a persistent store
   exist, but is not implemented yet. */
static void ensureStoreDirectory(void) 
{
  ;
}

/* saveProxyAction: Called for each object in the block that is about
   to be saved. It inserts the 'normalized' proxy of the object in the
   GC-Field. */
static void saveProxyAction(Object *theObj, void *generic)
{
  
  theObj -> GCAttr = appendProxyToList(theObj -> GCAttr, &proxyList) + PROXYNUMBEROFFSET;
  
  scanObject(theObj,
	     saveProxyInCell,
	     TRUE);
}

/* savePersistentAOABlock: */
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
      u_long size;
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
      
      writeLong(fd, &size);
      
      INFO_PERSISTENTSTORE(fprintf(output,"[ Block %d: Saving proxylist of size 0x%X bytes]\n", 
				   (int)b -> id,
				   (int)size));
      
      writeSome(fd, (void *)proxyList, size);
      
      freeProxyList(proxyList);
      proxyList = NULL;
      
      /* Then we write the block itself. */
      b -> top = (long *) ((long) b -> top - (long) b);
      b -> limit = (long *)((long) b -> limit - (long) b);
      size = (long) b -> limit;
      
      writeLong(fd, &size);
      
      INFO_PERSISTENTSTORE(fprintf(output,"[ Saving block %d ", (int)b ->id));
      
      writeSome(fd, (void *)b, size);
      INFO_PERSISTENTSTORE(fprintf(output,"]\n"));

      memset(b, 0, size);

      close(fd);
    }
  }
}

/* reMapProxyAction: Called for each object in th eblock that has just
   been loaded and maps the 'normalized' proxy to the in-memory
   proxy. See 'remapProxyInCell' above. */
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

/* loadPersistentAOABlock: */
Block *loadPersistentAOABlock(long id) 
{
  int fd;
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
  readLong(fd, &size);

  proxyList = (void *)calloc(size, 1);
  
  INFO_PERSISTENTSTORE(fprintf(output,"[ Block %d: Loading proxylist of size 0x%X bytes]\n", 
			       (int)id,
			       (int)size));
  
  readSome(fd, (void *)proxyList, size);
  
  readLong(fd, &size);
  
  b = (Block *)malloc(size);  
  
  INFO_PERSISTENTSTORE(fprintf(output,"[ Loading block %d ", (int)id));
  
  readSome(fd, (void *)b, size);

  INFO_PERSISTENTSTORE(fprintf(output,"]\n"));
  
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


/* noReferenceAction: Is called for each reference. */
static void noReferenceAction(Object **theCell) 
{ 
  ;
}

/* unswizzleOriginAction: Is called for each autonomous object in the
   persistent block just loaded. This is not called for part
   objects. */
static void unswizzleOriginAction(Object *theObj, void *generic) 
{
  
  scanObject(theObj,
	     noReferenceAction,
	     TRUE);
  
}

/* unswizzleOriginObjectAction: Is called for each object, including
   part-objects, just loaded. */
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

#endif /* PERSIST */

