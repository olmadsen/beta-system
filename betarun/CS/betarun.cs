using System;
using System.Reflection;

namespace betarun 
  {
  public class helpers 
    {
      public static Object Create(string classname)
        {
          // Load the assembly to use.
          Assembly a = Assembly.Load(classname);
          
          // Get the type to use from the assembly.
          Type t = a.GetType(classname);
          
          // Create an instance of the class.
          Object o = Activator.CreateInstance(t);
          
          return o;
        }
      public static void Call(object o, string classname, string method)
        {
          // Load the assembly to use.
          Assembly a = Assembly.Load(classname);
          
          // Get the type to use from the assembly.
          Type t = a.GetType(classname);
          
          // Get the method to call from the type.
          MethodInfo m = t.GetMethod(method);
          
          // Create the args array.
          // Object[] args = new Object[1];
          // Set the arguments.
          // args[0] = ...;
          
          // Invoke the method.
          m.Invoke(o, /*args*/null);
        }
      public static void CreateAndCall(string classname, string method)
        {
          // Load the assembly to use.
          Assembly a = Assembly.Load(classname);
          
          // Get the type to use from the assembly.
          Type t = a.GetType(classname);
          
          // Get the method to call from the type.
          MethodInfo m = t.GetMethod(method);
          
          // Create an instance of the class.
          Object o = Activator.CreateInstance(t);
          
          // Create the args array.
          // Object[] args = new Object[1];
          // Set the arguments.
          // args[0] = ...;
          
          // Invoke the method.
          m.Invoke(o, /*args*/null);
        }
    }
  }
