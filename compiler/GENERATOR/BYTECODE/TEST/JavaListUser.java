class JavaListUser extends Object
/*  Use pattern List.bet in this Java program */
{
    public static void main(String args[])
    { List L = new List(null);
      number N1 = new number(null);
      number N2;
      N1.set(88);
      L.insert(N1);
      N2 = (number)L.get();
      System.out.println(N2.get());
    }
}
