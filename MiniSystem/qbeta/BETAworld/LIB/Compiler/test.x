test: obj {
   %public;
   x: var integer;
   foo: {v:< object; y: var boolean };
   bar: foo{v:: text};
   fisk: foo{v::< #record};
   x := 119;
   x := 3.14;
   @if x = 17 :then
       { put (x) }
   }
