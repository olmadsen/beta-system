

CLASS Object$44 dNo:44 topDno:44 orgOff:1 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID Object
 --  %basic 64
 --  %public
 --  =  : 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %ID Object
 --  %basic 64
 --  %public
 --  =  : 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "inner(Object)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "inner(Object)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(Object)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(Object)" 0 0 
-- loadOriginII: "inner(Object)" 
-- beforedoinvoke true 
-- doInvoke: "inner(Object)" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(Object)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(Object)" rec: none 
11:	 pushThis 
12:	 innerP  1
14:	 rpopThisObj 
L2:
15:	 setThisStack 
16:	 pushThis 
17:	 rtn D
19:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:0 V 2:55 V 3:0 V 4:0 

CLASS BETAworld$1 dNo:1 topDno:1 orgOff:1 orgId:Object$44 orgDno:44

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "BETAworld"
 --  %modules BETA, LIB, LIB.StringLib, LIB.BasicIo
 --  error: 
 --     %basic 999
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %id "BETAworld"
 --  %modules BETA, LIB, LIB.StringLib, LIB.BasicIo
 --  error: 
 --     %basic 999
4:	 allocEventQ 
6:	 pushThis 
7:	 saveBETAworld 0
10:	 mvStack 
11:	 pushThis 
12:	 invoke BETA$3 3 2 1
18:	 rpop 
19:	 pushThis 
20:	 invoke LIB$235 235 3 1
26:	 rpop 
27:	 pushThis 
28:	 invoke workspace$319 319 4 1
34:	 rpop 
35:	 rtnAlloc 1
DO:
37:	 doEventQ 
38:	 mvStack 
L1:
L2:
39:	 setThisStack 
40:	 pushThis 
41:	 rtn D
43:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:1 V 2:0 V 3:0 V 4:0 

CLASS BETA$3 dNo:3 topDno:3 orgOff:1 orgId:BETAworld$1 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID BETA
 --  %OSDvisibility disguised
 --  %module LIB, LIB.StringLib
 --  %public
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %ID BETA
 --  %OSDvisibility disguised
 --  %module LIB, LIB.StringLib
 --  %public
4:	 allocEventQ 
6:	 mvStack 
7:	 pushThis 
8:	 invoke ascii$4 4 2 1
14:	 rpop 
15:	 rtnAlloc 1
DO:
17:	 doEventQ 
18:	 mvStack 
L1:
L2:
19:	 setThisStack 
20:	 pushThis 
21:	 rtn D
23:	 END OSDV:2 objSize:3 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:3 V 2:0 V 3:0 V 4:0 

CLASS ascii$4 dNo:4 topDno:4 orgOff:1 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  asciiFoo: 
 --     msg1: 
 --        _put('F')
 --        asciiBar.msg2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  asciiFoo: 
 --     msg1: 
 --        _put('F')
 --        asciiBar.msg2
4:	 allocEventQ 
6:	 mvStack 
-- handleInv: "10 -- <lf>"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "10 -- <lf>" 
7:	 pushc 10
9:	 pushThis 
10:	 storeg nl 2
-- handleInv: "13"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "13" 
12:	 pushc 13
14:	 pushThis 
15:	 storeg cr 3
-- handleInv: "0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
17:	 pushc 0
19:	 pushThis 
20:	 storeg null 4
22:	 rtnAlloc 1
DO:
24:	 doEventQ 
25:	 mvStack 
L1:
-- handleInv: 
 --  nl -- Win:<cr><lf>, Unix:<lf>, Mac:<lf>, Cygwin default:<lf>
 --        --asciiFoo.msg1
 --   staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: 
 --  nl -- Win:<cr><lf>, Unix:<lf>, Mac:<lf>, Cygwin default:<lf>
 --        --asciiFoo.msg1
 --  
26:	 pushc 10
-- handleInv: "newline"  staticOff: 0 doLoad: false useRtnVal: 
 --  false 
-- handleInv:elm: "newline" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "newline" false false "
 --  ObjectInvocation_Unary" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "newline" 0 0 
-- loadOriginII: "newline" 
28:	 pushThis 
-- loadOrigin: "newline" on: 0 
-- beforedoinvoke false 
29:	 storeg newline%$14 5
L2:
31:	 setThisStack 
32:	 pushThis 
33:	 rtn D
35:	 END OSDV:0 objSize:5 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:4 V 2:0 V 3:0 V 4:0 

CLASS Value$7 dNo:7 topDno:7 orgOff:0 orgId:BETA$3 orgDno:0 isValueObj

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID Value
 --  %globals
 --  %basic 21
 --  %public
-- StoreOrigin: 
-- AllocateSuper: 
 --  %ID Value
 --  %globals
 --  %basic 21
 --  %public
DO:
L1:
L2:
1:	 setThisStack 
2:	 pushThis 
3:	 rtn D
5:	 END OSDV:0 objSize:0 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:7 V 2:0 V 3:8 V 4:10 

CLASS integer$30 dNo:30 topDno:7 orgOff:0 orgId:BETA$3 orgDno:0 isValueObj

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID integer
 --  %basic 1, 32
 --  %globals
 --  %public
-- StoreOrigin: 
-- AllocateSuper: 
 --  %ID integer
 --  %basic 1, 32
 --  %globals
 --  %public
DO:
L1:
L2:
1:	 setThisStack 
2:	 pushThis 
3:	 rtn D
5:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:30 V 2:0 V 3:0 V 4:0 

CLASS universal$56 dNo:56 topDno:7 orgOff:0 orgId:BETA$3 orgDno:0 isValueObj

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID universal
 --  %basic 1, 32
 --  %globals
 --  +  : 
-- StoreOrigin: 
-- AllocateSuper: 
 --  %ID universal
 --  %basic 1, 32
 --  %globals
 --  +  : 
DO:
L1:
L2:
1:	 setThisStack 
2:	 pushThis 
3:	 rtn D
5:	 END OSDV:0 objSize:0 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:56 V 2:0 V 3:0 V 4:0 

CLASS char$14 dNo:14 topDno:7 orgOff:0 orgId:BETA$3 orgDno:0 isValueObj

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "char"
 --  %globals
 --  %basic 3, 16
 --  %public
-- StoreOrigin: 
-- AllocateSuper: 
 --  %id "char"
 --  %globals
 --  %basic 3, 16
 --  %public
DO:
L1:
L2:
1:	 setThisStack 
2:	 pushThis 
3:	 rtn D
5:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:14 V 2:0 V 3:0 V 4:0 

CLASS ConsoleIF$231 dNo:231 topDno:231 orgOff:1 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "ConsoleIF"
 --  put:< 
 --     %id "ConsoleIF::put"
 --     ...
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %id "ConsoleIF"
 --  put:< 
 --     %id "ConsoleIF::put"
 --     ...
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:231 V 2:0 V 3:232 V 4:233 V 5:234 

CLASS put$232 dNo:232 topDno:232 orgOff:1 orgId:ConsoleIF$231 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "ConsoleIF::put"
 --  ...
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %id "ConsoleIF::put"
 --  ...
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:232 V 2:0 V 3:0 V 4:0 

CLASS String$285 dNo:285 topDno:7 orgOff:0 orgId:StringLib$284 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "String pattern"
 --  %OSDvisibility disguised
 --  %basic 5
 --        --%immutable      
-- StoreOrigin: 
-- AllocateSuper: 
 --  %id "String pattern"
 --  %OSDvisibility disguised
 --  %basic 5
 --        --%immutable      
1:	 allocEventQ 
3:	 mvStack 
4:	 rtnAlloc 1
DO:
6:	 doEventQ 
7:	 mvStack 
L1:
L2:
8:	 setThisStack 
9:	 pushThis 
10:	 rtn D
12:	 END OSDV:2 objSize:0 isIndexed:1
-- endNewVirtDefs: 
-- vdtTable:final: I 1:285 V 2:0 V 3:296 V 4:303 

CLASS =$8 dNo:8 topDno:8 orgOff:1 orgId:Value$7 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %basic 50
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  inner(= )
 --  
-- arg: in Veq:var this(Value) isVirtualDataItem: false primNo: 18 
-- before:currentArg.store: mainIS: 
 --  %basic 50
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  inner(= )
 --  
1:	 jmpFalse  L3
4:	 pushThis 
5:	 vassign 2 2 0
10:	 jmp L4

L3:
13:	 invokeVal  Veq 88 1
19:	 rpop 
L4:
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 21 
20:	 tstOriginIsNone 
21:	 rstore  1 origin
-- AllocateSuper: 
 --  %basic 50
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  inner(= )
 --  
23:	 allocEventQ 
25:	 mvStack 
26:	 rtnAlloc 1
DO:
28:	 doEventQ 
29:	 mvStack 
L1:
-- handleInv: "inner(= )"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "inner(= )" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(= )" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(= )" 0 0 
-- loadOriginII: "inner(= )" 
-- beforedoinvoke true 
-- doInvoke: "inner(= )" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(= )" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(= )" rec: none 
30:	 pushThis 
31:	 innerP  3
33:	 rpopThisObj 
L2:
34:	 setThisStack 
35:	 pushThis 
36:	 rtn D
38:	 END OSDV:0 objSize:5 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:8 V 2:0 I 3:0 V 4:0 

CLASS =$296 dNo:296 topDno:8 orgOff:1 orgId:String$285 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID "String ="
 --  loop: do 
 --     c1:var char
 --     c2:var char
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 5 
1:	 rShiftUp  1
3:	 tstOriginIsNone 
4:	 rstore  1 origin
-- AllocateSuper: 
 --  %ID "String ="
 --  loop: do 
 --     c1:var char
 --     c2:var char
6:	 allocEventQ 
-- push:super.origin: 
-- AllocateSuper:isSingularImplSuper: "
 --  %ID "String ="
 --     loop: do 
 --        c1:var char
 --        c2:var char
 --        L:var integer
 --        L := length
 --        if (L <> Veq.length) :then 
 --           leave(loop)
 --        beq := true
 --        for(1):to(length):repeat
 --           c1 := get[inx]
 --           c2 := Veq.get[inx]
 --           if (c1 <> c2) :then 
 --              Beq := false
 --              leave(loop)
 --        " false 
8:	 pushThis 
9:	 rpushg iOrigin 1
11:	 rShiftDown 1
-- handleArgOrg:super: =  $8 
-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID "String ="
 --  loop: do 
 --     c1:var char
 --     c2:var char
-- arg: in Veq:var this(Value) isVirtualDataItem: false primNo: 18 
13:	 pushThis 
14:	 rstoreg Veq 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 5 
16:	 tstOriginIsNone 
17:	 rstore  1 origin
-- AllocateSuper: 
 --  %basic 50
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  inner(= )
 --  
19:	 allocEventQ 
21:	 mvStack 
DO:
22:	 doEventQ 
23:	 mvStack 
L1:
24:	 pushThis 
25:	 invoke loop$297 297 0 0
31:	 rpop 
L2:
32:	 setThisStack 
33:	 pushThis 
34:	 rtn D
36:	 END OSDV:0 objSize:3 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:8 V 2:0 I 3:296 V 4:0 

CLASS loop$297 dNo:297 topDno:297 orgOff:1 orgId:=$296 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  c1:var char
 --  c2:var char
 --  L:var integer
 --  L := length
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  c1:var char
 --  c2:var char
 --  L:var integer
 --  L := length
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "length"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "length" 0 0 
-- loadOriginII: "length" 
11:	 pushThis 
-- loadOrigin: "length" on: 2 
12:	 rpushg loop$297 1
14:	 rpushg =$296 1
-- beforedoinvoke true 
-- doInvoke: "length" 0 1 useRtnVal: true 
-- doInvoke:X: "length" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "length" rec: none 
16:	 invoke length$105 105 0 0
22:	 pushg 2 
-- handleInv: "L"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
24:	 pushThis 
-- loadOrigin: "L" on: 0 
-- beforedoinvoke false 
25:	 storeg L%$30 4
-- handleInv: 
 --  if (L <> Veq.length) :then 
 --     leave(loop)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (L <> Veq.length) :then 
 --     leave(loop)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (L <> Veq.length) :then 
 --     leave(loop)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (L <> Veq.length) :then 
 --     leave(loop)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (L <> Veq.length) :then 
 --     leave(loop)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "L <> Veq.length"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "<> Veq.length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "<> Veq.length" true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L <> Veq.length" 0 1 
-- loadOriginII: "L" 
27:	 pushThis 
-- loadOrigin: "L" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "L" 
-- DI:loadAccessor: "L" 
28:	 pushg 4 L
-- beforedoinvoke true 
-- doInvoke: "L <> Veq.length" 1 2 useRtnVal: true 
-- doInvoke:X: "<> Veq.length" 1 2 E.label: 
 --  ObjectInvocation_Binary 2 pRec: none rec: "L" ix->next none 
-- handleInv: "Veq.length"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "Veq" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Veq.length" 0 1 
-- loadOriginII: "Veq" 
30:	 pushThis 
-- loadOrigin: "Veq" on: 1 
31:	 rpushg loop$297 1
-- isVirtualDI: var 
-- OI:loadAccessor: "Veq" 
-- DI:loadAccessor: "Veq" 
33:	 rpushg Veq 2
-- beforedoinvoke true 
-- doInvoke: "Veq.length" 1 2 useRtnVal: true 
-- doInvoke:X: "length" 1 2 E.label: ObjectInvocation_Unary 2 
 --  pRec: none rec: "Veq" ix->next none 
-- OI:newInvoke: "length" rec: Veq 
35:	 invoke length$105 105 0 0
41:	 pushg 2 
-- OI:newInvoke: "<> Veq.length" rec: L 
43:	 ne 

44:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: true 
-- handleInv: "leave(loop)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "leave(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(loop)" 0 0 
-- loadOriginII: "leave(loop)" 
-- beforedoinvoke true 
-- doInvoke: "leave(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(loop)" rec: none 
47:	 jmp L2

L4:
-- handleInv: "true"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "true" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "true" false true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- beforedoinvoke true 
-- doInvoke: "true" 0 1 useRtnVal: true 
-- doInvoke:X: "true" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "true" rec: none 
50:	 invoke True$63 63 0 0
56:	 pushg 1 
-- handleInv: "beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "beq" 0 0 
-- loadOriginII: "beq" 
58:	 pushThis 
-- loadOrigin: "beq" on: 1 
59:	 rpushg loop$297 1
-- beforedoinvoke false 
61:	 storeg Beq%$59 3
63:	 pushThis 
64:	 invoke for:to:repeat$S$301 301 0 0
70:	 rpop 
L2:
71:	 setThisStack 
72:	 pushThis 
73:	 rtn D
75:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:297 V 2:0 V 3:0 V 4:0 

CLASS length$105 dNo:105 topDno:105 orgOff:1 orgId:String$285 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  out V:var integer
 --  V := get[-1] -- actually an index error, accessing length
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 5 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  out V:var integer
 --  V := get[-1] -- actually an index error, accessing length
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "
 --  get[-1] -- actually an index error, accessing length"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "
 --  get[-1] -- actually an index error, accessing length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[-1]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "get[-1]" 0 0 
-- loadOriginII: "get[-1]" 
11:	 pushThis 
-- loadOrigin: "get[-1]" on: 1 
12:	 rpushg length$105 1
-- beforedoinvoke true 
-- doInvoke: "get[-1]" 0 1 useRtnVal: true 
-- doInvoke:X: "get[-1]" 0 1 E.label: ObjectInvocation_KeyWord 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "-1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "-1" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "-1" false true "UnaryOp:-" useRtnVal: true 
-- beforedoinvoke true 
-- doInvoke: "-1" 0 1 useRtnVal: true 
-- doInvoke:X: "-1" 0 1 E.label: UnaryOp:- 1 pRec: none rec: 
 --  none ix->next none 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
14:	 pushc 1
16:	 uminus 
-- OI:newInvoke: "get[-1]" rec: none 
17:	 xpushg  inx 1 0
-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
20:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke false 
21:	 storeg V%$30 2
L2:
23:	 setThisStack 
24:	 pushThis 
25:	 rtn D
27:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:105 V 2:0 V 3:0 V 4:0 

CLASS this$88 dNo:88 topDno:88 orgOff:1 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %basic 18
 --  in this: ref Object
 --  
-- arg: in this: ref Object isVirtualDataItem: false primNo: 64 
-- before:currentArg.store: mainIS: 
 --  %basic 18
 --  in this: ref Object
 --  
1:	 pushThis 
2:	 rstoreg this 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
4:	 tstOriginIsNone 
5:	 rstore  1 origin
-- AllocateSuper: 
 --  %basic 18
 --  in this: ref Object
 --  
7:	 allocEventQ 
9:	 mvStack 
10:	 rtnAlloc 1
DO:
12:	 doEventQ 
13:	 mvStack 
L1:
L2:
14:	 setThisStack 
15:	 pushThis 
16:	 rtn D
18:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:88 V 2:0 V 3:0 V 4:0 

CLASS X_asString$55 dNo:55 topDno:55 orgOff:1 orgId:Object$44 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  out S:var LIB.StringLib.String
 --  inner(X_asString)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 64 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  out S:var LIB.StringLib.String
 --  inner(X_asString)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 pushText ""
9:	 pushThis 
10:	 rstoreg S 2
12:	 rtnAlloc 1
DO:
14:	 doEventQ 
15:	 mvStack 
L1:
-- handleInv: "inner(X_asString)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "inner(X_asString)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(X_asString)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(X_asString)" 0 0 
-- loadOriginII: "inner(X_asString)" 
-- beforedoinvoke true 
-- doInvoke: "inner(X_asString)" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(X_asString)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(X_asString)" rec: none 
16:	 pushThis 
17:	 innerP  3
19:	 rpopThisObj 
L2:
20:	 setThisStack 
21:	 pushThis 
22:	 rtn D
24:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:55 V 2:0 I 3:0 V 4:0 

CLASS LIB$235 dNo:235 topDno:235 orgOff:1 orgId:BETAworld$1 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "LIB"
 --  %module BETA
 --  %Include BETA
 --  x_dummy_LIB:var integer
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %id "LIB"
 --  %module BETA
 --  %Include BETA
 --  x_dummy_LIB:var integer
4:	 allocEventQ 
6:	 mvStack 
7:	 pushThis 
8:	 invoke BasicIO$236 236 3 1
14:	 rpop 
15:	 pushThis 
16:	 invoke Dimensions$250 250 4 1
22:	 rpop 
23:	 pushThis 
24:	 invoke StringLib$284 284 5 1
30:	 rpop 
31:	 rtnAlloc 1
DO:
33:	 doEventQ 
34:	 mvStack 
L1:
L2:
35:	 setThisStack 
36:	 pushThis 
37:	 rtn D
39:	 END OSDV:0 objSize:5 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:235 V 2:0 V 3:0 V 4:0 

CLASS BasicIO$236 dNo:236 topDno:236 orgOff:1 orgId:LIB$235 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %module LIB.StringLib
 --  %Public
 --  Lock: 
 --     dummy:var integer
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %module LIB.StringLib
 --  %Public
 --  Lock: 
 --     dummy:var integer
4:	 allocEventQ 
6:	 mvStack 
7:	 pushThis 
8:	 invoke keyboard$237 237 2 1
14:	 rpop 
15:	 pushThis 
16:	 invoke screen$241 241 3 1
22:	 rpop 
23:	 rtnAlloc 1
DO:
25:	 doEventQ 
26:	 mvStack 
L1:
L2:
27:	 setThisStack 
28:	 pushThis 
29:	 rtn D
31:	 END OSDV:0 objSize:3 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:236 V 2:0 V 3:0 V 4:0 

CLASS keyboard$237 dNo:237 topDno:237 orgOff:1 orgId:BasicIO$236 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %Public
 --  readLine: 
 --     out M: var LIB.StringLib.String
 --     inx:var integer
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %Public
 --  readLine: 
 --     out M: var LIB.StringLib.String
 --     inx:var integer
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:237 V 2:0 V 3:0 V 4:0 

CLASS screen$241 dNo:241 topDno:241 orgOff:1 orgId:BasicIO$236 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  L: obj Lock
 --  %Public
 --  init: 
 --     L.get
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  L: obj Lock
 --  %Public
 --  init: 
 --     L.get
4:	 allocEventQ 
6:	 mvStack 
-- handleInv: "Lock"  staticOff: 2 doLoad: true useRtnVal: false 
-- handleInv:elm: "Lock" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Lock" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Lock" 0 0 
-- loadOriginII: "Lock" 
7:	 pushThis 
-- loadOrigin: "Lock" on: 1 
8:	 rpushg screen$241 1
-- beforedoinvoke true 
-- doInvoke: "Lock" 0 1 useRtnVal: false 
-- doInvoke:X: "Lock" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "Lock" rec: none 
10:	 invoke Lock$242 242 2 1
16:	 rpop 
17:	 rtnAlloc 1
DO:
19:	 doEventQ 
20:	 mvStack 
L1:
L2:
21:	 setThisStack 
22:	 pushThis 
23:	 rtn D
25:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:241 V 2:0 V 3:0 V 4:0 

CLASS Lock$242 dNo:242 topDno:242 orgOff:1 orgId:BasicIO$236 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  dummy:var integer
 --  %Public
 --  M:var integer
 --  init: 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  dummy:var integer
 --  %Public
 --  M:var integer
 --  init: 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:3 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:242 V 2:0 V 3:0 V 4:0 

CLASS Dimensions$250 dNo:250 topDno:250 orgOff:1 orgId:LIB$235 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %domain_boundary
 --  %public
 --  Dimension: 
 --     %dimension "-top-"
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %domain_boundary
 --  %public
 --  Dimension: 
 --     %dimension "-top-"
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:250 V 2:0 V 3:0 V 4:0 

CLASS StringLib$284 dNo:284 topDno:284 orgOff:1 orgId:LIB$235 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "String module"
 --  %module LIB
 --  %public
 --  String: Value
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %id "String module"
 --  %module LIB
 --  %public
 --  String: Value
4:	 allocEventQ 
6:	 saveStringOrigin 
7:	 mvStack 
8:	 rtnAlloc 1
DO:
10:	 doEventQ 
11:	 mvStack 
L1:
L2:
12:	 setThisStack 
13:	 pushThis 
14:	 rtn D
16:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:284 V 2:0 V 3:0 V 4:0 

CLASS Object$S$298 dNo:298 topDno:298 orgOff:1 orgId:loop$297 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "leave(loop)" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "leave(loop)" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "leave(loop)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "leave(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(loop)" 0 0 
-- loadOriginII: "leave(loop)" 
-- beforedoinvoke true 
-- doInvoke: "leave(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(loop)" rec: none 
11:	 jmp L2

L2:
14:	 setThisStack 
15:	 pushThis 
16:	 rtn D
18:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:298 V 2:0 V 3:0 V 4:0 

CLASS if:then$113 dNo:113 topDno:113 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %OSDvisibility skipInternal
 --  %basic 100
 --  %globals inSub
 --  
-- arg: cond:var boolean isVirtualDataItem: false primNo: 4 
-- before:currentArg.store: mainIS: 
 --  %OSDvisibility skipInternal
 --  %basic 100
 --  %globals inSub
 --  
1:	 pushThis 
2:	 storeg cond%$59 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %basic 100
 --  %globals inSub
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:1 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:113 V 2:0 V 3:114 V 4:0 

CLASS thenPart$114 dNo:114 topDno:44 orgOff:0 orgId:if:then$113 orgDno:113 isVstub

DO:
1:	 invoke Object$44 44 0 0
7:	 pushThis 
8:	 rstoreg  2
10:	 setThisStack 
11:	 pushThis 
12:	 rpushg  2
14:	 rtn D
16:	 END OSDV:1 objSize:3 isIndexed:0

CLASS Boolean$59 dNo:59 topDno:7 orgOff:0 orgId:BETA$3 orgDno:0 isValueObj

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "Boolean"
 --  %globals inSub
 --  %basic 4, 8
 --  %public
-- StoreOrigin: 
-- AllocateSuper: 
 --  %id "Boolean"
 --  %globals inSub
 --  %basic 4, 8
 --  %public
DO:
L1:
L2:
1:	 setThisStack 
2:	 pushThis 
3:	 rtn D
5:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:59 V 2:0 V 3:0 V 4:0 

CLASS True$63 dNo:63 topDno:63 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %globals
 --  out B:var boolean
 --  B := 1
 --  
-- StoreOrigin: 
-- AllocateSuper: 
 --  %globals
 --  out B:var boolean
 --  B := 1
 --  
1:	 allocEventQ 
3:	 mvStack 
4:	 rtnAlloc 1
DO:
6:	 doEventQ 
7:	 mvStack 
L1:
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
8:	 pushc 1
-- handleInv: "B"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "B" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "B" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "B" 0 0 
-- loadOriginII: "B" 
10:	 pushThis 
-- loadOrigin: "B" on: 0 
-- beforedoinvoke false 
11:	 storeg B%$59 1
L2:
13:	 setThisStack 
14:	 pushThis 
15:	 rtn D
17:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:63 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$109 dNo:109 topDno:109 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
1:	 pushThis 
2:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
4:	 pushThis 
5:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
7:	 allocEventQ 
9:	 mvStack 
10:	 rtnAlloc 1
DO:
12:	 doEventQ 
13:	 mvStack 
L1:
-- handleInv: "first"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "first" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "first" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "first" 0 0 
-- loadOriginII: "first" 
14:	 pushThis 
-- loadOrigin: "first" on: 0 
-- beforedoinvoke true 
-- doInvoke: "first" 0 1 useRtnVal: true 
-- doInvoke:X: "first" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "first" rec: none 
15:	 pushg 1 first
-- handleInv: "inx"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
17:	 pushThis 
-- loadOrigin: "inx" on: 0 
-- beforedoinvoke false 
18:	 storeg inx%$30 3
20:	 pushThis 
21:	 invoke _doIt$110 110 0 0
27:	 rpop 
L2:
28:	 setThisStack 
29:	 pushThis 
30:	 rtn D
32:	 END OSDV:1 objSize:3 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:108 V 4:0 

CLASS repeat$108 dNo:108 topDno:44 orgOff:0 orgId:for:to:repeat$109 orgDno:109 isVstub

DO:
1:	 invoke Object$44 44 0 0
7:	 pushThis 
8:	 rstoreg  2
10:	 setThisStack 
11:	 pushThis 
12:	 rpushg  2
14:	 rtn D
16:	 END OSDV:1 objSize:3 isIndexed:0

CLASS _doIt$110 dNo:110 topDno:110 orgOff:1 orgId:for:to:repeat$109 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  if (inx <= last) :then 
 --     repeat
 --     inx := inx + 1
 --     restart(_doIt)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  if (inx <= last) :then 
 --     repeat
 --     inx := inx + 1
 --     restart(_doIt)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: 
 --  if (inx <= last) :then 
 --     repeat
 --     inx := inx + 1
 --     restart(_doIt)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (inx <= last) :then 
 --     repeat
 --     inx := inx + 1
 --     restart(_doIt)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (inx <= last) :then 
 --     repeat
 --     inx := inx + 1
 --     restart(_doIt)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (inx <= last) :then 
 --     repeat
 --     inx := inx + 1
 --     restart(_doIt)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (inx <= last) :then 
 --     repeat
 --     inx := inx + 1
 --     restart(_doIt)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "inx <= last"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "<= last" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "<= last" true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx <= last" 0 1 
-- loadOriginII: "inx" 
11:	 pushThis 
-- loadOrigin: "inx" on: 1 
12:	 rpushg _doIt$110 1
-- isVirtualDI: var 
-- OI:loadAccessor: "inx" 
-- DI:loadAccessor: "inx" 
14:	 pushg 3 inx
-- beforedoinvoke true 
-- doInvoke: "inx <= last" 1 2 useRtnVal: true 
-- doInvoke:X: "<= last" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "inx" ix->next none 
-- handleInv: "last"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "last" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "last" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "last" 0 0 
-- loadOriginII: "last" 
16:	 pushThis 
-- loadOrigin: "last" on: 1 
17:	 rpushg _doIt$110 1
-- beforedoinvoke true 
-- doInvoke: "last" 0 1 useRtnVal: true 
-- doInvoke:X: "last" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "last" rec: none 
19:	 pushg 2 last
-- OI:newInvoke: "<= last" rec: inx 
21:	 le 

22:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: true 
-- handleInv: "repeat"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "repeat" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "repeat" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "repeat" 0 0 
-- loadOriginII: "repeat" 
25:	 pushThis 
-- loadOrigin: "repeat" on: 1 
26:	 rpushg _doIt$110 1
-- beforedoinvoke true 
-- doInvoke: "repeat" 0 1 useRtnVal: false 
-- doInvoke:X: "repeat" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "repeat" rec: none 
28:	 invokev 3 0 repeat$108$108 0
32:	 rpop 
-- handleInv: "inx + 1"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ 1" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ 1" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx + 1" 0 1 
-- loadOriginII: "inx" 
33:	 pushThis 
-- loadOrigin: "inx" on: 1 
34:	 rpushg _doIt$110 1
-- isVirtualDI: var 
-- OI:loadAccessor: "inx" 
-- DI:loadAccessor: "inx" 
36:	 pushg 3 inx
-- beforedoinvoke true 
-- doInvoke: "inx + 1" 1 2 useRtnVal: true 
-- doInvoke:X: "+ 1" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "inx" ix->next none 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
38:	 pushc 1
-- OI:newInvoke: "+ 1" rec: inx 
40:	 plus 

-- handleInv: "inx"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
41:	 pushThis 
-- loadOrigin: "inx" on: 1 
42:	 rpushg _doIt$110 1
-- beforedoinvoke false 
44:	 storeg inx%$30 3
-- handleInv: "restart(_doIt)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "restart(_doIt)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "restart(_doIt)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "restart(_doIt)" 0 0 
-- loadOriginII: "restart(_doIt)" 
-- beforedoinvoke true 
-- doInvoke: "restart(_doIt)" 0 1 useRtnVal: false 
-- doInvoke:X: "restart(_doIt)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "restart(_doIt)" rec: none 
46:	 jmp L1

L4:
L2:
49:	 setThisStack 
50:	 pushThis 
51:	 rtn D
53:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:110 V 2:0 V 3:0 V 4:0 

CLASS Object$S$111 dNo:111 topDno:111 orgOff:1 orgId:_doIt$110 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  repeat
 --  inx := inx + 1
 --  restart(_doIt)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  repeat
 --  inx := inx + 1
 --  restart(_doIt)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "repeat"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "repeat" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "repeat" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "repeat" 0 0 
-- loadOriginII: "repeat" 
11:	 pushThis 
-- loadOrigin: "repeat" on: 1 
12:	 rpushg _doIt$110 1
-- beforedoinvoke true 
-- doInvoke: "repeat" 0 1 useRtnVal: false 
-- doInvoke:X: "repeat" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "repeat" rec: none 
14:	 invokev 3 0 repeat$108$108 0
18:	 rpop 
-- handleInv: "inx + 1"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ 1" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ 1" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx + 1" 0 1 
-- loadOriginII: "inx" 
19:	 pushThis 
-- loadOrigin: "inx" on: 1 
20:	 rpushg _doIt$110 1
-- isVirtualDI: var 
-- OI:loadAccessor: "inx" 
-- DI:loadAccessor: "inx" 
22:	 pushg 3 inx
-- beforedoinvoke true 
-- doInvoke: "inx + 1" 1 2 useRtnVal: true 
-- doInvoke:X: "+ 1" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "inx" ix->next none 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
24:	 pushc 1
-- OI:newInvoke: "+ 1" rec: inx 
26:	 plus 

-- handleInv: "inx"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
27:	 pushThis 
-- loadOrigin: "inx" on: 1 
28:	 rpushg _doIt$110 1
-- beforedoinvoke false 
30:	 storeg inx%$30 3
-- handleInv: "restart(_doIt)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "restart(_doIt)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "restart(_doIt)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "restart(_doIt)" 0 0 
-- loadOriginII: "restart(_doIt)" 
-- beforedoinvoke true 
-- doInvoke: "restart(_doIt)" 0 1 useRtnVal: false 
-- doInvoke:X: "restart(_doIt)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "restart(_doIt)" rec: none 
32:	 jmp L1

L2:
35:	 setThisStack 
36:	 pushThis 
37:	 rtn D
39:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:111 V 2:0 V 3:0 V 4:0 

CLASS Object$S$299 dNo:299 topDno:299 orgOff:1 orgId:for:to:repeat$S$301 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  c1 := get[inx]
 --  c2 := Veq.get[inx]
 --  if (c1 <> c2) :then 
 --     Beq := false
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  c1 := get[inx]
 --  c2 := Veq.get[inx]
 --  if (c1 <> c2) :then 
 --     Beq := false
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "get[inx]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "get[inx]" 0 0 
-- loadOriginII: "get[inx]" 
11:	 pushThis 
-- loadOrigin: "get[inx]" on: 4 
12:	 rpushg Object$S$299 1
14:	 rpushg for:to:repeat$S$301 4
16:	 rpushg loop$297 1
18:	 rpushg =$296 1
-- beforedoinvoke true 
-- doInvoke: "get[inx]" 0 1 useRtnVal: true 
-- doInvoke:X: "get[inx]" 0 1 E.label: ObjectInvocation_KeyWord 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
20:	 pushThis 
-- loadOrigin: "inx" on: 1 
21:	 rpushg Object$S$299 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
23:	 pushg 3 inx
-- OI:newInvoke: "get[inx]" rec: none 
25:	 xpushg  inx 1 0
-- handleInv: "c1"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "c1" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c1" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "c1" 0 0 
-- loadOriginII: "c1" 
28:	 pushThis 
-- loadOrigin: "c1" on: 2 
29:	 rpushg Object$S$299 1
31:	 rpushg for:to:repeat$S$301 4
-- beforedoinvoke false 
33:	 storeg c1%$14 2
-- handleInv: "Veq.get[inx]"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "Veq" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Veq.get[inx]" 0 1 
-- loadOriginII: "Veq" 
35:	 pushThis 
-- loadOrigin: "Veq" on: 3 
36:	 rpushg Object$S$299 1
38:	 rpushg for:to:repeat$S$301 4
40:	 rpushg loop$297 1
-- isVirtualDI: var 
-- OI:loadAccessor: "Veq" 
-- DI:loadAccessor: "Veq" 
42:	 rpushg Veq 2
-- beforedoinvoke true 
-- doInvoke: "Veq.get[inx]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[inx]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "Veq" ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
44:	 pushThis 
-- loadOrigin: "inx" on: 1 
45:	 rpushg Object$S$299 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
47:	 pushg 3 inx
-- OI:newInvoke: "get[inx]" rec: Veq 
49:	 xpushg  inx 1 0
-- handleInv: "c2"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "c2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "c2" 0 0 
-- loadOriginII: "c2" 
52:	 pushThis 
-- loadOrigin: "c2" on: 2 
53:	 rpushg Object$S$299 1
55:	 rpushg for:to:repeat$S$301 4
-- beforedoinvoke false 
57:	 storeg c2%$14 3
-- handleInv: 
 --  if (c1 <> c2) :then 
 --     Beq := false
 --     leave(loop)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (c1 <> c2) :then 
 --     Beq := false
 --     leave(loop)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (c1 <> c2) :then 
 --     Beq := false
 --     leave(loop)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (c1 <> c2) :then 
 --     Beq := false
 --     leave(loop)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (c1 <> c2) :then 
 --     Beq := false
 --     leave(loop)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "c1 <> c2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "c1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "<> c2" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "<> c2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c1 <> c2" 0 1 
-- loadOriginII: "c1" 
59:	 pushThis 
-- loadOrigin: "c1" on: 2 
60:	 rpushg Object$S$299 1
62:	 rpushg for:to:repeat$S$301 4
-- isVirtualDI: var 
-- OI:loadAccessor: "c1" 
-- DI:loadAccessor: "c1" 
64:	 pushg 2 c1
-- beforedoinvoke true 
-- doInvoke: "c1 <> c2" 1 2 useRtnVal: true 
-- doInvoke:X: "<> c2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "c1" ix->next none 
-- handleInv: "c2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "c2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c2" 0 0 
-- loadOriginII: "c2" 
66:	 pushThis 
-- loadOrigin: "c2" on: 2 
67:	 rpushg Object$S$299 1
69:	 rpushg for:to:repeat$S$301 4
-- beforedoinvoke true 
-- doInvoke: "c2" 0 1 useRtnVal: true 
-- doInvoke:X: "c2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "c2" rec: none 
71:	 pushg 3 c2
-- OI:newInvoke: "<> c2" rec: c1 
73:	 ne 

74:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: true 
-- handleInv: "false"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "false" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "false" false true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- beforedoinvoke true 
-- doInvoke: "false" 0 1 useRtnVal: true 
-- doInvoke:X: "false" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "false" rec: none 
77:	 invoke False$62 62 0 0
83:	 pushg 1 
-- handleInv: "Beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Beq" 0 0 
-- loadOriginII: "Beq" 
85:	 pushThis 
-- loadOrigin: "Beq" on: 3 
86:	 rpushg Object$S$299 1
88:	 rpushg for:to:repeat$S$301 4
90:	 rpushg loop$297 1
-- beforedoinvoke false 
92:	 storeg Beq%$59 3
-- handleInv: "leave(loop)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "leave(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(loop)" 0 0 
-- loadOriginII: "leave(loop)" 
-- beforedoinvoke true 
-- doInvoke: "leave(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(loop)" rec: none 
94:	 break 2 2 297 0
L4:
L2:
101:	 setThisStack 
102:	 pushThis 
103:	 rtn D
105:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:299 V 2:0 V 3:0 V 4:0 

CLASS Object$S$300 dNo:300 topDno:300 orgOff:1 orgId:Object$S$299 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  Beq := false
 --  leave(loop)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  Beq := false
 --  leave(loop)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "false"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "false" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "false" false true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- beforedoinvoke true 
-- doInvoke: "false" 0 1 useRtnVal: true 
-- doInvoke:X: "false" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "false" rec: none 
11:	 invoke False$62 62 0 0
17:	 pushg 1 
-- handleInv: "Beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Beq" 0 0 
-- loadOriginII: "Beq" 
19:	 pushThis 
-- loadOrigin: "Beq" on: 3 
20:	 rpushg Object$S$299 1
22:	 rpushg for:to:repeat$S$301 4
24:	 rpushg loop$297 1
-- beforedoinvoke false 
26:	 storeg Beq%$59 3
-- handleInv: "leave(loop)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "leave(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(loop)" 0 0 
-- loadOriginII: "leave(loop)" 
-- beforedoinvoke true 
-- doInvoke: "leave(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(loop)" rec: none 
28:	 break 2 2 297 0
L2:
35:	 setThisStack 
36:	 pushThis 
37:	 rtn D
39:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:300 V 2:0 V 3:0 V 4:0 

CLASS False$62 dNo:62 topDno:62 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %globals
 --  out B:var boolean
 --  B := 0
 --  
-- StoreOrigin: 
-- AllocateSuper: 
 --  %globals
 --  out B:var boolean
 --  B := 0
 --  
1:	 allocEventQ 
3:	 mvStack 
4:	 rtnAlloc 1
DO:
6:	 doEventQ 
7:	 mvStack 
L1:
-- handleInv: "0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
8:	 pushc 0
-- handleInv: "B"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "B" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "B" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "B" 0 0 
-- loadOriginII: "B" 
10:	 pushThis 
-- loadOrigin: "B" on: 0 
-- beforedoinvoke false 
11:	 storeg B%$59 1
L2:
13:	 setThisStack 
14:	 pushThis 
15:	 rtn D
17:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:62 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$S$301 dNo:301 topDno:109 orgOff:4 orgId:loop$297 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  4 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
4:	 pushc 1
-- handleInv: "length"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "length" 0 0 
-- loadOriginII: "length" 
6:	 pushThis 
-- loadOrigin: "length" on: 2 
7:	 rpushg loop$297%$297 4
9:	 rpushg loop$297 1
11:	 rpushg =$296 1
-- beforedoinvoke true 
-- doInvoke: "length" 0 1 useRtnVal: true 
-- doInvoke:X: "length" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "length" rec: none 
13:	 invoke length$105 105 0 0
19:	 pushg 2 
-- handleArgOrg:super: 
 --  for(first:var integer):to(last:var integer):repeat{repeat:< object}$109 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
21:	 pushThis 
22:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
24:	 pushThis 
25:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
27:	 allocEventQ 
29:	 rtnAlloc 1
31:	 toSuper  109
DO:
34:	 mvStack 
L1:
L2:
35:	 rtnInner  M
36:	 END OSDV:1 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:299 V 4:0 

CLASS <=$10 dNo:10 topDno:10 orgOff:1 orgId:Value$7 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %basic 52
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  
-- arg: in Veq:var this(Value) isVirtualDataItem: false primNo: 18 
-- before:currentArg.store: mainIS: 
 --  %basic 52
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  
1:	 jmpFalse  L3
4:	 pushThis 
5:	 vassign 2 2 0
10:	 jmp L4

L3:
13:	 invokeVal  Veq 88 1
19:	 rpop 
L4:
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 21 
20:	 tstOriginIsNone 
21:	 rstore  1 origin
-- AllocateSuper: 
 --  %basic 52
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  
23:	 allocEventQ 
25:	 mvStack 
26:	 rtnAlloc 1
DO:
28:	 doEventQ 
29:	 mvStack 
L1:
L2:
30:	 setThisStack 
31:	 pushThis 
32:	 rtn D
34:	 END OSDV:0 objSize:5 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:10 V 2:0 V 3:0 V 4:0 

CLASS <=$303 dNo:303 topDno:10 orgOff:1 orgId:String$285 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID "String: <="
 --  loop: obj 
 --     matchEq: 
 --        inx:var integer
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 5 
1:	 rShiftUp  1
3:	 tstOriginIsNone 
4:	 rstore  1 origin
-- AllocateSuper: 
 --  %ID "String: <="
 --  loop: obj 
 --     matchEq: 
 --        inx:var integer
6:	 allocEventQ 
-- push:super.origin: 
-- AllocateSuper:isSingularImplSuper: "
 --  %ID "String: <="
 --     loop: obj 
 --        matchEq: 
 --           inx:var integer
 --           c1:var char
 --           c2:var char
 --           isEmpty: do 
 --              if (L1 = 0) :then 
 --                 Beq := L1 <= L2
 --                 leave(matchEq)
 --              if (L2 = 0) :then 
 --                 Beq := false
 --                 leave(matchEq)
 --           loop: do 
 --              inx := inx + 1
 --              c1 := get[inx]
 --              c2 := Veq.get[inx]
 --
--               if (c1 = c2) :then 
 --                 if (inx < L) :then 
 --                    restart(loop)
 --           doit: do 
 --              if (c1 = c2) :then 
 --                 Beq
 --                       -- we have inx = L := L1 <= L2
 --                    leave(matchEq)
 --              :else 
 --                 Beq := c1 < c2
 --                 leave(matchEq)
 --        L:var integer
 --        L1:var integer
 --        L2:var integer
 --        L1 := length
 --             -- min length of this and V
 --        L2 := Veq.length
 --        if (L1 < L2) :then 
 -
-- -           L := L1
 --        :else 
 --           L := L2
 --        matchEq" false 
8:	 pushThis 
9:	 rpushg iOrigin 1
11:	 rShiftDown 1
-- handleArgOrg:super: <=  $10 
-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %ID "String: <="
 --  loop: obj 
 --     matchEq: 
 --        inx:var integer
-- arg: in Veq:var this(Value) isVirtualDataItem: false primNo: 18 
13:	 pushThis 
14:	 rstoreg Veq 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 5 
16:	 tstOriginIsNone 
17:	 rstore  1 origin
-- AllocateSuper: 
 --  %basic 52
 --  in Veq:var this(Value)
 --  out Beq:var boolean
 --  
19:	 allocEventQ 
21:	 mvStack 
22:	 pushThis 
23:	 invoke loop$304 304 4 1
29:	 rpop 
DO:
30:	 doEventQ 
31:	 mvStack 
L1:
L2:
32:	 setThisStack 
33:	 pushThis 
34:	 rtn D
36:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:10 V 2:0 V 3:0 V 4:0 

CLASS loop$304 dNo:304 topDno:304 orgOff:1 orgId:<=$303 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  matchEq: 
 --     inx:var integer
 --     c1:var char
 --     c2:var char
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  matchEq: 
 --     inx:var integer
 --     c1:var char
 --     c2:var char
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: 
 --  length
 --             -- min length of this and V
 --   staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: 
 --  length
 --             -- min length of this and V
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  length
 --             -- min length of this and V
 --  true true "ObjectInvocation_Unary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: 
 --  length
 --             -- min length of this and V
 --  0 0 
-- loadOriginII: 
 --  length
 --             -- min length of this and V
 --  
11:	 pushThis 
-- loadOrigin: "length
 --             -- min length of this and V" on: 2 
12:	 rpushg loop$304 1
14:	 rpushg <=$303 1
-- beforedoinvoke true 
-- doInvoke: 
 --  length
 --             -- min length of this and V
 --  0 1 useRtnVal: true 
-- doInvoke:X: 
 --  length
 --             -- min length of this and V
 --  0 1 E.label: ObjectInvocation_Unary 1 pRec: none rec: none 
 --  ix->next none 
-- OI:newInvoke: 
 --  length
 --             -- min length of this and V
 --  rec: none 
16:	 invoke length$105 105 0 0
22:	 pushg 2 
-- handleInv: "L1"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "L1" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L1" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "L1" 0 0 
-- loadOriginII: "L1" 
24:	 pushThis 
-- loadOrigin: "L1" on: 0 
-- beforedoinvoke false 
25:	 storeg L1%$30 3
-- handleInv: "Veq.length"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "Veq" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Veq.length" 0 1 
-- loadOriginII: "Veq" 
27:	 pushThis 
-- loadOrigin: "Veq" on: 1 
28:	 rpushg loop$304 1
-- isVirtualDI: var 
-- OI:loadAccessor: "Veq" 
-- DI:loadAccessor: "Veq" 
30:	 rpushg Veq 2
-- beforedoinvoke true 
-- doInvoke: "Veq.length" 1 2 useRtnVal: true 
-- doInvoke:X: "length" 1 2 E.label: ObjectInvocation_Unary 2 
 --  pRec: none rec: "Veq" ix->next none 
-- OI:newInvoke: "length" rec: Veq 
32:	 invoke length$105 105 0 0
38:	 pushg 2 
-- handleInv: "L2"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "L2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "L2" 0 0 
-- loadOriginII: "L2" 
40:	 pushThis 
-- loadOrigin: "L2" on: 0 
-- beforedoinvoke false 
41:	 storeg L2%$30 4
-- handleInv: 
 --  if (L1 < L2) :then 
 --     L := L1
 --  :else 
 --     L := L2
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (L1 < L2) :then 
 --     L := L1
 --  :else 
 --     L := L2
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (L1 < L2) :then 
 --     L := L1
 --  :else 
 --     L := L2
 --  false true "IfThenElse" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (L1 < L2) :then 
 --     L := L1
 --  :else 
 --     L := L2
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (L1 < L2) :then 
 --     L := L1
 --  :else 
 --     L := L2
 --  0 1 E.label: IfThenElse 1 pRec: none rec: none ix->next none 
-- handleInv: "L1 < L2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "L1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "< L2" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "< L2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L1 < L2" 0 1 
-- loadOriginII: "L1" 
43:	 pushThis 
-- loadOrigin: "L1" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "L1" 
-- DI:loadAccessor: "L1" 
44:	 pushg 3 L1
-- beforedoinvoke true 
-- doInvoke: "L1 < L2" 1 2 useRtnVal: true 
-- doInvoke:X: "< L2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L1" ix->next none 
-- handleInv: "L2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L2" 0 0 
-- loadOriginII: "L2" 
46:	 pushThis 
-- loadOrigin: "L2" on: 0 
-- beforedoinvoke true 
-- doInvoke: "L2" 0 1 useRtnVal: true 
-- doInvoke:X: "L2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L2" rec: none 
47:	 pushg 4 L2
-- OI:newInvoke: "< L2" rec: L1 
49:	 lt 

50:	 jmpFalse  L4
L3:
53:	 pushThis 
54:	 invoke Object$S$315 315 0 0
60:	 rpop 
61:	 jmp L5

L4:
64:	 pushThis 
65:	 invoke Object$S$316 316 0 0
71:	 rpop 
L5:
-- handleInv: "matchEq"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "matchEq" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "matchEq" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "matchEq" 0 0 
-- loadOriginII: "matchEq" 
72:	 pushThis 
-- loadOrigin: "matchEq" on: 0 
-- beforedoinvoke true 
-- doInvoke: "matchEq" 0 1 useRtnVal: false 
-- doInvoke:X: "matchEq" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "matchEq" rec: none 
73:	 invoke matchEq$305 305 0 0
79:	 rpop 
L2:
80:	 setThisStack 
81:	 pushThis 
82:	 rtn D
84:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:304 V 2:0 V 3:0 V 4:0 

CLASS Object$S$315 dNo:315 topDno:315 orgOff:1 orgId:loop$304 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "L := L1" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "L := L1" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "L1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L1" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L1" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L1" 0 0 
-- loadOriginII: "L1" 
11:	 pushThis 
-- loadOrigin: "L1" on: 1 
12:	 rpushg Object$S$315 1
-- beforedoinvoke true 
-- doInvoke: "L1" 0 1 useRtnVal: true 
-- doInvoke:X: "L1" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L1" rec: none 
14:	 pushg 3 L1
-- handleInv: "L"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
16:	 pushThis 
-- loadOrigin: "L" on: 1 
17:	 rpushg Object$S$315 1
-- beforedoinvoke false 
19:	 storeg L%$30 2
L2:
21:	 setThisStack 
22:	 pushThis 
23:	 rtn D
25:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:315 V 2:0 V 3:0 V 4:0 

CLASS Object$S$316 dNo:316 topDno:316 orgOff:1 orgId:loop$304 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "L := L2" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "L := L2" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "L2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L2" 0 0 
-- loadOriginII: "L2" 
11:	 pushThis 
-- loadOrigin: "L2" on: 1 
12:	 rpushg Object$S$316 1
-- beforedoinvoke true 
-- doInvoke: "L2" 0 1 useRtnVal: true 
-- doInvoke:X: "L2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L2" rec: none 
14:	 pushg 4 L2
-- handleInv: "L"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
16:	 pushThis 
-- loadOrigin: "L" on: 1 
17:	 rpushg Object$S$316 1
-- beforedoinvoke false 
19:	 storeg L%$30 2
L2:
21:	 setThisStack 
22:	 pushThis 
23:	 rtn D
25:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:316 V 2:0 V 3:0 V 4:0 

CLASS matchEq$305 dNo:305 topDno:305 orgOff:1 orgId:loop$304 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  inx:var integer
 --  c1:var char
 --  c2:var char
 --  isEmpty: do 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  inx:var integer
 --  c1:var char
 --  c2:var char
 --  isEmpty: do 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
11:	 pushThis 
12:	 invoke isEmpty$306 306 0 0
18:	 rpop 
19:	 pushThis 
20:	 invoke loop$309 309 0 0
26:	 rpop 
27:	 pushThis 
28:	 invoke doit$312 312 0 0
34:	 rpop 
L2:
35:	 setThisStack 
36:	 pushThis 
37:	 rtn D
39:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:305 V 2:0 V 3:0 V 4:0 

CLASS isEmpty$306 dNo:306 topDno:306 orgOff:1 orgId:matchEq$305 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  if (L1 = 0) :then 
 --     Beq := L1 <= L2
 --     leave(matchEq)
 --  if (L2 = 0) :then 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  if (L1 = 0) :then 
 --     Beq := L1 <= L2
 --     leave(matchEq)
 --  if (L2 = 0) :then 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: 
 --  if (L1 = 0) :then 
 --     Beq := L1 <= L2
 --     leave(matchEq)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (L1 = 0) :then 
 --     Beq := L1 <= L2
 --     leave(matchEq)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (L1 = 0) :then 
 --     Beq := L1 <= L2
 --     leave(matchEq)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (L1 = 0) :then 
 --     Beq := L1 <= L2
 --     leave(matchEq)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (L1 = 0) :then 
 --     Beq := L1 <= L2
 --     leave(matchEq)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "L1 = 0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "= 0" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "= 0" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L1 = 0" 0 1 
-- loadOriginII: "L1" 
11:	 pushThis 
-- loadOrigin: "L1" on: 2 
12:	 rpushg isEmpty$306 1
14:	 rpushg matchEq$305 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L1" 
-- DI:loadAccessor: "L1" 
16:	 pushg 3 L1
-- beforedoinvoke true 
-- doInvoke: "L1 = 0" 1 2 useRtnVal: true 
-- doInvoke:X: "= 0" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L1" ix->next none 
-- handleInv: "0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
18:	 pushc 0
-- OI:newInvoke: "= 0" rec: L1 
20:	 eq 

21:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: true 
-- handleInv: "L1 <= L2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "L1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "<= L2" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "<= L2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L1 <= L2" 0 1 
-- loadOriginII: "L1" 
24:	 pushThis 
-- loadOrigin: "L1" on: 2 
25:	 rpushg isEmpty$306 1
27:	 rpushg matchEq$305 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L1" 
-- DI:loadAccessor: "L1" 
29:	 pushg 3 L1
-- beforedoinvoke true 
-- doInvoke: "L1 <= L2" 1 2 useRtnVal: true 
-- doInvoke:X: "<= L2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L1" ix->next none 
-- handleInv: "L2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L2" 0 0 
-- loadOriginII: "L2" 
31:	 pushThis 
-- loadOrigin: "L2" on: 2 
32:	 rpushg isEmpty$306 1
34:	 rpushg matchEq$305 1
-- beforedoinvoke true 
-- doInvoke: "L2" 0 1 useRtnVal: true 
-- doInvoke:X: "L2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L2" rec: none 
36:	 pushg 4 L2
-- OI:newInvoke: "<= L2" rec: L1 
38:	 le 

-- handleInv: "Beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Beq" 0 0 
-- loadOriginII: "Beq" 
39:	 pushThis 
-- loadOrigin: "Beq" on: 3 
40:	 rpushg isEmpty$306 1
42:	 rpushg matchEq$305 1
44:	 rpushg loop$304 1
-- beforedoinvoke false 
46:	 storeg Beq%$59 3
-- handleInv: "leave(matchEq)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "leave(matchEq)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(matchEq)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(matchEq)" 0 0 
-- loadOriginII: "leave(matchEq)" 
-- beforedoinvoke true 
-- doInvoke: "leave(matchEq)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(matchEq)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(matchEq)" rec: none 
48:	 break 1 2 305 0
L4:
-- handleInv: 
 --  if (L2 = 0) :then 
 --     Beq := false
 --     leave(matchEq)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (L2 = 0) :then 
 --     Beq := false
 --     leave(matchEq)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (L2 = 0) :then 
 --     Beq := false
 --     leave(matchEq)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (L2 = 0) :then 
 --     Beq := false
 --     leave(matchEq)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (L2 = 0) :then 
 --     Beq := false
 --     leave(matchEq)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "L2 = 0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L2" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "= 0" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "= 0" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L2 = 0" 0 1 
-- loadOriginII: "L2" 
55:	 pushThis 
-- loadOrigin: "L2" on: 2 
56:	 rpushg isEmpty$306 1
58:	 rpushg matchEq$305 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L2" 
-- DI:loadAccessor: "L2" 
60:	 pushg 4 L2
-- beforedoinvoke true 
-- doInvoke: "L2 = 0" 1 2 useRtnVal: true 
-- doInvoke:X: "= 0" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L2" ix->next none 
-- handleInv: "0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
62:	 pushc 0
-- OI:newInvoke: "= 0" rec: L2 
64:	 eq 

65:	 jmpFalse  L7
L6:
-- IfThen:inLineThen: true 
-- handleInv: "false"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "false" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "false" false true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- beforedoinvoke true 
-- doInvoke: "false" 0 1 useRtnVal: true 
-- doInvoke:X: "false" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "false" rec: none 
68:	 invoke False$62 62 0 0
74:	 pushg 1 
-- handleInv: "Beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Beq" 0 0 
-- loadOriginII: "Beq" 
76:	 pushThis 
-- loadOrigin: "Beq" on: 3 
77:	 rpushg isEmpty$306 1
79:	 rpushg matchEq$305 1
81:	 rpushg loop$304 1
-- beforedoinvoke false 
83:	 storeg Beq%$59 3
-- handleInv: "leave(matchEq)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "leave(matchEq)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(matchEq)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(matchEq)" 0 0 
-- loadOriginII: "leave(matchEq)" 
-- beforedoinvoke true 
-- doInvoke: "leave(matchEq)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(matchEq)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(matchEq)" rec: none 
85:	 break 1 2 305 0
L7:
L2:
92:	 setThisStack 
93:	 pushThis 
94:	 rtn D
96:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:306 V 2:0 V 3:0 V 4:0 

CLASS Object$S$307 dNo:307 topDno:307 orgOff:1 orgId:isEmpty$306 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  Beq := L1 <= L2
 --  leave(matchEq)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  Beq := L1 <= L2
 --  leave(matchEq)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "L1 <= L2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "L1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "<= L2" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "<= L2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L1 <= L2" 0 1 
-- loadOriginII: "L1" 
11:	 pushThis 
-- loadOrigin: "L1" on: 2 
12:	 rpushg isEmpty$306 1
14:	 rpushg matchEq$305 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L1" 
-- DI:loadAccessor: "L1" 
16:	 pushg 3 L1
-- beforedoinvoke true 
-- doInvoke: "L1 <= L2" 1 2 useRtnVal: true 
-- doInvoke:X: "<= L2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L1" ix->next none 
-- handleInv: "L2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L2" 0 0 
-- loadOriginII: "L2" 
18:	 pushThis 
-- loadOrigin: "L2" on: 2 
19:	 rpushg isEmpty$306 1
21:	 rpushg matchEq$305 1
-- beforedoinvoke true 
-- doInvoke: "L2" 0 1 useRtnVal: true 
-- doInvoke:X: "L2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L2" rec: none 
23:	 pushg 4 L2
-- OI:newInvoke: "<= L2" rec: L1 
25:	 le 

-- handleInv: "Beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Beq" 0 0 
-- loadOriginII: "Beq" 
26:	 pushThis 
-- loadOrigin: "Beq" on: 3 
27:	 rpushg isEmpty$306 1
29:	 rpushg matchEq$305 1
31:	 rpushg loop$304 1
-- beforedoinvoke false 
33:	 storeg Beq%$59 3
-- handleInv: "leave(matchEq)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "leave(matchEq)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(matchEq)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(matchEq)" 0 0 
-- loadOriginII: "leave(matchEq)" 
-- beforedoinvoke true 
-- doInvoke: "leave(matchEq)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(matchEq)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(matchEq)" rec: none 
35:	 break 1 2 305 0
L2:
42:	 setThisStack 
43:	 pushThis 
44:	 rtn D
46:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:307 V 2:0 V 3:0 V 4:0 

CLASS Object$S$308 dNo:308 topDno:308 orgOff:1 orgId:isEmpty$306 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  Beq := false
 --  leave(matchEq)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  Beq := false
 --  leave(matchEq)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "false"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "false" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "false" false true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- beforedoinvoke true 
-- doInvoke: "false" 0 1 useRtnVal: true 
-- doInvoke:X: "false" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "false" rec: none 
11:	 invoke False$62 62 0 0
17:	 pushg 1 
-- handleInv: "Beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Beq" 0 0 
-- loadOriginII: "Beq" 
19:	 pushThis 
-- loadOrigin: "Beq" on: 3 
20:	 rpushg isEmpty$306 1
22:	 rpushg matchEq$305 1
24:	 rpushg loop$304 1
-- beforedoinvoke false 
26:	 storeg Beq%$59 3
-- handleInv: "leave(matchEq)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "leave(matchEq)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(matchEq)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(matchEq)" 0 0 
-- loadOriginII: "leave(matchEq)" 
-- beforedoinvoke true 
-- doInvoke: "leave(matchEq)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(matchEq)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(matchEq)" rec: none 
28:	 break 1 2 305 0
L2:
35:	 setThisStack 
36:	 pushThis 
37:	 rtn D
39:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:308 V 2:0 V 3:0 V 4:0 

CLASS loop$309 dNo:309 topDno:309 orgOff:1 orgId:matchEq$305 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  inx := inx + 1
 --  c1 := get[inx]
 --  c2 := Veq.get[inx]
 --  if (c1 = c2) :then 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  inx := inx + 1
 --  c1 := get[inx]
 --  c2 := Veq.get[inx]
 --  if (c1 = c2) :then 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "inx + 1"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ 1" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ 1" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx + 1" 0 1 
-- loadOriginII: "inx" 
11:	 pushThis 
-- loadOrigin: "inx" on: 1 
12:	 rpushg loop$309 1
-- isVirtualDI: var 
-- OI:loadAccessor: "inx" 
-- DI:loadAccessor: "inx" 
14:	 pushg 2 inx
-- beforedoinvoke true 
-- doInvoke: "inx + 1" 1 2 useRtnVal: true 
-- doInvoke:X: "+ 1" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "inx" ix->next none 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
16:	 pushc 1
-- OI:newInvoke: "+ 1" rec: inx 
18:	 plus 

-- handleInv: "inx"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
19:	 pushThis 
-- loadOrigin: "inx" on: 1 
20:	 rpushg loop$309 1
-- beforedoinvoke false 
22:	 storeg inx%$30 2
-- handleInv: "get[inx]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "get[inx]" 0 0 
-- loadOriginII: "get[inx]" 
24:	 pushThis 
-- loadOrigin: "get[inx]" on: 4 
25:	 rpushg loop$309 1
27:	 rpushg matchEq$305 1
29:	 rpushg loop$304 1
31:	 rpushg <=$303 1
-- beforedoinvoke true 
-- doInvoke: "get[inx]" 0 1 useRtnVal: true 
-- doInvoke:X: "get[inx]" 0 1 E.label: ObjectInvocation_KeyWord 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
33:	 pushThis 
-- loadOrigin: "inx" on: 1 
34:	 rpushg loop$309 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
36:	 pushg 2 inx
-- OI:newInvoke: "get[inx]" rec: none 
38:	 xpushg  inx 1 0
-- handleInv: "c1"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "c1" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c1" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "c1" 0 0 
-- loadOriginII: "c1" 
41:	 pushThis 
-- loadOrigin: "c1" on: 1 
42:	 rpushg loop$309 1
-- beforedoinvoke false 
44:	 storeg c1%$14 3
-- handleInv: "Veq.get[inx]"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "Veq" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Veq.get[inx]" 0 1 
-- loadOriginII: "Veq" 
46:	 pushThis 
-- loadOrigin: "Veq" on: 3 
47:	 rpushg loop$309 1
49:	 rpushg matchEq$305 1
51:	 rpushg loop$304 1
-- isVirtualDI: var 
-- OI:loadAccessor: "Veq" 
-- DI:loadAccessor: "Veq" 
53:	 rpushg Veq 2
-- beforedoinvoke true 
-- doInvoke: "Veq.get[inx]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[inx]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "Veq" ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
55:	 pushThis 
-- loadOrigin: "inx" on: 1 
56:	 rpushg loop$309 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
58:	 pushg 2 inx
-- OI:newInvoke: "get[inx]" rec: Veq 
60:	 xpushg  inx 1 0
-- handleInv: "c2"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "c2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "c2" 0 0 
-- loadOriginII: "c2" 
63:	 pushThis 
-- loadOrigin: "c2" on: 1 
64:	 rpushg loop$309 1
-- beforedoinvoke false 
66:	 storeg c2%$14 4
-- handleInv: 
 --  if (c1 = c2) :then 
 --     if (inx < L) :then 
 --        restart(loop)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (c1 = c2) :then 
 --     if (inx < L) :then 
 --        restart(loop)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (c1 = c2) :then 
 --     if (inx < L) :then 
 --        restart(loop)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (c1 = c2) :then 
 --     if (inx < L) :then 
 --        restart(loop)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (c1 = c2) :then 
 --     if (inx < L) :then 
 --        restart(loop)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "c1 = c2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "c1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "= c2" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "= c2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c1 = c2" 0 1 
-- loadOriginII: "c1" 
68:	 pushThis 
-- loadOrigin: "c1" on: 1 
69:	 rpushg loop$309 1
-- isVirtualDI: var 
-- OI:loadAccessor: "c1" 
-- DI:loadAccessor: "c1" 
71:	 pushg 3 c1
-- beforedoinvoke true 
-- doInvoke: "c1 = c2" 1 2 useRtnVal: true 
-- doInvoke:X: "= c2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "c1" ix->next none 
-- handleInv: "c2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "c2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c2" 0 0 
-- loadOriginII: "c2" 
73:	 pushThis 
-- loadOrigin: "c2" on: 1 
74:	 rpushg loop$309 1
-- beforedoinvoke true 
-- doInvoke: "c2" 0 1 useRtnVal: true 
-- doInvoke:X: "c2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "c2" rec: none 
76:	 pushg 4 c2
-- OI:newInvoke: "= c2" rec: c1 
78:	 eq 

79:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: false 
82:	 pushThis 
83:	 invoke Object$S$310 310 0 0
89:	 rpop 
L4:
L2:
90:	 setThisStack 
91:	 pushThis 
92:	 rtn D
94:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:309 V 2:0 V 3:0 V 4:0 

CLASS Object$S$310 dNo:310 topDno:310 orgOff:1 orgId:loop$309 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  if (inx < L) :then 
 --     restart(loop)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  if (inx < L) :then 
 --     restart(loop)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: 
 --  if (inx < L) :then 
 --     restart(loop)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (inx < L) :then 
 --     restart(loop)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (inx < L) :then 
 --     restart(loop)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (inx < L) :then 
 --     restart(loop)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (inx < L) :then 
 --     restart(loop)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "inx < L"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "< L" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "< L" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx < L" 0 1 
-- loadOriginII: "inx" 
11:	 pushThis 
-- loadOrigin: "inx" on: 2 
12:	 rpushg Object$S$310 1
14:	 rpushg loop$309 1
-- isVirtualDI: var 
-- OI:loadAccessor: "inx" 
-- DI:loadAccessor: "inx" 
16:	 pushg 2 inx
-- beforedoinvoke true 
-- doInvoke: "inx < L" 1 2 useRtnVal: true 
-- doInvoke:X: "< L" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "inx" ix->next none 
-- handleInv: "L"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
18:	 pushThis 
-- loadOrigin: "L" on: 3 
19:	 rpushg Object$S$310 1
21:	 rpushg loop$309 1
23:	 rpushg matchEq$305 1
-- beforedoinvoke true 
-- doInvoke: "L" 0 1 useRtnVal: true 
-- doInvoke:X: "L" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L" rec: none 
25:	 pushg 2 L
-- OI:newInvoke: "< L" rec: inx 
27:	 lt 

28:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: true 
-- handleInv: "restart(loop)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "restart(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "restart(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "restart(loop)" 0 0 
-- loadOriginII: "restart(loop)" 
-- beforedoinvoke true 
-- doInvoke: "restart(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "restart(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "restart(loop)" rec: none 
31:	 break 1 1 309 0
L4:
L2:
38:	 setThisStack 
39:	 pushThis 
40:	 rtn D
42:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:310 V 2:0 V 3:0 V 4:0 

CLASS Object$S$311 dNo:311 topDno:311 orgOff:1 orgId:Object$S$310 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "restart(loop)" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "restart(loop)" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "restart(loop)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "restart(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "restart(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "restart(loop)" 0 0 
-- loadOriginII: "restart(loop)" 
-- beforedoinvoke true 
-- doInvoke: "restart(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "restart(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "restart(loop)" rec: none 
11:	 break 1 1 309 0
L2:
18:	 setThisStack 
19:	 pushThis 
20:	 rtn D
22:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:311 V 2:0 V 3:0 V 4:0 

CLASS doit$312 dNo:312 topDno:312 orgOff:1 orgId:matchEq$305 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  if (c1 = c2) :then 
 --     Beq
 --                       -- we have inx = L := L1 <= L2
 --        leave(matchEq)
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  if (c1 = c2) :then 
 --     Beq
 --                       -- we have inx = L := L1 <= L2
 --        leave(matchEq)
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: 
 --  if (c1 = c2) :then 
 --     Beq
 --                       -- we have inx = L := L1 <= L2
 --        leave(matchEq) staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (c1 = c2) :then 
 --     Beq
 --                       -- we have inx = L := L1 <= L2
 --        leave(matchEq)
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (c1 = c2) :then 
 --     Beq
 --                       -- we have inx = L := L1 <= L2
 --        leave(matchEq)false true "IfThenElse" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (c1 = c2) :then 
 --     Beq
 --                       -- we have inx = L := L1 <= L2
 --        leave(matchEq)0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (c1 = c2) :then 
 --     Beq
 --                       -- we have inx = L := L1 <= L2
 --        leave(matchEq)0 1 E.label: IfThenElse 1 pRec: none rec: none ix->next none 
-- handleInv: "c1 = c2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "c1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "= c2" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "= c2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c1 = c2" 0 1 
-- loadOriginII: "c1" 
11:	 pushThis 
-- loadOrigin: "c1" on: 1 
12:	 rpushg doit$312 1
-- isVirtualDI: var 
-- OI:loadAccessor: "c1" 
-- DI:loadAccessor: "c1" 
14:	 pushg 3 c1
-- beforedoinvoke true 
-- doInvoke: "c1 = c2" 1 2 useRtnVal: true 
-- doInvoke:X: "= c2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "c1" ix->next none 
-- handleInv: "c2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "c2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c2" 0 0 
-- loadOriginII: "c2" 
16:	 pushThis 
-- loadOrigin: "c2" on: 1 
17:	 rpushg doit$312 1
-- beforedoinvoke true 
-- doInvoke: "c2" 0 1 useRtnVal: true 
-- doInvoke:X: "c2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "c2" rec: none 
19:	 pushg 4 c2
-- OI:newInvoke: "= c2" rec: c1 
21:	 eq 

22:	 jmpFalse  L4
L3:
25:	 pushThis 
26:	 invoke Object$S$313 313 0 0
32:	 rpop 
33:	 jmp L5

L4:
36:	 pushThis 
37:	 invoke Object$S$314 314 0 0
43:	 rpop 
L5:
L2:
44:	 setThisStack 
45:	 pushThis 
46:	 rtn D
48:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:312 V 2:0 V 3:0 V 4:0 

CLASS Object$S$313 dNo:313 topDno:313 orgOff:1 orgId:doit$312 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  Beq
 --                       -- we have inx = L := L1 <= L2
 --  leave(matchEq)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  Beq
 --                       -- we have inx = L := L1 <= L2
 --  leave(matchEq)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "L1 <= L2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "L1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "<= L2" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "<= L2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L1 <= L2" 0 1 
-- loadOriginII: "L1" 
11:	 pushThis 
-- loadOrigin: "L1" on: 3 
12:	 rpushg Object$S$313 1
14:	 rpushg doit$312 1
16:	 rpushg matchEq$305 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L1" 
-- DI:loadAccessor: "L1" 
18:	 pushg 3 L1
-- beforedoinvoke true 
-- doInvoke: "L1 <= L2" 1 2 useRtnVal: true 
-- doInvoke:X: "<= L2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L1" ix->next none 
-- handleInv: "L2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L2" 0 0 
-- loadOriginII: "L2" 
20:	 pushThis 
-- loadOrigin: "L2" on: 3 
21:	 rpushg Object$S$313 1
23:	 rpushg doit$312 1
25:	 rpushg matchEq$305 1
-- beforedoinvoke true 
-- doInvoke: "L2" 0 1 useRtnVal: true 
-- doInvoke:X: "L2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L2" rec: none 
27:	 pushg 4 L2
-- OI:newInvoke: "<= L2" rec: L1 
29:	 le 

-- handleInv: 
 --  Beq
 --                       -- we have inx = L
 --   staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: 
 --  Beq
 --                       -- we have inx = L
 --  0 0 
-- loadOriginII: "Beq" 
30:	 pushThis 
-- loadOrigin: "Beq" on: 4 
31:	 rpushg Object$S$313 1
33:	 rpushg doit$312 1
35:	 rpushg matchEq$305 1
37:	 rpushg loop$304 1
-- beforedoinvoke false 
39:	 storeg Beq%$59 3
-- handleInv: "leave(matchEq)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "leave(matchEq)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(matchEq)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(matchEq)" 0 0 
-- loadOriginII: "leave(matchEq)" 
-- beforedoinvoke true 
-- doInvoke: "leave(matchEq)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(matchEq)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(matchEq)" rec: none 
41:	 break 2 2 305 0
L2:
48:	 setThisStack 
49:	 pushThis 
50:	 rtn D
52:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:313 V 2:0 V 3:0 V 4:0 

CLASS Object$S$314 dNo:314 topDno:314 orgOff:1 orgId:doit$312 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  Beq := c1 < c2
 --  leave(matchEq)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  Beq := c1 < c2
 --  leave(matchEq)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "c1 < c2"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "c1" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "< c2" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "< c2" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c1 < c2" 0 1 
-- loadOriginII: "c1" 
11:	 pushThis 
-- loadOrigin: "c1" on: 2 
12:	 rpushg Object$S$314 1
14:	 rpushg doit$312 1
-- isVirtualDI: var 
-- OI:loadAccessor: "c1" 
-- DI:loadAccessor: "c1" 
16:	 pushg 3 c1
-- beforedoinvoke true 
-- doInvoke: "c1 < c2" 1 2 useRtnVal: true 
-- doInvoke:X: "< c2" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "c1" ix->next none 
-- handleInv: "c2"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "c2" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "c2" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "c2" 0 0 
-- loadOriginII: "c2" 
18:	 pushThis 
-- loadOrigin: "c2" on: 2 
19:	 rpushg Object$S$314 1
21:	 rpushg doit$312 1
-- beforedoinvoke true 
-- doInvoke: "c2" 0 1 useRtnVal: true 
-- doInvoke:X: "c2" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "c2" rec: none 
23:	 pushg 4 c2
-- OI:newInvoke: "< c2" rec: c1 
25:	 lt 

-- handleInv: "Beq"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "Beq" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Beq" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Beq" 0 0 
-- loadOriginII: "Beq" 
26:	 pushThis 
-- loadOrigin: "Beq" on: 4 
27:	 rpushg Object$S$314 1
29:	 rpushg doit$312 1
31:	 rpushg matchEq$305 1
33:	 rpushg loop$304 1
-- beforedoinvoke false 
35:	 storeg Beq%$59 3
-- handleInv: "leave(matchEq)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "leave(matchEq)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "leave(matchEq)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "leave(matchEq)" 0 0 
-- loadOriginII: "leave(matchEq)" 
-- beforedoinvoke true 
-- doInvoke: "leave(matchEq)" 0 1 useRtnVal: false 
-- doInvoke:X: "leave(matchEq)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "leave(matchEq)" rec: none 
37:	 break 2 2 305 0
L2:
44:	 setThisStack 
45:	 pushThis 
46:	 rtn D
48:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:314 V 2:0 V 3:0 V 4:0 

CLASS puttext$233 dNo:233 topDno:233 orgOff:1 orgId:ConsoleIF$231 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "ConsoleIF::puttext"
 --  inner(puttext)
 --  
-- arg: T: var LIB.StringLib.String isVirtualDataItem: false 
 --  primNo: 5 
1:	 pushThis 
2:	 rstoreg T 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
4:	 tstOriginIsNone 
5:	 rstore  1 origin
-- AllocateSuper: 
 --  %id "ConsoleIF::puttext"
 --  inner(puttext)
 --  
7:	 allocEventQ 
9:	 mvStack 
10:	 rtnAlloc 1
DO:
12:	 doEventQ 
13:	 mvStack 
L1:
-- handleInv: "inner(puttext)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "inner(puttext)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(puttext)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(puttext)" 0 0 
-- loadOriginII: "inner(puttext)" 
-- beforedoinvoke true 
-- doInvoke: "inner(puttext)" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(puttext)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(puttext)" rec: none 
14:	 pushThis 
15:	 innerP  3
17:	 rpopThisObj 
L2:
18:	 setThisStack 
19:	 pushThis 
20:	 rtn D
22:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:233 V 2:0 I 3:0 V 4:0 

CLASS putint$234 dNo:234 topDno:234 orgOff:1 orgId:ConsoleIF$231 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "inner(putint)" 
-- arg: V:var Integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "inner(putint)" 
1:	 pushThis 
2:	 storeg V%$30 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
4:	 tstOriginIsNone 
5:	 rstore  1 origin
-- AllocateSuper: "inner(putint)" 
7:	 allocEventQ 
9:	 mvStack 
10:	 rtnAlloc 1
DO:
12:	 doEventQ 
13:	 mvStack 
L1:
-- handleInv: "inner(putint)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "inner(putint)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(putint)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(putint)" 0 0 
-- loadOriginII: "inner(putint)" 
-- beforedoinvoke true 
-- doInvoke: "inner(putint)" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(putint)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(putint)" rec: none 
14:	 pushThis 
15:	 innerP  3
17:	 rpopThisObj 
L2:
18:	 setThisStack 
19:	 pushThis 
20:	 rtn D
22:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:234 V 2:0 I 3:0 V 4:0 

CLASS workspace$319 dNo:319 topDno:319 orgOff:1 orgId:BETAworld$1 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %id "workspace"
 --  %visible BETA, LIB, LIB.BasicIO, LIB.Dimensions, LIB.StringLib
 --  %domain_boundary
 --  --AbstractEx
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %id "workspace"
 --  %visible BETA, LIB, LIB.BasicIO, LIB.Dimensions, LIB.StringLib
 --  %domain_boundary
 --  --AbstractEx
4:	 allocEventQ 
6:	 mvStack 
7:	 pushThis 
8:	 invoke hello$320 320 2 1
14:	 rpop 
15:	 rtnAlloc 1
DO:
17:	 doEventQ 
18:	 mvStack 
L1:
L2:
19:	 setThisStack 
20:	 pushThis 
21:	 rtn D
23:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:319 V 2:0 V 3:0 V 4:0 

CLASS hello$320 dNo:320 topDno:320 orgOff:1 orgId:workspace$319 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  x:var integer
 --  y:var integer
 --  z:var integer
 --  snorf: 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  x:var integer
 --  y:var integer
 --  z:var integer
 --  snorf: 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "put(10)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(10)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(10)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(10)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(10)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "10"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "10" 
11:	 pushc 10
-- OI:newInvoke: "put(10)" rec: none 
13:	 %put 2
-- handleInv: "put(13)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(13)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(13)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(13)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(13)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "13"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "13" 
15:	 pushc 13
-- OI:newInvoke: "put(13)" rec: none 
17:	 %put 2
-- handleInv: "put('%')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('%')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('%')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('%')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('%')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'%'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'%'" 
19:	 pushc 37
-- OI:newInvoke: "put('%')" rec: none 
21:	 %put 2
-- handleInv: "put('A')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('A')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('A')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('A')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('A')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'A'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'A'" 
23:	 pushc 65
-- OI:newInvoke: "put('A')" rec: none 
25:	 %put 2
-- handleInv: "put('B')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('B')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('B')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('B')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('B')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'B'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'B'" 
27:	 pushc 66
-- OI:newInvoke: "put('B')" rec: none 
29:	 %put 2
-- handleInv: "'C'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'C'" 
31:	 pushc 67
-- handleInv: "ch"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
33:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke false 
34:	 storeg ch%$14 5
-- handleInv: "put(ch)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(ch)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(ch)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(ch)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(ch)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "ch"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
36:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke true 
-- doInvoke: "ch" 0 1 useRtnVal: true 
-- doInvoke:X: "ch" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "ch" rec: none 
37:	 pushg 5 ch
-- OI:newInvoke: "put(ch)" rec: none 
39:	 %put 2
-- handleInv: "28"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "28" 
41:	 pushc 28
-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
43:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke false 
44:	 storeg x%$30 2
-- handleInv: "5"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "5" 
46:	 pushc 5
-- handleInv: "z"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "z" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "z" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "z" 0 0 
-- loadOriginII: "z" 
48:	 pushThis 
-- loadOrigin: "z" on: 0 
-- beforedoinvoke false 
49:	 storeg z%$30 4
-- handleInv: "x + z * 8 -- 68 = 'D'"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ z * 8 -- 68 = 'D'" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ z * 8 -- 68 = 'D'" true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x + z * 8 -- 68 = 'D'" 0 1 
-- loadOriginII: "x" 
51:	 pushThis 
-- loadOrigin: "x" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "x" 
-- DI:loadAccessor: "x" 
52:	 pushg 2 x
-- beforedoinvoke true 
-- doInvoke: "x + z * 8 -- 68 = 'D'" 1 2 useRtnVal: true 
-- doInvoke:X: "+ z * 8 -- 68 = 'D'" 1 2 E.label: 
 --  ObjectInvocation_Binary 2 pRec: none rec: "x" ix->next none 
-- handleInv: "z * 8 -- 68 = 'D'"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "z" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "* 8 -- 68 = 'D'" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "* 8 -- 68 = 'D'" true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "z * 8 -- 68 = 'D'" 0 1 
-- loadOriginII: "z" 
54:	 pushThis 
-- loadOrigin: "z" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "z" 
-- DI:loadAccessor: "z" 
55:	 pushg 4 z
-- beforedoinvoke true 
-- doInvoke: "z * 8 -- 68 = 'D'" 1 2 useRtnVal: true 
-- doInvoke:X: "* 8 -- 68 = 'D'" 1 2 E.label: 
 --  ObjectInvocation_Binary 2 pRec: none rec: "z" ix->next none 
-- handleInv: "8 -- 68 = 'D'"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "8 -- 68 = 'D'" 
57:	 pushc 8
-- OI:newInvoke: "* 8" rec: z 
59:	 mult 

-- OI:newInvoke: "+ z * 8" rec: x 
60:	 plus 

-- handleInv: "y"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "y" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "y" 0 0 
-- loadOriginII: "y" 
61:	 pushThis 
-- loadOrigin: "y" on: 0 
-- beforedoinvoke false 
62:	 storeg y%$30 3
-- handleInv: "put(y)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(y)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(y)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(y)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(y)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "y"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "y" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "y" 0 0 
-- loadOriginII: "y" 
64:	 pushThis 
-- loadOrigin: "y" on: 0 
-- beforedoinvoke true 
-- doInvoke: "y" 0 1 useRtnVal: true 
-- doInvoke:X: "y" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "y" rec: none 
65:	 pushg 3 y
-- OI:newInvoke: "put(y)" rec: none 
67:	 %put 2
-- handleInv: "139"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "139" 
69:	 pushc 139
-- handleInv: "y"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "y" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "y" 0 0 
-- loadOriginII: "y" 
71:	 pushThis 
-- loadOrigin: "y" on: 0 
-- beforedoinvoke false 
72:	 storeg y%$30 3
-- handleInv: "y // 2 -- 'E'"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "// 2 -- 'E'" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "// 2 -- 'E'" true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "y // 2 -- 'E'" 0 1 
-- loadOriginII: "y" 
74:	 pushThis 
-- loadOrigin: "y" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "y" 
-- DI:loadAccessor: "y" 
75:	 pushg 3 y
-- beforedoinvoke true 
-- doInvoke: "y // 2 -- 'E'" 1 2 useRtnVal: true 
-- doInvoke:X: "// 2 -- 'E'" 1 2 E.label: 
 --  ObjectInvocation_Binary 2 pRec: none rec: "y" ix->next none 
-- handleInv: "2 -- 'E'"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "2 -- 'E'" 
77:	 pushc 2
-- OI:newInvoke: "// 2" rec: y 
79:	 idiv 

-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
80:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke false 
81:	 storeg x%$30 2
-- handleInv: "put(x)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(x)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(x)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(x)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(x)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "x"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
83:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke true 
-- doInvoke: "x" 0 1 useRtnVal: true 
-- doInvoke:X: "x" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "x" rec: none 
84:	 pushg 2 x
-- OI:newInvoke: "put(x)" rec: none 
86:	 %put 2
-- handleInv: "170"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "170" 
88:	 pushc 170
-- handleInv: "y"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "y" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "y" 0 0 
-- loadOriginII: "y" 
90:	 pushThis 
-- loadOrigin: "y" on: 0 
-- beforedoinvoke false 
91:	 storeg y%$30 3
-- handleInv: "y /% 100"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "/% 100" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "/% 100" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "y /% 100" 0 1 
-- loadOriginII: "y" 
93:	 pushThis 
-- loadOrigin: "y" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "y" 
-- DI:loadAccessor: "y" 
94:	 pushg 3 y
-- beforedoinvoke true 
-- doInvoke: "y /% 100" 1 2 useRtnVal: true 
-- doInvoke:X: "/% 100" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "y" ix->next none 
-- handleInv: "100"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "100" 
96:	 pushc 100
-- OI:newInvoke: "/% 100" rec: y 
98:	 modd 

-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
99:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke false 
100:	 storeg x%$30 2
-- handleInv: "put(x)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(x)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(x)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(x)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(x)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "x"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
102:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke true 
-- doInvoke: "x" 0 1 useRtnVal: true 
-- doInvoke:X: "x" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "x" rec: none 
103:	 pushg 2 x
-- OI:newInvoke: "put(x)" rec: none 
105:	 %put 2
-- handleInv: "3"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "3" 
107:	 pushc 3
-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
109:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke false 
110:	 storeg x%$30 2
-- handleInv: "17"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "17" 
112:	 pushc 17
-- handleInv: "y"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "y" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "y" 0 0 
-- loadOriginII: "y" 
114:	 pushThis 
-- loadOrigin: "y" on: 0 
-- beforedoinvoke false 
115:	 storeg y%$30 3
-- handleInv: "(y - x) * (101 - 96) + 1 -- 'G'    "  staticOff: 0 
 --  doLoad: true useRtnVal: true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "- x" 
-- doLoadII:i<range: "- x" false 
-- loadAccessor: "(y - x) * (101 - 96) + 1 -- 'G'    " 0 2 
-- loadOriginII: "y" 
117:	 pushThis 
-- loadOrigin: "y" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "y" 
-- DI:loadAccessor: "y" 
118:	 pushg 3 y
-- isVirtualDI: pattern false 
-- loadAccessor:X: "- x" rec: "y" 
-- handleInv: "x"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
120:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke true 
-- doInvoke: "x" 0 1 useRtnVal: true 
-- doInvoke:X: "x" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "x" rec: none 
121:	 pushg 2 x
-- OI:newInvoke: "- x" rec: y 
123:	 minus 

-- handleInv:elm: "* (101 - 96)" 
-- doLoadII:i<range: "* (101 - 96)" false 
-- loadAccessor: "(y - x) * (101 - 96) + 1 -- 'G'    " 2 3 
-- isVirtualDI: pattern false 
-- loadAccessor:X: "* (101 - 96)" rec: "- x" 
-- handleInv: "(101 - 96)"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "101" 
124:	 pushc 101
-- handleInv:elm: "- 96" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "- 96" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "(101 - 96)" 1 1 
-- beforedoinvoke true 
-- doInvoke: "(101 - 96)" 1 2 useRtnVal: true 
-- doInvoke:X: "- 96" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "101" ix->next none 
-- handleInv: "96"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "96" 
126:	 pushc 96
-- OI:newInvoke: "- 96" rec: 101 
128:	 minus 

-- OI:newInvoke: "* (101 - 96)" rec: - x 
129:	 mult 

-- handleInv:elm: "+ 1 -- 'G'    " 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ 1 -- 'G'    " true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "(y - x) * (101 - 96) + 1 -- 'G'    " 3 3 
-- beforedoinvoke true 
-- doInvoke: "(y - x) * (101 - 96) + 1 -- 'G'    " 3 4 
 --  useRtnVal: true 
-- doInvoke:X: "+ 1 -- 'G'    " 3 4 E.label: 
 --  ObjectInvocation_Binary 4 pRec: "- x" rec: "* (101 - 96)" ix->next none 
-- handleInv: "1 -- 'G'    "  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "1 -- 'G'    " 
130:	 pushc 1
-- OI:newInvoke: "+ 1" rec: * (101 - 96) 
132:	 plus 

-- handleInv: "z"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "z" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "z" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "z" 0 0 
-- loadOriginII: "z" 
133:	 pushThis 
-- loadOrigin: "z" on: 0 
-- beforedoinvoke false 
134:	 storeg z%$30 4
-- handleInv: "put(z)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(z)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(z)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(z)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(z)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "z"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "z" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "z" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "z" 0 0 
-- loadOriginII: "z" 
136:	 pushThis 
-- loadOrigin: "z" on: 0 
-- beforedoinvoke true 
-- doInvoke: "z" 0 1 useRtnVal: true 
-- doInvoke:X: "z" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "z" rec: none 
137:	 pushg 4 z
-- OI:newInvoke: "put(z)" rec: none 
139:	 %put 2
-- handleInv: "put('H')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('H')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('H')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('H')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('H')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'H'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'H'" 
141:	 pushc 72
-- OI:newInvoke: "put('H')" rec: none 
143:	 %put 2
-- handleInv: "snorf('J')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "snorf('J')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "snorf('J')" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "snorf('J')" 0 0 
-- loadOriginII: "snorf('J')" 
145:	 pushThis 
-- loadOrigin: "snorf('J')" on: 0 
-- beforedoinvoke true 
-- doInvoke: "snorf('J')" 0 1 useRtnVal: false 
-- doInvoke:X: "snorf('J')" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "'J'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'J'" 
146:	 pushc 74
-- OI:newInvoke: "snorf('J')" rec: none 
148:	 invoke snorf$321 321 0 0
154:	 rpop 
-- handleInv: "ParamVVV(70,5) -- pass 70 + 5 = 'K'"  staticOff: 0 
 --  doLoad: true useRtnVal: true 
-- handleInv:elm: "ParamVVV(70,5) -- pass 70 + 5 = 'K'" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "ParamVVV(70,5)" true true "
 --  ObjectInvocation_Function" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ParamVVV(70,5)" 0 0 
-- loadOriginII: "ParamVVV(70,5)" 
155:	 pushThis 
-- loadOrigin: "ParamVVV(70,5)" on: 0 
-- beforedoinvoke true 
-- doInvoke: "ParamVVV(70,5)" 0 1 useRtnVal: true 
-- doInvoke:X: "ParamVVV(70,5)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "70"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "70" 
156:	 pushc 70
-- handleInv: "5"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "5" 
158:	 pushc 5
-- OI:newInvoke: "ParamVVV(70,5)" rec: none 
160:	 invoke ParamVVV$343 343 0 0
166:	 pushg 4 
-- handleInv: "ch"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
168:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke false 
169:	 storeg ch%$14 5
-- handleInv: "put(ch)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(ch)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(ch)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(ch)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(ch)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "ch"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
171:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke true 
-- doInvoke: "ch" 0 1 useRtnVal: true 
-- doInvoke:X: "ch" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "ch" rec: none 
172:	 pushg 5 ch
-- OI:newInvoke: "put(ch)" rec: none 
174:	 %put 2
-- handleInv: "ParamRRR(77)"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "ParamRRR(77)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "ParamRRR(77)" true true "
 --  ObjectInvocation_Function" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ParamRRR(77)" 0 0 
-- loadOriginII: "ParamRRR(77)" 
176:	 pushThis 
-- loadOrigin: "ParamRRR(77)" on: 0 
-- beforedoinvoke true 
-- doInvoke: "ParamRRR(77)" 0 1 useRtnVal: true 
-- doInvoke:X: "ParamRRR(77)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "77"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "77" 
177:	 pushc 77
-- OI:newInvoke: "ParamRRR(77)" rec: none 
179:	 invoke ParamRRR$344 344 0 0
185:	 rpushg  3
-- handleInv: "R"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "R" 
-- handleInv:isVirtualDI: false ref false false 
-- doLoadII:i=range: "R" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "R" 0 0 
-- loadOriginII: "R" 
187:	 pushThis 
-- loadOrigin: "R" on: 0 
-- beforedoinvoke false 
188:	 rstoreg R%$322 6
-- handleInv: "R.get"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "R" 
-- handleInv:isVirtualDI: false ref false false 
-- handleInv:elm: "get" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "R.get" 0 1 
-- loadOriginII: "R" 
190:	 pushThis 
-- loadOrigin: "R" on: 0 
-- isVirtualDI: ref 
-- OI:loadAccessor: "R" 
-- DI:loadAccessor: "R" 
191:	 rpushg R 6
-- beforedoinvoke true 
-- doInvoke: "R.get" 1 2 useRtnVal: true 
-- doInvoke:X: "get" 1 2 E.label: ObjectInvocation_Unary 2 
 --  pRec: none rec: "R" ix->next none 
-- OI:newInvoke: "get" rec: R 
193:	 invoke get$323 323 0 0
199:	 pushg 2 
-- handleInv: "ch"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
201:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke false 
202:	 storeg ch%$14 5
-- handleInv: "'T'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'T'" 
204:	 pushc 84
-- handleInv: "ch"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
206:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke false 
207:	 storeg ch%$14 5
-- handleInv: "ArrayXX"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "ArrayXX" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "ArrayXX" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ArrayXX" 0 0 
-- loadOriginII: "ArrayXX" 
209:	 pushThis 
-- loadOrigin: "ArrayXX" on: 0 
-- beforedoinvoke true 
-- doInvoke: "ArrayXX" 0 1 useRtnVal: false 
-- doInvoke:X: "ArrayXX" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "ArrayXX" rec: none 
210:	 invoke ArrayXX$329 329 0 0
216:	 rpop 
-- handleInv: "'W'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'W'" 
217:	 pushc 87
-- handleInv: "ch"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
219:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke false 
220:	 storeg ch%$14 5
222:	 pushThis 
223:	 invoke doPut:exe$S$348 348 0 0
229:	 rpop 
-- handleInv: "Greating"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "Greating" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Greating" true true "
 --  ObjectInvocation_Unary" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Greating" 0 0 
-- loadOriginII: "Greating" 
230:	 pushThis 
-- loadOrigin: "Greating" on: 0 
-- beforedoinvoke true 
-- doInvoke: "Greating" 0 1 useRtnVal: false 
-- doInvoke:X: "Greating" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "Greating" rec: none 
231:	 invoke Greating$339 339 0 0
237:	 rpop 
-- handleInv: "Main"  staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "Main" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Main" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Main" 0 0 
-- loadOriginII: "Main" 
238:	 pushThis 
-- loadOrigin: "Main" on: 0 
-- beforedoinvoke true 
-- doInvoke: "Main" 0 1 useRtnVal: false 
-- doInvoke:X: "Main" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "Main" rec: none 
239:	 invoke Main$342 342 0 0
245:	 rpop 
-- handleInv: "putint(117)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "putint(117)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "putint(117)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "putint(117)" 0 1 useRtnVal: false 
-- doInvoke:X: "putint(117)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "117"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "117" 
246:	 pushc 117
-- OI:newInvoke: "putint(117)" rec: none 
248:	 invoke putint$191 191 0 0
254:	 rpop 
-- handleInv: ""\nHello world!\n".print"  staticOff: 0 doLoad: 
 --  true useRtnVal: false 
-- handleInv:elm: ""\nHello world!\n"" 
255:	 pushText "\nHello world!\n"
-- handleInv:elm: "print" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "print" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: ""\nHello world!\n".print" 1 1 
-- beforedoinvoke true 
-- doInvoke: ""\nHello world!\n".print" 1 2 useRtnVal: false 
-- doInvoke:X: "print" 1 2 E.label: ObjectInvocation_Unary 2 
 --  pRec: none rec: ""\nHello world!\n"" ix->next none 
-- OI:newInvoke: "print" rec: "\nHello world!\n" 
257:	 invoke print$103 103 0 0
263:	 rpop 
-- handleInv: "Record"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "Record" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Record" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Record" 0 0 
-- loadOriginII: "Record" 
264:	 pushThis 
-- loadOrigin: "Record" on: 0 
-- beforedoinvoke true 
-- doInvoke: "Record" 0 1 useRtnVal: true 
-- doInvoke:X: "Record" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "Record" rec: none 
265:	 invoke Record$322 322 0 1
-- handleInv: "R"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "R" 
-- handleInv:isVirtualDI: false ref false false 
-- doLoadII:i=range: "R" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "R" 0 0 
-- loadOriginII: "R" 
271:	 pushThis 
-- loadOrigin: "R" on: 0 
-- beforedoinvoke false 
272:	 rstoreg R%$322 6
-- handleInv: "fooBar(81,9,R)"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "fooBar(81,9,R)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "fooBar(81,9,R)" true true "
 --  ObjectInvocation_Function" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "fooBar(81,9,R)" 0 0 
-- loadOriginII: "fooBar(81,9,R)" 
274:	 pushThis 
-- loadOrigin: "fooBar(81,9,R)" on: 0 
-- beforedoinvoke true 
-- doInvoke: "fooBar(81,9,R)" 0 1 useRtnVal: true 
-- doInvoke:X: "fooBar(81,9,R)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "81"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "81" 
275:	 pushc 81
-- handleInv: "9"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "9" 
277:	 pushc 9
-- handleInv: "R"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "R" 
-- handleInv:isVirtualDI: false ref false false 
-- doLoadII:i=range: "R" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "R" 0 0 
-- loadOriginII: "R" 
279:	 pushThis 
-- loadOrigin: "R" on: 0 
-- beforedoinvoke true 
-- doInvoke: "R" 0 1 useRtnVal: true 
-- doInvoke:X: "R" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "R" rec: none 
280:	 rpushg R 6
-- OI:newInvoke: "fooBar(81,9,R)" rec: none 
282:	 invoke fooBar$324 324 0 0
288:	 pushg 5 
-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
290:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke false 
291:	 storeg x%$30 2
-- handleInv: "fooBar(81,9,Record)"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "fooBar(81,9,Record)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "fooBar(81,9,Record)" true true "
 --  ObjectInvocation_Function" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "fooBar(81,9,Record)" 0 0 
-- loadOriginII: "fooBar(81,9,Record)" 
293:	 pushThis 
-- loadOrigin: "fooBar(81,9,Record)" on: 0 
-- beforedoinvoke true 
-- doInvoke: "fooBar(81,9,Record)" 0 1 useRtnVal: true 
-- doInvoke:X: "fooBar(81,9,Record)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "81"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "81" 
294:	 pushc 81
-- handleInv: "9"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "9" 
296:	 pushc 9
-- handleInv: "Record"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "Record" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Record" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Record" 0 0 
-- loadOriginII: "Record" 
298:	 pushThis 
-- loadOrigin: "Record" on: 0 
-- beforedoinvoke true 
-- doInvoke: "Record" 0 1 useRtnVal: true 
-- doInvoke:X: "Record" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "Record" rec: none 
299:	 invoke Record$322 322 0 1
-- OI:newInvoke: "fooBar(81,9,Record)" rec: none 
305:	 invoke fooBar$324 324 0 0
311:	 pushg 5 
-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
313:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke false 
314:	 storeg x%$30 2
-- handleInv: "putint(x)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "putint(x)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "putint(x)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "putint(x)" 0 1 useRtnVal: false 
-- doInvoke:X: "putint(x)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "x"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
316:	 pushThis 
-- loadOrigin: "x" on: 0 
-- beforedoinvoke true 
-- doInvoke: "x" 0 1 useRtnVal: true 
-- doInvoke:X: "x" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "x" rec: none 
317:	 pushg 2 x
-- OI:newInvoke: "putint(x)" rec: none 
319:	 invoke putint$191 191 0 0
325:	 rpop 
-- handleInv: "fisk"  staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "fisk" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "fisk" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "fisk" 0 0 
-- loadOriginII: "fisk" 
326:	 pushThis 
-- loadOrigin: "fisk" on: 0 
-- beforedoinvoke true 
-- doInvoke: "fisk" 0 1 useRtnVal: false 
-- doInvoke:X: "fisk" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "fisk" rec: none 
327:	 invoke fisk$325 325 0 0
333:	 rpop 
L2:
334:	 setThisStack 
335:	 pushThis 
336:	 rtn D
338:	 END OSDV:0 objSize:6 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:320 V 2:0 V 3:0 V 4:0 

CLASS Record$322 dNo:322 topDno:322 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  get: 
 --     out V:var integer
 --     V := 78
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  get: 
 --     out V:var integer
 --     V := 78
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:322 V 2:0 V 3:0 V 4:0 

CLASS put$81 dNo:81 topDno:81 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %globals
 --  %basic 2
 --  in ch: val char
 --  
-- arg: in ch: val char isVirtualDataItem: false primNo: 3 
-- before:currentArg.store: mainIS: 
 --  %globals
 --  %basic 2
 --  in ch: val char
 --  
1:	 pushThis 
2:	 storeg ch%$14 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %globals
 --  %basic 2
 --  in ch: val char
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:81 V 2:0 V 3:0 V 4:0 

CLASS snorf$321 dNo:321 topDno:321 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  in Q:var integer
 --  put('I')
 --  put(Q)
 --  
-- arg: in Q:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  in Q:var integer
 --  put('I')
 --  put(Q)
 --  
1:	 pushThis 
2:	 storeg Q%$30 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
4:	 tstOriginIsNone 
5:	 rstore  1 origin
-- AllocateSuper: 
 --  in Q:var integer
 --  put('I')
 --  put(Q)
 --  
7:	 allocEventQ 
9:	 mvStack 
10:	 rtnAlloc 1
DO:
12:	 doEventQ 
13:	 mvStack 
L1:
-- handleInv: "put('I')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('I')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('I')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('I')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('I')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'I'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'I'" 
14:	 pushc 73
-- OI:newInvoke: "put('I')" rec: none 
16:	 %put 2
-- handleInv: "put(Q)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(Q)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(Q)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(Q)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(Q)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "Q"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "Q" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "Q" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Q" 0 0 
-- loadOriginII: "Q" 
18:	 pushThis 
-- loadOrigin: "Q" on: 0 
-- beforedoinvoke true 
-- doInvoke: "Q" 0 1 useRtnVal: true 
-- doInvoke:X: "Q" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "Q" rec: none 
19:	 pushg 2 Q
-- OI:newInvoke: "put(Q)" rec: none 
21:	 %put 2
L2:
23:	 setThisStack 
24:	 pushThis 
25:	 rtn D
27:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:321 V 2:0 V 3:0 V 4:0 

CLASS ParamVVV$343 dNo:343 topDno:343 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  in x:var integer
 --  in y:var integer
 --  out v:var integer
 --  put(x + y)
-- arg: in y:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  in x:var integer
 --  in y:var integer
 --  out v:var integer
 --  put(x + y)
1:	 pushThis 
2:	 storeg y%$30 3
-- arg: in x:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  in x:var integer
 --  in y:var integer
 --  out v:var integer
 --  put(x + y)
4:	 pushThis 
5:	 storeg x%$30 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
7:	 tstOriginIsNone 
8:	 rstore  1 origin
-- AllocateSuper: 
 --  in x:var integer
 --  in y:var integer
 --  out v:var integer
 --  put(x + y)
10:	 allocEventQ 
12:	 mvStack 
13:	 rtnAlloc 1
DO:
15:	 doEventQ 
16:	 mvStack 
L1:
-- handleInv: "put(x + y)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(x + y)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(x + y)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(x + y)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(x + y)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "x + y"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ y" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ y" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x + y" 0 1 
-- loadOriginII: "x" 
17:	 pushThis 
-- loadOrigin: "x" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "x" 
-- DI:loadAccessor: "x" 
18:	 pushg 2 x
-- beforedoinvoke true 
-- doInvoke: "x + y" 1 2 useRtnVal: true 
-- doInvoke:X: "+ y" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "x" ix->next none 
-- handleInv: "y"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "y" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "y" 0 0 
-- loadOriginII: "y" 
20:	 pushThis 
-- loadOrigin: "y" on: 0 
-- beforedoinvoke true 
-- doInvoke: "y" 0 1 useRtnVal: true 
-- doInvoke:X: "y" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "y" rec: none 
21:	 pushg 3 y
-- OI:newInvoke: "+ y" rec: x 
23:	 plus 

-- OI:newInvoke: "put(x + y)" rec: none 
24:	 %put 2
-- handleInv: "x + y + 1"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ y" 
-- doLoadII:i<range: "+ y" false 
-- loadAccessor: "x + y + 1" 0 2 
-- loadOriginII: "x" 
26:	 pushThis 
-- loadOrigin: "x" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "x" 
-- DI:loadAccessor: "x" 
27:	 pushg 2 x
-- isVirtualDI: pattern false 
-- loadAccessor:X: "+ y" rec: "x" 
-- handleInv: "y"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "y" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "y" 0 0 
-- loadOriginII: "y" 
29:	 pushThis 
-- loadOrigin: "y" on: 0 
-- beforedoinvoke true 
-- doInvoke: "y" 0 1 useRtnVal: true 
-- doInvoke:X: "y" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "y" rec: none 
30:	 pushg 3 y
-- OI:newInvoke: "+ y" rec: x 
32:	 plus 

-- handleInv:elm: "+ 1" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ 1" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x + y + 1" 2 2 
-- beforedoinvoke true 
-- doInvoke: "x + y + 1" 2 3 useRtnVal: true 
-- doInvoke:X: "+ 1" 2 3 E.label: ObjectInvocation_Binary 3 
 --  pRec: "x" rec: "+ y" ix->next none 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
33:	 pushc 1
-- OI:newInvoke: "+ 1" rec: + y 
35:	 plus 

-- handleInv: "v"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "v" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "v" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "v" 0 0 
-- loadOriginII: "v" 
36:	 pushThis 
-- loadOrigin: "v" on: 0 
-- beforedoinvoke false 
37:	 storeg v%$30 4
L2:
39:	 setThisStack 
40:	 pushThis 
41:	 rtn D
43:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:343 V 2:0 V 3:0 V 4:0 

CLASS ParamRRR$344 dNo:344 topDno:344 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  in ch:var Char
 --  out R: ref Record
 --  put(ch)
 --  R := Record
 --  
-- arg: in ch:var Char isVirtualDataItem: false primNo: 3 
-- before:currentArg.store: mainIS: 
 --  in ch:var Char
 --  out R: ref Record
 --  put(ch)
 --  R := Record
 --  
1:	 pushThis 
2:	 storeg ch%$14 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
4:	 tstOriginIsNone 
5:	 rstore  1 origin
-- AllocateSuper: 
 --  in ch:var Char
 --  out R: ref Record
 --  put(ch)
 --  R := Record
 --  
7:	 allocEventQ 
9:	 mvStack 
10:	 rtnAlloc 1
DO:
12:	 doEventQ 
13:	 mvStack 
L1:
-- handleInv: "put(ch)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(ch)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(ch)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(ch)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(ch)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "ch"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
14:	 pushThis 
-- loadOrigin: "ch" on: 0 
-- beforedoinvoke true 
-- doInvoke: "ch" 0 1 useRtnVal: true 
-- doInvoke:X: "ch" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "ch" rec: none 
15:	 pushg 2 ch
-- OI:newInvoke: "put(ch)" rec: none 
17:	 %put 2
-- handleInv: "Record"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "Record" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Record" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Record" 0 0 
-- loadOriginII: "Record" 
19:	 pushThis 
-- loadOrigin: "Record" on: 1 
20:	 rpushg ParamRRR$344 1
-- beforedoinvoke true 
-- doInvoke: "Record" 0 1 useRtnVal: true 
-- doInvoke:X: "Record" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "Record" rec: none 
22:	 invoke Record$322 322 0 1
-- handleInv: "R"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "R" 
-- handleInv:isVirtualDI: false ref false false 
-- doLoadII:i=range: "R" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "R" 0 0 
-- loadOriginII: "R" 
28:	 pushThis 
-- loadOrigin: "R" on: 0 
-- beforedoinvoke false 
29:	 rstoreg R%$322 3
L2:
31:	 setThisStack 
32:	 pushThis 
33:	 rtn D
35:	 END OSDV:0 objSize:3 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:344 V 2:0 V 3:0 V 4:0 

CLASS get$323 dNo:323 topDno:323 orgOff:1 orgId:Record$322 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  out V:var integer
 --  V := 78
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  out V:var integer
 --  V := 78
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "78"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "78" 
11:	 pushc 78
-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
13:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke false 
14:	 storeg V%$30 2
L2:
16:	 setThisStack 
17:	 pushThis 
18:	 rtn D
20:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:323 V 2:0 V 3:0 V 4:0 

CLASS ArrayXX$329 dNo:329 topDno:329 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  XXX: obj Array(10,#integer)
 --  V:var integer
 --  XXX.put(78):at[3] -- 'N'
 --  V := XXX.get[3]
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  XXX: obj Array(10,#integer)
 --  V:var integer
 --  XXX.put(78):at[3] -- 'N'
 --  V := XXX.get[3]
4:	 allocEventQ 
6:	 mvStack 
-- handleInv: "Array(10,#integer)"  staticOff: 2 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "Array(10,#integer)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Array(10,#integer)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "Array(10,#integer)" 0 1 useRtnVal: false 
-- doInvoke:X: "Array(10,#integer)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "10"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "10" 
7:	 pushc 10
-- OI:newInvoke: "Array(10,#integer)" rec: none 
9:	 pushThis 
10:	 pushc 1
12:	 allocIndexed ArrayXX$329%$329 124 1 0
17:	 pushThis 
18:	 rstoreg ArrayXX$329%$329 2
20:	 rtnAlloc 1
DO:
22:	 doEventQ 
23:	 mvStack 
L1:
-- handleInv: "XXX.put(78):at[3] -- 'N'"  staticOff: 0 doLoad: 
 --  true useRtnVal: false 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "put(78):at[3] -- 'N'" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(78):at[3]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "XXX.put(78):at[3]" 0 1 
-- loadOriginII: "XXX" 
24:	 pushThis 
-- loadOrigin: "XXX" on: 0 
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
25:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.put(78):at[3]" 1 2 useRtnVal: false 
-- doInvoke:X: "put(78):at[3]" 1 2 E.label: 
 --  ObjectInvocation_KeyWord 2 pRec: none rec: "XXX" ix->next none 
-- handleInv: "78"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "78" 
27:	 pushc 78
-- handleInv: "3"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "3" 
29:	 pushc 3
-- OI:newInvoke: "put(78):at[3]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
31:	 xstoreg inx  size:1 isValueObj:0
-- handleInv: "XXX.get[3]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "get[3]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[3]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "XXX.get[3]" 0 1 
-- loadOriginII: "XXX" 
34:	 pushThis 
-- loadOrigin: "XXX" on: 0 
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
35:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.get[3]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[3]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "XXX" ix->next none 
-- handleInv: "3"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "3" 
37:	 pushc 3
-- OI:newInvoke: "get[3]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
39:	 xpushg  inx 1 0
-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
42:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke false 
43:	 storeg V%$30 3
-- handleInv: "put(V)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(V)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(V)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(V)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(V)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
45:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke true 
-- doInvoke: "V" 0 1 useRtnVal: true 
-- doInvoke:X: "V" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "V" rec: none 
46:	 pushg 3 V
-- OI:newInvoke: "put(V)" rec: none 
48:	 %put 2
-- handleInv: "XXX.put(79):at[1] -- 'O'"  staticOff: 0 doLoad: 
 --  true useRtnVal: false 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "put(79):at[1] -- 'O'" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(79):at[1]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "XXX.put(79):at[1]" 0 1 
-- loadOriginII: "XXX" 
50:	 pushThis 
-- loadOrigin: "XXX" on: 0 
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
51:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.put(79):at[1]" 1 2 useRtnVal: false 
-- doInvoke:X: "put(79):at[1]" 1 2 E.label: 
 --  ObjectInvocation_KeyWord 2 pRec: none rec: "XXX" ix->next none 
-- handleInv: "79"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "79" 
53:	 pushc 79
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
55:	 pushc 1
-- OI:newInvoke: "put(79):at[1]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
57:	 xstoreg inx  size:1 isValueObj:0
-- handleInv: "XXX.get[1]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "get[1]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[1]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "XXX.get[1]" 0 1 
-- loadOriginII: "XXX" 
60:	 pushThis 
-- loadOrigin: "XXX" on: 0 
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
61:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.get[1]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[1]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "XXX" ix->next none 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
63:	 pushc 1
-- OI:newInvoke: "get[1]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
65:	 xpushg  inx 1 0
-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
68:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke false 
69:	 storeg V%$30 3
-- handleInv: "put(V)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(V)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(V)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(V)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(V)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
71:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke true 
-- doInvoke: "V" 0 1 useRtnVal: true 
-- doInvoke:X: "V" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "V" rec: none 
72:	 pushg 3 V
-- OI:newInvoke: "put(V)" rec: none 
74:	 %put 2
-- handleInv: "XXX.put(80):at[10] -- 'P'"  staticOff: 0 doLoad: 
 --  true useRtnVal: false 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "put(80):at[10] -- 'P'" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(80):at[10]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "XXX.put(80):at[10]" 0 1 
-- loadOriginII: "XXX" 
76:	 pushThis 
-- loadOrigin: "XXX" on: 0 
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
77:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.put(80):at[10]" 1 2 useRtnVal: false 
-- doInvoke:X: "put(80):at[10]" 1 2 E.label: 
 --  ObjectInvocation_KeyWord 2 pRec: none rec: "XXX" ix->next none 
-- handleInv: "80"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "80" 
79:	 pushc 80
-- handleInv: "10"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "10" 
81:	 pushc 10
-- OI:newInvoke: "put(80):at[10]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
83:	 xstoreg inx  size:1 isValueObj:0
-- handleInv: "XXX.get[10]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "get[10]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[10]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "XXX.get[10]" 0 1 
-- loadOriginII: "XXX" 
86:	 pushThis 
-- loadOrigin: "XXX" on: 0 
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
87:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.get[10]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[10]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "XXX" ix->next none 
-- handleInv: "10"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "10" 
89:	 pushc 10
-- OI:newInvoke: "get[10]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
91:	 xpushg  inx 1 0
-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
94:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke false 
95:	 storeg V%$30 3
-- handleInv: "put(V)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(V)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(V)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(V)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(V)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
97:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke true 
-- doInvoke: "V" 0 1 useRtnVal: true 
-- doInvoke:X: "V" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "V" rec: none 
98:	 pushg 3 V
-- OI:newInvoke: "put(V)" rec: none 
100:	 %put 2
102:	 pushThis 
103:	 invoke for:to:repeat$S$331 331 0 0
109:	 rpop 
110:	 pushThis 
111:	 invoke for:to:repeat$S$333 333 0 0
117:	 rpop 
-- handleInv: "put(ch)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(ch)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(ch)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(ch)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(ch)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "ch"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
118:	 pushThis 
-- loadOrigin: "ch" on: 1 
119:	 rpushg ArrayXX$329 1
-- beforedoinvoke true 
-- doInvoke: "ch" 0 1 useRtnVal: true 
-- doInvoke:X: "ch" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "ch" rec: none 
121:	 pushg 5 ch
-- OI:newInvoke: "put(ch)" rec: none 
123:	 %put 2
-- handleInv: "'U'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'U'" 
125:	 pushc 85
-- handleInv: "ch"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
127:	 pushThis 
-- loadOrigin: "ch" on: 1 
128:	 rpushg ArrayXX$329 1
-- beforedoinvoke false 
130:	 storeg ch%$14 5
L2:
132:	 setThisStack 
133:	 pushThis 
134:	 rtn D
136:	 END OSDV:0 objSize:3 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:329 V 2:0 V 3:0 V 4:0 

CLASS Array$124 dNo:124 topDno:124 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %globals
 --  %basic 114
 --  %public
 --  length: 
-- arg: range:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  %globals
 --  %basic 114
 --  %public
 --  length: 
1:	 pushThis 
2:	 storeg range%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %globals
 --  %basic 114
 --  %public
 --  length: 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:1
-- endNewVirtDefs: 
-- vdtTable:final: I 1:124 V 2:0 V 3:0 V 4:0 

CLASS Object$S$330 dNo:330 topDno:330 orgOff:1 orgId:for:to:repeat$S$331 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "XXX.put('P' + inx):at[inx]" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "XXX.put('P' + inx):at[inx]" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "XXX.put('P' + inx):at[inx]"  staticOff: 0 doLoad: 
 --  true useRtnVal: false 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "put('P' + inx):at[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('P' + inx):at[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "XXX.put('P' + inx):at[inx]" 0 1 
-- loadOriginII: "XXX" 
11:	 pushThis 
-- loadOrigin: "XXX" on: 2 
12:	 rpushg Object$S$330 1
14:	 rpushg for:to:repeat$S$331 4
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
16:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.put('P' + inx):at[inx]" 1 2 useRtnVal: false 
-- doInvoke:X: "put('P' + inx):at[inx]" 1 2 E.label: 
 --  ObjectInvocation_KeyWord 2 pRec: none rec: "XXX" ix->next none 
-- handleInv: "'P' + inx"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "'P'" 
18:	 pushc 80
-- handleInv:elm: "+ inx" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ inx" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "'P' + inx" 1 1 
-- beforedoinvoke true 
-- doInvoke: "'P' + inx" 1 2 useRtnVal: true 
-- doInvoke:X: "+ inx" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "'P'" ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
20:	 pushThis 
-- loadOrigin: "inx" on: 1 
21:	 rpushg Object$S$330 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
23:	 pushg 3 inx
-- OI:newInvoke: "+ inx" rec: 'P' 
25:	 plus 

-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
26:	 pushThis 
-- loadOrigin: "inx" on: 1 
27:	 rpushg Object$S$330 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
29:	 pushg 3 inx
-- OI:newInvoke: "put('P' + inx):at[inx]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
31:	 xstoreg inx  size:1 isValueObj:0
L2:
34:	 setThisStack 
35:	 pushThis 
36:	 rtn D
38:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:330 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$S$331 dNo:331 topDno:109 orgOff:4 orgId:ArrayXX$329 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  4 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
4:	 pushc 1
-- handleInv: "3"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "3" 
6:	 pushc 3
-- handleArgOrg:super: 
 --  for(first:var integer):to(last:var integer):repeat{repeat:< object}$109 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
8:	 pushThis 
9:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
11:	 pushThis 
12:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
14:	 allocEventQ 
16:	 rtnAlloc 1
18:	 toSuper  109
DO:
21:	 mvStack 
L1:
L2:
22:	 rtnInner  M
23:	 END OSDV:1 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:330 V 4:0 

CLASS Object$S$332 dNo:332 topDno:332 orgOff:1 orgId:for:to:repeat$S$333 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "put(XXX.get[inx])" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "put(XXX.get[inx])" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "put(XXX.get[inx])"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "put(XXX.get[inx])" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(XXX.get[inx])" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(XXX.get[inx])" 0 1 useRtnVal: false 
-- doInvoke:X: "put(XXX.get[inx])" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "XXX.get[inx]"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "XXX" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "XXX.get[inx]" 0 1 
-- loadOriginII: "XXX" 
11:	 pushThis 
-- loadOrigin: "XXX" on: 2 
12:	 rpushg Object$S$332 1
14:	 rpushg for:to:repeat$S$333 4
-- isVirtualDI: obj 
-- OI:loadAccessor: "XXX" 
-- DI:loadAccessor: "XXX" 
16:	 rpushg XXX 2
-- beforedoinvoke true 
-- doInvoke: "XXX.get[inx]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[inx]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "XXX" ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
18:	 pushThis 
-- loadOrigin: "inx" on: 1 
19:	 rpushg Object$S$332 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
21:	 pushg 3 inx
-- OI:newInvoke: "get[inx]" rec: XXX 
-- getIndexedArgs:rec.ATd: XXX: obj Array(10,#integer)
23:	 xpushg  inx 1 0
-- OI:newInvoke: "put(XXX.get[inx])" rec: none 
26:	 %put 2
L2:
28:	 setThisStack 
29:	 pushThis 
30:	 rtn D
32:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:332 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$S$333 dNo:333 topDno:109 orgOff:4 orgId:ArrayXX$329 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  4 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
4:	 pushc 1
-- handleInv: "3"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "3" 
6:	 pushc 3
-- handleArgOrg:super: 
 --  for(first:var integer):to(last:var integer):repeat{repeat:< object}$109 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
8:	 pushThis 
9:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
11:	 pushThis 
12:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
14:	 allocEventQ 
16:	 rtnAlloc 1
18:	 toSuper  109
DO:
21:	 mvStack 
L1:
L2:
22:	 rtnInner  M
23:	 END OSDV:1 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:332 V 4:0 

CLASS doPut:exe$345 dNo:345 topDno:345 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  put(V)
 --  S
 --  
-- arg: V:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  put(V)
 --  S
 --  
1:	 pushThis 
2:	 storeg V%$30 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
4:	 tstOriginIsNone 
5:	 rstore  1 origin
-- AllocateSuper: 
 --  put(V)
 --  S
 --  
7:	 allocEventQ 
9:	 mvStack 
10:	 rtnAlloc 1
DO:
12:	 doEventQ 
13:	 mvStack 
L1:
-- handleInv: "put(V)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(V)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(V)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(V)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(V)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
14:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke true 
-- doInvoke: "V" 0 1 useRtnVal: true 
-- doInvoke:X: "V" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "V" rec: none 
15:	 pushg 2 V
-- OI:newInvoke: "put(V)" rec: none 
17:	 %put 2
-- handleInv: "S"  staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "S" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "S" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "S" 0 0 
-- loadOriginII: "S" 
19:	 pushThis 
-- loadOrigin: "S" on: 0 
-- beforedoinvoke true 
-- doInvoke: "S" 0 1 useRtnVal: false 
-- doInvoke:X: "S" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "S" rec: none 
20:	 invokev 3 0 S$346$346 0
24:	 rpop 
L2:
25:	 setThisStack 
26:	 pushThis 
27:	 rtn D
29:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:345 V 2:0 V 3:346 V 4:0 

CLASS S$346 dNo:346 topDno:44 orgOff:1 orgId:doPut:exe$345 orgDno:345 isVstub

DO:
1:	 invoke Object$44 44 0 0
7:	 pushThis 
8:	 rstoreg  2
10:	 setThisStack 
11:	 pushThis 
12:	 rpushg  2
14:	 rtn D
16:	 END OSDV:0 objSize:3 isIndexed:0

CLASS Object$S$347 dNo:347 topDno:347 orgOff:1 orgId:doPut:exe$S$348 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  put('V')
 --  put(ch)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  put('V')
 --  put(ch)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "put('V')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('V')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('V')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('V')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('V')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'V'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'V'" 
11:	 pushc 86
-- OI:newInvoke: "put('V')" rec: none 
13:	 %put 2
-- handleInv: "put(ch)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(ch)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(ch)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(ch)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(ch)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "ch"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
15:	 pushThis 
-- loadOrigin: "ch" on: 2 
16:	 rpushg Object$S$347 1
18:	 rpushg doPut:exe$S$348 1
-- beforedoinvoke true 
-- doInvoke: "ch" 0 1 useRtnVal: true 
-- doInvoke:X: "ch" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "ch" rec: none 
20:	 pushg 5 ch
-- OI:newInvoke: "put(ch)" rec: none 
22:	 %put 2
L2:
24:	 setThisStack 
25:	 pushThis 
26:	 rtn D
28:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:347 V 2:0 V 3:0 V 4:0 

CLASS doPut:exe$S$348 dNo:348 topDno:345 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: 
 --  doPut('U'):exe
 --     put('V')
 --     put(ch)
 --   staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: 
 --  doPut('U'):exe
 --     put('V')
 --     put(ch)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  doPut('U'):exe
 --     put('V')
 --     put(ch)
 --  true true "ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: 
 --  doPut('U'):exe
 --     put('V')
 --     put(ch)
 --  0 0 
-- loadOriginII: 
 --  doPut('U'):exe
 --     put('V')
 --     put(ch)
 --  
4:	 pushThis 
-- loadOrigin: "doPut('U'):exe
 --     put('V')
 --     put(ch)
 --  " on: 0 
5:	 rpushg hello$320%$320 1
-- beforedoinvoke false 
-- handleInv: "'U'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'U'" 
7:	 pushc 85
-- handleArgOrg:super: doPut(V:var integer):exe(S:< Object)$345 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: V:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
9:	 pushThis 
10:	 storeg V%$30 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
12:	 tstOriginIsNone 
13:	 rstore  1 origin
-- AllocateSuper: 
 --  put(V)
 --  S
 --  
15:	 allocEventQ 
17:	 rtnAlloc 1
19:	 toSuper  345
DO:
22:	 mvStack 
L1:
L2:
23:	 rtnInner  M
24:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:345 V 2:0 V 3:347 V 4:0 

CLASS helloWorld$334 dNo:334 topDno:334 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  how:< Object
 --  are:< Object
 --  you:< Person
 --  how
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  how:< Object
 --  are:< Object
 --  you:< Person
 --  how
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: 
 --  how
 --        --you 
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "how" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "how" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: 
 --  how
 --        --you 
 --  0 0 
-- loadOriginII: "how" 
11:	 pushThis 
-- loadOrigin: "how" on: 0 
-- beforedoinvoke true 
-- doInvoke: 
 --  how
 --        --you 
 --  0 1 useRtnVal: false 
-- doInvoke:X: "how" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "how" rec: none 
12:	 invokev 3 0 how$335$335 0
16:	 rpop 
-- handleInv: "are"  staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "are" 
-- handleInv:isVirtualDI: false pattern true true 
-- doLoadII:i=range: "are" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "are" 0 0 
-- loadOriginII: "are" 
17:	 pushThis 
-- loadOrigin: "are" on: 0 
-- beforedoinvoke true 
-- doInvoke: "are" 0 1 useRtnVal: false 
-- doInvoke:X: "are" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "are" rec: none 
18:	 invokev 4 0 are$336$336 0
22:	 rpop 
L2:
23:	 setThisStack 
24:	 pushThis 
25:	 rtn D
27:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:334 V 2:0 V 3:335 V 4:336 V 5:338 

CLASS how$335 dNo:335 topDno:44 orgOff:1 orgId:helloWorld$334 orgDno:334 isVstub

DO:
1:	 invoke Object$44 44 0 0
7:	 pushThis 
8:	 rstoreg  2
10:	 setThisStack 
11:	 pushThis 
12:	 rpushg  2
14:	 rtn D
16:	 END OSDV:0 objSize:3 isIndexed:0

CLASS are$336 dNo:336 topDno:44 orgOff:1 orgId:helloWorld$334 orgDno:334 isVstub

DO:
1:	 invoke Object$44 44 0 0
7:	 pushThis 
8:	 rstoreg  2
10:	 setThisStack 
11:	 pushThis 
12:	 rpushg  2
14:	 rtn D
16:	 END OSDV:0 objSize:3 isIndexed:0

CLASS you$338 dNo:338 topDno:44 orgOff:1 orgId:helloWorld$334 orgDno:334 isVstub

DO:
1:	 rpushg helloWorld$334 1
3:	 invoke Person$337 337 0 0
9:	 pushThis 
10:	 rstoreg  2
12:	 setThisStack 
13:	 pushThis 
14:	 rpushg  2
16:	 rtn D
18:	 END OSDV:0 objSize:3 isIndexed:0

CLASS Person$337 dNo:337 topDno:337 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  put('P')
 --  inner(Person)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  put('P')
 --  inner(Person)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "put('P')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('P')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('P')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('P')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('P')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'P'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'P'" 
11:	 pushc 80
-- OI:newInvoke: "put('P')" rec: none 
13:	 %put 2
-- handleInv: "inner(Person)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "inner(Person)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(Person)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(Person)" 0 0 
-- loadOriginII: "inner(Person)" 
-- beforedoinvoke true 
-- doInvoke: "inner(Person)" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(Person)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(Person)" rec: none 
15:	 pushThis 
16:	 innerP  3
18:	 rpopThisObj 
L2:
19:	 setThisStack 
20:	 pushThis 
21:	 rtn D
23:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:337 V 2:0 I 3:0 V 4:0 

CLASS Greating$339 dNo:339 topDno:334 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  how:: 
 --     put('H')
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  how:: 
 --     put('H')
 --  
-- push:super.origin: 
-- handleInv: "helloWorld"  staticOff: 0 doLoad: false useRtnVal: 
 --  false 
-- handleInv:elm: "helloWorld" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "helloWorld" true true "
 --  ObjectInvocation_Unary" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "helloWorld" 0 0 
-- loadOriginII: "helloWorld" 
4:	 pushThis 
-- loadOrigin: "helloWorld" on: 0 
5:	 rpushg hello$320%$320 1
-- beforedoinvoke false 
-- handleArgOrg:super: helloWorld$334 
-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  how:: 
 --     put('H')
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
7:	 tstOriginIsNone 
8:	 rstore  1 origin
-- AllocateSuper: 
 --  how:< Object
 --  are:< Object
 --  you:< Person
 --  how
10:	 allocEventQ 
12:	 rtnAlloc 1
14:	 toSuper  334
DO:
17:	 mvStack 
L1:
L2:
18:	 rtnInner  M
19:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:334 V 2:0 V 3:340 V 4:336 V 5:338 

CLASS how$340 dNo:340 topDno:340 orgOff:1 orgId:Greating$339 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "put('H')" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "put('H')" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "put('H')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('H')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('H')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('H')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('H')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'H'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'H'" 
11:	 pushc 72
-- OI:newInvoke: "put('H')" rec: none 
13:	 %put 2
L2:
15:	 setThisStack 
16:	 pushThis 
17:	 rtn D
19:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:340 V 2:0 V 3:0 V 4:0 

CLASS Super$341 dNo:341 topDno:341 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  put('S')
 --  inner(Super)
 --  put(ch)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  put('S')
 --  inner(Super)
 --  put(ch)
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "put('S')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('S')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('S')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('S')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('S')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'S'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'S'" 
11:	 pushc 83
-- OI:newInvoke: "put('S')" rec: none 
13:	 %put 2
-- handleInv: "inner(Super)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "inner(Super)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(Super)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(Super)" 0 0 
-- loadOriginII: "inner(Super)" 
-- beforedoinvoke true 
-- doInvoke: "inner(Super)" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(Super)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(Super)" rec: none 
15:	 pushThis 
16:	 innerP  3
18:	 rpopThisObj 
-- handleInv: "put(ch)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put(ch)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(ch)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(ch)" 0 1 useRtnVal: false 
-- doInvoke:X: "put(ch)" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "ch"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
19:	 pushThis 
-- loadOrigin: "ch" on: 1 
20:	 rpushg Super$341 1
-- beforedoinvoke true 
-- doInvoke: "ch" 0 1 useRtnVal: true 
-- doInvoke:X: "ch" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "ch" rec: none 
22:	 pushg 5 ch
-- OI:newInvoke: "put(ch)" rec: none 
24:	 %put 2
L2:
26:	 setThisStack 
27:	 pushThis 
28:	 rtn D
30:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:341 V 2:0 I 3:0 V 4:0 

CLASS Main$342 dNo:342 topDno:341 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  put('T')
 --  ch := 'U'
 --  inner(Main)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  put('T')
 --  ch := 'U'
 --  inner(Main)
 --  
-- push:super.origin: 
-- handleInv: "Super"  staticOff: 0 doLoad: false useRtnVal: 
 --  false 
-- handleInv:elm: "Super" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Super" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "Super" 0 0 
-- loadOriginII: "Super" 
4:	 pushThis 
-- loadOrigin: "Super" on: 0 
5:	 rpushg hello$320%$320 1
-- beforedoinvoke false 
-- handleArgOrg:super: Super$341 
-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  put('T')
 --  ch := 'U'
 --  inner(Main)
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
7:	 tstOriginIsNone 
8:	 rstore  1 origin
-- AllocateSuper: 
 --  put('S')
 --  inner(Super)
 --  put(ch)
 --  
10:	 allocEventQ 
12:	 rtnAlloc 1
14:	 toSuper  341
DO:
17:	 mvStack 
L1:
-- handleInv: "put('T')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('T')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('T')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('T')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('T')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'T'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'T'" 
18:	 pushc 84
-- OI:newInvoke: "put('T')" rec: none 
20:	 %put 2
-- handleInv: "'U'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'U'" 
22:	 pushc 85
-- handleInv: "ch"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "ch" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "ch" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "ch" 0 0 
-- loadOriginII: "ch" 
24:	 pushThis 
-- loadOrigin: "ch" on: 1 
25:	 rpushg Main$342 1
-- beforedoinvoke false 
27:	 storeg ch%$14 5
-- handleInv: "inner(Main)"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "inner(Main)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "inner(Main)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "inner(Main)" 0 0 
-- loadOriginII: "inner(Main)" 
-- beforedoinvoke true 
-- doInvoke: "inner(Main)" 0 1 useRtnVal: false 
-- doInvoke:X: "inner(Main)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "inner(Main)" rec: none 
29:	 pushThis 
30:	 innerP  4
32:	 rpopThisObj 
L2:
33:	 rtnInner  M
34:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:341 V 2:0 I 3:342 I 4:0 

CLASS putint$191 dNo:191 topDno:191 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %globals
 --  in V:var integer
 --  D: obj Indexed(20,#integer)
 --  L:var integer
-- arg: in V:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  %globals
 --  in V:var integer
 --  D: obj Indexed(20,#integer)
 --  L:var integer
1:	 pushThis 
2:	 storeg V%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %globals
 --  in V:var integer
 --  D: obj Indexed(20,#integer)
 --  L:var integer
4:	 allocEventQ 
6:	 mvStack 
-- handleInv: "Indexed(20,#integer)"  staticOff: 2 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "Indexed(20,#integer)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Indexed(20,#integer)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "Indexed(20,#integer)" 0 1 useRtnVal: false 
-- doInvoke:X: "Indexed(20,#integer)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "20"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "20" 
7:	 pushc 20
-- OI:newInvoke: "Indexed(20,#integer)" rec: none 
9:	 pushThis 
10:	 pushc 1
12:	 allocIndexed putint$191%$191 137 1 0
17:	 pushThis 
18:	 rstoreg putint$191%$191 2
20:	 rtnAlloc 1
DO:
22:	 doEventQ 
23:	 mvStack 
L1:
-- handleInv: "V < 0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "< 0" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "< 0" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V < 0" 0 1 
-- loadOriginII: "V" 
24:	 pushThis 
-- loadOrigin: "V" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "V" 
-- DI:loadAccessor: "V" 
25:	 pushg 1 V
-- beforedoinvoke true 
-- doInvoke: "V < 0" 1 2 useRtnVal: true 
-- doInvoke:X: "< 0" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "V" ix->next none 
-- handleInv: "0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
27:	 pushc 0
-- OI:newInvoke: "< 0" rec: V 
29:	 lt 

-- handleInv: "isNeg"  staticOff: 0 doLoad: false useRtnVal: 
 --  false 
-- handleInv:elm: "isNeg" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "isNeg" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "isNeg" 0 0 
-- loadOriginII: "isNeg" 
30:	 pushThis 
-- loadOrigin: "isNeg" on: 0 
-- beforedoinvoke false 
31:	 storeg isNeg%$59 4
-- handleInv: 
 --  if (isNeg) :then 
 --     V := 0 - V
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (isNeg) :then 
 --     V := 0 - V
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (isNeg) :then 
 --     V := 0 - V
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (isNeg) :then 
 --     V := 0 - V
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (isNeg) :then 
 --     V := 0 - V
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "isNeg"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "isNeg" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "isNeg" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "isNeg" 0 0 
-- loadOriginII: "isNeg" 
33:	 pushThis 
-- loadOrigin: "isNeg" on: 0 
-- beforedoinvoke true 
-- doInvoke: "isNeg" 0 1 useRtnVal: true 
-- doInvoke:X: "isNeg" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "isNeg" rec: none 
34:	 pushg 4 isNeg
36:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: true 
-- handleInv: "0 - V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
39:	 pushc 0
-- handleInv:elm: "- V" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "- V" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "0 - V" 1 1 
-- beforedoinvoke true 
-- doInvoke: "0 - V" 1 2 useRtnVal: true 
-- doInvoke:X: "- V" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "0" ix->next none 
-- handleInv: "V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
41:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke true 
-- doInvoke: "V" 0 1 useRtnVal: true 
-- doInvoke:X: "V" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "V" rec: none 
42:	 pushg 1 V
-- OI:newInvoke: "- V" rec: 0 
44:	 minus 

-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
45:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke false 
46:	 storeg V%$30 1
L4:
48:	 pushThis 
49:	 invoke loop$193 193 0 0
55:	 rpop 
-- handleInv: 
 --  if (isNeg) :then 
 --     put('-')
 --        --for(ix)
 --        --   from:: 1 staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (isNeg) :then 
 --     put('-')
 --        --for(ix)
 --        --   from:: 1
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (isNeg) :then 
 --     put('-')
 --        --for(ix)
 --        --   from:: 1false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (isNeg) :then 
 --     put('-')
 --        --for(ix)
 --        --   from:: 10 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (isNeg) :then 
 --     put('-')
 --        --for(ix)
 --        --   from:: 10 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "isNeg"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "isNeg" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "isNeg" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "isNeg" 0 0 
-- loadOriginII: "isNeg" 
56:	 pushThis 
-- loadOrigin: "isNeg" on: 0 
-- beforedoinvoke true 
-- doInvoke: "isNeg" 0 1 useRtnVal: true 
-- doInvoke:X: "isNeg" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "isNeg" rec: none 
57:	 pushg 4 isNeg
59:	 jmpFalse  L7
L6:
-- IfThen:inLineThen: true 
-- handleInv: 
 --  put('-')
 --        --for(ix)
 --        --   from:: 1
 --        --   to:: L staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "put('-')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('-')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  put('-')
 --        --for(ix)
 --        --   from:: 1
 --        --   to:: L0 1 useRtnVal: false 
-- doInvoke:X: "put('-')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'-'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'-'" 
62:	 pushc 45
-- OI:newInvoke: "put('-')" rec: none 
64:	 %put 2
L7:
66:	 pushThis 
67:	 invoke for:to:repeat$S$197 197 0 0
73:	 rpop 
L2:
74:	 setThisStack 
75:	 pushThis 
76:	 rtn D
78:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:191 V 2:0 V 3:0 V 4:0 

CLASS Indexed$137 dNo:137 topDno:137 orgOff:0 orgId:BETA$3 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %globals
 --  %basic 114
 --  %public
 --  in range:var Integer
-- arg: in range:var Integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  %globals
 --  %basic 114
 --  %public
 --  in range:var Integer
1:	 pushThis 
2:	 storeg range%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %globals
 --  %basic 114
 --  %public
 --  in range:var Integer
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
L2:
11:	 setThisStack 
12:	 pushThis 
13:	 rtn D
15:	 END OSDV:0 objSize:1 isIndexed:1
-- endNewVirtDefs: 
-- vdtTable:final: I 1:137 V 2:0 V 3:0 V 4:0 

CLASS Object$S$192 dNo:192 topDno:192 orgOff:1 orgId:putint$191 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "V := 0 - V" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "V := 0 - V" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "0 - V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
11:	 pushc 0
-- handleInv:elm: "- V" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "- V" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "0 - V" 1 1 
-- beforedoinvoke true 
-- doInvoke: "0 - V" 1 2 useRtnVal: true 
-- doInvoke:X: "- V" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "0" ix->next none 
-- handleInv: "V"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
13:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke true 
-- doInvoke: "V" 0 1 useRtnVal: true 
-- doInvoke:X: "V" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "V" rec: none 
14:	 pushg 1 V
-- OI:newInvoke: "- V" rec: 0 
16:	 minus 

-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
17:	 pushThis 
-- loadOrigin: "V" on: 0 
-- beforedoinvoke false 
18:	 storeg V%$30 1
L2:
20:	 setThisStack 
21:	 pushThis 
22:	 rtn D
24:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:192 V 2:0 V 3:0 V 4:0 

CLASS loop$193 dNo:193 topDno:193 orgOff:1 orgId:putint$191 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  L := L + 1
 --  D.put(V /% 10):at[L]
 --  V := V // 10
 --  if (V > 0) :then 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  L := L + 1
 --  D.put(V /% 10):at[L]
 --  V := V // 10
 --  if (V > 0) :then 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "L + 1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ 1" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ 1" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L + 1" 0 1 
-- loadOriginII: "L" 
11:	 pushThis 
-- loadOrigin: "L" on: 1 
12:	 rpushg loop$193 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L" 
-- DI:loadAccessor: "L" 
14:	 pushg 3 L
-- beforedoinvoke true 
-- doInvoke: "L + 1" 1 2 useRtnVal: true 
-- doInvoke:X: "+ 1" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L" ix->next none 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
16:	 pushc 1
-- OI:newInvoke: "+ 1" rec: L 
18:	 plus 

-- handleInv: "L"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
19:	 pushThis 
-- loadOrigin: "L" on: 1 
20:	 rpushg loop$193 1
-- beforedoinvoke false 
22:	 storeg L%$30 3
-- handleInv: "D.put(V /% 10):at[L]"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "D" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "put(V /% 10):at[L]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(V /% 10):at[L]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "D.put(V /% 10):at[L]" 0 1 
-- loadOriginII: "D" 
24:	 pushThis 
-- loadOrigin: "D" on: 1 
25:	 rpushg loop$193 1
-- isVirtualDI: obj 
-- OI:loadAccessor: "D" 
-- DI:loadAccessor: "D" 
27:	 rpushg D 2
-- beforedoinvoke true 
-- doInvoke: "D.put(V /% 10):at[L]" 1 2 useRtnVal: false 
-- doInvoke:X: "put(V /% 10):at[L]" 1 2 E.label: 
 --  ObjectInvocation_KeyWord 2 pRec: none rec: "D" ix->next none 
-- handleInv: "V /% 10"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "/% 10" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "/% 10" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V /% 10" 0 1 
-- loadOriginII: "V" 
29:	 pushThis 
-- loadOrigin: "V" on: 1 
30:	 rpushg loop$193 1
-- isVirtualDI: var 
-- OI:loadAccessor: "V" 
-- DI:loadAccessor: "V" 
32:	 pushg 1 V
-- beforedoinvoke true 
-- doInvoke: "V /% 10" 1 2 useRtnVal: true 
-- doInvoke:X: "/% 10" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "V" ix->next none 
-- handleInv: "10"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "10" 
34:	 pushc 10
-- OI:newInvoke: "/% 10" rec: V 
36:	 modd 

-- handleInv: "L"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
37:	 pushThis 
-- loadOrigin: "L" on: 1 
38:	 rpushg loop$193 1
-- beforedoinvoke true 
-- doInvoke: "L" 0 1 useRtnVal: true 
-- doInvoke:X: "L" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L" rec: none 
40:	 pushg 3 L
-- OI:newInvoke: "put(V /% 10):at[L]" rec: D 
-- getIndexedArgs:rec.ATd: D: obj Indexed(20,#integer)
42:	 xstoreg inx  size:1 isValueObj:0
-- handleInv: "V // 10"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "// 10" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "// 10" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V // 10" 0 1 
-- loadOriginII: "V" 
45:	 pushThis 
-- loadOrigin: "V" on: 1 
46:	 rpushg loop$193 1
-- isVirtualDI: var 
-- OI:loadAccessor: "V" 
-- DI:loadAccessor: "V" 
48:	 pushg 1 V
-- beforedoinvoke true 
-- doInvoke: "V // 10" 1 2 useRtnVal: true 
-- doInvoke:X: "// 10" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "V" ix->next none 
-- handleInv: "10"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "10" 
50:	 pushc 10
-- OI:newInvoke: "// 10" rec: V 
52:	 idiv 

-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
53:	 pushThis 
-- loadOrigin: "V" on: 1 
54:	 rpushg loop$193 1
-- beforedoinvoke false 
56:	 storeg V%$30 1
-- handleInv: 
 --  if (V > 0) :then 
 --     restart(loop)
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (V > 0) :then 
 --     restart(loop)
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (V > 0) :then 
 --     restart(loop)
 --  false true "IfThen" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (V > 0) :then 
 --     restart(loop)
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (V > 0) :then 
 --     restart(loop)
 --  0 1 E.label: IfThen 1 pRec: none rec: none ix->next none 
-- handleInv: "V > 0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "> 0" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "> 0" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "V > 0" 0 1 
-- loadOriginII: "V" 
58:	 pushThis 
-- loadOrigin: "V" on: 1 
59:	 rpushg loop$193 1
-- isVirtualDI: var 
-- OI:loadAccessor: "V" 
-- DI:loadAccessor: "V" 
61:	 pushg 1 V
-- beforedoinvoke true 
-- doInvoke: "V > 0" 1 2 useRtnVal: true 
-- doInvoke:X: "> 0" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "V" ix->next none 
-- handleInv: "0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
63:	 pushc 0
-- OI:newInvoke: "> 0" rec: V 
65:	 gt 

66:	 jmpFalse  L4
L3:
-- IfThen:inLineThen: true 
-- handleInv: "restart(loop)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "restart(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "restart(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "restart(loop)" 0 0 
-- loadOriginII: "restart(loop)" 
-- beforedoinvoke true 
-- doInvoke: "restart(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "restart(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "restart(loop)" rec: none 
69:	 jmp L1

L4:
L2:
72:	 setThisStack 
73:	 pushThis 
74:	 rtn D
76:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:193 V 2:0 V 3:0 V 4:0 

CLASS Object$S$194 dNo:194 topDno:194 orgOff:1 orgId:loop$193 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "restart(loop)" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "restart(loop)" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "restart(loop)"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "restart(loop)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "restart(loop)" true true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "restart(loop)" 0 0 
-- loadOriginII: "restart(loop)" 
-- beforedoinvoke true 
-- doInvoke: "restart(loop)" 0 1 useRtnVal: false 
-- doInvoke:X: "restart(loop)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- OI:newInvoke: "restart(loop)" rec: none 
11:	 jmp L1

L2:
14:	 setThisStack 
15:	 pushThis 
16:	 rtn D
18:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:194 V 2:0 V 3:0 V 4:0 

CLASS Object$S$195 dNo:195 topDno:195 orgOff:1 orgId:putint$191 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  put('-')
 --        --for(ix)
 --        --   from:: 1
 --        --   to:: L
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  put('-')
 --        --for(ix)
 --        --   from:: 1
 --        --   to:: L
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: 
 --  put('-')
 --        --for(ix)
 --        --   from:: 1
 --        --   to:: L staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "put('-')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('-')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  put('-')
 --        --for(ix)
 --        --   from:: 1
 --        --   to:: L0 1 useRtnVal: false 
-- doInvoke:X: "put('-')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'-'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'-'" 
11:	 pushc 45
-- OI:newInvoke: "put('-')" rec: none 
13:	 %put 2
L2:
15:	 setThisStack 
16:	 pushThis 
17:	 rtn D
19:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:195 V 2:0 V 3:0 V 4:0 

CLASS Object$S$196 dNo:196 topDno:196 orgOff:1 orgId:for:to:repeat$S$197 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  i:var integer
 --  i := L + 1 - inx
 --  put('0' + D.get[i])
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  i:var integer
 --  i := L + 1 - inx
 --  put('0' + D.get[i])
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "L + 1 - inx"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ 1" 
-- doLoadII:i<range: "+ 1" false 
-- loadAccessor: "L + 1 - inx" 0 2 
-- loadOriginII: "L" 
11:	 pushThis 
-- loadOrigin: "L" on: 2 
12:	 rpushg Object$S$196 1
14:	 rpushg for:to:repeat$S$197 4
-- isVirtualDI: var 
-- OI:loadAccessor: "L" 
-- DI:loadAccessor: "L" 
16:	 pushg 3 L
-- isVirtualDI: pattern false 
-- loadAccessor:X: "+ 1" rec: "L" 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
18:	 pushc 1
-- OI:newInvoke: "+ 1" rec: L 
20:	 plus 

-- handleInv:elm: "- inx" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "- inx" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L + 1 - inx" 2 2 
-- beforedoinvoke true 
-- doInvoke: "L + 1 - inx" 2 3 useRtnVal: true 
-- doInvoke:X: "- inx" 2 3 E.label: ObjectInvocation_Binary 3 
 --  pRec: "L" rec: "+ 1" ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
21:	 pushThis 
-- loadOrigin: "inx" on: 1 
22:	 rpushg Object$S$196 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
24:	 pushg 3 inx
-- OI:newInvoke: "- inx" rec: + 1 
26:	 minus 

-- handleInv: "i"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "i" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "i" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "i" 0 0 
-- loadOriginII: "i" 
27:	 pushThis 
-- loadOrigin: "i" on: 0 
-- beforedoinvoke false 
28:	 storeg i%$30 2
-- handleInv: "put('0' + D.get[i])"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "put('0' + D.get[i])" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('0' + D.get[i])" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('0' + D.get[i])" 0 1 useRtnVal: false 
-- doInvoke:X: "put('0' + D.get[i])" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "'0' + D.get[i]"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "'0'" 
30:	 pushc 48
-- handleInv:elm: "+ D.get[i]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ D.get[i]" true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "'0' + D.get[i]" 1 1 
-- beforedoinvoke true 
-- doInvoke: "'0' + D.get[i]" 1 2 useRtnVal: true 
-- doInvoke:X: "+ D.get[i]" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "'0'" ix->next none 
-- handleInv: "D.get[i]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "D" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "get[i]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[i]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "D.get[i]" 0 1 
-- loadOriginII: "D" 
32:	 pushThis 
-- loadOrigin: "D" on: 2 
33:	 rpushg Object$S$196 1
35:	 rpushg for:to:repeat$S$197 4
-- isVirtualDI: obj 
-- OI:loadAccessor: "D" 
-- DI:loadAccessor: "D" 
37:	 rpushg D 2
-- beforedoinvoke true 
-- doInvoke: "D.get[i]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[i]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "D" ix->next none 
-- handleInv: "i"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "i" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "i" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "i" 0 0 
-- loadOriginII: "i" 
39:	 pushThis 
-- loadOrigin: "i" on: 0 
-- beforedoinvoke true 
-- doInvoke: "i" 0 1 useRtnVal: true 
-- doInvoke:X: "i" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "i" rec: none 
40:	 pushg 2 i
-- OI:newInvoke: "get[i]" rec: D 
-- getIndexedArgs:rec.ATd: D: obj Indexed(20,#integer)
42:	 xpushg  inx 1 0
-- OI:newInvoke: "+ D.get[i]" rec: '0' 
45:	 plus 

-- OI:newInvoke: "put('0' + D.get[i])" rec: none 
46:	 %put 2
L2:
48:	 setThisStack 
49:	 pushThis 
50:	 rtn D
52:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:196 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$S$197 dNo:197 topDno:109 orgOff:4 orgId:putint$191 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  4 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
4:	 pushc 1
-- handleInv: "L"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
6:	 pushThis 
-- loadOrigin: "L" on: 0 
7:	 rpushg putint$191%$191 4
-- beforedoinvoke true 
-- doInvoke: "L" 0 1 useRtnVal: true 
-- doInvoke:X: "L" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L" rec: none 
9:	 pushg 3 L
-- handleArgOrg:super: 
 --  for(first:var integer):to(last:var integer):repeat{repeat:< object}$109 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
11:	 pushThis 
12:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
14:	 pushThis 
15:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
17:	 allocEventQ 
19:	 rtnAlloc 1
21:	 toSuper  109
DO:
24:	 mvStack 
L1:
L2:
25:	 rtnInner  M
26:	 END OSDV:1 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:196 V 4:0 

CLASS print$103 dNo:103 topDno:103 orgOff:1 orgId:String$285 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  gogo: 
 --     "gogo\n".print
 --  for(1):to(length):repeat
 --     put(get[inx])
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 5 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  gogo: 
 --     "gogo\n".print
 --  for(1):to(length):repeat
 --     put(get[inx])
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
11:	 pushThis 
12:	 invoke for:to:repeat$S$115 115 0 0
18:	 rpop 
L2:
19:	 setThisStack 
20:	 pushThis 
21:	 rtn D
23:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:103 V 2:0 V 3:0 V 4:0 

CLASS Object$S$107 dNo:107 topDno:107 orgOff:1 orgId:for:to:repeat$S$115 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "put(get[inx])" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "put(get[inx])" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "put(get[inx])"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "put(get[inx])" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(get[inx])" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put(get[inx])" 0 1 useRtnVal: false 
-- doInvoke:X: "put(get[inx])" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "get[inx]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "get[inx]" 0 0 
-- loadOriginII: "get[inx]" 
11:	 pushThis 
-- loadOrigin: "get[inx]" on: 3 
12:	 rpushg Object$S$107 1
14:	 rpushg for:to:repeat$S$115 4
16:	 rpushg print$103 1
-- beforedoinvoke true 
-- doInvoke: "get[inx]" 0 1 useRtnVal: true 
-- doInvoke:X: "get[inx]" 0 1 E.label: ObjectInvocation_KeyWord 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
18:	 pushThis 
-- loadOrigin: "inx" on: 1 
19:	 rpushg Object$S$107 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
21:	 pushg 3 inx
-- OI:newInvoke: "get[inx]" rec: none 
23:	 xpushg  inx 1 0
-- OI:newInvoke: "put(get[inx])" rec: none 
26:	 %put 2
L2:
28:	 setThisStack 
29:	 pushThis 
30:	 rtn D
32:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:107 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$S$115 dNo:115 topDno:109 orgOff:4 orgId:print$103 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  4 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
4:	 pushc 1
-- handleInv: "length"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "length" 0 0 
-- loadOriginII: "length" 
6:	 pushThis 
-- loadOrigin: "length" on: 1 
7:	 rpushg print$103%$103 4
9:	 rpushg print$103 1
-- beforedoinvoke true 
-- doInvoke: "length" 0 1 useRtnVal: true 
-- doInvoke:X: "length" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "length" rec: none 
11:	 invoke length$105 105 0 0
17:	 pushg 2 
-- handleArgOrg:super: 
 --  for(first:var integer):to(last:var integer):repeat{repeat:< object}$109 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
19:	 pushThis 
20:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
22:	 pushThis 
23:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
25:	 allocEventQ 
27:	 rtnAlloc 1
29:	 toSuper  109
DO:
32:	 mvStack 
L1:
L2:
33:	 rtnInner  M
34:	 END OSDV:1 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:107 V 4:0 

CLASS fooBar$324 dNo:324 topDno:324 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  in foox:var integer
 --  in fooy:var integer
 --  in fooR: ref Record
 --  out foov:var integer
-- arg: in fooR: ref Record isVirtualDataItem: false primNo: 0 
-- before:currentArg.store: mainIS: 
 --  in foox:var integer
 --  in fooy:var integer
 --  in fooR: ref Record
 --  out foov:var integer
1:	 pushThis 
2:	 rstoreg fooR 4
-- arg: in fooy:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  in foox:var integer
 --  in fooy:var integer
 --  in fooR: ref Record
 --  out foov:var integer
4:	 pushThis 
5:	 storeg fooy%$30 3
-- arg: in foox:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: 
 --  in foox:var integer
 --  in fooy:var integer
 --  in fooR: ref Record
 --  out foov:var integer
7:	 pushThis 
8:	 storeg foox%$30 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
10:	 tstOriginIsNone 
11:	 rstore  1 origin
-- AllocateSuper: 
 --  in foox:var integer
 --  in fooy:var integer
 --  in fooR: ref Record
 --  out foov:var integer
13:	 allocEventQ 
15:	 mvStack 
16:	 rtnAlloc 1
DO:
18:	 doEventQ 
19:	 mvStack 
L1:
-- handleInv: "put('+')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('+')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('+')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('+')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('+')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'+'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'+'" 
20:	 pushc 43
-- OI:newInvoke: "put('+')" rec: none 
22:	 %put 2
-- handleInv: "fooR.get"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "fooR" 
-- handleInv:isVirtualDI: false ref false false 
-- handleInv:elm: "get" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "fooR.get" 0 1 
-- loadOriginII: "fooR" 
24:	 pushThis 
-- loadOrigin: "fooR" on: 0 
-- isVirtualDI: ref 
-- OI:loadAccessor: "fooR" 
-- DI:loadAccessor: "fooR" 
25:	 rpushg fooR 4
-- beforedoinvoke true 
-- doInvoke: "fooR.get" 1 2 useRtnVal: true 
-- doInvoke:X: "get" 1 2 E.label: ObjectInvocation_Unary 2 
 --  pRec: none rec: "fooR" ix->next none 
-- OI:newInvoke: "get" rec: fooR 
27:	 invoke get$323 323 0 0
33:	 pushg 2 
-- handleInv: "fooQ"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "fooQ" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "fooQ" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "fooQ" 0 0 
-- loadOriginII: "fooQ" 
35:	 pushThis 
-- loadOrigin: "fooQ" on: 0 
-- beforedoinvoke false 
36:	 storeg fooQ%$30 6
-- handleInv: "y + z"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ z" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ z" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "y + z" 0 1 
-- loadOriginII: "y" 
38:	 pushThis 
-- loadOrigin: "y" on: 1 
39:	 rpushg fooBar$324 1
-- isVirtualDI: var 
-- OI:loadAccessor: "y" 
-- DI:loadAccessor: "y" 
41:	 pushg 3 y
-- beforedoinvoke true 
-- doInvoke: "y + z" 1 2 useRtnVal: true 
-- doInvoke:X: "+ z" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "y" ix->next none 
-- handleInv: "z"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "z" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "z" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "z" 0 0 
-- loadOriginII: "z" 
43:	 pushThis 
-- loadOrigin: "z" on: 1 
44:	 rpushg fooBar$324 1
-- beforedoinvoke true 
-- doInvoke: "z" 0 1 useRtnVal: true 
-- doInvoke:X: "z" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "z" rec: none 
46:	 pushg 4 z
-- OI:newInvoke: "+ z" rec: y 
48:	 plus 

-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
49:	 pushThis 
-- loadOrigin: "x" on: 1 
50:	 rpushg fooBar$324 1
-- beforedoinvoke false 
52:	 storeg x%$30 2
-- handleInv: "foox + fooy + fooQ"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "foox" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ fooy" 
-- doLoadII:i<range: "+ fooy" false 
-- loadAccessor: "foox + fooy + fooQ" 0 2 
-- loadOriginII: "foox" 
54:	 pushThis 
-- loadOrigin: "foox" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "foox" 
-- DI:loadAccessor: "foox" 
55:	 pushg 2 foox
-- isVirtualDI: pattern false 
-- loadAccessor:X: "+ fooy" rec: "foox" 
-- handleInv: "fooy"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "fooy" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "fooy" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "fooy" 0 0 
-- loadOriginII: "fooy" 
57:	 pushThis 
-- loadOrigin: "fooy" on: 0 
-- beforedoinvoke true 
-- doInvoke: "fooy" 0 1 useRtnVal: true 
-- doInvoke:X: "fooy" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "fooy" rec: none 
58:	 pushg 3 fooy
-- OI:newInvoke: "+ fooy" rec: foox 
60:	 plus 

-- handleInv:elm: "+ fooQ" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ fooQ" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "foox + fooy + fooQ" 2 2 
-- beforedoinvoke true 
-- doInvoke: "foox + fooy + fooQ" 2 3 useRtnVal: true 
-- doInvoke:X: "+ fooQ" 2 3 E.label: ObjectInvocation_Binary 3 
 --  pRec: "foox" rec: "+ fooy" ix->next none 
-- handleInv: "fooQ"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "fooQ" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "fooQ" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "fooQ" 0 0 
-- loadOriginII: "fooQ" 
61:	 pushThis 
-- loadOrigin: "fooQ" on: 0 
-- beforedoinvoke true 
-- doInvoke: "fooQ" 0 1 useRtnVal: true 
-- doInvoke:X: "fooQ" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "fooQ" rec: none 
62:	 pushg 6 fooQ
-- OI:newInvoke: "+ fooQ" rec: + fooy 
64:	 plus 

-- handleInv: "foov"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "foov" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "foov" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "foov" 0 0 
-- loadOriginII: "foov" 
65:	 pushThis 
-- loadOrigin: "foov" on: 0 
-- beforedoinvoke false 
66:	 storeg foov%$30 5
L2:
68:	 setThisStack 
69:	 pushThis 
70:	 rtn D
72:	 END OSDV:0 objSize:6 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:324 V 2:0 V 3:0 V 4:0 

CLASS fisk$325 dNo:325 topDno:325 orgOff:1 orgId:hello$320 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  a:var integer
 --  snaps: 
 --     x := y + z
 --  a := 119 + x
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  a:var integer
 --  snaps: 
 --     x := y + z
 --  a := 119 + x
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "119 + x"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "119" 
11:	 pushc 119
-- handleInv:elm: "+ x" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ x" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "119 + x" 1 1 
-- beforedoinvoke true 
-- doInvoke: "119 + x" 1 2 useRtnVal: true 
-- doInvoke:X: "+ x" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "119" ix->next none 
-- handleInv: "x"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
13:	 pushThis 
-- loadOrigin: "x" on: 1 
14:	 rpushg fisk$325 1
-- beforedoinvoke true 
-- doInvoke: "x" 0 1 useRtnVal: true 
-- doInvoke:X: "x" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "x" rec: none 
16:	 pushg 2 x
-- OI:newInvoke: "+ x" rec: 119 
18:	 plus 

-- handleInv: "a"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "a" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "a" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "a" 0 0 
-- loadOriginII: "a" 
19:	 pushThis 
-- loadOrigin: "a" on: 0 
-- beforedoinvoke false 
20:	 storeg a%$30 2
-- handleInv: 
 --  if (a > 0) :then 
 --     a := 121
 --  :else 
 --     a := 123
 --   staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: 
 --  if (a > 0) :then 
 --     a := 121
 --  :else 
 --     a := 123
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  if (a > 0) :then 
 --     a := 121
 --  :else 
 --     a := 123
 --  false true "IfThenElse" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: 
 --  if (a > 0) :then 
 --     a := 121
 --  :else 
 --     a := 123
 --  0 1 useRtnVal: false 
-- doInvoke:X: 
 --  if (a > 0) :then 
 --     a := 121
 --  :else 
 --     a := 123
 --  0 1 E.label: IfThenElse 1 pRec: none rec: none ix->next none 
-- handleInv: "a > 0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "a" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "> 0" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "> 0" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "a > 0" 0 1 
-- loadOriginII: "a" 
22:	 pushThis 
-- loadOrigin: "a" on: 0 
-- isVirtualDI: var 
-- OI:loadAccessor: "a" 
-- DI:loadAccessor: "a" 
23:	 pushg 2 a
-- beforedoinvoke true 
-- doInvoke: "a > 0" 1 2 useRtnVal: true 
-- doInvoke:X: "> 0" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "a" ix->next none 
-- handleInv: "0"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "0" 
25:	 pushc 0
-- OI:newInvoke: "> 0" rec: a 
27:	 gt 

28:	 jmpFalse  L4
L3:
31:	 pushThis 
32:	 invoke Object$S$327 327 0 0
38:	 rpop 
39:	 jmp L5

L4:
42:	 pushThis 
43:	 invoke Object$S$328 328 0 0
49:	 rpop 
L5:
-- handleInv: "put('Q')"  staticOff: 0 doLoad: true useRtnVal: 
 --  false 
-- handleInv:elm: "put('Q')" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put('Q')" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "put('Q')" 0 1 useRtnVal: false 
-- doInvoke:X: "put('Q')" 0 1 E.label: ObjectInvocation_Function 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "'Q'"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "'Q'" 
50:	 pushc 81
-- OI:newInvoke: "put('Q')" rec: none 
52:	 %put 2
-- handleInv: "snaps"  staticOff: 0 doLoad: true useRtnVal: false 
-- handleInv:elm: "snaps" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "snaps" true true "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "snaps" 0 0 
-- loadOriginII: "snaps" 
54:	 pushThis 
-- loadOrigin: "snaps" on: 0 
-- beforedoinvoke true 
-- doInvoke: "snaps" 0 1 useRtnVal: false 
-- doInvoke:X: "snaps" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "snaps" rec: none 
55:	 invoke snaps$326 326 0 0
61:	 rpop 
L2:
62:	 setThisStack 
63:	 pushThis 
64:	 rtn D
66:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:325 V 2:0 V 3:0 V 4:0 

CLASS Object$S$327 dNo:327 topDno:327 orgOff:1 orgId:fisk$325 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "a := 121" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "a := 121" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "121"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "121" 
11:	 pushc 121
-- handleInv: "a"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "a" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "a" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "a" 0 0 
-- loadOriginII: "a" 
13:	 pushThis 
-- loadOrigin: "a" on: 1 
14:	 rpushg Object$S$327 1
-- beforedoinvoke false 
16:	 storeg a%$30 2
L2:
18:	 setThisStack 
19:	 pushThis 
20:	 rtn D
22:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:327 V 2:0 V 3:0 V 4:0 

CLASS Object$S$328 dNo:328 topDno:328 orgOff:1 orgId:fisk$325 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "a := 123" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "a := 123" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "123"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "123" 
11:	 pushc 123
-- handleInv: "a"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "a" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "a" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "a" 0 0 
-- loadOriginII: "a" 
13:	 pushThis 
-- loadOrigin: "a" on: 1 
14:	 rpushg Object$S$328 1
-- beforedoinvoke false 
16:	 storeg a%$30 2
L2:
18:	 setThisStack 
19:	 pushThis 
20:	 rtn D
22:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:328 V 2:0 V 3:0 V 4:0 

CLASS snaps$326 dNo:326 topDno:326 orgOff:1 orgId:fisk$325 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "x := y + z" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: "x := y + z" 
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "y + z"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "y" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ z" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ z" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "y + z" 0 1 
-- loadOriginII: "y" 
11:	 pushThis 
-- loadOrigin: "y" on: 2 
12:	 rpushg snaps$326 1
14:	 rpushg fisk$325 1
-- isVirtualDI: var 
-- OI:loadAccessor: "y" 
-- DI:loadAccessor: "y" 
16:	 pushg 3 y
-- beforedoinvoke true 
-- doInvoke: "y + z" 1 2 useRtnVal: true 
-- doInvoke:X: "+ z" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "y" ix->next none 
-- handleInv: "z"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "z" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "z" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "z" 0 0 
-- loadOriginII: "z" 
18:	 pushThis 
-- loadOrigin: "z" on: 2 
19:	 rpushg snaps$326 1
21:	 rpushg fisk$325 1
-- beforedoinvoke true 
-- doInvoke: "z" 0 1 useRtnVal: true 
-- doInvoke:X: "z" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "z" rec: none 
23:	 pushg 4 z
-- OI:newInvoke: "+ z" rec: y 
25:	 plus 

-- handleInv: "x"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "x" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "x" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "x" 0 0 
-- loadOriginII: "x" 
26:	 pushThis 
-- loadOrigin: "x" on: 2 
27:	 rpushg snaps$326 1
29:	 rpushg fisk$325 1
-- beforedoinvoke false 
31:	 storeg x%$30 2
L2:
33:	 setThisStack 
34:	 pushThis 
35:	 rtn D
37:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:326 V 2:0 V 3:0 V 4:0 

CLASS +$286 dNo:286 topDno:286 orgOff:1 orgId:String$285 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  in S: var String
 --  out V: var String
 --  L:var integer
 --  L := Length
-- arg: in S: var String isVirtualDataItem: false primNo: 5 
1:	 pushThis 
2:	 rstoreg S 2
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 5 
4:	 tstOriginIsNone 
5:	 rstore  1 origin
-- AllocateSuper: 
 --  in S: var String
 --  out V: var String
 --  L:var integer
 --  L := Length
7:	 allocEventQ 
9:	 mvStack 
10:	 pushText ""
12:	 pushThis 
13:	 rstoreg V 3
15:	 rtnAlloc 1
DO:
17:	 doEventQ 
18:	 mvStack 
L1:
-- handleInv: "Length"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "Length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "Length" 0 0 
-- loadOriginII: "Length" 
19:	 pushThis 
-- loadOrigin: "Length" on: 1 
20:	 rpushg +$286 1
-- beforedoinvoke true 
-- doInvoke: "Length" 0 1 useRtnVal: true 
-- doInvoke:X: "Length" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "Length" rec: none 
22:	 invoke length$105 105 0 0
28:	 pushg 2 
-- handleInv: "L"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
30:	 pushThis 
-- loadOrigin: "L" on: 0 
-- beforedoinvoke false 
31:	 storeg L%$30 4
33:	 pushThis 
34:	 invoke doplus$287 287 0 0
40:	 rpop 
L2:
41:	 setThisStack 
42:	 pushThis 
43:	 rtn D
45:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:286 V 2:0 V 3:0 V 4:0 

CLASS doplus$287 dNo:287 topDno:287 orgOff:1 orgId:+$286 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  e:var integer
 --  i:var integer
 --  T: obj Indexed(L + S.length,Integer)
 --  for(1):to(L):repeat
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  e:var integer
 --  i:var integer
 --  T: obj Indexed(L + S.length,Integer)
 --  for(1):to(L):repeat
4:	 allocEventQ 
6:	 mvStack 
-- handleInv: "Indexed(L + S.length,Integer)"  staticOff: 4 
 --  doLoad: true useRtnVal: false 
-- handleInv:elm: "Indexed(L + S.length,Integer)" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "Indexed(L + S.length,Integer)" false true "
 --  ObjectInvocation_Function" useRtnVal: false 
-- beforedoinvoke true 
-- doInvoke: "Indexed(L + S.length,Integer)" 0 1 useRtnVal: 
 --  false 
-- doInvoke:X: "Indexed(L + S.length,Integer)" 0 1 E.label: 
 --  ObjectInvocation_Function 1 pRec: none rec: none ix->next none 
-- handleInv: "L + S.length"  staticOff: 0 doLoad: true 
 --  useRtnVal: true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ S.length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ S.length" true true "
 --  ObjectInvocation_Binary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L + S.length" 0 1 
-- loadOriginII: "L" 
7:	 pushThis 
-- loadOrigin: "L" on: 1 
8:	 rpushg doplus$287 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L" 
-- DI:loadAccessor: "L" 
10:	 pushg 4 L
-- beforedoinvoke true 
-- doInvoke: "L + S.length" 1 2 useRtnVal: true 
-- doInvoke:X: "+ S.length" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L" ix->next none 
-- handleInv: "S.length"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "S" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "S.length" 0 1 
-- loadOriginII: "S" 
12:	 pushThis 
-- loadOrigin: "S" on: 1 
13:	 rpushg doplus$287 1
-- isVirtualDI: var 
-- OI:loadAccessor: "S" 
-- DI:loadAccessor: "S" 
15:	 rpushg S 2
-- beforedoinvoke true 
-- doInvoke: "S.length" 1 2 useRtnVal: true 
-- doInvoke:X: "length" 1 2 E.label: ObjectInvocation_Unary 2 
 --  pRec: none rec: "S" ix->next none 
-- OI:newInvoke: "length" rec: S 
17:	 invoke length$105 105 0 0
23:	 pushg 2 
-- OI:newInvoke: "+ S.length" rec: L 
25:	 plus 

-- OI:newInvoke: "Indexed(L + S.length,Integer)" rec: none 
26:	 pushThis 
27:	 pushc 1
29:	 allocIndexed doplus$287%$287 137 1 0
34:	 pushThis 
35:	 rstoreg doplus$287%$287 4
37:	 rtnAlloc 1
DO:
39:	 doEventQ 
40:	 mvStack 
L1:
41:	 pushThis 
42:	 invoke for:to:repeat$S$289 289 0 0
48:	 rpop 
49:	 pushThis 
50:	 invoke for:to:repeat$S$291 291 0 0
56:	 rpop 
-- handleInv: 
 --  T.asString
 --           -- V: obj Indexed(Length + S.length)
 --           -- V := T[1:length] + S.T[1:S.length]
 --   staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "T" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: 
 --  asString
 --           -- V: obj Indexed(Length + S.length)
 --           -- V := T[1:length] + S.T[1:S.length]
 --  
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: 
 --  asString
 --           -- V: obj Indexed(Length + S.length)
 --           -- V := T[1:length] + S.T[1:S.length]
 --  true true "ObjectInvocation_Unary" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: 
 --  T.asString
 --           -- V: obj Indexed(Length + S.length)
 --           -- V := T[1:length] + S.T[1:S.length]
 --  0 1 
-- loadOriginII: "T" 
57:	 pushThis 
-- loadOrigin: "T" on: 0 
-- isVirtualDI: obj 
-- OI:loadAccessor: "T" 
-- DI:loadAccessor: "T" 
58:	 rpushg T 4
-- beforedoinvoke true 
-- doInvoke: 
 --  T.asString
 --           -- V: obj Indexed(Length + S.length)
 --           -- V := T[1:length] + S.T[1:S.length]
 --  1 2 useRtnVal: true 
-- doInvoke:X: 
 --  asString
 --           -- V: obj Indexed(Length + S.length)
 --           -- V := T[1:length] + S.T[1:S.length]
 --  1 2 E.label: ObjectInvocation_Unary 2 pRec: none rec: "T" 
 --  ix->next none 
-- OI:newInvoke: 
 --  asString
 --           -- V: obj Indexed(Length + S.length)
 --           -- V := T[1:length] + S.T[1:S.length]
 --  rec: T 
60:	 %asString 118
-- handleInv: "V"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "V" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "V" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "V" 0 0 
-- loadOriginII: "V" 
62:	 pushThis 
-- loadOrigin: "V" on: 1 
63:	 rpushg doplus$287 1
-- beforedoinvoke false 
65:	 rstoreg V%$285 3
L2:
67:	 setThisStack 
68:	 pushThis 
69:	 rtn D
71:	 END OSDV:0 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:287 V 2:0 V 3:0 V 4:0 

CLASS Object$S$288 dNo:288 topDno:288 orgOff:1 orgId:for:to:repeat$S$289 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  e := get[inx]
 --  T.put(e):at[inx]
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  e := get[inx]
 --  T.put(e):at[inx]
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "get[inx]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "get[inx]" 0 0 
-- loadOriginII: "get[inx]" 
11:	 pushThis 
-- loadOrigin: "get[inx]" on: 4 
12:	 rpushg Object$S$288 1
14:	 rpushg for:to:repeat$S$289 4
16:	 rpushg doplus$287 1
18:	 rpushg +$286 1
-- beforedoinvoke true 
-- doInvoke: "get[inx]" 0 1 useRtnVal: true 
-- doInvoke:X: "get[inx]" 0 1 E.label: ObjectInvocation_KeyWord 1 
 --  pRec: none rec: none ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
20:	 pushThis 
-- loadOrigin: "inx" on: 1 
21:	 rpushg Object$S$288 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
23:	 pushg 3 inx
-- OI:newInvoke: "get[inx]" rec: none 
25:	 xpushg  inx 1 0
-- handleInv: "e"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "e" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "e" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "e" 0 0 
-- loadOriginII: "e" 
28:	 pushThis 
-- loadOrigin: "e" on: 2 
29:	 rpushg Object$S$288 1
31:	 rpushg for:to:repeat$S$289 4
-- beforedoinvoke false 
33:	 storeg e%$30 2
-- handleInv: "T.put(e):at[inx]"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "T" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "put(e):at[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(e):at[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "T.put(e):at[inx]" 0 1 
-- loadOriginII: "T" 
35:	 pushThis 
-- loadOrigin: "T" on: 2 
36:	 rpushg Object$S$288 1
38:	 rpushg for:to:repeat$S$289 4
-- isVirtualDI: obj 
-- OI:loadAccessor: "T" 
-- DI:loadAccessor: "T" 
40:	 rpushg T 4
-- beforedoinvoke true 
-- doInvoke: "T.put(e):at[inx]" 1 2 useRtnVal: false 
-- doInvoke:X: "put(e):at[inx]" 1 2 E.label: 
 --  ObjectInvocation_KeyWord 2 pRec: none rec: "T" ix->next none 
-- handleInv: "e"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "e" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "e" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "e" 0 0 
-- loadOriginII: "e" 
42:	 pushThis 
-- loadOrigin: "e" on: 2 
43:	 rpushg Object$S$288 1
45:	 rpushg for:to:repeat$S$289 4
-- beforedoinvoke true 
-- doInvoke: "e" 0 1 useRtnVal: true 
-- doInvoke:X: "e" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "e" rec: none 
47:	 pushg 2 e
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
49:	 pushThis 
-- loadOrigin: "inx" on: 1 
50:	 rpushg Object$S$288 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
52:	 pushg 3 inx
-- OI:newInvoke: "put(e):at[inx]" rec: T 
-- getIndexedArgs:rec.ATd: T: obj Indexed(L + S.length,Integer)
54:	 xstoreg inx  size:1 isValueObj:0
L2:
57:	 setThisStack 
58:	 pushThis 
59:	 rtn D
61:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:288 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$S$289 dNo:289 topDno:109 orgOff:4 orgId:doplus$287 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  4 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
4:	 pushc 1
-- handleInv: "L"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "L" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L" 0 0 
-- loadOriginII: "L" 
6:	 pushThis 
-- loadOrigin: "L" on: 1 
7:	 rpushg doplus$287%$287 4
9:	 rpushg doplus$287 1
-- beforedoinvoke true 
-- doInvoke: "L" 0 1 useRtnVal: true 
-- doInvoke:X: "L" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "L" rec: none 
11:	 pushg 4 L
-- handleArgOrg:super: 
 --  for(first:var integer):to(last:var integer):repeat{repeat:< object}$109 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
13:	 pushThis 
14:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
16:	 pushThis 
17:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
19:	 allocEventQ 
21:	 rtnAlloc 1
23:	 toSuper  109
DO:
26:	 mvStack 
L1:
L2:
27:	 rtnInner  M
28:	 END OSDV:1 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:288 V 4:0 

CLASS Object$S$290 dNo:290 topDno:290 orgOff:1 orgId:for:to:repeat$S$291 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  e := S.get[inx]
 --  i := L + inx
 --  T.put(e):at[i]
 --  
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  e := S.get[inx]
 --  i := L + inx
 --  T.put(e):at[i]
 --  
4:	 allocEventQ 
6:	 mvStack 
7:	 rtnAlloc 1
DO:
9:	 doEventQ 
10:	 mvStack 
L1:
-- handleInv: "S.get[inx]"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "S" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "get[inx]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "get[inx]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "S.get[inx]" 0 1 
-- loadOriginII: "S" 
11:	 pushThis 
-- loadOrigin: "S" on: 3 
12:	 rpushg Object$S$290 1
14:	 rpushg for:to:repeat$S$291 4
16:	 rpushg doplus$287 1
-- isVirtualDI: var 
-- OI:loadAccessor: "S" 
-- DI:loadAccessor: "S" 
18:	 rpushg S 2
-- beforedoinvoke true 
-- doInvoke: "S.get[inx]" 1 2 useRtnVal: true 
-- doInvoke:X: "get[inx]" 1 2 E.label: ObjectInvocation_KeyWord 2 
 --  pRec: none rec: "S" ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
20:	 pushThis 
-- loadOrigin: "inx" on: 1 
21:	 rpushg Object$S$290 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
23:	 pushg 3 inx
-- OI:newInvoke: "get[inx]" rec: S 
25:	 xpushg  inx 1 0
-- handleInv: "e"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "e" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "e" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "e" 0 0 
-- loadOriginII: "e" 
28:	 pushThis 
-- loadOrigin: "e" on: 2 
29:	 rpushg Object$S$290 1
31:	 rpushg for:to:repeat$S$291 4
-- beforedoinvoke false 
33:	 storeg e%$30 2
-- handleInv: "L + inx"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "L" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "+ inx" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "+ inx" true true "ObjectInvocation_Binary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "L + inx" 0 1 
-- loadOriginII: "L" 
35:	 pushThis 
-- loadOrigin: "L" on: 3 
36:	 rpushg Object$S$290 1
38:	 rpushg for:to:repeat$S$291 4
40:	 rpushg doplus$287 1
-- isVirtualDI: var 
-- OI:loadAccessor: "L" 
-- DI:loadAccessor: "L" 
42:	 pushg 4 L
-- beforedoinvoke true 
-- doInvoke: "L + inx" 1 2 useRtnVal: true 
-- doInvoke:X: "+ inx" 1 2 E.label: ObjectInvocation_Binary 2 
 --  pRec: none rec: "L" ix->next none 
-- handleInv: "inx"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "inx" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "inx" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "inx" 0 0 
-- loadOriginII: "inx" 
44:	 pushThis 
-- loadOrigin: "inx" on: 1 
45:	 rpushg Object$S$290 1
-- beforedoinvoke true 
-- doInvoke: "inx" 0 1 useRtnVal: true 
-- doInvoke:X: "inx" 0 1 E.label: ObjectInvocation_Unary 1 
 --  pRec: none rec: none ix->next none 
-- OI:newInvoke: "inx" rec: none 
47:	 pushg 3 inx
-- OI:newInvoke: "+ inx" rec: L 
49:	 plus 

-- handleInv: "i"  staticOff: 0 doLoad: false useRtnVal: false 
-- handleInv:elm: "i" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "i" false false "ObjectInvocation_Unary" 
 --  useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "i" 0 0 
-- loadOriginII: "i" 
50:	 pushThis 
-- loadOrigin: "i" on: 2 
51:	 rpushg Object$S$290 1
53:	 rpushg for:to:repeat$S$291 4
-- beforedoinvoke false 
55:	 storeg i%$30 3
-- handleInv: "T.put(e):at[i]"  staticOff: 0 doLoad: true 
 --  useRtnVal: false 
-- handleInv:elm: "T" 
-- handleInv:isVirtualDI: false obj false false 
-- handleInv:elm: "put(e):at[i]" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "put(e):at[i]" true true "
 --  ObjectInvocation_KeyWord" useRtnVal: false 
-- before:loadAccessorA 
-- loadAccessor: "T.put(e):at[i]" 0 1 
-- loadOriginII: "T" 
57:	 pushThis 
-- loadOrigin: "T" on: 2 
58:	 rpushg Object$S$290 1
60:	 rpushg for:to:repeat$S$291 4
-- isVirtualDI: obj 
-- OI:loadAccessor: "T" 
-- DI:loadAccessor: "T" 
62:	 rpushg T 4
-- beforedoinvoke true 
-- doInvoke: "T.put(e):at[i]" 1 2 useRtnVal: false 
-- doInvoke:X: "put(e):at[i]" 1 2 E.label: 
 --  ObjectInvocation_KeyWord 2 pRec: none rec: "T" ix->next none 
-- handleInv: "e"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "e" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "e" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "e" 0 0 
-- loadOriginII: "e" 
64:	 pushThis 
-- loadOrigin: "e" on: 2 
65:	 rpushg Object$S$290 1
67:	 rpushg for:to:repeat$S$291 4
-- beforedoinvoke true 
-- doInvoke: "e" 0 1 useRtnVal: true 
-- doInvoke:X: "e" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "e" rec: none 
69:	 pushg 2 e
-- handleInv: "i"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "i" 
-- handleInv:isVirtualDI: false var false false 
-- doLoadII:i=range: "i" false false "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "i" 0 0 
-- loadOriginII: "i" 
71:	 pushThis 
-- loadOrigin: "i" on: 2 
72:	 rpushg Object$S$290 1
74:	 rpushg for:to:repeat$S$291 4
-- beforedoinvoke true 
-- doInvoke: "i" 0 1 useRtnVal: true 
-- doInvoke:X: "i" 0 1 E.label: ObjectInvocation_Unary 1 pRec: 
 --  none rec: none ix->next none 
-- OI:newInvoke: "i" rec: none 
76:	 pushg 3 i
-- OI:newInvoke: "put(e):at[i]" rec: T 
-- getIndexedArgs:rec.ATd: T: obj Indexed(L + S.length,Integer)
78:	 xstoreg inx  size:1 isValueObj:0
L2:
81:	 setThisStack 
82:	 pushThis 
83:	 rtn D
85:	 END OSDV:0 objSize:1 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:290 V 2:0 V 3:0 V 4:0 

CLASS for:to:repeat$S$291 dNo:291 topDno:109 orgOff:4 orgId:doplus$287 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 0 
1:	 tstOriginIsNone 
2:	 rstore  4 origin
-- AllocateSuper: "" 
-- push:super.origin: 
-- handleInv: "1"  staticOff: 0 doLoad: true useRtnVal: true 
-- handleInv:elm: "1" 
4:	 pushc 1
-- handleInv: "S.length"  staticOff: 0 doLoad: true useRtnVal: 
 --  true 
-- handleInv:elm: "S" 
-- handleInv:isVirtualDI: false var false false 
-- handleInv:elm: "length" 
-- handleInv:isVirtualDI: false pattern true false 
-- doLoadII:i=range: "length" true true "ObjectInvocation_Unary" 
 --  useRtnVal: true 
-- before:loadAccessorA 
-- loadAccessor: "S.length" 0 1 
-- loadOriginII: "S" 
6:	 pushThis 
-- loadOrigin: "S" on: 1 
7:	 rpushg doplus$287%$287 4
9:	 rpushg doplus$287 1
-- isVirtualDI: var 
-- OI:loadAccessor: "S" 
-- DI:loadAccessor: "S" 
11:	 rpushg S 2
-- beforedoinvoke true 
-- doInvoke: "S.length" 1 2 useRtnVal: true 
-- doInvoke:X: "length" 1 2 E.label: ObjectInvocation_Unary 2 
 --  pRec: none rec: "S" ix->next none 
-- OI:newInvoke: "length" rec: S 
13:	 invoke length$105 105 0 0
19:	 pushg 2 
-- handleArgOrg:super: 
 --  for(first:var integer):to(last:var integer):repeat{repeat:< object}$109 
-- handleArgumentsAndOrigin: 
-- StoreArguments: "" 
-- arg: last:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
21:	 pushThis 
22:	 storeg last%$30 2
-- arg: first:var integer isVirtualDataItem: false primNo: 1 
-- before:currentArg.store: mainIS: "" 
24:	 pushThis 
25:	 storeg first%$30 1
-- StoreOrigin: 
-- AllocateSuper: 
 --  %OSDvisibility skipInternal
 --  %globals inSub
 --  inx:var integer
 --  inx := first
27:	 allocEventQ 
29:	 rtnAlloc 1
31:	 toSuper  109
DO:
34:	 mvStack 
L1:
L2:
35:	 rtnInner  M
36:	 END OSDV:1 objSize:4 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:109 V 2:0 V 3:290 V 4:0 

CLASS asString$149 dNo:149 topDno:149 orgOff:1 orgId:Indexed$137 orgDno:0

-- handleArgumentsAndOrigin: 
-- StoreArguments: 
 --  %basic 118
 --           -- converts this (indexed) to a String
 --           -- we should move String to here and qualify S as String
 --           --%if _cond: var boolean %then% _thenPart:< Object:
-- StoreOrigin: 
-- StoreOrigin:hasOrigin: 114 
1:	 tstOriginIsNone 
2:	 rstore  1 origin
-- AllocateSuper: 
 --  %basic 118
 --           -- converts this (indexed) to a String
 --           -- we should move String to here and qualify S as String
 --           --%if _cond: var boolean %then% _thenPart:< Object:
4:	 allocEventQ 
6:	 mvStack 
7:	 pushText ""
9:	 pushThis 
10:	 rstoreg S 2
12:	 rtnAlloc 1
DO:
14:	 doEventQ 
15:	 mvStack 
L1:
L2:
16:	 setThisStack 
17:	 pushThis 
18:	 rtn D
20:	 END OSDV:0 objSize:2 isIndexed:0
-- endNewVirtDefs: 
-- vdtTable:final: I 1:149 V 2:0 V 3:0 V 4:0 

CLASS valProx dNo:349 topDno:1 orgOff:1 orgId:Object orgDno:0

DO:
1:	 END OSDV:0 objSize:4 isIndexed:0

CLASS VM dNo:350 topDno:1 orgOff:0 orgId:Object orgDno:0

DO:
L1:
1:	 pushThis 
2:	 invoke BETAworld$1 1 0 1
8:	 stop
 
L2:
9:	 rtn D
11:	 END OSDV:0 objSize:2 isIndexed:0

CLASS EventProcessor dNo:351 topDno:1 orgOff:0 orgId:Object orgDno:0

DO:
1:	 stop
 
2:	 END OSDV:0 objSize:1 isIndexed:0

CLASS ThreadStub dNo:352 topDno:352 orgOff:0 orgId:Object orgDno:0

DO:
1:	 call D ThreadStub
3:	 stop
 
4:	 END OSDV:0 objSize:1 isIndexed:0
CLASS BETAworld$1 descInx:1 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	pushthis 
7:	saveBETAworld 0
10:	mvStack
allocE: 
11:	pushthis 
12:	invoke 3 2 1
18:	rpop 
19:	pushthis 
20:	invoke 235 3 1
26:	rpop 
27:	pushthis 
28:	invoke 319 4 1
34:	rpop 
35:	rtnAlloc 1
doE: 
37:	doEventQ 
38:	mvStack
39:	setThisStack
40:	pushthis 
41:	rtn D


CLASS BETA$3 descInx:3 objSize:3 originOff: 1 visibility: 2
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 4 2 1
14:	rpop 
15:	rtnAlloc 1
doE: 
17:	doEventQ 
18:	mvStack
19:	setThisStack
20:	pushthis 
21:	rtn D


CLASS ascii$4 descInx:4 objSize:5 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushc 10
9:	pushthis 
10:	storeg 2
12:	pushc 13
14:	pushthis 
15:	storeg 3
17:	pushc 0
19:	pushthis 
20:	storeg 4
22:	rtnAlloc 1
doE: 
24:	doEventQ 
25:	mvStack
26:	pushc 10
28:	pushthis 
29:	storeg 5
31:	setThisStack
32:	pushthis 
33:	rtn D


CLASS Value$7 descInx:7 objSize:0 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
doE: 
1:	setThisStack
2:	pushthis 
3:	rtn D


CLASS =$8 descInx:8 objSize:5 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	jmpFalse 13
4:	pushthis 
5:	vassign 2 2 0
10:	jmp 20
13:	invokeVal 88 1 0
19:	rpop 
20:	tstOriginNone 
21:	rstore 1
23:	allocEventQ 0
25:	mvStack
allocE: 
26:	rtnAlloc 1
doE: 
28:	doEventQ 
29:	mvStack
30:	pushthis 
31:	innerP 3
33:	rpopThisObj
34:	setThisStack
35:	pushthis 
36:	rtn D


CLASS <=$10 descInx:10 objSize:5 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	jmpFalse 13
4:	pushthis 
5:	vassign 2 2 0
10:	jmp 20
13:	invokeVal 88 1 0
19:	rpop 
20:	tstOriginNone 
21:	rstore 1
23:	allocEventQ 0
25:	mvStack
allocE: 
26:	rtnAlloc 1
doE: 
28:	doEventQ 
29:	mvStack
30:	setThisStack
31:	pushthis 
32:	rtn D


CLASS char$14 descInx:14 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
doE: 
1:	setThisStack
2:	pushthis 
3:	rtn D


CLASS integer$30 descInx:30 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
doE: 
1:	setThisStack
2:	pushthis 
3:	rtn D


CLASS Object$44 descInx:44 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	innerP 1
14:	rpopThisObj
15:	setThisStack
16:	pushthis 
17:	rtn D


CLASS X_asString$55 descInx:55 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	pushText 1
9:	pushthis 
10:	rstoreg 2
12:	rtnAlloc 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	innerP 3
19:	rpopThisObj
20:	setThisStack
21:	pushthis 
22:	rtn D


CLASS universal$56 descInx:56 objSize:0 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
doE: 
1:	setThisStack
2:	pushthis 
3:	rtn D


CLASS Boolean$59 descInx:59 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
allocE: 
doE: 
1:	setThisStack
2:	pushthis 
3:	rtn D


CLASS False$62 descInx:62 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	allocEventQ 0
3:	mvStack
allocE: 
4:	rtnAlloc 1
doE: 
6:	doEventQ 
7:	mvStack
8:	pushc 0
10:	pushthis 
11:	storeg 1
13:	setThisStack
14:	pushthis 
15:	rtn D


CLASS True$63 descInx:63 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	allocEventQ 0
3:	mvStack
allocE: 
4:	rtnAlloc 1
doE: 
6:	doEventQ 
7:	mvStack
8:	pushc 1
10:	pushthis 
11:	storeg 1
13:	setThisStack
14:	pushthis 
15:	rtn D


CLASS put$81 descInx:81 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS this$88 descInx:88 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnAlloc 1
doE: 
12:	doEventQ 
13:	mvStack
14:	setThisStack
15:	pushthis 
16:	rtn D


CLASS print$103 descInx:103 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	invoke 115 0 0
18:	rpop 
19:	setThisStack
20:	pushthis 
21:	rtn D


CLASS length$105 descInx:105 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushc 1
16:	uminus
17:	xpushg 1 0
20:	pushthis 
21:	storeg 2
23:	setThisStack
24:	pushthis 
25:	rtn D


CLASS Object$S$107 descInx:107 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
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
23:	xpushg 1 0
26:	%prim put 2
28:	setThisStack
29:	pushthis 
30:	rtn D


CLASS repeat$108 descInx:108 objSize:3 originOff: 0 visibility: 1
storeOrgAndArgsE:
doE: 
1:	invoke 44 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


CLASS for:to:repeat$109 descInx:109 objSize:3 originOff: 0 visibility: 1
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnAlloc 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	pushg 1
17:	pushthis 
18:	storeg 3
20:	pushthis 
21:	invoke 110 0 0
27:	rpop 
28:	setThisStack
29:	pushthis 
30:	rtn D


CLASS _doIt$110 descInx:110 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
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
22:	jmpFalse 49
25:	pushthis 
26:	rpushg 1
28:	invokev 3 0 0
32:	rpop 
33:	pushthis 
34:	rpushg 1
36:	pushg 3
38:	pushc 1
40:	+
41:	pushthis 
42:	rpushg 1
44:	storeg 3
46:	jmp 11
49:	setThisStack
50:	pushthis 
51:	rtn D


CLASS Object$S$111 descInx:111 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	invokev 3 0 0
18:	rpop 
19:	pushthis 
20:	rpushg 1
22:	pushg 3
24:	pushc 1
26:	+
27:	pushthis 
28:	rpushg 1
30:	storeg 3
32:	jmp 11
35:	setThisStack
36:	pushthis 
37:	rtn D


CLASS if:then$113 descInx:113 objSize:1 originOff: 0 visibility: 1
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS thenPart$114 descInx:114 objSize:3 originOff: 0 visibility: 1
storeOrgAndArgsE:
doE: 
1:	invoke 44 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


CLASS for:to:repeat$S$115 descInx:115 objSize:4 originOff: 4 visibility: 1
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	rpushg 1
11:	invoke 105 0 0
17:	pushg 2
19:	pushthis 
20:	storeg 2
22:	pushthis 
23:	storeg 1
25:	allocEventQ 0
allocE: 
27:	rtnAlloc 1
29:	toSuper 109
doE: 
32:	mvStack
33:	rtnInner


CLASS Array$124 descInx:124 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS Indexed$137 descInx:137 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS asString$149 descInx:149 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	pushText 1
9:	pushthis 
10:	rstoreg 2
12:	rtnAlloc 1
doE: 
14:	doEventQ 
15:	mvStack
16:	setThisStack
17:	pushthis 
18:	rtn D


CLASS putint$191 descInx:191 objSize:4 originOff: 0 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	pushc 20
9:	pushthis 
10:	pushc 1
12:	allocIndexed 137 1 0 
17:	pushthis 
18:	rstoreg 2
20:	rtnAlloc 1
doE: 
22:	doEventQ 
23:	mvStack
24:	pushthis 
25:	pushg 1
27:	pushc 0
29:	lt
30:	pushthis 
31:	storeg 4
33:	pushthis 
34:	pushg 4
36:	jmpFalse 48
39:	pushc 0
41:	pushthis 
42:	pushg 1
44:	-
45:	pushthis 
46:	storeg 1
48:	pushthis 
49:	invoke 193 0 0
55:	rpop 
56:	pushthis 
57:	pushg 4
59:	jmpFalse 66
62:	pushc 45
64:	%prim put 2
66:	pushthis 
67:	invoke 197 0 0
73:	rpop 
74:	setThisStack
75:	pushthis 
76:	rtn D


CLASS Object$S$192 descInx:192 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 0
13:	pushthis 
14:	pushg 1
16:	-
17:	pushthis 
18:	storeg 1
20:	setThisStack
21:	pushthis 
22:	rtn D


CLASS loop$193 descInx:193 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushg 3
16:	pushc 1
18:	+
19:	pushthis 
20:	rpushg 1
22:	storeg 3
24:	pushthis 
25:	rpushg 1
27:	rpushg 2
29:	pushthis 
30:	rpushg 1
32:	pushg 1
34:	pushc 10
36:	modd
37:	pushthis 
38:	rpushg 1
40:	pushg 3
42:	xstoreg 1 0
45:	pushthis 
46:	rpushg 1
48:	pushg 1
50:	pushc 10
52:	idiv
53:	pushthis 
54:	rpushg 1
56:	storeg 1
58:	pushthis 
59:	rpushg 1
61:	pushg 1
63:	pushc 0
65:	gt 
66:	jmpFalse 72
69:	jmp 11
72:	setThisStack
73:	pushthis 
74:	rtn D


CLASS Object$S$194 descInx:194 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	jmp 11
14:	setThisStack
15:	pushthis 
16:	rtn D


CLASS Object$S$195 descInx:195 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 45
13:	%prim put 2
15:	setThisStack
16:	pushthis 
17:	rtn D


CLASS Object$S$196 descInx:196 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	pushg 3
18:	pushc 1
20:	+
21:	pushthis 
22:	rpushg 1
24:	pushg 3
26:	-
27:	pushthis 
28:	storeg 2
30:	pushc 48
32:	pushthis 
33:	rpushg 1
35:	rpushg 4
37:	rpushg 2
39:	pushthis 
40:	pushg 2
42:	xpushg 1 0
45:	+
46:	%prim put 2
48:	setThisStack
49:	pushthis 
50:	rtn D


CLASS for:to:repeat$S$197 descInx:197 objSize:4 originOff: 4 visibility: 1
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	pushg 3
11:	pushthis 
12:	storeg 2
14:	pushthis 
15:	storeg 1
17:	allocEventQ 0
allocE: 
19:	rtnAlloc 1
21:	toSuper 109
doE: 
24:	mvStack
25:	rtnInner


CLASS ConsoleIF$231 descInx:231 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS put$232 descInx:232 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS puttext$233 descInx:233 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnAlloc 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	innerP 3
17:	rpopThisObj
18:	setThisStack
19:	pushthis 
20:	rtn D


CLASS putint$234 descInx:234 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnAlloc 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	innerP 3
17:	rpopThisObj
18:	setThisStack
19:	pushthis 
20:	rtn D


CLASS LIB$235 descInx:235 objSize:5 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 236 3 1
14:	rpop 
15:	pushthis 
16:	invoke 250 4 1
22:	rpop 
23:	pushthis 
24:	invoke 284 5 1
30:	rpop 
31:	rtnAlloc 1
doE: 
33:	doEventQ 
34:	mvStack
35:	setThisStack
36:	pushthis 
37:	rtn D


CLASS BasicIO$236 descInx:236 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 237 2 1
14:	rpop 
15:	pushthis 
16:	invoke 241 3 1
22:	rpop 
23:	rtnAlloc 1
doE: 
25:	doEventQ 
26:	mvStack
27:	setThisStack
28:	pushthis 
29:	rtn D


CLASS keyboard$237 descInx:237 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS screen$241 descInx:241 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	rpushg 1
10:	invoke 242 2 1
16:	rpop 
17:	rtnAlloc 1
doE: 
19:	doEventQ 
20:	mvStack
21:	setThisStack
22:	pushthis 
23:	rtn D


CLASS Lock$242 descInx:242 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS Dimensions$250 descInx:250 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS StringLib$284 descInx:284 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	saveStringOrigin
7:	mvStack
allocE: 
8:	rtnAlloc 1
doE: 
10:	doEventQ 
11:	mvStack
12:	setThisStack
13:	pushthis 
14:	rtn D


CLASS String$285 descInx:285 objSize:0 originOff: 0 visibility: 2
storeOrgAndArgsE:
1:	allocEventQ 1
3:	mvStack
allocE: 
4:	rtnAlloc 1
doE: 
6:	doEventQ 
7:	mvStack
8:	setThisStack
9:	pushthis 
10:	rtn D


CLASS +$286 descInx:286 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	pushText 1
12:	pushthis 
13:	rstoreg 3
15:	rtnAlloc 1
doE: 
17:	doEventQ 
18:	mvStack
19:	pushthis 
20:	rpushg 1
22:	invoke 105 0 0
28:	pushg 2
30:	pushthis 
31:	storeg 4
33:	pushthis 
34:	invoke 287 0 0
40:	rpop 
41:	setThisStack
42:	pushthis 
43:	rtn D


CLASS doplus$287 descInx:287 objSize:4 originOff: 1 visibility: 0
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
17:	invoke 105 0 0
23:	pushg 2
25:	+
26:	pushthis 
27:	pushc 1
29:	allocIndexed 137 1 0 
34:	pushthis 
35:	rstoreg 4
37:	rtnAlloc 1
doE: 
39:	doEventQ 
40:	mvStack
41:	pushthis 
42:	invoke 289 0 0
48:	rpop 
49:	pushthis 
50:	invoke 291 0 0
56:	rpop 
57:	pushthis 
58:	rpushg 4
60:	%prim asString 118
62:	pushthis 
63:	rpushg 1
65:	rstoreg 3
67:	setThisStack
68:	pushthis 
69:	rtn D


CLASS Object$S$288 descInx:288 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	rpushg 1
18:	rpushg 1
20:	pushthis 
21:	rpushg 1
23:	pushg 3
25:	xpushg 1 0
28:	pushthis 
29:	rpushg 1
31:	rpushg 4
33:	storeg 2
35:	pushthis 
36:	rpushg 1
38:	rpushg 4
40:	rpushg 4
42:	pushthis 
43:	rpushg 1
45:	rpushg 4
47:	pushg 2
49:	pushthis 
50:	rpushg 1
52:	pushg 3
54:	xstoreg 1 0
57:	setThisStack
58:	pushthis 
59:	rtn D


CLASS for:to:repeat$S$289 descInx:289 objSize:4 originOff: 4 visibility: 1
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
21:	rtnAlloc 1
23:	toSuper 109
doE: 
26:	mvStack
27:	rtnInner


CLASS Object$S$290 descInx:290 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	rpushg 1
18:	rpushg 2
20:	pushthis 
21:	rpushg 1
23:	pushg 3
25:	xpushg 1 0
28:	pushthis 
29:	rpushg 1
31:	rpushg 4
33:	storeg 2
35:	pushthis 
36:	rpushg 1
38:	rpushg 4
40:	rpushg 1
42:	pushg 4
44:	pushthis 
45:	rpushg 1
47:	pushg 3
49:	+
50:	pushthis 
51:	rpushg 1
53:	rpushg 4
55:	storeg 3
57:	pushthis 
58:	rpushg 1
60:	rpushg 4
62:	rpushg 4
64:	pushthis 
65:	rpushg 1
67:	rpushg 4
69:	pushg 2
71:	pushthis 
72:	rpushg 1
74:	rpushg 4
76:	pushg 3
78:	xstoreg 1 0
81:	setThisStack
82:	pushthis 
83:	rtn D


CLASS for:to:repeat$S$291 descInx:291 objSize:4 originOff: 4 visibility: 1
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	rpushg 1
11:	rpushg 2
13:	invoke 105 0 0
19:	pushg 2
21:	pushthis 
22:	storeg 2
24:	pushthis 
25:	storeg 1
27:	allocEventQ 0
allocE: 
29:	rtnAlloc 1
31:	toSuper 109
doE: 
34:	mvStack
35:	rtnInner


CLASS =$296 descInx:296 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	rshiftup 1
3:	tstOriginNone 
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	rshiftdown 1
13:	pushthis 
14:	rstoreg 2
16:	tstOriginNone 
17:	rstore 1
19:	allocEventQ 0
21:	mvStack
allocE: 
doE: 
22:	doEventQ 
23:	mvStack
24:	pushthis 
25:	invoke 297 0 0
31:	rpop 
32:	setThisStack
33:	pushthis 
34:	rtn D


CLASS loop$297 descInx:297 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	invoke 105 0 0
22:	pushg 2
24:	pushthis 
25:	storeg 4
27:	pushthis 
28:	pushg 4
30:	pushthis 
31:	rpushg 1
33:	rpushg 2
35:	invoke 105 0 0
41:	pushg 2
43:	ne 
44:	jmpFalse 50
47:	jmp 71
50:	invoke 63 0 0
56:	pushg 1
58:	pushthis 
59:	rpushg 1
61:	storeg 3
63:	pushthis 
64:	invoke 301 0 0
70:	rpop 
71:	setThisStack
72:	pushthis 
73:	rtn D


CLASS Object$S$298 descInx:298 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	jmp 14
14:	setThisStack
15:	pushthis 
16:	rtn D


CLASS Object$S$299 descInx:299 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	rpushg 1
18:	rpushg 1
20:	pushthis 
21:	rpushg 1
23:	pushg 3
25:	xpushg 1 0
28:	pushthis 
29:	rpushg 1
31:	rpushg 4
33:	storeg 2
35:	pushthis 
36:	rpushg 1
38:	rpushg 4
40:	rpushg 1
42:	rpushg 2
44:	pushthis 
45:	rpushg 1
47:	pushg 3
49:	xpushg 1 0
52:	pushthis 
53:	rpushg 1
55:	rpushg 4
57:	storeg 3
59:	pushthis 
60:	rpushg 1
62:	rpushg 4
64:	pushg 2
66:	pushthis 
67:	rpushg 1
69:	rpushg 4
71:	pushg 3
73:	ne 
74:	jmpFalse 101
77:	invoke 62 0 0
83:	pushg 1
85:	pushthis 
86:	rpushg 1
88:	rpushg 4
90:	rpushg 1
92:	storeg 3
94:	break 2 2 297 0
101:	setThisStack
102:	pushthis 
103:	rtn D


CLASS Object$S$300 descInx:300 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	invoke 62 0 0
17:	pushg 1
19:	pushthis 
20:	rpushg 1
22:	rpushg 4
24:	rpushg 1
26:	storeg 3
28:	break 2 2 297 0
35:	setThisStack
36:	pushthis 
37:	rtn D


CLASS for:to:repeat$S$301 descInx:301 objSize:4 originOff: 4 visibility: 1
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushthis 
7:	rpushg 4
9:	rpushg 1
11:	rpushg 1
13:	invoke 105 0 0
19:	pushg 2
21:	pushthis 
22:	storeg 2
24:	pushthis 
25:	storeg 1
27:	allocEventQ 0
allocE: 
29:	rtnAlloc 1
31:	toSuper 109
doE: 
34:	mvStack
35:	rtnInner


CLASS <=$303 descInx:303 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	rshiftup 1
3:	tstOriginNone 
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	rshiftdown 1
13:	pushthis 
14:	rstoreg 2
16:	tstOriginNone 
17:	rstore 1
19:	allocEventQ 0
21:	mvStack
allocE: 
22:	pushthis 
23:	invoke 304 4 1
29:	rpop 
doE: 
30:	doEventQ 
31:	mvStack
32:	setThisStack
33:	pushthis 
34:	rtn D


CLASS loop$304 descInx:304 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	invoke 105 0 0
22:	pushg 2
24:	pushthis 
25:	storeg 3
27:	pushthis 
28:	rpushg 1
30:	rpushg 2
32:	invoke 105 0 0
38:	pushg 2
40:	pushthis 
41:	storeg 4
43:	pushthis 
44:	pushg 3
46:	pushthis 
47:	pushg 4
49:	lt
50:	jmpFalse 64
53:	pushthis 
54:	invoke 315 0 0
60:	rpop 
61:	jmp 72
64:	pushthis 
65:	invoke 316 0 0
71:	rpop 
72:	pushthis 
73:	invoke 305 0 0
79:	rpop 
80:	setThisStack
81:	pushthis 
82:	rtn D


CLASS matchEq$305 descInx:305 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	invoke 306 0 0
18:	rpop 
19:	pushthis 
20:	invoke 309 0 0
26:	rpop 
27:	pushthis 
28:	invoke 312 0 0
34:	rpop 
35:	setThisStack
36:	pushthis 
37:	rtn D


CLASS isEmpty$306 descInx:306 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	pushg 3
18:	pushc 0
20:	eq 
21:	jmpFalse 55
24:	pushthis 
25:	rpushg 1
27:	rpushg 1
29:	pushg 3
31:	pushthis 
32:	rpushg 1
34:	rpushg 1
36:	pushg 4
38:	le
39:	pushthis 
40:	rpushg 1
42:	rpushg 1
44:	rpushg 1
46:	storeg 3
48:	break 1 2 305 0
55:	pushthis 
56:	rpushg 1
58:	rpushg 1
60:	pushg 4
62:	pushc 0
64:	eq 
65:	jmpFalse 92
68:	invoke 62 0 0
74:	pushg 1
76:	pushthis 
77:	rpushg 1
79:	rpushg 1
81:	rpushg 1
83:	storeg 3
85:	break 1 2 305 0
92:	setThisStack
93:	pushthis 
94:	rtn D


CLASS Object$S$307 descInx:307 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	pushg 3
18:	pushthis 
19:	rpushg 1
21:	rpushg 1
23:	pushg 4
25:	le
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	storeg 3
35:	break 1 2 305 0
42:	setThisStack
43:	pushthis 
44:	rtn D


CLASS Object$S$308 descInx:308 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	invoke 62 0 0
17:	pushg 1
19:	pushthis 
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	storeg 3
28:	break 1 2 305 0
35:	setThisStack
36:	pushthis 
37:	rtn D


CLASS loop$309 descInx:309 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushg 2
16:	pushc 1
18:	+
19:	pushthis 
20:	rpushg 1
22:	storeg 2
24:	pushthis 
25:	rpushg 1
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	pushthis 
34:	rpushg 1
36:	pushg 2
38:	xpushg 1 0
41:	pushthis 
42:	rpushg 1
44:	storeg 3
46:	pushthis 
47:	rpushg 1
49:	rpushg 1
51:	rpushg 1
53:	rpushg 2
55:	pushthis 
56:	rpushg 1
58:	pushg 2
60:	xpushg 1 0
63:	pushthis 
64:	rpushg 1
66:	storeg 4
68:	pushthis 
69:	rpushg 1
71:	pushg 3
73:	pushthis 
74:	rpushg 1
76:	pushg 4
78:	eq 
79:	jmpFalse 90
82:	pushthis 
83:	invoke 310 0 0
89:	rpop 
90:	setThisStack
91:	pushthis 
92:	rtn D


CLASS Object$S$310 descInx:310 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	pushg 2
18:	pushthis 
19:	rpushg 1
21:	rpushg 1
23:	rpushg 1
25:	pushg 2
27:	lt
28:	jmpFalse 38
31:	break 1 1 309 0
38:	setThisStack
39:	pushthis 
40:	rtn D


CLASS Object$S$311 descInx:311 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	break 1 1 309 0
18:	setThisStack
19:	pushthis 
20:	rtn D


CLASS doit$312 descInx:312 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushg 3
16:	pushthis 
17:	rpushg 1
19:	pushg 4
21:	eq 
22:	jmpFalse 36
25:	pushthis 
26:	invoke 313 0 0
32:	rpop 
33:	jmp 44
36:	pushthis 
37:	invoke 314 0 0
43:	rpop 
44:	setThisStack
45:	pushthis 
46:	rtn D


CLASS Object$S$313 descInx:313 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushg 3
20:	pushthis 
21:	rpushg 1
23:	rpushg 1
25:	rpushg 1
27:	pushg 4
29:	le
30:	pushthis 
31:	rpushg 1
33:	rpushg 1
35:	rpushg 1
37:	rpushg 1
39:	storeg 3
41:	break 2 2 305 0
48:	setThisStack
49:	pushthis 
50:	rtn D


CLASS Object$S$314 descInx:314 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	pushg 3
18:	pushthis 
19:	rpushg 1
21:	rpushg 1
23:	pushg 4
25:	lt
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	rpushg 1
35:	storeg 3
37:	break 2 2 305 0
44:	setThisStack
45:	pushthis 
46:	rtn D


CLASS Object$S$315 descInx:315 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushg 3
16:	pushthis 
17:	rpushg 1
19:	storeg 2
21:	setThisStack
22:	pushthis 
23:	rtn D


CLASS Object$S$316 descInx:316 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	pushg 4
16:	pushthis 
17:	rpushg 1
19:	storeg 2
21:	setThisStack
22:	pushthis 
23:	rtn D


CLASS workspace$319 descInx:319 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	pushthis 
8:	invoke 320 2 1
14:	rpop 
15:	rtnAlloc 1
doE: 
17:	doEventQ 
18:	mvStack
19:	setThisStack
20:	pushthis 
21:	rtn D


CLASS hello$320 descInx:320 objSize:6 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 10
13:	%prim put 2
15:	pushc 13
17:	%prim put 2
19:	pushc 37
21:	%prim put 2
23:	pushc 65
25:	%prim put 2
27:	pushc 66
29:	%prim put 2
31:	pushc 67
33:	pushthis 
34:	storeg 5
36:	pushthis 
37:	pushg 5
39:	%prim put 2
41:	pushc 28
43:	pushthis 
44:	storeg 2
46:	pushc 5
48:	pushthis 
49:	storeg 4
51:	pushthis 
52:	pushg 2
54:	pushthis 
55:	pushg 4
57:	pushc 8
59:	*
60:	+
61:	pushthis 
62:	storeg 3
64:	pushthis 
65:	pushg 3
67:	%prim put 2
69:	pushc 139
71:	pushthis 
72:	storeg 3
74:	pushthis 
75:	pushg 3
77:	pushc 2
79:	idiv
80:	pushthis 
81:	storeg 2
83:	pushthis 
84:	pushg 2
86:	%prim put 2
88:	pushc 170
90:	pushthis 
91:	storeg 3
93:	pushthis 
94:	pushg 3
96:	pushc 100
98:	modd
99:	pushthis 
100:	storeg 2
102:	pushthis 
103:	pushg 2
105:	%prim put 2
107:	pushc 3
109:	pushthis 
110:	storeg 2
112:	pushc 17
114:	pushthis 
115:	storeg 3
117:	pushthis 
118:	pushg 3
120:	pushthis 
121:	pushg 2
123:	-
124:	pushc 101
126:	pushc 96
128:	-
129:	*
130:	pushc 1
132:	+
133:	pushthis 
134:	storeg 4
136:	pushthis 
137:	pushg 4
139:	%prim put 2
141:	pushc 72
143:	%prim put 2
145:	pushthis 
146:	pushc 74
148:	invoke 321 0 0
154:	rpop 
155:	pushthis 
156:	pushc 70
158:	pushc 5
160:	invoke 343 0 0
166:	pushg 4
168:	pushthis 
169:	storeg 5
171:	pushthis 
172:	pushg 5
174:	%prim put 2
176:	pushthis 
177:	pushc 77
179:	invoke 344 0 0
185:	rpushg 3
187:	pushthis 
188:	rstoreg 6
190:	pushthis 
191:	rpushg 6
193:	invoke 323 0 0
199:	pushg 2
201:	pushthis 
202:	storeg 5
204:	pushc 84
206:	pushthis 
207:	storeg 5
209:	pushthis 
210:	invoke 329 0 0
216:	rpop 
217:	pushc 87
219:	pushthis 
220:	storeg 5
222:	pushthis 
223:	invoke 348 0 0
229:	rpop 
230:	pushthis 
231:	invoke 339 0 0
237:	rpop 
238:	pushthis 
239:	invoke 342 0 0
245:	rpop 
246:	pushc 117
248:	invoke 191 0 0
254:	rpop 
255:	pushText 1
257:	invoke 103 0 0
263:	rpop 
264:	pushthis 
265:	invoke 322 0 1
271:	pushthis 
272:	rstoreg 6
274:	pushthis 
275:	pushc 81
277:	pushc 9
279:	pushthis 
280:	rpushg 6
282:	invoke 324 0 0
288:	pushg 5
290:	pushthis 
291:	storeg 2
293:	pushthis 
294:	pushc 81
296:	pushc 9
298:	pushthis 
299:	invoke 322 0 1
305:	invoke 324 0 0
311:	pushg 5
313:	pushthis 
314:	storeg 2
316:	pushthis 
317:	pushg 2
319:	invoke 191 0 0
325:	rpop 
326:	pushthis 
327:	invoke 325 0 0
333:	rpop 
334:	setThisStack
335:	pushthis 
336:	rtn D


CLASS snorf$321 descInx:321 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnAlloc 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushc 73
16:	%prim put 2
18:	pushthis 
19:	pushg 2
21:	%prim put 2
23:	setThisStack
24:	pushthis 
25:	rtn D


CLASS Record$322 descInx:322 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 1
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	setThisStack
12:	pushthis 
13:	rtn D


CLASS get$323 descInx:323 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 78
13:	pushthis 
14:	storeg 2
16:	setThisStack
17:	pushthis 
18:	rtn D


CLASS fooBar$324 descInx:324 objSize:6 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	rstoreg 4
4:	pushthis 
5:	storeg 3
7:	pushthis 
8:	storeg 2
10:	tstOriginNone 
11:	rstore 1
13:	allocEventQ 0
15:	mvStack
allocE: 
16:	rtnAlloc 1
doE: 
18:	doEventQ 
19:	mvStack
20:	pushc 43
22:	%prim put 2
24:	pushthis 
25:	rpushg 4
27:	invoke 323 0 0
33:	pushg 2
35:	pushthis 
36:	storeg 6
38:	pushthis 
39:	rpushg 1
41:	pushg 3
43:	pushthis 
44:	rpushg 1
46:	pushg 4
48:	+
49:	pushthis 
50:	rpushg 1
52:	storeg 2
54:	pushthis 
55:	pushg 2
57:	pushthis 
58:	pushg 3
60:	+
61:	pushthis 
62:	pushg 6
64:	+
65:	pushthis 
66:	storeg 5
68:	setThisStack
69:	pushthis 
70:	rtn D


CLASS fisk$325 descInx:325 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 119
13:	pushthis 
14:	rpushg 1
16:	pushg 2
18:	+
19:	pushthis 
20:	storeg 2
22:	pushthis 
23:	pushg 2
25:	pushc 0
27:	gt 
28:	jmpFalse 42
31:	pushthis 
32:	invoke 327 0 0
38:	rpop 
39:	jmp 50
42:	pushthis 
43:	invoke 328 0 0
49:	rpop 
50:	pushc 81
52:	%prim put 2
54:	pushthis 
55:	invoke 326 0 0
61:	rpop 
62:	setThisStack
63:	pushthis 
64:	rtn D


CLASS snaps$326 descInx:326 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	pushg 3
18:	pushthis 
19:	rpushg 1
21:	rpushg 1
23:	pushg 4
25:	+
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	storeg 2
33:	setThisStack
34:	pushthis 
35:	rtn D


CLASS Object$S$327 descInx:327 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 121
13:	pushthis 
14:	rpushg 1
16:	storeg 2
18:	setThisStack
19:	pushthis 
20:	rtn D


CLASS Object$S$328 descInx:328 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 123
13:	pushthis 
14:	rpushg 1
16:	storeg 2
18:	setThisStack
19:	pushthis 
20:	rtn D


CLASS ArrayXX$329 descInx:329 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	pushc 10
9:	pushthis 
10:	pushc 1
12:	allocIndexed 124 1 0 
17:	pushthis 
18:	rstoreg 2
20:	rtnAlloc 1
doE: 
22:	doEventQ 
23:	mvStack
24:	pushthis 
25:	rpushg 2
27:	pushc 78
29:	pushc 3
31:	xstoreg 1 0
34:	pushthis 
35:	rpushg 2
37:	pushc 3
39:	xpushg 1 0
42:	pushthis 
43:	storeg 3
45:	pushthis 
46:	pushg 3
48:	%prim put 2
50:	pushthis 
51:	rpushg 2
53:	pushc 79
55:	pushc 1
57:	xstoreg 1 0
60:	pushthis 
61:	rpushg 2
63:	pushc 1
65:	xpushg 1 0
68:	pushthis 
69:	storeg 3
71:	pushthis 
72:	pushg 3
74:	%prim put 2
76:	pushthis 
77:	rpushg 2
79:	pushc 80
81:	pushc 10
83:	xstoreg 1 0
86:	pushthis 
87:	rpushg 2
89:	pushc 10
91:	xpushg 1 0
94:	pushthis 
95:	storeg 3
97:	pushthis 
98:	pushg 3
100:	%prim put 2
102:	pushthis 
103:	invoke 331 0 0
109:	rpop 
110:	pushthis 
111:	invoke 333 0 0
117:	rpop 
118:	pushthis 
119:	rpushg 1
121:	pushg 5
123:	%prim put 2
125:	pushc 85
127:	pushthis 
128:	rpushg 1
130:	storeg 5
132:	setThisStack
133:	pushthis 
134:	rtn D


CLASS Object$S$330 descInx:330 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	rpushg 2
18:	pushc 80
20:	pushthis 
21:	rpushg 1
23:	pushg 3
25:	+
26:	pushthis 
27:	rpushg 1
29:	pushg 3
31:	xstoreg 1 0
34:	setThisStack
35:	pushthis 
36:	rtn D


CLASS for:to:repeat$S$331 descInx:331 objSize:4 originOff: 4 visibility: 1
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushc 3
8:	pushthis 
9:	storeg 2
11:	pushthis 
12:	storeg 1
14:	allocEventQ 0
allocE: 
16:	rtnAlloc 1
18:	toSuper 109
doE: 
21:	mvStack
22:	rtnInner


CLASS Object$S$332 descInx:332 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	rpushg 1
14:	rpushg 4
16:	rpushg 2
18:	pushthis 
19:	rpushg 1
21:	pushg 3
23:	xpushg 1 0
26:	%prim put 2
28:	setThisStack
29:	pushthis 
30:	rtn D


CLASS for:to:repeat$S$333 descInx:333 objSize:4 originOff: 4 visibility: 1
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 4
4:	pushc 1
6:	pushc 3
8:	pushthis 
9:	storeg 2
11:	pushthis 
12:	storeg 1
14:	allocEventQ 0
allocE: 
16:	rtnAlloc 1
18:	toSuper 109
doE: 
21:	mvStack
22:	rtnInner


CLASS helloWorld$334 descInx:334 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushthis 
12:	invokev 3 0 0
16:	rpop 
17:	pushthis 
18:	invokev 4 0 0
22:	rpop 
23:	setThisStack
24:	pushthis 
25:	rtn D


CLASS how$335 descInx:335 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
doE: 
1:	invoke 44 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


CLASS are$336 descInx:336 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
doE: 
1:	invoke 44 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


CLASS Person$337 descInx:337 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 80
13:	%prim put 2
15:	pushthis 
16:	innerP 3
18:	rpopThisObj
19:	setThisStack
20:	pushthis 
21:	rtn D


CLASS you$338 descInx:338 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
doE: 
1:	rpushg 1
3:	invoke 337 0 0
9:	pushthis 
10:	rstoreg 2
12:	setThisStack
13:	pushthis 
14:	rpushg 2
16:	rtn D


CLASS Greating$339 descInx:339 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
allocE: 
12:	rtnAlloc 1
14:	toSuper 334
doE: 
17:	mvStack
18:	rtnInner


CLASS how$340 descInx:340 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 72
13:	%prim put 2
15:	setThisStack
16:	pushthis 
17:	rtn D


CLASS Super$341 descInx:341 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 83
13:	%prim put 2
15:	pushthis 
16:	innerP 3
18:	rpopThisObj
19:	pushthis 
20:	rpushg 1
22:	pushg 5
24:	%prim put 2
26:	setThisStack
27:	pushthis 
28:	rtn D


CLASS Main$342 descInx:342 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
allocE: 
12:	rtnAlloc 1
14:	toSuper 341
doE: 
17:	mvStack
18:	pushc 84
20:	%prim put 2
22:	pushc 85
24:	pushthis 
25:	rpushg 1
27:	storeg 5
29:	pushthis 
30:	innerP 4
32:	rpopThisObj
33:	rtnInner


CLASS ParamVVV$343 descInx:343 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 3
4:	pushthis 
5:	storeg 2
7:	tstOriginNone 
8:	rstore 1
10:	allocEventQ 0
12:	mvStack
allocE: 
13:	rtnAlloc 1
doE: 
15:	doEventQ 
16:	mvStack
17:	pushthis 
18:	pushg 2
20:	pushthis 
21:	pushg 3
23:	+
24:	%prim put 2
26:	pushthis 
27:	pushg 2
29:	pushthis 
30:	pushg 3
32:	+
33:	pushc 1
35:	+
36:	pushthis 
37:	storeg 4
39:	setThisStack
40:	pushthis 
41:	rtn D


CLASS ParamRRR$344 descInx:344 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnAlloc 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	pushg 2
17:	%prim put 2
19:	pushthis 
20:	rpushg 1
22:	invoke 322 0 1
28:	pushthis 
29:	rstoreg 3
31:	setThisStack
32:	pushthis 
33:	rtn D


CLASS doPut:exe$345 descInx:345 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	pushthis 
2:	storeg 2
4:	tstOriginNone 
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
allocE: 
10:	rtnAlloc 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	pushg 2
17:	%prim put 2
19:	pushthis 
20:	invokev 3 0 0
24:	rpop 
25:	setThisStack
26:	pushthis 
27:	rtn D


CLASS S$346 descInx:346 objSize:3 originOff: 1 visibility: 0
storeOrgAndArgsE:
doE: 
1:	invoke 44 0 0
7:	pushthis 
8:	rstoreg 2
10:	setThisStack
11:	pushthis 
12:	rpushg 2
14:	rtn D


CLASS Object$S$347 descInx:347 objSize:1 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	allocEventQ 0
6:	mvStack
allocE: 
7:	rtnAlloc 1
doE: 
9:	doEventQ 
10:	mvStack
11:	pushc 86
13:	%prim put 2
15:	pushthis 
16:	rpushg 1
18:	rpushg 1
20:	pushg 5
22:	%prim put 2
24:	setThisStack
25:	pushthis 
26:	rtn D


CLASS doPut:exe$S$348 descInx:348 objSize:2 originOff: 1 visibility: 0
storeOrgAndArgsE:
1:	tstOriginNone 
2:	rstore 1
4:	pushthis 
5:	rpushg 1
7:	pushc 85
9:	pushthis 
10:	storeg 2
12:	tstOriginNone 
13:	rstore 1
15:	allocEventQ 0
allocE: 
17:	rtnAlloc 1
19:	toSuper 345
doE: 
22:	mvStack
23:	rtnInner


CLASS valProx descInx:349 objSize:4 originOff: 1 visibility: 0
storeOrgAndArgsE:
doE: 
1:	0


CLASS VM descInx:350 objSize:2 originOff: 0 visibility: 0
storeOrgAndArgsE:
doE: 
1:	pushthis 
2:	invoke 1 0 1
8:	stop 
9:	rtn D


CLASS EventProcessor descInx:351 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
doE: 
1:	stop 


CLASS ThreadStub descInx:352 objSize:1 originOff: 0 visibility: 0
storeOrgAndArgsE:
doE: 
1:	call D
3:	stop 

