/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * stack.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 */

#include "beta.h"

#ifndef MT

/* #define DEBUG_LABELS */

#ifdef sparc
#include "../CRUN/crun.h"
#ifdef RTDEBUG
/*#define LD_SEGMENT_TEST*/
#endif
#endif

#ifdef hpux
/* #include <sys/cache.h> */
#endif

#ifdef NEWRUN
/************************* Begin NEWRUN ****************************/

#define DumpProto(theObj)                                        \
{                                                                \
  if ((theObj)&&((theObj)!=CALLBACKMARK)&&((theObj)!=GENMARK)){  \
     if (isObject(theObj)){                                      \
       fprintf(output, " (proto: 0x%x)", (theObj)->Proto);       \
       fprintf(output, " (%s)", ProtoTypeName((theObj)->Proto)); \
     } else {                                                    \
       fprintf(output, " (ILLEGAL OBJECT!)");                    \
     }                                                           \
  }                                                              \
}

#define FrameSeparator() \
fprintf(output, "============================================================================\n")

#if 0
/* Trace search for prefix in ObjectDescription */
#define TRACE_CODEENTRY(code) code; fflush(output)
#else
#define TRACE_CODEENTRY(code)
#endif

/* Return the M or G part obtained from theProto, that PC is in */
unsigned long CodeEntry(struct ProtoType *theProto, long PC)
{
  /* Find the active prefix level based on the PC.
   * Here we use both the G-entry and the M-entry. 
   * The prefix we are in is the one, where the distance from the 
   * G-entry or M-entry of the corresponding prefix-level
   * to PC is smallest.
   */
  long gPart, gDist, mPart, mDist, minDist;
  struct ProtoType *activeProto;
  struct ProtoType *protoArg=theProto;

  TRACE_CODEENTRY(fprintf(output, "CodeEntry(theProto=0x%x (%s), PC=0x%x)\n", theProto, ProtoTypeName(theProto), PC)); 
  mPart = M_Part(theProto);
  gPart = G_Part(theProto);
  gDist  = PC - gPart; 
  mDist  = PC - mPart;
  activeProto = theProto;
  if (gDist < 0) gDist = MAXINT;
  if (mDist < 0) mDist = MAXINT;
  TRACE_CODEENTRY(fprintf(output, "CodeEntry(initial gDist: 0x%x, proto=0x%x)\n", gDist, theProto));
  TRACE_CODEENTRY(fprintf(output, "CodeEntry(initial mDist: 0x%x, proto=0x%x)\n", mDist, theProto));
  minDist = (gDist<mDist) ? gDist : mDist;
    
  while(theProto && theProto->Prefix != theProto){
    theProto = theProto->Prefix;
    TRACE_CODEENTRY(fprintf(output, "CodeEntry: new candidate: theProto=0x%x (%s)\n", theProto, ProtoTypeName(theProto))); 
    mPart = M_Part(theProto);
    gPart = G_Part(theProto);
    if((PC-gPart > 0) && (PC-gPart <= minDist)){ 
      /* Use <= to get the LAST level, that has the entry point */ 
      minDist = gDist = PC-gPart;
      activeProto = theProto; 
      TRACE_CODEENTRY(fprintf(output, "CodeEntry(gDist: 0x%x, proto=0x%x)\n", gDist, theProto));
    }
    if((PC-mPart > 0) && (PC-mPart <= minDist)){ 
      /* Use <= to get the LAST level, that has the entry point */ 
      minDist = mDist = PC-mPart; 
      activeProto = theProto;
      TRACE_CODEENTRY(fprintf(output, "CodeEntry(mDist: 0x%x, proto=0x%x)\n", mDist, theProto));
    }
  }
  if (minDist == MAXINT) {
    fprintf(output, 
	    "Fatal Error: CodeEntry(proto=0x%x, PC=0x%x): minDist == MAXINT\n",
	    protoArg,
	    PC);
    DEBUG_CODE(Illegal());
    BetaExit(1);
  }
  if (minDist == gDist) {
    TRACE_CODEENTRY(fprintf(output, "CodeEntry returns: 0x%x\n", G_Part(activeProto)));
    return (unsigned long)G_Part(activeProto);
  } else {
    TRACE_CODEENTRY(fprintf(output, "CodeEntry returns: 0x%x\n", M_Part(activeProto)));
    return (unsigned long)M_Part(activeProto);
  }
}

/* ProcessRefStack:
 *  Process references in a stack frame.
 */
static 
void ProcessRefStack(struct Object **topOfStack, long dynOnly, CellProcessFunc func)
{
  struct Object **theCell=topOfStack;
  struct Object *theObj= *theCell;

  if (dynOnly) {
    DEBUG_STACK(fprintf(output, 
			"RefStack(dyn): 0x%08x: 0x%08x", 
			(int)theCell,
			(int)*theCell));
    DEBUG_STACK(DumpProto(theObj));
    func(theCell, theObj);
    DEBUG_STACK(fprintf(output, " done\n"));
    return;
  }

  while(theObj) {
    DEBUG_STACK(fprintf(output, 
			"RefStack(%d): 0x%08x: 0x%08x", 
			((long)topOfStack - (long)theCell)/4,
			(int)theCell,
			(int)*theCell));
    DEBUG_STACK(DumpProto(theObj));
    func(theCell, theObj);
    DEBUG_STACK(fprintf(output, " done\n"));
    /* Take next reference from stack */
    theCell--;
    theObj = *theCell;
  } 
}

#if 0
#define TRACE_NEW_FRAME() \
DEBUG_STACK(fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__)); \
DEBUG_STACK(fprintf(output, "Own SP:        0x%x\n", SP));              \
DEBUG_STACK(fprintf(output, "Caller PC:     0x%x\n", PC));              \
DEBUG_STACK(fprintf(output, "Caller object: 0x%x", theObj));            \
DEBUG_STACK(DumpProto(theObj));                                         \
DEBUG_STACK(fprintf(output, "\n"));
#else
#define TRACE_NEW_FRAME() 
#endif

#define TRACE_STACK(SP,PC,theObj) \
DEBUG_STACK(fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__));       \
DEBUG_STACK(fprintf(output, "---------------------\n", SP));                  \
DEBUG_STACK(fprintf(output, "SP:        0x%08x\n", SP));                      \
DEBUG_STACK(fprintf(output, "PC:        0x%08x\n", PC));                      \
DEBUG_STACK(fprintf(output, "object:    0x%08x", theObj));                    \
DEBUG_STACK(DumpProto(theObj));                                               \
DEBUG_STACK(fprintf(output, "\n"));                                           \
DEBUG_STACK(fprintf(output, "---------------------\n", SP))


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
  struct Object *theObj;
  long *CSP = CompSP;
  long SPoff, PC;
#ifdef macppc
  long SPz = StackObjEnd; /* Used for stackobjects */
#endif
#ifdef RTDEBUG
  struct Object *current;
  long currentSP, currentPC;
  int unknown=-1;
#endif
  
  DEBUG_STACK(fprintf(output, "ProcessStackFrames(SP=0x%x, StackStart=0x%x)\n",
		      SP, StackStart));
  DEBUG_CODE(Claim(SP<=(long)StackStart, "SP<=StackStart"));

  /* Process the top frame */
  DEBUG_STACK(FrameSeparator());
  DEBUG_STACK(fprintf(output, "Processing top frame:\n"));
  TRACE_STACK(SP,unknown,GetThis((long *)SP));
  ProcessRefStack((struct Object **)SP-DYNOFF, dynOnly, func);
  PC = GetPC(SP);
  theObj = *((struct Object **)SP-DYNOFF);

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
     * the frame for this previous object (saved in BetaStackTop[1]).
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
      DEBUG_CODE(Claim(oldSP<SP, "SP greater before callback/allocation"));
      DEBUG_STACK(fprintf(output, " Skipping to prevSP=0x%x\n", SP));
      /* Treat this frame as a top frame */
      DEBUG_CODE(Claim(SP<=(long)StackStart, "SP<=StackStart"));
      DEBUG_STACK(FrameSeparator());
      DEBUG_STACK(fprintf(output, 
			  "Processing top frame before %s:\n",
			  (isGen) ? "allocation" : "callback"));
      TRACE_STACK(unknown,unknown,GetThis((long*)SP));
      ProcessRefStack((struct Object **)SP-DYNOFF, dynOnly, func);
      PC = GetPC(SP);
      theObj = *((struct Object **)SP-DYNOFF); 
      TRACE_NEW_FRAME();
      if (SP<StackStart) {
	continue; /* Restart do-loop */
      } else {
	break; /* Leave do-loop */
      }
    }

    /* Check for passing of a DoPart object */
    if ((long)theObj->Proto == (long)DopartObjectPTValue) {
      DEBUG_STACK(fprintf(output, "Passing dopart object 0x%x\n", theObj));
      theObj = ((struct DopartObject *)theObj)->Origin;
      continue;
    }

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

    if ((long)theObj->Proto == (long)ComponentPTValue) {
      struct Component *comp = (struct Component *)theObj;
      struct Component *callerComp = comp->CallerComp;

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
      
      DEBUG_CODE(Claim(!isSpecialProtoType(theObj->Proto), 
		       "!isSpecialProtoType(theObj->Proto)"));
      
#ifdef ppcmac
      SP = *(long*)SP; /* Use FramePointer */
      if (isStackObject){
      	SP += SPz; 
      }
#else
      {
         long SPoff /* size allocated on stack when theObj became active */;
	 GetSPoff(SPoff, CodeEntry(theObj->Proto, PC)); 
#if 0
         DEBUG_STACK(fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__));
         DEBUG_STACK(fprintf(output, "New SP:      0x%x\n", SP));
         DEBUG_STACK(fprintf(output, "CodeEntry:   0x%x\n", CodeEntry(theObj->Proto, PC)));
         DEBUG_STACK(fprintf(output, "SPoff:       0x%x\n", SPoff));
#endif
         SP = (long)SP+SPoff;
      }
#endif
      /* SP now points to end of *previous* frame, i.e. bottom of top frame */
      /* normal dyn from the start of this frame gives current object */
      theObj = *((struct Object **)SP-DYNOFF); 
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

    DEBUG_CODE(Claim(SP<=(long)StackStart, "SP<=StackStart"));
    DEBUG_STACK(FrameSeparator());
    DEBUG_STACK(fprintf(output, "Processing normal frame:\n"));
    TRACE_STACK(currentSP,currentPC,current);
    ProcessRefStack((struct Object **)SP-DYNOFF, dynOnly, func);

  } while (SP<StackStart);
#if 0
  /* The following claim does not hold anymore because of the 
   * CallB frame after main and Att.
   */
  DEBUG_CODE(Claim(SP==(long)StackStart, "SP==StackStart"));
#endif

  DEBUG_STACK(FrameSeparator());

} /* ProcessStackFrames */

void ProcessStack()
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
  ProcessRefStack(RefSP-1, FALSE, DoIOACell); /* RefSP points to first free */
  DEBUG_STACK(FrameSeparator());
  DEBUG_STACK(fprintf(output, "Processing MachineStack.\n"));
  ProcessStackFrames((long)StackEnd, (long)StackStart, FALSE, FALSE, DoIOACell);
}

void ProcessStackObj(struct StackObject *sObj, CellProcessFunc func)
{
  DEBUG_STACK(fprintf(output, "\nProcessStackObject 0x%x\n", sObj));
#ifdef ppcmac
  StackObjEnd = (long)sObj->Body;
#endif
  ProcessStackFrames((long)sObj->Body+(long)sObj->StackSize, /* top frame off */
		     (long)sObj->Body+(long)sObj->BodySize, /* bottom */
		     TRUE, /* Stop at component */
		     FALSE, /* Do not only process dyn cells */
		     func
		     ); 
}

#endif /* NEWRUN */
/*************************** End NEWRUN ***************************/

/* Traverse an stack parts and process all references.
 * Don't process references from the stack to LVRA. The ValReps in
 * in LVRA are not moved by CopyObject, but if ProcessReference
 * is called with such a reference, the LVRA cycle is broken!
 */

#ifdef hppa
/***************************** SNAKE ****************************/

#ifdef RTDEBUG
void PrintRefStack()
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

void ProcessRefStack(size, bottom)
     unsigned size; /* number of pointers to process */
     long **bottom;
{
  long i;
  struct Object **theCell;
  struct Object *theObj;

  DEBUG_IOA(PrintRefStack());
  theCell = (struct Object **)bottom;
  for(; size > 0; size--, theCell++) {
    if (!isLazyRef(*theCell)) {
      i = ((unsigned)*theCell & 1) ? 1 : 0; 
      *theCell = (struct Object *)((unsigned)*theCell & ~1);
    } else {
      i = 0;
    }
#ifdef RTVALHALLA
    /* If i=1 then the cell is tagged, and the previous cell that was
     * processed was actually a return address. This can newer be confused with
     * a BETA object, so it does not matter except for speed.
     */
#endif
    DEBUG_IOA(fprintf(output, "ProcessRefStack: 0x%08x: 0x%08x\n", (int)theCell, (int)(*theCell)));
    theObj = *theCell;
    if(theObj && (theObj!=(struct Object *)ExternalMarker) && 
       inBetaHeap(theObj) && isObject(theObj)) {
      if(inLVRA( theObj)){
	DEBUG_IOA( fprintf( output, "(STACK(%x) is pointer into LVRA)", (int)theCell));
      } else {
	ProcessReference(theCell);
	CompleteScavenging();
      }
    }
#ifdef RTLAZY
    else if (isLazyRef(theObj)) {
      DEBUG_IOA(fprintf (output, "ProcessRefStack: Lazy ref: %d\n", (int)theObj));
      ProcessReference(casthandle(Object)(theCell));
    }
#endif
#ifdef RTDEBUG
    else {
      if (theObj 
	  && !isProto(theObj) /* e.g. AlloI is called with prototype in ref. reg. */
	  && !isCode(theObj)  /* e.g. at INNER a ref. reg contains code address */
          && (theObj!=(struct Object *)ExternalMarker)
	  ) {
	if (inLVRA(theObj)){
	  fprintf(output, "[ProcessRefStack: pointer into LVRA: 0x%x: 0x%x]\n", 
		  (int)theCell,
		  (int)theObj);
	} else {
	  fprintf(output, "[ProcessRefStack: ***Illegal: 0x%x: 0x%x]\n", 
		  (int)theCell, 
		  (int)theObj);
	  Illegal();
	}
      }
    }
#endif
    if(i) *theCell = (struct Object *)((unsigned)*theCell | 1);
  }
}

void ProcessStack()
{

  ProcessRefStack(((unsigned)/*getRefSP()*/RefSP-(unsigned)&ReferenceStack[0]) >> 2,
                  &ReferenceStack[0]);
}

/*
 * A stackobject on the snake looks like this:
 * Header
 * Body (the runtime stack-section)
 * RefStackLength
 * RefStack section
 */
void ProcessStackObj(struct StackObject *theStackObject)
{
  ptr(long)        theEnd;

  DEBUG_IOA(fprintf(output, "ProcessStackObj: theStack: 0x%x, size: 0x%x\n", (int)theStackObject, (int)(theStackObject->StackSize)));

  DEBUG_IOA( Claim(theStackObject->StackSize <= theStackObject->BodySize,
                   "ProcessReference: StackObjectType: Stack <= Object") );

  theEnd = &theStackObject->Body[0] + theStackObject->StackSize;

  ProcessRefStack(*theEnd, theEnd+1);
}

#endif /* hppa */

/*************************** CRTS *********************************/

#ifdef crts

#ifdef RTDEBUG
/* This is currently a copy of the hppa function. */
void PrintRefStack()
{
  long *theCell = (long *)&ReferenceStack[0];
  long size = ((long)RefSP - (long)&ReferenceStack[0])/4;
  fprintf(output, "RefStk: [%x .. %x[\n", (int)&ReferenceStack[0], (int)RefSP);
  for(; size > 0; size--, theCell++){
    if (!isLazyRef(*theCell) && ((*theCell)!=ExternalMarker) && (*theCell & 1)){ 
      /* Used in beta.dump */
      fprintf(output, "  0x%08x: 0x%08x #\n", (int)theCell, (int)*theCell);
    } else {
      fprintf(output, "  0x%08x: 0x%08x\n", (int)theCell, (int)*theCell);
    }
  }
}
#endif

void ProcessRefStack(size, bottom)
     unsigned size; /* number of pointers to process */
     long **bottom;
{
  long isTagged;
  struct Object **theCell;
  struct Object *theObj;

  DEBUG_IOA(PrintRefStack());
  theCell = (struct Object **)bottom;
  for(; size > 0; size--, theCell++) {
    if (!isLazyRef(*theCell)) {
      isTagged = ((unsigned)*theCell & 1) ? 1 : 0; 
      *theCell = (struct Object *)((unsigned)*theCell & ~1);
    } else {
      isTagged = 0;
    }
    /* DEBUG_IOA(fprintf(output, "ProcessRefStack: 0x%08x: 0x%08x\n", (int)theCell,
                         (int)*theCell));*/
    theObj = *theCell;
    if(theObj && (theObj!=(struct Object *)ExternalMarker) && 
       inBetaHeap(theObj) && isObject(theObj)) {
      if(inLVRA( theObj)){
	DEBUG_IOA( fprintf( output, "(STACK(%x) is pointer into LVRA)", (int)theCell));
      } else {
	ProcessReference(theCell);
	CompleteScavenging();
      }
    }
#ifdef RTLAZY
    else if (isLazyRef(theObj)) {
      DEBUG_IOA(fprintf (output, "ProcessRefStack: Lazy ref: %d\n", (int)theObj));
      ProcessReference(casthandle(Object)(theCell));
    }
#endif
#ifdef RTDEBUG
#ifndef MAC
    else {
      if (theObj 
	  && !isProto(theObj) /* e.g. AlloI is called with prototype in ref. reg. */
	  && !isCode(theObj)  /* e.g. at INNER a ref. reg contains code address */
          && (theObj!=(struct Object *)ExternalMarker)
	  ) {
	if (inLVRA(theObj)){
	    fprintf(output, "[ProcessRefStack: pointer into LVRA: 0x%x: 0x%x]\n", 
		    (int)theCell, 
		    (int)theObj);
	} else {
	  fprintf(output, "[ProcessRefStack: ***Illegal: 0x%x: 0x%x]\n", 
		  (int)theCell,
		  (int)theObj);
	  Illegal();
	}
      }
    }
#endif
#endif
    if(isTagged) *theCell = (struct Object *)((unsigned)*theCell | 1);
  }
}

void ProcessStack()
{
  ProcessRefStack(((unsigned)RefSP-(unsigned)&ReferenceStack[0]) >> 2,
		  &ReferenceStack[0]);
}

/*
 * A stackobject in the CRTS looks like this:
 * Header, with 
 *   StackSize= sizeof(runtime stack-section)+sizeof(JumpBufStack)
 * Body, with 
 *   Body[0] = size of runtime stack
 *   Runtime stack
 *   Jump buffer stack
 *   RefStack section
 */
void ProcessStackObj(struct StackObject *theStackObject)
{
  long *        theEnd;

  DEBUG_IOA(fprintf(output, "ProcessStackObj: theStack: 0x%x, size: 0x%x\n", 
		    (int)theStackObject, (int)(theStackObject->StackSize)));
  DEBUG_IOA( Claim(theStackObject->StackSize <= theStackObject->BodySize,
                   "ProcessReference: StackObjectType: Stack <= Object") );

  theEnd = &theStackObject->Body[1] + theStackObject->StackSize;

  ProcessRefStack(theStackObject->BodySize-theStackObject->StackSize-1, (long**)theEnd);
}


void ProcessStackPart(long *low, long *high)
{
}


#endif /* crts */

/*************************** SPARC *********************************/

#ifdef sparc

#ifdef RTDEBUG
struct RegWin *BottomAR=0, *lastAR=0;
GLOBAL(long PC) = 0;
void PrintAR(struct RegWin *ar, struct RegWin *theEnd);
void PrintCAR(struct RegWin *cAR);
#endif

/* Traverse an activation record (AR) [ar, theEnd[
   Notice theEnd is *not* included
   */

/* Don't process references from the stack to LVRA. The ValReps in
 * in LVRA are not moved by CopyObject, but if PrecessReference
 * is called with such a reference, the LVRA cycle is broken!
 */

void ProcessAR(struct RegWin *ar, struct RegWin *theEnd)
{
    struct Object **theCell = (struct Object **) &ar[1];
    
    DEBUG_STACK(PrintAR(ar, theEnd));

    DEBUG_CODE(Claim((long)ar < (long)theEnd,  "ProcessAR: ar is less than theEnd");
	       Claim(((long) theEnd) % 4 == 0, "ProcessAR: theEnd is 4 byte aligned");
	       Claim(((long) theEnd) % 4 == 0, "ProcessAR: theEnd is 4 byte aligned");
	       )
        
    /* Process GC registers of the activation record. */
    DEBUG_IOA(if (inBetaHeap(cast(Object)(ar->i0)) 
		  && inLVRA(cast(Object)(ar->i0)))
	      fprintf(output, "ProcessAR: ar->i0 (0x%x) is pointer into LVRA\n", (int)(ar->i0)));
    DEBUG_IOA(if (inBetaHeap(cast(Object)(ar->i1)) 
		  && inLVRA(cast(Object)(ar->i1)))
	      fprintf(output, "ProcessAR: ar->i1 (0x%x) is pointer into LVRA\n", (int)(ar->i1)));
    DEBUG_IOA(if (inBetaHeap(cast(Object)(ar->i2)) 
		  && inLVRA(cast(Object)(ar->i2)))
	      fprintf(output, "ProcessAR: ar->i2 (0x%x) is pointer into LVRA\n", (int)(ar->i2)));
    DEBUG_IOA(if (inBetaHeap(cast(Object)(ar->i3)) 
		  && inLVRA(cast(Object)(ar->i3)))
	      fprintf(output, "ProcessAR: ar->i3 (0x%x) is pointer into LVRA\n", (int)(ar->i3)));
    DEBUG_IOA(if (inBetaHeap(cast(Object)(ar->i4)) 
		  && inLVRA(cast(Object)(ar->i4)))
	      fprintf(output, "ProcessAR: ar->i4 (0x%x) is pointer into LVRA\n", (int)(ar->i4)));

    if (inBetaHeap(cast(Object)(ar->i0)) 
	&& isObject(cast(Object)(ar->i0)) 
	&& !inLVRA(cast(Object)(ar->i0))) {
      if (isProto((cast(Object)ar->i0)->Proto)) 
	ProcessReference(casthandle(Object)(&ar->i0)); } 
#ifdef RTLAZY
    else if (isLazyRef(ar->i0)) {
      DEBUG_IOA(fprintf (output, "Lazy ref in i0: %d\n", (int)(ar->i0)));
      ProcessReference(casthandle(Object)(&ar->i0));
    }
#endif
    if (inBetaHeap(cast(Object)(ar->i1)) 
	&& isObject(cast(Object)(ar->i1)) 
	&& !inLVRA(cast(Object)(ar->i1))) {
      if (isProto((cast(Object)ar->i1)->Proto)) 
	ProcessReference(casthandle(Object)(&ar->i1)); }
#ifdef RTLAZY
    else if (isLazyRef(ar->i1)) {
      DEBUG_IOA(fprintf (output, "Lazy ref in i1: %d\n", (int)(ar->i1)));
      ProcessReference(casthandle(Object)(&ar->i1));
    }
#endif
    if (inBetaHeap(cast(Object)(ar->i2)) 
	&& isObject(cast(Object)(ar->i2)) 
	&& !inLVRA(cast(Object)(ar->i2))) {
      if (isProto((cast(Object)ar->i2)->Proto)) 
	ProcessReference(casthandle(Object)(&ar->i2)); }
#ifdef RTLAZY
    else if (isLazyRef(ar->i2)) {
      DEBUG_IOA(fprintf (output, "Lazy ref in i2: %d\n", (int)(ar->i2)));
      ProcessReference(casthandle(Object)(&ar->i2));
    }
#endif
    if (inBetaHeap(cast(Object)(ar->i3)) 
	&& isObject(cast(Object)(ar->i3)) 
	&& !inLVRA(cast(Object)(ar->i3))) {
      if (isProto((cast(Object)ar->i3)->Proto)) 
	ProcessReference(casthandle(Object)(&ar->i3)); }
#ifdef RTLAZY
    else if (isLazyRef(ar->i3)) {
      DEBUG_IOA(fprintf (output, "Lazy ref in i3: %d\n", (int)(ar->i3)));
      ProcessReference(casthandle(Object)(&ar->i3));
    }
#endif
    if (inBetaHeap(cast(Object)(ar->i4)) 
	&& isObject(cast(Object)(ar->i4)) 
	&& !inLVRA(cast(Object)(ar->i4))) {
      if (isProto((cast(Object)ar->i4)->Proto)) 
	ProcessReference(casthandle(Object)(&ar->i4)); }
#ifdef RTLAZY
    else if (isLazyRef(ar->i4)) {
      DEBUG_IOA(fprintf (output, "Lazy ref in i4: %d\n", (int)(ar->i4)));
      ProcessReference(casthandle(Object)(&ar->i4));
    }
#endif
    CompleteScavenging();

    /* Process the stack part */
    for (; theCell != (struct Object **) theEnd; theCell+=2)
      /* +2 because the compiler uses "dec %sp,8,%sp" before pushing */
      if (inBetaHeap(*theCell) && isObject(*theCell))
	if(inLVRA(*theCell) ){
	  DEBUG_IOA( fprintf(output, "STACK(%d) (0x%x) is pointer into LVRA", 
			     (int)((long)theCell-(long)&ar[1]), (int)(*theCell)));
	} else {
	  if (isProto((cast(Object)*theCell)->Proto)){
	    ProcessReference(theCell);
	    CompleteScavenging();
	  }
	}
#ifdef RTLAZY
      else if (isLazyRef(*theCell))
	/* Assumes that the only negative values on sparcstack are danglers. */
	ProcessReference(theCell);
#endif
	
}

void ProcessStack()
{
    struct RegWin *theAR;
    struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
    struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
    
    /* Flush register windows to stack */
    __asm__("ta 3");

    DEBUG_STACK(fprintf(output, "\n ***** Trace of stack *****\n"));
    DEBUG_STACK(fprintf(output,
			"IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
			(int)IOA, (int)IOATop, (int)IOALimit));

    /* StackEnd points to the activation record of doGC, which in turn was called
     * from either DoGC, or IOA(c)alloc.
     */
    DEBUG_CODE( PC=((struct RegWin *) StackEnd)->i7 +8);
    StackEnd = (long *)((struct RegWin *) StackEnd)->fp; /* Skip AR of doGC() */

#if 0
    /* IOA(c)alloc now inlined! */
    StackEnd = (long *)((struct RegWin *) StackEnd)->fp
      /* Skip AR of IOA(c)alloc / DoGC() / lazyFetchIOAGc() */;
#endif

#ifdef RTDEBUG
    for (theAR =  (struct RegWin *) StackEnd;
	 theAR != (struct RegWin *) 0;
	 PC = theAR->i7 +8, theAR = (struct RegWin *) theAR->fp) {
#else    
    for (theAR =  (struct RegWin *) StackEnd;
	 theAR != (struct RegWin *) 0;
	 theAR =  (struct RegWin *) theAR->fp) {
#endif
	if (theAR == nextCompBlock) {
	    /* This is the AR of attach. Continue GC, but get
	     * new values for nextCompBlock and nextCBF. 
	     * Please read StackLayout.doc
	     */
	    nextCBF = (struct RegWin *) theAR->l5;
	    nextCompBlock = (struct RegWin *) theAR->l6;
	    if (nextCompBlock == 0)
	      break; /* we reached the bottom */
	} else {
	  if (theAR == nextCBF) {
	    /* This is AR of HandleCB. Don't GC this, but
	     * skip to betaTop and update nextCBF */
	    nextCBF = (struct RegWin *) theAR->l5;
	    
	    DEBUG_STACK({ /* Wind down the stack until betaTop is reached */
			  struct RegWin *cAR;
			  for (cAR = theAR;
			       cAR != (struct RegWin *) theAR->l6;
			       PC = cAR->i7 +8, cAR = (struct RegWin *) cAR->fp)
			    PrintCAR(cAR);
			});

	    theAR = (struct RegWin *) theAR->l6; /* Skip to betaTop */
	  }
	}
	ProcessAR(theAR, (struct RegWin *) theAR->fp);
	DEBUG_CODE(lastAR = theAR);
    }
    DEBUG_CODE(if (BottomAR) Claim(lastAR==BottomAR, "lastAR==BottomAR");
	       else BottomAR=lastAR;
	       )
    DEBUG_STACK(fprintf(output, " *****  End of trace  *****\n"));

}

#ifdef RTDEBUG
GLOBAL(long lastPC)=0;
#endif

void ProcessStackObj(struct StackObject *theStack)
{
    struct RegWin *theAR;

    /* Start at theStack->Body[1], since theStack->Body[0] is saved FramePointer */
    long delta = (char *) &theStack->Body[1] - (char *) theStack->Body[0];
    
    DEBUG_STACK(fprintf(output, " *-*-* StackObject *-*-* \n");
		lastPC=PC;
		/* The PC of the topmost AR is saved in CallerLCS of the comp this stackobj 
		 * belongs to. It is not known here. 
		 */
		PC = 0;
		)

#ifdef RTDEBUG
    for (theAR =  (struct RegWin *) &theStack->Body[1];
	 theAR != (struct RegWin *) &theStack->Body[theStack->StackSize];
	 PC = theAR->i7 +8, theAR =  (struct RegWin *) (theAR->fp + delta))
#else
    for (theAR =  (struct RegWin *) &theStack->Body[1];
	 theAR != (struct RegWin *) &theStack->Body[theStack->StackSize];
	 theAR =  (struct RegWin *) (theAR->fp + delta))
#endif
      {
	Claim(&theStack->Body[1] <= (long *) theAR
	      && (long *) theAR <= &theStack->Body[theStack->StackSize],
	      "ProcessStackObj: theAR in StackObject");
	ProcessAR(theAR, (struct RegWin *) (theAR->fp + delta));
      }

    DEBUG_STACK(fprintf(output, " *-*-* End StackObject *-*-*\n");
		PC=lastPC;
		)
}
#endif /* sparc */


/****************************** LINUX & NTI **********************************/

#if (defined(linux) || defined(nti))

/* Traverse the StackArea [low..high] and Process all references within it. */
void ProcessStackPart(long *low, long *high)
{
  ptr(long) current = low;
  ref(Object) theObj;
  handle(Object) theCell;
  
  DEBUG_IOA(fprintf(output, "StackPart: [0x%x..0x%x]\n", (int)low, (int)high);
	    fprintf(output, "ComponentBlock/CallbackFrame: [0x%x, 0x%x, 0x%x]\n", 
		    (int)(*(high+1)), (int)(*(high+2)), (int)(*(high+3)));
	    );
  Claim( high <= (long *)StackStart, "ProcessStackPart: high<=StackStart" );
  
  while( current <= high ){
    if( inBetaHeap( (ref(Object))*current)){
      theCell = (handle(Object)) current;
      theObj  = *theCell;
      if( isObject( theObj) ){
	if(inLVRA(theObj)){
	  DEBUG_IOA( fprintf( output, "(STACK(%d) is pointer into LVRA)", current-low));
	}else{
	  ProcessReference( (handle(Object))current);
	  CompleteScavenging();
	}
      } else {
	DEBUG_CODE( if (!isValRep(theObj))
		   fprintf(output, "Suspicious reference on stack: *0x%x=0x%x\n", 
			   (int)current, (int)(*current)) );
      }
    }else{
      /* handle value register objects on the stack ref. ../Asm/DataRegs.s */
      switch( *current){
      case -8: current++;
      case -7: current++;
      case -6: current++;
      case -5: current++;
	break;
#ifdef RTLAZY
      default:
	if (isLazyRef (*current)){
	  /* (*current) is a dangling reference */
	  ProcessReference ((handle(Object))current);
	}
	break;
#endif
      }
    }
    current++;
  }
}

void ProcessStack()
{
    ptr(long)          theTop;
    ptr(long)          theBottom;
    
    ref(CallBackFrame)  theFrame;
    ref(ComponentBlock) currentBlock;
    
    /*
     * First handle the topmost component block
     */
    theTop    = StackEnd;
    theBottom = (ptr(long)) lastCompBlock;
    theFrame  = ActiveCallBackFrame;
    /* Follow the stack */
    while( theFrame){
	ProcessStackPart( theTop, (long *)theFrame-1);
	theTop   = theFrame->betaTop;
	theFrame = theFrame->next;
    }
    ProcessStackPart( theTop, theBottom-1);  
    
    /*
     * Then handle the remaining component blocks.
     */
    currentBlock = lastCompBlock;
    while( currentBlock->next ){
	theTop    = (long *) ((long) currentBlock +
			      sizeof(struct ComponentBlock) );
	theBottom = (long *) currentBlock->next;
	theFrame  = currentBlock->callBackFrame;
	while( theFrame){
	    ProcessStackPart( theTop, (long *)theFrame-1);
	    theTop   = theFrame->betaTop;
	    theFrame = theFrame->next;
	}
	ProcessStackPart( theTop, theBottom-1);  
	currentBlock = currentBlock->next;
    }
}

void ProcessStackObj(theStack)
     struct StackObject *theStack;
{ ptr(long)        stackptr; 
  handle(Object)   theCell; 
  ptr(long)        theEnd;
	    
  DEBUG_IOA( Claim(theStack->StackSize <= theStack->BodySize,
		   "ProcessReference: StackObjectType: Stack > Object") );
	    
  theEnd = &theStack->Body[0] + theStack->StackSize;
	    
  for( stackptr = &theStack->Body[0]; stackptr < theEnd; stackptr++){
    if( inBetaHeap( (ref(Object))*stackptr)){
      theCell = (handle(Object)) stackptr;
      if( isObject( *theCell ) )
	ProcessReference( (handle(Object))stackptr);
    }else{
      switch( *stackptr ){
      case -8: stackptr++;
      case -7: stackptr++;
      case -6: stackptr++;
      case -5: stackptr++;
	break;
#ifdef RTLAZY
      default:
	if (isLazyRef (*stackptr))
	  /* Dangling reference. */
	  ProcessReference ((handle(Object))stackptr);
#endif
      }
    }
  }
}

#endif /* linux & nti */


/***************************** MC680X0 ************************************/

#ifdef mc68020

/* Traverse the StackArea [low..high] and Process all references within it. */
void ProcessStackPart(long *low, long *high)
{
    ptr(long) current = low;
    ref(Object) theObj;
    handle(Object) theCell;
    
    DEBUG_IOA(fprintf(output, "StackPart: [0x%x..0x%x]\n", (int)low, (int)high);
	      fprintf(output, "ComponentBlock/CallbackFrame: [0x%x, 0x%x, 0x%x]\n", 
		      (int)(*(high+1)), (int)(*(high+2)), (int)(*(high+3)));
	      );
    Claim( high <= (long *)StackStart, "ProcessStackPart: high<=StackStart" );
    
    while( current <= high ){
	if( inBetaHeap(cast(Object)(*current))){
	    theCell = (handle(Object)) current;
	    theObj  = *theCell;
	    if( isObject( theObj) ){
		if(inLVRA(theObj)){
		    DEBUG_IOA( fprintf(output, "(STACK(%d) is pointer into LVRA)", 
				       (int)(current-low)));
		}else{
		    ProcessReference(casthandle(Object)current);
		    CompleteScavenging();
		}
	    }
	}else{
	    /* handle value register objects on the stack ref. ../Asm/DataRegs.s */
	    switch( *current){
	      case -8: current++;
	      case -7: current++;
	      case -6: current++;
	      case -5: current++;
		break;
#ifdef RTLAZY
	      default:
		if (isLazyRef (*current))
		  /* (*current) is a dangling reference */
		  ProcessReference (casthandle(Object)current);
		break;
#endif
            }
	}
	current++;
    }
}

void ProcessStack()
{
    ptr(long)          theTop;
    ptr(long)          theBottom;
    
    ref(CallBackFrame)  theFrame;
    ref(ComponentBlock) currentBlock;
    
    /*
     * First handle the topmost component block
     */
    theTop    = StackEnd;
    theBottom = (ptr(long)) lastCompBlock;
    theFrame  = ActiveCallBackFrame;
    /* Follow the stack */
    while( theFrame){
	ProcessStackPart( theTop, (long *)theFrame-1);
	theTop   = theFrame->betaTop;
	theFrame = theFrame->next;
    }
    ProcessStackPart( theTop, theBottom-1);  
    
    /*
     * Then handle the remaining component blocks.
     */
    currentBlock = lastCompBlock;
    while( currentBlock->next ){
	theTop    = (long *) ((long) currentBlock +
			      sizeof(struct ComponentBlock) );
	theBottom = (long *) currentBlock->next;
	theFrame  = currentBlock->callBackFrame;
	while( theFrame){
	    ProcessStackPart( theTop, (long *)theFrame-1);
	    theTop   = theFrame->betaTop;
	    theFrame = theFrame->next;
	}
	ProcessStackPart( theTop, theBottom-1);  
	currentBlock = currentBlock->next;
    }
}

void ProcessStackObj(theStack)
     struct StackObject *theStack;
{ ptr(long)        stackptr; 
  handle(Object)   theCell; 
  ptr(long)        theEnd;
	    
  DEBUG_IOA( Claim(theStack->StackSize <= theStack->BodySize,
		   "ProcessReference: StackObjectType: Stack > Object") );
	    
  theEnd = &theStack->Body[0] + theStack->StackSize;
	    
  for( stackptr = &theStack->Body[0]; stackptr < theEnd; stackptr++){
    if( inBetaHeap(cast(Object)(*stackptr))){
      theCell = (handle(Object)) stackptr;
      if( isObject( *theCell ) )
	ProcessReference(casthandle(Object)stackptr);
    }else{
      switch( *stackptr ){
      case -8: stackptr++;
      case -7: stackptr++;
      case -6: stackptr++;
      case -5: stackptr++;
	break;
#ifdef RTLAZY
      default:
	if (isLazyRef (*stackptr))
	  /* Dangling reference. */
	  ProcessReference (casthandle(Object)stackptr);
#endif
      }
    }
  }
}

#endif /* mc68020 */

/*************************** DEBUG ****************************/

#ifdef RTDEBUG

#ifdef sparc

struct label {
  long address;
  char *id;
};

GLOBAL(long labelOffset) = 0;
GLOBAL(struct label **labels) = 0;
GLOBAL(long numLabels) = 0;

static void initLabels()
{
  char ch;
  char command[200];
  char theLabel[200];
  FILE *thePipe; 
  long labelAddress;

  fprintf(output, "(initLabels ... ");
  fflush(output);

#ifdef sun4s
  (void)sprintf(command,"nm -hxp %s | egrep -v '( f | s | S | b | B )' | sort -r", ArgVector[0]);
#else
  (void)sprintf(command, "nm -grn %s", ArgVector[0]);
#endif

#ifdef DEBUG_LABELS
  fprintf(output, "\n%s:\n", command);
#endif

  /* Find number of labels */
  thePipe = popen (command, "r");

#ifdef SPARC_LD_SEGMENT_TEST
  /* Skip to etext */
  for (;;){
    fscanf(thePipe, "0x%08x %c %s\n", &labelAddress, &ch, theLabel);
    if (labelAddress==(long)&etext) break;
  }
#endif /* SPARC_LD_SEGMENT_TEST */
  numLabels=0;
  for (;;){
    if (fscanf(thePipe, "0x%08x %c %s\n", (int *)&labelAddress, &ch, theLabel) == EOF)
      break;
    numLabels++;
#ifdef DEBUG_LABELS
    fprintf(output, "0x%08x %c %s\n",  (unsigned)labelAddress, ch, theLabel);
    fflush(output);
#endif
  }

  if (! (labels=(struct label **)MALLOC(numLabels * sizeof(struct label *)))) {
    fprintf(output, "Failed to allocate memory for labels\n");
    numLabels = -1;
    labels = 0;
  } else {
    long lastLab=0;
    INFO_ALLOC(numLabels * sizeof(struct label *));

      /* Read into labels */
      pclose (thePipe);
      thePipe = popen (command, "r");
#ifdef SPARC_LD_SEGMENT_TEST
      /* Skip to etext */
      for (;;){
	fscanf(thePipe, "0x%08x %c %s\n", (int *)&labelAddress, &ch, theLabel);
	if (labelAddress==(long)&etext) break;
      }
#endif /* SPARC_LD_SEGMENT_TEST */
      /* Read labels */
      for (;;lastLab++){
	struct label *lab;
	if (fscanf(thePipe, "0x%08x %c %s\n", (int *)&labelAddress, &ch, theLabel) == EOF)
	  break;
	if (! (lab = (struct label *) MALLOC(sizeof(struct label)))){
	  fprintf(output, "Allocation of struct label failed\n");
	  numLabels = -1;
	  /* free previously allocated labels */
	  FREE(labels);
	  labels = 0;
	  break;
	}
	INFO_ALLOC(sizeof(struct label));
	if (! (lab->id = (char *)MALLOC(strlen(theLabel)+1))) {
	  fprintf(output, "Allocation of label id failed\n");
	  numLabels = -1;
	  /* free previously allocated labels */
	  FREE(labels);
	  labels = 0;
	  break;
	}
	INFO_ALLOC(strlen(theLabel)+1);
	lab->address = labelAddress;
	strcpy(lab->id, theLabel);
	labels[lastLab] = lab;
      }
      pclose (thePipe);
    }
  fprintf(output, " done)\n");
  fflush(output);

#ifdef DEBUG_LABELS
  fprintf(output, "Labels:\n");
  { 
    long n;
    for (n=0; n<numLabels; n++){
      fprintf(output, "0x%x\t%s\n", (unsigned)labels[n]->address, labels[n]->id);
    }
  }
  fflush(output);
#endif
}

char *getLabel (addr)
     long addr;
{
  long n;

  if (numLabels==0) initLabels();

  if (!addr){
    labelOffset=0;
    return "<unknown>";
  }

  if (labels){
    for (n=0; n<numLabels; n++){
      if (labels[n]->address <= addr){
	labelOffset = addr-(labels[n]->address);
	return labels[n]->id;
      }
    }
  }
  labelOffset=0;
  return "<unknown>";
}

void PrintRef(ref(Object) ref)
{
  if (ref) {
    if (inBetaHeap(ref) && isObject(ref) ){
      fprintf(output, ", is object");
      if (isProto((ref)->Proto)){
	fprintf(output, ", proto ok: 0x%x (", 
		(int)ref->Proto);
	DescribeObject(ref);
	fprintf(output, ")");
      } else {
	fprintf(output, ", proto NOT ok: 0x%x", (int)ref->Proto);
      }
    } else {
      fprintf(output, ", is NOT object");
#ifdef SPARC_LD_SEGMENT_TEST
      if (isCode(ref) && (((int)ref & 3) == 0)) fprintf(output, " (is code)");
      if (isData(ref)) fprintf(output, " (is data)");
#endif /* SPARC_LD_SEGMENT_TEST */
    }
  }
  fprintf(output, "\n");
}

void PrintCAR(struct RegWin *cAR)
{
  fprintf(output, 
	  "\n----- C AR: 0x%x, end: 0x%x, PC: 0x%x (%s+0x%x)\n",
	  (int)cAR, 
	  (int)cAR->fp,
	  (int)PC,
	  getLabel(PC),
	  (int)labelOffset);
}

void PrintAR(struct RegWin *ar, struct RegWin *theEnd)
{
  struct Object **theCell = (struct Object **) &ar[1];

  fprintf(output, 
	  "\n----- AR: 0x%x, theEnd: 0x%x, PC: 0x%x (%s+0x%x)\n",
	  (int)ar, 
	  (int)theEnd,
	  (int)PC,
	  getLabel(PC),
	  (int)labelOffset);

  fprintf(output, "%%i0: 0x%x", (int)ar->i0); PrintRef(cast(Object)ar->i0);
  fprintf(output, "%%i1: 0x%x", (int)ar->i1); PrintRef(cast(Object)ar->i1)
    /* Notice that CopyT, AlloVR1-4 gets an offset in this parameter.
     * This should be safe.
     */;
  fprintf(output, "%%i2: 0x%x", (int)ar->i2); PrintRef(cast(Object)ar->i2);
  fprintf(output, "%%i3: 0x%x", (int)ar->i3); PrintRef(cast(Object)ar->i3);
  fprintf(output, "%%i4: 0x%x", (int)ar->i4); PrintRef(cast(Object)ar->i4);

  fprintf(output, "stackpart:\n");
  /* Notice that in INNER some return adresses are pushed. This is no
   * danger.
   */
  for (; theCell != (struct Object **) theEnd; theCell+=2) {
    fprintf(output, "0x%x", (int)(*theCell));
    PrintRef(cast(Object)(*theCell));
  }
  fflush(output);
}

/* PrintStack.
 * Should probably not be called during GC. Instead, you may set DebugStack to
 * TRUE before calling IOAGc()
 */
void PrintStack()
{
  struct RegWin *theAR;
  struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
  struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
  struct RegWin *end;
  
  /* Flush register windows to stack */
  __asm__("ta 3");
  
  fprintf(output, "\n ***** Trace of stack *****\n");
  
  end  = (struct RegWin *)StackPointer;
  /* end points to the activation record of PrintStack() */
  PC=((struct RegWin *) end)->i7 +8;
  end = (struct RegWin *)((struct RegWin *) end)->fp; /* Skip AR of PrintStack() */

  for (theAR =  (struct RegWin *) end;
       theAR != (struct RegWin *) 0;
       PC = theAR->i7 +8, theAR = (struct RegWin *) theAR->fp) {
    if (theAR == nextCompBlock) {
      /* This is the AR of attach. Continue, but get
       * new values for nextCompBlock and nextCBF. 
       * Please read StackLayout.doc
       */
      nextCBF = (struct RegWin *) theAR->l5;
      nextCompBlock = (struct RegWin *) theAR->l6;
      if (nextCompBlock == 0)
	break; /* we reached the bottom */
    } else {
      if (theAR == nextCBF) {
	/* This is AR of HandleCB. Skip this and
	 * skip to betaTop and update nextCBF
	 */
	    nextCBF = (struct RegWin *) theAR->l5;

	    DEBUG_STACK({ /* Wind down the stack until betaTop is reached */
			  struct RegWin *cAR;
			  for (cAR = theAR;
			       cAR != (struct RegWin *) theAR->l6;
			       PC = cAR->i7 +8, cAR = (struct RegWin *) cAR->fp)
			    PrintCAR(cAR);
			});

	    theAR = (struct RegWin *) theAR->l6; /* Skip to betaTop */
      }
    }
    PrintAR(theAR, (struct RegWin *) theAR->fp);
  }
   
  fprintf(output, " *****  End of trace  *****\n");
  
}

#endif /* sparc */

#endif /* RTDEBUG */

#endif /* MT */
