/*  Define structs describing all sorts of beta objects.  */

struct ProtoType{
    short           GCTabOff;  /* Offset to the GC Table            */
    short           OriginOff; /* Where should the origin be        */
    ptr(long)       GenPart;   /* Reference to the generation code  */
    short           Size;      /* Object size -1 in longs           */
    ref(ProtoType)  Prefix;    /* Reference to the prefix prototype */
    short int       FormOff;   /* Reference to the FormID string    */
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
    ref(StackObject)StackObj;  /* Lower bound of range        */
    ref(Object)     CallerObj; /* Higher bound of range       */
    ref(Component)  CallerComp;/* The body part               */ 
    long            CallerLSC; /* LSC to calling object       */ 
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
    ref(ProtoType)  Proto;     /* Reference to the Prototype  */
    long            GCAttr;    /* The GC attribute            */
    long            iOrigin;   /* The origin of the structure */
    ref(ProtoType)  iProto;    /* The protoType of the struc  */
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
