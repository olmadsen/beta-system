#!/usr/local/bin/perl

$num_files = 36;

system ("rm log log13 log80");

for ($i=1; $i<=$num_files; $i++) 
{
    if ($i==21) {
	$i++;
    }
    if ($i==23) {
	$i++;
    }

    if ($i<10)
    {
	$filename = "tstexcept0$i";
    }
    else
    {
	$filename = "tstexcept$i";
    }
    system("beta $filename.bet > $filename.compile");
    system("./$filename > $filename.output");

    @gr = `grep "Aborting" $filename.output`;
    if ($#gr == -1) {
	system("echo $filename >> log");
    }

    system("beta -s 13 $filename.bet > $filename.compile");
    system("./$filename > $filename.output");

    @gr = `grep "Aborting" $filename.output`;
    if ($#gr == -1) {
	system("echo $filename >> log13");
    }

    system("beta -s 80 $filename.bet > $filename.compile");
    system("./$filename > $filename.output");

    @gr = `grep "Aborting" $filename.output`;
    if ($#gr == -1) {
	system("echo $filename >> log80");
    }

}

