/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-1992 Mjolner Informatics Aps.
 * scavenging.c
 * by Lars Bak, Peter Andersen, Peter Orbaek and Tommy Thorn.
 */

#include "beta.h"
#ifdef sparc
#include "../CRUN/crun.h"
#endif

#ifdef hpux
#include <sys/cache.h>
#endif

#ifdef hppa
/***************************** for the snake ****************************/

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
/************************************************************************/
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
    
    Claim(((long)  ar) % 4 == 0, "ProcessAR: ar is 4 byte aligned");
    Claim(((long) end) % 4 == 0, "ProcessAR: end is 4 byte aligned");
        
    /* Process GC registers of the activation record. */
    DEBUG_IOA(if (inBetaHeap(ar->i0) && objIsValRep(cast(Object)(ar->i0)))
	      fprintf(output, "ProcessAR: ar->i0 (0x%x) is *ValRep\n", ar->i0));
    DEBUG_IOA(if (inBetaHeap(ar->i1) && objIsValRep(cast(Object)(ar->i1)))
	      fprintf(output, "ProcessAR: ar->i1 (0x%x) is *ValRep\n", ar->i1));
    DEBUG_IOA(if (inBetaHeap(ar->i3) && objIsValRep(cast(Object)(ar->i3)))
	      fprintf(output, "ProcessAR: ar->i3 (0x%x) is *ValRep\n", ar->i3));
    DEBUG_IOA(if (inBetaHeap(ar->i4) && objIsValRep(cast(Object)(ar->i4)))
	      fprintf(output, "ProcessAR: ar->i4 (0x%x) is *ValRep\n", ar->i4));

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

void ProcessStack()
{
    struct RegWin *theAR;
    struct RegWin *nextCBF = (struct RegWin *) ActiveCallBackFrame;
    struct RegWin *nextCompBlock = (struct RegWin *) lastCompBlock;
    
    /* Flush register windows to stack */
    asm("ta 3");
    
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
    }
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
/*********************************************************************/
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
/*********************************************************************/

static long FreePercentage( bottom, top, limit)
     long bottom, top, limit;
{
    return (100 * areaSize(top, limit))/areaSize(bottom, limit); 
}

/*
 * IOAGc:
 *  Called from DoGC in the assembly part of the runtime system.
 *  Make a scavenging garbage collection on IOA.
 */
void IOAGc()
{
#ifdef macintosh
    RotateTheCursor();
#endif

#ifdef RTDEBUG
    memset(ToSpace, 0, IOASize);
#endif
    
    NumIOAGc++;

/******************** DEMO Limitation in IOAGc ****************************/
#ifdef DEMO
    if (NumIOAGc==20) {

#ifdef macintosh
      Prompt(
"\p\
This program was compiled using the demo version of \
the Mj\277lner BETA System. The demo version is limited \
in the number of garbage collections allowed. This ",
"\p\
limit will soon be reached; if you want to save your \
work, please do it now, and quit your program.",
"", "");

#else macintosh
      fprintf(output, "\
  ********************************************************\n\
  * This program was compiled using the demo version of  *\n\
  * the Mjolner BETA System. The demo version is limited *\n\
  * in the number of garbage collections allowed. This   *\n\
  * limit will soon be reached; if you want to save your *\n\
  * work, please do it now, and quit your program.       *\n\
  ********************************************************\n\
");
#endif macintosh

    } else
    if (NumIOAGc==30) {

#ifdef macintosh
      Prompt(
"\p\
This program was compiled using the demo version of \
the Mj\277lner BETA System. The demo version is limited \
in the number of garbage collections allowed. This ",
"\p\
limit has now been reached and your program will be \
terminated - sorry!\n\
You may order an unconstrained version from\n",
"\p\n\
    Mj\277lner Informatics, Gustav Wiedsvej 10,\n\
    Science Park Aarhus, DK-8000 Aarhus C, Denmark,\n",
"\p\
    Phone: +45 86 20 20 00,  Fax: +45 86 20 12 22\n\
    e-mail: support@mjolner.dk"
);

#else macintosh
      fprintf(output, "\
  ********************************************************\n\
  * This program was compiled using the demo version of  *\n\
  * the Mjolner BETA System. The demo version is limited *\n\
  * in the number of garbage collections allowed. This   *\n\
  * limit has now been reached and your program will be  *\n\
  * terminated - sorry!                                  *\n\
  * You may order an unconstrained version from          *\n\
  *                                                      *\n\
  *     Mjolner Informatics, Gustav Wiedsvej 10,         *\n\
  *     Science Park Aarhus, DK-8000 Aarhus C, Denmark,  *\n\
  *     Phone: +45 86 20 20 00,  Fax: +45 86 20 12 22    *\n\
  *     e-mail: support@mjolner.dk                       *\n\
  ********************************************************\n\
");
#endif macintosh

      exit(0);
    }
#endif DEMO
/***************** End of DEMO Limitation in IOAGc ****************************/

    IOAActive = TRUE;
    
    INFO_IOA( fprintf( output, "#(IOA-%d %d? ", NumIOAGc, ReqObjectSize));
    InfoS_LabA();
    
    /* Initialize the ToSpace */
    ToSpaceTop       = ToSpace;
    HandledInToSpace = ToSpace;
    
    DEBUG_IOA( IOACheck() );
    DEBUG_LVRA( LVRACheck() );
    
    DEBUG_AOA( AOAtoIOACheck() );
    DEBUG_AOA( AOACheck() );
    IOAStackObjectSum = IOAStackObjectNum = 0;
    ToSpaceToAOALimit = ToSpaceToAOAptr = ToSpaceLimit;
    { long i; for(i=0; i < IOAMaxAge;i++) IOAAgeTable[i] = 0; }
    /* Save the state of AOA, this state is used at end of IOAGc, to proceed 
     * not handled objects.
     */
    HandledAOABlock = AOATopBlock;
    if( AOATopBlock ) HandledInAOA = AOATopBlock->top;
    
    AOAtoIOACount = 0;
    if( AOAtoIOAtable ){ 
	long i; ptr(long) pointer = BlockStart( AOAtoIOAtable);
	for(i=0; i<AOAtoIOAtableSize; i++){ 
	    if( *pointer ){
		AOAtoIOACount++;
		ProcessAOAReference( *pointer);
	    }
	    pointer++;
	}
    }
    DEBUG_AOA( AOAtoIOAReport() );
    DEBUG_AOA( AOAcopied = 0; IOAcopied = 0; );
    
    /* Follow ActiveComponent */ 
    if (!ActiveComponent && NumIOAGc == 1) {
      fprintf(output, "#BETA: Could not allocate basic component\n");
      exit(1);
    }
    ActiveComponent->StackObj = 0;  /* the stack is not valid anymore. */
    ProcessReference( &ActiveComponent);
    ProcessReference( &BasicItem );
    CompleteScavenging();
    
    ProcessStack();
    
    /* Follow all struct pointers in the Call Back Functions area. */
    if (CBFABlockSize){
	if( CBFATop != CBFA->entries ){
	    ref(CallBackArea) cbfa = CBFA;
	    ref(CallBackEntry) current = cbfa->entries;
	    long limit = (long) cbfa->entries + CBFABlockSize;
	    
	    for (; current != CBFATop; current++){
		if ( (long) current >= limit){
		    /* Go to next block */
		    cbfa = cbfa->next;        
		    /* guarentied to be non-nil since current != CBFATop */
		    
		    current = cbfa->entries; 
		    /* guarentied to be different from CBFATop. 
		     * If not the block would not have been allocated 
		     */
		    limit = (long)cbfa->entries + CBFABlockSize;
		}
		if (current->theStruct)
		  ProcessReference(&current->theStruct);
	    }
	    CompleteScavenging();
	}
    }
    
    /* Objects copied til AOA until now has not been proceesed. 
     * During proceesing these objects, new objects may be copied to
     * ToSpace and AOA, therefore we must alternate between handeling
     * objects in ToSpace and AOA until no more objects is to procees.
     */
    if( AOABaseBlock ){
	if( !HandledAOABlock ){
	    HandledAOABlock = AOABaseBlock; HandledInAOA = BlockStart( AOABaseBlock);
	}
	while( HandledAOABlock ){
	    /* Process objects from AOAoldTop to blockPtr->top. */
	    while( HandledInAOA < HandledAOABlock->top ){
		ProcessAOAObject( (ref(Object))  HandledInAOA );
		HandledInAOA = (ptr(long)) (((long) HandledInAOA)
					    + 4*ObjectSize( (ref(Object)) HandledInAOA ));
		CompleteScavenging();
	    }
	    HandledAOABlock = HandledAOABlock->next;
	    if( HandledAOABlock ) HandledInAOA = BlockStart( HandledAOABlock);
	}
	DEBUG_AOA( AOAtoIOACheck());
    }

    if( DOT ){
	/* The Debugger Object Table is in use, so traverse this table. */
	ptr(long) current = DOT;
	while( current < DOTTop){
	    if( *current ) {
	      if (inIOA(*current)){
		INFO_DOT(fprintf(output, "#DOT: updating IOA reference 0x%x\n", *current));
		if( isForward( (cast(Object)(*current))->GCAttr ) ){ 
		  /* *current has a forward pointer. */
		  *current = (long) (ref(Object)) (cast(Object)(*current))->GCAttr;
		} else {
		  *current = 0;
		}
	      }
	    }
	    current++;
	}
    }
    
    if( AOANeedCompaction)  AOAGc();
    
    if (tempToSpaceToAOA) {
	/* ToSpace was not big enough to hold both objects and table.
	 * Free the table that was allocated in CopyObject().
	 */
	tempToSpaceToAOAfree();
    }
#ifdef RTDEBUG
    else {
      /* Clear the part of ToSpace used for ToSpaceToAOAtable */
      memset(ToSpaceToAOAptr, 0, ToSpaceToAOALimit-ToSpaceToAOAptr);
    }
#endif
    
    /* Swap IOA and ToSpace */
    {
	ptr(long) Tmp; ptr(long) TmpTop; ptr(long) TmpLimit;
      
	Tmp     = IOA;     TmpTop     = IOATop;     TmpLimit     = IOALimit; 
      
#ifdef sparc
	IOA       = ToSpace;                          
	IOATopoff = (char *) ToSpaceTop - (char *) IOA;
#endif
#ifdef hppa
	setIOAReg(ToSpace);
	setIOATopoffReg((char *) ToSpaceTop - (char *) IOA);
#endif
#ifdef mc68020
	IOA       = ToSpace;                          
	IOATop    = ToSpaceTop; 
#endif
	IOALimit     = ToSpaceLimit;
      
	ToSpace = Tmp;     ToSpaceTop = TmpTop;     ToSpaceLimit = TmpLimit;

    }
    
    IOAActive = FALSE;
    
    {
	long limit = areaSize(IOA,IOALimit) / 10;long sum = 0;
      
	limit -= IOAStackObjectSum;
	if (limit < 0) {
	    DEBUG_IOA( fprintf(output, 
			       "#IOA: %d StackObjects fill up more than 10%% of IOA (%d)\n", 
			       IOAStackObjectNum, 
			       IOAStackObjectSum));
	    limit = 0;
	}
	IOAtoAOAtreshold = 0;
	do
	  {
	      sum += IOAAgeTable[IOAtoAOAtreshold++];
	  } while ((sum < limit) && (IOAtoAOAtreshold < IOAMaxAge));
	
	if (limit)
	  IOAtoAOAtreshold +=1; 
    }
    DEBUG_IOA( fprintf( output, " treshold=%d", IOAtoAOAtreshold));
    DEBUG_IOA( fprintf( output, " ToSpaceToAOA=%d", 
		       areaSize(ToSpaceToAOAptr,ToSpaceToAOALimit)));
    
    INFO_IOA( fprintf( output," %d%%)\n",
		      (100 * areaSize(IOA,IOATop))/areaSize(IOA,IOALimit)));
    
    DEBUG_IOA( IOACheck() );
    DEBUG_AOA( AOACheck() );
    DEBUG_LVRA( LVRACheck() );
    InfoS_LabB();
    
    /* Based on IOAPercentage, determine if IOA space is exhausted. */
    
    if( FreePercentage( IOA, (long) IOATop + ReqObjectSize*4, IOALimit) 
       < IOAPercentage ){
	fprintf( output,"#IOA Heap space full, request: %d.\n", ReqObjectSize);
	BetaExit(1);
    }

#ifdef hpux
/*    cachectl(CC_FLUSH, 0, 0); */
#endif
}

/*
 * ProcessReference:
 *  Takes as input a reference to a cell containing a root for IOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore one forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 *  Copies at most one object to ToSpace/AOA. You must call 
 *  CompleteScavenging sometimes later to process references from the 
 *  copied object.
 *  Optimization: USE theObj instead of newObj and inline GetDistanceToEnc....
 */

void ProcessReference( theCell)
     handle(Object) theCell;
{
    ref(Object) theObj;
    long GCAttribute;
    
    theObj = *theCell;
    
    if( inIOA(theObj)){
	/* 'theObj' is inside IOA */
	DEBUG_IOA( Claim(isObject(theObj),"ProcessReference: theObj is consistent."));
	GCAttribute = theObj->GCAttr;
	if( isForward(GCAttribute) ){ 
	    /* theObj has a forward pointer. */
	    *theCell = (ref(Object)) GCAttribute;
	    DEBUG_LVRA( Claim( !inLVRA(GCAttribute), "ProcessReference: Forward ValRep"));
	    /* If the forward pointer refers an AOA object, insert
	     * theCell in ToSpaceToAOA table.
	     */
	    if( !inToSpace( GCAttribute))
	      if (inAOA( GCAttribute)) {
		  SaveToSpaceToAOAref(theCell);
	      }
	}else{
	    if( GCAttribute >= 0 ){ 
		/* '*theCell' is an autonomous object. */
		*theCell = NewCopyObject( *theCell, theCell);
	    }else{
		/* theObj is a part object. */
		long Distance;
		ref(Object) newObj;
		ref(Object) AutObj;
		
		Distance = GetDistanceToEnclosingObject( theObj);
		AutObj = (ref(Object)) Offset( theObj, Distance);
		if( isForward(AutObj->GCAttr) ){
		    newObj = (ref(Object)) AutObj->GCAttr;
		    /* If the forward pointer refers an AOA object, insert
		     * theCell in ToSpaceToAOA table.
		     */
		    if( !inToSpace( AutObj->GCAttr))
		      if( inAOA( AutObj->GCAttr)){
			  SaveToSpaceToAOAref(theCell);
		      }
		}else
		  newObj = NewCopyObject( AutObj, theCell);
		*theCell = (ref(Object)) Offset( newObj, -Distance);
	    }
	}
	DEBUG_IOA( Claim( !inIOA(*theCell),"ProcessReference: !inIOA(*theCell)"));
    }else{
	/* '*theCell' is pointing outside IOA */
	/* If the forward pointer refers an AOA object, insert
	 * theCell in ToSpaceToAOA table.
	 */
	if (inAOA( *theCell)) {
	    SaveToSpaceToAOAref(theCell);
	    return;
	}
	if( inLVRA( *theCell)){
	    /* Preserve the LVRA-cycle. */
	    ((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
	    DEBUG_LVRA( Claim( isValRep(*theCell),
			      "ProcessObject: isValRep(*theCell)"));
	    return;
	}
    }
}

/*
 * ProcessObject:
 *  Takes as input a reference to an object residing in the ToSpace.
 *  It traverses the object and processes all the references in it.    
 */

void ProcessObject(theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  if( (long) theProto < 0 ){  
      switch( (long) theProto ){
	case (long) ByteRepPTValue:
	case (long) WordRepPTValue:
	case (long) DoubleRepPTValue:
	case (long) ValRepPTValue: return; /* No references in the type of object, so do nothing*/
	  
	case (long) RefRepPTValue:
	  /* Scan the repetition and follow all entries */
	  { ptr(long) pointer;
	    register long size, index;
	    
	    size = toRefRep(theObj)->HighBorder;
	    pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	    
	    for(index=0; index<size; index++) 
	      if( *pointer != 0) ProcessReference( pointer++ );
	      else pointer++;
	}
	  
	  return;
	  
	case (long) ComponentPTValue:
	  { ref(Component) theComponent;
	    
	    theComponent = Coerce( theObj, Component);
	    ProcessReference( &theComponent->StackObj);
	    ProcessReference( &theComponent->CallerComp);
	    ProcessReference( &theComponent->CallerObj);
	    ProcessObject( ComponentItem( theComponent));
	}
	  return;
	  
	case (long) StackObjectPTValue:
#ifdef mc68020
	  { ref(StackObject) theStackObject;
	    ptr(long)        stackptr; 
	    handle(Object)   theCell; 
	    ptr(long)        theEnd;
	    
	    theStackObject = Coerce(theObj, StackObject);
	    
	    DEBUG_IOA( Claim(theStackObject->StackSize <= theStackObject->BodySize,
			     "ProcessReference: StackObjectType: Stack > Object") );
	    
	    theEnd = &theStackObject->Body[0] + theStackObject->StackSize;
	    
	    for( stackptr = &theStackObject->Body[0]; stackptr < theEnd; stackptr++){
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
#else
	  ProcessStackObj((struct StackObject *)theObj);
#endif
	  return;
	  
	case (long) StructurePTValue:
	  ProcessReference( &(toStructure(theObj))->iOrigin );
	  return;
      }
  }else{
#ifdef UGLY_CODE
      ptr(short)  Tab;
      ptr(long)   theCell;
      
      /* Calculate a pointer to the GCTabel inside the ProtoType. */
      Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
      
      /* Handle all the static objects. 
       * The static table have the following structure:
       * { .word Offset
       *   .word Distance_To_Inclosing_Object
       *   .long T_entry_point
       * }*
       * This table contains all static objects on all levels.
       * Here vi only need to perform ProcessObject on static objects
       * on 1 level. The recursion in ProcessObject handle other
       * levels. 
       * The way to determine the level of an static object is to 
       * compare the Offset and the Distance_To_Inclosing_Object.
       */
      
      while( *Tab != 0 ){
	  if( *Tab == -Tab[1] ) 
	    ProcessObject( Offset( theObj, *Tab * 4));
	  Tab += 4;
      }
      Tab++;
      
      /* Handle all the references in the Object. */
      while( *Tab != 0 ){
	  theCell = (ptr(long)) Offset( theObj, *Tab++ );
	  if( *theCell != 0 ) ProcessReference( theCell );
      }
#else
      struct GCEntry *tab =
	(struct GCEntry *) ((char *) theProto + theProto->GCTabOff);
      short *refs_ofs;
      struct Object **theCell;
      
      /* Handle all the static objects. 
       *
       * The static table, tab[0], tab[1], 0,
       * contains all static objects on all levels.
       * Here we only need to perform ProcessObject on static objects
       * on 1 level. The recursion in ProcessObject handle other
       * levels. 
       * The way to determine the level of an static object is to 
       * compare the Offset (StaticOff) and the
       * Distance_To_Inclosing_Object (OrigOff).
       */
      for (;tab->StaticOff; ++tab)
	if (tab->StaticOff == -tab->OrigOff)
	  ProcessObject((long *)theObj + tab->StaticOff);
      
      /* Handle all the references in the Object. */
      for (refs_ofs = (short *)&tab->StaticOff + 1; *refs_ofs; ++refs_ofs) {
	  theCell = (struct Object **) ((char *) theObj + *refs_ofs);
	  if (*theCell) ProcessReference(theCell);
      }
#endif
  }
}


/*
 * ProcessAOAReference:
 *  Takes as input a reference to a cell residing outside IOA.
 *  If the cell refers an object residing in IOA, the 
 *  object is copied to ToSpace/AOA and the cell is updated.
 *  Furthermore one forward reference in the most enclosing
 *  object is inserted in the GC-attribute.
 */
void ProcessAOAReference( theCell)
     handle(Object) theCell;
{
    ref(Object) theObj;
    long GCAttribute;
    
    DEBUG_AOA( Claim( inAOA( theCell),"#ProcessAOAReference: theCell inside AOA\n"));
    theObj = *theCell;
    
    if( inIOA(theObj)){ /* theObj is inside IOA */
	GCAttribute = theObj->GCAttr;
	if( GCAttribute > 2048 ){ /* theObj has a forward pointer. */
	    *theCell = (ref(Object)) GCAttribute;
	    DEBUG_LVRA( Claim( !inLVRA(GCAttribute),
			      "ProcessAOAReference: Forward ValRep"));
	}else{
	    if( GCAttribute >= 0 ){ /* theObj is an autonomous object. */
		*theCell = NewCopyObject( theObj, 0);
		if( !inToSpace( *theCell)){
		    if( inLVRA( *theCell)){
			/* Preserve the LVRA-cycle. */
			((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
			DEBUG_LVRA( Claim( isValRep(*theCell),
					  "ProcessAOAReference: isValRep(*theCell)"));
		    }
		}
	    }else{ /* theObj is a part object. */
		long Distance;
		ref(Object) newObj;
		ref(Object) AutObj;
		
		Distance = GetDistanceToEnclosingObject( theObj);
		AutObj = (ref(Object)) Offset( theObj, Distance);
		if( !isAutonomous(AutObj->GCAttr)) 
		  newObj = (ref(Object)) AutObj->GCAttr;
		else
		  newObj = NewCopyObject( AutObj, 0);
		*theCell = (ref(Object)) Offset( newObj, -Distance);
	    }
	}
    }else{
	if( inLVRA( *theCell)){
	    /* Preserve the LVRA-cycle. */
	    ((ref(ValRep)) *theCell)->GCAttr = (long) theCell;
	    DEBUG_LVRA( Claim( isValRep(*theCell), 
			      "ProcessAOAReference: isValRep(*theCell)"));
	}
    }
    DEBUG_AOA( Claim( !inIOA(*theCell),"ProcessAOAReference: !inIOA(*theCell)"));
    DEBUG_AOA( if( inAOA( *theCell)){ AOACheckObjectSpecial( *theCell); } );
    
    /* Insert 'theCell' in the AOAtoIOAtable iff *theCell is inToSpace. */
    if( inToSpace( *theCell ) ) AOAtoIOAInsert( theCell);
}

/*
 * ProcessAOAObject:
 *  Takes as input a reference to an object residing in the AOA.
 *  It traverse the object and process all the references in it.    
 */

void ProcessAOAObject(theObj)
     ref(Object) theObj;
{ ref(ProtoType) theProto;
  
  theProto = theObj->Proto;
  
  if( (long) theProto < 0 ){  
      switch( (long) theProto ){
	case (long) ByteRepPTValue: 
	case (long) WordRepPTValue: 
	case (long) DoubleRepPTValue: 
	case (long) ValRepPTValue: 
	  return; /* No references in the type of object, so do nothing*/
	case (long) RefRepPTValue:
	  /* Scan the repetition and follow all entries */
	  { ptr(long) pointer;
	    register long size, index;
	    
	    size = toRefRep(theObj)->HighBorder;
	    pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	    for(index=0; index<size; index++) 
	      if( *pointer != 0) ProcessAOAReference( pointer++ );
	      else pointer++;
	}
	  return;
	case (long) ComponentPTValue:
	  { ref(Component) theComponent;
	    theComponent = Coerce( theObj, Component);
	    ProcessAOAReference( &theComponent->StackObj);
	    ProcessAOAReference( &theComponent->CallerComp);
	    ProcessAOAReference( &theComponent->CallerObj);
	    ProcessAOAObject( ComponentItem( theComponent));
	}
	  return;
	case (long) StackObjectPTValue:
	  Claim( FALSE, "ProcessAOAObject: No StackObject in AOA");
	  return;
	case (long) StructurePTValue:
	  ProcessAOAReference( &(toStructure(theObj))->iOrigin );
	  return;
      }
  }else{
      ptr(short)  Tab;
      ptr(long)   theCell;
      
      /* Calculate a pointer to the GCTabel inside the ProtoType. */
      Tab = (ptr(short)) ((long) ((long) theProto) + ((long) theProto->GCTabOff));
      
      /* Handle all the static objects. 
       * The static table have the following structure:
       * { .word Offset
       *   .word Distance_To_Inclosing_Object
       *   .long T_entry_point
       * }*
       * This table contains all static objects on all levels.
       * Here vi only need to perform ProcessAOAObject on static objects
       * on 1 level. The recursion in ProcessAOAObject handle other
       * levels. 
       * The way to determine the level of an static object is to 
       * compare the Offset and the Distance_To_Inclosing_Object.
       */
      
      while( *Tab != 0 ){
	  if( *Tab == -Tab[1] ) 
	    ProcessAOAObject( Offset( theObj, *Tab * 4));
	  Tab += 4;
      }
      Tab++;
      
      /* Handle all the references in the Object. */
      while( *Tab != 0 ){
	  theCell = (ptr(long)) Offset( theObj, *Tab++ );
	  if( *theCell != 0 ) ProcessAOAReference( theCell );
      }
  }
}

/*
 * CompleteScavenging:
 *  Process all the objects in the ToSpace, which has not been handled yet.
 *  i.e. objects coiped to ToSpace since last call of CompleteScavenging.
 *  The reason that this is done "stepwise" is to ensure the locallity of 
 *  related objects, to avoid unnecessary swapping. 
 */

void CompleteScavenging()
{
    ref(Object) theObj;
    
    while( HandledInToSpace < ToSpaceTop){
	theObj = (ref(Object)) HandledInToSpace;
	HandledInToSpace = (ptr(long)) (((long) HandledInToSpace)
					+ 4*ObjectSize(theObj));
	ProcessObject( theObj);
    }
    DEBUG_IOA( Claim( HandledInToSpace == ToSpaceTop,
		     "CompleteScavenging: HandledInToSpace == ToSpaceTop"));
}

/*
 * GetDistanceToEnclosingObject:
 *  Find the offset (negative) to the most inclosing object e.g.
 *  the offset to the autonomous object in which theObj reside.  
 */

long GetDistanceToEnclosingObject( theObj)
     ref(Object)theObj;
{
    long Distance, GCAttribute;
    
    Distance = 0;
    GCAttribute = theObj->GCAttr*4;
    while( GCAttribute < 0 ){
	Distance += GCAttribute; 
	theObj = (struct Object *) Offset( theObj, GCAttribute);
	GCAttribute = theObj->GCAttr*4;
    }
    return Distance;
}

#ifdef RTDEBUG
void IOACheck()
{
    ref(Object) theObj;
    long        theObjectSize;
    
    theObj = (ref(Object)) IOA;
    /*fprintf(output, "\n");*/
    while ((long *) theObj < IOATop) {
      Claim(theObj->Proto, "IOACheck: theObj->Proto");
      theObjectSize = 4*ObjectSize(theObj);
      
      /*fprintf(output, "theObj: 0x%x theObjectSize: 0x%x\n", theObj, theObjectSize);*/
      IOACheckObject (theObj);
      theObj = (ref(Object)) Offset(theObj, theObjectSize);
    }
}

void IOACheckObject (theObj)
     ref(Object) theObj;
{
    ref(ProtoType) theProto;
    
    theProto = theObj->Proto;

    /* DEBUG_IOA(printf("IOACheckObject: theObj = %x\n", theObj)); */
    Claim( !inBetaHeap(theProto),"#IOACheckObject: !inBetaHeap(theProto)");
    
    if( (long) theProto < 0 ){  
	switch( (long) theProto ){
	  case (long) ByteRepPTValue:
	  case (long) WordRepPTValue:
	  case (long) DoubleRepPTValue:
	  case (long) ValRepPTValue:
	    /* No references in the type of object, so do nothing*/
	    return;
	    
	  case (long) RefRepPTValue:
	    /* Scan the repetition and follow all entries */
	    { ptr(long) pointer;
	      register long size, index;
	      
	      size = toRefRep(theObj)->HighBorder;
	      pointer =  (ptr(long)) &toRefRep(theObj)->Body[0];
	      
	      for(index=0; index<size; index++) 
		if( *pointer != 0) IOACheckReference( pointer++ );
		else pointer++;
	  }
	    
	    return;
	    
	  case (long) ComponentPTValue:
	    { ref(Component) theComponent;
	      
	      theComponent = Coerce( theObj, Component);
	      if (theComponent->StackObj == (ref(StackObject))-1) {
		  /*  printf("\nIOACheckObject: theComponent->StackObj=-1, skipped!\n"); */
	      } else {
		  IOACheckReference( &theComponent->StackObj);
	      }
	      IOACheckReference( &theComponent->CallerComp);
	      IOACheckReference( &theComponent->CallerObj);
	      IOACheckObject( ComponentItem( theComponent));
	  }
	    return;
	    
	  case (long) StackObjectPTValue:
	    { ref(StackObject) theStackObject;
	      ptr(long)        stackptr; 
	      handle(Object)   theCell; 
	      ptr(long)        theEnd;
	      
	      theStackObject = Coerce(theObj, StackObject);
	      
	      theEnd = &theStackObject->Body[0] + theStackObject->StackSize;
	      
	      for( stackptr = &theStackObject->Body[0]; stackptr < theEnd; stackptr++){
		  if( inIOA( *stackptr)){
		      theCell = (handle(Object)) stackptr;
		      if( isObject( *theCell ) ) IOACheckReference( stackptr);
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
	    return;
	    
	  case (long) StructurePTValue:
	    IOACheckReference( &(toStructure(theObj))->iOrigin );
	    return;
	}
    } else {
	short *Tab;
	long *theCell;
	
	/* Calculate a pointer to the GCTabel inside the ProtoType. */
	Tab = (short *) ((long) theProto + (long) theProto->GCTabOff);
	
	/* Handle all the static objects. 
	 * The static table have the following structure:
	 * { .word Offset
	 *   .word Distance_To_Inclosing_Object
	 *   .long T_entry_point
	 * }*
	 * This table contains all static objects on all levels.
	 * Here vi only need to perform ProcessObject on static objects
	 * on 1 level. The recursion in ProcessObject handle other
	 * levels. 
	 * The way to determine the level of an static object is to 
	 * compare the Offset and the Distance_To_Inclosing_Object.
	 */
	
	while( *Tab != 0 ){
	    if( *Tab == -Tab[1] ) 
	      IOACheckObject( Offset( theObj, *Tab * 4));
	    Tab += 4;
	}
	Tab++;
	
	/* Handle all the references in the Object. */
	while (*Tab != 0) {
	    theCell = (long *) Offset(theObj, *Tab++);
	    if (*theCell != 0) IOACheckReference(theCell);
	}
    }
}

void IOACheckReference(theCell)
     handle(Object) theCell;
{
    if( *theCell ){
	if (!(inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell)))
	  Claim( inIOA(*theCell) || inAOA(*theCell) || inLVRA(*theCell),
		"IOACheckReference: *theCell inside IOA, AOA or LVRA");
	if( inLVRA(*theCell) ){
	    Claim( ((ref(ValRep)) *theCell)->GCAttr == (long) theCell,
		  "IOACheckReference:  ((ref(ValRep)) *theCell)->GCAttr == theCell");
	    DEBUG_LVRA( Claim( isValRep(*theCell),
			      "IOACheckReference: isValRep(*theCell)"));
	}
    }
}
#endif
