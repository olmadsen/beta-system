using System;
using System.Runtime.InteropServices;

public class PcreClrHelper
{

  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    pcre_compile           (string exp, 
			    int options,
			    ref string errptr,
			    ref int erroffset,
			    int tableptr);

  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    locale_pcre_compile    (string exp, 
			    int options,
			    ref string errptr,
			    ref int erroffset);

  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    pcre_exec              (int code, 
			    int extra, 
			    string subject, 
			    int length, 
			    int startOffset, 
			    int options, 
			    int[] ovector, 
			    int ovecsize);
  
  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int 
    pcre_study             (int code, 
			    int options,
			    ref string errptr);
     
  [ DllImport("PcreDLL.dll", CallingConvention=CallingConvention.Cdecl) ]
    public static extern int
    pcre_fullinfo          (int code, 
			    int extra,
			    int what,
			    ref int where);

  /* Fuctions below hide the use of ref parameters,
   * which is currenly not possible from BETA .
   */

  static string errtext = null;
  static int erroffset = 0;

  public static int compile (string exp, int options, int tableptr)
    {
      errtext = null;
      int result = pcre_compile(exp, options, ref errtext, ref erroffset, tableptr);
      return result;
    }

  public static int locale_compile (string exp, int options)
    {
      errtext = null;
      int result = locale_pcre_compile(exp, options, ref errtext, ref erroffset);
      return result;
    }

  public static int study (int code, int options)
    {
      errtext = null;
      int result = pcre_study(code, options, ref errtext);
      return result;
    }

  public static int[] full_info (int code, int extra, int what)
    {
      int[] results = new int[2];
      results[1] = pcre_fullinfo(code, 
				 extra, 
				 what, 
				 ref results[0]);
      return results;
    }

  public static string last_error()
    {
      return errtext;
    }
    
  public static int last_error_offset()
    {
      return erroffset;
    }
}
