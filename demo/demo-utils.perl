#!/usr/local/bin/perl -s

### Main

undef %progs;
undef @dirs;

if (defined($c)){
    # run.demos -c
    &compile_all_demos();
}

sub findprogs
# find all .bet files in dir and
# record all corresponding programs in %progs
{
    my ($dir) = @_;
    my (@subdirs);
    undef @subdirs;
    opendir (DIR, $dir) || die "Unable to readdir $dir: $!";
    foreach (readdir(DIR)) {
	next if (/^\.$/);
	next if (/^\.\.$/);
	if (/\.bet$/){
	    # found a .bet file
	    $prog = "$dir/$`";
	    #print $prog . "\n";
	    if ((-f "$prog") || (-f "$prog.exe")){
		$progs{&trim_path($prog)} = 999;
	    } else {
		$progs{&trim_path($prog)} = undef;
	    }
	} elsif (-d $_){
	    push (@dirs, "$dir/$_");
	    push (@subdirs, $_);
	}
    }
    close(DIR);
    foreach $sub (@subdirs){
	&findprogs("$dir/$sub");
    }
}

sub checkprogs
# check that all programs in %progs have been executed
{
    print "\nProgram run status:\n";
    print "====================\n";
    foreach $prog (sort keys %progs){
	if (!defined $progs{$prog}){
	    print "CHECK: Not a program file (or not compiled): $prog.bet\n";
	} elsif ($progs{$prog}==999){
	    print "CHECK: program not attempted run: $prog\n";
	} elsif ($progs{$prog}==0){
	    print "ok   : program tested ok: $prog\n";
	} else {
	    if (-f "$prog"){
		print "ERROR: Program run with error: $prog (exit $progs{$prog})\n";
	    } else {
		print "ERROR: Program not compiled: $prog\n";
	    }
	}
    }
}

sub read_default
# read run.default to run.def while expanding environment variables.
{
    open(IN, "<run.default") || die "cannot open run.default: $!\n";
    open(OUT, ">run.def") || die "cannot open run.def: $!\n";
    while(<IN>) {
	s/\$\{(\w+)\}/expand_envvar($1)/ge;
	print OUT;
    }
    close IN;
    close OUT;
}
    
sub expand_envvar
{
    my ($var) = @_;
    return $ENV{$var} if (defined($ENV{$var}));
    print SAVEERR "Warning: environment variable not defined: $var\n";
}

sub compare_output
{
    if ( -f "run.default"){
	print("Comparing run.default with run.out\n");
	&read_default();
	if (system("diff run.def run.out") == 0){
	    print "[No differences]\n";
	    unlink "run.out";
	    unlink "run.def";
	} else {
	    print "[Differences found]\n";
	}
    } else {
	print("Renaming run.out to run.default\n");
	rename("run.out","run.default");
    }
}

sub setup_demo_run
{

    undef %progs;
    &findprogs('.');
    if (scalar(keys %progs) == 0){
	print "Warning: no .bet files found!\n";
    }

    &setup_variables();

    unlink "run.def";

    open(SAVEOUT, ">&STDOUT");
    open(SAVEERR, ">&STDERR");
    
    select(SAVEERR); $| = 1;       # make unbuffered
    select(SAVEOUT); $| = 1;       # make unbuffered
 
    open(STDOUT, ">run.out") || die "Can't redirect stdout";
    open(STDERR, ">&STDOUT") || die "Can't dup stdout";
    
    select(STDERR); $| = 1;       # make unbuffered
    select(STDOUT); $| = 1;       # make unbuffered
    
    print(SAVEOUT "Running demos with output to file run.out\n");
    print SAVEOUT "BETALIB: $betalib\n";
    print SAVEOUT "Platform: $objdir\n";
}

sub setup_graphics_demo_run
{
    undef %progs;
    &findprogs('.');
    if (scalar(keys %progs) == 0){
	print "Warning: no .bet files found!\n";
    }
    
    &setup_variables();
    
    unlink "run.def";

    open(STDERR, ">&STDOUT") || die "Can't dup stdout";
    select(STDERR); $| = 1;       # make unbuffered
    select(STDOUT); $| = 1;       # make unbuffered

    print(SAVEOUT "Running demos with output to file run.out\n");
}

sub complete_demo_run()
{
    print(SAVEOUT "\nRun done\n");

    close(STDOUT);
    close(STDERR);
    
    open(STDOUT, ">&SAVEOUT");
    open(STDERR, ">&SAVEERR");
    
    &compare_output();
    &checkprogs();
}

sub complete_graphics_demo_run()
{
    print("Run done\n");
    &checkprogs();
}

sub trim_path
{
    local ($path) = @_;
    # delete double slashes
    $path =~ s%//+%/%g;
    # delete trailing slash
    $path =~ s%/$%%;
    # delete initial ./
    $path =~ s%^\./%%;
    return $path;
}

sub countdirs
{
    local ($path) = @_;
    local $numdirs = 0;
    $path = &trim_path($path);
    $path =~ s%/%$numdirs++%ge;
    #print STDERR "numdirs($path)=$numdirs\n";
    return $numdirs;
}

sub run_demo
{
    my ($dir, $prog, $args) = @_;

    $dir = '.' if ($dir eq "");
    if (!-d $dir){
	print SAVEOUT "\nrun_demo(\"" . join('", "', @_) . "\"): $dir is not a directory\n";
	exit 1;
    }
    my ($numdirs) = &countdirs("$dir/$prog");

    print "\n";
    chdir "$dir" || die "cannot chdir($dir): $!\n";
    print "############# Running $prog\n";
    print SAVEOUT ".";
    system("$prog $args");
    $progs{&trim_path("$dir/$prog")}=$?;
    chdir ("../" x $numdirs) if ($numdirs>0);

}

sub write_to_demo
{
    my ($dir, $prog, $args, @inputlines) = @_;

    $dir = '.' if ($dir eq "");
    if (!-d $dir){
	print SAVEOUT "\nwrite_to_demo(\"" . join('", "', @_) . "\"): $dir is not a directory\n";
	exit 1;
    }
    my ($numdirs) = &countdirs("$dir/$prog");

    print "\n";
    chdir "$dir" || die "cannot chdir($dir): $!\n";
    print "############# Running $prog\n";
    print SAVEOUT ".";
    open (EXEC, "| $prog $args");
    foreach $input (@inputlines){
	print EXEC $input;
    }
    close EXEC;
    $progs{&trim_path("$dir/$prog")}=$?;
    chdir ("../" x $numdirs) if ($numdirs>0);

}

sub compile_all_demos
# find all .bet files in current directory and
# attempt to compile them
{
    undef %progs;
    &findprogs('.');
    #print "keys: \n" . join("\n", keys %progs) . "\n";
    #print "sort: \n" . join("\n", sort keys %progs) . "\n";
    print "############# Compiling all .bet files recursively\n";
    if (scalar(keys %progs) == 0){
	print "Warning: no .bet files found!\n";
    }
    system "beta -qw " . join(' ', sort keys %progs);
    undef %progs;
}

sub run_all_demos
# find all .bet files in current directory and
# run all corresponding programs
{
    local($all) =0;
    undef %progs;
    &findprogs('.');
    if (length(keys %progs) == 0){
	print "Warning: no .bet files found!\n";
    }
    #print "keys: \n" . join("\n", keys %progs) . "\n";
    #print "sort: \n" . join("\n", sort keys %progs) . "\n";
    foreach $prog (sort keys %progs){
	next if ($progs{$prog}!=999);
	if (!$all) {
	    while (1){
		print "Do you want to execute $prog? (n/y/q/a/?) ";
		$answer=<STDIN>;
		chop $answer;
		if ($answer eq "?"){
		    print " n  - no:   Do not execute this program (default)\n";
		    print " y  - yes:  Execute this program\n";
		    print " q  - quit\n";
		    print " a  - all:  Execute all remaining programs\n";
		    print " ?  - help: Display this help\n";
		} else {
		    if ($answer eq "a") {
			$all=1;
			$answer = "y";
		    }
		    last;
		}
	    };
	} else {
	    $answer="y";
	}
	if ($answer eq "n") {
	    next;
	} elsif ($answer eq "y") {
	    $prog = &trim_path("$prog");
	    print "############# Running $prog\n";
	    local ($dir, ,$numdirs, $program);
	    if ($prog =~ m%/([^/]+)$%){
		$program = $1;
		$dir = $`;
		$numdirs = &countdirs($prog);
		#print "chdir($dir)\n";
		chdir "$dir" || die "cannot chdir($dir): $!\n";
	    } else {
		$program = $prog;
		$numdirs = 0;
	    }
	    system("$program");
	    $progs{$prog}=$?;
	    #print "chdir (" . "../" x $numdirs . ")\n" if ($numdirs>0);
	    chdir ("../" x $numdirs) if ($numdirs>0);
	} elsif ($answer eq "q") {
	    return;
	} else {
	    next;
	} 
    }
}

sub setup_variables
# Cut-down version of BETALIB/bin/admin/env.perl
{
    $SIG{'INT'}  = 'IntHandler';

    $|=1;
    
    # Add . to your path, since a lot of stuff doesn't otherwise work
    $ENV{"PATH"} = ".:" . $ENV{"PATH"};
    $betalib = $ENV{'BETALIB'};
    
    if (-e "c:\\") {
	$OS = "WIN";
	$ast = "astL";
	$betalib =~ s#\\#/#g;
	if ($ENV{'MIASDK'} =~ /^(ms|bor|gnu)$/i) {
	    $MIASDK = $1;
	    $MACHINETYPE = "\UNTI_$MIASDK";
	    $objdir = "\L$MACHINETYPE";
	} else {
	    print "MIASDK not set, giving up\n";
	    exit 1;
	}
    } elsif (-e "/etc") {
	# UNIX
	$OS = "UNIX";
	$ast = "ast";
	$mach = `uname -m`;
	$rev  = `uname -r`;
	if ($mach =~ /^sun4/) {
	    $objdir = 'sun4s';
	} elsif ($mach =~ /^9000\/7../) {
	    $objdir = 'hpux9pa';
	} elsif ($mach =~ /^i.86/) {
	    $objdir = 'linux';
	    $ast = "astL";
	} elsif ($mach =~ /^IP\d+/) {
	    local $lib = $ENV{'LD_LIBRARY_PATH'};
	    $objdir = 'sgi';
	    $lib .= ":" if ($lib ne "");
	    $lib .= "$betalib/lib/sgi";
	    foreach $s (@dirs){
		# temporary hack for compile bug
	    	$lib .= ":../$s/sgi";
	    }
	    $lib .= ":./sgi";
	    $ENV{'LD_LIBRARY_PATH'} = $lib;
	    #print "LD_LIBRARY_PATH set to\n\t$lib\n";
	} elsif ($mach =~ /^i86pc$/) {
	    $objdir = 'sol_x86';
	    $ast = "astL";
	} else {
	    print "Unknown/unsupported architecture.\n";
	    exit 1;
	}
    } else {
	# Macintosh
	$OS = "MAC";
	$objdir='ppcmac';
    }
    $ENV{'objdir'} = $objdir;
    $ENV{'OS'}     = $OS;
}

sub unlink_recursive()
{
    my ($dir) = @_;
    my (@subdirs);
    undef @subdirs;
    return if (!-e $dir);
    if (!-d $dir){
	warn "unlink_recursive: not a directory: $dir\n";
	return;
    }
    opendir (DIR, $dir) || warn "unlink_recursive: unable to readdir $dir: $!\n";
    foreach (readdir(DIR)) {
	next if (/^\.$/);
	next if (/^\.\.$/);
	if (-d "$dir/$_"){
	    #print "subdir: $dir/$_\n";
	    push (@subdirs, $_);
	} else {
	    #print "rm($dir/$_)\n";
	    unlink("$dir/$_") ||  warn "unlink_recursive: cannot remove file $dir/$_: $!\n";
	}
    }
    close(DIR);
    foreach $sub (@subdirs){
	#print "unlink_recursive($dir/$sub)\n";
	&unlink_recursive("$dir/$sub");
    }
    #print "rmdir($dir)\n";
    rmdir ($dir) || warn "unlink_recursive: cannot remove directory $dir: $!\n";
}

sub unlink_match()
{
    my (@patterns) = @_;
    opendir (DIR, ".") || warn "unlink_match: unable to readdir $dir: $!\n";
    foreach $entry (readdir(DIR)) {
	#print "unlink_match: found entry $entry\n";
	next if ($entry =~ /^\.$/);
	next if ($entry =~ /^\.\.$/);
	foreach $pattern (@patterns){
	    #$pattern =~ s/(\W)/\\$1/g;
	    $pattern .= '$';
	    #print "unlink_match: compare $entry and $pattern\n";
	    if ($entry =~ m%$pattern%){
		# $entry must be removed
		if (-d $entry){
		    #print "unlink_recursive($entry)\n";
		    &unlink_recursive($entry);
		} else {
		    #print "rm($entry)\n";
		    unlink ($entry) || warn "unlink_match: cannot remove $entry: $!\n";
		}
	    }
	}
    }
    close(DIR);
}

sub cat()
{
    my ($file) = @_;
    if (! open FILE, "$file"){
	warn "cat: cannot open $file for reading: $!\n";
	return;
    }
    while (<FILE>) { print; };
    close FILE;
}

sub cp()
{
    my ($file1, $file2) = @_;
    if (! open FILE1, "$file1"){
	warn "cp: cannot open $file1 for reading: $!\n";
	return;
    }
    if (! open FILE2, ">$file2"){
	warn "cp: cannot open $file2 for writing: $!\n";
	close FILE1;
	return;
    }
    while (<FILE1>) { print FILE2; };
    close FILE1;
    close FILE2;
}

sub IntHandler 
{
    local ($answer);
    print "\nrun.demos interrupted. Quit? (n/y) ";
    $answer=<STDIN>;
    chop $answer;
    if ($answer eq "y"){
	print("run.demos interrupted\n");
	&checkprogs();
	exit(0);
    } else {
	print "Please answer question asked before interrupt: ";
    }
}

return 1;
