using System;
public class SupportClass
{
	public static int GetConstructorModifiers(System.Reflection.ConstructorInfo constructor)
	{
		int temp;
		if (constructor.IsPublic)
			temp = 1;
		else if (constructor.IsPrivate)
			temp = 2;
		else
			temp= 4;
		return temp;
	}

	/*******************************/
	public static void WriteStackTrace(System.Exception throwable, System.IO.TextWriter stream)
	{
		stream.Write(throwable.StackTrace);
		stream.Flush();
	}

}
