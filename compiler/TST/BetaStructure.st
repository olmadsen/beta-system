BetaStructure = Object (
   | theClass origin |
   init: org class: class = (
      theClass := class.
      origin := org.
      ^self.
   )
   class = ( ^class. )
   origin = ( ^origin. )
   create = (
      ^theClass new: origin.
   )
   = aBetaStructure = (
     ^ theClass = aBetaStructure class.
   )
   <> aBetaStructure = (
     
   )
   <= aBetaStructure = (
     
   )
   >= aBetaStructure = (
     
   )
   < aBetaStructure = (
     
   )
   > aBetaStructure = (
     
   )
   -----------------------

   new: org class: class= (
      ^self new init: org class: class.
   )

   new: class origin: org= (
      ^self new init: org class: class.
   )
)

