
 class Object 26 1 BETA 2
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 innerP  1
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class BETAworld 1 1 Object 26
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 pushThis 
 saveBETAworld
 mvStack 
 pushThis 
 invoke BETA 2 2 1
 rpop 
 pushThis 
 invoke LIB 10 3 1
 rpop 
 pushThis 
 invoke QBETA 111 5 1
 rpop 
 pushThis 
 invoke BETA 2 2 1
 rpop 
 pushThis 
 invoke LIB 10 3 1
 rpop 
 pushThis 
 invoke QBETA 111 5 1
 rpop 
 pushThis 
 invoke OOPM 21 4 1
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:5 isIndexed:0

 class BETA 2 1 BETAworld 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 invoke ascii 3 2 1
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class ascii 3 1 BETA 2
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 invoke asciiFoo 4 2 1
 rpop 
 pushThis 
 invoke asciiBar 5 3 1
 rpop 
 pushc 10
 pushThis 
 storeg ascii$3 4
 pushc 13
 pushThis 
 storeg ascii$3 5
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 pushc 13
 storeg ascii$3 6
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:6 isIndexed:0

 class asciiFoo 4 1 ascii 3
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class asciiBar 5 1 ascii 3
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class Value 7 0 BETA 2 isValueObj
 rtnEventQ 1
DO:
 L1:
 L2:
 rtnV
 rtn(D)
 end OSDV:0 objSize:0 isIndexed:0

 class char 8 0 BETA 2 isValueObj
 rtnEventQ 1
DO:
 L1:
 L2:
 rtnV
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class universal 9 0 BETA 2 isValueObj
 rtnEventQ 1
DO:
 L1:
 L2:
 rtnV
 rtn(D)
 end OSDV:0 objSize:0 isIndexed:0

 class := 6 1 Value 7
 pushThis 
 storeg Value$7 4
 tstOriginIsNone 
 rstore  1 origin
 store 3 origin.valueOff
 store 2 origin.valueOff
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:4 isIndexed:0

 class LIB 10 1 BETAworld 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 invoke BasicIO 12 3 1
 rpop 
 pushThis 
 invoke Containers 16 4 1
 rpop 
 pushThis 
 invoke StringLib 19 5 1
 rpop 
 pushThis 
 invoke BasicIO 12 3 1
 rpop 
 pushThis 
 invoke Containers 16 4 1
 rpop 
 pushThis 
 invoke StringLib 19 5 1
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:5 isIndexed:0

 class integer 11 0 BETA 2 isValueObj
 rtnEventQ 1
DO:
 L1:
 L2:
 rtnV
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class BasicIO 12 1 LIB 10
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 invoke keyboard 13 2 1
 rpop 
 pushThis 
 invoke screen 14 3 1
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class keyboard 13 1 BasicIO 12
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class screen 14 1 BasicIO 12
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 rpushg screen$14 1
 invoke Lock 15 2 0
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class Lock 15 1 BasicIO 12
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class Containers 16 1 LIB 10
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 invoke OrderedList 17 2 1
 rpop 
 pushThis 
 invoke Set 18 3 1
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class OrderedList 17 1 Containers 16
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class Set 18 1 Containers 16
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class StringLib 19 1 LIB 10
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 saveStringOrigin
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class String 20 1 StringLib 19
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:1

 class OOPM 21 1 BETAworld 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 invoke console 22 3 1
 rpop 
 pushThis 
 invoke ReservationSystem 23 4 1
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:4 isIndexed:0

 class console 22 1 OOPM 21
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class ReservationSystem 23 1 OOPM 21
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 invoke bookingRegister 30 2 1
 rpop 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushText Start:
 invoke print 31 0 0
 rpop 
 pushThis 
 pushThis 
 invoke FlightBooking 105 0 0
 rswap 0
 rstoreg  ReservationSystem$23 3
   ;; vTop(0,0)=[] rTop(-3,0)=[]
 pushText FlightBooking:
 invoke print 31 0 0
 rpop 
 pushThis 
 rpushg ReservationSystem$23 3
 pushThis 
 pushText Joe Smith
 invoke Person 110 0 0
 rswap 0
 rstoreg  ReservationSystem$23 3
   ;; vTop(0,0)=[] rTop(-4,0)=[]
 pushThis 
 rpushg ReservationSystem$23 3
 pushc 111
 storeg ReservationSystem$23 2
 pushText RegisterBooking:
 invoke print 31 0 0
 rpop 
 pushThis 
 rpushg ReservationSystem$23 3
 invoke registerBooking 36 0 0
 rpop 
 pushText confirm:
 invoke print 31 0 0
 rpop 
 pushThis 
 rpushg ReservationSystem$23 3
 invokev 3 0 confirm$39 0
 rpop 
 pushText Send:email:
 invoke print 31 0 0
 rpop 
 pushThis 
 rpushg ReservationSystem$23 3
 rpushg ReservationSystem$23 3
 pushThis 
 rpushg ReservationSystem$23 3
 rpushg ReservationSystem$23 5
 invoke sendEmail 40 0 0
 rpop 
 pushText done!\n
 invoke print 31 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class Container 25 1 Containers 16
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 innerP  7
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class elm#28 28 1 Container$25 25 isVstub
 invoke Object 26 0 0
 pushThis 
 rstoreg   2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 setThisStack 
 pushThis 
 rpushg  2
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class scan 43 1 Container 25
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 innerP  2
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class insert 37 1 Container 25
 pushThis 
 rstoreg  e 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 innerP  2
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class has 44 1 Container 25
 pushThis 
 rstoreg  E 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 innerP  2
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class Boolean 45 0 BETA 2 isValueObj
 rtnEventQ 1
DO:
 L1:
 L2:
 rtnV
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class remove 46 1 Container 25
 pushThis 
 rstoreg  E 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 innerP  2
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class Set 29 2 Set 18
 tstOriginIsNone 
 rstore  2 origin
 -- super Container
 pushThis 
 rpushg Set$18 2
 rpushg Set$18 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 25
DO:
 mvStack 
 L1:
 pushThis 
 innerP  8
 rpopThisObj 
 L2:
 rtnInner  M
 end OSDV:0 objSize:3 isIndexed:0

 class has 47 1 Set 29
 rShiftUp  1
 tstOriginIsNone 
 rstore  1 origin
 -- super has
 pushThis 
 rpushg iOrigin 1
 rShiftDown  1
 pushThis 
 rstoreg  E 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 44
DO:
 mvStack 
 L1:
 pushThis 
 invoke False 61 0 0
 pushg 1 
 storeg has$47 3
 pushThis 
 invoke scan$S$56 56 0 0
 rpop 
 L2:
 rtnInner  M
 end OSDV:0 objSize:3 isIndexed:0

 class False 61 0 BETA 2
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 pushc 0
 storeg False$61 1
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class scan 48 1 Set 29
 tstOriginIsNone 
 rstore  1 origin
 -- super scan
 pushThis 
 rpushg iOrigin 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 43
DO:
 mvStack 
 L1:
 pushThis 
 pushThis 
 rpushg scan$48 1
 rpushg Set$29 3
 rswap 0
 rstoreg  scan$48 3
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 pushThis 
 invoke Loop 49 0 0
 rpop 
 L2:
 rtnInner  M
 end OSDV:0 objSize:3 isIndexed:0

 class link 62 1 Set 29
 pushThis 
 rstoreg  next 3
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 pushThis 
 rstoreg  e 2
   ;; vTop(0,0)=[] rTop(-4,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class := 35 1 Object 26
 pushThis 
 storeg Value$7 2
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class Loop 49 1 scan 48
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushc 117
 vpop
 pushThis 
 rpushg Loop$49 1
 rpushg Loop$49 3
 pushNone 
 rne
 jmpFalse  L4
 L3:
 pushThis 
 invoke $S$51 51 0 0
 rpop 
 jmp L5
 L4:
 pushThis 
 invoke $S$53 53 0 0
 rpop 
 L5:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class $S$51 51 1 Loop 49
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$51$51 1
 rpushg $S$51$51 1
 pushThis 
 rpushg $S$51$51 1
 rpushg $S$51$51 1
 rpushg $S$51$51 3
 rpushg $S$51$51 2
 rswap 0
 rstoreg  scan$48 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 pushThis 
 rpushg $S$51$51 1
 rpushg $S$51$51 1
 innerP  3
 rpopThisObj 
 pushThis 
 rpushg $S$51$51 1
 rpushg $S$51$51 1
 pushThis 
 rpushg $S$51$51 1
 rpushg $S$51$51 1
 rpushg $S$51$51 3
 rpushg $S$51$51 3
 rswap 0
 rstoreg  scan$48 3
   ;; vTop(0,0)=[] rTop(-4,0)=[]
 break  1 1 49 0
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class $S$53 53 1 Loop 49
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$53$53 1
 rpushg $S$53$53 1
 pushThis 
 rpushg $S$53$53 1
 rpushg $S$53$53 1
 rpushg scan$48 3
 rswap 0
 rstoreg  scan$48 3
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class scan$S$56 56 4 has 47
 tstOriginIsNone 
 rstore  4 origin
 -- super scan
 pushThis 
 rpushg has$47 4
 rpushg has$47 1
 tstOriginIsNone 
 rstore  1 origin
 -- super scan
 pushThis 
 rpushg iOrigin 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 43
DO:
 mvStack 
 L1:
 pushc 117
 vpop
 pushThis 
 rpushg scan$S$56$56 2
 pushThis 
 rpushg scan$S$56$56 4
 rpushg has$47 2
 req
 jmpFalse  L4
 L3:
 pushThis 
 invoke $S$58 58 0 0
 rpop 
 jmp L5
 L4:
 pushThis 
 invoke $S$60 60 0 0
 rpop 
 L5:
 L2:
 rtnInner  M
 end OSDV:0 objSize:4 isIndexed:0

 class $S$58 58 1 scan$S$56 56
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$58$58 1
 rpushg $S$58$58 4
 invoke True 63 0 0
 pushg 1 
 storeg has$47 3
 break  2 2 44 1
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class True 63 0 BETA 2
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 pushc 1
 storeg True$63 1
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class $S$60 60 1 scan$S$56 56
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$60$60 1
 rpushg $S$60$60 4
 pushThis 
 rpushg $S$60$60 1
 rpushg $S$60$60 4
 pushg 3 has$47
 storeg has$47 3
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class insert 38 1 Set 29
 rShiftUp  1
 tstOriginIsNone 
 rstore  1 origin
 -- super insert
 pushThis 
 rpushg iOrigin 1
 rShiftDown  1
 pushThis 
 rstoreg  e 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 37
DO:
 mvStack 
 L1:
 pushThis 
 rpushg insert$38 1
 pushThis 
 rpushg insert$38 1
 pushThis 
 rpushg insert$38 2
 pushThis 
 rpushg insert$38 1
 rpushg Set$29 3
 invoke link 62 0 0
 rswap 0
 rstoreg  Set$29 3
   ;; vTop(0,0)=[] rTop(-4,0)=[]
 L2:
 rtnInner  M
 end OSDV:0 objSize:2 isIndexed:0

 class remove 64 1 Set 29
 rShiftUp  1
 tstOriginIsNone 
 rstore  1 origin
 -- super remove
 pushThis 
 rpushg iOrigin 1
 rShiftDown  1
 pushThis 
 rstoreg  E 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 46
DO:
 mvStack 
 L1:
 pushText \nObs! Set:remove:not implemented!\n
 invoke print 31 0 0
 rpop 
 L2:
 rtnInner  M
 end OSDV:0 objSize:2 isIndexed:0

 class print 31 1 String 20
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 invoke @for::to:repeat$S$34 34 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class @for::to:repeat 32 0 BETA 2
 pushThis 
 storeg integer$11 2
 pushThis 
 storeg integer$11 1
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 pushThis 
 pushg 1 @for::to:repeat$32
 storeg @for::to:repeat$32 3
 pushThis 
 invoke $S$65 65 0 0
 rpop 
 pushThis 
 innerP  3
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class repeat#33 33 0 @for::to:repeat$32 32 isVstub
 invoke Object 26 0 0
 pushThis 
 rstoreg   2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 setThisStack 
 pushThis 
 rpushg  2
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class $S$65 65 1 @for::to:repeat 32
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$65$65 1
 pushg 3 $S$65$65
 pushThis 
 rpushg $S$65$65 1
 pushg 2 @for::to:repeat$32
 le
 jmpFalse  L4
 L3:
 pushThis 
 invoke $S$67 67 0 0
 rpop 
 L4:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class $S$67 67 1 $S$65 65
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$67$67 1
 rpushg $S$67$67 1
 invokev 2 0 repeat$33$33 0
 rpop 
 pushThis 
 rpushg $S$67$67 1
 rpushg $S$67$67 1
 pushThis 
 rpushg $S$67$67 1
 rpushg $S$67$67 1
 pushg 3 $S$67$67
 pushc 1
 plus
 storeg @for::to:repeat$32 3
 break  1 1 65 0
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class length 68 1 String 20
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 pushThis 
 rpushg length$68 1
 pushc 0
 xpushg  inx 1 0 1
 storeg length$68 2
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class repeat$S$69 69 1 @for::to:repeat$S$34 34
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg repeat$S$69$69 1
 rpushg repeat$S$69$69 4
 rpushg repeat$S$69$69 1
 pushThis 
 rpushg repeat$S$69$69 1
 pushg 3 @for::to:repeat$S$34$34
 xpushg  inx 1 0 1
 %put 2
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class put 42 0 BETA 2
 pushThis 
 storeg char$8 1
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class @for::to:repeat$S$34 34 4 print 31
 tstOriginIsNone 
 rstore  4 origin
 -- super @for::to:repeat
 pushc 1
 pushThis 
 rpushg print$31 4
 rpushg print$31 1
 invoke length 68 0 0
 pushg 2 
 pushThis 
 storeg integer$11 2
 pushThis 
 storeg integer$11 1
 allocEventQ
 toSuper 32
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:4 isIndexed:0

 class Booking 70 1 ReservationSystem 23
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 invokeVal  Date 71 2
 invokeVal  Date 71 4
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:5 isIndexed:0

 class Date 71 0 ReservationSystem 23 isValueObj
 rtnEventQ 1
DO:
 L1:
 L2:
 rtnV
 rtn(D)
 end OSDV:0 objSize:0 isIndexed:0

 class cancel 72 1 Booking 70
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 invoke if:then:else$S$78 78 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class if:then:else 73 0 QBETA 111
 pushThis 
 storeg Boolean$45 1
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushc 117
 vpop
 pushThis 
 pushg 1 if:then:else$73
 jmpFalse  L4
 L3:
 pushThis 
 invoke $S$76 76 0 0
 rpop 
 jmp L5
 L4:
 pushThis 
 invoke $S$77 77 0 0
 rpop 
 L5:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class th#74 74 0 if:then:else$73 73 isVstub
 invoke Object 26 0 0
 pushThis 
 rstoreg   2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 setThisStack 
 pushThis 
 rpushg  2
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class ep#75 75 0 if:then:else$73 73 isVstub
 invoke Object 26 0 0
 pushThis 
 rstoreg   2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 setThisStack 
 pushThis 
 rpushg  2
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class $S$76 76 1 if:then:else 73
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$76$76 1
 invokev 2 0 th$74$74 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class $S$77 77 1 if:then:else 73
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$77$77 1
 invokev 3 0 ep$75$75 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class toDay 79 1 ReservationSystem 23
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 invokeVal  Date 71 1
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class > 80 1 Date 71
 tstOriginIsNone 
 rstore  1 origin
 store 3 origin.valueOff
 store 2 origin.valueOff
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:4 isIndexed:0

 class th$S$81 81 1 if:then:else$S$78 78
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg th$S$81$81 1
 rpushg th$S$81$81 2
 rpushg th$S$81$81 1
 rpushg th$S$81$81 1
 rpushg th$S$81$81 1
 rpushg th$S$81$81 3
 pushText cancellation not possible
 invoke print 82 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class print 82 1 console 22
 pushThis 
 rstoreg  S 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg print$82 2
 invoke print 31 0 0
 rpop 
 invoke newline 41 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class newline 41 0 BETA 2
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushc 10
 %put 2
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:0 isIndexed:0

 class ep$S$83 83 1 if:then:else$S$78 78
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg ep$S$83$83 1
 rpushg ep$S$83$83 2
 rpushg ep$S$83$83 1
 rpushg ep$S$83$83 1
 rpushg ep$S$83$83 2
 pushThis 
 rpushg ep$S$83$83 1
 rpushg ep$S$83$83 2
 rpushg ep$S$83$83 1
 invoke remove 64 0 0
 rpop 
 pushThis 
 rpushg ep$S$83$83 1
 rpushg ep$S$83$83 2
 innerP  2
 rpopThisObj 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class this 84 1 BETA 2
 pushThis 
 rstoreg  this 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class if:then:else$S$78 78 2 cancel 72
 tstOriginIsNone 
 rstore  2 origin
 -- super if:then:else
 pushThis 
 rpushg cancel$72 2
 rpushg cancel$72 1
 rpushg cancel$72 1
 invoke toDay 79 0 0
 pushc 2
 pushc 0
 pushThis 
 rpushg cancel$72 2
 rpushg cancel$72 1
 pushc 5
 pushc 71
  pushvalue  0
 pushc 1
 invoke > 80 0 0
 pushg 4 
 pushThis 
 storeg Boolean$45 1
 allocEventQ
 toSuper 73
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:2 isIndexed:0

 class confirm 39 1 Booking 70
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg confirm$39 1
 pushText Booking no:
 pushThis 
 rpushg confirm$39 1
 pushg 2 Booking$70
 invoke I2S 94 0 0
 rpushg  2
 pushText :\n
 invoke + 85 0 0
 rpushg  3
 invoke + 85 0 0
 rpushg  3
 rswap 0
 rstoreg  Booking$70 5
   ;; vTop(1,1)=[0/0] rTop(-1,1)=[]
 pushThis 
 innerP  2
 rpopThisObj 
 pushThis 
 rpushg confirm$39 1
 pushThis 
 rpushg confirm$39 1
 rpushg confirm$39 5
 pushText has been confirmed\n
 invoke + 85 0 0
 rpushg  3
 rswap 0
 rstoreg  Booking$70 5
   ;; vTop(1,1)=[0/0] rTop(-2,1)=[]
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class + 85 1 String 20
 pushThis 
 rstoreg  S 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 pushThis 
 rpushg +$85 1
 invoke length 68 0 0
 pushg 2 
 storeg +$85 4
 pushThis 
 invoke $S$86 86 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:4 isIndexed:0

 class $S$86 86 1 + 85
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 pushThis 
 rpushg $S$86$86 1
 pushg 4 $S$86$86
 pushThis 
 rpushg $S$86$86 1
 rpushg $S$86$86 2
 invoke length 68 0 0
 pushg 2 
 plus
 pushThis 
 pushc 1
 allocIndexed $S$86$86 87 1 0
 pushThis 
 rstoreg  $S$86$86 4
   ;; vTop(2,2)=[0/0,0/0] rTop(-4,0)=[]
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 invoke @for::to:repeat$S$89 89 0 0
 rpop 
 pushThis 
 invoke @for::to:repeat$S$90 90 0 0
 rpop 
 pushThis 
 rpushg $S$86$86 1
 pushThis 
 rpushg $S$86$86 4
 %asString 118
 rswap 0
 rstoreg  +$85 3
   ;; vTop(2,2)=[0/0,0/0] rTop(-8,0)=[]
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:4 isIndexed:0

 class Indexed 87 0 BETA 2
 pushThis 
 storeg integer$11 1
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:1

 class elm#88 88 0 Indexed$87 87 isVstub
 invoke Object 26 0 0
 pushThis 
 rstoreg   2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 setThisStack 
 pushThis 
 rpushg  2
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class repeat$S$91 91 1 @for::to:repeat$S$89 89
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg repeat$S$91$91 1
 rpushg repeat$S$91$91 4
 pushThis 
 rpushg repeat$S$91$91 1
 rpushg repeat$S$91$91 4
 rpushg repeat$S$91$91 1
 rpushg repeat$S$91$91 1
 pushThis 
 rpushg repeat$S$91$91 1
 pushg 3 @for::to:repeat$S$89$89
 xpushg  inx 1 0 1
 storeg $S$86$86 2
 pushThis 
 rpushg repeat$S$91$91 1
 rpushg repeat$S$91$91 4
 rpushg repeat$S$91$91 4
 pushThis 
 rpushg repeat$S$91$91 1
 rpushg repeat$S$91$91 4
 pushg 2 $S$86$86
 pushThis 
 rpushg repeat$S$91$91 1
 pushg 3 @for::to:repeat$S$89$89
 xstoreg  inx 1 0 1
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class @for::to:repeat$S$89 89 4 $S$86 86
 tstOriginIsNone 
 rstore  4 origin
 -- super @for::to:repeat
 pushc 1
 pushThis 
 rpushg $S$86$86 4
 rpushg $S$86$86 1
 pushg 4 +$85
 pushThis 
 storeg integer$11 2
 pushThis 
 storeg integer$11 1
 allocEventQ
 toSuper 32
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:4 isIndexed:0

 class repeat$S$93 93 1 @for::to:repeat$S$90 90
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 4
 pushThis 
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 4
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 2
 pushThis 
 rpushg repeat$S$93$93 1
 pushg 3 @for::to:repeat$S$90$90
 xpushg  inx 1 0 1
 storeg $S$86$86 2
 pushThis 
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 4
 pushThis 
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 4
 rpushg repeat$S$93$93 1
 pushg 4 repeat$S$93$93
 pushThis 
 rpushg repeat$S$93$93 1
 pushg 3 @for::to:repeat$S$90$90
 plus
 storeg $S$86$86 3
 pushThis 
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 4
 rpushg repeat$S$93$93 4
 pushThis 
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 4
 pushg 2 $S$86$86
 pushThis 
 rpushg repeat$S$93$93 1
 rpushg repeat$S$93$93 4
 pushg 3 $S$86$86
 xstoreg  inx 1 0 1
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class @for::to:repeat$S$90 90 4 $S$86 86
 tstOriginIsNone 
 rstore  4 origin
 -- super @for::to:repeat
 pushc 1
 pushThis 
 rpushg $S$86$86 4
 rpushg $S$86$86 1
 rpushg $S$86$86 2
 invoke length 68 0 0
 pushg 2 
 pushThis 
 storeg integer$11 2
 pushThis 
 storeg integer$11 1
 allocEventQ
 toSuper 32
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:4 isIndexed:0

 class I2S 94 0 StringLib 19
 pushThis 
 storeg integer$11 1
 allocEventQ
 mvStack 
 pushc 20
 pushThis 
 pushc 1
 allocIndexed I2S$94 87 1 0
 pushThis 
 rstoreg  I2S$94 3
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 pushc 20
 pushThis 
 pushc 1
 allocIndexed I2S$94 87 1 0
 pushThis 
 rstoreg  I2S$94 4
   ;; vTop(0,0)=[] rTop(-4,0)=[]
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 pushThis 
 pushg 1 I2S$94
 pushc 0
 lt
 storeg I2S$94 6
 pushThis 
 pushg 6 I2S$94
 jmpFalse  L4
 L3:
 pushThis 
 invoke $S$95 95 0 0
 rpop 
 L4:
 pushThis 
 invoke $S$97 97 0 0
 rpop 
 pushThis 
 invoke @for::to:repeat$S$96 96 0 0
 rpop 
 pushThis 
 pushThis 
 rpushg I2S$94 4
 %asString 118
 rswap 0
 rstoreg  I2S$94 2
   ;; vTop(2,2)=[0/0,0/0] rTop(-11,0)=[]
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:7 isIndexed:0

 class $S$95 95 1 I2S 94
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$95$95 1
 pushc 0
 pushThis 
 rpushg $S$95$95 1
 pushg 1 I2S$94
 minus
 storeg I2S$94 1
 pushThis 
 rpushg $S$95$95 1
 rpushg $S$95$95 3
 pushc 45
 pushc 1
 xstoreg  inx 1 0 1
 pushThis 
 rpushg $S$95$95 1
 pushc 1
 storeg I2S$94 5
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class $S$97 97 1 I2S 94
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg $S$97$97 1
 pushThis 
 rpushg $S$97$97 1
 pushg 5 $S$97$97
 pushc 1
 plus
 storeg I2S$94 5
 pushThis 
 rpushg $S$97$97 1
 rpushg $S$97$97 3
 pushc 48
 pushThis 
 rpushg $S$97$97 1
 pushg 1 $S$97$97
 pushc 10
 modd
 plus
 pushThis 
 rpushg $S$97$97 1
 pushg 5 I2S$94
 xstoreg  inx 1 0 1
 pushThis 
 rpushg $S$97$97 1
 pushThis 
 rpushg $S$97$97 1
 pushg 1 $S$97$97
 pushc 10
 idiv
 storeg I2S$94 1
 pushThis 
 rpushg $S$97$97 1
 pushg 1 $S$97$97
 pushc 0
 gt
 jmpFalse  L4
 L3:
 pushThis 
 invoke $S$99 99 0 0
 rpop 
 L4:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class $S$99 99 1 $S$97 97
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 break  1 1 97 0
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class repeat$S$100 100 1 @for::to:repeat$S$96 96
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg repeat$S$100$100 1
 rpushg repeat$S$100$100 4
 rpushg repeat$S$100$100 4
 pushThis 
 rpushg repeat$S$100$100 1
 rpushg repeat$S$100$100 4
 rpushg repeat$S$100$100 3
 pushThis 
 rpushg repeat$S$100$100 1
 rpushg repeat$S$100$100 4
 pushg 5 repeat$S$100$100
 pushc 1
 pushThis 
 rpushg repeat$S$100$100 1
 pushg 3 @for::to:repeat$S$96$96
 minus
 plus
 xpushg  inx 1 0 1
 pushThis 
 rpushg repeat$S$100$100 1
 pushg 3 @for::to:repeat$S$96$96
 xstoreg  inx 1 0 1
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class @for::to:repeat$S$96 96 4 I2S 94
 tstOriginIsNone 
 rstore  4 origin
 -- super @for::to:repeat
 pushc 1
 pushThis 
 rpushg I2S$94 4
 pushg 5 I2S$94
 pushThis 
 storeg integer$11 2
 pushThis 
 storeg integer$11 1
 allocEventQ
 toSuper 32
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:4 isIndexed:0

 class bookingRegister 30 2 ReservationSystem 23
 tstOriginIsNone 
 rstore  2 origin
 -- super Set
 pushThis 
 rpushg ReservationSystem$23 2
 rpushg OOPM$21 1
 rpushg OOPM$21 1
 rpushg LIB 3
 rpushg Containers 4
 rpushg Set 3
 tstOriginIsNone 
 rstore  2 origin
 -- super Set
 pushThis 
 rpushg Set$18 2
 rpushg Set$18 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 25
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:3 isIndexed:0

 class S#24 24 2 bookingRegister$30 30 isVstub
 rpushg ReservationSystem$23 2
 invoke Booking 70 0 0
 pushThis 
 rstoreg   2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 setThisStack 
 pushThis 
 rpushg  2
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class S#24 24 2 bookingRegister$30 30 isVstub
 rpushg ReservationSystem$23 2
 invoke Booking 70 0 0
 pushThis 
 rstoreg   2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 setThisStack 
 pushThis 
 rpushg  2
 rtn(D)
 end OSDV:0 objSize:3 isIndexed:0

 class TravelBooking 101 1 ReservationSystem 23
 tstOriginIsNone 
 rstore  1 origin
 -- super Booking
 pushThis 
 rpushg ReservationSystem$23 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 invokeVal  Date 71 2
 invokeVal  Date 71 4
 pushThis 
 invokev 4 0 TravelInfo$103 0
 rpop 
 toSuper 70
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:6 isIndexed:0

 class Travel 102 1 ReservationSystem 23
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class TravelInfo 103 2 TravelBooking 101
 tstOriginIsNone 
 rstore  2 origin
 -- super Travel
 pushThis 
 rpushg TravelBooking$101 2
 rpushg TravelBooking$101 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 102
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:4 isIndexed:0

 class confirm 104 1 TravelBooking 101
 tstOriginIsNone 
 rstore  1 origin
 -- super confirm
 pushThis 
 rpushg iOrigin 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 39
DO:
 mvStack 
 L1:
 pushThis 
 rpushg confirm$104 1
 pushThis 
 rpushg confirm$104 1
 rpushg confirm$104 5
 pushText (text special for TravelBooking)
 invoke + 85 0 0
 rpushg  3
 rswap 0
 rstoreg  TravelBooking$101 5
   ;; vTop(0,0)=[] rTop(-1,1)=[]
 L2:
 rtnInner  M
 end OSDV:0 objSize:1 isIndexed:0

 class FlightBooking 105 1 ReservationSystem 23
 tstOriginIsNone 
 rstore  1 origin
 -- super TravelBooking
 pushThis 
 rpushg ReservationSystem$23 1
 tstOriginIsNone 
 rstore  1 origin
 -- super TravelBooking
 pushThis 
 rpushg ReservationSystem$23 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 invokeVal  Date 71 2
 invokeVal  Date 71 4
 pushThis 
 invokev 4 0 TravelInfo$103 0
 rpop 
 toSuper 70
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:6 isIndexed:0

 class TravelInfo 106 2 FlightBooking 105
 tstOriginIsNone 
 rstore  2 origin
 -- super TravelInfo
 pushThis 
 rpushg iOrigin 2
 tstOriginIsNone 
 rstore  2 origin
 -- super TravelInfo
 pushThis 
 rpushg TravelBooking$101 2
 rpushg TravelBooking$101 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 102
DO:
 mvStack 
 L1:
 L2:
 rtnInner  M
 end OSDV:0 objSize:8 isIndexed:0

 class cancel 107 1 FlightBooking 105
 tstOriginIsNone 
 rstore  1 origin
 -- super cancel
 pushThis 
 rpushg iOrigin 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 72
DO:
 mvStack 
 L1:
 pushThis 
 rpushg cancel$107 1
 rpushg cancel$107 6
 rpushg cancel$107 8
 invoke notifyCancellation 108 0 0
 rpop 
 L2:
 rtnInner  M
 end OSDV:0 objSize:1 isIndexed:0

 class notifyCancellation 108 1 Carrier 0
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class confirm 109 1 FlightBooking 105
 tstOriginIsNone 
 rstore  1 origin
 -- super confirm
 pushThis 
 rpushg iOrigin 1
 tstOriginIsNone 
 rstore  1 origin
 -- super confirm
 pushThis 
 rpushg iOrigin 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 toSuper 39
DO:
 mvStack 
 L1:
 pushThis 
 rpushg confirm$109 1
 pushThis 
 rpushg confirm$109 1
 rpushg confirm$109 5
 pushText (text special for FlightBooking)
 invoke + 85 0 0
 rpushg  3
 rswap 0
 rstoreg  FlightBooking$105 5
   ;; vTop(0,0)=[] rTop(-1,1)=[]
 L2:
 rtnInner  M
 end OSDV:0 objSize:1 isIndexed:0

 class Person 110 1 ReservationSystem 23
 pushThis 
 rstoreg  name 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class registerBooking 36 1 Booking 70
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushThis 
 rpushg registerBooking$36 1
 rpushg registerBooking$36 1
 rpushg registerBooking$36 2
 pushThis 
 rpushg registerBooking$36 1
 invoke insert 38 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class sendEmail 40 1 Person 110
 pushThis 
 rstoreg  msg 2
   ;; vTop(0,0)=[] rTop(-2,0)=[]
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 pushText \nEmail: 
 invoke print 31 0 0
 rpop 
 pushThis 
 rpushg sendEmail$40 2
 invoke print 31 0 0
 rpop 
 invoke newline 41 0 0
 rpop 
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class QBETA 111 1 BETAworld 1
 tstOriginIsNone 
 rstore  1 origin
 allocEventQ
 mvStack 
 rtnEventQ 1
DO:
 doEventQ
 mvStack 
 L1:
 L2:
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:0 objSize:1 isIndexed:0

 class main 112 0 Object 0
 L1:
 pushThis 
 invoke BETAworld 1 0 1
 stop
 L2:
 rtn(D)
 end OSDV:0 objSize:2 isIndexed:0

 class EventProcessor 113 0 Object 0
 stop
 end OSDV:0 objSize:1 isIndexed:0

 class ThreadStub 114 0 Object 0
DO:
 call(D)ThreadStub
 stop
 end OSDV:0 objSize:1 isIndexed:0

Class BETAworld descInx:1 objSize:5 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	pushthis 
7:	saveBETAworld
8:	mvStack
allocE: 
9:	pushthis 
10:	invoke 2 2 1
16:	rpop 
17:	pushthis 
18:	invoke 10 3 1
24:	rpop 
25:	pushthis 
26:	invoke 111 5 1
32:	rpop 
33:	pushthis 
34:	invoke 2 2 1
40:	rpop 
41:	pushthis 
42:	invoke 10 3 1
48:	rpop 
49:	pushthis 
50:	invoke 111 5 1
56:	rpop 
57:	pushthis 
58:	invoke 21 4 1
64:	rpop 
65:	rtnEventQ 1
doE: 
67:	doEventQ 
68:	mvStack
69:	setThisStack
70:	pushthis 
71:	rtn D


Class BETA descInx:2 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 3 2 1
14:	rpop 
15:	rtnEventQ 1
doE: 
17:	doEventQ 
18:	mvStack
19:	setThisStack
20:	pushthis 
21:	rtn D


Class ascii descInx:3 objSize:6 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 4 2 1
14:	rpop 
15:	pushthis 
16:	invoke 5 3 1
22:	rpop 
23:	pushc 10
25:	pushthis 
26:	storeg 4
28:	pushc 13
30:	pushthis 
31:	storeg 5
33:	rtnEventQ 1
doE: 
35:	doEventQ 
36:	mvStack
37:	pushthis 
38:	pushc 13
40:	storeg 6
42:	setThisStack
43:	pushthis 
44:	rtn D


Class asciiFoo descInx:4 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class asciiBar descInx:5 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class := descInx:6 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 4
4:	tstOriginNone 
5:	rstore 1
7:	store 3
9:	store 2
11:	allocEventQ 0
13:	mvStack
allocE: 
14:	rtnEventQ 1
doE: 
16:	doEventQ 
17:	mvStack
18:	setThisStack
19:	pushthis 
20:	rtn D


Class Value descInx:7 objSize:0 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
1:	rtnEventQ 1
doE: 
3:	rtnV
4:	rtn D


Class char descInx:8 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
1:	rtnEventQ 1
doE: 
3:	rtnV
4:	rtn D


Class universal descInx:9 objSize:0 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
1:	rtnEventQ 1
doE: 
3:	rtnV
4:	rtn D


Class LIB descInx:10 objSize:5 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 12 3 1
14:	rpop 
15:	pushthis 
16:	invoke 16 4 1
22:	rpop 
23:	pushthis 
24:	invoke 19 5 1
30:	rpop 
31:	pushthis 
32:	invoke 12 3 1
38:	rpop 
39:	pushthis 
40:	invoke 16 4 1
46:	rpop 
47:	pushthis 
48:	invoke 19 5 1
54:	rpop 
55:	rtnEventQ 1
doE: 
57:	doEventQ 
58:	mvStack
59:	setThisStack
60:	pushthis 
61:	rtn D


Class integer descInx:11 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
1:	rtnEventQ 1
doE: 
3:	rtnV
4:	rtn D


Class BasicIO descInx:12 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 13 2 1
14:	rpop 
15:	pushthis 
16:	invoke 14 3 1
22:	rpop 
23:	rtnEventQ 1
doE: 
25:	doEventQ 
26:	mvStack
27:	setThisStack
28:	pushthis 
29:	rtn D


Class keyboard descInx:13 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class screen descInx:14 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	rpushg 1
10:	invoke 15 2 0
16:	rpop 
17:	rtnEventQ 1
doE: 
19:	doEventQ 
20:	mvStack
21:	setThisStack
22:	pushthis 
23:	rtn D


Class Lock descInx:15 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Containers descInx:16 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 17 2 1
14:	rpop 
15:	pushthis 
16:	invoke 18 3 1
22:	rpop 
23:	rtnEventQ 1
doE: 
25:	doEventQ 
26:	mvStack
27:	setThisStack
28:	pushthis 
29:	rtn D


Class OrderedList descInx:17 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Set descInx:18 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class StringLib descInx:19 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	saveStringOrigin
7:	mvStack
allocE: 
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	setThisStack
13:	pushthis 
14:	rtn D


Class String descInx:20 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class OOPM descInx:21 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 22 3 1
14:	rpop 
15:	pushthis 
16:	invoke 23 4 1
22:	rpop 
23:	rtnEventQ 1
doE: 
25:	doEventQ 
26:	mvStack
27:	setThisStack
28:	pushthis 
29:	rtn D


Class console descInx:22 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class ReservationSystem descInx:23 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 30 2 1
14:	rpop 
15:	rtnEventQ 1
doE: 
17:	doEventQ 
18:	mvStack
19:	pushText 1
21:	invoke 31 0 0
27:	rpop 
28:	pushthis 
29:	pushthis 
30:	invoke 105 0 0
36:	rswap 0
38:	rstoreg 3
40:	pushText 8
42:	invoke 31 0 0
48:	rpop 
49:	pushthis 
50:	rpushg 3
52:	pushthis 
53:	pushText 23
55:	invoke 110 0 0
61:	rswap 0
63:	rstoreg 3
65:	pushthis 
66:	rpushg 3
68:	pushc 111
70:	storeg 2
72:	pushText 33
74:	invoke 31 0 0
80:	rpop 
81:	pushthis 
82:	rpushg 3
84:	invoke 36 0 0
90:	rpop 
91:	pushText 50
93:	invoke 31 0 0
99:	rpop 
100:	pushthis 
101:	rpushg 3
103:	invokev 3 0 0
107:	rpop 
108:	pushText 59
110:	invoke 31 0 0
116:	rpop 
117:	pushthis 
118:	rpushg 3
120:	rpushg 3
122:	pushthis 
123:	rpushg 3
125:	rpushg 5
127:	invoke 40 0 0
133:	rpop 
134:	pushText 71
136:	invoke 31 0 0
142:	rpop 
143:	setThisStack
144:	pushthis 
145:	rtn D


Class S#24 descInx:24 objSize:3 originOff: 2 visibility: 0
storeOrgAndArgsE:
1:	rpushg 2
3:	invoke 70 0 0
9:	pushthis 
10:	rstoreg 2
12:	setThisStack
13:	pushthis 
14:	rpushg 2
16:	rtn D


Class Container descInx:25 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	innerP 7
14:	rpopThisObj
15:	setThisStack
16:	pushthis 
17:	rtn D


Class Object descInx:26 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	innerP 1
14:	rpopThisObj
15:	setThisStack
16:	pushthis 
17:	rtn D


Class elm#28 descInx:28 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	invoke 26 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


Class Set descInx:29 objSize:3 originOff: 2 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 2
4:	pushthis 
5:	rpushg 2
7:	rpushg 1
9:	tstOriginNone 
10:	rstore 1
12:	allocEventQ 0
allocE: 
14:	toSuper 25
doE: 
17:	mvStack
18:	pushthis 
19:	innerP 8
21:	rpopThisObj
22:	rtnInner


Class bookingRegister descInx:30 objSize:3 originOff: 2 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 2
4:	pushthis 
5:	rpushg 2
7:	rpushg 1
9:	rpushg 1
11:	rpushg 3
13:	rpushg 4
15:	rpushg 3
17:	tstOriginNone 
18:	rstore 2
20:	pushthis 
21:	rpushg 2
23:	rpushg 1
25:	tstOriginNone 
26:	rstore 1
28:	allocEventQ 0
allocE: 
30:	toSuper 25
doE: 
33:	mvStack
34:	rtnInner


Class print descInx:31 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	invoke 34 0 0
18:	rpop 
19:	setThisStack
20:	pushthis 
21:	rtn D


Class @for::to:repeat descInx:32 objSize:3 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	pushthis 
16:	pushg 1
18:	storeg 3
20:	pushthis 
21:	invoke 65 0 0
27:	rpop 
28:	pushthis 
29:	innerP 3
31:	rpopThisObj
32:	setThisStack
33:	pushthis 
34:	rtn D


Class repeat#33 descInx:33 objSize:3 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	invoke 26 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


Class @for::to:repeat$S$34 descInx:34 objSize:4 originOff: 4 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	rpushg 1
11:	invoke 68 0 0
17:	pushg 2
19:	pushthis 
20:	storeg 2
22:	pushthis 
23:	storeg 1
25:	allocEventQ 0
allocE: 
27:	toSuper 32
doE: 
30:	mvStack
31:	rtnInner


Class := descInx:35 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	setThisStack
15:	pushthis 
16:	rtn D


Class registerBooking descInx:36 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	rpushg 2
18:	pushthis 
19:	rpushg 1
21:	invoke 38 0 0
27:	rpop 
28:	setThisStack
29:	pushthis 
30:	rtn D


Class insert descInx:37 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	innerP 2
17:	rpopThisObj
18:	setThisStack
19:	pushthis 
20:	rtn D


Class insert descInx:38 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	rshiftup 1
3:	tstOriginNone 
4:	rstore 1
6:	pushthis 
7:	rpushg 1
9:	rshiftdown 1
11:	pushthis 
12:	rstoreg 2
14:	tstOriginNone 
15:	rstore 1
17:	allocEventQ 0
allocE: 
19:	toSuper 37
doE: 
22:	mvStack
23:	pushthis 
24:	rpushg 1
26:	pushthis 
27:	rpushg 1
29:	pushthis 
30:	rpushg 2
32:	pushthis 
33:	rpushg 1
35:	rpushg 3
37:	invoke 62 0 0
43:	rswap 0
45:	rstoreg 3
47:	rtnInner


Class confirm descInx:39 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushText 1
16:	pushthis 
17:	rpushg 1
19:	pushg 2
21:	invoke 94 0 0
27:	rpushg 2
29:	pushText 13
31:	invoke 85 0 0
37:	rpushg 3
39:	invoke 85 0 0
45:	rpushg 3
47:	rswap 0
49:	rstoreg 5
51:	pushthis 
52:	innerP 2
54:	rpopThisObj
55:	pushthis 
56:	rpushg 1
58:	pushthis 
59:	rpushg 1
61:	rpushg 5
63:	pushText 16
65:	invoke 85 0 0
71:	rpushg 3
73:	rswap 0
75:	rstoreg 5
77:	setThisStack
78:	pushthis 
79:	rtn D


Class sendEmail descInx:40 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushText 1
16:	invoke 31 0 0
22:	rpop 
23:	pushthis 
24:	rpushg 2
26:	invoke 31 0 0
32:	rpop 
33:	invoke 41 0 0
39:	rpop 
40:	setThisStack
41:	pushthis 
42:	rtn D


Class newline descInx:41 objSize:0 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	allocEventQ 0
3:	mvStack
allocE: 
4:	rtnEventQ 1
doE: 
6:	doEventQ 
7:	mvStack
8:	pushc 10
10:	%prim put 2
12:	setThisStack
13:	pushthis 
14:	rtn D


Class put descInx:42 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class scan descInx:43 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	innerP 2
14:	rpopThisObj
15:	setThisStack
16:	pushthis 
17:	rtn D


Class has descInx:44 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	innerP 2
17:	rpopThisObj
18:	setThisStack
19:	pushthis 
20:	rtn D


Class Boolean descInx:45 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
1:	rtnEventQ 1
doE: 
3:	rtnV
4:	rtn D


Class remove descInx:46 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	innerP 2
17:	rpopThisObj
18:	setThisStack
19:	pushthis 
20:	rtn D


Class has descInx:47 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	rshiftup 1
3:	tstOriginNone 
4:	rstore 1
6:	pushthis 
7:	rpushg 1
9:	rshiftdown 1
11:	pushthis 
12:	rstoreg 2
14:	tstOriginNone 
15:	rstore 1
17:	allocEventQ 0
allocE: 
19:	toSuper 44
doE: 
22:	mvStack
23:	pushthis 
24:	invoke 61 0 0
30:	pushg 1
32:	storeg 3
34:	pushthis 
35:	invoke 56 0 0
41:	rpop 
42:	rtnInner


Class scan descInx:48 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
allocE: 
12:	toSuper 43
doE: 
15:	mvStack
16:	pushthis 
17:	pushthis 
18:	rpushg 1
20:	rpushg 3
22:	rswap 0
24:	rstoreg 3
26:	pushthis 
27:	invoke 49 0 0
33:	rpop 
34:	rtnInner


Class Loop descInx:49 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 117
13:	vpop 
14:	pushthis 
15:	rpushg 1
17:	rpushg 3
19:	pushNone 
20:	57
21:	jmpFalse 35
24:	pushthis 
25:	invoke 51 0 0
31:	rpop 
32:	jmp 43
35:	pushthis 
36:	invoke 53 0 0
42:	rpop 
43:	setThisStack
44:	pushthis 
45:	rtn D


Class $S$51 descInx:51 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	pushthis 
17:	rpushg 1
19:	rpushg 1
21:	rpushg 3
23:	rpushg 2
25:	rswap 0
27:	rstoreg 2
29:	pushthis 
30:	rpushg 1
32:	rpushg 1
34:	innerP 3
36:	rpopThisObj
37:	pushthis 
38:	rpushg 1
40:	rpushg 1
42:	pushthis 
43:	rpushg 1
45:	rpushg 1
47:	rpushg 3
49:	rpushg 3
51:	rswap 0
53:	rstoreg 3
55:	break 1 1 49 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class $S$53 descInx:53 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	pushthis 
17:	rpushg 1
19:	rpushg 1
21:	rpushg 3
23:	rswap 0
25:	rstoreg 3
27:	setThisStack
28:	pushthis 
29:	rtn D


Class scan$S$56 descInx:56 objSize:4 originOff: 4 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushthis 
5:	rpushg 4
7:	rpushg 1
9:	tstOriginNone 
10:	rstore 1
12:	pushthis 
13:	rpushg 1
15:	tstOriginNone 
16:	rstore 1
18:	allocEventQ 0
allocE: 
20:	toSuper 43
doE: 
23:	mvStack
24:	pushc 117
26:	vpop 
27:	pushthis 
28:	rpushg 2
30:	pushthis 
31:	rpushg 4
33:	rpushg 2
35:	req 
36:	jmpFalse 50
39:	pushthis 
40:	invoke 58 0 0
46:	rpop 
47:	jmp 58
50:	pushthis 
51:	invoke 60 0 0
57:	rpop 
58:	rtnInner


Class $S$58 descInx:58 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	invoke 63 0 0
22:	pushg 1
24:	storeg 3
26:	break 2 2 44 1
33:	setThisStack
34:	pushthis 
35:	rtn D


Class $S$60 descInx:60 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	pushthis 
17:	rpushg 1
19:	rpushg 4
21:	pushg 3
23:	storeg 3
25:	setThisStack
26:	pushthis 
27:	rtn D


Class False descInx:61 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	allocEventQ 0
3:	mvStack
allocE: 
4:	rtnEventQ 1
doE: 
6:	doEventQ 
7:	mvStack
8:	pushthis 
9:	pushc 0
11:	storeg 1
13:	setThisStack
14:	pushthis 
15:	rtn D


Class link descInx:62 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 3
4:	pushthis 
5:	rstoreg 2
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
12:	mvStack
allocE: 
13:	rtnEventQ 1
doE: 
15:	doEventQ 
16:	mvStack
17:	setThisStack
18:	pushthis 
19:	rtn D


Class True descInx:63 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	allocEventQ 0
3:	mvStack
allocE: 
4:	rtnEventQ 1
doE: 
6:	doEventQ 
7:	mvStack
8:	pushthis 
9:	pushc 1
11:	storeg 1
13:	setThisStack
14:	pushthis 
15:	rtn D


Class remove descInx:64 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	rshiftup 1
3:	tstOriginNone 
4:	rstore 1
6:	pushthis 
7:	rpushg 1
9:	rshiftdown 1
11:	pushthis 
12:	rstoreg 2
14:	tstOriginNone 
15:	rstore 1
17:	allocEventQ 0
allocE: 
19:	toSuper 46
doE: 
22:	mvStack
23:	pushText 5
25:	invoke 31 0 0
31:	rpop 
32:	rtnInner


Class $S$65 descInx:65 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushg 3
16:	pushthis 
17:	rpushg 1
19:	pushg 2
21:	le
22:	jmpFalse 33
25:	pushthis 
26:	invoke 67 0 0
32:	rpop 
33:	setThisStack
34:	pushthis 
35:	rtn D


Class $S$67 descInx:67 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	invokev 2 0 0
20:	rpop 
21:	pushthis 
22:	rpushg 1
24:	rpushg 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	pushg 3
33:	pushc 1
35:	+
36:	storeg 3
38:	break 1 1 65 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class length descInx:68 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	pushthis 
13:	rpushg 1
15:	pushc 0
17:	xpushg 1 0 1
21:	storeg 2
23:	setThisStack
24:	pushthis 
25:	rtn D


Class repeat$S$69 descInx:69 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	rpushg 1
18:	pushthis 
19:	rpushg 1
21:	pushg 3
23:	xpushg 1 0 1
27:	%prim put 2
29:	setThisStack
30:	pushthis 
31:	rtn D


Class Booking descInx:70 objSize:5 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	invokeVal 71 2
12:	invokeVal 71 4
17:	rtnEventQ 1
doE: 
19:	doEventQ 
20:	mvStack
21:	setThisStack
22:	pushthis 
23:	rtn D


Class Date descInx:71 objSize:0 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
1:	rtnEventQ 1
doE: 
3:	rtnV
4:	rtn D


Class cancel descInx:72 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	invoke 78 0 0
18:	rpop 
19:	setThisStack
20:	pushthis 
21:	rtn D


Class if:then:else descInx:73 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 117
13:	vpop 
14:	pushthis 
15:	pushg 1
17:	jmpFalse 31
20:	pushthis 
21:	invoke 76 0 0
27:	rpop 
28:	jmp 39
31:	pushthis 
32:	invoke 77 0 0
38:	rpop 
39:	setThisStack
40:	pushthis 
41:	rtn D


Class th#74 descInx:74 objSize:3 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	invoke 26 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


Class ep#75 descInx:75 objSize:3 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	invoke 26 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


Class $S$76 descInx:76 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	invokev 2 0 0
18:	rpop 
19:	setThisStack
20:	pushthis 
21:	rtn D


Class $S$77 descInx:77 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	invokev 3 0 0
18:	rpop 
19:	setThisStack
20:	pushthis 
21:	rtn D


Class if:then:else$S$78 descInx:78 objSize:2 originOff: 2 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 2
4:	pushthis 
5:	rpushg 2
7:	rpushg 1
9:	rpushg 1
11:	invoke 79 0 0
17:	pushc 2
19:	pushc 0
21:	pushthis 
22:	rpushg 2
24:	rpushg 1
26:	pushc 5
28:	pushc 71
30:	pushValue 0
32:	pushc 1
34:	invoke 80 0 0
40:	pushg 4
42:	pushthis 
43:	storeg 1
45:	allocEventQ 0
allocE: 
47:	toSuper 73
doE: 
50:	mvStack
51:	rtnInner


Class toDay descInx:79 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	invokeVal 71 1
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	setThisStack
17:	pushthis 
18:	rtn D


Class > descInx:80 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	store 3
6:	store 2
8:	allocEventQ 0
10:	mvStack
allocE: 
11:	rtnEventQ 1
doE: 
13:	doEventQ 
14:	mvStack
15:	setThisStack
16:	pushthis 
17:	rtn D


Class th$S$81 descInx:81 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 2
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	rpushg 3
24:	pushText 1
26:	invoke 82 0 0
32:	rpop 
33:	setThisStack
34:	pushthis 
35:	rtn D


Class print descInx:82 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 2
17:	invoke 31 0 0
23:	rpop 
24:	invoke 41 0 0
30:	rpop 
31:	setThisStack
32:	pushthis 
33:	rtn D


Class ep$S$83 descInx:83 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 2
16:	rpushg 1
18:	rpushg 1
20:	rpushg 2
22:	pushthis 
23:	rpushg 1
25:	rpushg 2
27:	rpushg 1
29:	invoke 64 0 0
35:	rpop 
36:	pushthis 
37:	rpushg 1
39:	rpushg 2
41:	innerP 2
43:	rpopThisObj
44:	setThisStack
45:	pushthis 
46:	rtn D


Class this descInx:84 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	setThisStack
15:	pushthis 
16:	rtn D


Class + descInx:85 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	pushthis 
16:	rpushg 1
18:	invoke 68 0 0
24:	pushg 2
26:	storeg 4
28:	pushthis 
29:	invoke 86 0 0
35:	rpop 
36:	setThisStack
37:	pushthis 
38:	rtn D


Class $S$86 descInx:86 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	pushthis 
8:	rpushg 1
10:	pushg 4
12:	pushthis 
13:	rpushg 1
15:	rpushg 2
17:	invoke 68 0 0
23:	pushg 2
25:	+
26:	pushthis 
27:	pushc 1
29:	allocIndexed 87 1 0 
34:	pushthis 
35:	rstoreg 4
37:	rtnEventQ 1
doE: 
39:	doEventQ 
40:	mvStack
41:	pushthis 
42:	invoke 89 0 0
48:	rpop 
49:	pushthis 
50:	invoke 90 0 0
56:	rpop 
57:	pushthis 
58:	rpushg 1
60:	pushthis 
61:	rpushg 4
63:	%prim asString 118
65:	rswap 0
67:	rstoreg 3
69:	setThisStack
70:	pushthis 
71:	rtn D


Class Indexed descInx:87 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class elm#88 descInx:88 objSize:3 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	invoke 26 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


Class @for::to:repeat$S$89 descInx:89 objSize:4 originOff: 4 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	rpushg 1
11:	pushg 4
13:	pushthis 
14:	storeg 2
16:	pushthis 
17:	storeg 1
19:	allocEventQ 0
allocE: 
21:	toSuper 32
doE: 
24:	mvStack
25:	rtnInner


Class @for::to:repeat$S$90 descInx:90 objSize:4 originOff: 4 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	rpushg 1
11:	rpushg 2
13:	invoke 68 0 0
19:	pushg 2
21:	pushthis 
22:	storeg 2
24:	pushthis 
25:	storeg 1
27:	allocEventQ 0
allocE: 
29:	toSuper 32
doE: 
32:	mvStack
33:	rtnInner


Class repeat$S$91 descInx:91 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	pushthis 
17:	rpushg 1
19:	rpushg 4
21:	rpushg 1
23:	rpushg 1
25:	pushthis 
26:	rpushg 1
28:	pushg 3
30:	xpushg 1 0 1
34:	storeg 2
36:	pushthis 
37:	rpushg 1
39:	rpushg 4
41:	rpushg 4
43:	pushthis 
44:	rpushg 1
46:	rpushg 4
48:	pushg 2
50:	pushthis 
51:	rpushg 1
53:	pushg 3
55:	xstoreg 1 0 1 
59:	setThisStack
60:	pushthis 
61:	rtn D


Class repeat$S$93 descInx:93 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	pushthis 
17:	rpushg 1
19:	rpushg 4
21:	rpushg 1
23:	rpushg 2
25:	pushthis 
26:	rpushg 1
28:	pushg 3
30:	xpushg 1 0 1
34:	storeg 2
36:	pushthis 
37:	rpushg 1
39:	rpushg 4
41:	pushthis 
42:	rpushg 1
44:	rpushg 4
46:	rpushg 1
48:	pushg 4
50:	pushthis 
51:	rpushg 1
53:	pushg 3
55:	+
56:	storeg 3
58:	pushthis 
59:	rpushg 1
61:	rpushg 4
63:	rpushg 4
65:	pushthis 
66:	rpushg 1
68:	rpushg 4
70:	pushg 2
72:	pushthis 
73:	rpushg 1
75:	rpushg 4
77:	pushg 3
79:	xstoreg 1 0 1 
83:	setThisStack
84:	pushthis 
85:	rtn D


Class I2S descInx:94 objSize:7 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	pushc 20
9:	pushthis 
10:	pushc 1
12:	allocIndexed 87 1 0 
17:	pushthis 
18:	rstoreg 3
20:	pushc 20
22:	pushthis 
23:	pushc 1
25:	allocIndexed 87 1 0 
30:	pushthis 
31:	rstoreg 4
33:	rtnEventQ 1
doE: 
35:	doEventQ 
36:	mvStack
37:	pushthis 
38:	pushthis 
39:	pushg 1
41:	pushc 0
43:	lt
44:	storeg 6
46:	pushthis 
47:	pushg 6
49:	jmpFalse 60
52:	pushthis 
53:	invoke 95 0 0
59:	rpop 
60:	pushthis 
61:	invoke 97 0 0
67:	rpop 
68:	pushthis 
69:	invoke 96 0 0
75:	rpop 
76:	pushthis 
77:	pushthis 
78:	rpushg 4
80:	%prim asString 118
82:	rswap 0
84:	rstoreg 2
86:	setThisStack
87:	pushthis 
88:	rtn D


Class $S$95 descInx:95 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushc 0
16:	pushthis 
17:	rpushg 1
19:	pushg 1
21:	-
22:	storeg 1
24:	pushthis 
25:	rpushg 1
27:	rpushg 3
29:	pushc 45
31:	pushc 1
33:	xstoreg 1 0 1 
37:	pushthis 
38:	rpushg 1
40:	pushc 1
42:	storeg 5
44:	setThisStack
45:	pushthis 
46:	rtn D


Class @for::to:repeat$S$96 descInx:96 objSize:4 originOff: 4 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	pushg 5
11:	pushthis 
12:	storeg 2
14:	pushthis 
15:	storeg 1
17:	allocEventQ 0
allocE: 
19:	toSuper 32
doE: 
22:	mvStack
23:	rtnInner


Class $S$97 descInx:97 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushthis 
15:	rpushg 1
17:	pushg 5
19:	pushc 1
21:	+
22:	storeg 5
24:	pushthis 
25:	rpushg 1
27:	rpushg 3
29:	pushc 48
31:	pushthis 
32:	rpushg 1
34:	pushg 1
36:	pushc 10
38:	modd
39:	+
40:	pushthis 
41:	rpushg 1
43:	pushg 5
45:	xstoreg 1 0 1 
49:	pushthis 
50:	rpushg 1
52:	pushthis 
53:	rpushg 1
55:	pushg 1
57:	pushc 10
59:	idiv
60:	storeg 1
62:	pushthis 
63:	rpushg 1
65:	pushg 1
67:	pushc 0
69:	gt 
70:	jmpFalse 81
73:	pushthis 
74:	invoke 99 0 0
80:	rpop 
81:	setThisStack
82:	pushthis 
83:	rtn D


Class $S$99 descInx:99 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	break 1 1 97 0
18:	setThisStack
19:	pushthis 
20:	rtn D


Class repeat$S$100 descInx:100 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	rpushg 4
18:	pushthis 
19:	rpushg 1
21:	rpushg 4
23:	rpushg 3
25:	pushthis 
26:	rpushg 1
28:	rpushg 4
30:	pushg 5
32:	pushc 1
34:	pushthis 
35:	rpushg 1
37:	pushg 3
39:	-
40:	+
41:	xpushg 1 0 1
45:	pushthis 
46:	rpushg 1
48:	pushg 3
50:	xstoreg 1 0 1 
54:	setThisStack
55:	pushthis 
56:	rtn D


Class TravelBooking descInx:101 objSize:6 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
allocE: 
12:	invokeVal 71 2
17:	invokeVal 71 4
22:	pushthis 
23:	invokev 4 0 0
27:	rpop 
28:	toSuper 70
doE: 
31:	mvStack
32:	rtnInner


Class Travel descInx:102 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class TravelInfo descInx:103 objSize:4 originOff: 2 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 2
4:	pushthis 
5:	rpushg 2
7:	rpushg 1
9:	tstOriginNone 
10:	rstore 1
12:	allocEventQ 0
allocE: 
14:	toSuper 102
doE: 
17:	mvStack
18:	rtnInner


Class confirm descInx:104 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
allocE: 
12:	toSuper 39
doE: 
15:	mvStack
16:	pushthis 
17:	rpushg 1
19:	pushthis 
20:	rpushg 1
22:	rpushg 5
24:	pushText 58
26:	invoke 85 0 0
32:	rpushg 3
34:	rswap 0
36:	rstoreg 5
38:	rtnInner


Class FlightBooking descInx:105 objSize:6 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	pushthis 
11:	rpushg 1
13:	tstOriginNone 
14:	rstore 1
16:	allocEventQ 0
allocE: 
18:	invokeVal 71 2
23:	invokeVal 71 4
28:	pushthis 
29:	invokev 4 0 0
33:	rpop 
34:	toSuper 70
doE: 
37:	mvStack
38:	rtnInner


Class TravelInfo descInx:106 objSize:8 originOff: 2 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 2
4:	pushthis 
5:	rpushg 2
7:	tstOriginNone 
8:	rstore 2
10:	pushthis 
11:	rpushg 2
13:	rpushg 1
15:	tstOriginNone 
16:	rstore 1
18:	allocEventQ 0
allocE: 
20:	toSuper 102
doE: 
23:	mvStack
24:	rtnInner


Class cancel descInx:107 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
allocE: 
12:	toSuper 72
doE: 
15:	mvStack
16:	pushthis 
17:	rpushg 1
19:	rpushg 6
21:	rpushg 8
23:	invoke 108 0 0
29:	rpop 
30:	rtnInner


Class notifyCancellation descInx:108 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class confirm descInx:109 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	pushthis 
11:	rpushg 1
13:	tstOriginNone 
14:	rstore 1
16:	allocEventQ 0
allocE: 
18:	toSuper 39
doE: 
21:	mvStack
22:	pushthis 
23:	rpushg 1
25:	pushthis 
26:	rpushg 1
28:	rpushg 5
30:	pushText 147
32:	invoke 85 0 0
38:	rpushg 3
40:	rswap 0
42:	rstoreg 5
44:	rtnInner


Class Person descInx:110 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	setThisStack
15:	pushthis 
16:	rtn D


Class QBETA descInx:111 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnEventQ 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


Class main descInx:112 objSize:2 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	invoke 1 0 1
8:	stop 
9:	rtn D


Class EventProcessor descInx:113 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	stop 


Class ThreadStub descInx:114 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
doE: 
1:	call D
3:	stop 

