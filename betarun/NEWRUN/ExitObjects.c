/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"
  
/* ExO:
 * arguments jumpAdr=a0, exitObj=a1, SP-offset=dataRegA  
 * mch.saveSp MUST be  saved: see MC68machine.bet;
 * We dont use jumpAdr here;
 * and is SP-offset really needed? We compute it using dyn?
 * NOT in official betarun.h
*/

long *ExO(long *jumpAdr, struct Object *exitObj, long *PC, struct Object* this, long *SP) 
{
  DEBUG_CODE(NumExO++);

  /* printf("\nExO: jumpAdr=0x%x, exitObj=0x%x, PC=0x%x, this=0x%x\n",
   * jumpAdr,exitObj,PC,this);
   */

  while (this != exitObj) {
    /* Check for passing of a callback */
    if ((long) this == CALLBACKMARK ) {
      printf("ExO: passing cb\n");
      this = *((struct Object **)SP+1);
      SP = *((long **)SP);
      continue;
    }
    /* Check for passing of a component */
    if ((long)this->Proto == (long)ComponentPTValue) {
      struct Component *comp = (struct Component *)this;
      struct Component *callerComp = comp->CallerComp;
      printf("ExO: passing comp\n");
      SP = (long *)callerComp->CallerComp->SPx;
      this = comp->CallerObj;
      /* TerminateComponent: (see Attach.c) */
      comp->CallerLSC = -1;
      continue;
    }
    /* Normal case: find stack frame size and continue */
    {  
      long SPoff;
      /* size allocated on stack when this became active */
      GetSPoff(SPoff, CodeEntry(this->Proto, PC)); 
      SP = (long)SP+SPoff;      
      /* SP now points to end of previous frame, i.e. bottom of top frame */
      /* normal dyn from the start of this frame gives current object */
      this = *((struct Object **)SP-2); 
      /* RTS from the start of this frame gives PC */
      PC = *((long*)SP-1);
    }
  }
  return SP;
}
