#ifndef _P_PSTORESERVER_H_
#define _P_PSTORESERVER_H_

char *crossStoreTableName(unsigned long store);
char *objectStoreName(unsigned long store);
unsigned long openWriteExt(unsigned long name_r);
unsigned long openReadExt(unsigned long name_r);
unsigned long deleteExt(unsigned long name_r);
unsigned long createExt(unsigned long name_r);
unsigned long putExt(unsigned long dooverwrite, unsigned long name_r, Object *theObj);
void closeExt(void);
unsigned long isOpen(void);

#endif /* _P_PSTORESERVER_H_ */
