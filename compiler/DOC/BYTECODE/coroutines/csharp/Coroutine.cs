public abstract class Coroutine {

  internal Component _comp;

  public Coroutine(){
    _comp = new Component(this);
  }

  public void call() { _comp.swap(); }

  protected void suspend() { _comp.swap(); }

  public abstract void Do();
}

public class Component {
  public static Component current;
  private Component caller;
  private Coroutine body;
  private System.Threading.Thread thread;

  public Component(Coroutine b) { 
    body = b; 
    thread = new System.Threading.Thread(new System.Threading.ThreadStart(run));
    thread.IsBackground = true;
    b._comp = this;
    caller = this;
  }

  private void run() 
    { 
      body.Do();
      // Terminate component
      lock(this) { 
	System.Threading.Monitor.Pulse(this);
      }
    }

  public void swap()
    { 
      lock (this){
	Component old_current = current; // may be equal to this when suspend()
	current = caller; // may be equal to this when call()
	caller = old_current;
	if (!thread.IsAlive) {
	  thread.Start(); // only relevant if attach
	} else { 
	  System.Threading.Monitor.Pulse(this);
	}
	System.Threading.Monitor.Wait(this);
      }
    }
  }

