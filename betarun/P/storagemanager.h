#ifndef _STORAGEMANAGER_H_
#define _STORAGEMANAGER_H_
#include "../C/beta.h"

#ifdef PERSIST
#include <sys/types.h>

void SMinit(void);
void SMopen(CAStorage *csb);
void SMGC();

#endif /* PERSIST */
#endif /* _STORAGEMANAGER_H_ */
