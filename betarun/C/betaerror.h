enum BetaErr {
  RefNoneErr =         -1 /* Reference is none */,
  CompTerminatedErr =  -2 /* Executing terminated component */,
  RepRangeErr =        -3 /* Repetition index out of range */,
  ArithExceptErr =     -4 /* Arithmetic exception */,
  RepSubRangeErr =     -5 /* Repetition subrange out of range */,
  RepLowRangeErr =     -6 /* Repetition subrange out of range (low) */,
  RepHighRangeErr =    -7 /* Repetition subrange out of range (high) */,
  StopCalledErr =      -8 /* Stop is called */,
  LVRAfullErr =        -9 /* LVRA is full */,
  ZeroDivErr =        -10 /* Integer division by zero */,
  CBFAfullErr =       -11 /* Call back function area (CBFA) is full (obsolete) */,
  PascalCallBackErr = -12 /* Call back Pascal function has wrong return size */,
  CompCallBackErr =   -13 /* Suspending component involving call backs */,
  LeaveBasicCompErr = -14 /* Attempt to leave basic component */,
  QuaErr =            -15 /* Qualification error in reference assignment */,
  QuaOrigErr =        -16 /* Qualification error in reference assignment; origins differ */,
  RecursiveAttErr =   -17 /* Attempt to attach a component that is already attached */,
  IOAFullErr =        -18 /* IOA heap is full */,
#ifdef RTDEBUG	     	  
  InterruptErr =      -28 /* User Interupt */,
#endif		     	  
		     	  
  EmulatorTrapErr =   -29 /* Emulator trap */,
  IllegalInstErr =    -30 /* Illegal instruction */,
  BusErr =            -31 /* Bus error */,
  SegmentationErr =   -32 /* Segmentation fault */,
  AOAtoIOAfullErr =   -33 /* AOAtoIOAtable is full */,
  AOAtoLVRAfullErr =  -34 /* AOAtoLVRAtable is full */,
  CTextPoolErr =      -35 /* Text parameter to C routine too big (max. 1000 bytes) */,
  AOAtoIOAallocErr =  -36 /* Failed to allocate AOAtoIOAtable */,
  UnorderedFval =     -37 /* Unordered Floating Point Value */,
  UnknownSigErr =    -100 /* Unknown signal */
};
