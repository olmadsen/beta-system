/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"


ParamOriginSize(struct DopartObject *, AlloDO)
{
    DeclReference1(struct DopartObject *, theObj);
    GCable_Entry();

    FetchOriginSize();

    DEBUG_CODE(NumAlloDO++);

    Ck(origin);

    DEBUG_CODE( Claim(size > 0, "AlloDO: size > 0") );

    Protect(origin, 
	    theObj = cast(DopartObject) IOAalloc(DopartObjectSize(size)));

    theObj->Proto  = DopartObjectPTValue;
    if (IOAMinAge!=0) theObj->GCAttr = IOAMinAge;
    theObj->Origin = origin;
    theObj->Size   = size;

    Ck(origin); Ck(theObj);

#ifdef sparc
    return_in_i0(theObj);
#endif

#ifdef hppa
    setThisReg(theObj);
    return theObj;
#endif

}
