using System;
using System.Runtime.InteropServices;

public class PcreClrHelper
{

  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    pcre_compile           (String exp, 
			    int options,
			    ref String errptr,
			    ref int erroffset,
			    int tableptr);

  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    locale_pcre_compile    (String exp, 
			    int options,
			    ref String errptr,
			    ref int erroffset);

  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    pcre_exec              (int code, 
			    int extra, 
			    String subject, 
			    int length, 
			    int startOffset, 
			    int options, 
			    int[] ovector, 
			    int ovecsize);
  
  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    pcre_study             (int code, 
			    int options,
			    ref String errptr);
     
  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int[] 
    pcre_fullinfo          (int code, 
			    int extra,
			    int what,
			    ref int where);
}
