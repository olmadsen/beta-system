/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-96 Mjolner Informatics Aps.
 *   registers.c
 * Describe explicit global register bindings.
 * 
 * Written by Peter Andersen and Morten Grouleff
 */

#ifdef sparc
register long     *IOA            __asm__("%g6");
register unsigned  IOATopOff      __extension__ __asm__("%g7");

register long     *StackPointer   __extension__ __asm__("%sp");
register long     *FramePointer   __extension__ __asm__("%fp");
register long     retAddress      __extension__ __asm__("%i7");

#ifdef MT
/* Most of the following are not actually used from RTS, but
 * by defining them here, we prevent gcc from using them.
 * (-ffixed-g2 etc apparently does NOT work in gcc-2.7.2)
 */
register unsigned *RefTopOffReg   __extension__ __asm__("%g2");
register unsigned *DataTopOffReg  __extension__ __asm__("%g3");
register unsigned *ActiveStackReg __extension__ __asm__("%g4");
register unsigned *IOALimitReg    __extension__ __asm__("%g5");

#endif /* MT */

#endif
