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
extern void 		    CopyRR(struct ValRep *theRep, struct Object* theObj, unsigned offset, long *SP);
extern void 		    CopySRR(struct RefRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void 		    CopySVR(struct ValRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high, long *SP);
extern void 		    CopyT(char *asciz, struct Item *theItem, unsigned offset, long *SP);
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
extern long 		    leS(struct Structure *arg1, struct Structure *arg2, long *SP);
extern long 		    geS(struct Structure *arg1, struct Structure *arg2, long *SP);
extern long 		    gtS(struct Structure *arg1, struct Structure *arg2, long *SP);
extern long 		    ltS(struct Structure *arg1, struct Structure *arg2, long *SP);

/* Routines that do not cause GC */
extern long 		    eqS(struct Structure *arg1, struct Structure *arg2);
extern long 		    neS(struct Structure *arg1, struct Structure *arg2);
extern void 		    Qua(struct ProtoType *dstQuaProto, struct Object **theCell, struct Object *dstQuaOrigin, long *SP);
extern void		    Return(void);
extern void		    SetArgValues(long argc, char *argv[]);
extern void		    FailureExit(long *SP, struct Object *this);
extern void		    HandleIndexErr(long *SP, struct Object *this);
extern void                 RefNone(long *SP, struct Object *this);
extern void *               CopyCPP(struct Structure *theStruct, struct Structure *dummy);
extern void 		    CinitT(void);
extern char *		    CpkVT(struct ValRep *theRep, long *SP);
extern char *		    CpkSVT(struct ValRep *theRep, unsigned low, long high, long *SP);
extern void 		    ChkRA(struct Object **theObjHandle);
extern void                 Susp(struct Object *this, long dummy, long RA, long SPz);
extern void                 Att(struct Object *this, struct Component *comp, long RA, long SPx);
extern void                 SetProtos(struct ProtoType *basic, struct ProtoType *text);
extern unsigned long        CodeEntry(struct ProtoType *theProto, long PC);

/* Garbage collector interface */
extern void                 doGC(long *SP, struct Object *this, unsigned long NumLongs); /* The one called from IOA(c)alloc */
extern void 		    DoGC(long *SP, struct Object *this);                         /* The one called directly from betaenv */

/* Defined in BETA */
long *GetSP(void);
struct Object *ThisObject(void);

#ifdef __GNUC__
/* GCC supports inline functions.
 * In that case we declare them here.
 * 
 * SGI note: It seems that the sgi cc compiler supports inlines
 * too by using "prarma intrinsic (func)" (see math.h).
 */
#include "IOAAlloc.h"
#else
/* If inline funktions are not supported, we declare them as normal
 * functions in Misc.c, and add prototypes here:
 */
extern void *IOAalloc(unsigned size, long *SP);
extern void *IOAcalloc(unsigned size, long *SP);
extern void AssignReference(long *theCell, struct Item *newObject);
extern void long_clear(char *p, unsigned bytesize);
extern void zero_check(char *p, unsigned bytesize);
extern void setup_item(struct Item *theItem,
		       struct ProtoType *prototype,
		       struct Object *origin
		       );
#endif

/* Call address "entry" with "current" as first and "item" as second argument */
#define CallBetaEntry(entry, current, item) \
  /* fprintf(output, "CallBetaEntry(0x%x, 0x%x, 0x%x)\n", (long)entry, current, item); */ \
  (* (void (*)(void *, void *))(entry)) ((void *)current, (void *)item)

#define CallGPart(entry, item, SP) \
  *++TraceSP = (long *) SP; \
  *++TraceSP = (long *) GetSP(); \
  (* (void (*)(void *, void *))(entry)) ((void *)0, (void *)item); \
  TraceSP -= 2;


#endif /* _CRUN_H_ */
