
/* ------------------------- FILE echoError.h ------------------------- */

/* Error messages by default go to stderr. To redirect, define STDERR */
#ifndef STDERR
#  error "STDERR hasn't been defined"
#  define STDERR stderr
#endif

#if defined(A_SUN4)
   /* Actually - the bad, stupid, pre-ANSI-C, Neanderthal, inconsistent,
    * man-page-disconformant, wicked-minded, misanthropic sun4-headers
    * don't define 'sys_errlist' ANYWHERE, and 'perror' only in X11/Xlibos.h!!
    * Still, it's there when you try to link to it, somehow.
    */
   extern char const * sys_errlist[];
#  define STRERROR(no) sys_errlist[no]
#else
#  define STRERROR(no) strerror(no)
#endif

/* choice of level for tracing output */
extern int asynch_level;
#define ECHO_ERROR_ACTIVE (asynch_level & 0x1)
#define ECHO_ACTION_ACTIVE (asynch_level & 0x2)
#define ECHO_TRANSFER_ACTIVE (asynch_level & 0x4)
#define ECHO_TRANSFERDATA_ACTIVE (asynch_level & 0x8)

#ifdef DO_ECHO_ERROR
#  define ECHO_ERROR(msg)                                               \
     if (ECHO_ERROR_ACTIVE) {                                           \
       fprintf(STDERR,FILE_ID ", " msg ": %s\n",STRERROR(errno));       \
       fflush(STDERR);                                                  \
     }
#  define COND_ECHO_ERROR(test,msg) if (test) ECHO_ERROR(msg)
#  define ECHO_USER_ERROR(msg)                                          \
     if (ECHO_ERROR_ACTIVE) {                                           \
       fprintf(STDERR,FILE_ID ", " msg "\n");                           \
       fflush(STDERR);                                                  \
     }
#  define COND_ECHO_USER_ERROR(test,msg) if (test) ECHO_USER_ERROR(msg)
#else
#  define ECHO_ERROR(msg)
#  define COND_ECHO_ERROR(test,msg)
#  define ECHO_USER_ERROR(msg)
#  define COND_ECHO_USER_ERROR(test,msg)
#endif

#ifdef DO_ECHO_ACTION
#  define ECHO_ACTION(action,fd,somenum) \
     if (ECHO_ACTION_ACTIVE) {                                          \
       printf(FILE_ID ", [fd=%d:%lu] %s, %d\n",fd,GET_TIMESTAMP(fd),    \
	      action,somenum);                                          \
       fflush(stdout);                                                  \
     } 
#else
#  define ECHO_ACTION(action,fd,somenum)
#endif

#ifdef DO_ECHO_TRANSFER

   char *hexList(char *data, int len);

#  define ECHO_TRANSFER(op,fd,data,n1,n2) \
     if (ECHO_TRANSFER_ACTIVE) {                                        \
       printf(FILE_ID ", [fd=%d:%lu] %s(%d/%d)",fd,GET_TIMESTAMP(fd),   \
	      op,n1,n2);                                                \
       if (ECHO_TRANSFERDATA_ACTIVE)                                    \
         printf("%s",hexList(data,n1));                                 \
       printf("\n");                                                    \
       fflush(stdout);                                                  \
     }
#else
#  define ECHO_TRANSFER(op,fd,data,n1,n2)
#endif


/* ------------------------- END echoError.h ------------------------- */
