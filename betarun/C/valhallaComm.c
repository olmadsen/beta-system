#include "beta.h"

#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */

#include <stdio.h>
#include <errno.h>
#include "valhallaComm.h"
#include "valhallaFindComp.h"
#include "dot.h"

#ifdef nti 
#ifdef nti_gnu
#  include <Windows32/Sockets.h> 
#  include <limits.h>
#endif /* nti_gnu */

#else /* not nti */
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#endif /* nti */

/* Opcodes for communication between valhalla and debugged process.
 *
 * VOP_* constants are replicated in
 *
 *    ~debugger/processCommCodes.bet
 * 
 * A protocol description including parameters and return value is
 * found in processCommCodes.bet as well.
 */

#define VOP_SCANGROUPS          1 
#define VOP_KILL                2 
#define VOP_GETDATAMEM          3 
#define VOP_GETINSTRUCTIONMEM   4 
#define VOP_SETDATAMEM          5 
#define VOP_GETDATAWORDS        6 
#define VOP_CONTINUE            7
#define VOP_DOTINSERT           9
#define VOP_GETPROTOINFO       10
#define VOP_DOTDELETE          11
#define VOP_SCANSTACK          12
#define VOP_OBJADRCANONIFY     13
#define VOP_BETARUN            14
#define VOP_DATASTART          15

#define VOP_STOPPED            50

#ifdef DEBUG_VALHALLA
#undef DEBUG_VALHALLA
#define DEBUG_VALHALLA(code) if (0) { code; }
#endif

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
  DEBUG_VALHALLA(fprintf(stdout,"debuggee: valhallaport=%d\n", valhallaport));
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
  wheader[0] = ntohl((wnext+3)/4); /* len = number of longs of data */
  wheader[1] = ntohl(wnext); /* header = number of bytes of data. */
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_socket_flush: len=%d,header=%d\n",(int)htonl(wheader[0]),(int)htonl(wheader[1])));
  if (valhalla_writeDataMax (sock,(char *) wheader, (4*htonl(wheader[0]))+8) != (int)(4*htonl(wheader[0]))+8) {
    fprintf (output, "WARNING -- valhalla_socket_flush failed. errno=%d\n",errno);
  }
  wnext=0;
}

void valhalla_writebytes (char* buf, int bytes)
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

void valhalla_writetext (char* txt)
{ 
  int len = strlen (txt);
  DEBUG_VALHALLA (fprintf(output,"debuggee: valhalla_writetext\n"));  
  valhalla_writeint (len);
  valhalla_writebytes (txt,len+1);
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

static void DOTgarbageOnDelete (int index)
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
  default:
    fprintf (output,"UNKNOWN OPCODE"); break;
  }
}
#endif

static int valhallaCommunicate (int curPC, struct Object *curObj);

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
    switch (todo=valhallaCommunicate (0,0)) {
    case CONTINUE: break;
    case TERMINATE: exit (99);
    default:
      fprintf (output, "Unexpected return from valhallaCommunicate: %d \n",
	       todo);
      exit (99);
    }
  }
} /* End ValhallaInit */



/* int valhallaCommunicate (int curPC)
 * ==========================
 *
 * Serves requests from valhalla regarding the state of this process.
 * curPC is needed to serve VOP_SCANSTACK requests.
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

static int valhallaCommunicate (int curPC, struct Object* curObj)
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
      int address, index;
      
      address = valhalla_readint ();
      index = DOThandleInsert (address, DOTgarbageOnDelete, FALSE);
      
      valhalla_writeint (opcode);
      valhalla_writeint (index);
      valhalla_writeint (ObjectSize((ref(Object)) address));
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
      stacktype=scanComponentStack (comp,curObj,curPC,forEachStackEntry);
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
    case VOP_DATASTART: {
      long code_start;
      code_start = (long)((struct group_header*)BETA_DATA1_ADDR)->code_start;

      valhalla_writeint (opcode);
      valhalla_writeint (code_start);
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

void forEachAlive (int handle, int address, DOTonDelete onDelete)
{
  DEBUG_VALHALLA(fprintf (output,"debuggee: forEachAlive: handle=%d, address=%d \n", handle, address));
  if (onDelete==DOTgarbageOnDelete) {
    valhalla_writeint (handle);
    valhalla_writeint (address);
  }
}



/* 
 * int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
 *                            long sig, long errorNumber)
 * ====================================================================
 *
 * Calls back to valhalla to inform that this process has stopped and
 * is ready to serve requests. */

static int invops = 0; /* TRUE iff ValhallaOnProcessStop is active. Used to check
			* for reentrance of ValhallaOnProcessStop. This could happen
			* in case of bus-errors or the like during communication with
			* valhalla . */


int ValhallaOnProcessStop (long*  PC, long* SP, ref(Object) curObj, 
			   long sig, long errorNumber)
{ 
  char *txt; int res;
  DEBUG_VALHALLA(fprintf(output,"debuggee: ValhallaOnProcessStop: PC=%d, SP=0x%x, curObj=%d,sig=%d,errorNumber=%d\n",(int) PC, (int) SP, (int) curObj, (int) sig, (int) errorNumber));

  if (invops) {
  fprintf (output,"FATAL: ValhallaOnProcessStop re-entered\n");
  exit (99);
  } else
    invops=TRUE;

  valhalla_writeint (VOP_STOPPED);
  valhalla_writeint ((int) PC);

  if (PC==0) { /* Process about to stop. */
    valhalla_socket_flush ();
    invops=FALSE;
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

  
  switch (res=valhallaCommunicate ((int) PC, curObj)){
  case CONTINUE: break;
  case TERMINATE: exit (99);
  }
  invops=FALSE;

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


