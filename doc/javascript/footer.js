function first_footer(title,scriptdir)
{
  document.write(  "<HR>\n"
                   + "<P></P>\n"
                   + "<TABLE COLS=3 BORDER=0 WIDTH=\"100%\">\n"
                   + "<TR>\n"
                   + "<TD WIDTH=\"50%\" ALIGN=\"left\">"
		   + "  <ADDRESS>" + title + "</ADDRESS>\n"
		   + "</TD>\n"
                   + "<TD WIDTH=\"50%\" ALIGN=\"right\">\n"
                   + "  <SCRIPT LANGUAGE=JavaScript TYPE=\"text/javascript\" SRC=\""
		   +    scriptdir + "lastmod.js\"></SCRIPT>\n"
		   + "</TD>\n"
                   + "</TABLE>\n"
		 );
  document.close();
}


function footer(title,scriptdir)
{
  document.write(  "<HR>\n"
                   + "<P></P>\n"
                   + "<TABLE COLS=3 BORDER=0 WIDTH=\"100%\">\n"
                   + "<TR>\n"
                   + "<TD WIDTH=\"40%\" ALIGN=\"left\">"
		   + "  <ADDRESS>" + title + "</ADDRESS>\n"
		   + "</TD>\n"
                   + "<TD WIDTH=\"20%\" ALIGN=\"center\">\n"
                   + "  <FONT SIZE=\"-1\">&COPY; \n"
		   + "     <A HREF=\"http://www.mjolner.com\">Mj&oslash;lner Informatics</A>\n"
                   + "  </FONT>\n"
                   + "</TD>\n"
                   + "<TD WIDTH=\"40%\" ALIGN=\"right\">\n"
                   + "  <SCRIPT LANGUAGE=JavaScript TYPE=\"text/javascript\" SRC=\""
		   +    scriptdir + "lastmod.js\"></SCRIPT>\n"
		   + "</TD>\n"
                   + "</TABLE>\n"
		 );
  document.close();
}

