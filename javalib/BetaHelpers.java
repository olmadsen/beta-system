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
  public static InputStream get_System_in(){
    return System.in;
  }
  public static PrintStream get_System_out(){
    return System.out;
  }
  public static PrintStream get_System_err(){
    return System.err;
  }
  
  public static native String getenv(String key);
  
  public static void loadJNILibraries (){
    // Cannot be static class constructor - e.g. applets will fail then
    java.lang.System.loadLibrary("BetaHelpers"); // OK to call more than once
    //System.err.println("Loaded JNI library BetaHelpers");
  }
}
