#ifndef _PEXCEPTION_H_
#define _PEXCEPTION_H_
#include "beta.h"

Object *newPUID(u_long offset);
u_long getPUID(void *ip);
int inPIT(void *ip);
#ifdef UNIX
void initProxyTrapHandler(void);
#endif
void printProxyStatistics(void);
void PITAlloc(void);

#endif /* _PEXCEPTION_H_ */
