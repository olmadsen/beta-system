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
extern struct Component *   AlloC(struct Object *origin, struct ProtoType *proto, long *SP);
extern struct DopartObject *AlloDO(unsigned size, struct Object *this, long *SP);
extern struct Item *	    AlloI(struct Object *origin, struct ProtoType *proto, long *SP);
extern struct Item *	    AlloH(struct ProtoType *proto, long *SP);
extern void            	    AlloRR (struct Object* theObj, unsigned offset, int range, long *SP);
extern void            	    AlloVR1(struct Object* theObj, unsigned offset, int range, long *SP);
extern void 		    AlloVR2(struct Object* theObj, unsigned offset, int range, long *SP);
extern void		    AlloVR4(struct Object* theObj, unsigned offset, int range, long *SP);
extern void		    AlloVR8(struct Object* theObj, unsigned offset, int range, long *SP);
extern void                 AlloORR (struct Object *origin, struct ProtoType *proto, struct Object *theObj, unsigned offset, int range, long *SP);
extern void                 AlloORRC(struct Object *origin, struct ProtoType *proto, struct Object *theObj, unsigned offset, int range, long *SP);
extern struct ValRep *	    CopyCT(unsigned char *textPtr, long *SP);
extern void 		    CopyRR(struct RefRep *theRep, struct Object* theObj, unsigned offset, long *SP);
extern void 		    CopySRR(struct RefRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void 		    CopySVR(struct ValRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern struct Item *	    CopyT(char *asciz, struct Item *theItem, unsigned offset, long *SP);
extern void 		    CopyVR(struct ValRep *theRep, struct Object *theObj, unsigned offset, long *SP);
extern void		    ExtRR(struct Object *theObj, unsigned offset, long add, long *SP);
extern void		    ExtVR(struct Object *theObj, unsigned offset, long add, long *SP);
extern void 		    MkTO(char *cText, struct Item *theItem, unsigned offset, long *SP);
extern void		    NewRR(struct Object *theObj, long offset, long range, long *SP);
extern void		    NewVR(struct Object *theObj, long offset, long range, long *SP);
extern struct Structure *   AlloS(struct Object *origin, struct ProtoType *proto, long *SP);
extern struct Structure *   ThisS(struct Object *this, long *SP);
extern struct Structure *   ObjS(struct Object *theObj, long *SP);
extern struct Item *        AlloSICB(struct Structure **struchandle, long *SP);
extern struct Item *	    AlloSI(long dummy, struct Structure *struc, long *SP);
extern struct Component *   AlloSC(struct Structure *struc, long *SP);
extern struct StackObject * AlloSO(unsigned size, long *SP);
extern void                 Susp(struct Object *this, long prevSP, long RA, long SPz); /* calls AlloSO */
extern long 		    leS(struct Structure *arg1, struct Structure *arg2, long *SP);
extern long 		    geS(struct Structure *arg1, struct Structure *arg2, long *SP);
extern long 		    gtS(struct Structure *arg1, struct Structure *arg2, long *SP);
extern long 		    ltS(struct Structure *arg1, struct Structure *arg2, long *SP);

/* Routines that do not cause GC */
extern long 		    eqS(struct Structure *arg1, struct Structure *arg2);
extern long 		    neS(struct Structure *arg1, struct Structure *arg2);
extern void 		    Qua(struct Object *dstQuaOrigin, struct ProtoType *dstQuaProto, struct Object **theCell, long *SP);
extern void		    Return(void);
extern void		    SetArgValues(long argc, char *argv[]);
extern void		    FailureExit();
extern void		    HandleIndexErr(long *SP, struct Object *this);
extern void *               CopyCPP(struct Structure *theStruct);
extern void 		    CinitT(void);
extern char *		    CpkVT(struct ValRep *theRep, long *SP);
extern char *		    CpkSVT(struct ValRep *theRep, unsigned low, long high, long *SP);
#ifdef MAC
extern char *		    PpkVT(struct ValRep *theRep, long *SP);
extern char *		    PpkCT(char *, long *SP);
extern char *		    PpkSVT(struct ValRep *theRep, unsigned low, long high, long *SP);
#endif
extern void 		    ChkRA(struct Object **theObjHandle);
extern void                 Att(struct Object *this, struct Component *comp, long RA, long SPx);
extern void                 SetProtos(struct ProtoType *basic, struct ProtoType *text);

/* Garbage collector interface */
extern void                 doGC(long *SP, struct Object *this, unsigned long NumLongs); /* The one called from IOA(c)alloc */

#ifdef __GNUC__
/* GCC supports inline functions.
 * In that case we declare them here.
 * 
 * SGI note: It seems that the sgi cc compiler supports inlines
 * too by using "pragma intrinsic (func)" (see math.h).
 */
#include "IOAAlloc.h"
#else
/* If inline funktions are not supported, we declare them as normal
 * functions in Misc.c, and add prototypes here:
 */
extern void *IOAalloc(unsigned size, long *SP);
extern void *IOAcalloc(unsigned size, long *SP);
#endif

#endif /* _CRUN_H_ */
