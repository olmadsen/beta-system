#! /usr/local/bin/perl5

# betawc wrapper script. 
# Written by Morten Grouleff Aug 96, based on the nonportable betawc.sh

$betalib = ($ENV{'BETALIB'} || '/usr/local/beta/bin');

# FINAL: require "$betalib/configuration/env.perl5";
# Experimental:
require "/users/grouleff/Beta/env.perl5";

$BETAWC  = "$betalib/betawc/v1.1/$objdir/betawc";
if ( !-x $BETAWC) {
    print "$0: Unable to exec '$BETAWC'\n";
    exit 1;
}

$tmp = ($ENV{'TMP'} || $ENV{'TMP'} || '/tmp');
chop $tmp if ($tmp =~ /\/$/);	# remove trailing slash.
if (!-d $tmp) {
    print "Unable to verify exsistance of temporary directory: \"$tmp\"\n";
    &Usage;
}


sub Usage {
    print "\n";
    print "Usage: $0 [options] file [options]\n";
    print "      file:          name of fragment to analyse\n";
    print "Known options are:\n";
    print "   -a --all:         same as --conflict --full --list\n";
    print "   -c --conflict:    check for conflicts\n";
    print "   -f --full:        include standard files\n";
    print "                        (files located in $betalib)\n";
    print "   -x --exclude str: exclude all files containing str\n";
    print "                         Note, that str may be any egrep pattern\n";
    print "   -i --include str: include all files containing str\n";
    print "                         Note, that str may be any egrep pattern\n";
    print "   -l --list:        list the fragment groups in the dependency graph.\n";
    print "   -h --help:        prints this text\n";
    exit 1;
}


&Usage if ($#ARGV == -1);		# Quit if no args.

undef $file;
undef $exclude;
undef $include;
$doConflict = 0;		 
$doFull=0;			
$doList=0;


while ($_ = shift @ARGV) {
    undef $opt; undef $arg;
    if (/^--(\S)$/) {	# --option
	$opt = $1;
    } elsif (/^-(.)$/) {
	$opt = $1;
    } elsif (!defined $file) {
	$file = $_;
    } else {
	print "$0: Only one file-arg is allowed.\n(Unable to parse \"$_\")\n";
	exit 1;
    }
    
    if (defined $opt) {
	if ($opt eq 'all' || $opt eq 'a') {
	    $doConflict=1; $doFull=1; $doList=1;
	} elsif ($opt eq 'conflict' || $opt eq 'c') {
	    $doConflict=1;
	} elsif ($opt eq 'exclude' || $opt eq 'x') {
	    $arg = shift @ARGV;
	    if ($arg =~ /^-/) {
		print "$0: Warning: pattern for exclude begins with '-'\n";
	    }
	    if (defined $exclude) {    
		$exclude="($exclude)|($arg)";
	    } else {
		$exclude=$arg;
	    }
	} elsif ($opt eq 'include' || $opt eq 'i') {
	    $arg = shift @ARGV;
	    if ($arg =~ /^-/) {
		print "$0: Warning: pattern for include begins with '-'\n";
	    }
	    if (defined $include) {    
		$include="($include)|($arg)";
	    } else {
		$include=$arg;
	    }
	} elsif ($opt eq 'list' || $opt eq 'l') {
	    $doList=1;
	} elsif ($opt eq 'help' || $opt eq 'h') {
	    &Usage;
	} else {		
	    print "$0: Unknown option: \"$opt\"\n";
	    exit 1;			
	}
    }
}

&Usage if (!defined $file);

$file =~ s/\\/\//;		# '\' to '/'
if ($file =~ /^(.*\/)?([^\/]+)$/) {
    $dir = $1;
    $name = $2;
    if ($name =~ /^(.*)(\.[^\.]+)$/) {
	$name = $1;
	$ext = $2;
    } else {
	undef $ext;
    }
    $root = "$dir$name";
} else {
    print "Unable to parse filename \"$file\"\n";
    exit 1;
}


if (!-r "$root.bet" && !-r "$root.ast" && !-r "$root.atsL") {
    print "$0: no fragment file: $root\n";
    &Usage;
}

print "\nAnalysis of fragment: $root\n";

$tmp0 = "$tmp/betawc0.$$";
$tmp1 = "$tmp/betawc1.$$";

system $BETAWC, $file, $tmp1, $tmp0;

if (-s $tmp0) {
    if ($doConflict) {
	open (IN, $tmp0) || die "$!\n";
	print <IN>;
	close IN;
    } else {
	print "  --- NOTE: version conflicts.\n";
	print "  --- Use '--conflict' to obtain more detailed info.\n";
    }
} elsif ($doConflict) {
    print "\nNo version conflicts\n";
}


open (IN, $tmp1) || die "Unable to open $tmp1: $!\n";
@fragmentfiles = <IN>;
close IN;

foreach (@fragmentfiles) {
    ($path,$version,$rest) = split;
    if ($version ne '.') {
	push @libs, "$rest $version $path\n";
    }
}


@libs = sort @libs;		# Case-sensitive sort!

print "\nLibraries used:\n";

undef %unique;
foreach (@libs) {
    ($path,$version,$rest) = split;
    if (!defined $unique{$path}) {
	$unique{$path} = 1;
	printf "  %-15s %-10s (%s/%s/%s)\n", $path, $version, $rest, $path, $version;
    }
}

foreach (@fragmentfiles) {
    ($a,$b,$c,$d,$e) = split;
    if ($b eq '.') {
	push @tmp2a, "$a/$d.bet $e\n";
    } else {
	push @tmp2a, "$a/$c/$b/$d.bet $e\n";
    }
}


undef %unique;
foreach (@tmp2a) {
    ($a,$b) = split;
    if (!defined $unique{$a}) {
	$unique{$a} = 1;
	push @tmp2, $_;
    }
}

undef @tmp2a;			# free mem.
@tmp2 = sort @tmp2;		# Case-sensitive sort!

($betalibexp = $betalib) =~ s/(\W)/\\$1/g; # Quote metachars.

@tmp3 = @tmp2;
if (!$doFull) {
    $tmp5 = "  EXCLUDED: Libraries with $betalib/\n";
    $tmp5 .= "            in the beginning of their path\n";
    
    @tmp3 = grep {!/((^$betalibexp)|(^\~beta)|(^\/users\/beta))/} @tmp2;
}

@tmp3 =~ s/\~beta/$betalibexp/g;
@tmp3 =~ s/\/users\/beta/$betalibexp/g;

if (defined $exclude) {
    $tmp5 .= "  EXCLUDED: Libraries with '$exclude'\n";
    $tmp5 .= "            in their path\n";
    @tmp4 = grep {!/$exclude/} @tmp3;
} else {
    @tmp4 = @tmp3;
}

if (defined $include) {
    $tmp5 .= "  INCLUDED: Libraries with '$include'\n";
    $tmp5 .= "            in their path\n";
    push (@tmp4, grep {/$include/} @tmp2);
}

if (defined $tmp5) {
    print "\n--------------------------------------------\n"; 
    print " The following information is based on the  \n";
    print " entire dependency graph with the following \n";
    print " exceptions:                                \n";
    print $tmp5;
    print "--------------------------------------------\n"; 
}

$sum = 0;
foreach (@tmp4) {
    ($a,$b,$c) = split;
    $sum += $b;
}

print "\nNumber of:\n";
printf "  Fragment groups: %8d\n", $#tmp4 + 1;
printf "  Fragment forms:  %8d\n", $sum;

$chars = 0; $words=0; $lines=0;
foreach (@tmp4) {
    ($a,$b) = split;
    $chars += -s $a;
    open (IN, $a);
    foreach (<IN>) {
	$lines++;
	$words += split;
    }
}

printf "  Lines:           %8d\n", $lines;
printf "  Words:           %8d\n", $words;
printf "  Chars:           %8d\n", $chars;

if ($doList) {
    print "\nList of fragment groups:\n";
    print "--------------------------------------------\n";

    foreach (@tmp4) {
	($a,$b) = split;
	print "  $a\n";
    }
}
