public class clrproblems
  { 
    public static void Main(){
      try {
        goto L;
	System.Console.WriteLine("Not reached");
      } catch (System.Exception) {
      }
      L:
        int[] a = new int[1] { 1 };
	System.Console.WriteLine(a[0]);
	return;
    }
  }
