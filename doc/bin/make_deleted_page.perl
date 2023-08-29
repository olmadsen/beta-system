#!/usr/bin/perl

# Generates (on stdout) an HTML page which tells the user that
# a page has been deleted.

if ($#ARGV!=0){
    print "Usage: make_deleted_page.perl <alternative-url>\n";
    exit 1;
}

$url=$ARGV[0];

print<<EOT
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
>
<HTML>
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">
<TITLE>Page Deleted</TITLE>
</HEAD>

<META HTTP-EQUIV=REFRESH CONTENT="2; URL=$url">

<BODY>

<H2>Page has been deleted. Please goto <A HREF="$url">$url</A> instead.</H2>

</BODY>
</HTML>
EOT

