/* C/initialize.c */
#ifdef macintosh
extern void CPrompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern void Prompt(char *msg1, char *msg2, char *msg3, char *msg4);
extern long StandAlone;
#endif

/* C/betaenv.c */
extern void GetBetaEnv(void);

/* C/property.c */
extern void SetupProperties(char *);

/* C/wordsort.c */
#ifdef USE_WORDSORT
extern void WordSort(unsigned long*, int);
#else /* USE_WORDSORT */
#include <stdlib.h>
extern int intcompare(const void *, const void *);
#define WordSort(base, num) {                                     \
  /*fprintf(output, "wordsort(0x%x, 0x%x)\n", base, num); */      \
  qsort((char*)(base), (num), sizeof(unsigned long), intcompare); \
}
#endif /* USE_WORDSORT */

#ifdef RTDEBUG
/* C/dumper.c */
extern char *DumpItemName();
extern char *DumpItemFragment();
extern char *DumpValContents();
extern void DumpIOA();
#endif

/* C/outpattern.c */
extern void  DisplayObject(ptr(FILE),ref(Object),long);
extern char *ErrorMessage(long);
extern int  DisplayBetaStack(long, ref(Object), long *, long);
extern struct group_header* NextGroup (struct group_header*);
extern char* NameOfGroup (struct group_header *);
extern char *GroupName(long, int);
#ifdef RTDEBUG
extern char *DescribeObject(struct Object *);
#endif

/* C/exit.c */
extern void BetaExit(long);
extern void BetaError(long, ref(Object));

/* C/cbfa.c */
extern void CBFAAlloc(void);
extern void CBFArelloc(void);
extern void freeCBF(unsigned long);
extern void freeCallbackCalled();
#ifdef RTDEBUG
extern void CBFACheck(void);
#endif

/* C/sighandler.c */
extern void BetaSignalHandler();


/* GC/block.c */
extern ref(Block) newBlock(long);
extern void freeBlock(ref(Block));
extern long inArea(ref(Block), ref(Object));

/* GC/objectsize.c */
extern long ObjectSize(ref(Object));

/* GC/aoatoioa.c */
extern void AOAtoIOAInsert(handle(Object));
extern long AOAtoIOAAlloc(void);
extern void AOAtoIOAClear(void);
#ifdef RTDEBUG
void AOAtoIOACheck(void);
void AOAtoIOAReport(void);
#endif

/* GC/aoa.c */
extern ref(Object) CopyObjectToAOA(ref(Object));
extern void AOAGc(void);
#ifdef RTDEBUG
extern void AOACheck(void);
extern void AOACheckObject(ref(Object));
extern void AOACheckReference(handle(Object));
extern void AOACheckObjectSpecial(ref(Object));
#endif

/* GC/copyobject.c */
extern ref(Object) NewCopyObject(ref(Object), handle(Object));

/* GC/stack.c */
extern void ProcessStackPart(long *, long *);
extern void ProcessStack(void);
extern void ProcessStackObj(struct StackObject *);

/* GC/ioa.c */
extern void IOAGc(void);
extern void ProcessReference(handle(Object));
extern void ProcessObject(ref(Object));
extern void ProcessAOAReference(handle(Object));
extern void ProcessAOAObject(ref(Object));
extern void CompleteScavenging(void);
extern long GetDistanceToEnclosingObject(ref(Object));
extern void tempAOArootsAlloc(void);
extern void tempAOArootsFree(void);
#ifdef RTDEBUG
extern void IOACheck(void);
extern void IOACheckObject(ref(Object));
extern void IOACheckReference(handle(Object));
#endif

/* GC/lvra.c */
extern ref(ValRep) LVRAAlloc(ref(ProtoType), long);
extern ref(ValRep) LVRACAlloc(ref(ProtoType), long);
extern long inLVRA(ref(Object));
extern long LVRARestInBlock(ref(LVRABlock));
extern void LVRAkill(struct ValRep *);
extern ref(Object) CopyObjectToLVRA(ref(ValRep)); 
#ifdef RTDEBUG
void LVRACheck(void);
long LVRAAlive(ref(ValRep));
#endif

/* GC/misc.c */
#ifdef RTDEBUG
extern void Illegal();
#endif
extern long isObject(ref(Object));
extern long inBetaHeap(ref(Object));
extern long ObjectType(ref(Object));
extern void Claim(long, char*);
#ifdef macintosh
extern void InitTheCursor(void);
extern void RotateTheCursor(void);
extern void RotateTheCursorBack(void);
#endif


#ifdef sparc
/* Fucking header files on sun4 do not include function prototypes?? */
extern void *memalign(/*unsigned alignment, unsigned size*/);
extern int fprintf(FILE *, const char *, ...);
extern int fflush(FILE *);
extern int tolower(int);
extern int fclose(FILE *);
#ifdef sun4s
extern int pclose(FILE *);
#else
extern void pclose(FILE *);
#endif
extern int fscanf(FILE *stream, const char *format, ...);
#endif
