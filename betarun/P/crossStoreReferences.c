#include "beta.h"
#include "PStore.h"
#include "sequenceTable.h"
#include "crossStoreReferences.h"

#ifdef PERSIST

/* Import:

   A crossstorereference 'csr' is encountered. Proxy is looked up in
   store to get (store, offset) pair. 'store' is translated to
   'name'. 'name' is looked up in context to map it to context ID
   'cid' of store. reference is inserted in reference table with (cid,
   offset) pair.

   Export:

   A crossstore reference 'csr' is encountered as a (cid, offset)
   pair. cid is looked up in context to map it to a name. name is
   looked up in store of object containing reference to map it to
   store local id 'lid'. A proxy (lid, offset) is generated in the
   store if one does not exist and 'csr' can be transferred to a
   reference to this proxy.

   Maps in store:

   1) Proxy to (store, offset).
   2) Store to name.
   3) Name to store.
   4) (store, offset) to Proxy.
   
   Maps in context:
   
   1) Name to context store id.
   2) Context store id to name.
*/

#define INITIALSTOREELEMENTS 8
#define STOREISOPEN 1
#define STOREISCLOSED 0

static sequenceTable *id2name = NULL;

static int isFree(void *elm)
{
  storeLocation *sl;
  
  sl = (storeLocation *)elm;
  if (sl -> path[0] == '\0') {
    return 1;
  } else {
    return 0;
  }
}

static void Free(void *elm)
{
  Claim(elm != NULL, "Free: NULL element");
  free(elm);
}

static void markStoreAs(unsigned long storeID, unsigned long mark)
{
  storeLocation *current;
  
  current = STLookup(id2name, storeID - 1);
  
  Claim(current != NULL, "IDToName: Illegal storeID");
  Claim(current -> path[0] != '\0', "IDToName: Illegal store path");
  
  current -> open = mark;
}

void markStoreAsOpen(unsigned long storeID)
{
  markStoreAs(storeID, STOREISOPEN);
}

void markStoreAsClosed(unsigned long storeID)
{
  markStoreAs(storeID, STOREISCLOSED);
}

unsigned long storeIsOpen(unsigned long storeID)
{
  storeLocation *current;
  
  current = STLookup(id2name, storeID - 1);
  
  Claim(current != NULL, "IDToName: Illegal storeID");
  Claim(current -> path[0] != '\0', "IDToName: Illegal store path");
  
  return current -> open == STOREISOPEN;
}

unsigned long registerNewStore(char *host, char *path)
{
  /* (host, path) is inserted in the sequenceTable. The index of
     (host, path) will be the local ID of the store in this context.
  */
  
  if (id2name) {
    /* For now only path is considered */
    if (path) {
      if (strlen(path) < MAXPATHNAMELENGTH) {
	unsigned long inx;
	
	/* Check if the store is already there */
	
	if ((inx = nameToID(host, path)) == -1) {
	  storeLocation *sl;
	  
	  sl = (storeLocation *)malloc(sizeof(struct storeLocation));
	  sprintf(&(sl -> path[0]), "%s", path);
	  sprintf(&(sl -> host[0]), "%s", host);
	  sl -> open = STOREISCLOSED;
	  
	  inx = STInsert(&id2name, (void *)sl);
	  
	  /* The mapping to the trie is not implemented yet */
	  return inx + 1; /* We do not want 0 as store ID */

	} else {
	  return inx;
	}
      } else {
	fprintf(output, 
		"registerNewStore: path name too long (%s), only %d characters allowed\n",
		path,
		MAXPATHNAMELENGTH);
	BetaExit(1);
      }
    } else {
      fprintf(output, "registerNewStore: NULL path name\n");
      BetaExit(1);
    }
  } else {
    id2name = STInit(INITIALSTOREELEMENTS, 
		     isFree, 
		     Free, 
		     sizeof(struct storeLocation));
    return registerNewStore(host, path);
  }
  return -1;
}

unsigned long nameToID(char *host, char *path)
{
  unsigned long size, count;
  storeLocation *current;
  
  size = STSize(id2name);
  
  for (count = 0; count < size; count++) {
    current = STLookup(id2name, count);
    
    if (strcmp(&(current -> path[0]), path) == 0) {
      return count + 1;
    }
  }
  return -1;
}

storeLocation *IDToName(unsigned long id)
{
  storeLocation *current;
  
  current = STLookup(id2name, id - 1);
  
  Claim(current != NULL, "IDToName: Illegal storeID");
  Claim(current -> path[0] != '\0', "IDToName: Illegal store path");
  return current;
}

#endif /* PERSIST */
