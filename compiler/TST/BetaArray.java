
public class BetaArray {

    static{
	System.out.println("\nUSING BetaArray.java!\n");
    }
  
    public static char[] ExtVR1(char[] array, int add) {
	int copysize = array.length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	char[] newArray = new char[newsize];
	System.arraycopy(array, 0, newArray, 0, copysize);
	return newArray;
    }
}
