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

/************************* Valhalla/persist reference stack ****************/
#ifdef RTVALHALLA

/* Various stuff for supporting valhalla evaluators (VOP_EXECUTEOBJECT) */

#ifdef intel

#ifdef RTDEBUG
void PrintValhallaRefStack(void)
{
  Object *theObj;
  Object **theCell = (Object **)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;

  fprintf(output, "\nReferenceStack: [%x .. %x[\n", (int)&ReferenceStack[0], (int)RefSP);
  for(; size > 0; size--, theCell++){
    theObj = *theCell;
    fprintf(output, "  0x%08x: 0x%08x\n", (int)theCell, (int)theObj);
    if (theObj && inBetaHeap(theObj) && isObject(theObj)) {
      /* Normal object */
    } 
#ifdef RTLAZY
    else if (isLazyRef(theObj)) {
      DEBUG_LAZY(fprintf (output, "ProcessRefStack: Lazy ref: %d\n", (int)theObj));
      ProcessReference((Object **)(theCell));
    }
#endif
    else {
      if (theObj 
	  && !isProto(theObj) /* e.g. AlloI is called with prototype in ref. reg. */
	  && !isCode(theObj)  /* e.g. at INNER a ref. reg contains code address */
	  ) {
	fprintf(output, "[ProcessRefStack: ***Illegal: 0x%x: 0x%x]\n", 
		(int)theCell, 
		(int)theObj);
	Illegal();
      }
    }
  }
}
#endif /* RTDEBUG */

void ProcessValhallaRefStack(void)
{
  Object *theObj;
  Object **theCell = (Object **)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;

  DEBUG_IOA(PrintValhallaRefStack());
  for(; size > 0; size--, theCell++) {
    theObj = *theCell;
    if (theObj && inBetaHeap(theObj) && isObject(theObj)) {
      ProcessReference(theCell);
      CompleteScavenging();
    }
#ifdef RTLAZY
    else if (isLazyRef(theObj)) {
      ProcessReference(theCell);
    }
#endif /* RTLAZY */
  }
}

#endif /* intel */

#ifdef sparc
/* ReferenceStack is used to store SP values corresponding to 
 * VOP_EXECUTEOBJECT stack values.
 */
static int isExecuteObjectSP(long *SP)
{
  long *theSP;
  long **theCell = (long **)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;

  /*fprintf(output, "isExecuteObjectSP(0x%x)=", (int)SP);*/
  for(; size > 0; size--, theCell++) {
    theSP = *theCell;
    /*fprintf(output, "[0x%x:0x%x]", (int)theCell, (int)theSP);*/
    if (theSP == SP) {
      /*fprintf(output, "TRUE\n");*/
      return 1;
    }
  }
  /*fprintf(output, "FALSE\n");*/
  return 0;
}

#endif /* sparc */

#endif /* RTVALHALLA */
/************************* End Valhalla reference stack ****************/


/************************* Other common debug stuff ****************/
#if defined(RTDEBUG) && (!defined(UseRefStack))
static void PrintSkipped(long *current)
{
  Object *ref = (Object *)*current;
  DEBUG_STACK(fprintf(output, "0x%08x: 0x%08x ", (int)current, (int)ref));
  if (ref && inBetaHeap(ref) && isObject(ref) && IsPrototypeOfProcess((long)GETPROTO(ref))){ 
    fprintf(output, "*** SUSPICIOUS STACK-SKIP!");
    fflush(output);
    if (!DebugStack) {
      fprintf(output, "0x%08x: 0x%08x ", (int)current, (int)ref);
    }
    fprintf(output, " proto: 0x%08x (%s)\n", (int)GETPROTO(ref), ProtoTypeName(GETPROTO(ref))); 
  } else {
    fprintf(output, "- SKIPPED\n");
  } 
  fflush(output);
}
#endif /* RTDEBUG */
/************************* End common debug stuff *************************/


#ifdef NEWRUN
/************************* Begin NEWRUN ****************************/

long WindBackSP(long SP, Object *obj, long PC)
{
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
  return SP;
}

#ifdef RTDEBUG
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
void PrintStackFrame(long *PrevSP, long *SP)
{
  long *StackCell;
  int in_refs=0;

  DEBUG_STACK(fprintf(output, 
		      "PrintStackFrame(PrevSP=0x%x, SP=0x%x)\n",
		      (int)PrevSP,
		      (int)SP));
  Claim(PrevSP>=SP, "PrevSP=>SP");
#ifdef ppcmac
  /* Print LR and CR too */
  fprintf(output, "   +8:  0x%08x: 0x%08x", (int)PrevSP+2, (int)*(PrevSP+2));
  fprintf(output, "(LR/RTS)");
  PrintCodeAddress((int)*StackCell);
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
      PrintCodeAddress((int)*StackCell);
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
			"RefStack(dyn): 0x%08x: 0x%08x", 
			(int)theCell,
			(int)*theCell));
    DEBUG_STACK(PrintRef(theObj); fprintf(output, "\n"));
    func(theCell, theObj);
    return;
  }

  while(theObj) {
    DEBUG_STACK(fprintf(output, 
			"RefStack(%d): 0x%08x: 0x%08x", 
			((long)topOfStack - (long)theCell)/4,
			(int)theCell,
			(int)*theCell));
    DEBUG_STACK(PrintRef(theObj); fprintf(output, "\n"));
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
    fprintf(output, "Own SP:        0x%x\n", SP);              
    fprintf(output, "Caller PC:     0x%x " , PC);              
    if (PC==-1){                                               
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
static void TRACE_STACK(long SP, long PC, Object *theObj) 
{
  if (DebugStack){
    fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__); 
    fprintf(output, "---------------------\n", SP);            
    fprintf(output, "SP:        0x%08x\n", SP);                
    fprintf(output, "PC:        0x%08x ",  PC);                
    if (PC==-1){                                               
      fprintf(output, "<UNKNOWN_MARK>\n");                    
    } else {                                                   
      PrintCodeAddress(PC);                                    
      fprintf(output, "\n");
    }                                                          
    fprintf(output, "object:    0x%08x", theObj);              
    DEBUG_STACK(PrintRef(theObj); fprintf(output, "\n"));
    fprintf(output, "---------------------\n", SP);            
  }
}
#else /* !RTDEBUG */
#define TRACE_STACK(SP,PC,theObj) 
#endif /* RTDEBUG */

#ifdef ppcmac
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
  long PC;
#ifdef macppc
  long SPz = StackObjEnd; /* Used for stackobjects */
#endif
#ifdef RTDEBUG
  Object *current;
  long currentSP, currentPC;
  int unknown=-1;
#endif
  
  DEBUG_STACK(fprintf(output, "ProcessStackFrames(SP=0x%x, StackStart=0x%x)\n",
		      SP, StackStart));
  Claim(SP<=(long)StackStart, "SP<=StackStart");

  /* Process the top frame */
  DEBUG_STACK(FrameSeparator());
  DEBUG_STACK(fprintf(output, "Processing top frame:\n"));
  TRACE_STACK(SP,unknown,GetThis((long *)SP));
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
     * function DoStackCell in valhallaFindComp.c.
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
	fprintf(output, "Passing callback at SP=0x%x.", SP);
      } else {
	isGen=1;
	fprintf(output, "Passing allocation/main at SP=0x%x.", SP);
      })
      DEBUG_CODE(oldSP=SP);
      SP = GetSPbeta(SP);
      if (SP==0){
	DEBUG_STACK(fprintf(output, " stopping at main.\n"));
	/*SP=StackStart;*/
	break;
      }
      Claim(oldSP<SP, "SP greater before callback/allocation");
      DEBUG_STACK(fprintf(output, " Skipping to prevSP=0x%x\n", SP));
      /* Treat this frame as a top frame */
      Claim(SP<=(long)StackStart, "SP<=StackStart");
      DEBUG_STACK(FrameSeparator());
      DEBUG_STACK(fprintf(output, 
			  "Processing top frame before %s (prevSP=0x%x):\n",
			  (isGen) ? "allocation" : "callback",
			  (int)SP));
      TRACE_STACK(unknown,unknown,GetThis((long*)SP));
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
      DEBUG_STACK(fprintf(output, "Passing dopart object 0x%x\n", theObj));
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
      Component *callerComp = comp->CallerComp;

      if (isStackObject){
	/* Processing stackobject:
	 * Stop processing when the component is reached
	 */
	DEBUG_STACK(fprintf(output, "Stopping at component 0x%x\n", comp));
	break;
      } else {
	DEBUG_STACK(fprintf(output, "Passing component 0x%x\n", comp));
      }
      /* SP     = (long)callerComp->SPx; */
      SP     = *--CSP; CSP--; /* count down one before reading and one after */
#ifdef ppcmac
      PC = (long)-1; /* Check everywhere */
#else
      PC     = (long)callerComp->CallerLSC;
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
      
#ifdef ppcmac
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
    TRACE_STACK(currentSP,currentPC,current);
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

static
void ProcessNEWRUNStack(void)
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
  ProcessRefStack(RefSP-1, FALSE, DoStackCell); /* RefSP points to first free */
  DEBUG_STACK(FrameSeparator());
  DEBUG_STACK(fprintf(output, "Processing MachineStack.\n"));
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, DoStackCell);
}

static
void ProcessNEWRUNStackObj(StackObject *sObj, CellProcessFunc func)
{
  DEBUG_CODE(long oldDebugStack=DebugStack);

  DEBUG_STACKOBJ({
    fprintf(output,
	    " *-*-* StackObject: 0x%x, size: 0x%x %s *-*-*\n", 
	    (int)sObj, 
	    (int)(sObj->StackSize),
	    WhichHeap((Object*)sObj));
    fprintf(output, "func is 0x%x", (int)func);
    PrintCodeAddress((long)func);
    fprintf(output, "\n");
    fprintf(output, "StackRefAction is 0x%x", (int)StackRefAction);
    PrintCodeAddress((long)StackRefAction);
    fprintf(output, "\n");
  });
  DEBUG_CODE(if (DebugStackObj){
    DebugStack=TRUE;
  } else {
    DebugStack=FALSE;
  });
  
#ifdef ppcmac
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

#endif /* NEWRUN */
/*************************** End NEWRUN ***************************/

#ifdef hppa
/***************************** Begin HPPA ****************************/

#ifdef RTDEBUG
void PrintRefStack(void)
{
  long *theCell = (long *)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;
  fprintf(output, "RefStk: [%x .. %x[\n", (int)&ReferenceStack[0], (int)RefSP);
  for(; size > 0; size--, theCell++){
    if (!isLazyRef(*theCell) && ((*theCell)!=ExternalMarker) && (*theCell & 1)){ 
      /* Used in beta.dump */
      fprintf(output, "  0x%08x: 0x%08x #\n", (int)theCell, (int)(*theCell));
    } else {
      fprintf(output, "  0x%08x: 0x%08x\n", (int)theCell, (int)(*theCell));
    }
  }
}
#endif

void ProcessRefStack(unsigned size, Object **bottom, CellProcessFunc func)
{
  long i;
  Object **theCell;

  DEBUG_IOA(PrintRefStack());
  theCell = bottom;
  for(; size > 0; size--, theCell++) {
    if (!isLazyRef(*theCell)) {
      i = ((unsigned)*theCell & 1);
      *theCell = (Object *)((unsigned)*theCell & ~1);
    } else {
      i = 0;
    }
#ifdef RTVALHALLA
    /* If i=1 then the cell is tagged, and the previous cell that was
     * processed was actually a return address. This can newer be confused with
     * a BETA object, so it does not matter except for speed.
     */
#endif
    DEBUG_IOA(fprintf(output, "ProcessRefStack: 0x%08x: 0x%08x\n", 
		      (int)theCell, (int)(*theCell)));
    func(theCell, *theCell);
    DEBUG_LAZY({
      if (isLazyRef(*theCell)) {
	fprintf(output, "ProcessRefStack: Lazy ref: %d\n",
		(int)*theCell);
      }
    });
    DEBUG_CODE({
      if (*theCell
	  && !inBetaHeap(*theCell) && !isObject(*theCell)
	  && !isProto(*theCell) /* e.g. AlloI is called with prototype in ref. reg. */
	  && !isCode(*theCell)  /* e.g. at INNER a ref. reg contains code address */
	  && (*theCell!=(Object *)ExternalMarker)
	  ) {
	fprintf(output, "[ProcessRefStack: ***Illegal: 0x%x: 0x%x]\n", 
	      (int)theCell, 
	      (int)*theCell);
      Illegal();
    }
    });
    *theCell = (Object *)((unsigned)*theCell | i);
  }
}

static 
void ProcessHPPAStack(void)
{
  ProcessRefStack(((unsigned)RefSP-(unsigned)&ReferenceStack[0]) >> 2,
                  (Object **)ReferenceStack, 
		  DoStackCell);
}

/*
 * A stackobject on the snake looks like this:
 * Header
 * Body (the runtime stack-section)
 * RefStackLength
 * RefStack section
 */
static
void ProcessHPPAStackObj(StackObject *sObj, CellProcessFunc func)
{
  long *        theEnd;
  DEBUG_CODE(long oldDebugStack=DebugStack);

  DEBUG_STACKOBJ({
      fprintf(output,
	      " *-*-* StackObject: 0x%x, size: 0x%x %s *-*-*\n", 
	      (int)sObj, 
	      (int)(sObj->StackSize),
	      WhichHeap((Object*)sObj));
      fprintf(output, "func is 0x%x", (int)func);
      PrintCodeAddress((long)func);
      fprintf(output, "\n");
      fprintf(output, "StackRefAction is 0x%x", (int)StackRefAction);
      PrintCodeAddress((long)StackRefAction);
      fprintf(output, "\n");
  });

  DEBUG_CODE(if (DebugStackObj){
    DebugStack=TRUE;
  } else {
    DebugStack=FALSE;
  });

  Claim(sObj->StackSize <= sObj->BodySize, "StackObject: Stack <= Object");

  theEnd = &sObj->Body[0] + sObj->StackSize;

  ProcessRefStack(*theEnd, (Object **)(theEnd+1), func);

  DEBUG_STACKOBJ(fprintf(output, " *-*-* End StackObject 0x%x *-*-*\n", (int)sObj));
  DEBUG_CODE(DebugStack=oldDebugStack);
}

#endif /* hppa */
/*************************** End HPPA *********************************/

/*************************** Begin SPARC ******************************/

#ifdef sparc
#include "../CRUN/crun.h"

static long skipCparams;

/* #define DEBUG_LABELS */
/* #define SPARC_SKIP_TO_ETEXT 1*/

#ifdef RTDEBUG
RegWin *BottomAR=0, *lastAR=0;
GLOBAL(long PC) = 0;
void PrintAR(RegWin *ar, RegWin *theEnd);
void PrintCAR(RegWin *cAR);
#endif

/* ProcessStackCell:
 * Called for each GC register in the register window.
 */
static __inline__ void ProcessStackCell(long *addr, char *desc, CellProcessFunc func)
{
  /* On the sparc, the register windows for CAlloI and CAlloC 
   * may be used as roots for GC, since these routines may have called
   * G-parts, that have triggered the GC.
   * Although the C routines are written so that gcc should avoid putting
   * strange things into the GC-registers of the register window, this 
   * will probably happen anyway. Thus we need a slightly stronger check
   * for whether *(Object**)addr really looks like it is an object
   * (the isObject macro used in "func" is defined to always return 1 
   * for non-debug systems). 
   * It is probably OK with a relatively expensive test a la the debug-version
   * of isObject, since there are not that many stack- and stackobject roots.
   *
   * Notice that adding a stronger test around the call of func, will probably
   * mean that e.g. inBetaHeap(*addr) is done twice (it is also done in "func")
   * but this is probably a price we have to pay for the generality of the
   * function-parameterized routines.
   */
  if (strongIsObject(*(Object **)addr)) {
    func((Object **)addr, *(Object **)addr);
    DEBUG_LAZY({
      if (isLazyRef(*addr)) {
	fprintf (output, "Lazy ref in %s: %d\n", desc, (int)(*addr));
      }
    });
  }
}

/* ProcessAR:
 * Traverse an activation record (AR) [ar, theEnd[
 * Notice theEnd is *not* included.
 * Used to process register windows+stackpart on machine stack and in 
 * stack objects.
 */

static void ProcessAR(RegWin *ar, RegWin *theEnd, CellProcessFunc func)
{
  long *theCell = (long *) &ar[1] /* first cell after regwin */;
  
  /* Claim(ar->fp == theEnd)? 
   * No: sometimes fp is zero (for frame of _start, e.g.)
   */
  
  DEBUG_STACK(PrintAR(ar, theEnd));
  
  Claim((long)ar < (long)theEnd,  "ProcessAR: ar is less than theEnd");
  Claim(((long) theEnd) % 4 == 0, "ProcessAR: theEnd is 4 byte aligned");
  
  /* Process GC registers of the activation record. */
  ProcessStackCell(&ar->i0, "i0", func);
  ProcessStackCell(&ar->i1, "i1", func);
  ProcessStackCell(&ar->i2, "i2", func);
  ProcessStackCell(&ar->i3, "i3", func);
  ProcessStackCell(&ar->i4, "i4", func);
  
  /* Process the stack part */
  if (skipCparams){
    /* This AR called C, skip one hidden word, and (at least) 
     * six parameters (compiler allocates 12, that may be too much...)
     */
#if defined(RTVALHALLA) || defined(PERSIST)
    Claim((long)theCell+48>=(long)ar->fp, "C Skip must be inside frame");
    if ((valhallaID && (valhalla_exelevel>0)) || (callRebinderC)){
      /* We are running under valhalla, and at least one evaluator is
       * under execution.
       * In this case a callback is simulated by setting BetaStackTop
       * to the value of SP at the time valhallaOnProcess was called.
       * This resembles a C call (BETA code was left, external code
       * was entered). However, the BETA code was NOT left using
       * an actual call instruction, and there was NOT allocated
       * room on the stack for parameteres.
       */
      if (isExecuteObjectSP((long*)ar)){ 
	DEBUG_VALHALLA(fprintf(output, 
			       "ProcessAR: SP of VOP_EXECUTEOBJECT: 0x%x\n",
			       (int)ar));
	skipCparams = 0;
      } 
    }
#endif /* RTVALHALLA */
    if (skipCparams){
      /* Will not skip out of frame - let's do it... */
      theCell += (48/sizeof(long*));
    }
  }
  
  for (; theCell != (long*)theEnd; theCell+=2) {
    /* +2 because the compiler uses "dec %sp,8,%sp" before pushing */
    /* (Maybe build a more descriptive description using sprintf) */
    ProcessStackCell(theCell, "stackpart", func);
  }
}

static void ProcessSPARCStack(void)
{
    RegWin *theAR;
    RegWin *nextCBF = (RegWin *) ActiveCallBackFrame;
    RegWin *nextCompBlock = (RegWin *) lastCompBlock;
    
    /* Flush register windows to stack */
    __asm__("ta 3");

    skipCparams=FALSE;

    DEBUG_STACK(fprintf(output, "\n ***** Trace of stack *****\n"));
    DEBUG_STACK(fprintf(output,
			"IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
			(int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit));

    /* StackEnd points to the activation record of doGC, which in turn was called
     * from either DoGC, or IOA(c)alloc.
     */
    DEBUG_CODE( PC=((RegWin *) StackEnd)->i7 +8);
    StackEnd = (long *)((RegWin *) StackEnd)->fp; /* Skip AR of doGC() */

#if 0
    /* IOA(c)alloc now inlined! */
    StackEnd = (long *)((RegWin *) StackEnd)->fp
      /* Skip AR of IOA(c)alloc / DoGC() / lazyFetchIOAGc() */;
#endif

    for (theAR =  (RegWin *) StackEnd;
	 theAR != (RegWin *) 0;
#ifdef RTDEBUG
	 PC = theAR->i7 +8,
#endif
	   theAR = (RegWin *) theAR->fp) {
      
      if (theAR == nextCompBlock) {
	/* This is the AR of attach. Continue GC, but get
	 * new values for nextCompBlock and nextCBF. 
	 * Please read StackLayout.doc
	 */
	nextCBF = (RegWin *) theAR->l5;
	nextCompBlock = (RegWin *) theAR->l6;
	if (nextCompBlock == 0)
	  break; /* we reached the bottom */
      } else {
	if (theAR == nextCBF) {
	  /* This is AR of HandleCB. Don't GC this, but
	   * skip to betaTop and update nextCBF */
	  nextCBF = (RegWin *) theAR->l5;
	  DEBUG_STACK({ 
	    fprintf(output, "Met frame of HandleCB at SP=0x%x.\n",(int)theAR);
	    if (valhallaID || callRebinderC){
	      fprintf(output, "Cannot wind down past signal handler.\n");
	      fprintf(output, "Skipping directly to SP=0x%x.\n", (int)theAR->l6);
	    } else {
	      /* Wind down the stack until betaTop is reached */
	      RegWin *cAR;
	      fprintf(output, "Winding down to frame with %%fp=0x%x",(int)theAR->l6);
	      fprintf(output, " (BetaStackTop)\n");
	      for (cAR = theAR;
		   cAR != (RegWin *) theAR->l6;
		   PC = cAR->i7 +8, cAR = (RegWin *) cAR->fp){
		if (!cAR) {
		  fprintf(output, "ProcessStack: gone past _start - exiting...!\n");
		  Illegal();
		  BetaExit(1);
		}
		PrintCAR(cAR);
	      }
	    }
	  });
	  
	  theAR = (RegWin *) theAR->l6; /* Skip to betaTop */
	  
	  skipCparams = TRUE;
	}
      }
      ProcessAR(theAR, (RegWin *) theAR->fp, DoStackCell);
      CompleteScavenging();
      skipCparams=FALSE;
      DEBUG_CODE(lastAR = theAR);
    }
    DEBUG_CODE(if (BottomAR)
               Claim(lastAR==BottomAR, "lastAR==BottomAR");
               else
               BottomAR=lastAR;
	       );
    DEBUG_STACK(fprintf(output, " *****  End of trace  *****\n"));
}

#ifdef RTDEBUG
GLOBAL(long lastPC)=0;
#endif

static void ProcessSPARCStackObj(StackObject *sObj, CellProcessFunc func)
{
    RegWin *theAR;
    long delta;
    DEBUG_CODE(long oldDebugStack=DebugStack);

    DEBUG_STACKOBJ({
      fprintf(output,
	      " *-*-* StackObject: 0x%x, size: 0x%x %s *-*-*\n", 
	      (int)sObj, 
	      (int)(sObj->StackSize),
	      WhichHeap((Object*)sObj));
      fprintf(output, "func is 0x%x", (int)func);
      PrintCodeAddress((long)func);
      fprintf(output, "\n");
      fprintf(output, "StackRefAction is 0x%x", (int)StackRefAction);
      PrintCodeAddress((long)StackRefAction);
      fprintf(output, "\n");
      
      lastPC=PC;
      /* The PC of the topmost AR is saved in CallerLCS of the comp 
       * this stackobj belongs to. It is not known here. 
       */
      PC = 0;
    });
    DEBUG_CODE(if (DebugStackObj){
      DebugStack=TRUE;
    } else {
      DebugStack=FALSE;
    });

    if (!sObj->StackSize) {
      if (do_unconditional_gc) {
	/* OK - can happen in gc triggered by AlloSO */
      } else {
	DEBUG_CODE({
	  fprintf(output, 
		  "stackobject 0x%x has stacksize=0\n", (int)sObj);
	    Illegal();
	});
      }
      return;
    }
    /* Start at sObj->Body[1], since sObj->Body[0] is saved FramePointer */
    delta = (char *) &sObj->Body[1] - (char *) sObj->Body[0];
    
    for (theAR =  (RegWin *) &sObj->Body[1];
	 theAR != (RegWin *) &sObj->Body[sObj->StackSize];
	 theAR =  (RegWin *) (theAR->fp + delta)){
	Claim(&sObj->Body[1] <= (long *) theAR
	      && (long *) theAR <= &sObj->Body[sObj->StackSize],
	      "ProcessSPARCStackObj: theAR in StackObject");
	ProcessAR(theAR, (RegWin *) (theAR->fp + delta), func);
	DEBUG_CODE(PC = theAR->i7 +8);
      }

    DEBUG_STACKOBJ(fprintf(output, " *-*-* End StackObject 0x%x *-*-*\n", (int)sObj);
		   PC=lastPC;
		   );
    DEBUG_CODE(DebugStack=oldDebugStack);
}

#ifdef RTDEBUG
void PrintCAR(RegWin *cAR)
{
  char *lab = getLabel(PC);
  fprintf(output, 
	  "\n----- C AR: 0x%x, end: 0x%x, PC: 0x%x <%s+0x%x>\n",
	  (int)cAR, 
	  (int)cAR->fp,
	  (int)PC,
	  lab,
	  (int)labelOffset);
  fprintf(output, "%%fp: 0x%x\n", (int)cAR->fp); 
}

void PrintAR(RegWin *ar, RegWin *theEnd)
{
  Object **theCell = (Object **) &ar[1];
  char *lab = getLabel(PC);
  int oldSkipCparams = skipCparams;

  fprintf(output, 
	  "\n----- AR: 0x%x, theEnd: 0x%x, PC: 0x%x <%s+0x%x>\n",
	  (int)ar, 
	  (int)theEnd,
	  (int)PC,
	  lab,
	  (int)labelOffset);

  fprintf(output, "%%i0: 0x%x", (int)ar->i0); 
  PrintRef((Object *)ar->i0);
  fprintf(output, "\n");
  fprintf(output, "%%i1: 0x%x", (int)ar->i1); 
  PrintRef((Object *)ar->i1)
    /* Notice that CopyT, AlloVR1-4 gets an offset in this parameter.
     * This should be safe.
     */;
  fprintf(output, "\n");
  fprintf(output, "%%i2: 0x%x", (int)ar->i2); 
  PrintRef((Object *)ar->i2);
  fprintf(output, "\n");
  fprintf(output, "%%i3: 0x%x", (int)ar->i3); 
  PrintRef((Object *)ar->i3);
  fprintf(output, "\n");
  fprintf(output, "%%i4: 0x%x", (int)ar->i4); 
  PrintRef((Object *)ar->i4);
  fprintf(output, "\n");
  fprintf(output, "%%fp: 0x%x\n", (int)ar->fp); 
  fprintf(output, "%%l5: 0x%x\n", (int)ar->l5); 
  fprintf(output, "%%l6: 0x%x\n", (int)ar->l6); 

  fprintf(output, "stackpart:\n");
  /* Notice that in INNER some return adresses are pushed. This is no
   * danger.
   */
  if (skipCparams){
    /* This AR called C, skip one hidden word, and (at least) 
     * six parameters. See comments in ProcessAR.
     */
    int i;
    Claim((long)theCell+48>=(long)ar->fp, "C Skip must be inside frame");
    if (valhallaID && (valhalla_exelevel>0)){
      if (isExecuteObjectSP((long*)ar)){
	DEBUG_STACK({
	  fprintf(output, 
		  "Frame is invoker of valhalla evaluator.\n"
		  );
	});
	skipCparams = 0;
      }
      if (skipCparams){
	fprintf(output, "Skipping 12 words in frame that called C:\n");
	for (i=0; i<12; i++) PrintSkipped((long*)theCell+i);
	theCell = (Object **)((long)theCell+48);
      }
    }      
  }
  for (; theCell != (Object **) theEnd; theCell+=2) {
    fprintf(output, "0x%x", (int)(*theCell));
    PrintRef((Object *)(*theCell));
    fprintf(output, "\n");
  }
  fflush(output);
  skipCparams = oldSkipCparams;
}

/* PrintStack: (sparc).
 * Should probably not be called during GC. Instead, you may set DebugStack to
 * TRUE before calling IOAGc()
 */
void PrintStack(void)
{
  RegWin *theAR;
  RegWin *nextCBF = (RegWin *) ActiveCallBackFrame;
  RegWin *nextCompBlock = (RegWin *) lastCompBlock;
  RegWin *end;
  
  /* Flush register windows to stack */
  __asm__("ta 3");
  
  fprintf(output, "\n ***** PrintStack: Trace of stack *****\n");
  
  end  = (RegWin *)StackPointer;
  /* end points to the activation record of PrintStack() */
  PC=((RegWin *) end)->i7 +8;
  end = (RegWin *)((RegWin *) end)->fp; /* Skip AR of PrintStack() */

  skipCparams = TRUE; /* Skip 12 longs allocated for the call to PrintStack() */

  for (theAR =  (RegWin *) end;
       theAR != (RegWin *) 0;
       PC = theAR->i7 +8, theAR = (RegWin *) theAR->fp) {
    if (theAR == nextCompBlock) {
      /* This is the AR of attach. Continue, but get
       * new values for nextCompBlock and nextCBF. 
       * Please read StackLayout.doc
       */
      nextCBF = (RegWin *) theAR->l5;
      nextCompBlock = (RegWin *) theAR->l6;
      if (nextCompBlock == 0)
	break; /* we reached the bottom */
    } else {
      if (theAR == nextCBF) {
	/* This is AR of HandleCB. Skip this and
	 * skip to betaTop and update nextCBF
	 */
	    nextCBF = (RegWin *) theAR->l5;

	    DEBUG_STACK({ /* Wind down the stack until betaTop is reached */
			  RegWin *cAR;
			  for (cAR = theAR;
			       cAR != (RegWin *) theAR->l6;
			       PC = cAR->i7 +8, cAR = (RegWin *) cAR->fp)
			    PrintCAR(cAR);
			});

	    theAR = (RegWin *) theAR->l6; /* Skip to betaTop */
	    skipCparams=TRUE;
      }
    }
    PrintAR(theAR, (RegWin *) theAR->fp);
    skipCparams=FALSE;
  }
   
  fprintf(output, " *****  PrintStack: End of trace  *****\n");
  
}
#endif /* RTDEBUG */
#endif /* sparc */
/****************************** End SPARC **********************************/

/****************************** Begin INTEL ********************************/

#ifdef intel

#ifdef RTDEBUG
static void PrintSkipped(long *current);
#endif /* RTDEBUG */

/* Traverse the StackArea [low..high] and Process all references within it. */
static
void ProcessStackPart(long *low, long *high)
{
  long * current = low;
  Object * theObj;
  Object ** theCell;
  DEBUG_STACK(fprintf(output, 
		      "\n----- AR: low: 0x%08x, high: 0x%08x\n", (int)low, (int)high);
	      fprintf(output, "ComponentBlock/CallbackFrame: [0x%08x, 0x%08x, 0x%08x]\n", 
		      (int)(*(high+1)), (int)(*(high+2)), (int)(*(high+3)));
	      );
  Claim( high <= (long *)StackStart, "ProcessStackPart: high<=StackStart" );
  
  while( current <= high ){
    if(inBetaHeap((Object *)*current)){
      theCell = (Object **) current;
      theObj  = *theCell;
      if (isObject(theObj)) {
	  DEBUG_STACK({ fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
			PrintRef(*(Object**)current);
			fprintf(output, "\n");
		      });
	  ProcessReference( (Object **)current);
	  CompleteScavenging();
      } else {
	DEBUG_CODE({
	  if (!isValRep(theObj)){
	    fprintf(output, "*** SUSPICIOUS REFERENCE ON STACK: 0x%08x: 0x%08x", 
		    (int)current, (int)(*current));
	    if (IsPrototypeOfProcess((long)GETPROTO(theObj))){
	      fprintf(output, " Proto: 0x%08x (%s)\n",
		      (int)GETPROTO(theObj),
		      ProtoTypeName(GETPROTO(theObj)));
	    } else {
	      fprintf(output, " *** ILLEGAL PROTOTYPE: 0x%08x\n", (int)GETPROTO(theObj));
	    }
	  }
	});
      }
    } else {
      /* Not in beta heap */
      /* handle tagged data registers on the stack */
      DEBUG_STACK({
	if ((-8<=(*current)) && ((*current)<=-5))
	  fprintf(output, 
		  "0x%08x: %d (SKIP NEXT %d)\n", 
		  (int)current, 
		  (int)*current, 
		  -(int)*current-4
		  );
      });
      switch(*current){
      case -8: 
	current++; 
	DEBUG_STACK(PrintSkipped(current)); 
	/* deliberately no break here */
      case -7: /* skip 3 */
	current++; 
	DEBUG_STACK(PrintSkipped(current)); 
	/* deliberately no break here */
      case -6: /* skip 2 */
	current++; 
	DEBUG_STACK(PrintSkipped(current));
	/* deliberately no break here */
      case -5: /* skip 1 */
	current++;
	DEBUG_STACK(PrintSkipped(current)); 
	break;
      default:
	if (isLazyRef(*current)) {
	  /* (*current) is a dangling reference */
	  DEBUG_STACK(fprintf(output, "0x%08x: %d - LAZY\n", (int)current, (int)*current));
	  ProcessReference ((Object **)current);
	} else {
	  DEBUG_STACK({
	    fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
	    if (*current) {
	      if (IsPrototypeOfProcess(*current)) {
		fprintf(output, ", is proto  (");
		PrintProto((ProtoType*)*current);
		fprintf(output, ")\n");
	      } else {
		fprintf(output, " ");
		PrintCodeAddress(*current);
		fprintf(output, "\n");
	      }
	    } else {
	      fprintf(output, "\n");
	    }
	  });
	}
	break;
      }
    }
    current++;
  }
}

static
void ProcessINTELStack(void)
{
    long *theTop;
    long *theBottom;
    
    CallBackFrame *  theFrame;
    ComponentBlock * currentBlock;
    
    DEBUG_STACK(fprintf(output, "\n ***** Trace of stack *****\n"));
    /*
     * First handle the topmost component block
     */
    theTop    = StackEnd;
    theBottom = (long *) lastCompBlock;
    theFrame  = ActiveCallBackFrame;
    /* Follow the stack */
    while( theFrame){
	ProcessStackPart( theTop, (long *)theFrame-1);
	theTop   = theFrame->betaTop;
	theFrame = theFrame->next;
    }
    ProcessStackPart(theTop, theBottom-1);  
    
    /*
     * Then handle the remaining component blocks.
     */
    currentBlock = lastCompBlock;
    while( currentBlock->next ){
	theTop    = (long *) ((long) currentBlock +
			      sizeof(ComponentBlock) );
	theBottom = (long *) currentBlock->next;
	theFrame  = currentBlock->callBackFrame;
	while( theFrame){
	    ProcessStackPart( theTop, (long *)theFrame-1);
	    theTop   = theFrame->betaTop;
	    theFrame = theFrame->next;
	}
	ProcessStackPart(theTop, theBottom-1);  
	currentBlock = currentBlock->next;
    }
    DEBUG_STACK(fprintf(output, " *****  End of trace  *****\n"));
}

static
void ProcessINTELStackObj(StackObject *sObj, CellProcessFunc func)
{ 
  long    *current; 
  long    *theEnd;
  DEBUG_CODE(long oldDebugStack=DebugStack);

  DEBUG_STACKOBJ({
      fprintf(output,
	      " *-*-* StackObject: 0x%x, size: 0x%x %s *-*-*\n", 
	      (int)sObj, 
	      (int)(sObj->StackSize),
	      WhichHeap((Object*)sObj));
      fprintf(output, "func is 0x%x", (int)func);
      PrintCodeAddress((long)func);
      fprintf(output, "\n");
      fprintf(output, "StackRefAction is 0x%x", (int)StackRefAction);
      PrintCodeAddress((long)StackRefAction);
      fprintf(output, "\n");
  });
  DEBUG_CODE(if (DebugStackObj){
    DebugStack=TRUE;
  } else {
    DebugStack=FALSE;
  });
    
  Claim(sObj->StackSize <= sObj->BodySize, "sObj->StackSize <= sObj->BodySize");
	    
  theEnd = &sObj->Body[0] + sObj->StackSize;
	
  /* FIXME: could call ProcessStackPart (if parameterized with a CellProcessFunc) */

  for (current = &sObj->Body[0]; current < theEnd; current++) {
    DEBUG_STACK({
      if ((-8<=(*current)) && ((*current)<=-5))
	fprintf(output, 
		"0x%08x: %d (SKIP NEXT %d)\n", 
		(int)current, 
		(int)*current, 
		-(int)*current-4
		);
    });
    switch (*current) {
    case -8: 
      current++;
      DEBUG_STACK(PrintSkipped(current)); 
      /* deliberately no break here */
    case -7: 
      current++;
      DEBUG_STACK(PrintSkipped(current)); 
      /* deliberately no break here */
    case -6: 
      current++;
      DEBUG_STACK(PrintSkipped(current)); 
      /* deliberately no break here */
    case -5: 
      current++;
      DEBUG_STACK(PrintSkipped(current)); 
      break;
    default:
      DEBUG_LAZY({
	if (isLazyRef(*current)) {
	  fprintf(output, "Dangler on stack: 0x08%x: %d\n", (int)current, (int)*current);
	}
      });
      DEBUG_STACKOBJ({
	if(inBetaHeap((Object*)*current)){
	  Object *theObj = *(Object **)current;
	  if (isObject(theObj)) {
	    fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
	    PrintRef(*(Object**)current);
	    fprintf(output, "\n");
	  } else {
	    if (!isValRep(theObj)){
	      fprintf(output, "*** SUSPICIOUS REFERENCE IN STACKOBJ: 0x%08x: 0x%08x", 
		      (int)current, (int)(*current));
	      if (IsPrototypeOfProcess((long)GETPROTO(theObj))){
		fprintf(output, " Proto: 0x%08x (%s)\n",
			(int)GETPROTO(theObj),
			ProtoTypeName(GETPROTO(theObj)));
	      } else {
		fprintf(output, " *** ILLEGAL PROTOTYPE: 0x%08x\n", (int)GETPROTO(theObj));
	      }
	    }
	  }
	} else {
	  fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
	  if (*current) {
	    if (IsPrototypeOfProcess(*current)) {
	      fprintf(output, ", is proto  (");
	      PrintProto((ProtoType*)*current);
	      fprintf(output, ")\n");
	    } else {
	      fprintf(output, " ");
	      PrintCodeAddress(*current);
	      fprintf(output, "\n");
	    }
	  } else {
	    fprintf(output, "\n");
	  }
	}
      }) /* DEBUG_STACKOBJ */;
      func((Object**)current, *(Object**)current);
    }
  }
  DEBUG_STACKOBJ(fprintf(output, " *-*-* End StackObject 0x%x *-*-*\n", (int)sObj));
  DEBUG_CODE(DebugStack=oldDebugStack);
}

#ifdef RTDEBUG

/* PrintStackPart: (intel)
 * Traverse the StackArea [low..high] and print all references within it. 
 */
void PrintStackPart(long *low, long *high)
{
  long * current = low;
  Object * theObj;
  Object ** theCell;
  fprintf(output, 
	  "\n----- AR: low: 0x%08x, high: 0x%08x\n", (int)low, (int)high);
  fprintf(output, "ComponentBlock/CallbackFrame: [0x%08x, 0x%08x, 0x%08x]\n", 
	  (int)(*(high+1)), (int)(*(high+2)), (int)(*(high+3)));
  Claim( high <= (long *)StackStart, "PrintStackPart: high<=StackStart" );
  
  while( current <= high ){
    if(inBetaHeap( (Object *)*current)){
      theCell = (Object **) current;
      theObj  = *theCell;
      if( isObject( theObj) ){
	  fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
	  PrintRef(*(Object**)current);
	  fprintf(output, "\n");
      } else {
	if (!isValRep(theObj)){
	  fprintf(output, "*** SUSPICIOUS REFERENCE ON STACK: 0x%08x: 0x%08x", 
		  (int)current, (int)(*current));
	  if (IsPrototypeOfProcess((long)GETPROTO(theObj))){
	    fprintf(output, " Proto: 0x%08x (%s)\n",
		    (int)GETPROTO(theObj),
		    ProtoTypeName(GETPROTO(theObj)));
	  } else {
	    fprintf(output, " *** ILLEGAL PROTOTYPE: 0x%08x\n", (int)GETPROTO(theObj));
	  }
	}
      }
    } else {
      /* handle tagged data registers on the stack */
      if ((-8<=(*current)) && ((*current)<=-5))
	fprintf(output, 
		"0x%08x: %d (SKIP NEXT %d)\n", 
		(int)current, 
		(int)*current, 
		-(int)*current-4
		);
      switch(*current){
      case -8: 
	current++; 
	PrintSkipped(current); 
	/* deliberately no break here */
      case -7: /* skip 3 */
	current++; 
	PrintSkipped(current); 
	/* deliberately no break here */
      case -6: /* skip 2 */
	current++; 
	PrintSkipped(current);
	/* deliberately no break here */
      case -5: /* skip 1 */
	current++;
	PrintSkipped(current); 
	break;
      default:
	if (isLazyRef(*current)) {
	  /* (*current) is a dangling reference */
            fprintf(output, "0x%08x: %d - LAZY\n", (int)current, (int)*current);
        } else {
	  fprintf(output, "0x%08x: 0x%08x", (int)current, (int)*current);
	  if (*current) {
	    if (IsPrototypeOfProcess(*current)) {
	      fprintf(output, ", is proto  (");
	      PrintProto((ProtoType*)*current);
	      fprintf(output, ")\n");
	    } else {
	      fprintf(output, " ");
	      PrintCodeAddress(*current);
	      fprintf(output, "\n");
	    }
	  } else {
	    fprintf(output, "\n");
	  }
	}
	break;
      }
    }
    current++;
  }
}

/* PrintStack: (intel)
 * Notice that StackEnd MUST be supplied!
 */
void PrintStack(long *StackEnd)
{
  /* FIXME: Could find stack top from here with (e.g. &theTop),
   * but it may sometimes be useful to display from another SP.
   */
  long *          theTop;
  long *          theBottom;
  
  CallBackFrame *  theFrame;
  ComponentBlock * currentBlock;
  
  fprintf(output, "\n ***** Trace of stack *****\n");
  /*
   * First handle the topmost component block
   */
  theTop    = StackEnd;
  theBottom = (long *) lastCompBlock;
  theFrame  = ActiveCallBackFrame;
  /* Follow the stack */
  while( theFrame){
    PrintStackPart( theTop, (long *)theFrame-1);
    theTop   = theFrame->betaTop;
    theFrame = theFrame->next;
  }
  PrintStackPart( theTop, theBottom-1);  
  
  /*
   * Then handle the remaining component blocks.
   */
  currentBlock = lastCompBlock;
  while( currentBlock->next ){
    theTop    = (long *) ((long) currentBlock +
			  sizeof(ComponentBlock) );
    theBottom = (long *) currentBlock->next;
    theFrame  = currentBlock->callBackFrame;
    while( theFrame){
      PrintStackPart( theTop, (long *)theFrame-1);
      theTop   = theFrame->betaTop;
      theFrame = theFrame->next;
    }
    PrintStackPart( theTop, theBottom-1);  
    currentBlock = currentBlock->next;
  }
  fprintf(output, " *****  End of trace  *****\n");
}

#endif /* RTDEBUG */


#endif /* intel */
/***************************** End INTEL **********************************/

/************************* ProcessStack: ***************************/
void ProcessStack(void)
{
#ifdef NEWRUN
  ProcessNEWRUNStack();
#endif /* NEWRUN */
#ifdef hppa
  ProcessHPPAStack();
#endif /* HPPA */
#ifdef intel
  ProcessINTELStack();
#endif /* INTEL */
#ifdef sparc
  ProcessSPARCStack();
#endif /* SPARC */
}

/************************* ProcessStackObj: ***************************/
void ProcessStackObj(StackObject *sObj, CellProcessFunc func)
{
#ifdef NEWRUN
  ProcessNEWRUNStackObj(sObj, func);
#endif /* NEWRUN */
#ifdef hppa
  ProcessHPPAStackObj(sObj, func);
#endif /* HPPA */
#ifdef intel
  ProcessINTELStackObj(sObj, func);
#endif /* INTEL */
#ifdef sparc
  ProcessSPARCStackObj(sObj, func);
#endif /* SPARC */
}

#endif /* MT */
