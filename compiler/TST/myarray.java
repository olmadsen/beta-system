public class myarray {
    Object Q[];
    String S[] = new String[3];
    public void go(){
        System.out.println("Begin myarray");

	Q = S;
	S = (String[])Q;
        System.out.println("Cast of Object[] to String[]");

        String[] newArray1 = new String[3];          // Declared as String
        System.arraycopy(S, 0, newArray1, 0, 3);
        S = (String[]) newArray1;                  
        System.out.println("Cast of copied String/String[]");

        Object[] newArray2 = new String[3];           // new String
        System.arraycopy(S, 0, newArray2, 0, 3);
        S = (String[]) newArray2;                    
        System.out.println("Cast of copied Object/new String/String[]");

        Object[] newArray3 = new Object[3];            // new Object
        System.arraycopy(S, 0, newArray3, 0, 3);
        S = (String[]) newArray3;                      // CAST FAILURE
        System.out.println("Cast of copied Object/new Object/String[]");
    }

    static public void main(String[] arg)
    {
	myarray S = new myarray();
        S.go();
    }
}
