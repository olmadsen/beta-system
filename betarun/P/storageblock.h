#ifndef _STORAGEBLOCK_H_
#define _STORAGEBLOCK_H_
#include "beta.h"

#ifdef PERSIST
#ifndef ppcmac
#include <sys/types.h>
#endif
#include "cache.h"
#define ROOTOFFSET 0

#define TAGBITS          2
#define NORMALREFERENCE  0
#define OUTREFERENCE     1
#define SPECIALREFERENCE 2
#define LOADREFERENCE    3
#define MAXTAG           ((1 << TAGBITS) - 1)

#define isSpecialReference(offset) ((offset & MAXTAG) == SPECIALREFERENCE)
#define isOutReference(offset)     ((offset & MAXTAG) == OUTREFERENCE)
#define isLoadReference(offset)    ((offset & MAXTAG) == LOADREFERENCE)
#define isNormalReference(offset)  ((offset & MAXTAG) == NORMALREFERENCE)

/* flags */
#define OPEN (1 << 0)

CAStorage *SBcreate(char *host, char *path);
CAStorage *SBopen(char *host, char *path);
void SBclose(CAStorage *csb);
u_long SBstat(CAStorage *csb);
u_long /* in reference id */ SBINREFcreate(CAStorage *csb, u_long offset);
u_long /* failed */ SBOBJload(CAStorage *csb, u_long oid, void *obj, u_long objSize);
u_long /* offset */ SBINREFlookup(CAStorage *csb, u_long id);
u_long /* out reference id */ SBOUTREFcreate(CAStorage *csb,
                                             char *host,
                                             char *path,
                                             u_long id);
void SBOUTREFlookup(CAStorage *csb,
                    u_long id,
                    char **host,
                    char **path,
                    u_long *outid);
u_long /* groupname id */ SBGNcreate(CAStorage *csb, char *groupname);
char *SBGNlookup(CAStorage *csb, u_long id, u_long *length);
u_long SBGNtop(CAStorage *csb);
u_long /* object id */ SBOBJcreate(CAStorage *csb, char *obj, u_long nb);
void SBOBJsave(CAStorage *csb, char *obj, u_long oid, u_long nb);
u_long SBOBJlookup(CAStorage *csb, u_long oid, u_long *objSize);
void SBstart(void);
void SBend(void);
u_long SBOBJpresent(CAStorage *csb, u_long oid);

#endif /* PERSIST */
#endif /* _STORAGEBLOCK_H_ */
