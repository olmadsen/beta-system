// nbeta ../../betaenv
// csc -t:library -r:../../clr/betaenv.dll Component.cs

public class Component
{ public static Component current;
  private Component caller;
  private BetaObject body;
  private System.Threading.Thread thread;

  static bool nocatch = false;
  static string betart = null;

  static Component(){
    // Parse BETART
    betart = System.Environment.GetEnvironmentVariable("BETART");
    if (betart!=null && betart.Length>0){
      //System.Console.WriteLine("Using BETART: " + betart);
      string[] values = betart.Split(new char[]{':'}, 100);
      foreach (string v in values){
	// System.Console.WriteLine("  " + v);
	if (System.String.Compare(v, "nocatch", true)==0){
	  nocatch = true;
	}
      }
    }
  }

  public Component(BetaObject b) { 
    body = b; 
    thread = new System.Threading.Thread(new System.Threading.ThreadStart(run));
    thread.IsBackground = true;
    b._comp = this;
    caller = this;
  }

  private void run() 
    { 
      try
	{
	  body.Do();
	} catch (System.Exception e) {
	  if (nocatch){
	    throw e;
	  } else {
	    makeDumpFile(e);
	  }
	}
      // Terminate component
      lock(this) { 
         System.Threading.Monitor.Pulse(this);
      }
    }

  public void swap()
    { 
      lock (this){
	Component old_current = current;
	current = caller; // may be equal to this in case of suspend
	caller = old_current;
	if (!thread.IsAlive) {
	  thread.Start(); // only relevant if attach
	} else { 
	  System.Threading.Monitor.Pulse(this);
	}
	System.Threading.Monitor.Wait(this);
      }
    }

  public void makeDumpFile(System.Exception e){
      System.String dumpFileName;
      if (e is ExOException){
	  System.Console.Error.WriteLine("# Beta execution aborted: Cross Component leave/restart NYI.");
		// Stop this thread and delegate exception to caller???
	    } else {
		System.Console.Error.WriteLine("# Beta execution aborted: " + e.GetType().ToString() + ": " + e.Message);
	    }
	    try {
		dumpFileName = System.Environment.GetCommandLineArgs()[0];
		dumpFileName = dumpFileName.Substring(0,dumpFileName.Length-4); // strip .exe
		dumpFileName = dumpFileName.Replace('\\','/');
		dumpFileName += ".dump";
		System.Console.Error.WriteLine("# Look at '" + dumpFileName + "'");
		System.IO.StreamWriter dumpWriter 
		  = new System.IO.StreamWriter(new System.IO.FileStream(dumpFileName, System.IO.FileMode.Create));
		dumpWriter.WriteLine(e.Message);
		dumpWriter.WriteLine(e.StackTrace);
		dumpWriter.Close();
	    } catch (System.Exception){		    
		System.Console.Error.WriteLine(e.StackTrace);
	    }
	    System.Environment.Exit(-1);
	}

}

