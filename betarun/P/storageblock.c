#include "beta.h"

/* storageblock.c
 *
 * A storage block is one 32bit addressable collection of persistent
 * objects. If a persistent store cannot be contained in a single
 * storage block, it is possible to use as many storage blocks as
 * necessary.
 *
 * A storage block consists of several dynamically extendable areas,
 *
 * - SBINReferences. All references from other storage blocks into this
 *   one goes via a table of incomming references. This way the
 *   storage block can relocate externally referred objects.
 *
 * - SBOUTReferences. All references to other storage blocks goes via a
 *   table of outgoing references. This way an unlimited number of
 *   storage blocks can be referred.
 *
 * - SBGroupNames. A prototype can be identified by a the name of the
 *   group to which it belongs and the offset of the prototype in that
 *   group (for further details, see elsewhere). When a prototype is
 *   exported to storage the name of the group to which it belongs
 *   must be saved in order to enable rebinding of the prototype at a
 *   later load. This area saves all group names. The position of a
 *   groupname within this area is a unique idetification of the
 *   groupname. This ID can be saved as part of the exported
 *   prototype.
 *
 * - SBObjects. Holds the persistent objects in this storage block.
 *
 * Storage blocks are implemented by using a cached dynamical
 * extendable storage area as implemented by the modules 'des.c' and
 * 'cache.c'.
 *
 * */

#ifdef PERSIST

#include "des.h"
#include "cache.h"
#include "storageblock.h"
#include "storagemanager.h"
#include "error.h"
#include "PSfile.h"
#include "objectTable.h"

#ifdef PSENDIAN
/* Get definition of ntohl */
#ifdef linux
# include <sys/types.h>
# include <netinet/in.h>
#else
# include "winsock.h"
#endif 
#endif 

#define SBINReferences  0
#define SBOUTReferences 1
#define SBGroupNames    2
#define SBObjects       3

#define SBINITIALNUMINREFS 8
#define SBINITIALSIZEOUTREFS 1024
#define SBINITIALSIZEGROUPNAMES 1024*128
#define SBINTIALSIZEOBJECTS 1024

typedef struct sbinreference
{
    u_long offset; /* offset of referred object in the object area */
} SBINreference;

typedef struct sboutreference
{
    u_long sizehostname;
    char *host;
    u_long sizepathname;
    char *path;
    u_long refID;
} SBOUTreference;

typedef struct sbgroupname
{
    u_long sizegroupname;
    char *groupname;
} SBGgroupName;
    
/* Local variables */
static u_long objects;

/* Local function declarations */
static char *DBname(char *path, int checkdirectory /* backward compatibility */);

/* */
CAStorage *SBcreate(char *host, char *path)
{
   CAStorage *csb; /* cached storage block */
   DEStorage *des; /* dynamic extendable storage */
   if (!isDir(path)) {
     /*if (createDirectory(path
#ifdef UNIX
                         , S_IFDIR | S_IREAD | S_IWRITE | S_IEXEC 
#endif
#ifdef nti
                         , 0
#endif 
#ifdef MAC
						, 0
#endif
) >= 0) {         */
     if (!fileExists(path)) {
       char *dbn = DBname(path, 0);
       
       /* First we create the dynamic extendable storage used to hold
          * this storage block.
          */
         des = DEScreate(host, dbn, TRUE);
         
         if ((u_long)des > MAXERROR) {
            /* Turn on caching for the storage block.
             */
            csb = CAcreate(des);
            
            /* Now we append the needed 'dynamically extendable areas'.
             */
            
            /* SBINReferences. All references from other storage
             *                 blocks into this one goes via a table
             *                 of incomming references. This way the 
             *                 storage block can relocate externally
             *                 referred objects.
             */
            if (CAarea(csb, SBINITIALNUMINREFS * sizeof(struct sbinreference)) ==
                SBINReferences) {
               /* That DESarea is supposed to return 'SBINReferences'
                * the first time it is called seems magical, but for
                * now we use our knowledge about the implementation
                * of 'des.c'. Alternatively the number of the
                * inreferences area should be saved along with the
                * store as well.
                */

               /* SBOUTReferences. All references to other storage
                *                  blocks goes via a table of
                *                  outgoing references. This way an
                *                  unlimited number of storage
                *                  blocks can be referred
                */
               if (CAarea(csb, SBINITIALSIZEOUTREFS) == SBOUTReferences) {

                  /* - SBGroupNames. A prototype can be identified
                   *   by a the name of the group to which it
                   *   belongs and the offset of the prototype in
                   *   that group (for further details, see
                   *   elsewhere). When a prototype is exported to
                   *   storage the name of the group to which it
                   *   belongs must be saved in order to enable
                   *   rebinding of the prototype at a later
                   *   load. This area saves all group names. The
                   *   position of a groupname within this area is a
                   *   unique idetification of the groupname. This
                   *   ID can be saved as part of the exported
                   *   prototype.
                   */
                    
                  if (CAarea(csb, SBINITIALSIZEGROUPNAMES) == SBGroupNames) {
                        
                     /* - SBObjects. Holds the persistent objects
                      *              in this storage block.
                      */
                        
                     if (CAarea(csb, SBINTIALSIZEOBJECTS) == SBObjects) {
                        SMopen(csb);
                        csb -> open = 1;
                        return csb;
                     } else {
                        /* XXX: free cas needed */
                        return (CAStorage *)CREATIONERRORERROR;
                     }
                  } else {
                     /* XXX: free cas needed */
                     return (CAStorage *)CREATIONERRORERROR;
                  }
               } else {
                  /* XXX: free cas needed */
                  return (CAStorage *)CREATIONERRORERROR;
               }
            } else {
               /* XXX: free cas needed */
               return (CAStorage *)CREATIONERRORERROR;
            }
         } else {
            DESdestroy(des);
            return (CAStorage *)CREATIONERRORERROR;
         }
      } else {
         return (CAStorage *)CREATIONERRORERROR;
      }
   } else {
      return (CAStorage *)EXISTSERROR;
   }
}

u_long SBstat(CAStorage *csb)
{
    return (csb -> open);
}

CAStorage *SBopen(char *host, char *path)
{
   DEStorage *des; /* dynamic extendable storage */
   char *dbn = DBname(path, 1);
   u_long rcode;
    /* First we create the dynamic extendable storage used to hold
     * this storage block.
     */
   des = DEScreate(NULL, NULL, FALSE);
   
   rcode = DESattach(des, host, dbn);
   
   if (rcode == 0) {
      CAStorage *csb; /* cached storage block */
      
      /* turn on caching for the store */
      csb = CAcreate(des);
      
      /* Mark the block as opened */
      SMopen(csb);
      csb -> open = 1;
      return csb;
   } else {
      return (CAStorage *)rcode;
   }
}

/* */
void SBclose(CAStorage *csb)
{

  /* fprintf(stderr, "SBclose(csb=0x%08x)\n", (int)csb); fflush(stderr); */

   /* Unpersistify objects in memory */
   closeStore(csb);
   
   /* Flush cache */
   CAflush(csb);
   
   /* flush header */
   DESflush(csb -> des);
   
   /* free memory */
   /* CAdestroy(csb);
   
      memset(csb, 0, sizeof(struct castorage));
   */
}

/*
 * Methods on the in reference area
 *
 *
 *
 */

u_long /* in reference id */ SBINREFcreate(CAStorage *csb, u_long offset)
{
    u_long id;
    SBINreference sbin;

    Claim(csb -> open, "Store closed");

#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBINREFcreate: offset = 0x%X\n", (int)offset);
#endif /* DEBUGPERSISTENCE */
    
    /* Allocate room for a new in reference */
    id = CAallocate(csb, SBINReferences, sizeof(struct sbinreference));
    
    /* Write the offset in the id */
#ifdef PSENDIAN
    sbin.offset = htonl(offset);
#else
    sbin.offset = offset;
#endif
    CAsave(csb, SBINReferences, (char *)&sbin, id, sizeof(struct sbinreference));
    
#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBINREFcreate: id = 0x%X\n", (int)id);
#endif /* DEBUGPERSISTENCE */

    return id;
}

u_long /* offset */ SBINREFlookup(CAStorage *csb, u_long id)
{
    SBINreference sbin;
    
    Claim(csb -> open, "Store closed");

    CAload(csb, SBINReferences, (char *)&sbin, id, sizeof(struct sbinreference));
#ifdef PSENDIAN
    sbin.offset = ntohl(sbin.offset);
#endif
    return sbin.offset;
}

/*
 * Methods on the out reference area
 *
 *
 *
 */

u_long /* out reference id */ SBOUTREFcreate(CAStorage *csb,
                                             char *host,
                                             char *path,
                                             u_long id)
{
    u_long hostnamelength, pathnamelength, alignedsize;
    u_long hostnamelengthendian, pathnamelengthendian;
    u_long outid, idendian;
    
    Claim(csb -> open, "Store closed");
    
#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBOUTREFcreate: host = %s, path = %s, id = 0x%X\n",
            host,
            path,
            (int)id);
#endif /* DEBUGPERSISTENCE */

    /* See comment (1) below for explenation of the alignment below.
     */
    hostnamelength = strlen(host);
    pathnamelength = strlen(path);
        
    alignedsize = sizeof(u_long) * 3 + hostnamelength + pathnamelength;
    alignedsize = ((alignedsize >> TAGBITS) << TAGBITS) + (1 << TAGBITS);
    
    /* Allocate room for a new in reference */
    outid = CAallocate(csb, SBOUTReferences, alignedsize);

    /* Write hostname length */
#ifdef PSENDIAN
    hostnamelengthendian = htonl(hostnamelength);
#else
    hostnamelengthendian = hostnamelength;
#endif    
    CAsave(csb, SBOUTReferences,
           (char *)&hostnamelengthendian,
           outid,
           sizeof(u_long));
    
    /* Write hostname */
    CAsave(csb, SBOUTReferences,
           (char *)host,
           outid + sizeof(u_long),
           hostnamelength);

    /* Write pathname length */
#ifdef PSENDIAN
    pathnamelengthendian = htonl(pathnamelength);
#else
    pathnamelengthendian = pathnamelength;
#endif
    CAsave(csb, SBOUTReferences,
           (char *)&pathnamelengthendian,
           outid + sizeof(u_long) + hostnamelength,
           sizeof(u_long));
    
    /* Write pathname */
    CAsave(csb, SBOUTReferences,
           (char *)path,
           outid + sizeof(u_long) * 2 + hostnamelength,
           pathnamelength);
    
    /* write id */
#ifdef PSENDIAN
    idendian = htonl(id);
#else
    idendian = id;
#endif
    CAsave(csb, SBOUTReferences,
           (char *)&idendian,
           outid + sizeof(u_long) * 2 + hostnamelength + pathnamelength,
           sizeof(u_long));
    
    
#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBOUTREFcreate: outid = 0x%X\n",
            (int)outid);
#endif /* DEBUGPERSISTENCE */

    return outid | OUTREFERENCE;
}

void SBOUTREFlookup(CAStorage *csb,
                    u_long outid,
                    char **host,
                    char **path,
                    u_long *id)
{
    u_long hostnamelength, pathnamelength;

    Claim(csb -> open, "Store closed");
    Claim(isOutReference(outid), "SBOUTREFlookup: Illegal out reference");
    
    CAload(csb, SBOUTReferences, (char *)&hostnamelength, outid, sizeof(u_long));
#ifdef PSENDIAN
    hostnamelength = ntohl(hostnamelength);
#endif
    *host = (char *)malloc(sizeof(char)*(hostnamelength + 1));
    CAload(csb, SBOUTReferences, *host, outid + sizeof(u_long), hostnamelength);
    *host[hostnamelength] = 0;
    
    CAload(csb, SBOUTReferences, (char *)&pathnamelength,
           outid + sizeof(u_long) + hostnamelength, sizeof(u_long));
#ifdef PSENDIAN
    pathnamelength = ntohl(pathnamelength);
#endif
    *path = (char *)malloc(sizeof(char)*(pathnamelength + 1));
    CAload(csb, SBOUTReferences, *path,
           outid + 2*sizeof(u_long) + hostnamelength, pathnamelength);
    *path[pathnamelength] = 0;

    CAload(csb, SBOUTReferences, (char *)id,
           outid + 2*sizeof(u_long) + hostnamelength + pathnamelength, sizeof(u_long));
#ifdef PSENDIAN
    *id = ntohl(*id);
#endif    
    return;
}
    
/*
 * Methods on the groupname area
 *
 *
 *
 */
u_long /* group name id */ SBGNcreate(CAStorage *csb, char *groupname)
{
    u_long groupid;
    u_long length, lengthendian;

    Claim(csb -> open, "Store closed");

#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBGNcreate: groupname = %s\n",
            groupname);
#endif /* DEBUGPERSISTENCE */

    length = strlen(groupname);
    
    /* Allocate room for a new groupname */
    groupid = CAallocate(csb, SBGroupNames, sizeof(u_long) + length);
    
    /* write length */
#ifdef PSENDIAN
    lengthendian = htonl(length);
#else
    lengthendian = length;
#endif
    CAsave(csb, SBGroupNames, (char *)&lengthendian, groupid, sizeof(u_long));
    
    /* Write groupname */
    CAsave(csb, SBGroupNames, groupname, groupid + sizeof(u_long), length);
    
#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBGNcreate: groupid = 0x%X\n",
            (int)groupid);
#endif /* DEBUGPERSISTENCE */
    
    return groupid;    
}

static char *buffer = NULL;
static u_long bufferlength = 0;

char *SBGNlookup(CAStorage *csb, u_long id, u_long *length)
{
   Claim(csb -> open, "Store closed");

   /* load length */
   CAload(csb, SBGroupNames, (char *)length, id, sizeof(u_long));
#ifdef PSENDIAN
   *length = ntohl(*length);
#endif
   if (*length + 1 < bufferlength) {
      CAload(csb, SBGroupNames, buffer, id + sizeof(u_long), *length);
      buffer[*length] = '\0';
      return buffer;
   } else {
      if (buffer) {
         free(buffer);
      }
      bufferlength = bufferlength*2 + 1;
      buffer=(char *)malloc(sizeof(char)*bufferlength);
      return SBGNlookup(csb, id, length);
   }
}

u_long SBGNtop(CAStorage *csb)
{
    Claim(csb -> open, "Store closed");

    return DESsize(csb -> des, SBGroupNames);
}
    
/*
 * Methods on the object area
 *
 *
 *
 */
u_long /* object id */ SBOBJcreate(CAStorage *csb, char *obj, u_long nb)
{
    u_long oid, alignedsize;
    u_long nbendian;
    
    Claim(csb -> open, "Store closed");

#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBOBJcreate: nb = 0x%X\n",
            (int)nb);
#endif /* DEBUGPERSISTENCE */

    /* (1) In order to handle references to objects in other storage
     * blocks, to types of references must be allowed. One type is
     * references into the object area to objects in the same storage
     * block. The other type of references are references into the out
     * references area to proxies. Due to the lack of obvious better
     * options, we tag references into the out references area, so
     * that they may be distinguished from references into the
     * object area.
     *
     * References into the object area aligned to 8 byte boundaries in
     * order to allow for this tagging.
     */

    /* The object must not be a part object */

    /* Allocate room for the object and size */
    alignedsize = nb + sizeof(u_long);
    if (alignedsize & ((1 << TAGBITS) - 1)) {
        alignedsize = ((alignedsize >> TAGBITS) << TAGBITS) + (1 << TAGBITS);
    }
    oid = CAallocate(csb, SBObjects, alignedsize);
    
    /* Write object size */
#ifdef PSENDIAN
    nbendian = htonl(nb);
#else
    nbendian = nb;
#endif
    CAsave(csb, SBObjects, (char *)&nbendian, oid, sizeof(u_long));

    /* Write object to area */
    CAsave(csb, SBObjects, obj, oid + sizeof(u_long), nb);

#ifdef DEBUGPERSISTENCE
    fprintf(output, "SBOBJcreate: oid = 0x%X\n",
            (int)oid);
#endif /* DEBUGPERSISTENCE */

    return oid + sizeof(u_long);
}


void SBOBJsave(CAStorage *csb, char *obj, u_long oid, u_long nb)
{
   u_long nbendian;
   
#ifdef DEBUGPERSISTENCE
   fprintf(output, "SBOBJsave: oid = 0x%X, nb = 0x%X\n",
           (int)oid,
           (int)nb);
#endif /* DEBUGPERSISTENCE */

    Claim(csb -> open, "Store closed");
   /* The object must not be a part object */
   
   /* Write object size */
#ifdef PSENDIAN
   nbendian = htonl(nb);
#else
   nbendian = nb;
#endif
   CAsave(csb, SBObjects, (char *)&nbendian, oid - sizeof(u_long), sizeof(u_long));
   
   /* Write object to area */
   CAsave(csb, SBObjects, obj, oid, nb);
}

u_long getNumberOfUpdates(CAStorage *csb)
{
    Claim(csb -> open, "Store closed");

   return csb -> updates;
}

/* oid is offset in store */
u_long SBOBJload(CAStorage *csb, u_long oid, void *obj, u_long objSize)
{
   Claim(csb -> open, "Store closed");
   CAload(csb, SBObjects, (char *)obj, oid, objSize);
   return 0;
}

/* oid is offset in store */
u_long SBOBJlookup(CAStorage *csb, u_long oid, u_long *objSize)
{
    u_long GCAttr;

    Claim(csb -> open, "Store closed");

    /* read GCAttribute, 4 bytes ahead in the object */
    CAload(csb, SBObjects, (char *)&GCAttr, oid + sizeof(u_long), sizeof(u_long));

    if (GCAttr == 0) {
       /* Autonomous object - read size right before object */
       CAload(csb, SBObjects, (char *)objSize, oid - sizeof(u_long), sizeof(u_long));
#ifdef PSENDIAN
       *objSize = ntohl(*objSize);
#endif       
       return oid;
    } else {
      /* part object */
       u_long distance;
       
#ifdef PSENDIAN
       distance = -4 * ntohl(GCAttr);
#else
       distance = -4 * GCAttr;
#endif
       return SBOBJlookup(csb, oid - distance, objSize);
    }
}

u_long SBOBJpresent(CAStorage *csb, u_long oid)
{
    Claim(csb -> open, "Store closed");

    return CApresent(csb, SBObjects, oid);
}

/* Endian conversions */

/* Profiling */
void SBstart(void)
{
    objects = 0;
}

void SBend(void)
{
    fprintf(stderr, "objects: %d\n", (int)objects);
}
             
/* Local functions */
#define MAXDBNAMELENGTH 512
#define DBNAME "db"

static char dbname[MAXDBNAMELENGTH];

static char *DBname(char *path, int checkdir)
{
  if (checkdir && isDir(path)) {
    if (strlen(path) + strlen(DBNAME) + 1 < MAXDBNAMELENGTH) {
      sprintf(dbname, "%s/%s", path, DBNAME);
      return &dbname[0];
    } else {
      fprintf(output, "DBname: path name length exceeded only %d characters are allowed\n", MAXDBNAMELENGTH - strlen(DBNAME) - 1);
      BetaExit(1);
      return NULL;
    }
    if (fileExists(dbname)) {
      return &dbname[0];
    } else {
      checkdir = 0;
    }
  }
  else {
    checkdir = 0;
  }

  if (checkdir) {
    if (strlen(path) + strlen(DBNAME) + 1 < MAXDBNAMELENGTH) {
      sprintf(dbname, "%s/%s", path, DBNAME);
      return &dbname[0];
    } else {
      fprintf(output, "DBname: path name length exceeded only %d characters are allowed\n", MAXDBNAMELENGTH - strlen(DBNAME) - 1);
      BetaExit(1);
      return NULL;
    }
  } else {
    if (strlen(path)+1 < MAXDBNAMELENGTH) {
      sprintf(dbname, "%s.pst", path);
      return &dbname[0];
    } else {
      fprintf(output, "DBname: path name length exceeded only %d characters are allowed\n", MAXDBNAMELENGTH - strlen(DBNAME) - 1);
      BetaExit(1);
      return NULL;
    }
  }
}

#endif /* PERSIST */
