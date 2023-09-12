small: obj
   %basic 1, "small"
   x: var integer
   y: val 14
   R: obj TTT
   S: ref TTT
   xx := 117
   %public
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
   R: ref bar:with
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
   "Hello\n".print
   ("world".print)
   if (xx = 117) :then
      xx := xx + 1
   :else
      xx := xx - 1
   if (xx = 12) :then
      xx := xx + 5
      if (xx =13) :then
          xx := 7
      :else
          xx := 8
   :else
      xx := xx - 1
