/* 
   cl -Fehellolib.dll -Zi -LD hellolib.c -link -DEF:hellolib.def
   csc -t:library hellowrapper.cs
   csc -t:exe -r:hellowrapper.dll helloworld.cs
   helloworld.exe
 */

using System;

public class helloworld
  {
    public static void Main(String[] args)
      {  
	hellolib.hello("C#");
      }
  }
