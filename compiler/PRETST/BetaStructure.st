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
     aBetaStructure isNil ifTrue: [^0].
     ^ (theClass = aBetaStructure theClass) ifTrue: [^1] ifFalse: [^0].
   )
   <> aBetaStructure = (
     (aBetaStructure isNil ) ifTrue: [^1].
     (theClass <> aBetaStructure theClass) ifTrue: [^1] ifFalse: [^0]
   )
   <= aBetaStructure = (
     aBetaStructure isNil ifTrue: [^0].
     ^ ((self theClass = aBetaStructure theClass) 
         || (self theClass < aBetaStructure theClass))ifTrue: [^1] ifFalse: [^0]
   )
   >= aBetaStructure = (
     aBetaStructure isNil ifTrue: [^0].
     ^ ((self theClass = aBetaStructure theClass) 
         || (aBetaStructure theClass < self theClass))ifTrue: [^1] ifFalse: [^0]
   )
   < aBetaStructure = (
     aBetaStructure isNil ifTrue: [^0].
     ^ (theClass < aBetaStructure theClass) ifTrue: [^1] ifFalse: [^0]
   )
   > aBetaStructure = (
     aBetaStructure isNil ifTrue: [^0].
     ^ ((aBetaStructure theClass) < theClass) ifTrue: [^1] ifFalse: [^0]
   )
   -----------------------

   new: org class: class= (
      ^self new init: org class: class.
   )

   new: class origin: org= (
      ^self new init: org class: class.
   )
)

