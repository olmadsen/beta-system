#!/usr/local/bin/perl

$dst=$ENV{'DST'};
$target=$ENV{'TARGET'};

if ($target =~ m/^nti$/){
    if (! defined $ENV{'ZIPLIST'}){
	print "make_list: can only generate configuration.lst for ZIPLIST packing\n";
	exit 0;
    }
}

chdir($dst);
$dirs="";

while(<>){
    if ( m%\w+[\w/]+/v\d+\.\d+\.?\d*/% ){
	$dirs .= "$&\n";
    }
    if ( m%\w+[\w/]+/r\d+\.\d+\.?\d*/% ){
	$dirs .= "$&\n";
    }
}

open(OUT, "| sort -u > $dst/configuration.lst") || die "cannot open pipe to sort -u > $dst/configuration.lst\n";
print OUT $dirs;
print "List of dirs in $dst/configuration.lst\n";

