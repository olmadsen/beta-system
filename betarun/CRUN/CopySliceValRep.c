/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopySliceValRep.c,v $, rel: %R%, date: $Date: 1992-07-21 17:17:04 $, SID: $Revision: 1.7 $
 * by Peter Andersen and Tommy Thorn.
 */

#include "beta.h"
#include "crun.h"

asmlabel(CopySVR, "
	mov	%l7, %o3
	ba	_CCopySVR
	mov	%l6, %o4
");

void CCopySVR(ref(ValRep) theRep,
	      ref(Item) theItem,
	      unsigned offset, /* i ints */
	      unsigned low,
	      unsigned high
	      )
{
  register long i;
  register ref(ValRep) newRep;
  
  /* Copy a slice of a Value Repetition. */
  
  /* stack[12] -> theRep; */
  /* Check that low and high usable. */
  if (low  < theRep->LowBorder)
    BetaError(-6, theItem);
  if (high > theRep->HighBorder)
    BetaError(-7, theItem);
  
  /* Calculate the range of the new repetition. */
  high =  high - low + 1;
  if (high < 0) high = 0;
  
  newRep = cast(ValRep) IOAalloc(DispatchValRepSize(theRep, high));
  
  /* The new Object is now allocated, but not assigned yet! */
  
  /* Initialize the structual part of the repetition. */
  newRep->Proto = theRep->Proto;
  newRep->GCAttr = 1;
  newRep->LowBorder = 1;
  newRep->HighBorder = high;
  
  /* Copy the body part of the repetition. */
  switch ( (int) theRep->Proto){
  case (int) ByteRepPTValue:
    /* Since the slice may start on any byte we copy it byte by byte */
    for (i = 0;  i < high; ++(char *)i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    break;
  case (int) WordRepPTValue:
    /* Since the slice may start on any word we copy it word by word */
    for (i = 0; i < high; ++(short *)i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    break;
  case (int) ValRepPTValue:
    for (i = 0; i < high; ++(long *)i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    break;
  case (int) DoubleRepPTValue:
    for (i = 0; i < high; ++(long *)i)
      newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
    newRep->Body[2*i] = theRep->Body[2*i+low-theRep->LowBorder];
    break;
  default:
    printf(output, "CopySliceValRep: wrong prototype\n");
    exit(1);
  }
  
  /* stack[8] -> theItem;
   * stack[4] -> offset
   */

  AssignReference((long *)theItem + offset, cast(Item) newRep);
}


