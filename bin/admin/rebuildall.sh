#! /usr/local/bin/tcsh

### Usage:
# Put in crontab on machines where a periodical recompilation 
# of all files and programs is desired.
#
# Arguments: 
#   First aguments is the bealib to cleanup.
#
#   Second argument is 'yes' iff all asts and codefiles should be removed
#	before the compilation begins.  Set this on one platform only and set
#	it to 'no' on the other platforms
#
###

if ($# != 2) then
    echo "Wrong number of arguments."
    exit 1
endif

setenv BETALIB    $1
setenv REMOVEASTS $2
source ${BETALIB}/configuration/env.csh

setenv LOG ${BETALIB}/log/rebuildall.$MACHINETYPE

rm -f $LOG
echo "rebuildall.sh: Starting." >>& $LOG
date >>& $LOG
if ( $REMOVEASTS == "yes" ) then
    echo "rebuildall.sh: Removing all asts and codefiles." >>& $LOG
    mbs_rmast -u >>& $LOG
    mbs_rmcode -u sun4s linux sgi hpux9pa nti_ms nti_gnu ms gnu bor >>& $LOG
endif
mbs_compiletools compiler >>& $LOG
mbs_compile >>& LOG
mbs_compiletools -u >>& $LOG
date >>& $LOG
echo "rebuildall.sh: Completed." >>& $LOG

