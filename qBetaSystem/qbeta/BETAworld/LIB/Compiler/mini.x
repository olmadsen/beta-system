small: obj
   %globals
   %id "small"
   V: var integer
   W: var integer
   B: var Boolean
   C: val 117
   put(v: var integer):at[ix: var integer]:doit{StmtX:< Object}:
      StmtY
   R: ref put:at:exe
   S: ref #record:get 
   V := 117
   V := W := 119
   B := V = W
   R.foo
   if (B) :then
      V := 21
   V := if (B):then{12}:else{13}
   (V,w) := (100,200)
   put(4):at[8]:doIt
      koks
   run: do
      R.fisk(3)
   foo ?+ fisk ?* hest
   V := W ^3
