class Comp extends Thread
{ static Comp current;
  Comp caller;
  BetaObject body;

  Comp(){};
  Comp(BetaObject b) { body = b; }

  synchronized void att()
    { trace("Comp:att");
      caller = current;
      current = this;
      if (!isAlive()) start();
      else notify();
      try{ wait(); } catch (InterruptedException e){}
    }
    
  synchronized void susp()
    { current = caller;
      notify();
      try{ wait(); } catch (InterruptedException e){}
    } 

  public void run() 
    { trace("Comp:run");
      body.xdo();
    }
  public void trace(String T)
    { if (false) System.out.println(T);
    }
}

