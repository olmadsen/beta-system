#include "beta.h"

#ifdef PERSIST
#include "referenceTable.h"
#include "sequenceTable.h"
#include "trie.h"
#include "objectTable.h"
#include "PException.h"
#include "misc.h"
#include "storageblock.h"
#include "pit.h"

/* LOCAL TYPES */

/* LOCAL DEFINITIONS */

/* LOCAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */

/* FUNCTIONS */
void initTransitObjectTable(void)
{
   ;
}

void insertObjectInTransit(CAStorage *store,
                           unsigned long offset,
                           Object *theObj)
{
   void *ip;
   RefInfo *refInfo;
   
   if ((ip = lookupReferenceInfo(store, offset)) != NULL) {
      ;
   } else {
      ip = referenceInfo(store, offset);
   }

   refInfo = PITlookup(ip);
   refInfo -> objInTransit = theObj;
}

void redirectAOACells(Array *clients, Object *from, Object *to)
{
   unsigned long max, count;
   Object **theCell;
  
   if (clients) {
      max = clients -> top;
      
      for (count = 0; count < max; count++) {
         theCell = (Object **)(clients -> theCells[count]);
         if (*theCell == from) {
            Claim(inAOA(to), "Where is the object?");
            
            *theCell = to;
            
            Claim(*theCell != NULL, "Assigning NULL");
         }
      }
   }
}

#endif /* PERSIST */
