/* C/initialize.c */
#ifdef macintosh
extern void Prompt(char *msg1, char *msg2, char *msg3, char *msg4);
#endif

/* C/betaenv.c */
extern void GetBetaEnv();

/* C/property.c */
void SetupProperties();

/* C/wordsort.c */
extern void wordsort();

/* C/outpattern.c */
extern void DisplayObject();
extern void ErrorMessage();
extern void DisplayBetaStack();

/* C/exit.c */
extern void BetaExit();
extern void BetaError();



/* GC/objectsize.c */
extern long ObjectSize();

/* GC/aoatoioa.c */
extern void AOAtoIOAInsert();
extern long AOAtoIOAAlloc();
extern void AOAtoIOAClear();

#ifdef AO_Area
/* GC/aoa.c */
extern ref(Object) CopyObjectToAOA();
extern void AOAGc();

#ifdef RTDEBUG
extern void AOACheck();
extern void AOACheckObject();
extern void AOACheckReference();
extern void AOACheckObjectSpecial();
#endif

#endif AO_Area

/* GC/scavenging.c */
extern void ProcessStackPart();
extern void ProcessStack();
extern void IOAGc();
extern void ProcessReference();
extern void ProcessObject();

#ifdef AO_Area
extern void ProcessAOAReference();
extern void ProcessAOAObject();
#endif

extern void CompleteScavenging();
extern long GetDistanceToEnclosingObject();

/* Safe way to save ToSpaceToAOA references */
#define SaveToSpaceToAOAref(cell)				\
  ((ToSpaceTop == ToSpaceToAOAptr)?tempToSpaceToAOAalloc(): (void) 0,	\
   *--ToSpaceToAOAptr = (long) (cell))

extern void tempToSpaceToAOAalloc();
extern void tempToSpaceToAOAfree();
     
#ifdef RTDEBUG
extern void IOACheck();
extern void IOACheckObject();
extern void IOACheckReference();
#endif


/* GC/lvra.c */
extern long inLVRA();
long LVRARestInBlock();



/* GC/misc.c */

extern long isObject( );
extern long inBetaHeap( );
extern long ObjectType( );
extern void Claim( );

#ifdef macintosh
extern void InitTheCursor();
extern void RotateTheCursor();
extern void RotateTheCursorBack();
#endif





