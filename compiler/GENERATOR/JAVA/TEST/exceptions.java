// javac -g:none exceptions.java
// java exceptions

public class exceptions
{
    public void do_throw() throws ArithmeticException
    {
        throw new ArithmeticException();
    }

    public void try_catch()
    {
	try
	    {
		do_throw();
	    } 
	catch (ArithmeticException e)
	    {
		System.out.println("Caught ArithmeticException");
	    }
    }

    public static void main(String[] args) 
    {
	exceptions e = new exceptions();
	e.try_catch();
    }
}
