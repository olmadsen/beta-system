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
	case "4.1*":
		######## Sun4 SPARC / SunOS4.1.x configuration #######
		setenv MACHINETYPE SUN4 
		setenv objdir sun4
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME /home/quercus1/motif-sunos/Motif-1.2.3a/IXImd12x
		if ( ! $?MOTIFINC  ) setenv MOTIFINC  $MOTIFHOME/include
		if ( ! $?OPENWINHOME ) setenv OPENWINHOME /usr/openwin
		#setenv PATH $MOTIFHOME/bin:$PATH
		#if ( $?XFILESEARCHPATH ) then
		#	setenv XFILESEARCHPATH $MOTIFHOME/lib/%T/%N%S:$XFILESEARCHPATH
		#else
		#	setenv XFILESEARCHPATH $MOTIFHOME/lib/%T/%N%S
		#endif
		#setenv XMBINDDIR $MOTIFHOME/etc/key_bindings
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:$OPENWINHOME/lib:/usr/local/lib:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:$OPENWINHOME/lib:/usr/local/lib
		endif
		if ( $?LD_RUN_PATH ) then
			setenv LD_RUN_PATH $MOTIFHOME/lib:$OPENWINHOME/lib:/usr/local/lib:$LD_RUN_PATH
		else
			setenv LD_RUN_PATH $MOTIFHOME/lib:$OPENWINHOME/lib:/usr/local/lib
		endif
		breaksw
	case "5.[23]":
		######## Sun4 SPARC / Solaris configuration #######
		setenv MACHINETYPE SUN4S
		setenv objdir sun4s
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME   /opt/SUNWmotif
		if ( ! $?MOTIFINC  ) setenv MOTIFINC    $MOTIFHOME/include
		if ( ! $?OPENWINHOME ) setenv OPENWINHOME /usr/openwin
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
	case "5.[45]*":
		######## Sun4 SPARC / Solaris configuration #######
		setenv MACHINETYPE SUN4S
		setenv objdir sun4s
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME   /usr/dt
		if ( ! $?MOTIFINC  ) setenv MOTIFINC    $MOTIFHOME/include
		if ( ! $?OPENWINHOME ) setenv OPENWINHOME /usr/openwin
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
	default:
		echo ${0}: Unsupported Sun4 OS.
		exit 1
		breaksw
	endsw
	breaksw
case "sun3*":
	################### Sun3 configuration ########################
	setenv MACHINETYPE SUN3 
	setenv objdir sun3
	breaksw
case "9000/[34]??":
	################### HP9000s300/400 configuration ##############
	switch("`uname -r`")
	case "*7.*":
		########### HP-UX 7 configuration ###################
		setenv MACHINETYPE HP
		setenv objdir hp
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/Motif1.1
		if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Motif1.1
		breaksw
	case "*8.*":
		########### HP-UX 8 configuration ###################
		setenv MACHINETYPE HPUX8
		setenv objdir hpux8 
		setenv betaopt "-s 38 0"
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/Motif1.1
		if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Motif1.1
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib
		endif
		breaksw
	case "*9.*":
		########### HP-UX 9 configuration ###################
		setenv MACHINETYPE HPUX9MC
		setenv objdir hpux9mc
		setenv betaopt 
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/Motif1.2
		if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Motif1.2
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:/usr/lib/X11R5:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH $MOTIFHOME/lib:/usr/lib/X11R5
		endif
		breaksw
	default:
		echo $0: Unsupported HP-UX version.
		exit 1;
		breaksw
	endsw
	breaksw
case "9000/7??":
	################### HP9000s700/SNAKE configuration ############
	switch("`uname -r`")
	case "*8.*":
		########### HP-UX 8 configuration ###################
		setenv MACHINETYPE SNAKE
		setenv objdir snake
		setenv betaopt 
		if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/Motif1.1
		if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Motif1.1
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH ${MOTIFHOME}/lib:$LD_LIBRARY_PATH
		else
			setenv LD_LIBRARY_PATH ${MOTIFHOME}/lib
		endif
		breaksw
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
	default:
		echo $0: Unsupported HP-UX version.
		exit 1;
		breaksw
	endsw
	breaksw
case "i?86":
	#################### Linux configuration ######################
	setenv MACHINETYPE LINUX
	setenv objdir linux
	if ( ! $?MOTIFHOME ) setenv MOTIFHOME /usr/lib/X11/Motif
	if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include/Xm
	switch("`uname -r`")
	case "1.1*":
		set xlib=/usr/X11R5/lib
		breaksw
	default:
		set xlib=/usr/X11R6/lib
		breaksw
	endsw
	if ( $?LD_LIBRARY_PATH ) then
		setenv LD_LIBRARY_PATH ${xlib}:${MOTIFHOME}:$LD_LIBRARY_PATH
	else
		setenv LD_LIBRARY_PATH ${xlib}:${MOTIFHOME}
	endif
	breaksw
case "IP22":
case "IP32":
	########### Silicon Graphics IRIX configuration #############
	setenv MACHINETYPE SGI
	setenv MOTIFHOME /usr/lib
	if ( ! $?MOTIFINC  ) setenv MOTIFINC  /usr/include
	setenv objdir sgi
	if ( $?LD_LIBRARY_PATH ) then
		setenv LD_LIBRARY_PATH ${MOTIFHOME}:$LD_LIBRARY_PATH
	else
		setenv LD_LIBRARY_PATH ${MOTIFHOME}
	endif
	breaksw
default:
	echo ${0}: Unsupported architecture.
	exit 1
	breaksw
endsw
