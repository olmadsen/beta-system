/*
  File: Coroutine.java

  Originally written by Keld Helsgaun and released into the public domain.
  This may be used for any purposes whatsoever without acknowledgment.

  History:
  Date       Who                What
  5May2000  kh         Created public version
*/

/*package javaCoroutine;*/

/**
* This class may be used for coroutine sequencing in Java.
* <p>
* Coroutines are created as instances of <tt>Coroutine</tt>-derived
* classes that override the abstract method <tt>body</tt>. 
* The <tt>body</tt> method is used to specify their actions.
* <p>
* A coroutine may temporarily suspend its execution and another
* coroutine may take over. A suspended coroutine may later
* be resumed at the point where it was suspended.
* <p> 
* Resumption can be performed by one of
* two operations, <tt>resume(c)</tt> and <tt>call(c)</tt>, where
* <tt>c</tt> is a <tt>Coroutine</tt>-object.
* <p> 
* Both operations resumes <tt>c</tt> and supends the currently 
* executing coroutine.
* <p>
* The <tt>call</tt> operation furthermore establishes the current
* coroutine as <tt>c</tt>'s caller. 
* Coroutine <tt>c</tt> is said to be <i>attached</i> to its caller.
* <p>
* A coroutine can relinquish control to its caller by means 
* of the operation <tt>detach()</tt>.
* This causes the caller to resume its execution from the point where 
* it last left off.
*/
public abstract class Coroutine {
    /**
    * The actions of this coroutine. 
    */	
    protected abstract void body();

    /**
    * Resumes the specified coroutine and suspends the currently
    * executing coroutine.
    * <p>
    * The coroutine is resumed from the point where if last left off.
    *
    * @param <tt>next</tt> The coroutine to be resumed.
    *
    * @exception <tt>RuntimeException</tt>
    * if <tt>next</tt> is terminated, attached or <tt>null</tt>.  
    */			
    public static final void resume(Coroutine next) {
         if (next == null) 
             error("resume non-existing coroutine");
         if (next.terminated)
             error("resume terminated coroutine");
         if (next.caller != null)
             error("resume attached coroutine");
         if (next == current) 
             return; 
         while (next.callee != null)
              next = next.callee;
         next.enter(); 		
    }
    
    /**
    * Calls the specified coroutine and suspends the currently
    * executing coroutine.
    * <p>
    * The coroutine is attached to the current coroutine 
    * and resumed from the point where if last left off. 
    *
    * @param <tt>next</tt> The coroutine to be called.
    *
    * @exception <tt>RuntimeException</tt>
    * if <tt>next</tt> is terminated, attached or <tt>null</tt>.  
    */	
    public static final void call(Coroutine next) {
        if (next == null) 
            error("call non-existing coroutine");
        if (next.terminated)
            error("call terminated coroutine");
        if (next.caller != null)
            error("call attached coroutine");
        if (current != null)
            current.callee = next;
        next.caller = current;
        while (next.callee != null)
            next = next.callee;
        if (next == current) 
            error("call operating coroutine");
        next.enter();	 
    }

    /**
    * Detaches the specified coroutine.
    * <p>
    * The coroutine is suspended and its caller is resumed.
    * <p>
    * If the coroutine has no caller, the "main coroutine" 
    * is resumed. The main coroutine designates the first 
    * coroutine  <tt>resume</tt>d (or <tt>call</tt>ed) in a 
    * system of coroutines.
    */	
    public static final void detach() {
        Coroutine next = current.caller;
        if (next != null) {
            current.caller = next.callee = null;
            next.enter();
        }
        else if (main != null && current != main)
            main.enter();
    }

    /**
    * Returns the currently operating coroutine.
    */
    public static final Coroutine currentCoroutine() {
        return current;
    }

    /**
    * Returns the main coroutine.
    */
    public static final Coroutine mainCoroutine() {
        return main;
    }

    /**
    * Throws a run-time exception with a specified error
    * message.
    *
    * @exception <tt>RuntimeException</tt> 
    * always. 
    */			
    private static void error(String msg) {
        throw new RuntimeException(msg);
    }

    /**
    * This class is used to run coroutines.
    *<p>
    * Each coroutine is run by its own thread. 
    * When a thread is no longer needed by a coroutine, 
    * the thread is inserted into a free list. 
    * Threads from this list may be reused to run new coroutines.   
    */
    private final class Runner extends Thread {
        Coroutine myCoroutine;  // The target coroutine
        Runner nextFree;        // Next Runner in the free list

        Runner(Coroutine c) {
            myCoroutine = c;
            setDaemon(true);    // Runners must die when all user threads have died
        }

        public void run() {
            while (true) {
                myCoroutine.body();             // Run my coroutine  
                if (!myCoroutine.terminated) {
                    myCoroutine.terminated = true;
                    detach();               
                }
                if (myCoroutine == Coroutine.main) { 
                    Coroutine.current = null;  // The main coroutine has exited           
                    synchronized(Runner.class) {   
                        Coroutine.main = null;           
                        Runner.class.notify(); // Start the next coroutine system (if any)
                    }
                    return; 
                }
                nextFree = firstFree;          // Insert this Runner into the free list
                firstFree = this;
                try {
                    synchronized(this) { 
                        wait();                // Wait to be employed again
                    }
                } catch (InterruptedException e) {}
            }
        }

        void go() {                             
            if (!isAlive())
                start();	       // Start this thread
            else 
            synchronized(this) { 
                notify();                      // Resume the target coroutine
            }
        }
    }

    /** 
    /* The curently operating coroutine.
    */ 
    private static Coroutine current;

    /** 
    /* The main coroutine.
    */ 
    private static Coroutine main;

    /**
    * The caller of this coroutine.
    */	
    private Coroutine caller;

    /**
    * The coroutine called by this coroutine.
    */
    private Coroutine callee;

    /**
    * A boolean flag used to inform the associated coroutine 
    * whether or not its body should terminate.
    */
    protected boolean terminated;

    /**
    * The <tt>Runner</tt> of this coroutine.
    */
    private Runner myRunner;

    /**
    * The first Runner in the free list.
    */
    private static Runner firstFree;

    /**
    * Transfers control from the current coroutine to this coroutine.
    */	
    private void enter() {
        if (myRunner == null) {                  // Get a Runner for this coroutine
            if (firstFree == null)        
                myRunner = new Runner(this);     // Create a new Runner
            else {
                myRunner = firstFree;            // Allocate a Runner from the free list
                firstFree = firstFree.nextFree;
                myRunner.myCoroutine = this;
            }
        }
        if (main == null) {                      
            main = current = this;               // This coroutine is the main coroutine
            myRunner.go();                       // Start this coroutine
            synchronized(Runner.class) {    
                try {                   
                    while (main != null)
                        Runner.class.wait(); // Wait until the current coroutine system stops        
                } catch (InterruptedException e) {}
            }
            return;
        }
        Coroutine old_current = current; 
        synchronized(old_current.myRunner) {           
            current = this;                       
            myRunner.go();                        // Resume this coroutine (the new current) 
            if (old_current.terminated)
                return;
            try {
                old_current.myRunner.wait();      // Wait to be resumed
            } catch(InterruptedException e) {}
        }
    }	
}
