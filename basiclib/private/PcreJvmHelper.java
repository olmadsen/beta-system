package beta;
import java.lang.*;

/* JNI wrappers for PCRE library.
 * Most of the stuff below is pretty much straight forward 
 * one-to-one wrappers, just converting arguments and results.
 * Multiple results (out parameters and/or return value) 
 * are returned in integer arrays.
 * One exception to the one-to-one mapping: 
 * Error handling is made "delayed" by saving possible errors
 * in the static variables errtext and erroffset, and supplying
 * two accessor functions last_error and last_error_offset 
 * for the latest error. 
 */

public class PcreJvmHelper
{
  // class constructor
  static {
    java.lang.System.loadLibrary("PcreJvmHelper");
  }
  
  // native methods

  public static native int 
  compile           (String exp, 
		     int options, 
		     int tableptr);

  public static native int 
  locale_compile    (String exp, 
		     int options);

  public static native int 
  exec              (int code, 
		     int extra, 
		     String subject, 
		     int length, 
		     int startOffset, 
		     int options, 
		     int[] ovector, 
		     int ovecsize);
  
  public static native int 
  study             (int code, 
		     int options);
     
  public static native int[] 
  full_info         (int code, 
		     int extra,
		     int what);

  public static native String 
  last_error        ();

  public static native int 
  last_error_offset ();

}
