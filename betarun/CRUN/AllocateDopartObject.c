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
	 "ba   "CPREF"AlloDO;"
	 "clr  %o4;"
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

    Ck(origin);
    Protect(origin, theObj = cast(DopartObject) IOAalloc(DopartObjectSize(size)));
    Ck(origin);

    theObj->Proto  = DopartObjectPTValue;
    theObj->GCAttr = 1;
    theObj->Origin = origin;
    theObj->Size   = size;

#ifdef sparc
    /* hack hack. Olm wants the result in %i0 */
    __asm__ volatile("":: "r" (theObj));
    __asm__("ret;restore %0, 0, %%i0"::"r" (theObj));
#endif

    return theObj; /* Keeps gcc happy */
}
