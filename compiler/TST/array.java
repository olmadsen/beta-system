public class array {
    Object Q[];
    String S[] = new String[3];
    public void go(){
	Q = S;
	S = (String[])Q;
        Object[] newArray = new Object[3];
        System.arraycopy(S, 0, newArray, 0, 3);
        S = (String[]) newArray;
   }
    public void main(String[] argv)
    {
	array S = new array();
        S.go();
    }
}
