#!/usr/local/bin/perl5 -s

# Written by Morten Grouleff on 20-21. of May 1996.
# Somewhat testet, but I recommend keeping a backup of the files in any case.
# Run without arguments for usage-istructions.

sub ExitUsage {
    print "Usage: perl setversion.perl [option]* [<libraryname> <version-string>]*\n";
    print "\n";    
    print "Options:\n";
    print " -f    Force. Do not ask the user for confirmation.\n";
    print " -v    Verbose. Print names fo directories when they are entered.\n";
    print "\n";
    print "Example: perl setversion.perl basiclib v1.5grouleff\n";
    print "         -Changes all ORIGIN,INCLUDE,BODY,MDBODY references to\n";
    print "              '~beta/basiclib/vXX.?????/somefragment';\n";
    print "         - to -\n";
    print "              '~beta/basiclib/v1.5grouleff/somefragment';\n";
    print "\n";
    print "         Where the XX are decimal digits and ????? is anything but slashes.\n";
    print "The change is performed on all .bet files recursively from current dir.\n";
    print "In addition, all lines using the old fragment syntax (--- include) will be changed.\n"; 
    exit 1;
}

sub ProcessCurrentDirectory {
    ($cwd) = @_;
    foreach $file (<*.bet>) {
	next if ($file =~ /~$/);
	open(IN, $file) || die "$0: Cannot open file: $file: $!\n";
	@contents = <IN>;
	close IN;

	$out = '';
	$changed = 0;
	$FoundSlot = 0;

	foreach $line (@contents) {
	    if ($FoundSlot) {
		last if (!$changed);
		$out .= $line;
	    } else {
		if ($line =~ /^---\s*include\s+(.*)$/) {
		    $line = "INCLUDE $1;\n";          # Change to new syntax.
		    print "$cwd/$file, --- include -> INCLUDE\n";
		    $changed = 1;
		}
		if ($line =~ /^(ORIGIN|INCLUDE|BODY|MDBODY)\s+\'\~beta\/([^\/]+)\/(v\d+\.\d+[^\/]*)\/(.*)$/) {
		    ($type, $lib, $ver, $rest) = ($1, $2, $3, $4);
		    $new = $line; #Expect not to make any changes.
		    foreach $library (@libraries) {
			if ($lib eq $library) {
			    $version = $versions{$lib};
			    $new = "$type '~beta/$lib/$version/$rest\n";
			    last;
			}
		    }
		    if ($new ne $line) {
			print "$cwd/$file, $type $lib: $ver -> $version\n";
			$changed = 1;
		    }		
		    $out .= $new;
		} elsif ($line =~ /^---.+---/) {
		    $out.= $line;
		    $FoundSlot = 1;
		} else {
		    $out .= $line;
		}
	    }			 
	}			 
				
	if ($changed) {
	    unlink("$file~");
	    rename($file, "$file~");
	    
	    open(OUT, ">$file") || die "$0: Cannot write output $!";
	    print OUT $out;
	    close OUT;
	}
    }
}

sub RecurseDirs {
    local ($cwd, @subdirs);
    ($cwd) = @_;

    print "Processing $cwd\n" if $verbose;
    &ProcessCurrentDirectory($cwd);

    opendir(DIR, ".") || die "Unable to read directory: $!";
    @subdirs = ();
    foreach $file (readdir(DIR)) {
	next unless -d $file;
	next if ($file =~ /^\.\.?/);
	next if ($file =~ /^CVS$/);
	push(@subdirs, $file);
    }
    closedir DIR;

    foreach $dir (@subdirs) {
	chdir $dir;
	&RecurseDirs("$cwd/$dir");
	chdir "..";
    }
}

$verbose = 0;
$force   = 0;

foreach (@ARGV) {
    if (/^-(.)$/) {
	$opt = $1;
	if ($opt eq 'v') {
	    $verbose = 1;
	} 
	elsif ($opt eq 'f') {
	    $force = 1;
	} 
	else {
	    print "Unknown option $1\n";
	    exit 1;
	}
    }
    else {
	push(@args, $_);
    }
}

@ARGV = @args;

&ExitUsage if ($#ARGV != -1 && ($#ARGV % 2)  != 1);

@libraries = ();
while ($#ARGV != -1) {
    $lib = shift @ARGV;
    $ver = shift @ARGV;
    if ($lib =~ /v\d+\.\d+[^\/]*/ || $ver !~ /v\d+\.\d+[^\/]*/) {
	print "Cannot parse library \"$lib\", version \"$ver\"\n";
	exit 1;
    }
    push(@libraries, $lib);
    $versions{$lib} = $ver;
}


if (!$force) {
    $pwd = `pwd`;
    chop($pwd);
    print "This is the plan:\n";
    print "Starting from: \"$pwd\"\nI will recusively make the following changes to ALL .bet files:\n";
    print " - Changing old fragment syntax (--- include) to the new (INCLUDE)\n";
    foreach $lib (@libraries) {
	print " - Setting $lib to ", $versions{$lib}, "\n";
    }
    print "Is this what you want? (enter 'y' to start)";
    $yes = <STDIN>;
    chop($yes);
    if ($yes eq 'y') {
	$force = 1;
    }
}

if ($force) {
    &RecurseDirs(".");
}
