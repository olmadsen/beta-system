#define RefNoneErr          -1 /* Reference is none */
#define CompTerminatedErr   -2 /* Executing terminated component */
#define RepRangeErr         -3 /* Repetition index out of range */
#define ArithExceptErr      -4 /* Arithmetic exception */
#define RepSubRangeErr      -5 /* Repetition subrange out of range */
#define RepLowRangeErr      -6 /* Repetition subrange out of range */
#define RepHighRangeErr     -7 /* Repetition subrange out of range */
#define StopCalledErr       -8 /* Stop is called */
#define LVRAfullErr         -9 /* LVRA is full */
#define ZeroDivErr         -10 /* Integer division by zero */
#define CBFAfullErr        -11 /* Call back function area (CBFA) is full (obsolete) */
#define PascalCallBackErr  -12 /* Call back Pascal function has wrong return size */
#define CompCallBackErr    -13 /* Suspending component involving call backs */
#define LeaveBasicCompErr  -14 /* Attempt to leave basic component */
#define QuaErr             -15 /* Qualification error in reference assignment */
#define QuaOrigErr         -16 /* Qualification error in reference assignment; origins differ */
#define RecursiveAttErr    -17 /* Attempt to attach a component that is already attached */

#define EmulatorTrapErr    -29 /* Emulator trap */
#define IllegalInstErr     -30 /* Illegal instruction */
#define BusErr             -31 /* Bus error */
#define SegmentationErr    -32 /* Segmentation fault */
#define AOAtoIOAfullErr    -33 /* AOAtoIOAtable is full */
#define AOAtoLVRAfullErr   -34 /* AOAtoLVRAtable is full */
#define CTextPoolErr       -35 /* Text parameter to C routine too big (max. 1000 bytes) */
#define AOAtoIOAallocErr   -36 /* Failed to allocate AOAtoIOAtable */
#define UnknownSigErr     -100 /* Unknown signal */
