/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * misc.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#if defined(MAC)
#include <CursorCtl.h>
#endif

/* Used by 
 *    objinterface.bet for: extGetCstring
 *    Xt for: copyInput
 *    basiclib/external: makeCBF
 */
long copyInput (long input)
{ return input; }

#ifdef nti
#include <string.h>
#ifdef nti_bor
#include <nonansi/alloc.h>
#else
#include <malloc.h>
#endif /* nti_bor */

char *convert_to_winnt(char *src, char nl)
{
  /* Allocate room for worst case: src is all '\n' */
  char *dst = malloc(strlen(src)*2+1), *ret = dst;
  if (dst) {
    do {
      if (*src == nl) {
        *dst++ = '\r'; *dst++ = '\n';
      } else
        *dst++ = *src;
    } while (*src++);
  }
  return ret;
}

char *convert_from_winnt(char *src, char nl)
{
  /* Allocate room for worst case: no '\n' */
  char *dst = malloc(strlen(src)+1), *ret = dst;
  if (dst) {
    do {
      if (src[0] == '\r' && src[1] == '\n') {
        *dst++ = nl; src++;
      } else
        *dst++ = *src;
    } while (*src++);
  }
  return ret;
}
#endif /* nti */

/* Used by objinterface.bet and lazyref_gc.c */
void assignRef(long *theCell, ref(Item) newObject)
/* If theCell is in AOA and will now reference an object in IOA, 
 * then insert in AOAtoIOA table.
 * If theCell is in AOA and will now reference a lazy dangler,
 * then insert in negAOArefs table. This may occur from e.g. missingRefs.replace.
 */
{
  *(struct Item **)theCell = newObject;
  if (!inIOA(theCell)){
    /* theCell is in AOA */
    if (inIOA(newObject)){
      AOAtoIOAInsert((handle(Object))theCell);
      return;
    }
    if (isLazyRef(newObject)){
      negAOArefsINSERT((long)theCell);
      return;
    }
  }
}

#ifdef RUN
/* Only used in debug version, but declared unconditionally in Declaration.run */
GLOBAL(long CkPC1);
GLOBAL(long CkPC2);
GLOBAL(ref(Object) CkP1);
GLOBAL(ref(Object) CkP2);
GLOBAL(ref(Object) CkP3);
GLOBAL(ref(Object) CkP4);
GLOBAL(ref(Object) CkP5);
#endif

#ifdef RTDEBUG

#ifdef NEWRUN
static void DoNothing(struct Object **theCell,struct Object *theObj)
{
}
#endif

void Illegal()
{ 
#if defined(sgi)
  GLOBAL(static unsigned break_inst);
  int (*f)(void);
#endif

  /* used to break in! */
  fprintf(output, "Illegal() called\n");

#ifdef NEWRUN
  if (IOAActive){
    /* An IOAGc is going on. Thus StackEnd should be well defined */
  fprintf(output, "Attempting to do a stack dump\n");
  DebugStack=1;
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, DoNothing);
  }
#endif
  
  if (StopAtIllegal){
    fprintf(output, "Illegal: hardcoded break!\n");

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
    /* call MacsBug */
    DebugStr("\pIllegal Called. Type 'g' to return to shell");
#endif
  }
}
#endif

#ifdef RTDEBUG
GLOBAL(long isObjectState);
#endif

long isObject( theObj)
  ref(Object) theObj;
{ 
#if defined(sparc) || defined(hppa)
  /* For the SPARC isObject also checks alignment constraints */
  if (((unsigned)theObj & 7) != 0)
    return FALSE;
#endif /* defined(sparc) || defined(hppa) */
  /* Check that theObj is non-negative */
  DEBUG_CODE(isObjectState=0);
  if (!isPositiveRef(theObj)) return FALSE;

  DEBUG_CODE(isObjectState=1);
  /* check that the GCAttr of the object is valid. */
  if( inBetaHeap((ref(Object))(theObj->Proto)) ) return FALSE;

  DEBUG_CODE(isObjectState=2);
  if( theObj->Proto == 0 ) return FALSE;

  DEBUG_CODE(isObjectState=3);
  if( inAOA(theObj) && ((isStatic(theObj->GCAttr)) || (theObj->GCAttr == 0)) ) 
    return TRUE;

  DEBUG_CODE(isObjectState=4);
  if( (isStatic(theObj->GCAttr)) || isAutonomous(theObj->GCAttr) ){
    DEBUG_CODE(isObjectState=5);
    return TRUE;
  } else {
    DEBUG_CODE(isObjectState=6);
    if( inToSpace(theObj->GCAttr) || inAOA(theObj->GCAttr) ){
      DEBUG_CODE(isObjectState=7);
      return TRUE;
    } else {
      DEBUG_CODE(isObjectState=8);
      return FALSE;
    }
  }
}

long inBetaHeap( theObj)
  ref(Object) theObj;
{ 
#if defined(sparc) || defined(hppa) 
    /* For the SPARC inBetaHeap also checkes alignment constraints */
    if (((unsigned)theObj & 7) != 0)
      return FALSE;
#endif /* defined(sparc) || defined(hppa) */
  if (!isPositiveRef(theObj)) return FALSE;
#ifdef MT
  if ((gIOA<(long*)theObj) && inIOA(theObj)) return TRUE;
#else
  if (inIOA( theObj)) return TRUE;
#endif
  if (inAOA( theObj)) return TRUE;
  if (inLVRA( theObj)) return TRUE;
  return FALSE;
}

#ifdef RTDEBUG
void Claim( expr, message)
  long  expr;
  ptr(char) message;
{
  if( expr == 0 ){
    fprintf(output, "\n\nAssumption failed: %s\n\n", message);
#ifdef intel
    if (CkPC1 && CkPC2){
      fprintf(output, "Caused by Ck called from PC=0x%x (called from 0x%x)\n\n", (int)CkPC1, (int)CkPC2); 
    }
#endif

    fprintf(output,
	    "IOA:     0x%x, IOATop:     0x%x, IOALimit:     0x%x\n",
	    (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit);
    fprintf(output,
	    "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	    (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
    Illegal(); /* Usefull to break in */
  }
}
#endif

#ifdef RTDEBUG
GLOBAL(static char __CkString[100]);
void CCk(void *r, char *fname, int lineno, char *ref)
{
  register struct Object* rr = (struct Object *)r; 

  CHECK_HEAP(IOACheck(); LVRACheck(); AOACheck());

#if 0
  fprintf(output, "Ck: IOATop is 0x%x\n", (int)IOATop); fflush(output);
#endif
 
  if(r) 
    {
      sprintf(__CkString, 
	      "%s:%d: Ck(%s) (%s=0x%x)", fname, lineno, ref, ref, (int)(r));
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
      /* Check alignment */
      Claim(isLazyRef(r) || (((long)r&3)==0), __CkString);
      /* Check it's in a heap */
      Claim(inIOA(rr) || inAOA(rr) || inLVRA(rr) || isLazyRef(rr), __CkString);
    }
}

long isInIOA(long x)
{
  return (long)inIOA(x);
}
long isInToSpace(long x)
{
  return (long)inToSpace(x);
}
long isInAOA(long x)
{
  return (long)inAOA(x);
}
#endif

#if defined(MAC)
GLOBAL(static long gcRotateCursor)=0;
void InitTheCursor(void)   
{ 
  if(StandAlone == 0 || gcRotateCursor) InitCursorCtl(0); 
}

void RotateTheCursor() 
{ 
  if(StandAlone == 0 || gcRotateCursor) SpinCursor(32);
}

void RotateTheCursorBack()
{
  if(StandAlone == 0 || gcRotateCursor) SpinCursor(-32);
}

#endif


/* Only used in debug version, but declared unconditionally in Declaration.run */
void NotifyRTDebug() 
{
#ifdef RTDEBUG
  Notify("RTS: Runtime routines perform consistency checks on registers.");
#endif /* RTDEBUG */
}

#ifdef RTDEBUG

void PrintHeap(long * startaddr, long numlongs)
{ 
  int i;
  struct Object *ref;

  ref=(struct Object *)startaddr;
  fprintf(output, "\n\nPrintHeap:\n");
  fprintf(output,
	  "IOA:     0x%x, IOATop:     0x%x, IOALimit:     0x%x\n",
	  (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit);
  fprintf(output,
	  "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	  (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
  fprintf(output, "\nDisplaying %d longs starting from address 0x%x",
	  (int)numlongs, (int)startaddr);
  if (inBetaHeap(ref)){
    if (inIOA(ref)) 
      fprintf(output, " (IOA)");
    if (inAOA(ref)) 
      fprintf(output, " (AOA)");
    if (inLVRA(ref)) 
      fprintf(output, " (LVRA)");
    if (ToSpace<=(long*)ref && (long*)ref<ToSpaceLimit)
      fprintf(output, " (ToSpace)");
  } else {
    fprintf(output, " (not in beta heap)");
  }
  fprintf(output, ":\n\n");

  for (i=0; i<numlongs; i++){
    fprintf(output, 
	    " [%d] 0x%08x: 0x%08x", 
	    i, 
	    (int)(startaddr+i), 
	    (int)(*(startaddr+i)));
    ref=(struct Object *)(*(startaddr+i));
    if (inBetaHeap(ref)){
      if (inIOA(ref)) 
	fprintf(output, " (IOA)");
      if (inAOA(ref)) 
	fprintf(output, " (AOA)");
      if (inLVRA(ref)) 
	fprintf(output, " (LVRA)");
      if (ToSpace<=(long*)ref && (long*)ref<ToSpaceLimit)
	fprintf(output, " (ToSpace)");
    } else {
      if (ref){
	fprintf(output, " (not in beta heap)");
      } else {
	fprintf(output, " (NONE)");
      }
    }
    fprintf(output, "\n");
  }
  fprintf(output, "\n");

  PrintHeapUsage("");
    
  fflush(output);
  return;
}


#ifdef intel
static void RegError(long pc1, long pc2, char *reg, ref(Object) value)
{
  fprintf(output, "\nIllegal value for GC register at PC=0x%x (called from 0x%x): %s=0x%x ", 
	  (int)pc1, (int)pc2, reg, (int)value);
  if (inIOA(value)){
    fprintf(output, "(is in IOA, but is not a legal object)\n");
  }
  if (inAOA(value)){
    fprintf(output, "(is in AOA, but is not a legal object)\n");
  }
  if (inLVRA(value)){
    fprintf(output, "(is in LVRA)\n");
  }
  if (inToSpace(value)){
    fprintf(output, "(is in ToSpace)\n");
  }
  fprintf(output, "\n");
  fflush(stdout);
  Illegal();
}

static long CheckCell(struct Object *theCell)
{
  if(theCell) {
    if (inBetaHeap(theCell)) {
      if (isObject(theCell) ||
	  isValRep(theCell) ||
	  inLVRA(theCell)  /* may point to old place in LVRA if there has just been an LVRA GC */
	  ) 
	return TRUE;
      return FALSE;
    }
  }
  return TRUE;
}
#endif /* intel */
#endif /* RTDEBUG */

/* Only used in debug version, but declared unconditionally in Declaration.run */
void CheckRegisters(void)
{
#ifdef RTDEBUG
#if (defined(linux) || defined(nti))
  extern ref(Object) a2;
  extern ref(Object) a3;
  extern ref(Object) a4;
  long pc1 = CkPC1 - 5; /* sizeof(call) = 1+4 bytes */
  long pc2 = CkPC2 - 5; /* sizeof(call) = 1+4 bytes */
  ref(Object) ebp = CkP1;
  ref(Object) esi = CkP2;
  ref(Object) edx = CkP3;
  ref(Object) edi = CkP4;

  CHECK_HEAP(IOACheck(); LVRACheck(); AOACheck());

  if (!CheckCell(a2)) RegError(pc1, pc2, "_a2", a2);
  if (!CheckCell(a3)) RegError(pc1, pc2, "_a3", a3);
  if (!CheckCell(a4)) RegError(pc1, pc2, "_a4", a4);
  if (!CheckCell(ebp)) RegError(pc1, pc2, "ebp", ebp);
  if (!CheckCell(esi)) RegError(pc1, pc2, "esi", esi);
  if (!CheckCell(edx)) RegError(pc1, pc2, "edx", edx);
  if (!CheckCell(edi)) RegError(pc1, pc2, "edi", edi);
#endif /* (defined(linux) || defined(nti)) */
#endif /* RTDEBUG */
}
