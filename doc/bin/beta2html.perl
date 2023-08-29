#!/usr/bin/perl

sub usage()
{
    print "Usage:\n";
    print "beta2html.perl -n next_URL -p previous_URL -t title <betafiles>\n";
    exit 1;
}

# Parse arguments

&usage() if ($#ARGV < 6);

$waiting_for_next=0;
$waiting_for_prev=0;
$waiting_for_title=0;

while ($#ARGV>=0) {
    if ($waiting_for_next){
	$next=$ARGV[0]; $waiting_for_next=0; shift(@ARGV);
    } elsif ($waiting_for_prev){
	$prev=$ARGV[0]; $waiting_for_prev=0; shift(@ARGV);
    } elsif ($waiting_for_title){
	$title=$ARGV[0]; $waiting_for_title=0; shift(@ARGV);
    } elsif ($ARGV[0] eq "-n") {
	$waiting_for_next=1; shift(@ARGV);
    } elsif ($ARGV[0] eq "-p") {
	$waiting_for_prev=1; shift(@ARGV);
    } elsif ($ARGV[0] eq "-t") {
	$waiting_for_title=1; shift(@ARGV);
    } else {
	last;
    }
}

&usage() if ($waiting_for_next || $waiting_for_prev || $waiting_for_title);

foreach $betafile (@ARGV) {
    next if ($betafile =~ /~$/);
    next if ($betafile !~ /\.bet$/);
    print "$betafile";
    if (length($betafile) > 30){
	print "\n";
    }
    print "  -> ";
    open(IN, $betafile) || die "$0: Cannot open file: $betafile: $!\n";
    $contents="";
    while (<IN>){
	$contents .= $_;
    }
    close IN;

    $htmlfile = $betafile;
    $htmlfile =~ s/\.bet$/.html/i;
    print "$htmlfile\n";

    open(OUT, ">$htmlfile") || die "$0: Cannot write output $!";

    print OUT<<"EOT";
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
>
<HTML>
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">
<TITLE>$title</TITLE>
<LINK REL="stylesheet" HREF="../style/miadoc.css" TYPE="text/css">
</HEAD>

<BODY>

<P>
<A HREF=$next><IMG ALIGN=BOTTOM SRC="../images/next.gif" ALT=Next BORDER=0></A> 
<A HREF=$prev><IMG ALIGN=BOTTOM SRC="../images/prev.gif" ALT=Previous BORDER=0></A> 
<A HREF=../index.html><IMG ALIGN=BOTTOM SRC=../images/top.gif ALT=Top BORDER=0></A> 
<A HREF=index.html#_toc><IMG ALIGN=BOTTOM SRC="../images/content.gif" ALT=Contents BORDER=0></A>
<A HREF=inx.html><IMG ALIGN=BOTTOM SRC="../images/index.gif" ALT=Index BORDER=0></A>
<P>

<H1>$title</H1>
EOT

    print OUT "<A NAME=\"$betafile\"><H4 class=betacaption>$betafile</H4></A>\n";
    print OUT "<PRE CLASS=beta>\n";
    $contents =~ s/&/&amp;/g;
    $contents =~ s/</&lt;/g;
    $contents =~ s/>/&gt;/g;
    print OUT $contents;
    print OUT "</PRE>\n";

print OUT<<"EOT";
<!---------------------------------------------------------->
<HR>
<P>
<TABLE cols=3 border=0 width=100%>
<TR>
<TD width="40%" align="left">
<ADDRESS>$title</ADDRESS>
</TD>
<TD width="20%" align="center"><FONT size=-1>&COPY; <A HREF="http://www.mjolner.com">Mj&oslash;lner Informatics</A></FONT></TD>
<TD width="40%" align="right"><SCRIPT LANGUAGE=JavaScript SRC="../javascript/lastmod.js"></SCRIPT></TD>
</TABLE>
<P>
<A HREF=$next><IMG ALIGN=BOTTOM SRC="../images/next.gif" ALT=Next BORDER=0></A> 
<A HREF=$prev><IMG ALIGN=BOTTOM SRC="../images/prev.gif" ALT=Previous BORDER=0></A> 
<A HREF=../index.html><IMG ALIGN=BOTTOM SRC=../images/top.gif ALT=Top BORDER=0></A> 
<A HREF=index.html#_toc><IMG ALIGN=BOTTOM SRC="../images/content.gif" ALT=Contents BORDER=0></A>
<A HREF=inx.html><IMG ALIGN=BOTTOM SRC="../images/index.gif" ALT=Index BORDER=0></A>

</BODY>
</HTML>
EOT

    close OUT;
}
