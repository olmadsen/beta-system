#include <stdio.h>
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int create_pipe(const char *cmd,
		FILE **cmdpipe, FILE **readpipe,
		int *wfd) {
  int filedes[2];
  int oldstdout,oldstderr;

  /* Create a pipe for output from cmd */
  if (pipe(filedes) == -1) return -2;

  /* Create a filepointer which corresponds to output from cmd */
  if ((*readpipe = fdopen(filedes[0],"r")) == NULL) return -3;

  *wfd = filedes[1];

  /* Save stdout and stderr */
  if ((oldstdout = dup(STDOUT_FILENO)) == -1) {
    close(filedes[0]);
    close(filedes[1]);
    return -4;
  }
  if ((oldstderr = dup(STDERR_FILENO)) == -1) {
    close(filedes[0]);
    close(filedes[1]);
    return -5;
  }

  /* Capture output from cmd */
  if (dup2(filedes[1],STDOUT_FILENO) == -1) {
    close(filedes[0]);
    close(filedes[1]);
    return -6;
  }
  if (dup2(filedes[1],STDERR_FILENO) == -1) {
    dup2(oldstdout,STDOUT_FILENO);
    close(filedes[0]);
    close(filedes[1]);
    return -7;
  }

  /* Open the pipe to cmd */
  if ((*cmdpipe = popen(cmd,"w")) == NULL) {
    dup2(oldstdout,STDOUT_FILENO);
    dup2(oldstderr,STDERR_FILENO);
    close(filedes[0]);
    close(filedes[1]);
    return -8;
  }

  /* Restore stdout and stderr */
  if (dup2(oldstdout,STDOUT_FILENO) == -1) {
    pclose(*cmdpipe);
    dup2(oldstderr,STDERR_FILENO);
    close(filedes[0]);
    close(filedes[1]);
    return -9;
  }

  if (dup2(oldstderr,STDERR_FILENO) == -1) {
    pclose(*cmdpipe);
    close(filedes[0]);
    close(filedes[1]);
    return -10;
  }

  return 0;
}

char *close_pipe(FILE *cmdpipe, FILE *readpipe, int wfd) {
  char *buf = (char*) malloc(1000,sizeof(char));
  char format[100];
  int cmdstat;
  int error = 0;

  /* close cmd and the pipe from its output */
  cmdstat = pclose(cmdpipe);
  fprintf(stdout,"%s",buf);
  if (close(wfd) == -1) {
    fprintf(stderr,"ipipe.c: Error closing wfd\n");
    error = 1;
  }

  bzero(buf,1000);
  /* Read stdout and stderr */
  fscanf(readpipe,"%999c",buf);
  /* ignore errors from fscanf */

  /* Close filedes[0] filepointer */
  if (fclose(readpipe) == EOF) {
    fprintf(stderr,"ipipe.c: Error closing readpipe\n");
    error = 1;
  }

  if (error) { return "ipipe error"; } else { return buf; };
}
