#!/usr/local/bin/perl

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
#    See bifrost-ref/Makefile for an example.
# 5. Run 'make pdf' once. This will create and cvs add the pdf file for you.
# 6. Add PDF button in top and bottom panel in your index.html.
#    See bifrost-ref/index.html for an example.
# 7. cvs commit your directory.
# 8. Change the status line for your manual in doc/admin/document-list.html
#    to indicate that the manual also exists in PDF format.

### main #######

open SEQUENCE, "sequence" || die "Cannot open \"sequence\" file: !$\n";
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
$cmd = "htmldoc-1.8b4 -v -t pdf -f $pdf --toclevels 4 --bodycolor #ffffff --size A4 --left 1.0in --right 0.5in --top 0.5in --bottom 0.5in --header .t. --footer h.1 --tocheader .t. --tocfooter l.1 --compression=9 --fontsize 11.0 --fontspacing 1.2 --headingfont Helvetica --bodyfont Helvetica --headfootsize 11.0 --headfootfont Helvetica $files";

print "$cmd\n";
$ENV{'LD_LIBRARY_PATH'} = "/usr/local/lib";
system "$cmd";
unlink "title.html";
print "Wrote $pdf\n";
if (!$pdfexisted) {
    print "Seems to be first generation of $pdf. CVS adding...\n";
    $cmd = "cvs add -kb $pdf";
    print "$cmd\n";
    system($cmd);
}

exit 0;


#### helper functions ####

sub make_titlepage()
{
    open TITLE, ">title.html" || die "Cannot open title.html for writing: $!\n";
    print TITLE <<"EOT";
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<HTML>
<HEAD>
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
Copyright &copy; $copyright <IMG SRC="../images/trans5.5.gif" WIDTH=10 HEIGHT=5 ALT=""><A HREF="http://www.mjolner.com">Mj&oslash;lner Informatics</A>.<BR>
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
