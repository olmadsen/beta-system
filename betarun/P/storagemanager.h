#ifndef _STORAGEMANAGER_H_
#define _STORAGEMANAGER_H_
#include "beta.h"

#ifdef PERSIST

#ifndef ppcmac
#include <sys/types.h>
#endif

void SMinit(void);
void SMopen(CAStorage *csb);
void SMGC(void);

#endif /* PERSIST */
#endif /* _STORAGEMANAGER_H_ */
