#ifndef _TRANSITOBJECTTABLE_H_
#define _TRANSITOBJECTTABLE_H_
#include "beta.h"
#include "objectStore.h"

void initTransitObjectTable(void);
u_long TOTSize(void);
u_long insertObjectInTransit(BlockID store,
			     u_long offset,
			     Object *theObj);
void TOTFlush(void);
Object *indexLookupTOT(BlockID store, u_long offset);
void redirectCells(Array *clients, Object *from, Object *to);
void clearCells(Array *clients);

#endif /* _TRANSITOBJECTTABLE_H_ */
