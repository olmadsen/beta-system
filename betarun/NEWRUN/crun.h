/*
 * BETA C RUNTIME SYSTEM, Copyright (C) 1992-94 Mjolner Informatics Aps.
 * by Peter Andersen, Tommy Thorn, and Jacob Seligmann
 */


#ifndef _CRUN_H_
#define _CRUN_H_

/* function prototypes - move to function.h when
 * NEWRUN is standard.
 */

/* Routines that may cause GC */
extern Component *   AlloC(Object *origin, ProtoType *proto, long *SP);
extern DopartObject *AlloDO(unsigned size, Object *this, long *SP);
extern Item *	    AlloI(Object *origin, ProtoType *proto, long *SP);
extern Item *	    AlloH(ProtoType *proto, long *SP);
extern void            	    AlloRR (unsigned offset /* in bytes */, int range, Object* theObj, long *SP);
extern void            	    AlloVR1(unsigned offset /* in bytes */, int range, Object* theObj, long *SP);
extern void 		    AlloVR2(unsigned offset /* in bytes */, int range, Object* theObj, long *SP);
extern void		    AlloVR4(unsigned offset /* in bytes */, int range, Object* theObj, long *SP);
extern void		    AlloVR8(unsigned offset /* in bytes */, int range, Object* theObj, long *SP);
extern void                 AlloVRI(Object *origin, ProtoType *proto, unsigned offset /* in bytes */, int range, Object* theObj, long *SP);
extern void                 AlloVRC(Object *origin, ProtoType *proto, unsigned offset /* in bytes */, int range, Object* theObj, long *SP);
extern ValRep *	    CopyCT(unsigned char *textPtr, long *SP);
extern void 		    CopyRR(RefRep *theRep, Object* theObj, unsigned offset, long *SP);
extern void 		    CopySRR(RefRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void                 CopySVR1(ValRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void                 CopySVR2(ValRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void                 CopySVR4(ValRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void                 CopySVR8(ValRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void                 CopySVRI(ObjectRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void                 CopySVRC(ObjectRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);

extern void 		    CopySVR(ValRep *theRep, Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern Item *	    CopyT(char *asciz, Item *theItem, unsigned offset, long *SP);
extern void 		    CopyVR(ValRep *theRep, Object *theObj, unsigned offset, long *SP);
extern void		    ExtRR(Object *theObj, unsigned offset, long add, long *SP);
extern void		    ExtVR(Object *theObj, unsigned offset, long add, long *SP);
extern void 		    MkTO(char *cText, Item *theItem, unsigned offset, long *SP);
extern void		    NewRR(Object *theObj, long offset, long range, long *SP);
extern void		    NewVR1(Object *theObj, long offset, long range, long *SP);
extern void		    NewVR2(Object *theObj, long offset, long range, long *SP);
extern void		    NewVR4(Object *theObj, long offset, long range, long *SP);
extern void		    NewVR8(Object *theObj, long offset, long range, long *SP);
extern void		    NewVRI(Object *theObj, long offset, long range, long *SP);
extern void		    NewVRC(Object *theObj, long offset, long range, long *SP);
extern Structure *   AlloS(Object *origin, ProtoType *proto, long *SP);
extern Structure *   ThisS(Object *this, long *SP);
extern Structure *   ObjS(Object *theObj, long *SP);
extern Item *        AlloSICB(Structure **struchandle, long *SP);
extern Item *	    AlloSI(long dummy, Structure *struc, long *SP);
extern Component *   AlloSC(Structure *struc, long *SP);
extern StackObject * AlloSO(unsigned size, long *SP);
extern void                 Susp(Object *this, long prevSP, pc_t RA, long SPz); /* calls AlloSO */
extern long 		    leS(Structure *arg1, Structure *arg2, long *SP);
extern long 		    geS(Structure *arg1, Structure *arg2, long *SP);
extern long 		    gtS(Structure *arg1, Structure *arg2, long *SP);
extern long 		    ltS(Structure *arg1, Structure *arg2, long *SP);

/* Routines that do not cause GC */
extern long 		    eqS(Structure *arg1, Structure *arg2);
extern long 		    neS(Structure *arg1, Structure *arg2);
extern void 		    Qua(Object *dstQuaOrigin, ProtoType *dstQuaProto, Object **theCell, long *SP);
extern void		    Return(void);
extern void		    SetArgValues(long argc, char *argv[]);
extern void		    FailureExit();
extern void		    HandleIndexErr(long *SP, Object *this);
extern void *               CopyCPP(Structure *theStruct);
extern void 		    CinitT(void);
extern char *		    CpkVT(ValRep *theRep, long *SP);
extern char *		    CpkSVT(ValRep *theRep, unsigned low, long high, long *SP);
#ifdef MAC
extern char *		    PpkVT(ValRep *theRep, long *SP);
extern char *		    PpkCT(char *, long *SP);
extern char *		    PpkSVT(ValRep *theRep, unsigned low, long high, long *SP);
#endif
extern void 		    ChkRA(Object **theObjHandle);
extern void                 Att(Object *this, Component *comp, pc_t RA, long SPx);
extern void                 SetProtos(ProtoType *basic, ProtoType *text);

/* Garbage collector interface */
extern void                 doGC(long *SP, Object *this, unsigned long NumLongs); /* The one called from IOA(c)alloc */

#ifdef __GNUC__
/* GCC supports inline functions.
 * In that case we declare them here.
 * 
 * SGI note: It seems that the sgi cc compiler supports inlines
 * too by using "pragma intrinsic (func)" (see math.h).
 */
#include "IOAAlloc.h"
#else
/* If inline functions are not supported, we declare them as normal
 * functions in Misc.c, and add prototypes here:
 */
extern void *IOAalloc(unsigned size, long *SP);
extern void *IOATryAlloc(unsigned size, long *SP);
#endif

#endif /* _CRUN_H_ */
