using System;
using System.Runtime.InteropServices;

public class hellowrapper
  {
    [ DllImport("hellolib.dll", CallingConvention=CallingConvention.Cdecl) ]
    public extern static void hello(String who);

  }
