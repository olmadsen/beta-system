package beta;

public class PcreJvmHelper
{
  // class constructor
  static {
    java.lang.System.loadLibrary("PcreJvmHelper");
  }
  
  // native methods
  public static native int[] initialize (java.lang.String exp, int options);
  public static native int   exec       (int code, int extra, java.lang.String subject, int length, int startOffset, int options, int[] ovector, int ovecsize);
  
}
