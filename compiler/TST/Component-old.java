package beta;

public class Component extends Thread
{ static Component current;
    static int id = 0;
    int myId;
    Component caller;
    BetaObject body;

    static {
	System.out.println("\n*** NOTICE:Using compiler/TST/Component.java!\n");
    }

    Component(BetaObject b) { 
	body = b; 
	setDaemon(true); 
	b.comp$ = this; 
        caller = this;
        id = id + 1;
        myId = id;
    }

    synchronized public void swap()
	// attach : current is calling component
	//          component being attached is locked
	// suspend: current is component to be suspended
	//          suspending component is locked
        //          current == this 
    {  boolean isAttach = false;
	if (current == this) 
	    trace("suspend");
	else
	    {// trace("attach ");
	    isAttach = true;
	    };
	Component old_current;
	old_current = current;                                    
	current = caller;
	caller = old_current;
	if (isAttach)  trace("attach ");
	if (!isAlive()) start(); // only relevant if attach
	else notify(); // attach:  attached component is notified,
	               //          but awaits termination of swap
                       // suspend: caller is waiting notify and gets it
                       //          but awaits termination of swap
	try{ wait();   // attach:  caller now waits notify from attached component
                       //          lock on attached component is released
                       //          attached component continues
                       // suspend: suspending component now awaits notify
                       //          from attaching component; lock is release
                       //          and caller is resumed 
           } catch (InterruptedException e){}
    }

    synchronized void att()
    { 
	trace("Component:att");
	caller = current;
	current = this;
	if (!isAlive()) start();
	else notify();
	try{ wait(); } catch (InterruptedException e){}
    }
    
    synchronized void susp()
    { 
	trace("Component:susp");
	current = caller;
	notify();
	try{ wait(); } catch (InterruptedException e){}
    } 

    public void run() 
    { 
	trace("run");
	body.xdo();
	trace("terminated");
        swap();
	// synchronized(this) { notify();};
    }
    public void display()
    { System.out.print("id:"+myId+':');
      if ((caller != null) & (caller != this) & (id > 2))
	  caller.display();
    }
	
    public void trace(String T)
    { 
	if (false) {
	    Class C = body.getClass();
	    System.out.println(T+':'+' '+C.getName());
	    display();
	    System.out.println();      
	}
    }
}
