/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

struct DopartObject *AlloDO(unsigned size, struct Object *this, long *SP)
{
    struct DopartObject *theObj;

    DEBUG_CODE(NumAlloDO++);
    
    Ck(this);

    DEBUG_CODE( Claim(size > 0, "AlloDO: size > 0") );

    Protect(this, 
	    theObj = (struct DopartObject *)IOAalloc(DopartObjectSize(size), SP));
    Ck(this);

    theObj->Proto  = DopartObjectPTValue;
    theObj->GCAttr = 1;
    theObj->Origin = this;
    theObj->Size   = size;

    return theObj;
}
