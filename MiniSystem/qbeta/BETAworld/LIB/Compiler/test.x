test: obj {
   %public;
   x: var integer;
   S: ref String;
   foo: {v:< object; y: var boolean };
   bar: foo{v:: text};
   fisk: foo{v::< #record};
   x := 119;
   § hello there!
   x := 3.14;
   @if (x = 17) && (x <> 0) :then
       { put (x) }
   S := "Hello"       
   }
