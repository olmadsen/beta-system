class YourComp extends Component
{ String idf;
  YourComp(String id)
    { super(); idf = id; System.out.println("Create: " + idf);}
  public void run()
    { System.out.println(idf + ":1");
      susp();
      System.out.println(idf + ":2");
    }  

}
class MyComp extends Component
{ 
  String idf;
  MyComp(String id) 
    { super(); idf = id; System.out.println("Create: " + idf);}
  public void run()
    { System.out.println(idf + ":1");
      susp();
      System.out.println(idf + ":2");
      foo();
    }
    public void foo()
    { 
      System.out.println(idf + ":3");
      X.att();
      System.out.println(idf + ":4");
      susp();
      System.out.println(idf + ":5");
      X.att();
      System.out.println(idf + ":6");
    }     
  static YourComp X = new YourComp("Jensen");
  static public void main(String args[])
    { MyComp C1;
      YourComp C2;
      
      C1 = new MyComp("Olsen");
      C2 = new YourComp("Hansen");
      System.out.println("Main:1");
      C1.att();
      System.out.println("Main:2");
      C2.att();
      System.out.println("Main:3");
      C2.att();
      System.out.println("Main:4");
      C1.att();
      System.out.println("Main:5");
      C1.att();
      System.out.println("Main:6");
    }
}

