#!/usr/local/bin/perl

# Generates (on stdout) an HTML page which automatically
# redirect browsers to the URL specified as argument.
# Useful to place instead of a page, when the original page
# has been moved. This way old bookmarks will still work.

if ($#ARGV!=1){
    print "Usage: make_redirect_page.perl <new-url> <seconds>\n";
    exit 1;
}

$url=$ARGV[0];
$time=$ARGV[1];

print<<EOT
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
>
<HTML>
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">
<TITLE>Page Moved</TITLE>
</HEAD>

<META HTTP-EQUIV=REFRESH CONTENT="$time; URL=$url">

<BODY>

<H2>Page has moved to <A HREF="$url">$url</A></H2>

</BODY>
</HTML>
EOT

