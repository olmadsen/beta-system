/*  Define structs describing all sorts of beta objects.  */

/* 92-04-02 tthorn: All heap objects now have a Body element;
   		    thus one can use the headsize macro
 */

struct ProtoType{
    short           GCTabOff;  /* Offset to the GC Table            */
    short           OriginOff; /* Where should the origin be        */
    ptr(long)       GenPart;   /* Reference to the generation code  */
    ref(ProtoType)  Prefix;    /* Reference to the prefix prototype */
    short           Size;      /* Object size -1 in longs           */
    short int       FormOff;   /* Reference to the FormID string    */
    short           AstRef;    /* AST reference of this object-desc.*/
    short	    pad;
    void	    (*CallBackRoutine)();
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

struct StackObject{
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            ObjectSize;/* The size of the object body */
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
    ptr(long)           betaTop;
    long                tmp;
};

/* Callback Entry. It is VITAL that theStruct is FIRST element. See cbfa.c */
struct CallBackEntry {
#ifdef sparc
    ref(Structure)	theStruct;
    long		mov_o7_g1;
    long		call_HandleCallBack;
    long		nop;
#else
    ref(Structure)      theStruct;
    short		jsr;
    void 	        (*handleCallBackPtr)();
    short		rts;
#endif
};

struct ComponentBlock{
    ref(CallBackFrame)  callBackFrame;
    ref(ComponentBlock) next;
    long                level;
};

struct GCEntry {
    unsigned short StaticOff;
    unsigned short OrigOff;
    ref(ProtoType) Proto;
};

struct PartObject {
    ref(ProtoType) Proto;
    unsigned int OrigOff;
};

/* Statistic structs */

#ifdef GATHERSTATS
struct IOAStatistic {
   int NumOfMoved;
   int SizeOfMoved;
   int NumOfStatic;
   int SizeOfStatic;
   int TotalNumOfGC;
   int TotalNumOfMoved;
   int TotalSizeOfMoved;
   int TotalNumOfStatic;
   int TotalSizeOfStatic;
};
#endif
