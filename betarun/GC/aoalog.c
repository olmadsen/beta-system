
#include "beta.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static char *AOALogName = ".aoa_log";
static long AOALogOpened = FALSE;
static int logFd;

void AOALogOpen(void) 
{
    if (AOALogOpened == FALSE) {
        if ((logFd = open(AOALogName, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1) {
            fprintf(stdout,"AOALogOpen: Could not open AOALogFile\n");
        } else {
            AOALogOpened = TRUE;
        }
    }
}

void AOALogClose(void)
{
    if (AOALogOpened == TRUE) {
        close(logFd);
    }
}

void AOALogPutText(char *str) 
{
    if (AOALogOpened == FALSE) {
        AOALogOpen();
    }
    write(logFd, str, strlen(str));
}

void AOALogNewLine(void) 
{
    AOALogPutText("\n");
}

void AOALogPutInt(int i) 
{
    char buf[512];
    
    sprintf(buf,"%d",i);
    AOALogPutText(buf);
}
