#ifndef _P_MISC_H_
#define _P_MISC_H_
#include "../C/beta.h"

typedef struct ObjectKey {
  unsigned long theProto;
  unsigned long GCattr;
  unsigned long theOrigin;
  unsigned long store;
  unsigned long offset;
} ObjectKey;

void delayedInsert(Object *theObj);
void markPersistentObject(Object *theObj);
void newPersistentObject(Object *theObj);
void markReachableObjects(REFERENCEACTIONARGSTYPE);
void handleNewPersistentObject(Object *theObj);
void markOfflineAndOriginObjectsAlive(REFERENCEACTIONARGSTYPE);
void resetStatistics(void);
void showStatistics(void);
void handlePersistentCell(REFERENCEACTIONARGSTYPE);
void getKeyForObject(ObjectKey *ok, Object *theObj);
void setClosingGC(void);
Object *keyToObject(ObjectKey *ok);
void setForceAOAGG(void);
void markSpecialObject(unsigned long tag, Object *theObj);

#endif /* _P_MISC_H_ */
