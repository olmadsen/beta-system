#!/usr/bin/env perl

sub usage()
{
    print "Usage: bootdogram.pl <grammar-name>\n";
    exit (1);
}

push(@INC, $ENV{"BETALIB"} . "/bin/admin");
require "env.perl";

if (! defined($grammarname)){
    usage if ($#ARGV != 0);
    $grammarname = $ARGV[0];
}
   

# generator
print "boot-generator\n";
system "$betalib/boot/bin/$objdir/gen $grammarname" || die "gen failed\n";

# bobsit
do "$betalib/boot/grammars/bootbobsit.pl";

