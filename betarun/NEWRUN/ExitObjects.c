/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

#ifdef ppcmac
#define WIND_BACK_SP                                          \
      SP = *(long**)SP /* Use FramePointer */
#else
#define WIND_BACK_SP                                          \
      {                                                       \
        long SPoff;                                           \
        /* size allocated on stack when this became active */ \
        GetSPoff(SPoff, CodeEntry(GETPROTO(this), (long)PC)); \
        SP = (long *)((long)SP+SPoff);                        \
      }
#endif

  
long *ExO(long *jumpAdr, 
	  Object *exitObj, 
	  long *PC, 
	  Object* this, 
	  long *SP) 
{
  long *CSP = CompSP;
  long *OrigSP = SP;
  long *OrigPC = PC;
  Object *theObj = this;
  Component *OrigActiveComponent = ActiveComponent;
  /* ActiveCallBackFrame and lastCompBlock not used on NEWRUN */

  DEBUG_CODE(NumExO++);

#if 0
  fprintf(output, "\nExO: ");
  fprintf(output, "\n  jumpAdr:"); PrintCodeAddress((long)jumpAdr);
  fprintf(output, "\n  exitObj:"); PrintObject(exitObj);
  fprintf(output, "\n  PC:     "); PrintCodeAddress((long)PC);
  fprintf(output, "\n  this:   "); PrintObject(this);
  fprintf(output, "\n");
  fflush(output);
#define TRACE_EXO() \
 fprintf(output, "File %s; Line %d", __FILE__, __LINE__);      \
 fprintf(output, "\nNew SP:     0x%08x", (long)SP);            \
 fprintf(output, "\nNew PC:    "); PrintCodeAddress((long)PC); \
 fprintf(output, "\nNew object:"); PrintObject(this);          \
 fprintf(output, "\n");                                        \
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
      /* Check for SP=0 (can happen from main) */
      if (SP==0){
	/* Attempt to leave basic component! */
	/* Restore global variables to ensure correct dump.
	 * FramePointer and StackPointer are still unchanged 
	 * at this point.
	 */
	DEBUG_CODE({
	  fprintf(output, "Leaving basic component - calling BetaError\n");
	});
	SP = OrigSP;
	PC = OrigPC;
	this = theObj;
	/*WIND_BACK_SP; (done in BetaError) */
	ActiveComponent = OrigActiveComponent;
	BetaError(LeaveBasicCompErr,theObj,SP,PC);
      }	

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
      this = *((Object **)SP-DYN_OFF);       
      TRACE_EXO();
      continue;
    }
    
    /* Check for passing of a DoPart object */
    if ((long)GETPROTO(this) == (long)DopartObjectPTValue) {
      this = ((DopartObject *)this)->Origin;
      TRACE_EXO();
      continue;
    }
    
    /* Check for passing of a component */
    if ((long)GETPROTO(this) == (long)ComponentPTValue) {
      Component *comp = (Component *)this;
      Component *callerComp = comp->CallerComp;
      DEBUG_CODE(fprintf(output, "ExO: passing comp 0x%x\n", (int)comp); fflush(output));
      SP     = (long*) *--CSP; CSP--; /* count down one before reading and one after */
#ifdef ppcmac
      PC = (long*)-1; /* Check everywhere */
#else
      PC     = (long*)callerComp->CallerLSC;
#endif

      /* TerminateComponent: (see Attach.c) */
      DEBUG_CODE(NumTermComp++);
      /* No need to check for comp->CallerComp == 0 since illegal
       * leave is detected above.
       */
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
    
      WIND_BACK_SP;

      /* SP now points to end of previous frame, i.e. bottom of top frame */
      /* normal dyn from the start of this frame gives current object */
      this = *((Object **)SP-DYN_OFF); 
      /* RTS from the start of this frame gives PC */
      PC = (long*)GetPC(SP);
      TRACE_EXO();
    }
  }
  return SP;
}

/****************************** New version *******************************/


long *ExOx(long *jumpAdr, 
	   Object *exitObj, 
	   long *PC, 
	   Object* this, 
	   long *SP) 
{
  long *CSP = CompSP;
  long *OrigSP = SP;
  long *OrigPC = PC;
  Object *theObj = this;
  int one_more_done = 0;
  Component *OrigActiveComponent = ActiveComponent;
  /* ActiveCallBackFrame and lastCompBlock not used on NEWRUN */

  DEBUG_CODE(NumExO++);

#if 1
  fprintf(output, "\nExOx: ");
  fprintf(output, "\n  jumpAdr:"); PrintCodeAddress((long)jumpAdr);
  fprintf(output, "\n  exitObj:"); PrintObject(exitObj);
  fprintf(output, "\n  PC:     0x%08x", (int)PC); PrintCodeAddress((long)PC);
  fprintf(output, "\n  this:   "); PrintObject(this);
  fprintf(output, "\n");
  fflush(output);
#define TRACE_EXOX() \
 fprintf(output, "File %s; Line %d", __FILE__, __LINE__);      \
 fprintf(output, "\nNew SP:     0x%08x", (long)SP);            \
 fprintf(output, "\nNew PC:     0x%08x", (int)PC); PrintCodeAddress((long)PC); \
 fprintf(output, "\nNew object:"); PrintObject(this);          \
 fprintf(output, "\n");                                        \
 fflush(output)
 
#else
#define TRACE_EXOX()
#endif

  while (1) {
    if ((this == exitObj) || one_more_done){
      if (!one_more_done){
	DEBUG_CODE(fprintf(output, "ExOx: One more\n"));
	one_more_done = 1;
      } else {
	DEBUG_CODE(fprintf(output, "ExOx: done\n"));
	break;
      }
    }
    /* Check for passing of a callback - see STACK LAYOUT in stack.c */
    if ((this == CALLBACKMARK) || (this == GENMARK)) {
      DEBUG_CODE(fprintf(output, 
			 "ExO: passing %s\n", 
			 (this==GENMARK)?"allocation/main":"callback"); 
		 fflush(output));
      SP = (long*)GetSPbeta(SP);
      /* Check for SP=0 (can happen from main) */
      if (SP==0){
	/* Attempt to leave basic component! */
	/* Restore global variables to ensure correct dump.
	 * FramePointer and StackPointer are still unchanged 
	 * at this point.
	 */
	DEBUG_CODE({
	  fprintf(output, "Leaving basic component - calling BetaError\n");
	});
	SP = OrigSP;
	PC = OrigPC;
	this = theObj;
	/*WIND_BACK_SP; (done in BetaError) */
	ActiveComponent = OrigActiveComponent;
	BetaError(LeaveBasicCompErr,theObj,SP,PC);
      }	

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
      this = *((Object **)SP-DYN_OFF);       
      TRACE_EXOX();
      continue;
    }
    
    /* Check for passing of a DoPart object */
    if ((long)GETPROTO(this) == (long)DopartObjectPTValue) {
      DEBUG_CODE(fprintf(output, "ExO: passing DopartObject\n"); fflush(output));
      this = ((DopartObject *)this)->Origin;
      TRACE_EXOX();
      continue;
    }
    
    /* Check for passing of a component */
    if ((long)GETPROTO(this) == (long)ComponentPTValue) {
      Component *comp = (Component *)this;
      Component *callerComp = comp->CallerComp;
      DEBUG_CODE(fprintf(output, "ExO: passing comp 0x%x\n", (int)comp); fflush(output));
      SP     = (long*) *--CSP; CSP--; /* count down one before reading and one after */
#ifdef ppcmac
      PC = (long*)-1; /* Check everywhere */
#else
      PC     = (long*)callerComp->CallerLSC;
#endif

      /* TerminateComponent: (see Attach.c) */
      DEBUG_CODE(NumTermComp++);
      /* No need to check for comp->CallerComp == 0 since illegal
       * leave is detected above.
       */
      ActiveComponent  = comp->CallerComp;
      this             = comp->CallerObj;
      comp->CallerLSC  = -2; /* indicate that comp is terminated */
      comp->StackObj   = 0;
      comp->CallerComp = 0;
      comp->CallerObj  = 0;
      CompSP -= 2;
      TRACE_EXOX();
      continue;
    }
    
    /* Normal case: find stack frame size and continue */
    {  
    
      DEBUG_CODE(fprintf(output, "ExO: normal case\n"); fflush(output));

      WIND_BACK_SP;

      /* SP now points to end of previous frame, i.e. bottom of top frame */
      /* normal dyn from the start of this frame gives current object */
      this = *((Object **)SP-DYN_OFF); 
      /* RTS from the start of this frame gives PC */
      PC = (long*)GetPC(SP);
      TRACE_EXOX();
    }
  }

  return SP;
}
