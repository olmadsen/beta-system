#ifndef _C_RTSIGHANDLER_H_
#define _C_RTSIGHANDLER_H_

#if defined(UNIX)
#include <signal.h>
#endif /* UNIX  */

#ifdef ppcmac
#include <MachineExceptions.h>
#endif /* ppcmac */

#if defined(sun4s) || defined(x86sol)
#include <siginfo.h>
#include <sys/regset.h>
#include <sys/ucontext.h>
#endif

#ifdef macosx
#include <sys/ucontext.h>
#endif

#ifdef linux
#include <asm/sigcontext.h> 
#endif

#ifdef nti
#include <float.h>
#ifdef nti_gnu
#include "old-excpt.h"
#define OUR_EXCEPTION_CONTINUE_SEARCH ExceptionContinueSearch
#define OUR_EXCEPTION_CONTINUE_EXECUTION ExceptionContinueExecution
#else /* !nti_gnu */
#define OUR_EXCEPTION_CONTINUE_SEARCH EXCEPTION_CONTINUE_SEARCH
#define OUR_EXCEPTION_CONTINUE_EXECUTION EXCEPTION_CONTINUE_EXECUTION
#endif /* nti_gnu */
#endif /* nti */

#ifdef linux
#define SIGNAL_CONTEXT struct sigcontext_struct *
#endif /* linux */

#ifdef nti
#define SIGNAL_CONTEXT CONTEXT *
#endif /* nti */

#ifdef sgi
#define SIGNAL_CONTEXT struct sigcontext *
#endif
#ifdef sparc
#define SIGNAL_CONTEXT ucontext_t *
#endif
#ifdef x86sol
#define SIGNAL_CONTEXT ucontext_t *
#endif
#ifdef ppcmac
#define SIGNAL_CONTEXT ExceptionInformation *
#endif
#ifdef macosx
#define SIGNAL_CONTEXT ucontext_t *
#endif
#ifdef hppa
#define SIGNAL_CONTEXT struct sigcontext *
#endif

extern void set_BetaStackTop(long *sp);

#ifdef intel
typedef struct register_handles {
  int edx;
  int edi;
  int ebp;
  int esi;
} register_handles;

#ifdef linux
void SaveLinuxRegisters(SIGNAL_CONTEXT scp, register_handles *handles);
#define BeforeBetaCallback()
#define AfterBetaCallback()
#endif /* linux */

#ifdef x86sol
void SaveX86SolRegisters(SIGNAL_CONTEXT scp, register_handles *handles);
#define BeforeBetaCallback()
#define AfterBetaCallback()
#endif /* linux */

#ifdef nti
void SaveWin32Registers(SIGNAL_CONTEXT scp, register_handles *handles);
#define BeforeBetaCallback()
#define AfterBetaCallback()
#endif /* nti */
#endif /* intel */

#ifdef sgi
typedef struct register_handles {
  int s0;
  int s1;
  int s2;
  int s8;
  int a1;
} register_handles;

void SaveSGIRegisters(SIGNAL_CONTEXT scp, register_handles *handles);
void RestoreSGIRegisters(SIGNAL_CONTEXT scp, register_handles *handles);
#define BetaCallback(ctx, sp, func) \
{ \
  register_handles handles = {-1, -1, -1, -1, -1}; \
  set_BetaStackTop((long *)sp); \
  /* User code must call fix_stacks manually */ \
  SaveSGIRegisters(ctx, &handles); \
  func; \
  RestoreSGIRegisters(ctx, &handles); \
}
#endif /* sgi */

#ifdef sparc
#define BetaCallback(ctx, sp, func) \
set_BetaStackTop((long *)sp); \
func; \
ctx->uc_mcontext.gregs[REG_IOA] = (long)IOA; \
ctx->uc_mcontext.gregs[REG_IOATOPOFF] = (long)IOATopOff
#endif /* sparc */

#ifdef ppcmac
#define BeforeBetaCallback() \
fprintf(output, \
	"BeforeBetaCallback: BetaCallback not implemented on Mac" \
	" (look in sighandler.c)\n"); 
#define AfterBetaCallback() \
fprintf(output, \
	"AfterBetaCallback: BetaCallback not implemented on Mac" \
	" (look in sighandler.c)\n"); 
#endif /* ppcmac */

/* Definition of BetaSignalHandler */

#ifdef linux
void BetaSignalHandler(long sig, struct sigcontext_struct scp);
void BoundSignalHandler(long sig, struct sigcontext_struct *scp);
#endif /* linux */

#ifdef sgi
void BetaSignalHandler(long sig, long code, SIGNAL_CONTEXT scp, char *addr);
#endif /* sgi */

#if defined(sun4s) || defined(x86sol)
void BetaSignalHandler(long sig, siginfo_t *info, SIGNAL_CONTEXT ucon);
#endif /* sun4s||x86sol */

#if defined(macosx)
void BetaSignalHandler(int sig, ucontext_t *scp);
#endif /* macosx*/

#ifdef nti
#ifdef nti_gnu
EXCEPTION_DISPOSITION 
BetaSignalHandler_GNU(EXCEPTION_RECORD* pExceptionRec,
		      void* pEstablisherFrame,
		      SIGNAL_CONTEXT pContextRecord,
		      void* pDispatcherContext);
EXCEPTION_DISPOSITION 
BoundSignalHandler_GNU(EXCEPTION_RECORD* pExceptionRec,
		      void* pEstablisherFrame,
		      SIGNAL_CONTEXT pContextRecord,
		      void* pDispatcherContext);
#else  /* !nti_gnu */
int BetaSignalHandler(LPEXCEPTION_POINTERS lpEP);
int BoundSignalHandler(LPEXCEPTION_POINTERS lpEP);
#endif /* !nti_gnu */
#endif /* nti */

#endif /* _C_RTSIGHANDLER_H_ */
