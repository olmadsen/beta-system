#! perl

unlink "idl-parser.generated";
print `generator idl`;
rename ("idl-parser.bobs", "idl-parser.generated") or die "rename: $!";

print "Fixing '<<' in idl-parser.bobs\n";
open (IN, "<idl-parser.generated") 
    or die "Unable to open idl-parser.generated: $!\n";
open (OUT, ">idl-parser.bobs") 
    or die "Unable to create idl-parser.bobs: $!\n";

while(<IN>) {
    if (s/\<\</\!\!/) {
	print OUT $_;
	last;
    }
    print OUT $_;
}

while(<IN>) {
    print OUT $_;
}

close(IN);
close(OUT);

print "Invoking standard dogram on idl-meta.gram\n";
print `dogram idl`;
