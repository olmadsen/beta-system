using System;

public class GetValuesTest {
    enum Colors { Red, Green, Blue, Yellow };
    enum Styles { Plaid = 0, Striped = 23, Tartan = 65, Corduroy = 78 };

    public static void Main() {

        Console.WriteLine("The values of the Colors Enum are:");
	String[] names = Enum.GetNames(typeof(Colors));
        foreach(int i in Enum.GetValues(typeof(Colors))){
	  Console.Write(names[i] + ": ");
	  Console.WriteLine(i);
	}
    }
}
