using System;

public class BetaHelpers
{
   
  // static fields
  static long zero;

  // static constructor
  static BetaHelpers() {
    zero = (new DateTime(1970,1,1)).ToFileTime();
    // Console.WriteLine("zero: " + DateTime.FromFileTime(zero).ToString());
  }

  // static methods
  public static long modtimeToFileTime(int modtime){
    // Convert modtime (seconds since 1970/1/1) to filetime
    long filetime = ((long)10000000*(long)modtime)+zero;
    // Console.WriteLine("modtimeToFileTime:    " + modtime + " ->\n                      " + filetime);
    return filetime;
  }
  public static int  fileTimeToModtime(long filetime){
    // Convert filetime to modtime (seconds since 1970/1/1)
    int modtime = (int)((filetime-zero)/(long)10000000);
    // Console.WriteLine("fileTimeToModtime:    " + filetime + " ->\n                      " + modtime);
    return modtime;
  }

}
