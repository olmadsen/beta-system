#ifndef _OBJECTSET_H_
#define _OBJECTSET_H_
#include "beta.h"

void OSinsert(Object *theObj);
void OSscan(void (*foreach)(Object *theObj));
void OSclear(void);

#endif /* _OBJECTSET_H_ */
