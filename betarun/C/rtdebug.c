/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * rtdebug.c
 *   Various RTDEBUG stuff not directly related to GC.
 * 
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#ifdef PERSIST
#include "referenceTable.h"
#endif /* PERSIST */

#include "trie.h"

#ifdef UNIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#endif /* UNIX */

#if defined(MAC)
#include <MachineExceptions.h>
#endif

#ifdef RUN
/* The following variables are only used in debug version, 
 * but declared unconditionally in Declaration.run.
 * Thus declared unconditionally here.
 */
GLOBAL(pc_t CkPC1);
GLOBAL(pc_t CkPC2);
GLOBAL(Object * CkP1);
GLOBAL(Object * CkP2);
GLOBAL(Object * CkP3);
GLOBAL(Object * CkP4);
GLOBAL(Object * CkP5);
#endif


#ifndef RTDEBUG
#ifdef RUN
/* The following functions are only used in debug version, 
 * but declared unconditionally in Declaration.run.
 * Here we supply empty implementations to allow linking.
 */
void NotifyRTDebug() 
{}
void CheckRegisters(void)
{}
#endif /* RUN */

#else /* RTDEBUG defined */

/********* Rest of file is only compiled if RTDEBUG defined ***********/

void NotifyRTDebug() 
{
  Notify("RTS: Runtime routines perform consistency checks on registers.");
}

#ifdef NEWRUN
static void EmptyCellProcessFunc(Object **theCell,Object *theObj)
{
}
#endif /* NEWRUN */

void CClaim(long expr, char *description, char *fname, int lineno)
{
  if (expr)
    return;
  
  fprintf(output, "\n%s:%d:\nAssumption failed: %s\n\n", 
	  fname, lineno, description);

#ifdef intel
  if (CkPC1 && CkPC2){
    char *lab;
    fprintf(output, "Caused by Ck called from PC=0x%x (called from 0x%x)\n\n",
	    (int)CkPC1, (int)CkPC2); 
    lab = getLabel(CkPC1);
    fprintf(output, "I.e., Ck called from <%s+0x%x> ", lab, (int)labelOffset);
    lab = getLabel(CkPC2);
    fprintf(output, ", called from <%s+0x%x>\n", lab, (int)labelOffset);
  }
#endif
  
  fprintf(output,
	  "IOA:     0x%x, IOATop:     0x%x, IOALimit:     0x%x\n",
	  (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit);
  fprintf(output,
	  "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	  (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
  ILLEGAL; /* Usefull to break in */
}

void CCk(void *r, char *fname, int lineno, char *ref)
{
  register Object* rr = (Object *)r; 

  CHECK_HEAP(IOACheck(); AOACheck());

#if 0
  fprintf(output, "Ck: IOATop is 0x%x\n", (int)IOATop); fflush(output);
#endif
 
  if(r) 
    {
#ifdef NEWRUN
      if (r==CALLBACKMARK){
	DEBUG_STACK(fprintf(output, 
			    " [Ck: ignoring CALLBACKMARK at %s:%d]", 
			    fname, 
			    lineno));
	return;
      }
      if (r==GENMARK){
	DEBUG_STACK(fprintf(output, 
			    " [Ck: ignoring GENMARK at %s:%d]", 
			    fname, 
			    lineno));
	return;
      }
#endif /* NEWRUN */
#ifdef MT
      if (r==(void*)16){
	DEBUG_MT(fprintf(output, 
			 " [Ck: ignoring 0x10 (origin?) at %s:%d]", 
			 fname, 
			 lineno));
	return;
      }
      if (r==(void*)-1){
	DEBUG_MT(fprintf(output, 
			 " [Ck: ignoring -1 (origin?) at %s:%d]", 
			 fname, 
			 lineno));
	return;
      }
#endif /* MT */

#ifdef PERSIST
      /* Check not in PIT */
      if (inPIT(r)) {
	fprintf(output, "CCk:%s:%d: Ck(%s): inPIT: (%s=0x%x)\n",
		fname, lineno, ref, ref, (int)(r));
	fflush(output);
	ILLEGAL;
      }
#endif /* PERSIST */

      if (!inBetaHeap(rr)){
	fprintf(output, "Warning: CCk:%s:%d: Ck(%s): not in Heap: (%s=0x%x). COM?\n",
		fname, lineno, ref, ref, (int)(r));
	fflush(output);
      } else {
	/* Check alignment */
	if (ObjectAlign((unsigned)r)!=(unsigned)r) {
	  fprintf(output, "CCk:%s:%d: Ck(%s): bad aligment: (%s=0x%x)\n",
		  fname, lineno, ref, ref, (int)(r));
	  fflush(output);
	  ILLEGAL;
	}
	
	/* Check it's not in ToSpace */
	if (inToSpace(rr)) {
	  fprintf(output, "CCk:%s:%d: Ck(%s): is in ToSpace: (%s=0x%x)\n",
		  fname, lineno, ref, ref, (int)(r));
	  fflush(output);
	  ILLEGAL;
	}

	/* Check it's in a heap */
	if (!(inIOA(rr) || inAOA(rr)
#ifdef PERSIST
	      || inPIT(rr)
#endif /* PERSIST */
	      )) {
	  fprintf(output, "CCk:%s:%d: Ck(%s): not in Heap: (%s=0x%x)\n",
		  fname, lineno, ref, ref, (int)(r));
	  fflush(output);
	  ILLEGAL;
	}
      }
    }
}

void PrintHeap(long * startaddr, long numlongs)
{ 
  int i;
  Object *ref;

  ref=(Object *)startaddr;
  fprintf(output, "\n\nPrintHeap:\n");
  fprintf(output,
	  "IOA:     0x%x, IOATop:     0x%x, IOALimit:     0x%x\n",
	  (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit);
  fprintf(output,
	  "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	  (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
  fprintf(output, "\nDisplaying %d longs starting from address 0x%x",
	  (int)numlongs, (int)startaddr);
  PrintWhichHeap(ref);
  fprintf(output, ":\n");

  for (i=0; i<numlongs; i++){
    fprintf(output, 
	    " [%d] 0x%08x: 0x%08x", 
	    i, 
	    (int)(startaddr+i), 
	    (int)(*(startaddr+i)));
    ref=(Object *)(*(startaddr+i));
    PrintWhichHeap(ref);
    fprintf(output, "\n");
  }
  fprintf(output, "\n");

  PrintHeapUsage("");
    
  fflush(output);
  return;
}


#ifdef intel
static void RegError(pc_t pc1, pc_t pc2, char *reg, Object * value)
{ 
  char *lab;
  fprintf(output, 
	  "\nIllegal value for GC register %s=0x%x at PC=0x%x (called by 0x%x)\n", 
	  reg, 
	  (int)value,
	  (int)pc1, 
	  (int)pc2);
  if (inBetaHeap(value)){
    if (inIOA(value)){
      fprintf(output, "%s points into IOA, but not to a legal object.\n", reg);
    }
    if (inAOA(value)){
      fprintf(output, "%s points into AOA, but not to a legal object.\n", reg);
    }
    if (inToSpaceArea(value)){
      fprintf(output, "%s points into ToSpace!\n", reg);
    }
  } else {
    fprintf(output, "%s points out of BETA heaps!\n", reg);
  }
  fprintf(output, "\t%s:\t0x%08x\n", reg, (int)value);
  lab = getLabel(pc1);
  fprintf(output, "\tPC:\t0x%08x <%s+0x%x>\n", (int)pc1, lab, (int)labelOffset);
  lab = getLabel(pc2);
  fprintf(output, "\tCaller:\t0x%08x <%s+0x%x>\n", (int)pc2, lab, (int)labelOffset);
  
  fprintf(output, "\n");
  fflush(output);
  ILLEGAL;
  return;
}

static long CheckCell(Object *theCell)
{
  if (theCell && inBetaHeap(theCell) && !isObject(theCell)) {
    return 0;
  }
  return 1;
}

void CheckRegisters(void)
{
  extern Object * a2;
  extern Object * a3;
  extern Object * a4;
  pc_t pc1 = CkPC1 - 5; /* sizeof(call) = 1+4 bytes */
  pc_t pc2 = CkPC2 - 5; /* sizeof(call) = 1+4 bytes */
  Object * ebp = CkP1;
  Object * esi = CkP2;
  Object * edx = CkP3;
  Object * edi = CkP4;

  CHECK_HEAP(IOACheck(); AOACheck());

  if (!CheckCell(a2)) RegError(pc1, pc2, "_a2", a2);
  if (!CheckCell(a3)) RegError(pc1, pc2, "_a3", a3);
  if (!CheckCell(a4)) RegError(pc1, pc2, "_a4", a4);
  if (!CheckCell(ebp)) RegError(pc1, pc2, "ebp", ebp);
  if (!CheckCell(esi)) RegError(pc1, pc2, "esi", esi);
  if (!CheckCell(edx)) RegError(pc1, pc2, "edx", edx);
  if (!CheckCell(edi)) RegError(pc1, pc2, "edi", edi);
}

#endif /* intel */

void PrintObjProto(Object *obj)
{
#ifdef NEWRUN
  if (obj==CALLBACKMARK){
    fprintf(output, "[CALLBACKMARK]");
    fflush(output);
    return;
  }
  if (obj==GENMARK){
    fprintf(output, "[GENMARK]");
    fflush(output);
    return;
  }
#endif /* NEWRUN */
  PrintProto(GETPROTO(obj));
}

void zero_check(char *p, long bytesize)
{                                                       
  long i;                                      
  if (ObjectAlign(bytesize)!=(unsigned)bytesize) {
    fprintf(output, "zero_check: ObjectAlign(bytesize)!=bytesize\n");   
  }
  for (i = (long)(bytesize)/4-1; i >= 0; i--)           
    if (*((long *)(p)+i) != 0) {                        
      fprintf(output,                                   
              "%s: %d: zero_check(0x%x, %d) failed: 0x%x: 0x%x\n",  
              __FILE__,                                 
              __LINE__,                                 
              (int)p,                                   
              (int)bytesize,
	      (int)((long *)(p)+i),
	      (int)*((long *)(p)+i)
	      );                                
      ILLEGAL;                                        
    }                                                   
}

void CkReg(char *func,long value, char *reg)   
{ 
  Object *theObj = (Object *)(value);                          
  if (theObj && /* Cleared registers are ok */                               
      !isProto(theObj) && /* e.g. AlloI is called with proto in ref. reg. */ 
      !isCode(theObj) && /* e.g. at INNER a ref. reg contains code addr */   
      !(inBetaHeap(theObj) && isObject(theObj))){                            
    fprintf(output,                                                          
	    "%s: ***Illegal reference register %s: 0x%x\n",                  
	    func, reg, (int)theObj); 
    ILLEGAL;								     
  }								             
}

void Illegal(char *file, int line)
{ 
#if defined(sgi) || defined(nti)
  GLOBAL(static unsigned break_inst);
  int (*f)(void);
#endif

  /* used to break in! */
  fprintf(output, "Illegal() called from %s, line %d\n",file,line);
  fflush(stdout);
  fflush(stderr);
  fflush(output) /* not necessarily same as stderr */;

#ifdef NEWRUN
  if (IOAActive){
    /* An IOAGc is going on. Thus StackEnd should be well defined */
    fprintf(output, "Attempting to do a stack dump\n");
    DebugStack=1;
    if (!isMakingDump){
      isMakingDump=1;
      ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, EmptyCellProcessFunc);
    }
  }
#endif /* NEWRUN */

  if (PrintStackAtIllegal){
#ifdef intel
    long stackvariable = 0;
    fprintf(output, "Illegal: Attempting to dump stack to stderr\n");
    fflush(output);
    PrintStack(&stackvariable);
#endif /* intel */
  }
  
  if (StopAtIllegal){
#ifdef RTVALHALLA
#ifdef UNIX
    if (valhallaID){
      fprintf(output, "debuggee: Illegal called. sleeping for 10 minuttes...\n");
      sleep(10*60);
      fprintf(output, "debuggee: 10 minuttes past - dying...\n");
    }
#endif /* UNIX */
#endif /* RTVALHALLA */
    fprintf(output, "Illegal: hardcoded break: %s, line %d\n",file,line);
    fflush(output);
#ifdef nti
    break_inst = 0xc39090cc; /* int 3 ; nop ; nop ; ret */
    f = (int(*)(void))&break_inst;
    f();
#endif

#ifdef linux
    __asm__("int3");
#endif

#ifdef sparc
    __asm__("unimp 0");
#endif

#ifdef sgi
    break_inst = 0x00000a0d; /* break 80 */
    f = (int(*)())&break_inst;
    f();
#endif

#ifdef hppa
    __asm__("break 0,0");
#endif

#ifdef MAC
    { 
      extern ExceptionHandler default_exceptionhandler;
      /* Reinstall original sighandler */
      
      if (default_exceptionhandler) {
        InstallExceptionHandler(default_exceptionhandler);
      }
      /* call MacsBug */
      DebugStr("\pIllegal Called. Type 'g' to return to shell");
    }
#endif /* MAC */
  }
}

#endif /* RTDEBUG */

#ifndef ALLOC_TRACE
#ifdef RUN
/* The following functions are only used in debug version, 
 * but declared unconditionally in Declaration.run.
 * Here we supply empty implementations to allow linking.
 */
void CTraceAlloc(void)
{}
#endif /* RUN */
#else /* ALLOC_TRACE */

void CTraceAlloc(void)
{
  pc_t pc1 = CkPC1 - 5; /* sizeof(call) = 1+4 bytes */
  pc_t pc2 = CkPC2 - 5; /* sizeof(call) = 1+4 bytes */
  Object * ebp = CkP1;
  Object * esi = CkP2;
  Object * edx = CkP3;
  Object * edi = CkP4;

  if (alloc_trace_handle)
      fprintf(alloc_trace_handle, "ebp = %p, esi = %p, edx = %p, edi = %p, pc1 = %p, pc2 = %p\n", ebp, esi, edx, edi, pc1, pc2);
}

#endif /* ALLOC_TRACE */
