BetaStructure = Object (
   | theClass origin |
   init: org class: class = (
      theClass := class.
      origin := org.
      ^self.
   )
   theClass = ( ^theClass. )
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
     ^ (self = aBetaStructure) || (self < aBetaStructure)
   )
   >= aBetaStructure = (
     
   )
   < aBetaStructure = (
     ^ (theClass < aBetaStructure theClass) ifTrue:[^1]ifFalse:[0].
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

