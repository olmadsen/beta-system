BetaStructure = Object (
   | theClass origin |
   init: org class: class = (
      theClass := class.
      origin := org.
      ^self.
   )
   create = (
      theClass new: origin
   )
   = aBetaStructure = (
     
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

