#ifndef _UNSWIZZLE_H_
#define _UNSWIZZLE_H_
#include "beta.h"
#include "storageblock.h"

#define BETAENVOBJ 42 /* must match tag for BETAENVOBJ in virtualobjectstore.bet */
#define PRGOBJ 43 /* must match tag for PROGRAM in virtualobjectstore.bet */

Object *unswizzleReference(void *ip);
Object *lookUpReferenceEntry(CAStorage *store,
                             unsigned long offset,
                             unsigned long inx,
                             u_long follow);
Object *handleSpecialReference(unsigned long specRef);
void registerRebinderFunc(Object *(*rebinderFunc)(unsigned long tag));
void showUnswizzleStatistics(void);
Object *USloadObject(CAStorage *store,
                     unsigned long offset,
                     unsigned long inx,
                     u_long follow);
#endif /* _UNSWIZZLE_H_ */
