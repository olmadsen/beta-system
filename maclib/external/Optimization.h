/*
**	The Optimization changes to MoreFiles source and header files, along with
**	this file and OptimizationEnd.h, let you optimize the code produced
**	by MoreFiles in several ways.
**
**	You may disable Pascal calling conventions in all MoreFiles routines
**	except for system callbacks that require Pascal calling conventions.
**	This will make C programs both smaller and faster.
**	Just define __WANTPASCALELIMINATION to be 1 to turn this optimization on
**	when building MoreFiles for use from C programs (you'll need to keep
**	Pascal calling conventions when linking MoreFiles routines with Pascal
**	programs).
**
=**	If Metrowerks compiler is used, "#pragma internal on" is defined to
**	help produce better code when using Metrowerks compilers.
**
**	Original changes supplied by Fabrizio Oddone
**
**	File:	Optimization.h
*/


/*
**	If you want Pascal calling conventions disabled, set __WANTPASCALELIMINATION to 1.
*/
#ifndef	__WANTPASCALELIMINATION
#define	__WANTPASCALELIMINATION	0
#endif

#if	__WANTPASCALELIMINATION
#define pascal	
#endif

/*  The following produces smaller code on the PowerPC;
**  see the Metrowerks documentation for details.
*/
#if defined(__MWERKS__)
#pragma internal on
#endif
