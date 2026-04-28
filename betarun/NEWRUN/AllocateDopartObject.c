/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

DopartObject *AlloDO(unsigned size, Object *this, long *SP)
{
    DopartObject *theObj;

    DEBUG_CODE(NumAlloDO++);
    
    Ck(this);

    DEBUG_CODE( Claim(size > 0, "AlloDO: size > 0") );

    /* No need to check for IOAMAXSIZE */
    Protect(this, 
	    theObj = (DopartObject *)IOAalloc(DopartObjectSize(size), SP));

    SETPROTO(theObj, DopartObjectPTValue);
    if (IOAMinAge!=0) theObj->GCAttr = IOAMinAge;
    theObj->Origin = this;
    theObj->Size   = size;

    Ck(this);

#if 0
    { int i;
      fprintf(output, "AlloDO#%d: returns 0x%x\n", NumAlloDO, theObj);
      for (i=0; i<size/4; i++){
	fprintf(output, "  0x%x: 0x%x\n", (long *)theObj+i, *((long *)theObj+i));
      }
      fflush(output);
    }
#endif

    return theObj;
}
