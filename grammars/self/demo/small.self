--- selftest: expression: self ---
(|  var1 . var2  . max .
     
    foo = ( 'here is foo' print ).

    bar = ( bar . 'and bar' print).

    put: At: =(| :val . :index | var1 + val * index ).

    * = (| :a . :b | a * b )
|)