public class ExOException extends Exception
{
    
    public Object exitobj;
    public int labno;
    
    // Constructor used for Object checking
    public ExOException (Object e, int l) 
    {
        super();
        exitobj = e;
        labno = l;
    }
}
