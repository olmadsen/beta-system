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
  public static long Int2Long(int i){
    // Needed because of missing int64 arithmetic in beta
    return (long)i;
  }
  public static int  Long2Int(long j){
    // Needed because of missing int64 arithmetic in beta
    return (int)j;
  }

  public static long ModTimeToFileTime(int modtime){
    // Convert modtime (seconds since 1970/1/1) to filetime
    // Needed because of missing int64 arithmetic in beta
    long filetime = ((long)10000000*(long)modtime)+zero;
    // Console.WriteLine("modtimeToFileTime:    " + modtime + " ->\n                      " + filetime);
    return filetime;
  }
  public static int  FileTimeToModtime(long filetime){
    // Convert filetime to modtime (seconds since 1970/1/1)
    // Needed because of missing int64 arithmetic in beta
    int modtime = (int)((filetime-zero)/(long)10000000);
    // Console.WriteLine("fileTimeToModtime:    " + filetime + " ->\n                      " + modtime);
    return modtime;
  }

  public static bool DiskEntryHasAttribute(FileSystemInfo info, int att){
    // Needed because of missing bit-operations for enumerations (implemented as references)
    return (info.Attributes & ((FileAttributes)att)) != 0;
  }

  public static string FormatReal(string format, double r){
    // Needed because boxing not implemented in beta
    CultureInfo old_culture = Thread.CurrentThread.CurrentCulture;
    Thread.CurrentThread.CurrentCulture = new CultureInfo("en-us");
    string result = String.Format(format, r); // boxing r here
    Thread.CurrentThread.CurrentCulture = old_culture;
    return result;
  }

  public static void WriteInt8(BinaryWriter bw, sbyte v){
    // Not really needed, since there is a Write(sbyte)
    bw.Write(v);
  }  

  public static sbyte ReadInt8(BinaryReader br){
    // Not really needed, since there is a ReadSByte()
    return br.ReadSByte();
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
    // Needed since int8u (result type of br.ReadBytes) not implemented in nbeta
    byte[] Rx = br.ReadBytes(range);
    for (int i=0; i<range; i++){
      R[i] = (sbyte)Rx[i];
    }
  }

  public static string FormatModTime(int modtime){
    // Needed since DateTimeFormatInfo implements multiple interfaces, which is not
    // correctly supported by nbeta; see sysutils/private/time_clrbody.bet
    DateTime dt = DateTime.FromFileTime(ModTimeToFileTime(modtime));
    return dt.ToString("ddd MMM dd HH':'mm':'ss yyyy", DateTimeFormatInfo.InvariantInfo);
  }

  public static string AssemblyNameGetPublicKeyToken(System.Reflection.AssemblyName an){
    // Needed since result of an.GetPublicKeyToken is intu8 array -- currently not supported
    byte[] pt = an.GetPublicKeyToken();
    System.Text.StringBuilder s = new System.Text.StringBuilder(pt.GetLength(0));
    for (int i=0;i<pt.GetLength(0);i++){
      s.AppendFormat ("{0:x}", pt[i]);
    }
    return s.ToString();
  }
}
