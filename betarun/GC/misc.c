/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * misc.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

#ifdef UNIX
#include <unistd.h>
#endif /* UNIX */

#if defined(MAC)
#include <MachineExceptions.h>
#include <CursorCtl.h>
#include <Events.h>
#include <Windows.h>
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

/* Used by objinterface.bet and lazyref_gc.c */
void assignRef(long *theCell, Item * newObject)
/* If theCell is in AOA and will now reference an object in IOA, 
 * then insert in AOAtoIOA table.
 * If theCell is in AOA and will now reference a lazy dangler,
 * then insert in negAOArefs table. This may occur from e.g. missingRefs.replace.
 */
{
  *(Item **)theCell = newObject;
  if (!inIOA(theCell)){/* inAOA? */
    /* theCell is in AOA */
    if (inIOA(newObject)){
#ifdef MT
      MT_AOAtoIOAInsert((Object **)theCell);
#else /* MT */
      AOAtoIOAInsert((Object **)theCell);
#endif /* MT */
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
GLOBAL(Object * CkP1);
GLOBAL(Object * CkP2);
GLOBAL(Object * CkP3);
GLOBAL(Object * CkP4);
GLOBAL(Object * CkP5);
#endif

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

  obj = (Object*)theObj;

  isObjectState = 1;
  if (ObjectAlign((unsigned)obj) != (unsigned)obj)
    return 0;

  isObjectState = 2;
  if (!inBetaHeap(obj))
    return 0;

  isObjectState = 3;
  proto = obj->Proto;
  gc = obj->GCAttr;

  if (inAOA(obj)) {
    isObjectState = 4;
    if (gc == FREECHUNK)
      return 0;
  }

  if (inIOA(obj)) {
    if (IOAActive) {
      isObjectState = 5;
      if (!(isStatic(gc) || isAutonomous(gc) || isForward(gc)))
	return 0;
    } else {
      isObjectState = 6;
      if (!(isStatic(gc) || isAutonomous(gc)))
	return 0;
    }
  } 

  if (inToSpace(obj)) {
    isObjectState = 7;
    if (!(isStatic(gc) || isAutonomous(gc)))
      return 0;
  }
    
  isObjectState = 8;
  if (!IsPrototypeOfProcess((long)proto))
    return 0;

  isObjectState = 0;
  return 1;
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
      Illegal();                                        
    }                                                   
}

void CkReg(char *func,long value, char *reg)   
{ 
  Object *theObj = (Object *)(value);                          
  if (theObj && /* Cleared registers are ok */                               
      !isLazyRef(theObj) &&                                                  
      !isProto(theObj) && /* e.g. AlloI is called with proto in ref. reg. */ 
      !isCode(theObj) && /* e.g. at INNER a ref. reg contains code addr */   
      !(inBetaHeap(theObj) && isObject(theObj))){                            
    fprintf(output,                                                          
	    "%s: ***Illegal reference register %s: 0x%x\n",                  
	    func, reg, (int)theObj); 
    Illegal();								     
  }								             
}

void Illegal()
{ 
#if defined(sgi) || defined(nti)
  GLOBAL(static unsigned break_inst);
  int (*f)(void);
#endif

  /* used to break in! */
  fprintf(output, "Illegal() called\n");
  fflush(stdout);
  fflush(stderr);
  fflush(output) /* not necessarily same as stderr */;

#ifdef NEWRUN
  if (IOAActive){
    /* An IOAGc is going on. Thus StackEnd should be well defined */
  fprintf(output, "Attempting to do a stack dump\n");
  DebugStack=1;
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, DoNothing);
  }
#endif
  
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
    fprintf(output, "Illegal: hardcoded break!\n");
    
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
  if (!isPositiveRef(theObj)) return FALSE;
  if (inIOA(theObj)) return TRUE;
  if (inToSpace(theObj)) return TRUE;
  if (inAOA(theObj)) return TRUE;
  return FALSE;
}

#ifdef RTDEBUG
void Claim(long expr, char *message)
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
  register Object* rr = (Object *)r; 

  CHECK_HEAP(IOACheck(); AOACheck());

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
#endif /* NEWRUN */
      /* Check alignment */
      Claim(isLazyRef(r) || (ObjectAlign((unsigned)r)==(unsigned)r), 
	    __CkString);
      /* Check it's in a heap */
      Claim(inIOA(rr) || inAOA(rr) || isLazyRef(rr), __CkString);
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
            GetMenuItemText(GetMenustruct 128 **, menuItem, daName);
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

void PrintWhichHeap(Object *ref)
{
  if (inBetaHeap(ref)){
    if (inIOA(ref)) 
      fprintf(output, " (IOA)");
    if (inAOA(ref)) 
      fprintf(output, " (AOA)");
    if (inToSpaceArea(ref))
      fprintf(output, " (ToSpace area)");
  } else {
    if (ref){
      fprintf(output, " (not in beta heap)");
    } else {
      fprintf(output, " (NONE)");
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
static void RegError(long pc1, long pc2, char *reg, Object * value)
{
  fprintf(output, 
	  "\nIllegal value for GC register %s at PC=0x%x (called from 0x%x): %s=0x%x\n", 
	  reg, 
	  (int)pc1, 
	  (int)pc2, 
	  reg, 
	  (int)value);
  fprintf(output, "I.e., PC is <%s+0x%x> ", getLabel(pc1), (int)labelOffset);
  fprintf(output, ", called from <%s+0x%x>\n", getLabel(pc2), (int)labelOffset);
  
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
  Illegal();
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
}

/*************************** Label Debug ****************************/

#undef DEBUG_LABELS 

typedef struct _label {
  long address;
  char *id;
} label;

GLOBAL(long labelOffset) = 0;
GLOBAL(label **labels) = 0;
GLOBAL(long numLabels) = 0;
GLOBAL(long maxLabels) = 1000;
#ifdef nti
GLOBAL(long process_offset) = 0;
#endif

static void initLabels()
{

#ifdef ppcmac
  return;
#endif
  char exefilename[500];
  char *theLabel;
  labeltable *table;
  long lastLab=0;
  long labelAddress;

  fprintf(output, "[initLabels ... ");
  fflush(output);
  sprintf(exefilename,"%s", ArgVector[0]);
#ifdef nti
  if ((strlen(exefilename)<=4) || 
      (strncasecmp(&exefilename[0]+strlen(exefilename), ".exe", 4)!=0)){
    strcat(exefilename, ".exe");
  }
#endif
  table = initReadNameTable(exefilename, 1);
  if (!table){
    fprintf(output, "FAILED!]");
    fflush(output);
    return;
  }
#ifdef nti
  {
    extern void main();
    process_offset = getProcessOffset((long)&main);
  }
#endif
  labels=(label**)MALLOC(maxLabels * sizeof(label*));
  if (!labels) {
    fprintf(output, "Failed to allocate memory for labels\n");
    labels = 0; 
  }
  INFO_ALLOC(maxLabels * sizeof(label *));
  /* Read labels */
  for (;;lastLab++){
    label *lab;
    lab = (label *) MALLOC(sizeof(label));
    if (!lab){
      fprintf(output, "Allocation of label failed\n");
      /* free previously allocated labels */
      FREE(labels);
      labels = 0;
      break;
    }
    INFO_ALLOC(sizeof(label));
    labelAddress = nextAddress(table);
    if (labelAddress==-1){
      /* Termination condition reached */
      break;
    }
    theLabel = nextLabel(table);
#if 0
#ifdef DEBUG_LABELS
    fprintf(output, "0x%08x %s\n",  (unsigned)labelAddress, theLabel);
    fflush(output);
#endif
#endif
    lab->id = (char *)MALLOC(strlen(theLabel)+1);
    if (!lab) {
      fprintf(output, "Allocation of label id failed\n");
      /* free previously allocated labels */
      FREE(labels);
      labels = 0;
      break;
    }
    INFO_ALLOC(strlen(theLabel)+1);
    lab->address = labelAddress;
    strcpy(lab->id, theLabel);
    if (lastLab>=maxLabels){
      maxLabels *= 2;
      fprintf(output, "*"); fflush(output);
      labels=REALLOC(labels, maxLabels * sizeof(label*));
    }
    labels[lastLab] = lab;
  }
  numLabels=lastLab;
  fprintf(output, " done]");
  fflush(output);
#ifdef DEBUG_LABELS
  fprintf(output, "Labels:\n");
  { 
    long n;
    for (n=0; n<lastLab; n++){
      fprintf(output, "0x%x\t%s\n", (unsigned)labels[n]->address, labels[n]->id);
    }
  }
  fflush(output);
#endif
}

char *getLabel (long addr)
{
  long n;

#ifdef ppcmac
  labelOffset=0;
  return "<unknown>";
#endif

if (!labels) initLabels();
  if (!addr){
    labelOffset=0;
    return "<unknown>";
  }
#ifdef nti
  addr -= process_offset;
#endif
  if (labels){
    for (n=numLabels-1; n>=0; n--){
      if (labels[n]->address <= addr){
	labelOffset = addr-(labels[n]->address);
	return labels[n]->id;
      }
    }
  }
  labelOffset=0;
  return "<unknown>";
}

/************************* End Label Debug *************************/


#endif /* RTDEBUG */
