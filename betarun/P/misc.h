#ifndef _MISC_H_
#define _MISC_H_
#include "beta.h"

void delayedInsert(Object *theObj);
void markPersistentObject(Object *theObj);
void newPersistentObject(Object *theObj);
void markReachableObjects(REFERENCEACTIONARGSTYPE);
void handleNewPersistentObject(Object *theObj);
void markOriginsAlive(Object *theObj);
void resetStatistics(void);
void showStatistics(void);
void handlePersistentCell(REFERENCEACTIONARGSTYPE);

#endif /* _MISC_H_ */
