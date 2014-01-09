#-*-Perl-*-
require 5.001;
use Cwd;
use File::Path;

sub PrintDate {
    print scalar localtime, "\n";
}

sub GetDirsRecursively {
    my (@todo,$curdir,@result,$file);
    @todo = @_;
    push @result, @todo;
    while ($curdir = shift @todo) {
	$curdir = &path($curdir);
	print "Scanning $curdir\n" if ($debug);
	if (-d $curdir) {
	    opendir(DIR, $curdir) || die "GetDirsRecursively:Failed to open $curdir: $!";
	    foreach $file (readdir DIR) {
		next if ($file eq '.' or $file eq '..');
		$file = "$curdir/$file";
		if (-d $file) {
		    push @todo, "$file"; 
		    push @result, "$file";
		}
	    }
	    closedir DIR;
	}
    }
    return @result;
}

sub GetDirsInDir {
    my (@result,$file,$dir);
    $dir = shift @_;
    print "Scanning $dir\n" if ($debug);
    if (-d $dir) {
	opendir(DIR, $dir) || die "GetDirsInDir:Failed to open $dir: $!";
	foreach $entry (readdir DIR) {
	    print "$entry " if ($debug);
	    if (-d "$dir/$entry") {
		print "is a directory\n" if ($debug);
		push @result, $entry;
	    } else { 
		print "is not a directory\n" if ($debug);
	    }
	}
	closedir DIR;
    }
    return @result;
}

sub GetFilesInDir {
    my (@result,$file,$dir);
    $dir = shift @_;
    print "Scanning $dir\n" if ($debug);
    if (-d $dir) {
	opendir(DIR, $dir) || die "GetFilesInDir:Failed to open $dir: $!";
	foreach $file (readdir DIR) {
	    $file = "$dir/$file";
	    print "$file " if ($debug);
	    if (-f $file) {
		print "is a regular file\n" if ($debug);
		push @result, $file;
	    } else { 
		print "is not a regular file\n" if ($debug);
	    }
	}
	closedir DIR;
    }
    return @result;
}
    
sub GetFilesInDirs {
    my (@result);
    foreach $dir (@_){
	push @result, &GetFilesInDir($dir);
    }
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
	if ($Generate) {
	    print "cvsout \"cd $p\\n\"\n";
		print "cd $p;\n"; 
	}
    print "chdir($p)\n" if $verbose;
    chdir $p or die "Unable to chdir: $!" unless $simulate;
}

sub path {			# Convert path to LOCAL convention
    my($p)=@_;
    $p =~ s/\~beta/$betalib/gi;	# Replace ~beta with unix-style betalib.
    if ($OS eq 'WIN'){
	if ($ENV{'TERM'} ne 'cygwin'){
	    $p =~ s#/#\\#g;
	}
    } elsif ($OS eq 'MAC'){
	$p =~ s#/#:#g;
    } 
    return $p;
}

sub compiler_name()
{
    if ($clr) {
	return "nbeta";
    } elsif ($jvm) {
	return "jbeta";
    } elsif ($OS eq 'MAC'){
    	return &path("$betalib/scripts/beta");
    } elsif ($OS eq "WIN") {
	return &path("~beta/bin/nti_$MIASDK/beta");
    } else {
	return "beta";
    }
}

sub beta {
    my $compiler=&compiler_name();
    if ($OS eq 'MAC'){
        print "$compiler --verbose @_\n";
    	print `$compiler --verbose @_`;
    } else {
	system "$compiler @_";
    }
}

sub bootbeta {
    if ($OS eq 'MAC'){
    	$compiler=&path("$betalib/boot/bin/$objdir/beta");
        print "$compiler --verbose @_\n";
    	print `$compiler --verbose @_`;
    } else {
	system "$betalib/boot/bin/$objdir/beta --gram $betalib/boot/grammars/beta/beta @_";
    }
}

sub which {
    my($cmd, $all)=@_;
    my(@path);
    my($found);
    print "which($cmd, $all)\n" if($verbose);
    if ($OS eq 'MAC'){
	@path = split(',', $ENV{'COMMANDS'});
    } elsif ($OS eq 'WIN'){
	if ($cygwin){
	    @path = split(':', $ENV{'PATH'});
	} else {
	    @path = split(';', $ENV{'PATH'});
	}
    } else {
	@path = split(':', $ENV{'PATH'});
    }
    $found = "";
    foreach $dir (@path) {
	print "  Trying: $dir/$cmd\n" if($verbose);
	if (-f "$dir/$cmd"){
	    print "yep, that's it!\n" if($verbose);
	    $found .= "$dir/$cmd";
	    $found .= "\n" if ($all);
	    last unless ($all);
	}
	if ($OS eq 'WIN'){
	    print "Trying: $dir\\$cmd.bat\n" if($verbose);
	    if (-f "$dir/$cmd.bat"){
		print "yep, that's it!\n" if($verbose);
		$found .= "$dir/$cmd.bat";
		$found .= "\n" if ($all);
		last unless ($all);
	    }
	    print "Trying: $dir/$cmd.exe\n" if($verbose);
	    if (-f "$dir/$cmd.exe"){
		print "yep, that's it!\n" if($verbose);
		$found .= "$dir/$cmd.exe";
		$found .= "\n" if ($all);
		last unless ($all);
	    }
	}
	if ($OS eq 'WIN'){
	    $found =~ s#/#\\#g;
	}
    }
    return "$found";
}

sub execute_script {
    my($cmd)=@_;
    if ($OS eq 'MAC'){
    	print "execute_script: NYI for mac\n";
    } elsif ($OS eq 'WIN'){
	my(@cmd) = split(' ', $cmd);
	my($comspec) = $ENV{'COMSPEC'};
	#@cmd[0] = &which(@cmd[0], 0);
	print "$comspec /C @cmd\n";
	system "$comspec /C @cmd";
    } else {
	my(@cmd) = split(' ', $cmd);
	#print "execute_script: @cmd\n";
	system @cmd;
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
  @output = `cvs @_ 2>&1`;
  return @output;
}

sub cvs {
      local ($cvscmd) = "cvs ";
      #$cvscmd .= "-d $ENV{'CVSROOT'} " if defined($ENV{'CVSROOT'}) && (!$Generate);
      $cvscmd .= "@_";
      print "$cvscmd\n" if ($verbose);
      if ($Generate) {
	  print "cvsout \"$cvscmd\\n\"\n";
	  print "set output [" . "$cvscmd" . "]\n";
	  print "cvsout \"\$output\\n\"\n";
      }
      system "$cvscmd" unless $simulate;
}


sub SmartMkdir {
    # Could probably use mkpath() from File::Path
    my ($path, $full) = @_;
    $full = '';
    foreach $dir (split '/', $path) {
	$full .= $dir . '/';
	if (!-d &path($full)){
	    print "\tmkdir $full\n" if ($verbose || $simulate);
	    mkdir (&path($full), 0755) if (!$simulate);
	}
    }
}

# Recursively delete all files and dirs in $path, including $path.
sub SmartRmDir {
    my ($path) = @_;
    if ($OS eq "UNIX" || $cygwin){
	system "rm -rf $path";
    } else {
	rmtree($path, 1, 1);
    }
}

sub cat()
{
    my ($file) = @_;
    if (! open FILE, "$file"){
	warn "cat: cannot open $file for reading: $!\n";
	return;
    }
    while (<FILE>) { print; };
    close FILE;
}

sub cp()
{
    my ($file1, $file2) = @_;
    if (! open FILE1, "$file1"){
	warn "cp: cannot open $file1 for reading: $!\n";
	return;
    }
    if (! open FILE2, ">$file2"){
	warn "cp: cannot open $file2 for writing: $!\n";
	close FILE1;
	return;
    }
    while (<FILE1>) { print FILE2; };
    close FILE1;
    close FILE2;
}

sub touch ()
{
    local ($time, $entry) = @_;
    if (! -e $entry){
	open E, ">$entry" || die "touch: cannot create $entry: $!\n";
	close E;
    }
    if ($time==0){ $time = time; }
    utime $time, $time, $entry;
}

sub pushd()
{
    local ($dir) = @_;
    push @dirstack, cwd;
    chdir $dir || die "pushd: cannot chdir to $dir: $!\n";
}

sub popd()
{
    if (scalar @dirstack){ 
	chdir pop @dirstack;
    } else {
	die "popd: directory stack empty\n";
    }
}

sub do_perl()
{
    local ($file) = @_;
    local $return;
    #if ($cygwin){
    #	$file = `cygpath -u $file`;
    #}
    if (! -e $file){
	print "do_perl: perl file does not exist: $file\n";
	exit;
    }
    print "Calling $file\n";
    if (0){
	# Fails on Oles newly installed cygwin?? 2003-10-03
	unless ($return = do $file) {
	    die "couldn't parse $file: $@\n" if $@;
	    die "couldn't do $file: $!\n"    unless defined $return;
	    die "couldn't run $file\n"       unless $return;
	}
    } else {
	eval `cat $file`;
    }
}

1;
