#!/usr/local/bin/perl

$num_files = 36;

### main:

mkdir("logs", 0755) if (! -d "logs") ;

system ("rm -f *.dump logs/log* logs/*.compile* logs/*.output* logs/*.stderr*");

for ($i=1; $i<=$num_files; $i++) 
{
    $filename = sprintf "tstexcept%02d", $i;
    print "$filename\n";

    next if ($i==21);
    next if ($i==23);

    &compile($filename, "");
    &execute($filename, "");
    &compare($filename, "");

    &compile($filename, "13");
    &execute($filename, "13");
    &compare($filename, "13");

    &compile($filename, "80");
    &execute($filename, "80");
    &compare($filename, "80");
}

print "List of possibly failed executions in logs/{log,log13,log80}\n";

### Helper functions:

sub compile()
{
    local ($filename, $switch) = @_;
    
    system("beta -s $switch $filename.bet > logs/$filename.compile$switch");
    if (!-x $filename){
	print "$filename: compilation failed";
	if ($switch ne ""){
	    print " (switch $switch)";
	}
	print ":\n";
	system("cat logs/$filename.compile$switch");
    }
}

sub execute()
{
    local ($filename, $switch) = @_;
     
    if (-x $filename){
	system("sh -c \"./$filename > logs/$filename.output$switch 2>logs/$filename.stderr$switch\"");
    }
}

sub compare()
{
    local ($filename, $switch) = @_;
     
    @gr = `grep "Aborting" logs/$filename.output$switch`;
    if ($#gr == -1) {
	system("echo $filename >> logs/log$switch");
    }
}

