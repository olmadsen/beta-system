/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * exit.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann,
 *    S|ren Brandt and S|ren Pingel Dalsgaard
 */

#include "beta.h"
#ifdef RTVALHALLA
#include "valhallaComm.h"
#endif /* RTVALHALLA */

void BetaExit( number )
     long number;
{
#ifdef RTVALHALLA
  if (valhallaID) 
    /* Tell valhalla that we are terminating: */
    ValhallaOnProcessStop (0,0,0,0,0);
#endif /* RTVALHALLA */

  InfoS_End();

#ifdef RTDEBUG
#if defined(UNIX) || defined (crts)
  fprintf(stderr, "\n");
  fprintf(stderr, "IOAGc:    %-8d  ", (int)NumIOAGc);
  fprintf(stderr, "AOAGc:    %-8d  ", (int)NumAOAGc);
  fprintf(stderr, "LVRAGc:   %-8d\n", (int)NumLVRAGc);
  fprintf(stderr, "\n");
  fprintf(stderr, "AlloI:    %-8d  ", (int)NumAlloI);
  fprintf(stderr, "AlloC:    %-8d  ", (int)NumAlloC);
  fprintf(stderr, "AlloDO:   %-8d\n", (int)NumAlloDO);
  fprintf(stderr, "AlloRR:   %-8d  ", (int)NumAlloRR);
  fprintf(stderr, "AlloVR1:  %-8d  ", (int)NumAlloVR1);
  fprintf(stderr, "AlloVR2:  %-8d\n", (int)NumAlloVR2);
  fprintf(stderr, "AlloVR4:  %-8d  ", (int)NumAlloVR4);
  fprintf(stderr, "AlloVR8:  %-8d  ", (int)NumAlloVR8);
  fprintf(stderr, "AlloORR:  %-8d\n", (int)NumAlloORR);
  fprintf(stderr, "AlloORRC: %-8d  ", (int)NumAlloORRC);
  fprintf(stderr, "CopyCT:   %-8d  ", (int)NumCopyCT);
  fprintf(stderr, "CopyRR:   %-8d\n", (int)NumCopyRR);
  fprintf(stderr, "CopySRR:  %-8d  ", (int)NumCopySRR);
  fprintf(stderr, "CopySVR:  %-8d  ", (int)NumCopySVR);
  fprintf(stderr, "CopyT:    %-8d\n", (int)NumCopyT);
  fprintf(stderr, "CopyVR:   %-8d  ", (int)NumCopyVR);
  fprintf(stderr, "ExtRR:    %-8d  ", (int)NumExtRR);
  fprintf(stderr, "ExtVR:    %-8d\n", (int)NumExtVR);
  fprintf(stderr, "MkTO:     %-8d  ", (int)NumMkTO);
  fprintf(stderr, "NewRR:    %-8d  ", (int)NumNewRR);
  fprintf(stderr, "NewVR:    %-8d\n", (int)NumNewVR);
  fprintf(stderr, "AlloS:    %-8d  ", (int)NumAlloS);
  fprintf(stderr, "ThisS:    %-8d  ", (int)NumThisS);
  fprintf(stderr, "ObjS:     %-8d\n", (int)NumObjS);
  fprintf(stderr, "AlloSI:   %-8d  ", (int)NumAlloSI);
  fprintf(stderr, "AlloSC:   %-8d  ", (int)NumAlloSC);
  fprintf(stderr, "leS:      %-8d\n", (int)NumleS);
  fprintf(stderr, "geS:      %-8d  ", (int)NumgeS);
  fprintf(stderr, "gtS:      %-8d  ", (int)NumgtS);
  fprintf(stderr, "ltS:      %-8d\n", (int)NumltS);
  fprintf(stderr, "eqS:      %-8d  ", (int)NumeqS);
  fprintf(stderr, "neS:      %-8d  ", (int)NumneS);
  fprintf(stderr, "CopyCPP:  %-8d\n", (int)NumCopyCPP);
  fprintf(stderr, "AlloSICB: %-8d  ", (int)NumAlloSICB);
  fprintf(stderr, "AlloSO:   %-8d  ", (int)NumAlloSO);
  fprintf(stderr, "Qua:      %-8d\n", (int)NumQua);
  fprintf(stderr, "Return:   %-8d  ", (int)NumReturn);
  fprintf(stderr, "CinitT:   %-8d  ", (int)NumCinitT);
  fprintf(stderr, "CpkVT:    %-8d\n", (int)NumCpkVT);
  fprintf(stderr, "CpkSVT:   %-8d  ", (int)NumCpkSVT);
  fprintf(stderr, "ChkRA:    %-8d  ", (int)NumChkRA);
  fprintf(stderr, "ExO:      %-8d\n", (int)NumExO);
  fprintf(stderr, "Att:      %-8d  ", (int)NumAtt);
  fprintf(stderr, "Susp:     %-8d  ", (int)NumSusp);
  fprintf(stderr, "TermComp: %-8d\n", (int)NumTermComp);
  fprintf(stderr, "\n");
  fprintf(stderr, "AOAAlloc: %-8d\n", (int)NumAOAAlloc);
  fprintf(stderr, "\n");
#endif /* UNIX */
#endif /* RTDEBUG */

#ifdef apollo
  AsmExit( number );
#else
  exit( number );
#endif
}

#ifdef RTLAZY
#if defined(linux) || defined(nti) || defined(macintosh)
long RefNonePC = 0; 
int *RefNoneStackEnd = 0;
/* SBRANDT 7/6/94: RefNonePC is set by RefNone in Misc.run to point to return 
 * address after the "call RefNone" instruction during RefNone check. 
 * RefNoneStackEnd is set, also by RefNone, to point out the stackpart 
 * containing the lazy reference. */
static unsigned char regnum;
static volatile int InLazyHandler;
#endif
#endif

#if defined(macintosh) || defined(nti)
extern void CallLazyItem ();
#endif


#ifdef RTVALHALLA
#ifdef hppa
/* Stupid very machine dependent function needed to
 * find the PC when BetaError has been called.
 * FrameSizes must be checked after each code change! (:-(
 */

#define BetaErrorFrameSize 0x80
#define RefNoneFrameSize 0x80
#define HandleIndexErrFrameSize 0x80

static inline long GetBetaPC(long errno)
{
  register long PC, SP;
  asm volatile ("COPY\t%%sp, %0" : "=r" (SP)); 
  SP = (SP-BetaErrorFrameSize); /* SP in function that called BetaError */
  switch(errno){
  case RepRangeErr:
    PC = *(long *)(SP-HandleIndexErrFrameSize-0x14);
    break;
  case RefNoneErr:
    PC = *(long *)(SP-RefNoneFrameSize-0x14);
    break;
  default:
    printf("GetBetaPC: error not yet handled\n");
    PC=0;
  }
  return PC & ~3 /* The lower bits are not always cleared in the rp register */;
}
#endif /* hppa */
#endif /* RTVALHALLA */


/* BetaError: */

#ifdef NEWRUN
void BetaError(long errorNo, struct Object *theObj, long *SP, long *thePC)
#else
void BetaError(long errorNo, struct Object *theObj)
#endif
{
#ifndef NEWRUN
  long *thePC;
#endif

  do {
    if( errorNo < 0 ){

      /* Set up StackEnd before calling DisplayBetaStack */

#ifdef NEWRUN
	StackEnd = SP;
#endif


#ifdef sparc
      asm("ta 3");
      StackEnd = (long *) ((struct RegWin *)FramePointer)->fp;
      thePC = (long *) ((struct RegWin *)FramePointer)->i7;
#endif /* sparc */


#ifdef hppa
#ifdef RTVALHALLA
      thePC=(long *)GetBetaPC(errorNo);
      fprintf(output, "BetaError %d: PC is 0x%x\n", (int)errorNo, (int)thePC);
#else
      thePC=(long*)0;
#endif /* RTVALHALLA */
#ifdef UseRefStack
      /* RefSP or SP is used - no need to do anything */
#else
#error Find out Stack End for hppa without Reference Stack
#endif /* UseRefStack */
#endif /* hppa */


#ifdef crts
      getret(thePC);
#endif


#if defined(mac) || defined(hpux9mc) || defined(intel)
      /* Ordinary MOTOROLA-like stack */
      thePC = 0;
      switch(errorNo){
      case StopCalledErr:
	/* betaenv.stop   -> FailureExit -> BetaError */
	/* betaenvbody.bet   Misc.{c,run}   exit.c    */
	StackEnd = BetaStackTop;
#ifdef mc68020
	/* a0 and a1 were pushed before calling FailureExit */
	StackEnd += 2;
#endif
#ifdef intel
	/* edx, edi, ebp, esi were pushed before calling FailureExit */
	StackEnd += 4;
#endif
	break;
      default:
	/* Current object was pushed as the first thing, when
	 * the error was detected. The "thing" just below
	 * is the first real part of the Beta stack
	 */
	StackEnd = (ptr(long)) &theObj; StackEnd++;
	break;
      }
#endif

      /* Treat QUA errors specially */
      if (errorNo==QuaErr || errorNo==QuaOrigErr){
	if (QuaCont) {
	  fprintf(output, "\n*** OBS. ");
	  fprintf(output, ErrorMessage(QuaErr));
	  if( theObj != 0 ){
	    if( isObject(theObj)){
	      fprintf(output, ".\nCurrent object:\n");
	      DisplayObject(output, theObj, (long)thePC);
	    }else{
	      fprintf(output,"Current object is damaged!\n");
	    }
	  } else {
	    fprintf(output,"Current object is 0!\n");
	  }
	  fprintf(output, "(continuing)\n");
	  fflush(output);
	  break; /* Don't BetaExit() */
	}
	/* Normal Qua error: Display BETA stack.
	 * Adjust StackEnd before calling DisplayBetaStack.
	 */
#ifndef sparc
#if defined(linux) || defined(nti)
	(long *)StackEnd += 10;
	/* We have performed 'pushad', and also we have a return
	 * address from call Qua to ignore.; see Qua.run.
	 * Also the compiler has pushed %edi during the qua-check.
	 */
#else
#ifdef mc68020
	(long *)StackEnd += 15;
	/* We have saved a0-a4, d0-d7, and also we have a return
	 * address from jsr Qua to ignore.; see Qua.run.
	 * Also the compiler has pushed a1 during the qua-check.
	 */
#endif
#endif
#endif
      }

#ifdef RTLAZY
      
      /* Treat REFNONE errors specially */

#if defined(macintosh)
      else if (errorNo==RefNoneErr) {

	/* Check whether it is a genuine error or whether the RefNoneErr
         * was caused by a lazy persistent reference */

	if (LazyItem) {
	  /* If LazyItem is 0, the reference cannot be a dangler, since
	   * the objectserver has not been initialized.
	   *
	   * Fetch the register number "n" from the "move.l am,dn" instruction.
           * This is the register containing the lazy or NONE reference. */ 
	  
	  regnum = ((* (short *) (RefNonePC-12)) >> 9) & 7;
	  
	  /* RefNone pushed data registers as shown below. The register
	   * (if any) containing a lazy reference must be found  by the
	   * garbage collector in order to be updated by the lazy fetch
           * mechanism. This is ensured by clearing the "-5" pushed
	   * after the relevant register.
	   *
	   * Notice: Stack grows downwards.
	   *                      ____
	   *                     | d7 |
	   *                     | -5 |
	   *                     | d6 |
	   *                     | -5 |
	   *                     | d5 |
	   *                     | -5 |
	   *                     | d4 |
	   *                     | -5 |
	   *                     | d3 |
	   *                     | -5 |
	   *                     | d2 |
	   *                     | -5 |
	   *                     | d1 |
	   *                     | -5 |
	   *                     | d0 |
	   * RefNoneStackEnd ->  | -5 |
	   *                      ----                              */

	  fprintf (output,"Lazy ref in register %d\n", regnum);

	  LazyDangler = RefNoneStackEnd[2*regnum+1];
	  RefNoneStackEnd[2*regnum] = 0;
	  
	  if (LazyDangler) {
	    
	    if (InLazyHandler)
	      fprintf (output,"WARNING: Lazy fetch reentered !\n");
	    
	    /* The stack now hopefully has a layout that wont setup the
	     * garbage collector. Call back to BETA to fetch the missing
	     * object. */
	    
	    InLazyHandler = 1;
	    
	    /* call beta object handling the lazy fetch. */
	    CallLazyItem ();
	    
	    InLazyHandler = 0;
		  
	    return;
	  }
	}
	/* Normal RefNone error: Display BETA stack.
	 * Adjust StackEnd before calling DisplayBetaStack.
	 */
	StackEnd += 20;
	  /* Ignore 4 adr regs, and 8 dataregs+tags (see RefNone
	   * in Misc.run)
	   */
	thePC=(long *)RefNonePC;
      }
#endif /* mac */
#if defined(linux) || defined(nti)
      else if (errorNo==RefNoneErr) {

	/* Check whether it is a genuine error or whether the RefNoneErr
         * was caused by a lazy persistent reference */

	if (LazyItem) {
	  /* If LazyItem is 0, the reference cannot be a dangler, since
	   * the objectserver has not been initialized.
	   *
	   * Fetch the register number from the "cmpl $0,%reg" instruction.
           * This is the register containing the lazy or NONE reference. */ 
	  
	  regnum = (* (unsigned char *) (RefNonePC-9)) & 7;
	  
	  /* RefNone pushed data registers as shown below. The register
	   * (if any) containing a lazy reference must be found  by the
	   * garbage collector in order to be updated by the lazy fetch
           * mechanism. This is ensured by clearing the "-5" pushed
	   * after the relevant register.
	   *
	   * Notice: Stack grows downwards.
	   *                      _____
	   *                     | eax |
	   *                     | -5  |
	   *                     | ecx |
	   *                     | -5  |
	   *                     | ebx |
	   * RefNoneStackEnd ->  | -5  |
	   *                      -----                              */
	  
	  switch (regnum) {
	  case 0: 
	    LazyDangler = RefNoneStackEnd[5]; RefNoneStackEnd[4] = 0;
	    break;
	  case 3: 
	    LazyDangler = RefNoneStackEnd[1]; RefNoneStackEnd[0] = 0;
	    break;
	  case 1: 
	    LazyDangler = RefNoneStackEnd[3]; RefNoneStackEnd[2] = 0;
	    break;
	  default:
	    LazyDangler = 0; break;
	  }
	  
	  if (LazyDangler) {
	    
	    if (InLazyHandler)
	      fprintf (output,"WARNING: Lazy fetch reentered !\n");
	    
	    /* The stack now hopefully has a layout that wont setup the
	     * garbage collector. Call back to BETA to fetch the missing
	     * object. */
	    
	    InLazyHandler = 1;
	    
	    /* call beta object handling the lazy fetch.
	     * To ensure that the C return statement works correctly, we
	     * need to save %ebp, the stack-base register. There's no 
	     * need to save other registers, since we will be returning 
	     * to RefNone immediately after calling BETA. */

#ifdef linux
	    asm volatile ("pushl %ebp # Save base pointer for C");
	    asm volatile ("movl LazyItem,%edi # Call lazy handler");
	    asm volatile ("movl (%edi),%edx");
	    asm volatile ("movl -4(%edx),%edx");
	    asm volatile ("call *%edx");
	    asm volatile ("popl %ebp #restore base pointer");
#else
	    /* NTI: Borland C is not good at inline assembler */
	    CallLazyItem();
#endif /* linux */

	    InLazyHandler = 0;
		  
	    return;
	  }
	}
	/* Normal RefNone error: Display BETA stack.
	 * Adjust StackEnd before calling DisplayBetaStack.
	 */
	StackEnd += 12
	  /* Ignore 12 pushed registers/tags (see RefNone in Misc.run)
	   */;
	thePC=(long *)RefNonePC;
      }
#endif /* linux || nti */
#endif /* RTLAZY */

      /* If not QUA error with QuaCont or 
       * REFNONE error with lazy reference, 
       * we fall through to here */
      if (DisplayBetaStack( errorNo, theObj, thePC, 0))
	break; /*  DisplayBetaStack <> 0 => continue execution */
    }    
    BetaExit(1);
  } while (FALSE);
}
