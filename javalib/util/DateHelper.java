package beta;

public class DateHelper
{

    // Helper needed since BETA.java does not support long/int64
    public static java.util.Date DateFromSeconds(int seconds){
	return new java.util.Date((long)seconds*1000);
    }

    // Helper needed since BETA.java does not support long/int64
    public static int DateGetTimeSeconds(java.util.Date date){
	return (int)date.getTime()/1000;
    }

    // Helper needed since BETA.java does not overloaded constructors
    public static java.util.Date DateNow(){
	return new java.util.Date();
    }
}
