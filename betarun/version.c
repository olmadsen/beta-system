char betarun_version[] = "BETARUN VERSION 5.3(19)";

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.18  2001/06/21 12:06:50  datpete
 * Fixes for dynamic exception handling on intel.
 * Now stack traversal can determine if external activation records found
 * on the stack comes from a real callback from beta or via a system
 * exception handler from betarun.
 * Betarun version number: 18
 *
 * Revision 1.17  2001/06/20 09:13:30  corry
 * Prettyness fixes to makefiles
 * Betarun version number: 17
 *
 * Revision 1.16  2001/06/20 08:50:40  corry
 * * Add variables with system-independent versions of mv, rm, cp, echo (use perl)
 * * Move Betarun version number to major.minor(release) number and add access
 *   functions
 * * Pretty up output so commands are more clearly visible (mostly Unix)
 * Betarun version number: 16
 *
 * Revision 1.15  2001/06/19 11:41:13  datpete
 * Added support for -O2 instead of -O6 on sgi in Makefile-vpath's
 * Betarun version number: 15
 *
 * Revision 1.14  2001/05/23 12:23:57  falk
 * Rettet en def i Exithandler metoden i ./C/sighandler.c
 * Betarun version number: 14
 *
 * Revision 1.13  2001/05/16 14:32:06  falk
 * a ExitHandler detail
 * Betarun version number: 13
 *
 * Revision 1.12  2001/05/16 12:31:40  falk
 * removed the 'DataRegs.run' entry
 * Betarun version number: 12
 *
 * Revision 1.11  2001/05/10 13:08:10  datpete
 * Fixed sparc scanComponentStack for find_activation
 * Betarun version number: 11
 *
 * Revision 1.10  2001/05/10 12:53:00  corry
 * Make CRUN Makefile more pretty
 * Some support for rungen.exe dependency on x86 targets
 * Betarun version number: 10
 *
 * Revision 1.9  2001/05/10 12:44:07  corry
 * Make output of Makefiles more beautiful
 * Betarun version number: 9
 *
 * Revision 1.8  2001/05/10 11:31:06  datpete
 * test
 * Betarun version number: 8
 *
 * Revision 1.7  2001/05/10 11:14:55  datpete
 * Small fixes for dynamic exceptions
 * Betarun version number: 8
 *
 * Revision 1.6  2001/04/16 14:58:31  corry
 * Define and export MV, CP and RM variables in Makefile for names of common utils
 * Add rules to build rungen (gen) the run compiler (for arches that need it)
 * Betarun version number: 7
 *
 * Revision 1.5  2001/04/11 11:54:43  corry
 * Fix comments (CVS test)
 * Betarun version number: 6
 *
 * Revision 1.4  2001/04/10 15:36:09  corry
 * Just testing
 * Betarun version number: 4
 *
 * Revision 1.3  2001/04/10 15:16:59  beta
 * Betarun version number: 3
 * Added (c) message
 *
 * Revision 1.2  2001/04/10 14:55:50  corry
 *
 * Betarun version number: 2
 * Developer:
 * Added (C) message to Makefile-toplev
 *
 * Revision 1.1  2001/04/10 13:49:53  corry
 * Added version.c
 *
 */

#include <ctype.h> /* For isdigit */
#include <stdlib.h> /* For atoi */

int
get_betarun_major()
{
    char *p = betarun_version;
    while(!isdigit((unsigned char)(*p))) p++;
    return atoi(p);
}

int
get_betarun_minor()
{
    char *p = betarun_version;
    while(!isdigit((unsigned char)(*p))) p++;
    while(isdigit((unsigned char)(*p))) p++;
    while(!isdigit((unsigned char)(*p))) p++;
    return atoi(p);
}

int
get_betarun_release()
{
    char *p = betarun_version;
    while(!isdigit((unsigned char)(*p))) p++;
    while(isdigit((unsigned char)(*p))) p++;
    while(!isdigit((unsigned char)(*p))) p++;
    while(isdigit((unsigned char)(*p))) p++;
    while(!isdigit((unsigned char)(*p))) p++;
    return atoi(p);
}

char *
get_betarun_version()
{
    char *p = betarun_version;
    while(!isdigit((unsigned char)(*p))) p++;
    return p;
}

/*
main()
{
    printf("Major = %d\nMinor = %d\nRelease=%d\n", get_betarun_major(), get_betarun_minor(), get_betarun_release());
    printf("Version = %s\n", get_betarun_version());
}
*/
