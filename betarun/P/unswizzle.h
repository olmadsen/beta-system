#ifndef _UNSWIZZLE_H_
#define _UNSWIZZLE_H_
#include "beta.h"

Object *unswizzleReference(void *ip);
Object *lookUpReferenceEntry(unsigned long store, unsigned long offset, unsigned long inx);
Object *handleSpecialReference(unsigned long specRef);
void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long objectTag, unsigned long typeTag));
void showUnswizzleStatistics(void);

#endif /* _UNSWIZZLE_H_ */
