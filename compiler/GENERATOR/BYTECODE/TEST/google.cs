/*
  Compilation statements: 
    csc -target:library -out: googleapi/dotnet/GoogleSearchService.dll googleapi/dotnet/GoogleSearchService.cs
    csc /r:System.dll /r:googleapi/dotnet/GoogleSearchService.dll google.cs 
*/ 
using System;
using System.Text.RegularExpressions;

class Google
{
  public static void Main(String[] arguments) 
    { 
      String licence = "hweCKhQvbXY6kvKmOpDS2P3lTqQ5ggBu";
      String query = "";
      int i;
      foreach (String a in arguments) query += a + " ";
      if (query == "") {
	Console.Write("Search Google for: ");
	query = Console.ReadLine();
      }
      if (query == "") {
	query = "Ole Lehrmann Madsen BETA.NET";
      }
      Console.WriteLine("\nSearching Google for: " + query);
      GoogleSearchService s = new GoogleSearchService();
      GoogleSearchResult r = s.doGoogleSearch(licence, query, 0, 10, false, "", false, "", "latin1", "latin1");
      Console.WriteLine("\n" + r.resultElements.Length + " Results:");
      for (i=0; i<r.resultElements.Length; i++){
	// Print result stripped for HTML using Regular Expressions
	Regex paras  = new Regex("<p>");     // match HTML paragraph break tags
	Regex breaks = new Regex("<br>");    // match HTML line break tags
	Regex tags   = new Regex("<[^>]+>"); // match HTML tags
	Regex less   = new Regex("&lt;");    // match HTML less
	Regex greater= new Regex("&gt;");    // match HTML greater
	Regex amp    = new Regex("&amp;");   // match HTML ampersand
	String title = r.resultElements[i].title;
	String snippet = r.resultElements[i].snippet;

	title = tags.Replace(title, "");
	Console.WriteLine("\n" + (i+1) + ". " + title);

	snippet = paras.Replace(snippet, "\n");
	snippet = breaks.Replace(snippet, "\n");
	snippet = tags.Replace(snippet, "");
	snippet = less.Replace(snippet, "<");
	snippet = greater.Replace(snippet, ">");
	snippet = amp.Replace(snippet, "&");

	Console.WriteLine(snippet);
	Console.WriteLine("URL: " + r.resultElements[i].URL);
      }
      Console.WriteLine();
    }
}






