/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * exit.c
 * by Lars Bak, Peter Andersen, Peter Orbaek, Tommy Thorn, Jacob Seligmann,
 *    S|ren Brandt and S|ren Pingel Dalsgaard
 */

#include "beta.h"

void BetaExit( number )
     long number;
{
#ifdef RTDEBUG
  char buf[100];
#endif /* RTDEBUG */

  InfoS_End();
#ifdef RTDEBUG
  sprintf(buf, "NumIOAGc: %d, NumAOAGc: %d, NumLVRAGc: %d", 
	  NumIOAGc, NumAOAGc, NumLVRAGc);
  Notify(buf);
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


void BetaError(errorNo, theObj)
     long errorNo;
     ref(Object) theObj;
{
  long *thePC;

  do {
    if( errorNo < 0 ){
#ifdef sparc
      asm("ta 3");
      StackEnd = (long *) ((struct RegWin *)FramePointer)->fp;
      thePC = (long *) ((struct RegWin *)FramePointer)->i7;
#else
#if !(defined(hppa) && defined(REFSTACK))
      StackEnd = (ptr(long)) &theObj; StackEnd++;
      /* Current object was pushed as the first thing, when
       * the error was detected. The "thing" just below
       * is the first real part of the Beta stack
       */
#endif /* hppa && REFSTACK */
      thePC = 0;
#endif
      if (errorNo==QuaErr || errorNo==QuaOrigErr){
	if (QuaCont) {
	  fprintf(output, "\n*** OBS. ");
	  fprintf(output, ErrorMessage(QuaErr));
	  fprintf(output, ".\nCurrent object:\n");
	  if( theObj != 0 ){
	    if( isObject(theObj)){
	      DisplayObject(output, theObj, 0);
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
#ifndef sparc
#if defined(linux) || defined(nti)
	(long *)StackEnd += 9;
	/* We have performed 'pushad', and also we have a return
	 * address from call Qua to ignore.; see Qua.run.
	 */
#else
#ifndef hppa
	(long *)StackEnd += 14;
	/* We have saved a0-a4, d0-d7, and also we have a return
	 * address from jsr Qua to ignore.; see Qua.run.
	 */
#endif
#endif
#endif
      }
#ifdef RTLAZY
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

	  printf ("Lazy ref in register %d\n", regnum);

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
	    asm volatile ("movl _LazyItem,%edi # Call lazy handler");
	    asm volatile ("movl (%edi),%edx");
	    asm volatile ("movl -4(%edx),%edx");
	    asm volatile ("call *%edx");
	    asm volatile ("popl %ebp #restore base pointer");

#else

	    /* Borland C is not good at inline assembler */
	    CallLazyItem();

#endif

	    InLazyHandler = 0;
		  
	    return;
	  }
	}
      }
#endif
#endif
      if (DisplayBetaStack( errorNo, theObj, thePC, 0))
	break; /*  DisplayBetaStack <> 0 => continue execution */
    }    
    BetaExit(1);
  } while (FALSE);
  asmemptylabel(BetaErrorEnd);
}
