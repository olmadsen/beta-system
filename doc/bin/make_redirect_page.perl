#!/usr/local/bin/perl

# Generates (on stdout) an HTML page which automatically
# redirect browsers to the URL specified as argument.
# Useful to place instead of a page, when the original page
# has been moved. This way old bookmarks will still work.

if ($#ARGV!=0){
    print "Usage: make_redirect_page.perl <new-url>\n";
    exit 1;
}

$url=$ARGV[0];

print<<EOT
<HTML>
<HEAD>
<TITLE>Page Moved</TITLE>
</HEAD>

<META HTTP-EQUIV=REFRESH CONTENT="2; URL=$url">

<BODY>

<H2>Page has moved to <A HREF="$url">$url</A></H2>

</BODY>
</HTML>
EOT

