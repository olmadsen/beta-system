#ifndef _P_PSTORESERVER_H_
#define _P_PSTORESERVER_H_
#include "objectStore.h"

char *crossStoreTableName(BlockID store);
char *objectStoreName(BlockID store);
BlockID getNextBlockID(void);
u_long openWriteExt(u_long name_r);
u_long openReadExt(u_long name_r);
u_long deleteExt(u_long name_r);
u_long createExt(u_long name_r);
u_long putExt(u_long dooverwrite, u_long name_r, Object *theObj);

#endif /* _P_PSTORESERVER_H_ */
