#ifndef _DOMAIN_H_
#define _DOMAIN_H_
#include "beta.h"

#define DEFAULTDOMAIN -1

unsigned long newDomain(Structure *structure);
unsigned long getDomain(Object *theObj);

#endif /* _DOMAIN_H_ */
