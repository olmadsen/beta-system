#ifndef _DOMAIN_H_
#define _DOMAIN_H_
#include "beta.h"

#define DEFAULTDOMAIN -1

u_long newDomain(Structure *structure);
u_long getDomain(Object *theObj);

#endif /* _DOMAIN_H_ */
