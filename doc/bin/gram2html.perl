#!/usr/local/bin/perl

# Create HTML file on stdout for the xxx-meta.gram file
# specified as argument 1.
# Retains formatting of original file.
# Requires rule specifier and '::' to be on the same line in order to
# work.

# Style sheet:
$css = "../style/miadoc.css";

$in_rules = 0;

sub print_header
{
    local ($file, $title) = @_;

    print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<!-- Generated from $file by gram2html.perl -->
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
</HEAD>
<BODY>
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
<TD width="33%" align="left"><ADDRESS>$title</ADDRESS></TD>
<TD width="34%" align="center"><FONT size=-1>&COPY; <A HREF="http://www.mjolner.com">Mj&oslash;lner Informatics</A></FONT></TD>
<TD width="33%" align="right"><FONT size=-1><SCRIPT LANGUAGE=JavaScript SRC="../javascript/lastmod.js"></SCRIPT></FONT></TD>
</TABLE>
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
    $name = "<A CLASS=leftside NAME=$name>&lt;$name&gt;</A>";
    return $name;
}

sub make_hrefs
{
    local ($string) = @_[0];
    $string =~ s/<([-\w]+)>/<A HREF="#$1">&lt;$1&gt;<\/A\>/g;
    return $string;
}

sub make_h2
{
    local ($string) = @_[0];
    return "<P><HR><P><H2>$string</H2>";
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

sub unquote_html
# replace '<+' with '<' and , '+>' with '>'
{
    local ($string) = @_[0];
    $string =~ s/\<\+/\</g;
    $string =~ s/\+\>/\>/g;
    return $string;
}

######## MAIN #######

if ($#ARGV!=0){
    print "Usage: makehtml.perl <grammar-file>\n";
    exit 1;
}

$file=$ARGV[0];

open (GRAM, "$file") || die "cannot open $file: $!\n";

$title=$file;
$title=~s%.*/%%; # delete path
$title=~s/-meta.gram//; # delete -meta.gram
$title=ucfirst($title) . " Grammar";

&print_header($file, $title);

while(<GRAM>){
    $line = $_;
    chomp($line);
    $line = &quote_strings($line);
    if (/^\s*Option\s*$/i){
	$line=&make_h2($line);
    } elsif (/^\s*Rule\s*$/i){
	$line=&make_h2($line);
	$in_rules = 1;
    } elsif (/^\s*Attribute\s*$/i){
	$line=&make_h2($line)
    } elsif ($in_rules){
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
	    $line =~ s/<([-\w]+)>/<A HREF="#$1">&lt;$1&gt<\/A>/g;
	}
    }
    $line = &unquote_html($line);
    print "$line\n";
}
close(GRAM);

&print_trailer($title);

