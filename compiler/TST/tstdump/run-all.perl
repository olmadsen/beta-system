#!/usr/local/bin/perl -s
#-*-Perl-*-

# nti usage: perl -I..\..\..\..\bin\admin run-all.perl

$UseDefaults = 1 if ($u);
$FastMode = 1 if ($f);

push(@INC, $ENV{'BETALIB'} . "/bin/admin");

require "env.perl";
require "ctime.pl";

$nti = ($OS eq "WIN");
$exe = "\.exe" if ($nti);

$ENV{'BETART'}="";
$ENV{'LD_LIBRARY_PATH'}= $ENV{'LD_LIBRARY_PATH'} . ":../lib/${objdir}";

print "\nRemoving old output- and dump files...\n";
print "======================================================\n";
&rm("*.out");
&rm("*.err");
&rm("*.dump");
&rm("*.ref");
&rm("*.app");
&rm("*.diff");
&rm("*.nodump");
&rm("*.candidate");

if ($FastMode) {
    print "\nUsing existing executables.\n";
    print "======================================================\n";
} else {
    print "\nCompiling all...\n";
    print "======================================================\n";
    &beta("-qw tstdump??.bet");
}

print "\nRunning and diffing all (left is correct version)...\n";
print "======================================================\n";

@files = &GetFilesInDirs(".");
@files = sort @files;
$match = "tstdump\\d\\d";
foreach $f (@files) {
    $f =~ s/^\.\///;
    $f =~ s/${exe}$//;
    next if ($f !~ m/^$match$/);
    print "\n-------- $f: -------\n";
    if ( $f eq "tstdump24" ){
	print "$f skipped.\n";
	print "--------------------------\n";
	next;
    } 
    if ( $f eq "tstdump26" ){
	print "$f will attempt to provoke stack overflow.\n";
	print "This is not handled correctly by betarun. tstdump26 skipped.\n";
	#print "This will take a while, and will probably not be.\n";
	#print "caught properly be betarun, but instead dump core.\n";
	#$f
	#&rm("core");
	#print "--------------------------\n"
	next;
    }
       
    #FIXME: stderr og stdout redirect missing...
    if ($nti) {
	system("$f >$f.out 2>$f.err");   #Probably requires 4NT / 4DOS.
    } else {
	system("$f >$f.out 2>$f.err");
    }
    if ( -f "output/$f.out" ) {
	if (system("diff -i output/$f.out $f.out") == 0){
	    print "[stdout is correct]\n";
	    &rm("$f.out");
	} else {
	    print "[Difference in output]\n";
	}
    } else {
	print "[No reference output exists]\n";
    }
    if ($nti){
	print "[stderr not compared on nti]\n";
    } else {
	if ( -f "output/$f.err" ) {
	    open(IN, "<$f.err");
	    open(OUT, ">$f.ref") || die "Unable to write processed stderr:$!";
	    while(<IN>) {
		s/Segmentation fault/Bus error/g;
		print OUT;
	    }
	    close IN;
	    close OUT;
	    if (system("diff -i $f.ref $f.err") == 0){
		print "[stderr is correct]\n";
		&rm("$f.err");
	    } else {
		print "[Difference in stderr]\n";
	    }
	    &rm("$f.ref");
	} else {
	    print "[No reference stderr exists]\n";
	}
    }
    if ( -f "$f.dump") {
	if ( -f "dumps/$f.dump" ) {
	    open(IN, "<dumps/$f.dump");
	    open(OUT, ">$f.ref") || die "Unable to write processed reference dump:$!";
	    while(<IN>) {
		s/MACHINE_TYPE/$objdir/g;
		s/address 0x[0-9a-f]+/address 0xXXXXXXXX/g;
		print OUT;
	    }
	    close IN;
	    close OUT;
	    
	    open(IN, "<$f.dump");
	    open(OUT, ">$f.app") || die "Unable to write processed application dump: $!";
	    while(<IN>) {
		next if (/\{/);
		s/set\ +BETART\=SimpleDump/setenv BETART SimpleDump/;
		s/address 0x[0-9a-f]+/address 0xXXXXXXXX/g;
		print OUT;
	    }
	    close IN;
	    close OUT;
	    
	    if (system("diff -i $f.ref $f.app") == 0){
		print "[Dump is correct]\n";
		&rm("$f.dump");
		&rm("$f.ref");
		&rm("$f.app");
		&rm("$f$exe");
	    } else {
		print "[Difference in dump]\n";
		system("diff -i $f.ref $f.app > $f.diff");
	    }
	} else {
	    print "[No reference dump exists. Creating $f.candidate]\n";
	    open(IN, "<$f.dump");
	    open(OUT, ">$f.candidate") || die "Unable to write candidate dump: $!";
	    while(<IN>) {
		next if (/\{/);
		s/$objdir/MACHINE_TYPE/g;
		s/set\ +BETART\=SimpleDump/setenv BETART SimpleDump/;
		s/address 0x[0-9a-f]+/address 0xXXXXXXXX/g;
		print OUT;
	    }
	    close IN;
	    close OUT;
	}
    } else {
	print "[No dump created.]\n";
	open(OUT, ">$f.nodump") || die "Unable to write nodump: $!";
	close(OUT);
    }
    print "--------------------------\n";
}

open(SUMMARY, ">summary.run-all" || die "cannot open summary.run-all for writing: $!\n");

print SUMMARY ctime(time);
print SUMMARY "Summary:\n";
foreach $f (@files) {
    $f =~ s%^\.\/%%;
    $f =~ s/${exe}$//;
    next if ($f !~ m/^$match$/);
    if (-f "$f.out")      { print SUMMARY "  $f: difference in output\n"; }
    if (-f "$f.err")      { print SUMMARY "  $f: difference in stderr\n"; }
    if (-f "$f.diff")     { print SUMMARY "  $f: difference in dump\n"; }
    if (-f "$f.nodump")   { print SUMMARY "  $f: no dump created\n"; &rm("$f.nodump"); }
    if (-f "$f.candidate"){ print SUMMARY "  $f: no reference dump exists. Candidate created\n"; }
}
close SUMMARY;
open(SUMMARY, "summary.run-all" || die "cannot open summary.run-all for reading: $!\n");
while(<SUMMARY>){
    print;
}
close SUMMARY;

print "Done.\n";

sub rm()
{
    #FIXME: make a better one using unlink and move to utils.perl
    if ($OS eq 'MAC'){
    	### hmmm.
    } elsif ($OS eq "WIN") {
	system "del @_";
    } else {
	system "/bin/rm -f @_";
    }
}
