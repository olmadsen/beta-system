# This script sets the following environment variables:
#   MACHINETYPE	set to machine type in UPPER CASE (e.g SUN4)
#   objdir   	set to machine type in lower case (e.g sun4)
#   LD_LIBRARY_PATH (see man ld)
#   LD_RUN_PATH     (see man ld)
#
# usage in C-shell (/bin/csh or descendants) script:
# -------------------------------------------------- 
# setenv BETALIB ...
# source $BETALIB/configuration/r3.0/env.csh

switch("`uname -m`")
case "sun4*"
	switch("`uname -r`")
	case "5.[23]":
		######## Sun4 SPARC / Solaris configuration #######
		setenv MACHINETYPE SUN4S
		setenv objdir sun4s
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME   /opt/SUNWmotif
		if ( ! $?MOTIFINC  ) setenv MOTIFINC    $MOTIFHOME/include
		if ( ! $?OPENWINHOME ) setenv OPENWINHOME /usr/openwin
		setenv MOTIFLINKOPT '-lXm'
		#setenv PATH $MOTIFHOME/bin:$PATH
		#if ( $?XFILESEARCHPATH ) then
		#	setenv XFILESEARCHPATH $MOTIFHOME/lib/%T/%N%S:$XFILESEARCHPATH
		#else
		#	setenv XFILESEARCHPATH $MOTIFHOME/lib/%T/%N%S
		#endif
		#setenv XMBINDDIR $MOTIFHOME/etc/key_bindings
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib
		endif
		if ( $?LD_RUN_PATH ) then
			setenv LD_RUN_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:$LD_RUN_PATH
		else
			setenv LD_RUN_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib
		endif
		breaksw
	case "5.[45678]*":
		######## Sun4 SPARC / Solaris configuration #######
		setenv MACHINETYPE SUN4S
		setenv objdir sun4s
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME   /usr/dt
		if ( ! $?MOTIFINC  ) setenv MOTIFINC    $BETALIB/X11/Motif/private/external/include
		if ( ! $?OPENWINHOME ) setenv OPENWINHOME /usr/openwin
		if ( -f $MOTIFHOME/lib/libXm.so.4 ) then
		# We use Motif 1.2.3 since our C object files 
		# are compiled with Motif 1.2.3 headers.
		setenv MOTIFLINKOPT "$MOTIFHOME/lib/libXm.so.3"
		#setenv PATH $MOTIFHOME/bin:$PATH
		#if ( $?XFILESEARCHPATH ) then
		#	setenv XFILESEARCHPATH $MOTIFHOME/lib/%T/%N%S:$XFILESEARCHPATH
		#else
		#	setenv XFILESEARCHPATH $MOTIFHOME/lib/%T/%N%S
		endif
		#setenv XMBINDDIR $MOTIFHOME/etc/key_bindings
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib
		endif
		if ( $?LD_RUN_PATH ) then
			setenv LD_RUN_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:$LD_RUN_PATH
		else
			setenv LD_RUN_PATH $MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib
		endif
		breaksw
	default:
		echo ${0}: Unsupported Sun4 OS.
		exit 1
		breaksw
	endsw
	breaksw
case "9000/7??":
	################### HP9000s700/SNAKE configuration ############
	switch("`uname -r`")
	case "*9.*":
		########### HP-UX 9 configuration ###################
		setenv MACHINETYPE HPUX9PA
		setenv objdir hpux9pa
		setenv betaopt 
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/Motif1.2
		if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Motif1.2
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH ${MOTIFHOME}:/usr/lib/X11R5:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH ${MOTIFHOME}:/usr/lib/X11R5
		endif
		breaksw
	case "*10.*":
		########### HP-UX 9 configuration ###################
		setenv MACHINETYPE HPUX9PA
		setenv objdir hpux9pa
		setenv betaopt 
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/Motif1.2_R6
		if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Motif1.2
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH ${MOTIFHOME}:/usr/lib/X11R6:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH ${MOTIFHOME}:/usr/lib/X11R6
		endif
		breaksw
	default:
		echo $0: Unsupported HP-UX version.
		exit 1;
		breaksw
	endsw
	breaksw
case i86pc:
	#################### Solaris X86 configuration ###############
	setenv MACHINETYPE X86SOL
	setenv objdir x86sol
	if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/dt
	if ( ! $?MOTIFINC )  setenv MOTIFINC  /usr/dt/include
	breaksw
case "i?86":
	#################### Linux configuration ######################
	setenv MACHINETYPE LINUX
	setenv objdir linux
	if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/X11/Motif
	#if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Xm
	#if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/X11/include
	if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/X11R6/include
	switch("`uname -r`")
	case "1.1*":
		set xlib=/usr/X11R5/lib
		if ( $?LD_LIBRARY_PATH ) then
		  setenv LD_LIBRARY_PATH ${xlib}:${MOTIFHOME}:$LD_LIBRARY_PATH
		else
		  setenv LD_LIBRARY_PATH ${xlib}:${MOTIFHOME}
		endif
		breaksw
	default:
		breaksw
	endsw
	breaksw
case "IP[23][0127]":
	########### Silicon Graphics IRIX configuration #############
	setenv MACHINETYPE SGI
	setenv MOTIFHOME /usr/lib
	if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include
	setenv objdir sgi
	# No need to set LD_LIBRARY_PATH - MOTIFHOME is in a standard place
	# And setting LD_LIBRARY_PATH on sgi's where LD_LIBRARYN32_PATH is
	# also used by the linker results in annoying runtime warnings.
	#if ( $?LD_LIBRARY_PATH ) then
	#    setenv LD_LIBRARY_PATH ./sgi:$BETALIB/lib/sgi:$LD_LIBRARY_PATH
	#else
	#    setenv LD_LIBRARY_PATH ./sgi:$BETALIB/lib/sgi
	#endif
	#
	breaksw
default:
	echo ${0}: Unsupported architecture.
	exit 1
	breaksw
endsw
