#!/usr/local/bin/perl

# Style sheet:
$css = "/~beta/doc/style/miadoc.css";

sub print_header
{
    local ($title) = @_;

    print<<EOT;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>
<HEAD>
<LINK REL="stylesheet" HREF="$css" TYPE="text/css">
</HEAD>
<BODY>
<H1>$title</H1>
<PRE CLASS=gram>
EOT
}

sub print_trailer
{
    print<<EOT;
</PRE>
</BODY>
</HTML>
EOT
}

################ MAIN ####################

&print_header("Interface Description");

# Read entire input-stream into $line.

while ( <> ) {
    $line .= $_;
};

$_ = $line;		
				
# Insert World Wide Web tags for declarations (HTML format).
# Outermost declaration is indexed by its own name, inner declarations are 
# indexed by its name followed by the outermost index and vice versa.
# Only declarations on the $scope outermost scope levels are indexed.
# Initial $scope is 2. The following pseudo commands in the beta
# text (each on a line by itself), can be used to control the indexing 
# scope level:
#  (* idx: i *)
#     sets $scope to i
#  (* idx= i *)
#     sets $scope to i
#  (* idx+ *)
#     increments $scope by 1
#  (* idx- *)
#     decrements $scope by 1
#
# Super- and sub pattern indices are also added in the following fashion:
#    X: (#
#          Y: Z(# ... #)
#       #)
#
# yields
#    X
#      Y
#        Superpattern:
#           Z
#
# and
#    X
#      Z
#        Subpatterns:
#           Y
#
# i.e. it is assumed that the prefix is declared at the same scope.
# This is not always the case, but is impossible to check in a simple way.
# 
# Indexed words are set in bold.
#
# BUGS:
#   "enter (foo, type##)" where type is pattern variable does not work
#   Has to be written "enter (foo, type ## )"
#

# Mark '(#', '#)' and ':' in comments to avoid interference with
# subsequent matchings.

$after = $_;			# in case of no comments at all
$line = "";
while ( /\(\*|\*\)/ ) {
    $before = $`;
    $match  = $&;
    $after  = $';
    if ( $match eq '*)' ) {
        $before =~ s/:/\001/g;
	$before =~ s/\(\#/\002/g;
	$before =~ s/\#\)/\003/g;
    }
    $line .= $before.$match;
    $_ = $after;
}
$_ = $line.$after;

# Substitute ':' in slots with \004
s/(\<\<\s*SLOT\s*\w+\s*):(\s*\w+\s*\>\>)/$1\004$2/gi;

# Substitute ':' in fragmentIds with \004
#   (assumes entire fragment syntax on one line - I think)
s/(\-\-+\s*\w+\s*):(\s*\w+\s*\-\-+)/$1\004$2/g;

# Formatting commands. Notice that the '}'s and '{'s are not all here.
$format="<A href=#";
$indexid=0;

# Index text for subpatterns.
$subpatterns="_subpatterns";

# Index text for superpatterns.
$superpattern="__superpattern";

# Run through $_, matching for pattern-begin and pattern-end, while
# keeping track of scope level.
# Insert nested index-information for declarations at the outermost
# $scope levels.
$scope  = 2;

$*=0;
$patterns = "";
$revpatterns = "";
$level  = 1;
$line = "";
$prefix = "";

while ( m/\n[ \t]*\(\*\s+idx([\+\-\=\001])\s*(\d*)\s*\*\)\s*\n|\(\#|\#\)|::?<?/i ){
    $before = $`;
    $match  = $&; 
    $idxop  = $1; $idxlev = $2; # if index information present
    $after  = $';
    if ( "$idxop" ne "" ) {
	# index pseudo comment found
	if ( "$idxop" eq "+" ) { $scope++; }
	elsif ( "$idxop" eq "-" ) { $scope--; }
	if ( "$idxop" eq "=" || "$idxop" eq "\001" ) {
	    if ( "$idxlev" eq "" ) {
		die "No level specified in idx= command";
	    }
	    $scope = $idxlev;
	}
	$match = ""; # delete comment
	$after = "\n".$after;
	# $match = "\nINDEXLEVEL: $scope\n";
    }
    elsif ( "$match" eq "(#" ) {
	# add previously found identifier in scope descripion
	if ( "$patternid" ne "" ) {
	    $patterns .= "$patternid.$level:";
	} else {	   
	    $patterns .= "ANONYMOUS.$level:";
	}
	$level += 1;
	$patternid = "";
	# $match = "BEGIN";
	# $match = "\n[PATTERNS: $patterns]\n";
    }
    elsif ( "$match" eq "#)" ){	
	$level -= 1;
	if ( $patterns =~ m/:\w+.\w+:$/ ) {
	    $patterns = $`.":";
	}
	elsif ( $patterns =~ m/^\w+.\w+:$/ ) {
	    $patterns = "";
	} else {
	    $line .= $before;
	    die "PATTERNS is wrong: $patterns\nBEFORE: $line\n";
	}
	# $match .= "\n[PATTERNS: $patterns]\n";
    }
    elsif ( $match =~ m/:/ )  { # a colon was found
	if ( $level <= $scope ){
	    if ( $before =~ m/(\w+[\w\s,]*)\s*$/ ) {
		$head = $`;
		@ids = split( ',' , $1); # list of identifiers, e.g.: x, y, z
		$tail = "";
		$prefix = "";
		if ( $after =~ m/^\s*\(\*/ ) {
		    # move comment after colon but before prefix from $after to $tail
		    $tail = $&;            # the stuff matched by the regexp
		    $after = $';           # the stuff after the match
		    $after =~ m/\*\)\s*/;  # MUST succeed if comment matches
		    $tail .= $`.$&;        # the stuff before the last match and the match itself
		    $after = $';           # the stuff after the match
		}
		 
		if ( $after  =~ m/^\s*(\w+)\s*\(\#/ ) { 
		    $prefix = $1;
		} else {
		    # the match for prefix failed.
		    # look ahead and check if there was a comment after the prefix
		    # and try the match again.
		    # don't change $tail or $after, the superpattern info should be 
		    # inserted before the prefix, not after the prefix+comment
		    if ( $after =~ m/^\s*(\w+)\s*\(\*/ ) {
			# there was a comment after the word after the colon
			$possibleprefix = $1;
			# set $peekafter to the stuff after the match, i.e. start of comment text
			$peekafter = $';
			$peekafter =~ m/\*\)\s*/;  # MUST succeed if comment matches
			# set $peektext to the stuff after the match, i.e. what's after the comment
			$peekafter = $';           
			if ( $peekafter  =~ m/^\s*\(\#/ ) {
			    # there was a pattern-begin after the comment
			    $prefix = $possibleprefix; 
			}
		    }
		}
	    }
	
	    $marker = $match;
	    $match = "";

	    if ( @ids == 1 ) {
		# keep identifier for next "(#" found
		$patternid = $ids[0];
		$patternid =~ s/\s//g;
	    } else {
		$patternid = "";
	    }

	    $before = $head;
	    foreach $id ( @ids ) {
		$id =~ m/(\w+)/; # MUST succeed
		$anchor += 1;
		$idxid = "$1.$level($anchor)"; # $id without whitespace.
		$bid = "<b>$id</b>"; # anchored identifier
		if ( "$patterns" eq "" ){
		    if ( $prefix eq "" ){
			$before .= "$bid<A name=\"$idxid\"> </a>";
		    } else { # prefix is present
			# Insert super- and sub pattern information
			$super{$prefix} .= "$idxid-";
			$l = $level; $l1 = $level+1; $l2 = $level+2;
			$before .= "$bid<A name=\"$idxid\"> </a><A name=\"$prefix.$l:$subpatterns.$l1:$id.$l2\"> </a>";
			$index[$indexid] = "$idxid";
			$indexid += 1;
			$index[$indexid] = "$prefix.$l:$subpatterns.$l1:$id.$l2";
			$indexid += 1;
		    }
		} else { # inner scope
		    if ( $prefix eq "" ){
			$before .= "$bid<A name=\"$patterns$idxid\"> </a><A name=\"$idxid\"> </a>";
			$index[$indexid] = "$idxid";
			$indexid += 1;
			$index[$indexid] = "$patterns$idxid";
			$indexid += 1;
		    } else { # prefix is present
			# Insert super- and sub pattern information
			$super{$prefix} .= "$patterns$idxid-";
			$l = $level; $l1 = $level+1; $l2 = $level+2;
			$before .= "$bid<A name=\"$patterns$idxid\"> </a><A name=\"$idxid\"> </a><A name=\"$patterns$prefix.$l:$subpatterns.$l1:$id.$l2\"> </a>";
			$index[$indexid] = "$idxid";
			$indexid += 1;
			$index[$indexid] = "$patterns$idxid";
			$indexid += 1;
			$index[$indexid] = "$patterns$prefix.$l:$subpatterns.$l1:$id.$l2";
			$indexid += 1;
		    } # prefix present
		} # inner scope
		$before .= ",";
	    } # foreach id
	    $before =~ s/,$//;
	    $before .= $marker.$tail;
	} # $level <= $scope
    } # colon was found
    else {
	die "Something is wrong in while loop !!!";
    } # "switch" on $match finished
    
    $line .= $before.$match;
    $_ = $after;
} # while
		
$_ = $line."\n";

s/\n/<br>\n/g;
		
# Now insert the superpatterns collected in %super at the right places:
$external = "___Externally defined";

foreach $superid ( keys %super ) {
    @subs = split( /-/, $super{$superid});
    foreach $sub (@subs){
	$sub =~ m/((\w+\.\d+\:)*)(\w+)\.(\d+)$/;
	$subprefix = $1; $subid = $3; $sublevel = $4;
	$superprefix = $subprefix; $superlevel = $sublevel;
	if ( "$superprefix" eq "" )
	{ $l = $sublevel; $l1 = $l+1; $l2 = $l+2;
	  s/(<A name=\")$subid\.$sublevel\s*\">/$&<A name=\"$sub:$superpattern.$l1:$superid.$l2\"> <\/a>/;
	  s/(<A name=\")$superid.\d+:($subpatterns.\d+:$subid)/$1$superid.$l:$2/;
	} else
	{ loop: { if ( "$superprefix" ne "" )
		  { if ( m/\{\\v\s*$superprefix$superid.$superlevel\s*\}\}\}/ )
		    { $l = $sublevel; $l1 = $l+1; $l2 = $l+2;
		      s/(<A name=\")$superprefix$superid.$superlevel\s*\">/$&<A name=\"$sub:$superpattern.$l1:$superid.$l2\"> <\/a>/;
		      s/(<A name=\")$subprefix$superid.\d+:($subpatterns.\d+:$subid)/$1$superprefix$superid.$l:$2/;
		    } elsif ( $superprefix =~ m/\w+\.(\d+)\:$/ )
		      { $superprefix = $`; $superlevel= $1;
		        redo loop;
		      } else { $superprefix = ""; $superlevel = 1; }
		  } else
		  { $l = $sublevel; $l1 = $l+1; $l2 = $l+2;
		    s/$/$&<A name=\"$sub:$superpattern.$l1:$superid.$l2\"> <\/a>\n/;
		    s/(<A name=\")$subprefix$superid.\d+:$subpatterns.\d+:$subid.\d+/$1$external.1:$superid.2:$subpatterns.3:$subid.4/;
		  }
	        }
	}
    }
}

# Prefix to indicate one indexlevel indentation.
$indent="|  ";

# Remove levels on single index-entries.
#s/(\{\\v\s*\w+)\.\d+/$1/g;
# Insert indentation patterns for each indentation.
#while ( m/[ :](\w+)\.(\d+)[:}]/ ) {
#	$id = $1; $level = $2;
#	$indents = $indent x ($level-1);
#	s/([ \:])$id\.$level([\:}])/$1$indents$id$2/;
#}

# Clean up and insert paragraph marks.
s/\001/:/g;
s/\002/\(\#/g;
s/\003/\#\)/g;
s/\004/:/g;
#s/\n/<br>\n/g;

print;

@index = sort @index;


print "<HR><H2><A name=\"Index.identifiers\">Index of identifiers</H2><HR>";

for($i = 0; $i <= $#index; $i++) {
    $_ = $index[$i];
    s/(\s*\w+)\.\d+/$1/g;
    s/\(\d+\)//g;
    while ( m/[ :](\w+)\.(\d+)[:}]/ ) {
    $id = $1; $level = $2;
    $indents = $indent x ($level-1);
    s/([ \:])$id\.$level([\:])/$1$indents$id$2/;
}				# 

print "<A href=\"#".$index[$i]."\">".$_."</a><br>\n"
}
				# 
print "<HR>";

&print_trailer();

