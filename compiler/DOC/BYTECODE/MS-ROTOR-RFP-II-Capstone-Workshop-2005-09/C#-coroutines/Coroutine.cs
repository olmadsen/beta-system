
public abstract class Coroutine {
  public static Coroutine current;
  private Coroutine caller;
  private System.Threading.Thread myThread;

  public void call() { swap(); }

  protected void suspend() { swap(); }

  public abstract void Do();

  public Coroutine() { 
    myThread = new System.Threading.Thread(new System.Threading.ThreadStart(run));
    myThread.IsBackground = true;  // Don't keep alive if terminated
    caller = this;
  }

  private void run() 
    { 
      Do();
      // Terminate component
      lock(this) { 
        current = caller;
        myThread = null;
        System.Threading.Monitor.Pulse(this);
      }
    }

  public void swap()
    { 
      lock (this){
        Coroutine old_current = current; // may be equal to this when suspend()
        current = caller; // may be equal to this when call()
        caller = old_current;
        if (!myThread.IsAlive) {
          myThread.Start(); // only relevant if attach
        } else { 
          System.Threading.Monitor.Pulse(this);
        }
        System.Threading.Monitor.Wait(this);
      }
    }
  }

