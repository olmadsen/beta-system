/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-1992 Mjolner Informatics Aps.
 * stack.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"
#ifdef sparc
#include "../CRUN/crun.h"
#endif

#ifdef hpux
/* #include <sys/cache.h> */
#endif

#ifdef hppa
/***************************** SNAKE ****************************/

void ProcessRefStack(size, bottom)
     unsigned size; /* number of pointers to process */
     long **bottom;
{
  long i;
  struct Object **theCell;
  struct Object *theObj;

  DEBUG_IOA(printf("RefStk: [%x .. %x]\n", (long)bottom, (long)(bottom+size)));
  theCell = (struct Object **)bottom;
  for(; size > 0; size--, theCell++) {
    i = ((unsigned)*theCell & 1) ? 1 : 0;
    *theCell = (struct Object *)((unsigned)*theCell & ~1);
    theObj = *theCell;
    if(theObj && inBetaHeap(theObj) && isObject(theObj)) {
      if( inLVRA( theObj)){
        DEBUG_IOA( fprintf( output, "(STACK(%x) is *ValRep)", theCell));
      } else {
        ProcessReference(theCell);
        CompleteScavenging();
      }
    }
    if(i) *theCell = (struct Object *)((unsigned)*theCell | 1);
  }
}

void ProcessStack()
{
  struct SnakeSF *top;

  ref(CallBackFrame)  frm;
  ref(ComponentBlock) cur;

  ProcessRefStack(((unsigned)getRefSP()-(unsigned)&ReferenceStack[0]) >> 2,
                  &ReferenceStack[1]);
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
  ptr(long)        stackptr;
  ptr(long)        theEnd;

  DEBUG_IOA(printf("ProcessStackObj()\n"));

  DEBUG_IOA( Claim(theStackObject->StackSize <= theStackObject->BodySize,
                   "ProcessReference: StackObjectType: Stack > Object") );

  theEnd = &theStackObject->Body[0] + theStackObject->StackSize;

  ProcessRefStack(*theEnd, theEnd+1);
}

#endif /* hppa */
/*************************** SPARC *********************************/
#ifdef sparc
/* Traverse an activation record (AR) [ar, end[
   Notice end is *not* included
   */

/* Don't process references from the stack to LVRA. The ValReps in
 * in LVRA are not moved by CopyObject, but if PrecessReference
 * is called with such a reference, the LVRA cycle is broken!
 */
# define objIsValRep(theObj) inLVRA(theObj)

void ProcessAR(struct RegWin *ar, struct RegWin *end)
{
    struct Object **theCell = (struct Object **) &ar[1];
    
    DEBUG_IOA (fprintf(output, "***** ProcessAR: ar: 0x%x, end: 0x%x\n", ar, end);
	       fflush(output);
	       )
    DEBUG_CODE(Claim((long)ar < (long)end,   "ProcessAR: ar is less than end");
	       Claim(((long) end) % 4 == 0, "ProcessAR: end is 4 byte aligned");
	       Claim(((long) end) % 4 == 0, "ProcessAR: end is 4 byte aligned");
	       )
        
    /* Process GC registers of the activation record. */
    DEBUG_IOA(if (inBetaHeap(ar->i0) && objIsValRep(cast(Object)(ar->i0)))
	      fprintf(output, "ProcessAR: ar->i0 (0x%x) is *ValRep\n", ar->i0));
    DEBUG_IOA(if (inBetaHeap(ar->i1) && objIsValRep(cast(Object)(ar->i1)))
	      fprintf(output, "ProcessAR: ar->i1 (0x%x) is *ValRep\n", ar->i1));
    DEBUG_IOA(if (inBetaHeap(ar->i3) && objIsValRep(cast(Object)(ar->i3)))
	      fprintf(output, "ProcessAR: ar->i3 (0x%x) is *ValRep\n", ar->i3));
    DEBUG_IOA(if (inBetaHeap(ar->i4) && objIsValRep(cast(Object)(ar->i4)))
	      fprintf(output, "ProcessAR: ar->i4 (0x%x) is *ValRep\n", ar->i4));

    DEBUG_IOA(if (ar->i0 && (! (inBetaHeap(ar->i0) && isObject(ar->i0)))){
		fprintf(output, "ar: 0x%x, %%i0: 0x%x NOT AN OBJECT\n", ar, ar->i0); 
		fflush(output);
	      });

    if (inBetaHeap(ar->i0) && isObject(ar->i0) && !objIsValRep(cast(Object)(ar->i0)))
      ProcessReference(&ar->i0);
    if (inBetaHeap(ar->i1) && isObject(ar->i1) && !objIsValRep(cast(Object)(ar->i1)))
      ProcessReference(&ar->i1);
    if (inBetaHeap(ar->i3) && isObject(ar->i3) && !objIsValRep(cast(Object)(ar->i3)))
      ProcessReference(&ar->i3);
    if (inBetaHeap(ar->i4) && isObject(ar->i4) && !objIsValRep(cast(Object)(ar->i4)))
	ProcessReference(&ar->i4);
    CompleteScavenging();

    /* Process the stack part */
    for (; theCell != (struct Object **) end; theCell+=2)
      if (inBetaHeap(*theCell) && isObject(*theCell))
	if( objIsValRep(*theCell) ){
	  DEBUG_IOA( fprintf(output, "STACK(%d) (0x%x) is *ValRep", 
			     (long)theCell-(long)&ar[1], *theCell));
	} else {
	  ProcessReference(theCell);
	  CompleteScavenging();
	}
}

#ifdef RTDEBUG
struct RegWin *BottomAR=0, *lastAR=0;
#endif

void ProcessStack()
{
    struct RegWin *theAR;
    struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
    struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
    
    /* Flush register windows to stack */
    asm("ta 3");

    /* StackEnd points to the activation record of doGC, which in turn was called
     * from either DoGC, or IOA(c)alloc.
     */
    StackEnd = (long *)((struct RegWin *) StackEnd)->fp; /* Skip AR of doGC() */
    StackEnd = (long *)((struct RegWin *) StackEnd)->fp; /* Skip AR of IOA(c)alloc / DoGC() */

    
    for (theAR =  (struct RegWin *) StackEnd;
	 theAR != (struct RegWin *) 0;
	 theAR =  (struct RegWin *) theAR->fp) {
	if (theAR == nextCompBlock) {
	    /* This is the AR of attach. Continue GC, but get
	     * new values for nextCompBlock and nextCBF. 
	     * Please read StackLayout.doc
	     */
	    nextCBF = (struct RegWin *) theAR->l5;
	    nextCompBlock = (struct RegWin *) theAR->l6;
	    if (nextCompBlock == 0)
	      break; /* we reached the bottom */
	}
	else if (theAR == nextCBF) {
	    /* This is AR of HandleCB. Don't GC this, but
	     * skip to betaTop and update nextCBF */
	    nextCBF = (struct RegWin *) theAR->l5;
	    theAR = (struct RegWin *) theAR->l6;
	}
	ProcessAR(theAR, (struct RegWin *) theAR->fp);
	DEBUG_CODE(lastAR = theAR);
    }
    DEBUG_CODE(if (BottomAR) Claim(lastAR==BottomAR, "lastAR==BottomAR");
	       else BottomAR=lastAR;
	       )
}

void ProcessStackObj(struct StackObject *theStack)
{
    struct RegWin *theAR;
    long delta = (char *) &theStack->Body[1] - (char *) theStack->Body[0];
    
    for (theAR =  (struct RegWin *) &theStack->Body[1];
	 theAR != (struct RegWin *) &theStack->Body[theStack->StackSize];
	 theAR =  (struct RegWin *) (theAR->fp + delta)) {
	Claim(&theStack->Body[1] <= (long *) theAR
	      && (long *) theAR <= &theStack->Body[theStack->StackSize],
	      "ProcessStackObj: theAR in StackObject");
	ProcessAR(theAR, (struct RegWin *) (theAR->fp + delta));
    }
}
#endif /* sparc */

/***************************** MC680X0 ************************************/

#ifdef mc68020

long *StackStart=0;

/* Traverse the StackArea [low..high] and Process all references within it. */
void ProcessStackPart(low, high)
     ptr(long) low;
     ptr(long) high;
{
    ptr(long) current = low;
    ref(Object) theObj;
    handle(Object) theCell;
    
    DEBUG_IOA(fprintf(output, "StackPart: [0x%x..0x%x]\n", low, high);
	      fprintf(output, "ComponentBlock/CallbackFrame: [0x%x, 0x%x, 0x%x]\n", 
		      *(high+1), *(high+2), *(high+3));
	      );
    Claim( high<=StackStart, "ProcessStackPart: high<=StackStart" );
    
    while( current <= high ){
	if( inBetaHeap( *current)){
	    theCell = (handle(Object)) current;
	    theObj  = *theCell;
	    if( isObject( theObj) ){
		if( inLVRA( theObj) || isValRep(theObj) ){
		    DEBUG_IOA( fprintf( output, "(STACK(%d) is *ValRep)", current-low));
		}else{
		    ProcessReference( current);
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
#endif /* mc68020 */


#ifdef RTDEBUG

#ifdef sparc

void CheckStackReference(theCell)
     handle(Object) theCell;
{
  fprintf(output, "0x%x: 0x%x\n", theCell, *theCell); 
  fflush(output);
  Ck(*theCell);
  ObjectSize(*theCell);
}

void CheckAR(struct RegWin *ar, struct RegWin *end)
{
    struct Object **theCell = (struct Object **) &ar[1];

    Claim((long)ar < (long)end,   "ProcessAR: ar is less than end");
    Claim(((long) end) % 4 == 0, "ProcessAR: end is 4 byte aligned");
    Claim(((long) end) % 4 == 0, "ProcessAR: end is 4 byte aligned");
        
    fprintf(output, "---activation record: 0x%x\niregs:\n", ar); fflush(output);
    /* Check GC registers of the activation record. */
    if (ar->i0 && (! (inBetaHeap(ar->i0) && isObject(ar->i0)))){
	fprintf(output, "-- %%i0: 0x%x NOT AN OBJECT\n", ar->i0); 
	fflush(output);
    } else {
      fprintf(output, "-- %%i0: 0x%x\n", ar->i0); 
      fflush(output);
    }

    if (inBetaHeap(ar->i0) && isObject(ar->i0) && !objIsValRep(cast(Object)(ar->i0)))
      CheckStackReference(&ar->i0);
    if (inBetaHeap(ar->i1) && isObject(ar->i1) && !objIsValRep(cast(Object)(ar->i1)))
      CheckStackReference(&ar->i1);
    if (inBetaHeap(ar->i3) && isObject(ar->i3) && !objIsValRep(cast(Object)(ar->i3)))
      CheckStackReference(&ar->i3);
    if (inBetaHeap(ar->i4) && isObject(ar->i4) && !objIsValRep(cast(Object)(ar->i4)))
	CheckStackReference(&ar->i4);

    /* Check the stack part */
    fprintf(output, "stackpart:\n"); fflush(output);
    for (; theCell != (struct Object **) end; theCell+=2)
      if (inBetaHeap(*theCell) && isObject(*theCell))
	if( objIsValRep(*theCell) ){
	  DEBUG_IOA( fprintf(output, "STACK(%d) (0x%x) is *ValRep", 
			     (long)theCell-(long)&ar[1], *theCell));
	} else {
	  CheckStackReference(theCell);
	}
}

void CheckStack()
{
    struct RegWin *theAR;
    struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
    struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
    
    if (!lastCompBlock) 
      /* BasicComponent hasn't been attached yet: There is an AlloC
       * before AttBC.
       */
      return;

    NumCheckStack++;

    fprintf(output, "---------------CheckStack--------------\n"); fflush(output);
    StackEnd = StackPointer;

    /* Flush register windows to stack */
    asm("ta 3");
    
    StackEnd = (long *)((struct RegWin *) StackEnd)->fp; /* Skip AR of CheckStack() */

    for (theAR =  (struct RegWin *) StackEnd;
	 theAR != (struct RegWin *) 0;
	 theAR = (struct RegWin *) theAR->fp) {
	if (theAR == nextCompBlock) {
	    /* This is the AR of attach. Continue check, but get
	     * new values for nextCompBlock and nextCBF. 
	     * Please read StackLayout.doc
	     */
	    nextCBF = (struct RegWin *) theAR->l5;
	    nextCompBlock = (struct RegWin *) theAR->l6;
	    if (nextCompBlock == 0)
	      break; /* we reached the bottom */
	}
	else if (theAR == nextCBF) {
	    /* This is AR of HandleCB. Don't check this, but
	     * skip to betaTop and update nextCBF */
	    nextCBF = (struct RegWin *) theAR->l5;
	    theAR = (struct RegWin *) theAR->l6;
	}
	CheckAR(theAR, (struct RegWin *) theAR->fp);
    }
}

#endif /* sparc */

#endif
