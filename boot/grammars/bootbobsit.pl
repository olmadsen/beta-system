#!/usr/bin/env perl

sub usage()
{
    print "Usage: bootbobsit.pl <grammar-name>\n";
    exit (1);
}

push(@INC, $ENV{"BETALIB"} . "/bin/admin");
require "env.perl";

if (! defined($grammarname)){
    usage if ($#ARGV != 0);
    $grammarname = $ARGV[0];
}

print "boot-bobsit $grammarname-parser.bobs\n";
if ("metagrammar" eq $grammarname){
    $bobsfile = "$betalib/boot/grammars/metagrammar/metagrammar-parser.bobs";
} else {
    $bobsfile = "$grammarname-parser.bobs";
}
#print "$betalib/boot/bin/$objdir/exbobs < $bobsfile\n";
system "$betalib/boot/bin/$objdir/exbobs < $bobsfile" || die "exbobs failed\n";
rename("bobslist", "$grammarname-parser.lst");
if ( ! -f "tables"){   
    print "ERRORS IN GRAMMAR\n";
    print "Look at $grammarname-parser.lst\n";
} else {
    # tabc
    print "boot-tabc\n";
    #print "$betalib/boot/bin/$objdir/tabc tables $grammarname-parser $grammarname\n";
    system "$betalib/boot/bin/$objdir/tabc tables $grammarname-parser $grammarname" || die "tabc failed\n";
}
