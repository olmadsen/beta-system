#!/usr/local/bin/perl

# Create HTML file on stdout for the xxx-meta.gram file
# specified as argument 1.
# Retains formatting of original file.
# Requires rule specifier and '::' to be on the same line in order to
# work.

if ($#ARGV!=0){
    print "Usage: makehtml.perl <grammar-file>\n";
    exit 1;
}

$file=$ARGV[0];

open (GRAM, "$file") || die "cannot open $file: $!\n";

$title=$file;
$title=~s%.*/%%;
$title=~s/-meta.gram//;
$title="\U$title" . " Grammar";

print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<TITLE>$title</TITLE>
</HEAD>
<BODY>
<H1>$title</H1>
<PRE>
EOT

while(<GRAM>){
    $line = $_;
    if (/^\s*Option\s*$/i){
	# header line
	$line="<H2>$line</H2>";
    } elsif (/^\s*Rule\s*$/i){
	# header line
	$line="<H2>$line</H2>";
    } elsif (/^\s*Attribute\s*$/i){
	# header line
	$line="<H2>$line</H2>";
    } elsif (/^(\s*)<(\w+)>(\s*::)/) {
	# line with rule definition
	$rest = $';
	$line = "$1<FONT COLOR=\"red\"\><A NAME=$2>&lt;$2&gt;<A><\/FONT>$3";
	$rest =~ s/<(\w+)>/<A HREF="#$1">&lt;$1&gt<\/A\>/g;
	$line .= $rest;
    } else {
	#line without rule definition
	$line =~ s/<(\w+)>/<A HREF="#$1">&lt;$1&gt<\/A>/g;
    }
    # boldface literals
    $line =~ s/'([^']+)'/'<B>$1<\/B>'/g;
    print $line;
}
close(GRAM);

print<<EOT;
</PRE>
</BODY>
</HTML>
EOT

