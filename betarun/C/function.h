/* C/initialize.c */
extern void Initialize(void);
#if defined(MAC)
extern void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern long StandAlone;
extern void EnlargeMacHeap(char *buf);
#endif /* Mac */
#ifdef RTDEBUG
extern long GetBetaCodeStart(void);
extern long GetBetaCodeEnd(void);
#endif /* RTDEBUG */
extern unsigned long address_of_me(void);

/* C/floats.c */
void SetupFPU(void);

/* C/betaenv.c */
extern void GetBetaEnv(void);
#ifdef nti
extern int isWinNT();
extern int isWin95();
extern int isWin32s();
#endif
#ifdef hppa
extern void *memalign(size_t, size_t);
#endif

/* C/property.c */
extern void SetupProperties(char *);

/* C/heapview.c */
extern void PrintHeapUsage(char *prompt);
extern int getHeapInfo(int infoId);

#ifdef RTDEBUG
/* C/dumper.c */
extern char *DumpItemName(void);
extern char *DumpItemFragment(void);
extern char *DumpValContents(void);
extern void DumpIOA(void);
#endif

/* C/outpattern.c */
extern char *ProtoTypeName(ProtoType *theProto);
extern long M_Part(ProtoType * proto);
extern void  DisplayObject(FILE *,Object *,long);
extern char *ErrorMessage(enum BetaErr);
extern int  DisplayBetaStack(enum BetaErr, Object *, long *, long);
#ifdef RTDEBUG
extern void DescribeObject(Object *);
extern void DescribeProto(ProtoType * theProto);

#endif
#ifdef NEWRUN
extern unsigned long        CodeEntry(ProtoType *theProto, long PC);
#endif

/* C/group.c */
extern group_header* NextGroup (group_header*);
extern char *GroupName(long, int);
extern void AddGroup(group_header *new_group);
extern int IsPrototypeOfGroup(group_header *gh, long data_addr);
extern int IsPrototypeOfProcess(long pt);
extern int IsBetaCodeAddrOfProcess(long addr);

/* C/exit.c */
extern void BetaExit(long);
#ifdef MT
extern void ThreadExit(void);
#endif
#ifdef NEWRUN
extern void BetaError(enum BetaErr err, Object *theObj, long *SP, long *thePC);
#else
extern void BetaError(enum BetaErr, Object *);
#endif

/* C/cbfa.c */
extern void CBFAalloc(void);
extern void CBFArelloc(void);
extern void freeCBF(unsigned long);
extern void freeCallbackCalled(void);
extern void ProcessCBFA(void);
#ifdef RTDEBUG
extern void CBFACheck(void);
#endif

/* C/dot.c */
/* See dot.h */


/* C/sighandler.c */
extern void SetupBetaSignalHandlers(void);
extern void InstallSigHandler(int sig);

#ifdef MT
/* C/multithread.c */
extern TSD* create_TSD(void);
extern void destroy_TSD(void);
extern void ProcessTSD(void);
#ifdef RTDEBUG
extern void TSDCheck(void);
#endif
extern void initSynchVariables(void);
extern int numProcessors(int online);
extern thread_t attToProcessor(Component *comp);
extern void SetupVirtualTimerHandler(void);
extern void SetupVirtualTimer(unsigned usec);
extern void* MT_malloc(int size);
extern void CalculateSliceSize(void);
#endif /* MT */

/* C/valhallaComm.c */
extern void valhallaInit (int debug_valhalla);

/* C/sockets.c */
extern signed long host2inetAddr(char *host);
extern signed long inetAddrOfThisHost(void);
extern int createActiveSocket(unsigned long inetAddr, long port, int nonblock);
extern int createPassiveSocket(long *port, int nonblock);
extern int acceptConn(int sock, int *pBlocked, unsigned long *pInetAddr);
extern int sockToRead(int fd);
extern int closeSocket(int fd);
extern int readDataMax(int fd, char *destbuffer, int buflen);
extern int writeDataMax(int fd, char *srcbuffer, int length);
extern void initSockets(void);
extern long selectReadable(int fd);
extern long doBlock(long fd, long rd, long wr, long timeoutValue);
extern long Errno(void);

/* C/labelnametable.c */
extern char* nextLabel(labeltable *handle);
extern int nextAddress(labeltable *handle);
extern labeltable *initReadNameTable (char* execFileName, int full);
extern void freeNameTable(labeltable *handle);
#ifdef nti
extern long getProcessOffset(labeltable *handle, long main_physical);
#endif

/* GC/block.c */
extern Block * newBlock(long);
extern void freeBlock(Block *);
extern long inArea(Block *, Object *);
#ifdef USEMMAP
void mmapInitial(unsigned long numbytes);
void InsertGuardPage(void);
Block * reserveBlock(long numbytes);
int extendBlock(Block * theBlock, long numbytes);
Block * AllocateBlock(long numbytes);
#endif
#ifdef RTDEBUG
extern long inAreaUnused(Block *, Object *);
#endif

/* GC/objectsize.c */
extern long ObjectSize(Object *);

/* GC/aoatoioa.c */
#ifdef MT
extern void MT_AOAtoIOAInsert(Object **);
#else /* MT */
extern void AOAtoIOAInsert(Object **);
#endif /* MT */
extern long AOAtoIOAalloc(void);
extern void AOAtoIOAClear(void);
#ifdef RTDEBUG
void AOAtoIOACheck(void);
void AOAtoIOAReport(void);
#endif

/* GC/aoa.c */
extern void tempAOArootsAlloc(void);
extern void tempAOArootsFree(void);
extern long sizeOfAOA(void);
#ifdef NEWRUN
extern Object *AOAalloc(long numbytes, long *SP);
extern Object *AOAcalloc(long numbytes, long *SP);
#else
extern Object *AOAalloc(long numbytes);
extern Object *AOAcalloc(long numbytes);
#endif
#ifdef MT
extern Object *AOAalloc(long numbytes);
extern Object *AOAcalloc(long numbytes);
#endif
/* Allocate block without possibility of doing IOAGc: */
extern Object *AOAallocate(long numbytes);

extern Object * CopyObjectToAOA(Object *);
extern void AOAGc(void);
#ifdef RTDEBUG
extern void AOACheck(void);
extern void AOACheckObject(Object *);
extern void AOACheckReference(Object **);
extern void AOACheckObjectSpecial(Object *);
#endif

/* GC/copyobject.c */
extern Object * NewCopyObject(Object *, Object **);

/* GC/stack.c */
extern void ProcessStackObj(StackObject *, CellProcessFunc func);

extern void ProcessStack(void);
#ifdef NEWRUN
extern void ProcessStackFrames(long SP, long StackStart, long stopAtComp, long dynOnly, CellProcessFunc func);
#endif
#if (defined(RTVALHALLA) && defined(intel))
extern void ProcessRefStack(void);
#endif /* RTVALHALLA && intel */

/* GC/ioa.c */
extern void IOAGc(void);
extern void ProcessReference(Object **);
extern void ProcessObject(Object *);
extern void CompleteScavenging(void);
extern void DoStackCell(Object **theCell,Object *theObj);
extern void DoIOACell(Object **theCell,Object *theObj);
#ifdef RTDEBUG
extern void IOACheck(void);
extern void IOACheckObject(Object *);
extern void IOACheckReference(REFERENCEACTIONARGSTYPE);
#endif

/* GC/lvra.c */
extern ValRep * LVRAAlloc(ProtoType *, long);
extern ValRep * LVRACAlloc(ProtoType *, long);
extern ValRep * LVRAXAlloc(ProtoType *, long, long);

/* GC/misc.c */
extern void assignRef(long *theCell, Item * newObject);
#ifdef RTDEBUG
void PrintWhichHeap(Object *ref);
extern void Illegal(void);
#endif
extern long inBetaHeap(Object *);
#if defined(MAC)
extern void InitTheCursor(void);
extern void RotateTheCursor(void);
extern void RotateTheCursorBack(void);
#endif

#ifdef NEWRUN
/* Defined in betaenv */
extern void DoGC(long *SP); /* The one called directly from betaenv */
extern void doAtt(long SPx, Object *topObj, long spSize, long *stack, long entry);
extern long *GetSP(void);
extern void CallB(Object *caller,
		          Object *callee,
		          long address,
		          long SP);
extern void BETA_main(void);
#ifdef ppcmac
extern void FlushCodeCash(long start, long end);
#endif

extern Object * GetThis(long *SP);
#endif

/* aoa.c */
extern void scanObject(Object *obj,
                       void referenceAction(REFERENCEACTIONARGSTYPE),
                       int doPartObjects);
extern Object * getRealObject(Object * obj);
extern void appendToListInAOA(REFERENCEACTIONARGSTYPE);
extern void initialCollectList(Object * root,
                               void referenceAction(REFERENCEACTIONARGSTYPE));
extern void extendCollectList(Object * root,
                              void referenceAction(REFERENCEACTIONARGSTYPE));
extern void scanList(Object * root, void (foreach)(Object * current));

/* aoafreelist.c */
extern void AOAInit(void);
extern void AOAFreeInFreeList(Object *chunk);
extern Object *AOAAllocateFromFreeList(long numbytes);
extern void AOAInsertFreeBlock(char *block, long numbytes); 
extern void AOACleanFreeList(void);
extern void AOADisplayFreeList(void);
extern long AOAScanMemoryArea(long *start, long *end);
extern void AOAFreeListAnalyze1(void);
extern void AOAFreeListAnalyze2(void);
extern void AOADisplayMemoryArea(long *start, long *end);
extern void GCInfo(void) ;
