/*  Define structs describing all sorts of beta objects.  */

/* 92-04-02 tthorn: All heap objects now have a Body element;
   		    thus one can use the headsize macro
 */

typedef struct ProtoType{
  short           GCTabOff;  /* 0:  Byte offset to the GC Table                */
  short           OriginOff; /* 2:  Where should the origin be                 */
  ptr(long)       GenPart;   /* 4:  Reference to the generation code (or NULL) */
  ref(ProtoType)  Prefix;    /* 8:  Reference to the prefix prototype          */
  short           Size;      /* 12: Object size in longs                       */
  short           MpartOff;  /* 14: Byte offset to M entry prototype (or NULL) */
  short           FormInx;   /* 16: FragmentForm index of this object-desc     */
  short           AstRef;    /* 18: AST index of this object-desc.             */
  long            (*CBR)();  /* 20: Callback routine (or NULL)                 */
  long            TopMpart;  /* 24: M entry for top prefix                     */
} ProtoType;

typedef struct Item{ 
    ref(ProtoType)  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    long            Body[1];   /* The body part              */ 
} Item;

typedef struct Object{ 
    ref(ProtoType)  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    long            Body[1];   /* The body part              */ 
} Object;

typedef struct TextObject { 
    ref(ProtoType)  Proto;     /* Reference to TextProto     */
    long            GCAttr;    /* The GC attribute           */
    ref(Object)     Origin;    /* Reference to basicItem     */
    ref(ValRep)     T;         /* Repetition holding chars   */
    long            Pos;       /* Position in T              */
    long            Lgth;      /* Length in T                */
} TextObject;

typedef struct DopartObject{ 
    ref(ProtoType)  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    ref(Object)     Origin;    /* Origin of dopart object    */
    long            Size;      /* Size in BYTES of body      */
    long            Body[1];   /* The body part              */ 
} DopartObject;

typedef struct StackObject{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            BodySize;  /* The size of the body part   */
    long            StackSize; /* Size of the packed stack   
				* Size of top frame in NEWRUN 
				*/
    long            Body[1];   /* The body part               */ 
} StackObject;

typedef struct Component{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    ref(StackObject)StackObj;  /* Packed stack (suspended) 
				  or -1 (active)              */
    ref(Object)     CallerObj; /* Calling object              */
    ref(Component)  CallerComp;/* Calling component           */ 
    long            CallerLSC; /* Local sequence counter in
				* calling object              
				*/ 
    long            Body[1];   /* The body part               */ 
} Component;

typedef struct ValRep{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            LowBorder; /* Lower bound of range        */
    long            HighBorder;/* Higher bound of range       */
    long            Body[1];   /* The body part               */ 
} ValRep;

typedef struct RefRep{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            LowBorder; /* Lower bound of range        */
    long            HighBorder;/* Higher bound of range       */
    long            Body[1];   /* The body part               */ 
} RefRep;

typedef struct ObjectRep{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            LowBorder; /* Lower bound of range        */
    long            HighBorder;/* Higher bound of range       */
    ref(ProtoType)  iProto;    /* Prototype of objects in rep */
    ref(Object)     iOrigin;   /* Origin of objects in rep    */
    long            Body[1];   /* The body part               */ 
} ObjectRep;

typedef struct Structure{
    ref(ProtoType)  Proto;     /* StructurePTValue	      */
    long            GCAttr;    /* The GC attribute            */
    ref(Object)     iOrigin;   /* The origin of the structure */
    ref(ProtoType)  iProto;    /* The protoType of the struc  */
    long	    Body[1];   /* Dummy. Makes headsize work. */
} Structure;

/* Block is memory unit for AOArea and LVRArea. */
typedef struct Block{
    ref(Block)      next;      /* Refernece to the next Block     */
    union { 
             ptr(long) nextTop; 
             long      state; 
          } info;
    ptr(long)       top;       /* Refers the top in this(Block)   */
    ptr(long)       limit;     /* Refers the limit of this(Block) */
} Block;

typedef struct LVRABlock{
    ref(LVRABlock)  next;
    long            state;
    ptr(long)       top;
    ptr(long)       limit;
} LVRABlock;

typedef struct CallBackFrame {
    ref(CallBackFrame)  next;
#if !(defined(hppa) && defined(UseRefStack))
    ptr(long)           betaTop;
#endif
    long                tmp;
} CallBackFrame;

typedef struct CallBackEntry {
#ifdef crts
    ref(Structure)      theStruct;
#ifdef macppc
    unsigned long *     code[2]; /* codeptr and TOC */
#else
    unsigned long       code[40];
#endif
#endif
#ifdef sparc
    ref(Structure)	theStruct;
    long		mov_o7_g1;
    long		call_HandleCallBack;
    long		nop;
#endif
#ifdef hppa
    ref(Structure)      theStruct;
    unsigned long       code[7];
#endif
#ifdef mc68020 
    ref(Structure)      theStruct;
    short		jsr;
    void 	        (*handleCallBackPtr)();
    short		rts;
#endif
#ifdef linux
    ref(Structure)      theStruct;
    char                call;
    long                address;
    char                rts;
#endif
#ifdef nti
    ref(Structure)      theStruct;
    char                call;
    long                address;
    char                rts;
    short               disp; /* Only used for pascal and std call */
#endif
#ifdef sgi
    ref(Structure)      theStruct;
    unsigned long       code[5];
#endif
#ifdef macppc
    ref(Structure)      theStruct;
    unsigned long       code[10];
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
  ref(CallBackArea) next;
  ref(CallBackEntry) entries;
} CallBackArea;

typedef struct ComponentBlock{
    ref(CallBackFrame)  callBackFrame;
    ref(ComponentBlock) next;
    long                level;
#ifdef hppa
    void *              RefBlock;
#endif
} ComponentBlock;

typedef struct GCEntry {
    unsigned short StaticOff;
    short OrigOff;
    ref(ProtoType) Proto;
} GCEntry;

typedef struct PartObject {
    ref(ProtoType) Proto;
    long OrigOff;
} PartObject;

/* Statistic structs */

#ifdef GATHERSTATS
typedef struct IOAStatistic {
   long NumOfMoved;
   long SizeOfMoved;
   long NumOfStatic;
   long SizeOfStatic;
   long TotalNumOfGC;
   long TotalNumOfMoved;
   long TotalSizeOfMoved;
   long TotalNumOfStatic;
   long TotalSizeOfStatic;
} IOAStatistic;
#endif

typedef struct group_header
{
  struct group_header *data_start;
  long                *protoTable;
  struct group_header *data_end;
  long                code_start;
  long                code_end;
  /* The next entry is only used internally in RTS and only in
   * new implementations of nextgroup etc (sgi, b2c, ... )
   */
  char                *group_id;
  struct group_header **ptr;
} group_header;

#if defined(linux) || defined(nti)
/* Header files do not declare this! */
struct sigcontext {
  unsigned short gs, __gsh;
  unsigned short fs, __fsh;
  unsigned short es, __esh;
  unsigned short ds, __dsh;
  unsigned long edi;
  unsigned long esi;
  unsigned long ebp;
  unsigned long esp;
  unsigned long ebx;
  unsigned long edx;
  unsigned long ecx;
  unsigned long eax;
  unsigned long trapno;
  unsigned long err;
  unsigned long eip;
  unsigned short cs, __csh;
  unsigned long eflags;
  unsigned long esp_at_signal;
  unsigned short ss, __ssh;
  unsigned long i387;
  unsigned long oldmask;
  unsigned long cr2;
};
#endif /* linux || nti */

#ifdef NEWRUN
typedef void (*CellProcessFunc)(struct Object **theCell,struct Object *theObj);
#endif
