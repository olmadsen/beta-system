#!/usr/local/bin/perl

if ($#ARGV == -1) {
    print "Usage:\n";
    print "beta2html.perl <betafiles>\n";
    exit 1;
}

foreach $betafile (@ARGV) {
    next if ($betafile =~ /~$/);
    next if ($betafile !~ /\.bet$/);
    print "$betafile -> ";
    open(IN, $betafile) || die "$0: Cannot open file: $betafile: $!\n";
    $contents="";
    while (<IN>){
	$contents .= $_;
    }
    close IN;

    $htmlfile = $betafile;
    $htmlfile =~ s/\.bet$/.html/i;
    print "$htmlfile\n";

    open(OUT, ">$htmlfile") || die "$0: Cannot write output $!";
    print OUT "<A NAME=\"$betafile\"><H4 class=betacaption>$betafile</H4></A>\n";
    print OUT "<PRE CLASS=beta>\n";
    $contents =~ s/&/&amp;/g;
    $contents =~ s/</&lt;/g;
    $contents =~ s/>/&gt;/g;
    print OUT $contents;
    print OUT "</PRE>\n";
    close OUT;
}
