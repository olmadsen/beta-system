#!/usr/local/bin/perl

$num_files = 36;

system ("rm log");

for ($i=1; $i<=$num_files; $i++) 
{
    if ($i<10)
    {
	$filename = "tstexcept0$i";
    }
    else
    {
	$filename = "tstexcept$i";
    }
    print "Compiling $filename.bet\n";
    system("beta $filename.bet > $filename.compile");
    print "Running $filename\n";
    if ($i == 21)
    {
	print "infinite loop. please interrupt\n";
    }
    system("./$filename > $filename.output");

    @gr = `grep "Aborting" $filename.output`;
    if ($#gr == -1)
    {
	@gr2 = `grep "external" $filename.bet`;
	if ($#gr2 >= 0)
	{
	    print "External used trying with s 13\n";
	    print "Compiling $filename.bet\n";
	    system("beta -s 13 $filename.bet > $filename.compile");
	    print "Running $filename\n";
	    if ($i == 21)
	    {
		print "infinite loop. please interrupt\n";
	    }
	    system("./$filename > $filename.output");

	    @gr = `grep "Aborting" $filename.output`;
	    if ($#gr == -1)
	    {
		system("echo \"$filename (external)\" >> log");
	    }
	    else
	    {
		system("echo \"$filename (external works with s 13)\" >> log");
	    }
	}
	else
	{
	    system("echo $filename >> log");
	}
    }
}

