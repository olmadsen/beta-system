#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#include "valhallaFindComp.h"

#ifdef hpux
void findComponentStack (struct ComponentStack* compStack, int PC)
{
}

void scanComponentStack (struct ComponentStack* compStack,
			 forEachCallType forEach)
{
}
#endif /* hpux */

#ifdef sparc

# define objIsValRep(theObj) inLVRA(theObj)

void handleStackPart (struct RegWin *theAR, int lastReturnAdr, forEachCallType forEach)
{ long* this, *end;
  struct Object *lastObj, *theObj;
  
  lastObj= (struct Object *) theAR->i0;
  forEach ((int) lastReturnAdr,(int) lastObj);
  
  this = (long *) (((long) theAR)+16*4);
  end = (long *) (((long) theAR->fp)-4);
  
  while (this<=end) {
    if (isCode(this[0])) {
      theObj = (struct Object *) this[2];
      if (inBetaHeap(theObj) 
	  && isObject(theObj) 
	  && !objIsValRep(theObj)) {
	/* Add 8 to get the real SPARC return address. */
	forEach (this[0]+8,(int) theObj);
	lastObj= theObj;
	this+=2;
      } else {
	forEach (this[0]+8,(int) lastObj);
      }
    }
    this+=2;
  }
}


/* findComponentStack (SPARC)
 * ========================== */

void findComponentStack (struct ComponentStack* compStack, int PC)
{ 
  struct RegWin *thisCompBlock = (struct RegWin *) lastCompBlock;
  struct RegWin *prevCompBlock = 0;
  struct Component *thisComponent = ActiveComponent;

  DEBUG_VALHALLA(fprintf (output,"Entering findComponentStack\n"));

  while (thisCompBlock) {
    if (compStack->comp == thisComponent){
      /* comp found on processor stack. */
      
      compStack->info.if_onstack.firstAR 
	= (struct RegWin *) thisCompBlock->fp;
      
      if (prevCompBlock) { 
	
	compStack->stacktype = CS_PROCESSORSTACK; 
	compStack->info.if_onstack.lastAR
	  = (struct RegWin *) prevCompBlock->fp;
	compStack->returnAdr = thisComponent->CallerLSC;
	compStack->info.if_onstack.activeCBF 
	  = (struct RegWin *) prevCompBlock->l5;

      } else {
	/* comp is the active component. */

	compStack->stacktype = CS_ACTIVECOMPONENT;
	compStack->info.if_onstack.lastAR = (struct RegWin *) StackEnd;

	compStack->info.if_onstack.activeCBF 
	  = (struct RegWin *) ActiveCallBackFrame;
	compStack->returnAdr = PC;
	
      }
      DEBUG_VALHALLA(fprintf (output,"Leaving findComponentStack. Stacktype = %d\n",compStack->stacktype));
      return;
    } else {
      prevCompBlock = thisCompBlock;
      thisCompBlock = (struct RegWin *) thisCompBlock->l6; /* See SparcDoc.c */
      thisComponent = thisComponent->CallerComp;
    }
  }

  /* Component not found on the processor stack.
   * If the component has ever been attached and suspended, it should have
   * been assigned a stack object.
   * Otherwise it has no stack at all. */

  switch ((int) compStack->info.stackObj = compStack->comp->StackObj) {
  case 0:
  case -1:
    compStack->stacktype = CS_NOSTACK;
    compStack->returnAdr = 0;
    break;
  default:
    compStack->stacktype = CS_STACKOBJ;
    compStack->returnAdr = compStack->comp->CallerLSC;
    break;
  }
  DEBUG_VALHALLA(fprintf (output,"Leaving findComponentStack. Stacktype = %d\n",compStack->stacktype));
}


void scanComponentStack (struct ComponentStack* compStack,
			 forEachCallType forEach)
{
  DEBUG_VALHALLA(fprintf (output,"Entering scanComponentStack. Stacktype = %d\n",compStack->stacktype))
  switch (compStack->stacktype) {
  case CS_NOSTACK: 
    break;
  case CS_STACKOBJ:
    { struct StackObject *theStack = compStack->info.stackObj;
      struct RegWin *theAR;
      int lastReturnAdr = compStack->returnAdr; 
      
      /* ASSUMES THAT THERE ARE NO CALLBACK FRAMES IN A COMPONENT OBJECT.
       * IF THIS CHANGES, SO SHOULD THE CODE BELOW. */
      
      /* Start at theStack->Body[1], since theStack->Body[0] 
       * is saved FramePointer */
      long delta = (char *) &theStack->Body[1] - (char *) theStack->Body[0];
      
      for (theAR =  (struct RegWin *) &theStack->Body[1];
	   theAR != (struct RegWin *) &theStack->Body[theStack->StackSize];
	   theAR =  (struct RegWin *) (theAR->fp + delta))
	{
	  handleStackPart (theAR,lastReturnAdr,forEach);
	  lastReturnAdr = theAR->i7+8;
	}
    };
    break;
  case CS_PROCESSORSTACK:
  case CS_ACTIVECOMPONENT:
    { struct RegWin *theAR = compStack->info.if_onstack.lastAR;
      struct RegWin *nextCBF = compStack->info.if_onstack.activeCBF;
      int lastReturnAdr = compStack->returnAdr;

      /* Skip external code on top of stack: */
      while ((int) theAR < (int) BetaStackTop) {
	forEach (lastReturnAdr,0);
	lastReturnAdr = theAR->i7+8;
	theAR = (struct RegWin *) theAR->fp;
      }	
      
      for (;theAR != compStack->info.if_onstack.firstAR;
	   theAR = (struct RegWin *) theAR->fp)
	{
	  if (theAR == nextCBF) {
	    /* This is AR of HandleCB. Skip this and
	     * skip to betaTop and update nextCBF
	     */
	    nextCBF = (struct RegWin *) theAR->l5;
	    { /* Wind down the stack until betaTop is reached. Needed in 
	       * order to update lastReturnAdr. */
	      struct RegWin *cAR;
	      forEach (lastReturnAdr,0);
	      lastReturnAdr = theAR->i7+8;
	      for (cAR = theAR;
		   cAR != (struct RegWin *) theAR->l6;
		   cAR = (struct RegWin *) cAR->fp) {
		forEach (lastReturnAdr,0);
		lastReturnAdr = cAR->i7+8;
	      }
	    }
	    theAR = (struct RegWin *) theAR->l6; /* Skip to betaTop */
	  }
	  handleStackPart (theAR,lastReturnAdr,forEach);
	  lastReturnAdr = theAR->i7+8; /* First return address used is actually PC of the process. 
					* For other return addresses, add 8. */
	};
      break;
    }
  }
}

#endif sparc
#endif RTVALHALLA
