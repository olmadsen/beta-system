#!/usr/local/bin/perl -s

# How to use:
# 1. Currently only possible at UNIX Sparc (because I only installed the
#    "htmldoc" program on sun4s).
# 2. Include /users/beta/GNU/bin/sun4s in your path
# 3. Create a file named 'sequence' specifying list of files to generate PDF from
#    (exclude index.html and inx.html) and title etc. to use on front page.
#    See bifrost-ref/sequence for an example.
#    cvs add sequence.
# 4. Add a "pdf:" target to your Makefile (create one if you don't have one).
#    And add "pdf" as the last thing made by 'make generated'.
#    See bifrost-ref/Makefile for an example. Notice that it's the *body*
#    files from the interface directory!
# 5. Run 'make pdf' once. This will create and cvs add the pdf file for you.
# 6. Add PDF button in top and bottom panel in your index.html.
#    See bifrost-ref/index.html for an example.
# 7. cvs commit your directory.
# 8. Change the status line for your manual in doc/admin/document-list.html
#    to indicate that the manual also exists in PDF format.

### main #######

# Command line options
$verbose = "-v" if (defined($v));

$old=1;
if ($old){
    $htmldoc = "htmldoc";
} else {
    $htmldoc = "htmldoc-1.8.3";
    #NOTICE: from config.h.in:
    #define MAX_CHAPTERS	1000
    #define MAX_COLUMNS	20
    #define MAX_HEADINGS	20000
    #define MAX_IMAGES	2000
    #define MAX_LINKS	40000
    #define MAX_OBJECTS	(10 * MAX_PAGES)
    #define MAX_PAGES	5000
    #define MAX_ROWS	2000
}

$sequence_file = "sequence";
if ($#ARGV == 0){ $sequence_file = $ARGV[0] };

open SEQUENCE, $sequence_file || die "Cannot open \"$sequence_file\" file: !$\n";
push @sequence, "title.html";
while (<SEQUENCE>){
    chomp;
    if (-f $_){
	push @sequence, $_;
    } else {
	if (m/^date: (.*)$/){ $date = $1 };
	if (m/^mia: (.*)$/){ $mia = $1 };
	if (m/^title: (.*)$/){ $title = $1 };
	if (m/^copyright: (.*)$/){ $copyright = $1 };
	if (m/^pdf: (.*)$/){ $pdf= $1 };
    }
}
$pdfexisted=1 if ( -f $pdf );
&make_titlepage();
$files = join (' ', @sequence);
$cmd = "$htmldoc $verbose -t pdf -f $pdf --toclevels 4 --bodycolor #ffffff --size A4 --left 1.0in --right 0.5in --top 0.5in --bottom 0.5in --header .t. --footer h.1 --tocheader .t. --tocfooter l.i --firstpage p1 --compression=9 --fontsize 11.0 --fontspacing 1.2 --headingfont Helvetica --bodyfont Helvetica --headfootsize 11.0 --headfootfont Helvetica $files";

print "Generating $pdf\n";
print "$cmd\n" if $verbose;
$ENV{'LD_LIBRARY_PATH'} = "/usr/local/lib";
system "$cmd" || die "ERROR in HTMLDOC !!!";
unlink "title.html";

if (-f $pdf){
    print "Wrote $pdf\n";
    if (!$pdfexisted) {
	print "Seems to be first generation of $pdf. CVS adding...\n";
	$cmd = "cvs add -kb $pdf";
	print "$cmd\n";
	system($cmd);
    }
} else {
    print "\n***FAILED to generate $pdf!\n\n";
}

exit 0;


#### helper functions ####

sub make_titlepage()
{
    open TITLE, ">title.html" || die "Cannot open title.html for writing: $!\n";
    print TITLE <<"EOT";
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
>
<HTML>
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">
<TITLE>$mia: $title</TITLE>
<LINK REL=stylesheet HREF=../style/miadoc.css TYPE=text/css>
</HEAD>
<BODY>
<H1>Copyright Notice</H1>
<center><B>
Mj&oslash;lner Informatics Report<BR>
$mia<BR>
$date
</B>
<P>
<TABLE border=1 cellpadding=3>
<TR><TD align=center>
Copyright &copy; $copyright <IMG SRC="../images/trans5x5.gif" WIDTH=10 HEIGHT=5 ALT=""><A HREF="http://www.mjolner.com">Mj&oslash;lner Informatics</A>.<BR>
All rights reserved.<BR>
No part of this document may be copied or distributed<BR>
without the prior written permission of Mj&oslash;lner Informatics
</TD></TR>
</TABLE>
</center>
<HR BREAK>
</BODY>
</HTML>
EOT

    close TITLE;
}
