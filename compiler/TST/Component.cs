// nbeta tstenv
// csc -t:library -r:clr/tstenv.dll Component.cs

class Component
{ static Component current;
  Component caller;
  BetaObject body;
  System.Threading.Thread thread;

  Component(BetaObject b) { 
    body = b; 
    thread = new System.Threading.Thread(new System.Threading.ThreadStart(run));
    thread.IsBackground = true;
  }

  static public void AlloC(BetaObject b)
    { Component C = new Component(b);
    //b.comp$ = C;
      C.caller = C;
    }

  public void swap()
    { 
      lock (this){
	trace("Component:swap");
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

  void att()
    { 
      lock (this){
	trace("Component:att");
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
    
  void susp()
    { 
      lock (this){
	trace("Component:susp");
	current = caller;
	System.Threading.Monitor.Pulse(this);
	System.Threading.Monitor.Wait(this);
      } 
    }

  public void run() 
    { 
      trace("Component:run");
      body.xdo();
      trace("Component:terminated");
      lock(this) { 
	System.Threading.Monitor.Pulse(this);
      }
    }

  public void trace(System.String T)
    { 
      if (true) System.Console.WriteLine(T);
    }
}

