#include "beta.h"
#include "PStore.h"
#include "PSfile.h"
#include "misc.h"

void pstoreserver_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

#ifdef UNIX
#include <unistd.h>
#endif
#ifdef nti
#include <io.h>
#include <direct.h>
#endif

/* LOCAL CONSTANTS */
#define SMALLTEXTSIZE       512
#define ACCESSERRORERROR    1
#define NOTFOUNDERROR       2
#define ALREADYOPENERROR    3
#define EXISTSERROR         4
#define CREATIONERRORERROR  5
#define ALREADYTHEREERROR   6
#define HASOVERWRITTENERROR 7

#define MAXNAMES      10
#define MAXNAMELENGTH 100
#define STOREINFO       "storeInfo"

#define SIZEOFNAMEMAP   MAXNAMES * (MAXNAMELENGTH + sizeof(ObjectKey))
#define SIZEOFSTOREINFO SIZEOFNAMEMAP + sizeof(BlockID)

/* LOCAL TYPES */
typedef struct charRep {
  unsigned long Proto;
  unsigned long GCAttr;
  unsigned long LowBorder;
  unsigned long HighBorder;
  char elements[1];
} charRep;

typedef struct Text {
  unsigned long Proto;
  unsigned long GCAttr;
  unsigned long Origin;
  charRep *theRep;
} Text;

typedef struct nameMapEntry {
  char name[MAXNAMELENGTH];
  ObjectKey ok;
} nameMapEntry;

typedef struct storeInfo {
  nameMapEntry nameMap[MAXNAMES];
  BlockID next;
} storeInfo;

/* LOCAL VARIABLES */
static char storename[SMALLTEXTSIZE];
static char *currentStore = NULL;
static unsigned long permission;
static char *currentDir;
static storeInfo si;

/* LOCAL FUNCTION DECLARATIONS */
static void CallbackFnc(char *s);
static char *getBetaText(unsigned long name_r);
static unsigned long openExt(unsigned long name_r, unsigned long perm);
static int getNameMap(void);
static int setNameMap(void);

/* IMPLEMENTATION */
static int getStoreInfo(void)
{
  if (currentStore) {
    if (isDir(currentStore)) {
      char *filename = (char *)malloc(sizeof(char)*(strlen(currentStore) + 
						    strlen(STOREINFO) +
						    2));
      int fd;
      
      sprintf(filename, "%s/%s", currentStore, STOREINFO);
      if ((fd = open(filename,O_RDWR | O_CREAT | _O_BINARY,
		     S_IWRITE | S_IREAD))<0) {
	perror("getStoreInfo");
	free(filename);
	return 1;
      } else {
	readSome(fd, &si, SIZEOFSTOREINFO); 
	close(fd);
	free(filename);
	return 0;
      }
    } else {
      return 2;
    }
  } else {
    return 3;
  }
}

static int setStoreInfo(void)
{
  if (currentStore) {
    if (isDir(currentStore)) {
      char *filename = (char *)malloc(sizeof(char)*(strlen(currentStore) + 
						    strlen(STOREINFO) +
						    2));
      int fd;
      
      sprintf(filename, "%s/%s", currentStore, STOREINFO);
      if ((fd = open(filename,O_RDWR | O_CREAT | _O_BINARY,
		     S_IWRITE | S_IREAD))<0) {
	perror("setStoreInfo");
	free(filename);
	return 1;
      } else {
	writeSome(fd, &si, SIZEOFSTOREINFO); 
	close(fd);
	free(filename);
	return 0;
      }
    } else {
      return 2;
    }
  } else {
    return 3;
  }
}

static int getNameMap(void)
{
  return getStoreInfo();
}

static int setNameMap(void)
{
  return setStoreInfo();
}


char *crossStoreTableName(BlockID store)
{
  /* maps BlockID's to store names. For now stores cannot survive
     across runs and cannot be shared between clients. */
  
  if (currentStore) {
    sprintf(storename, "%s/CS%d", currentStore, (int)store);
  } else {
    fprintf(output, "crossStoreTableName: Could not calculate new name\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return &storename[0];
}

char *objectStoreName(BlockID store)
{
  /* maps BlockID's to store names. For now stores cannot survive
     across runs and cannot be shared between clients. */
  if (currentStore) {
    sprintf(storename, "%s/OS%d", currentStore, (int)store);
  } else {
    fprintf(output, "crossStoreTableName: Could not calculate new name\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  return &storename[0];
}

BlockID getNextBlockID(void)
{
  return ++si.next;
}

static char *getBetaText(unsigned long name_r)
{
  return strdup((char*)name_r);

#if 0
  Text *currentText;
  charRep *theRep;
  char *name;
  unsigned long j;
  
  currentText = (Text *)name_r;
  theRep = currentText -> theRep;
      
  name = (char *)malloc(sizeof(char)*(theRep -> HighBorder - theRep -> LowBorder + 1 + 1));
	
  for (j = theRep -> LowBorder; j <= theRep -> HighBorder; j++) {
    name[j - theRep -> LowBorder] = theRep -> elements[j - 1];
  }
  name[j - 1] = '\0';

  return name;
#endif
}

static unsigned long openExt(unsigned long name_r, unsigned long perm)
{
  char *name;
  
  if (name_r) {
    name = getBetaText(name_r);
    
    /* Ensure directory containing the store */
    if (!isDir(name)) {
      free(name);
      return NOTFOUNDERROR;
    }
    
    if (currentStore) {
      free(currentStore);
      currentStore = NULL;
    }
    currentStore = name;
    permission = perm;
    
    if (getNameMap()) {
      free(name);
      currentStore = NULL;
      return ACCESSERRORERROR;
    }
    
    return 0;
  } else {
    return ACCESSERRORERROR;
  }
}

unsigned long openWriteExt(unsigned long name_r)
{
  return openExt(name_r, S_IWRITE);
}

unsigned long openReadExt(unsigned long name_r)
{
  return openExt(name_r, S_IREAD);
}

unsigned long deleteExt(unsigned long name_r)
{
  fprintf(output, "deleteExt: Not implemented yet!\n");
  BetaExit(1);
}

unsigned long createExt(unsigned long name_r)
{
  char *name;
  
  if (name_r) {
    name = getBetaText(name_r);
    if (isDir(name)) {
      free(name);
      return EXISTSERROR;
    } else {
      /* make new directory */
#ifdef UNIX
      if (mkdir(name, S_IFDIR | S_IREAD | S_IWRITE | S_IEXEC) < 0) 
#else
      if (mkdir(name) < 0) 
#endif
      {
	perror("");
	free(name);
	return CREATIONERRORERROR;
      } else {
	if (currentStore) {
	  free(currentStore);
	  currentStore = NULL;
	}
	currentStore = name;
	memset(si.nameMap, 0, MAXNAMES * MAXNAMELENGTH);
	si.next = 0;
	if (setNameMap()) {
	  free(currentStore);
	  currentStore = NULL;
	  return CREATIONERRORERROR;
	}
	return 0;
      }
    }
  } else {
    return CREATIONERRORERROR;
  }
}

unsigned long putExt(unsigned long dooverwrite, unsigned long name_r, Object *theObj)
{
  ObjectKey ok;
  unsigned long return_value;

  return_value = 0;
  if (name_r) {
    getKeyForObject(&ok, theObj);
    
    if (ok.store != -1) {
      unsigned long count;
      char *name;
      
      name = getBetaText(name_r);
      
      for (count = 0; count <  MAXNAMES; count++) {
	if (si.nameMap[count].name[0] == '\0') {
	  if (strlen(name) < MAXNAMELENGTH) {
	    sprintf(&(si.nameMap[count].name[0]), "%s", name);
	    si.nameMap[count].ok.store = ok.store;
	    si.nameMap[count].ok.offset = ok.offset;
	    free(name);
	    return return_value;
	  } else {
	    fprintf(output, "putExt: Could not put new object to store (name too long)\n");
	    DEBUG_CODE(Illegal());
	    BetaExit(1);
	  }
	} else {
	  if (strcmp(&(si.nameMap[count].name[0]), name) == 0) {
	    if (dooverwrite) {
	      si.nameMap[count].name[0] = '\0';
	      return_value = ALREADYTHEREERROR;
	      count--;
	    } else {
	      free(name);
	      return ALREADYTHEREERROR;
	    }
	  }
	}
      }
      
      fprintf(output, "putExt: Could not put new object to store (too many names)\n");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    } else {
      fprintf(output, "putExt: Could not put new object to store\n");
      DEBUG_CODE(Illegal());
      BetaExit(1);
    }
  } else {
    fprintf(output, "putExt: Could not put new object to store (name is NULL)\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }

  fprintf(output, "putExt: Could not put new object to store (impossible error)\n");
  DEBUG_CODE(Illegal());
  BetaExit(1);
  return 0;
}

void closeExt(void)
{
  if (setNameMap()) {
    fprintf(output, "closeExt: Could not close object store\n");
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  free(currentStore);
  currentStore = NULL;
}

unsigned long isOpen(void)
{
  return (currentStore != NULL);
}

unsigned long getExt(unsigned long name_r, Object *theObj, Object **theCell)
{
  unsigned long count;
  unsigned long offset;

  Claim((unsigned long)theCell > (unsigned long)theObj, "getExt: theCell is before theObj");
  
  offset = (unsigned long)theCell - (unsigned long)theObj;
  
  if (name_r) {
    char *name;
    
    name = getBetaText(name_r);
    
    for (count = 0; count <  MAXNAMES; count++) {
      if (strcmp(&(si.nameMap[count].name[0]), name) == 0) {
	Object *target;
	
#ifdef sparc
	Protect(theObj, target = keyToObject(&(si.nameMap[count].ok)));
#else
	/* FIXME: Should protect regs */
	target = keyToObject(&(si.nameMap[count].ok));
#endif
	theCell = (Object **)((unsigned long)theObj + offset);
	*theCell = target;
	free(name);
	return 0;
      }
    }
    free(name);
  }
  return NOTFOUNDERROR;
}

#endif /* PERSIST */
