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

#ifdef RTDEBUG

#ifdef NEWRUN
static void DoNothing(struct Object **theCell,struct Object *theObj)
{
}
#endif

void Illegal()
{ 
#if defined(sgi)
  static unsigned break_inst;
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

#ifdef sun4s
    __asm__("illtrap 0");
#endif
#ifdef sun4
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
long isObjectState;
#endif

long isObject( theObj)
  ref(Object) theObj;
{ 
#if defined(sparc) || defined(hppa) || defined(crts)
  /* For the SPARC isObject also checks alignment constraints */
  if (((unsigned)theObj & 7) != 0)
    return FALSE;
#endif /* defined(sparc) || defined(hppa) || defined(crts) */
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
#if defined(sparc) || defined(hppa) || defined(crts)
    /* For the SPARC inBetaHeap also checkes alignment constraints */
    if (((unsigned)theObj & 7) != 0)
      return FALSE;
#endif /* defined(sparc) || defined(hppa) || defined(crts) */
  if (!isPositiveRef(theObj)) return FALSE;
  if (inIOA( theObj)) return TRUE;
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
    fprintf(output,
	    "IOA:     0x%x, IOATop:     0x%x, IOALimit:     0x%x\n",
	    (int)IOA, (int)IOATop, (int)IOALimit);
    fprintf(output,
	    "ToSpace: 0x%x, ToSpaceTop: 0x%x, ToSpaceLimit: 0x%x\n", 
	    (int)ToSpace, (int)ToSpaceTop, (int)ToSpaceLimit);
    Illegal(); /* Usefull to break in */
  }
}
#endif

#ifdef RTDEBUG
static char __CkString[100];
void CCk(void *r, char *fname, int lineno, char *ref)
{
  register struct Object* rr = (struct Object *)r; 

  CHECK_HEAP(IOACheck(); LVRACheck(); AOACheck());
 
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
#endif

#if defined(MAC)
long gcRotateCursor=0;
void InitTheCursor()   { if(StandAlone == 0 || gcRotateCursor) InitCursorCtl(0); }
void RotateTheCursor() { if(StandAlone == 0 || gcRotateCursor) SpinCursor(32); }
void RotateTheCursorBack() { if(StandAlone == 0 || gcRotateCursor) SpinCursor(-32); }
#endif


/* Only used in debug version, but declared unconditionally in Declaration.run */
void NotifyRTDebug() 
{
#ifdef RTDEBUG
  Notify("RTS: Runtime routines perform consistency checks on registers.");
#endif /* RTDEBUG */
}

/* Only used in debug version, but declared unconditionally in Declaration.run */
long CkPC1;
long CkPC2;
ref(Object) CkP1;
ref(Object) CkP2;
ref(Object) CkP3;
ref(Object) CkP4;
ref(Object) CkP5;

#ifdef RTDEBUG
#if defined(mc68020)||defined(nti)||defined(linux)
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
#endif /* defined(mc68020)||defined(nti)||defined(linux) */
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
#ifdef mc68020
  long pc1 = CkP1;
  long pc2 = CkP2;
  ref(Object) a0 = CkP1;
  ref(Object) a1 = CkP2;
  ref(Object) a2 = CkP3;
  ref(Object) a3 = CkP4;
  ref(Object) a4 = CkP5;
  if (!CheckCell(a0)) RegError(pc1, pc2, "a0", a0);
  if (!CheckCell(a1)) RegError(pc1, pc2, "a1", a1);
  if (!CheckCell(a2)) RegError(pc1, pc2, "a2", a2);
  if (!CheckCell(a3)) RegError(pc1, pc2, "a3", a3);
  if (!CheckCell(a4)) RegError(pc1, pc2, "a4", a4);
#endif /* mc68020*/
#endif /* RTDEBUG */
}
