#include "beta.h"
#include "PSfile.h"
#include "misc.h"
#include "unswizzle.h"
#include "transitObjectTable.h"
#include "objectTable.h"
#include "PStoreServer.h"
#include "crossStoreReferences.h"
#include "PImport.h"
#include "PException.h"

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
#define EXISTSERROR         4
#define CREATIONERRORERROR  5
#define ALREADYTHEREERROR   6
#define HASOVERWRITTENERROR 7

#define SIZEOFNAMEMAP   MAXNAMES * (MAXNAMELENGTH + sizeof(ObjectKey))

#define MAXDBNAMELENGTH 512
#define DBNAME "db"

/* LOCAL TYPES */

/* LOCAL VARIABLES */
static char dbname[MAXDBNAMELENGTH];

/* LOCAL FUNCTION DECLARATIONS */
static unsigned long openExt(unsigned long host_r,
			     unsigned long path_r, 
			     unsigned long perm);

/* IMPLEMENTATION */
char *DBname(char *path)
{
  if (strlen(path) + strlen(DBNAME) + 1 < MAXDBNAMELENGTH) {
    sprintf(dbname, "%s/%s", path, DBNAME);
    return &dbname[0];
  } else {
    fprintf(output, "DBname: path name length exceeded only %d characters are allowed\n", MAXDBNAMELENGTH - strlen(DBNAME) - 1);
    BetaExit(1);
    return NULL;
  }
}
  
char *getBetaText(unsigned long str)
{
  return strdup((char*)str);
}

static unsigned long openExt(unsigned long host_r, 
			     unsigned long path_r, 
			     unsigned long perm)
{
  char *path, *host;
  unsigned long r;
  
  if (host_r) {
    if (path_r) {
      host = getBetaText(host_r);
      path = getBetaText(path_r);
      /* Ensure that the store file exists */
      if (!fileExists(DBname(path))) {
	r = NOTFOUNDERROR;
      } else {
	unsigned long storeID;
	
	if ((storeID = registerNewStore(host, path)) != -1) {
	  markStoreAsOpen(storeID);
	  setCurrentPStore(storeID);
	  r = 0;
	} else {
	  r = ACCESSERRORERROR;
	}
      }
      free(host);
      free(path);
    } else {
      r = ACCESSERRORERROR;
    }
  } else {
    r = ACCESSERRORERROR;
  }
  return r;
}

unsigned long openWriteExt(unsigned long host_r, unsigned long path_r)
{
  return openExt(host_r, path_r, S_IWRITE);
}

unsigned long openReadExt(unsigned long host_r, unsigned long path_r)
{
  return openExt(host_r, path_r, S_IREAD);
}

void closeExt(unsigned long host_r, unsigned long path_r)
{
  char *path, *host;
  unsigned long storeID;
  
  if (host_r) {
    if (path_r) {
      host = getBetaText(host_r);
      path = getBetaText(path_r);
      if ((storeID = nameToID(host, path)) != -1) {
	markStoreAsClosed(storeID);
	saveStore(storeID);
	closeStore(storeID);
      }
      free(host); free(path);
    }
  }
}

unsigned long deleteExt(unsigned long host_r, unsigned long path_r)
{
  fprintf(output, "deleteExt: Not implemented yet!\n");
  BetaExit(1);
  return 0;
}

unsigned long createExt(unsigned long host_r, unsigned long path_r)
{
  char *path, *host;
  unsigned long r=0, storeID;

  /* Current applications using the persistence facilities assumes
     that the persistent store is placed in a directory. There seems
     no need for this any more since the store is placed in one file
     only. Still to support 'legacy' software the store is placed in
     its one directory */
  
  if (host_r && path_r) {
    host = getBetaText(host_r);
    path = getBetaText(path_r);
    
    if (isDir(path) && fileExists(DBname(path))) {
      r = EXISTSERROR;
    } else {
      if ((storeID = createPStore(host, path))) {
	markStoreAsOpen(storeID);
      } else {
	r = CREATIONERRORERROR;
      }
    }
    
    free(host); 
    free(path);

  } else {
    r = CREATIONERRORERROR;
  }
  
  return r;

}

unsigned long putExt(unsigned long dooverwrite, 
		     unsigned long host_r, 
		     unsigned long path_r,
		     unsigned long name_r,
		     Object *theObj)
{
  char *host, *path, *name;
  unsigned long offset, storeID, r=-1;
  Object *theRealObj;
  
  Claim(host_r, "getExt: Illegal host (is NULL)");
  Claim(path_r, "getExt: Illegal path (is NULL)");
  Claim(name_r, "getExt: Illegal name (is NULL)");
  
  host = getBetaText(host_r);
  path = getBetaText(path_r);
  name = getBetaText(name_r);
  
  if (inPIT(theObj)) {
    /* The object is a proxy reference. */
    theRealObj = unswizzleReference((void *)theObj);
  } else {
    theRealObj = getRealObject(theObj);
  }
  
  if (!inIOA(theRealObj)) {
    if (!AOAISPERSISTENT(theRealObj)) {
      if ((storeID = nameToID(host, path)) != -1) {
	if (setCurrentPStore(storeID)) {
	  offset = newPersistentObject(storeID, theRealObj);
	} else {
	  fprintf(output, "putExt: Could not set store (%d)\n", (int)(storeID));
	  BetaExit(1);
	}
      } else {
	fprintf(output, "putExt: Could not map store name to ID (%s)\n", path);
	BetaExit(1);
      }
    } else {
      unsigned short GCAttr;
      Object *dummy;
      
      objectLookup(getPUID((void *)(theRealObj -> GCAttr)),
		   &GCAttr,
		   &storeID,
		   &offset,
		   &dummy);
      
      Claim(GCAttr == ENTRYALIVE, "Reference to dead entry!");
      Claim(dummy == theObj, "Table mismatch");
    }
    if (getRootOffset(storeID, name) != -1) {
      r = ALREADYTHEREERROR;
      if (dooverwrite) {
	insertRoot(storeID, name, offset);
      } 
    } else {
      /* Insert */
      insertRoot(storeID, name, offset);
      r = 0;
    }
  } else {
    fprintf(output, "putExt: Object not in AOA\n");
    BetaExit(1);
  }
  
  free(host); free(path); free(name);
  return r;
}

unsigned long getExt(unsigned long host_r, 
		     unsigned long path_r, 
		     unsigned long name_r)
{
  unsigned long offset, storeID;
  char *host, *path, *name;
  Object *target = NULL;
  
  Claim(host_r, "getExt: Illegal host (is NULL)");
  Claim(path_r, "getExt: Illegal path (is NULL)");
  Claim(name_r, "getExt: Illegal name (is NULL)");
  
  host = getBetaText(host_r);
  path = getBetaText(path_r);
  name = getBetaText(name_r);
  
  /* Set the current store */
  if ((storeID = nameToID(host, path)) != -1) {
    if (setCurrentPStore(storeID)) {
      /* Look up the name */
      if ((offset = getRootOffset(storeID, name)) != -1) {
	target = importReference(storeID, offset, NULL);
      }
    }
  }
  free(host); free(path); free(name);
  return (unsigned long)target;
}
#endif /* PERSIST */
