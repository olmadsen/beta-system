#!/usr/local/bin/perl -s

### Main

use Cwd;

undef %progs;
undef @dirstack;

sub usage(){
    print "Usage:\n";
    print "perl -s run.demos [-h] [-c] [-j] [-d]\n";
    print "  -h  print this help\n";
    print "  -v  verbose mode\n";
    print "  -O  do not display correct outputs, only errors\n";
    print "  -p  preserve executables after execution\n";
    print "  -P  no disassembly for JVM\n";
    print "  -c  skip compilation (run only)\n";
    print "  -R  Remove all code for target from entire BETALIB before compilation\n";
    print "  -d  target clr (.NET bytecode)\n";
    print "  -j  target jvm (Java bytecode)\n";
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
};

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
	    $prog = "$dir/$`";
	    #print $prog . "\n";
	    if ((-f "$prog") || (-f "$prog.exe")){
		$progs{&trim_path($prog)} = 999;
	    } else {
		$progs{&trim_path($prog)} = undef;
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
    print sprintf("%-7s",$status) . " : " . sprintf("%-40s",$msg) . " : " . $prog . "\n";
}

sub print_summary
{
    print "\nProgram run status ($target):\n";
    print "===============================\n";
    foreach $prog (sort keys %progs){
	if (!defined $progs{$prog}){
	    &print_status("CHECK", "Not a program file (or not compiled)", $prog);
	} elsif ($progs{$prog}==999){
	    &print_status("CHECK", "Program not attempted run", $prog);
	} elsif ($progs{$prog}==111){
	    &print_status("ok", "Program explicitly ignored", $prog);
	} elsif ($progs{$prog}==222){
	    # implicitly ignored
	} elsif ($progs{$prog}==0){
	    if ($status{$prog}==1){
		&print_status("ok", "Program tested ok", $prog);
	    } elsif ($status{$prog}==0){
		&print_status("DIFF", "Program ran ok, but with wrong output", $prog);
	    } else {
		&print_status("CHECK", "Program ran ok, but output not tested", $prog);
	    }
	} else {
	    if (-f "$prog"){
		&print_status("ERROR", "Program ran with error ($progs{$prog})", $prog);
	    } else {
		&print_status("ERROR", "Program not compiled", $prog);
	    }
	}
    }
    print "\n";
}
   
sub expand_envvar
{
    my ($var) = @_;
    return $ENV{$var} if (defined($ENV{$var}));
    print "Warning: environment variable not defined: $var\n";
}

sub compare_expected()
{
    local ($dir, $exec) = @_;
    local $prog = ($dir eq ".")? "$exec" : "$dir/$exec";

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
	    unlink "$prog.run", "$prog.out", "$prog.ref", "$prog.diff";
	    unlink &stripcounter("$prog.run"), &stripcounter("$prog.out");
	    unlink &stripcounter("$prog") unless ($preserve);
	    unlink &stripcounter("$prog")."-jdb" if ($target eq "jvm" && !$preserve);
	    $status{$prog} = 1;
	} else {
	    # Save diff file for easy lookup
	    system "diff $diffoptions $prog.ref $prog.out > $prog.diff";
	    print "[Difference in output - see $prog.diff]\n";
	    $status{$prog} = 0;
	}
    } else {
	system "mv $prog.run reference/$exec.run";
	print "[No reference existed. $exec.run used for future reference]\n";
	print "[Please do a manual 'cvs add reference/$exec.run']\n";
	$status{$prog} = 2;
    }
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

sub register_status()
{
    local ($dir, $exec, $status) = @_;
    local $prog = &trim_path("$dir/$exec");
    $progs{&trim_path($prog)}=$status;
    local $baseprog = &trim_path(&stripcounter($prog));
    if (! defined($progs{$baseprog})){
	# base program not attempted run
	$progs{$baseprog} = 222; # set to implicitly ignore
    }
}

sub run_demo
{
    # If $exec is of the form 'foo[1]' the executable will be expected to be
    # foo and the '[1]' just used to distinguish multiple executions.
    
    my ($dir, $exec, $args) = @_;

    $dir = '.' if ($dir eq "");
    if (!-d $dir){
	print "\nrun_demo(\"" . join('", "', @_) . "\"): $dir is not a directory\n";
	exit 1;
    }
    &compile_demo($dir, &stripcounter($exec));
    &pushd($dir);
    unlink "$exec.dump", "$exec.run", "$exec.out", "$exec.ref", "$exec.diff";
    print "-"x10 . "Executing " . &trim_path("$dir/$exec") . "-"x10  . "\n"; 
    system &stripcounter($exec) . " $args > $exec.run";
    &register_status($dir, $exec, $?);

    &cat("$exec.run") unless ($skipoutput);
    
    &popd();
    &compare_expected($dir, $exec);

}

sub write_to_demo
{
    my ($dir, $exec, $args, @inputlines) = @_;

    $dir = '.' if ($dir eq "");
    if (!-d $dir){
	print "\nwrite_to_demo(\"" . join('", "', @_) . "\"): $dir is not a directory\n";
	exit 1;
    }

    &compile_demo($dir, &stripcounter($exec));
    &pushd("$dir");
    unlink "$exec.dump $exec.run $exec.out $exec.ref $exec.diff";
    print "-"x10 . "Executing " . &trim_path("$dir/$exec") . " with input" . "-"x10  . "\n";
    open(SAVEOUT, ">&STDOUT");
    select(SAVEOUT); $| = 1;       # make unbuffered
    open(STDOUT, ">$exec.run") || die "Can't redirect stdout";
    open (EXEC, "| " . &stripcounter($exec) . " $args");
    foreach $input (@inputlines){
	print EXEC $input;
    }
    close EXEC;
    close(STDOUT);
    open(STDOUT, ">&SAVEOUT");
    &register_status($dir, $exec, $?);

    &cat("$exec.run") unless ($skipoutput);

    &popd();
    &compare_expected($dir, $exec);
    
}

sub ignore()
{
    my ($dir, $exec) = @_;
    $progs{&trim_path("$dir/$exec")}=111;
}
sub ignore_completely()
{
    my ($dir, $exec) = @_;
    $progs{&trim_path("$dir/$exec")}=222;
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
    my $compilecmd = &compile_command();
    &pushd($dir);
    print "-"x10 . "Compiling " . &trim_path("$dir/$f") . "-"x10  . "\n"; 
    system "$compilecmd $f > $f.out 2>&1" if (!$verbose);
    system "$compilecmd $f" if ($verbose);
    &popd();
}

sub run_all_demos
# find all .bet files in current directory and
# run all corresponding programs
{
    local($all) = 0;
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
	    } else {
		$program = $prog;
		$numdirs = 0;
		$dir = ".";
	    }
	    &compile_demo($dir, $program);
	    &pushd($dir);
	    system("$program");
	    $progs{$prog}=$?;
	    &popd();
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
