
public abstract class BetaArray {

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

    public static char[] CopyVR1(char[] array) {
	int size = array.length;
	if (size<0) size = 0;
	char[] newArray = new char[size];
	System.arraycopy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static char[] CopySVR1(int low, int high,char[] array) 
	throws ArrayIndexOutOfBoundsException
    {

	CkSR(low, high, array.length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	char[] newArray = new char[newsize];
	if (newsize>0) System.arraycopy(array, low-1, newArray, 0, newsize);
	return newArray;
    }




    public static boolean[] ExtVRZ(boolean[] array, int add) {
	int copysize = array.length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	boolean[] newArray = new boolean[newsize];
	System.arraycopy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static boolean[] CopyVRZ(boolean[] array) {
	int size = array.length;
	if (size<0) size = 0;
	boolean[] newArray = new boolean[size];
	System.arraycopy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static boolean[] CopySVRZ(int low, int high,boolean[] array) 
	throws ArrayIndexOutOfBoundsException
    {

	CkSR(low, high, array.length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	boolean[] newArray = new boolean[newsize];
	if (newsize>0) System.arraycopy(array, low-1, newArray, 0, newsize);
	return newArray;
    }




    public static short[] ExtVR2(short[] array, int add) {
	int copysize = array.length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	short[] newArray = new short[newsize];
	System.arraycopy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static short[] CopyVR2(short[] array) {
	int size = array.length;
	if (size<0) size = 0;
	short[] newArray = new short[size];
	System.arraycopy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static short[] CopySVR2(int low, int high,short[] array) 
	throws ArrayIndexOutOfBoundsException
    {

	CkSR(low, high, array.length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	short[] newArray = new short[newsize];
	if (newsize>0) System.arraycopy(array, low-1, newArray, 0, newsize);
	return newArray;
    }



    public static int[] ExtVR4(int[] array, int add) {
	int copysize = array.length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	int[] newArray = new int[newsize];
	System.arraycopy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static int[] CopyVR4(int[] array) {
	int size = array.length;
	if (size<0) size = 0;
	int[] newArray = new int[size];
	System.arraycopy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static int[] CopySVR4(int low, int high,int[] array) 
	throws ArrayIndexOutOfBoundsException
    {

	CkSR(low, high, array.length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	int[] newArray = new int[newsize];
	if (newsize>0) System.arraycopy(array, low-1, newArray, 0, newsize);
	return newArray;
    }


    public static double[] ExtVR8(double[] array, int add) {
	int copysize = array.length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	double[] newArray = new double[newsize];
	System.arraycopy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static double[] CopyVR8(double[] array) {
	int size = array.length;
	if (size<0) size = 0;
	double[] newArray = new double[size];
	System.arraycopy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static double[] CopySVR8(int low, int high,double[] array) 
	throws ArrayIndexOutOfBoundsException
    {

	CkSR(low, high, array.length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	double[] newArray = new double[newsize];
	if (newsize>0) System.arraycopy(array, low-1, newArray, 0, newsize);
	return newArray;
    }


    public static void CkSR(int low, int high, int range) 
	throws ArrayIndexOutOfBoundsException
    {

	// Check that low and high are usable. 
	if (low<1) 
	    throw new ArrayIndexOutOfBoundsException("Repetition subrange out of bounds (low): " 
						     + low 
						     + "<1");
	if (range<high) 
	    throw new ArrayIndexOutOfBoundsException("Repetition subrange out of bounds (high): "
						     + high
						     + ">"
						     + range
						     );
    }

}
