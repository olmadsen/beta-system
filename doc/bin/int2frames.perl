#!/usr/local/bin/perl -s

sub usage
{
    print "Usage: int2html.perl [-c] [-v] [-w] [-t] [-f] [-x] <interfacefiles>\n";
    print "  -c: leave out Mjolner Informatics Copyright\n";
    print "  -v: print progress to STDERR\n";
    print "  -w: special Wiki server variant\n";
    print "  -t: print trace to STDERR\n";
    print "  -f: use full paths to style sheets, images, javascripts\n";
    print "  -x: reference images, javascripts, stylesheets three directory levels up.\n";
    print "      default is two directory levels up.\n";
    print "  Generate HTML file in local directory for each <interfacefile>\n";
    print "  Also generates index.html with table of contents and idx.html with index.\n";
}
$verbose=$v;
$trace=$t;
$extradir=$x;
$fullpath=$f;
$nocopyright=$c;
$wiki=$w;

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
# Indexed words are set in bold.
#
# FIXME:
# BUGS:
#   1. "enter (foo, type##)" where type is pattern variable does not work
#      Has to be written "enter (foo, type ## )" Currently gives warning.
#
#   2. "do" inside comments tend to "eat" the newline after the "do"?

# TODO: 
#
# 6. Generate tiles like "Foo Interface Descriptions" instead of just
#    "Interface Descriptions". "Foo" can be found as ucfirst($directory)
#    where $directory is directory of the Makefile.
#


##### Configuration #####

if ($wiki){
    $fullpath=1;
    $nocopyright=1;
}

if ($nocopyright){
    $copyright = "";
} else {
    $copyright = "<FONT size=-1>&COPY; <A HREF=\"http://www.mjolner.com\" TARGET=\"_top\">Mj&oslash;lner Informatics</A></FONT>";
}
if ($fullpath){
    if ($extradir){
	print "int2html.perl: Both -f and -x specified: -x is ignored\n";
    }
    $css = "http://www.mjolner.com/mjolner-system/documentation/style/miadoc.css";
    $scriptdir = "http://www.mjolner.com/mjolner-system/documentation/javascript";
    $imagedir = "http://www.mjolner.com/mjolner-system/documentation/images/";
    $topfile = "http://www.mjolner.com/mjolner-system/documentation/index.html";
    $upfile = "http://www.mjolner.com/mjolner-system/documentation/index.html";
} else {
    if ($extradir){
	$css = "../../../style/miadoc.css";
	$scriptdir = "../../../javascript";
	$imagedir = "../../../images/";
	$topfile = "../../../index.html";
	$upfile = "../../index.html";
    } else {
	$css = "../../style/miadoc.css";
	$scriptdir = "../../javascript";
	$imagedir = "../../images/";
	$topfile = "../../index.html";
	$upfile = "../index.html";
    }
}

# Other file names:
$lastmodscript = "$scriptdir/lastmod.js";
$hashfromparent = "$scriptdir/hashfromparent.js";
$printframe = "$scriptdir/printframe.js";
$indexfile = "inx.html";
($indexnavfile = $indexfile) =~ s/\.html$/-nav.html/;
($indexdocfile = $indexfile) =~ s/\.html$/-body.html/;
if ($wiki){
    $tocfile = $ENV{'TOCURL'};
} else {
    $tocfile = "index.html";
}
($tocnavfile = $tocfile) =~ s/\.html$/-nav.html/;
($tocdocfile = $tocfile) =~ s/\.html$/-body.html/;


###### Functions for buttons and standard HTML header and frameset ##

sub print_button
{
    local ($type, $href) = @_;
    local ($alt) = ucfirst ($type);
    local ($javascript) = "";

    # special case for "prev":
    $alt =~ s/Prev/Previous/g;

    if ($href =~ m/^javascript:/ ){
	print<<"EOT";
<A HREF="$href" TARGET="_self"><IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="${imagedir}${type}g-jsr.gif" ALT="${alt} (JavaScript Required)" NAME="$alt" BORDER=0></A>
EOT
        $javascript = "document.images.$alt.src = \"${imagedir}${type}.gif\";";

    } elsif ("$href" eq ""){
	print "<A><IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC=\"$imagedir";
	print $type . "g.gif\" ALT=";
	print $alt . " NAME=\"$alt\" BORDER=0></A>\n";
    } else {
	print "<A HREF=\"" . $href . "\"" . ">";
	print "<IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC=\"$imagedir";
	print $type . ".gif\" ALT=";
	print $alt . " NAME=\"$alt\" BORDER=0></A>\n";
    }
    
    return $javascript;
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
	if ($wiki){
	    &print_button("prev", "");
	} else {
	    &print_button("prev", $tocfile);
	};
    } else {
	&print_button("prev", 
		      &strip_path(&strip_extension($files[$filenumber-1])) . ".html");
    }
    &print_button("top", $topfile) if (!$wiki);
    &print_button("content", $tocfile);
    &print_button("index", $indexfile);
    return &print_button("print", "javascript:parent.${basename}Body.printframe(parent.${basename}Body);");
}

sub print_header
{
    local ($title, $flags) = @_;

    print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<!-- Autogenerated file - do not edit -->
<HEAD>
<TITLE>$title</TITLE>
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
EOT

    print <<"EOT" if ($flags&1);
<SCRIPT DEFER TYPE="text/javascript" LANGUAGE="JavaScript" SRC="$hashfromparent"></SCRIPT>
EOT

    print <<"EOT" if ($flags&2);
<SCRIPT DEFER TYPE="text/javascript" LANGUAGE="JavaScript" SRC="$printframe"></SCRIPT>
EOT

    print <<"EOT" if ($flags&4);
<BASE TARGET="_top">
</HEAD>
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
<TABLE cols=3 border=0 width=100%>
<TR>
<TD width="40%" align="left"><ADDRESS>$title</ADDRESS></TD>
<TD width="20%" align="center">$copyright</TD>
<TD width="40%" align="right"><SCRIPT LANGUAGE=JavaScript SRC="$lastmodscript"></SCRIPT></TD>
</TABLE>
EOT

#    print<<EOT;
#</PRE>
#<SCRIPT LANGUAGE=JavaScript TYPE="text/javascript" SRC="$scriptdir/footer.js">
#<SCRIPT LANGUAGE=JavaScript TYPE="text/javascript">
#<--
#footer("$title");
#// -->
#</SCRIPT>
#EOT

}

sub print_frameset()
{
    
    local ($title, $basename, $height) = @_;

    &print_header($title,4);

    print<<"EOT";
<FRAMESET border=0 noresize scrolling=no ROWS="$height,*">
   <NOFRAMES>
   <BODY>
   <H1>$title</H1>
   To display this page correctly, frames are required. Your browser 
   does not support it, or has not enabled it.  
   <P>
   Click here instead:
   <UL>
     <LI><A href="$basename-body.html">$title</A>
   </UL>
   </BODY>
   </NOFRAMES>
   <FRAME SRC="$basename-nav.html" NAME="${basename}Nav" SCROLLING=NO MARGINHEIGHT=1>
   <FRAME SRC="$basename-body.html" NAME="${basename}Body">
</FRAMESET>
</HTML>
EOT
}

################### Functions for body files ######################

sub print_nav_frame
{
    local ($title) = @_;
    local ($javascript);

    &print_header($title,4);

    print <<EOT;
<BODY>
<TABLE VALIGN=MIDDLE WIDTH="100%" CELLPADDING=0 CELLSPACING=2>
<TR>
<TD NOWRAP>
EOT

    $javascript = &print_std_buttons();

    print<<EOT;
</TD>
<TH NOWRAP ALIGN=right>$title</TH>
</TR>
</TABLE>
EOT

    print<<"EOT" if ("$javascript" ne "");
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
$javascript
</SCRIPT>
EOT

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub print_body_frame(){
    local ($title, $basename, $contents) = @_;
    
    &print_header($title,4+2+1);
    print<<"EOT";
<BODY onLoad='HashFromParent()'>
<H1><A name="$basename">$title</A></H1>
<PRE CLASS=interface>
EOT
    print $contents; # full interface file as build in $_ above.
    &print_trailer($title);
    print<<EOT;
</BODY>
</HTML>
EOT
}

############### Functions for index generation ####################

sub print_index_nav_frame
{
    local ($title, $basename) = @_;

    &print_header($title,4);

    print <<EOT;
<BODY>
<TABLE VALIGN=MIDDLE WIDTH="100%" CELLPADDING=0 CELLSPACING=5>
<TR>
<TD>
EOT

    &print_button("next", "");
    &print_button("prev", 
		  &strip_path(&strip_extension($files[$#files])) . ".html");
    &print_button("top", $topfile) if (!$wiki);
    &print_button("content", $tocfile);

    print<<EOT;
</TD>
<TH ALIGN=right>Interface Descriptions: Index</TH>
</TR>
<TR>
<TD colspan=2>
EOT

    &calculate_index();
    &print_index_toc();

    print<<EOT;
</TD>
</TR>
</TABLE>
</BODY>
</HTML>
EOT
}

sub print_index_toc
{
    local ($i, $ch);
    print "<HR>\n";
    for ($i=65; $i<=90; $i++){
	$ch = sprintf ("%c", $i);
	if ($caps{$ch}){
	    print "<STRONG><A HREF=\"inx-body.html#_$ch\" TARGET=\"inxBody\">$ch</A></STRONG> &nbsp; \n";
	} else {
	    # no indices starting with $ch
	    print "<STRONG CLASS=disabled>$ch</STRONG> &nbsp; \n";
	}	    
    }
    print "<HR><P></P>\n";
}

sub print_index_header()
{
    local ($title) = @_;

    &print_header($title,4);

    print<<"EOT";
<BODY>

<NOSCRIPT>
<IMG SRC="$imagedir/warning.gif" ALT="Warning!" width=16 height=16 align=left>
<EM>JavaScript Required!</EM>
<BLOCKQUOTE>
<P>It appears, that either your browser does not support JavaScript, or you
have disabled scripting.<BR>
The links to identifiers below will not work correctly without JavaScript.<BR>
They will, however, take you to the correct file. But you must use your
browser's Find facility to get to the correct location within the page.</P>
</BLOCKQUOTE>
</NOSCRIPT>

<H1><A name="Index.identifiers">Index of Identifiers</A></H1>
<PRE CLASS=interface>
EOT
}

sub print_index_trailer()
{
    print<<EOT;
</PRE>
EOT
    &print_trailer();

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub calculate_index()
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

    # Sort index ignoring case
    @index = sort {lc($a) cmp lc($b)} @index;
    local ($prev_id, $prev_no, $initial_ch, $htmlfile, $i, %entries);

    #print STDERR "index:++++++++++++++++++++\n";
    #print STDERR join ("\n", @index);
    #print STDERR "indexend:++++++++++++++++++++\n";

    $html_index = "";
    $prev_id = "";
    $prev_no = 1;

    for($i = 0; $i <= $#index; $i++) {
	#$html_index .= "[$index[$i]]\n" if $trace;
	# delete traling file name (after '@')
	$index[$i] =~ s/(.+)\@(.+)/$1/;
	# save target file name
	$htmlfile = $2;
	$_ = $index[$i];

	# In betaenv: exit T[1:lgth] is taken to be
	# an identifer with name 1. Prevent this.
	if (!&legal_identifier($_)){
	    printf STDERR "skipped illegal identifier: $_\n" if $verbose;
	    next;
	}

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
	    $html_index .= "</PRE><H2><A name=\"_$initial_ch\">$initial_ch<\/A><\/H2><PRE CLASS=interface>\n";
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
	# Index entries:
	#    foo
	#    foo:bar
	#    foo:bar:kuk
	#
	# Should print as this:
	#    foo
	#      bar
	#       kuk
	#
	
	# print STDERR "$index[$i]\n";

	# Handle ANONYMOUS especially
	if ($_ =~ m/^ANONYMOUS:/){
	    if (!$entries{"ANONYMOUS"}){
		print STDERR "Treating ANONYMOUS specially\n" if $verbose;
		$html_index .= "\n  <I>Anonymous pattern</I>";
		$entries{"ANONYMOUS"} = 1;
	    }
	}
	# Handle betaenv specially
	if ( ($index[$i] =~ m/^betaenv.1/) && ($htmlfile eq "betaenv.html")){
	    if (!$entries{"betaenv"}){
		print STDERR "Treating betaenv specially\n" if $verbose;
		$html_index .= "\n  <I><A HREF=\"betaenv.html\">betaenv</I></A>";
		$entries{"betaenv"} = 1;
	    }
	}
	if ($_ =~ m/(.*):([^:]+)/){
	    $scopes = $1;
	    $id = $2;
	    # We are in a specific scope. There cannot be identical index entries
	    # here (BETA semantic error!). So no need to check for prev_id.
	    $prev_id="";
	    $prev_no=0;
	    if ($entries{$scopes}){
		# foo:bar already emitted
		$html_index .= "\n";
		# indent with double-spaces
		$html_index .= "  " x (1+&num_chars(':', $scopes));
		$html_index .= "  <A href=\"$htmlfile?" . $index[$i] . "\">" . $id . "</A>";
		$entries{$_} = 1;
	    } else {
		$html_index .= "Index Error: $_ ($scopes) ($id)\n";
	    }
	} else {
	    $id = $_;
	    if ($prev_id eq $id){
		$prev_no++;
		if (!($prev_no % 10)){
		    # break line of references
		    $html_index .= "\n   ";
		}
		$html_index .= " <A href=\"$htmlfile?" . $index[$i] . "\">[" . $prev_no . "]</A>";
	    } else {
		$prev_no=1;
		$html_index .= "\n";
		$html_index .= "  <A href=\"$htmlfile?" . $index[$i] . "\">" . $id . "</A>";
		$prev_id = $id;
	    }
	    $entries{$_} = 1;
	}
    }
}

sub print_index_body_frame()
{
    &print_index_header;
    print $html_index;
    &print_index_trailer;
}

####### Functions for table of contents #######################

sub print_toc_nav_frame
{
    local ($title) = @_;

    &print_header($title,4);

    print <<EOT;
<BODY>
<TABLE VALIGN=MIDDLE WIDTH="100%" CELLPADDING=0 CELLSPACING=5>
<TR>
<TD>
EOT

    &print_button("next", 
		  &strip_path(&strip_extension($files[0])) . ".html");
    &print_button("prev", "");
    &print_button("up", $upfile) if (!$wiki);
    &print_button("top", $topfile) if (!$wiki);
    &print_button("index", $indexfile);

    print<<EOT;
</TD>
<TH ALIGN=right>Interface Descriptions: Contents</TH>
</TR>
</TABLE>
</BODY>
</HTML>
EOT
}

sub print_toc_header
{
    local ($title) = @_;

    &print_header($title,4);

    print<<EOT;
<BODY>
<P></P>
<H1><A name="_toc">Table of Contents</A></H1>
EOT
}

sub print_toc_trailer
{
    local ($title) = @_;
    
    &print_trailer($title);

    print<<EOT;
<P></P>
</BODY>
</HTML>
EOT
}

sub print_toc_body_frame
{
    local ($title) = @_;
    local ($htmlfile);

    &print_toc_header($title);
    print "<DIV CLASS=toc>\n";
    print "<DL>\n";
    print "<DT><DD>\n";
    print "<DL>\n";
    for ($i=0; $i<=$#htmlfiles; $i++){
	($htmlfile = $htmlfiles[$i]) =~ s/\-body$//;
	print "<DT><A HREF=\"" . $htmlfile . ".html\">";
	print $htmlfile ." Interface</A>\n<DD>\n";
    }
    print "<DT>&nbsp;\n<DD>\n";
    print "<DT><A HREF=\"" . $indexfile . "\">Index</A>\n<DD>\n";
    print "</DL>\n";
    print "</DL>\n";
    print "</DIV>\n";
    &print_toc_trailer;
}


######################## Utility functions #####################

sub strip_extension
{
    local ($string) = @_;
    if ($wiki) {
	# hack for wiki server
	$string =~ s/\.int$/.bet/;
	return $string;
    };

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

    $basename=&strip_path(&strip_extension($file));
    $outfile=$basename . ".html";

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

    printf STDERR "Searching for idx-comments/patterns/colons .....\n" if $verbose==1;
    if   (! m/\n[ \t]*\(\*\s+idx([\+\-\=\001])\s*(\d*)\s*\*\)\s*\n|\(\#|\#\)|::?<?/i ){
	printf STDERR "  None found - emitting without markup\n" if $verbose==1;
	$line = $_;
    }
    while(  m/\n[ \t]*\(\*\s+idx([\+\-\=\001])\s*(\d*)\s*\*\)\s*\n|\(\#|\#\)|::?<?/i ){
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
	    # add previously found identifier in scope description
	    if ( "$patternid" ne "" ) {
		$patterns .= "$patternid.$level:";
		printf STDERR "***  %s\n", $patternid if $trace==1;
	    } else {	
		if (($outfile eq "betaenv.html") && ($level == 1)){
		    $patterns .= "betaenv.1:";
		    printf STDERR "  BETAENV\n" if $trace==1;
		} else {
		    $patterns .= "ANONYMOUS.$level:";
		    printf STDERR "  ANONYMOUS\n" if $trace==1;
		}
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
		# Identifiers must start with alpha or _.
		# In betaenv, there is "exit T[1:lgth], which would
		# cause 1: to be identified as identifier.
		# However, if [a-zA-Z_] is used instead of \w,
		# the "[1:" does not get into the output (:-(
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
			# don't change $tail or $after (historical: superpattern index generation)
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
		    #print STDERR "IDS: @ids\n";
		    $id =~ m/(\w+)/; # MUST succeed
		    $anchor += 1;
		    $idxid = "$1.$level($anchor)"; # $id without whitespace.
		    if (&legal_identifier($id)){
			$bid = "<B>$id</B>"; # boldface anchored identifier
		    } else {
			$bid = $id;
		    }
		    if ( "$patterns" eq "" ){
			$before .= "$bid<A name=\"$idxid\"></A>";
			$index[$indexid++] = "$idxid\@$outfile";
			#print STDERR "111. {$idxid\@$outfile}\n";
		    } else { 
			# inner scope
			$before .= "$bid<A name=\"$patterns$idxid\"></A><A name=\"$idxid\"></A>";
			#print STDERR "222. {$idxid\@$outfile}\n";
			$index[$indexid++] = "$idxid\@$outfile";
			#print STDERR "333. {$patterns$idxid\@$outfile}\n";
			$index[$indexid++] = "$patterns$idxid\@$outfile";
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

    printf STDERR "Writing frameset to $outfile ... " if $verbose==1;
    if (!open (STDOUT, ">$outfile")){
	print "\nCannot open $outfile for writing: $!\n";
	return;
    }
    &print_frameset($title, $basename,45);
    close (STDOUT);
    printf STDERR "done.\n" if $verbose==1;
    
    $outfile = $basename . "-nav.html";
    printf STDERR "Writing navigation frame to $outfile ... " if $verbose==1;
    if (!open (STDOUT, ">$outfile")){
	print "\nCannot open $outfile for writing: $!\n";
	return;
    }
    &print_nav_frame($title);
    close (STDOUT);
    printf STDERR "done.\n" if $verbose==1;
    
    $outfile = $basename . "-body.html";
    printf STDERR "Writing body frame to $outfile ... " if $verbose==1;
    if (!open (STDOUT, ">$outfile")){
	print "\nCannot open $outfile for writing: $!\n";
	return;
    }
    
    &print_body_frame($title, $basename, $_);
    close (STDOUT);
    printf STDERR "done.\n" if $verbose==1;

    push @htmlfiles, &strip_extension($outfile);


}

################ MAIN ####################

if ($#ARGV==-1){
    &usage();
    exit 1;
}

$indexid=0;

@files = @ARGV;
for ($filenumber=0; $filenumber<=$#ARGV; $filenumber++){
    &process_file($files[$filenumber]);
}


### Generate index ###
printf STDERR "\nWriting common index ...\n" if $verbose=1;

printf STDERR "Writing frameset to $indexfile ..." if $verbose==1;
if (!open (STDOUT, ">$indexfile")){
    print "\nCannot open $indexfile for writing: $!\n";
    return;
}
&print_frameset("Interface Descriptions: Index", "inx", 100);
close (STDOUT);
printf STDERR "done.\n" if $verbose==1;

printf STDERR "Writing navigation frame to $indexnavfile ... " if $verbose==1;
if (!open (STDOUT, ">$indexnavfile")){
    print "\nCannot open $indexnavfile for writing: $!\n";
    return;
}
&print_index_nav_frame("Interface Descriptions: Index", "inx");
close (STDOUT);
printf STDERR "done.\n" if $verbose==1;

printf STDERR "Writing body frame to $indexdocfile ... " if $verbose==1;
if (!open (STDOUT, ">$indexdocfile")){
    print "\nCannot open $indexdocfile for writing: $!\n";
    return;
}
&print_index_body_frame("Interface Descriptions: Index");
close (STDOUT);
printf STDERR "done.\n" if $verbose==1;

### Generate table of contents ###

if (!$wiki){
    printf STDERR "\nWriting common toc ...\n" if $verbose=1;
    
    printf STDERR "Writing frameset to $tocfile ..." if $verbose==1;
    if (!open (STDOUT, ">$tocfile")){
	print "\nCannot open $tocfile for writing: $!\n";
	return;
    }
    &print_frameset("Interface Descriptions: Contents", "index", 45);
    close (STDOUT);
    printf STDERR "done.\n" if $verbose==1;
    
    printf STDERR "Writing navigation frame to $tocnavfile ... " if $verbose==1;
    if (!open (STDOUT, ">$tocnavfile")){
	print "\nCannot open $tocnavfile for writing: $!\n";
	return;
    }
    &print_toc_nav_frame("Interface Descriptions: Contents");
    close (STDOUT);
    printf STDERR "done.\n" if $verbose==1;
    
    printf STDERR "Writing body frame to $tocdocfile ... " if $verbose==1;
    if (!open (STDOUT, ">$tocdocfile")){
	print "\nCannot open $tocdocfile for writing: $!\n";
	return;
    }
    &print_toc_body_frame("Interface Descriptions: Contents");
    close (STDOUT);
    printf STDERR "done.\n" if $verbose==1;
}
printf STDERR "done.\n" if $verbose==1;

