// nbeta tstenv
// csc -t:library -r:clr/tstenv.dll Component.cs

public class Component
{ public static Component current;
  private Component caller;
  private BetaObject body;
  private System.Threading.Thread thread;

  Component(BetaObject b) { 
    body = b; 
    thread = new System.Threading.Thread(new System.Threading.ThreadStart(run));
    thread.IsBackground = true;
  }

  static public void AlloC(BetaObject b)
    { 
      Component C = new Component(b);
      //b.comp\u0024 = C; // b.comp$
      b._comp = C;
      C.caller = C;
    }


  private void run() 
    { 
      body.xdo();
      lock(this) { 
	System.Threading.Monitor.Pulse(this);
      }
    }

  public void swap()
    { 
      lock (this){
	Component X = current;
	current = caller;
	caller = X;
	if (!thread.IsAlive) {
	  thread.Start(); // only relevant if attach
	} else { 
	  System.Threading.Monitor.Pulse(this);
	}
	System.Threading.Monitor.Wait(this);
      }
    }

#if ATT_NEEDED
  public void att()
    { 
      lock (this){
	caller = current;
	current = this;
	if (!thread.IsAlive){
	  thread.Start();
	} else {
	  System.Threading.Monitor.Pulse(this);
	}
	System.Threading.Monitor.Wait(this);
      }
    }
#endif

#if SUSP_NEEDED
  public void susp()
    { 
      lock (this){
	current = caller;
	System.Threading.Monitor.Pulse(this);
	System.Threading.Monitor.Wait(this);
      } 
    }
#endif

}

