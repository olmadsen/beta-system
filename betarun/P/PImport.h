#ifndef _PIMPORT_H_
#define _PIMPORT_H_
#include "beta.h"

void importStoreObject(Object *theObj, 
		       unsigned long store, 
		       unsigned long offset, 
		       unsigned long inx);
Object *importReference(unsigned long storeOfReferredObject, 
			unsigned long offsetOfReferredObject, 
			Object **theCell);

#endif /* _PIMPORT_H_ */
