#include "beta.h"
#include "rtsighandler.h"

extern int doshutdown(int fd, int how);

#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */

#include <stdio.h>
#include <errno.h>
#include "valhallaComm.h"
#include "dot.h"

#ifndef nti
#ifdef MAC

#define ntohl(x) x
#define htonl(x) x

#else /* not mac */
#include <sys/types.h>
#ifdef linux /* hack needed to avoid -pedantic-warning with redhat haeder files */
#  ifndef __STRICT_ANSI__ 
#    define __STRICT_ANSI__
#    include <netinet/in.h>
#    undef __STRICT_ANSI__
#  endif /* __STRICT_ANSI__  */
#else
#  include <netinet/in.h>
#endif /* linux */
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#endif /* mac */
#endif /* nti */

#if (defined(UNIX) && !defined(hppa))
static void *self=0;
#endif /* UNIX */


/* TRUE iff ValhallaOnProcessStop is active. Used to check
 * for reentrance of ValhallaOnProcessStop. This could happen
 * in case of bus-errors or the like during communication with
 * valhalla. 
*/
static int invops = 0;


/* SOCKET OPERATIONS
 * ================= */

#include "valhallaSOCKETS.h"

#define commbufsize 8192
#define WSPACE (commbufsize-wnext)
#define RAVAIL (rlen-rnext)

char *wbuf, *rbuf;
int *wheader, *rheader;
int wnext, rnext, rlen;

static int sock;  /* active socket */
static int psock; /* passive socket. Used if this process started valhalla. */

void valhalla_create_buffers ()
{
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_create_buffers\n"));  
  wheader = (int *) malloc (commbufsize+2*sizeof(int)); wnext = 0;
  rheader = (int *) malloc (commbufsize+2*sizeof(int)); rnext = 0; rlen = 0;
  wbuf = (char *) &wheader[2];
  rbuf = (char *) &rheader[2];
}

void valhalla_init_sockets (int valhallaport)
{
#if (defined(UNIX) && !defined(hppa))
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_init_sockets\n"));  
  TRACE_VALHALLACOMM(fprintf(output,"debuggee: valhallaport=%d\n", valhallaport));
  DEBUG_VALHALLA(fprintf(output,"debuggee: dlopen(NULL)\n"));
  self=dlopen(NULL, (RTLD_NOW | RTLD_GLOBAL) );
  if (!self) {
    fprintf(output, 
            "debuggee: dlopen(NULL) failed. Do NOT use dynamic compilation!\n");
  }
#endif /* UNIX */
#ifdef nti
  valhalla_initSockets();
#endif
  sock = valhalla_openActiveSocket (valhalla_inetAddrOfThisHost(),valhallaport);
  if (sock==-1) {
    fprintf (output, 
             "valhalla_init_sockets failed. errno=%d (%s)\n",
             errno,
             strerror(errno));
        exit(0);
  } else {
    valhalla_create_buffers ();
  }
}

void valhalla_await_connection (void)
{ int blocked;
  unsigned long inetAdr;
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_await_connection\n"));  
  sock = valhalla_acceptConn (psock,&blocked,&inetAdr);
  if (sock==-1) {
    fprintf (output,"valhalla_await_connection: acceptConn failed\n");
    exit (99);
  } else {
    valhalla_create_buffers ();
  }
}

static void valhalla_socket_flush (void)
{
  if (!wnext) return;

  wheader[0] = htonl((wnext+3)/4); /* len = number of longs of data */
  wheader[1] = htonl(wnext); /* header = number of bytes of data. */
  TRACE_VALHALLACOMM({
    fprintf(output,
	    "debuggee: valhalla_socket_flush: len=%d,header=%d\n",
	    (int)ntohl(wheader[0]),
	    (int)ntohl(wheader[1])
	    );
  });
  if (valhalla_writeDataMax(sock,(char *)wheader, (4*ntohl(wheader[0]))+8) 
      != (int)(4*ntohl(wheader[0]))+8) {
    fprintf (output, "WARNING -- valhalla_socket_flush failed. errno=%d\n",errno);
  }
  /* Flush output stream also, to make sure everything written by debuggee is
   * printed, before valhalla starts outputting to same stream
   */
  fflush(output);
  /* Nothing more to write: */
  wnext=0;
}

void valhalla_writebytes (const char* buf, int bytes)
{ int written = 0;
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_writebytes\n"));  
  while (written<bytes) { 
    if (WSPACE<bytes-written) {
      memcpy (&wbuf[wnext],&buf[written],WSPACE);
      written = WSPACE+written;
      wnext=commbufsize;
      valhalla_socket_flush ();
    } else {
      memcpy (&wbuf[wnext],&buf[written],bytes-written);
      wnext = wnext+bytes-written;
      return;
    }
  }
}

void valhalla_writeint (int val)
{ 
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_writeint: writing integer 0x%x\n",(int)val));  
  valhalla_writebytes ((char *)&val,sizeof(val));
}

void valhalla_writetext (const char* txt)
{ 
  int len = strlen (txt);
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_writetext \"%s\"\n", txt));  
  valhalla_writeint (len);
  valhalla_writebytes (txt,len+1);
}

/* valhalla_readtext:
 *   Reads text into allocated string.
 *   The string should be FREE'ed after use.
 */
char *valhalla_readtext (void)
{
  char *txt;
  int len;
  
  len=valhalla_readint();
  txt=MALLOC(len+1);
  valhalla_readbytes (txt,len+1);
  return txt;
}

void on_valhalla_crashed (void)
{
  fprintf (output, "Debuggee: Valhalla crashed? Exiting.\n");
  exit (99);
}

void valhalla_fill_buffer ()
{ 
  int received;
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_fill_buffer\n"));

  received = valhalla_readDataMax (sock,(char *) &rheader[0],sizeof(int));
  rheader[0]=htonl(rheader[0]);
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_fill_buffer: converted rheader[0] to 0x%x\n",(int)rheader[0]));

  if (received != sizeof(int)) { 
    TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_fill_buffer,1\n"));
    on_valhalla_crashed(); 
  } 

  received = valhalla_readDataMax (sock,(char *) &rheader[1],sizeof(int));
  rheader[1]=htonl(rheader[1]);
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_fill_buffer: converted rheader[1] to 0x%x\n",(int)rheader[1]));

  if (received != sizeof(int)) { 
    TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_fill_buffer,2\n"));
    on_valhalla_crashed();
  }

  if (rheader[0]*4>commbufsize) {
    TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_fill_buffer,3 (rheader[0]*4=%d>commbufsize=%d)\n",rheader[0]*4,commbufsize));
    
    on_valhalla_crashed();
  } 

  if (valhalla_readDataMax (sock,rbuf,rheader[0]*4) != rheader[0]*4) {
    TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_fill_buffer,4\n"));
    on_valhalla_crashed();
  }

  rnext=0; rlen=rheader[1];
}

void valhalla_readbytes (char* buf, int bytes)
{ int read=0;
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_readbytes\n"));  
  valhalla_socket_flush();
  while (read<bytes) {
    if (RAVAIL<bytes-read) {
      memcpy (&buf[read],&rbuf[rnext],RAVAIL);
      read = RAVAIL+read;
      valhalla_fill_buffer ();
    } else {
      memcpy (&buf[read],&rbuf[rnext],bytes-read);
      rnext = rnext+bytes-read;
      return;
    }
  }
}

int valhalla_readint ()
{ int val;
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_readint\n"));  
  valhalla_readbytes ((char *) &val,sizeof(val));
  TRACE_VALHALLACOMM (fprintf(output,"debuggee: valhalla_readint: read 0x%x\n",(int)val));  
  return val;
}


/* DOTgarbageOnDelete
 * ==================
 * 
 * Dummy function used as parameter to DOT operations demanding a callback
 * function. Deleted indices are not saved explicitly since DOT is scanned
 * each time the process stops to keep valhalla up to date with its part
 * of the DOT contents. */

static void DOTgarbageOnDelete (int handle)
{ 
}

#ifdef RTDEBUG
void printOpCode (int opcode)
{
  switch (opcode) {
  case VOP_SCANGROUPS:  
    fprintf (output,"VOP_SCANGROUPS"); break;
  case VOP_KILL:  
    fprintf (output,"VOP_KILL"); break;
  case VOP_GETDATAMEM: 
    fprintf (output,"VOP_GETDATAMEM"); break;
  case VOP_GETINSTRUCTIONMEM: 
    fprintf (output,"VOP_GETINSTRUCTIONMEM"); break;
  case VOP_SETDATAMEM: 
    fprintf (output,"VOP_SETDATAMEM"); break;
  case VOP_GETDATAWORDS:  
    fprintf (output,"VOP_GETDATAWORDS"); break;
  case VOP_CONTINUE:  
    fprintf (output,"VOP_CONTINUE"); break;
  case VOP_DOTINSERT: 
    fprintf (output,"VOP_DOTINSERT"); break;
  case VOP_GETPROTOINFO: 
    fprintf (output,"VOP_GETPROTOINFO"); break;
  case VOP_DOTDELETE:
    fprintf (output,"VOP_DOTDELETE"); break;
  case VOP_OBJADRCANONIFY:
    fprintf (output,"VOP_OBJADRCANONIFY"); break;
  case VOP_SCANSTACK:
    fprintf (output,"VOP_SCANSTACK"); break;
  case VOP_BETARUN:
    fprintf (output,"VOP_BETARUN"); break;
  case VOP_MEMALLOC:
    fprintf (output,"VOP_MEMALLOC"); break;
  case VOP_MEMFREE:
    fprintf (output,"VOP_MEMFREE"); break;
  case VOP_EXECUTEOBJECT:
    fprintf (output,"VOP_EXECUTEOBJECT"); break;
  case VOP_ADDGROUP:
    fprintf (output,"VOP_ADDGROUP"); break;
  case VOP_LOOKUP_SYM_OFF:
    fprintf (output,"VOP_LOOKUP_SYM_OFF"); break;
  case VOP_LOOKUP_ADDRESS:
    fprintf (output,"VOP_LOOKUP_ADDRESS"); break;
  case VOP_MAIN_PHYSICAL:
    fprintf (output,"VOP_MAIN_PHYSICAL"); break;
  case VOP_HEAPINFO:
    fprintf (output,"VOP_HEAPINFO"); break;
  case VOP_PROGRAM_PATH:
    fprintf (output,"VOP_PROGRAM_PATH"); break;
  case VOP_EXT_HEAPINFO:
    fprintf (output,"VOP_EXT_HEAPINFO"); break;
  case VOP_SCANHEAPS:
    fprintf (output,"VOP_SCANHEAPS"); break;
  case VOP_GETREFSTO:
    fprintf (output,"VOP_GETREFSTO"); break;
  default:
    fprintf (output,"UNKNOWN OPCODE: %d", opcode); break;
  }
}
#endif

static int valhallaCommunicate (int pc, int sp, Object *curObj);

extern char *Argv (int);

/* VALHALLAINIT
 * ============
 * 
 * Called when connection to valhalla should be setup. If valhalla is already
 * running, valhallaID is expected to contain the PID of the valhalla process 
 * is textual form. */

void valhallaInit (int debug_valhalla)
{ 
  DEBUG_VALHALLA(fprintf(output,"debuggee: valhallaInit\n"));

  if (valhallaID) {
    int valhallaPORT;

    /* Valhalla is already running. */
    valhallaPORT = atoi (valhallaID);
    DEBUG_VALHALLA (fprintf (output,"debuggee: valhalla port = %d\n",valhallaPORT));
    valhalla_init_sockets (valhallaPORT);
  } else {
#if  defined(nti) || defined(MAC)
    fprintf(output,"betarun: valhalla is not runnning\n");
    exit(99);
#else /* not nti */

    long port=0;
    unsigned long inetAdr = 0;
    int valhallaPID;
    int pid = getpid ();

    /* Valhalla is not running. */
    
    psock = valhalla_createPassiveSocket (&port,&inetAdr);
    if (psock==-1) {
      fprintf (output,"Failed to create passive socket\n");
      return;
    }
    
    valhallaPID = fork ();

    if (valhallaPID) {

      if (valhallaPID!=-1) {
        fprintf (output,"Waiting for valhalla (pid=%d) to connect\n",valhallaPID);
        valhallaID = malloc (20);
        sprintf (valhallaID,"%d",(int)port);
        valhalla_await_connection ();
      } else {
        fprintf (output, "Could not fork\n");
        shutdown (psock,2);
        return;
      }
      DEBUG_CODE(DebugValhalla = debug_valhalla);
      
    } else {
      char valhallaname[200];
      char tmppid[20], tmpport[20];
      char* betalib;
      
      betalib = getenv ("BETALIB");
      if (!betalib) {
        betalib="/usr/local/lib/beta";
        DEBUG_VALHALLA(fprintf(output,"debuggee: BETALIB not found\n"));
      }
      /*sprintf (valhallaname,"%s/%s",betalib,"bin/valhalla2.0");*/
      sprintf (valhallaname,"%s/%s",betalib,"debugger/v2.2.x/valhalla");
      sprintf (tmppid,"%d",pid);
      sprintf (tmpport,"%d",(int) port);
      
      execl (valhallaname,valhallaname,"-BOPT","debugValhalla","TRUE","-PORT",tmpport,"-PID",tmppid,"-EXECNAME",Argv(1),(char *) 0);
      fprintf (output, "Could not exec\n");
      exit (99);
    }
#endif /* nti */
  }

  /* Make BetaSignalHandler handle the SIGINT signal.
   * Since SIGINT is not handled specially by the runtime system,
   * it will be sent to DisplayBetaStack, and from there to
   * valhallaOnProcessStop that will recognize it as a breakpoint hit. */
  
#ifndef nti
#ifndef MAC
  InstallSigHandler(SIGINT);
#endif
#endif

  /* Initialize DOT */

  /*fprintf(output, "DOTinit()\n");*/
  DOTinit ();
  /*fprintf(output, "DOTinit() done\n");*/
  /* Do initial communication with valhalla. ValhallaCommunicate returns
   * what to do next. */

  { int todo;
    switch (todo=valhallaCommunicate (0,0,0)) {
    case CONTINUE: break;
    case TERMINATE: exit (99);
    default:
      fprintf (output, "Unexpected return from valhallaCommunicate: %d \n",
               todo);
      exit (99);
    }
  }
} /* End ValhallaInit */



/* int valhallaCommunicate (int pc, int sp, Object *curObj)
 * ==========================
 *
 * Serves requests from valhalla regarding the state of this process.
 * PC is needed to serve VOP_SCANSTACK requests.
 *
 * Possible return values:
 *    0: CONTINUE.
 *    1: TERMINATE. */

void HandleStackCell(long returnAdr, Object *returnObj)
/* Used by VOP_SCANSTACK */
{
  DEBUG_VALHALLA (fprintf(output,"debuggee: forEachStackEntry \n"));  
  if (GETPROTO(returnObj)==DopartObjectPTValue){
    /* Fetch the real object */
    DEBUG_VALHALLA({
      fprintf(output,
            "debuggee: forEachStackEntry: fetching Origin 0x%x from DoPartObject 0x%x\n",
	      (int)((DopartObject *)returnObj)->Origin,
	      (int)returnObj);
    });
    returnObj = ((DopartObject *)returnObj)->Origin;
  }
  valhalla_writeint ((int)returnAdr);
  valhalla_writeint ((int)returnObj);
  DEBUG_VALHALLA({
    fprintf(output,
            "debuggee: forEachStackEntry: returnAdr=0x%x, returnObj=",
            (int)returnAdr);
    PrintObject((Object*)returnObj);
    fprintf(output, "\n");
  });
}

/* HasRefTo: */
static long HasRefToTargetSize;
static long HasRefToFlag;
static Object* HasRefToTarget;
static void HasRefToCheck(REFERENCEACTIONARGSTYPE)
{
  long ptr = (long)(*theCell);
  if ((long)HasRefToTarget <= ptr 
      && ptr < (long)HasRefToTarget + HasRefToTargetSize) {
    HasRefToFlag = TRUE;
  }
}

void HasRefDoObj(Object* obj) 
{
  ProtoType * proto;
  long size;
  HasRefToFlag = FALSE;
  scanObject(obj, HasRefToCheck, NULL, TRUE);
  if (HasRefToFlag) {
    proto = GETPROTO(obj);
    size = 4*ObjectSize(obj);
    DEBUG_VALHALLA(fprintf(output, "%08x %08x %5d\n", 
                           (int)obj, (int)proto, (int)size));
    valhalla_writeint((int)obj);
    valhalla_writeint((int)proto);
    valhalla_writeint((int)size);
  }
}

void HasRefDoRef(Object** theCell) 
{
  ProtoType * proto;
  long size;
  if (theCell) {
    if ((long)HasRefToTarget <= (long)*theCell
        && (long)*theCell < (long)HasRefToTarget + HasRefToTargetSize) {
      proto = NULL;
      size = 4;
      DEBUG_VALHALLA(fprintf(output, "%08x %08x %5d\n", 
                             (int)theCell, (int)proto, (int)size));
      valhalla_writeint((int)theCell);
      valhalla_writeint((int)proto);
      valhalla_writeint((int)size);
    }
  }
}


extern void Return ();

#ifdef NEWRUN
static void terminate_reference_stack(long *PrevSP)
{
  long *StackCell;

  StackCell = PrevSP-(DYN_OFF+1) /* Don't clear DYN */;
  DEBUG_VALHALLA(fprintf(output, 
			 "terminate_reference_stack(PrevSP=0x%x):"
			 "cell 0x%x changed from 0x%0x to 0.\n",
			 (int)PrevSP,
			 (int)(StackCell),
			 (int)(*StackCell));
		 fflush(output));
  *StackCell=0;
  return;
}

static void fix_stacks(long PrevSP)
{
  /* The SP is already winded back in beginning
   * of DisplayBetaStack, before it calls valhallaOnProcessStop, which calls
   * valhallaCommunicate, which calls fix_stacks.
   * Hence the name PrevSP.
   */
    
  /* The referencestack part of the top frame is not
   * necessarily terminated at this point (depending on
   * how the debuggee stopped).
   * The two main cases are:
   *   1. Debuggee is stopped in a breakpoint.
   *   2. Debuggee detected a fatal error
   *      (Qua may be an exception, if QuaCont is set).
   * Here we go in and terminate the reference stack as if there was no
   * references on it. This is assumed OK in case 1, since Ole
   * claims that the compiler has nothing on the reference stack
   * at the points where breakpoints may be set.
   * In case two, we may forget a few references on the stack by terminating
   * it, but since a fatal error has happened in the debugee, this should
   * not harm it - it will not be able to continue anyway (yet - has to be
   * reconsidered when system exceptions are introduced).
   * A more elegant solution would be to include in the .db file format
   * how many references are on stack between each imperative.
   */
  
  DEBUG_STACK(fprintf(output, "fix_stacks: Terminating reference stack.\n"));
  terminate_reference_stack((long*)PrevSP);
}
#endif /* NEWRUN */

INLINE void *valhalla_CopyCPP(Structure *struc, long *sp, Object *curobj)
{
  void *cb = 0;
#ifdef sparc
  extern void *CCopyCPP(Structure * theStruct, Object * theObj);
  cb = CCopyCPP(struc, curobj);
#endif /* sparc */
#ifdef intel
  /* C implementation of CopyCPP for intel, as implemented
   * in RUN/linuxadditions.run and RUN/ntiadditions.run
   */
  extern void HandleCB(void);
  DEBUG_CODE(NumCopyCPP++);
  if (!struc) return (void *)0 /* NULL function pointer given to C */;
  /* Take the next free entry in the Call Back Functions Area.  */
  /* This area is defined by 
   * [ lastCBFABlock->entries <= CBFATop < CBFALimit ].
   */
  if ((long)CBFATop+CallBackEntrySize > (long)CBFALimit){
    CBFArelloc();
  }
  CBFATop->theStruct = struc;
  /* Write call opcode */
  CBFATop->code[0] = 0xe8;
  /* Write call argument: relative offset to HandleCB */
  *(long*)(&CBFATop->code[1]) = (signed long)&HandleCB-(signed long)&CBFATop->code[5];
  /* Write ret opcode */
  CBFATop->code[5] = 0xc3;
  cb = (void *)&CBFATop->code[0];
  CBFATop  = (CallBackEntry*)((long)CBFATop + CallBackEntrySize);
  /* __asm__("invd"); Flush cache -- i486 only */
#endif /* intel */
#ifdef NEWRUN
  extern void *CopyCPP(Structure *theStruct);
  cb = CopyCPP(struc);  
#endif /* NEWRUN */
#ifdef hppa
  fprintf(output, "valhalla_CopyCPP: NYI for hppa\n");
  /* Valhalla not yet supported */
#endif /* hppa */
  return cb;
}

INLINE int findMentry (ProtoType *proto)
     /* 
      * Return the Mentry point corresponding to a T entry, or 0, if
      * the corresponding pattern does not have a do-part.
      * 
      */
{ 
  DEBUG_VALHALLA (fprintf(output,"debuggee: findMentry\n"));  
  if (proto && proto->MpartOff){
#ifdef MAC
    return **(long **)((long)proto+proto->MpartOff);
#else
    return *(long*)((long)proto+proto->MpartOff);
#endif
    
  } else {
    return 0;
  }
}

#ifdef MAC
static void print_protos(group_header *gh)
{
  long* proto=&gh->protoTable[1];
  int i, NoOfPrototypes;
  ProtoType *current;
  
  NoOfPrototypes = gh->protoTable[0];
  for (i=0; i<NoOfPrototypes; i++){
    current = (ProtoType *) *proto;
    if (current->MpartOff) {
      fprintf(output, "%d\n", **(long **)((long)current+current->MpartOff));
    }
    proto++;
  }
  return;
}

static void adjust_header(group_header *gh)
{
  long* proto=&gh->protoTable[1];
  unsigned long mincode = 0xFFFFFFFF;
  unsigned long maxcode = 0L;
  unsigned long mindata = 0xFFFFFFFF;
  unsigned long maxdata = 0L;
  
  unsigned long mpart;
  unsigned long *code;
  
  int i, NoOfPrototypes;
  ProtoType *current;
  
  NoOfPrototypes = gh->protoTable[0];
  for (i=0; i<NoOfPrototypes; i++){
    current = (ProtoType *) *proto;
    
    if(*proto > maxdata) {
      maxdata = (unsigned long) *proto;
    }
    if(*proto < mindata) { 
      mindata = (unsigned long) *proto;
    }
    
    if (current->MpartOff) {
      mpart = **(long **)((long)current+current->MpartOff);
      
      if (mpart < mincode) {
		mincode = mpart;
      }
      if (mpart > maxcode) {
		maxcode = mpart;
      }
    }
    proto++;
  }
  
  if(maxdata == 0) {
  	maxdata = (unsigned long) gh->data_start;
  }
  gh->code_start = *(long *)(gh->code_start);
  gh->code_end = *(long *)(gh->code_end);
  gh->data_end = (group_header *) (maxdata + 4);
  return;
}

#endif /* mac */


/* used in find-attribute */

int evaluatorResult;
void evaluatorSaveInt(int val)
{
  evaluatorResult = val; 
}



static int valhallaCommunicate (int pc, int sp, Object* curObj)
{ 
  int opcode=0;
  
  /*fprintf(output,"debuggee: valhallaCommunicate\n");*/
  
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhallaCommunicate\n"));  
  while (TRUE) {
    opcode = valhalla_readint ();
#ifdef RTDEBUG
    DEBUG_VALHALLA(fprintf (output, "debuggee: valhallaCommunicate: opcode is "));
    DEBUG_VALHALLA(printOpCode(opcode); fprintf (output,"\n"));
#endif
    switch (opcode) {
    case VOP_SCANGROUPS: { 
      group_header *current = 0;
      valhalla_writeint (opcode);
      while ((current = NextGroup (current))) {
#ifdef MAC
        DEBUG_VALHALLA(print_protos(current));
        adjust_header(current);
#endif 
        valhalla_writetext (NameOfGroupMacro(current));/* groupName */
        valhalla_writeint ((int) current->data_start); 
        valhalla_writeint ((int) current->data_end);   
        valhalla_writeint ((int) current->code_start); 
        valhalla_writeint ((int) current->code_end);   
        valhalla_writeint ((int) current->unique_group_id.hash);       
        valhalla_writeint ((int) current->unique_group_id.modtime);
      }
      valhalla_writetext ("");
      valhalla_socket_flush ();
    }
    break;
    case VOP_KILL:
      doshutdown (sock,2);
      return TERMINATE;
    case VOP_CONTINUE:
      valhallaIsStepping = valhalla_readint ();
      valhalla_writeint (opcode);
      valhalla_socket_flush ();
      return CONTINUE;
    case VOP_GETDATAMEM:
    case VOP_GETINSTRUCTIONMEM: { 
      int address = valhalla_readint ();
      int bytelen = valhalla_readint ();
      DEBUG_VALHALLA(fprintf (output, "debuggee: VOP_GET*MEM: %d bytes from address 0x%x\n",bytelen, address));
      valhalla_writeint (opcode);
      valhalla_writebytes ((char *) address, bytelen);
      valhalla_socket_flush ();
    }
    break;
    case VOP_SETDATAMEM: {
      int address = valhalla_readint ();
      int bytelen = valhalla_readint ();
      valhalla_readbytes((char *) address, bytelen);
      valhalla_writeint (opcode);
      valhalla_socket_flush ();
    }
    break;
    case VOP_GETDATAWORDS: { 
      int address;
      valhalla_writeint (opcode);
      while ((address = valhalla_readint ()))
        valhalla_writeint ((* (int *) address));
      valhalla_socket_flush ();
    }
    break;
    case VOP_OBJADRCANONIFY: { 
      int address;
      int legal;
      Object *obj = (Object *) valhalla_readint ();
      
      DEBUG_VALHALLA(fprintf(output,"debuggee: Got object %d\n",(int) obj));
      if (obj && inBetaHeap(obj) && isObject(obj)){
        legal=1;
      } else {
        legal=0;
      }
      if (legal) {
        address = (int) obj;
        if ((GETPROTO(obj)) != (ComponentPTValue)) {
          DEBUG_VALHALLA(fprintf(output,"debuggee: Not ComponentPTValue\n"));
          if (obj->GCAttr == -6) {
            Component *comp = (Component *) (address - 24);
            DEBUG_VALHALLA(fprintf(output,"debuggee: GCAttr was -6\n"));
            if (GETPROTO(comp) == (ComponentPTValue)){
              address = address - 24;
            }
          }
        }
      } else {
        address=0;
        DEBUG_VALHALLA(if (obj && !legal) fprintf(output,"debuggee: NOT object!\n"));
      }
      valhalla_writeint (opcode);
      valhalla_writeint (address);
      valhalla_socket_flush ();
    }
    break;
    case VOP_DOTINSERT: { 
      Object *address;
      int handle;
      
      address = (Object*)valhalla_readint ();
      handle = DOThandleInsert (address, DOTgarbageOnDelete, FALSE);
      
      valhalla_writeint (opcode);
      valhalla_writeint (handle);
      valhalla_writeint (ObjectSize(address));
      valhalla_socket_flush ();
    }
    break;
    case VOP_DOTDELETE: {
      int handle = valhalla_readint ();
      DOThandleDelete (handle);
      valhalla_writeint (opcode);
      valhalla_socket_flush ();
    }
    break;
    case VOP_GETPROTOINFO: {
      group_header* header; int tableSize;
      long** protoTable; int i;
      
      header = (group_header*) valhalla_readint ();
      protoTable = (long **) header->protoTable;
      
      tableSize= (int) protoTable[0];
      
      for (i=1; i<=tableSize; i++) {
        /* M entry point: */
        valhalla_writeint (findMentry ((ProtoType *) protoTable[i]));
        
        valhalla_writeint (protoTable[i][1]); /* G entry point. */
        valhalla_writeint (protoTable[i][4]); /* (formIndex,AstIndex) */
      };
      valhalla_writeint (opcode);
      
      valhalla_socket_flush ();
    }
    break;
    case VOP_SCANSTACK: { 
      Component *comp;
      int stacktype;
      
      comp = (Component *) valhalla_readint ();
      DEBUG_VALHALLA({
	fprintf (output,"debuggee: Received component: ");
	PrintObject((Object*)comp);
	fprintf(output, "\n");
      });
      
      DEBUG_VALHALLA(fprintf (output,"debuggee: Scanning ComponentStack.\n"));
      stacktype=scanComponentStack (comp,curObj,pc,HandleStackCell);
      DEBUG_VALHALLA(fprintf (output,"debuggee: ScanComponentStack done.\n"));
      
      valhalla_writeint (-1);
      valhalla_writeint (stacktype);

      for(comp=comp->CallerComp;comp;comp=comp->CallerComp) {
	DEBUG_VALHALLA({
	  fprintf (output,"debuggee: ScanComponentStack: found component: ");
	  PrintObject((Object*)comp);
	  fprintf(output, "\n");
	});
	valhalla_writeint ((int)comp);
      };
      valhalla_writeint (-1);
      valhalla_writeint (opcode);
      valhalla_socket_flush ();
    }
    break;
    case VOP_BETARUN: {
      valhalla_writeint (opcode);
      valhalla_writetext (BETARUN_ID);
      valhalla_socket_flush ();
    }
    break;
    case VOP_MEMALLOC: {
      long numbytes, addr;
      numbytes = (long) valhalla_readint ();
      addr = (long) MALLOC(numbytes);
      DEBUG_VALHALLA(fprintf(output, "VOP_MEMALLOC(%d) returns 0x%08x\n",(int)numbytes,(int)addr));

      valhalla_writeint (opcode);
      valhalla_writeint (addr);
      valhalla_socket_flush ();
    }
    break;
    case VOP_MEMFREE: {
      void * addr;
      addr = (void *) valhalla_readint ();
      FREE(addr);
      DEBUG_VALHALLA(fprintf(output, "VOP_MEMFREE(%d)\n",(int)addr));

      valhalla_writeint (opcode);
      valhalla_socket_flush ();
    }
    break;
    case VOP_EXECUTEOBJECT: {
      Object    * origin;
      ProtoType * proto;
      Structure * struc;
      long   old_valhallaIsStepping;
      void (*cb)(void);
      int origin_handle, curObj_handle;

      DEBUG_STACK(fprintf(output, "VOP_EXECUTEOBJECT: SP=0x%x\n", (int)sp));
      DEBUG_STACK(fprintf(output, "VOP_EXECUTEOBJECT: PC=0x%x\n", (int)pc));

      /* Debuggee is currently stopped in C code.
       * To activate a BETA object in debuggee, we thus have
       * to create a structure object "struc" from
       * "origin" and "proto" and then to create a
       * callback entry using "struc" and then
       * call this callback entry.
       * Before calling the callback entry the C variable
       * BetaStackTop should be set to the value of the
       * stack pointer at the point where debuggee was
       * stopped (trapped).
       */
      origin = (Object *) valhalla_readint ();
      proto  = (ProtoType *) valhalla_readint ();
      
      DEBUG_VALHALLA(fprintf(output, "VOP_EXECUTEOBJECT:\n"));
      DEBUG_VALHALLA(fprintf(output, "Origin Object:\n"));
      DEBUG_VALHALLA(DescribeObject((Object *)origin));
      DEBUG_VALHALLA(fprintf(output, "\n"));
      DEBUG_VALHALLA(fprintf(output, "Prototype: %s\n", ProtoTypeName(proto)));

#ifdef NEWRUN
      /* SP already adjusted one frame back by DisplayBetaStack; */
      fix_stacks(sp);
#endif /* NEWRUN */

      /* Save origin and curObj in DOT in case of a GC during VAlloS */
      origin_handle = DOThandleInsert(origin, DOTgarbageOnDelete, FALSE);
      curObj_handle = DOThandleInsert(curObj, DOTgarbageOnDelete, FALSE);
      /* VAlloS may cause GC - is specially constructed to handle this */
      struc = VAlloS(proto, (long*)sp, (long)pc);
      origin = DOThandleLookup(origin_handle);
      curObj = DOThandleLookup(curObj_handle);
      /* struc->iOrigin is NOT set up by VAlloS */
      assignRef((long*)&struc->iOrigin, (Item*)origin);
      /* Dispose the DOT handles */
      DOThandleDelete(origin_handle);
      DOThandleDelete(curObj_handle);
      DEBUG_VALHALLA(fprintf(output, "Struc Object:\n"));
      DEBUG_VALHALLA(DescribeObject((Object *)struc));
      DEBUG_VALHALLA(fprintf(output, "\n"));

      /* Construct callback function */
      cb = (void (*)(void))valhalla_CopyCPP(struc, (long*)sp, curObj);
      DEBUG_VALHALLA(fprintf(output, "Installed callback at 0x%08x\n", (int)cb));

      DEBUG_VALHALLA(fprintf(output, 
			     "Calling callback function [%d]\n",
			     valhalla_exelevel
			     ));
      old_valhallaIsStepping = valhallaIsStepping;
      valhallaIsStepping = FALSE;
      valhalla_exelevel++;

      /*Clear old saved value */
      evaluatorResult = 0;

      /* Save stackpointer in BetaStackTop to make the trap look like 
       * an external call
       */
      set_BetaStackTop((long*)sp);
      /* valhalla_socket_flush? */
      /* Callback: cb() may cause GC. Stack setup has been adjust for this */
      cb();
      valhalla_exelevel--;
      valhallaIsStepping = old_valhallaIsStepping;
      DEBUG_VALHALLA(fprintf(output, "VOP_EXECUTEOBJECT done.\n"));
      valhalla_writeint (opcode);
      valhalla_writeint (evaluatorResult);
      valhalla_writeint (opcode);
      valhalla_socket_flush ();
    }
    break;
    case VOP_ADDGROUP: {
      group_header *gh;
      gh = (group_header *) valhalla_readint ();
      DEBUG_VALHALLA(fprintf(output, "VOP_ADDGROUP(0x%x)\n",(int)gh));
      AddGroup(gh);
      valhalla_writeint (opcode);
      valhalla_writetext (NameOfGroupMacro(gh));/* groupName */
      valhalla_writeint ((int) gh->data_start); 
      valhalla_writeint ((int) gh->data_end);   
      valhalla_writeint ((int) gh->code_start); 
      valhalla_writeint ((int) gh->code_end);   
      valhalla_writeint ((int) gh->unique_group_id.hash);       
      valhalla_writeint ((int) gh->unique_group_id.modtime);
      valhalla_socket_flush ();
    }
    break;
    case VOP_LOOKUP_SYM_OFF: {
      long addr = valhalla_readint();
      const char *sym=0;
      long off=0;
      DEBUG_VALHALLA(fprintf(output,"VOP_LOOKUP_SYM_OFF(%d)\n",(int)addr));
#if defined(sun4s) || defined(linux)
      /* Not available for sgi - grrrr... */
      {
        static Dl_info info;
        if (dladdr((void*)addr, &info)){
          sym = info.dli_sname;
          off = (long)addr - (long)info.dli_saddr;
        }
      }
#else /* !sun4s */
      fprintf(output, "debuggee: VOP_LOOKUP_SYM_OFF(0x%x): NYI\n", (int)addr);
#endif /* sun4s */
      valhalla_writeint (opcode);
      valhalla_writetext(sym);
      valhalla_writeint(off);
      valhalla_socket_flush ();
    }
    break;
    case VOP_LOOKUP_ADDRESS: {
      char *sym = valhalla_readtext();
      long addr = 0;
      DEBUG_VALHALLA(fprintf(output,"VOP_LOOKUP_ADDRESS(%s)=",sym));
#if (defined(UNIX) && !defined(hppa))
      addr = (long)dlsym(self, sym);
#else /* !UNIX */
      fprintf(output, "debuggee: VOP_LOOKUP_ADDRESS: NYI\n");
#endif /* UNIX */
#if (defined(UNIX) && !defined(hppa))
      DEBUG_VALHALLA({
	fprintf(output,"0x%x\n",(int)addr);
	if (!addr) {
	  char *e = dlerror();
	  if (e) fprintf(output, "*** debuggee: dlerror: %s\n", e);
	}
      });
#endif /* UNIX */
      FREE(sym);
      valhalla_writeint(opcode);
      valhalla_writeint(addr);
      valhalla_socket_flush ();
    }
    break;
    case VOP_MAIN_PHYSICAL: {
      DEBUG_VALHALLA(fprintf(output,
                             "VOP_MAIN_PHYSICAL()=0x%x",
                             (int)getMainPhysical()));
      valhalla_writeint(opcode);
      valhalla_writeint(getMainPhysical());
      valhalla_socket_flush();
    }
    break;    
    case VOP_HEAPINFO: {
      int infoID;
      int result;
      infoID=valhalla_readint();
      result=getHeapInfo(infoID);
      DEBUG_VALHALLA(fprintf(output,
			     "VOP_HEAPINFO(%d)=0x%x",
			     infoID,
			     result));

      valhalla_writeint(result);
      valhalla_socket_flush ();
    }
    break;

    case VOP_EXT_HEAPINFO: {
      /* FIXME: Extend this with information on IOA and CBFA */
      long index, min, max, usecount, usesize, freecount, freesize;
      valhalla_writeint(opcode);
      DEBUG_VALHALLA({
        fprintf(output, "   min  -   max   usecount  usesize"
                " / freecount freesize\n");
      });
      for (index = 0;
           AOAFreeListIndexGetStat(index, &min, &max, 
                                   &usecount, &usesize,
                                   &freecount, &freesize);
           index++) {
        DEBUG_VALHALLA({
          fprintf(output, "%08x-%08x %8d %8d /  %8d %8d\n",
                  (int)min, (int)max, (int)usecount, 
                  (int)usesize, (int)freecount, (int)freesize);
        });
        valhalla_writeint(index);
        valhalla_writeint(min);
        valhalla_writeint(max);
        valhalla_writeint(usecount);
        valhalla_writeint(usesize);
        valhalla_writeint(freecount);
        valhalla_writeint(freesize);
      }
      DEBUG_VALHALLA(fprintf(output, "-1\n"));
      valhalla_writeint(-1);
      DEBUG_VALHALLA(fprintf(output, "\n"));
      valhalla_socket_flush();
    }
    break;

    case VOP_PROGRAM_PATH: {
      /* Previously we referenced M1PROGRAM as a symbol here,
       * but that caused linking problems on SGI, where M1PROGRAM
       * might be in a shared library, which did not expose all
       * symbols to linker.
       * Instead we search through prototype symbols to look for
       * the name of the PROGRAM SLOT. The corresponding
       * group's groupname is what is requested.
       * Rather expensive, but this is only done once.
       */
      group_header *gh = NextGroup(0);
      char *group_name = "";
      int done = 0;

      while (!done && gh){
	long* protoptr=&gh->protoTable[1];
	int i, NoOfPrototypes;
	
	NoOfPrototypes = gh->protoTable[0];
	for (i=0; i<NoOfPrototypes; i++){
	  ProtoType *proto = *(ProtoType**)protoptr;
	  if (strcmp(ProtoTypeName(proto), "PROGRAM-~") == 0){
	    /* Found the group containing M1PROGRAM */
	    group_name = gh->group_name;
	    done = 1;
	    break;
	  } else {
	    protoptr++;
	  }
	}
	gh = NextGroup(gh);
      }
      valhalla_writeint(opcode);
      valhalla_writetext(group_name);
      valhalla_socket_flush();
    }
    break;

    case VOP_SCANHEAPS: {
      Object *current;
      Block *currentBlock;
      ProtoType * proto;
      long size;

      forceAOAGC = TRUE;
      /* FIXME: Forcing a IOA and AOAGC right here. This
       * will make the results accurate rather than approximate.
       * To get the least possible live garbage, everything has to
       * be pushed to AOA, and then AOA must be GC'ed.
       */
      
      valhalla_writeint(opcode);

      DEBUG_VALHALLA(fprintf(output, " address   proto    size\n"));
      for (current = (Object*)IOA;
           current < (Object*)IOATop;
           current = (Object*)((long)current + size)) {
        proto = GETPROTO(current);
        size = 4*ObjectSize(current);
        DEBUG_VALHALLA(fprintf(output, "%08x %08x %5d\n", 
                               (int)current, (int)proto, (int)size));
        valhalla_writeint((int)current);
        valhalla_writeint((int)proto);
        valhalla_writeint((int)size);
      }
      if (current < (Object*)IOALimit) {
        size = (long)IOALimit - (long)IOATop;
        DEBUG_VALHALLA(fprintf(output, "%08x %08x %5d\n", 
                               (int)IOATop, (int)0, (int)size));
        valhalla_writeint((int)IOATop);
        valhalla_writeint((int)0);
        valhalla_writeint((int)size);
      }
      DEBUG_VALHALLA(fprintf(output, "0\n"));
      valhalla_writeint(0);

      for (currentBlock = AOABaseBlock;
           currentBlock;
           currentBlock = currentBlock -> next) {
        for (current = (Object*)BlockStart(currentBlock);
             current < (Object*)currentBlock->limit;
             current = (Object*)((long)current + size)) {
          if (AOAISFREE(current)) {
            size = ((AOAFreeChunk*)current)->size;
            DEBUG_VALHALLA(fprintf(output, "%08x %08x %5d\n", 
                                   (int)current, (int)0, (int)size));
            valhalla_writeint((int)current);
            valhalla_writeint((int)0);
            valhalla_writeint((int)size);
          } else {
            proto = GETPROTO(current);
            size = 4*ObjectSize(current);
            DEBUG_VALHALLA(fprintf(output, "%08x %08x %5d\n", 
                                   (int)current, (int)proto, (int)size));
            valhalla_writeint((int)current);
            valhalla_writeint((int)proto);
            valhalla_writeint((int)size);
          }
        }
        DEBUG_VALHALLA(fprintf(output, "0\n"));
        valhalla_writeint(0);
      }
      DEBUG_VALHALLA(fprintf(output, "-1\n"));
      valhalla_writeint(-1);
      DEBUG_VALHALLA(fprintf(output, "\n"));
      valhalla_socket_flush();
    }
    break;

    case VOP_GETREFSTO: {
      /* FIXME: Should scan stack and CBFA as well.
       * This could be added easily, but I do not want yet another
       * copy of that code; It should be abstracted from the existing one. 
       */
      Object *current;
      Block *currentBlock;
      long size;
      Object* target;

      target = (Object*)valhalla_readint();
      DEBUG_VALHALLA(fprintf(output, "Got target=%08x: ", (int)target));
      if (!target || isObject(target)) {
        DEBUG_VALHALLA(fprintf(output, "Is object.\n"));
        valhalla_writeint(opcode);
      } else {
        DEBUG_VALHALLA(fprintf(output, "Is not object\n"));
        valhalla_writeint(-1);
        break;
      }

      HasRefToTarget = target;
      if (HasRefToTarget) {
        HasRefToTargetSize = 4*ObjectSize(HasRefToTarget);
      } else {
        HasRefToTargetSize = 4;
      }
      
      DEBUG_VALHALLA(fprintf(output, " address   proto    size\n"));
      for (current = (Object*)IOA;
           current < (Object*)IOATop;
           current = (Object*)((long)current + size)) {
        size = 4*ObjectSize(current);
        HasRefDoObj(current);
      }
      for (currentBlock = AOABaseBlock;
           currentBlock;
           currentBlock = currentBlock -> next) {
        for (current = (Object*)BlockStart(currentBlock);
             current < (Object*)currentBlock->top;
             current = (Object*)((long)current + size)) {
          if (!AOAISFREE(current)) {
            size = 4*ObjectSize(current);
            HasRefDoObj(current);
          } else {
            size = ((AOAFreeChunk*)current)->size;
          }
        }
      }
      /* now the tricky part: check all refs outside objects: */
      HasRefDoRef((Object**)&ActiveComponent);
      HasRefDoRef((Object**)&BasicItem);
      DEBUG_VALHALLA(fprintf(output, "0\n"));
      valhalla_writeint(0);
      DEBUG_VALHALLA(fprintf(output, "\n"));
      valhalla_socket_flush();
    }
    break;

    default:
      {
#ifdef nti
        char dirCh = '\\';
#else
        char dirCh = '/';
#endif
        char *execname, *localname;

        execname = ArgVector[0];
        if ( (localname=strrchr(execname, dirCh)) ) 
          localname = &localname[1];
        else
          localname = execname;
        
        fprintf (output, 
                 "%s: Unexpected valhalla opcode: %d\n", 
                 localname, 
                 opcode);
      }
    break;
    }
    DEBUG_VALHALLA(fprintf (output, "debuggee: valhallaCommunicate: opcode "));
#ifdef RTDEBUG
    DEBUG_VALHALLA(printOpCode(opcode); fprintf (output," done\n"));
#endif
  }
}


/* forEachAlive
 * ============
 *
 * Callback function used by ValhallaOnProcessStop during DOTscan. */

void forEachAlive (int handle, Object *address, DOTonDelete onDelete)
{
  DEBUG_VALHALLA({
    fprintf (output,
             "debuggee: forEachAlive: handle=%d, address=%d \n", 
             (int)handle, 
             (int)address);
  });
  if (onDelete==DOTgarbageOnDelete) {
    valhalla_writeint ((int)handle);
    valhalla_writeint ((int)address);
  }
}



/* 
 * int ValhallaOnProcessStop (long*  pc, long* sp, Object * curObj, 
 *                            long sig, long errorNumber)
 * ====================================================================
 *
 * Calls back to valhalla to inform that this process has stopped and
 * is ready to serve requests. */

int ValhallaOnProcessStop (long*  pc, long* sp, Object * curObj, 
                           long sig, long errorNumber)
{ 
  char *txt; int res;
  DEBUG_VALHALLA(fprintf(output,"debuggee: ValhallaOnProcessStop: PC=0x%x, SP=0x%x, curObj=%d,sig=%d,errorNumber=%d\n",(int) pc, (int) sp, (int) curObj, (int) sig, (int) errorNumber));
  invops++;
  if (invops > valhalla_exelevel+1) {
    fprintf (output,"FATAL: ValhallaOnProcessStop re-entered\n");
#ifdef UNIX
    DEBUG_CODE({
      fprintf(output,
	      "debuggee(PID=%d): sleeping for 10 minuttes...\n",
	      (int)getpid()
	      );
      sleep(10*60);
      fprintf(output, 
	      "debuggee(PID=%d): 10 minuttes past - dying...\n",
	      (int)getpid()
	      );
    });
#endif /* UNIX */
    exit(99);
  }

  valhalla_writeint (VOP_STOPPED);
  valhalla_writeint ((int) pc);

  if (pc==0) { /* Process about to stop. */
    valhalla_socket_flush ();
    doshutdown(sock,2);
    closeSocket(sock);
    invops=0;
    return TERMINATE;
  };

  valhalla_writeint ((int) curObj);
  valhalla_writeint ((int) ActiveComponent);
  
  valhalla_writeint ((int) sp);

  valhalla_writeint (sig);

  switch (sig) {
    /* FIXME: Use a (modified) PrintSignal here */
#ifndef MAC
#ifndef nti
  case SIGILL:  txt = "SIGILL"; break;
  case SIGFPE:  txt = "SIGFPE"; break;
  case SIGBUS:  txt = "SIGBUS"; break;
  case SIGSEGV: txt = "SIGSEGV"; break;
  case SIGINT:  txt = "SIGINT"; break;
  case SIGQUIT: txt = "SIGQUIT"; break;
#ifdef SIGTRAP
  case SIGTRAP: txt = "SIGTRAP"; break;
#endif
#ifdef SIGEMT
  case SIGEMT:  txt = "SIGEMT"; break;
#endif
#endif /* nti */
#endif /* MAC */
  default: txt = "UNKNOWN"; break;
  }
  valhalla_writetext (txt);

  DEBUG_VALHALLA(fprintf(output,"debuggee: ValhallaOnProcessStop: errorText=%s\n",txt));
                         
  valhalla_writeint (errorNumber);
  if (errorNumber<0) {
    txt = ErrorMessage (errorNumber);
    valhalla_writetext (txt);
  }

  /* Locate objects known by valhalla that have become garbage: */
  DOThandlePerformCompaction (DOTgarbageOnDelete);
    
  /* Scan and send info on all alive objects known by valhalla: */
  DOTscan (forEachAlive);
  valhalla_writeint (-1);

  /* valhalla_socket_flush (); -- not needed; done by valhalla_readint */

  if (valhalla_readint () != VOP_STOPPED)
    fprintf (output, "Warning! Wrong answer from Valhalla on VOP_STOPPED\n"); 

  
  switch (res=valhallaCommunicate ((int) pc, (int)sp, curObj)){
  case CONTINUE: break;
  case TERMINATE: exit (99);
  }
  invops--;

  /* If we came here through BetaSignalHandler, signals have been redirected to
   * ExitHandler. Reinstall BetaSignalHandler: */

#ifndef MAC
#ifndef nti
  InstallSigHandler(SIGFPE);
  InstallSigHandler(SIGILL);
  InstallSigHandler(SIGBUS);
  InstallSigHandler(SIGSEGV);
#ifdef linux
  InstallSigHandler(SIGTRAP);
#else
  InstallSigHandler(SIGEMT);
#endif
  InstallSigHandler(SIGINT);
#endif /* nti */ 
#endif /* MAC */
  return res;
}

#ifdef hppa
/* Shortcut for calling valhallaOnProcessStop from SnakeAdditions.S 
 * without having to transfer argument 5 via stack in assembler.
 */
void ValhallaOPS(long *pc, long event)
{
  ValhallaOnProcessStop(pc, 0, 0, 0, event);
}
#endif

int connected_to_valhalla ()
{
  DEBUG_VALHALLA(fprintf(output,"debuggee: connected_to_valhalla\n"));
  return (valhallaID!=0);
}
#endif /* RTVALHALLA */


