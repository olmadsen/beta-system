
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

  public static char[] NewVR1(char[] array) {
    int size = array.length;
    if (size<0) size = 0;
    return new char[size];
  }

  public static char[] CopyVR1(char[] array) {
    int size = array.length;
    if (size<0) size = 0;
    char[] newArray = new char[size];
    System.arraycopy(array, 0, newArray, 0, size);
    return newArray;
  }

  public static char[] CopySVR1(char[] array, int low, int high) 
    throws ArrayIndexOutOfBoundsException
  {

    // Check that low and high are usable. 
    if (low<1) 
      throw new ArrayIndexOutOfBoundsException("Repetition subrange out of bounds (low): " 
					       + low 
					       + "<1");
    if (array.length<high) 
      throw new ArrayIndexOutOfBoundsException("Repetition subrange out of bounds (high): "
					       + high
					       + ">"
					       + array.length
					       );
      
    int newsize = high - low + 1;
    if (newsize<0) newsize = 0;
    char[] newArray = new char[newsize];
    System.arraycopy(array, low-1, newArray, 0, newsize);
    return newArray;
  }
}
