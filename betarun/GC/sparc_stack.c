/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * stack.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann and S|ren Brandt
 *
 * Traverse an stack parts and process all references.
 */

#include "beta.h"

#ifdef RTDEBUG
#include <ieeefp.h>
#define FPU_ZERODIVISION  FP_X_DZ
#define FPU_INVALID       FP_X_INV
#define FPU_DENORMALIZED  0
#define FPU_OVERFLOW      FP_X_OFL
#define FPU_UNDERFLOW     FP_X_UFL
#define FPU_PRECISIONLOST FP_X_IMP
#define EnableFPUexceptions(mask) fpsetmask(mask)
#define DisableFPUexceptions() fpsetmask(0)
#endif /* RTDEBUG */

#ifndef MT

extern void (*StackRefAction)(REFERENCEACTIONARGSTYPE);

#include "../CRUN/crun.h"
#define MAXDATAREGSONSTACK 64 /* FIXME: Is this sufficient? --mg */

#ifdef RTDEBUG
static RegWin *BottomAR=0 /* Currently never set up - use StackStart? */;
static RegWin *lastAR=0;
pc_t frame_PC = 0;
static void PrintAR(RegWin *ar, RegWin *theEnd);
static void PrintCAR(RegWin *cAR);
#endif

/* ProcessStackCell:
 * Called for each GC register in the register window and stack part.
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
  if (IsBetaCodeAddrOfProcess((pc_t)addr)) {
    return;
  } else if (strongIsObject(*(Object **)addr)) {
    func((Object **)addr, *(Object **)addr);
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

  for (; theCell != (long*)theEnd; theCell+=2) {
    /* +2 because the compiler uses "dec %sp,8,%sp" before pushing */

    /* Test for tagged data regs on stack. The compiler may push
     * floating point and busy %o-registers. If so it has
     * pushed a tag constructed as tag = -(n*2+4), where n is the number of
     * 8-byte stack-cells to skip. 
     * So n*2+2 longs should be skipped by GC (skipping the tag too).
     * Since for-loop skips 2 after continue, skip n*2 = -tag-4 longs.
     */
    int tag = (int)*theCell /* potential tag */;
    if (tag <= -4
#if MMAPANYADDR
	&& -MAXDATAREGSONSTACK-4 <= tag
#endif
	) {
      if ((int)(theCell+(-tag-2)) > (int)(ar->fp)) {
	/* Skip would be out of frame */
	DEBUG_CODE({
	  fprintf(output, "Attempt to skip out of frame!\n");
	  ILLEGAL;
	});
      } else {
	/* Do the skip */
	theCell += -tag-4;
	continue;
      }
    }

    /* (Maybe build a more descriptive description using sprintf) */
    ProcessStackCell(theCell, "stackpart", func);
  }
}

/* ProcessSPARCStack:
 *  Precondition: 
 *     1. Register windows must be flushed to stack - asm(ta 3)
 *     2. StackEnd must point to top of stack part that is to be GC'ed.
 *     3. If RTDEBUG, frame_PC must be PC corresponding to frame that
 *        ends in StackEnd.
 */

void
GeneralProcessStack(CellProcessFunc func)
{
   RegWin *theAR;
   RegWin *nextCBF = (RegWin *) ActiveCallBackFrame;
   RegWin *nextCompBlock = (RegWin *) lastCompBlock;
    
   DEBUG_STACK(fprintf(output, "\n ***** Trace of stack *****\n"));
   DEBUG_STACK(fprintf(output,
                       "IOA: 0x%x, IOATop: 0x%x, IOALimit: 0x%x\n",
                       (int)GLOBAL_IOA, (int)GLOBAL_IOATop, (int)GLOBAL_IOALimit));

   for (theAR =  (RegWin *) StackEnd;
        theAR != (RegWin *) 0;
#ifdef RTDEBUG
        frame_PC = (pc_t)(theAR->i7 + 8),
#endif
	   theAR = (RegWin *) theAR->fp) {
      
      DEBUG_STACK({
         fprintf(output, 
                 "\n *** theAR=0x%08x, nextCompBlock=0x%08x, lastCompBlock=0x%08x) ***\n",
                 (int)theAR,
                 (int)nextCompBlock,
                 (int)lastCompBlock);});
      if (theAR == nextCompBlock) {
         /* This is the AR of attach. Continue GC, but get
          * new values for nextCompBlock and nextCBF. 
          * Please read StackLayout.doc
          */
         DEBUG_STACK(fprintf(output, " *** Passing Attach ***\n"));
         nextCBF = (RegWin *) theAR->l5;
         nextCompBlock = (RegWin *) theAR->l6;
         if (nextCompBlock == 0){
            DEBUG_STACK({
               fprintf(output, 
                       " *** reached the bottom (theAR=0x%08x, theAR->l6=0x%08x) ***\n",
                       (int)theAR,
                       (int)theAR->l6);});
            break; /* we reached the bottom */
         }
      } else {
         if (theAR == nextCBF) {
            /* This is AR of HandleCB. Don't GC this, but
             * skip to betaTop and update nextCBF */
            nextCBF = (RegWin *) theAR->l5;
            DEBUG_STACK({ 
               fprintf(output, 
                       "Met frame of HandleCB at SP=0x%08x, %%l5=0x%08x, %%l6=0x%08x.\n",
                       (int)theAR,
                       (int)theAR->l5,
                       (int)theAR->l6
                       );
               if (valhallaID || isHandlingException) {
                  fprintf(output, "Cannot wind down past signal handler.\n");
                  fprintf(output, "Skipping directly to SP=0x%x.\n", (int)theAR->l6);
               } else {
                  /* Wind down the stack until betaTop is reached */
                  RegWin *cAR;
                  fprintf(output, "Winding down to frame with %%fp=betatop (0x%x)",(int)theAR->l6);
                  fprintf(output, " (BetaStackTop)\n");
                  for (cAR = theAR;
                       cAR != (RegWin *) theAR->l6;
                       frame_PC = (pc_t)(cAR->i7 + 8), cAR = (RegWin *) cAR->fp){
                     if (!cAR) {
                        fprintf(output, "ProcessStack: gone past _start - exiting...!\n");
                        ILLEGAL;
                        BetaExit(1);
                     }
                     PrintCAR(cAR);
                  }
               }
            });
            theAR = (RegWin *) theAR->l6; /* Skip to betaTop */
         }
      }
      ProcessAR(theAR, (RegWin *) theAR->fp, func);
      DEBUG_CODE(lastAR = theAR);
   }
   DEBUG_CODE(if (BottomAR) Claim(lastAR==BottomAR, "lastAR==BottomAR"));
   DEBUG_STACK(fprintf(output, " *****  End of trace  *****\n"));
}

#ifdef RTDEBUG
GLOBAL(pc_t lastPC)=0;
#endif

/* ProcessSPARCStackObj */
void
ProcessStackObj(StackObject *sObj, CellProcessFunc func)
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
      PrintCodeAddress((pc_t)func);
      fprintf(output, "\n");
      fprintf(output, "StackRefAction is 0x%x", (int)StackRefAction);
      PrintCodeAddress((pc_t)StackRefAction);
      fprintf(output, "\n");
      
      lastPC=frame_PC;
      /* The PC of the topmost AR is saved in CallerLCS of the comp 
       * this stackobj belongs to. It is not known here. 
       */
      frame_PC = 0;
    });
    DEBUG_CODE(if (DebugStackObj){
      DebugStack=TRUE;
    } else {
      DebugStack=FALSE;
    });

    if (!sObj->StackSize) {
      /* OK - can happen in gc triggered by AlloSO */
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
	DEBUG_CODE(frame_PC = (pc_t)(theAR->i7 + 8));
      }

    DEBUG_STACKOBJ(fprintf(output, " *-*-* End StackObject 0x%x *-*-*\n", (int)sObj);
		   frame_PC=lastPC;
		   );
    DEBUG_CODE(DebugStack=oldDebugStack);
}


/************* beta.dump/valhalla/exception stuff below **************/

void DisplayAR(RegWin *theAR, pc_t pc, CellDisplayFunc func)
{
  Object *prevObj /* used for last successfully identified object */;

  TRACE_DUMP({
    fprintf(output, 
	    "\n\n>>>TraceDump: DisplayAR: [%%sp=0x%x..%%fp=0x%x[, %%i0: 0x%x, PC: 0x%x", 
	    (int)theAR, 
	    (int)theAR->fp, 
	    (int)theAR->i0, 
	    (int)pc);
    if (!SimpleDump) PrintCodeAddress(pc);
    fprintf(output, "\n");
  });

  /* Handle current object in this frame */
  prevObj  = (Object *) theAR->i0;
  if (inBetaHeap(prevObj) && isObject(prevObj)){
    if (!isComponent(prevObj) && IsComponentItem(prevObj)){
      prevObj = (Object*)EnclosingComponent(prevObj);
      TRACE_DUMP({
	fprintf(output, 
		">>>TraceDump: DisplayAR: Current object is item of component 0x%x\n", 
		(int)prevObj);
      });
    } 
    func(pc, prevObj);
  }

  TraverseSparcStackPart(theAR, prevObj, func);
  
}

void TraverseSparcStackPart(RegWin *theAR, Object* prevObj, CellDisplayFunc func)
{

  long* this, *end;
  pc_t pc;

  /* handle possible pushed PCs (%o7s) in the
   * stackpart (INNER call chains).
   * In case of INNER P, the previous current object has been
   * pushed before the code address.
   */
  this = (long *) (((long)theAR)+sizeof(RegWin));
  end  = (long *) (((long)theAR->fp));
  TRACE_DUMP({
    if (this<end){
      fprintf(output, 
	      ">>>TraceDump: DisplayAR: stackpart is [0x%x..0x%x[\n", 
	      (int)this, 
	      (int)end);
    } else {
      fprintf(output, 
	      ">>>TraceDump: DisplayAR: no stackpart (this=0x%x, end=0x%x)\n",
	      (int)this,
	      (int)end);
    }
  });
  while (this<end) {
    TRACE_DUMP({
      fprintf(output, 
	      ">>>TraceDump: DisplayAR: stackpart 0x%08x: 0x%08x\n", 
	      (int)this, 
	      (int)this[0]);
    });

    /* Test for floating point regs on stack. See comment in ProcessAR */
    {
      int tag = (int)*this;
      if ( (-(2*16+4)<=tag) && (tag<=-4) ){
	DEBUG_CODE({
	  fprintf(output, 
		  "Skipping %d saved floating points regs.\n", 
		  (-tag-4)/2);
	});
	if ( (int)(this+(-tag-4)) >= (int)(theAR->fp) ){
	  /* Skip would be out of frame */
	  DEBUG_CODE({
	    fprintf(output, 
		    "NO: not skipping anyway: skip would be out of frame!.\n");
	  });
	} else {
	  this += -tag-4;
	}
      }
    }

    pc = (pc_t)(this[0]);
    if (isCode(pc)) {
      /* isCode is a real macro on sparc. So now we know that
       * a code address has been pushes in the stack part.
       * Add 2 (8 bytes) to get the real SPARC return address.
       */
      pc+=2;
      TRACE_DUMP({
	fprintf(output, 
		">>>TraceDump: DisplayAR: PC 0x%x\n",
		(int)pc);
      });
      if ((this+2<end) && inBetaHeap((Object*)this[2]) && isObject((Object*)this[2])) {
	/* There was an object, assumed to be from an INNER P */
	prevObj = (Object*)this[2];
	TRACE_DUMP({
	  fprintf(output, 
		  ">>>TraceDump: DisplayAR: stackpart 0x%08x: 0x%08x INNER P object\n", 
		  (int)(this+2), 
		  (int)prevObj);
	});
	if (!isComponent(prevObj) && IsComponentItem(prevObj)){
	  prevObj = (Object*)EnclosingComponent(prevObj);
	  TRACE_DUMP({
	    fprintf(output,
		    ">>>TraceDump: DisplayAR: object is item of component 0x%x\n",
		    (int)prevObj);
	  });
	} 
	func(pc, prevObj);
	this+=2; /* Skip the object */
      } else {
	/* No Object below the code. Display with the previous
	 * found object.
	 */
	func(pc, prevObj);
      }
    }
    this+=2;
  }
}

void DisplaySPARCStack(BetaErr errorNumber, 
		       Object *theObj, 
		       pc_t thePC, 
		       long theSignal)
{
  /* FIXME: Could possibly use ProcessSPARCStack with suitable CellProcessFunc */
  RegWin *theAR;
  RegWin *nextCBF = (RegWin *) ActiveCallBackFrame;
  RegWin *nextCompBlock = (RegWin *) lastCompBlock;
  pc_t pc=thePC;
  
  /* Flush register windows to stack */
  __asm__("ta 3");

  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackEnd:   0x%x\n", (int)StackEnd));
  TRACE_DUMP(fprintf(output, ">>>TraceDump: StackStart: 0x%x\n", (int)StackStart));

  theAR = (RegWin *) StackEnd;

  /* First check for errors occured outside BETA and wind down
   * to BETA part of stack, if possible.
   */
  if (!IsBetaCodeAddrOfProcess(pc)){
    fprintf(output, 
	    "  [ EXTERNAL ACTIVATION PART (address 0x%x", 
	    (int)pc);
    if (!SimpleDump) PrintCodeAddress(error_pc);
    fprintf(output, ") ]\n");

    TRACE_DUMP(fprintf(output, "  Winding back through C frames on top\n"));
    for (pc = (pc_t)theAR->i7, theAR = (RegWin *) theAR->fp;
	 !IsBetaCodeAddrOfProcess(pc);
	 pc = (pc_t)theAR->i7, theAR = (RegWin *) theAR->fp){
      if (!SimpleDump) {
	fprintf(output, "  { PC  0x%x", (int)pc);
	if (!SimpleDump) PrintCodeAddress(pc);
	fprintf(output, " }\n");
      }
      if ((theAR->fp==0) || (theAR->fp==StackStart) || (pc == 0)){
	TRACE_DUMP({
	  fprintf(output, 
		  "Wierd: Did not find any BETA frames... At theAR=0x%x\n",
		  (int)theAR);
	});
	return;
      }
    }
    TRACE_DUMP(fprintf(output, "  Winding through frames on top done."));
  }

  for (;
       theAR != (RegWin *) 0;
       pc = (pc_t)theAR->i7, theAR =  (RegWin *) theAR->fp) {
    /* PC is execution point in THIS frame. The update of PC
     * in the for-loop is not done until it is restarted.
     */
    TRACE_DUMP(fprintf(output, ">>>TraceDump: DisplaySPARCStack: theAR->fp: 0x%x\n", (int)theAR->fp));
    if (theAR->fp == (long)nextCBF) {
      /* This is AR of the code stub (e.g. <foo>) called from HandleCB. 
       * Don't display objects in this, but skip to betaTop and update 
       * nextCBF 
       */
      RegWin *cAR;

      TRACE_DUMP(fprintf(output, "  cb: "));
      fprintf( output,"  [ EXTERNAL ACTIVATION PART ]\n");
      /* Wind down the stack until betaTop is reached.
       * This is only done to update PC in order to get the PC
       * for the first frame before the callback.
       */
      TRACE_DUMP(fprintf(output, 
			 "  Winding back to 0x%x", 
			 (int)((RegWin *)theAR->fp)->l6
			 ));
      for (cAR = theAR;
	   cAR != (RegWin *)((RegWin *)theAR->fp)->l6;
	   pc = (pc_t)cAR->i7, cAR = (RegWin *) cAR->fp){
	if (!SimpleDump) {
	  fprintf(output, "  { PC  0x%x", (int)pc);
	  PrintCodeAddress(pc);
	  fprintf(output, " }\n");
	}
      }
      nextCBF = (RegWin*) ((RegWin*)(theAR->fp))->l5;
      theAR   = (RegWin*) ((RegWin*)(theAR->fp))->l6;
      TRACE_DUMP(fprintf(output, "  Winding done."));
    }
    if (theAR == nextCompBlock) {
      /* This is the AR of attach. Continue, but get
       * new values for nextCompBlock and nextCBF. 
       * Please read StackLayout.doc
       */
      nextCBF = (RegWin *) theAR->l5;
      nextCompBlock = (RegWin *) theAR->l6;
      
      if (nextCompBlock == 0){ 
	/* We reached the bottom */
	TRACE_DUMP({
	  fprintf(output, 
		  ">>>TraceDump: reached frame of AttBC at SP=0x%x\n", 
		  (int)theAR);
	});
	break;
      }
      
      TRACE_DUMP({
	fprintf(output, 
		">>>TraceDump: reached frame of Att at SP=0x%x\n", 
		(int)theAR);
      });
      continue;
    } 
    /* Normal frame */
    DisplayAR(theAR, pc, DisplayCell);
  }
  return;
}

typedef struct ComponentStack {
  Component *comp; /* The component */
  int stacktype;          /* One of CS_*   */
  pc_t returnAdr;         /* The address to return to when this component 
			   * starts running the next time. */
  union {
    struct { /* if stacktype==CS_PROCESSORSTACK or CS_ACTIVECOMPONENT: */
      /* FirstAR is the largest address that is not part of the stack of comp.
       * lastAR is the least RegWin that *is* part of the stack, i.e. the 
       * StackEnd for this component stack. Notice that the stack grows 
       * downwards. 
       * I.e. to scan the stack, scan from (and including) lastAR to firstAR.
       * activeCBF is the active callback frame of this component.
       */
      RegWin* firstAR;
      RegWin* lastAR;
      RegWin* activeCBF;
    } if_onstack;
    /* if stacktype==CS_STACKOBJ: */
    StackObject *stackObj; 
  } info;
} ComponentStack;

/* findComponentStack (SPARC)
 *
 * Fills in the structure compStack. compStack->comp should point to a 
 * component object. PC is expected to be the current BETA PC, and is
 * used to set compStack->returnAdr in case compStack->comp is the
 * active component.
 *
 * The implementation of findComponentStack assumes that it has been called
 * via some other runtime routine that correctly set up the StackEnd
 * variable to point to the top of the current BETA stack. This is
 * e.g. the case with BetaError or BetaSignalHandler.
 * ========================== 
 */

static void findComponentStack (ComponentStack* compStack, pc_t pc)
{ 
  RegWin *thisCompBlock = (RegWin *) lastCompBlock;
  RegWin *prevCompBlock = 0;
  Component *thisComponent = ActiveComponent;

  DEBUG_VALHALLA(fprintf (output,"Entering findComponentStack (SPARC)\n"));

  while (thisCompBlock) {
    if (compStack->comp == thisComponent){
      /* comp found on processor stack. */
      
      compStack->info.if_onstack.firstAR 
	= (RegWin *) thisCompBlock/*->fp (pa/gram 07/01/2000)*/;
      
      if (prevCompBlock) { 
	
	compStack->stacktype = CS_PROCESSORSTACK; 
	compStack->info.if_onstack.lastAR
	  = (RegWin *) prevCompBlock->fp;
	compStack->returnAdr = thisComponent->CallerLSC;
	compStack->info.if_onstack.activeCBF 
	  = (RegWin *) prevCompBlock->l5;

      } else {
	/* comp is the active component. */

	compStack->stacktype = CS_ACTIVECOMPONENT;
	compStack->info.if_onstack.lastAR = (RegWin *) StackEnd;

	compStack->info.if_onstack.activeCBF 
	  = (RegWin *) ActiveCallBackFrame;
	compStack->returnAdr = pc;
	
      }
      DEBUG_VALHALLA(fprintf (output,"Leaving findComponentStack. Stacktype = %d\n",compStack->stacktype));
      return;
    } else {
      prevCompBlock = thisCompBlock;
      thisCompBlock = (RegWin *) thisCompBlock->l6; /* See SparcDoc.c */
      thisComponent = thisComponent->CallerComp;
    }
  }

  /* Component not found on the processor stack.
   * If the component has ever been attached and suspended, it should have
   * been assigned a stack object.
   * Otherwise it has no stack at all. */

  switch ((int) (compStack->info.stackObj = compStack->comp->StackObj)) {
  case 0:
  case -1:
    compStack->stacktype = CS_NOSTACK;
    compStack->returnAdr = 0;
    break;
  default:
    compStack->stacktype = CS_STACKOBJ;
    compStack->returnAdr = compStack->comp->CallerLSC;
    break;
  }
  DEBUG_VALHALLA(fprintf (output,"Leaving findComponentStack. Stacktype = %d\n",compStack->stacktype));
}


int scanComponentStack (Component* comp,
			Object *curObj,
			pc_t pc,
			CellDisplayFunc forEach)
{ 
  struct ComponentStack compStack;
#ifndef RTDEBUG
  pc_t frame_PC;
#endif

  compStack.comp = comp;

  DEBUG_VALHALLA(fprintf (output,"Entering scanComponentStack. \n"));

  findComponentStack (&compStack,pc);

  DEBUG_VALHALLA(fprintf (output,"FindComponentStack done. stacktype = %d. \n",compStack.stacktype));

  switch (compStack.stacktype) {
  case CS_NOSTACK: 
    break;
  case CS_STACKOBJ:
    { StackObject *theStack = compStack.info.stackObj;
      RegWin *theAR;
      
      /* ASSUMES THAT THERE ARE NO CALLBACK FRAMES IN A COMPONENT OBJECT.
       * IF THIS CHANGES, SO SHOULD THE CODE BELOW. */
      
      /* Start at theStack->Body[1], since theStack->Body[0] 
       * is saved FramePointer */
      long delta = (char *) &theStack->Body[1] - (char *) theStack->Body[0];
      frame_PC = compStack.returnAdr; 
      
      for (theAR =  (RegWin *) &theStack->Body[1];
	   theAR != (RegWin *) &theStack->Body[theStack->StackSize];
	   theAR =  (RegWin *) (theAR->fp + delta))
	{
	  DisplayAR(theAR, frame_PC, forEach);
	  frame_PC = (pc_t)(theAR->i7+8);
	}
    };
    break;
  case CS_PROCESSORSTACK:
  case CS_ACTIVECOMPONENT:
    { RegWin *theAR = compStack.info.if_onstack.lastAR;
      RegWin *nextCBF = compStack.info.if_onstack.activeCBF;
      frame_PC = compStack.returnAdr;

      /* Scan machine stack like ProcessSPARCStack.
       *  Precondition: 
       *     1. Register windows must be flushed to stack - asm(ta 3)
       *     2. StackEnd must point to top of stack part that is to be GC'ed.
       *     3. If RTDEBUG, frame_PC must be PC corresponding to frame that
       *        ends in StackEnd.
       */
      __asm__("ta 3");

      if (pc && !IsBetaCodeAddrOfProcess(pc)){
	DEBUG_VALHALLA(fprintf(output,"BetaStackTop = 0x%08x\n",(int)BetaStackTop));
	/* Skip external code on top of stack: */
	while ((unsigned int) theAR < (unsigned int) BetaStackTop) {
	  DEBUG_VALHALLA(fprintf(output,"External return address: "));
	  forEach (frame_PC,0);
	  frame_PC = (pc_t)(theAR->i7 + 8);
	  theAR = (RegWin *) theAR->fp;
	}
      }
      
      for (;
	   theAR != compStack.info.if_onstack.firstAR;
	   theAR = (RegWin *) theAR->fp){
	DEBUG_STACK({
	  PrintAR(theAR, (RegWin*)theAR->fp); 
	  fprintf(output, "nextCBF=0x%08x\n", (int)nextCBF);
	});
	if (theAR == nextCBF) {
	  /* This is AR of HandleCB. Skip this and
	   * skip to betaTop and update nextCBF
	   */
	  nextCBF = (RegWin *) theAR->l5;

	  DEBUG_STACK({ 
	    fprintf(output, 
		    "Met frame of HandleCB at SP=0x%08x, %%l5=0x%08x, %%l6=0x%08x.\n",
		    (int)theAR,
		    (int)theAR->l5,
		    (int)theAR->l6
		    );
	  });

	  if (isHandlingException
#ifdef RTVALHALLA
	      || valhallaID
#endif
	      ) {
	    DEBUG_STACK({
	      fprintf(output, "Cannot wind down past signal handler.\n");
	      fprintf(output, "Skipping directly to SP=0x%x.\n", (int)theAR->l6);
	    });
	    frame_PC = 0;
	  } else {
	    /* Wind down the stack until betaTop is reached */
	    RegWin *cAR;
	    DEBUG_STACK({
	      fprintf(output, 
		      "Winding down to frame with %%fp=betatop (0x%x)",
		      (int)theAR->l6);
	      fprintf(output, " (BetaStackTop)\n");
	    });
	    for (cAR = theAR;
		 cAR != (RegWin *) theAR->l6;
		 frame_PC = (pc_t)(cAR->i7 + 8), cAR = (RegWin *) cAR->fp){
	      if (!cAR) {
		fprintf(output, "scanComponentStack: gone past _start - exiting...!\n");
		ILLEGAL;
		BetaExit(1);
	      }
	      DEBUG_STACK(PrintCAR(cAR));
	    }
	  }
	  theAR = (RegWin *) theAR->l6; /* Skip to betaTop */
	}
	DisplayAR(theAR, frame_PC, forEach);
	frame_PC = (pc_t)(theAR->i7 + 8);
      };
      break;
    }
  }
  return compStack.stacktype;
}

#ifdef RTDEBUG
void PrintCAR(RegWin *cAR)
{
  char *lab = getLabel(frame_PC);
  fprintf(output, 
	  "\n----- C AR: 0x%x, end: 0x%x, PC: 0x%x <%s+0x%x>\n",
	  (int)cAR, 
	  (int)cAR->fp,
	  (int)frame_PC,
	  lab,
	  (int)labelOffset);
  fprintf(output, "%%fp: 0x%x\n", (int)cAR->fp); 
}

void PrintAR(RegWin *ar, RegWin *theEnd)
{
  Object **theCell = (Object **) &ar[1];
  char *lab = getLabel(frame_PC);

  fprintf(output, 
	  "\n----- AR(%%sp): 0x%x, theEnd(%%fp): 0x%x, PC: 0x%x <%s+0x%x>\n",
	  (int)ar, 
	  (int)theEnd,
	  (int)frame_PC,
	  lab,
	  (int)labelOffset);

  fprintf(output, "%%i0: "); PrintObject((Object *)ar->i0);
  fprintf(output, "\n");
  fprintf(output, "%%i1: "); PrintObject((Object *)ar->i1)
    /* Notice that CopyT, AlloVR1-4 gets an offset in this parameter.
     * This should be safe.
     */;
  fprintf(output, "\n");
  fprintf(output, "%%i2: "); PrintObject((Object *)ar->i2);
  fprintf(output, "\n");
  fprintf(output, "%%i3: "); PrintObject((Object *)ar->i3);
  fprintf(output, "\n");
  fprintf(output, "%%i4: "); PrintObject((Object *)ar->i4);
  fprintf(output, "\n");
  fprintf(output, "%%fp: 0x%x\n", (int)ar->fp); 
  fprintf(output, "%%l5: 0x%x\n", (int)ar->l5); 
  fprintf(output, "%%l6: 0x%x\n", (int)ar->l6); 

  /* Now do the stack part */
  fprintf(output, "stackpart:\n");
  /* Notice that in INNER some return adresses are pushed. This is no
   * danger. These will be identified as code addresses in the debug output.
   */
  for (; theCell != (Object **) theEnd; theCell+=2) {
    /* Test for floating point regs on stack. See comment in ProcessAR */
    int tag = (int)*theCell /* potential tag */;
    if (tag <= -4
#if MMAPANYADDR
	&& -MAXDATAREGSONSTACK-4 <= tag
#endif
	) {
      if ((int)(theCell+(-tag-2)) > (int)(ar->fp)) {
	/* Skip would be out of frame */
	fprintf(output, 
		"0x%08x: %d: NOT skipping %d 8-byte cells: skip would be out of frame! (%%fp=0x%08x).\n",
		(int)theCell,
		tag,
		(-tag-4)/2,
		(int)(ar->fp));
	ILLEGAL;
      } else {
	long *ptr;
	unsigned long oldmask = DisableFPUexceptions();
	fprintf(output, 
		"0x%08x: %d: Skipping tag and %d 8-byte stack cells:\n", 
		(int)theCell,
		tag,
		(-tag-4)/2);
	for (ptr = (long*)(theCell+2); 
	     ptr < (long *)(theCell+(-tag-2));
	     ptr++){
	  fprintf(output, "0x%08x: %8d %8.4g", (int)ptr, *(int*)ptr, *(float*)ptr);
	  if (((long)ptr)%8 == 0){
	    fprintf(output, "%8.8g\n", *(double*)ptr);
	  } else {
	    fprintf(output, "\n");
	  }
	}
	EnableFPUexceptions(oldmask);
	/* Do the skip  */
      	theCell += (-tag-4);
	continue;
      }
    }
    fprintf(output, "0x%08x: ", (int)theCell);
    PrintObject((Object *)(*theCell));
    fprintf(output, "\n");
  }
  fflush(output);
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
  frame_PC=(pc_t)(((RegWin *) end)->i7 + 8);
  end = (RegWin *)((RegWin *) end)->fp; /* Skip AR of PrintStack() */

  for (theAR =  (RegWin *) end;
       theAR != (RegWin *) 0;
       frame_PC = (pc_t)(theAR->i7 + 8), theAR = (RegWin *) theAR->fp) {
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
	       frame_PC = (pc_t)(cAR->i7 + 8), cAR = (RegWin *) cAR->fp)
	    PrintCAR(cAR);
	});
	
	theAR = (RegWin *) theAR->l6; /* Skip to betaTop */
      }
    }
    PrintAR(theAR, (RegWin *) theAR->fp);
  }
   
  fprintf(output, " *****  PrintStack: End of trace  *****\n");
  
}
#endif /* RTDEBUG */

#endif /* MT */
