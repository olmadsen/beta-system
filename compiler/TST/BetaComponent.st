BetaComponent = Coroutine (
   | body |
   init: obj = (
      body := obj.
      body comp: self.
   )
   run = (
      body Do.
   )
   -----------------------

   new: obj = (
      ^self new init: obj.
   )
)

