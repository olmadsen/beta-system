/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * copyobject.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

/*
 * CopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 */

static Object * CopyObject(Object * theObj)
{
    Object * newObj;
    long        size;
    
    size = 4*ObjectSize( theObj);
    DEBUG_CODE( Claim(ObjectSize(theObj) > 0, "#CopyObject: ObjectSize(theObj) > 0") );
    
    /* Assure that IOAMinAge <= theObj->GCAttr <= IOAMaxAge. */
    DEBUG_IOA( Claim(IOAMinAge <= theObj->GCAttr,
		     "CopyObject: IOAMinAge <= Age of object."));
    DEBUG_IOA( Claim( theObj->GCAttr<=IOAMaxAge,
		     "CopyObject: Age of object<=IOAMaxAge."));
    
    if (theObj->GCAttr==IOAMaxAge)
      theObj->GCAttr--;
#ifdef KEEP_STACKOBJ_IN_IOA
    if (!isStackObject(theObj))
      IOAAgeTable[theObj->GCAttr-IOAMinAge] += size;
    else {
	IOAStackObjectSum += size;
	IOAStackObjectNum++;
    }
#else
    IOAAgeTable[theObj->GCAttr-IOAMinAge] += size;
#endif
      
    
    DEBUG_AOA( IOAcopied += size );
    
    {
	register long * src;
	register long * dst;
	register long * theEnd;
	
	newObj     = (Object *) ToSpaceTop;
	theEnd     = (long *) (((long) newObj) + size); 
	
	DEBUG_IOA( Claim(theEnd<=ToSpaceLimit, "theEnd<=ToSpaceLimit") );
	
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
 * 
 * FIXME: better parameters: (Object **theCell, int useForAOAroot)
 *        will be more readable.
 */
Object * NewCopyObject(Object * theObj, Object ** theCell)
{
    MCHECK();

#ifdef KEEP_STACKOBJ_IN_IOA
    if(isStackObject(theObj)) return CopyObject(theObj);
#endif

    if( theObj->GCAttr < IOAtoAOAtreshold ){
        /* theObj is not old enough for AOA */
        return CopyObject(theObj);
    } else {
        /* theObj is old enough to go into AOA */
        Object * newObj;

        MCHECK();
        if( (newObj = CopyObjectToAOA(theObj)) ){
            /* Insert theCell in AOAroots table. 
             * Used as roots in AOA GC if invoked after IOAGc.
             */
            MCHECK();
            if (theCell) {
                MCHECK();
                saveAOAroot(theCell);
                MCHECK();
            }
            return newObj;
        } else {
            /* CopyObjectToAOA failed */
            return CopyObject(theObj);
        }
    }
}
