#ifndef _TRANSITOBJECTTABLE_H_
#define _TRANSITOBJECTTABLE_H_
#include "beta.h"
#include "referenceTable.h"

void initTransitObjectTable(void);
unsigned long TOTSize(void);
unsigned long insertObjectInTransit(unsigned long store,
				    unsigned long offset,
				    Object *theObj);
void TOTFlush(void);
Object *indexLookupTOT(unsigned long store, unsigned long offset);
void redirectCells(Array *clients, Object *from, Object *to);
void clearCells(Array *clients);

#endif /* _TRANSITOBJECTTABLE_H_ */
