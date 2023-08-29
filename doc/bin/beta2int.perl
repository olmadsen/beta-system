#!/usr/bin/perl

# Read entire input-stream into $line, while doing single-line editing.

while ( <> ) {

    # Delete fragment syntax (removed by JLK)
    # next if /\bORIGIN\b/i;
    # next if /\bBODY\b/i;
    # next if /\[\[/;
    # next if /--\s*\bINCLUDE\b/i;
    # next if /--.*\bATTRIBUTES\b/i;
    # next if /--\]\]/;
    
    # << .... descriptor>> -> "..."
    s/<<.*\bOBJECTDESCRIPTOR\b.*>>/.../gi;
    s/<<.*\bDESCRIPTOR\b.*>>/.../gi;
    s/<<.*\bDOPART\b.*>>/.../gi;    

    # Uppercase inner
    s/\bINNER\b/INNER/gi;
    # Remove trailing blanks
    s/^(.*)\s*$/$1\n/;
           
    # Squeze multiple blank lines down into one
    next if /\S/ ? ($was_blank=0) : $was_blank++;

    $line .= $_;
    
};				
				
# Now perform multiline editing

$*=1;
$_=$line;

# delete RCS/CVS stuff
s/\$\Revision:[^\$]*\$//;
s/\$\RCSfile:[^\$]*\$//; 
s/\$\Date:[^\$]*\$//;
s/\$\Author:[^\$]*\$//;

s/\bdo\s*\.\.\./do .../gi;
s/\bINNER(;?)\s*\.\.\./INNER$1 .../g;
# s/\n\s*INNER(;?)/ INNER$1/g;
s/do\b\s*/do /gi;
s/\(\#\s*do\s+INNER(;?)\s*\#\)/\(\# do INNER$1 \#\)/g;
s/\(\#\s*do\s+INNER(;?)\s+\.\.\.\s*\#\)/\(\# do INNER$1 ... \#\)/g;
s/\(\#\s*do\s+\.\.\.\s+INNER(;?)\s*\#\)/\(\# do ... INNER$1 \#\)/g;
s/\(\#\s*do\s+\.\.\.\s+INNER(;?)\s+\.\.\.\s*\#\)/\(\# do ... INNER$1 ... \#\)/g;
s/(:< *)\s*\(\#(.*)\#\);?/$1(\#$2\#);/g;
s/\.\.\.  /... /g;

# Delete private virtuals/patterns/instances of the form
#  foo:<  (* private *) [(* ... *)] (# ... #)
#  foo::< (* private *) [(* ... *)] (# ... #)
#  bar:   (* private *) [(* ... *)] (# ... #) 
#  bar:   (* private *) [(* ... *)] @ (# ... #)
#  foo:<  (* private *) [(* ... *)] yyy (# ... #)
#  foo::< (* private *) [(* ... *)] yyy (# ... #)
#  bar:   (* private *) [(* ... *)] yyy (# ... #) 
#  bar:   (* private *) [(* ... *)] @ yyy (# ... #)
#  x:   (* private *) [(* ... *)] {@,^,##} yyyy;
#  x:   (* private *) [(* ... *)] @ yyyy(# ... #);
#  x:<  (* private *) [(* ... *)] yyyy;
#  x::< (* private *) [(* ... *)] yyyy;

#s/^[\w,\s]*\s*\::?<?\s*\(\* private \*\)\s*\@?\s*\w*\s*\(\#[^\#]*\#\);?\s*\n//gi;
#s/^[\w,\s]*\s*\::?<?\s*\s*\(\* private \*\)\s*\(\*[^\*]*\*\)\s*\@?\s*\w*\s*\(\#[^\#]*\#\);?\s*\n//gi;

#s/^[\w,\s]*\s*\:\:?<?\s*\(\* private \*\)\s*\@?\^?\#?\#?\s*\w*\s*\;?\s*\n//gi;
#s/^[\w,\s]*\s*\:\:?<?\s*\(\* private \*\)\s*\@?\s*\w*\s*\(\#[^\#]*\#\);?\s*\n//gi;
#s/^[\w,\s]*\s*\:\:?<?\s*\(\* private \*\)\s*\(\*[^\*]*\*\)\s*\@?\^?\#?\#?\s*\w*\s*\;?\s*\n//gi;
#s/^[\w,\s]*\s*\:\:?<?\s*\(\* private \*\)\s*\(\*[^\*]*\*\)\s*\@?\s*\w*\s*\(\#[^\#]*\#\);?\s*\n//gi;


# Delete other lines containing the word "private" or the word "implpart"
#s/.*private.*\n+//gi;
s/.*implpart.*\n+//gi;

print;
