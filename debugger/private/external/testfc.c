#include <stdio.h>
#include "../../betarun/sun4s/C/valhallaFindComp.h"

void forEach (int returnAdr, int returnObj)
{
  if (returnObj) {
    DescribeObject (returnObj);
    fprintf (stderr,"\n");
  } else {
    fprintf (stderr,"<<C activation record>>\n");
  }
}

void printStackObj (struct Component *comp)
{ struct ComponentStack cs;

  /* Flush register windows to stack */
  asm("ta 3");

  StackEnd = (long *) ((struct RegWin *)FramePointer)->fp;
  
  cs.comp = comp;
  findComponentStack (&cs,-1);

  switch (cs.stacktype) {
  case CS_PROCESSORSTACK:
    fprintf (stderr, "CS_PROCESSORSTACK: firstAR = 0x%x, lastAR = 0x%x\n",
	     (int) cs.info.if_onstack.firstAR, 
	     (int) cs.info.if_onstack.lastAR);
    break;
  case CS_ACTIVECOMPONENT:
    fprintf (stderr, "CS_ACTIVECOMPONENT: firstAR = 0x%x, lastAR = 0x%x\n",
	     (int) cs.info.if_onstack.firstAR, 
	     (int) cs.info.if_onstack.lastAR);
    break;
  case CS_STACKOBJ:
    fprintf (stderr, "CS_STACKOBJ\n");
    break;
  case CS_NOSTACK:
    fprintf (stderr, "CS_NOSTACK\n");
  }

  scanComponentStack (&cs, forEach);

  fprintf (stderr,"\n");
  
}

void callback (void (*cb)())
{
  cb();
}
