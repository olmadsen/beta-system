#include "beta.h"
extern int doshutdown(int fd, int how);

#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */

#include <stdio.h>
#include <errno.h>
#include "valhallaComm.h"
#include "valhallaFindComp.h"
#include "dot.h"

#ifdef nti 
#  ifdef nti_gnu
#    include <Windows32/Sockets.h> 
#  endif /* nti_gnu*/

#else /* not nti */

#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#endif /* nti */

#ifdef UNIX
#include <dlfcn.h>
static void *self=0;
#endif /* UNIX */




/* TRUE iff ValhallaOnProcessStop is active. Used to check
 * for reentrance of ValhallaOnProcessStop. This could happen
 * in case of bus-errors or the like during communication with
 * valhalla. 
*/

static int exelevel = 1;
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

int sock;  /* active socket */
int psock; /* passive socket. Used if this process started valhalla. */

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
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_init_sockets\n"));  
  DEBUG_VALHALLA(fprintf(output,"debuggee: valhallaport=%d\n", valhallaport));
#ifdef UNIX
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
  } else {
    valhalla_create_buffers ();
  }
}

void valhalla_await_connection ()
{ int blocked;
  unsigned long inetAdr;
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_await_connection\n"));  
  sock = valhalla_acceptConn (psock,&blocked,&inetAdr);
  if (sock==-1) {
    fprintf (output,"valhalla_await_connection: acceptConn failed\n");
    exit (99);
  } else {
    valhalla_create_buffers ();
  }
}

void valhalla_socket_flush ()
{
  wheader[0] = htonl((wnext+3)/4); /* len = number of longs of data */
  wheader[1] = htonl(wnext); /* header = number of bytes of data. */
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_socket_flush: len=%d,header=%d\n",(int)ntohl(wheader[0]),(int)ntohl(wheader[1])));
  if (valhalla_writeDataMax (sock,(char *) wheader, (4*ntohl(wheader[0]))+8) != (int)(4*ntohl(wheader[0]))+8) {
    fprintf (output, "WARNING -- valhalla_socket_flush failed. errno=%d\n",errno);
  }
  wnext=0;
}

void valhalla_writebytes (const char* buf, int bytes)
{ int written = 0;
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_writebytes\n"));  
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
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_writeint: writing integer %d\n",val));  
  valhalla_writebytes ((char *)&val,sizeof(val));
}

void valhalla_writetext (const char* txt)
{ 
  int len = strlen (txt);
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_writetext\n"));  
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
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_fill_buffer\n"));

  received = valhalla_readDataMax (sock,(char *) &rheader[0],sizeof(int));
  rheader[0]=htonl(rheader[0]);
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_fill_buffer: converted integer to %d\n",rheader[0]));

  if (received != sizeof(int)) { 
    DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_fill_buffer,1\n"));
    on_valhalla_crashed(); 
  } 

  received = valhalla_readDataMax (sock,(char *) &rheader[1],sizeof(int));
  rheader[1]=htonl(rheader[1]);
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_fill_buffer: converted integer to %d\n",rheader[1]));

  if (received != sizeof(int)) { 
    DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_fill_buffer,2\n"));
    on_valhalla_crashed();
  }

  if (rheader[0]*4>commbufsize) {
    DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_fill_buffer,3 (rheader[0]*4=%d>commbufsize=%d)\n",rheader[0]*4,commbufsize));
    
    on_valhalla_crashed();
  } 

  if (valhalla_readDataMax (sock,rbuf,rheader[0]*4) != rheader[0]*4) {
    DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_fill_buffer,4\n"));
    on_valhalla_crashed();
  }

  rnext=0; rlen=rheader[1];
}

void valhalla_readbytes (char* buf, int bytes)
{ int read=0;
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_readbytes\n"));  
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
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_readint\n"));  
  valhalla_readbytes ((char *) &val,sizeof(val));
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_readint: read %d\n",val));  
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
  default:
    fprintf (output,"UNKNOWN OPCODE: %d", opcode); break;
  }
}
#endif

static int valhallaCommunicate (int PC, int SP, struct Object *curObj);

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
#ifdef nti
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
  InstallSigHandler(SIGINT);
#endif

  /* Initialize DOT */

  DOTinit ();

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



/* int valhallaCommunicate (int PC, int SP, Object *curObj)
 * ==========================
 *
 * Serves requests from valhalla regarding the state of this process.
 * PC is needed to serve VOP_SCANSTACK requests.
 *
 * Possible return values:
 *    0: CONTINUE.
 *    1: TERMINATE. */

void forEachStackEntry (int returnAdr, int returnObj)
/* Used by VOP_SCANSTACK */
{
  DEBUG_VALHALLA (fprintf(output,"debuggee: forEachStackEntry \n"));  
  valhalla_writeint (returnAdr);
  valhalla_writeint (returnObj);
  DEBUG_VALHALLA(fprintf(output,"debuggee: forEachStackEntry: returnAdr=%d, returnObj=%d\n",returnAdr,returnObj));
}

extern void Return ();

INLINE Structure *valhalla_AlloS(Object *origin, ProtoType *proto, long *SP, Object *curobj)
{
  Structure *struc;
#ifdef sparc
  extern Structure *CAlloS(Object *origin, int i1, ProtoType *proto);
  BetaStackTop = SP; /* Must be set in case of GC during AlloS */
  struc = CAlloS(origin, 0, proto);
#endif /* sparc */
#ifdef intel
  extern Structure *VAlloS(Object *origin, ProtoType *proto);
  BetaStackTop = SP; /* Must be set in case of GC during AlloS */
  struc = VAlloS(origin, proto);
#endif /* intel */
#ifdef NEWRUN
  extern Structure *AlloS(Object *origin, ProtoType *proto, long *SP);
  BetaStackTop[0] = SP;
  struc = AlloS(origin, proto, SP);
#endif /* NEWRUN*/
#ifdef hppa
  /* Valhalla not yet supported */
  fprintf(output, "valhalla_AlloS: NYI for hppa\n");
  struc = 0;
#endif /* hppa */
  return struc;
} 


INLINE void *valhalla_CopyCPP(Structure *struc, long *SP, Object *curobj)
{
  void *cb = 0;
#ifdef sparc
  extern void *CCopyCPP(ref(Structure) theStruct, ref(Object) theObj);
  BetaStackTop = SP; /* Must be set in case og GC during callback */
  cb = CCopyCPP(struc, curobj);
#endif /* sparc */
#ifdef intel
  /* C implementation of CopyCPP for intel, as implemented
   * in RUN/linuxadditions.run and RUN/ntiadditions.run
   */
  extern void HandleCB(void);
  DEBUG_CODE(NumCopyCPP++);
  if (!struc) return (void *)0 /* NULL function pointer given to C */;
  /* Take the next free entry in the Call Back Functions Area.	*/
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
  extern void *CopyCPP(struct Structure *theStruct);
  BetaStackTop[0] = SP;
  cb = CopyCPP(struc);  
#endif /* NEWRUN */
#ifdef hppa
  fprintf(output, "valhalla_CopyCPP: NYI for hppa\n");
  /* Valhalla not yet supported */
#endif /* hppa */
  return cb;
}

INLINE int findMentry (struct ProtoType *proto)
     /* 
      * Return the Mentry point corresponding to a T entry, or 0, if
      * the corresponding pattern does not have a do-part.
      * 
      */
{ 
  DEBUG_VALHALLA (fprintf(output,"debuggee: findMentry\n"));  
  if (proto && proto->MpartOff){
    return *(long*)((long)proto+proto->MpartOff);
  } else {
    return 0;
  }
}

static int valhallaCommunicate (int PC, int SP, struct Object* curObj)
{ int opcode;
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
      shutdown (sock,2);
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
      struct Object *obj = (struct Object *) valhalla_readint ();
      
      DEBUG_VALHALLA(fprintf(output,"debuggee: Got object %d\n",(int) obj));
      if (obj && inBetaHeap(obj) && isObject(obj)){
	legal=1;
      } else {
	legal=0;
      }
      if (legal) {
	address = (int) obj;
	if ((obj->Proto) != (ComponentPTValue)) {
	  DEBUG_VALHALLA(fprintf(output,"debuggee: Not ComponentPTValue\n"));
	  if (obj->GCAttr == -6) {
	    struct Component *comp = (struct Component *) (address - 24);
	    DEBUG_VALHALLA(fprintf(output,"debuggee: GCAttr was -6\n"));
	    if ((comp->Proto) == (ComponentPTValue))
	      address = address - 24;
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
      struct group_header* header; int tableSize;
      long** protoTable; int i;
      
      header = (struct group_header*) valhalla_readint ();
      protoTable = (long **) header->protoTable;
      
      tableSize= (int) protoTable[0];
      
      for (i=1; i<=tableSize; i++) {
	/* M entry point: */
	valhalla_writeint (findMentry ((struct ProtoType *) protoTable[i]));
	
	valhalla_writeint (protoTable[i][1]); /* G entry point. */
	valhalla_writeint (protoTable[i][4]); /* (formIndex,AstIndex) */
      };
      valhalla_writeint (opcode);
      
      valhalla_socket_flush ();
    }
    break;
    case VOP_SCANSTACK: { 
      struct Component *comp;
      int stacktype;
      
      comp = (struct Component *) valhalla_readint ();
      DEBUG_VALHALLA(fprintf (output,"debuggee: Received component: %d, pt = %d\n",(int)comp, (int) comp->Proto));
      
      DEBUG_VALHALLA(fprintf (output,"debuggee: Scanning ComponentStack.\n"));
      stacktype=scanComponentStack (comp,curObj,PC,forEachStackEntry);
      DEBUG_VALHALLA(fprintf (output,"debuggee: ScanComponentStack done.\n"));
      
      valhalla_writeint (-1);
      valhalla_writeint (stacktype);
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
      struct Object    * origin;
      struct ProtoType * proto;
      struct Structure * struc;
      long   old_valhallaIsStepping;
      void (*cb)(void);
      int origin_handle, curObj_handle;

      DEBUG_STACK(fprintf(output, "VOP_EXECUTEOBJECT: SP=0x%x\n", (int)SP));
      DEBUG_STACK(fprintf(output, "VOP_EXECUTEOBJECT: PC=0x%x\n", (int)PC));

      /* Debuggee is currently stopped in C code.
       * To activate a BETA object in debuggee, we thus have
       * to create a structure object "struc" from
       * "origin" and "proto" and then to create a
       * callback entry using "struc" and then
       * call this callback entry.
       * Before calling the callback entry the C variable
       * BetaStackTop should be set to the value of the
       * stack pointer at the point where debuggee was
       * stopped.
       */
      origin = (struct Object *) valhalla_readint ();
      proto  = (struct ProtoType *) valhalla_readint ();
      
      DEBUG_VALHALLA(fprintf(output, "VOP_EXECUTEOBJECT:\n"));
      DEBUG_VALHALLA(fprintf(output, "Origin Object:\n"));
      DEBUG_VALHALLA(DescribeObject((Object *)origin));
      DEBUG_VALHALLA(fprintf(output, "\n"));
      DEBUG_VALHALLA(fprintf(output, "Prototype: %s\n", ProtoTypeName(proto)));

#ifdef NEWRUN
      /* The SP points to end of current frame. We have to
       * adjust it to point to end of previous frame, as
       * this is expected when callback occurs (see figure
       * "STACK LAYOUT at callback/gpart" in stack.c.
       */
      {
	long SPoff /* size allocated on stack when theObj became active */;
	DEBUG_STACK(fprintf(output, "VOP_EXECUTEOBJECT: Finding previous frame:\n"));
	GetSPoff(SPoff, CodeEntry(curObj->Proto, PC)); 
	DEBUG_STACK({
	  fprintf(output, "File %s; Line %d\n", __FILE__, __LINE__);
	  fprintf(output, "Old SP:      0x%x\n", SP);
	  fprintf(output, "CodeEntry:   0x%x\n", CodeEntry(curObj->Proto, PC));
	  fprintf(output, "SPoff:       0x%x\n", SPoff);
	  fprintf(output, "New SP:      0x%x\n", SP+SPoff);
	});
	SP = (long)SP+SPoff;
      }
#endif /* NEWRUN */

      /* Save origin and curObj in DOT in case of a GC during AlloS */
      origin_handle = DOThandleInsert(origin, DOTgarbageOnDelete, FALSE);
      curObj_handle = DOThandleInsert(curObj, DOTgarbageOnDelete, FALSE);
      /* valhalla_AlloS may cause GC */
      struc = valhalla_AlloS(origin, proto, (long*)SP, curObj);
      origin = DOThandleLookup(origin_handle);
      curObj = DOThandleLookup(curObj_handle);
      DOThandleDelete(origin_handle);
      DOThandleDelete(curObj_handle);
      DEBUG_VALHALLA(fprintf(output, "Struc Object:\n"));
      DEBUG_VALHALLA(DescribeObject((Object *)struc));
      DEBUG_VALHALLA(fprintf(output, "\n"));

      /* Call the constructed callback function */
      cb = (void (*)(void))valhalla_CopyCPP(struc, (long*)SP, curObj);
      DEBUG_VALHALLA(fprintf(output, "Installed callback at 0x%08x\n", (int)cb));

      /* Notice: origin and curObj are now invalid: May have moved.
       * Don't use them below!
       */

      DEBUG_VALHALLA(fprintf(output, "Calling callback function\n"));
      old_valhallaIsStepping = valhallaIsStepping;
      valhallaIsStepping = FALSE;
      exelevel++;
      /* cb() may cause GC */
      cb();
      exelevel--;
      valhallaIsStepping = old_valhallaIsStepping;
      DEBUG_VALHALLA(fprintf(output, "VOP_EXECUTEOBJECT done.\n"));
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
#if defined(sun4s) /* || defined(linux) - only in GNU libs 2 */
      /* Not available for sgi - grrrr... */
      {
	Dl_info info;
	if (dladdr((void*)addr, &info)){
	  sym = info.dli_sname;
	  off = (long)addr - (long)info.dli_saddr;
	}
      }
#else /* !sun4s */
      fprintf(output, "debuggee: VOP_LOOKUP_SYM_OFF: NYI\n");
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
#ifdef UNIX
      addr = (long)dlsym(self, sym);
#else /* !UNIX */
      fprintf(output, "debuggee: VOP_LOOKUP_ADDRESS: NYI\n");
#endif /* UNIX */
      DEBUG_VALHALLA(fprintf(output,"0x%x\n",(int)addr));
      FREE(sym);
      valhalla_writeint (opcode);
      valhalla_writeint (addr);
      valhalla_socket_flush ();
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
 * int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
 *                            long sig, long errorNumber)
 * ====================================================================
 *
 * Calls back to valhalla to inform that this process has stopped and
 * is ready to serve requests. */

int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
			   long sig, long errorNumber)
{ 
  char *txt; int res;
  DEBUG_VALHALLA(fprintf(output,"debuggee: ValhallaOnProcessStop: PC=%d, SP=0x%x, curObj=%d,sig=%d,errorNumber=%d\n",(int) PC, (int) SP, (int) curObj, (int) sig, (int) errorNumber));
  invops++;
  if (invops > exelevel) {
    fprintf (output,"FATAL: ValhallaOnProcessStop re-entered\n");
#ifdef UNIX
    DEBUG_CODE(fprintf(output,"debuggee: sleeping for 10 minuttes...\n"); sleep(10*60));
    DEBUG_CODE(fprintf(output, "debuggee: 10 minuttes past - dying...\n"));
#endif /* UNIX */
    exit(99);
  }

  valhalla_writeint (VOP_STOPPED);
  valhalla_writeint ((int) PC);

  if (PC==0) { /* Process about to stop. */
    valhalla_socket_flush ();
    doshutdown(sock,2);
    closeSocket(sock);
    invops=0;
    return TERMINATE;
  };

  valhalla_writeint ((int) curObj);
  valhalla_writeint ((int) ActiveComponent);
  
  valhalla_writeint ((int) SP);

  valhalla_writeint (sig);

  switch (sig) {
#ifndef nti
  case SIGILL:  txt = "SIGILL"; break;
  case SIGFPE:  txt = "SIGFPE"; break;
  case SIGBUS:  txt = "SIGBUS"; break;
  case SIGSEGV: txt = "SIGSEGV"; break;
  case SIGINT:  txt = "SIGINT"; break;
  case SIGQUIT: txt = "SIGQUIT"; break;
#ifdef linux
  case SIGTRAP: txt = "SIGTRAP"; break;
#else
  case SIGEMT:  txt = "SIGEMT"; break;
#endif
#endif /* nti */
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

  valhalla_socket_flush ();

  if (valhalla_readint () != VOP_STOPPED)
    fprintf (output, "Warning! Wrong answer from Valhalla on VOP_STOPPED\n"); 

  
  switch (res=valhallaCommunicate ((int) PC, (int)SP, curObj)){
  case CONTINUE: break;
  case TERMINATE: exit (99);
  }
  invops--;

  /* If we came here through BetaSignalHandler, signals have been redirected to
   * ExitHandler. Reinstall BetaSignalHandler: */

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
  
  return res;
}

#ifdef hppa
/* Shortcut for calling valhallaOnProcessStop from SnakeAdditions.S 
 * without having to transfer argument 5 via stack in assembler.
 */
void ValhallaOPS(long *PC, long event)
{
  ValhallaOnProcessStop(PC, 0, 0, 0, event);
}
#endif

int connected_to_valhalla ()
{
  DEBUG_VALHALLA(fprintf(output,"debuggee: connected_to_valhalla\n"));
  return (valhallaID!=0);
}
#endif /* RTVALHALLA */


