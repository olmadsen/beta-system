/* C/initialize.c */
#ifdef macintosh
extern void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern void Prompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern long StandAlone;
#endif

/* C/betaenv.c */
extern void GetBetaEnv();

/* C/property.c */
extern void SetupProperties();

/* C/wordsort.c */
extern void WordSort();

#ifdef RTDEBUG
/* C/dumper.c */
extern char *DumpItemName();
extern char *DumpItemFragment();
extern char *DumpValContents();
extern void DumpIOA();
#endif

/* C/outpattern.c */
extern void  DisplayObject();
extern char *ErrorMessage();
extern void  DisplayBetaStack();
#ifdef RTDEBUG
extern char *DescribeObject();
#endif

/* C/exit.c */
extern void BetaExit();
extern void BetaError();

/* C/cbfa.c */
extern void CBFAAlloc();
extern void CBFArelloc();
extern void freeCBF();
#ifdef RTDEBUG
extern void CBFACheck();
#endif

/* C/sighandler.c */
extern void BetaSignalHandler();


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

#ifdef RTDEBUG
void AOAtoIOACheck();
void AOAtoIOAReport();
#endif

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

/* GC/stack.c */
extern void ProcessStackPart();
extern void ProcessStack();
extern void ProcessStackObj();

/* GC/ioa.c */
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

#ifdef RTDEBUG
void LVRACheck();
long LVRAAlive();
#endif


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
