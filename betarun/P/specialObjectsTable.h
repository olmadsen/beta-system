#ifndef _SPECIALOBJECTTABLE_H_
#define _SPECIALOBJECTTABLE_H_

#include "beta.h"

void initSpecialObjectTable(void);
unsigned long SOTSize(void);
unsigned long insertSpecialObject(unsigned long tag, Object *theObj);
void SOStartGC(void);
void SOEndGC(void);
void remarkSpecialObjects(void);
void saveTagForObject(Object *realObj, unsigned long tag);
unsigned long getTagForObject(Object *theObj);
unsigned long getTag(Object *theObj);
void freeSOTags(void);

#endif /* _SPECIALOBJECTTABLE_H_ */
