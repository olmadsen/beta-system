// Generate table data with right justified last modification date of
// html file
var mod=document.lastModified;

document.writeln(" <TD align=center><FONT size=-1>&COPY; <A HREF=\"http://www.mjolner.com\">Mjølner Informatics</A></FONT></TD>");
document.writeln(" <TD align=right><FONT size=-1>[Last modified: " + mod + "]</FONT></TD>");
