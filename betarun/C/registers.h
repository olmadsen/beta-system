/*
 * BETA RUNTIME SYSTEM, Copyright (C) 1990-96 Mjolner Informatics Aps.
 *   registers.c
 * Describe explicit global register bindings.
 * 
 * Written by Peter Andersen and Morten Grouleff
 */

#ifdef sparc
register long     *IOA            asm("%g6");
register unsigned  IOATopOff      asm("%g7");

#ifdef MT
/* Most of the following are not actually used from RTS, but
 * by defining them here, we prevent gcc from using them.
 * (-ffixed-g2 etc apparently does NOT work in gcc-2.7.2)
 */
register unsigned *RefTopOffReg   asm("%g2");
register unsigned *DataTopOffReg  asm("%g3");
register unsigned *ActiveStackReg asm("%g4");
register unsigned *IOALimitReg    asm("%g5");

#endif /* MT */

#endif
