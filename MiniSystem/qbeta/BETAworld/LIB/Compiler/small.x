small: obj
   %basic 1, "small"
   x: var integer
   y: val 14
   R: obj TTT
   S: ref TTT
   xx := 117
   go: do
      q: var integer
   foo:
      z: var integer
      V:<
          a: var integer
   bar: foo
      V::
         b: var integer
   B: obj bar	 
   xx := xx + 118
   b.V
   fisk(n: var integer, m: var integer):
      n := n + 1 * m
   putGo(V: var integer):at[inx: var integer]:until{go:< object}:
       V := inx
       go
   put(V: var integer):at[inx: var integer]:
       V := inx
       go        
   fisk(x,17)
   put(117):at[12]
