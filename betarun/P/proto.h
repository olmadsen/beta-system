#ifndef _PROTO_H_
#define _PROTO_H_
#include "beta.h"

void protoAddrToID(ProtoType *theProto, unsigned long *group, unsigned long *protoNo);
ProtoType *IDtoProtoAddr(unsigned long group, unsigned long protoNo);
void exportProtoTypes(Object *theObj);
void importProtoTypes(Object *theObj);
unsigned long StoreObjectSize(Object * theObj);
void initProtoHandling(void);
void freeProtoHandling(void);

#endif /* _PROTO_H_ */
