#ifndef _PROTO_H_
#define _PROTO_H_
#include "beta.h"

void initProtoHandling(void);
void freeProtoHandling(void);
void exportProtoType(Object *theObj);
void importProtoType(Object *theObj);

#endif /* _PROTO_H_ */
