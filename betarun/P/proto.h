#ifndef _PROTO_H_
#define _PROTO_H_
#include "beta.h"

void protoAddrToID(ProtoType *theProto, u_long *group, u_long *protoNo);
ProtoType *IDtoProtoAddr(u_long group, u_long protoNo);
void exportProtoTypes(Object *theObj);
void importProtoTypes(Object *theObj);
u_long StoreObjectSize(Object * theObj);
void initProtoHandling(void);
void freeProtoHandling(void);

#endif /* _PROTO_H_ */
