#!/usr/local/bin/perl -s

sub usage
{
    print "Usage: int2html.perl [-v] [-t] <interfacefiles>\n";
    print "  -v: print progress to STDERR\n";
    print "  -t: print trace to STDERR\n";
    print "  Generate HTML file in local directory for each <interfacefile>\n";
    print "  Also generates index.html with table of contents and idx.html with index.\n";
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
# If $index_super_subs is 1, super- and sub pattern indices are also added 
# in the following fashion (NYI for HTML):
#
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
#
# 1. Formatting of index HTML is not yet complete:
#    Attributes of a pattern should be shown indented without the
#    pattern name.
#    Subpatterns and superpatterns should be handled as in word.
#
# 2. superpatterns are not even generated?

# Style sheet:
$css = "../../style/miadoc.css";

# File names:
$topfile = "../index.html";
$indexfile = "inx.html";
$contentsfile = "index.html";

# Flags
$index_super_subs=0;

sub print_button
{
    local ($type, $href) = @_;
    local ($alt) = ucfirst ($type);
    if ("$href" eq ""){
	print "<A><IMG ALIGN=BOTTOM SRC=\"../../images/";
	print $type . "g.gif\" ALT=";
	print $alt . " BORDER=0></A>\n";
    } else {
	print "<A HREF=\"" .$href . "\">";
	print "<IMG ALIGN=BOTTOM SRC=\"../../images/";
	print $type . ".gif\" ALT=";
	print $alt . " BORDER=0></A>\n";
    }
}

sub print_std_buttons
{
    if ($filenumber==$#files){
	# last file
	&print_button("next", $indexfile);
    } else {
	&print_button("next", 
		      &strip_path(&strip_extension($files[$filenumber+1])) . ".html");
    }
    if ($filenumber==0){
	# first file
	&print_button("prev", $contentsfile);
    } else {
	&print_button("prev", 
		      &strip_path(&strip_extension($files[$filenumber-1])) . ".html");
    }
    &print_button("top", $topfile);
    &print_button("content", $contentsfile);
    &print_button("index", $indexfile);
}

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
EOT

    &print_std_buttons;

    print<<EOT;
<P></P>
<P>Interface Description</P>
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
<ADDRESS>Interface Description</ADDRESS>
<P></P>
EOT

    &print_std_buttons;

    print<<EOT;
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
EOT

    &print_button("next", "");
    &print_button("prev", 
		  &strip_path(&strip_extension($files[$#files])) . ".html");
    &print_button("top", $topfile);
    &print_button("content", $contentsfile);

    print<<EOT;
<P></P>
<P>Interface Description</P>
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
<ADDRESS>Interface Description</ADDRESS>
<P></P>
EOT

    &print_button("next", "");
    &print_button("prev", 
		  &strip_path(&strip_extension($files[$#files])) . ".html");
    &print_button("top", $topfile);
    &print_button("content", $contentsfile);

    print<<EOT;
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
	    print "<STRONG><FONT color=\"#BEBEBE\">$ch</FONT></STRONG> &nbsp; \n";
	}	    
    }
    print "<P></P>\n<HR>\n<P></P>\n<PRE CLASS=interface>\n";
}

sub print_index
{

    # Remove levels on single index-entries.
    #s/(\{\\v\s*\w+)\.\d+/$1/g;

    #printf STDERR "Inserting \"$indent\" markers in index ...\n" if $verbose;
    # Insert indentation patterns for each indentation.
    #
    # Prefix to indicate one indexlevel indentation.
    #$indent="|  ";
    #while ( m/[ :](\w+)\.(\d+)[:}]/ ) {
    #	$id = $1; $level = $2;
    #       printf STDERR "  %s level %d\n", $id, $level if $trace==1;
    #	$indents = $indent x ($level-1);
    #	s/([ \:])$id\.$level([\:}])/$1$indents$id$2/;
    #}

    @index = sort @index;
    local ($html_index, $initial_ch, $htmlfile, $i, %entries);

    $html_index = "";

    for($i = 0; $i <= $#index; $i++) {
	# delete traling file name (after '@')
	$index[$i] =~ s/(.+)\@(.+)/$1/;
	# save target file name
	$htmlfile = $2;
	$_ = $index[$i];

	# In betaenv: exit T[1:lgth] is taken to be
	# an identifer with name 1. Prevent this.
	next if (!&legal_identifier($_));
	
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

	# Block levels are present as such in the entries:
	#   foo:
	#     (# bar:
	#          (# kuk: 
	#               (# ... #)
	#          #)
	#     #);
	#
	# Index:
	#    foo
	#    foo:bar
	#    foo:bar:kuk
	#
	# Should print as this:
	#    foo
	#      bar
	#       kuk
	#
	if ($_ =~ m/(.*):([^:]+)/){
	    $scopes = $1;
	    $id = $2;
	    if ($entries{$scopes}){
		# foo:bar already emitted
		$html_index .= "&nbsp;" x (2* (1+&num_chars(':', $scopes)));
		$html_index .= "<A href=\"$htmlfile\#" . $index[$i] . "\">" . $id . "</A>\n";
		$entries{$_} = 1;
	    } else {
		$html_index .= "Index Error: $_ ($scopes) ($id)\n";
	    }
	} else {
	    $html_index .= "<A href=\"$htmlfile\#" . $index[$i] . "\">" . $_ . "</A>\n";
	    $entries{$_} = 1;
	}
    }
    &print_index_header;
    &print_index_toc;
    print $html_index;
    &print_index_trailer;
}

sub print_toc_header
{
    print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<TITLE>Interface Description: Table of Contents</TITLE>
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
</HEAD>
<BODY>
<P></P>
EOT

    &print_button("next", 
		  &strip_path(&strip_extension($files[0])) . ".html");
    &print_button("prev", "");
    &print_button("top", $topfile);
    &print_button("index", $indexfile);

    print<<EOT;
<P></P>
<P>Interface Description</P>
<HR>
<!---------------------------------------------------------->

<H1><A name="Interface.TOC">Table of Contents</A></H1>
<PRE CLASS=interface>
EOT
}

sub print_toc_trailer
{
    print<<EOT;
</PRE>
<!---------------------------------------------------------->
<HR>
<P></P>
<ADDRESS>Interface Description</ADDRESS>
<P></P>
EOT

    &print_button("next", 
		  &strip_path(&strip_extension($files[0])) . ".html");
    &print_button("prev", "");
    &print_button("top", $topfile);
    &print_button("index", $indexfile);

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub print_toc
{
    &print_toc_header;
    print "<UL>\n";
    for ($i=0; $i<=$#htmlfiles; $i++){
	print "<LI><A HREF=\"" . $htmlfiles[$i] . ".html\">";
	print $htmlfiles[$i] ." Interface</A></LI>\n";
    }
    print "<LI><A HREF=\"" . $indexfile . "\">Index</A></LI>\n";
    print "</UL>\n";
    &print_toc_trailer;
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

sub legal_identifier

{
    local ($id) = @_[0];
    return ($id =~ m/[a-zA-Z_]\w*/);
}

sub num_chars
# Occurences of $ch in $string
{
    local ($ch, $string) = @_;
    local ($i, $num);
    $num=0;
    for ($i=0; $i<length($string); $i++){
	$num++ if (substr($string, $i, 1) eq "$ch");
    }
    #print STDERR "num_chars($ch, $string) = $num\n";
    return $num;
}

sub process_file
{
    local ($file) = @_[0];

    $title=ucfirst(&strip_path(&strip_extension($file))) . " Interface";
    $outfile=&strip_path(&strip_extension($file)) . ".html";

    # Read entire input-stream into $line.

    printf STDERR "\nReading $file ...\n" if $verbose==1;

    if (!open(INT, $file)){
	print "Cannot open $file for reading: $!\n";
	return;
    }

    $line="";
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

    if ($index_super_subs){
	# Index text for subpatterns.
	$subpatterns="_subpatterns";
	# Index text for superpatterns.
	$superpattern="__superpattern";
    }

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
		    print "No level specified in idx= command";
		    return;
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
		    print "*** PATTERNS is wrong: $patterns";
		    print "*** context:";
		    print "\n------------\n";
		    print substr($line, -100,100);
		    print "\n------------\n";
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
		    # In betaenv: exit T[1:lgth] is taken to be
		    # an identifer with name 1. Prevent this.
		    if (&legal_identifier($id)){
			$bid = "<B>$id</B>"; # boldface anchored identifier
		    } else {
			$bid = $id;
		    }
		    if ( "$patterns" eq "" ){
			if ( ($prefix eq "") || (!$index_super_subs) ){
			    $before .= "$bid<A name=\"$idxid\"></A>";
			    $index[$indexid++] = "$idxid\@$outfile";
			} else { 
			    # prefix is present
			    # Insert super- and sub pattern information
			    $super{$prefix} .= "$idxid-";
			    $l = $level; $l1 = $level+1; $l2 = $level+2;
			    $before .= "$bid<A name=\"$idxid\"></A><A name=\"$prefix.$l:$subpatterns.$l1:$id.$l2\"></A>";
			    $index[$indexid++] = "$idxid\@$outfile";
			    $index[$indexid++] = "$prefix.$l:$subpatterns.$l1:$id.$l2\@$outfile";
			}
		    } else { 
			# inner scope
			if ( ($prefix eq "") || (!$index_super_subs) ){
			    $before .= "$bid<A name=\"$patterns$idxid\"></A><A name=\"$idxid\"></A>";
			    $index[$indexid++] = "$idxid\@$outfile";
			    $index[$indexid++] = "$patterns$idxid\@$outfile";
			} else { 
			    # prefix is present
			    # Insert super- and sub pattern information
			    $super{$prefix} .= "$patterns$idxid-";
			    $l = $level; $l1 = $level+1; $l2 = $level+2;
			    $before .= "$bid<A name=\"$patterns$idxid\"></A><A name=\"$idxid\"></A><A name=\"$patterns$prefix.$l:$subpatterns.$l1:$id.$l2\"></A>";
			    $index[$indexid++] = "$idxid\@$outfile";
			    $index[$indexid++] = "$patterns$idxid\@$outfile";
			    $index[$indexid++] = "$patterns$prefix.$l:$subpatterns.$l1:$id.$l2\@$outfile";
			} # prefix present
		    } # inner scope
		    $before .= ",";
		} # foreach id
		$before =~ s/,$//;
		$before .= $marker.$tail;
	    } # $level <= $scope
	} # colon was found
	else {
	    print "Something is wrong in while loop !!!";
	    return;
	} # "switch" on $match finished
	
	$line .= $before.$match;
	$_ = $after;
    } # while

    $_ = $line."\n";

    if ($index_super_subs){
	# Now insert the superpatterns collected in %super at the right places:
	$external = "___Externally defined";
	#FIXME: no insertion into $index!!!
	
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
    }

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
    if (!open (STDOUT, ">$outfile")){
	print "\nCannot open $outfile for writing: $!\n";
	return;
    }
    &print_header($title);
    print;
    &print_trailer($title);
    close (STDOUT);

    push @htmlfiles, &strip_extension($outfile);

    printf STDERR "done.\n" if $verbose==1;

}

################ MAIN ####################

if ($#ARGV==-1){
    &usage();
    exit 1;
}

$verbose=$v;
$trace=$t;

@files = @ARGV;
for ($filenumber=0; $filenumber<=$#ARGV; $filenumber++){
    &process_file($files[$filenumber]);
}

printf STDERR "\nWriting common index to $indexfile ... " if $verbose==1;
open (STDOUT, ">$indexfile") || die "\nCannot open $indexfile for writing: $!\n";
&print_index();
close (STDOUT);
printf STDERR "done.\n" if $verbose==1;

printf STDERR "\nWriting table of contents to $contentsfile ... " if $verbose==1;
open (STDOUT, ">$contentsfile") || die "\nCannot open $contentsfile for writing: $!\n";
&print_toc();
close (STDOUT);
printf STDERR "done.\n" if $verbose==1;
