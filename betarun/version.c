char betarun_version[] = "BETARUN VERSION 5.3(69+)";

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.72  2002/01/23 13:52:06  corry
 * lsdkjfslkdjf
 * Betarun version number: 69
 *
 * Revision 1.71  2002/01/23 13:49:04  corry
 * Just testing mbs_commit again
 *
 * Betarun version number: 68
 *
 * Revision 1.70  2002/01/23 10:26:54  corry
 * Get rid of /./ in paths
 * Betarun version number: 67
 *
 * Revision 1.69  2002/01/23 10:08:35  corry
 * Fixed up log messages again
 * Betarun version number: 66+
 *
 * Revision 1.68  2002/01/23 10:05:39  corry
 * Cosmetic change
 * Betarun version number: 66
 *
 * Revision 1.67  2002/01/23 10:03:40  corry
 * Another test!
 * Betarun version number: 65++
 *
 * Revision 1.66  2002/01/23 10:01:37  corry
 * Testing + feature
 * Betarun version number: 65+
 *
 * Revision 1.65  2002/01/23 09:57:16  corry
 * This time really get rid of those comments!
 * Betarun version number: 65
 *
 * Revision 1.64  2002/01/23 09:55:22  corry
 * Get rid of stupid comments in version.c
 * Betarun version number: 64
 *
 * Revision 1.63  2002/01/22 20:47:34  corry
 * Just testing mbs_commit igen
 * Betarun version number: 63
 *
 * Revision 1.62  2002/01/22 20:46:45  corry
 * Just testing mbs_commit
 * Betarun version number: 62
 *
 * Revision 1.61  2002/01/09 09:51:36  beta
 * Default IOA now back to 1024 on all but Intel
 * Betarun version number: 61
 * Developer: grouleff
 *
 * Revision 1.60  2002/01/04 23:02:00  beta
 * Changes for X86 sol r5.3 betarun boot
 * Betarun version number: 60
 * Developer: pa
 *
 * Revision 1.59  2002/01/03 15:20:44  corry
 * Use .lib, not .o file for betarun on nti_gnu
 * Now can make new betarun on nti_gnu, and it works for simple programs (for all?)
 * Betarun version number: 59
 *
 * Revision 1.58  2002/01/03 12:15:01  corry
 * Don't use parenthesis around (cd dir; do command) sequences in Makefile.  They
 * are not necessary and they confuse shmsdos.exe, the minimal shell)
 * Betarun version number: 58
 *
 * Revision 1.57  2002/01/02 12:23:13  corry
 * Moved betarun file locations as agreed
 * Betarun version number: 57
 *
 * Revision 1.56  2001/12/28 11:39:21  datpete
 * Added debug count of calls of Ck()
 * Betarun version number: 56
 *
 * Revision 1.55  2001/12/05 13:45:15  corry
 * Patches to help Windows compile with mbs_make
 * Betarun version number: 55
 *
 * Revision 1.54  2001/12/05 11:58:02  corry
 * Fix off_t and pc_t error in Windows
 * Betarun version number: 53
 *
 * Revision 1.53  2001/11/30 12:31:41  falk
 * fixed comment in comment in version.c (:-)
 * Betarun version number: 52
 *
 * Revision 1.52  2001/11/29 21:38:37  grouleff
 * Fixed minor bugs introduced in v51.
 * Made sure r5.2.2 and r5.3 are in sync for P/{*.[ch]}
 * Betarun version number: 52
 *
 * Revision 1.51  2001/11/28 09:41:36  grouleff
 * Fixed BUG in PImport: refhandler was not called on references in
 * refeference repetitions (RefRepPTValue)
 *
 * Extended refhandler to deal with references internal to the object.
 * Useful as e.g. origin references often refer to the same "object", and
 * needed to get origins of static partobjects correct, as the surrounding
 * object is not in any table at that point in time.
 *
 * Added updateOtherReferences to referenceTable. I'm not 100% sure whether
 * it is really needed or if some other code guarantees that all oter
 * proxies referring to parts of the same object are updated when an object
 * is loaded?
 *
 * Betarun version number: 51
 *
 * Revision 1.50  2001/11/22 23:04:05  corry
 * Remove compile warnings/errors on SGI and HP
 * Betarun version number: 50
 *
 * Revision 1.49  2001/11/22 15:18:54  corry
 * Let it compile on linux again
 * Betarun version number: 49
 *
 * Revision 1.48  2001/11/22 15:10:25  corry
 * Let it compile on SPARC again
 * Betarun version number: 48
 *
 * Revision 1.47  2001/11/22 14:00:26  corry
 * Make it work on non-AMD chips again (oops!)
 * Betarun version number: 47
 *
 * Revision 1.46  2001/11/22 13:48:50  grouleff
 * Removed extra buffer in SBOBJlookup and USloadObject. Now loads directly
 * into AOA. Added SBOBJload and changed SBOBJlookup, USloadObject for
 * this.
 *
 * Tried to get sun4s to compile after EC's changes to the type of thePC in
 * various places... He'll get it back now...
 *
 * Betarun version number: 46
 *
 * Revision 1.45  2001/11/22 13:37:23  corry
 * * Fix building of novalhalla betarun
 * * Build alloc_tracing version of betarun
 * * Introduce pc_t type as pointer to an instruction
 * * (Optional) support for reducing code size by using bound insn for IOA2AOA test
 * * Try to get mbs_make working again for MG
 * Betarun version number: 42
 *
 * Revision 1.44  2001/11/22 12:36:19  grouleff
 * Merged in support for allowLazyFetch from r5.2.2b
 * Betarun version number: 44
 *
 * Revision 1.43  2001/11/22 11:40:52  grouleff
 * Added translation of iProto field in DynItemRep and DynCompRep.
 *
 * Cleaned up PSENDIAN: All endian code is now within #ifdef PSENDIAN.
 * It should be possible to build a betarun for linux without PSENDIAN
 * by undefining PSENDIAN in C/define.h. This can be ued to make
 * measurements of the added cost os PSENDIAN.
 *
 * Moved external declaration of functions in proto.c from other files to
 * proto.h
 *
 * Betarun version number: 43
 *
 * Revision 1.42  2001/11/22 09:23:37  grouleff
 * Fixed spelling errors.
 * Added printouts under RTDEBUG for some error cases.
 * Betarun version number: 42
 *
 * Revision 1.41  2001/11/21 13:59:06  datpete
 * PS comments from PS workshop today.
 * Fixed iProto handling for ObjectReps
 * Betarun version number: 41
 *
 * Revision 1.40  2001/09/19 15:00:08  beta
 * x86 sol fix: Do not use variables named "PC"
 * Betarun version number: 40
 * Developer: pa
 *
 * Revision 1.39  2001/09/19 14:55:46  beta
 * Fix for X86 sol makefile
 *
 * Betarun version number: 39
 * Developer: pa
 *
 * Revision 1.38  2001/09/09 13:34:42  beta
 * hppa AlloI warning fixed
 * Betarun version number: 38
 * Developer: pa
 *
 * Revision 1.37  2001/09/09 13:24:03  beta
 * hppa PException (MG?)
 * Betarun version number: 37
 * Developer: pa
 *
 * Revision 1.36  2001/09/06 08:03:02  corry
 * Add version.c to xmakefile_nti to avoid
 * > mjolner.obj : error LNK2001: unresolved external symbol _get_betarun_version
 * Betarun version number: 36
 *
 * Revision 1.35  2001/08/24 09:58:38  datpete
 * Removed test prints from valhallaComm.c "sock = 3; done creating buffers"
 * Betarun version number: 35
 *
 * Revision 1.34  2001/08/22 12:05:25  datpete
 * Fixed error in sparc debug code when processing StackObject
 * Betarun version number: 34
 *
 * Revision 1.33  2001/08/22 06:44:16  corry
 * Small makefile fix for profiling (Linux)
 * Put multiple include protection in a file or two
 * Test commit in betarun as part of beta_project CVS area
 * Betarun version number: 33
 *
 * Revision 1.32  2001/08/09 20:16:09  corry
 * More info from TIME_IOA and TIME_AOA
 * Default IOA semispace size reduced from 1024 to 64k
 * We don't need inArea any more
 * Betarun version number: 32
 *
 * Revision 1.31  2001/08/09 20:11:37  corry
 * Add nodebug_pg profiling version of betarun on GNUC platforms
 * Add comments to Makefile-toplev to tell you how to use the library versions
 * Add EXTRA_C_OPTIONS, an environment variable you can set before doing mbs_make
 * Use $(PROF) variable on all builds, incl optimising ones
 * Betarun version number: 31
 *
 * Revision 1.30  2001/08/03 10:45:43  datpete
 * Fixed groupname in beta.dump to be that of the prototype, not the mPart.
 * Betarun version number: 30
 *
 * Revision 1.29  2001/08/02 07:19:52  datpete
 * Small fixes for nti_ms build
 * Betarun version number: 29
 *
 * Revision 1.28  2001/08/01 09:05:13  corry
 * fmt -t only works on GNU fmt.  Restrict its use to Linux.
 * Betarun version number: 28
 *
 * Revision 1.27  2001/07/31 14:22:49  datpete
 * Fix in lowlevel beta.dump
 * Betarun version number: 27
 *
 * Revision 1.26  2001/07/27 12:49:20  datpete
 * Added memory cell a7 too
 * Betarun version number: 26
 *
 * Revision 1.25  2001/07/27 12:38:39  beta
 * Added global variables a5 and a6
 * Betarun version number: 25
 * Developer: gram
 *
 * Revision 1.24  2001/07/27 10:10:34  brogger
 * fixed PROTO_STATISTICS in exit.c
 * Betarun version number: 24
 *
 * Revision 1.23  2001/07/27 09:26:19  datpete
 * Print of formIndex in beta.dump
 * Betarun version number: 23
 *
 * Revision 1.22  2001/07/24 09:19:23  datpete
 * Added memory cell a1 to intel betarun.
 * Used for spilling by new backend.
 * Saved during GC in PerformGC.run.
 * Betarun version number: 22
 *
 * Revision 1.21  2001/07/23 11:34:14  sosh
 * Added Protoype trace to AllocateItem.c and exit.c so that it is possible to see how many times different objects are allocated. Uncomment the define in defines.h to activate
 * Betarun version number: 21
 *
 * Revision 1.20  2001/07/20 09:47:32  sosh
 * Changed the placement of database files. See changes
 * Betarun version number: 20
 *
 * Revision 1.19  2001/06/25 13:56:44  corry
 * Fix calls of isdigit to get _unsigned_ char parameter to avoid warning
 * on Sun.
 * Betarun version number: 19
 *
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
