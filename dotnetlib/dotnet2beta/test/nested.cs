using System;
using System.Reflection;
using System.Reflection.Emit;

// Create a class with two nested public classes and two nested protected classes.
public class MyTypeClass
{
    public class Myclass1
    {
    }
    public class Myclass2 
    {
    }
    protected class MyClass3
    {
    }
    protected class MyClass4
    {
    }
}

public class TypeMain
{
    public static void Main() 
    {
        Type myType =(typeof(MyTypeClass));
        // Get the public nested classes.
        Type[] myTypeArray = myType.GetNestedTypes(BindingFlags.Public|BindingFlags.Instance);
        Console.WriteLine("The number of nested public classes is {0}.", myTypeArray.Length);
        // Display all the public nested classes.
        DisplayTypeInfo(myTypeArray);
        // Get the nonpublic nested classes.
        Type[] myTypeArray1 = myType.GetNestedTypes(BindingFlags.NonPublic|BindingFlags.Instance);
        Console.WriteLine("The number of nested protected classes is {0}.", myTypeArray1.Length);
        // Display all the nonpublic nested classes.
        DisplayTypeInfo(myTypeArray1); 
	Console.WriteLine("Declaring class of Myclass2 is: " + typeof(MyTypeClass.Myclass2).DeclaringType);
	Console.WriteLine("Declaring class of MyTypeClass is: " + typeof(MyTypeClass).DeclaringType);
    }
    public static void DisplayTypeInfo(Type[] myArrayType)
    {
        // Display the information for all the nested classes.
        for(int i=0;i<myArrayType.Length;i++)
        {
            Type myType = (Type)myArrayType[i];
            Console.WriteLine("The name of the nested class is {0}.", myType.ToString());
        }
    }
}
