#include "PStore.h"

void pstore_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

int compareStoreID(StoreID a, StoreID b)
{
  return a == b;
}

#endif /* PERSIST */
