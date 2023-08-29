#!/usr/bin/perl -s

# Create HTML file on stdout for the xxx-meta.gram file
# specified as argument 1.
# Retains formatting of original file.
# Requires rule specifier and '::' to be on the same line in order to
# work.

sub usage()
{
    print "usage: gram2html [-c] [-f] [-v] <grammar-meta.gram>\n";
    print "  -c:  leave out Mjolner Informatics Copyright\n";
    print "  -f:  use full paths to style sheets, images, javascripts\n";
    print "  -v:  verbose\n";
}

$verbose = $v;

if ($f){
    $css = "http://www.mjolner.com/mjolner-system/documentation/style/miadoc.css";
    $lastmodscript = "http://www.mjolner.com/mjolner-system/documentation/javascript/lastmod.js";
    $imagedir = "http://www.mjolner.com/mjolner-system/documentation/images/";
    $topfile = "http://www.mjolner.com/mjolner-system/documentation/index.html#grammars";
} else {
    $css = "../style/miadoc.css";
    $lastmodscript = "../javascript/lastmod.js";
    $imagedir = "../images/";
    $topfile = "../index.html#grammars";
}
if ($c){
    $copyright = "";
} else {
    $copyright = "<FONT size=-1>&COPY; <A HREF=\"http://www.mjolner.com\">Mj&oslash;lner Informatics</A></FONT>";
}

$in_rules = 0;

sub print_header()
{
    local ($file, $title) = @_;

    print<<"EOT";
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
>
<!-- Generated from $file by gram2html.perl -->
<HTML>
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">
<TITLE>$title</TITLE>
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
</HEAD>
<BODY>
<P></P>
EOT

    &print_button("index", $inxfile);
    &print_button("top", $topfile);

    print<<EOT;
<P></P>
<P>$title</P>

<H1>$title</H1>
<PRE CLASS=gram>
EOT
}

sub print_trailer
{
    local ($title) = @_;

    print<<EOT;
</PRE>
<!---------------------------------------------------------->
<HR>
<P>
<TABLE cols=3 border=0 width=100%>
<TR>
<TD width="40%" align="left"><ADDRESS>$title</ADDRESS></TD>
<TD width="20%" align="center">$copyright</TD>
<TD width="40%" align="right"><SCRIPT LANGUAGE=JavaScript SRC="$lastmodscript"></SCRIPT></TD>
</TABLE>
<P></P>
EOT

    &print_button("index", $inxfile);
    &print_button("top", $topfile);

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub quote_html
# replace '<', '>', '&' with their HTML equivalents
{
    local ($string) = @_[0];
    $string =~ s/\&/\&amp\;/g;
    $string =~ s/\</\&lt\;/g;
    $string =~ s/\>/\&gt\;/g;
    return $string;
}

sub make_anchor
{
    local ($name) = @_[0];
    push (@index, $name);
    $name = "<A CLASS=leftside NAME=\"" . lc($name) . "\">&lt;$name&gt;</A>";
    return $name;
}

sub isLexem
{
    local ($name) = @_[0];
    $name = lc($name);
    return (($name eq "const") || ($name eq "string") || ($name eq "nameappl") || ($name eq "namedecl"));
}

sub make_href1
{ 
    local ($string) = @_[0];
    if ($string =~ m/<([-\w]+)>/) {
	return "&lt;$1&gt;" if (&isLexem($1));
	return "<A HREF=\"#" . "\L$1" . "\">&lt;$1&gt;<\/A\>";
    } else {
	return $string;
    }
}
sub make_href2
{ 
    local ($string) = @_[0];
    if ($string =~ m/<([-\w]+):([-\w]+)>/) {
	return "&lt;$1:$2&gt;" if (&isLexem($2));
	return "<A HREF=\"#" . "\L$2" . "\">&lt;$1:$2&gt;<\/A\>";
    } else {
	return $string;
    }
}
sub make_comment
{
    local ($string) = @_[0];
    if ($string =~ m/\(\*(.*\*\))/) {
	$string =~ s/&/&amp\;/g;
	$string =~ s/>/&gt\;/g;
	$string =~ s/</&lt\;/g;
    }
    return $string;
}
sub make_hrefs
{
    local ($string) = @_[0];
    $string =~ s/(\(\*.*\*\))/&make_comment($1)/ge;
    $string =~ s/(<[-\w]+>)/&make_href1($1)/ge;
    $string =~ s/(<[-\w]+:[-\w]+>)/&make_href2($1)/ge;
    return $string;
}

sub make_h2
{
    local ($string) = @_[0];
    return "<P><H2>$string</H2>";
}

sub quote_strings
# boldface literals and quote HTML in string constants
{
    local ($line) = @_[0];
    local ($processedline) = "";

    while (1){
	if ($line =~ m/\'([^\']+)\'/){
	    $processedline .= $`;
	    $after = $';
	    $literal = $1;
	    $literal = &quote_html($literal);
	    # HTML tags are generated as <+...+> to avoid
	    # interpreting, e.g. <B> as a rule in later
	    # processing. The plus signs are removed by unquote_html.
	    $literal = "<+B+>$literal<+/B+>" if ($in_rules);
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

sub unplus_html
# replace '<+' with '<' and , '+>' with '>'
{
    local ($string) = @_[0];
    $string =~ s/\<\+/\</g;
    $string =~ s/\+\>/\>/g;
    return $string;
}

sub do_gram_file()
{

    local ($file) = @_[0];
    
    open (GRAM, "$file") || die "cannot open $file: $!\n";
    while(<GRAM>){
	$line = $_;
	chomp($line);
	if (/^\s*Option\s*$/i){
	    $line=&make_h2($line);
	} elsif (/^\s*Rule\s*$/i){
	    $line=&make_h2($line);
	    $in_rules = 1;
	} elsif (/^\s*Attribute\s*$/i){
	    $line=&make_h2($line);
	} elsif ($in_rules){
	    $line = &quote_strings($line);
	    if ($line =~ m/^(\s*)<([-\w]+)>(\s*)::/) {
		# line with rule definition
		#   <name>   :: ...
		#             ^ matched to here
		$w1 = $1; $name = $2; $w2 = $3; 
		$rest = $';
		$name = &make_anchor($name);
		# insert link from rightsides to corresponding leftsides:
		$rest = &make_hrefs($rest);
		$line = $w1 . $name . $w2 . "::" . $rest;
	    } else {
		#line without rule definition
		$line = &make_hrefs($line);
	    }
	    $line = &unplus_html($line);
	} else {
	    # Not yet in rules section
	    $line = &quote_html($line);
	}
	print "$line\n";
    }
    close(GRAM);
}

sub print_index_toc()
{
    local ($i, $ch);
    print "</PRE>\n<HR>\n";
    for ($i=65; $i<=90; $i++){
	$ch = sprintf ("%c", $i);
	if ($caps{$ch}){
	    print "<STRONG><A HREF=\"#_$ch\">$ch</A></STRONG> &nbsp; \n";
	} else {
	    # no indices starting with $ch
	    print "<STRONG CLASS=disabled>$ch</STRONG> &nbsp; \n";
	}	    
    }
    print "<HR>\n<P></P>\n<PRE CLASS=gram>\n";
}

sub print_button
{
    local ($type, $href) = @_;
    local ($alt) = ucfirst ($type);
    # special case for "prev":
    $alt =~ s/Prev/Previous/g;
    if ("$href" eq ""){
	print "<A><IMG ALIGN=BOTTOM SRC=\"$imagedir";
	print $type . "g.gif\" ALT=";
	print $alt . " BORDER=0></A>\n";
    } else {
	print "<A HREF=\"" .$href . "\">";
	print "<IMG ALIGN=BOTTOM SRC=\"$imagedir";
	print $type . ".gif\" ALT=";
	print $alt . " BORDER=0></A>\n";
    }
}

sub print_index_header
{
    print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
>
<HTML>
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">
<TITLE>Index for $title</TITLE>
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
</HEAD>
<BODY>
<P></P>
EOT

    &print_button("up", $htmlfile);
    &print_button("top", $topfile);

    print<<EOT;
<P></P>
<P>Index for $title</P>

<H1><A name="Index">Index for $title</A></H1>
<PRE CLASS=gram>
EOT
}

sub print_index_trailer()
{
    print<<EOT;
</PRE>
<!---------------------------------------------------------->
<HR>
<P></P>
<TABLE cols=3 border=0 width=100%>
<TR>
<TD width="40%" align="left"><ADDRESS>Index for $title</ADDRESS></TD>
<TD width="20%" align="center">$copyright</TD>
<TD width="40%" align="right"><SCRIPT LANGUAGE=JavaScript SRC="$lastmodscript"></SCRIPT></TD>
</TABLE>
<P></P>
EOT

    &print_button("up", $htmlfile);
    &print_button("top", $topfile);

    print<<EOT;
</BODY>
</HTML>
EOT
}

sub print_index()
{
    local ($initial_ch, $i);

    # Sort index ignoring case
    @index = sort {lc($a) cmp lc($b)} @index;
        
    for ($i = 0; $i <= $#index; $i++) {
	# Generate caps heading at first occurrence of a letter.
	$initial_ch = ucfirst (substr($index[$i], 0, 1));
	if (! $caps{$initial_ch} ){
	    $html_index .= "</PRE><H2><A name=\"_$initial_ch\">$initial_ch<\/A><\/H2><PRE CLASS=gram>\n";
	    $caps{$initial_ch} = 1;
	}
	# Print index line
	$html_index .= "  <A href=\"$htmlfile\#" . lc($index[$i]) . "\">&lt;" . $index[$i] . "&gt</A>\n";
    }
    &print_index_toc;
    print $html_index;
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
$htmlfile=lc($title) . ".html";
$inxfile=lc($title) . "-inx.html";
$title=ucfirst($title) . " Grammar";

printf STDERR "\nProcessing $file ... " if $verbose;
open (STDOUT, ">$htmlfile") || die "\nCannot open $htmlfile for writing: $!\n";
&print_header($file, $title);
&do_gram_file($file);
&print_trailer($title);
close (STDOUT);
printf STDERR "done.\n" if $verbose;


printf STDERR "\nWriting index to $inxfile ... " if $verbose;
open (STDOUT, ">$inxfile") || die "\nCannot open $inxfile for writing: $!\n";
&print_index_header();
&print_index();
&print_index_trailer();
close (STDOUT);
printf STDERR "done.\n" if $verbose;
