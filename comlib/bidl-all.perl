#!perl

chdir("MsApplication");
system("bidl -F -q -l Excel8.Idl");
system("bidl -F -q VBEEXT1.Idl");
system("bidl -f -q MSCAL.IDL");
chdir("..");
system("bidl -F -q MsHtml.Idl");
system("bidl -F -q ExDisp.Idl");
