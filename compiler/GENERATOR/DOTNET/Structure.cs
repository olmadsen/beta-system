public class Structure {

    private System.Object iOrigin;
    private System.Type iProto;
    private System.Reflection.ConstructorInfo iConstructor;

    static Structure(){
	System.Console.WriteLine("\nUSING Structure.cs!\n");
    }

    public Structure(System.Object o, System.Type p){
	iOrigin = o;
	iProto = p;
	iConstructor = null;
    }
  
    public static Structure AlloS(System.Object o, System.Type p) {
	return new Structure(o, p);
    }
  
    public static Structure ObjS(System.Object o){
	System.Type proto = o.GetType();
	System.Reflection.FieldInfo origin_field = proto.GetField("origin");
	System.Object origin = origin_field.GetValue(o);
	return new Structure(origin, proto);
    }

    public System.Object AlloSI(){
	System.Reflection.ConstructorInfo[] constructors = iProto.GetConstructors();
	if (iConstructor == null){
	  for (int i = 0; i < constructors.Length; i++) {
	    //System.Console.WriteLine("AlloSI: constructor: " + constructors[i].Name);
	    System.Reflection.ParameterInfo[] parameters = constructors[i].GetParameters();
	    if (parameters.Length == 1){
	      //System.Console.WriteLine("Has one parameter of type: " + parameters[0].ParameterType.FullName);
	      if (parameters[0].ParameterType.IsAssignableFrom(iOrigin.GetType())){
		iConstructor = constructors[i];
		break;
	      }
	    }
	  }
	}
#if false
	if (iConstructor==null){
	    System.Console.WriteLine("AlloSI:\tNo constructor with parameter type (origin)\n\t'" + iOrigin.GetType().FullName + "' found in class '" + iProto.FullName + "'!");
	}
#endif
	return iConstructor.Invoke(new System.Object[]{iOrigin});
    }
  
    public static bool eqS(Structure arg1, Structure arg2) {
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

    public static bool neS(Structure arg1, Structure arg2) {
	return !eqS(arg1, arg2);
    }

    public static bool leS(Structure arg1, Structure arg2) { 
	return (eqS(arg1, arg2) || ltS(arg1, arg2));
    }

    public static bool geS(Structure arg1, Structure arg2) { 
	return (eqS(arg1, arg2) || gtS(arg1, arg2));
    }

    public static bool gtS(Structure arg1, Structure arg2){
	return ltS(arg2, arg1);
    }
  
    public static bool ltS(Structure arg1, Structure arg2){
	System.Type proto1;
	System.Type proto2;
	if (arg1==null) return false;
	if (arg2==null) return false;
	proto1 = arg1.iProto;
	proto2 = arg2.iProto;
	if (proto1 == proto2) return false;
	  
	for (proto1 = proto1.BaseType;
	     proto1 != null;
	     proto1 = proto1.BaseType) {
	    if (proto1 == proto2) {
		if (false){
		  //return arg1.iOrigin == arg2.iOrigin;
		} else {
		    System.Object newObject = arg1.AlloSI();
		    System.Reflection.FieldInfo origin_field = proto1.GetField("origin");
		    return origin_field.GetValue(newObject) == arg2.iOrigin;
		}
	    }
	}
	return false; 
    }
}
