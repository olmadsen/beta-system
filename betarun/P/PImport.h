#ifndef _PIMPORT_H_
#define _PIMPORT_H_
#include "beta.h"
#include "storageblock.h"

void importStoreObject(Object *theObj, 
                       CAStorage *store,
                       u_long offset,
                       u_long inx,
                       u_long follow);
#endif /* _PIMPORT_H_ */
