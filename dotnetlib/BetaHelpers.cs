using System;
using System.Threading;
using System.Globalization;
using System.IO;

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
  public static long int2long(int i){
    // Needed because of missing int64 arithmetic in beta
    return (long)i;
  }
  public static int  long2int(long j){
    // Needed because of missing int64 arithmetic in beta
    return (int)j;
  }

  public static long modtimeToFileTime(int modtime){
    // Convert modtime (seconds since 1970/1/1) to filetime
    // Needed because of missing int64 arithmetic in beta
    long filetime = ((long)10000000*(long)modtime)+zero;
    // Console.WriteLine("modtimeToFileTime:    " + modtime + " ->\n                      " + filetime);
    return filetime;
  }
  public static int  fileTimeToModtime(long filetime){
    // Convert filetime to modtime (seconds since 1970/1/1)
    // Needed because of missing int64 arithmetic in beta
    int modtime = (int)((filetime-zero)/(long)10000000);
    // Console.WriteLine("fileTimeToModtime:    " + filetime + " ->\n                      " + modtime);
    return modtime;
  }

  public static bool diskentryHasAttribute(FileSystemInfo info, int att){
    // Needed because of missing bit-operations for enumerations (implemented as references)
    return (info.Attributes & ((FileAttributes)att)) != 0;
  }

  public static string formatReal(string format, double r){
    // Needed because boxing not implemented in beta
    CultureInfo old_culture = Thread.CurrentThread.CurrentCulture;
    Thread.CurrentThread.CurrentCulture = new CultureInfo("en-us");
    string result = String.Format(format, r); // boxing r here
    Thread.CurrentThread.CurrentCulture = old_culture;
    return result;
  }

  public static void WriteInt8Array(BinaryWriter bw, sbyte[] R, int range){
    // Needed since int8u (argument type of bw.Write) not implemented in nbeta
    byte[] Rx = new byte[range];
    for (int i=0; i<range; i++){
      Rx[i] = (byte)R[i];
    }
    bw.Write(Rx);
  }

  public static void ReadInt8Array(BinaryReader br, sbyte[] R, int range){
    // Needed since int8u (result type of bw.ReadBytes) not implemented in nbeta
    byte[] Rx = br.ReadBytes(range);
    for (int i=0; i<range; i++){
      R[i] = (sbyte)Rx[i];
    }
  }
}
