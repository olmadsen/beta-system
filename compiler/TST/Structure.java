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
    {
	return !eqS(arg1, arg2);
    }

    public static boolean leS(Structure arg1, Structure arg2)
    { 
	return (eqS(arg1, arg2) || ltS(arg1, arg2));
    }

    public static boolean geS(Structure arg1, Structure arg2)
    { 
	return (eqS(arg1, arg2) || gtS(arg1, arg2));
    }

    public static boolean gtS(Structure arg1, Structure arg2)
    {
	return ltS(arg2, arg1);
    }

    public static boolean ltS(Structure arg1, Structure arg2)
    {
	Class proto1;
	Class proto2;
	Object newObject;

	if (arg1==null) return false;
	if (arg2==null) return false;
  
	proto1 = arg1.iProto;
	proto2 = arg2.iProto;
  
	if (proto1 == proto2)
	    return false;

	/* Prefix of proto1 is the first try */
  
	for (proto1 = proto1.getSuperclass();
	     proto1 != null; /* proto1 != Object## */
	     proto1 = proto1.getSuperclass()) {
	    if (proto1 == proto2) {
		/* There is some hope, now we need to check if origins are equal. */
		if (true /*FIXME: proto2->OriginOff == arg1->iProto->OriginOff*/){
		    /* The original prototypes have same origin offset 
		     * i.e. (same prefix level),
		     * so the result is (arg1->iOrigin == arg2->iOrigin) 
		     */
		    return arg1.iOrigin == arg2.iOrigin;
		}
	
		/* If proto1 and proto2 has different Origin Prefix
		 * we need to generate an object from arg1 and then
		 * test the resulting origin from the new object.
		 *   
		 * We need to generate a new item, as this is currently the only
		 * way we can get the origin.
		 * The problem is that there are several origins 
		 * (one per prefixlevel).
		 * So we generate an object corresponding to arg1 and find the 
		 * origin at the offset determined *by the prefix* (proto2). 
		 * This should be the same as origin of arg2.
		 */
	
		//newObject = arg1.AlloSI();
		//return true; // FIXME: (Object *)((long*)newObject)[proto2->OriginOff] == (arg2->iOrigin);
	    }
	}
    
	return false; 
    }

}
