/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990 Mjolner Informatics Aps.
 * Mod: $RCSfile: copyobject.c,v $, rel: %R%, date: $Date: 1992-02-27 13:19:03 $, SID: $Revision: 1.3 $
 * by Lars Bak.
 */

#include "beta.h"

/*
 * CopyObject:
 *  Copy an object refered by theObj from IOASpace to ToSpace.
 */

ref(Object) CopyObject( theObj)
  ref(Object) theObj;
{
  ref(Object) newObj;
  long        size;

  size = ObjectSize( theObj) * 4;
  
  /* Assume that theObj->GCAttr <= IOAMaxAge. */
  DEBUG_IOA( Claim( theObj->GCAttr<=IOAMaxAge,
		   "CopyObject: Age of object > IOAMaxAge."));

  IOAAgeTable[theObj->GCAttr-1] += size;


  DEBUG_AOA( IOAcopied += size );

  {
    register ptr(long) src;
    register ptr(long) dst;
    register ptr(long) theEnd;

    newObj     = (ref(Object)) ToSpaceTop;
    theEnd     = (ptr(long)) (((long) newObj) + size); 

    ToSpaceTop = theEnd;
#ifdef AO_Area
    if( ToSpaceTop >= ToSpacePtr ){
      fprintf(output, "#CopyObject:::::::: ToSpaceTop > ToSpacePtr\n" );
      fprintf(output, "#IOAtoAOAarea = %d longs\n",
              ((long) ToSpaceLimit - (long) ToSpacePtr)/4 );
    }
#endif
    src = (ptr(long)) theObj; dst = (ptr(long)) newObj; 

    while( dst < theEnd) *dst++ = *src++; 

  }
  /* Increase the age of the object */
  if( newObj->GCAttr < IOAMaxAge ) newObj->GCAttr++;

  /* Set one forward reference in theObj to newObj */
  theObj->GCAttr = (long) newObj;

  /* Return the new object in ToSpace */
  return newObj;
}

ref(Object) NewCopyObject( theObj, theCell)
  ref(Object)    theObj;
  handle(Object) theCell;
{
#ifdef LVR_Area
  if( isValRep( theObj) ){
    if( ((ref(ValRep)) theObj)->HighBorder > 200){
      ref(Object) newObj; extern ref(Object) CopyObjectToLVRA(); 
      if( newObj = CopyObjectToLVRA( theObj) ){
	newObj->GCAttr = (long) theCell; /* Preserve the LVRA-Cycle */
	DEBUG_LVRA( Claim( (long) ((ref(ValRep)) *theCell)->Proto == -3,
			  "NewCopyObject: theRep->Proto == -3"));
	return newObj;
      }else 
	return CopyObject( theObj);
    }
  }
#endif

#ifdef AO_Area
  if( theObj->GCAttr >= IOAtoAOAtreshold ){
    if( !isStackObject(theObj) ){
      ref(Object) newObj; extern ref(Object) CopyObjectToAOA(); 
      if( newObj = CopyObjectToAOA( theObj) ){
        /* Insert theCell in IOAtoAOAtable. */
        if( theCell ) *--ToSpacePtr = (long) theCell;
	return newObj;
      }else
	return CopyObject( theObj);
    }
  }
#endif
  return CopyObject( theObj);
}
