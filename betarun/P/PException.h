#ifndef _PEXCEPTION_H_
#define _PEXCEPTION_H_
#include "beta.h"

#ifdef UNIX
void initProxyTrapHandler(void);
#endif
void printProxyStatistics(void);

#endif /* _PEXCEPTION_H_ */
