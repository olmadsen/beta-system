/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * betaerror.c
 * by Peter Andersen and Morten Grouleff
 */

#include "beta.h"


/******************** BetaError ******************/

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
#endif /* RUN */
#endif /* RTLAZY */

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
void BetaError(BetaErr err, Object *theObj, long *SP, long *thePC)
#else
void BetaError(BetaErr err, Object *theObj)
#endif
{
#ifndef NEWRUN
  long *thePC;
#endif

  DEBUG_CODE({
    fprintf(output, "\n");
    fprintf(output, "BetaError(err=%d", err);
    PrintBetaError(err);
    fprintf(output, ",\n");
    fprintf(output, "          theObj=0x%x ", (int)theObj);
    DescribeObject(theObj);
    fprintf(output, ",\n");
  });

  do {
    if( err < 0 ){

      /* Set up StackEnd before calling DisplayBetaStack */

#ifdef NEWRUN
      DEBUG_CODE(fprintf(output, "          SP=0x%x,\n", SP));
      DEBUG_CODE(fprintf(output, "          thePC=0x%x", thePC));
      DEBUG_CODE(PrintCodeAddress((long)thePC));
      DEBUG_CODE(fprintf(output, ")\n"));
      switch(err){
      case CTextPoolErr /* called via CpkVT, CpkSVT in betaenv.o */:
      case RepLowRangeErr /* called via CpkSVT, CopySVR*, CopySRR in betaenv.o */:
      case RepHighRangeErr /* called via CpkSVT, CopySVR*, CopySRR in betaenv.o */:
      case QuaErr /* called via Qua in betaenv.o */:
	/* Situation is (here examplified by Qua):
	 * 
	 *    ___________
	 *   |           |
	 *   |   BETA    | (caller of Qua)
	 *   |___________|
	 *   |           | <-- SP
	 *   |   Qua     |
	 *   |___________|
	 *   |           |
	 *   |   CQua    |
	 *   |___________|
	 *   |           |
	 *   | BetaError |
	 *   |___________|
	 *   |           |
	 */
	/* Get PC of caller of (betaenv.o) Qua */
	thePC = (long*)GetPC(SP);
	/* Get current object of caller of (betaenv.o) Qua */
	theObj = (Object *)GetDyn(SP);
	/* DELIBERATELY NO BREAK HERE */
      case RepRangeErr /* called via HandleIndexErr in betaenv.o */:
	{
	  /* Wind back to start of frame of caller of betaenv.o code stub */
	  long SPoff;
	  GetSPoff(SPoff, CodeEntry(theObj->Proto, (long)thePC)); 
	  SP = (long *) ((long)SP+SPoff);
	}
      }
      StackEnd = SP;
#endif /* NEWRUN */


#ifdef sparc
      __asm__("ta 3");
#ifndef MT
      StackEnd = (long *) ((RegWin *)FramePointer)->fp;
#endif /* MT */
      thePC = (long *) ((RegWin *)FramePointer)->i7;
      DEBUG_CODE(fprintf(output, "          StackEnd=0x%x,\n", (int)StackEnd));
      DEBUG_CODE(fprintf(output, "          thePC=0x%x", (int)thePC));
      DEBUG_CODE(PrintCodeAddress((long)thePC));
      DEBUG_CODE(fprintf(output, ")\n"));
#endif /* sparc */


#ifdef hppa
      thePC=(long*)0;
#ifdef RTVALHALLA
#if 0
      thePC=(long *)GetBetaPC(err);
#endif
#endif /* RTVALHALLA */
#ifdef UseRefStack
      /* RefSP or SP is used - no need to do anything */
#else
#error Find out Stack End for hppa without Reference Stack
#endif /* UseRefStack */
      DEBUG_CODE(fprintf(output, "thePC=0x%x", (int)thePC));
      DEBUG_CODE(PrintCodeAddress((long)thePC));
      DEBUG_CODE(fprintf(output, ")\n"));
#endif /* hppa */

#ifdef intel
      switch(err){
      case RepLowRangeErr /* CpkSVT, CopySRR, CopySVRx,  */:
      case RepHighRangeErr /* CpkSVT, CopySRR, CopySVRx,   */:
      case CompCallBackErr /* Susp */:
      case RecursiveAttErr /* Att */:
      case CompTerminatedErr /* Att */:
	/* Should be caught by valhalla, so thePC must be set up.
	 * Current object was pushed as the first thing, when
	 * the error was detected, but the PC was left on stack.
	 * The "thing" two positions below is the first real part 
	 * of the Beta stack
	 */
	StackEnd = (long *) &theObj; 
	StackEnd++; /* One below */
	thePC = *(long**)StackEnd;
	StackEnd++;  /* Two below */
	break;
      case CTextPoolErr /* CpkVT, CpkSVT */:
	/* BETA -> CInitT; BETA -> CpkSVT */
      case StopCalledErr:
	/* betaenv.stop   -> FailureExit        -> BetaError   */
	/* betaenvbody.bet   linuxadditions.run    betaerror.c */
	StackEnd = BetaStackTop;
	/* BetaStackTop was written just before calling FailureExit/Cpk(S)VT,
	 * i.e. the instruction pointer can be found one up
	 * on the stack (the call instruction puts it there).
	 */
	thePC = *(long**)(StackEnd-1);
	/* edx, edi, ebp, esi were pushed before setting BetaStackTop:
	 *   pushl  %edx
	 *   pushl  %edi
	 *   pushl  %ebp
	 *   pushl  %esi
	 *   movl   %esp,BetaStackTop
	 *   call   FailureExit
	 */
	StackEnd += 4;
	break;
      default:
	/* Current object was pushed as the first thing, when
	 * the error was detected. The "thing" just below
	 * is the first real part of the Beta stack.
	 * Hard to figure out thePC.
	 * Caused by:
	 *    RefNoneErr - OK: is handled specially below
	 *    QuaErr - OK: is handled specially below
	 *    LeaveBasicCompErr (ExO) - FIXME
	 *    FIXME: should insert debug assertion that no other errors
	 *           are met here.
	 */
	thePC = 0;
	StackEnd = (long *) &theObj; StackEnd++;
	break;
      }
      DEBUG_CODE(fprintf(output, "          StackEnd=0x%x,\n", (int)StackEnd));
      DEBUG_CODE(fprintf(output, "          thePC=0x%x", (int)thePC));
      DEBUG_CODE(PrintCodeAddress((long)thePC));
      DEBUG_CODE(fprintf(output, ")\n"));
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
	/* Normal Qua error: Display BETA stack */
#ifdef intel
	/* StackEnd initially set up by default case above.
	 * Adjust StackEnd before calling DisplayBetaStack.
	 * We have performed 'pushad' (8 longs), and also we have a return
	 * address from call Qua to ignore.; see Qua.run.
	 * Also the compiler has pushed %edi during the qua-check.
	 * This sums up to 10 longs to skip.
	 * Stack: 
	 *    <theobj>
	 *    <8 regs>            <-- StackEnd
	 *    <return-from-Qua>   <-- StackEnd+8
	 *    <%edi>              <-- StackEnd+9
	 *                        <-- StackEnd+10
	 */
	thePC=(long*)(StackEnd[8]); /* StackEnd is long* */
	StackEnd+=10; /* StackEnd is long* */
#endif /* intel */
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

	  /* Binary compiler generates this, regardless of which register:
	   * 0:      testl  reg,reg    # register is in lower 3 bits of second byte
	   * 2:      jg     L1
	   * 4:      call   RefNone
	   * 9:  L1:      
	   */
	  regnum = (* (unsigned char *) (RefNonePC-8)) & 7;
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
	 * Ignore 12 pushed registers/tags (see RefNone in Misc.run)
	 * AND the return address to current object (current object
	 * is displayed specially).
	 */
	StackEnd += 12+1;
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

/******************** ErrorMessage ******************/

static const struct errorEntry 
{
  BetaErr  errorNumber;
  char    *errorMessage;
} 
errorTable[] = 
{
  { RefNoneErr,        "Reference is none" },
  { CompTerminatedErr, "Executing terminated component" },
  { RepRangeErr,       "Repetition index out of range" },
  { ArithExceptErr,    "Arithmetic exception" },
  { RepSubRangeErr,    "Repetition subrange out of range" },
  { RepLowRangeErr,    "Repetition subrange out of range (low)" },
  { RepHighRangeErr,   "Repetition subrange out of range (high)" },
  { StopCalledErr,     "Stop is called" },
  { LVRAfullErr,       "LVRA is full" },
  { ZeroDivErr,        "Integer division by zero" },
  { CBFAfullErr,       "Call back function area (CBFA) is full" },
  { PascalCallBackErr, "Call back Pascal function has wrong return size" },
  { CompCallBackErr,   "Suspending component involving call backs" },
  { LeaveBasicCompErr, "Illegal leave/restart" },
  { QuaErr,            "Qualification error in reference assignment" },
  { QuaOrigErr,        "Qualification error in reference assignment; origins differ" },
  { RecursiveAttErr,   "Attach of component that is already attached" },
  { IOAFullErr,        "IOA heap is full" },
  { FpZeroDivErr,      "Floating Point division by zero" },
  { FpExceptErr,       "Floating Point exception" },
#ifdef intel
  { FpStackUflowErr,   "Floating Point stack underflow" },
  { FpStackOflowErr,   "Floating Point stack overflow" },
#endif
#ifdef RTDEBUG
  { InterruptErr,      "User Interrupt" },
#endif
  { EmulatorTrapErr,   "Emulator trap" },
  { IllegalInstErr,    "Illegal instruction" },
  { BusErr,            "Bus error" },
#ifdef UNIX
  { SegmentationErr,   "Segmentation fault" },
#else
  { SegmentationErr,   "Access violation" },
#endif /* UNIX */
  { AOAtoIOAfullErr,   "AOAtoIOAtable is full" },
  { AOAtoLVRAfullErr,  "AOAtoLVRAtable is full" },
  { CTextPoolErr,      "Text parameter to C routine too big (max. 1000 bytes)" },
  { AOAtoIOAallocErr,  "Failed to allocate AOAtoIOAtable" },
  { UnorderedFval,     "Unordered Floating Point value in comparison" },
#ifdef MT
  { StackErr,          "Component Stack Overflow" },
#else
  { StackErr,          "Stack Overflow" },
#endif
#ifdef UNIX
  { UnknownSigErr,     "Unknown signal" },
#else
  { UnknownSigErr,     "Unknown exception" },
#endif
  { 0, 0 }
  };

GLOBAL(static char UnknownError[25]);

char *ErrorMessage(BetaErr errorNumber)
{
  long  index = 0;
  
  while( errorTable[index].errorNumber != 0){
    if( errorNumber == errorTable[index].errorNumber){
      BetaErrorString = errorTable[index].errorMessage; /* For Valhalla */
      return errorTable[index].errorMessage;
    }
    index++;
  }
  sprintf(UnknownError, "Unknown error (%d)", (int)errorNumber);
  BetaErrorString = UnknownError;
  return UnknownError;
}

#ifdef RTDEBUG
void PrintBetaError(BetaErr err)
{
  fprintf(output, " <");
  switch(err){
  case RefNoneErr:
    fprintf(output, "RefNoneErr"); break; 
  case CompTerminatedErr:
    fprintf(output, "CompTerminatedErr"); break;
  case RepRangeErr:
    fprintf(output, "RepRangeErr"); break;      
  case ArithExceptErr:
    fprintf(output, "ArithExceptErr"); break;   
  case RepSubRangeErr:
    fprintf(output, "RepSubRangeErr"); break;   
  case RepLowRangeErr:
    fprintf(output, "RepLowRangeErr"); break;   
  case RepHighRangeErr:
    fprintf(output, "RepHighRangeErr"); break;  
  case StopCalledErr:
    fprintf(output, "StopCalledErr"); break;    
  case LVRAfullErr:
    fprintf(output, "LVRAfullErr"); break;      
  case ZeroDivErr:
    fprintf(output, "ZeroDivErr"); break;       
  case CBFAfullErr:
    fprintf(output, "CBFAfullErr"); break;      
  case PascalCallBackErr:
    fprintf(output, "PascalCallBackErr"); break;
  case CompCallBackErr:
    fprintf(output, "CompCallBackErr"); break;  
  case LeaveBasicCompErr:
    fprintf(output, "LeaveBasicCompErr"); break;
  case QuaErr:
    fprintf(output, "QuaErr"); break;           
  case QuaOrigErr:
    fprintf(output, "QuaOrigErr"); break;  
  case RecursiveAttErr:
    fprintf(output, "RecursiveAttErr"); break;  
  case IOAFullErr:
    fprintf(output, "IOAFullErr"); break;       
  case FpZeroDivErr:
    fprintf(output, "FpZeroDivErr"); break;     
  case FpExceptErr:
    fprintf(output, "FpExceptErr"); break;      
#ifdef intel	     
  case FpStackUflowErr:
    fprintf(output, "FpStackUflowErr"); break;  
  case FpStackOflowErr:
    fprintf(output, "FpStackOflowErr"); break;  
#endif		     
  case InterruptErr:
    fprintf(output, "InterruptErr"); break;     
  case EmulatorTrapErr:
    fprintf(output, "EmulatorTrapErr"); break;  
  case IllegalInstErr:
    fprintf(output, "IllegalInstErr"); break;   
  case BusErr:
    fprintf(output, "BusErr"); break;           
  case SegmentationErr:
    fprintf(output, "SegmentationErr"); break;  
  case AOAtoIOAfullErr:
    fprintf(output, "AOAtoIOAfullErr"); break;  
  case AOAtoLVRAfullErr:
    fprintf(output, "AOAtoLVRAfullErr"); break; 
  case CTextPoolErr:
    fprintf(output, "CTextPoolErr"); break;     
  case AOAtoIOAallocErr:
    fprintf(output, "AOAtoIOAallocErr"); break; 
  case UnorderedFval:
    fprintf(output, "UnorderedFval"); break;    
  case StackErr:
    fprintf(output, "StackErr"); break;         
  case UnknownSigErr:
    fprintf(output, "UnknownSigErr"); break;    
  default:
    fprintf(output, "Unknown Error!"); break;    
  }
  fprintf(output, ">");
  fflush(output);
}
#endif /* RTDEBUG */
