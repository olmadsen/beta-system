using System;
using System.Text;
using System.Runtime.InteropServices;

public class hellowrapper
  {
    [ DllImport("hellolib.dll", CallingConvention=CallingConvention.Cdecl) ]
    public extern static void hello(String who);

    [ DllImport("hellolib.dll", CallingConvention=CallingConvention.Cdecl) ]
    public extern static void gethello(ref String where);

    public static String gethello_wrapper()
      {
	String result = null;
	gethello(ref result);
	return result;
      }

  }
