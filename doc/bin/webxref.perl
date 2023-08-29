#!/usr/bin/perl
# Note: Webxref now is a Perl5 script, let the author know 
# if this is a problem.

# ==============================================================
#  W E B X R E F
# ==============================================================
# Webxref is a WWW link checker and cross referencing tool, intended
# to quickly check a local set of HTML documents for missing files,
# anchors etc. You simply call webxref with a HTML document as the 
# parameter, without any configuring. 
# Webxref compiles a list of HTML documents, URLs, name anchors, 
# images etc and the html files that reference those, i.e. a 
# cross-reference list. Hence the name: webxref.
# 
# Written July 1995 by Rick Jansen at SARA as part of the SURFACE 
# project (SURFnet Advanced Communication Environment)
# Updated February-March 1997 by Rick Jansen as part of the zoutmijn
# project.
# email:  rja@euronet.nl
# url:    http://www.sara.nl/Rick.Jansen
#
# New versions can be obtained from:
#   http://www.sara.nl/Rick.Jansen/Web/
#
# Usage: see PrintHelp
#
# Lists are made of:
# - html files
# - directories
# - binary files (images)
# - named anchors
# - mailto's
# - news
# - ftp
# - telnet
# - gopher
# - external URLs
# - cgi-bin scripts
# - file:'s
# - files that can't be found
# - files that are not world readable
# - directories that can't be found
# - name anchors that can't be found
# - files and directories in your website never actually used
# - files whose content matched the find parameter
# - files in which text was search-replaced
# - files older/younger than a certain date/time
# - http:// ok references
# - http:// failed references
#
# Modification history:
# 11-JUL-95 lcheck version 0.0.0
# 18-JUL-95 renamed webxref 0.0.1
# 20-JUL-95 webxref 0.0.2
# 21-JUL-95 webxref 0.0.3 root handling
# 27-JUL-95 webxref 0.0.4 metachar interpretation in substitutions fixed
# 28-JUL-95 webxref 0.0.5 pass associative array to sub
# 08-AUG-95 webxref 0.0.6 parsing with temp file
# 08-AUG-95 webxref 0.0.7 handle Welcome/welcome/index.html in case of dir
# 08-AUG-95 webxref 0.0.8 'file:' refs
# 10-AUG-95 webxref 0.0.9 Extensible DefaultFiles
# 14-AUG-95 webxref 0.1.0 Some perl lint removed, cgi-bin added
# 28-SEP-95 webxref 0.1.1 1-level external URL checking added
# 04-OCT-95 webxref 0.1.2 options -nohttp -htmlonly and -avoid added
# 04-OCT-95 webxref 0.1.3 Restriction on tags not being allowed to spread
#                         over more than 1 source line removed, thanks to
#                         Hans Hoppe (hopha@sci.kun.nl)
# 10-OCT-95 webxref 0.1.4 -silent option
# 15-APR-96 webxref 0.1.5 Temporary fix for $SOCK_STREAM
# 22-FEB-97 webxref 0.2.0 Updated internals
# 23-FEB-97 webxref 0.2.0 added -root, -noxref and -islocal
# 26-FEB-97 webxref 0.2.0 added TryExtensions, try html, htm in case of
#                         missing extension
# 01-MAR-97 webxref 0.2.1 speedup by testing files before recursing
# 01-MAR-97 webxref 0.2.2 optional testing for fluff (never referenced files)
# 02-MAR-97 webxref 0.2.3 -depth, -find and -replace 
# 02-MAR-97 webxref 0.2.4 -before -after -date -time
# 02-MAR-97 webxref 0.2.5 -one, frames
# 03-MAR-97 webxref 0.2.6 switched to less verbose output
# 03-MAR-97 webxref 0.2.6 on interrupt print output so far and exit
# 03-MAR-97 webxref 0.2.6 -long/-brief -errors -verbose 
# 04-MAR-97 webxref 0.2.7 interrupt handling, extended -help
# 04-MAR-97 webxref 0.2.8 fixed bug in ../.. constructions
# 05-MAR-97 webxref 0.2.9 area href and another ../ bug
# 05-MAR-97 webxref 0.3.0 delay in http checking
# 07-MAR-97 webxref 0.3.1 two roots from now: server root and site root
# 07-MAR-97 webxref 0.3.2 -html
# 12-MAR-97 webxref 0.3.3 -onexref -intermediair
# 13-MAR-97 webxref 0.3.4 garbage collection while printing (undef %list)
# 13-MAR-97 webxref 0.3.5 bug fixed in fluff detector and -avoid, -noint
#

# ===================================================================
# DISCLAIMER: the author cannot be held responsible for any damage
# resulting from using the edit- or any other functions of webxref
# or indeed any software, hardware, chemical substance, imagined
# or real (or imagined to be real) effects or by-effects of anything,
# at all, whatsoever. I didn't do it. Honestly.
# ===================================================================



# Pay attention, webxref starts here

$debug = 0;  # Bugs? haha! hm.

#---------------------------------------------
# Configurable things:

# Files to try in case of a directory reference like ../..
@DefaultFiles = ('index.html','index.htm',
                 'welcome.html','Welcome.html',
                 'Index.html','index.shtml',
                 'README.html');
@Extensions =   ('html','htm','shtml');

$MaxDots = 50;  # 50 +/-'s per line max
#---------------------------------------------

&GetParams;

# Hello
print <<EOM if ($HTMLReport);
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
                      "http://www.w3.org/TR/REC-html40/loose.dtd"
>
<HTML>
<HEAD>
<META http-equiv="Content-Type" CONTENT="text/html; CHARSET=ISO-8859-1">

<LINK REL="stylesheet" HREF="../style/miadoc.css" TYPE="text/css">
<title>
Errors Found
</title>
</head>
<body>
<h1>Errors Found</h1>
EOM

# If interrupted print output so far
# NOTE: This is unreliable if webxref was interrupted
# asynchronously. The C-library is not re-entrant, so
# if printing was in progress printing may well fail
# due to malloc running into trouble. Oh well. It does
# work sometimes.
$SIG{INT} = 'InterruptHandler' if (! $NoInterrupt);

$WebxrefReferer = '--webxref--';
foreach (@ARGV) {
  # Does the input file exist at all?
  if (! -e $InFile) {
    &AddedToList(*LostFileList,$InFile,$WebxrefReferer);
    print "Cannot find file $InFile\n";
    next;
  }


  # Assume webxref is called in the document root directory if
  # no root supplied as a parameter
  $SiteRoot = &GetCWD;
  die "The site directory $SiteRoot does not exist" unless -e $SiteRoot;
  die "\"$SiteRoot\" is not a directory" unless -d $SiteRoot;
  die "Cannot access directory \"$SiteRoot\"" unless -r $SiteRoot;
  
  # Expression to replace root filepath when printing
  $SiteRootExpr = $SiteRoot;
  if ($SiteRootExpr !~ m#/$#) { $SiteRootExpr .= '/'; }
  $SiteRootExpr =~ s/(\W)/\\$1/g;  # escape regexp chars

  $ServerRoot = $SiteRoot if (!$ServerRoot);
  $ServerRootExpr = $ServerRoot;
  if ($ServerRootExpr !~ m#/$#) { $ServerRootExpr .= '/'; }
  $ServerRootExpr =~ s/(\W)/\\$1/g;  # escape regexp chars

  ($d,$f,$a,$RootDepth) = &SplitFile($SiteRoot);
  #print "\nSiteRoot=$SiteRoot, \nd=$d \nf=$f \na=$a \ndep=$RootDepth\n";
  $MaxDepth = $MaxDepth + $RootDepth;
  #print "Maxdepth=$MaxDepth\n";
  
  #print "<pre>\n" if ($HTMLReport);

  &GetFluffFiles($SiteRoot) if ($Fluff);
  
  #if (!$Silent) { print "\nChecking $InFile\n\n"; }
  $InFile = $SiteRoot . $_;
  &GetReferences($InFile,"--webxref--");
}

# See if there are any never-referenced files
&PickFluff if ($Fluff);

#print "</pre>\n" if ($HTMLReport);

&PrintLists;

$DotCount = 0;
if ($Do_External_URLs  && (%HTTPList)) {
  print STDERR "\n\nExternal HTTP checking starts\n" if ($Dots);
}

# Check external URLs
if (($Do_External_URLs) && (%HTTPList)) {
  if (!$Silent) {
  print STDERR <<"E_O_T";

- - - - - - - - - - - - - - - - - - - - - - - - - - -
Going to really check external URLs via the network.
This may take some time. Simply abort webxref if you
are out of patience.
- - - - - - - - - - - - - - - - - - - - - - - - - - -
E_O_T

}


  &InitStatusMessages;
  &Check_External_URLs("Checking external URLs:", %HTTPList);
}

$Xref=0;
&PrintList(*FileList,"Local documents found:",0);
&PrintList(*HTTPList,"External URLs found:",0);
&PrintList(*MailList,"Mailto: links found",0);

print STDERR "\nAll done.\n";

print <<EOM if ($HTMLReport);
</body>
</html>
EOM


exit;  # End of webxref

#---------------------------------------------

sub InterruptHandler {

# Called on interrupt
# Print output accumulated so far and exit

$| = 0;
print "\n\n** Interrupt!\n";

&PrintLists;
exit;

}


#---------------------------------------------

sub GetParams {

# Process parameters

$Do_External_URLs = 1; # Default we do check external URLs

$HTML_only = 0;        # If 0, referenced files are checked for links
                       # even if the file has no .html extension

$Avoid = "";           # Regexp to avoid certain URLs, files,...

# Silent: webxref keeps shut up entirely, apart from failed things
#         in the end
# Verbose: webxref tells which files it checks on the way and reports
#          errors immediately
# Dots:    if true print a '+' for each file tested, print a '-' if failed
# Errors:  print errors right away, even if silent is true
$Silent = 1;           # If silent=1 only error msgs will be printed
$Verbose = 0;          # Default as little output as possible
$Dots = 1;             # Print a + for every file checked (- if failed)
$Errors = 0;           # Print error messages only

$Xref = 1;             # Default generation of cross references

$MaxDepth = 99999999;  # Default max nesting level

$Fluff = 0;            # Default do check for never referenced files

$LongReport = 0;       # Short report is default

$FullPath = 0;        # If true print full filepaths

$HTTPDelay = 1;        # default 1 second between external link checks

$Time = '000000';

$NoInterrupt = 0;      # Default webxref is interruptable

$InFile = "";
while ($ARGV[0] =~ /^-/) {
  if    ($ARGV[0] eq "-help")     { &PrintHelp; }
  if    ($ARGV[0] eq "-h")        { &PrintHelp; }

  elsif ($ARGV[0] eq "-noxref")   { $Xref = 0; }
  elsif ($ARGV[0] eq "-xref")     { $Xref = 1; }
  elsif ($ARGV[0] eq "-onexref")  { $OneXref = 1; }
  elsif ($ARGV[0] eq "-x")        { $Xref = 1; }
  elsif ($ARGV[0] eq "-htmlonly") { $HTML_only = 1; }

  elsif ($ARGV[0] eq "-nohttp")   { $Do_External_URLs = 0; }
  elsif ($ARGV[0] eq "-delay")    { $HTTPDelay = &NextArg; }

  elsif ($ARGV[0] eq "-nofluff")  { $Fluff = 0; }
  elsif ($ARGV[0] eq "-fluff")    { $Fluff = 1; }

  elsif ($ARGV[0] eq "-silent")   { $Silent = 1; $Dots = 0; }
  elsif ($ARGV[0] eq "-s")        { $Silent = 1; $Dots = 0; }
  elsif ($ARGV[0] eq "-verbose")  { $Verbose = 1; $Silent = 0; 
                                    $Dots = 0;  $Errors = 1; }

  elsif ($ARGV[0] eq "-noint")    { $NoInterrupt = 1; }

  elsif ($ARGV[0] eq "-v")        { $Verbose = 1; $Silent = 0; 
                                    $Dots = 0; $Errors = 1; }
  elsif ($ARGV[0] eq "-errors")   { $Errors = 1; }
  elsif ($ARGV[0] eq "-error")    { $Errors = 1; }
  elsif ($ARGV[0] eq "-e")        { $Errors = 1; }

  elsif ($ARGV[0] eq "-long")     { $LongReport = 1; }
  elsif ($ARGV[0] eq "-l")        { $LongReport = 1; }
  elsif ($ARGV[0] eq "-brief")    { $LongReport = 0; }
  elsif ($ARGV[0] eq "-html")     { $HTMLReport = 1; }

  elsif ($ARGV[0] eq "-islocal")  { $IsLocal = &NextArg; }
  elsif ($ARGV[0] eq "-avoid")    { $Avoid = &NextArg; }
  elsif ($ARGV[0] eq "-a")        { $Avoid = &NextArg; }

  elsif ($ARGV[0] eq "-root")     { $ServerRoot = &NextArg; }
  elsif ($ARGV[0] eq "-r")        { $ServerRoot = &NextArg; }
  elsif ($ARGV[0] eq "-fullpath") { $FullPath = 1; }

  elsif ($ARGV[0] eq "-depth")    { $MaxDepth = &NextArg; }
  elsif ($ARGV[0] eq "-one")      { $One = 1; }
  elsif ($ARGV[0] eq "-1")        { $One = 1; }

  elsif ($ARGV[0] eq "-date")     { $Date = &NextArg; }
  elsif ($ARGV[0] eq "-time")     { $Time = &NextArg; }
  elsif ($ARGV[0] eq "-before")   { $Before = 1; }
  elsif ($ARGV[0] eq "-after")    { $After = 1; }

  elsif ($ARGV[0] eq "-files")    { shift @ARGV; last; }
  elsif ($ARGV[0] eq "-f")        { shift @ARGV; last; }

  elsif ($ARGV[0] eq "-find")     { $FindExpr = &NextArg; 
                                    $OrgFindExpr = $FindExpr;
                                    # escape regexp chars
                                    $FindExpr =~ s/(\W)/\\$1/g;  
                                  }
  elsif ($ARGV[0] eq "-findexpr") { $FindExpr = &NextArg; 
                                    $OrgFindExpr = $FindExpr;
                                  }
  elsif ($ARGV[0] eq "-replace")  { $FindExpr = &NextArg; 
                                    $OrgFindExpr = $FindExpr;
                                    # escape regexp chars
                                    $FindExpr =~ s/(\W)/\\$1/g;  
                                  }
  elsif ($ARGV[0] eq "-replaceexpr")  { $FindExpr = &NextArg; 
                                        $OrgFindExpr = $FindExpr; }
  elsif ($ARGV[0] eq "-by")       { $Replacement = &NextArg; }

  elsif ($ARGV[0] eq "-intermediair") { $Intermediair = 1; }  # Special case

  else {&PrintUsage; exit;} 

  shift @ARGV;
}

$InFile = $ARGV[0];
die "No input file(s).\n(try webxref -help)\n" if ($InFile eq "");

if ($After || $Before) {
  die "You cannot specify both -before AND -after\n" if ($Before && $After);
  die "-time format must be hhmmss or hhmm" 
    unless ($Time =~ /\d\d\d\d(\d\d)?/);
  die "-date format must be yymmdd or yymm" 
    unless ($Date =~ /\d\d\d\d(\d\d)?/);

  $Before = 0 if ($After);  # We don't user $After
  $TimeStamp = &ConvertTimeStamp($Date,$Time);
}

if ($IsLocal) {
  $IsLocal =~ s#^http://##;   # Delete http://
  $IsLocal =~ s#/*##;         # delete port no
  $IsLocal =~ s/(\W)/\\$1/g;  # escape regexp chars
}

}  # GetParams



sub NextArg {

  shift @ARGV;
  return $ARGV[0];

}  # NextArg




sub PrintUsage {

print <<"E_O_T";

Usage: webxref  -help/-h -noxref -xref/-x -onexref -fluff -htmlonly 
                -nohttp -delay seconds
		-silent/-s -verbose/-v -errors/-e -noint
		-long/-l -html
		-islocal <address> -avoid/-a <regexp>
		-one/-1 -depth <depth>
		-root/-r <server rootdir> -fullpath
		-date <yymmdd> -time <hhmmss> -before -after
		-find <string> -findexpr <regexp>>
		-replace <string> -replaceexpr <regexp> -by <string/expr>
		[-files/-f] file1 file2
		file.html

E_O_T

}



sub PrintHelp {

&PrintUsage;

print <<"E_O_T";
=========================================
Which parameters to use for what purpose:
=========================================
Default webxref checks the given file and follows the links in 
that file. While working it lets you know it's alive by printing 
a '+' for each file checked ok, and a '-' for each file with a 
problem.  

A webxref run can take some time. You can, however, interrupt
webxref with ctrl-c (Unix). Webxref will report on the files
it has inspected up to that moment and exit. (*New!*)
(Note: this is not reliable! webxref is not interruptable at
any time, due to the C-libraries not being re-entrant. (This
probably does not interest you at all, but it's not the
author's fault.)) Specify -noint if you don't want webxref to
try and generate output after an interrupt.

When the whole site has been searched and all links have been 
inspected webxref prints a report. Default only problems are
reported. Specify -long to obtain a long report. Specify -html
to get a report in HTML form.

If you want more information while webxref is working specify
-verbose to get messages on every file or -errors to see only
files with problems. With -silent webxref prints nothing at
all while working.

Webxref keeps track of which html-documents are being linked
to from other documents. This is called cross-referencing,
hence webxref's name. If you are not interested in this,
specify -noxref, so you won't be told where things have 
failed and probably have to run webxref again. If you're 
just interested in one location where a file is referenced
specify -onexref. This saves memory too.

If you need to know if there are files and/or directories in
your site that are not referenced at all by any pages in your
site specify -fluff. 

If you want to only inspect files that really have the .html 
or .htm extension specify -htmlonly

References starting with a '/', like <a href=/icons/icon.gif>
refer to the server "root" directory. Specify where this 
directory is with -root

File names are abbreviated, that is /u/people/rick/www/a.html
is printed as "a.html" is webxref is called from ~/rick/www.
If you specify -fullpath you'll get the full paths.

If you use full URLs in your site referring to your own site,
say "www.sara.nl" is your www-address and you use links like
<a href=www.sara.nl/rick/index.html> then tell webxref that
"www.sara.nl" actually can be found on the local machine with:
-islocal 'www.sara.nl'

If you want to avoid certain files use the -avoid parameter
to specify which files to avoid. 

If you want to limit the number of files webxref inspects
you may want to limit the scan to 1 or 2 directories deep
in the file system. If you specify -depth 0 only files in
the current directory are inspected.

If you just want to check if links in a file are valid 
specify -one (or -1). Only the links present in the file are 
tested, but no more. Use this with -files to specify
a collection of files to just check those files.

When all local files are inspected webxref goes out into
the net to check if the http:// links work. This may be
time-consuming. Specify -nohttp if you don't want that.
To avoid overloading a webserver there is a delay of 1 second 
between checks. If you want longer or shorter delays specify 
the number of seconds with -delay. (Longer delays may be 
necessary if a lot of links refer to the same webserver.)

To see if you have files or directories that were modified
last before or after a certain date/time use:
-before/-after -date yymmdd -time hhmmss. If -before
is given files are reported that were modified before the 
date given, with -after files last modified after the date
given are reported.

To tell webxref which files to inspect simply list the file
or files at the end of the command, or use -files or -f

Webxref can search and even search-replace text, see later.

=======================
What the parameters do:
=======================
While checking webxref prints output according to:
-silent/-s	Only list files with problems at the end of the run.
-verbose/-v	Print information while checking files.
-errors/-e	Print errors when they occur, even when -silent.
-noint		Do not generate output on interrupt

Webxref generates a report according to:
-long/-l	List all files found, not just problems.
-xref/-x	List which files reference files (cross-references).
-noxref		Do not list which files reference files (default).
-html		Print report in html form, links made active and all.

Webxref inspects files/directories according to:
-fluff		List which files/directories are never used.
-htmlonly	Only inspect files with the .html/.htm extension.
-root rootdir	The server root where cgi-bin, icons etc reside
		default: the directory where webxref is called.
		Links like <a href=/index.html> are looked for
		in the rootdir directory.
-fullpath	Print full-length filenames, e.g. /u/people/rick/www.html
-islocal url	'www.mymachine.nl' is actually a local file reference.
-avoid regexp	Avoid files with names matching regexp for inspection.
-depth number	The maximum directory nesting level.
		0 means: current directory only,
		1 means: directories from the current directory.
		100 probably means there is no restriction in
		how deep webxref is allowed to find files.
-one/-1		Specify -one if you just want to check the links
		from the given file(s) and no further link following.
-nohttp		Do not check external URLs via the network.
-delay seconds	Wait the specified number of seconds between HTTP checks
-date -time	Date [yymm<dd>], time [hhmm<ss>].
-before -after	List files that are modified before or after
		the date/time given with -date and -time.
-files/-f files	If you want webxref to test a series of files
		user the -files parameter, else simply list the
		file to test last. 

=================
Find/replacement: ** EXPERT ONLY **
=================
Webxref can scan your site for files containing certain text. 
To find fixed text use -find. To find text using e.g. wildcards 
use -findexpr. The Perl expression is matched with the text of
the file under test. Take care to not have the shell interpret 
'*' and '/' by using appropriate quoting. Search is always case-
insensitive.  Webxref does search/replace beyond end-of-line. 
I.e. newlines are matched, and can even be inserted (use \n).

To replace text with something else use -replace and -replaceexpr
and -by. The string or expression you specify with -replace or
-replaceexpr is replaced by the string you specify with -by. 
In case of editing, a backup file with a random numeric extension
is placed next to the resulting file. E.g. when index.html is
edited there'll be a file "index.html.1234" or something similar.
(DISCLAIMER: the author cannot be held responsible for any damage
resulting from using the edit- or any other functions of webxref
or indeed any software, hardware, chemical substance, imagined
or real (or imagined to be real) effects or by-effects of anything,
at all, whatsoever.)

-find string		report files containing the given string
-findexpr regexp	report files containing the given expression
-replace string		*REPLACE* string by the string given with -by
-replaceexpr regexp	*REPLACE* regexpr by the string given with -by
-by string		replacement string (or regexp)
-nobackup		Not implemented on purpose.

========
Examples
========
webxref file.html
	Checks file.html and files/URLs referenced from file.html
	Only lists problems at the end of the run, + and - for each
	file checked.
webxref index.html another.html
	checks index.html and another.html
webxref -one index.html
	just check the links in index.html, don't follow the links
webxref -one *.html
	Check only the links in the html-files in the current dir.
webxref -depth 0 index.html
	Check index.html, but don't check files in directories
	that are deeper in the file system. 
webxref -nohttp file.html
	Checks file.html, but not external URLs
webxref -htmlonly file.html
	Checks file.html, but only files with the .html/htm extension
webxref -avoid '.*Archive.*' file.html
	Checks file.html but avoids files with names containing
	'Archive'
webxref -avoid '.*Archive.*|.*Distribution.*' file.html
	Same as above, but also files with names containing
webxref -islocal www.sara.nl
	Treat things like '<a href=http://www.sara.nl/rick' as a 
	local reference, as if it would have been '<a href=/rick'
webxref -root /u/webserver/ index.html
	Links to things starting with a slash, like /cgi-bin, /icons etc
	are now looked for in /u/webserver/, the directory your webserver
	knows as the 'root'
webxref -fluff index.html
	Checks index.html and reports files in the directories 
	encountered that were not referenced by index.html or any 
	file linked to from there.
webxref -silent index.html
	Just report problems at the end of the run. This may take
	a while with a big website.
webxref -silent -errors index.html
	Prints only problems while scanning, and the final report.
webxref -verbose index.html
	Prints a message for every file under test.
webxref -long -silent index.html
	Does not print anything while scanning, but generates a
	long report, i.e. lists every file encountered.
webxref -before -date 970823 -time 1200 index.html
	Reports files last modified before August 23rd 1997
webxref -find 'me.gif' index.html
	Reports a list of pages containing the text 'me.gif'
webxref -findexpr '<img .*\.gif' index.html
	Reports files containing links to gif files.
webxref -replace 'me' -by 'you' -one index.html
	Replace 'me' by 'you' in index.html one-ly.
  
E_O_T

exit;
}

#---------------------------------------------

sub GetCWD {

# -- GetCWD
# Get the current working directory, make sure it ends with a slash
# No parameters
# Returns cwd

local($dir);

$dir = `pwd`;
$dir =~ s/\n//g;
if ($dir !~ m#/$#) {
  $dir = "$dir/";
}

return $dir;

}  # GetCWD



sub SplitFile {

# -- SplitFile($filename)
# Split filename into base directory, filename, anchor and depth
# Returns (dir,file,anchor,depth)

local($file)= @_;

local(@parts,$filename,$dir,$anchor,$depth);

@parts = split(/\//,$file);

# The recursion "level" of webxref is linked to the depth
# we're currently operating at on the file system
$depth = scalar(@parts);

# If ends with a slash it's a directory ref
# If there's no slash it can still be a directory ref, but
# we'll find that out later
if ($file eq "/") {
  return ($file,'','',0);
}
elsif ($file =~ m#/$#) {
  return ($file,'','',$depth-1);
}

$filename = pop(@parts);
$depth = $depth-2;

($filename,$anchor) = split(/#/,$filename);
if ($anchor) { $anchor = '#' . $anchor; }

$dir = join('/',@parts);
if ($dir ne "") {
  if ($dir !~ /\/$/) { $dir .= '/'; }
}
while ($dir =~ s#[^/]+/\.\./##) { ; } # collapse ../ constructions
# Add slash if not there already
if ($dir ne "") {
  if ($dir !~ /\/$/) { $dir .= '/'; }
}

return ($dir,$filename,$anchor,$depth);

}  # SplitFile




sub SplitURL {

# -- SplitURL(url)
# Split the parameter given as if it's an url.
# Method: http, ftp, telnet, news, ...
# In case of a file $method is "file:"
# Returns (method,file)

# http://www.sara.nl:80/rick
# http://www.sara.nl:80/cgi-bin/wibble
# http://www.sara.nl:80/cgi-bin/wibble?param
# http://www.sara.nl:80/cgi-bin/wibble?param&param2

local($URL) = @_;
local($method,$rest);

$URL =~ s/^\s+//;  # Remove leading whitespace

# http://  gopher://  news://  etc
if ($URL =~ m#^(\w+)://(.*)#) {
  $method = lc($1);
  $rest = $2;
}
#  //something is http too
elsif ($URL =~ m#^//(.*)#) {
  $method = 'http';
  $rest = $2;
}
# mailto:  
elsif ($URL =~ m#^(\w+):(.+)#) {
  $method = lc($1);
  $rest = $2;
}
elsif ($URL =~ m#^/cgi-bin/(.+)#i) {
  $method = 'CGI';
  $rest = $1;
}
else {
  $method = 'file'; # Can be dir too, will find out later
  $rest = $URL;
}
 
return ($method,$file);

}  # SplitURL




sub AddedToList {

# -- AddedToList(list,url,referer)
# Add resource location and referer to the hash belonging to the method
# Often AddedToList is just called to add a referer of the file.
# Returns 0 if already listed
# Returns 1 if newly added

local(*list,$url,$referer) = @_;    
#print "\nADD: $url,$referer\n";

if ($list{$url}) {
  $list{$url} .= " $referer" if ($Xref);
  return 0;
}

# New
$list{$url} = "$referer";
return 1;

}  # AddedToList




sub PrintDot {

# -- PrintDot
# Prints a dot with autoflush on.
# (Actually: a '+' for an ok file, a '-' for files
# with problems)
# Called for every file in certain modes.

local($Dot) = @_;

local($Save) = $|;  # Save autoflush

$| = 1;
print STDERR $Dot;
$| = $Save;

$DotCount++;
if ($DotCount >= $MaxDots) {
  print "\n";
  $DotCount = 0;
}

}  # PrintDot




sub GetReferences {

# -- GetReferences($link,$referer)
# Get all references from the link(file) and check those recursively.
# Link can be a file, or a ref in the form http:// etc

# Note: the files referenced are kept as full filesystem paths
# to those files. This is done to ensure that references to 
# the file /u/user/file.html is the same as a reference "../file.html"

local($link,$referer) = @_;
#print "\nGetRefs:\nLink: $link\nReferer: $referer\n";


# These vars are pushed onto the stack each recursive call
local($dir,$file,$anchor);
local($Old_Dir);
local($filename);

($method,$rest) = SplitURL($link);
#print "GetReferences link: $link  method: $method\n";

if    ($method eq 'http')   { ; }
elsif ($method eq 'ftp')    { return unless &AddedToList(*FTPList, $link, $referer);   }
elsif ($method eq 'telnet') { return unless &AddedToList(*TelnetList, $link, $referer);  }
elsif ($method eq 'gopher') { return unless &AddedToList(*GopherList, $link, $referer);  }
elsif ($method eq 'mailto') { return unless &AddedToList(*MailList, $link, $referer);    }
elsif ($method eq 'news')   { return unless &AddedToList(*NewsList, $link, $referer);     }
elsif ($method eq 'CGI')    { ; }
elsif ($method eq 'file')   { ; }
else  { print "Unknown method \"$method\": $link\n"; }


#
# Apply the -islocal thingie: try to map a http reference to
# a local file on the machine specified with -islocal.
#
# If http check if it's a local reference after all (-islocal parameter!)
if ($method eq 'http') {
  if (! $IsLocal) {
      #print "HTTP: $link\n";
    return unless &AddedToList(*HTTPList, $link, $referer);
  }
  else {
    if ($link =~ m#^http://$IsLocal(/?.*)#i) {  # We have a match!
      $method = 'file';
      $link = $1;

      # Could be a cgi call now...
      ($method,$rest) = SplitURL($link);
    }
  }
}


# If CGI just try to check if the script is present
if ($method eq 'CGI') {
  # Delete parameters of cgi script
  $link =~ s/\?.*//;
  if (-e "$ServerRoot$link") { 
    return unless &AddedToList(*CGIList, $link, $referer); 
  }
  else {
    return unless &AddedToList(*LostCGIList, $link, $referer);
  }

  return;
}  # cgi



return if ($method ne 'file');



# Apparently what we have ended up with at this point
# is a reference to a file of some sort. This "file" 
# can also still be a directory. It can also be a name 
# anchor in the file.
($dir,$file,$anchor,$depth) = &SplitFile($link);
#print "split: $dir $file\n";


# Apply the regexp to avoid certain files
if ($Avoid) {
  #print "Avoid: $Avoid  File: $file  Dir: ",&PrintFile($dir),"\n";
  if (&PrintFile($file) =~ m/$Avoid/o) {
    print "  Avoided file ",&PrintFile($file),"\n" if (!$Silent) || ($Errors);
    return;
  }
  if (&PrintFile($dir) =~ m/$Avoid/o) {
    print "  Avoided directory ",&PrintFile($dir),"\n" if (!$Silent) || ($Errors);
    return;
  }
}


$cwd = &GetCWD;
if ($dir eq "") {
  $dir = $cwd;
}

# Move to the specified directory to obtain the expanded 
# file path
if (-d $dir) {
  $Old_Dir = $cwd;  
  chdir($dir);
  $dir = &GetCWD;
  $filename = $dir . $file;

  # See which files are in this directory if we are checking 
  # for unreferenced files, if not done before
  &GetFluffFiles($dir) if ($Fluff && (! $FluffScannedDirList{$dir}));
}
else {
  &PrintDot("-") if ($Dots);
  print "\n" if ($Errors && $Dots);
  print "  ", &PrintFile($dir.$file)," cannot be found\n" 
    if (!$Silent) || ($Errors);
  print "     Referenced by: ",&PrintFile($referer),"\n" 
    if (!$Silent) || ($Errors);
  &AddedToList(*LostFileList,$dir.$file,$referer);
  return;
}




#
# Add to the list of already tested files if not inspected before
#

# If the "file" is a directory try Welcome/welcome/index.html etc.
if (-d $filename) { 
  return unless &AddedToList(*DirList,$filename,$referer);

  &DoDirectory; 
}


# Not found?
if (! -f $filename) {

  # If the file lacks an extension try the default
  # extensions html, htm etc.
  $SecondChance = &TryExtensions($filename);
  if (! $SecondChance) {
    &PrintDot("-") if ($Dots);
    print "\n" if ($Errors && $Dots);
    print "  ", &PrintFile($filename)," cannot be found\n"
      if (!$Silent) || ($Errors);
    print "     Referenced by: ",&PrintFile($referer),"\n"
      if (!$Silent) || ($Errors);
  
    # Add to list of lost files
    &AddedToList(*LostFileList,$filename,$referer);
    return;
  }
  else {  # Apparently adding an extension did the trick
    $filename = $SecondChance;
  }
}



# World readable? (do not use -r, doesn't work for root)
($dev,$ino,$mode,$nlink,
 $uid,$gid,
 $rdev,$size,
 $atime,$mtime,$ctime,
 $blksize,$blocks) = stat($filename);
$readmode = ($mode & 4);
if ($readmode == 0) {
  # Not world readable, add to list
  &AddedToList(*UnreadableList,$filename,$referer);
}

# Check if we need to list this file
&CheckTimeStamp($filename,$mtime) if ($Before || $After);

# Binary file? (pictures,...)
if (-B $filename) {
  &AddedToList(*ImageFileList,$filename,$referer);
  return;
}


if ($HTML_only) {
  # Filename *must* have extension .html or .htm, else we don't inspect it.
  if ($filename !~ /.*\.htm[l]*$/i) {return;}
}

# Apply the regexp to avoid certain files
if ($Avoid && ($filename =~ m/$Avoid/)) { 
  #print "** The above file is avoided.\n" if (!$Silent) || ($Errors);
  return;
}


# else it's a text (html)file
# return if we already inspected it
return unless &AddedToList(*FileList,$filename,$referer);


# We now have a (html) file to check for further links, name anchors etc.

# But not if we're just checking the One file
if ($One) {
  #print "** ref eq INFILE\n" if ($filename eq $InFile);
  #print "** ref eq websrfe\n" if ($filename eq $WebxrefReferer);
  #print "RETURNED\n" if (($filename ne $InFile) && ($filename ne $WebxrefReferer));
  return if (($filename ne $InFile) && ($filename ne $WebxrefReferer));
}

print "Checking: ",&PrintFile($filename),"\n" if (!$Silent);
#&PrintDot('+') if (($Dots) && (!$Silent));
&PrintDot('+') if ($Dots);

local(@newlist) = GetLinks($filename);
print "done getlinks from ",&PrintFile($filename),":\n", join("\n",@newlist),"\n";

# Now see if the anchor we were after was found
if ($anchor) { 
  if (!defined($AnchorList{"$filename$anchor"})) {
    return unless &AddedToList(*LostAnchorList,"$filename$anchor",$referer);
    print "   Anchor ",&PrintFile($anchor)," is NOT (1) present in file ",
          &PrintFile($filename),"\n" if (!$Silent) || ($Errors);
    print "\n" if ($Errors && $Dots);
    &PrintDot('-') if ($Dots);
  }
  else {
    # Anchor found, add referer
    AddedToList(*AnchorList,"$filename$anchor",$referer);
  }
  return;
}

# Walk the list and check everything is there
foreach $file (@newlist) {
  print "foreach: $file\n";
  ($method,$rest) = SplitURL($file);
  if ($method eq 'file') { 
    if ($file =~ m#^/#) {  # root reference
      $Notlocal_file = "$ServerRoot$file";
    }
    else {  # Reference relative to directory
      $Notlocal_file = $dir . $file; 
    }
  }
  else {  # Not file but http, news etc
    $Notlocal_file = $file;
  }

  $Notlocal_ref_filename = $filename;

  # Don't go deeper than he wanted (ooh!)
  ($dummy,$dummy,$dummy,$depth) = SplitFile($Notlocal_file);
  #print "Depth of $Notlocal_file is $depth, Max Depth is $MaxDepth\n";
  #print "we skip\n" if ($depth > $MaxDepth);
  next if ($depth > $MaxDepth);

  # Prevent from recursing if there's an easy check...
  next if (&AlreadyChecked($Notlocal_file,$Notlocal_ref_filename));


  print "foreach: GetReferences($Notlocal_file, $Notlocal_ref_filename)\n";
  &GetReferences($Notlocal_file, $Notlocal_ref_filename);
} # foreach

chdir($Old_Dir) if ($dir ne $Old_Dir);

} #sub GetReferences




sub GetLinks {

# -- GetLinks($file)
# Read the html file and extract all links
# returns @Newlist

local($filename) = @_;

local(@Tags,$tag,%Newlist,@Newlist,%LocalAnchorsFound,%LocalAnchorsWanted);

unless (open(HTML, $filename)) {
  print "Could not open file $filename\n";
  return; 
}

# Read the file into a big string and remove crud in between tags.
print "opening $filename\n";
open(HTML, $filename) || die "Could not open $filename\n";
@Tags = <HTML>;
close(HTML);
#print "File: $filename\n";

$_ = join('',@Tags);

# Note down files matching the find (expression)
&DoFind($filename,$_) if (defined($FindExpr));

s/\n/ /g;

# Remove html comments
s/<!--.*?-->//g;

@Tags = split(/</);

foreach (@Tags) {
  s/>.*//;
  #print "tag: $_\n";

  # <a href/name
  if (/^a\s+/i) {
#print "-anchor: $_\n";
    # -- a href
    if (m#href\s*=\s*"?([^"\s]*)"?#i) {
      $Link = $1;
      # print "  href: -$Link-\n";
  
      # Link to name anchor within current document? (<a href=#anchor>)
      if ($Link =~ m/^#/) {
        #print "  -$filename$Link- wanted\n";

        # Special case for Intermediair: do not generate error for "href=file.html#"
        # (empty name anchor)
        #print "  -$Link- wanted\n";
        if ($Intermediair) {
          next if ($Link eq "#");
        }

        $LocalAnchorsWanted{"$filename$Link"} = 1;
      }
      # Link to another document?  a href=file.html#anchor
      elsif ($Link =~ m/#/) {
        $Link =~ m/(.+)#(.+)/;
	#print "LINK: $Link\n";
	#print "$1 $file - equal?\n";
        if ($1 eq $file) {  # Current file after all
          $LocalAnchorsWanted{("$filename" . '#' . "$2")} = 1;
        } 
        else {
          $Newlist{$Link} = 1;
        }
      }
      else {  
	# print "Just a file ref\n";
        $Newlist{$Link} = 1;
      }
    }
    elsif (m#name\s*=\s*"?([^"\s]*)"?#i) {
      # -- a name=...
      $Link = $1;
      #print "  name: $Link\n";
#print "  -$filename$Link- found\n";
      $LocalAnchorsFound{"$filename#$Link"} = 1;
    }
  }


  # frame src=
  elsif (/^frame\s+/i) {
    if (m#src\s*=\s*"?([^"\s]*)"?#i) {
      $Link = $1;
      #print "  frame: $Link\n";

      $Newlist{$Link} = 1;
    }
    else { print "  Frame parse error in ",&PrintFile($filename),":\n  $_\n"; }
  }



  # area href=
  elsif (/^area\s+/i) {
    if (m#href\s*=\s*"?([^"\s]*)"?#i) {
      $Link = $1;
      #print "  area: $Link\n";

      $Newlist{$Link} = 1;
    }
    else { print "  Area parse error in ",&PrintFile($filename),":\n  $_\n"; }
  }

 
  # <img src=...
  # NB: <img and src= must be on same line
  elsif (/^img/i) {
    if (m#src\s*=\s*"?([^"\s]*)"?#i) {
      $Link = $1;
      #print "  img: $Link\n";
      # Add file to the list
      $Newlist{$Link} = 1;
    }
    else { print "  Image parse error in ",&PrintFile($filename),":\n  $_\n"; }
  }


  # <form action=...
  elsif (/^form/i) {
    #print "form: $_\n";
    if (m#action\s*=\s*"?([^"\s]*)"?#i) {
      $Link = $1;
      #print "  form: $Link\n";
      # Add file to the list
      $Newlist{$Link} = 1;
    }
    else { print "  Form parse error in ",&PrintFile($filename),":\n  $_\n"; }
  }

}  # foreach

#print "LocalAnchorsFound: \n",join("\n",keys(%LocalAnchorsFound)),"\n";
#print "\nLocalAnchorsWanted: \n",join("\n",keys(%LocalAnchorsWanted)),"\n";


# Add the local anchors found to the global list
foreach $Anchor (keys(%LocalAnchorsFound)) {
  &AddedToList(*AnchorList,$Anchor,$filename);
}

# Check if the locally referenced anchors are there
# and remove them from Newlist if they are

foreach $Anchor (keys(%LocalAnchorsWanted)) {
  if (!defined($LocalAnchorsFound{$Anchor})) {
    &AddedToList(*LostAnchorList,$Anchor,$filename);
    print "\n" if ($Errors && $Dots);
    &PrintDot('-') if ($Dots);
    print "  Anchor ",&PrintFile($Anchor)," is NOT (2) present in file ",
          &PrintFile($filename),"\n" if (!$Silent) || ($Errors);
  }
  else {
    $Newlist{$Anchor} = 0; # Remove from list
  }
}
foreach (keys(%Newlist)) {
  if ($Newlist{$_}) { push(@Newlist, $_); }
}
#print "\nnewlist2: \n",join("\n",@Newlist),"\n";

return @Newlist;

}  # GetLinks




sub AlreadyChecked {

# -- AlreadyChecked($file,$referer) 
# Return 1 if $file already referenced in one of the lists

local($file,$referer) = @_;

if ($FileList{$file}) {
  &AddedToList(*FileList,$file,$referer) if $Xref;
  return 1;
}
elsif ($LostFileList{$file}) {
  &AddedToList(*LostFileList,$file,$referer) if $Xref;
  return 1;
}
elsif ($UnreadableList{$file}) {
  &AddedToList(*UnreadableList,$file,$referer) if $Xref;
  return 1;
}
elsif ($ImageFileList{$file}) {
  &AddedToList(*ImageFileList,$file,$referer) if $Xref;
  return 1;
}
#elsif ($DirList{$file}) {
#  &AddedToList(*DirList,$file,$referer) if $Xref;
#  return 1;
#}
#elsif ($DirNotFoundList{$file}) {
#  &AddedToList(*DirNotFoundList,$file,$referer) if $Xref;
#  return 1;
#}
#elsif ($HTTPList{$file}) {
#  &AddedToList(*HTTPList,$file,$referer) if $Xref;
#  return 1;
#}
#elsif ($CGIList{$file}) {
#  &AddedToList(*CGIList,$file,$referer) if $Xref;
#  return 1;
#}
#elsif ($LostCGIList{$file}) {
#  &AddedToList(*LostCGIList,$file,$referer) if $Xref;
#  return 1;
#}
#elsif ($AnchorList{$file}) {
#  &AddedToList(*AnchorList,$file,$referer) if $Xref;
#  return 1;
#}
#elsif ($LostAnchorList{$file}) {
#  &AddedToList(*LostAnchorList,$file,$referer) if $Xref;
#  return 1;
#}

return 0;

}  # AlreadyChecked





sub TryExtensions {

# -- TryExtensions(file)
# Apparently $file could not be located. Maybe the extension
# was missing, in that case try html, htm, shtml etc.
# Returns the filename plus extension if that conbination
# does exist.

local($file) = @_;
local($d,$f,$extension);

($d,$f) = &SplitFile($file);

($f,$extension) = split(/\./, $f);
if (! $extension) {  # No extension, try some
  foreach $extension (@Extensions) {
    if (-f "$file.$extension") {
      return "$file.$extension";
    }
  }
}

return "";  # Not found or file does have extension

}  # TryExtensions





sub DoDirectory {

#print "xx $filename is a directory, trying Welcome/welcome/index.html.\n";

$found = 0;
foreach $default_file (@DefaultFiles) {
  #print "Trying $default_file\n";
  if (-f ($filename . '/' . $default_file)) {
    $dirname=$filename;
    $file= $default_file;
    $found = 1;
    last;
  }
}

if (! $found) {
  print "\n" if ($Errors && $Dots);
  &PrintDot("-") if ($Dots);
  print "  No Welcome/welcome/index.html can be found in ",
        &PrintFile($filename),"\n" 
     if (!$Silent) || ($Errors);
  print "     Referenced by: ",&PrintFile($referer),"\n"
     if (!$Silent) || ($Errors);
  $filename = "$filename/index or welcome file";

  # Add to list of lost files
  if (!defined($LostFileList{$filename})) {
    $LostFileList{$filename} = $referer; 
    }
  else {
    $LostFileList{$filename} = "$LostFileList{$filename} $referer";
  }
  return;
}

# Move to the specified directory
chdir($dirname);
$dir=&GetCWD;
$filename = $dir . $file;

# See which files are in this directory if we are checking 
# for unreferenced files, if not done before
&GetFluffFiles($dir) if ($Fluff && (! $FluffScannedDirList{$dir}));

}  # DoDirectory




sub GetFluffFiles {

# -- GetFluffFiles
# If we're checking for never referenced files a list
# is maintained of all files in all directories we have
# encountered. This list is checked against all files
# referenced. Any files left over are considered fluff.
# GetFluffFiles reads the current working directory

local($dir) = @_;
$dir .= '/' if ($dir !~ m#/$#); # Add / if not there

local(@Files);

# Read dir contents
#print "Fluff-dir: $dir\n";
opendir(DIR,"$dir");
  @Everything = readdir(DIR);
closedir(DIR);

# Separate in list of files and list of dirs
@Files = grep !/^\./, @Everything;  # No .-files
@Directories = @Files;
@Files = grep -f, @Files;  
@Directories = grep -d, @Directories; 

# Add them to the fluff-list
foreach (@Files) {
  #print "f: $dir$_\n";
  $FluffFileList{"$dir$_"} = 1;
}
foreach (@Directories) {
  $_ .= '/' if (! m#/$#); # Add / if not there
  #print "d: $dir$_\n";
  $FluffDirectoryList{"$dir$_"} = 1;
}

# Mark this directory scanned
#print "fsdl: $dir\n";
$FluffScannedDirList{$dir} = 1;

}  # GetFluffFiles



sub PickFluff {

# Determine the files that were never referenced but
# that did reside in the directories we have scanned.
# Actually, files in the list are unmarked if we have
# encountered them while checking.


# ----- Files
foreach (keys(%FileList)) {
  $FluffFileList{$_} = 0;  # unmark
}
foreach (keys(%LostFileList)) {
  $FluffFileList{$_} = 0;  # unmark
}
foreach (keys(%ImageFileList)) {
  $FluffFileList{$_} = 0;  # unmark
}

# The actual fluff files
foreach (keys(%FluffFileList)) {
  push(@FluffFiles,$_) if ($FluffFileList{$_});
}
undef %FluffFileList;
@FluffFiles = sort(@FluffFiles);


# ----- Directories
foreach (keys(%DirList)) {
  $FluffDirectoryList{$_} = 0;  # unmark
}
foreach (keys(%LostDirList)) {
  $FluffDirectoryList{$_} = 0;  # unmark
}
foreach (keys(%FluffScannedDirList)) {
  $FluffDirectoryList{$_} = 0;  # unmark
}

# The actual fluff directories
foreach (keys(%FluffDirectoryList)) {
  push(@FluffDirectories,$_) if ($FluffDirectoryList{$_});
}
undef %FluffDirectoryList;
undef %FluffScannedDirList;

}  # PickFluff


#---------------------------------------------



sub DoFind {

# -- DoFind($filename,$html-file-as-string)
# Match the text of the html-doc to the find and findexpr
# parameters.

local($filename,$content) = @_;
#print "DOFIND: f=$filename\n\ncont:\n----$content\n----\nfind: $FindExpr\n";

if (defined($FindExpr)) {
  if ($content =~ /$FindExpr/moi) {
    $FindFiles{$filename} = 1;
    #if ($FindFiles{$filename}) {
      #print "YES we have a match\n" 
    #}
    #else {
      #print "NO match\n";
    #}

    # EDIT!
    if (defined($Replacement)) {
      # Just in case we've been here before...
      return if (defined($EditedFile{$filename}));

      $oldcontent = $content;
      $content =~ s/$FindExpr/$Replacement/gmoi;
      if (&WriteFile($filename,$oldcontent,$content)) {
        $EditedOkList{$filename} = 1;
      }
      else {
        $EditFailedList{$filename} = 1;
      }
    }
  }
}

}  # DoFind




sub WriteFile {

# -- WriteFile($filename,$oldcontent,$content)
# Write $content to $filename, while making a backup

local($filename,$oldcontent,$content) = @_;
local($backupfile) = $filename . '.' . $$;

# First make backup: $filename.$$ (pid) --> a.html.12345
open(BAKFILE, ">$backupfile")  || return 0;
print BAKFILE $oldcontent;
close(BAKFILE);

# Write new edited version
open(NEWFILE,">$filename") || return 0;
print NEWFILE $content;
close(NEWFILE);

return 1;

}  # WriteFile



sub PrintFindHeader {

local($header) = 'Files matching ';

if (defined($OrgFindExpr)) { $header .= "\"$OrgFindExpr\""; }

return $header;

}  # PrintFindHeader



sub PrintEditHeader {

# -- PrintEditHeader($ok)
# If $ok returns succesful, else failed header

local($ok) = @_;

local($header) = 'Files where replacing ';

if (defined($OrgFindExpr)) { $header .= "\"$OrgFindExpr\""; }

if (defined($Replacement)) { 
  $header .= "  by \"$Replacement\""; 
}
 
if ($ok) {
  $header .= ' was succesful:';
}
else {
  $header .= ' FAILED:';
}

return $header;

}  # PrintEditHeader
  


#---------------------------------------------

# Time/date stuff


sub CheckTimeStamp {

# -- CheckTimeStamp($filename,$mtime)

local($filename,$mtime) = @_;

if ($Before) {
  $TimeList{$filename} = 1 if ($mtime <= $TimeStamp);
}
else {
  $TimeList{$filename} = 1 if ($mtime >= $TimeStamp);
}

}  # CheckTimeStamp



sub PrintTimeStamp {

# -- PrintTimeStamp($mtime)
# Returns date/time string:  yymmdd hh:mm:ss

local($mtime) = @_;

local($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) =
  localtime($mtime);

$hour = '00' unless $hour;
$min =  '00' unless $min;
$sec = '00'  unless $sec;

$mon = "0$mon" if ($mon =~ /^\d$/);
$mday = "0$mday" if ($mday =~ /^\d$/);

return "$year/$mon/$mday at $hour:$min:$sec";

}  # PrintTimeStamp




sub ConvertTimeStamp {

# -- ConvertTimeStamp($date,$Time)
# Convert $Date and $Time given as parameters to tm struct
# Date: yymm(dd)   Time: hhmm(ss)

# Perl library module
use Time::Local;

local($Date,$Time) = @_;

local($year,$month,$day,$hour,$min,$sec);

$Date =~ m/(\d\d)(\d\d)(\d\d)?/;
$year = $1;
$month = $2-1;
$day = 1;
$day = $3 if defined($3);

$hour = '00'; $min = '00'; $sec = '00';
$Time =~ m/(\d\d)(\d\d)(\d\d)?/;
$hour = $1;
$min = $2;
$sec = 0;
$sec = $3 if defined($3);

#print "\n\nhour $hour\n";
#print "min $min\n";
#print "sec $sec\n";
#print "day $day\n";
#print "mon $month\n";
#print "year $year\n";
#print "ts:", timelocal($sec,$min,$hour,$day,$month,$year);

# From Perl library module
return timelocal($sec,$min,$hour,$day,$month,$year);

}  # ConvertTimeStamp




#---------------------------------------------

sub Check_External_URLs {


local($header, %list) = @_;
local($URL);

if (!$Silent) { print "\n\n----------------\n$header\n"; } 
@TheList=keys(%list);
@SortedList = sort @TheList;

foreach $URL (@SortedList) {
    print STDERR "\n$URL: " ; #if (!$Silent);

  if (defined($HTTPStatusList{$URL})) {
    # Already checked on this one
    next;
  }
  else {
    sleep($HTTPDelay);
    $rcode = &Check_URL($URL);
  }

  if (defined($OkStatusMsgs{$rcode})) {
    # URL is ok, server responds and all.
    print STDERR "  OK ($rcode)\n"  if (!$Silent);
    &PrintDot('+') if ($Dots);
    $HTTP_OK_List{$URL} = $HTTPList{$URL};  # The references
  }
  else {
    # Something is wrong.
      print STDERR "$URL: BAD ($rcode)\n" if (!$Silent);
    if (defined($FailStatusMsgs{$rcode})) {
      &PrintDot('-') if ($Dots);
      print "\n" if ($Errors && $Dots);
      print "    Failed: $FailStatusMsgs{$rcode}\n" 
        if (!$Silent) || ($Errors);
    }
    else {
      &PrintDot('-') if ($Dots);
      print "\n" if ($Errors && $Dots);
      print "  Failed with code $rcode\n"
        if (!$Silent) || ($Errors);
    }
    $HTTP_Fail_List{$URL} = $rcode;
  }
}
 
&PrintList(%HTTP_OK_List,"External URLs checked ok:");
&Print_Failed_URL_List("Failed External URLs:", %HTTP_Fail_List);

}




sub Check_URL {

# http://host:port/path

local($URL) = @_;

if ($URL !~ m#^http://.*#i) { 
  print "wrong format http: $URL\n";
  return;
}
else {

  # Get the host and port
  #if ($URL =~ m#^http://([\w-\.]+):?(\d*)($|/(.*))#i) {
  if ($URL =~ m#^http://([^:/]+):?(\d*)($|/(.*))#i) {
    $host = $1;
    $port = $2;
    $path = $3;
    #print "URL:$URL host:$host port:$port path:$path\n";
  }
  else {
    print "Unrecognized URL: $URL\n";
    return;
  }
  if ($path eq "") { $path = '/'; }
  if ($port eq "") { $port = 80; }

  # Delete name anchor. (check if the anchor is present in the doc?)
  $path =~ s/#.*//;
  # Delete parameters
  #$path =~ s/\?.*//;

  #print "-->\n URL: $URL\n host: $host\n port: $port\n path: $path\n";
}


# The following is largely taken from the Camel book, chapter 6

$AF_INET = 2;
$SOCK_STREAM = 1;

$sockaddr = 'S n a4 x8';  # (Bless you)

chop($hostname = `hostname`);

($name,$aliases,$proto) = getprotobyname('tcp');
($name,$aliases,$port) = getservbyname($port,'tcp') unless $port =~ /^\d+$/;
($name,$aliases,$type,$len,$thisaddr) = gethostbyname($hostname);
if (!(($name,$aliases,$type,$len,$thataddr) = gethostbyname($host))) {
  return -1;
}

$this = pack($sockaddr, $AF_INET, 0, $thisaddr);
$that = pack($sockaddr, $AF_INET, $port, $thataddr);

# Make the socket filehandle.
# ** Temporary fix, this is NOT The way to do it. 15-APR-96
# But we'll still use it anyway, cannot rely on Perl to be 
# installed correctly everywhere. 
if (!(socket(S, $AF_INET, $SOCK_STREAM, $proto))) {
  $SOCK_STREAM = 2;
  if (!(socket(S, $AF_INET, $SOCK_STREAM, $proto))) { return -2; }
}

# Give the socket an address
if (!(bind(S, $this))) {
  return -3;
}

if (!(connect(S,$that))) {
  return -4;
}

select(S); $| = 1; select(STDOUT);

print S "HEAD $path HTTP/1.0\n\n";

$response = <S>;
($protocol, $status) = split(/ /, $response);
while (<S>) {
  #print STDERR;
}
close(S);

#print STDERR "Status: $status\n";

return $status;

}







#---------------------------------------------

sub SortUnique {

# Sort the list and remove doubles

local(%list);

# Remove doubles
foreach (@_) {
  $list{$_} = 1;
}

return (sort(keys(%list)));

}  # SortUnique



sub PrintFile {

# Returns filename without the root path

local($file) = @_;

$file =~ s/^$ServerRootExpr//o if (!$FullPath); # delete root from path
$file =~ s/^$SiteRootExpr//o if (!$FullPath); # delete root from path

# datpete: hack: because we place output HTML in subdirectory 'admin'
# we need to add '../':
if (("$file" ne "") && !$FullPath && (substr($file,0,4) ne "http") && (substr($file,0,6) ne "mailto")){
    $file = "../" . $file;
}

return $file;

}  #




sub Print_Failed_URL_List {

local($header, %list) = @_;
local(@SortedList);
local(@SortedReferList);
local($URL,$lostURL);

# Don't list empty lists
if (! %list) {return};

print "<h2>\n" if ($HTMLReport);

#print "\n\n", '-' x length($header);
print "\n$header\n";
print '-' x length($header), "\n" if (!$HTMLReport);;

print "</h2>\n<pre>\n" if ($HTMLReport);

@SortedList = sort(keys(%list));
foreach $URL (@SortedList) {
  if ($HTMLReport) {
    print "<a href=",&PrintFile($_),"> ",&PrintFile($_),"</a>\n";
  }
  else {
    print &PrintFile($_),"\n";
  }

  if ($HTMLReport) {
    print "<a href=$URL> $URL</a>\n";
  }
  else {
    print "$URL \n";
  }
  $rcode = $HTTP_Fail_List{$URL};
  print "  Status: $rcode ($FailStatusMsgs{$rcode})\n";

  if ($Xref) {
    @SortedReferList = split(/ /,$HTTPList{$URL});
    @SortedReferList = &SortUnique(@SortedReferList);
    print "     Referenced by:\n";
    foreach $lostURL (@SortedReferList) {
      next if ("$lostURL" eq "");
      if ($HTMLReport) {
        print "       <a href=",&PrintFile($lostURL),">",&PrintFile($lostURL),"</a>\n";
      }
      else {
        print "       ",&PrintFile($lostURL),"\n";
      }
    }
  }  # $Xref
}

print "</pre><!--Print_Failed_URL_List-->\n" if ($HTMLReport);

}  # sub Print_Failed_URL_List




sub PrintList {

local(*list, $header, $NoXref) = @_;

local($file,$i);
local(@SortedFileList);
local(@SortedReferList);

# Don't list empty lists
return if (! %list);

@SortedFileList = sort(keys(%list));

# Append number to header
$header = "$header ".($#SortedFileList+1);

print "<h2>" if ($HTMLReport);
print "\n$header\n";
print "</h2>\n" if ($HTMLReport);
print '-' x length($header), "\n\n" if (!$HTMLReport);; 
print "<pre>\n";
foreach (@SortedFileList) {
  if ($HTMLReport) {
    print "<a href=",&PrintFile($_),"> ",&PrintFile($_),"</a>\n";
  }
  else {
    print &PrintFile($_),"\n";
  }

  if ($Xref || $OneXref) {
    @SortedReferList = split(/ /,$list{$_});
    @SortedReferList = &SortUnique(@SortedReferList);
    print "   Referenced by:\n";
    foreach $i (@SortedReferList) {
      if ($HTMLReport) { print "    <a href=",&PrintFile($i),"> ",&PrintFile($i),"</a>\n";}
      else { print "    ",&PrintFile($i),"\n"; }

      last if ($OneXref);
    }
    #print "\n";
  }  # $Xref
}

print "</pre><!--PrintList-->\n" if ($HTMLReport);

# CAUTION! TRY TO RETRIEVE MEMORY 13.3.97
undef %list;

}  # sub PrintList




sub PrintFluff {

# The Fluff list is an array, not a hash

local(*list, $header) = @_;

# Don't list empty lists
return if (! @list);


# Append number to header
$header = "$header ".($#list+1);

#print "\n\n", '-' x length($header);
print "\n$header\n";
print '-' x length($header), "\n\n";

foreach (@list) {
  print &PrintFile($_)," \n";
}

}  # PrintFluff




sub PrintLists {

# Print lists

# List all files found
&PrintList(*FileList,"Web documents found:",0) if ($LongReport);

# List of directories referenced
&PrintList(*DirList,"Directories:",0) if ($LongReport);

# List of images referenced
&PrintList(*ImageFileList,"Images:",0) if ($LongReport);

# List of mailto's
&PrintList(*MailList,"Mailto:",0) if ($LongReport);

# List of ftp's
&PrintList(*FTPList,"ftp:",0) if ($LongReport);

# List of telnets
&PrintList(*TelnetList,"telnet:",0) if ($LongReport);

# List of gophers
&PrintList(*GopherList,"gopher:",0) if ($LongReport);

# List of news
&PrintList(*NewsList,"News:",0) if ($LongReport);

# List of http's
&PrintList(*HTTPList,"External URLs:",0) if ($LongReport);

# List of file:'s
&PrintList(*ExtFileList,"External file:",0) if ($LongReport);

# List of cgi-bin scripts/forms
&PrintList(*CGIList,"cgi-bin scripts/forms:",0) if ($LongReport);

# List of name anchors
&PrintList(*AnchorList,"Name anchors found:",0) if ($LongReport);

# ---- PROBLEM SECTION -----

# List of files that can't be found
&PrintList(*LostFileList,"Files not found:",0);

# List of cgi-bin scripts/forms not found
&PrintList(*LostCGIList,"cgi-bin scripts/forms not found:",0);

# List of files that are not world readable
# Override Xref, as reference list for non-world-readable files is not kept
&PrintList(*UnreadableList,"Files not world readable:",1);

# List of directories that can't be found
&PrintList(*DirNotFoundList,"Directories not found:",0);

# List of name anchors not found
&PrintList(*LostAnchorList,"Name anchors not found:",0);

# List of files found in the directories but not referenced
&PrintFluff(*FluffFiles,"Files never referenced:");

# List of directories found in the directories but not referenced
&PrintFluff(*FluffDirectories,"Directories never referenced:");

# List of files that matched $Find/$FindExpr
&PrintList(*FindFiles, &PrintFindHeader,1);

# List of files successfully edited
&PrintList(*EditedOkList, &PrintEditHeader(1), 1);

# List of files not edited
&PrintList(*EditFailedList, &PrintEditHeader(0), 1);

# List of files matching the date/time criterium
if ($Before) {
  &PrintList(*TimeList, "Files last modified before: ".
                         &PrintTimeStamp($TimeStamp).":", 1);
}
else {
  &PrintList(*TimeList, "Files last modified after: ".
                         &PrintTimeStamp($TimeStamp).":", 1);
}

print STDERR "\nDone.\n";

} #sub PrintLists




sub InitStatusMessages {

# HTTP status codes and messages

%OkStatusMsgs = (
  200, "OK 200",
  201, "CREATED 201",
  202, "Accepted 202",
  203, "Partial Information 203",
  204, "No Response 204",
);

%FailStatusMsgs = (
  -1,  "Could not lookup server",
  -2,  "Could not open socket",
  -3,  "Could not bind socket",
  -4,  "Could not connect",
  301, "Found, but moved",
  302, "Found, but data resides under different URL (add a /)",
  303, "Method",
  304, "Not Modified",
  400, "Bad request",
  401, "Unauthorized",
  402, "PaymentRequired",
  403, "Forbidden",
  404, "Not found",
  500, "Internal Error",
  501, "Not implemented",
  502, "Service temporarily overloaded",
  503, "Gateway timeout ",
  600, "Bad request",
  601, "Not implemented",
  602, "Connection failed (host not found?)",
  603, "Timed out",
);

}  # sub InitStatusMessages

# This is the last line of the webxref script really.
# If this line is missi
