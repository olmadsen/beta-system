#ifdef RTVALHALLA /* Only relevant in valhalla specific runtime system. */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "valhallaComm.h"
#include "valhallaFindComp.h"
#include "dot.h"
#include <errno.h>
#include <sys/socket.h>

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

#define VOP_STOPPED            50



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
  wheader = (int *) malloc (commbufsize+2*sizeof(int)); wnext = 0;
  rheader = (int *) malloc (commbufsize+2*sizeof(int)); rnext = 0; rlen = 0;
  wbuf = (char *) &wheader[2];
  rbuf = (char *) &rheader[2];
}


void valhalla_init_sockets (int valhallaport)
{
  sock = valhalla_openActiveSocket (valhalla_inetAddrOfThisHost(),valhallaport);
  if (sock==-1) {
    fprintf (output, "valhalla_init_sockets failed. errno=%d\n",errno);
  } else {
    valhalla_create_buffers ();
  }
}

void valhalla_await_connection ()
{ int blocked;
  unsigned long inetAdr;
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
  wheader[0] = (wnext+3)/4; /* len = number of longs of data */
  wheader[1] = wnext; /* header = number of bytes of data. */
  DEBUG_VALHALLA (fprintf(output,"valhalla_socket_flush: len=%d,header=%d\n",wheader[0],wheader[1]));
  if (valhalla_writeDataMax (sock,(char *) wheader, (4*wheader[0])+8) != (4*wheader[0])+8) {
    fprintf (output, "WARNING -- valhalla_socket_flush failed. errno=%d\n",errno);
  }
  DEBUG_VALHALLA (fprintf(output,"valhalla_socket_flush: Done\n"));
  wnext=0;
}

void valhalla_writebytes (char* buf, int bytes)
{ int written = 0;
  
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
  valhalla_writebytes ((char *)&val,sizeof(val));
}

void valhalla_writetext (char* txt)
{ int len = strlen (txt);
  valhalla_writeint (len);
  valhalla_writebytes (txt,len+1);
}

void valhalla_fill_buffer ()
{ 
  DEBUG_VALHALLA (fprintf(output,"valhalla_fill_buffer\n"));
  if (valhalla_readDataMax (sock,(char *) &rheader[0],sizeof(int)) != sizeof(int)) {
    fprintf (output, "valhalla_fill_buffer failed (1) \n");
    exit (99);
  }
  if (valhalla_readDataMax (sock,(char *) &rheader[1],sizeof(int)) != sizeof(int)) {
    fprintf (output, "valhalla_fill_buffer failed (2) \n");
    exit (99);
  }
  if (rheader[0]*4>commbufsize) {
    fprintf (output, "valhalla_fill_buffer failed (3) \n");
    exit (99);
  }
  if (valhalla_readDataMax (sock,rbuf,rheader[0]*4) != rheader[0]*4) {
    fprintf (output, "valhalla_fill_buffer failed (4) \n");
    exit (99);
  }
  rnext=0; rlen=rheader[1];
  DEBUG_VALHALLA (fprintf(output,"valhalla_fill_buffer: Done\n"));
}

void valhalla_readbytes (char* buf, int bytes)
{ int read=0;

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
  valhalla_readbytes ((char *) &val,sizeof(val));
  return val;
}


/* DOTgarbageOnDelete
 * ==================
 * 
 * Dummy function used as parameter to DOT operations demanding a callback
 * function. Deleted indices are not saved explicitly since DOT is scanned
 * each time the process stops to keep valhalla up to date with its part
 * of the DOT contents. */

static void DOTgarbageOnDelete (index)
     int index;
{ ;
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
  default:
    fprintf (output,"UNKNOWN OPCODE"); break;
  }
}
#endif

int valhallaCommunicate (int curPC);

extern char *Argv (int);

void InstallHandler (int sig)
{
#ifndef sun4s
#ifdef UNIX
     signal (sig, BetaSignalHandler);
#endif
#else /* sun4s */
  { struct sigaction sa;
    sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigemptyset(&sa.sa_mask); 
    sa.sa_handler = BetaSignalHandler;
    sigaction(sig,&sa,0);
  }
#endif /* sun4s */
}

/* VALHALLAINIT
 * ============
 * 
 * Called when connection to valhalla should be setup. If valhalla is already
 * running, valhallaID is expected to contain the PID of the valhalla process 
 * is textual form. */

void valhallaInit ()
{ 
  if (valhallaID) {
    int valhallaPORT;

    /* Valhalla is already running. */
    valhallaPORT = atoi (valhallaID);
    DEBUG_VALHALLA (fprintf (output,"valhalla port = %d\n",valhallaPORT));
    valhalla_init_sockets (valhallaPORT);

  } else {
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
      
    } else {
      char valhallaname[200];
      char tmppid[20], tmpport[20];
      char* betalib;
      
      betalib = getenv ("BETALIB");
      if (!betalib) {
	betalib="/users/beta";
	DEBUG_VALHALLA(fprintf(output,"BETALIB not found\n"));
      }
      /*sprintf (valhallaname,"%s/%s",betalib,"bin/valhalla2.0");*/
      sprintf (valhallaname,"%s/%s",betalib,"debugger/v2.0/valhalla");
      sprintf (tmppid,"%d",pid);
      sprintf (tmpport,"%d",(int) port);
      
      execl (valhallaname,valhallaname,"-PORT",tmpport,"-PID",tmppid,"-EXECNAME",Argv(1),(char *) 0);
      fprintf (output, "Could not exec\n");
      _exit (99);
    }
  }

  /* Make BetaSignalHandler handle the SIGINT signal.
   * Since SIGINT is not handled specially by the runtime system,
   * it will be sent to DisplayBetaStack, and from there to
   * valhallaOnProcessStop that will recognize it as a breakpoint hit. */
  
  InstallHandler(SIGINT);

  /* Initialize DOT */

  DOTinit ();

  /* Do initial communication with valhalla. ValhallaCommunicate returns
   * what to do next. */

  { int todo;
    switch (todo=valhallaCommunicate (0)) {
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
  valhalla_writeint (returnAdr);
  valhalla_writeint (returnObj);
  DEBUG_VALHALLA(fprintf(output,"forEachStackEntry: returnAdr=%d, returnObj=%d\n",returnAdr,returnObj));

}

extern void Return ();
static inline int findMentry (struct ProtoType *proto)
     /* 
      * Used to locate the Mentry point corresponding to a T entry. This is
      * done by scanning backwards in the INNER table of the prototype until
      * the address of Return is seen. The previous address seen is then the 
      * Mentry.
      *
      * However, if a prototype does not have an M entry point of its own
      * (no dopart), this method may return the Mentry point of one of its
      * prefixes. To ensure that this does not happen, the INNER table of
      * the immediate prefix prototype is scanned to ensure that the Mentry
      * found is not in that table too. If it is anyway, the current prototype 
      * has no Mentry of its own, and an Mentry of 0 is used. */
{ long tmp,Mentry=0;
  long* INNERtab = ((long *) proto)-1;
  struct ProtoType *prefix;
  
  while (TRUE) {
    tmp = *(INNERtab--);
    if (tmp==(long)Return) break;
    Mentry=tmp;
  }
  if (!Mentry) return 0; /* Empty INNER table. */
  
  /* Now check that the Mentry found cannot be found in the
   * prefix INNER table. */
  
  prefix = proto->Prefix;
  
  if ((prefix) && (prefix!=proto)) {
    INNERtab = ((long *) prefix)-1;
    while (TRUE) {
      tmp = *(INNERtab--);
      if (tmp==(long)Return) break;
      if (tmp==Mentry) return 0;
    }
  }
  
  return Mentry;
}

int valhallaCommunicate (int curPC)
{ int opcode;

  while (TRUE) {
    opcode = valhalla_readint ();
    
    DEBUG_VALHALLA(fprintf (output, "valhallaCommunicate: opcode is "));
    DEBUG_VALHALLA(printOpCode(opcode); fprintf (output,"\n"));

    switch (opcode) {

    case VOP_SCANGROUPS:
      
      { group_header *current = 0;

	valhalla_writeint (opcode);
	while ((current = NextGroup (current))) {
	  valhalla_writetext (NameOfGroup(current));     /* groupName */
	  valhalla_writeint ((int) current->self);       /* dataStart */ 
	  valhalla_writeint ((int) current->next);       /* dataEnd   */
	  valhalla_writeint ((int) current->code_start); /* codeStart */
	  valhalla_writeint ((int) current->code_end);   /* codeEnd   */
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
    case VOP_GETINSTRUCTIONMEM:
      { 
	int address = valhalla_readint ();
	int bytelen = valhalla_readint ();
	DEBUG_VALHALLA(fprintf (output, "VOP_GET*MEM: %d bytes from address 0x%x\n",bytelen, address));
	   
	valhalla_writeint (opcode);
	valhalla_writebytes ((char *) address, bytelen);
	valhalla_socket_flush ();
      }
      break;

    case VOP_SETDATAMEM:
      {
	int address = valhalla_readint ();
	int bytelen = valhalla_readint ();
	valhalla_readbytes((char *) address, bytelen);
	valhalla_writeint (opcode);
	valhalla_socket_flush ();
      }
      break;

    case VOP_GETDATAWORDS:
      { 
	int address;
	
	valhalla_writeint (opcode);
	while ((address = valhalla_readint ()))
	  valhalla_writeint ((* (int *) address));
	valhalla_socket_flush ();
      }
      break;

    case VOP_OBJADRCANONIFY:
      { int address;
	struct Object *obj = (struct Object *) valhalla_readint ();

	DEBUG_VALHALLA(fprintf(output,"Got object %d\n",(int) obj));
	
	if (obj) {
	  address = (int) obj;
	  if (obj->Proto != ComponentPTValue) {
	    DEBUG_VALHALLA(fprintf(output,"Not ComponentPTValue\n"));
	    if (obj->GCAttr == -6) {
	      struct Component *comp = (struct Component *) (address - 24);
	      DEBUG_VALHALLA(fprintf(output,"GCAttr was -6\n"));
	      if (comp->Proto == ComponentPTValue)
		address = address - 24;
	    }
	  }
	} else {
	  address=0;
	}
	valhalla_writeint (opcode);
	valhalla_writeint (address);
	valhalla_socket_flush ();
      }
      break;

    case VOP_DOTINSERT:
      { int address, index;

	address = valhalla_readint ();
	index = DOThandleInsert (address, DOTgarbageOnDelete, FALSE);

	valhalla_writeint (opcode);
	valhalla_writeint (index);
	valhalla_writeint (ObjectSize((ref(Object)) address));
	valhalla_socket_flush ();
      }
      break;

    case VOP_DOTDELETE:
      {
	int handle = valhalla_readint ();
	DOThandleDelete (handle);
	valhalla_writeint (opcode);
	valhalla_socket_flush ();
      }
      break;

    case VOP_GETPROTOINFO:
      {
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

    case VOP_SCANSTACK:
      { struct ComponentStack cs;

	cs.comp = (struct Component *) valhalla_readint ();

	DEBUG_VALHALLA(fprintf (output,"Received component: %d, pt = %d\n",(int)cs.comp, (int) cs.comp->Proto));

	findComponentStack (&cs,curPC);

	DEBUG_VALHALLA(fprintf (output,"FindComponentStack done. stacktype = %d. \n",cs.stacktype));
	  
	valhalla_writeint (cs.stacktype);
	
	DEBUG_VALHALLA(fprintf (output,"Scanning ComponentStack.\n"));
	
	scanComponentStack (&cs,forEachStackEntry);
	
	DEBUG_VALHALLA(fprintf (output,"ScanComponentStack done.\n"));
	
	valhalla_writeint (-1);
	valhalla_writeint (opcode);
	valhalla_socket_flush ();
      }
      break;
      
    default:
      
      fprintf (output, "Unexpected valhalla opcode: %d\n", opcode);
      break;
      
    }

    DEBUG_VALHALLA(fprintf (output, "valhallaCommunicate: opcode "));
    DEBUG_VALHALLA(printOpCode(opcode); fprintf (output," done\n"));

  }
}


/* forEachAlive
 * ============
 *
 * Callback function used by ValhallaOnProcessStop during DOTscan. */

void forEachAlive (int handle, int address, DOTonDelete onDelete)
{
  DEBUG_VALHALLA(fprintf (output,"forEachAlive: handle=%d, address=%d \n", handle, address));
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
{ char *txt; int res;

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
  case SIGILL:  txt = "SIGILL"; break;
  case SIGFPE:  txt = "SIGFPE"; break;
  case SIGBUS:  txt = "SIGBUS"; break;
  case SIGSEGV: txt = "SIGSEGV"; break;
  case SIGINT:  txt = "SIGINT"; break;
  case SIGQUIT: txt = "SIGQUIT"; break;
#ifndef linux
  case SIGEMT:  txt = "SIGEMT"; break;
#endif
  default: txt = "UNKNOWN"; break;
  }
  valhalla_writetext (txt);

  DEBUG_VALHALLA(fprintf(output,"ValhallaOnProcessStop: PC=%d, SP=0x%x, StackEnd=0x%x, curObj=%d,sig=%d,errorNumber=%d,errorText=%s\n",(int) PC, (int) SP, (int) StackEnd, (int) curObj, (int) sig, (int) errorNumber, txt));
			 
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

  
  switch (res=valhallaCommunicate ((int) PC)){
  case CONTINUE: break;
  case TERMINATE: exit (99);
  }
  invops=FALSE;

  /* If we came here through BetaSignalHandler, signals have been redirected to
   * ExitHandler. Reinstall BetaSignalHandler: */

  InstallHandler(SIGFPE);
  InstallHandler(SIGILL);
  InstallHandler(SIGBUS);
  InstallHandler(SIGSEGV);
#ifndef linux
  InstallHandler(SIGEMT);
#endif
  InstallHandler(SIGINT);

  
  return res;
}

int connected_to_valhalla ()
{
  return (valhallaID!=0);
}
#endif RTVALHALLA
