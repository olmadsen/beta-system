/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1990,91,92 Mjolner Informatics Aps.
 * Mod: $RCSfile: CopySliceValRep.c,v $, rel: %R%, date: $Date: 1992-08-27 15:46:48 $, SID: $Revision: 1.11 $
 * by Peter Andersen and Tommy Thorn.
 */

#define GCable_Module

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
    DeclReference1(struct ValRep *newRep);
    register long i;
    
    GCable_Entry();
    
    Ck(theItem); Ck(theRep);
    /* Copy a slice of a Value Repetition. */
    
    /* Check that low and high are usable. */
    if (low<theRep->LowBorder) BetaError(-6, theItem);
    if (high<theRep->LowBorder) BetaError(-7, theItem);
    if (low>theRep->HighBorder) BetaError(-6, theItem);
    if (high>theRep->HighBorder) BetaError(-7, theItem);
    
    /* Calculate the range of the new repetition. */
    high =  high - low + 1;
    if (high < 0) high = 0;
    
    newRep = cast(ValRep) IOAalloc(DispatchValRepSize(theRep, high));
    
    ForceVolatileRef(theRep);
    ForceVolatileRef(theItem);
    Ck(theRep); Ck(theItem);

    /* The new Object is now allocated, but not assigned yet! */
    
    /* Initialize the structual part of the repetition. */
    newRep->Proto = theRep->Proto;
    newRep->GCAttr = 1;
    newRep->LowBorder = 1;
    newRep->HighBorder = high;
    
    /* Copy the body part of the repetition. */
    switch ( (int) theRep->Proto){
      case (int) ByteRepPTValue:
	{ /* Since the slice may start on any byte we copy it byte by byte */
	    unsigned char *newBody= (unsigned char *)newRep->Body;
	    unsigned char *oldBody= (unsigned char *)((unsigned)theRep->Body+(low-theRep->LowBorder));
	    for (i = 0;  i < high; i+=1)
	      *(unsigned char *)((unsigned)newBody+i) = *(unsigned char *)((unsigned)oldBody+i);
	    break;
	}
      case (int) WordRepPTValue:
	{ /* Since the slice may start on any word we copy it word by word */
	    short *newBody= (short *)newRep->Body;
	    short *oldBody= (short *)((unsigned)theRep->Body+(low-theRep->LowBorder));
	    for (i = 0;  i < high; i+=1)
	      *(short *)((unsigned)newBody+i) = *(short *)((unsigned)oldBody+i);
	    break;
	}
      case (int) ValRepPTValue:
	for (i = 0; i < high; i++)
	  newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
	break;
      case (int) DoubleRepPTValue:
	for (i = 0; i < high; ++(long *)i){
	    newRep->Body[i] = theRep->Body[i+low-theRep->LowBorder];
	    newRep->Body[2*i] = theRep->Body[2*i+low-theRep->LowBorder];
	}
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


