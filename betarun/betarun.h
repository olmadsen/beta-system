/*
 * betarun.h: interface from BETA compiler generated C-files 
 * to BETA Runtime system.
 *
 * Copyright (C) 1992-94 Mjolner Informatics Aps.
 * Written by Ole Lehrmann Madsen, Jacob Seligmann, and Peter Andersen.
 *
 * $Id: betarun.h,v 1.11 1995-02-22 12:38:15 beta Exp $
 *
 */


#ifndef _CRTS_H_
#define _CRTS_H_

typedef struct ProtoType{
    short           GCTabOff;  /* Offset to the GC Table            */
    short           OriginOff; /* Where should the origin be        */
    long*       GenPart;   /* Reference to the generation code  */
    struct ProtoType*  Prefix;    /* Reference to the prefix prototype */
    short           Size;      /* Object size in longs              */
    short           FormOff;   /* Reference to the FormID string    */
    short           FormInx;   /* FragmentForm index of this object-desc */
    short           AstRef;    /* AST index of this object-desc.*/
    long            (*CallBackRoutine)();
} ProtoType;

typedef struct Object{ 
    ProtoType*  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    long            Body[1];   /* The body part              */ 
} Object;

typedef struct Item{ 
    ProtoType*  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    long            Body[1];   /* The body part              */ 
} Item;

typedef struct DopartObject{ 
    ProtoType*  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    Object*     Origin;    /* Origin of dopart object    */
    long            Size;      /* Size in BYTES of body      */
    long            Body[1];   /* The body part              */ 
} DopartObject;

typedef struct StackObject{
    ProtoType*  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            BodySize;  /* The size of the body part   */
    long            StackSize; /* Size of the packed stack    */
    long            Body[1];   /* The body part               */ 
} StackObject;

typedef struct Component{
    ProtoType*  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    StackObject* StackObj;  /* Packed stack (suspended) 
				  or -1 (active)              */
    Object*     CallerObj; /* Calling object              */
    struct Component*  CallerComp;/* Calling component           */ 
    long            CallerLSC; /* Local sequence counter in
				  calling object              */ 
    long            Body[1];   /* The body part               */ 
} Component;

typedef struct ValRep{
    ProtoType*  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            LowBorder; /* Lower bound of range        */
    long            HighBorder;/* Higher bound of range       */
    long            Body[1];   /* The body part               */ 
} ValRep;

typedef struct RefRep{
    ProtoType*  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            LowBorder; /* Lower bound of range        */
    long            HighBorder;/* Higher bound of range       */
    long            Body[1];   /* The body part               */ 
} RefRep;

typedef struct Structure{
    ProtoType*  Proto;     /* StructurePTValue	      */
    long            GCAttr;    /* The GC attribute            */
    Object*     iOrigin;   /* The origin of the structure */
    ProtoType*  iProto;    /* The protoType of the struc  */
    long	    Body[1];   /* Dummy. Makes headsize work. */
} Structure;

/* Block is memory unit for AOArea and LVRArea. */
typedef struct Block{
    struct Block*      next;      /* Refernece to the next Block     */
    union { 
             long* nextTop; 
             long      state; 
          } info;
    long*       top;       /* Refers the top in this(Block)   */
    long*       limit;     /* Refers the limit of this(Block) */
} Block;

typedef struct LVRABlock{
    struct LVRABlock*  next;
    long            state;
    long*       top;
    long*       limit;
} LVRABlock;

typedef struct CallBackFrame {
    struct CallBackFrame*  next;
#if !(defined(hppa) && defined(REFSTACK))
    long*           betaTop;
#endif
    long                tmp;
} CallBackFrame;

typedef struct CallBackEntry {
#ifdef crts
    Structure*      theStruct;
#ifdef __powerc
    unsigned long *     code[2]; /* codeptr and TOC */
#else
    unsigned long       code[40];
#endif
#endif
#ifdef sparc
    Structure*	theStruct;
    long		mov_o7_g1;
    long		call_HandleCallBack;
    long		nop;
#endif
#ifdef hppa
    Structure*      theStruct;
    unsigned long       code[7];
#endif
#ifdef mc68020 
    Structure*      theStruct;
    short		jsr;
    void 	        (*handleCallBackPtr)();
    short		rts;
#endif
#ifdef linux
    Structure*      theStruct;
    char                call;
    long                address;
    char                rts;
#endif
#ifdef nti
    Structure*      theStruct;
    char                call;
    long                address;
    char                rts;
    short               disp; /* Only used for pascal and std call */
#endif
} CallBackEntry;

#ifdef linux
#define CallBackEntrySize 10
#else
#ifdef nti
#define CallBackEntrySize 12
#else
#define CallBackEntrySize sizeof(struct CallBackEntry)
#endif
#endif


typedef struct CallBackArea {
  struct CallBackArea* next;
  CallBackEntry* entries;
} CallBackArea;

typedef struct ComponentBlock{
    CallBackFrame*  callBackFrame;
    struct ComponentBlock* next;
    long                level;
#ifdef hppa
    void *              RefBlock;
#endif
} ComponentBlock;

typedef struct GCEntry {
    unsigned short StaticOff;
    short OrigOff;
    ProtoType* Proto;
} GCEntry;

typedef struct PartObject {
    ProtoType* Proto;
    long OrigOff;
} PartObject;


extern long *IOA;
extern long *IOATop;

extern long a0, a1, a2, a3, a4, a7; 
extern long leave;
extern void *CRTSjbp;

extern long * cIntStackPtr;
extern double * cFloatStackPtr;
extern long * RefSP;
extern long * oldSP;

extern void Trap(void);

#define LOCAL_DECLS \
	long d0,d1,d2,d3,d4,d5,d6,d7, \
	     C1,C2,C3,C4,C5,C6,C7,C8,C9,C10; \
	char *T1, *T2, *T3, *T4, *T5, *T6, *T7, *T8, *T9, *T10; \
	double fp0,fp1,fp2,fp3,fp4,fp5,fp6,fp7,fTmp; \
	double F1,F2,F3,F4,F5,F6,F7;


#if defined(sun4) || defined(sun4s)
/* oldStackPtr is provided to the callback function by HandleCB which read the
   value of the old stack pointer when called. It is then necessary that the
   called BETA object is called with the parameters theObj, oldStackPtr, arg1,..
*/
#define CallBackPar1(dReg) (dReg = arg1)
#define CallBackPar2(dReg) (dReg = arg2)
#define CallBackPar3(dReg) (dReg = arg3)
#define CallBackPar4(dReg) (dReg = arg4)
#define CallBackPar5(dReg) (dReg = arg5)
#define CallBackPar6(dReg) (dReg = arg6)

#define CallBackParN(oldStackPtr, dReg, parNo)						\
  /* Ok, this is a hard one: oldStackPtr points to the previosly stack frame.		\
     This frame contains the parameters of the C-function calling back to BETA.		\
     On SPARC 23 words are used before the the parameters past the sixth (if any)	\
     are pushed on the stack. The first parameter on the stack is then the		\
     seventh parameter and so one.							\
   */											\
  dReg = *(long *)(oldStackPtr+(23+parNo-7));

#define SaveCompState()

#define RestoreCompState()

#define SaveCurrSP()

#endif /* SUN4 & SUN4S */

#ifdef sgi

#if 0
#define SaveCurrSP() \
  { register long * SP asm("$29"); \
    asm("":"=r" (SP)); /* fool gcc */ \
    oldSP = SP; \
   }
#else
#define SaveCurrSP() \
  { register long * SP; \
    asm("move %0,$29" : "=r" (SP)); /* copy SP to C-var */ \
    oldSP = SP; \
   }
#endif

#define SaveCompState()				\
  asm(" addiu $29, $29, -108 ");		\
  asm(" sw $2, 4($29) ");			\
  asm(" sw $3, 8($29) ");			\
  asm(" sw $4, 12($29) ");			\
  asm(" sw $5, 16($29) ");			\
  asm(" sw $6, 20($29) ");			\
  asm(" sw $7, 24($29) ");			\
  asm(" sw $8, 28($29) ");			\
  asm(" sw $9, 32($29) ");			\
  asm(" sw $10, 36($29) ");			\
  asm(" sw $11, 40($29) ");			\
  asm(" sw $12, 44($29) ");			\
  asm(" sw $13, 48($29) ");			\
  asm(" sw $14, 52($29) ");			\
  asm(" sw $15, 56($29) ");			\
  asm(" sw $24, 60($29) ");			\
  asm(" sw $25, 64($29) ");			\
  asm(" sw $16, 68($29) ");			\
  asm(" sw $17, 72($29) ");			\
  asm(" sw $18, 76($29) ");			\
  asm(" sw $19, 80($29) ");			\
  asm(" sw $20, 84($29) ");			\
  asm(" sw $21, 88($29) ");			\
  asm(" sw $22, 92($29) ");			\
  asm(" sw $23, 96($29) ");			\
  asm(" sw $28, 100($29) ");			\
  asm(" sw $30, 104($29) ");			\
  asm(" sw $31, 108($29) ");                    \
  SaveCurrSP();

#define RestoreCompState()			\
  asm(" lw $2, 4($29) ");			\
  asm(" lw $3, 8($29) ");			\
  asm(" lw $4, 12($29) ");			\
  asm(" lw $5, 16($29) ");			\
  asm(" lw $6, 20($29) ");			\
  asm(" lw $7, 24($29) ");			\
  asm(" lw $8, 28($29) ");			\
  asm(" lw $9, 32($29) ");			\
  asm(" lw $10, 36($29) ");			\
  asm(" lw $11, 40($29) ");			\
  asm(" lw $12, 44($29) ");			\
  asm(" lw $13, 48($29) ");			\
  asm(" lw $14, 52($29) ");			\
  asm(" lw $15, 56($29) ");			\
  asm(" lw $24, 60($29) ");			\
  asm(" lw $25, 64($29) ");			\
  asm(" lw $16, 68($29) ");			\
  asm(" lw $17, 72($29) ");			\
  asm(" lw $18, 76($29) ");			\
  asm(" lw $19, 80($29) ");			\
  asm(" lw $20, 84($29) ");			\
  asm(" lw $21, 88($29) ");			\
  asm(" lw $22, 92($29) ");			\
  asm(" lw $23, 96($29) ");			\
  asm(" lw $28, 100($29) ");			\
  asm(" lw $30, 104($29) ");			\
  asm(" lw $31, 108($29) ");			\
  asm(" addiu $29, $29, 108 ");

#define CallBackPar1(dReg) (dReg = arg1)
#define CallBackPar2(dReg) (dReg = arg2)
#define CallBackPar3(dReg) (dReg = arg3)
#define CallBackPar4(dReg) (dReg = arg4)
#define CallBackPar5(dReg) (dReg = arg5)
#define CallBackPar6(dReg) (dReg = arg6)

#define CallBackParN(oldStackPtr, dReg, parNo)	\
    dReg = *(long *)(oldStackPtr+(parNo-1));

#endif /* sgi */

#ifdef MAC

extern long PPC_GetStackPointer();
#define SaveCurrSP() oldSP=PPC_GetStackPointer()

extern void PPC_SaveCompState(void);
#define SaveCompState()	\
  PPC_SaveCompState(); \
  SaveCurrSP();  

extern void PPC_RestoreCompState(void);
#define RestoreCompState() \
  PPC_RestoreCompState();

#define CallBackPar1(dReg) (dReg = arg1)
#define CallBackPar2(dReg) (dReg = arg2)
#define CallBackPar3(dReg) (dReg = arg3)
#define CallBackPar4(dReg) (dReg = arg4)
#define CallBackPar5(dReg) (dReg = arg5)
#define CallBackPar6(dReg) (dReg = arg6)

#define CallBackParN(oldStackPtr, dReg, parNo) \
    if (parNo==7) dReg = arg7;                 \
	else if (parNo==8) dReg = arg8;            \
	else dReg = *(long *)(oldStackPtr+(24)+(parNo-1));

#define CallBackPascalPar1(dReg) (dReg = *(long *)(ParamPtr+(1-1)))
#define CallBackPascalPar2(dReg) (dReg = *(long *)(ParamPtr+(2-1)))
#define CallBackPascalPar3(dReg) (dReg = *(long *)(ParamPtr+(3-1)))
#define CallBackPascalPar4(dReg) (dReg = *(long *)(ParamPtr+(4-1)))
#define CallBackPascalPar5(dReg) (dReg = *(long *)(ParamPtr+(5-1)))
#define CallBackPascalPar6(dReg) (dReg = *(long *)(ParamPtr+(6-1)))

#define CallBackPascalParN(oldStackPtr, dReg, parNo) \
    dReg = *(long *)((parNo-1));

#define CallBackPascalParShort1(dReg) (dReg = *(short *)(ParamPtr+(1-1)))
#define CallBackPascalParShort2(dReg) (dReg = *(short *)(ParamPtr+(2-1)))
#define CallBackPascalParShort3(dReg) (dReg = *(short *)(ParamPtr+(3-1)))
#define CallBackPascalParShort4(dReg) (dReg = *(short *)(ParamPtr+(4-1)))
#define CallBackPascalParShort5(dReg) (dReg = *(short *)(ParamPtr+(5-1)))
#define CallBackPascalParShort6(dReg) (dReg = *(short *)(ParamPtr+(6-1)))

#endif /* MAC */

#include <setjmp.h>
jmp_buf *UseJmpBuf(int,int);
jmp_buf *GetJmpBuf(int,int);
void FreeJmpBuf(int, int);

extern char 		GetByte(unsigned long a, int byteNo /* 0-3 */);
extern unsigned short 	GetShort(unsigned long a,int shortNo /* 0-1 */);
extern void 		PutBits(unsigned long a, unsigned long *b, int pos, int len);
extern unsigned long 	GetBits(unsigned long a, int pos, int len);
extern signed long 	GetSignedBits(unsigned long a, int pos, int len);
extern signed long 	SignExtByte(signed char a);
extern signed long 	SignExtWord(signed short a);

extern struct Component *	AlloC(struct Object *origin, struct ProtoType *proto);
extern struct DopartObject * 	AlloDO(unsigned size, struct Object *origin);
extern struct Item *		AlloI(struct Object *origin, struct ProtoType *proto);
extern struct Item *		AlloH(struct Object *origin, struct ProtoType *proto);
extern struct RefRep *		AlloRR(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR1(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR2(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR4(struct Object* theObj, unsigned offset, int range);
extern struct ValRep *		AlloVR8(struct Object* theObj, unsigned offset, int range);
extern struct Component *	Att(struct Item *this, struct Component *comp);
extern void			AttBC(struct Item *this, struct Component *comp);
extern void 			CinitT(void);
extern char *			CpkVT(struct Object *currentObj, struct ValRep *theRep);
extern char *			CpkSVT(struct Object *currentObj, struct ValRep *theRep, unsigned low, long high);
extern void *			CopyCPP(struct Structure *theStruct, struct Object *theObj);
extern void *			CopyPPP(struct Structure *theStruct, long size, struct Object *theObj);
extern void 			ChkRA(struct Object **theObjHandle);
extern struct ValRep *		CopyCT(unsigned char *textPtr);
extern void 			CopyRR(struct ValRep *theRep, struct Object* theObj, unsigned offset);
extern void 			CopySRR(struct RefRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high);
extern void 			CopySVR(struct RefRep *theRep, struct Item *theItem, unsigned offset, unsigned low, unsigned high);
extern void 			CopyT(char *asciz, struct Item *theItem, unsigned offset);
extern void 			CopyVR(struct ValRep *theRep, struct Object *theObj, unsigned offset);
extern void			ExtRR(struct Object *theObj, unsigned offset, long add);
extern void			ExtVR(struct Object *theObj, unsigned offset, long add);
extern void			HandleIndexErr(struct Item *this);
extern void 			MkTO(char *cText, struct Item *theItem, unsigned offset);
extern void			Return(void);
extern void			BetaError(int, struct Object *theObj);
extern void			SetArgValues(long argc, char *argv[]);
extern void			FailureExit(void);
extern void			NewRR(struct Object *theObj, long offset, long range);
extern void			NewVR(struct Object *theObj, long offset, long range);
extern void 			DoGC(void);
extern void 			Qua(struct ProtoType *dstQuaProto, struct Object **theCell, struct Object *dstQuaOrigin, struct Object *this);
extern struct Structure *	AlloS(struct Object *origin, struct ProtoType *proto);
extern struct Structure * 	ThisS(struct Object *this);
extern struct Structure * 	ObjS(struct Object *theObj);
extern struct Item *		AlloSI(struct Structure *struc);
extern struct Component *	AlloSC(struct Structure *struc);
extern long 			eqS(struct Structure *arg1, struct Structure *arg2);
extern long 			neS(struct Structure *arg1, struct Structure *arg2);
extern long 			leS(struct Structure *arg1, struct Structure *arg2);
extern long 			geS(struct Structure *arg1, struct Structure *arg2);
extern long 			gtS(struct Structure *arg1, struct Structure *arg2);
extern long 			ltS(struct Structure *arg1, struct Structure *arg2);
extern struct Component * 	Susp(struct Object *this);

#endif
