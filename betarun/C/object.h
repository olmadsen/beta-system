/*  Define structs describing all sorts of beta objects.  */

/* 92-04-02 tthorn: All heap objects now have a Body element;
   		    thus one can use the headsize macro
 */

struct ProtoType{
    short           GCTabOff;  /* Offset to the GC Table            */
    short           OriginOff; /* Where should the origin be        */
    ptr(long)       GenPart;   /* Reference to the generation code  */
    ref(ProtoType)  Prefix;    /* Reference to the prefix prototype */
    short           Size;      /* Object size in longs              */
    short           FormOff;   /* Reference to the FormID string    */
    short           FormInx;   /* FragmentForm index of this object-desc */
    short           AstRef;    /* AST index of this object-desc.*/
    long            (*CallBackRoutine)();
};

struct Object{ 
    ref(ProtoType)  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    long            Body[1];   /* The body part              */ 
};

struct Item{ 
    ref(ProtoType)  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    long            Body[1];   /* The body part              */ 
};

struct DopartObject{ 
    ref(ProtoType)  Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    ref(Object)     Origin;    /* Origin of dopart object    */
    long            Size;      /* Size in BYTES of body      */
    long            Body[1];   /* The body part              */ 
};

struct StackObject{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            BodySize;  /* The size of the body part   */
    long            StackSize; /* Size of the packed stack    */
    long            Body[1];   /* The body part               */ 
};

struct Component{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    ref(StackObject)StackObj;  /* Packed stack (suspended) 
				  or -1 (active)              */
    ref(Object)     CallerObj; /* Calling object              */
    ref(Component)  CallerComp;/* Calling component           */ 
    long            CallerLSC; /* Local sequence counter in
				  calling object              */ 
    long            Body[1];   /* The body part               */ 
};

struct ValRep{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            LowBorder; /* Lower bound of range        */
    long            HighBorder;/* Higher bound of range       */
    long            Body[1];   /* The body part               */ 
};

struct RefRep{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            LowBorder; /* Lower bound of range        */
    long            HighBorder;/* Higher bound of range       */
    long            Body[1];   /* The body part               */ 
};

struct Structure{
    ref(ProtoType)  Proto;     /* StructurePTValue	      */
    long            GCAttr;    /* The GC attribute            */
    ref(Object)     iOrigin;   /* The origin of the structure */
    ref(ProtoType)  iProto;    /* The protoType of the struc  */
    long	    Body[1];   /* Dummy. Makes headsize work. */
};

/* Block is memory unit for AOArea and LVRArea. */
struct Block{
    ref(Block)      next;      /* Refernece to the next Block     */
    union { 
             ptr(long) nextTop; 
             long      state; 
          } info;
    ptr(long)       top;       /* Refers the top in this(Block)   */
    ptr(long)       limit;     /* Refers the limit of this(Block) */
};

struct LVRABlock{
    ref(LVRABlock)  next;
    long            state;
    ptr(long)       top;
    ptr(long)       limit;
};

struct CallBackFrame {
    ref(CallBackFrame)  next;
#if !(defined(hppa) && defined(REFSTACK))
    ptr(long)           betaTop;
#endif
    long                tmp;
};

struct CallBackEntry {
#ifdef crts
    ref(Structure)      theStruct;
    long		mov_o7_g1;
    long		call_HandleCallBack;
    long		nop;
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
};

#ifdef linux
#define CallBackEntrySize 10
#else
#ifdef nti
#define CallBackEntrySize 12
#else
#define CallBackEntrySize sizeof(struct CallBackEntry)
#endif
#endif


struct CallBackArea {
  ref(CallBackArea) next;
  ref(CallBackEntry) entries;
};

struct ComponentBlock{
    ref(CallBackFrame)  callBackFrame;
    ref(ComponentBlock) next;
    long                level;
#ifdef hppa
    void *              RefBlock;
#endif
};

struct GCEntry {
    unsigned short StaticOff;
    short OrigOff;
    ref(ProtoType) Proto;
};

struct PartObject {
    ref(ProtoType) Proto;
    long OrigOff;
};

/* Statistic structs */

#ifdef GATHERSTATS
struct IOAStatistic {
   long NumOfMoved;
   long SizeOfMoved;
   long NumOfStatic;
   long SizeOfStatic;
   long TotalNumOfGC;
   long TotalNumOfMoved;
   long TotalSizeOfMoved;
   long TotalNumOfStatic;
   long TotalSizeOfStatic;
};
#endif

typedef struct group_header
{
  struct group_header *self;
  long                *protoTable;
  struct group_header *next;
  long                code_start;
  long                code_end;
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

