#ifndef _P_MISC_H_
#define _P_MISC_H_
#include "beta.h"
#include "cache.h"

void MIstart(void);
void MIend(void);
void markSpecialObject(Object *theObj, unsigned long tag);
void markPersistentObject(CAStorage *ID, Object *obj);
void setForceAOAGG(void);
   
#endif /* _P_MISC_H_ */
