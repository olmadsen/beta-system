/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-94 Mjolner Informatics Aps.
 * betaerror.c
 * by Peter Andersen and Morten Grouleff
 */

#include "beta.h"


/******************** BetaError ******************/

#ifdef RUN
GLOBAL(long RefNonePC) = 0; 
GLOBAL(int *RefNoneStackEnd) = 0;
/* SBRANDT 7/6/94: RefNonePC is set by RefNone in Misc.run to point to return 
 * address after the "call RefNone" instruction during RefNone check. 
 * RefNoneStackEnd is set, also by RefNone, to point out the stackpart 
 * containing the lazy reference.
 * datpete: 26/05/2000: probably not needed anymore.
 */
#endif /* RUN */

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
void BetaError(BetaErr err, Object *theObj, long *SP, pc_t thePC)
#else
void BetaError(BetaErr err, Object *theObj)
#endif
{
#ifndef NEWRUN
  pc_t thePC;
#endif

  long DoNotExit=0; /* used in DumpStackErr */

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

      if (err == DumpStackErr){
	if (SkipDumpStack) {
	  return;
	} else {
	  DoNotExit = 1;  /* note no break here !! */
	}
      }

      /* Set up StackEnd before calling DisplayBetaStack */

#ifdef NEWRUN
      DEBUG_CODE(fprintf(output, "          SP=0x%x,\n", SP));
      DEBUG_CODE(fprintf(output, "          thePC=0x%x", (int)thePC));
      DEBUG_CODE(PrintCodeAddress(thePC));
      DEBUG_CODE(fprintf(output, ")\n"));
      switch(err){
      case StopCalledErr /* called via FailureExit in betaenv.o */:
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
	thePC = GetPC(SP);
	/* Get current object of caller of (betaenv.o) Qua */
	theObj = (Object *)GetDyn(SP);
	/* DELIBERATELY NO BREAK HERE */
      case RepRangeErr /* called via HandleIndexErr in betaenv.o */:
	/* DELIBERATELY NO BREAK HERE */
      case LeaveBasicCompErr:
	/* Wind back to start of frame of caller of betaenv.o code stub */
	SP = (long*)WindBackSP((long)SP, theObj, (long)thePC);
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
      DEBUG_CODE(PrintCodeAddress(thePC));
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
      DEBUG_CODE(PrintCodeAddress(thePC));
      DEBUG_CODE(fprintf(output, ")\n"));
#endif /* hppa */

#ifdef intel
      switch(err){
      case RepLowRangeErr /* CpkSVT, CopySRR, CopySVRx,  */:
      case RepHighRangeErr /* CpkSVT, CopySRR, CopySVRx,   */:
      case CompCallBackErr /* Susp */:
      case RecursiveAttErr /* Att */:
      case CompTerminatedErr /* Att */:
      case LeaveBasicCompErr /* ExO*/:
	/* Should be caught by valhalla, so thePC must be set up.
	 * Current object was pushed as the first thing, when
	 * the error was detected, but the PC was left on stack.
	 * The "thing" two positions below is the first real part 
	 * of the Beta stack
	 */
	StackEnd = (long *) &theObj; 
	StackEnd++; /* One below */
	thePC = (pc_t)(*(long**)StackEnd);
	StackEnd++;  /* Two below */
	break;
      case DumpStackErr:
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
	thePC = (pc_t)(*(long**)(StackEnd-1));
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
	 *    FIXME: should insert debug assertion that no other errors
	 *           are met here.
	 */
	thePC = 0;
	StackEnd = (long *) &theObj; StackEnd++;
	break;
      }
      DEBUG_CODE(fprintf(output, "          StackEnd=0x%x,\n", (int)StackEnd));
      DEBUG_CODE(fprintf(output, "          thePC=0x%x", (int)thePC));
      DEBUG_CODE(PrintCodeAddress(thePC));
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
	      DisplayObject(output, theObj, thePC);
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
	thePC=(pc_t)(StackEnd[8]); /* StackEnd is long* */
	StackEnd+=10; /* StackEnd is long* */
#endif /* intel */
      }

#ifdef intel
      else if (err==RefNoneErr) {
	/* RefNone error: Display BETA stack.
	 * Adjust StackEnd before calling DisplayBetaStack.
	 * Ignore 12 pushed registers/tags (see RefNone in Misc.run)
	 * AND the return address to current object (current object
	 * is displayed specially).
	 */
	StackEnd += 12+1;
	thePC=(pc_t)RefNonePC;
      }
#endif /* intel */
      
      /* If not QUA error with QuaCont or REFNONE error, 
       * we fall through to here */

      if (DisplayBetaStack( err, theObj, thePC, 0)) {
	break; /*  DisplayBetaStack <> 0 => continue execution */
      } else {
	if (DoNotExit) {
	  break;
	} 
      }
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
  { EmulatorTrapErr,   "Breakpoint trap" },
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
  { DumpStackErr,      "Program requested Stack Dump" },
  { InternalErr,       "Internal Error" },
  { SignalErr,         "Unexpected Signal" },
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
  long  dummy;
  
  dummy = strlen(UnknownError);
  
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
  case DumpStackErr:
    fprintf(output, "DumpStackErr"); break;         
  case UnknownSigErr:
    fprintf(output, "UnknownSigErr"); break;    
  default:
    fprintf(output, "Unknown Error!"); break;    
  }
  fprintf(output, ">");
  fflush(output);
}
#endif /* RTDEBUG */

/* Function called by COM code in case of
 * COM virtual called with struct parameter transfered by
 * value (not yet implemented).
 */
void _struct_param_by_value(void)
{
  fprintf(output, 
	  "RTS: Warning: \n"
	  "  COM virtual called with struct parameter transferred by value.\n"
	  "This is not yet implemented, sorry!\n");
  return;
}
