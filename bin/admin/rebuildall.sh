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

# Now I would like to get the settings from .login, but that is noisy...
# source $HOME/.login >& /dev/null
set path=(/users/beta/bin /users/beta/bin/admin /usr/local/bin /usr/ucb /bin /usr/bin /usr/bin/X11  /usr/bsd /usr/lib/tex /usr/etc /usr/share/etc/supervise/bin /usr/etc/supervise/bin /etc .)
setenv CVSROOT /users/beta/.CVSHOME
set OSTYPE = `uname -rs`

switch("$OSTYPE")
case "SunOS 5.*"
	echo 'This is a SPARC Solaris.'
	set path = (/opt/SUNWspro/bin $path)
	set path = (/users/beta/GNU/bin/sun4s /usr/sbin /usr/ccs/bin $path)
	breaksw
case "SunOS 4.*"
	echo 'This is a SunOS SPARC.'
	set path = ( /users/beta/GNU/bin/sun4 $path )
	breaksw
case "HP-UX B.08.*"
	echo 'This is an HP-UX 8 machine.'
	set path = ( /users/beta/GNU/bin/hpux8 $path )
	breaksw
case "HP-UX B.09.*"
	switch("`uname -m`")
	case "9000/[34]??":
		echo 'This is an HP-UX 9 MC machine.'
		set path = ( /users/beta/GNU/bin/hpux9mc $path )
		breaksw
	case "9000/7??":
		echo 'This is an HP-UX 9 PA machine.'
		set path = ( /users/beta/GNU/bin/hpux9pa $path )
		breaksw
	endsw
	breaksw
case "IRIX*"
	echo 'This is a Silicon Graphics.'
	if( $?prompt != 0 ) stty erase "^?" intr "^C" # sgiterm
	set path = ( /users/beta/GNU/bin/sgi /usr/sbin /usr/bsd $path )
	breaksw
case "Linux*"
	echo 'This is Linux'
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

