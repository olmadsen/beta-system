/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"
  
long *ExO(long *jumpAdr, 
	  struct Object *exitObj, 
	  long *PC, 
	  struct Object* this, 
	  long *SP) 
{
  DEBUG_CODE(NumExO++);

#if 0
  printf("\nExO: jumpAdr=0x%x, exitObj=0x%x, PC=0x%x, this=0x%x\n",
	 jumpAdr,exitObj,PC,this);
#endif

  while (this != exitObj) {
    /* Check for passing of a callback - see STACK LAYOUT in stack.c */
    if ((long) this == CALLBACKMARK ) {
      printf("ExO: passing cb\n");
      SP =  *((long **)SP); /* SP-beta */
      /* Check top frame */
      this = GetThis(SP);
      if (this==exitObj){
	/* ExO to frame just before callback */
	fprintf(output, "Error: cannot determine SP in ExO\n");
	/* Problem: We have a pointer to the BOTTOM of the frame, 
	 * and no PC for the frame to determine the SPoff with.
	 */
	return 0;
      }
      /* Continue down the stack */
      PC = *((long**)SP-1);
      this = *((struct Object **)SP-2);       
      continue;
    }
    /* Check for passing of a component */
    if ((long)this->Proto == (long)ComponentPTValue) {
      struct Component *comp = (struct Component *)this;
      struct Component *callerComp = comp->CallerComp;
      printf("ExO: passing comp 0x%x\n", (int)comp);
      SP   = (long *)callerComp->SPx;
      PC   = (long *)callerComp->CallerLSC;
      /* TerminateComponent: (see Attach.c) */
      ActiveComponent  = comp->CallerComp;
      this             = comp->CallerObj;
      comp->CallerLSC  = -2; /* indicate that comp is terminated */
      comp->StackObj   = 0;
      comp->CallerComp = 0;
      comp->CallerObj  = 0;
      continue;
    }
    /* Normal case: find stack frame size and continue */
    {  
      long SPoff;
      /* size allocated on stack when this became active */
      GetSPoff(SPoff, CodeEntry(this->Proto, (long)PC)); 
      SP = (long *)((long)SP+SPoff);      
      /* SP now points to end of previous frame, i.e. bottom of top frame */
      /* normal dyn from the start of this frame gives current object */
      this = *((struct Object **)SP-2); 
      /* RTS from the start of this frame gives PC */
      PC = *((long**)SP-1);
    }
  }
  return SP;
}
