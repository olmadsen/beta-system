/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"
#include "crun.h"

struct Object *GetThis(long *SP)
{ 
  /* Find current object in stack frame starting in SP-1.
   * (SP points to top of previous frame).
   * By now it is always the last reference pushed.
   */
  struct Object **FP; 
  struct Object *top; 
  struct Object *next;

  FP = (struct Object **)SP-DYNOFF;
  top  = *FP--; /* dyn */
  next = *FP--; /* 1'st ref */
  while(next){
    top=next;
    next=*FP--; /* stack grows toward low adresses */
  }
  return top;   
}

void Return() 
{
  DEBUG_CODE(NumReturn++);
  return;
}

void FailureExit()
{
  BetaError(StopCalledErr, GetThis(BetaStackTop[0]), BetaStackTop[0], 0);
}

/* RefNone always referenced by betaenv, but not called on platforms,
 * that use traps to check refnone.
 */
void RefNone()
{
  DEBUG_CODE(NumRefNone++);
  DEBUG_CODE(fprintf(output, "RefNone() called\n"));
}

void SetArgValues(long argc, char *argv[])
{
  ArgCount = argc;
  ArgVector = argv;
}

#ifdef macppc
double i2f(long n) 
{ 
  return (double)n;
}
#ifdef RTDEBUG
void printCompStack(long * SPz, long dummy, long SPsize)
{ 
#if 0
 int i;
 for (i=0; i < (SPsize / 4)+4; i++) {
    printf("StackElm: %i: &SPz[i]= 0x%x, SPz[i]=0x%x\n",
	i*4, 
	&((long *)SPz)[i],
	((long *)SPz)[i]);
 }
#endif
}
#endif /* RTDEBUG */
#endif /* macppc */

#ifndef __GNUC__
/* Only gcc is able to inline. If not inlined, the functions in
 * IOAAlloc.h are defined as normal C functions here.
 */
#include "IOAAlloc.h"
#endif

