#ifndef _P_MISC_H_
#define _P_MISC_H_
#include "../C/beta.h"
#include "trie.h"

typedef struct ObjectKey {
  unsigned long theProto;
  unsigned long GCattr;
  unsigned long theOrigin;
  unsigned long store;
  unsigned long offset;
} ObjectKey;

unsigned long newPersistentObject(unsigned long storeID,
				  Object *theObj);
void markReachableObjects(REFERENCEACTIONARGSTYPE);
void markOfflineAndOriginObjectsAlive(REFERENCEACTIONARGSTYPE);
void resetStatistics(void);
void showStatistics(void);
void handlePersistentCell(REFERENCEACTIONARGSTYPE);
void getKeyForObject(ObjectKey *ok, Object *theObj);
void setForceAOAGG(void);
void markSpecialObject(unsigned long tag, Object *theObj);
void insertStoreOffset(unsigned long store, 
		       unsigned long offset, 
		       unsigned long inx,
		       Trie **loadedObjects);
void forceObjectToAOA(Object *theObj);

#endif /* _P_MISC_H_ */
