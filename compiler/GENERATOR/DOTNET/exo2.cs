// csc -doc:exo2.xml -r:System.dll exo2.cs

using System;

public class ExOException : Exception
{

  public object exitobj;
  public int labno;
  public bool restart;

  // Constructor used for object checking
  public ExOException (object e, int l, bool r) 
    {
      exitobj = e;
      labno = l;
      restart = r;
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
          if ((e.exitobj == this) && (e.labno==1)){
            /* We have a leave/restart of L1 in this object (program) */
            if (e.restart){
              goto L1;
            }
          } else {
            /* Not L1 in this object - propagate further */
            throw;
          }
        }
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
      L2:
        try 
          { 
            singular_2.eval_singular_2(this);
          }
        catch (ExOException e)
          {
            if ((e.exitobj == this) && (e.labno==2)){
              /* We have a leave/restart of L2 in this object (singular_1) */
              if (e.restart){
                goto L2;
              }
            } else {
              /* Not L2 in this object - propagate further */
              throw;
            }
          }
        Console.Write(-4);
      }
  }

public class singular_2
  {
    public singular_1 origin;
    public char dummy2;
    // constructor
    public singular_2(singular_1 s1) { origin = s1; }

    public static void eval_singular_2(singular_1 s1)
      {
        singular_2 s2 = new singular_2(s1);
        s2._do();
      }

    /// <summary>Method throwing exceptions to model leave/restart</summary>
    public void _do()
      {
        Console.Write(origin.origin.i);
        if (origin.origin.i==1){
          origin.origin.i = 2;
          throw new ExOException(origin.origin, 1, true); // restart L1
          Console.Write(-1);
        } else {
          origin.origin.i = 3;
          throw new ExOException(origin.origin, 1, false); // leave L1
          Console.Write(-2);
        }
        Console.Write(-3);
      }
  }
