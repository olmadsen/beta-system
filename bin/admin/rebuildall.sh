#!/usr/local/bin/tcsh

# Hvis er er frysning nu, saa lad vaere med at blande dig!
# exit 0

# configuration:
set CVSUPDATE=yes
set RCMUPDATE=yes
set BUILDMACHINES=(lisa amigo)

# You can touch the following files to get a one-shot effect as if the
# flags had been set in this script:
# "$BETALIB/.rebuildall-cvsupdate"
# "$BETALIB/.rebuildall-rcmupdate"

### Usage:
# Put in crontab on the machine where a periodical recompilation 
# of all files and programs is desired and the files are physically located.
# Insert other machines into BUILDMACHINES to get them to rebuild too,
# after the machine running this script has cleaned up everything.
#
# Arguments: 
#   First aguments is the betalib to cleanup.
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
setenv RAGNAROOT /users/beta/.Ragnarok


# Hack:  HP machines have too little space on /tmp.  Use ~beta/tmp instead.
# Well, lisa has enough room on /tmp.  No need for now.
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
    mbs_rmcode -u sun4s linux sgi hpux9pa nti_ms nti_gnu ms gnu >>& $LOG

    # Check one-shot variables...
    if (-f "$BETALIB/.rebuildall-cvsupdate") then
	rm -f "$BETALIB/.rebuildall-cvsupdate"
	set CVSUPDATE=yes
    endif
    if (-f "$BETALIB/.rebuildall-rcmupdate") then
	rm -f "$BETALIB/.rebuildall-rcmupdate"
	set RCMUPDATE=yes
    endif

    if ( $CVSUPDATE == "yes" ) then
        echo "rebuildall.sh: Doing mbs_cvsupdate -u -c." >>& $LOG
        mbs_cvsupdate -u -c >>& $LOG
    endif
    if ( $RCMUPDATE == "yes" ) then
	if ( $MACHINETYPE == "SUN4S" ) then
	    echo "rebuildall.sh: Doing rcm -do 'gettip;quit'." >>& $LOG
	    cd $BETALIB/compiler
	    rcm -do "gettip; quit" >>& $LOG
	    cd $BETALIB
	endif
    endif
    #date >>& $LOG
    #echo "rebuildall.sh: Checking compiler." >>& $LOG
    #setenv BETAOPTS --nocode
    #date >>& $LOG
    #mbs_compiletools compiler >>& $LOG
    #unsetenv BETAOPTS
    date >>& $LOG
    echo "rebuildall.sh: Building betarun." >>& $LOG
    date >>& $LOG
    cd $BETALIB/betarun/$objdir
    make all >>& $LOG
    date >>& $LOG
    echo "rebuildall.sh: Building compiler." >>& $LOG
    mbs_compiletools compiler >>& $LOG
    date >>& $LOG
    echo "rebuildall.sh: mbs_compile -- --nocode." >>& $LOG
    mbs_compile -- --nocode >> $LOG
    date >>& $LOG
    echo "rebuildall.sh: rsh'ing to other machines." >>& $LOG
    foreach mach ($BUILDMACHINES) 
         ( rsh $mach $BETALIB/bin/admin/rebuildall.sh $BETALIB no < /dev/zero ) &
    end
    date >>& $LOG
    echo "rebuildall.sh: mbs_compile." >>& $LOG
    mbs_compile >> $LOG
    date >>& $LOG
    echo "rebuildall.sh: Building tools." >>& $LOG
    mbs_compiletools -u >>& $LOG
    date >>& $LOG
else
    date >>& $LOG
    echo "rebuildall.sh: Building betarun." >>& $LOG
    cd $BETALIB/betarun/$objdir
    make all >>& $LOG
    cd $BETALIB
    date >>& $LOG
    echo "rebuildall.sh: Building compiler." >>& $LOG
    mbs_compiletools compiler >>& $LOG
    date >>& $LOG
    echo "rebuildall.sh: mbs_compile." >>& $LOG
    mbs_compile >> $LOG
    date >>& $LOG
    echo "rebuildall.sh: Building tools." >>& $LOG
    mbs_compiletools -u >>& $LOG
    date >>& $LOG
endif

echo "rebuildall.sh: Completed." >>& $LOG

