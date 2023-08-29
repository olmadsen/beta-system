#!/usr/bin/perl -s # -w

#use strict;

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

##### Global variables ####
# Variables set from command options
my $verbose     = (defined($v)) ? 1 : 0;
my $trace       = (defined($t)) ? 1 : 0;
my $extradir    = (defined($x)) ? 1 : 0;
my $fullpath    = (defined($f)) ? 1 : 0;
my $nocopyright = (defined($c)) ? 1 : 0;
my $wiki        = (defined($w)) ? 1 : 0;
# Mentioning of option variables once more to prevent "used only once" warns
# NO overwrites command line values!
#$v = $t = $x = $f = $c = $w = "";

# Other global variables
my $insert_validhtml40 = 0;
my $scriptdir = "";
my $imagedir = "";
my $topfile = "";
my $upfile = "";
my $copyright = "";
my $lastmodscript = "";
my $hashfromparent = "";
my $printframe = "";
my $fixprintbutton = "";
my $indexfile = "";
my $indexnavfile = "";
my $indexdocfile = "";
my $tocfile = "";
my $css = "";
my $wikiroot = "";
my $wikidoc = "";
my $wikihelp = "";
my $bodyatt = "";

# Flags for sub print_header
my $flag_hash  = 1;
my $flag_print = 2;
my $flag_base  = 4;
my $flag_frame = 8;

print STDERR "Generating WIKI layout.\n" if ($wiki && $verbose);

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
}

if ($fullpath){
    if ($extradir){
	print "int2html.perl: Both -f and -x specified: -x is ignored\n";
    }
    $css = <<EOT;
<LINK REL="stylesheet" HREF="http://www.mjolner.com/mjolner-system/documentation/style/miadoc.css" TYPE="text/css">
EOT
    $scriptdir = "http://www.mjolner.com/mjolner-system/documentation/javascript";
    $imagedir = "http://www.mjolner.com/mjolner-system/documentation/images/";
    $topfile = "http://www.mjolner.com/mjolner-system/documentation/index.html";
    $upfile = "http://www.mjolner.com/mjolner-system/documentation/index.html";
} else {
    if ($extradir){
	$css = <<EOT;
<LINK REL="stylesheet" HREF="../../../style/miadoc.css" TYPE="text/css">
EOT
	$scriptdir = "../../../javascript";
	$imagedir = "../../../images/";
	$topfile = "../../../index.html";
	$upfile = "../../index.html";
    } else {
	$css = <<EOT;
<LINK REL="stylesheet" HREF="../../style/miadoc.css" TYPE="text/css">
EOT
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
$fixprintbutton = "$scriptdir/fixprintbutton.js";
$indexfile = "inx.html";
($indexnavfile = $indexfile) =~ s/\.html$/-nav.html/;
($indexdocfile = $indexfile) =~ s/\.html$/-body.html/;
$tocfile = "index.html";

if ($nocopyright){
    $copyright = "";
} else {
    $copyright = <<EOT;
<FONT size="-1">&#169; <A HREF="http://www.mjolner.com" TARGET="_top">Mj&oslash;lner Informatics</A></FONT>
EOT
}

if ($wiki){
    $css = <<EOT;
<STYLE REL="stylesheet" TYPE="text/css">
  A:link, A:visited, A:active {text-decoration:none}              
  H1, H2, H3, H4 {font-family:sans-serif}
  .reverse        {color: white}
  .red            {color: red}
  .navigation     {font-family:sans-serif; font-size: 10pt}
  .title          {font-family:sans-serif; font-size: 24pt; font-weight: bold; color: blue}
  .logo           {font-size: 24pt; font-weight: bold}
  .description    {font-family:sans-serif; color: blue}
  .category       {font-family:sans-serif}
  .version        {font-family:sans-serif; font-size: 9pt}
  .preview        {font-family:sans-serif; font-size: 24pt; font-weight: bold; color: #7f0000}
  .disabled       { color: #BEBEBE; background: none; }
  PRE.interface   { font-size: 12pt; font-family: Courier, monospace; white-space: pre; }
</STYLE>
EOT
    $copyright = "";
    $tocfile = $ENV{'TOCURL'} || "";
    $wikiroot = $ENV{'WIKIROOT'} || "";
    ($wikidoc = $wikiroot ) =~ s%.*/([^/]+)/?$%$1%;
    ($wikihelp = $wikiroot) =~ s%(.*/)[^/]+/?$%$1%;
    $wikihelp .= "/wiki/help.wiki";
    $bodyatt = " bgcolor=\"white\" text=\"black\"";
}

($tocnavfile = $tocfile) =~ s/\.html$/-nav.html/;
($tocdocfile = $tocfile) =~ s/\.html$/-body.html/;


###### Functions for buttons and standard HTML header and frameset ##

sub H1(){
    local ($name, $title) = @_;
    chomp $title;
    if ($wiki){
	return "<A name=\"$name\"><TABLE border=0 cellspacing=0 width=\"100%\"><TR><TD bgcolor=blue><H2 class=reverse>$title</H2></TD></TR></TABLE></A>\n";
    } else {
	if ($name eq ""){
	    return "<H1>$title</H1>\n";
	} else {
	    return "<H1><A name=\"$name\">$title</A></H1>\n";
	}
    }
}
sub H2(){
    local ($name, $title) = @_;
    chomp $title;
    if ($wiki){
	return "<A name=\"$name\"><TABLE border=0 cellspacing=0 width=\"100%\"><TR><TD bgcolor=\"#CCCCCC\"><H3>$title</H3></TD></TR></TABLE></A>\n";
    } else {
	if ($name eq ""){
	    return "<H2>$title</H2>\n";
	} else {
	    return "<H2><A name=\"$name\">$title</A></H2>\n";
	}
    }
}
sub H3(){
    local ($name, $title) = @_;
    chomp $title;
    if ($wiki){
	return "<H3>$title<HR noshade></H3>\n;"
    } else {
	if ($name eq ""){
	    return "<H3>$title</H3>\n";
	} else {
	    return "<H3><A name=\"$name\">$title</A></H3>\n";
	}
    }
}
sub H4(){
    local ($name, $title) = @_;
    chomp $title;
    if ($wiki){
	return "<H3>$title</H3>\n;"
    } else {
	if ($name eq ""){
	    return "<H4>$title</H4>\n";
	} else {
	    return "<H4><A name=\"$name\">$title</A></H4>\n";
	}
    }
}

sub print_valid_html_button()
{

    print<<EOT if ($insert_validhtml40);
<TABLE BORDER=0 ALIGN=RIGHT>
<TR>
<TD>
<A HREF="http://validator.w3.org/check/referer">
<IMG BORDER=0 SRC="${imagedir}vh40.gif" ALT="Valid HTML 4.01!" HEIGHT=31 WIDTH=88>
</A>
</TD>
</TR>
</TABLE>
<BR CLEAR=right>
EOT
}

sub print_button
{
    local ($type, $href, $alt) = @_;
    local ($name) = ucfirst ($type);
    local ($javascript) = "";

    if ($wiki){
	if ($href ne ""){
	    print "<A HREF=\"$href\">$name</A>\n";
	}
	return "";
    }

    if ($href =~ m/^javascript:/ ){
	print<<"EOT";
<A NAME="A$name" HREF="$href" TARGET="_self"><IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="${imagedir}${type}g-jsr.gif" ALT="${alt} (JavaScript Required)" NAME="$name" BORDER=0></A>
EOT
    } elsif ("$href" eq ""){
	print<<"EOT";
<A><IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="$imagedir${type}g.gif" ALT="$alt" NAME="$name" BORDER=0></A>
EOT
    } else {
	print<<"EOT";
<A HREF="$href"><IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="$imagedir$type.gif" ALT="$alt" NAME="$name" BORDER=0></A>
EOT
    }
    
    return $javascript;
}

sub print_std_buttons
{
    local ($next, $prev, $javascript);
    local ($target);
    ($target = $basename) =~ s/\./_/g;

    if ($filenumber==$#files){
	# last file
	&print_button("next", $indexfile, "Next: Interface Descriptions Index");
	print " | " if ($wiki);
    } else {
	$next = &strip_path(&strip_extension($files[$filenumber+1]));
	&print_button("next", 
		      "$next.html",
		      "Next: " . ucfirst($next) . " Interface");
	print " | " if ($wiki);
    }
    if ($filenumber==0){
	# first file
	if ($wiki){
	    # Print nothing
	} else {
	    &print_button("prev", $tocfile, "Previous: Interface Descriptions Contents");
	};
    } else {
	$prev = &strip_path(&strip_extension($files[$filenumber-1]));
	&print_button("prev", 
		      "$prev.html",
		      "Previous: " . ucfirst($prev) . " Interface");
	print " | " if ($wiki);
    }
    &print_button("top", $topfile, "Top: Manuals Main Entry") if (!$wiki);
    &print_button("content", $tocfile, "Interface Descriptions Contents");
    print " | " if ($wiki);
    &print_button("index", $indexfile, "Interface Descriptions Index");
    print " | " if ($wiki);
    $javascript = &print_button("print", "javascript:if (parent && parent.${target}Body){printframe(parent.${target}Body)}", "Print \u$basename Interface Frame");
    return $javascript;
}

sub print_header
{
    local ($title, $basename, $flags) = @_;
    local ($doctype);

    if ($flags&$flag_frame){
	$doctype=<<EOT
"-//W3C//DTD HTML 4.01 Frameset//EN"
                      "http://www.w3.org/TR/REC-html40/frameset.dtd"
EOT
    } else {
	$doctype=<<EOT
"-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
EOT
    }
    
    print<<EOT;
<!DOCTYPE HTML PUBLIC $doctype>
<HTML>
<!-- Autogenerated file - do not edit -->
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">
<TITLE>$title</TITLE>
$css
EOT

    print <<"EOT" if ($flags&$flag_hash);
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript" SRC="$hashfromparent"></SCRIPT>
EOT

    if ($flags&$flag_hash){
	if ($wiki){
	    my ($b) = $basename;
	    $b =~ s/\./_/g;
	    print <<"EOT";
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
<!--
    CheckParent2("$b", "$basename");
//-->
</SCRIPT>
EOT
	} else {
	    print <<"EOT";
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
<!--
    CheckParent("$basename");
//-->
</SCRIPT>
EOT
        }
    }

    print <<"EOT" if ($flags&$flag_print);
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript" SRC="$printframe"></SCRIPT>
EOT
    print <<"EOT" if (($flags&$flag_print) && !$wiki);
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript" SRC="$fixprintbutton"></SCRIPT>
EOT

    print <<"EOT" if ($flags&$flag_base);
<BASE TARGET="_parent">
EOT

    print<<EOT;
</HEAD>
EOT
}

sub print_trailer
{
    local ($title) = @_;

    return if ($wiki);

    print_valid_html_button();

    print<<EOT;
<P></P>
<!--++++++++++++++++++++++++++++++++++++++++++++++++++++++++-->
<HR>
<P></P>
<TABLE border=0 width="100%">
<TR>
<TD width="40%" align="left"><ADDRESS>$title</ADDRESS></TD>
<TD width="20%" align="center">${copyright}</TD>
<TD width="40%" align="right"><SCRIPT TYPE="text/javascript" LANGUAGE=JavaScript SRC="$lastmodscript"></SCRIPT></TD>
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
    local ($header) = &H1("", $title);
    local ($targetbase);
    local ($marginheight) = ($wiki)? "" : "MARGINHEIGHT=1";

    ($targetbase = $basename) =~ s/\./_/g;

    &print_header($title,"",($flag_base|$flag_frame));

    # FRAMESPACING and BORDER below are not valid HTML 4.0, 
    # but required by IE4 and NS4, respectively, to display this correctly
    # See e.g. http://www.idocs.com/tags/frames/noborder.html
    print<<"EOT";
<FRAMESET FRAMESPACING=0 FRAMEBORDER=0 BORDER=0 ROWS="$height,*">
   <NOFRAMES>
   <BODY$bodyatt>
   $header
   To display this page correctly, frames are required. Your browser 
   does not support it, or has not enabled it.  
   <P>
   Click here instead:
   <UL>
     <LI><A href="$basename-body.html">$title</A>
   </UL>
   </BODY>
   </NOFRAMES>
   <FRAME SRC="$basename-nav.html" NAME="${targetbase}Nav" SCROLLING=NO NORESIZE $marginheight>
   <FRAME SRC="$basename-body.html" NORESIZE NAME="${targetbase}Body">
</FRAMESET>
</HTML>
EOT
}

################### Functions for body files ######################

sub print_nav_frame
{
    local ($title) = @_;
    local ($javascript);
    local ($file);

    &print_header($title,"",$flag_base|$flag_print);

    if ($wiki){
	($file = $title) =~ s/ Interface//;
	print <<"EOT";
<BODY$bodyatt>
<TABLE BORDER=0 CELLSPACING=0 WIDTH="100%">
<TR>
<TD>
<SPAN CLASS=navigation>
EOT
        $javascript = &print_std_buttons();
        print<<"EOT";
</SPAN>
</TD>
<TD align=right>
<SPAN CLASS=navigation>
EOT

        &print_button("Home page", $wikiroot . "/_home.wiki", "");
        print " | ";
        &print_button("Site map",  $wikiroot . "/_sitemap.wiki", "");
        print " | ";
        &print_button("Recent changes", $wikiroot . "/_recent.wiki", "");
        print " | ";
        &print_button("Help", $wikihelp, "");
        print<<"EOT";
</SPAN>
</TD>
</TR>
</TABLE>
<HR>
<TABLE BORDER=0 CELLSPACING=0 WIDTH="100%">
<TR VALIGN=MIDDLE>
<TD>
<SPAN CLASS=title>$file</SPAN>
</TD>
<TD align=right>
<SPAN CLASS=logo><A href="$wikiroot">$wikidoc</A></SPAN>
</TD>
</TR>
<TR VALIGN=BOTTOM>
<TD>
<SPAN CLASS=description>
Interface Description
</SPAN>
</TD>
<TD align=right>
<SPAN CLASS=description>
EOT
        &print_button("Documentation", $wikiroot . "/documentation.wiki", "");
	print <<EOT;
</SPAN>
</TD>
</TR>
</TABLE>
<HR>
<P>
EOT
    } else {
	print <<EOT;
<BODY$bodyatt onLoad='fixPrintButton("$imagedir", "\u$basename", "Interface")'>
<TABLE WIDTH="100%" CELLPADDING=0 CELLSPACING=2>
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
    }
    chomp $javascript;
    print<<"EOT" if ("$javascript" ne "");
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
<!--
$javascript
//-->
</SCRIPT>
<P></P>
EOT

    print_valid_html_button();

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub print_body_frame(){
    local ($title, $basename, $contents) = @_;
    local ($header) = &H1($basename, $title);
    
    &print_header($title,$basename,($flag_base|$flag_hash));
    print<<"EOT";
<BODY onLoad='HashFromParent()'$bodyatt>
$header
<PRE CLASS=interface>
EOT
    print $contents; # full interface file as build in $_ above.
    print<<"EOT";
</PRE>
EOT
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
    local ($prev) = &strip_path(&strip_extension($files[$#files]));

    &print_header($title,"",$flag_base);

    if ($wiki){
	print <<"EOT";
<BODY$bodyatt>
<TABLE BORDER=0 CELLSPACING=0 WIDTH="100%">
<TR>
<TD>
<SPAN CLASS=navigation>
EOT
        &print_button("prev", 
		      "$prev.html",
		      "Previous: " . ucfirst($prev) . " Interface");
        print " | " if ($wiki);
        &print_button("content", $tocfile, "Interface Descriptions Contents");

        print<<"EOT";
</SPAN>
</TD>
<TD align=right>
<SPAN CLASS=navigation>
EOT

        &print_button("Home page", $wikiroot . "/_home.wiki", "");
        print " | ";
        &print_button("Site map",  $wikiroot . "/_sitemap.wiki", "");
        print " | ";
        &print_button("Recent changes", $wikiroot . "/_recent.wiki", "");
        print " | ";
        &print_button("Help", $wikihelp, "");
        print<<"EOT";
</SPAN>
</TD>
</TR>
</TABLE>
<HR>
<TABLE BORDER=0 CELLSPACING=0 WIDTH="100%">
<TR VALIGN=MIDDLE>
<TD>
<SPAN CLASS=title>
Index of Identifiers
</SPAN>
</TD>
<TD align=right>
<SPAN CLASS=logo><A href="$wikiroot">$wikidoc</A></SPAN>
</TD>
</TR>
<TR VALIGN=BOTTOM>
<TD>
<SPAN CLASS=description>
Interface Description
</SPAN>
</TD>
<TD align=right>
<SPAN CLASS=description>
EOT
        &print_button("Documentation", $wikiroot . "/documentation.wiki", "");
	print <<EOT;
</SPAN>
</TD>
</TR>
</TABLE>
EOT
    } else {
	# Not wiki
	print <<EOT;
<BODY$bodyatt>
<TABLE WIDTH="100%" CELLPADDING=0 CELLSPACING=5>
<TR>
<TD>
EOT

        &print_button("next", "", "No Next Interface Description");
        &print_button("prev", 
		      "$prev.html",
		      "Previous: " . ucfirst($prev) . " Interface");
        &print_button("top", $topfile, "Top: Manuals Main Entry");
        &print_button("content", $tocfile, "Interface Descriptions Contents");

        print<<EOT;
</TD>
<TH ALIGN=right>Interface Descriptions: Index</TH>
</TR>
<TR>
<TD colspan=2>
EOT
    }

    &calculate_index();
    &print_index_toc();

    print<<EOT;
</TD>
</TR>
</TABLE>
<P></P>
EOT

    print_valid_html_button();

    print<<EOT;
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
    local ($header) = &H1("Index.identifiers", "Index of Identifiers");

    &print_header($title,"",$flag_base);

    print<<"EOT";
<BODY$bodyatt>

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

$header
<PRE CLASS=interface>
EOT
}

sub print_index_trailer()
{
    local ($title) = @_;
    print<<EOT;
</PRE>
EOT
    &print_trailer($title);

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub calculate_index()
{
    # Sort index ignoring case
    @index = sort {lc($a) cmp lc($b)} @index;

    # Local variables
    local ($prev_id, $prev_no, $initial_ch, $htmlfile, $htmlbodyfile, $i, %entries);

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
	($htmlbodyfile = $htmlfile) =~ s/\.html$/-body.html/;
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
	    fprintf STDERR "Warning: Undefined indent: $indent\n";
	    $indents = $indent x ($level-1);
	    s/([ \:])$id\.$level([\:])/$1$indents$id$2/;
	}
	
	# Generate caps heading at first occurrence of a letter.
	$initial_ch = ucfirst (substr($index[$i], 0, 1));
	if (! $caps{$initial_ch} ){
	    local ($header) = &H2("_$initial_ch", $initial_ch);
	    $html_index .= "</PRE>$header<PRE CLASS=interface>\n";
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
		$html_index .= "\n  <A HREF=\"betaenv.html\"><I>betaenv</I></A>";
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
		$html_index .= "  <A href=\"$htmlbodyfile\#" . &legalize_hash($index[$i]) . "\">" . $id . "</A>";
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
		$html_index .= " <A href=\"$htmlbodyfile\#" . &legalize_hash($index[$i]) . "\">[" . $prev_no . "]</A>";
	    } else {
		$prev_no=1;
		$html_index .= "\n";
		$html_index .= "  <A href=\"$htmlbodyfile\#" . &legalize_hash($index[$i]) . "\">" . $id . "</A>";
		$prev_id = $id;
	    }
	    $entries{$_} = 1;
	}
    }
}

sub print_index_body_frame()
{
    &print_index_header("Index of Identifiers");
    print $html_index;
    &print_index_trailer("Index of Identifiers");;
}

####### Functions for table of contents #######################

sub print_toc_nav_frame
{
    local ($title) = @_;
    local ($next) = &strip_path(&strip_extension($files[0]));

    &print_header($title,"",$flag_base);

    print <<EOT;
<BODY$bodyatt>
<TABLE WIDTH="100%" CELLPADDING=0 CELLSPACING=5>
<TR>
<TD>
EOT

    &print_button("next", 
		  "$next.html",
		  "Next: " . ucfirst($next) . " Interface");
    print " | " if ($wiki);
    &print_button("prev", "", "No Previous Interface Description");
    &print_button("up", $upfile, "Up: Manual Main Page") if (!$wiki);
    &print_button("top", $topfile, "Top: Manuals Main Entry") if (!$wiki);
    &print_button("index", $indexfile, "Interface Descriptions Index");
    print " | " if ($wiki);

    print<<EOT;
</TD>
<TH ALIGN=right>Interface Descriptions: Contents</TH>
</TR>
</TABLE>
<P></P>
EOT

    print_valid_html_button();

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub print_toc_header
{
    local ($title) = @_;
    local ($header) = &H1("_toc", "Table of Contents");

    &print_header($title,"",$flag_base);

    print<<EOT;
<BODY$bodyatt>
<P></P>
$header
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
	print $htmlfile . " Interface</A>\n<DD>\n";
    }
    print "<DT>&nbsp;\n<DD>\n";
    print "<DT><A HREF=\"" . $indexfile . "\">Index</A>\n<DD>\n";
    print "</DL>\n";
    print "</DL>\n";
    print "</DIV>\n";
    &print_toc_trailer;
}


######################## Utility functions #####################

sub legalize_hash() # (:-)
{
    # Hashes in URLs with colons in them fail when used from JavaScript
    local ($hash) = @_;
    $hash =~ s/:/./g;
    return $hash;
}

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
    local ($id) = @_;
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

$INTERFACE="";

sub process_file
{
    local ($file) = @_;
    local ($patterns,$revpatterns,$level,
	   $line,$prefix,$before,$match,
	   $idxop,$idxlev,$after);

    $title=ucfirst(&strip_path(&strip_extension($file))) . " Interface";

    $basename=&strip_path(&strip_extension($file));
    $outfile=$basename . ".html";

    # Read entire input-stream into $line.

    printf STDERR "\nReading $file ...\n" if $verbose==1;
    $INTERFACE=$file;
    if (!open(INTERFACE)){
	print STDERR "Cannot open $INTERFACE for reading: $!\n";
	return;
    }

    $line="";
    while (<INTERFACE>) {
	$line .= $_;
    };
    close (INTERFACE);

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

    # Enable multiline matching.
    # FIXME: `Use of $* is deprecated'
    #  (D) This variable magically turned on multiline pattern matching,
    #  both for you and for any luckless subroutine that you happen to call.
    #  You should use the new `//m' and `//s' modifiers now to do that
    #  without the dangerous action-at-a-distance effects of $*.
    $*=0;

    $patterns = "";
    $revpatterns = "";
    $level  = 1;
    $line = "";
    $prefix = "";
    $idxop = "";
    $patternid = "";

    printf STDERR "Searching for idx-comments/patterns/colons .....\n" if $verbose==1;
    if   (! m/\n[ \t]*\(\*\s+idx([\+\-\=\001])\s*(\d*)\s*\*\)\s*\n|\(\#|\#\)|::?<?/i ){
	printf STDERR "  None found - emitting without markup\n" if $verbose==1;
	$line = $_;
    }
    while(  m/\n[ \t]*\(\*\s+idx([\+\-\=\001])\s*(\d*)\s*\*\)\s*\n|\(\#|\#\)|::?<?/i ){
	$before = "$`";
	$match  = "$&"; 
	$idxop  = (defined($1)) ? "$1" : ""; 
	$idxlev = (defined($2)) ? "$2" : ""; # if index info present
	$after  = "$'";

	if ( $idxop ne "" ) {
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
		printf(STDERR "***  %s\n", $patternid) if ($trace==1);
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
			$before .= "$bid<A name=\"" . &legalize_hash($idxid) . "\"></A>";
			$index[$indexid++] = "$idxid\@$outfile";
		    } else { 
			# inner scope
			$before .= "$bid<A name=\"" . &legalize_hash("$patterns$idxid") . "\"></A><A name=\"$idxid\"></A>";
			$index[$indexid++] = "$idxid\@$outfile";
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
    &print_frameset($title, $basename,($wiki)? 90 : 45);
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
printf STDERR "\nWriting common index ...\n" if $verbose==1;

printf STDERR "Writing frameset to $indexfile ..." if $verbose==1;
if (!open (STDOUT, ">$indexfile")){
    print "\nCannot open $indexfile for writing: $!\n";
    return;
}
&print_frameset("Interface Descriptions: Index", "inx", ($wiki) ? 120 : 100);
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
    printf STDERR "\nWriting common toc ...\n" if $verbose==1;
    
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

