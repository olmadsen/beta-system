/*  Define structs describing all sorts of beta objects.  */

/* 92-04-02 tthorn: All heap objects now have a Body element;
   thus one can use the headsize macro
   */

typedef struct _ProtoType{
  short              GCTabOff;  /* 0:  Byte offset to the GC Table                */
  short              OriginOff; /* 2:  Where should the origin be                 */
  long *             GenPart;   /* 4:  Reference to the generation code (or NULL) */
  struct _ProtoType *Prefix;    /* 8:  Reference to the prefix prototype          */
  short              Size;      /* 12: Object size in longs                       */
  short              MpartOff;  /* 14: Byte offset to M entry prototype (or NULL) */
  short              FormInx;   /* 16: FragmentForm index of this object-desc     */
  short              AstRef;    /* 18: AST index of this object-desc.             */
  long               (*CBR)();  /* 20: Callback routine (or NULL)                 */
  long               TopMpart;  /* 24: M entry for top prefix                     */
} ProtoType;

typedef struct _Item{ 
  ProtoType *Proto;     /* Reference to the Prototype */
  long       GCAttr;    /* The GC attribute           */
  long       Body[1];   /* The body part              */ 
} Item;

typedef struct _Object{ 
  ProtoType *Proto;     /* Reference to the Prototype */
  long       GCAttr;    /* The GC attribute           */
  long       Body[1];   /* The body part              */ 
} Object;

typedef struct _StackObject{
  ProtoType *Proto;     /* StackObjectPTValue         */
  long       GCAttr;    /* The GC attribute            */
  long       BodySize;  /* The size of the body part   */
#ifdef MT
  long       refTopOff; /* byte offset to refstack top */
  long       dataTopOff;/* byte offset to datastack top*/
  long       Body[1];   /* The body part               */ 
#else
  long       StackSize; /* Size of the packed stack   
			 * Size of top frame in NEWRUN 
			 */
  long       Body[1];   /* The body part               */ 
#endif
} StackObject;

typedef struct _Component{
  ProtoType         *Proto;     /* ComponentPTValue           */
  long               GCAttr;    /* The GC attribute            */
  StackObject       *StackObj;  /* Packed stack (suspended) 
				 * or -1 (active)
				 */
  Object            *CallerObj; /* Calling object 
				 * (called "Return Link" in the BETA book)
				 */
  struct _Component *CallerComp;/* Calling component           */ 
  long               CallerLSC; /* Local sequence counter in
				 * calling object.
				 * (called "Code Point" in BETA book)        
				 */ 
  long               Body[1];   /* The body part               */ 
} Component;

typedef struct _ValRep{
  ProtoType *Proto;     /* {Byte/Short/Long/Double}RepPTValue  */
  long       GCAttr;    /* The GC attribute            */
  long       LowBorder; /* Lower bound of range        */
  long       HighBorder;/* Higher bound of range       */
  long       Body[1];   /* The body part               */ 
} ValRep;

typedef struct _RefRep{
  ProtoType *Proto;     /* RefRepPTValue  */
  long       GCAttr;    /* The GC attribute            */
  long       LowBorder; /* Lower bound of range        */
  long       HighBorder;/* Higher bound of range       */
  long       Body[1];   /* The body part               */ 
} RefRep;

typedef struct _ObjectRep{
  ProtoType *Proto;     /* Dyn{Item/Comp}RepPTValue    */
  long       GCAttr;    /* The GC attribute            */
  long       LowBorder; /* Lower bound of range        */
  long       HighBorder;/* Higher bound of range       */
  ProtoType *iProto;    /* Prototype of objects in rep */
  Object    *iOrigin;   /* Origin of objects in rep    */
  long       Body[1];   /* The body part               */ 
} ObjectRep;

typedef struct _Structure{
  ProtoType *Proto;     /* StructurePTValue	      */
  long       GCAttr;    /* The GC attribute            */
  Object    *iOrigin;   /* The origin of the structure */
  ProtoType *iProto;    /* The protoType of the struc  */
  long       Body[1];   /* Dummy. Makes headsize work. */
} Structure;

typedef struct _DopartObject{ 
  ProtoType *Proto;     /* DopartObjectPTValue        */
  long       GCAttr;    /* The GC attribute           */
  Object    *Origin;    /* Origin of dopart object    */
  long       Size;      /* Size in BYTES of body      */
  long       Body[1];   /* The body part              */ 
} DopartObject;

typedef struct _TextObject { 
  ProtoType *Proto;     /* Reference to TextProto     */
  long       GCAttr;    /* The GC attribute           */
  Object    *Origin;    /* Reference to basicItem     */
  ValRep    *T;         /* Repetition holding chars   */
  long       Pos;       /* Position in T              */
  long       Lgth;      /* Length in T                */
} TextObject;

/* Block is memory unit for AOArea. */
typedef struct _Block{
  struct _Block *next;      /* Reference to the next Block     */
  union { 
    long        *nextTop; 
    long         state; 
  } info;
  long          *top;          /* Refers the top in this(Block)   */
  long          *limit;        /* Refers the limit of this(Block) */
  long          *mmaplimit;    /* max limit of block */
  long          *mmapmaxlimit; /* max mmaplimit of block */
} Block;

typedef struct _CallBackFrame {
  struct _CallBackFrame *  next;
#if !(defined(hppa) && defined(UseRefStack))
  long *betaTop;
#endif
  long  tmp;
} CallBackFrame;

typedef struct _CallBackEntry {
#ifdef sparc
#ifdef MT
  Structure    *theStruct;
  long          code[6];
#else
  Structure    *theStruct;
  long          mov_o7_g1;
  long          call_HandleCallBack;
  long          nop;
#endif /* MT */
#endif /* sparc */
#ifdef hppa
  Structure    *theStruct;
  unsigned long code[7];
#endif
#ifdef intel
  Structure    *theStruct;
  unsigned char code[6];
#ifdef nti
  unsigned char disp[2]; /* Only used for pascal and std call */
#endif /* nti */
#endif /* intel */
#ifdef sgi
  Structure    *theStruct;
  unsigned long code[5];
#endif
#ifdef macppc
  Structure    *theStruct;
  unsigned long code[10];
#endif
} CallBackEntry;

#ifdef linux
#define CallBackEntrySize 10
#else
#ifdef nti
#define CallBackEntrySize 12
#else
#define CallBackEntrySize sizeof(CallBackEntry)
#endif
#endif


typedef struct _CallBackArea {
  struct _CallBackArea *next;
  CallBackEntry * entries;
} CallBackArea;

typedef struct _ComponentBlock{
  CallBackFrame          *callBackFrame;
  struct _ComponentBlock *next;
  long                    level;
#ifdef hppa
  void                   *RefBlock;
#endif
} ComponentBlock;

typedef struct _GCEntry {
  unsigned short  StaticOff;
  short           OrigOff;
  ProtoType      *Proto;
} GCEntry;

typedef struct _PartObject {
  ProtoType *Proto;
  long       OrigOff;
} PartObject;

typedef struct _group_header
{
  struct _group_header  *data_start;
  long                  *protoTable;
  struct _group_header  *data_end;
  long                   code_start;
  long                   code_end;
  char                  *group_name;
  struct _{
    unsigned long        hash;
    unsigned long        modtime;
  } unique_group_id;
  struct _group_header **ptr; /* pointer back to beta_data file */
} group_header;

#if !defined(KEEP_STACKOBJ_IN_IOA)
typedef void (*CellProcessFunc)(Object **theCell,Object *theObj);
#endif

typedef struct _nums
{
  long NumAlloI;
  long NumAlloCOM;
  long NumAlloC;
  long NumAlloDO;
  long NumAlloRR;
  long NumAlloVR1;
  long NumAlloVR2;
  long NumAlloVR4;
  long NumAlloVR8;
  long NumAlloVRI;
  long NumAlloVRC;
  long NumCopyCT;
  long NumCopyRR;
  long NumCopySRR;
  long NumCopySVR1;
  long NumCopySVR2;
  long NumCopySVR4;
  long NumCopySVR8;
  long NumCopySVRI;
  long NumCopySVRC;
  long NumCopyT;
  long NumCopyVR1;
  long NumCopyVR2;
  long NumCopyVR4;
  long NumCopyVR8;
  long NumCopyVRI;
  long NumCopyVRC;
  long NumExtRR;
  long NumExtVR1;
  long NumExtVR2;
  long NumExtVR4;
  long NumExtVR8;
  long NumExtVRI;
  long NumExtVRC;
  long NumMkTO;
  long NumNewRR;
  long NumNewVR1;
  long NumNewVR2;
  long NumNewVR4;
  long NumNewVR8;
  long NumNewVRI;
  long NumNewVRC;
  long NumAlloS;
  long NumThisS;
  long NumObjS;
  long NumAlloSICB;
  long NumAlloSI;
  long NumAlloSC;
  long NumAlloSO;
  long NumleS;
  long NumgeS;
  long NumgtS;
  long NumltS;
  long NumeqS;
  long NumneS;
  long NumQua;
  long NumReturn;
  long NumRefNone;
  long NumCopyCPP;
  long NumCinitT;
  long NumCpkVT;
  long NumCpkSVT;
  long NumChkRA;
  long NumExO;
  long NumSusp;
  long NumAtt;
  long NumTermComp;
  long NumAOAAlloc;
#ifdef MAC
  long NumPpkVT;
  long NumPpkCT;
  long NumPpkSVT;
  long NumCopyPPP;
#endif
} nums;

#ifdef MT
typedef enum { 
  Flag_Semablocked = (1UL<< 0), 
  Flag_GCblocked   = (1UL<< 1), 
  Flag_DoingGC     = (1UL<< 2),
  Flag_MAX         = (1UL<< 3)-1
} tsd_flag_t;

/* Thread Specific Data */
typedef struct _TSD 
{
  /*  0 */ Component   *_ActiveComponent;
  /*  4 */ StackObject *_ActiveStack;
  /*  8 */ long        *_IOALimit;
  /* 12 */ long        *_IOATop;
  /* 16 */ long        *_savedIOALimit;
  /* 20 */ long         _MallocExhausted;
  /* 24 */ thread_t     _thread_id;
  /* 28 */ nums        *_nums;
  /* 32 */ Object      *_CurrentObject;
  /*       NB: This offset is hardcoded into CallAndSave* in sparcdep.h */
  /* 36 */ Object      *_Origin;
  /* 40 */ Object      *_SavedCallO;
  /* 44 */ long         _TSDinx;
  /* 48 */ tsd_flag_t   _TSDFlags;
  /* 52 */ char        *_CTextPoolEnd;
  /* 56 */ long         _CTextPool [MAXCTEXTPOOL/4];
} TSD;

#define ActiveComponent TSDReg->_ActiveComponent
#define ActiveStack     TSDReg->_ActiveStack
#define IOALimit        TSDReg->_IOALimit
#ifdef IOATopInTSD
#  define IOATop        TSDReg->_IOATop
#endif
#define savedIOALimit   TSDReg->_savedIOALimit
#define ThreadId        TSDReg->_thread_id
#define Nums            TSDReg->_nums
#define MallocExhausted TSDReg->_MallocExhausted
#define CTextPoolEnd    TSDReg->_CTextPoolEnd
#define CTextPool       TSDReg->_CTextPool
#define TSDinx          TSDReg->_TSDinx
#define TSDFlags        TSDReg->_TSDFlags

#ifdef RTDEBUG
#define NumAlloI	Nums->NumAlloI
#define NumAlloCOM	Nums->NumAlloCOM
#define NumAlloC	Nums->NumAlloC
#define NumAlloDO	Nums->NumAlloDO
#define NumAlloRR	Nums->NumAlloRR
#define NumAlloVR1	Nums->NumAlloVR1
#define NumAlloVR2	Nums->NumAlloVR2
#define NumAlloVR4	Nums->NumAlloVR4
#define NumAlloVR8	Nums->NumAlloVR8
#define NumAlloVRI	Nums->NumAlloVRI
#define NumAlloVRC	Nums->NumAlloVRC
#define NumCopyCT	Nums->NumCopyCT
#define NumCopyRR	Nums->NumCopyRR
#define NumCopySRR	Nums->NumCopySRR
#define NumCopySVR1	Nums->NumCopySVR1
#define NumCopySVR2	Nums->NumCopySVR2
#define NumCopySVR4	Nums->NumCopySVR4
#define NumCopySVR8	Nums->NumCopySVR8
#define NumCopySVRI	Nums->NumCopySVRI
#define NumCopySVRC	Nums->NumCopySVRC
#define NumCopyT	Nums->NumCopyT
#define NumCopyVR1	Nums->NumCopyVR1
#define NumCopyVR2	Nums->NumCopyVR2
#define NumCopyVR4	Nums->NumCopyVR4
#define NumCopyVR8	Nums->NumCopyVR8
#define NumCopyVRI	Nums->NumCopyVRI
#define NumCopyVRC	Nums->NumCopyVRC
#define NumExtRR	Nums->NumExtRR
#define NumExtVR1	Nums->NumExtVR1
#define NumExtVR2	Nums->NumExtVR2
#define NumExtVR4	Nums->NumExtVR4
#define NumExtVR8	Nums->NumExtVR8
#define NumExtVRI	Nums->NumExtVRI
#define NumExtVRC	Nums->NumExtVRC
#define NumMkTO		Nums->NumMkTO
#define NumNewRR	Nums->NumNewRR
#define NumNewVR1	Nums->NumNewVR1
#define NumNewVR2	Nums->NumNewVR2
#define NumNewVR4	Nums->NumNewVR4
#define NumNewVR8	Nums->NumNewVR8
#define NumNewVRI	Nums->NumNewVRI
#define NumNewVRC	Nums->NumNewVRC
#define NumAlloS	Nums->NumAlloS
#define NumThisS	Nums->NumThisS
#define NumObjS		Nums->NumObjS
#define NumAlloSICB	Nums->NumAlloSICB
#define NumAlloSI	Nums->NumAlloSI
#define NumAlloSC	Nums->NumAlloSC
#define NumAlloSO	Nums->NumAlloSO
#define NumleS		Nums->NumleS
#define NumgeS		Nums->NumgeS
#define NumgtS		Nums->NumgtS
#define NumltS		Nums->NumltS
#define NumeqS		Nums->NumeqS
#define NumneS		Nums->NumneS
#define NumQua		Nums->NumQua
#define NumReturn	Nums->NumReturn
#define NumRefNone	Nums->NumRefNone
#define NumCopyCPP	Nums->NumCopyCPP
#define NumCinitT	Nums->NumCinitT
#define NumCpkVT	Nums->NumCpkVT
#define NumCpkSVT	Nums->NumCpkSVT
#define NumChkRA	Nums->NumChkRA
#define NumExO		Nums->NumExO
#define NumSusp		Nums->NumSusp
#define NumAtt		Nums->NumAtt
#define NumTermComp	Nums->NumTermComp
#define NumAOAAlloc	Nums->NumAOAAlloc
#ifdef MAC
#define NumPpkVT	Nums->NumPpkVT
#define NumPpkCT	Nums->NumPpkCT
#define NumPpkSVT	Nums->NumPpkSVT
#define NumCopyPPP	Nums->NumCopyPPP
#endif

#endif /* RTDEBUG */
#endif /* MT */


#ifdef MT
# define GLOBAL_IOA gIOA
# define GLOBAL_IOATop gIOATop
# define GLOBAL_IOALimit gIOALimit
#else /* MT */
# define GLOBAL_IOA IOA
# define GLOBAL_IOATop IOATop
# define GLOBAL_IOALimit IOALimit
#endif /* MT */
