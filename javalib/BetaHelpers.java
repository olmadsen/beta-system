package beta;
import java.io.*;

public class BetaHelpers
{
   
  // static methods
  public static long int2long(int i){
    return (long)i;
  }
  public static int  long2int(long j){
    return (int)j;
  }
  public static long int2longMul1000(int i){
    return 1000L*(long)i;
  }
  public static int  long2intDiv1000(long j){
    return (int)(j/1000L);
  }
  public static int[] long2Ints(long d){
      int[] ints = new int[2];
      ints[0] = (int) ((d >>32) & (long)0xffffffff);
      ints[1] = (int) ((d)      & (long)0xffffffff);
      //System.err.println("long2Ints("+d+")=("+ints[0]+","+ints[1]+")");
      return ints;
  }
  public static long ints2Long(int i0, int i1){
      long result = ((long)i0<<32 | (long)i1);
      //System.err.println("ints2Long("+i0+","+i1+")="+result);
      return result;
  }
  public static InputStream get_System_in(){
    return System.in;
  }
  public static PrintStream get_System_out(){
    return System.out;
  }
  public static PrintStream get_System_err(){
    return System.err;
  }
  
  public static void loadJNILibraries (){
    // Cannot be static class constructor - e.g. applets will fail then
    java.lang.System.loadLibrary("BetaHelpers"); // OK to call more than once
    //System.err.println("Loaded JNI library BetaHelpers");
  }

  public static native String getenv(String key);

  public static native   void setFileExePermission(String path);
  

}
