#include "beta.h"

#ifdef PERSIST

#include "misc.h"
#include "objectTable.h"
#include "referenceTable.h"
#include "storageblock.h"
#include "PException.h"
#include "unswizzle.h"
#include "specialObjectsTable.h"
#include "trie.h"
#include "dot.h"

/* IMPORTS */
extern int betaenvHandle; 
extern int programHandle;

/* LOCAL VARIABLES */

/* LOCAL FUNCTION DECLARATIONS */

/* FUNCTIONS */
void MIstart(void)
{
    ;
}

void MIend(void)
{
   ;
}

void markSpecialObject(Object *theObj, unsigned long tag)
{
    Object *realObj, *currentBetaenvObj, *currentProgramObj;

    currentBetaenvObj = DOThandleLookup(betaenvHandle);
    currentProgramObj = DOThandleLookup(programHandle);
  
    if (tag == BETAENVOBJ) {
        if (theObj != currentBetaenvObj) {
            fprintf(output, "markSpecialObject: Tag %d may only be used for BETAENV (this *will* cause problems soon, use another tag value for this object)\n", BETAENVOBJ);
        }
    }
  
    if (tag == PRGOBJ) {
        if (theObj != currentProgramObj) {
            fprintf(output, "markSpecialObject: Tag %d may only be used for PROGRAM (this *will* cause problems soon, use another tag value for this object)\n", PRGOBJ);
        }
    }
  
#ifndef sparc
    if (theObj != currentBetaenvObj) {
        if (theObj != currentProgramObj) {
            fprintf(output, "markSpecialObject: This platform does not support handling of user registered special objects");
        }
    }
#endif /* sparc */
  
    realObj = getRealObject(theObj);
  
    if (inIOA(realObj)) {
        realObj -> GCAttr = IOASpecial;
        saveTagForObject(realObj, tag & 0x000000FF);
    } else {
        insertSpecialObject(tag, realObj);
    }
}

/* markPersistentObject,
 *
 * Marks the new object as persistent, used to mark the root object
 * when creating a new store. The root object is in fact the root list.
 */
void markPersistentObject(CAStorage *ID, Object *obj)
{   
   setCurrentStoreID(ID);
   markObject(obj, 0);
}

#endif /* PERSIST */
