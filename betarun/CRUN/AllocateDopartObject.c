/*
 * BETA C RUNTIME SYSTEM, Copyright (C) Aarhus University
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"


ParamOriginSize(DopartObject *, AlloDO)
{
    DeclReference1(DopartObject *, theObj);
    FetchOriginSize();

    DEBUG_CODE(NumAlloDO++);

    Ck(origin);

    Claim((long)size>0, "size>0");

    Protect(origin, 
	    theObj = (DopartObject *) IOAalloc(DopartObjectSize(size)));

    SETPROTO(theObj,DopartObjectPTValue);
    if (IOAMinAge!=0) theObj->GCAttr = IOAMinAge;
    theObj->Origin = origin;
    theObj->Size   = size;

    Ck(origin); Ck(theObj);

    SPARC_CODE(return_in_i0(theObj));
    HPPA_CODE(setThisReg(theObj));

    return theObj /* keep gcc happy */; 
}
