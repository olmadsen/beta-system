import java.lang.reflect.*;

public class Structure {

    public Object iOrigin;
    public Class iProto;
    private Constructor iConstructor;
  
    Structure(Object o, Class p){
	iOrigin = o;
	iProto = p;
	iConstructor = null;
    }

    public static Structure AlloS(Object o, Class p) {
	return new Structure(o, p);
    }

    public static Structure ObjS(Object o)
	throws Exception
    {
	Class proto = o.getClass();
	Field origin_field;
	Object origin;
	origin_field = proto.getDeclaredField("origin");
	origin = origin_field.get(o);
	return new Structure(origin, proto);
    }

    public Object AlloSI() throws Exception
    {
	Constructor[] constructors = iProto.getDeclaredConstructors();
	if (iConstructor == null){
	    search:
	    for (int i = 0; i < constructors.length; i++) {
		Class[] parameterTypes = constructors[i].getParameterTypes();
		if (parameterTypes.length == 1){
		    if (parameterTypes[0].isAssignableFrom(iOrigin.getClass())){
			iConstructor = constructors[i];
			break search;
		    }
		}
	    }
	}
	return iConstructor.newInstance(new Object[]{iOrigin});
    }

    public static boolean eqS(Structure arg1, Structure arg2)
    {
	if (arg1==null) {
	    if (arg2==null)
		return true;
	    return false;
	}
	if (arg2==null)
	    return false;
	if (arg1.iProto != arg2.iProto)
	    return false;
	if (arg1.iOrigin != arg2.iOrigin)
	    return false;
	return true;
    }

    public static boolean neS(Structure arg1, Structure arg2)
    throws Exception
    {
	return !eqS(arg1, arg2);
    }

    public static boolean leS(Structure arg1, Structure arg2)
    throws Exception
    { 
	return (eqS(arg1, arg2) || ltS(arg1, arg2));
    }

    public static boolean geS(Structure arg1, Structure arg2)
    throws Exception
    { 
	return (eqS(arg1, arg2) || gtS(arg1, arg2));
    }

    public static boolean gtS(Structure arg1, Structure arg2)
    throws Exception
    {
	return ltS(arg2, arg1);
    }

    public static boolean ltS(Structure arg1, Structure arg2)
    throws Exception
    {
	if (arg1==null) return false;
	if (arg2==null) return false;
	Class proto1 = arg1.iProto;
	Class proto2 = arg2.iProto;
	if (proto1 == proto2) return false;
	/* Prefix of proto1 is the first try */
	for (proto1 = proto1.getSuperclass();
	     proto1 != null; /* proto1 != Object## */
	     proto1 = proto1.getSuperclass()) {
	    if (proto1 == proto2) {
		if (false /*identical originoff's*/){
		    return arg1.iOrigin == arg2.iOrigin;
		}
		Object newObject = arg1.AlloSI();
		Field origin_field = proto1.getDeclaredField("origin");
		return origin_field.get(newObject) == arg2.iOrigin;
	    }
	}
	return false; 
    }

}
