// nbeta ../../betaenv
// csc -t:library -r:../../clr/betaenv.dll Coroutine.cs

public class Coroutine
{ 
  public static Coroutine current;
  private Coroutine caller;
  private BetaObject body;
  private System.Threading.Thread myThread;
  private bool isTerminated = false;

  static bool nocatch = false;
  static string betart = null;

  static bool trace = false;

  private int myID = 0;
  private static int gID = 0;

  private static bool first = true;

  static Coroutine(){
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
    // Check for trace
    trace = (System.Environment.GetEnvironmentVariable("TRACE") != null);
    if (trace){
      System.Console.WriteLine("Trace enabled through TRACE environment variable");
    }

    if ((first) && (current == null)) {
      // Hack to set up dummy current, corresponding to Main
      first = false;
      current = new Coroutine(null);
    };
    Trace("Initial current: " + ID(current));
  }

  internal static void Trace(System.String msg){
    if (trace){
      System.Console.WriteLine("\n" + msg);
    }
  }

  internal static string ID(Coroutine c){
    System.String id = "";
    if (trace){
      if (c==null){
	id = "<Null> (Main)";
      }
      if (c.body==null){
	id = "[body=<NULL> (Main)";
      } else {
	id = "[body=" + c.body.ToString();
      }
      id += " #" + c.myID + "]";
    }
    return id;
  }

  public Coroutine(BetaObject b) { 
    if (b==null){
      /* Special case used for main/betaenv in static constructor above */
      //body = tstenv.betaenvRef; 
    } else {
      body = b; 
      body._comp = this;
      myThread = new System.Threading.Thread(new System.Threading.ThreadStart(run));
      myThread.IsBackground = true; // Don't keep alive if terminated
    }
    caller = this;
    myID = gID = gID + 1;
  }
    
  private void run() 
    { 
      Trace("Running coroutine: " + ID(this));
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
      // Terminate coroutine
      /* Acquire lock on this Coroutine object. 
       * A thread will wait here if it cannot aquire the lock.

       * The thread that attached this coroutine is currently waiting in the Wait() statement in the end of swap().
       * To 
       */
      Trace("Acquiring lock for termination of coroutine: " + ID(this));
      lock(this) { 
	Trace("Terminating (Pulse) coroutine waiting for lock on " + ID(this));
	System.Threading.Monitor.Pulse(this);
	isTerminated = true;
	/* Lock implicitly released here */
	Trace("Implicit release of lock after termination of coroutine: " + ID(this));
      }
	 
    }

  public void swap()
    { 

      // Attach:  this == callee  is being attached
      //          current is calling (active) component
      //
      //          lock callee
      //          swap(current,callee.current)
      //          callee.myRunner.go
      //          - start myRunner
      //          - callee.myRunner.notify()
      //          callee.myRunner.wait()
      //          - caller waits for callee.myRunner

      // Suspend: this == current is suspending component
      //          return to current.caller
      //
      //          lock current.myRunner
      //          swap(current.caller,current)
      //          current.myRunner.go
      //          - myRunner.notify()
      //          old_current.wait()
	 
      bool isAttach = (current != this);

      if (isTerminated){
	Trace("  swap[" + myID + "] : Executing terminated coroutine " + ID(this));
	makeDumpFile("Executing terminated coroutine " + ID(this), System.Environment.StackTrace);
	return;
      } 

      Trace("Swap (" + (isAttach?"attach":"suspend") + ") coroutine: " + ID(this));
	 
      /* Swap pointers */
      Coroutine old_current = current;

      Trace("  swap[" + myID + "] : Acquiring lock for old_current: " + ID(old_current));
      System.Threading.Monitor.Enter(this /*old_current ????? */);
      Trace("  swap[" + myID + "] : old_current = " + ID(old_current));
      current = caller; // may be equal to 'this' in case of suspend
      Trace("  swap[" + myID + "] : current = " + ID(current));
      caller = old_current;
      Trace("  swap[" + myID + "] : caller = old_current = " + ID(caller));
      
      /* Start or resume new current */
      /* Acquire lock on this Coroutine object. 
       * A thread will wait here if it cannot aquire the lock 
       */
      if (!myThread.IsAlive) {
	// only relevant if attach
	Trace("  swap[" + myID + "] : Start coroutine: " + ID(this));
	myThread.Start(); 
      } else { 
	// ????? Trace("  swap[" + myID + "] : Acquiring lock for this: " + ID(this));
	// ????? System.Threading.Monitor.Enter(this); 

	Trace("  swap[" + myID + "] : Resume (Pulse) some coroutine waiting for lock on " + ID(this)); 
	/* The current thread holds the lock on this Coroutine object, 
	 * and by Pulse it signals to the next thread waiting for the lock that 
	 * it can be moved to the ready-queue. When the current thread later
	 * releases the lock (wait below) one of the threads in the 
	 * ready-queue aquires the lock and can continue 
	 */
	System.Threading.Monitor.Pulse(this);
	// ????? Trace("  swap[" + myID + "] : Releasing lock for this: " + ID(this));
	// ????? System.Threading.Monitor.Exit(this); 
      
      }
      Trace("  swap[" + myID + "] : Suspend (Wait) coroutine, wait for lock on" + ID(this));
      /* Release lock on this Coroutine object and wait until lock reacquired */
      System.Threading.Monitor.Wait(this/*old_current ????? */); 
      Trace("  swap[" + myID + "] : Releasing lock for: " + ID(this));
      System.Threading.Monitor.Exit(this/*old_current ????? */); 
    }

  public void makeDumpFile(System.Exception e){
    System.String msg;
    System.String stackTrace;
    if (e is ExOException){
      msg = "Cross Coroutine leave/restart NYI.";
      // Stop myThread and delegate exception to caller???
    } else {
      msg = "";
      if (e.GetType() != typeof(System.Exception)){
	// Don't print trivial information
	msg += e.GetType().ToString() + ": ";
      }
      msg += e.Message;
    }
    stackTrace = e.StackTrace;
    // stackTrace = System.Environment.StackTrace;
    makeDumpFile(msg, stackTrace);
  }

  public void makeDumpFile(System.String msg, System.String stackTrace){
    System.String dumpFileName;
    msg = "\n# Beta execution aborted: " + msg;
    System.Console.Error.WriteLine(msg);
    try {
      dumpFileName = System.Environment.GetCommandLineArgs()[0];
      dumpFileName = dumpFileName.Substring(0,dumpFileName.Length-4); // strip .exe
      dumpFileName = dumpFileName.Replace('\\','/');
      dumpFileName += ".dump";
      System.Console.Error.WriteLine("# Look at '" + dumpFileName + "'");
      System.IO.StreamWriter dumpWriter 
	= new System.IO.StreamWriter(new System.IO.FileStream(dumpFileName, System.IO.FileMode.Create));
      dumpWriter.WriteLine(msg);
      dumpWriter.WriteLine(stackTrace);
      dumpWriter.Close();
    } catch (System.Exception){                   
      System.Console.Error.WriteLine(stackTrace);
    }
    System.Environment.Exit(-1);
  }
}

