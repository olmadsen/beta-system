public class BetaArray {

    static BetaArray(){
	System.Console.WriteLine("\nUSING BetaArray.cs!\n");
    }
  
    public static char[] ExtVR1(char[] array, int add) {
	int copysize = array.Length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	char[] newArray = new char[newsize];
	System.Array.Copy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static char[] CopyVR1(char[] array) {
	int size = array.Length;
	// cannot happen: if (size<0) size = 0;
	char[] newArray = new char[size];
	System.Array.Copy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static char[] CopySVR1(int low, int high, char[] array) 
    {

	CkSR(low, high, array.Length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	char[] newArray = new char[newsize];
	if (newsize>0) System.Array.Copy(array, low-1, newArray, 0, newsize);
	return newArray;
    }




    public static bool[] ExtVRZ(bool[] array, int add) {
	int copysize = array.Length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	bool[] newArray = new bool[newsize];
	System.Array.Copy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static bool[] CopyVRZ(bool[] array) {
	int size = array.Length;
	// cannot happen: if (size<0) size = 0;
	bool[] newArray = new bool[size];
	System.Array.Copy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static bool[] CopySVRZ(int low, int high,bool[] array) 
    {

	CkSR(low, high, array.Length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	bool[] newArray = new bool[newsize];
	if (newsize>0) System.Array.Copy(array, low-1, newArray, 0, newsize);
	return newArray;
    }




    public static short[] ExtVR2(short[] array, int add) {
	int copysize = array.Length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	short[] newArray = new short[newsize];
	System.Array.Copy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static short[] CopyVR2(short[] array) {
	int size = array.Length;
	// cannot happen: if (size<0) size = 0;
	short[] newArray = new short[size];
	System.Array.Copy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static short[] CopySVR2(int low, int high,short[] array) 
    {

	CkSR(low, high, array.Length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	short[] newArray = new short[newsize];
	if (newsize>0) System.Array.Copy(array, low-1, newArray, 0, newsize);
	return newArray;
    }



    public static int[] ExtVR4(int[] array, int add) {
	int copysize = array.Length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	int[] newArray = new int[newsize];
	System.Array.Copy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static int[] CopyVR4(int[] array) {
	int size = array.Length;
	// cannot happen: if (size<0) size = 0;
	int[] newArray = new int[size];
	System.Array.Copy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static int[] CopySVR4(int low, int high,int[] array) 
    {

	CkSR(low, high, array.Length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	int[] newArray = new int[newsize];
	if (newsize>0) System.Array.Copy(array, low-1, newArray, 0, newsize);
	return newArray;
    }


    public static double[] ExtVR8(double[] array, int add) {
	int copysize = array.Length;
	int newsize  = copysize + add;
	if (newsize<0) newsize = 0;
	if (copysize>newsize) copysize = newsize;
	double[] newArray = new double[newsize];
	System.Array.Copy(array, 0, newArray, 0, copysize);
	return newArray;
    }

    public static double[] CopyVR8(double[] array) {
	int size = array.Length;
	// cannot happen: if (size<0) size = 0;
	double[] newArray = new double[size];
	System.Array.Copy(array, 0, newArray, 0, size);
	return newArray;
    }

    public static double[] CopySVR8(int low, int high,double[] array) 
    {

	CkSR(low, high, array.Length);
      
	int newsize = high - low + 1;
	if (newsize<0) newsize = 0;
	double[] newArray = new double[newsize];
	if (newsize>0) System.Array.Copy(array, low-1, newArray, 0, newsize);
	return newArray;
    }


    public static void CkSR(int low, int high, int range) 
    {
	// Check that low and high are usable. 
	if (low<1) 
	    throw new System.IndexOutOfRangeException("Repetition subrange out of bounds (low): " 
						       + low 
						       + "<1");
	if (range<high) 
	    throw new System.IndexOutOfRangeException("Repetition subrange out of bounds (high): "
						       + high
						       + ">"
						       + range);
    }

}
