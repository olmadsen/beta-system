#!/usr/local/bin/perl

# Read entire input-stream into $line.

while ( <> ) {
    $line .= $_;
};

$*=1;
$_=$line;

s/\(\*\*+\*\)\s+\(\*+\s+([^\*]+)\s+\*+\)\s+\(\*\*+\*\)\s+/<\/PRE><P><HR><P><H2><A name=\"$1\">$1<\/A><\/H2><PRE CLASS=interface>\n/g;

# Delete copyrigth comments of the form
# (*
#  * COPYRIGHT
#  *       Copyright Mjolner Informatics, 199x-9x
#  *       All rights reserved.
#  *)
s/\(\*\s+\*\s+COPYRIGHT[\s\w\*\,\-\.]+\*\)\s*//g;


print $_;
