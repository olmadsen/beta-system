/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-93 Mjolner Informatics Aps.
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

#include "beta.h"
#include "crun.h"

#ifdef sparc
/* Dont allow size to be in a GC register. Also first argument 
 * is fixed to be current object.
 */
asmlabel(AlloDO,
	 "mov  %o0,%o2;" 
	 "mov  %i0,%o0;"
	 "clr  %o1;"
	 "clr  %o3;" 
	 "clr  %o4;"           /* Everything now set up for new frame */
	 "save %sp,-64,%sp;"   /* New frame due to C call below */
	 "mov  %i0,%o0;"
	 "mov  %i2,%o2;"
	 "clr  %o1;"
	 "clr  %o3;"         
	 "call "CPREF"AlloDO;"
	 "clr  %o4;"           /* Everything now set up for C frame */
	 "ret;"
	 "restore %o0,0,%i0;"  /* Ole wants result in %i0: necessitates call above */
	 );
ref(DopartObject)
CAlloDO(ref(Object) origin, int i1, unsigned size)
#else
ref(DopartObject)
AlloDO(unsigned size)
#endif
{
    DeclReference1(struct DopartObject *, theObj);

    GCable_Entry();

    theObj = cast(DopartObject) IOAalloc(DopartObjectSize(size));

    theObj->Proto  = DopartObjectPTValue;
    theObj->GCAttr = 1;
    theObj->Origin = origin;
    theObj->Size   = size;

    return theObj;
}
