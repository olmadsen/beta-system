/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * misc.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#ifdef PERSIST
#include "../P/referenceTable.h"
#endif /* PERSIST */

#define FAST_DUMP 1

#ifdef MAC
#include "trie.h"
#else
#include "../P/trie.h"
#endif /* MAC */

#ifdef UNIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#endif /* UNIX */

#if defined(MAC)
#include <MachineExceptions.h>
#include <CursorCtl.h>
#include <Events.h>
#include <Windows.h>
#endif


/* Hej Peter!  
 *
 * Jeg bliver nød til at have denne funktion nedenunder
 * med, ellers kan jeg ikke compilere denne fil uden optimering. Jeg
 * har brug for at kompilere denne fil uden optimering.
 */
void gcmisc_dummy() {
#ifdef sparc
  USE();
#endif /* sparc */
}

static Trie *trie;

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
#include <alloc.h>
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

/* Compare two null terminated strings non case sensitively */
int EqualNCS(char *s1, char *s2)
{
  /*fprintf(output, "EqualNCS:%s:%s:", s1, s2);*/
  while (tolower(*s1) == tolower(*s2)) {
    if (*s1 == '\0') {
      /*fprintf(output, "1\n");*/
      return 1;
    }
    s1++; s2++;
  }
  /*fprintf(output, "0\n");*/
  return 0;
}

/* Used by objinterface.bet */
void assignRef(long *theCell, Item * newObject)
/* If theCell is in AOA and will now reference an object in IOA, 
 * then insert in AOAtoIOA table.
 */
{
  *(Item **)theCell = newObject;
  if (!inIOA(theCell)){
    /* theCell is in AOA */
    if (inIOA(newObject)){
#ifdef MT
      MT_AOAtoIOAInsert((Object **)theCell);
#else /* MT */
      AOAtoIOAInsert((Object **)theCell);
#endif /* MT */
      return;
    }
#ifdef PERSIST
    else if (inPIT(newObject)) {
      newAOAclient((unsigned long)newObject, (Object **)theCell);
      return;
    }
#endif /* PERSIST */
  }
}

#ifdef RUN
/* Only used in debug version, but declared unconditionally in Declaration.run */
GLOBAL(long CkPC1);
GLOBAL(long CkPC2);
GLOBAL(Object * CkP1);
GLOBAL(Object * CkP2);
GLOBAL(Object * CkP3);
GLOBAL(Object * CkP4);
GLOBAL(Object * CkP5);
#endif

int strongIsObject(Object *obj)
{
  ProtoType *proto;
  long gc;
  
  if (!inBetaHeap(obj)) {
    if (obj) {
      DEBUG_STRONGISOBJECT({
	fprintf(output,"strongIsObject: (0x%X) is not in heap\n", (int)obj);
      });
      return 0; 
    } else {
      return 1;
    }
  }
  
  if (ObjectAlign((unsigned)obj) != (unsigned)obj) {
    DEBUG_STRONGISOBJECT({
      fprintf(output,"strongIsObject: (0x%X) is unaligned\n", (int)obj);
    });
    return 0;
  }
  
  proto = GETPROTO(obj);
  gc = obj->GCAttr;
  
  if (inAOA(obj)) {
    if (gc == FREECHUNK) {
      DEBUG_STRONGISOBJECT({
	fprintf(output,"strongIsObject: Free chunk in AOA\n");
      });
      return 0;
    }
  }

  if (inIOA(obj)) {
    if (IOAActive) {
      if (!(isStatic(gc) || isAutonomous(gc) || isForward(gc))) {
	DEBUG_STRONGISOBJECT({
	  fprintf(output,"strongIsObject: Is not static or autonomous (1)\n");
	});
	return 0;
      }
    } else {
      if (!(isStatic(gc) || isAutonomous(gc))) {
	DEBUG_STRONGISOBJECT({
	  fprintf(output,"strongIsObject: Is not static or autonomous (2)\n");
	});
	return 0;
      }
    }
  } 
  
  if (inToSpace(obj)) {
    if (!(isStatic(gc) || isAutonomous(gc))) {
      DEBUG_STRONGISOBJECT({
	fprintf(output,"strongIsObject: Is not static or autonomous (3) (gc = 0x%X)\n", (int)gc);
      });
      return 0;
    }
  }
  
  if (!isSpecialProtoType(proto)) {
#ifdef RISC
    if (((long)proto) & 3) {
      DEBUG_CODE(fprintf(output,"strongIsObject: proto is not 4-aligned: 0x%08X\n", (int)proto));
      DEBUG_CODE(fflush(output));
      ILLEGAL;
      return 0;
    }
#endif
    if (!IsBetaDataAddrOfProcess((unsigned long)proto)) {
      DEBUG_CODE(fprintf(output,"strongIsObject: proto is not in data segment: 0x%08X\n", (int)proto));
      DEBUG_CODE(fflush(output));
      ILLEGAL;
      return 0;
    }
  }
  
  return 1;
}

void PrintProto(ProtoType *proto)
{
  fprintf(output, "%s", ProtoTypeName(proto));
  if (!SimpleDump){
    PrintCodeAddress((long)proto);
  }
  fflush(output);
}

void PrintCodeAddress(unsigned long addr)
{
  char *lab = getLabel(addr);
  if (labelOffset){
    fprintf(output, " <%s+0x%x>", lab, (int)labelOffset);
  } else {
    fprintf(output, " <%s>", lab);
  }    
  fflush(output);
}


#ifdef RTDEBUG

#ifdef NEWRUN
static void DoNothing(Object **theCell,Object *theObj)
{
}
#endif

long isObjectState;

long isObject(void *theObj)
{ 
  ProtoType *proto;
  Object *obj;
  long gc;

  if (FastIsObject){
    /* Behave like non-debug isObject */
    goto success;
  }

  obj = (Object*)theObj;
  
  isObjectState = 99;
  if (!strongIsObject(obj)) {
      goto failure;
  }
  
  isObjectState = 1;
  if (ObjectAlign((unsigned)obj) != (unsigned)obj)
    goto failure;

  isObjectState = 2;
  if (!inBetaHeap(obj))
    goto failure;

  isObjectState = 3;
  proto = GETPROTO(obj);
  gc = obj->GCAttr;

  if (inAOA(obj)) {
    isObjectState = 4;
    if (gc == FREECHUNK)
      goto failure;
  }
  
  if (inIOA(obj)) {
    if (IOAActive) {
      isObjectState = 5;
      if (!(isStatic(gc) || isAutonomous(gc) || isForward(gc)))
	goto failure;
    } else {
      isObjectState = 6;
      if (!(isStatic(gc) || isAutonomous(gc)))
	goto failure;
    }
  } 

  if (inToSpace(obj)) {
    isObjectState = 7;
    if (!(isStatic(gc) || isAutonomous(gc)))
      goto failure;
  }
    
  if (!isSpecialProtoType(proto)) {
#ifdef RISC
    isObjectState = 8;
    if (((long)proto) & 3)
      goto failure;
#endif

    isObjectState = 9;
    if (!IsPrototypeOfProcess((long)proto))
        goto failure;
  }
  
  isObjectState = 10;
  if (ObjectSize(obj) <= 0)
    goto failure;

  isObjectState = 11;
  if (ObjectAlign(4*ObjectSize(obj))!=4*(unsigned)ObjectSize(obj))
    goto failure;

success:
  return 1;
  
failure:
  /* Hmmm, here we have a situation where the debug runtime systems
   * rejects an object reference that the non-debug version would
   * accept (isObject is defined to TRUE in non-debug). 
   * This is suspicious and gives a difference in behaviour
   * - we have better issue a warning, and call ILLEGAL.
   */
  fprintf(output, "RTS: DEBUG isObject(0x%x) returns FALSE (state = %d).\n", (int)theObj, (int)isObjectState);
  return 0;
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

void PrintRef(Object *ref)
{
  if (ref) {
#ifdef NEWRUN
    if (ref==CALLBACKMARK){
      fprintf(output, " CALLBACKMARK (%d)\n", (int)ref);
      fflush(output);
      return;
    }
    if (ref==GENMARK){
      fprintf(output, " GENMARK (%d)\n", (int)ref);
      fflush(output);
      return;
    }
#endif /* NEWRUN */
    if (inBetaHeap(ref) && isObject(ref) ){
      fprintf(output, " is object");
      if (IsPrototypeOfProcess((long)GETPROTO(ref))) {
	fprintf(output, " (");
	DescribeObject(ref);
	fprintf(output, ")");
      } else {
	fprintf(output, " proto NOT ok: 0x%x", (int)GETPROTO(ref));
      }
    } else {
      fprintf(output, " is NOT object");
      if (isCode(ref)) {
	char *lab = getLabel((unsigned long)ref);
	fprintf(output, " (is code: <%s+0x%x>)", lab, (int)labelOffset);
      } else {
	PrintWhichHeap(ref); /* Will most often be "(not in beta heap)" */
      }
    }
  }
  fflush(output);
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
      ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, DoNothing);
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
#endif

long inBetaHeap(Object *theObj)
{ 
#if !MMAPANYADDR
  if (!isPositiveRef(theObj)) return FALSE;
#endif
  if (inIOA(theObj)) return TRUE;
  if (inToSpace(theObj)) return TRUE;
  if (inAOA(theObj)) return TRUE;
  return FALSE;
}

#ifdef RTDEBUG
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
    lab = getLabel((unsigned long)CkPC1);
    fprintf(output, "I.e., Ck called from <%s+0x%x> ", lab, (int)labelOffset);
    lab = getLabel((unsigned long)CkPC2);
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
#endif

#ifdef RTDEBUG
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

long isInIOA(long x)
{
  return (long)inIOA(x);
}
long isInToSpace(long x)
{
  return (long)inToSpace(x);
}
long isInToSpaceArea(long x)
{
  return (long)inToSpaceArea(x);
}
#endif /* RTDEBUG */

#if defined(MT) || defined(RTDEBUG)
long isInAOA(long x)
{
  return (long)inAOA(x);
}
#endif

GLOBAL(static long gcGiveTime)=0;
void StartGiveTime(void)
{   
  gcGiveTime=1;
#if defined(Mac)
  gcInbackground = FALSE;
#endif
  return;
}

void StopGiveTime(void)
{  
  gcGiveTime=0;
  return;
}


#if defined(MAC)
#include <ToolUtils.h>

GLOBAL(static long gcRotateCursor)=0;
GLOBAL(static Boolean gcInbackground)=FALSE;

void GiveTime(void)
{
  EventRecord   event;
  Boolean       gotEvent;
  WindowPtr     thisWindow;
  short         part;
  long          menuResult;
  short         menuID;
  short         menuItem;
  Str255        daName;
  short         daRefNum;
  
  gotEvent = WaitNextEvent(everyEvent, &event, 2, 0);
  if (gotEvent) {
    switch (event.what) {
    case mouseDown:
      part = FindWindow(event.where, &thisWindow);
      switch(part) {
      case inMenuBar:
        menuResult = MenuSelect(event.where);
        menuID = HiWord(menuResult);
        menuItem = LoWord(menuResult);
        switch(menuID) {
        case 128: /* Apple Menu */
          switch(menuItem) {
          case 1:
            break;
          default:
            GetMenuItemText(GetMenuHandle(128), menuItem, daName);
            daRefNum = OpenDeskAcc(daName);
            break;
          }
          break;
        }
        break;
      case inSysWindow:
        SystemClick(&event, thisWindow);
        break;
      case inContent:
        break;
      case inDrag:
        break;
      case inGrow:
        break;
      case inGoAway:
        break;
      case inZoomIn:
        break;
      case inZoomOut:
        break;
      }
      break;
    case mouseUp:
      break;
    case keyDown:
    case autoKey:
      break;
    case activateEvt:
      break;
    case updateEvt:
      thisWindow = (WindowPtr) event.message;
      BeginUpdate(thisWindow);
      EndUpdate(thisWindow);
      break;
    case diskEvt:
      break;
    osEvt:
      break;
    kHighLevelEvent:
      break;
    }
  }
  return;
}

void InitTheCursor(void)   
{ 
  
  if(StandAlone == 0 || gcRotateCursor) InitCursorCtl(0); 
  else {
    if (GetResource('acur', 0)) {
      InitCursorCtl(0); 
    }
  }
}

void RotateTheCursor() 
{
  if(StandAlone == 0 || gcRotateCursor) SpinCursor(32);
  if (gcGiveTime && StandAlone) {
    SpinCursor(32);
    GiveTime();
  }
}

void RotateTheCursorBack()
{ 
  if(StandAlone == 0 || gcRotateCursor) SpinCursor(-32);
  if (gcGiveTime && StandAlone) {
    SpinCursor(-32);
    GiveTime();
  }
}

#endif /* MAC */



/* Only used in debug version, but declared unconditionally in Declaration.run */
void NotifyRTDebug() 
{
#ifdef RTDEBUG
  Notify("RTS: Runtime routines perform consistency checks on registers.");
#endif /* RTDEBUG */
}

#ifdef RTDEBUG

const char *WhichHeap(Object *ref)
{
  if (inBetaHeap(ref)){
    if (inIOA(ref)) 
      return "(IOA)";
    if (inAOA(ref)) 
      return "(AOA)";
    if (inToSpace(ref)){
      return "(ToSpace)";
    } else {
      if (inToSpaceArea(ref)){
	return "(ToSpace area)";
      } else {
	return "(Unknown part of heap!)";
      }
    }
  } else {
    if (ref){
      return "(not in beta heap)";
    } else {
      return "(NONE)";
    }
  }
}

void PrintWhichHeap(Object *ref)
{
  fprintf(output, " %s", WhichHeap(ref));
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
static void RegError(unsigned long pc1, unsigned long pc2, char *reg, Object * value)
{ 
  char *lab;
  fprintf(output, 
	  "\nIllegal value for GC register %s at PC=0x%x (called from 0x%x): %s=0x%x\n", 
	  reg, 
	  (int)pc1, 
	  (int)pc2, 
	  reg, 
	  (int)value);
  lab = getLabel(pc1);
  fprintf(output, "I.e., PC is <%s+0x%x> ", lab, (int)labelOffset);
  lab = getLabel(pc2);
  fprintf(output, ", called from <%s+0x%x>\n", lab, (int)labelOffset);
  
  if (inBetaHeap(value)){
    if (inIOA(value)){
      fprintf(output, "%s points to IOA, but not to a legal object.\n", reg);
    }
    if (inAOA(value)){
      fprintf(output, "%s points to AOA, but not to a legal object.\n", reg);
    }
    if (inToSpaceArea(value)){
      fprintf(output, "%s points in to ToSpace!\n", reg);
    }
  } else {
    fprintf(output, "%s points out of BETA heaps!\n", reg);
  }
  fprintf(output, "\n");
  ILLEGAL;
}

static long CheckCell(Object *theCell)
{
  if (theCell && inBetaHeap(theCell) && !isObject(theCell)) {
    return 0;
  }
  return 1;
}
#endif /* intel */
#endif /* RTDEBUG */

/* Only used in debug version, but declared unconditionally in Declaration.run */
void CheckRegisters(void)
{
#ifdef RTDEBUG
#if (defined(linux) || defined(nti))
  extern Object * a2;
  extern Object * a3;
  extern Object * a4;
  long pc1 = CkPC1 - 5; /* sizeof(call) = 1+4 bytes */
  long pc2 = CkPC2 - 5; /* sizeof(call) = 1+4 bytes */
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
#endif /* (defined(linux) || defined(nti)) */
#endif /* RTDEBUG */
}

/*************************** Label lookup by address ****************************/

typedef struct _label {
  unsigned long address;
  char *id;
} label;

GLOBAL(long labelOffset) = 0;
GLOBAL(label **labels) = 0;
GLOBAL(long numLabels) = 0;
GLOBAL(long maxLabels) = 2048;
GLOBAL(label **grouplabels) = 0;
GLOBAL(long numGroupLabels) = 0;
GLOBAL(long maxGroupLabels) = 2048;
#ifdef nti
GLOBAL(long process_offset) = 0;
#endif

/* Prototypes */
static void addLabelsFromGroupTable(void);
static char *getLabelExact(unsigned long addr);
static void addLabel(long adr, char *id);
static int cmpLabel(const void *left, const void *right);

static int isLocalLab(char *lab)
{
  /* Test for:
   *    L417 (linux, nti, ppcmac)
   *    .L417 (sun4s, sgi)
   *    L$C417 (hppa)
   */
  int l, L, i;

  if (!lab) return 0;
  l = strlen(lab);

  if (l<2) return 0;
  L=0;
#if defined(sun4s)||defined(sgi)
  if ((l<3) || (lab[0]!='.')) return 0; L=1;
#endif
#ifdef hpux9pa
  if ((l<4) || (lab[0]!='L')|| (lab[1]!='$')|| (lab[2]!='C')) return 0; L=2;
#else
  if (lab[L]!='L') return 0;
#endif
  for (i=L+1; i<l; i++){
    if ((lab[i]<'0') || (lab[i]>'9')) return 0;
  }
  return 1;
}

static void addLabel(long adr, char *id)
{
  label *lab;
  int len=strlen(id);
  char* buf;

  /* No need to check for slashes in id */

  /* Ignore locallabs */
  if (isLocalLab(id)){
    DEBUG_LABELS(fprintf(output, "addLabel: ignored locallab: %s\n", id));
    return;
  }

  /* Ignore duplicates */
  if (labels && getLabelExact(adr)) {
    /* There is already a symbol on that addr.  Ignore new one */
    return;
  } 

  buf = MALLOC(sizeof(label)+len+1);
  if (!buf) {
    INFO_LABELS(fprintf(output, "Allocation of label failed\n"));
    /* free previously allocated labels */
    FREE(labels);
    labels = 0;
    return;
  }
  INFO_ALLOC(sizeof(label)+len+1);

  lab = (label *) buf;
  lab->id = buf+sizeof(label);

  strcpy(lab->id, id);
  lab->address = adr;

  if (!labels) {
    labels=(label**)MALLOC(maxLabels * sizeof(label*));
    if (!labels) {
      INFO_LABELS(fprintf(output, "Failed to allocate memory for labels\n"));
      labels = 0; 
    }
    INFO_ALLOC(maxLabels * sizeof(label *));
  }
  if (numLabels>=maxLabels){
    maxLabels *= 2;
    INFO_LABELS(fprintf(output, "*"); fflush(output));
    labels=REALLOC(labels, maxLabels * sizeof(label*));
  }
  labels[numLabels] = lab;

#ifndef MAC
  /* Register label in trie */
  TInsert((unsigned long)(lab -> address), 
	  (unsigned long)(lab -> id), 
	  &trie, 
	  (unsigned long)(lab -> address));
  
#endif

  numLabels++;
  
}

static void addGroupLabel(long adr, char *id)
{
  label *lab;
  char* buf;
  int len = strlen(id);
  int i;
  int lastslash = 0;

  /* No need to check for locallabs and duplicates */

  /* Remove leading path */
  len  = strlen(id);
  for (i = 0; i < len; i++) {
    if (id[i] == '/') {
      lastslash = i+1;
    }
  } 

  buf = MALLOC(sizeof(label)+len+1-lastslash);
  if (!buf) {
    INFO_LABELS(fprintf(output, "Allocation of label failed\n"));
    /* free previously allocated labels */
    FREE(grouplabels);
    grouplabels = 0;
    return;
  }
  INFO_ALLOC(sizeof(label)+len+1-lastslash);

  lab = (label *) buf;
  lab->id = buf+sizeof(label);

  strcpy(lab->id, id+lastslash);
  lab->address = adr;

  if (!grouplabels) {
    grouplabels=(label**)MALLOC(maxGroupLabels * sizeof(label*));
    if (!grouplabels) {
      INFO_LABELS(fprintf(output, "Failed to allocate memory for group labels\n"));
      grouplabels = 0; 
    }
    INFO_ALLOC(maxLabels * sizeof(label *));
  }
  if (numGroupLabels>=maxGroupLabels){
    maxGroupLabels *= 2;
    INFO_LABELS(fprintf(output, "*"); fflush(output));
    grouplabels=REALLOC(grouplabels, maxGroupLabels * sizeof(label*));
  }
  grouplabels[numGroupLabels] = lab;

  numGroupLabels++;
  
}


static int cmpLabel(const void *left, const void *right)
{
  label **l = (label**)left, **r = (label**)right;

  return ((*l)->address - (*r)->address);
}

#define HAS_BSEARCH 1 /* possibly machine dependant */
/* Hmmm does not seem to work */
#undef HAS_BSEARCH

#ifdef HAS_BSEARCH
#define labelsearch bsearch
#else
static void* labelsearch(const void *key, const void *base,
			 size_t nmemb, size_t size,
			 int (*compar) (const void *keyval, const void *datum))
{
  size_t l, u, idx;
  const void *p;
  int comparison;
  
  l = 0;
  u = nmemb;
  while (l < u)
    {
      idx = (l + u) / 2;
      p = (void*) (((const char *) base) + (idx * size));
      comparison = (*compar)(key, p);
      if (comparison < 0)
	u = idx;
      else if (comparison > 0)
	l = idx + 1;
      else
	return (void*) p;
    }
  
  return NULL;
}
#endif /* HAS_BSEARCH */
 
label *label_candidate;
static int cmpLabelApprox(const void *key, const void *candidate)
{
  /* A little tricky since we must find the largest label "p" smaller 
   * than the address "key"
   */
  label **c = (label**)candidate;
  unsigned long k = (unsigned long)key;

  DEBUG_LABELS(fprintf(output, "cmpLabelApprox(key=0x%x, candidate->address=0x%x ", (int)k, (int)(*c)->address));

  if (k == (*c)->address) {
    /* label equal to address */
    label_candidate = *c;
    DEBUG_LABELS(fprintf(output, "returns 0\n"));
    return 0;
  }
  if (k < (*c)->address){
    /* label larger than address */
    DEBUG_LABELS(fprintf(output, "returns -1\n"));
    return -1;
  }
  /* label smaller than address */
  if (label_candidate->address < (*c)->address) {
    label_candidate = *c;
  }
  DEBUG_LABELS(fprintf(output, "returns 1\n"));
  return 1;
}

static void addLabelsFromGroupTable(void)
{
  group_header *gh;
  char theLabel[256];
  long mPart;
  long gPart;

  gh = NextGroup(0);
  while (gh) {
    long* proto = &(gh->protoTable[1]);
    int i, NoOfPrototypes;
    
    NoOfPrototypes = gh->protoTable[0];
    for (i=0; i<NoOfPrototypes; i++) {
      sprintf(theLabel, "%s:T%d", NameOfGroupMacro(gh), i+1);
      addGroupLabel((long)(*proto), theLabel);

      gPart=  G_Part(((ProtoType*)(*proto)));
      sprintf(theLabel, "%s:G%d", NameOfGroupMacro(gh), i+1);
      addGroupLabel(gPart, theLabel);
      
      mPart =  M_Part(((ProtoType*)(*proto)));
      if (mPart != MAXINT) {
	sprintf(theLabel, "%s:M%d", NameOfGroupMacro(gh), i+1);
	addGroupLabel(mPart, theLabel);
      }

      proto++;
    }
    gh = NextGroup(gh);
  }

  qsort(grouplabels, numGroupLabels, sizeof(label**), cmpLabel);
}

#ifdef UNIX
#ifndef hppa
/* static void *dl_self=0; */
#endif /* hppa */
#endif /* UNIX */

static void initLabels(void)
{
  char exefilename[500];
  char *theLabel;
  labeltable *table;
  long labelAddress;

#ifdef ppcmac
  addLabelsFromGroupTable();
  return;
#endif /* ppcmac */

#ifdef UNIX
#ifndef hppa
  /* dl_self = dlopen(NULL, (RTLD_NOW | RTLD_GLOBAL) ); */
#endif /* hppa */
#endif /* UNIX */
  
  trie = TInit();

  INFO_LABELS(fprintf(output, "[initLabels ... "); fflush(output););
  strcpy(exefilename, ArgVector[0]);
#ifdef nti
  /*fprintf(output, "%s\n", exefilename+strlen(exefilename)-4);*/
  if ((strlen(exefilename)<=4) || 
      (!EqualNCS(exefilename+strlen(exefilename)-4, ".exe"))){
    strcat(exefilename, ".exe");
  }
#endif /* nti */
  table = initReadNameTable(exefilename, 1);
  if (!table){
    INFO_LABELS(fprintf(output, "FAILED!]"); fflush(output));
    return;
  }
#ifdef nti
  process_offset = getProcessOffset(table, getMainPhysical());
  /*fprintf(output, "initLabels: ProcessOffset: 0x%x\n", process_offset);*/
#endif /* nti */
  /* Read labels */
  for (;;) {
    labelAddress = nextAddress(table);
    if (labelAddress==-1){
      /* Termination condition reached */
      break;
    }
    theLabel = nextLabel(table);
    DEBUG_LABELS({
      fprintf(output, "0x%08x %s\n",  (unsigned)labelAddress, theLabel);
      fflush(output);
    });
    addLabel(labelAddress, theLabel);
  }

  addLabelsFromGroupTable();

  INFO_LABELS(fprintf(output, " done]"); fflush(output));

  DEBUG_LABELS({
    fprintf(output, "Labels:\n");
    { 
      long n;
      for (n=0; n<numLabels; n++){
	fprintf(output, "0x%x\t%s\n", (unsigned)labels[n]->address, labels[n]->id);
      }
    }
    fflush(output);
  });

}

static char *getLabelExact(unsigned long addr)
{
  if (!addr) return NULL;
  
#ifdef nti
  addr -= process_offset;
#endif

#ifndef MAC
  if (labels) {
    return (char *)TILookup(addr, trie);
  }
#endif

  return NULL;
}

#if defined(sgi)
extern unsigned long etext;
#endif

char *getLabel (unsigned long addr)
{
  int skip_nm = 0;

#ifdef ppcmac
  labelOffset=0;
  return "<unknown>";
#endif /* ppcmac */

  if (!addr){
    labelOffset=0;
    return "<unknown>";
  }

  if (!labels && !grouplabels) initLabels();

#ifdef nti
  addr -= process_offset;
#endif

#if defined(sparc) || defined(linux)
  /* First try dladdr (for dynamic symbols) */
  /* FIXME: There are equivalent methods for PC,
   * see toollibs/labelnametable/private/name_to_address_ntibody.bet
   */
  {
    static Dl_info info;
    if (dladdr((void*)addr, &info)){
      labelOffset = (long)addr - (long)info.dli_saddr;
      return((char*)info.dli_sname);
    }
  }
#endif /* sparc || linux */

#if defined(sgi)||defined(sparc)
  if ((unsigned long)addr>(unsigned long)etext){
    skip_nm = 1;
  }
#endif

  if (!skip_nm){
    /* Try nm labels: binary search for largest label smaller than addr */
    if (labels && 
	((unsigned long)addr<(unsigned long)labels[numLabels-1]->address)) {
      label_candidate = labels[0];
      labelsearch((void*)addr, (void*)labels, numLabels, sizeof(label**), cmpLabelApprox);
      labelOffset = addr-(label_candidate->address);
      return label_candidate->id;
    }
  }

  /* Try Group labels: binary search for largest grouplabel smaller than addr */
  if (grouplabels && 
      ((unsigned long)addr<(unsigned long)grouplabels[numGroupLabels-1]->address)) {
    label_candidate = grouplabels[0];
    labelsearch((void*)addr, (void*)grouplabels, numGroupLabels, sizeof(label**), cmpLabelApprox);
    labelOffset = addr-(label_candidate->address);
    return label_candidate->id;
  }

  /* Give up: */
  labelOffset=0;
  return "<unknown>";
}

/************************* End Label lookup *************************/


/************************* DescribeObject: *************************/
#ifdef RTDEBUG

void DescribeObject(Object *theObj)
{
  ProtoType * theProto;

  if (!theObj){
    fprintf(output, "[NONE]");
    return;
  }
  theProto = GETPROTO(theObj);
  if (isSpecialProtoType(theProto)){
    switch (SwitchProto(theProto)){
    case SwitchProto(ComponentPTValue):
      fprintf(output, "Component: ");
      DescribeObject((Object *)((Component *)theObj)->Body);
      return;
    case SwitchProto(StackObjectPTValue):
      fprintf(output, "StackObj");
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(StructurePTValue):
      fprintf(output, 
	      "Struc: origin: 0x%x \"%s\", proto: 0x%x \"%s\"", 
	      (int)(((Structure *)theObj)->iOrigin),
	      ProtoTypeName(GETPROTO(((Structure *)theObj)->iOrigin)),
	      (int)(((Structure *)theObj)->iProto),
	      ProtoTypeName(((Structure *)theObj)->iProto)
	      );
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(DopartObjectPTValue):
      fprintf(output, 
	      "Dopart: origin: 0x%x, proto: 0x%x (%s)", 
	      (int)(((DopartObject *)theObj)->Origin),
	      (int)(GETPROTO(((DopartObject *)theObj)->Origin)),
	      ProtoTypeName(GETPROTO(((DopartObject *)theObj)->Origin))
	      );
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(DynItemRepPTValue):
    case SwitchProto(DynCompRepPTValue):
      fprintf(output, "ObjectRep"); 
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(RefRepPTValue):
      fprintf(output, "RefRep"); 
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(LongRepPTValue):
      fprintf(output, "IntegerRep"); 
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(ByteRepPTValue):
      fprintf(output, "CharRep: '");
      if ( ((((ValRep *)theObj)->HighBorder)-(((ValRep *)theObj)->LowBorder)+1) > 10 ){
	fprintf(output, "%s", (char *)((ValRep *)theObj)->Body);
	fprintf(output, "...'");
      } else {
	fprintf(output, "%s", (char *)((ValRep *)theObj)->Body);
	fprintf(output, "'");
      }
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(ShortRepPTValue):
      fprintf(output, "ShortRep");
      PrintWhichHeap(theObj);
      return;
    case SwitchProto(DoubleRepPTValue):
      fprintf(output, "RealRep");
      PrintWhichHeap(theObj);
      return;
    default:
      fprintf(output, "Unknown special prototype!");
      return;
    }
  } else {
    /* ordinary object */
    fprintf(output, "\"%s\" <%s>", 
	    ProtoTypeName(theProto), getLabel((long)theProto));
    PrintWhichHeap(theObj);
  }
}

#endif /* RTDEBUG */


double gettimestampdouble(void)
{
#ifdef MAC
  return (double)TickCount()/60.0;
#else

#ifdef nti
  return (double)GetTickCount()/1000.0;
#else
  static long firstsec = 0;
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp, &tzp);
  if (firstsec==0) {
    firstsec = (long)tp.tv_sec;
  }
  return ((double)tp.tv_sec-firstsec) + (double)tp.tv_usec/1000000.0;
#endif
#endif
}


long getmilisectimestamp(void)
{
#ifdef MAC
	return (TickCount() * 1000) / 60;
#else

#ifdef nti
  return GetTickCount();
#else
  static long firstsec = 0;
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp, &tzp);
  if (firstsec==0) {
    firstsec = (long)tp.tv_sec;
  }
  return 1000 * ((long)tp.tv_sec-firstsec) + (long)tp.tv_usec/1000;
#endif
#endif
}

long milisecsincelast(void)
{
  static long last = 0;
  long now = getmilisectimestamp();
  long diff = now - last;
  last = now;
  return diff;
}

ProtoType *getProto(Object *ref)
{
  return (ProtoType *)GETPROTO(ref);
}
