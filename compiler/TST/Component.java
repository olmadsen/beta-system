package beta;
//package org.eclipse.ui.betaeditor.beta;

class Component extends Thread
{ static Component current;
    Component caller;
    BetaObject body;

    Component(){};
    Component(BetaObject b) { body = b; setDaemon(true); }

    static public void AlloC(BetaObject b)
    { 
	Component C = new Component(b);
	b.comp$ = C;
	C.caller = C;
    }
    synchronized public void swap()
    { 
	trace("Component:swap");
	Component X;
	X = current;
	current = caller;
	caller = X;
	if (!isAlive()) start(); // only relevant if attach
	else notify();
	try{ wait(); } catch (InterruptedException e){}
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
	trace("Component:run");
	body.xdo();
	trace("Component:terminated");
	synchronized(this) { notify();};
    }
    public void trace(String T)
    { 
	if (false) System.out.println(T);
    }
}

