#!/usr/local/bin/perl

if (-f "../bin/webxref.perl"){
    system "perl ../bin/webxref.perl -xref -depth 0 index.html\n";
} else {
    print "Don't know where I am. Do something like this in your shell:\n\t";
    print "perl doc/bin/webxref.perl -xref -depth 0 index.html\n";
}
