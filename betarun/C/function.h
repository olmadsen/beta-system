/* C/initialize.c */
#ifdef macintosh
extern void Prompt(char *msg1, char *msg2, char *msg3, char *msg4);
#endif

/* C/betaenv.c */
extern void GetBetaEnv();

/* C/property.c */
extern void SetupProperties();

/* C/wordsort.c */
extern void WordSort();

/* C/outpattern.c */
extern void DisplayObject();
extern void ErrorMessage();
extern void DisplayBetaStack();

/* C/exit.c */
extern void BetaExit();
extern void BetaError();

/* C/cbfa.c */
extern void CBFAAlloc();
extern void CBFArelloc();

/* C/sighandler.c */
extern void SignalHandler();


/* GC/block.c */
extern ref(Block) newBlock();
extern void freeBlock();
extern long inArea();

/* GC/objectsize.c */
extern long ObjectSize();

/* GC/aoatoioa.c */
extern void AOAtoIOAInsert();
extern long AOAtoIOAAlloc();
extern void AOAtoIOAClear();

/* GC/aoa.c */
extern ref(Object) CopyObjectToAOA();
extern void AOAGc();

#ifdef RTDEBUG
extern void AOACheck();
extern void AOACheckObject();
extern void AOACheckReference();
extern void AOACheckObjectSpecial();
#ifdef sparc
extern void CheckStack();
#endif
#endif



/* GC/copyobject.c */
extern ref(Object) NewCopyObject();

/* GC/scavenging.c */
extern void ProcessStackPart();
extern void ProcessStack();
extern void IOAGc();
extern void ProcessReference();
extern void ProcessObject();
extern void ProcessAOAReference();
extern void ProcessAOAObject();

extern void CompleteScavenging();
extern long GetDistanceToEnclosingObject();
extern void tempAOArootsAlloc();
extern void tempAOArootsFree();
     
#ifdef RTDEBUG
extern void IOACheck();
extern void IOACheckObject();
extern void IOACheckReference();
#endif


/* GC/lvra.c */
extern long inLVRA();
extern long LVRARestInBlock();
extern void LVRAkill();
extern ref(Object) CopyObjectToLVRA(); 


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
