// csc -r:System.dll exo.cs

using System;

public class ExOException : Exception
{

  public object exitobj;
  public int labno;
  public bool restart;

  // Constructor used for object checking
  public ExOException (object e, int l) 
    {
      exitobj = e;
      labno = l;
    }
  public ExOException ()
    {
    }
}

public class program
  {
    public object origin;
    public int i;
    // Constructor
    public program(object o){ origin=o; }

    static void eval_program(object o)
      {
        program p = new program(o);
        p._do();
      }

    public void _do(){
      i = 1;
    L1:
      try 
        { 
          singular_1.eval_singular_1(this);
        }
      catch (ExOException e)
        {
          if (e.exitobj == this){
	    if (e.labno==1){
	      /* We have a restart in this object */
              goto L1;
            } else if (e.labno==2){
	      /* We have a leave in this object */
              goto L2;
	    }
	  }
	  /* Not leave/restart in this object - propagate further */
	  throw;
        }
    L2:
      Console.WriteLine(i);
    }

    public static void Main ()
      {
        program.eval_program(null);
      }
  }

public class singular_1
  {
    public program origin;
    public char dummy;
    // constructor
    public singular_1(program p) { origin = p; }

    public static void eval_singular_1(program p)
      {
        singular_1 s = new singular_1(p);
        s._do();
      }

    public void _do()
      {
        Console.Write(origin.i);
        if (origin.i==1){
          origin.i = 2;
          throw new ExOException(origin, 1); // restart L1
          Console.Write(-1);
        } else {
          origin.i = 3;
          throw new ExOException(origin, 2); // leave L1
          Console.Write(-2);
        }
        Console.Write(-3);
      }
  }
