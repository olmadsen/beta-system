#include "PStore.h"

void pstoreserver_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

#include <unistd.h>
/* */
#define SMALLTEXTSIZE 512

static char storename[SMALLTEXTSIZE];

static StoreID next = 0;

static int getProcessIDOfMe(void)
{
  return getpid();
}

char *crossStoreTableName(StoreID store)
{
  /* maps storeid's to store names. For now stores cannot survive
     across runs and cannot be shared between clients. */
  
  sprintf(storename, "CrossStore%dstore%d", (int)getProcessIDOfMe(), (int)store);
  
  return &storename[0];
}

char *objectStoreName(StoreID store)
{
  /* maps storeid's to store names. For now stores cannot survive
     across runs and cannot be shared between clients. */
  
  sprintf(storename, "ObjectsStore%dstore%d", (int)getProcessIDOfMe(), (int)store);
  
  return &storename[0];
}

StoreID getNextStoreId(void)
{
  return ++next;
}

#endif /* PERSIST */
