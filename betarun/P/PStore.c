#include "PStore.h"

void pstore_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

#ifdef PERSIST

int compareBlockID(BlockID a, BlockID b)
{
  return a == b;
}

#endif /* PERSIST */
