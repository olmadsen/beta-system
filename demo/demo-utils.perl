#!/usr/local/bin/perl -s

### Main

use Cwd;

undef %progs;
undef %status;
undef @dirstack;
undef @matchlist;


sub usage(){
    print "Usage:\n";
    print "perl -s run.demos [-h] [-c] [-j] [-d] [dir1] ... [dirN]\n";
    print "  -h  print this help\n";
    print "  -v  verbose mode\n";
    print "  -O  do not display correct outputs, only errors\n";
    print "  -p  preserve executables after execution\n";
    print "  -P  no disassembly for JVM\n";
    print "  -c  skip compilation (run only)\n";
    print "  -R  Remove all code for target from entire BETALIB before compilation\n";
    print "  -C  Force removal of all generated files after run (output, diff, ...)\n";
    print "  -S  Skip print of summary at end (still available in file)\n";
    print "  -X  clean directory for generated files without running demos\n";
    print "  -d  target clr (.NET bytecode)\n";
    print "  -j  target jvm (Java bytecode)\n";
    print "  [dir1] ... [dirN] specify optional directories to test (ignoring others)\n";
    print "\n";
    print "Example run.demos:\n";
    print '  push (@INC, "$ENV{\'BETALIB\'}/demo");' . "\n";
    print '  do "demo-utils.perl";' . "\n";
    print '  &setup_demo_run();' . "\n";
    print '  &run_demo("subdir", "programname", "arg1 arg2");' . "\n";
    print '  &complete_demo_run();' . "\n";
    exit;
}

sub read_command_options()
{
    &usage()              if (defined($h));
    $target       = "clr" if (defined($d));
    $target       = "jvm" if (defined($j));
    $skip_compile = 1     if (defined($c));
    $preserve     = 1     if (defined($p));
    $verbose      = 1     if (defined($v));
    $skipoutput   = 1     if (defined($O));
    $nodisassembly= 1     if (defined($P));
    $rmcode       = 1     if (defined($R));
    $forceclean   = 1     if (defined($C));
    $cleanall     = 1     if (defined($X));
    $printsummary = 1;
    $printsummary = 0     if (defined($S));

    if ($#ARGV>=0){
	print "Only testing directories matching: " . join (" ", @ARGV) . "\n";
	@matchlist = @ARGV;
    }

    $this = cwd;
    $this =~ s%/$%%;
    $this =~ s%/demo$%%;
    $this =~ s%^.*/%%;
    
};

sub inMatchList()
{
    local ($dir) = @_;
    return 1 if (! defined(@matchlist));
    foreach $m (@matchlist){
	return 1 if ($dir =~ $m);
    }
    return 0;
}

sub findprogs
# find all .bet files in dir and
# record all corresponding programs in %progs
{
    my ($dir) = @_;
    my @subdirs;
    opendir (DIR, $dir) || die "Unable to readdir $dir: $!";
    foreach (readdir(DIR)) {
	next if (/^\.$/);
	next if (/^\.\.$/);
	if (/\.bet$/){
	    # found a .bet file
	    local $prog = $`;
	    if ((-f "$dir/$prog") || (-f "$dir/$prog.exe")){
		&register_prog_status($dir, $prog, 999);
	    } else {
		&register_prog_status($dir, $prog, undef);
	    }
	} elsif (-d $_){
	    push (@subdirs, $_);
	}
    }
    close(DIR);
    foreach $sub (@subdirs){
	&findprogs("$dir/$sub");
    }
}

sub print_status()
{
    my ($status, $msg, $prog) = @_;
    print SUMMARY sprintf("%-7s",$status) . " : " . sprintf("%-40s",$msg) . " : " . $prog . "\n";
}

sub print_summary
{
    open SUMMARY, ">run.demos.$target.summary";

    print SUMMARY "\n$this run.demos status ($target):\n";
    print SUMMARY "=================================\n";
    if (defined(@matchlist)){
	print SUMMARY "[Only tested directories matching: " . join (" ", @ARGV) . "]\n";
    }
    foreach $prog (sort keys %progs){
	$status = &get_prog_status($prog);
	if (! defined($status)){
	    &print_status("CHECK", "Not a program file (or not compiled)", $prog);
	} elsif ($status==999){
	    &print_status("CHECK", "Program not attempted run", $prog);
	} elsif ($status==111){
	    &print_status("ok", "Program explicitly ignored", $prog);
	} elsif ($status==222){
	    # implicitly ignored
	} elsif ($status==0){
	    local $exec_status = $status{&trim_path($prog)};
	    if ($exec_status==1){
		&print_status("ok", "Program tested ok", $prog);
	    } elsif ($exec_status==0){
		&print_status("DIFF", "Program ran ok, but with wrong output", $prog);
	    } else {
		&print_status("CHECK", "Program ran ok, but output not tested", $prog);
	    }
	} else {
	    if (-f "$prog"){
		&print_status("ERROR", "Program ran with error ($status)", $prog);
	    } else {
		&print_status("ERROR", "Program not compiled", $prog);
	    }
	}
    }
    print "\n";

    close SUMMARY;

    if ($printsummary){
	&cat("run.demos.$target.summary");
	print "\n[This summary available in file run.demos.$target.summary]\n";
    } else {
	print "\nSummary available in file run.demos.$target.summary\n";
    }
}
   
sub expand_envvar
{
    my ($var) = @_;
    return $ENV{$var} if (defined($ENV{$var}));
    print "Warning: environment variable not defined: $var\n";
}

sub cleanup()
{
    my ($prog) = @_;
    my @files = ("$prog.dump", "$prog.run", "$prog.out", "$prog.ref", "$prog.diff");
    foreach $f (@files){
	#print "  cleanup: $f\n";
	if (-e $f){
	    print "Removing $f\n" if ($verbose);
	    unlink $f;
	}
    }
}

sub cleanup_exec()
{
    my ($prog) = @_;
    my @files = ("$prog", "$prog-jdb");
    foreach $f (@files){
	#print "  cleanup_exec: $f\n";
	if (-e $f){
	    if ($preserve){
		print "Preserving $f (run.demos -p)\n" if ($verbose);
	    } else {
		print "Removing $f\n" if ($verbose);
		unlink $f;
	    }
	}
    }
}

sub cleanup_all
{
    local($all) = 0;
    foreach $prog (sort keys %progs){
	#print "   clean: $prog\n";
	&cleanup($prog);
	&cleanup_exec($prog);
    }
    foreach $summary (glob("*.summary"), glob("*.dump"), glob("*/*.dump")){
	print "Removing $summary\n" if ($verbose);
	unlink $summary;
    }
}

sub compare_expected()
{
    local ($dir, $exec) = @_;
    local $prog = ($dir eq ".")? "$exec" : "$dir/$exec";

    if (! -f "$prog.run"){
	print "$prog.run does not exist - program not executed? (probably compile error)\n";
	return;
    }
    open(IN, "<$prog.run") || die "Unable to read raw output $prog.run: $!";
    open(OUT, ">$prog.out") || die "Unable to write processed output $prog.out: $!";
    while(<IN>) {
	s/\015$//;
	print OUT;
    }
    close IN;
    close OUT;
    if (! -d "reference"){
	print "['reference' directory does not exist. Now creating it.]\n";
	mkdir "reference", 0775 || die "Cannot create directory 'reference': $!";
	print "[Please do a manual 'cvs add reference']\n";
    }
    if ( -f "reference/$exec.run" ){
	open(IN, "<reference/$exec.run") || die "Unable to read reference output reference/$exec.run: $!";
	open(OUT, ">$prog.ref") || die "Unable to write processed reference output $prog.ref: $!";
	while(<IN>) {
	    s/\015$//;
	    s/\$\{(\w+)\}/expand_envvar($1)/ge;
	    print OUT;
	}
	close IN;
	close OUT;
	if (system("diff $diffoptions $prog.ref $prog.out") == 0){
	    print "[output is correct]\n";
	    &cleanup($prog);
	    &cleanup_exec($prog);
	    $status{$prog} = 1;
	} else {
	    if ($forceclean){
		&cleanup($prog);
		&cleanup_exec($prog);
		print "[Difference in output]\n";
	    } else {
		# Save diff file for easy lookup
		system "diff $diffoptions $prog.ref $prog.out > $prog.diff";
		print "[Difference in output - see $prog.diff]\n";
	    }
	    $status{$prog} = 0;
	}
    } else {
	system "mv $prog.run reference/$exec.run";
	print "[No reference existed. $exec.run used for future reference]\n";
	print "[Please do a manual 'cvs add reference/$exec.run']\n";
	$status{$prog} = 2;
    }
}

sub declare_success()
{
    local ($dir, $exec) = @_;
    $progs{&trim_path("$dir/$exec")} = 0;
    $status{&trim_path("$dir/$exec")} = 1;
}
    

sub find_local_progs()
{
    undef %progs;
    &findprogs('.');
    if (scalar(keys %progs) == 0){
	print "Warning: no .bet files found!\n";
    }
}

sub init()
{
    &read_command_options();
    &find_local_progs();
    &setup_variables();
    if ($cleanall){
	print "***Cleaning local directory.\n";
	&cleanup_all();
	exit 0;
    }
    open(STDERR, ">&STDOUT") || die "Can't dup stdout";
    select(STDERR); $| = 1;       # make unbuffered
    select(STDOUT); $| = 1;       # make unbuffered
}

sub rmcode(){
    return unless ($rmcode);
    print "Removing all code for target $target from $betalib ...";
    if ($verbose){
	print "\n";
	system "mbs_rmcode -u -v $target";
    } else {
	system "mbs_rmcode -u $target > rmcode.out";
	unlink "rmcode.out";
    }
    print "\n";
}

sub setup_demo_run
{
    &init();

    if ($verbose){
	print( "Testing demos against reference output in directory 'reference'\n");
	print  "BETALIB: $betalib\n";
	print  "Platform: $target\n";
	print  "Compiling with command: " . &compile_command() . "\n";
    }
    &rmcode();
}

sub setup_graphics_demo_run
{
    &init();
    &rmcode();
}

sub complete_demo_run()
{
    &print_summary();
}

sub complete_graphics_demo_run()
{
    &complete_demo_run()
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
    # delete initial /
    $path =~ s%^/%%;
    return $path;
}

sub stripcounter()
{
    my ($exec) = @_;
    $exec =~ s/\[(\d+)\]//;
    return $exec;
}

sub pushd()
{
    local ($dir) = @_;
    push @dirstack, cwd;
    chdir $dir || die "pushd: cannot chdir to $dir: $!\n";
}

sub popd()
{
    if (scalar @dirstack){ 
	chdir pop @dirstack;
    } else {
	die "popd: directory stack empty\n";
    }
}

sub register_prog_status()
{
    local ($dir, $exec, $status) = @_;
    local $prog = &trim_path("$dir/$exec");
    $progs{$prog}=$status;
    #print "register_prog_status: $prog: $status\n";
    local $baseprog = &stripcounter($prog);
    if (($baseprog ne $prog) && (!defined($progs{$baseprog}))){
	# base program not attempted run
	# print "register_prog_status: base: $baseprog: 222\n";
	$progs{$baseprog} = 222; # set to implicitly ignore
    }
}
sub get_prog_status()
{
    local ($prog) = @_;
    #print "get_prog_status: " . &trim_path($prog) . ": " . $progs{&trim_path($prog)} . "\n";
    return $progs{&trim_path($prog)};
}

sub check_compiled()
{
    local ($dir, $exec) = @_;
    if (&get_prog_status(&trim_path("$dir/$exec")) != 999){
	print "[" . &trim_path("$dir/$exec") . " did not compile into an executable.\n";
	print " - probably a library file (or a compile(r) error)].\n";
	return 0;
    }
    return 1;
}

sub run_demo
{
    # If $exec is of the form 'foo[1]' the executable will be expected to be
    # foo and the '[1]' just used to distinguish multiple executions.
    
    my ($dir, $exec, $args) = @_;

    $dir = '.' if ($dir eq "");
    if (!&inMatchList($dir)){
	&register_prog_status($dir, $exec, 222); #implicit ignore;
	return;
    }
    if (!-d $dir){
	print "\nrun_demo(\"" . join('", "', @_) . "\"): $dir is not a directory\n";
	exit 1;
    }
    &compile_demo($dir, $exec);
    return if (!&check_compiled($dir, $exec));
    &pushd($dir);
    &cleanup($exec);
    print "-"x10 . "Executing " . &trim_path("$dir/$exec") . "-"x10  . "\n"; 
    system "./$exec $args > $exec.run 2>&1";
    &register_prog_status($dir, $exec, $?);

    &cat("$exec.run") unless ($skipoutput);
    
    &popd();
    &compare_expected($dir, $exec);

}

sub write_to_demo
{
    my ($dir, $exec, $args, @inputlines) = @_;

    $dir = '.' if ($dir eq "");
        if (!&inMatchList($dir)){
	&register_prog_status($dir, $exec, 222); #implicit ignore;
	return;
    }
    if (!-d $dir){
	print "\nwrite_to_demo(\"" . join('", "', @_) . "\"): $dir is not a directory\n";
	exit 1;
    }

    &compile_demo($dir, $exec);
    return if (!&check_compiled($dir, $exec));    
    &pushd("$dir");
    &cleanup($exec);
    print "-"x10 . "Executing " . &trim_path("$dir/$exec") . " with input" . "-"x10  . "\n";
    open(SAVEOUT, ">&STDOUT");
    select(SAVEOUT); $| = 1;       # make unbuffered
    open(STDOUT, ">$exec.run") || die "Can't redirect stdout";
    select(STDOUT); $| = 1;       # make unbuffered
    open (EXEC, "| $exec $args");
    foreach $input (@inputlines){
	print EXEC $input;
    }
    close EXEC;
    close(STDOUT);
    &register_prog_status($dir, $exec, $?);
    open(STDOUT, ">&SAVEOUT");

    &cat("$exec.run") unless ($skipoutput);

    &popd();
    &compare_expected($dir, $exec);
    
}

sub ignore()
{
    my ($dir, $exec) = @_;
    if (&inMatchList($dir)){
	&register_prog_status($dir, $exec, 111); #explicit ignore;
    } else {
	&register_prog_status($dir, $exec, 222); #implicit ignore;
    }
}

sub ignore_completely()
{
    my ($dir, $exec) = @_;
    &register_prog_status($dir, $exec, 222);
}

sub compile_command()
{
    my $compilecmd;
    if ($target eq "jvm"){
	$compilecmd = "jbeta -s 188";
	$compilecmd .= " -p" unless ($nodisassembly);
    } elsif ($target eq "clr"){
	$compilecmd = "nbeta";
    } else {
	$compilecmd = "beta";
    } 
    return $compilecmd;
}

sub compile_demo()
{
    my ($dir, $f) = @_;
    return if ($skip_compile);
    $dir = "." if ($dir eq "");
    my $compilecmd = &compile_command();
    print "-"x10 . "Compiling " . &trim_path("$dir/$f") . "-"x10  . "\n"; 
    &pushd($dir);
    my $base = &stripcounter($f);
    if ($base ne $f){
	$compilecmd .= " -o $f $base";
    } else {
	$compilecmd .= " $base";
    }
    if ($verbose){
	print  "$compilecmd\n";
	system "$compilecmd";
    } else {
	system "$compilecmd > $f.out 2>&1";
    }
    &popd();
    if ((-f &trim_path("$dir/$f")) || (-f &trim_path("$dir/$f.exe"))){
	#print "Setting status of $dir/$f to 999\n";
	&register_prog_status($dir, $f, 999);
    }
}

sub run_all_demos
# find all .bet files in current directory and
# run all corresponding programs
{
    local($all) = 0;
    foreach $prog (sort keys %progs){
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
	    local ($dir, ,$numdirs, $program);
	    if ($prog =~ m%/([^/]+)$%){
		$program = $1;
		$dir = $`;
	    } else {
		$program = $prog;
		$numdirs = 0;
		$dir = ".";
	    }
	    &run_demo($dir, $program, "");
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
	if ($mach =~ /^Power Macintosh/) {
	    $objdir = 'macosx';
	} elsif ($mach =~ /^sun4/) {
	    $objdir = 'sun4s';
	} elsif ($mach =~ /^i.86/) {
	    $objdir = 'linux';
	    $ast = "astL";
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
    $target     = $objdir unless defined($target);
    $isByteCode = ($target eq "clr" || $target eq "jvm");
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

sub touch ()
{
    local ($time, $entry) = @_;
    if (! -e $entry){
	open E, ">$entry" || die "touch: cannot create $entry: $!\n";
	close E;
    }
    if ($time==0){ $time = time; }
    utime $time, $time, $entry;
}

sub IntHandler 
{
    local ($answer);
    print "\nrun.demos interrupted. Quit? (n/y) ";
    $answer=<STDIN>;
    chop $answer;
    if ($answer eq "y"){
	print("run.demos interrupted\n");
	&print_summary();
	exit(0);
    } else {
	print "Please answer question asked before interrupt: ";
    }
}

return 1;
