#!/usr/local/bin/perl5 -s
#-*-Perl-*-

NOT YET COMPLETE!!!!!!!!!!!

$UseDefaults = 1 if ($u);

require "env.perl";

$exe = ".exe" if ($OS eq "WIN");

$ENV{'BETART'}="";
$ENV{'LD_LIBRARY_PATH'}= $ENV{'LD_LIBRARY_PATH'} . ":../lib/${objdir}";

print "\nRemoving old output- and dump files...\n";
print "======================================================\n"
&rm("*.out");
&rm("*.err");
&rm("*.dump");
&rm("*.ref");
&rm("*.app");
&rm("*.diff");

print "\nCompiling all...\n";
print "======================================================\n"
&beta(-qw tstdump??.bet);

print "\nRunning and diffing all (left is correct version)...\n"
print "======================================================\n"

@files = &GetFilesInDirs(".");
$match = "tstdump\d\d$exe";
foreach $f (@files) {
    next if ($f !~ m/^$match$/);
    print "\n--------" $f: "-------\n";
    if ( $f eq "tstdump24" ){
       print "$f skipped.\n";
       print "--------------------------\n"
       next;
    fi 
    if ( $f eq "tstdump26" ){
       print "$f will attempt to provoke stack overflow.\n";
       print "This is not handled correctly by betarun. tstdump26 skipped.\n";
       #print "This will take a while, and will probably not be.\n";
       #print "caught properly be betarun, but instead dump core.\n";
       #$f
       #&rm("core");
       #print "--------------------------\n"
       next;
    fi 


    $f >$f.out 2>$f.err
    if [ -f output/$f.out ]; then
       diff output/$f.out $f.out
       if [ $? = 0 ]; then
	  print "[stdout is correct]"
	  rm $f.out
       else
	  print "[Difference in output]"
       fi
    else
       print "[No reference output exists]"
    fi
   if [ -f output/$f.err ]; then
       diff output/$f.err $f.err
       if [ $? = 0 ]; then
	  print "[stderr is correct]"
	  rm $f.err
       else
	  print "[Difference in stderr]"
       fi
    else
       print "[No reference stderr exists]"
    fi
    if [ -f dumps/$f.dump ]; then
       if [ -f $f.dump ]; then
	  sed -e "s/MACHINE_TYPE/$objdir/g" < dumps/$f.dump > $f.ref
	  grep -v '{' $f.dump                               > $f.app
          diff $f.ref $f.app
          if [ $? = 0 ]; then
	     echo "[Dump is correct]"
	     rm $f.dump
	     rm $f.ref
	     rm $f.app
	     rm $f
          else
	     echo "[Difference in dump]"
	     diff $f.ref $f.app > $f.diff
          fi
       else
          echo "[No dump created]"
       fi
    else
       echo "[No reference dump exists]"
    fi
    print "--------------------------"
done

print Done.

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
