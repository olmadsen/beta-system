#include "beta.h"

#ifdef PERSIST
static long nextStoreId = 1;
static char *storeOfProcess = "st1";

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
  USE(); /* Has no meaning */
  return storeOfProcess;
}

#endif /* PERSIST */
