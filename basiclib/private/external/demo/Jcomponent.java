/* Jcomponent.java is a clean Java version of Component.java.
 * Component.java implements coroutines for BETA on jvm.
 * Jcomponent.java is for implementing coroutines in Java.
 * The differences between Component.java and Jcomponent.java are:
 * - Jcomponent.java includes a class Coroutine.java
 * - in Jcomponent.java, BetaObject has been replaced by Coroutine
 * See CoEx.java and Merger.java for examples of using Jcomponent.java
 */

import java.lang.Thread;
import java.lang.reflect.*;
import java.io.*;


public class Jcomponent { 
    // A Component implements a BETA component.
    // A Component has an associated Runner, a subclass of a Thread
    // - A Runner object is associated when the Component is generated
    // - When a Component is terminated, the associated Runner is
    //   kept in a freelist to avoid expensive allocation of Threads

    static final boolean do_trace       = false;

    static Jcomponent current;        // The current executing Component
    private static Runner firstFree; // First free Runner
    private static int id = 0;       // Global counter of Component id's
    private static int freeRunners = 0;
    private static int releasedRunners = 0;
    private static int reusedRunners = 0;
    private static int newRunners = 0;

    private Runner myRunner ;       // The associated Runner
    private int myId;               // The id of this Component
    private Jcomponent caller;       // The Component calling/attaching
                                    // this Component. When suspended,
                                    // is refers to this(Component)
    private Coroutine body;         // The BETA object of this Component
    private boolean isTerminated = false;
    
    static {
	if (do_trace){
	    System.out.println("\n*** OBS:Using compiler/TST/Component.java!\n");
	}
    }

    private static boolean noInit= true;
    
    public Jcomponent(Coroutine b) { 
	if ((noInit) & (current == null)) {
	    noInit = false;
	    current = new Jcomponent(null);
	};
	body = b; 
	if (body != null) b.thisC = this; 
        caller = this;
        myId = id = id + 1;
	if (firstFree == null) {
	    myRunner = new Runner(this);
	    newRunners = newRunners + 1;
	    trace("New Runner");
	}
	else {
	    myRunner = firstFree;
	    firstFree = firstFree.next;
	    freeRunners = freeRunners - 1;
	    reusedRunners = reusedRunners + 1;
	    myRunner.myComponent = this;
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
	} else {
	    isAttach = true;
	    if (isTerminated) {
		System.out.println("Attaching terminated component:"+getName());
		display();
	};};
	Jcomponent old_current;
	old_current = current;
	current = caller;
	caller = old_current;

	if (isAttach) trace("attach");
	//old_current.trace("syncronize");
	synchronized(old_current.myRunner) { // this.myRunner
	    //trace("calling go");
	    current.myRunner.go();  
	    if (old_current.isTerminated) {
		old_current.myRunner = null;
		return;
	    } else { 
		old_current.trace("wait");
		try{old_current.myRunner.wait(); }
		catch (InterruptedException e){} 
	    }
	}
    }
    /*
    protected void finalize() throws Throwable {
	 System.out.print("finalize:new:"+newRunners+','+"released:"+releasedRunners+','+"reused:"+reusedRunners+','+"free:"+freeRunners);
	 if (myRunner != null) 
	     System.out.print("myRunner != null");
	 System.out.println();
	 }*/
 
    public String getName() {
	Class C = body.getClass();
	return C.getName();
    };
    public void displayID() {
	    System.out.println("thread:"+Thread.currentThread().getName());
	    System.out.print("   this:"+myId);
	    if (current != null) 
		System.out.print(",current:"+current.myId+',');
	    if (caller != null)
		System.out.print(",caller:"+caller.myId);
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
	Jcomponent myComponent;
	public int myRunId;
	Runner next;
	Runner(Jcomponent c){
	    myComponent = c;
	    myRunId = runnerId = runnerId + 1;
	    setDaemon(true);
	}

	public void run(){
	    while (true) {
		// myComponent.trace("Execute:body");
		if (myComponent.body == null) return;
		// Call myComponent.body.Do()
		// We cannot use "do" do this directly, since "do" is
		// a reserved Java language word.
		try{
		    myComponent.body.Do();
		} catch (Throwable e){
		    makeDumpFile(e);
		}
		myComponent.isTerminated = true;
		//myComponent.trace("Terminating Runner:"+myRunId);
		myComponent.swap();
		next = firstFree;
		firstFree = this;
		freeRunners = freeRunners + 1;
		releasedRunners = releasedRunners + 1;
		//myComponent.trace("Pooled Runner waits:"+myRunId);
		myComponent = null;  
		synchronized (this)
		    { try{wait(); } catch (InterruptedException e){}
		    };
		myComponent.trace("Pooled Runner resumed:"+myRunId);
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
		// notify();
		synchronized(this) {notify();};
	    }
	}

	void makeDumpFile(Throwable e){
	    String dumpFileName;
	}
    }

}

class Coroutine {
   
    Jcomponent thisC = new Jcomponent(this);

    public void call() { thisC.swap(); }

    public void suspend() { thisC.swap(); }
 
    public void Do(){}; // abstract
}
