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
  long *CSP = CompSP;

  DEBUG_CODE(NumExO++);

#if 0
  fprintf(output, "\nExO: jumpAdr=0x%x, exitObj=0x%x, PC=0x%x, this=0x%x\n",
	  jumpAdr,exitObj,PC,this);
  fflush(output);
#define TRACE_EXO() \
 fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__);  \
 fprintf(output, "New SP:     0x%x\n", (long)SP);           \
 fprintf(output, "New PC:     0x%x\n", (long)PC);           \
 fprintf(output, "New object: 0x%x", (long)this);           \
 if (this&&(this!=CALLBACKMARK)&&(this!=GENMARK)){          \
   fprintf(output, " (proto: 0x%x)", this->Proto);          \
   fprintf(output, " (%s)\n", ProtoTypeName(this->Proto));  \
 }                                                          \
 fflush(output)
 
#else
#define TRACE_EXO()
#endif

  while (this != exitObj) {
  
    /* Check for passing of a callback - see STACK LAYOUT in stack.c */
    if ((this == CALLBACKMARK) || (this == GENMARK)) {
      DEBUG_CODE(fprintf(output, 
			 "ExO: passing %s\n", 
			 (this==GENMARK)?"allocation/main":"callback"); 
		 fflush(output));
      SP = (long*)GetSPbeta(SP);
      /* No need to check for SP=0 (can happen from main), 
       * since leaving of basic component is detected otherwise.
       */

      /* Check top frame */
      this = GetThis(SP);
      if (this==exitObj){
	/* ExO to frame just before callback */
	fprintf(output, "Fatal error: cannot determine SP in ExO\n");
	/* FIXME: We have a pointer to the BOTTOM of the frame, 
	 * and no PC for the frame to determine the SPoff with.
	 */
	return 0;
      }
      /* Continue down the stack */
      PC = (long*)GetPC(SP);
      this = *((struct Object **)SP-DYNOFF);       
      TRACE_EXO();
      continue;
    }
    
    /* Check for passing of a DoPart object */
    if ((long)this->Proto == (long)DopartObjectPTValue) {
      this = ((struct DopartObject *)this)->Origin;
      TRACE_EXO();
      continue;
    }
    
    /* Check for passing of a component */
    if ((long)this->Proto == (long)ComponentPTValue) {
      struct Component *comp = (struct Component *)this;
      struct Component *callerComp = comp->CallerComp;
      DEBUG_CODE(fprintf(output, "ExO: passing comp 0x%x\n", (int)comp); fflush(output));
      SP     = (long*) *--CSP; CSP--; /* count down one before reading and one after */
#ifdef ppcmac
      PC = (long*)-1; /* Check everywhere */
#else
      PC     = (long*)callerComp->CallerLSC;
#endif

      /* TerminateComponent: (see Attach.c) */
      DEBUG_CODE(NumTermComp++);
      ActiveComponent  = comp->CallerComp;
      this             = comp->CallerObj;
      comp->CallerLSC  = -2; /* indicate that comp is terminated */
      comp->StackObj   = 0;
      comp->CallerComp = 0;
      comp->CallerObj  = 0;
      CompSP -= 2;
      TRACE_EXO();
      continue;
    }
    
    /* Normal case: find stack frame size and continue */
    {  
    
#ifdef ppcmac
      SP = *(long**)SP; /* Use FramePointer */
#else
      {
        long SPoff;
        /* size allocated on stack when this became active */
        GetSPoff(SPoff, CodeEntry(this->Proto, (long)PC)); 
        SP = (long *)((long)SP+SPoff);    
      }
#endif
      /* SP now points to end of previous frame, i.e. bottom of top frame */
      /* normal dyn from the start of this frame gives current object */
      this = *((struct Object **)SP-DYNOFF); 
      /* RTS from the start of this frame gives PC */
      PC = (long*)GetPC(SP);
      TRACE_EXO();
    }
  }
  return SP;
}
