/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-96 Mjolner Informatics Aps.
 *   registers.c
 * Describe explicit global register bindings.
 * 
 * Written by Peter Andersen and Morten Grouleff
 */

#ifdef sparc
/* Using %g5 and %g6 is NOT compliant with the SPARC ABI.
 * Instead %g2, %g3, %g4 should be used.
 * But e.g. %g2 is destroyed by tau() in ctstcproc.o. %g2 is
 * used as temp register by gcc unless -ffixed-g2 is used.
 * Using %g7 makes programs linked with -lthread crash.
 */
#ifdef MT
/* Most of the following are not actually used from RTS, but
 * by defining them here, we prevent gcc from using them.
 * (-ffixed-g2 etc apparently does NOT work in gcc-2.7.2)
 */
register unsigned *RefTopOffReg   __asm__("%g2");
register unsigned *DataTopOffReg  __asm__("%g3");
register TSD      *TSDReg         __asm__("%g6");

register long     *IOATop         __asm__("%g5");

#else

register long     *IOA            __asm__("%g5");
register unsigned  IOATopOff      __asm__("%g6");

#endif /* MT */

register long     *StackPointer   __asm__("%sp");
register long     *FramePointer   __asm__("%fp");
register long     retAddress      __asm__("%i7");

#endif

