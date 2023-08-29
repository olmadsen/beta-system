#!/usr/bin/perl

# Read entire input-stream into $line

while ( <> ) {
    $line .= $_;
}			
				
# Now perform multiline editing

$*=1;
$_=$line;

s/(<[^>]+>)/&remove_tag($1)/goe;

sub remove_tag()
{
    local ($tag) = @_;

    if ($tag =~ m/<.*<.*>/){
	print STDERR "Warning: unquoted '<' in tag:\n\t$tag";
    }
    return "";
}

print;
