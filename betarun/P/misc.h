#ifndef _P_MISC_H_
#define _P_MISC_H_
#include "../C/beta.h"

typedef struct ObjectKey {
  u_long theProto;
  u_long GCattr;
  u_long theOrigin;
  u_long store;
  u_long offset;
} ObjectKey;

void delayedInsert(Object *theObj);
void markPersistentObject(Object *theObj);
void newPersistentObject(Object *theObj);
void markReachableObjects(REFERENCEACTIONARGSTYPE);
void handleNewPersistentObject(Object *theObj);
void markOriginsAlive(Object *theObj);
void resetStatistics(void);
void showStatistics(void);
void handlePersistentCell(REFERENCEACTIONARGSTYPE);
void getKeyForObject(ObjectKey *ok, Object *theObj);
void setTerminatingGC(void);
void keyToObject(ObjectKey *ok, Object **theObj);
void setForceAOAGG(void);

#endif /* _P_MISC_H_ */
