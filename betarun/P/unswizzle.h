#ifndef _UNSWIZZLE_H_
#define _UNSWIZZLE_H_
#include "beta.h"
#include "objectStore.h"

Object *unswizzleReference(void *ip);
Object *lookUpReferenceEntry(BlockID store, u_long offset);

#endif /* _UNSWIZZLE_H_ */
