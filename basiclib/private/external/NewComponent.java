package beta;

import java.lang.Thread;
import java.lang.reflect.*;


public class Component { 
    // A Component implements a BETA component.
    // A Component has an associated Runner, a subclass of a Thread
    // - A Runner object is associated when the Component is generated
    // - When a Component is terminated, the associated Runner is
    //   kept in a freelist to avoid expensive allocation of Threads

    static final boolean do_trace       = false;
    static final boolean use_reflection = true;

    static Component current;        // The current executing Component
    private static Runner firstFree; // First free Runner
    private static int id = 0;       // Global counter of Component id's
    private static int freeRunners = 0;
    private static int releasedRunners = 0;
    private static int reusedRunners = 0;
    private static int newRunners = 0;
    private static int interrupted = 0;

    private Runner myRunner ;       // The associated Runner
    private int myId;               // The id of this Component
    private Component caller;       // The Component calling/attaching
                                    // this Component. When suspended,
                                    // is refers to this(Component)
    private BetaObject body;        // The BETA object of this Component
    private boolean isRunning = false;  // true if at least one attach
    private boolean isTerminated = false;
    private boolean isMainComponent = false;
    
    static {
	if (do_trace){
	    System.out.println("\n*** OBS:Using compiler/TST/Component.java!\n");
	}
    }

    private static boolean noInit= true;
    
    Component(BetaObject b) { 
	if ((noInit) & (current == null)) { 
	    noInit = false;
	    current = new Component(null);
	    current.isMainComponent = true;
	    current.myRunner.myComponent = current;
	};
	body = b; 
	if (body != null) b.comp$ = this; 
        caller = this;
        myId = id = id + 1;
	if (firstFree == null) {
	    myRunner = new Runner(null);
	    newRunners = newRunners + 1;
	    trace("New Runner");
	}
	else {
	    myRunner = firstFree;
	    firstFree = firstFree.next;
	    myRunner.next = null;
	    freeRunners = freeRunners - 1;
	    reusedRunners = reusedRunners + 1;
	    //myRunner.myComponent = this;
	    trace("Reusing Runner");
	};
    }

    public void swap() {
	// Attach:  this == callee  is being attached
	//          current is calling component
	//          lock callee.myRunner
	//          swap(current,callee.current)
	//          callee.myRunner.go
	//          - start myRunner
	//          - callee.myRunner.notify()
	//          callee.myRunner.wait()
	//          - caller waits for callee.myRunner
	// Suspend: this == current is suspending component
	//          return to current.caller
	//          lock current.myRunner
	//          swap(current.caller,current)
	//          current.myRunner.go
	//          - myRunner.notify()
	//          old_current.wait()

	boolean isAttach = false;
	if (current == this) {
	    trace("suspend");
	    isAttach = false;
	    myRunner.myComponent = null;
	} else {
	    isAttach = true;
	    isRunning = true;
	    if (isTerminated) {
		System.out.println("Attaching terminated component:"+getName());
		display();
	    } else {
		//System.out.println("set myComponent");
		//caller.display();
		myRunner.myComponent = caller;
	    }
	};
	Component old_current;
	old_current = current;
	current = caller;
	caller = old_current;

	if (isAttach) trace("attach");
	//old_current.trace("syncronize");
	synchronized(old_current.myRunner) { // this.myRunner
	    //trace("calling go");
	    current.myRunner.go();  
	    if (old_current.isTerminated) {
		old_current.trace("isTerminated");
		old_current.myRunner = null;
		if (current.isMainComponent) statistics();
		return;
	    } else { 
		old_current.trace("wait");
		try{old_current.myRunner.wait(); }
		catch (InterruptedException e)
		    { System.out.println("Interrupt in swap");} 
	    }
	}
    }
    protected void finalize() throws Throwable {
	if (myRunner != null) {
	    interrupted = interrupted + 1;
	    System.out.print("Finalize:interrupt:");
	    if (isRunning) {
		System.out.print("isRunning:"); 
	    } else {
		System.out.print("isNotRunning:"); 
	    };
	    trace("Finalize:interrupt");
	    if (isTerminated) System.out.print("isTerminated");
	    statistics();
	    myRunner.interrupt();
	}

    }
 
    public String getName() {
	Class C = body.getClass();
	return C.getName();
    };
    public void displayID() {
	    System.out.println("thread:"+Thread.currentThread().getName());
	    if (current != null) 
		System.out.print("   current:"+current.myId+',');
	    if (caller != null)
		System.out.print("   caller:"+caller.myId);
	    System.out.print("\n   ");
	    display();
	    System.out.println();      
    }
    public void display() {
	if (body != null) {
	    Class C = body.getClass();
	    System.out.print(C.getName());
	} else {
	    System.out.print("basic");
	};
	System.out.print("["+myId);
	if (myRunner != null) {
	    System.out.print(","+myRunner.myRunId+']');
	} else System.out.print(']');
	if ((caller != null) & (caller != this))
	    caller.display();
    }
    public void statistics() {
	System.out.println("new:"+newRunners+','
			   +"released:"+releasedRunners+','
			   +"reused:"+reusedRunners+','
			   +"free:"+freeRunners+','
			   +"interrupted:"+interrupted);
    }
    public void trace(String T) { 
	if (do_trace) { 
	    System.out.print("\n   "+T+':');
	    displayID(); 
	}
    } 
    public void trace2(String T) { if (true) trace(T); }

    static int runnerId=0;
    class Runner extends Thread
    { 
	Component myComponent;
	public int myRunId;
	Runner next;
	Runner(Component c){
	    myComponent = c;
	    myRunId = runnerId = runnerId + 1;
	    setDaemon(true);
	}
	public void doInterrupt() { interrupt(); }
	public void run() {
	    while (true) {
		myComponent.trace("Execute:body");
		// Call myComponent.body.do()
		// We cannot do this directly, since "do" is
		// a reserved Java language word.
		if (use_reflection){
		    // Calling the real do(), using reflection:
		    try {
			myComponent.body
			    .getClass()
			    .getMethod("do",null)
			    .invoke(myComponent.body,null);
		    } catch (NoSuchMethodException e){
			System.err.println("Component.java: myComponent.body.do(): no such method");
		    } catch (Exception e){
			
			System.err.println("Component.java: cannot call myComponent.body.do()");
			myComponent.displayID();
		    } ;
		} else {
		    // Calling this method xdo() instead.
		    // myComponent.body.xdo();
		}
		myComponent.isTerminated = true;
		myComponent.trace("Terminating Runner:"+myRunId);
		// myComponent.swap();
		Component old_current = current;
		current = myComponent.caller;
		myComponent.caller = old_current;
		myComponent.myRunner = null;
		old_current = null;
		myComponent = null;
		current.myRunner.go();
		while (true) {
		    next = firstFree;
		    firstFree = this;
		    freeRunners = freeRunners + 1;
		    releasedRunners = releasedRunners + 1;
		    //myComponent.trace("Pooled Runner waits:"+myRunId);
		    myComponent = null;  
		    synchronized (this) {
			try{wait(); 
			myComponent.trace("Pooled Runner resumed:"+myRunId);
			break; 
			} catch (InterruptedException e) { 
			    // return to Runner pool ;
			    // System.out.println("myRunner interrupted");
			};
		    }
		}
	    }
	}
	public void go() { 
	    if ((!isAlive()) & (myComponent.body != null)) { 
		//myComponent.trace("Runner.go:start:"+myRunId);
		start();
		//myComponent.trace("Runner.go:started:"+myRunId);
	    }
	    else {
		//myComponent.trace("Runner:go:notify:"+myRunId);
		synchronized(this) {notify();};
	    }
	}
    }
}

