#ifndef _P_PIT_H_
#define _P_PIT_H_

void PITalloc(void);
void *PITinsert(RefInfo *refInfo);
RefInfo *PITlookup(void *ip);
void PITfree(RefInfo *refInfo);

#endif /* _P_PIT_H_ */
