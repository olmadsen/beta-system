#ifndef _P_PSTORESERVER_H_
#define _P_PSTORESERVER_H_
#include "PStore.h"

char *crossStoreTableName(unsigned long store);
char *objectStoreName(unsigned long store);

unsigned long openWriteExt(unsigned long host_r, unsigned long path_r);
unsigned long openReadExt(unsigned long host_r, unsigned long path_r);
unsigned long deleteExt(unsigned long host_r, unsigned long path_r);
unsigned long createExt(unsigned long host_r, unsigned long path_r);
unsigned long putExt(unsigned long dooverwrite, 
		     unsigned long host_r, 
		     unsigned long path_r,
		     unsigned long name_r,
		     Object *theObj);
void closeExt(unsigned long host_r, unsigned long path_r);
char *DBname(char *path);

#endif /* _P_PSTORESERVER_H_ */
