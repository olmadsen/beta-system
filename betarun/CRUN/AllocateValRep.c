/* File: AllocateValRep.c
 * $Id: AllocateValRep.c,v 1.1 1992-06-06 03:36:33 beta Exp $
 */

#include "beta.h"
#include "crun.h"

asmlabel(AllocateValRep, "
	mov %i0, %o0
        mov %l0, %o1
	ba _CAllocateValRep
	mov %l1, %o2
");

ref(ValRep) CAllocateValRep(ref(Object) theObj,
			   unsigned offset, /* i bytes */
			   unsigned range
			   )
{
  register ref(ValRep) theRep;

  if (range < 0)
    range = 0;

  if (range > LARGE_REP_SIZE) {
    theRep = cast(ValRep) LVRAAlloc(range);
    if (theRep) {
      /* Make the LVRA-cycle: theCell -> theRep.GCAttr */
      theRep->GCAttr = (int) ((char *) theObj + offset);
      *casthandle(ValRep)((char *)theObj + offset) = theRep;
      int_clear((char*)theRep->Body, range*4);
      return theRep;
    }
  }

  theRep = cast(ValRep) IOAcalloc(range*4 + headsize(ValRep));

  theRep->Proto = cast(ProtoType) -3;
  theRep->GCAttr = 1;
  theRep->LowBorder = 1;
  theRep->HighBorder = range;

  *casthandle(ValRep)((char *)theObj + offset) = theRep;
  return theRep;
}


