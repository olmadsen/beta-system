#ifndef _SPECIALOBJECTTABLE_H_
#define _SPECIALOBJECTTABLE_H_

#include "beta.h"

void initSpecialObjectTable(void);
u_long SOTSize(void);
u_long insertSpecialObject(u_long tag, Object *theObj);
void unmarkSpecialObjects(void);
void GCspecialObjectsTable(void);
void remarkSpecialObjects(void);
void saveTagForObject(Object *realObj, u_long tag);
u_long getTagForObject(Object *theObj);
void freeSOTags(void);

#endif /* _SPECIALOBJECTTABLE_H_ */
