
// aClass:
class aClass extends Object {
  Object origin;
  public aClass(Object org){
    origin = org;
    c = 0;
  }
  long c;;
  
  // bClass:
  class bClass extends Object {
    aClass origin;
    public bClass(aClass org){
      origin = org;
      n = 0;
    }
    long n;;
    
    // up:
    class up extends Object {
      bClass origin;
      public up(bClass org){
        origin = org;
        m = 0;
      }
      long m;
      
      public void do_0(){
        m = n+m;
        c = c+1;
      }
      public void do_1(){}
    }
    public up new_up(){ return new up(this); }
    public void call_up(long m){
      up S;
      S = (up)new_up();
      S.m = m;
      S.do_0();
    };
    
  }
  public bClass new_bClass(){ return new bClass(this); };
  
  // stat:
  class stat extends Object {
    aClass origin;
    public stat(aClass org){
      origin = org;
    }
    
    public void do_0(){
      System.out.println(c);
      System.out.println();
    }
    public void do_1(){}
  }
  public stat new_stat(){ return new stat(this); }
  public void call_stat(){
    stat S;
    S = (stat)new_stat();
    S.do_0();
  };
  
};

