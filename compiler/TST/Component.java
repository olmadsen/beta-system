package beta;

public class Component { 
    // A Component implements a BETA component.
    // A Component has an associated Runner, a subclass of a Thread
    // - A Runner object is associated when the Component is generated
    // - When a Component is terminated, the associated Runner is
    //   kept in a freelist to avoid expensive allocation of Threads

    static Component current;        // The current executing Component
    private static Runner firstFree; // First free Runner
    private static int id = 0;       // Global counter of Component id's

    private Runner myRunner ;       // The associated Runner
    private int myId;               // The id of this Component
    private Component caller;       // The Component calling/attaching
                                    // this Component. When suspended,
                                    // is refers to this(Component)
    private BetaObject body;        // The BETA object of this Component

    static {
     System.out.println("\n*** OBS:Using compiler/TST/Component.java!\n");
    }

    Component(BetaObject b) { 
	body = b; 
	b.comp$ = this; 
        caller = this;
        myId = id = id + 1;
	if (firstFree == null) {
	    trace("New Runner ");
	    myRunner = new Runner(this);
	}
	else {
	    trace("Reusing Runner ");
	    myRunner = firstFree;
	    firstFree = firstFree.next;
	    myRunner.myComponent = this;
	};
    }

    public void swap() {  
	boolean isAttach = false;
	synchronized(myRunner) {
	    if (current == this) 
		trace("suspend");
	    else
		isAttach = true;
	    Component old_current;
	    old_current = current;                                    
	    current = caller;
	    caller = old_current;
	    if (isAttach) trace("attach");
	    myRunner.go();
	    try{ myRunner.wait(); } catch (InterruptedException e){}
	}
    }
 
    public void display() {
	System.out.print("id:"+myId+':');
	if ((caller != null) & (caller != this))
	    caller.display();
    }
	
    public void trace(String T) { 
	if (false) {
	    Class C = body.getClass();
	    System.out.println(T+':'+' '+C.getName());
	    display();
	    System.out.println();      
	}
    }

    class Runner extends Thread
    { Component myComponent;
	Runner next;
	Runner(Component c){
	    myComponent = c;
	    setDaemon(true);
	}

	public void run(){
	    while (true) {
		myComponent.body.xdo();
		trace("Terminating Runner ");
		swap();
		myComponent = null;
		next = firstFree;
		firstFree = this;
		trace("Pooled Runner waits");
		synchronized (this)
		    { try{wait(); } catch (InterruptedException e){}
		    };
		trace("Pooled Runner resumed");
	    }
	}
	public void go() { 
	    if (!isAlive()) { 
		trace("Runner.go");
		start();
	    }
	    else
		synchronized(this) {notify();};
	}
    }
}

