#-*-Perl-*-
require 5.001;
use Cwd;

sub PrintDate {
    print scalar localtime, "\n";
}

sub GetDirsRecursively {
    my (@todo,$curdir,@result,$file);
    @todo = @_;
    push @result, @todo;
    while ($curdir = shift @todo) {
	$curdir = &path($curdir);
	print "Scanning $curdir\n" if (defined $debug);
	opendir(DIR, $curdir) || die "Failed to open $curdir: $!";
	foreach $file (readdir DIR) {
	    next if ($file eq '.' or $file eq '..');
	    $file = "$curdir/$file";
	    if (-d $file) {
		push @todo, "$file"; 
		push @result, "$file";
	    }
	}
    }
    closedir DIR;
    return @result;
}

sub GetFilesInDirs {
    my (@result,$file,$dir);
    $dir = shift @_;
    print "Scanning $dir\n" if (defined $debug);
    opendir(DIR, $dir) || die "Failed to open $dir: $!";
    foreach $file (readdir DIR) {
	$file = "$dir/$file";
	print "$file " if (defined $debug);
	if (-f $file) {
	    print "is a regular file\n" if (defined $debug);
	    push @result, $file;
	} else { 
	    print "is not a regular file\n" if (defined $debug);
	}
    }
    closedir DIR;
    return @result;
}
    

    
sub FileCopy {
    my ($src, $dst) = (@_);
    $src = &path($src);
    $dst = &path($dst);
    if ($OS eq "WIN") {
	system("copy /Q $src $dst");
    } elsif ($OS eq 'UNIX') {
	system("cp $src $dst");
    } else {
	die "FileCopy: missing impl for $OS.\n";
    }
}

sub GetPath {
    my($p);
    $p=&cwd;
    if ($OS eq 'MAC') {
	$p =~ s#\:#/#g;
    } elsif ($OS eq 'WIN') {
	$p =~ s#\\#/#g;
    }
    $p =~ s/^$betalib/\~beta/i;
    return $p;
}

sub Chdir {
    my($p)=@_;
    $p = &path($p);
    if (!-d $p) {
	print "Chdir Warning: \"$p\" does not exist.\n";
    }
    chdir $p;
}

sub path {			# Convert path to LOCAL convention
    my($p)=@_;
    $p =~ s/\~beta/$betalib/gi;	# Replace ~beta with unix-style betalib.
    if ($OS eq 'WIN'){
	$p =~ s#/#\\#g;
    } elsif ($OS eq 'MAC'){
	$p =~ s#/#:#g;
    } 
    return $p;
}

sub beta {
    if ($OS eq 'MAC'){
    	$compiler=&path("$betalib/scripts/beta");
        print "$compiler --verbose @_\n";
    	print `$compiler --verbose @_`;
    } else {
	system &path("~beta/bin/beta @_");
    }
}

sub bootbeta {
    if ($OS eq 'MAC'){
    	$compiler=&path("$betalib/scripts/bootbeta");
        print "$compiler --verbose @_\n";
    	print `$compiler --verbose @_`;
    } else {
	system &path("~beta/bin/bootbeta @_");
    }
}

sub GetAnswer {
    my ($answer);
    if ($OS eq 'MAC'){
	print "\n";
    }
    $answer=<STDIN>; chop $answer;
    return $answer;
}

sub cvsoutput {
  if ($OS eq 'MAC'){
      $maccvs=$ENV{'maccvs'}."MacCvs";
      $cwd=`Directory`; chop $cwd;
      $outfile=$ENV{'tempfolder'}."cvs.out";
      
      unlink($outfile) if (-f "$outfile");
      $script  = "tell application \"$maccvs\"\n";
      $script .= "do script { \"@_\" } environment { \"CVSROOT\", \"ariel:/users/beta/.CVSHOME\" } pathway \"$cwd\" mode file filename \"$outfile\"\n";
      $script .= "end tell";
      &MacPerl::DoAppleScript($script);
      @output = ();
      while(! -f "$outfile") { sleep(1) }
      open (OUT, "$outfile") || die "cvsoutput: cannot open $outfile\n";
      @output = <OUT>;
      close OUT;
  } else {
      @output = `cvs @_ 2>&1`;
  }	
  return @output;
}

sub cvs {
    print &cvsoutput(@_);
}


sub SmartMkdir {
    my ($path, $full) = @_;
    $full = '';
    foreach $dir (split '/', $path) {
	$full .= $dir . '/';
	if (!-d &path($full)){
	    print "\tmkdir $full\n" if ($verbose);
	    mkdir (&path($full), 0755) if (!$simulate);
	}
    }
}

1;
