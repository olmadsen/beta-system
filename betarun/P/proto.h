#ifndef _PROTO_H_
#define _PROTO_H_
#include "beta.h"

extern CAStorage *currentcsb;

void initProtoHandling(void);
void freeProtoHandling(void);
void exportProtoType(Object *theObj);
void importProtoType(Object *theObj);
void protoAddrToID(ProtoType *theProto,
                   unsigned long *group,
                   unsigned long *protoNo);
ProtoType *translateStoreProto(ProtoType *theProto, CAStorage *store);

#endif /* _PROTO_H_ */
