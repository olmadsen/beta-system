public class Structure {

  public BetaObject iOrigin;
  public System.Type iProto;
  
  Structure(BetaObject o, System.Type p){
    iOrigin = o;
    iProto = p;
  }
  
  public static Structure AlloS(BetaObject o, System.Type p) {
    return new Structure(o, p);
  }
  
  public static Structure objS(BetaObject o){
    Structure s = new Structure(null, o.GetType());
    // Cannot be done since BetaObject has no origin field.
    // Must be done by compiler after objS call
    // s.iOrigin = o.origin
    return s;
  }

  public BetaObject AlloSI() 
  {
    BetaObject item = null;
    item = (BetaObject)(iProto.Assembly.CreateInstance(iProto.AssemblyQualifiedName));
    // Cannot be done since BetaObject has no origin field.
    // Must be done by compiler after AlloSI call
    // item.origin = iOrigin;
    return item;
  }
  
  public static bool eqS(Structure arg1, Structure arg2)
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

  public static bool neS(Structure arg1, Structure arg2)
  {
    return !eqS(arg1, arg2);
  }

  public static bool leS(Structure arg1, Structure arg2)
  { 
    return (eqS(arg1, arg2) || ltS(arg1, arg2));
  }

  public static bool geS(Structure arg1, Structure arg2)
  { 
    return (eqS(arg1, arg2) || gtS(arg1, arg2));
  }

  public static bool gtS(Structure arg1, Structure arg2)
  {
    return ltS(arg2, arg1);
  }

  public static bool ltS(Structure arg1, Structure arg2)
  {
    System.Type proto1;
    System.Type proto2;
    //BetaObject newObject;

    if (arg1==null) return false;
    if (arg2==null) return false;
  
    proto1 = arg1.iProto;
    proto2 = arg2.iProto;
  
    if (proto1 == proto2)
      return false;

   /* Prefix of proto1 is the first try */
  
    for (proto1 = proto1.BaseType;
	 proto1 != null; /* proto1 != Object## */
	 proto1 = proto1.BaseType) {
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
