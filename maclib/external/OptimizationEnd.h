/*
**	The Optimization changes to MoreFiles source and header files, along with
**	this file and Optimization.h, let you optimize the code produced by MoreFiles
**	in several ways.
**
**	Original changes supplied by Fabrizio Oddone
**
**	File:	OptimizationEnd.h
*/


#if defined(__MWERKS__)
#pragma internal reset
#endif


#if	__WANTPASCALELIMINATION

#ifndef __COMPILINGMOREFILES
#undef pascal
#endif

#endif
