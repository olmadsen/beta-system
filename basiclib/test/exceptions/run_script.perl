#!/usr/local/bin/perl

$num_files = 36;

### main:

&setup();

for ($i=1; $i<=$num_files; $i++) 
{
    $filename = sprintf "tstexcept%02d", $i;
    print "$filename";

    if ($i==20 || $i==21 || $i==23){
	print " (skipped)\n";
	next;
    }

    &compile($filename, "");
    &execute($filename, "");
    &compare($filename, "");

    &compile($filename, "13");
    &execute($filename, "13");
    &compare($filename, "13");

    &compile($filename, "80");
    &execute($filename, "80");
    &compare($filename, "80");

    print "\n";
}

&summary();

### Helper functions:

sub setup()
{
    mkdir("logs", 0755) if (! -d "logs") ;

    select(STDERR); $| = 1;       # make unbuffered
    select(STDOUT); $| = 1;       # make unbuffered

    system ("rm -f log log13 log80 *.dump logs/*");

    push(@INC, $ENV{'BETALIB'} . "/bin/admin");

    require "env.perl";
    require "ctime.pl";
};

sub compile()
{
    local ($filename, $switch) = @_;
    
    print ".";
    system("beta -s $switch $filename.bet > logs/$filename.compile$switch");
    if (!-x $filename){
	print "$filename: compilation failed";
	if ($switch ne ""){
	    print " (switch $switch)";
	}
	print ":\n";
	&cat("logs/$filename.compile$switch");
    }
}

sub execute()
{
    local ($filename, $switch) = @_;
     
    print ".";
    if (-x $filename){
	system("sh -c \"./$filename > logs/$filename.output$switch 2>logs/$filename.stderr$switch\"");
    }
}

sub compare()
{
    local ($filename, $switch) = @_;
     
    print ".";
    @gr = `grep "aborting" logs/$filename.output$switch`;
    if ($#gr == -1) {
	system("echo $filename >> log$switch");
    }
}

sub cat()
{
    local ($filename) = @_;
    open(CAT, $filename || die "cannot open $file for reading: $!\n");
    while(<CAT>){
	print;
    }
    close CAT;
}


sub summary()
{
    print "Summary (${objdir}): ";
    print ctime(time);
    if (-f "log"){
	print "Failed executions with normal betarun:\n";
	&cat("log");
    }
    if (-f "log13"){
	print "Failed executions with debug betarun:\n";
	&cat("log13");
    }
    if (-f "log80"){
	print "Failed executions with unconditional GC betarun:\n";
	&cat("log80");
    }
    print "List of possibly failed executions in {log,log13,log80}\n";
}
