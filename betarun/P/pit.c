#include "beta.h"

#ifdef PERSIST
#include "sequenceTable.h"
#include "referenceTable.h"

/* The proxy indirection table maps proxy references, which are
 * references into memory protected areas to reference info
 * objects. When a proxy is followed a trap occurs. Then the proxy is
 * uniquely mapped to a reference info object. This info object
 * contains information on which store and offset the referred object
 * recides at. Then a lookup is made in the transit object table to
 * see if the object has been loaded already. If so a reference to the
 * object is returned immediately. If not in th etransit object table
 * the object is loaded and inserted in the trasit object table. At
 * the next IOAGc all objects in the transit object table are
 * 'flushed' in the sense that all references to them are unswizzled
 * and they are removed from the transit object table. Henceforth the
 * object is directly referred and no trap occurs.
 */

/* LOCAL CONSTANTS */
#define MAXENTRIES        PERSIST_MAXENTRIES
#define INITIALENTRIES    128

/* LOCAL VARIABLES */
/* the 'map' is a list of reference info objects. */
static sequenceTable *map = NULL;

/* LOCAL FUNCTION DECLARATIONS */
static int STisFree(void *current);
static void STfree(void *current);

/* FUNCTIONS */
/* 'isFree' should return true if an entry in the 'map' is free */
static int STisFree(void *current) 
{
   RefInfo **refInfo;
   
   refInfo = (RefInfo **)current;
   
   return (*refInfo == NULL);
}

/* 'Free' is used when freeing an entry. Since the reference info
 * object is garbage collected by the beta collector there is no need
 * to explicitly free it here
 */
static void STfree(void *current) 
{
   ;
}

void PITalloc(void)
{  
   /* Allocate protected area for proxies */
   
   if (!PIT) {
      /* Allocate mmapped proxy indirection table. */
      PIT = newProtectedArea((unsigned long) MAXENTRIES);
      PITLimit = (void *)((unsigned long)PIT + (unsigned long)MAXENTRIES);
   }
   
   /* Allocate new map */
   if (!map) {
      map = STInit(INITIALENTRIES,
                   STisFree,
                   STfree,
                   sizeof(RefInfo));
   }
   
#if !MMAPANYADDR
   Claim((unsigned long)PITLimit < 0x7fffffff,
         "PIT must be in positive adresses");
#endif
}

void *PITinsert(RefInfo *refInfo)
{
   u_long inx;
   void *ip;
   
   inx = STInsert(&map, &refInfo);
   ip = (void *)((unsigned long )PIT + inx);
   refInfo -> ip = ip;

   return ip;
}

RefInfo *PITlookup(void *ip)
{
   u_long inx;
   RefInfo **refInfo;
   
   inx = (u_long)ip - (u_long)PIT;
   
   refInfo = STLookup(map, inx);
   
   Claim(inAOA(*refInfo), "Where is the ref info ?");
   
   return *refInfo;
}

void PITfree(RefInfo *refInfo) 
{
   u_long inx;
   RefInfo **ri;
   
   inx = (u_long)(refInfo -> ip) - (u_long)PIT;
   ri = STLookup(map, inx);

   Claim(inAOA(*ri), "Where is the reference info?");
   
   *ri = NULL;
}

#endif /* PERSIST */
