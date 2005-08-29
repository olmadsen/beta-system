// nbeta ../../betaenv
// csc -t:library -r:../../clr/betaenv.dll Coroutine.cs

#define LOCK_OLD_CURRENT

public class Coroutine
{ 
  public static Coroutine current;
  private Coroutine caller; // When attached: coroutine that attached me; when suspended: this Coroutine
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

       * The thread that attached this coroutine is currently waiting in the Wait() statement in the end of swap(). */
      Trace("Acquiring lock for termination of coroutine: " + ID(this));
      lock(this) { 
	Trace("Terminating (Pulse) coroutine waiting for lock on " + ID(this));
	System.Threading.Monitor.Pulse(this);
	isTerminated = true;
	current = caller;
	myThread = null;
	/* Lock implicitly released here */
	Trace("Implicit release of lock after termination of coroutine: " + ID(this));
      }
	 
    }

  // Swap currently split out into two different functions for readability

  public void swap()
    {
      Trace("Swap coroutine: " + ID(this));
      Trace(" Swap: Current: " + ID(current));
     if (current == this){
	suspend();
      } else {
	attach();
      }
    }

  public void suspend()
    { 

      Trace("Suspend coroutine: " + ID(this));

      if (isTerminated){
	Trace("  suspend[" + myID + "] : Suspending to terminated coroutine " + ID(this));
	makeDumpFile("Suspending to terminated coroutine " + ID(this), System.Environment.StackTrace);
	return;
      } 
      
      /* Swap pointers */
      Coroutine old_current = current; // Coroutine currently executing, to become detached
      Trace("  suspend[" + myID + "] : old_current = " + ID(old_current));
      current = caller; // Coroutine to become attached; may be equal to 'this' in case of suspend
      Trace("  suspend[" + myID + "] : current = " + ID(current));
      caller = old_current;
      Trace("  suspend[" + myID + "] : caller = old_current = " + ID(caller));

      Coroutine lock_obj;

      lock_obj = old_current;

      Trace("  suspend[" + myID + "] : Acquiring lock for " + ID(lock_obj)); 
      lock(lock_obj){
	/* Start or resume new current */
	if (!myThread.IsAlive) {
	  // Should NOT happen for suspend!!!
	  // Start the thread, causing run() to be executed.
	  // Only relevant if attach: if previously attached and not IsAlive,
	  // the test for isTerminated above will have caught the error
	  Trace("  suspend[" + myID + "] : Start coroutine: " + ID(this));
	  myThread.Start(); 
	} else { 
	  lock(lock_obj){
	    Trace("  suspend[" + myID + "] : Resume (Pulse) some coroutine waiting for lock on " + ID(lock_obj)); 
	    // Gets first thread waiting on lock_obj out of wait-queue and into lock-queue (list of threads competing to get
	    // lock on lock_obj, e.g. pulsed threads, or threads standing in Monitor.Enter(lock_obj)
	    System.Threading.Monitor.Pulse(lock_obj);
	  }
	}
	Trace("  suspend[" + myID + "] : Suspend (Wait) coroutine, wait for lock on " + ID(lock_obj));
	// Release lock and start waiting to get it again.
	// We wait here when we have attached another coroutine.
	System.Threading.Monitor.Wait(lock_obj); 

	Trace("  suspend[" + myID + "] : Releasing lock for: " + ID(lock_obj));
      }
    }

  public void attach()
    { 
      Trace("Attach coroutine: " + ID(this));

      if (isTerminated){
	Trace("  suspend[" + myID + "] : Attaching terminated coroutine " + ID(this));
	makeDumpFile("Attaching terminated coroutine " + ID(this), System.Environment.StackTrace);
	return;
      } 
 
      /* Swap pointers */
      Coroutine old_current = current; // Coroutine currently executing, to become waiting
      Trace("  attach[" + myID + "] : old_current = " + ID(old_current));
      current = caller; // Coroutine to become attached; may be equal to 'this' in case of suspend
      Trace("  attach[" + myID + "] : current = " + ID(current));
      caller = old_current;
      Trace("  attach[" + myID + "] : caller = old_current = " + ID(caller));

      Coroutine lock_obj;

      lock_obj = current;

      Trace("  attach[" + myID + "] : Acquiring lock for " + ID(lock_obj)); 
      lock(lock_obj){
	/* Start or resume new current */
	if (!myThread.IsAlive) {
	  // Start the thread, causing run() to be executed.
	  // Only relevant if attach: if previously attached and not IsAlive,
	  // the test for isTerminated above will have caught the error
	  Trace("  attach[" + myID + "] : Start coroutine: " + ID(this));
	  myThread.Start(); 
	} else { 
	  lock(lock_obj){
	    Trace("  attach[" + myID + "] : Resume (Pulse) some coroutine waiting for lock on " + ID(lock_obj)); 
	    // Gets first thread waiting on lock_obj out of wait-queue and into lock-queue (list of threads competing to get
	    // lock on lock_obj, e.g. pulsed threads, or threads standing in Monitor.Enter(lock_obj)
	    System.Threading.Monitor.Pulse(lock_obj);
	  }
	}
	Trace("  attach[" + myID + "] : Suspend (Wait) coroutine, wait for lock on " + ID(lock_obj));
	// Release lock and start waiting to get it again.
	// We wait here when we have attached another coroutine.
	System.Threading.Monitor.Wait(lock_obj); 

	Trace("  attach[" + myID + "] : Releasing lock for: " + ID(lock_obj));
      }
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

