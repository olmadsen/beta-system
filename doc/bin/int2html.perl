#!/usr/local/bin/perl -s

sub usage
{
    print "Usage: int2html.perl [-v] [-t] <interfacefile>\n";
    print "  -v: print progress to STDERR\n";
    print "  -t: print trace to STDERR\n";
}

# Insert World Wide Web tags for declarations (HTML format).
# Outermost declaration is indexed by its own name, inner declarations are 
# indexed by its name followed by the outermost index and vice versa.
# Only declarations on the $scope outermost scope levels are indexed.
# Initial $scope is 2. The following pseudo commands in the beta
# text (each on a line by itself), can be used to control the indexing 
# scope level:
#  (* idx: i *)
#     sets $scope to i
#  (* idx= i *)
#     sets $scope to i
#  (* idx+ *)
#     increments $scope by 1
#  (* idx- *)
#     decrements $scope by 1
#
# Super- and sub pattern indices are also added in the following fashion:
#    X: (#
#          Y: Z(# ... #)
#       #)
#
# yields
#    X
#      Y
#        Superpattern:
#           Z
#
# and
#    X
#      Z
#        Subpatterns:
#           Y
#
# i.e. it is assumed that the prefix is declared at the same scope.
# This is not always the case, but is impossible to check in a simple way.
# 
# Indexed words are set in bold.
#
# BUGS:
#   "enter (foo, type##)" where type is pattern variable does not work
#   Has to be written "enter (foo, type ## )"
#
# TODO: 
# 1. Make several file names accepted on command line
#    and generate separate HTML file for each. Then generate 
#    idx.html which contains *common* index.
#    Preparations has been made for this - should mostly be
#    a matter of putting a loop around the major part of MAIN.
#
# 2. Should automatically set up next and previous in navigation buttons, 
#    based on the argument files (see 1). And Top could be ../index.html.
#
# 3. Formatting of index HTML is not yet complete:
#    Attributes of a pattern should be shown indented without the
#    pattern name.
#    Subpatterns and superpatterns should be handled as in word.
#
# 4. superpatterns are not even generated?

# Style sheet:
$css = "../../style/miadoc.css";
$indexfile = "inx.html";

sub print_header
{
    local ($title) = @_;

    print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<TITLE>$title</TITLE>
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
</HEAD>
<BODY>
<P></P>
<A><IMG ALIGN=BOTTOM SRC="../../images/nextg.gif" ALT=Next BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/prevg.gif" ALT=Previous BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/topg.gif" ALT=Top BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/contentg.gif" ALT=Contents BORDER=0></A>
<A HREF="$indexfile"><IMG ALIGN=BOTTOM SRC="../../images/index.gif" ALT=Index BORDER=0></A>
<P></P>
<P>$title</P>
<HR>
<!---------------------------------------------------------->

<H1>$title</H1>
<PRE CLASS=interface>
EOT
}

sub print_trailer
{
    local ($title) = @_;

    print<<EOT;
</PRE>
<!---------------------------------------------------------->
<HR>
<P></P>
<ADDRESS>$title</ADDRESS>
<P></P>
<A><IMG ALIGN=BOTTOM SRC="../../images/nextg.gif" ALT=Next BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/prevg.gif" ALT=Previous BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/topg.gif" ALT=Top BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/contentg.gif" ALT=Contents BORDER=0></A>
<A HREF="$indexfile"><IMG ALIGN=BOTTOM SRC="../../images/index.gif" ALT=Index BORDER=0></A>

</BODY>
</HTML>
EOT
}

sub print_index_header
{
    print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<TITLE>Index of Identifiers</TITLE>
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
</HEAD>
<BODY>
<P></P>
<A><IMG ALIGN=BOTTOM SRC="../../images/topg.gif" ALT=Top BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/contentg.gif" ALT=Contents BORDER=0></A>
<P></P>
<P>Index of Identifiers</P>
<HR>
<!---------------------------------------------------------->

<H1><A name="Index.identifiers">Index of Identifiers</A></H1>
<PRE CLASS=interface>
EOT
}

sub print_index_trailer
{
    print<<EOT;
</PRE>
<!---------------------------------------------------------->
<HR>
<P></P>
<ADDRESS>Index of Identifiers</ADDRESS>
<P></P>
<A><IMG ALIGN=BOTTOM SRC="../../images/topg.gif" ALT=Top BORDER=0></A> 
<A><IMG ALIGN=BOTTOM SRC="../../images/contentg.gif" ALT=Contents BORDER=0></A>

</BODY>
</HTML>
EOT
}

sub print_index_toc
{
    local ($i, $ch);
    print "<P></P>\n</PRE>\n";
    for ($i=65; $i<=90; $i++){
	$ch = sprintf ("%c", $i);
	if ($caps{$ch}){
	    print "<STRONG><A HREF=\"#_$ch\">$ch</A></STRONG> &nbsp; \n";
	} else {
	    # no indices starting with $ch
	    print "<STRONG>$ch</STRONG> &nbsp; \n";
	}	    
    }
    print "<P></P>\n<HR>\n<P></P>\n<PRE CLASS=interface>\n";
}

sub print_index
{
    @index = sort @index;
    local ($html_index, $initial_ch, $htmlfile, $i);

    $html_index = "";

    for($i = 0; $i <= $#index; $i++) {
	# delete traling file name (after '@')
	$index[$i] =~ s/(.+)\@(.+)/$1/;
	# save target file name
	$htmlfile = $2;
	$_ = $index[$i];
	
	s/(\s*\w+)\.\d+/$1/g;
	s/\(\d+\)//g;
	while ( m/[ :](\w+)\.(\d+)[:\}]/ ) {
	    $id = $1; $level = $2;
	    $indents = $indent x ($level-1);
	    s/([ \:])$id\.$level([\:])/$1$indents$id$2/;
	}
	
	# Generate caps heading at first occurrence of a letter.
	$initial_ch = ucfirst (substr($index[$i], 0, 1));
	if (! $caps{$initial_ch} ){
	    $html_index .= "</PRE><H3><A name=\"_$initial_ch\">$initial_ch<\/A><\/H3><PRE CLASS=interface>\n";
	    $caps{$initial_ch} = 1;
	}

	$html_index .= "<A href=\"$htmlfile\#" . $index[$i] . "\">" . $_ . "</A>\n";
    }
    &print_index_header;
    &print_index_toc;
    print $html_index;
    &print_index_trailer;
}

sub strip_extension
{
    local ($string) = @_;
    if ( $string =~ m/([^\.]+)\..*/ ) {
	$string = $1;
    }
    return $string;
}

sub strip_path
{
    local ($string) = @_;
    if ( $string =~ m%.*/([^/]+)% ) {
	$string = $1;
    }
    return $string;
}

################ MAIN ####################

if ($#ARGV!=0){
    &usage();
    exit 1;
}

$verbose=$v;
$trace=$t;

$file=$ARGV[0];
$title=ucfirst(&strip_path(&strip_extension($file))) . " Interface";
$outfile=&strip_extension($file) . ".html";

# Read entire input-stream into $line.

printf STDERR "Reading $file ...\n" if $verbose==1;

open(INT, $file) || die "Cannot open $file: $!\n";

while (<INT>) {
    $line .= $_;
};
close (INT);

$_ = $line;		

# Mark '(#', '#)' and ':' in comments to avoid interference with
# subsequent matchings.

$after = $_;			# in case of no comments at all
$line = "";

printf STDERR "Substituting special symbols...\n" if $verbose==1;

while ( /\(\*|\*\)/ ) {
    $before = $`;
    $match  = $&;
    $after  = $';
    if ( $match eq '*)' ) {
        $before =~ s/:/\001/g;
	$before =~ s/\(\#/\002/g;
	$before =~ s/\#\)/\003/g;
    }
    $line .= $before.$match;
    $_ = $after;
}
$_ = $line.$after;

# Substitute ':' in slots with \004
s/(\<\<\s*SLOT\s*\w+\s*):(\s*\w+\s*\>\>)/$1\004$2/gi;

# Substitute ':' in fragmentIds with \004
#   (assumes entire fragment syntax on one line - I think)
s/(\-\-+\s*\w+\s*):(\s*\w+\s*\-\-+)/$1\004$2/g;

# quote HTML
s/&/\007/g;
s/</\021/g;
s/>/\022/g;

$indexid=0;

# Index text for subpatterns.
$subpatterns="_subpatterns";

# Index text for superpatterns.
$superpattern="__superpattern";

# Run through $_, matching for pattern-begin and pattern-end, while
# keeping track of scope level.
# Insert nested index-information for declarations at the outermost
# $scope levels.
$scope  = 2;

$*=0;
$patterns = "";
$revpatterns = "";
$level  = 1;
$line = "";
$prefix = "";

printf STDERR "Searching for patterns .....\n" if $verbose==1;

while ( m/\n[ \t]*\(\*\s+idx([\+\-\=\001])\s*(\d*)\s*\*\)\s*\n|\(\#|\#\)|::?<?/i ){
    $before = $`;
    $match  = $&; 
    $idxop  = $1; $idxlev = $2; # if index information present
    $after  = $';
    if ( "$idxop" ne "" ) {
	# index pseudo comment found
	if ( "$idxop" eq "+" ) { $scope++; }
	elsif ( "$idxop" eq "-" ) { $scope--; }
	if ( "$idxop" eq "=" || "$idxop" eq "\001" ) {
	    if ( "$idxlev" eq "" ) {
		die "No level specified in idx= command";
	    }
	    $scope = $idxlev;
	}
	$match = ""; # delete comment
	$after = "\n".$after;
	# $match = "\nINDEXLEVEL: $scope\n";
    }
    elsif ( "$match" eq "(#" ) {
	# add previously found identifier in scope descripion
	if ( "$patternid" ne "" ) {
	    $patterns .= "$patternid.$level:";
	    printf STDERR "  %s\n", $patternid if $trace==1;
	} else {	   
	    $patterns .= "ANONYMOUS.$level:";
	    printf STDERR "  ANONYMOUS\n" if $trace==1;
	}
	$level += 1;
	$patternid = "";
	# $match = "BEGIN";
	# $match = "\n[PATTERNS: $patterns]\n";
    }
    elsif ( "$match" eq "#)" ){	
	# check if $before ends with "#".
	if ( ($before =~ /\#$/ ) && ( ! ( $before =~ /\#\#$/ ) ) ) {
	    # found something like 
	    #   "... ->F##)
	    # i.e. a pattern variable at end of a parenthesed
	    # evaluation.
	    # This is NOT a pattern end!
	    printf STDERR "\n******* NOTICE: In the text ending like this:\n";
	    printf STDERR substr($line.$before.$match, -100, 100);
	    printf STDERR "\n******* the '##)' is not considered a pattern end.";
	    printf STDERR "\n******* Please check if this is correct.\n\n";	
	    # Just precede.
	} else {
	    # This is really a pattern end
	    $level -= 1;
	    if ( $patterns =~ m/:\w+.\w+:$/ ) {
		$patterns = $`.":";
	    }
	    elsif ( $patterns =~ m/^\w+.\w+:$/ ) {
		$patterns = "";
	    } else {
		$line .= $before.$match;
		die "*** PATTERNS is wrong: $patterns\n*** context:\n------------\n", substr($line, -100,100), "\n------------\n";
	    }
	    # $match .= "\n[PATTERNS: $patterns]\n";
	}
    }
    elsif ( $match =~ m/:/ )  { # a colon was found
	if ( $level <= $scope ){
	    if ( $before =~ m/(\w+[\w\s,]*)\s*$/ ) {
		$head = $`;
		@ids = split( ',' , $1); # list of identifiers, e.g.: x, y, z
		$tail = "";
		$prefix = "";
		if ( $after =~ m/^\s*\(\*/ ) {
		    # move comment after colon but before prefix from $after to $tail
		    $tail = $&;            # the stuff matched by the regexp
		    $after = $';           # the stuff after the match
		    $after =~ m/\*\)\s*/;  # MUST succeed if comment matches
		    $tail .= $`.$&;        # the stuff before the last match and the match itself
		    $after = $';           # the stuff after the match
		}
		
		if ( $after  =~ m/^\s*(\w+)\s*\(\#/ ) { 
		    $prefix = $1;
		} else {
		    # the match for prefix failed.
		    # look ahead and check if there was a comment after the prefix
		    # and try the match again.
		    # don't change $tail or $after, the superpattern info should be 
		    # inserted before the prefix, not after the prefix+comment
		    if ( $after =~ m/^\s*(\w+)\s*\(\*/ ) {
			# there was a comment after the word after the colon
			$possibleprefix = $1;
			# set $peekafter to the stuff after the match, i.e. start of comment text
			$peekafter = $';
			$peekafter =~ m/\*\)\s*/;  # MUST succeed if comment matches
			# set $peektext to the stuff after the match, i.e. what's after the comment
			$peekafter = $';           
			if ( $peekafter  =~ m/^\s*\(\#/ ) {
			    # there was a pattern-begin after the comment
			    $prefix = $possibleprefix; 
			}
		    }
		}
	    }
	    
	    $marker = $match;
	    $match = "";

	    if ( @ids == 1 ) {
		# keep identifier for next "(#" found
		$patternid = $ids[0];
		$patternid =~ s/\s//g;
	    } else {
		$patternid = "";
	    }

	    $before = $head;
	    foreach $id ( @ids ) {
		$id =~ m/(\w+)/; # MUST succeed
		$anchor += 1;
		$idxid = "$1.$level($anchor)"; # $id without whitespace.
		$bid = "<b>$id</b>"; # anchored identifier
		if ( "$patterns" eq "" ){
		    if ( $prefix eq "" ){
			$before .= "$bid<A name=\"$idxid\"></A>";
		    } else { # prefix is present
			# Insert super- and sub pattern information
			$super{$prefix} .= "$idxid-";
			$l = $level; $l1 = $level+1; $l2 = $level+2;
			$before .= "$bid<A name=\"$idxid\"></A><A name=\"$prefix.$l:$subpatterns.$l1:$id.$l2\"></A>";
			$index[$indexid] = "$idxid\@$outfile";
			$indexid += 1;
			$index[$indexid] = "$prefix.$l:$subpatterns.$l1:$id.$l2\@$outfile";
			$indexid += 1;
		    }
		} else { # inner scope
		    if ( $prefix eq "" ){
			$before .= "$bid<A name=\"$patterns$idxid\"></A><A name=\"$idxid\"></A>";
			$index[$indexid] = "$idxid\@$outfile";
			$indexid += 1;
			$index[$indexid] = "$patterns$idxid\@$outfile";
			$indexid += 1;
		    } else { # prefix is present
			# Insert super- and sub pattern information
			$super{$prefix} .= "$patterns$idxid-";
			$l = $level; $l1 = $level+1; $l2 = $level+2;
			$before .= "$bid<A name=\"$patterns$idxid\"></A><A name=\"$idxid\"></A><A name=\"$patterns$prefix.$l:$subpatterns.$l1:$id.$l2\"></A>";
			$index[$indexid] = "$idxid\@$outfile";
			$indexid += 1;
			$index[$indexid] = "$patterns$idxid\@$outfile";
			$indexid += 1;
			$index[$indexid] = "$patterns$prefix.$l:$subpatterns.$l1:$id.$l2\@$outfile";
			$indexid += 1;
		    } # prefix present
		} # inner scope
		$before .= ",";
	    } # foreach id
	    $before =~ s/,$//;
	    $before .= $marker.$tail;
	} # $level <= $scope
    } # colon was found
    else {
	die "Something is wrong in while loop !!!";
    } # "switch" on $match finished
    
    $line .= $before.$match;
    $_ = $after;
} # while

$_ = $line."\n";

# Now insert the superpatterns collected in %super at the right places:
$external = "___Externally defined";

printf STDERR "Generating tables for superpatterns...\n" if $verbose==1;

foreach $superid ( keys %super ) {
    printf STDERR "  %s\n", $superid if $trace==1;
    @subs = split( /-/, $super{$superid});
    foreach $sub (@subs){
	printf STDERR "    %s\n", $sub if $trace==1;
	$sub =~ m/((\w+\.\d+\:)*)(\w+)\.(\d+)$/;
	$subprefix = $1; $subid = $3; $sublevel = $4;
	$superprefix = $subprefix; $superlevel = $sublevel;
	if ( "$superprefix" eq "" )
	{ $l = $sublevel; $l1 = $l+1; $l2 = $l+2;
	  s/(<A name=\")$subid\.$sublevel\s*\">/$&<A name=\"$sub:$superpattern.$l1:$superid.$l2\"> <\/a>/;
	  s/(<A name=\")$superid.\d+:($subpatterns.\d+:$subid)/$1$superid.$l:$2/;
      } else
      { loop: { if ( "$superprefix" ne "" )
		{ if ( m/\{\\v\s*$superprefix$superid.$superlevel\s*\}\}\}/ )
		  { $l = $sublevel; $l1 = $l+1; $l2 = $l+2;
		    s/(<A name=\")$superprefix$superid.$superlevel\s*\">/$&<A name=\"$sub:$superpattern.$l1:$superid.$l2\"> <\/a>/;
		    s/(<A name=\")$subprefix$superid.\d+:($subpatterns.\d+:$subid)/$1$superprefix$superid.$l:$2/;
		} elsif ( $superprefix =~ m/\w+\.(\d+)\:$/ )
		{ $superprefix = $`; $superlevel= $1;
		  redo loop;
	      } else { $superprefix = ""; $superlevel = 1; }
	      } else
	      { $l = $sublevel; $l1 = $l+1; $l2 = $l+2;
		s/$/$&<A name=\"$sub:$superpattern.$l1:$superid.$l2\"> <\/a>\n/;
		s/(<A name=\")$subprefix$superid.\d+:$subpatterns.\d+:$subid.\d+/$1$external.1:$superid.2:$subpatterns.3:$subid.4/;
	    }
	    }
    }
    }
}

# Prefix to indicate one indexlevel indentation.
$indent="|  ";


# Remove levels on single index-entries.
#s/(\{\\v\s*\w+)\.\d+/$1/g;

#printf STDERR "Inserting \"$indent\" markers...\n" if $verbose==1;
# Insert indentation patterns for each indentation.
#while ( m/[ :](\w+)\.(\d+)[:}]/ ) {
#	$id = $1; $level = $2;
#       printf STDERR "  %s level %d\n", $id, $level if $trace==1;
#	$indents = $indent x ($level-1);
#	s/([ \:])$id\.$level([\:}])/$1$indents$id$2/;
#}

printf STDERR "Cleaning up...\n" if $verbose==1;

# Clean up
s/\001/:/g;
s/\002/\(\#/g;
s/\003/\#\)/g;
s/\004/:/g;
s/\005/</g;
s/\006/>/g;
s/\007/&amp;/g;
s/\021/&lt;/g;
s/\022/&gt;/g;

printf STDERR "Writing to $outfile ... " if $verbose==1;
open (STDOUT, ">$outfile") || die "\nCannot open $outfile for writing: $!\n";
&print_header($title);
print;
&print_trailer($title);
close (STDOUT);
printf STDERR "done.\n" if $verbose==1;


printf STDERR "Writing index to $indexfile ... " if $verbose==1;
open (STDOUT, ">$indexfile") || die "\nCannot open $indexfile for writing: $!\n";
&print_index();
close (STDOUT);
printf STDERR "done.\n" if $verbose==1;
