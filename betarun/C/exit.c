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

#ifdef RTDEBUG

#ifdef MAC
#define PrintMacNumVars()\
  fprintf(output, "PpkVT:    %-8d  ", (int)NumPpkVT);\
  fprintf(output, "PpkCT:    %-8d  ", (int)NumPpkCT);\
  fprintf(output, "PpkSVT:   %-8d\n", (int)NumPpkSVT);\
  fprintf(output, "CopyPPP:  %-8d\n", (int)NumCopyPPP)
#else
#define PrintMacNumVars()
#endif

static void PrintNumVars(void) 
{ 
  fprintf(output, "\n");
  fprintf(output, "AlloI:    %-8d  ", (int)NumAlloI);
  fprintf(output, "AlloC:    %-8d  ", (int)NumAlloC);
  fprintf(output, "AlloDO:   %-8d\n", (int)NumAlloDO);
  fprintf(output, "AlloRR:   %-8d  ", (int)NumAlloRR);
  fprintf(output, "AlloVR1:  %-8d  ", (int)NumAlloVR1);
  fprintf(output, "AlloVR2:  %-8d\n", (int)NumAlloVR2);
  fprintf(output, "AlloVR4:  %-8d  ", (int)NumAlloVR4);
  fprintf(output, "AlloVR8:  %-8d  ", (int)NumAlloVR8);
  fprintf(output, "AlloVRI:  %-8d\n", (int)NumAlloVRI);
  fprintf(output, "AlloVRC:  %-8d  ", (int)NumAlloVRC);
  fprintf(output, "CopyCT:   %-8d  ", (int)NumCopyCT);
  fprintf(output, "CopyRR:   %-8d\n", (int)NumCopyRR);
  fprintf(output, "CopySRR:  %-8d  ", (int)NumCopySRR);
  fprintf(output, "CopySVR1: %-8d  ", (int)NumCopySVR1);
  fprintf(output, "CopySVR2: %-8d\n", (int)NumCopySVR2);
  fprintf(output, "CopySVR4: %-8d  ", (int)NumCopySVR4);
  fprintf(output, "CopySVR8: %-8d  ", (int)NumCopySVR8);
  fprintf(output, "CopySVRI: %-8d\n", (int)NumCopySVRI);
  fprintf(output, "CopySVRC: %-8d  ", (int)NumCopySVRC);
  fprintf(output, "CopyT:    %-8d  ", (int)NumCopyT);
  fprintf(output, "CopyVR1:  %-8d\n", (int)NumCopyVR1);
  fprintf(output, "CopyVR2:  %-8d  ", (int)NumCopyVR2);
  fprintf(output, "CopyVR4:  %-8d  ", (int)NumCopyVR4);
  fprintf(output, "CopyVR8:  %-8d\n", (int)NumCopyVR8);
  fprintf(output, "CopyVRI:  %-8d  ", (int)NumCopyVRI);
  fprintf(output, "CopyVRC:  %-8d  ", (int)NumCopyVRC);
  fprintf(output, "ExtRR:    %-8d\n", (int)NumExtRR);
  fprintf(output, "ExtVR1:   %-8d  ", (int)NumExtVR1);
  fprintf(output, "ExtVR2:   %-8d  ", (int)NumExtVR2);
  fprintf(output, "ExtVR4:   %-8d\n", (int)NumExtVR4);
  fprintf(output, "ExtVR8:   %-8d  ", (int)NumExtVR8);
  fprintf(output, "ExtVRI:   %-8d  ", (int)NumExtVRI);
  fprintf(output, "ExtVRC:   %-8d\n", (int)NumExtVRC);
  fprintf(output, "MkTO:     %-8d  ", (int)NumMkTO);
  fprintf(output, "NewRR:    %-8d  ", (int)NumNewRR);
  fprintf(output, "NewVR1:   %-8d\n", (int)NumNewVR1);
  fprintf(output, "NewVR2:   %-8d  ", (int)NumNewVR2);
  fprintf(output, "NewVR4:   %-8d  ", (int)NumNewVR4);
  fprintf(output, "NewVR8:   %-8d\n", (int)NumNewVR8);
  fprintf(output, "NewVRI:   %-8d  ", (int)NumNewVRI);
  fprintf(output, "NewVRC:   %-8d  ", (int)NumNewVRC);
  fprintf(output, "AlloS:    %-8d\n", (int)NumAlloS);
  fprintf(output, "ThisS:    %-8d  ", (int)NumThisS);
  fprintf(output, "ObjS:     %-8d  ", (int)NumObjS);
  fprintf(output, "AlloSI:   %-8d\n", (int)NumAlloSI);
  fprintf(output, "AlloSC:   %-8d  ", (int)NumAlloSC);
  fprintf(output, "leS:      %-8d  ", (int)NumleS);
  fprintf(output, "geS:      %-8d\n", (int)NumgeS);
  fprintf(output, "gtS:      %-8d  ", (int)NumgtS);
  fprintf(output, "ltS:      %-8d  ", (int)NumltS);
  fprintf(output, "eqS:      %-8d\n", (int)NumeqS);
  fprintf(output, "neS:      %-8d  ", (int)NumneS);
  fprintf(output, "CopyCPP:  %-8d  ", (int)NumCopyCPP);
  fprintf(output, "AlloSICB: %-8d\n", (int)NumAlloSICB);
  fprintf(output, "AlloSO:   %-8d  ", (int)NumAlloSO);
  fprintf(output, "Qua:      %-8d  ", (int)NumQua);
  fprintf(output, "Return:   %-8d\n", (int)NumReturn);
  fprintf(output, "CinitT:   %-8d  ", (int)NumCinitT);
  fprintf(output, "CpkVT:    %-8d  ", (int)NumCpkVT);
  fprintf(output, "CpkSVT:   %-8d\n", (int)NumCpkSVT);
  fprintf(output, "ChkRA:    %-8d  ", (int)NumChkRA);
  fprintf(output, "ExO:      %-8d  ", (int)NumExO);
  fprintf(output, "Att:      %-8d\n", (int)NumAtt);
  fprintf(output, "Susp:     %-8d  ", (int)NumSusp);
  fprintf(output, "TermComp: %-8d\n", (int)NumTermComp);
  PrintMacNumVars();
  fprintf(output, "\n");
  fprintf(output, "AOAAlloc: %-8d\n", (int)NumAOAAlloc);
  fprintf(output, "\n");
  fprintf(output, "IOAGc:    %-8d  ", (int)NumIOAGc);
  fprintf(output, "AOAGc:    %-8d  ", (int)NumAOAGc);
  fprintf(output, "LVRAGc:   %-8d\n", (int)NumLVRAGc);
  fflush(output);

  fprintf(output, "\n");  
}
#endif /* RTDEBUG */

void BetaExit(long number)
{
#if (defined(RTVALHALLA) && !defined(nti_bor))
  if (valhallaID) 
    /* Tell valhalla that we are terminating: */
    ValhallaOnProcessStop (0,0,0,0,0);
#endif /* RTVALHALLA */

  InfoS_End();

#ifdef RTDEBUG
#if defined(UNIX) || defined(NEWRUN) || defined(nti)
#ifdef MT
  if (!TSDReg){
    fprintf(output, "TSDReg is zero!\n"); 
    fflush(output);
  } else
#endif
    PrintNumVars();
#endif /* UNIX */
#endif /* RTDEBUG */

  INFO_HEAP_USAGE(PrintHeapUsage("at exit"));

#ifdef MT
  DEBUG_MT(fprintf(output, "[thread 0x%x terminated]\n", (int)ThreadId);
	   fflush(output);
	   );
  destroy_TSD();

  fflush(stdout);
  fflush(stderr);
  fflush(output);
  if (NumTSD==0) {
    /* NumTSD was decremented to 0 by destroy_TSD so last thread is exiting */
    fclose(output);
    exit(number);
  } else {
    thr_exit(NULL);
  }
#else
  fflush(stdout);
  fflush(stderr);
  fflush(output);

  fclose(output);
  exit(number);
#endif
}

#ifdef RTLAZY
#ifdef RUN
GLOBAL(long RefNonePC) = 0; 
GLOBAL(int *RefNoneStackEnd) = 0;
/* SBRANDT 7/6/94: RefNonePC is set by RefNone in Misc.run to point to return 
 * address after the "call RefNone" instruction during RefNone check. 
 * RefNoneStackEnd is set, also by RefNone, to point out the stackpart 
 * containing the lazy reference. */
GLOBAL(static unsigned char regnum);
GLOBAL(static volatile int InLazyHandler);
#endif
#endif

#ifdef nti /* NOT linux */
extern void CallLazyItem (void);
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

#if 0 /* valhalla not yet ready for hppa */
static __inline__ long GetBetaPC(long errno)
{
  register long PC, SP;
  __asm__ volatile ("COPY\t%%sp, %0" : "=r" (SP)); 
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
#endif
#endif /* hppa */
#endif /* RTVALHALLA */


/* BetaError: */

#ifdef NEWRUN
void BetaError(enum BetaErr err, struct Object *theObj, long *SP, long *thePC)
#else
void BetaError(enum BetaErr err, struct Object *theObj)
#endif
{
#ifndef NEWRUN
  long *thePC;
#else
  DEBUG_CODE(fprintf(output, "BetaError(err=%d, theObj=0x%x, SP=0x%x, thePC=0x%x)\n", err, theObj, SP, thePC));
  DEBUG_CODE(fflush(output));
#endif

  do {
    if( err < 0 ){

      /* Set up StackEnd before calling DisplayBetaStack */

#ifdef NEWRUN
      if (err==RepRangeErr){
	/* Skip frame of HandleIndexErr */
	long SPoff;
	GetSPoff(SPoff, CodeEntry(theObj->Proto, (long)thePC)); 
	SP = (long *) ((long)SP+SPoff);
      }
      StackEnd = SP;
#endif


#ifdef sparc
      __asm__("ta 3");
#ifndef MT
      StackEnd = (long *) ((struct RegWin *)FramePointer)->fp;
#endif /* MT */
      thePC = (long *) ((struct RegWin *)FramePointer)->i7;
#endif /* sparc */


#ifdef hppa
      thePC=(long*)0;
#ifdef RTVALHALLA
#if 0
      thePC=(long *)GetBetaPC(err);
      fprintf(output, "BetaError %d: PC is 0x%x\n", (int)err, (int)thePC);
#endif
#endif /* RTVALHALLA */
#ifdef UseRefStack
      /* RefSP or SP is used - no need to do anything */
#else
#error Find out Stack End for hppa without Reference Stack
#endif /* UseRefStack */
#endif /* hppa */

#ifdef intel
      thePC = 0;
      switch(err){
      case StopCalledErr:
	/* betaenv.stop   -> FailureExit -> BetaError */
	/* betaenvbody.bet   Misc.{c,run}   exit.c    */
	StackEnd = BetaStackTop;
	/* edx, edi, ebp, esi were pushed before calling FailureExit */
	StackEnd += 4;
	break;
      default:
	/* Current object was pushed as the first thing, when
	 * the error was detected. The "thing" just below
	 * is the first real part of the Beta stack
	 */
	StackEnd = (ptr(long)) &theObj; StackEnd++;
	break;
      }
#endif /* intel */

      /* Treat QUA errors specially */
      if (err==QuaErr || err==QuaOrigErr){
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
#ifdef intel
	StackEnd = (long*)((long)StackEnd+10);
	/* We have performed 'pushad', and also we have a return
	 * address from call Qua to ignore.; see Qua.run.
	 * Also the compiler has pushed %edi during the qua-check.
	 */
#else
#endif
#endif
      }

#ifdef RTLAZY
      
      /* Treat REFNONE errors specially */

#ifdef intel
      else if (err==RefNoneErr) {

	/* Check whether it is a genuine error or whether the RefNoneErr
         * was caused by a lazy persistent reference */

	if (LazyItem) {
	  /* If LazyItem is 0, the reference cannot be a dangler, since
	   * the objectserver has not been initialized.
	   *
	   * Fetch the register number from the "cmpl $0,%reg" instruction.
           * This is the register containing the lazy or NONE reference. */ 
	  
#ifdef nti_bor
	  /*   The assembler generates this, regardless of which register:
	   *        
	   *   0000 83F800                cmpl    $0x0,%eax
	   *   0003 7F05                  jg      L1
	   *   0005 E8FCFFFF FF           call    RefNone
	   *   000a                    L1:  
	   */
	  regnum = (* (unsigned char *) (RefNonePC-9)) & 7;
#else /* nti_ms, nti_gnu or linux */
	  /* Binary compiler generates this, regardless of which register:
	   * 0:      testl  reg,reg    # register is in lower 3 bits of second byte
	   * 2:      jg     L1
	   * 4:      call   RefNone
	   * 9:  L1:      
	   */
	  regnum = (* (unsigned char *) (RefNonePC-8)) & 7;
#endif

	  DEBUG_LAZY(switch(regnum){
	  case 0:
	    fprintf(output, "Dangler in %%eax\n"); break;
	  case 1:
	    fprintf(output, "Dangler in %%ecx\n"); break;
	  case 2:
	    fprintf(output, "Dangler in %%edx\n"); break;
	  case 3:
	    fprintf(output, "Dangler in %%ebx\n"); break;
	  case 4:
	    fprintf(output, "Dangler in %%esp!\n"); break;
	  case 5:
	    fprintf(output, "Dangler in %%ebp\n"); break;
	  case 6:
	    fprintf(output, "Dangler in %%esi\n"); break;
	  case 7:
	    fprintf(output, "Dangler in %%edi\n"); break;
	  });

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

	    DEBUG_LAZY(fprintf(output, "Calling LazyItem\n"));
#ifdef linux
	    /* CallLazyItem: */
	    __asm__ volatile ("pushl %ebp # Save base pointer for C");
	    __asm__ volatile ("movl LazyItem,%edi # Call lazy handler");
	    __asm__ volatile ("movl (%edi),%edx");
	    __asm__ volatile ("movl 24(%edx),%edx");
	    __asm__ volatile ("call *%edx");
	    __asm__ volatile ("popl %ebp #restore base pointer");
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
      if (DisplayBetaStack( err, theObj, thePC, 0))
	break; /*  DisplayBetaStack <> 0 => continue execution */
    }    
    BetaExit(1);
  } while (FALSE);
}
