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
extern int EqualNCS(char *s1, char *s2);

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

/* C/betaerror.c */
extern char *ErrorMessage(BetaErr);
#ifdef NEWRUN
  extern void BetaError(BetaErr err, Object *theObj, long *SP, pc_t thePC);
#else
  extern void BetaError(BetaErr, Object *);
#endif
#ifdef RTDEBUG
  extern void PrintBetaError(BetaErr err);
#endif /* RTDEBUG */

/* C/outpattern.c */
extern char *ProtoTypeName(ProtoType *theProto);
extern pc_t M_Part(ProtoType * proto);
#ifdef nti
extern void NotifyFunc(char *s1);
#endif
extern void DisplayCell(pc_t pc, Object *theObj);
extern int IsmakingDump(void);
extern void  DisplayObject(FILE *,Object *,pc_t);
extern int  DisplayBetaStack(BetaErr, Object *, pc_t, long);
extern void NotifyErrorDuringDump(BetaErr errorNumber, BetaErr errorNumber2);
#ifdef NEWRUN
  extern unsigned long CodeEntry(ProtoType *theProto, pc_t PC);
#endif

/* C/group.c */
extern group_header* NextGroup (group_header*);
extern char *GroupName(pc_t, int);
extern void AddGroup(group_header *new_group);
extern int IsPrototypeOfGroup(group_header *gh, long data_addr);
extern int IsPrototypeOfProcess(long pt);
extern int IsBetaCodeAddrOfProcess(pc_t addr);
extern int IsBetaDataAddrOfProcess(unsigned long addr);

/* C/exit.c */
extern void BetaExit(long);
#ifdef MT
  extern void ThreadExit(void);
#endif

/* C/cbfa.c */
extern void CBFAalloc(void);
extern void CBFArelloc(void);
extern void CBFAfree(void);
extern void freeCBF(unsigned long);
extern void freeCallbackCalled(void);
extern void ProcessCBFA(void);
extern int  NumCBFAEntries(void);
#ifdef RTDEBUG
  extern void CBFACheck(void);
#endif

/* C/dot.c */
/* See dot.h */


/* C/sighandler.c */
extern void SetupBetaSignalHandlers(void);
extern void InstallSigHandler(int sig);
#ifdef RTDEBUG
  extern void PrintSignal(int sig);
#endif /* RTDEBUG */

#ifdef MT
  /* C/multithread.c */
  extern TSD* create_TSD(void);
  extern void destroy_TSD(void);
  extern void ProcessTSD(void);
# ifdef RTDEBUG
    extern void TSDCheck(void);
# endif
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
/* VAlloS is really in RUN/CRUN/NEWRUN */
extern Structure *VAlloS(ProtoType *proto, long *SP, pc_t PC);

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
extern pc_t nextAddress(labeltable *handle);
extern labeltable *initReadNameTable (char* execFileName, int full);
extern void freeNameTable(labeltable *handle);
#ifdef nti
  extern long getProcessOffset(labeltable *handle, long main_physical);
#endif
extern long getMainPhysical(void);
extern void LabelNameTableFree(void);

/* C/rtdebug.c */
#ifdef RTDEBUG
extern void PrintObjProto(Object *obj);
extern void Illegal(char*file,int line);
#endif

/* GC/block.c */
extern Block * newBlock(long);
extern void * newProtectedArea(unsigned long);
extern void freeBlock(Block *);
extern long inArea(Block *, Object *);
#ifdef USEMMAP
  void mmapInitial(unsigned long numbytes);
  unsigned long mmapUnusedSize(void);
  int InsertGuardPage(void);
  unsigned long mmapUnusedSize(void);
  Block * reserveProtectedBlock(long numbytes);
  Block * reserveBlock(long numbytes);
  int extendBlock(Block * theBlock, long numbytes);
  Block * AllocateBlock(long numbytes);
#else
  extern int SectorBasedInAOA(Object *);
  extern int SectorBasedInAOAUnused(Object *);
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
extern void AOAtoIOAfree(void);
extern void AOAtoIOACleanup(void);
#ifdef RTDEBUG
void AOAtoIOACheck(void);
void AOAtoIOAReport(void);
void saveAOArootDebug(Object **cell);
#endif

/* GC/aoa.c */
extern void StackRefActionWrapper(Object **theCell,Object *theObj);
extern void scanOrigins(Object *theObj, void (*originAction)(Object **theCell));
extern void clearTail(void);
extern Object *getHead(void);
extern void prependToList(Object *target);
extern void tempAOArootsAlloc(void);
extern void tempAOArootsFree(void);
extern long sizeOfAOA(void);
extern Object *AOAalloc(long numbytes);
extern Object *AOAcalloc(long numbytes);
/* Allocate block without possibility of doing IOAGc: */
extern Object *AOAallocate(long numbytes, int forceAOAAllocation);
extern Object *CopyObjectToAOA(Object *theObj, Object *newObj, int forceAOAAllocation);
extern void AOAGc(void);

extern ValRep * LVRAAlloc(ProtoType *, long);
extern ValRep * LVRACAlloc(ProtoType *, long);
extern ValRep * LVRAXAlloc(ProtoType *, long, long);

#ifdef RTDEBUG
extern void AOACheck(void);
extern void AOACheckObject(Object *);
extern void AOACheckReference(Object **, long);
extern void AOACheckObjectSpecial(Object *);
#endif

/* GC/copyobject.c */
extern Object * NewCopyObject(Object *, Object **, int);

/* GC/stack.c */
extern void DoStackCell(Object **theCell,Object *theObj);
extern void ProcessStackObj(StackObject *, CellProcessFunc func);
extern void GeneralProcessStack(CellProcessFunc func);
extern void ProcessStack(void);
extern void DoStackCell(Object **theCell, Object *theObj);
#ifdef RTVALHALLA
extern long *CollectStackRoots(long *SP);
#endif /* RTVALHALLA */
extern int scanComponentStack (Component* comp, Object *curObj, pc_t pc, CellDisplayFunc forEach);

#ifdef sparc
extern pc_t frame_PC;
extern void DisplayAR(RegWin *theAR, pc_t PC, CellDisplayFunc func);
extern void TraverseSparcStackPart(RegWin *theAR, Object* prevObj, CellDisplayFunc func);
extern void DisplaySPARCStack(BetaErr errorNumber, Object *theObj, pc_t thePC, long theSignal);
#endif /* sparc */

#ifdef NEWRUN
extern long WindBackSP(long SP, Object *obj, pc_t PC);
extern void ProcessStackFrames(long SP, long StackStart, long stopAtComp, long dynOnly, CellProcessFunc func);
extern void PrintStackFrame(long *PrevSP, long *SP);
extern void DisplayNEWRUNStack(pc_t pc, Object *theObj, int signal);
#ifdef RTDEBUG
extern void PrintRefStack(void);
#endif /* RTDEBUG */
#endif /* NEWRUN */

#ifdef intel
#ifdef RTVALHALLA
extern void ProcessValhallaRefStack(void);
#ifdef RTDEBUG
void PrintValhallaRefStack(void);
#endif /* RTDEBUG */
#endif /* RTVALHALLA */
extern void ProcessStackPart(long *low, long *high, CellProcessFunc whenObject,CellProcessFunc whenNotObject);
extern int SkipDataRegs(long *theCell);
extern void PrintStack(long *StackEnd);
extern void DisplayINTELStack(BetaErr errorNumber, Object *currentObject, pc_t pc, long theSignal);
extern long *DisplayCallbackFrames(CallBackFrame *cbFrame, long *low, Object *currentObject, CellDisplayFunc func);
  extern void DisplayStackPart(long *low, long *high, Object *currentObject, CellDisplayFunc func);
#endif /* intel */

#ifdef hppa
extern void DisplayHPPAStack(pc_t thePC);
#endif /* hppa */

/* GC/ioa.c */
extern void IOAfree(void);
extern void IOAGc(void);
extern void ProcessReference(Object **, long refType);
extern void ProcessObject(Object *);
extern void CompleteScavenging(void);
extern void foreachObjectInIOA(void (*objectAction)(Object *, void *),
			       void *generic);
#ifdef RTDEBUG
extern void IOACheck(void);
extern void IOACheckObject(Object *);
extern void IOACheckReference(REFERENCEACTIONARGSTYPE);
#endif

#ifdef ALLOC_TRACE
extern FILE *alloc_trace_handle;
extern void CTraceAlloc();
#endif

/* GC/misc.c */
extern int strongIsObject(Object *obj);
extern ProtoType *getProto(Object *ref);
extern double gettimestampdouble(void);
extern long getmilisectimestamp(void);
extern long milisecsincelast(void);
extern void assignRef(long *theCell, Item * newObject);
extern void PrintCodeAddress(pc_t addr);
extern void PrintProto(ProtoType *proto);
extern void PrintRef(Object *ref);
extern void PrintObject(Object *obj);
extern void DescribeObject(Object *);
extern char *getLabel (pc_t addr);
extern long labelOffset;
extern const char *WhichHeap(Object *ref);
extern void PrintWhichHeap(Object *ref);

extern long inBetaHeap(Object *);
#if defined(MAC)
extern void InitTheCursor(void);
extern void RotateTheCursor(void);
extern void RotateTheCursorBack(void);
extern void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern void InitToolbox(void);
extern void GiveTime(void);
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
                       void (*referenceAction)(REFERENCEACTIONARGSTYPE),
		       void (*objectAction)(Object *),
                       int doPartObjects);
extern Object * getRealObject(Object * obj);
#ifdef PERSIST
extern Object * getRealStoreObject(Object * obj);
#endif /* PERSIST */
extern void prependToListInAOA(REFERENCEACTIONARGSTYPE);
extern void collectList(Object * root,
			void (*referenceAction)(REFERENCEACTIONARGSTYPE));
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
extern void GCInfo(void);
extern long AOAFreeListTotalFree(void);
extern long AOAFreeListIndexGetStat(long index, long *min, long *max, 
				    long *usecount, long *usesize, 
				    long *freecount, long *freesize);
extern void AOAfree(void);
int AOAtoIOAInsertImpl(Object **theCell);
#ifdef MT
void AOAtoIOAInsert(handle( Object) theCell);
#endif
#ifdef linux
void donothingwithsiginfo(void *s);
#endif


/* PerformGC.c */
#ifdef CRUN
#ifdef MT
extern Object *doGC(unsigned long);
#else /* !MT */
extern void doGC(void);
extern void doGCtoSP(long *SP, pc_t PC); 
#endif /* !MT */
#endif /* CRUN */
#ifdef NEWRUN
extern void doGC(long *SP, Object *this, unsigned long NumLongs);
#endif /* NEWRUN */

