/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * copyobject.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#ifdef PERSIST
#include "../P/misc.h"
#include "../P/specialObjectsTable.h"
#endif /* PERSIST */

void copyobj_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

/*
 * CopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 */

static Object * CopyObject(Object * theObj)
{
    Object * newObj;
    long        size;
    
    size = 4*ObjectSize( theObj);
    Claim(isObject(theObj), "isObject(theObj)");
    
    
    /* Assure that IOAMinAge <= theObj->GCAttr <= IOAMaxAge. */
    Claim(IOAMinAge <= theObj->GCAttr,
	  "CopyObject: IOAMinAge <= Age of object.");
    Claim(theObj->GCAttr<=IOAMaxAge,
	  "CopyObject: Age of object<=IOAMaxAge.");
    
    if (theObj->GCAttr==IOAMaxAge) theObj->GCAttr--;
    IOAAgeTable[theObj->GCAttr-IOAMinAge] += size;
    
    DEBUG_AOA( IOAcopied += size );

    {
	register long * src;
	register long * dst;
	register long * theEnd;
	
	newObj     = (Object *) ToSpaceTop;
	theEnd     = (long *) (((long) newObj) + size); 
	
	Claim(theEnd<=ToSpaceLimit, "theEnd<=ToSpaceLimit");
	
	ToSpaceTop = theEnd;

	/* Check if ToSpace grows into AOAroots table 
	 * (residing in upper part of ToSpace) 
	 */
	if( !tempAOAroots &&
            (char *) ToSpaceTop+size > (char *) AOArootsPtr ){
            tempAOArootsAlloc();
	}
        
	src = (long *) theObj; dst = (long *) newObj; 
        
	while( dst < theEnd) *dst++ = *src++; 
	
    }
    /* Increase the age of the object */
    if( newObj->GCAttr < IOAMaxAge ) newObj->GCAttr++;
    
    /* Set one forward reference in theObj to newObj */
    theObj->GCAttr = (long) newObj;
    
    /* Return the new object in ToSpace */
    return newObj;
}

/*
 * NewCopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 *  If theCell is not 0 it should be treated as an AOA root, in case
 *  theObj is moved to AOA.
 *  The function is used by IOAGc.
 */
Object * NewCopyObject(Object * theObj, Object ** theCell)
{
  MCHECK();
  
  if (theObj->GCAttr < IOAtoAOAtreshold) {
    /* theObj is not old enough for AOA */
    return CopyObject(theObj);
    
  } else {
    /* theObj is old enough to go into AOA */
    Object * newObj;
#ifdef PERSIST
    long GCAttribute;
#endif /* PERSIST */
    MCHECK();

#ifdef PERSIST
    GCAttribute = theObj -> GCAttr;
#endif /* PERSIST */

    if ((newObj = CopyObjectToAOA(theObj))) {
      /* Insert theCell in AOAroots table. 
       * Used as roots in AOA GC if invoked after IOAGc.
       */
      MCHECK();
      if (theCell) {
	Claim(!inAOA(theCell), "!inAOA(theCell)");
	MCHECK();
	saveAOAroot(theCell);
	MCHECK();
      }

#ifdef PERSIST
      if (GCAttribute == IOAPersist) {
	/* KKK: We have just moved a persistent object to AOA. The
	   object is registered so that we can create an entry for it
	   in the ObjectTable, and mark it as persistent when this
	   IOAGc has finished. We cannot do it now as the GCAttribute
	   of the new object in AOA is needed by IOAGc. */
	delayedInsert(newObj);
      } else if (GCAttribute == IOASpecial) {
	insertSpecialObject(getTagForObject(theObj), newObj);
      }
#endif /* PERSIST */
      return newObj;
      
    } else {
      /* CopyObjectToAOA failed */
#ifdef PERSIST
      if ((theObj -> GCAttr != IOASpecial) && (theObj -> GCAttr != IOAPersist)) {
	return CopyObject(theObj);
      } else {
	Object *theAOAObj;
	
	forceAOAAllocation = TRUE;
	theAOAObj = NewCopyObject(theObj, theCell);
	forceAOAAllocation = FALSE;
	
	Claim(inAOA(theAOAObj), "Where is theAOAObj?");
	
	return theAOAObj;
      }
#else 
      return CopyObject(theObj);
#endif /* PERSIST */
    }
  }
}
