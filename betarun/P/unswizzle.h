#ifndef _UNSWIZZLE_H_
#define _UNSWIZZLE_H_
#include "beta.h"
#include "objectStore.h"

Object *unswizzleReference(void *ip);
Object *lookUpReferenceEntry(BlockID store, u_long offset);
Object *handleSpecialReference(u_long specRef);
void registerRebinderFunc(Object *(*rebinderFunc)(u_long objectTag, u_long typeTag));

#endif /* _UNSWIZZLE_H_ */
