#include "beta.h"
#include "PStore.h"
#include "PSfile.h"
#include "misc.h"
#include "unswizzle.h"

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

#define SIZEOFNAMEMAP   MAXNAMES * (MAXNAMELENGTH + sizeof(ObjectKey))

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

/* LOCAL VARIABLES */
static char storename[SMALLTEXTSIZE];
static char *currentStore = NULL;
static unsigned long permission;

/* LOCAL FUNCTION DECLARATIONS */
static unsigned long nameToID(char *name);
static char *getBetaText(unsigned long name_r);
static unsigned long openExt(unsigned long name_r, unsigned long perm);

/* IMPLEMENTATION */
char *objectStoreName(unsigned long store)
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
    
    setCurrentPStore(nameToID(currentStore));
    
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
  return 0;
}

static unsigned long nameToID(char *name)
{
  return 1;
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
      if (mkdir(name
		
#ifdef UNIX
		, S_IFDIR | S_IREAD | S_IWRITE | S_IEXEC 
#endif
		) < 0) 
	{
	  perror("createExt:");
	  free(name);
	  return CREATIONERRORERROR;
	} else {
	  if (currentStore) {
	    free(currentStore);
	    currentStore = NULL;
	  }
	  currentStore = name;
	  createPStore(nameToID(name));
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
      nameMapEntry *nameMap;
      
      name = getBetaText(name_r);
      getNameMap((void **)&nameMap);
      for (count = 0; count <  MAXNAMES; count++) {
	if (nameMap[count].name[0] == '\0') {
	  if (strlen(name) < MAXNAMELENGTH) {
	    sprintf(&(nameMap[count].name[0]), "%s", name);
	    nameMap[count].offset = ok.offset;
	    free(name);
	    return return_value;
	  } else {
	    fprintf(output, "putExt: Could not put new object to store (name too long)\n");
	    DEBUG_CODE(Illegal());
	    BetaExit(1);
	  }
	} else {
	  if (strcmp(&(nameMap[count].name[0]), name) == 0) {
	    if (dooverwrite) {
	      nameMap[count].name[0] = '\0';
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
  saveCurrentStore();
  free(currentStore);
  currentStore = NULL;
  closeCurrentStore();
  
}

unsigned long isOpen(void)
{
  return (currentStore != NULL);
}

unsigned long getExt(unsigned long name_r)
{
  unsigned long count;
  
  if (name_r) {
    char *name;
    nameMapEntry *nameMap;
    
    name = getBetaText(name_r);
    getNameMap((void **)&nameMap);
    
    for (count = 0; count <  MAXNAMES; count++) {
      if (strcmp(&(nameMap[count].name[0]), name) == 0) {
	Object *target;
#ifdef sparc
	target = lookUpReferenceEntry(getCurrentStoreID(), nameMap[count].offset, -1);
#else
	target = lookUpReferenceEntry(getCurrentStoreID(), 
				      nameMap[count].offset, -1);
#endif
	free(name);
	return (unsigned long)target;
      }
    }
    free(name);
  }
  return 0;
}

#endif /* PERSIST */
