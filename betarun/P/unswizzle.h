#ifndef _UNSWIZZLE_H_
#define _UNSWIZZLE_H_
#include "beta.h"

#define BETAENVOBJ 42 /* must match tag for BETAENVOBJ in virtualobjectstore.bet */
#define PRGOBJ 43 /* must match tag for PROGRAM in virtualobjectstore.bet */

Object *unswizzleReference(void *ip);
Object *lookUpReferenceEntry(unsigned long store, unsigned long offset, unsigned long inx);
Object *handleSpecialReference(unsigned long specRef);
void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long objectTag, unsigned long typeTag));
void showUnswizzleStatistics(void);
void registerBETAENV(Object *theObj);

#endif /* _UNSWIZZLE_H_ */
