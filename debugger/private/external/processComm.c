/* common declarations for all platforms */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITONEXCEPTION

static char **envp;
static char **argv;
static int envc,argc;  
extern char **environ;

typedef void (*forEachEnv) (char*,char*);

void process_comm_exception(char *message) {
  fprintf(stderr,"**** CException processing\n%s",message);
#ifdef EXITONEXCEPTION
  exit(1);
#endif
}

void extScanEnv (forEachEnv forEach) { 

#define MAXNAMELENGTH 100
#define MAXVALUELENGTH 1000
  
  char name[MAXNAMELENGTH], value[MAXVALUELENGTH], ch;
  int i,j;
  
  i=0;
  while (environ[i]) {
    j=0;
    while ((name[j]=environ[i][j])!='=') 
      if (j++>=MAXNAMELENGTH) 
	process_comm_exception("MAXNAMELENGTH exceeded\n");
    name[j]=0;
    if (strlen(&(environ[i][j])+1)<MAXVALUELENGTH)
      strcpy (value,&(environ[i][j])+1);
    else
      process_comm_exception("MAXVALUELENGTH exceeded\n");
    forEach (name,value);
    i++;
  }
}   

void initParamsAndEnv (int numParam, int numEnv) {
  if ((envp = (char **) malloc ((numEnv+2)*sizeof(char*)))==NULL) 
    process_comm_exception("Couldn't allocate memory for envp");
  if ((argv = (char **) malloc ((numParam+2)*sizeof(char*)))==NULL) 
    process_comm_exception("Couldn't allocate memory for argv");
  envc=0;
  argc=1;
}

void addEnv (char *name, char* value) { 

#define TMPLENGTH 1000

  char tmp[TMPLENGTH];
  
  if (strlen(name)+strlen(value)+2>=TMPLENGTH) 
    process_comm_exception("TMPLENGTH exceeded\n");
  sprintf (tmp,"%s=%s",name,value);
  envp[envc++] = (char *) strdup (tmp);
}

void addParam (char *name) {
  argv[argc++] = (char *) strdup (name);
}


/* platform-specifics */

#if defined(sun4s) || defined(sgi) || defined(sun4) || defined(linux)

#include <unistd.h>

extern char *machine_type(void); /* in betarun */

char *valhallaMachineName()
{
  return machine_name();
}

int executeProcess (char *execName)
{ int pid;
  int i;

  if (pid = fork ()) {

    /* Free argument and environment strings */
    for (i=1;i<argc;i++) free (argv[i]);
    for (i=0;i<envc;i++) free (envp[i]);
    free (argv); free (envp);

  } else {
    
    argv[0] = execName; argv[argc] = 0; envp[envc] = 0;
    execve (execName,argv,envp);
    _exit (99); /* Call _exit instead of exit if an execve after a fork
                 * fails. See why in man(2) vfork. */
    
  }
  
  return pid;
}

#endif /* not sun4 or sun4s or linux or sgi */

#if defined(nti)

#include <windows.h>

extern char *machine_type(void); /* in betarun */

char *valhallaMachineName() {
  printf("valhallaMachineName not implemented\n");
  exit(1);
}

int executeProcess (char *execName) { 
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  
  /* arguments */

  /* pointer to name of executable module.
   * Pointer to a null-terminated string that specifies the module to execute.
   * The string can specify the full path and filename of the module 
   * to execute. 
   * The string can specify a partial name. In that case, the function 
   * uses the current drive and current directory to complete 
   * the specification. 
   * The lpApplicationName parameter can be NULL. In that case, 
   * the module name must be the first white space-delimited token 
   * in the lpCommandLine string. 

   * Windows NT: If the executable module is a 16-bit application, 
   * lpApplicationName should be NULL, and the string pointed to 
   * by lpCommandLine should specify the executable module. 
   * A 16-bit application is one that executes as a VDM or WOW process.  
   *
   * Below it will be NULL, and the execName will be given as the first 
   * white space-delimited token in the lpCommandLine string. 
   * 
   */
  LPCTSTR lpApplicationName=NULL;	

  /* pointer to command line string 
   * Pointer to a null-terminated string that specifies the command line 
   * to execute. 
   */
  LPTSTR lpCommandLine;	

  /* pointer to process security attributes
   * Windows NT: The lpSecurityDescriptor member of the structure specifies 
   * a security descriptor for the new process. If lpProcessAttributes 
   * is NULL, the process gets a default security descriptor. 
   * Windows 95: The lpSecurityDescriptor member of the structure is ignored.
   */
  LPSECURITY_ATTRIBUTES lpProcessAttributes=NULL;	

  /* pointer to thread security attributes 
   * Windows NT: The lpSecurityDescriptor member of the structure specifies 
   * a security descriptor for the main thread. If lpThreadAttributes 
   * is NULL, the thread gets a default security descriptor. 
   * Windows 95: The lpSecurityDescriptor member of the structure is ignored.
   */
  LPSECURITY_ATTRIBUTES lpThreadAttributes=NULL;	

  /* handle inheritance flag 
   * Indicates whether the new process inherits handles from the calling 
   * process. If TRUE, each inheritable open handle in the calling 
   * process is inherited by the new process. Inherited handles have
   * the same value and access privileges as the original handles. 
   */
  BOOL bInheritHandles=TRUE;	

  /* creation flags */
  DWORD dwCreationFlags=0;

  /* pointer to new environment block 
   * Points to an environment block for the new process. If this 
   * parameter is NULL, the new process uses the environment of the 
   * calling process. 
   * An environment block consists of a null-terminated block of 
   * null-terminated strings. Each string is in the form: 
   *
   * name=value 
   *
   * Note that an ANSI environment block is terminated by two zero bytes: 
   * one for the last string, one more to terminate the block.
   */
  LPVOID lpEnvironment;	

  /* pointer to current directory name 
   * Points to a null-terminated string that specifies the current drive and 
   * directory for the child process. The string must be a full path and 
   * filename that includes a drive letter. If this parameter is NULL, 
   * the new process is created with the same current drive and directory
   * as the calling process.
   */
  LPCTSTR lpCurrentDirectory=NULL;	

  /* pointer to STARTUPINFO */
  LPSTARTUPINFO lpStartupInfo;	

  /* pointer to PROCESS_INFORMATION */
  LPPROCESS_INFORMATION lpProcessInformation; 	

  /* set arguments */

  /* startup info */
  
  /* cb
   * Specifies the size, in bytes, of the structure. 
   */
  si.cb=sizeof(STARTUPINFO); 

  /* lpReserved
   * Reserved. Set this member to NULL before passing the structure 
   * to CreateProcess. 
   */
  si.lpReserved=NULL;

  /* lpDesktop
   * Windows NT only: Points to a zero-terminated string that specifies 
   * either the name of the desktop only or the name of both the desktop 
   * and window station for this process. A backslash in the string pointed 
   * to by lpDesktop indicates that the string includes both desktop and 
   * window station names. If lpDesktop is NULL, the new process inherits 
   * the desktop and window station of its parent process. If lpDesktop
   * is an empty string, the process does not inherit the desktop and
   * window station of its parent process; instead, the system determines 
   * if a new desktop and window station need to be created. 
   */
  si.lpDesktop=NULL;

  /* lpTitle
   * For console processes, this is the title displayed in the title bar 
   * if a new console window is created. If NULL, the name of the 
   * executable file is used as the window title instead. This parameter 
   * must be NULL for GUI or console processes that do not create a 
   * new console window. 
   */
  si.lpTitle="Debugee";
  
  /* dwX, dwY
   * Ignored unless dwFlags specifies STARTF_USEPOSITION. Specifies the x 
   * and y offsets, in pixels, of the upper left corner of a window if a 
   * new window is created. The offsets are from the upper left corner 
   * of the screen. For GUI processes, the specified position is used 
   * the first time the new process calls CreateWindow to create an 
   * overlapped window if the x parameter of CreateWindow is CW_USEDEFAULT.
   */
  si.dwX=0;
  si.dwY=0;

  /* dwXSize, dwYSize
   * Ignored unless dwFlags specifies STARTF_USESIZE. Specifies the 
   * width (dwXSize) and height (dwYSize), in pixels, of the window if 
   * a new window is created. For GUI processes, this is used only the
   * first time the new process calls CreateWindow to create an 
   * overlapped window if the nWidth parameter of CreateWindow 
   * is CW_USEDEFAULT. 
   */
  si.dwXSize=0;
  si.dwYSize=0;

  /* dwXCountChars, dwYCountChars
   * Ignored unless dwFlags specifies STARTF_USECOUNTCHARS.
   * For console processes, if a new console window is created, 
   * dwXCountChars specifies the screen buffer width in character 
   * columns, and dwYCountChars specifies the screen buffer height 
   * in character rows. These values are ignored in GUI processes. 
   */
  si.dwXCountChars=0;
  si.dwYCountChars=0;

  /* dwFillAttribute
   * Ignored unless dwFlags specifies STARTF_USEFILLATTRIBUTE. Specifies 
   * the initial text and background colors if a new console window 
   * is created in a console application. These values are ignored in 
   * GUI applications. 
   */
  si.dwFillAttribute=0;

  /* dwFlags
   * This is a bit field that determines whether certain STARTUPINFO members 
   * are used when the process creates a window.
   */
  si.dwFlags= STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  
  /* wShowWindow
   * Ignored unless dwFlags specifies STARTF_USESHOWWINDOW. The wshowWindow 
   * member can be any of the SW_ constants defined in WINUSER.H. For GUI 
   * processes, wShowWindow specifies the default value the first time 
   * ShowWindow is called. The nCmdShow parameter of ShowWindow is ignored. 
   * In subsequent calls to ShowWindow, the wShowWindow member is 
   * used if the nCmdShow parameter of ShowWindow is set to SW_SHOWDEFAULT.  
   */
  si.wShowWindow = SW_SHOWDEFAULT;

  /* cbReserved2
   * Reserved; must be zero. 
   */
  si.cbReserved2=0;

  /* lpReserved2
   * Reserved; must be NULL. 
   */
  si.lpReserved2=NULL;

  /* hStdInput
   * Ignored unless dwFlags specifies STARTF_USESTDHANDLES. Specifies a 
   * handle that will be used as the standard input handle of the 
   * process if STARTF_USESTDHANDLES is specified. 
   */
  si.hStdInput=0;
  
  /* hStdOutput
   * Ignored unless dwFlags specifies STARTF_USESTDHANDLES. Specifies a 
   * handle that will be used as the standard output handle of the 
   * process if STARTF_USESTDHANDLES is specified. 
   */
  si.hStdOutput=0;

  /* hStdError
   * Ignored unless dwFlags specifies STARTF_USESTDHANDLES. Specifies a 
   * handle that will be used as the standard error handle of the process 
   * if STARTF_USESTDHANDLES is specified. 
   */
  si.hStdError=0;
  
  lpStartupInfo = &si;
  lpProcessInformation = &pi;

  /* set lpCommandLine */
  { 
    int size_of_cmdline=0;
    int cmdline_pointer=0;
    int count;
    
    argv[0] = execName; argv[argc] = 0;
    
    for(count=0;count<argc;count++) {
      /* add 1 to include separating white space (or null-terminator) */ 
      size_of_cmdline+=strlen(argv[count])+1;
    }
    
    lpCommandLine = (char *)malloc(sizeof(char)*(size_of_cmdline));

    for(count=0;count<argc-1;count++) {
      sprintf((char *)lpCommandLine + cmdline_pointer,"%s ",argv[count]);
      cmdline_pointer+=strlen(argv[count])+1;
    }
    
    sprintf((char *)lpCommandLine + cmdline_pointer,"%s",argv[count]);
  }

  /* set lpEnvironment */
  {
    int size_of_envblock=0;
    int envblock_pointer=0;
    int count;
    
    envp[envc] = 0;
    
    for(count=0;count<envc;count++) {
      /* add 1 to include null-terminator */ 
      size_of_envblock+=strlen(envp[count])+1;
    }
    
    /* add 1 to include null-terminator */ 
    size_of_envblock+=+1;

    lpEnvironment = (char *)malloc(sizeof(char)*(size_of_envblock));

    for(count=0;count<envc;count++) {
      sprintf((char *)lpEnvironment + envblock_pointer,"%s",envp[count]);
      envblock_pointer+=strlen(envp[count])+1;
    }
    *((char *)lpEnvironment + envblock_pointer) = '\0';
  }
  
  /* start process */
  if (CreateProcess(lpApplicationName,
		    lpCommandLine,
		    lpProcessAttributes,
		    lpThreadAttributes,
		    bInheritHandles,
		    dwCreationFlags,
		    lpEnvironment,
		    lpCurrentDirectory,
		    lpStartupInfo,
		    lpProcessInformation)) {
    /* Call succeeded */
    return (int)(lpProcessInformation -> dwProcessId);
  } else {
    /* Call failed */
    LPVOID lpMsgBuf;
    FormatMessage
      (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
       NULL,
       GetLastError(),
       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
       (LPTSTR) &lpMsgBuf,
       0,
       NULL);
     process_comm_exception((char *)lpMsgBuf);
  }
}

#endif /* not nti */












