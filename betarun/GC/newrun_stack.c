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

long WindBackSP(long SP, Object *obj, long PC)
{

#ifdef ppcmac
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
			"RefStack(dyn): 0x%08x: ", 
			(int)theCell));
    DEBUG_STACK(PrintObject(theObj); fprintf(output, "\n"));
    func(theCell, theObj);
    return;
  }

  while(theObj) {
    DEBUG_STACK(fprintf(output, 
			"RefStack(%d): 0x%08x: ", 
			((long)topOfStack - (long)theCell)/4,
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
static void TRACE_STACK(long SP, long PC, Object *theObj, int line) 
{
  if (DebugStack){
    fprintf(output, "File %s; Line %d\n", __FILE__, line); 
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
      TRACE_STACK(unknown,unknown,GetThis((long*)SP),__LINE__);
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

#endif /* MT */
