#-*-Perl-*-
#
# - This script sets the following environment variables, as well as perl-vars:
#   (They are ONLY visible to programs run from the perl-program. 
#    NOT in the shell afterwards!)
#
#   MACHINETYPE     set to machine type in UPPER CASE (e.g SUN4)
#   objdir          set to machine type in lower case (e.g sun4)
#   LD_LIBRARY_PATH (see man ld)
#   LD_RUN_PATH     (see man ld)
#   Other platform dependent vars, like MOTIFHOME, LD_*_PATH, etc.
#   may be set in the 'setup_<platform>' subroutine below.
#
# - The rest is only set at perl-vars, as exporting may be a bad thing to do
#
#   betalib	    set to the betalib with unixstyle '/' as seperator.
#   SDK             set to SDK used (NTI only)
#   TMP             set to either $TMP or '/tmp' or 'c:/temp' whichever exists.
#   OS              set to either WIN, UNIX or MAC
#   CURRENTDIR      set to '.' or ':' or whatever current-directory is.
#   PARENTDIR       set to '..' or '::' or whatever parent-directory is.
#
# - List of legal machinetypes. Allows errorchecking of if's.
#   @MachineTypes  (Only avaiable from perl)
#
# - List of legal OS'es. Allows errorchecking of if's.
#   @OsTypes  (Only avaiable from perl)
#


# When running the script using "perl5 -s" the following options will be set.
# This, of course, assumes that you have not used $n,$v, etc. for other 
# puposes when requiring env.perl.  So require env.perl as the FIRST line!
$simulate = 1 if (defined $n);
$verbose  = 1 if (defined $v);

$|=1;

require "utils.perl";

$betalib=$ENV{'BETALIB'} || die "BETALIB must be set!\n";

@MachineTypes = ('NTI', 'SUN4S', 'HPUX9PA', 'LINUX', 'SGI', 'PPCMAC');

@OsTypes = ('WIN', 'UNIX', 'MAC');

if (-e "c:\\") {
    $CURRENTDIR='.';
    $PARENTDIR='..';
    $betalib =~ s#\\#/#g;
    $OS='WIN';
    $MACHINETYPE = "NTI";
    $SDK = $ENV{'SDK'} || "ms";
    $objdir = "nti/$SDK";
    # LD_ stuff cannot be set here on nti. If you need it, you should set it!
    $TMP = $ENV{'TMP'} || $ENV{'TEMP'} || "c:/temp";
    $TMP =~ s#\\#/#g;
    if (!-d $TMP) {
	print "Unable to find TMP directory. Please create/setup env-vars!\n";
	exit 1;
    }
} elsif (-e "/etc") {
    # UNIX
    $CURRENTDIR='.';
    $PARENTDIR='..';
    $OS='UNIX';
    $TMP = '/tmp';
    $mach = `uname -m`;
    $rev  = `uname -r`;
    if ($mach =~ /^sun4/) {
	if ($rev =~ /^5\.[23]/) {
	    $MACHINETYPE = 'SUN4S';
	    $objdir = 'sun4s';
	    &setup_sun4_5_23;
	} elsif ($rev =~ /^5\.4/) {
	    $MACHINETYPE = 'SUN4S';
	    $objdir = 'sun4s';
	    &setup_sun4_5_4;
	} elsif ($rev =~ /^5\.5/) {
	    $MACHINETYPE = 'SUN4S';
	    $objdir = 'sun4s';
	    &setup_sun4_5_5;
	} else {
	    print "Unknown/unsupported Sun4 OS\n";
	    exit 1;
	}
    } elsif ($mach =~ /^9000\/7../) {
	if ($rev =~ /8\./) {
	    $MACHINETYPE = 'SNAKE';
	    $objdir = 'snake';
	    &setup_snake;
	} elsif ($rev =~ /9\./) {
	    $MACHINETYPE = 'HPUX9PA';
	    $objdir = 'hpux9pa';
	    &setup_hpux9pa;
	} else {
	    print "Unknown/unsupported HP-UX Version\n";
	    exit 1;
	} 
    } elsif ($mach =~ /^i.86/) {
	$MACHINETYPE = 'LINUX';
	$objdir = 'linux';
	&setup_linux;
    } elsif ($mach =~ /^IP22/) {
	$MACHINETYPE = 'SGI';
	$objdir = 'sgi';
	&setup_sgi;
    } else {
	print "Unknown/unsupported architecture.\n";
	exit 1;
    }
} else {
    # Macintosh
    $CURRENTDIR=':';
    $PARENTDIR='::';
    $betalib =~ s#:#/#g;
    $OS='MAC';
    $MACHINETYPE='PPCMAC';
    $objdir='ppcmac';
    $TMP='/';
}

$betalib =~ s#/$##g;               # betalib is now  std unixstyle.

if ($betalib =~ /\/(r\d+\.\d+\.?\d*)/i) {
    $RELEASE=$1;
} else {
    print "env.perl: Fatal: Could not find release-number in BETALIB\n";
    exit(1);
}



sub setup_sun4_5_23 {
    if (!defined $ENV{'MOTIFHOME'}) {
	$ENV{'MOTIFHOME'} = '/opt/SUNWmotif';
    }
    if (!defined $ENV{'MOTIFINC'}) {
	$ENV{'MOTIFINC'} = "$ENV{'MOTIFHOME'}/include";
    }
    if (!defined $ENV{'OPENWINHOME'}) {
	$ENV{'OPENWINHOME'} = '/usr/openwin';
    }
    if (defined $ENV{'LD_LIBRARY_PATH'}) { 
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib:$ENV{'LD_LIBRARY_PATH'}";
    } else {
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib";
    }
    if (defined $ENV{'LD_RUN_PATH'}) {
	$LD_RUN_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib:$ENV{'LD_RUN_PATH'}";
    } else {
	$LD_RUN_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib";
    }
}

sub setup_sun4_5_4 {
    if (!defined $ENV{'MOTIFHOME'}) {
	$ENV{'MOTIFHOME'} = '/opt/dt';
    }
    if (!defined $ENV{'MOTIFINC'}) {
	$ENV{'MOTIFINC'} = "$ENV{'MOTIFHOME'}/include";
    }
    if (!defined $ENV{'OPENWINHOME'}) {
	$ENV{'OPENWINHOME'} = '/usr/openwin';
    }
    if (defined $ENV{'LD_LIBRARY_PATH'}) { 
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib:$ENV{'LD_LIBRARY_PATH'}";
    } else {
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib";
    }
    if (defined $ENV{'LD_RUN_PATH'}) {
	$LD_RUN_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib:$ENV{'LD_RUN_PATH'}";
    } else {
	$LD_RUN_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib";
    }
}

sub setup_sun4_5_5 {
    if (!defined $ENV{'MOTIFHOME'}) {
	$ENV{'MOTIFHOME'} = '/opt/dt';
    }
    if (!defined $ENV{'MOTIFINC'}) {
	$ENV{'MOTIFINC'} = "$ENV{'MOTIFHOME'}/include";
    }
    if (!defined $ENV{'OPENWINHOME'}) {
	$ENV{'OPENWINHOME'} = '/usr/openwin';
    }
    if (defined $ENV{'LD_LIBRARY_PATH'}) { 
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib:$ENV{'LD_LIBRARY_PATH'}";
    } else {
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib";
    }
    if (defined $ENV{'LD_RUN_PATH'}) {
	$LD_RUN_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib:$ENV{'LD_RUN_PATH'}";
    } else {
	$LD_RUN_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/dt/lib:$ENV{'OPENWINHOME'}/lib";
    }
}

sub setup_hpux9pa {
    $ENV{'betaopt'} = "";
    if (!defined $ENV{'MOTIFHOME'}) {
	$ENV{'MOTIFHOME'} = '/usr/lib/Motif1.2';
    }
    if (!defined $ENV{'MOTIFINC'}) {
	$ENV{'MOTIFINC'} = '/usr/include/Motif1.2';
    }
    if (defined $ENV{'LD_LIBRARY_PATH'}) { 
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/lib/X11R5:$ENV{'LD_LIBRARY_PATH'}";
    } else {
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}/lib:/usr/lib/X11R5";
    }
}

sub setup_linux {
    if (!defined $ENV{'MOTIFHOME'}) {
	$ENV{'MOTIFHOME'} = '/usr/lib/X11/Motif';
    }
    if (!defined $ENV{'MOTIFINC'}) {
	$ENV{'MOTIFINC'} = '/usr/include/Xm';
    }
    if ($rev =~ /^1\.1/) {
	$xlib = '/usr/X11R5/lib';
    } else {
	$xlib = '/usr/X11R6/lib';
    }
    if (defined $ENV{'LD_LIBRARY_PATH'}) { 
	$LD_LIBRARY_PATH = "$xlib:$ENV{'MOTIFHOME'}:$ENV{'LD_LIBRARY_PATH'}";
    } else {
	$LD_LIBRARY_PATH = "$xlib:$ENV{'MOTIFHOME'}";
    }
}

sub setup_sgi {
    $ENV{'MOTIFHOME'} = '/usr/lib';

    if (!defined $ENV{'MOTIFINC'}) {
	$ENV{'MOTIFINC'} = '/usr/include';
    }
    if (defined $ENV{'LD_LIBRARY_PATH'}) { 
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}:$ENV{'LD_LIBRARY_PATH'}";
    } else {
	$LD_LIBRARY_PATH = "$ENV{'MOTIFHOME'}";
    }
}


# "Export" them to the environment.

# There is no need for these outside perl, right?
# $ENV{'TMP'} = $TMP;
# $ENV{'OS'} = $OS;
$ENV{'MACHINETYPE'} = $MACHINETYPE;
$ENV{'objdir'} = $objdir;
$ENV{'LD_LIBRARY_PATH'} = $LD_LIBRARY_PATH if (defined $LD_LIBRARY_PATH);
$ENV{'LD_RUN_PATH'} = $LD_RUN_PATH if (defined $LD_RUN_PATH);


1;
