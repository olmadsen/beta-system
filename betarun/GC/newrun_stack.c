/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * stack.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 *
 * Traverse an stack parts and process all references.
 */

#include "beta.h"

#ifndef MT

extern void (*StackRefAction)(REFERENCEACTIONARGSTYPE);

long WindBackSP(long SP, Object *obj, pc_t PC)
{

#if defined(ppcmac)  ||  defined(macosx)
  SP = *(long*)SP; /* Use FramePointer */
#else
  long SPoff /* size allocated on stack when theObj became active */;
  
  
  GetSPoff(SPoff, CodeEntry(GETPROTO(obj), PC)); 
  DEBUG_STACK({
    fprintf(output, "WindBackSP:\n");
    fprintf(output, "Old SP:      0x%x\n", SP);
    fprintf(output, "CodeEntry:   0x%x\n", CodeEntry(GETPROTO(obj), PC));
    fprintf(output, "SPoff:       0x%x\n", SPoff);
    fprintf(output, "New SP:      0x%x\n", SP+SPoff);
  });
  SP = (long)SP+SPoff;
#endif /* ppcmac */
  return SP;
}

#ifdef RTDEBUG
#if 0
static void DumpProto(Object *theObj)
{                                                                
  if ((theObj)&&((theObj)!=CALLBACKMARK)&&((theObj)!=GENMARK)){  
     if (isObject(theObj)){                                      
       PrintProto(GETPROTO(theObj));   
       fprintf(output, "\n");
     } else {                                                    
       fprintf(output, " (ILLEGAL OBJECT!)");                    
     }                                                           
  }                                                              
}
#endif

void PrintStackFrame(long *PrevSP, long *SP)
{
  long *StackCell;
  int in_refs=0;

  DEBUG_STACK(fprintf(output, 
		      "PrintStackFrame(PrevSP=0x%x, SP=0x%x)\n",
		      (int)PrevSP,
		      (int)SP));
  Claim(PrevSP>=SP, "PrevSP=>SP");
#if defined(ppcmac) || defined(macosx)
  /* Print LR and CR too */
  fprintf(output, "   +8:  0x%08x: 0x%08x", (int)PrevSP+2, (int)*(PrevSP+2));
  fprintf(output, "(LR/RTS)");
  PrintCodeAddress((pc_t)*StackCell);
  fprintf(output, "\n");
  fprintf(output, "   +4:  0x%08x: 0x%08x", (int)PrevSP+1, (int)*(PrevSP+2));
  fprintf(output, "(CR)");
  fprintf(output, "\n");
#endif /* ppcmac */
  fprintf(output, "PrevSP->0x%08x: 0x%08x\n", (int)PrevSP, (int)*PrevSP);
  fprintf(output, "        ----------------------\n");  
  for (StackCell=PrevSP-1; StackCell>=SP; StackCell--){
    if (StackCell==SP){
      fprintf(output, "    SP->");
    } else {
      fprintf(output, "        ");      
    }
    fprintf(output, "0x%08x: 0x%08x ", (int)StackCell, (int)*StackCell);
#ifdef sgi
    if (StackCell==PrevSP+PC_OFF){
      fprintf(output, "(RTS)");
      PrintCodeAddress((pc_t)*StackCell);
    }
#endif /* sgi */
    if (StackCell==PrevSP-DYN_OFF){
      fprintf(output, "(DYN)");
      in_refs=1;
    }
    if (in_refs){
      if (*StackCell){
	PrintRef((Object*)*StackCell);
      } else {
	fprintf(output, "(RefStack termination)");
	in_refs = 0;
      }
    }
    fprintf(output, "\n");
    if (StackCell==SP){
      fprintf(output, "        ----------------------\n");  
    }
    fflush(output);
  }
}

#define FrameSeparator() \
fprintf(output, "============================================================================\n")

#else /* !RTDEBUG */
#define DumpProto(theObj) 
#endif /* RTDEBUG */

/* ProcessRefStack:
 *  Process references in a stack frame.
 */
static 
void ProcessRefStack(Object **topOfStack, long dynOnly, CellProcessFunc func)
{
  Object **theCell=topOfStack;
  Object *theObj= *theCell;

  if (dynOnly) {
    DEBUG_STACK(fprintf(output, 
			"RefStack(dyn): 0x%08x: ", 
			(int)theCell));
    DEBUG_STACK(PrintObject(theObj); fprintf(output, "\n"));
    func(theCell, theObj);
    return;
  }

  while(theObj) {
    DEBUG_STACK(fprintf(output, 
			"RefStack(%d): 0x%08x: ", 
			(int)(((long)topOfStack - (long)theCell)/4),
			(int)theCell));
    DEBUG_STACK(PrintObject(theObj); fprintf(output, "\n"));
    func(theCell, theObj);
    /* Take next reference from stack */
    theCell--;
    theObj = *theCell;
  } 
}

#ifdef RTDEBUG

#if 1
#define TRACE_NEW_FRAME()
#else
static void TRACE_NEW_FRAME(void)
{
  if (DebugStack){
    fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__); 
    fprintf(output, "Own SP:        0x%x\n", (int)SP);              
    fprintf(output, "Caller PC:     0x%x " , (int)PC);              
    if (PC==(pc_t)-1){                                               
      fprintf(output, "<UNKNOWN_MARK>\n");                    
    } else {                                                   
      PrintCodeAddress(PC);                                    
      fprintf(output, "\n");
    }                                                          
    fprintf(output, "Caller object: 0x%x", theObj);            
    DEBUG_STACK(PrintRef(theObj); fprintf(output, "\n"));
  }
}
#endif

#else /* !RTDEBUG */
#define TRACE_NEW_FRAME()
#endif /* RTDEBUG */


#ifdef RTDEBUG
static void TRACE_STACK(long SP, pc_t PC, Object *theObj, int line) 
{
  if (DebugStack){
    fprintf(output, "File %s; Line %d\n", __FILE__, line); 
    fprintf(output, "---------------------\n");            
    fprintf(output, "SP:        0x%08x\n", (int)SP);                
    fprintf(output, "PC:        0x%08x ",  (int)PC);                
    if (PC==(pc_t)-1){                                               
      fprintf(output, "<UNKNOWN_MARK>\n");                    
    } else {                                                   
      PrintCodeAddress(PC);                                    
      fprintf(output, "\n");
    }                                                          
    fprintf(output, "object:    0x%08x", (int)theObj);              
    DEBUG_STACK(PrintRef(theObj); fprintf(output, "\n"));
    fprintf(output, "---------------------\n");            
  }
}
#else /* !RTDEBUG */
#define TRACE_STACK(SP,PC,theObj,line) 
#endif /* RTDEBUG */

#ifdef RTDEBUG
static void DoNothing(Object **theCell,Object *theObj)
{
  return;
}
void PrintRefStack(void)
{
  ProcessRefStack(RefSP-1, FALSE, DoNothing); /* RefSP points to first free */
}
#endif /* RTDEBUG */

#if defined(ppcmac) || defined(macosx)
GLOBAL(static long StackObjEnd); /* extra "parameter" for ProcessStackFrames */
#endif

/* ProcessStackFrames:
 *  The main stack traversal routine.
 *  Scans through frames in stack part.
 */
void ProcessStackFrames(long SP, 
			long StackStart, 
			long isStackObject,
			long dynOnly,
			CellProcessFunc func
			)
{
  /* Arguments:
   *  - SP points to address just ABOVE last BETA stack frame,
   *    i.e. to the top of the next-to-last frame.
   *  - StackStart point just above the bottom frame to process.
   * 
   *  STACK LAYOUT at entry:
   * 
   *            |            |   
   *StackStart->|____________|   
   *            |            |   
   *            |            |   
   *            | frames     |   
   *            | to process |   
   *            |            |   
   *            |            |   
   *            |            |   
   *            |            |   
   *        SP->|____________|     = stack top in next-to-last frame
   *            |   RTS      |     = current PC for next-to-last frame
   *            |   dyn      |     = current object for next-to-last frame
   *            |            |     
   *            | also       |  
   *            | processed  |    
   *            |____________|   
   *            |  AlloXXX   |
   *            |   IOAGC    |
   */
  Object *theObj;
  long *CSP = CompSP;
  pc_t PC;
#if defined(ppcmac) || defined(macosx)
  long SPz = StackObjEnd; /* Used for stackobjects */
#endif
#ifdef RTDEBUG
  Object *current;
  long currentSP;
  pc_t currentPC;
  pc_t unknown = (pc_t)-1;
  long unknown_sp = -1;
#endif
  
  DEBUG_STACK(fprintf(output, "ProcessStackFrames(SP=0x%x, StackStart=0x%x)\n",
		      (int)SP, (int)StackStart));
  Claim(SP<=(long)StackStart, "SP<=StackStart");

  /* Process the top frame */
  DEBUG_STACK(FrameSeparator());
  DEBUG_STACK(fprintf(output, "Processing top frame:\n"));
  TRACE_STACK(SP,unknown,GetThis((long *)SP),__LINE__);
  ProcessRefStack((Object **)SP-DYN_OFF, dynOnly, func);
  PC = GetPC(SP);
  theObj = *((Object **)SP-DYN_OFF);

  if (SP==StackStart){
    /* Only top frame to process - can happen for stack objects */
    return;
  }
  TRACE_NEW_FRAME();

  do {
    /* Handle special cases */

    /* Check for passing of a callback/Gpart.
     * When a callback/gpart is called, the callbackentry is called
     * with dyn=CALLBACKMARK/GENMARK.
     *  
     * Before this the compiler pushes the SP pointing to the *end* of 
     * the frame for this previous object 
     * (saved in BetaStackTop[0] when C was called).
     * 
     * BetaStackTop[1] was intended to save the current *object* before the 
     * C call, but this is currently commected out in compiler (ExternalMark).
     * This is probably because we can actually figure out the object ourselves.
     * See CALLBACKMARK stuff in function DumpCell in outpattern.c and in
     * function DoStackCell in stack.c.
     * So BetaStackTop[1] is currently unused.
     *
     * STACK LAYOUT at callback/gpart:
     * 
     *          |____________|<-.              _
     *          |            |  |               |
     *          |            |  |               |  Frame for BETA
     *          |            |  |               |  before entering C
     *          |____________|  |              _|
     *          |////////////|  |               |
     *          |////////////|  |               |  Frames for C and
     *          |////////////|  |               |  callback stub or AlloXXX
     *          |------------|  |              -'
     *      SP->|___SP-beta__|--'              _  Pseudo frame / CallB frame
     *          |   RTS      | = PC in stub     |
     *          |   dyn      | = CALLBACKMARK   |
     *          |            |   or GENMARK     |
     *          |            |                  |  Frame for first beta frame 
     *          |            |                  |  after callback 
     *          |            |                  |  or for first Gpart
     *          |____________|                 _|
     *          |            |
     *          |            |
     * 
     */
#if 0
    DEBUG_STACK(fprintf(output, "Testing for callback/allocation\n"));
#endif
    if ((theObj == CALLBACKMARK)||(theObj == GENMARK)) {
#ifdef RTDEBUG
      int isGen;
#endif
      DEBUG_CODE(long oldSP);
      DEBUG_STACK(if (theObj==CALLBACKMARK){
	isGen=0;
	fprintf(output, "Passing callback at SP=0x%x.", (int)SP);
      } else {
	isGen=1;
	fprintf(output, "Passing allocation/main at SP=0x%x.", (int)SP);
      })
      DEBUG_CODE(oldSP=SP);
      SP = GetSPbeta(SP);
      if (SP==0){
	DEBUG_STACK(fprintf(output, " stopping at main.\n"));
	/*SP=StackStart;*/
	break;
      }
      Claim(oldSP<SP, "SP greater before callback/allocation");
      DEBUG_STACK(fprintf(output, " Skipping to prevSP=0x%x\n", (int)SP));
      /* Treat this frame as a top frame */
      Claim(SP<=(long)StackStart, "SP<=StackStart");
      DEBUG_STACK(FrameSeparator());
      DEBUG_STACK(fprintf(output, 
			  "Processing top frame before %s (prevSP=0x%x):\n",
			  (isGen) ? "allocation" : "callback",
			  (int)SP));
      TRACE_STACK(unknown_sp,unknown,GetThis((long*)SP),__LINE__);
      ProcessRefStack((Object **)SP-DYN_OFF, dynOnly, func);
      PC = GetPC(SP);
      theObj = *((Object **)SP-DYN_OFF); 
      TRACE_NEW_FRAME();
      if (SP<StackStart) {
	continue; /* Restart do-loop */
      } else {
	break; /* Leave do-loop */
      }
    }

    /* Check for passing of a DoPart object */
#if 0
    DEBUG_STACK(fprintf(output, "Testing for Dopart Object\n"));
#endif
    if ((long)GETPROTO(theObj) == (long)DopartObjectPTValue) {
      DEBUG_STACK(fprintf(output, "Passing dopart object 0x%x\n", (int)theObj));
      theObj = ((DopartObject *)theObj)->Origin;
      continue;
    }

#if 0
    DEBUG_STACK(fprintf(output, "Testing for Component\n"));
#endif
    /* Check for passing of a component.
     * 
     * STACK LAYOUT for component:                          ____________      
     * 							,->| Proto = -1 |     
     *                                                 |   | GCAttr     |     
     *          |            |			       |   | StackObj   |     
     *          |            |                         |   | CallerObj  |     
     *          |            |      ____________       |   | CallerComp |     
     *          |            |     |            |<--.  |   | CallerLSC  |=PC(X)
     *          |            |     |  X item    |   |  |   |------------|     
     *          |            |     |            |   |  |   | ......     |    
     *          |            |     |____________|   |  |        
     *          | Frame for  |                      |  |   CompStack:     
     *          |  item X    |                      |  |    ____________
     *     SPx->|____________|<---------------------|--|---|            |CompSP
     *          |            |    ,-----------------|--|---|____________|
     *          | Att frame  |   /                  |  |   |            |
     *     SPy->|____________|<-'                   |  |   |            |
     *          |   RTS      |        ____________  |  |   
     *          |   dyn      |------>| Proto = -1 | |  |   
     *          |            |       | GCAttr     | |  |    
     *          |  Frame for |       | StackObj   | |  |
     *          |   item Y   |       | CallerObj  |-'  |
     *          |            |       | CallerComp |---'
     *          |____________|       | CallerLSC  | 
     *      SP->|            |       | SPx        |
     *          |            |       | SPy        |
     *                               | level      |
     *                               | dummy      |
     *                               |------------|
     *                               |  Y item    |
     * 
     */

    if ((long)GETPROTO(theObj) == (long)ComponentPTValue) {
      Component *comp = (Component *)theObj;
#if defined(ppcmac) || defined(macosx)
#else
      Component *callerComp = comp->CallerComp;
#endif

      if (isStackObject){
	/* Processing stackobject:
	 * Stop processing when the component is reached
	 */
	DEBUG_STACK(fprintf(output, "Stopping at component 0x%x\n", (int)comp));
	break;
      } else {
	DEBUG_STACK(fprintf(output, "Passing component 0x%x\n", (int)comp));
      }
      /* SP     = (long)callerComp->SPx; */
      SP     = *--CSP; CSP--; /* count down one before reading and one after */
#if defined(ppcmac) || defined(macosx)
      PC = (pc_t)-1; /* Check everywhere */
#else
      PC     = callerComp->CallerLSC;
#endif
      theObj = comp->CallerObj;
      TRACE_NEW_FRAME();
      if (SP<StackStart) {
	continue; /* Restart do-loop */
      } else {
	break; /* Leave do-loop */
      }
    }

    /* INVARIANT: 
     *    SP points to *end* of a *BETA* frame to process
     *    theObj is current object corresponding to this frame;
     *    PC is address in the code for theObj.
     */

    /* remember object etc for current frame in order to display the right one */
    DEBUG_CODE(current = theObj); 
    DEBUG_CODE(currentPC = PC); 
    DEBUG_CODE(currentSP = SP); 

#if 0
    DEBUG_STACK(fprintf(output, "Normal frame\n"));
#endif
    /* Normal case: Find stack frame size, normal dyn and new PC */
    {  
      /* STACK LAYOUT for normal stack frame:
       * 
       *  prevSP->|____________|    _     = stack top in previous frame
       *          |   RTS      |     |    = current PC for previous frame
       *          |   dyn      |     |    = current object for previous frame
       *          |            |     |
       *          |            |   SPoff  = given by current object and PC
       *          |            |     |
       *          |            |     |
       *          |____________|    _|
       *      SP->|            |
       *          |            |
       */
      
      Claim(!isSpecialProtoType(GETPROTO(theObj)), 
		       "!isSpecialProtoType(GETPROTO(theObj))");
      
#if defined(ppcmac) || defined(macosx)
      SP = *(long*)SP; /* Use FramePointer */
      if (isStackObject){
      	SP += SPz; 
      }
#else
      {
     
	long SPoff /* size allocated on stack when theObj became active */;
#if 0
	DEBUG_STACK(fprintf(output, "Finding previous frame\n"));
#endif
	GetSPoff(SPoff, CodeEntry(GETPROTO(theObj), PC)); 
#if 0
	DEBUG_STACK(fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__));
	DEBUG_STACK(fprintf(output, "New SP:      0x%x\n", SP));
	DEBUG_STACK(fprintf(output, "CodeEntry:   0x%x\n", CodeEntry(GETPROTO(theObj), PC)));
	DEBUG_STACK(fprintf(output, "SPoff:       0x%x\n", SPoff));
#endif
	SP = (long)SP+SPoff;
      }
#endif
      /* SP now points to end of *previous* frame, i.e. bottom of top frame */
      /* normal dyn from the start of this frame gives current object */
      theObj = *((Object **)SP-DYN_OFF); 
      /* RTS from the start of this frame gives PC */
      PC = GetPC(SP);
      TRACE_NEW_FRAME();
    }

    /* INVARIANT:
     *    "SP" points to end of *previous* frame,
     *    "theObj" is the current item for the *previous* frame
     *    "PC" is address in the code for theObj
     *    "this" is the current object in *current* frame (if RT_DEBUG)
     */

    Claim(SP<=(long)StackStart, "SP<=StackStart");
    DEBUG_STACK(FrameSeparator());
    DEBUG_STACK(fprintf(output, "Processing normal frame:\n"));
    TRACE_STACK(currentSP,currentPC,current,__LINE__);
    ProcessRefStack((Object **)SP-DYN_OFF, dynOnly, func);

  } while (SP<StackStart);
#if 0
  /* The following claim does not hold anymore because of the 
   * CallB frame after main and Att.
   */
  Claim(SP==(long)StackStart, "SP==StackStart");
#endif

  DEBUG_STACK(FrameSeparator());

} /* ProcessStackFrames */

/* ProcessNEWRUNStack */

void
GeneralProcessStack(CellProcessFunc func)
{
  /* There are two set of GC roots:
   * 1. The ReferenceStack contains roots
   *    saved during an active AlloI etc. via the Protect macro.
   * 2. The runtimestack contains frames, which contains refence
   *    sections.
   */

  DEBUG_STACK(fprintf(output, "\n"));
  DEBUG_STACK(FrameSeparator());
  DEBUG_STACK(fprintf(output, "Processing internal ReferenceStack used by RTS.\n"));
  ProcessRefStack(RefSP-1, FALSE, func); /* RefSP points to first free */
  DEBUG_STACK(FrameSeparator());
  DEBUG_STACK(fprintf(output, "Processing MachineStack.\n"));
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, func);
}

/* ProcessNEWRUNStackObj */

void
ProcessStackObj(StackObject *sObj, CellProcessFunc func)
{
  DEBUG_CODE(long oldDebugStack=DebugStack);

  DEBUG_STACKOBJ({
    fprintf(output,
	    " *-*-* StackObject: 0x%x, size: 0x%x %s *-*-*\n", 
	    (int)sObj, 
	    (int)(sObj->StackSize),
	    WhichHeap((Object*)sObj));
    fprintf(output, "func is 0x%x", (int)func);
    PrintCodeAddress((pc_t)func);
    fprintf(output, "\n");
    fprintf(output, "StackRefAction is 0x%x", (int)StackRefAction);
    PrintCodeAddress((pc_t)StackRefAction);
    fprintf(output, "\n");
  });
  DEBUG_CODE(if (DebugStackObj){
    DebugStack=TRUE;
  } else {
    DebugStack=FALSE;
  });
  
#if defined(ppcmac) || defined(macosx)
  StackObjEnd = (long)sObj->Body;
#endif
  ProcessStackFrames((long)sObj->Body+(long)sObj->StackSize, /* top frame off */
		     (long)sObj->Body+(long)sObj->BodySize, /* bottom */
		     TRUE, /* Stop at component */
		     FALSE, /* Do not only process dyn cells */
		     func
		     ); 
  DEBUG_STACKOBJ(fprintf(output, " *-*-* End StackObject 0x%x *-*-*\n", (int)sObj));
  DEBUG_CODE(DebugStack=oldDebugStack);
}



/************ beta.dump/valhalla/exception stuff below ***************/


static void DumpCell(Object **theCell, Object *theObj)
{ 
  register pc_t pc = (pc_t)-1;
  long *SP;

  /* theObj is dyn in a frame. This is the current object in the 
   * previous frame. 
   */

  TRACE_DUMP({
    fprintf(output, 
	    ">>>TraceDump: theCell=0x%x, theObj=0x%x",
	    (int)theCell, 
	    (int)theObj);
  });

  /* First check if theObj is CALLBACKMARK */
  if ((theObj==CALLBACKMARK)||(theObj==GENMARK)){
    SP = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
    pc = *((pc_t*)SP+PC_OFF);
    if (theObj==CALLBACKMARK){
      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf(output, 
	      "  [ EXTERNAL ACTIVATION PART (address 0x%x", 
	      (int)pc);
      if (!SimpleDump) PrintCodeAddress(pc);
      fprintf(output, ") ]\n");
    } else {
      TRACE_DUMP(fprintf(output, "  allo: "));
    }
    /* Since ProcessStackFrames now skips to previous frame before
     * BETA called C, we will not see the current object in the
     * frame before C as a dyn-pointer in any frame (it is hidden
     * by this CALLBACKMARK).
     * So we have to go to this previous frame ourselves and
     * find the current object for that frame and dump it.
     * See figure in stack.c.
     */
    SP = (long*)GetSPbeta(SP);	 /* SP-beta */
    if (SP==0){
      /* We passed the main+CallB frames */
      return;
    }
    theObj = GetThis(SP);
    pc = 0;			 /* not known - is somewhere in the C frames */
  }
    
  /* Check if theObj IS a component */
  if (theObj && (GETPROTO(theObj)==ComponentPTValue)){
    TRACE_DUMP(fprintf(output, " is comp - getting real dyn"));
    /* Passing a component frame. The real dyn is found 
     * as theComp->CallerObj - see stack.c for details.
     */
    pc = ((Component *)theObj)->CallerComp->CallerLSC;
    theObj = ((Component *)theObj)->CallerObj;
  } 
    
  /* Check if theObj is inlined in a component */
  if (!isComponent(theObj) && IsComponentItem(theObj)) {
    TRACE_DUMP(fprintf(output, " dump as comp"));
    theObj = (Object *)EnclosingComponent(theObj);
  } 
    
  if (pc == (pc_t)-1){
    SP = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
    pc = *((pc_t *)SP+PC_OFF);
  }

  TRACE_DUMP(fprintf(output, ", PC=0x%x *\n", (int)pc));
  DisplayObject(output, theObj, pc);
}

void DisplayNEWRUNStack(pc_t pc, Object *theObj, int signal)
{ 

  /* First check for errors occured outside BETA */
  if (!IsBetaCodeAddrOfProcess(pc)){
#ifdef sgi
    long *betatop = BetaStackTop[0];
#endif
    fprintf(output, 
	    "  [ EXTERNAL ACTIVATION PART (address 0x%x", 
	    (int)pc);
    if (!SimpleDump) PrintCodeAddress(error_pc);
    fprintf(output, ") ]\n");
    
    /* 
     * Adjust StackEnd to BETA part of stack, if possible.
     */
#if defined(ppcmac) || defined(macosx)
    /* FIXME: could wind down through frame pointers */
#endif /* ppcmac */
#ifdef sgi
    if ((StackEnd<betatop) && (betatop<StackStart)){
      /* BetaStackTop is in the active stack. Try continuing from there.
       * This will work if BETA called a C routine, but not if the error
       * occurred in a runtime routine - BetaStackTop is not set, when
       * runtime routines are called.
       */
      TRACE_DUMP(fprintf(output, "  Adjusting StackEnd to BetaStackTop\n"));
      StackEnd = betatop;
      /* Unfortunately the BetaStackTop points to the next-to-top-entry on 
       * the stack (for other reasons). The topmost BETA object can be found
       * as the saved THIS in the frame just above SP but we cannot figure
       * out the PC, at this is saved somewhere in the C frames.
       */
      DisplayObject(output, GetThis(StackEnd), 0);
    } else {
       /* In low level dump StackEnd will be equal to betatop since the
	* above code has just been performed for the simple dump.
	*/ 
      if (StackEnd==betatop){
	/* Low level dump - dump topmost object here too */
	DisplayObject(output, GetThis(StackEnd), 0);
      } else {
	fprintf(output, "\n");
	fprintf(output, "  (Unable to find start of BETA stack - sorry)\n");
	BetaExit(1);
      }
    }
#endif /* sgi */
  }

  /* Dump the stack */
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, TRUE, DumpCell);
}

/* Trace scanComponentStack() */
#define TRACE_SCAN(code) TRACE_DUMP(code)

GLOBAL(static int CompFound);
GLOBAL(static int CompDone);
GLOBAL(static Component *TheComponent);
GLOBAL(static CellDisplayFunc DoForEach);
GLOBAL(static int BasicItemShown);

static void ShowCell(pc_t pc, Object *theObj)
{
  if (theObj==(Object *)BasicItem){
    if (!BasicItemShown){
      TRACE_SCAN(fprintf(output, ", PC=0x%x *\n", (int)pc));
      DoForEach(pc, theObj);
      BasicItemShown=TRUE;
    }
  } else {
    TRACE_SCAN(fprintf(output, ", PC=0x%x *\n", (int)pc));
    if (!strongIsObject(theObj)) {
      TRACE_SCAN(fprintf(output, "(strongIsObject failed!?)\n"));
      return;
    }
    DoForEach(pc, theObj);
  }
}

static void HandleStackCell(Object **theCell,Object *theObj)
{ 
  /* FIXME: This function does pretty much the same as function DumpCell
   * in outpattern.c. An abstraction could be useful (i.e. having
   * DumpCell take a CellDisplayFunc pointer as argument).
   */
  register pc_t pc;
  long *sp;

  TRACE_SCAN(fprintf(output, 
		     ">>>HandleStackCell: theCell=0x%x, theObj=0x%x",
		     (int)theCell, (int)theObj);
	     fflush(output);
	     if (strongIsObject(theObj)){
	       PrintRef(theObj);
	       fprintf(output, ", proto=0x%x", (int)GETPROTO(theObj));
	       fflush(output);
	     });

  if (CompDone) {
    TRACE_SCAN(fprintf(output, " comp is done - ignored\n"));
    return;
  }
  
  /* theObj is dyn in a frame. This is the current object in the 
   * previous frame. 
   */
  if (CompFound){
    /* We are processing the relevant part of the stack */
    
    /* First check if theObj is CALLBACKMARK/GENMARK */
    if ((theObj==CALLBACKMARK)||(theObj==GENMARK)){
      TRACE_SCAN(fprintf(output, "  cb/allo: "));
      /* Since ProcessStackFrames now skips to previous frame before
       * BETA called C, we will not see the current object in the
       * frame before C as a dyn-pointer in any frame (it is hidden
       * by this CALLBACKMARK).
       * So we have to go to this previous frame ourselves and
       * find the current object for that frame and dump it.
       * See figure in stack.c.
       */
      sp = (long *)theCell+DYN_OFF; /* Frame starts DYN_OFF longs above dyn */
      sp = (long*)GetSPbeta(sp);   /* SP-beta */
      if (sp==0){
      /* We passed the main+CallB frames */
      return;
      }
      theObj = GetThis(sp);
      pc = 0;  /* not known - is somewhere in the C frames */
    } else {
      sp = (long *)theCell+DYN_OFF; /* Frame starts DYN_O longs above dyn */
      pc = *((pc_t *)sp+PC_OFF);
    }
    
    /* Check if theObj IS a component */
    if (theObj && (GETPROTO(theObj)==ComponentPTValue)){
      TRACE_SCAN(fprintf(output, " found a component 0x%08x\n", (int)theObj));

      CompDone=TRUE;

      
      return;
    } 
    ShowCell(pc, theObj);
  } else {
    /* Not yet found */
    if (theObj==(Object *)TheComponent){
      /* Found: The real dyn is found as theComp->CallerObj 
       * - see stack.c for details.
       * In this case, the component was not met as a caller
       * component of some other component (see if-clause below).
       * Can happen, e.g., if TheComponent==ActiveComponent.
       */	
      TRACE_SCAN(fprintf(output, " comp found\n"));
      CompFound=TRUE;
      pc = ((Component *)theObj)->CallerComp->CallerLSC;
      theObj = ((Component *)theObj)->CallerObj;
      ShowCell(pc, theObj);
      return;
    } 
    if (theObj && (GETPROTO(theObj)==ComponentPTValue)){
      TRACE_SCAN(fprintf(output, 
			 " Test if it is TheComponent 0x%08x\n", 
			 (int)TheComponent));
      if (((Component*)theObj)->CallerComp == TheComponent){
	/* We found a component on stack, which was attached from TheComponent.
	 * To enable ShowCell for all objects on the stack of TheComponent,
	 * we must NOW set CompFound=TRUE.
	 */
	TRACE_SCAN(fprintf(output, " CallerComp is comp to scan\n"));
	CompFound = TRUE;
	pc = ((Component *)theObj)->CallerComp->CallerLSC;
	theObj = ((Component *)theObj)->CallerObj;
	ShowCell(pc, theObj);
	return;
      } 
    }
    TRACE_SCAN(fprintf(output, " comp not yet found\n"));
  }
}

int scanComponentStack (Component* comp,
			Object *curObj,
			pc_t pc,
			CellDisplayFunc forEach)
{ /* scan through the stackpart corresponding to the comp parameter.
   * pc is the top code-address.
   * calling "forEach" for each (code-address, object) pair on the stack.
   */
  int stacktype=0;

  CompFound=FALSE;
  CompDone=FALSE;
  DoForEach = forEach;
  TheComponent = comp;
  BasicItemShown=0;

  DEBUG_VALHALLA(fprintf(output, 
			 "scanComponentStack(comp=0x%x, obj=0x%x, PC=0x%x)\n",
			 (int)comp, (int)curObj, (int)pc));

  if (comp->StackObj){
    StackObject *sObj = comp->StackObj;
    /* See ProcessStackObj in stack.c */
    CompFound = TRUE;

    /* Process top object in stack object */
    forEach(comp->CallerLSC, /* PC in comp top item */
	    GetThis( (long *)((long)sObj->Body+(long)sObj->StackSize) )
	    );

    ProcessStackFrames((long)sObj->Body+(long)sObj->StackSize, /* top */
		       (long)sObj->Body+(long)sObj->BodySize,  /* bottom */
		       TRUE, 
		       TRUE,
		       HandleStackCell
		       );
    return CS_STACKOBJ;
  }

  if (comp==ActiveComponent) {
    CompFound = TRUE;
    stacktype = CS_ACTIVECOMPONENT;
    forEach(pc, curObj);
  }
  /* FIXME: What about PC outside BETA, compare code in outpattern.c */
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, TRUE, HandleStackCell);
  if (!stacktype){
    if (CompFound){
      stacktype=CS_PROCESSORSTACK;
    } else {
      stacktype=CS_NOSTACK;
    }
  }
  return stacktype;
}

#endif /* MT */
