#ifndef _TRANSITOBJECTTABLE_H_
#define _TRANSITOBJECTTABLE_H_
#include "beta.h"
#include "referenceTable.h"
#include "storageblock.h"

void initTransitObjectTable(void);
void insertObjectInTransit(CAStorage *store,
                           unsigned long offset,
                           Object *theObj);
void redirectAOACells(Array *clients, Object *from, Object *to);

#endif /* _TRANSITOBJECTTABLE_H_ */
