# This script sets the following variables:
#   MACHINETYPE	set to machine type in UPPER CASE (e.g SUN4)
#   objdir   	set to machine type in lower case (e.g sun4)
#		
# Further the following variables are set and exported 
# (i.e. made visible to subprocesses): 
#   LD_LIBRARY_PATH (see man ld)
#   LD_RUN_PATH     (see man ld)
# The following environtment variables are set *if not already set*.
#   MOTIFHOME       Placement of Motif libraries
#   MOTIFINC        Placement of Motif include files
#
# usage in bourne shell (/bin/sh) script:
# --------------------------------------- 
# BETALIB=...
# export BETALIB
# . {BETALIB}/configuration/r2.6/env.sh

# debug:
# set -x

case "`uname -m`" in
	sun4*)
		case "`uname -r`" in
		4.1*)
			######## Sun4 SPARC / SunOS4.1.x configuration #######
			MACHINETYPE=SUN4
			objdir=sun4
			# Motif 1.1 (IXI) setup.
			# MOTIFHOME=${MOTIFHOME-/home/tatra/Motif-1.1}
			# Motif 1.2 (IXI) setup.
			MOTIFHOME=${MOTIFHOME-/home/quercus1/motif-sunos/Motif-1.2.3a/IXImd12x}
			MOTIFINC=${MOTIFINC-$MOTIFHOME/include}
			OPENWINHOME=${OPENWINHOME-/usr/openwin}
			export OPENWINHOME
			#PATH=$MOTIFHOME/bin:/usr/bin/X11:$PATH
			#export PATH
			#XFILESEARCHPATH=$MOTIFHOME/lib/%T/%N%S:$XFILESEARCHPATH
			#export XFILESEARCHPATH
			#XMBINDDIR=$MOTIFHOME/etc/key_bindings
			#export XMBINDDIR
			LD_LIBRARY_PATH=$MOTIFHOME/lib:$OPENWINHOME/lib:$LD_LIBRARY_PATH
			;;
		5.[23])
			######## Sun4 SPARC / Solaris configuration #######
			MACHINETYPE=SUN4S
			objdir=sun4s
			# Motif 1.2.2 (IXI) setup.
			MOTIFHOME=${MOTIFHOME-/opt/SUNWmotif}
			MOTIFINC=${MOTIFINC-$MOTIFHOME/include}
			OPENWINHOME=${OPENWINHOME-/usr/openwin}
			export OPENWINHOME
			#PATH=$MOTIFHOME/bin:/usr/bin/X11:/usr/ccs/bin:$PATH
			#export PATH
			#XFILESEARCHPATH=$MOTIFHOME/lib/%T/%N%S:$XFILESEARCHPATH
			#export XFILESEARCHPATH
			#XMBINDDIR=$MOTIFHOME/etc/key_bindings
			#export XMBINDDIR
			LD_LIBRARY_PATH=$MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:/usr/local/lib:$LD_LIBRARY_PATH
			LD_RUN_PATH=$MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:/usr/local/lib:$LD_RUN_PATH
			;;
		5.*)
			######## Sun4 SPARC / Solaris configuration #######
			MACHINETYPE=SUN4S
			objdir=sun4s
			MOTIFHOME=${MOTIFHOME-/usr/dt}
			MOTIFINC=${MOTIFINC-$MOTIFHOME/include}
			OPENWINHOME=${OPENWINHOME-/usr/openwin}
			export OPENWINHOME
			#PATH=$MOTIFHOME/bin:/usr/bin/X11:/usr/ccs/bin:$PATH
			#export PATH
			#XFILESEARCHPATH=$MOTIFHOME/lib/%T/%N%S:$XFILESEARCHPATH
			#export XFILESEARCHPATH
			#XMBINDDIR=$MOTIFHOME/etc/key_bindings
			#export XMBINDDIR
			LD_LIBRARY_PATH=$MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:/usr/local/lib:$LD_LIBRARY_PATH
			LD_RUN_PATH=$MOTIFHOME/lib:/usr/dt/lib:$OPENWINHOME/lib:/usr/local/lib:$LD_RUN_PATH
			;;
		*)	echo $0: Unsupported Sun4 OS.
			;;
		esac
		;;
	sun3*)
		################### Sun3 configuration ########################
		MACHINETYPE=SUN3 
		objdir=sun3
		;;
	9000/[34]??)
		################### HP9000s300/400 configuration ##############
		case "`uname -r`" in
		*7.*)
		        ########### HP-UX 7 configuration ###################
			MACHINETYPE=HP
			objdir=hp
			MOTIFINC=${MOTIFINC-/usr/include/Motif1.1}
			MOTIFHOME=${MOTIFHOME-/usr/lib/Motif1.1}
			LD_LIBRARY_PATH=$MOTIFHOME:$LD_LIBRARY_PATH
			;;
		*8.*)
		        ########### HP-UX 8 configuration ###################
			MACHINETYPE=HPUX8
			objdir=hpux8 
			betaopt="-s 38 0"
			MOTIFINC=${MOTIFINC-/usr/include/Motif1.1}
			MOTIFHOME=${MOTIFHOME-/usr/lib/Motif1.1}
			PATH=/usr/bin/X11:$PATH
			export PATH
			LD_LIBRARY_PATH=$MOTIFHOME:$LD_LIBRARY_PATH
			;;
		*9.*)
			########### HP-UX 9 configuration ###################
			MACHINETYPE=HPUX9MC
			objdir=hpux9mc
			betaopt=
			MOTIFINC=${MOTIFINC-/usr/include/Motif1.2}
			MOTIFHOME=${MOTIFHOME-/usr/lib/Motif1.2}
			PATH=/usr/bin/X11:$PATH
			export PATH
			LD_LIBRARY_PATH=$MOTIFHOME:/usr/lib/X11R5:$LD_LIBRARY_PATH
			;;
		*)
			echo $0: Unsupported HP-UX version
			exit 1
			;;
		esac
		;;
	9000/7??)
		################### HP9000s700/SNAKE configuration ############
		case "`uname -r`" in
		*8.*)
		        ########### HP-UX 8 configuration ###################
			MACHINETYPE=SNAKE
			objdir=snake 
			betaopt=
			MOTIFINC=${MOTIFINC-/usr/include/Motif1.1}
			MOTIFHOME=${MOTIFHOME-/usr/lib/Motif1.1}
			PATH=/usr/bin/X11:$PATH
			export PATH
			LD_LIBRARY_PATH=$MOTIFHOME:$LD_LIBRARY_PATH
			;;
		*9.*)
			########### HP-UX 9 configuration ###################
			MACHINETYPE=HPUX9PA
			objdir=hpux9pa
			betaopt=
			MOTIFINC=${MOTIFINC-/usr/include/Motif1.2}
			MOTIFHOME=${MOTIFHOME-/usr/lib/Motif1.2}
			PATH=/usr/bin/X11:$PATH
			export PATH
			LD_LIBRARY_PATH=$MOTIFHOME:/usr/lib/X11R5:$LD_LIBRARY_PATH
			;;
		*)
			echo $0: Unsupported HP-UX version.
			exit 1
			;;
		esac
		;;
	i?86)
		#################### Linux configuration ######################
		MACHINETYPE=LINUX
		objdir=linux
		MOTIFINC=${MOTIFINC-/usr/include/Xm}
		MOTIFHOME=${MOTIFHOME-/usr/lib/X11/Motif}
		PATH=/usr/bin/X11:$PATH
		export PATH
		case "`uname -r`" in
		1.1*)
			LD_LIBRARY_PATH=/usr/X11R5/lib/:$MOTIFHOME:$LD_LIBRARY_PATH
			;;
		*)
			LD_LIBRARY_PATH=/usr/X11R6/lib/:$MOTIFHOME:$LD_LIBRARY_PATH
			;;
		esac
		;;
	IP22)
		########### Silicon Graphics IRIX configuration #############
		MACHINETYPE=SGI
		MOTIFHOME=${MOTIFHOME-/usr/lib}
		MOTIFINC=${MOTIFINC-/usr/include}
		PATH=/usr/bin/X11:$PATH
		LD_LIBRARY_PATH=$MOTIFHOME:$LD_LIBRARY_PATH
		export PATH
		objdir=sgi
		;;
	*)
		echo $0: Unsupported architecture.
		exit 1
		;;
esac
export LD_LIBRARY_PATH
export LD_RUN_PATH
export MOTIFHOME
export MOTIFINC