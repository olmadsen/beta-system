#ifndef _PROTO_H_
#define _PROTO_H_
#include "beta.h"

void importProtoTypes(Object *theObj, CAStorage *store);
void exportProtoTypes(Object *theObj, CAStorage *store);
unsigned long StoreObjectSize(Object * theObj, CAStorage *store);
void initProtoHandling(void);
void freeProtoHandling(void);

#endif /* _PROTO_H_ */
