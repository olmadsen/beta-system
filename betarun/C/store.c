#include "beta.h"

static long nextStoreId = 1;
static char *storeOfProcess = "AOA";

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
