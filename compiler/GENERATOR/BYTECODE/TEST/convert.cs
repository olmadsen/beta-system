public class convert
{
  public int Int64ToInt32(long x){
    System.Console.WriteLine("Int64ToInt32(" + x + ")");
    return (int)x;
  }
  public long Int32ToInt64(int x){
    System.Console.WriteLine("Int32ToInt32(" + x + ")");
    return (long)x;
  }
  public static int staticInt64ToInt32(long x){
    System.Console.WriteLine("staticInt64ToInt32(" + x + ")");
    return (int)x;
  }
  public static long staticInt32ToInt64(int x){
    System.Console.WriteLine("staticInt32ToInt32(" + x + ")");
    return (long)x;
  }
}
