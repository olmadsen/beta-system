#!/usr/local/bin/perl

# Read entire input-stream into $line.

while ( <> ) {
    $line .= $_;
};

$*=1;
$_=$line;

$header= "";
$tail= "";

$headerpre= "";

$headerpost=" (HEADING)";

s/\(\*\*+\*\)\s+\(\*+\s+([^\*]+)\s+\*+\)\s+\(\*\*+\*\)\s+/$headerpre$1$headerpost\n/g;
#s/\(\*\*+\*\)\s+\(\*+\s+([^\*]+)\s+\*+\)\s+\(\*\*+\*\)\s+//g;

# Delete copyrigth comments of the form
# (*
#  * COPYRIGHT
#  *       Copyright Mjolner Informatics, 199x-9x
#  *       All rights reserved.
#  *)
s/\(\*\s+\*\s+COPYRIGHT[\s\w\*\,\-\.]+\*\)\s*//g;


print $_;
