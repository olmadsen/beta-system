/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * misc.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, and Jacob Seligmann
 */

#include "beta.h"

void misc_dummy()
{
#ifdef sparc
  USE();
#endif /* sparc */
}

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

/* Used by objinterface.bet and lazyref_gc.c */
void assignRef(long *theCell, Item * newObject)
/* If theCell is in AOA and will now reference an object in IOA, 
 * then insert in AOAtoIOA table.
 * If theCell is in AOA and will now reference a lazy dangler,
 * then insert in negAOArefs table. This may occur from e.g. missingRefs.replace.
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
#ifdef RTLAZY
    if (isLazyRef(newObject)){
      negAOArefsINSERT((long)theCell);
      return;
    }
#endif /* RTLAZY */
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
  
  if (ObjectAlign((unsigned)obj) != (unsigned)obj)
    return 0;

  if (!inBetaHeap(obj))
    return 0;

  proto = GETPROTO(obj);
  gc = obj->GCAttr;

  if (inAOA(obj)) {
    if (gc == FREECHUNK)
      return 0;
  }

  if (inIOA(obj)) {
    if (IOAActive) {
      if (!(isStatic(gc) || isAutonomous(gc) || isForward(gc)))
	return 0;
    } else {
      if (!(isStatic(gc) || isAutonomous(gc)))
	return 0;
    }
  } 
  
  if (inToSpace(obj)) {
    if (!(isStatic(gc) || isAutonomous(gc)))
      return 0;
  }
  
  if (!isSpecialProtoType(proto)) {
#ifdef RISC
    if (((long)proto) & 3) {
      fprintf(output,"proto is not 4-aligned: 0x%08X\n", (int)proto);
      fflush(output);
      return 0;
    }
#endif
    if (!IsBetaDataAddrOfProcess((unsigned long)proto)) {
      fprintf(output,"proto is not in data segment: 0x%08X\n", (int)proto);
      fflush(output);
      return 0;
    }
  }
  
  return 1;
}

void PrintProto(ProtoType *proto)
{
  fprintf(output, "\"%s\" <%s>", ProtoTypeName(proto), getLabel((long)proto));
  fflush(output);
}

void PrintCodeAddress(long addr)
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
   * - we have better issue a warning, and call Illegal().
   */
  fprintf(output, "RTS: DEBUG isObject(0x%x) returns FALSE.\n", (int)theObj);
  Illegal();
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

void PrintRef(Object *ref)
{
  if (ref) {
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
	char *lab = getLabel((long)ref);
	fprintf(output, " (is code: <%s+0x%x>)", lab, (int)labelOffset);
      } else {
	PrintWhichHeap(ref); /* Will most often be "(not in beta heap)" */
      }
    }
  }
  fflush(output);
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
    if (!isMakingDump){
      ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, DoNothing);
      isMakingDump=1;
    }
  }
#endif /* NEWRUN */
  
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
  Illegal(); /* Usefull to break in */
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
#endif /* NEWRUN */

      /* Check alignment */
      if (!(isLazyRef(r) || (ObjectAlign((unsigned)r)==(unsigned)r))) {
          fprintf(output, "CCk:!ref:%s:%d: Ck(%s) (%s=0x%x)",
                  fname, lineno, ref, ref, (int)(r));
      }
/* Check it's in a heap */
      if (!(inIOA(rr) || inAOA(rr) || isLazyRef(rr))) {
          fprintf(output, "CCk:!inHeap:%s:%d: Ck(%s) (%s=0x%x)",
                  fname, lineno, ref, ref, (int)(r));
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
static void RegError(long pc1, long pc2, char *reg, Object * value)
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
#endif /* RTDEBUG */
}

/*************************** Label lookup by address ****************************/

typedef struct _label {
  long address;
  char *id;
} label;

GLOBAL(long labelOffset) = 0;
GLOBAL(label **labels) = 0;
GLOBAL(long numLabels) = 0;
GLOBAL(long maxLabels) = 2048;
#ifdef nti
GLOBAL(long process_offset) = 0;
#endif

static void addLabel(long adr, char *id);
static void addLabel(long adr, char *id)
{
  label *lab;
  int len = strlen(id);
  int lastslash = 0;
  int i;
  char* buf;

  for (i = 0; i < len; i++) {
    if (id[i] == '/') {
      lastslash = i+1;
    }
  }  

  buf = MALLOC(sizeof(label)+len+1-lastslash);

  if (!buf) {
    INFO_LABELS(fprintf(output, "Allocation of label failed\n"));
    /* free previously allocated labels */
    FREE(labels);
    labels = 0;
    return;
  }
  INFO_ALLOC(sizeof(label));

  lab = (label *) buf;
  lab->id = buf+sizeof(label);

  strcpy(lab->id, id+lastslash);
  lab->address = adr;

  if (numLabels>=maxLabels){
    maxLabels *= 2;
    INFO_LABELS(fprintf(output, "*"); fflush(output));
    labels=REALLOC(labels, maxLabels * sizeof(label*));
  }
  labels[numLabels] = lab;
  numLabels++;
}

#ifdef sgi
static int cmpLabel(const void *left, const void *right);
static int cmpLabel(const void *left, const void *right)
{
  label **l = (label**)left, **r = (label**)right;

  fprintf(output, "%d ? %d\n", (*l)->address, (*r)->address);
  return ((*l)->address - (*r)->address);
}

static void addLabelsFromGroupTable(void);
static void addLabelsFromGroupTable(void)
{
  group_header *gh;
  label *lab;
  char theLabel[256];
  long mPart;
  long gPart;

  gh = NextGroup(0);
  while (gh) {
    long* proto = &(gh->protoTable[1]);
    int i, NoOfPrototypes;
    
    NoOfPrototypes = gh->protoTable[0];
    TRACE_GROUP(fprintf(output, 
			">>>addLabelsFromGroupTable(group=0x%x, addr=0x%x)\n",
			(int)gh,
			(int)data_addr));
    for (i=0; i<NoOfPrototypes; i++) {
      TRACE_GROUP(fprintf(output,">>>addLabelsFromGroupTable: Try 0x%x\n", (int)*proto));
      sprintf(theLabel, "%s:T%d", NameOfGroupMacro(gh), i+1);
      addLabel((long)(*proto), theLabel);

      gPart=  G_Part(((ProtoType*)(*proto)));
      sprintf(theLabel, "%s:G%d", NameOfGroupMacro(gh), i+1);
      addLabel(gPart, theLabel);
      
      mPart =  M_Part(((ProtoType*)(*proto)));
      if (mPart != MAXINT) {
	sprintf(theLabel, "%s:M%d", NameOfGroupMacro(gh), i+1);
	addLabel(mPart, theLabel);
      }

      proto++;
    }
    gh = NextGroup(gh);
  }

  fprintf(output, "qsort(labels)...");
  qsort(labels, numLabels, sizeof(label**), cmpLabel);
  fprintf(output, "done\n");
}
#endif


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
  return;
#endif /* ppcmac */

#ifdef UNIX
#ifndef hppa
  /* dl_self = dlopen(NULL, (RTLD_NOW | RTLD_GLOBAL) ); */
#endif /* hppa */
#endif /* UNIX */

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
  labels=(label**)MALLOC(maxLabels * sizeof(label*));
  if (!labels) {
    INFO_LABELS(fprintf(output, "Failed to allocate memory for labels\n"));
    labels = 0; 
  }
  INFO_ALLOC(maxLabels * sizeof(label *));
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

#ifdef sgi
  addLabelsFromGroupTable();
#endif  

  INFO_LABELS(fprintf(output, " done]"); fflush(output));
#ifdef sgi
  fprintf(output, 
	  "[*** NOTICE: initLabels: if linked shared, "
	  "most symbols will be missing!] ");
#endif

  DEBUG_LABELS({
    fprintf(output, "Labels:\n");
    { 
      long n;
      for (n=0; n<lastLab; n++){
	fprintf(output, "0x%x\t%s\n", (unsigned)labels[n]->address, labels[n]->id);
      }
    }
    fflush(output);
  });
}

char *getLabel (long addr)
{
  long n;

#ifdef ppcmac
  labelOffset=0;
  return "<unknown>";
#endif /* ppcmac */

  if (!labels) initLabels();

  if (!addr){
    labelOffset=0;
    return "<unknown>";
  }

#ifdef UNIX
#ifndef hppa
  /* FIXME: could use dladdr here - but not on sgi (:-( */
#endif /* hppa */
#endif /* UNIX */

#ifdef nti
  addr -= process_offset;
#endif
  if (labels) {
    for (n=numLabels-1; n>=0; n--) {
      if (labels[n]->address <= addr){
	labelOffset = addr-(labels[n]->address);
	return labels[n]->id;
      }
    }
  }
#if defined(sparc) || defined(linux)
  /* Fall back on dladdr (for dynamic symbols not found by nm) */
  {
    static Dl_info info;
    if (dladdr((void*)addr, &info)){
      labelOffset = (long)addr - (long)info.dli_saddr;
      return((char*)info.dli_sname);
    }
  }
#endif /* sparc */
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
