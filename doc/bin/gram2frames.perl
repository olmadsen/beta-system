#!/usr/local/bin/perl -s -w

# Create HTML file on stdout for the xxx-meta.gram file
# specified as argument 1.
# Retains formatting of original file.
# Requires rule specifier and '::' to be on the same line in order to
# work.

sub usage()
{
    print "usage: gram2frames [-c] [-f] [-v] <grammar-meta.gram>\n";
    print "  -c:  leave out Mjolner Informatics Copyright\n";
    print "  -f:  use full paths to style sheets, images, javascripts\n";
    print "  -v:  verbose\n";
}

########## Global variables #############################################
# Flags for sub print_gram_header
my $flag_hash  = 1;
my $flag_print = 2;
my $flag_base  = 4;
my $flag_frame = 8;

my $in_gram_rules  = 0;

# Command line
my $verbose     = (defined($v)) ? 1 : 0;
my $fullpath    = (defined($f)) ? 1 : 0;

# Other global variables
my $scriptdir = "";
my $imagedir = "";
my $topfile = "";
my $upfile = "";
my $copyright = "";
my $lastmodscript = "";
my $hashfromparent = "";
my $printframe = "";
my $fixprintbutton = "";
my $gram_inxfile = "";
my $indexnavfile = "";
my $indexdocfile = "";
my $gram_tocfile = "";
my $css = "";
my $wiki = 0;

if ($fullpath){
    #if ($extradir){
    #   print "int2html.perl: Both -f and -x specified: -x is ignored\n";
    #}
    $css = <<EOT;
<LINK REL="stylesheet" HREF="http://www.mjolner.com/mjolner-system/documentation/style/miadoc.css" TYPE="text/css">
EOT
    $imagedir = "http://www.mjolner.com/mjolner-system/documentation/images/";
    $topfile = "http://www.mjolner.com/mjolner-system/documentation/index.html";
} else {
    $css = <<EOT;
<LINK REL="stylesheet" HREF="../style/miadoc.css" TYPE="text/css">
EOT
    $scriptdir = "../javascript";
    $imagedir = "../images/";
    $topfile = "../index.html";
}
$lastmodscript = "$scriptdir/lastmod.js";
$hashfromparent = "$scriptdir/hashfromparent.js";
$printframe = "$scriptdir/printframe.js";
$fixprintbutton = "$scriptdir/fixprintbutton.js";
if ($wiki){
    $gram_tocfile = $ENV{'TOCURL'};
} else {
    $gram_tocfile = "index.html";
}

if (defined($c)){
    $copyright = "";
} else {
    $copyright = "<FONT size=\"-1\">&#169; <A HREF=\"http://www.mjolner.com\" TARGET=\"_top\">Mj&oslash;lner Informatics</A></FONT>";
}

# Mentioning of option variables once more to prevent "used only once" warns
$v = $f = $c = "";


########## Helper functions #############################################

sub quote_gram_html
# replace '<', '>', '&' with their HTML equivalents
{
    local ($string) = $_[0];
    $string =~ s/\&/\&amp\;/g;
    $string =~ s/\</\&lt\;/g;
    $string =~ s/\>/\&gt\;/g;
    return $string;
}

sub make_gram_anchor
{
    local ($name) = $_[0];
    push (@index, $name);
    $name = "<A CLASS=leftside NAME=\"" . lc($name) . "\">&lt;$name&gt;</A>";
    return $name;
}

sub isLexem
{
    local ($name) = $_[0];
    $name = lc($name);
    return (($name eq "const") || ($name eq "string") || ($name eq "nameappl") || ($name eq "namedecl"));
}

sub make_gram_href1
{ 
    local ($string) = $_[0];
    if ($string =~ m/<([-\w]+)>/) {
	return "&lt;$1&gt;" if (&isLexem($1));
	return "<A HREF=\"#" . "\L$1" . "\">&lt;$1&gt;<\/A\>";
    } else {
	return $string;
    }
}
sub make_gram_href2
{ 
    local ($string) = $_[0];
    if ($string =~ m/<([-\w]+):([-\w]+)>/) {
	return "&lt;$1:$2&gt;" if (&isLexem($2));
	return "<A HREF=\"#" . "\L$2" . "\">&lt;$1:$2&gt;<\/A\>";
    } else {
	return $string;
    }
}
sub make_gram_comment
{
    local ($string) = $_[0];
    if ($string =~ m/\(\*(.*\*\))/) {
	$string =~ s/&/&amp\;/g;
	$string =~ s/>/&gt\;/g;
	$string =~ s/</&lt\;/g;
    }
    return $string;
}
sub make_gram_hrefs
{
    local ($string) = $_[0];
    $string =~ s/(\(\*.*\*\))/&make_gram_comment($1)/ge;
    $string =~ s/(<[-\w]+>)/&make_gram_href1($1)/ge;
    $string =~ s/(<[-\w]+:[-\w]+>)/&make_gram_href2($1)/ge;
    return $string;
}

sub make_gram_h2
{
    local ($string) = $_[0];
    return "</PRE>\n<H2>$string</H2>\n<PRE>";
}

sub quote_gram_strings
# boldface literals and quote HTML in string constants
{
    local ($line) = $_[0];
    local ($processedline) = "";

    while (1){
	if ($line =~ m/\'([^\']+)\'/){
	    $processedline .= $`;
	    $after = $';
	    $literal = $1;
	    $literal = &quote_gram_html($literal);
	    # HTML tags are generated as <+...+> to avoid
	    # interpreting, e.g. <B> as a rule in later
	    # processing. The plus signs are removed by unquote_gram_html.
	    $literal = "<+B+>$literal<+/B+>" if ($in_gram_rules);
	    $literal = "\'$literal\'";
	    $processedline .= $literal;
	    $line = $after;
	} else {
	    $processedline .= $line;
	    last;
	}
    }
    return  $processedline;
}

sub unplus_gram_html
# replace '<+' with '<' and , '+>' with '>'
{
    local ($string) = $_[0];
    $string =~ s/\<\+/\</g;
    $string =~ s/\+\>/\>/g;
    return $string;
}

###### Functions for buttons and standard HTML header and frameset ##

sub print_button
{
    local ($type, $href, $alt) = @_;
    local ($name) = ucfirst ($type);
    local ($javascript) = "";

    if ($href =~ m/^javascript:/ ){
	print<<"EOT";
<A NAME="A$name" HREF="$href" TARGET="_self"><IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="${imagedir}${type}g-jsr.gif" ALT="${alt} (JavaScript Required)" NAME="$name" BORDER=0></A>
EOT
        # JavaScript to enable Print button. In Microsoft IE we can change
        # the HTML of the surrounding <A>, thus replacing the Alternative
        # text too. In NetScape we can only change the Image.
        $javascript = <<"EOT";
if (navigator.appName.substring(0,9) == "Microsoft"){
  document.all.APrint.outerHTML = '<A NAME="A$name" HREF="$href" TARGET="_self"><IMG WIDTH=69 HEIGHT=24 ALIGN=BOTTOM SRC="${imagedir}${type}.gif" ALT="${alt}" NAME="$name" BORDER=0></A>';
} else {
  document.images.$name.src = \"${imagedir}${type}.gif\";
}
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

sub print_gram_header
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
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
<!--
    CheckParent("$basename");
//-->
</SCRIPT>
EOT

    print <<"EOT" if ($flags&$flag_print);
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript" SRC="$printframe"></SCRIPT>
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript" SRC="$fixprintbutton"></SCRIPT>
EOT

    print <<"EOT" if ($flags&$flag_base);
<BASE TARGET="_parent">
EOT

    print <<"EOT";
</HEAD>
EOT
}

sub print_gram_trailer
{
    local ($title) = @_;

    print<<"EOT";
<!--+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++-->
<HR>
<P></P>
<TABLE border=0 width="100%">
<TR>
<TD width="40%" align="left"><ADDRESS>$title</ADDRESS></TD>
<TD width="20%" align="center">$copyright</TD>
<TD width="40%" align="right"><SCRIPT TYPE="text/javascript" LANGUAGE=JavaScript SRC="$lastmodscript"></SCRIPT></TD>
</TABLE>
EOT
}

sub print_gram_frameset()
{
    
    local ($title, $basename, $height) = @_;

    &print_gram_header($title,"",$flag_base|$flag_frame);

    print<<"EOT";
<FRAMESET FRAMEBORDER=0 FRAMESPACING=0 BORDER=0 ROWS="$height,*">
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
   <FRAME SRC="$basename-nav.html" NAME="${basename}Nav"SCROLLING=NO MARGINHEIGHT=1>
   <FRAME SRC="$basename-body.html" NAME="${basename}Body">
</FRAMESET>
</HTML>
EOT
}


###### Functions for body file ###############################

sub print_gram_nav_frame
{
    local ($title) = @_;
    local ($javascript);

    &print_gram_header($title,"",$flag_base|$flag_print);

    print <<EOT;
<BODY onLoad='fixPrintButton("$imagedir", "\u$basename", "Grammar")'>
<TABLE WIDTH="100%" CELLPADDING=0 CELLSPACING=2>
<TR VALIGN=MIDDLE>
<TD NOWRAP>
EOT

    &print_button("top", $topfile, "Top: Manuals Main Entry");
    &print_button("index", $gram_inxfile, "\u$basename Grammar Index");
    &print_button("content", $gram_tocfile, "Contents: List of Grammars");
    $javascript = &print_button("print", 
				"javascript:if (parent && parent.${basename}Body){printframe(parent.${basename}Body)};",
				"Print \u$basename Grammar Frame");

    print<<EOT;
</TD>
<TH NOWRAP ALIGN=right>$title</TH>
</TR>
</TABLE>
</BODY>
</HTML>
EOT
}


sub print_gram_body_frame()
{

    local ($file) = $_[0];
    
    &print_gram_header($title, $basename, $flag_hash);

    print<<"EOT";
<BODY onLoad='HashFromParent();'>
<H1>$title</H1>
<PRE CLASS=gram>
EOT

    open (GRAM, "$file") || die "cannot open $file: $!\n";
    while(<GRAM>){
	$line = $_;
	chomp($line);
	if (/^\s*Option\s*$/i){
	    $line=&make_gram_h2($line);
	} elsif (/^\s*Rule\s*$/i){
	    $line=&make_gram_h2($line);
	    $in_gram_rules = 1;
	} elsif (/^\s*Attribute\s*$/i){
	    $line=&make_gram_h2($line);
	} elsif ($in_gram_rules){
	    $line = &quote_gram_strings($line);
	    if ($line =~ m/^(\s*)<([-\w]+)>(\s*)::/) {
		# line with rule definition
		#   <name>   :: ...
		#             ^ matched to here
		$w1 = $1; $name = $2; $w2 = $3; 
		$rest = $';
		$name = &make_gram_anchor($name);
		# insert link from rightsides to corresponding leftsides:
		$rest = &make_gram_hrefs($rest);
		$line = $w1 . $name . $w2 . "::" . $rest;
	    } else {
		#line without rule definition
		$line = &make_gram_hrefs($line);
	    }
	    $line = &unplus_gram_html($line);
	} else {
	    # Not yet in rules section
	    $line = &quote_gram_html($line);
	}
	print "$line\n";
    }
    close(GRAM);

    print<<EOT;
</PRE>
EOT

    &print_gram_trailer($title);

print<<EOT;
</BODY>
</HTML>
EOT

}


######## Functions for index generation ##############################

sub print_gram_index_toc()
{
    local ($i, $ch);
    print "<HR>\n";
    for ($i=65; $i<=90; $i++){
	$ch = sprintf ("%c", $i);
	if ($caps{$ch}){
	    print "<STRONG><A HREF=\"#_$ch\" TARGET=${inxbasename}Body>$ch</A></STRONG> &nbsp; \n";
	} else {
	    # no indices starting with $ch
	    print "<STRONG CLASS=disabled>$ch</STRONG> &nbsp; \n";
	}	    
    }
    print "<HR>\n<P></P>\n";
}

sub print_gram_index_nav_frame
{
    local ($title, $basename) = @_;

    &print_gram_header($title,"",$flag_base|$flag_print);

    print <<EOT;
<BODY onLoad="fixPrintButton()">
<TABLE WIDTH="100%" CELLPADDING=0 CELLSPACING=5>
<TR>
<TD VALIGN=MIDDLE>
EOT

    $basename =~ s/-inx$//;
    &print_button("top", $topfile, "Top: Manuals Main Entry");
    &print_button("up", $htmlfile, "Up: \u$basename Grammar");
    &print_button("content", $gram_tocfile, "Contents: List of Grammars");

    print<<EOT;
</TD>
<TH ALIGN=right>$title</TH>
</TR>
<TR>
<TD colspan=2>
EOT

    &calculate_gram_index();
    &print_gram_index_toc();

    print<<EOT;
</TD>
</TR>
</TABLE>
</BODY>
</HTML>
EOT
}

sub calculate_gram_index()
{
    local ($initial_ch, $i, $htmlbodyfile);

    # Sort index ignoring case
    @index = sort {lc($a) cmp lc($b)} @index;
        
    for ($i = 0; $i <= $#index; $i++) {
	# Generate caps heading at first occurrence of a letter.
	$initial_ch = ucfirst (substr($index[$i], 0, 1));
	if (! $caps{$initial_ch} ){
	    $html_index .= "</PRE>\n<H2><A name=\"_$initial_ch\">$initial_ch<\/A><\/H2>\n<PRE CLASS=gram>\n";
	    $caps{$initial_ch} = 1;
	}
	# Generate index line
	($htmlbodyfile = $htmlfile) =~ s/\.html$/-body.html/;
	$html_index .= "  <A href=\"$htmlbodyfile\#" . lc($index[$i]) . "\">&lt;" . $index[$i] . "&gt</A>\n";
    }
    &print_gram_index_toc;
    print "<PRE CLASS=gram>\n$html_index</PRE>\n";
}

sub print_gram_index_header()
{
    local ($title) = @_;

    &print_gram_header($title,"",$flag_base);

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

<H1><A name="Index">$title</A></H1>
<PRE CLASS=gram>
EOT
}

sub print_gram_index_trailer()
{
    local $title = $_[0];
    print<<EOT;
</PRE>
EOT
    &print_gram_trailer($title);

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub print_gram_index_frame()
{
    local ($title) = @_;

    &print_gram_index_header($title);
    print $html_index;
    &print_gram_index_trailer($title);
}

######## MAIN #######

if ($#ARGV!=0){
    print "Usage: makehtml.perl <grammar-file>\n";
    exit 1;
}

$file=$ARGV[0];

$title=$file;
$title=~s%.*/%%; # delete path
$title=~s/-meta.gram//; # delete -meta.gram
$basename=lc($title);
$htmlfile=$basename . ".html";
$htmlnavfile=$basename . "-nav.html";
$htmlbodyfile=$basename . "-body.html";
$inxbasename=lc($title) . "-inx";
$gram_inxfile=$inxbasename . ".html";
$inxnavfile=$inxbasename . "-nav.html";
$inxbodyfile=$inxbasename . "-body.html";
$title=ucfirst($basename) . " Grammar";

### generate body frameset

printf STDERR "\nProcessing $file ... \n" if $verbose;

printf STDERR "Writing frameset to $htmlfile ... \n" if $verbose==1;
open (STDOUT, ">$htmlfile") || die "\nCannot open $htmlfile for writing: $!\n";
&print_gram_frameset($title, $basename,45);
close (STDOUT);

printf STDERR "Writing navigation frame to $htmlnavfile ... \n" if $verbose==1;
open (STDOUT, ">$htmlnavfile") || die "\nCannot open $htmlnavfile for writing: $!\n";
&print_gram_nav_frame($title);
close (STDOUT);

printf STDERR "Writing body file to $htmlbodyfile ... \n" if $verbose==1;
open (STDOUT, ">$htmlbodyfile") || die "\nCannot open $htmlbodyfile for writing: $!\n";
&print_gram_body_frame($file);
close (STDOUT);
printf STDERR "done.\n" if $verbose;

### generate index frameset

printf STDERR "\nWriting index frameset to $gram_inxfile ... \n" if $verbose;
open (STDOUT, ">$gram_inxfile") || die "\nCannot open $gram_inxfile for writing: $!\n";
&print_gram_frameset("$title: Index", $inxbasename, 100);
close (STDOUT);

printf STDERR "Writing index navigation frame to $inxnavfile ... \n" if $verbose;
open (STDOUT, ">$inxnavfile") || die "\nCannot open $inxnavfile for writing: $!\n";
&print_gram_index_nav_frame("$title: Index", $inxbasename);
close (STDOUT);

printf STDERR "Writing index body to $inxbodyfile ... \n" if $verbose;
open (STDOUT, ">$inxbodyfile") || die "\nCannot open $inxbodyfile for writing: $!\n";
&print_gram_index_frame("$title: Index");
close (STDOUT);
printf STDERR "done.\n" if $verbose;

printf STDERR "$basename-meta.gram complete.\n" if $verbose;
