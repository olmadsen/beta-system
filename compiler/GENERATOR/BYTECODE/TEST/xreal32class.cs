using System;
using System.Globalization;

public class xreal32class
{
    public void put(float f) 
    { 
      // Create a CultureInfo object for English in the U.S.
      CultureInfo us = new CultureInfo("en-US");
      // Display i formatted as compact decimal form for "us".
      Console.WriteLine(f.ToString("g", us));
    }
    
}

