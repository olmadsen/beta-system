#!/usr/local/bin/perl

# Read entire input-stream into $line.

while ( <> ) {
    $line .= $_;
};

$*=1;
$_=$line;

s/\(\*\*+\*\)\s+\(\*+\s+([^\*]+)\s+\*+\)\s+\(\*\*+\*\)\s+/\005\/PRE\006\005P\006\005HR\006\005P\006\005H2\006\005A name=\"$1\"\006$1\005\/A\006\005\/H2\006\005PRE CLASS=interface\006\n/g;

# Delete copyrigth comments of the form
# (*
#  * COPYRIGHT
#  *       Copyright Mjolner Informatics, 199x-9x
#  *       All rights reserved.
#  *)
s/\(\*\s+\*\s+COPYRIGHT[\s\w\*\,\-\.]+\*\)\s*//g;

print $_;
