struct ProtoType{
    short           GCTabOff;  /* Offset to the GC Table            */
    short           OriginOff; /* Where should the origin be        */
    short           Size;      /* Object size in longs              */
    short           FormOff;   /* Reference to the FormID string    */
    short           FormInx;   /* FragmentForm index of this object-desc */
    short           AstRef;    /* AST index of this object-desc.*/
    long            (*CallBackRoutine)();
};

struct Object{ 
    struct ProtoType *Proto;     /* Reference to the Prototype */
    long            GCAttr;    /* The GC attribute           */
    long            Body[1];   /* The body part              */ 
};

void dyt ()
{ struct Object * LazyItem;
  void (* cb) () = (void (*) ()) ((long *) LazyItem->Proto)[-1];
  cb ();
}
