// csc -t:exe -r:System.dll startprocess.cs

public class StartProcess
  {
    public static void Main()
        {
	  System.Diagnostics.Process p = new System.Diagnostics.Process();
	  p.StartInfo.FileName = "hello.exe";
	  p.Start();
	  p.WaitForExit();
	}
  }

