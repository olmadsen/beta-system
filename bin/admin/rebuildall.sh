#! /usr/local/bin/tcsh

# Der er frysning nu, lad vaer med at blande dig!!!
# exit 0  Den er overstaaet nu...

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

# Now I would like to get the settings from .login, but that is noisy...
# source $HOME/.login >& /dev/null
set path=(/users/beta/bin /users/beta/bin/admin /usr/local/bin /usr/ucb /bin /usr/bin /usr/bin/X11  /usr/bsd /usr/lib/tex /usr/etc /usr/share/etc/supervise/bin /usr/etc/supervise/bin /etc .)
setenv CVSROOT /users/beta/.CVSHOME
set OSTYPE = `uname -rs`

switch("$OSTYPE")
case "SunOS 5.*"
	set path = (/opt/SUNWspro/bin $path)
	set path = (/users/beta/GNU/bin/sun4s /usr/sbin /usr/ccs/bin $path)
	breaksw
case "SunOS 4.*"
	set path = ( /users/beta/GNU/bin/sun4 $path )
	breaksw
case "HP-UX B.08.*"
	set path = ( /users/beta/GNU/bin/hpux8 $path )
	breaksw
case "HP-UX B.09.*"
	switch("`uname -m`")
	case "9000/[34]??":
		set path = ( /users/beta/GNU/bin/hpux9mc $path )
		breaksw
	case "9000/7??":
		set path = ( /users/beta/GNU/bin/hpux9pa $path )
		breaksw
	endsw
	breaksw
case "IRIX*"
	if( $?prompt != 0 ) stty erase "^?" intr "^C" # sgiterm
	set path = ( /users/beta/GNU/bin/sgi /usr/sbin /usr/bsd $path )
	breaksw
case "Linux*"
	stty erase "^?" intr "^C"
	breaksw
endsw

setenv BETALIB    $1
setenv REMOVEASTS $2
source ${BETALIB}/configuration/env.csh >& /dev/null

setenv LOG ${BETALIB}/log/rebuildall.$MACHINETYPE

# Hack:  HP machines have too little space on /tmp.  Use ~beta/tmp instead.
# Well, belfort has enough room on /tmp.  No need for now.
#if ( $$MACHINETYPE == "HPUX9PA" ) then
#    setenv TMPDIR $HOME/tmp
#endif

rm -f $LOG
echo "rebuildall.sh: Starting on BETALIB $BETALIB." >>& $LOG
date >>& $LOG
if ( $REMOVEASTS == "yes" ) then
    echo "rebuildall.sh: Removing all asts files for all platforms." >>& $LOG
    mbs_rmast -u >>& $LOG
    echo "rebuildall.sh: Removing all code files for all platforms." >>& $LOG
    mbs_rmcode -u sun4s linux sgi hpux9pa nti_ms nti_gnu ms gnu bor >>& $LOG
endif
# Fragbody and possibly others make the compiler crash for the time being.  
# Make sure there is a compiler by just retrying.
setenv BETAOPTS --nocode
mbs_compiletools compiler >>& $LOG
unsetenv BETAOPTS
mbs_compiletools compiler >>& $LOG
mbs_compiletools compiler >>& $LOG
if ( $REMOVEASTS == "yes" ) then
    echo "rebuildall.sh: Removing all asts files for all platforms." >>& $LOG
    mbs_rmast -u >>& $LOG
endif
echo "rebuildall.sh: Removing all code files for $objdir." >>& $LOG
mbs_rmcode -u $objdir >>& $LOG
mbs_compile --nocode >>& LOG
mbs_compile >>& LOG
mbs_compiletools -u >>& $LOG
date >>& $LOG
echo "rebuildall.sh: Completed." >>& $LOG

