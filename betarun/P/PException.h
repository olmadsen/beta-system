#ifndef _PEXCEPTION_H_
#define _PEXCEPTION_H_
#include "beta.h"

Object *newPUID(unsigned long offset);
unsigned long getPUID(void *ip);
#ifdef UNIX
void initProxyTrapHandler(void);
#endif
void printProxyStatistics(void);
void PITAlloc(void);

#endif /* _PEXCEPTION_H_ */
