#ifndef _UNSWIZZLE_H_
#define _UNSWIZZLE_H_
#include "beta.h"
#include "objectStore.h"

Object *unswizzleReference(void *ip);
Object *lookUpReferenceEntry(BlockID store, unsigned long offset);
Object *handleSpecialReference(unsigned long specRef);
void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long objectTag, unsigned long typeTag));

#endif /* _UNSWIZZLE_H_ */
