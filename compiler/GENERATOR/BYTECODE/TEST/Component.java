class Component extends Thread
{ static Component current;
  Component caller;
  BetaObject body;

  Component(){};
  Component(BetaObject b) { body = b; setDaemon(true); }

  synchronized void att()
    { trace("Component:att");
      caller = current;
      current = this;
      if (!isAlive()) start();
      else notify();
      try{ wait(); } catch (InterruptedException e){}
    }
    
  synchronized void susp()
    { trace("Component:susp");
      current = caller;
      notify();
      try{ wait(); } catch (InterruptedException e){}
    } 

  public void run() 
    { trace("Component:run");
      body.xdo();
      trace("Component:terminated");
      synchronized(this) { notify();};
    }
  public void trace(String T)
    { if (false) System.out.println(T);
    }
}

