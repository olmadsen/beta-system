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

extern long *etext;
extern long *end;
#define isData(addr) ( ((long*)&etext <= (long*)(addr)) && ((long*)(addr) < (long*)&end) )
#define isProto(addr) (isSpecialProtoType(addr) || \
		       (isData(addr) && ((int)(addr) % 4 == 0)))

static long skipCparams=FALSE;

#ifdef RTDEBUG

struct RegWin *BottomAR=0, *lastAR=0;
long PC = 0;
void PrintAR(struct RegWin *ar, struct RegWin *theEnd);

#endif

/* Traverse an activation record (AR) [ar, theEnd[
   Notice theEnd is *not* included
   */

/* Don't process references from the stack to LVRA. The ValReps in
 * in LVRA are not moved by CopyObject, but if PrecessReference
 * is called with such a reference, the LVRA cycle is broken!
 */
# define objIsValRep(theObj) inLVRA(theObj)


void ProcessAR(struct RegWin *ar, struct RegWin *theEnd)
{
    struct Object **theCell = (struct Object **) &ar[1];
    
    DEBUG_STACK(PrintAR(ar, theEnd));

    DEBUG_CODE(Claim((long)ar < (long)theEnd,   "ProcessAR: ar is less than theEnd");
	       Claim(((long) theEnd) % 4 == 0, "ProcessAR: theEnd is 4 byte aligned");
	       Claim(((long) theEnd) % 4 == 0, "ProcessAR: theEnd is 4 byte aligned");
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
      if (isProto((cast(Object)ar->i0)->Proto)) ProcessReference(&ar->i0);
    if (inBetaHeap(ar->i1) && isObject(ar->i1) && !objIsValRep(cast(Object)(ar->i1)))
      if (isProto((cast(Object)ar->i1)->Proto)) ProcessReference(&ar->i1);
    if (inBetaHeap(ar->i3) && isObject(ar->i3) && !objIsValRep(cast(Object)(ar->i3)))
      if (isProto((cast(Object)ar->i3)->Proto)) ProcessReference(&ar->i3);
    if (inBetaHeap(ar->i4) && isObject(ar->i4) && !objIsValRep(cast(Object)(ar->i4)))
      if (isProto((cast(Object)ar->i4)->Proto)) ProcessReference(&ar->i4);
    CompleteScavenging();

    /* Process the stack part */
    if (skipCparams)
      /* This AR called C, skip one hidden word, and (at least) 
       * six parameters (compiler allocates 48, that may be too much...)
       */
       ((long) theEnd) -= 48;
    for (; theCell != (struct Object **) theEnd; theCell+=2)
      if (inBetaHeap(*theCell) && isObject(*theCell))
	if( objIsValRep(*theCell) ){
	  DEBUG_IOA( fprintf(output, "STACK(%d) (0x%x) is *ValRep", 
			     (long)theCell-(long)&ar[1], *theCell));
	} else {
	  if (isProto((cast(Object)*theCell)->Proto)){
	    ProcessReference(theCell);
	    CompleteScavenging();
	  }
	}
}

void ProcessStack()
{
    struct RegWin *theAR;
    struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
    struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
    
    /* Flush register windows to stack */
    asm("ta 3");

    DEBUG_STACK(fprintf(output, "\n ***** Trace of stack *****\n"));

    /* StackEnd points to the activation record of doGC, which in turn was called
     * from either DoGC, or IOA(c)alloc.
     */
    StackEnd = (long *)((struct RegWin *) StackEnd)->fp; /* Skip AR of doGC() */
    DEBUG_CODE( PC=((struct RegWin *) StackEnd)->i7 +8);
    StackEnd = (long *)((struct RegWin *) StackEnd)->fp; /* Skip AR of IOA(c)alloc / DoGC() */

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
	    DEBUG_CODE(PC = 0)
	      /* Cannot know where we came from in beta before C was called */;
	    skipCparams = TRUE;
	    theAR = (struct RegWin *) theAR->l6;
	  }
	}
	ProcessAR(theAR, (struct RegWin *) theAR->fp);
	skipCparams=FALSE;
	DEBUG_CODE(lastAR = theAR);
    }
    DEBUG_CODE(if (BottomAR) Claim(lastAR==BottomAR, "lastAR==BottomAR");
	       else BottomAR=lastAR;
	       )
    DEBUG_STACK(fprintf(output, " *****  End of trace  *****\n"));

}

#ifdef RTDEBUG
long lastPC=0;
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

void ProcessStackObj(theStack)
     struct StackObject *theStack
{ ptr(long)        stackptr; 
  handle(Object)   theCell; 
  ptr(long)        theEnd;
	    
  DEBUG_IOA( Claim(theStack->StackSize <= theStack->BodySize,
		   "ProcessReference: StackObjectType: Stack > Object") );
	    
  theEnd = &theStack->Body[0] + theStack->StackSize;
	    
  for( stackptr = &theStack->Body[0]; stackptr < theEnd; stackptr++){
    if( inBetaHeap( *stackptr)){
      theCell = (handle(Object)) stackptr;
      if( isObject( *theCell ) )
	ProcessReference( stackptr);
    }else{
      switch( *stackptr ){
      case -8: stackptr++;
      case -7: stackptr++;
      case -6: stackptr++;
      case -5: stackptr++;
	break;
      }
    }
  }
}

#endif /* mc68020 */

/*************************** DEBUG ****************************/

#ifdef RTDEBUG

#ifdef sparc

static FILE *thePipe=0; 
static char theLabel[100]; 
static long labelAddress;
long labelOffset = 0;
static char *labels=0;

static void initLabels()
{
  char ch;
  char command[200];
  int size=0;

  fprintf(output, "(initLabels ...");
  fflush(output);

  (void) strcpy (command, "nm -grn ");
  (void) strcat (command, ArgVector[0]);

  thePipe = popen (command, "r");

  for (;;){
    fscanf(thePipe, "%x %c %s", &labelAddress, &ch, theLabel);
    if (labelAddress==(long)&etext) break;
  }
      
  while (fgetc (thePipe) != EOF)
    size+=1;

  if (! (labels=(char *)malloc(size+1)))
    fprintf(output, "Failed to allocate memory for labels\n");
  else
    {
      pclose (thePipe);
      thePipe = popen (command, "r");
      for (;;){
	fscanf(thePipe, "%x %c %s", &labelAddress, &ch, theLabel);
	if (labelAddress==(long)&etext) break;
      }
      fread(labels, 1, size, thePipe);
      pclose (thePipe);
    }
  fprintf(output, " done)\n");
  fflush(output);
}

char *getLabel (addr)
     long addr;
{
  char ch;
  char *lab;
  int chars;

  if (labels==0) initLabels();

  if (!addr){
    labelOffset=0;
    labelAddress=0;
    return "<unknown>";
  }
  
  if (labels)
    for (lab=labels;;){
      if (sscanf (lab, "%x %c %s%n", &labelAddress, &ch, theLabel, &chars) 
	  == EOF)
	{
	  labelAddress = 0;
	  break;
	}
      else 
	if (labelAddress <= addr){
	  labelOffset = addr-labelAddress;
	  return theLabel;
	} else {
	  lab += chars;
	}
    }
}

void PrintRef(ref(Object) ref)
{
  if (ref) {
    if (inBetaHeap(ref) && isObject(ref) ){
      if(objIsValRep(ref)) {
	fprintf(output, ", is *ValRep");
      } else {
	fprintf(output, ", is object");
	if (isProto((ref)->Proto))
	  fprintf(output, ", proto ok: 0x%x", ref->Proto);
	else
	  fprintf(output, ", proto NOT ok: 0x%x", ref->Proto);
      }
    } else {
      fprintf(output, ", is NOT object");
    }
  }
  fprintf(output, "\n");
}

void PrintAR(struct RegWin *ar, struct RegWin *theEnd)
{
  struct Object **theCell = (struct Object **) &ar[1];

  if (DebugLabels){
    fprintf(output, 
	    "----- ar: 0x%x, theEnd: 0x%x, PC: 0x%x (%s+0x%x)\n",
	    ar, 
	    theEnd,
	    PC,
	    getLabel(PC),
	    labelOffset);
  } else {
    fprintf(output, 
	    "----- ar: 0x%x, theEnd: 0x%x, PC: 0x%x\n",
	    ar, 
	    theEnd,
	    PC);
  }    
  fprintf(output, "%%i0: 0x%x", ar->i0); PrintRef(cast(Object)ar->i0);
  fprintf(output, "%%i1: 0x%x", ar->i1); PrintRef(cast(Object)ar->i1)
    /* Notice that CopyT, AlloVR1-4 gets an offset in this parameter.
     * This should be safe.
     */;
  fprintf(output, "%%i3: 0x%x", ar->i3); PrintRef(cast(Object)ar->i3);
  fprintf(output, "%%i4: 0x%x", ar->i4); PrintRef(cast(Object)ar->i4);

  fprintf(output, "stackpart:\n");
  /* Notice that in INNER some return adresses are pushed. This is no
   * danger.
   */
  if (skipCparams)
    /* This AR called C, skip one hidden word, and (at least) 
     * six parameters
     */
    ((long) theEnd) -= 48;

  for (; theCell != (struct Object **) theEnd; theCell+=2) {
    fprintf(output, "0x%x", *theCell);
    PrintRef(cast(Object)(*theCell));
  }
  fflush(output);
}

#endif /* sparc */

#endif /* RTDEBUG */
