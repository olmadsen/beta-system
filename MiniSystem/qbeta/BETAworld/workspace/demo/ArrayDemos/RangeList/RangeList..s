	-- QBETA
	-- Module:gen: 
	component Comp NoOfDescs: 1015
	-- ConsRef:gen: BETAworld

	class Object 33
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: := V: ? Object
	-- pattern:gen: = obj: ? Object -> V: ? Boolean
	-- pattern:gen: <> obj: ? Object -> V: ? Boolean
	-- pattern:gen: suspend
	-- pattern:gen: attach(V: ? integer)
	-- pattern:gen: resume
	call(D)Resume
	-- pattern:gen: onResume
	-- pattern:gen: onSuspend
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L1:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner Object:IS-empty: staticOff: 0
	-- Invocation:gen: %inner Object
	-- Invocation:loadOrigin: %inner Object
	-- Invocation:loadOrigin:scan: %inner Object
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner Object
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner Object
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L2:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BETAworld 1
	rstore 1 origin
	allocEventQ
	pushThis 
	saveBETAworld
	mvStack 
	-- pattern:gen: error
	-- Module:gen: 
	-- ModuleItem:gen BETA
	-- ConsRef:gen: BETA
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 3 2 BETA
	rpop
	-- Module:gen: 
	-- ModuleItem:gen LIB
	-- ConsRef:gen: LIB
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 71 3 LIB
	rpop
	-- Module:gen: 
	-- ModuleItem:gen workspace
	-- ConsRef:gen: workspace
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 260 4 workspace
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L3:
	-- Include:gen: 
 L4:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BETA 3
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: integer(W: ? integer)
	-- pattern:gen: Boolean
	-- pattern:gen: False -> B: ? Boolean
	-- pattern:gen: True -> B: ? Boolean
	-- pattern:gen: char
	-- pattern:gen: put(ch: ? char)
	-- pattern:gen: Object
	-- pattern:gen: none
	-- pattern:gen: inner
	-- pattern:gen: %inner P: ? Object
	-- pattern:gen: %this P: ? Object
	-- pattern:gen: disable
	-- pattern:gen: enable
	-- pattern:gen: fork(S: ? Object)
	-- pattern:gen: sleep(V: ? integer)
	-- pattern:gen: core
	-- pattern:gen: thisCore -> C: ? core
	-- pattern:gen: Indexed(range: ? Integer,elm:< Object)
	-- pattern:gen: %if _cond: ? Boolean %then% _thenPart:< Object
	-- pattern:gen: %restart Obj: ? integer
	-- pattern:gen: %leave Obj: ? integer
	-- pattern:gen: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object
	-- pattern:gen: cycle
	-- pattern:gen: %for first: ? integer %to% last: ? integer %do% body:< Object
	-- pattern:gen: newline
	-- pattern:gen: putint(V: ? integer)
	rtnEventQ 0
	DO:
	mvStack 
 L5:
	-- Include:gen: 
 L6:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class LIB 71
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_dummy
	-- Module:gen: 
	-- ModuleItem:gen BasicSystem
	-- ConsRef:gen: BasicSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 72 2 BasicSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen Complex
	-- ConsRef:gen: Complex
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 167 3 Complex
	rpop
	-- Module:gen: 
	-- ModuleItem:gen Containers
	-- ConsRef:gen: Containers
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 73 4 Containers
	rpop
	-- Module:gen: 
	-- ModuleItem:gen EMC2array
	-- ConsRef:gen: EMC2array
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 172 5 EMC2array
	rpop
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen ForkJoinSystem
	-- ConsRef:gen: ForkJoinSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 7
	pushThis 
	invoke 228 7 ForkJoinSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen MonitorSystem
	-- ConsRef:gen: MonitorSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 8
	pushThis 
	invoke 235 8 MonitorSystem
	rpop
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen String
	-- ConsRef:gen: String
	-- ObjectGenerator:gen: super: :singular:staticOff: 10
	pushThis 
	invoke 96 10 String
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L7:
	-- Include:gen: 
 L8:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class workspace 260
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: dummy
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen demo
	-- ConsRef:gen: demo
	-- ObjectGenerator:gen: super: :singular:staticOff: 19
	pushThis 
	invoke 537 19 demo
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L9:
	-- Include:gen: 
 L10:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class False 23
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L11:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := 0:IS-empty: staticOff: 0
	-- Invocation:gen: B := 0
	-- Invocation:loadOrigin: B := 0
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L12:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class True 24
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L13:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := 1:IS-empty: staticOff: 0
	-- Invocation:gen: B := 1
	-- Invocation:loadOrigin: B := 1
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L14:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class core 50
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: dummy
	rtnEventQ 0
	DO:
	mvStack 
 L15:
	-- Include:gen: 
 L16:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Indexed 52
	pushThis 
	storeg 1 range
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: %put V: ? elm %at% inx: ? integer
	-- pattern:gen: %get inx: ? integer -> V: ? integer
	-- pattern:gen: length -> res: ? integer
	-- pattern:gen: asString -> S: ? Object
	rtnEventQ 0
	DO:
	mvStack 
 L17:
	-- Include:gen: 
 L18:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else% 60
	pushThis 
	storeg 1 cond
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: ugly_y
	-- ConsRef:gen: _L
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 61 2 _L
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L19:
	-- Include:gen: 
 L20:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class cycle 62
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L21:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner cycle:IS-empty: staticOff: 0
	-- Invocation:gen: %inner cycle
	-- Invocation:loadOrigin: %inner cycle
	-- Invocation:loadOrigin:scan: %inner cycle
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner cycle
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner cycle
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %restart cycle:IS-empty: staticOff: 0
	-- Invocation:gen: %restart cycle
	-- Invocation:loadOrigin: %restart cycle
	-- Invocation:loadOrigin:scan: %restart cycle
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart cycle
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart cycle
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	jmp L21
 L22:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do% 63
	pushThis 
	storeg 2 last
	pushThis 
	storeg 1 first
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx
	-- pattern:gen: do
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L23:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inx := first:IS-empty: staticOff: 0
	-- Invocation:gen: inx := first
	-- Invocation:loadOrigin: inx := first
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := first
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: first:IS-empty: staticOff: 0
	-- Invocation:gen: first
	-- Invocation:loadOrigin: first
	-- Invocation:loadOrigin:scan: first
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: first
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: first
	pushg 1 first
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 inx
	-- ObjectGenerator:gen: super: do:IS-empty: staticOff: 0
	-- Invocation:gen: do
	-- Invocation:loadOrigin: do
	-- Invocation:loadOrigin:scan: do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: do
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 64 0 do
	rpop
 L24:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class newline 66
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L25:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(10):IS-empty: staticOff: 0
	-- Invocation:gen: put(10)
	-- Invocation:loadOrigin: put(10)
	-- Invocation:loadOrigin:scan: put(10)
	-- Function:pushThis: 
	-- Function:loadOrigin: put(10)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 10:IS-empty: staticOff: 0
	-- Invocation:gen: 10
	-- Invocation:loadOrigin: 10
	-- Invocation:loadOrigin:scan: 10
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 10
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L26:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class putint 67
	pushThis 
	storeg 1 V
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: D
	-- ObjectGenerator:gen: super: Indexed(20,Integer):IS-empty: staticOff: 2
	-- Invocation:gen: Indexed(20,Integer)
	-- Invocation:loadOrigin: Indexed(20,Integer)
	-- Invocation:loadOrigin:scan: Indexed(20,Integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(20,Integer)
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 20:IS-empty: staticOff: 0
	-- Invocation:gen: 20
	-- Invocation:loadOrigin: 20
	-- Invocation:loadOrigin:scan: 20
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 20
	-- ObjectGenerator:gen: super: Integer:IS-empty: staticOff: 0
	-- Invocation:gen: Integer
	-- Invocation:loadOrigin: Integer
	-- Invocation:loadOrigin:scan: Integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: Integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer(W: ? integer)
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	-- VarRef:gen: L
	-- VarRef:gen: isNeg
	-- pattern:gen: doit
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L27:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: isNeg := V < 0:IS-empty: staticOff: 0
	-- Invocation:gen: isNeg := V < 0
	-- Invocation:loadOrigin: isNeg := V < 0
	-- Invocation:loadOrigin:scan: isNeg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: isNeg
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := V < 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: V < 0:IS-empty: staticOff: 0
	-- Invocation:gen: V < 0
	-- Invocation:loadOrigin: V < 0
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: < 0 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: < 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 isNeg
	-- ObjectGenerator:gen: super: %if isNeg %then% V := 0 - V:IS-empty: staticOff: 0
	-- Invocation:gen: %if isNeg %then% V := 0 - V
	-- Invocation:loadOrigin: %if isNeg %then% V := 0 - V
	-- Invocation:loadOrigin:scan: %if isNeg %then% V := 0 - V
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if isNeg %then% V := 0 - V
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if isNeg %then% V := 0 - V
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: isNeg:IS-empty: staticOff: 0
	-- Invocation:gen: isNeg
	-- Invocation:loadOrigin: isNeg
	-- Invocation:loadOrigin:scan: isNeg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: isNeg
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: isNeg
	pushg 3 isNeg
	jmpFalse L29
	-- ObjectGenerator:gen: super: V := 0 - V:IS-empty: staticOff: 0
	-- Invocation:gen: V := 0 - V
	-- Invocation:loadOrigin: V := 0 - V
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 0 - V
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0 - V:IS-empty: staticOff: 0
	-- Invocation:gen: 0 - V
	-- Invocation:loadOrigin: 0 - V
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: - V :E: 0
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Invocation:loadOrigin:scan: - V
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: V:IS-empty: staticOff: 0
	-- Invocation:gen: V
	-- Invocation:loadOrigin: V
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L29:
	-- ObjectGenerator:gen: super: doit:IS-empty: staticOff: 0
	-- Invocation:gen: doit
	-- Invocation:loadOrigin: doit
	-- Invocation:loadOrigin:scan: doit
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: doit
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: doit
	invoke 68 0 doit
	rpop
 L28:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicSystem 72
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: BasicSystem
	rtnEventQ 0
	DO:
	mvStack 
 L30:
	-- Include:gen: 
 L31:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Complex 167
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Complex(re: ? integer,im: ? integer)
	rtnEventQ 0
	DO:
	mvStack 
 L32:
	-- Include:gen: 
 L33:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Containers 73
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: xxx
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen mQueue
	-- ConsRef:gen: mQueue
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 81 3 mQueue
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L34:
	-- Include:gen: 
 L35:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class EMC2array 172
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Array
	-- pattern:gen: Range(low: ? integer,upp: ? integer)
	-- pattern:gen: D1_Array(R: ? Range,ElmType:< Object)
	-- pattern:gen: D2_Array(R1: ? Range,R2: ? Range) -> res: ? D2_array
	rtnEventQ 0
	DO:
	mvStack 
 L36:
	-- Include:gen: 
 L37:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ForkJoinSystem 228
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: ForkJoinSystem
	rtnEventQ 0
	DO:
	mvStack 
 L38:
	-- Include:gen: 
 L39:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class MonitorSystem 235
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: System
	rtnEventQ 0
	DO:
	mvStack 
 L40:
	-- Include:gen: 
 L41:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class String 96
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: String(S: ? String)
	rtnEventQ 0
	DO:
	mvStack 
 L42:
	-- Include:gen: 
 L43:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class demo 537
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: olsen_nils
	-- Module:gen: 
	-- ModuleItem:gen ArrayDemos
	-- ConsRef:gen: ArrayDemos
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 538 2 ArrayDemos
	rpop
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	rtnEventQ 0
	DO:
	mvStack 
 L44:
	-- Include:gen: 
 L45:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 55
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L46:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: res := %get 0
	-- Invocation:loadOrigin: res := %get 0
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %get 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: %get 0
	-- Invocation:loadOrigin: %get 0
	-- Invocation:loadOrigin:scan: %get 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get 0
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get 0
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L47:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class _L 61
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_uglye
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L48:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if cond %then% 
    thenPart
    %leave _L:IS-empty: staticOff: 0
	-- Invocation:gen: %if cond %then% 
    thenPart
    %leave _L
	-- Invocation:loadOrigin: %if cond %then% 
    thenPart
    %leave _L
	-- Invocation:loadOrigin:scan: %if cond %then% 
    thenPart
    %leave _L
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if cond %then% 
    thenPart
    %leave _L
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if cond %then% 
    thenPart
    %leave _L
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: cond:IS-empty: staticOff: 0
	-- Invocation:gen: cond
	-- Invocation:loadOrigin: cond
	-- Invocation:loadOrigin:scan: cond
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cond
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cond
	pushg 1 cond
	jmpFalse L50
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 775 0 #S#775
	rpop
 L50:
	-- ObjectGenerator:gen: super: elsePart:IS-empty: staticOff: 0
	-- Invocation:gen: elsePart
	-- Invocation:loadOrigin: elsePart
	-- Invocation:loadOrigin:scan: elsePart
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elsePart
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: elsePart
	sendv 2 elsePart
	rpop
 L49:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 64
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 65 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L51:
	-- Include:gen: 
 L52:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 68
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 69 2 loop
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L53:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if isNeg %then% put('-'):IS-empty: staticOff: 0
	-- Invocation:gen: %if isNeg %then% put('-')
	-- Invocation:loadOrigin: %if isNeg %then% put('-')
	-- Invocation:loadOrigin:scan: %if isNeg %then% put('-')
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if isNeg %then% put('-')
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if isNeg %then% put('-')
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: isNeg:IS-empty: staticOff: 0
	-- Invocation:gen: isNeg
	-- Invocation:loadOrigin: isNeg
	-- Invocation:loadOrigin:scan: isNeg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: isNeg
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: isNeg
	pushg 3 isNeg
	jmpFalse L55
	-- ObjectGenerator:gen: super: put('-'):IS-empty: staticOff: 0
	-- Invocation:gen: put('-')
	-- Invocation:loadOrigin: put('-')
	-- Invocation:loadOrigin:scan: put('-')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('-')
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: '-':IS-empty: staticOff: 0
	-- Invocation:gen: '-'
	-- Invocation:loadOrigin: '-'
	-- Invocation:loadOrigin:scan: '-'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 45
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L55:
	-- ObjectGenerator:gen: super: %for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i):IS-empty: staticOff: 0
	pushThis 
	invoke 70 0 %for%to%%do%#S#70
	rpop
 L54:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicSystem 119
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Lock
	-- pattern:gen: BasicProcess(id: ? String)
	-- pattern:gen: Scheduler
	-- pattern:gen: Core
	-- ConsRef:gen: noOfCores
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 1
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	pushThis 
	storeg 1 noOfCores
	-- ConsRef:gen: cores
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 136 2 cores
	rpop
	-- ConsRef:gen: P_status
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 138 3 P_status
	rpop
	-- pattern:gen: ProcessQueue
	-- ConsRef:gen: sch
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 141 4 sch
	rpop
	-- ConsRef:gen: SQS
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 149 5 SQS
	rpop
	-- ConsRef:gen: coreLock
	-- ObjectGenerator:gen: super: Lock:IS-empty: staticOff: 6
	-- Invocation:gen: Lock
	-- Invocation:loadOrigin: Lock
	-- Invocation:loadOrigin:scan: Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Lock
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 120 6 Lock
	rpop
	-- ConsRef:gen: console
	-- ObjectGenerator:gen: super: :singular:staticOff: 7
	pushThis 
	invoke 163 7 console
	rpop
	-- pattern:gen: init
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L56:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: init:IS-empty: staticOff: 0
	-- Invocation:gen: init
	-- Invocation:loadOrigin: init
	-- Invocation:loadOrigin:scan: init
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: init
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 166 0 init
	rpop
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: cores.init:IS-empty: staticOff: 0
	-- Invocation:gen: cores.init
	-- Invocation:loadOrigin: cores.init
	-- Invocation:loadOrigin:scan: cores
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cores
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: init :E: cores
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: cores
	rpushg 2 cores
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 137 0 init
	rpop
 L57:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Complex 168
	pushThis 
	storeg 2 im
	pushThis 
	storeg 1 re
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: + C: ? Complex -> res: ? Complex
	-- pattern:gen: - C: ? Complex -> res: ? Complex
	-- pattern:gen: display
	rtnEventQ 0
	DO:
	mvStack 
 L58:
	-- Include:gen: 
 L59:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class mQueue 81
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Queue
	rtnEventQ 0
	DO:
	mvStack 
 L60:
	-- Include:gen: 
 L61:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Array 173
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: pos
	-- VarRef:gen: noof
	-- VarRef:gen: rep
	-- pattern:gen: put(e: ? integer) -> res: ? array
	-- pattern:gen: get -> res: ? integer
	-- pattern:gen: nxt -> res: ? integer
	-- pattern:gen: prv -> res: ? integer
	-- pattern:gen: forAll
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=184
	innerA  2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L62:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 pos
	-- ObjectGenerator:gen: super: %inner Array:IS-empty: staticOff: 0
	-- Invocation:gen: %inner Array
	-- Invocation:loadOrigin: %inner Array
	-- Invocation:loadOrigin:scan: %inner Array
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner Array
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner Array
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  2
	rpopThisObj 
 L63:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Range 186
	pushThis 
	storeg 2 upp
	pushThis 
	storeg 1 low
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: noof
	-- ObjectGenerator:gen: super: (upp - low) + 1:IS-empty: staticOff: 3
	-- Invocation:gen: (upp - low) + 1
	-- Invocation:loadOrigin: (upp - low) + 1
	-- Invocation:loadOrigin:scan: (upp - low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (upp - low)
	-- Invocation:loadOrigin: upp - low
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - low :E: upp
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Invocation:loadOrigin:scan: - low
	-- BE:loadOrigin:E: - low
	-- next not assign: + 1 :E: - low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	pushThis 
	storeg 3 noof
	-- pattern:gen: check(inx: ? integer)
	-- pattern:gen: print
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L64:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if noof < 1 %then% 
    "range error\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: %if noof < 1 %then% 
    "range error\n".print
	-- Invocation:loadOrigin: %if noof < 1 %then% 
    "range error\n".print
	-- Invocation:loadOrigin:scan: %if noof < 1 %then% 
    "range error\n".print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if noof < 1 %then% 
    "range error\n".print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if noof < 1 %then% 
    "range error\n".print
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: noof < 1:IS-empty: staticOff: 0
	-- Invocation:gen: noof < 1
	-- Invocation:loadOrigin: noof < 1
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: < 1 :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: < 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L66
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 817 0 #S#817
	rpop
 L66:
 L65:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class D1_Array 189
	pushThis 
	rstoreg 3 R
	rstore 1 origin
	allocEventQ
	-- super Array
	--  1:184 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=189
	-- Invocation:loadOrigin: Array
	-- Invocation:loadOrigin:scan: Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  173
	-- pattern:gen: putAt(inx: ? integer,exp: ? integer) -> res: ? Array
	-- pattern:gen: getAt(inx: ? integer) -> res: ? integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=192
	innerA  4
	rtnInner
	DO:
	doEventQ
	mvStack 
 L67:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: noof := R.noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof := R.noof
	-- Invocation:loadOrigin: noof := R.noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := R.noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R.noof:IS-empty: staticOff: 0
	-- Invocation:gen: R.noof
	-- Invocation:loadOrigin: R.noof
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: noof :E: R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 noof
	-- ObjectGenerator:gen: super: rep := Indexed(noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: rep := Indexed(noof,integer)
	-- Invocation:loadOrigin: rep := Indexed(noof,integer)
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Indexed(noof,integer)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Indexed(noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: Indexed(noof,integer)
	-- Invocation:loadOrigin: Indexed(noof,integer)
	-- Invocation:loadOrigin:scan: Indexed(noof,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(noof,integer)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- ObjectGenerator:gen: super: integer:IS-empty: staticOff: 0
	-- Invocation:gen: integer
	-- Invocation:loadOrigin: integer
	-- Invocation:loadOrigin:scan: integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer(W: ? integer)
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 rep
	-- ObjectGenerator:gen: super: %inner D1_Array:IS-empty: staticOff: 0
	-- Invocation:gen: %inner D1_Array
	-- Invocation:loadOrigin: %inner D1_Array
	-- Invocation:loadOrigin:scan: %inner D1_Array
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner D1_Array
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner D1_Array
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  4
	rpopThisObj 
 L68:
	rtnInner
	end 1

	class D2_Array 193
	pushThis 
	rstoreg 4 R2
	pushThis 
	rstoreg 3 R1
	rstore 1 origin
	allocEventQ
	-- super Array
	--  1:184 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=193
	-- Invocation:loadOrigin: Array
	-- Invocation:loadOrigin:scan: Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  173
	-- pattern:gen: putAt(inx1: ? integer,inx2: ? integer,exp: ? integer) -> res: ? D2_Array
	-- pattern:gen: getAt(inx1: ? integer,inx2: ? integer) -> exp: ? integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=196
	rtnInner
	DO:
	doEventQ
	mvStack 
 L69:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: rep := indexed(R1.noof * R2.noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: rep := indexed(R1.noof * R2.noof,integer)
	-- Invocation:loadOrigin: rep := indexed(R1.noof * R2.noof,integer)
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := indexed(R1.noof * R2.noof,integer)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: indexed(R1.noof * R2.noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: indexed(R1.noof * R2.noof,integer)
	-- Invocation:loadOrigin: indexed(R1.noof * R2.noof,integer)
	-- Invocation:loadOrigin:scan: indexed(R1.noof * R2.noof,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: indexed(R1.noof * R2.noof,integer)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: R1.noof * R2.noof:IS-empty: staticOff: 0
	-- Invocation:gen: R1.noof * R2.noof
	-- Invocation:loadOrigin: R1.noof * R2.noof
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: noof :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: * R2.noof :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: * R2.noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof:IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof
	-- Invocation:loadOrigin: R2.noof
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- ObjectGenerator:gen: super: integer:IS-empty: staticOff: 0
	-- Invocation:gen: integer
	-- Invocation:loadOrigin: integer
	-- Invocation:loadOrigin:scan: integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer(W: ? integer)
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 rep
	-- ObjectGenerator:gen: super: res := %this D2_Array:IS-empty: staticOff: 0
	-- Invocation:gen: res := %this D2_Array
	-- Invocation:loadOrigin: res := %this D2_Array
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this D2_Array
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this D2_Array:IS-empty: staticOff: 0
	-- Invocation:gen: %this D2_Array
	-- Invocation:loadOrigin: %this D2_Array
	-- Invocation:loadOrigin:scan: %this D2_Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this D2_Array
	-- AdjustOrigin: 0
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this D2_Array
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 res
	-- ObjectGenerator:gen: super: "D2_array:".print:IS-empty: staticOff: 0
	-- Invocation:gen: "D2_array:".print
	-- Invocation:loadOrigin: "D2_array:".print
	-- Invocation:loadOrigin:scan: "D2_array:"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText D2_array:
	-- next not assign: print :E: "D2_array:"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
 L70:
	rtnInner
	end 1

	class ForkJoinSystem 229
	rstore 1 origin
	allocEventQ
	-- super BasicSystem
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=229
	-- Invocation:loadOrigin: BasicSystem
	-- Invocation:loadOrigin:scan: BasicSystem
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: BasicSystem
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  119
	-- pattern:gen: ForkJoin
	innerA  2
	rtnInner
	DO:
	doEventQ
	mvStack 
 L71:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner ForkJoinSystem:IS-empty: staticOff: 0
	-- Invocation:gen: %inner ForkJoinSystem
	-- Invocation:loadOrigin: %inner ForkJoinSystem
	-- Invocation:loadOrigin:scan: %inner ForkJoinSystem
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner ForkJoinSystem
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner ForkJoinSystem
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  2
	rpopThisObj 
 L72:
	rtnInner
	end 1

	class System 236
	rstore 8 origin
	allocEventQ
	-- super BasicSystem
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=236
	-- Invocation:loadOrigin: LIB.BasicSystem.basicSystem
	-- Invocation:loadOrigin:scan: LIB
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: LIB
	-- AdjustOrigin: 8
	rpushg 8 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: BasicSystem :E: LIB
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: LIB
	rpushg 3 LIB
	-- Invocation:loadOrigin:scan: BasicSystem
	-- next not assign: basicSystem :E: BasicSystem
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: BasicSystem
	rpushg 2 BasicSystem
	-- Invocation:loadOrigin:scan: basicSystem
	-- Unary:loadArgs: 
	topSuper  119
	-- pattern:gen: Semaphore
	-- pattern:gen: Process
	-- pattern:gen: Monitor
	innerA  2
	rtnInner
	DO:
	doEventQ
	mvStack 
 L73:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  2
 L74:
	rtnInner
	end 1

	class String 97
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: length -> V: ? integer
	-- pattern:gen: %get inx: ? integer -> ch: ? Char
	-- pattern:gen: + S: ? String -> V: ? String
	-- pattern:gen: asLowerCase -> T: ? String
	-- pattern:gen: scan
	-- pattern:gen: print
	-- pattern:gen: = S: ? string -> B: ? boolean
	-- pattern:gen: <= S: ? string -> B: ? boolean
	rtnEventQ 0
	DO:
	mvStack 
 L75:
	-- Include:gen: 
 L76:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ArrayDemos 538
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: _xxx
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen RangeList
	-- ConsRef:gen: RangeList
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 557 5 RangeList
	rpop
	-- Module:gen: 
	-- Module:gen: 
	rtnEventQ 0
	DO:
	mvStack 
 L77:
	-- Include:gen: 
 L78:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#775 775
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L79:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: thenPart:IS-empty: staticOff: 0
	-- Invocation:gen: thenPart
	-- Invocation:loadOrigin: thenPart
	-- Invocation:loadOrigin:scan: thenPart
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: thenPart
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thenPart
	sendv 1 thenPart
	rpop
	-- ObjectGenerator:gen: super: %leave _L:IS-empty: staticOff: 0
	-- Invocation:gen: %leave _L
	-- Invocation:loadOrigin: %leave _L
	-- Invocation:loadOrigin:scan: %leave _L
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave _L
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave _L
	-- KeyWord:invoke: 
	-- pattern:load: %leave Obj: ? integer
	break 1 49
 L80:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 65
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L81:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if inx <= last %then% 
    body
    inx := inx + 1
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if inx <= last %then% 
    body
    inx := inx + 1
    %restart loop
	-- Invocation:loadOrigin: %if inx <= last %then% 
    body
    inx := inx + 1
    %restart loop
	-- Invocation:loadOrigin:scan: %if inx <= last %then% 
    body
    inx := inx + 1
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if inx <= last %then% 
    body
    inx := inx + 1
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if inx <= last %then% 
    body
    inx := inx + 1
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: inx <= last:IS-empty: staticOff: 0
	-- Invocation:gen: inx <= last
	-- Invocation:loadOrigin: inx <= last
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: <= last :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Invocation:loadOrigin:scan: <= last
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: last:IS-empty: staticOff: 0
	-- Invocation:gen: last
	-- Invocation:loadOrigin: last
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	pushg 2 last
	-- Binary:invoke: 
	-- pattern:load: <= V: ? integer -> B: ? Boolean
	52
	jmpFalse L83
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 776 0 #S#776
	rpop
 L83:
 L82:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 69
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L84:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := L + 1:IS-empty: staticOff: 0
	-- Invocation:gen: L := L + 1
	-- Invocation:loadOrigin: L := L + 1
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := L + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L + 1:IS-empty: staticOff: 0
	-- Invocation:gen: L + 1
	-- Invocation:loadOrigin: L + 1
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 L
	-- ObjectGenerator:gen: super: D.%put V /% 10 %at% L:IS-empty: staticOff: 0
	-- Invocation:gen: D.%put V /% 10 %at% L
	-- Invocation:loadOrigin: D.%put V /% 10 %at% L
	-- Invocation:loadOrigin:scan: D
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: D
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %put V /% 10 %at% L :E: D
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: D
	rpushg 2 D
	-- Invocation:loadOrigin:scan: %put V /% 10 %at% L
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put V /% 10 %at% L
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: V /% 10:IS-empty: staticOff: 0
	-- Invocation:gen: V /% 10
	-- Invocation:loadOrigin: V /% 10
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: /% 10 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: /% 10
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 10:IS-empty: staticOff: 0
	-- Invocation:gen: 10
	-- Invocation:loadOrigin: 10
	-- Invocation:loadOrigin:scan: 10
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 10
	-- Binary:invoke: 
	-- pattern:load: /% V: ? integer -> R: ? integer
	69
	-- name::gen: 
	-- ObjectGenerator:gen: super: L:IS-empty: staticOff: 0
	-- Invocation:gen: L
	-- Invocation:loadOrigin: L
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: V := V // 10:IS-empty: staticOff: 0
	-- Invocation:gen: V := V // 10
	-- Invocation:loadOrigin: V := V // 10
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := V // 10
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: V // 10:IS-empty: staticOff: 0
	-- Invocation:gen: V // 10
	-- Invocation:loadOrigin: V // 10
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: // 10 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: // 10
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 10:IS-empty: staticOff: 0
	-- Invocation:gen: 10
	-- Invocation:loadOrigin: 10
	-- Invocation:loadOrigin:scan: 10
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 10
	-- Binary:invoke: 
	-- pattern:load: // V: ? integer -> B: ? Integer
	68
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
	-- ObjectGenerator:gen: super: %if V > 0 %then% 
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if V > 0 %then% 
    %restart loop
	-- Invocation:loadOrigin: %if V > 0 %then% 
    %restart loop
	-- Invocation:loadOrigin:scan: %if V > 0 %then% 
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if V > 0 %then% 
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if V > 0 %then% 
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: V > 0:IS-empty: staticOff: 0
	-- Invocation:gen: V > 0
	-- Invocation:loadOrigin: V > 0
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: > 0 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: > 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: > V: ? integer -> B: ? Boolean
	gt
	jmpFalse L86
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 777 0 #S#777
	rpop
 L86:
 L85:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#70 70
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i)
	-- Invocation:loadOrigin:scan: %for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i)
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i)
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i)
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: L:IS-empty: staticOff: 0
	-- Invocation:gen: L
	-- Invocation:loadOrigin: L
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L87:
 L88:
	rtnInner
	end 1

	class Lock 120
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: dummy
	-- VarRef:gen: M
	-- pattern:gen: init
	-- pattern:gen: get
	-- pattern:gen: free
	rtnEventQ 0
	DO:
	mvStack 
 L89:
	-- Include:gen: 
 L90:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicProcess 125
	pushThis 
	rstoreg 2 id
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: status
	-- pattern:gen: start
	-- vdtAdd: inx=1 descInx=126
	innerA  2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L91:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (%this BasicProcess).suspend:IS-empty: staticOff: 0
	-- Invocation:gen: (%this BasicProcess).suspend
	-- Invocation:loadOrigin: (%this BasicProcess).suspend
	-- Invocation:loadOrigin:scan: (%this BasicProcess)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (%this BasicProcess)
	-- Invocation:loadOrigin: %this BasicProcess
	-- Invocation:loadOrigin:scan: %this BasicProcess
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this BasicProcess
	-- AdjustOrigin: 0
	-- BE:loadOrigin:E: %this BasicProcess
	-- next not assign: suspend :E: %this BasicProcess
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this BasicProcess
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  2
	-- ObjectGenerator:gen: super: status := P_status.TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: status := P_status.TERMINATED
	-- Invocation:loadOrigin: status := P_status.TERMINATED
	-- Invocation:loadOrigin:scan: status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: status
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := P_status.TERMINATED
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: P_status.TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.TERMINATED
	-- Invocation:loadOrigin: P_status.TERMINATED
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: TERMINATED :E: P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: TERMINATED
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: TERMINATED
	pushg 3 TERMINATED
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
 L92:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Scheduler 127
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: active
	-- VarRef:gen: inScheduler
	-- VarRef:gen: P
	-- pattern:gen: do
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L93:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (%this Scheduler).suspend:IS-empty: staticOff: 0
	-- Invocation:gen: (%this Scheduler).suspend
	-- Invocation:loadOrigin: (%this Scheduler).suspend
	-- Invocation:loadOrigin:scan: (%this Scheduler)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (%this Scheduler)
	-- Invocation:loadOrigin: %this Scheduler
	-- Invocation:loadOrigin:scan: %this Scheduler
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Scheduler
	-- AdjustOrigin: 0
	-- BE:loadOrigin:E: %this Scheduler
	-- next not assign: suspend :E: %this Scheduler
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Scheduler
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: sch.add:IS-empty: staticOff: 0
	-- Invocation:gen: sch.add
	-- Invocation:loadOrigin: sch.add
	-- Invocation:loadOrigin:scan: sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sch
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: add :E: sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: add
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: add
	invoke 143 0 add
	rpop
	-- ObjectGenerator:gen: super: do:IS-empty: staticOff: 0
	-- Invocation:gen: do
	-- Invocation:loadOrigin: do
	-- Invocation:loadOrigin:scan: do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: do
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 128 0 do
	rpop
 L94:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Core 131
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: main
	-- pattern:gen: attach(M: ? Scheduler)
	-- pattern:gen: do
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L95:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (%this Core).suspend:IS-empty: staticOff: 0
	-- Invocation:gen: (%this Core).suspend
	-- Invocation:loadOrigin: (%this Core).suspend
	-- Invocation:loadOrigin:scan: (%this Core)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (%this Core)
	-- Invocation:loadOrigin: %this Core
	-- Invocation:loadOrigin:scan: %this Core
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Core
	-- AdjustOrigin: 0
	-- BE:loadOrigin:E: %this Core
	-- next not assign: suspend :E: %this Core
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Core
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: do:IS-empty: staticOff: 0
	-- Invocation:gen: do
	-- Invocation:loadOrigin: do
	-- Invocation:loadOrigin:scan: do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: do
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 133 0 do
	rpop
 L96:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class cores 136
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: C1
	-- VarRef:gen: C2
	-- VarRef:gen: C3
	-- VarRef:gen: C4
	-- pattern:gen: init
	rtnEventQ 0
	DO:
	mvStack 
 L97:
	-- Include:gen: 
 L98:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class P_status 138
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: ACTIVE
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 1
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	pushThis 
	storeg 1 ACTIVE
	-- ConsRef:gen: WAITING
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 2
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	pushThis 
	storeg 2 WAITING
	-- ConsRef:gen: TERMINATED
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 3
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	pushThis 
	storeg 3 TERMINATED
	rtnEventQ 0
	DO:
	mvStack 
 L99:
	-- Include:gen: 
 L100:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Queue 82
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Element(elm: ? Object) -> res: ? Element
	-- VarRef:gen: head
	-- VarRef:gen: last
	-- pattern:gen: scan
	-- pattern:gen: scanFromLast
	-- pattern:gen: insert(elm: ? Object)
	-- pattern:gen: remove(elm: ? Object)
	-- pattern:gen: removeNext -> elm: ? Object
	-- pattern:gen: isEmpty -> B: ? Boolean
	-- pattern:gen: clear
	rtnEventQ 0
	DO:
	mvStack 
 L101:
	-- Include:gen: 
 L102:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ProcessQueue 139
	rstore 1 origin
	allocEventQ
	-- super Queue
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: LIB.Containers.mQueue.Queue
	-- Invocation:loadOrigin:scan: LIB
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: LIB
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: Containers :E: LIB
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: LIB
	rpushg 3 LIB
	-- Invocation:loadOrigin:scan: Containers
	-- next not assign: mQueue :E: Containers
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: Containers
	rpushg 4 Containers
	-- Invocation:loadOrigin:scan: mQueue
	-- next not assign: Queue :E: mQueue
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: mQueue
	rpushg 3 mQueue
	-- Invocation:loadOrigin:scan: Queue
	-- Unary:loadArgs: 
	topSuper  82
	-- pattern:gen: display
	rtnInner
	DO:
	mvStack 
 L103:
	-- Include:gen: 
 L104:
	rtnInner
	end 1

	class sch 141
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: L
	-- ObjectGenerator:gen: super: Lock:IS-empty: staticOff: 2
	-- Invocation:gen: Lock
	-- Invocation:loadOrigin: Lock
	-- Invocation:loadOrigin:scan: Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Lock
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 120 2 Lock
	rpop
	-- VarRef:gen: M
	-- pattern:gen: entry
	-- pattern:gen: add
	-- pattern:gen: dcr
	-- pattern:gen: running -> B: ? Boolean
	rtnEventQ 0
	DO:
	mvStack 
 L105:
	-- Include:gen: 
 L106:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class SQS 149
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: Q
	-- ObjectGenerator:gen: super: ProcessQueue:IS-empty: staticOff: 2
	-- Invocation:gen: ProcessQueue
	-- Invocation:loadOrigin: ProcessQueue
	-- Invocation:loadOrigin:scan: ProcessQueue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ProcessQueue
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 139 2 ProcessQueue
	rpop
	-- ConsRef:gen: L
	-- ObjectGenerator:gen: super: Lock:IS-empty: staticOff: 3
	-- Invocation:gen: Lock
	-- Invocation:loadOrigin: Lock
	-- Invocation:loadOrigin:scan: Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Lock
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 120 3 Lock
	rpop
	-- VarRef:gen: V
	-- VarRef:gen: W
	-- pattern:gen: entry
	-- pattern:gen: init
	-- pattern:gen: insert(P: ? BasicProcess)
	-- pattern:gen: removeNext -> P: ? BasicProcess
	-- pattern:gen: remove(P: ? BasicProcess)
	-- pattern:gen: isEmpty -> B: ? Boolean
	-- pattern:gen: display
	-- pattern:gen: addWaiting
	-- pattern:gen: dcrWaiting
	-- pattern:gen: hasWaiting -> B: ? boolean
	rtnEventQ 0
	DO:
	mvStack 
 L107:
	-- Include:gen: 
 L108:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class console 163
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: L
	-- ObjectGenerator:gen: super: Lock:IS-empty: staticOff: 2
	-- Invocation:gen: Lock
	-- Invocation:loadOrigin: Lock
	-- Invocation:loadOrigin:scan: Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Lock
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 120 2 Lock
	rpop
	-- VarRef:gen: V
	-- pattern:gen: init
	-- pattern:gen: display
	rtnEventQ 0
	DO:
	mvStack 
 L109:
	-- Include:gen: 
 L110:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 166
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L111:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: SQS.init:IS-empty: staticOff: 0
	-- Invocation:gen: SQS.init
	-- Invocation:loadOrigin: SQS.init
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: init :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 151 0 init
	rpop
 L112:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class + 169
	pushThis 
	rstoreg 2 C
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L113:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := Complex(re + C.re,im + C.im):IS-empty: staticOff: 0
	-- Invocation:gen: res := Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin: res := Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Complex(re + C.re,im + C.im)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Complex(re + C.re,im + C.im):IS-empty: staticOff: 0
	-- Invocation:gen: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin:scan: Complex(re + C.re,im + C.im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Complex(re + C.re,im + C.im)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: re + C.re:IS-empty: staticOff: 0
	-- Invocation:gen: re + C.re
	-- Invocation:loadOrigin: re + C.re
	-- Invocation:loadOrigin:scan: re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + C.re :E: re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Invocation:loadOrigin:scan: + C.re
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: C.re:IS-empty: staticOff: 0
	-- Invocation:gen: C.re
	-- Invocation:loadOrigin: C.re
	-- Invocation:loadOrigin:scan: C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: re :E: C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- ObjectGenerator:gen: super: im + C.im:IS-empty: staticOff: 0
	-- Invocation:gen: im + C.im
	-- Invocation:loadOrigin: im + C.im
	-- Invocation:loadOrigin:scan: im
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: im
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + C.im :E: im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Invocation:loadOrigin:scan: + C.im
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: C.im:IS-empty: staticOff: 0
	-- Invocation:gen: C.im
	-- Invocation:loadOrigin: C.im
	-- Invocation:loadOrigin:scan: C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: im :E: C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: Complex(re: ? integer,im: ? integer)
	invoke 168 0 Complex
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 res
 L114:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 3 res
	rtn(D)
	end 1

	class - 170
	pushThis 
	rstoreg 2 C
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L115:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := Complex(re + C.re,im + C.im):IS-empty: staticOff: 0
	-- Invocation:gen: res := Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin: res := Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Complex(re + C.re,im + C.im)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Complex(re + C.re,im + C.im):IS-empty: staticOff: 0
	-- Invocation:gen: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin:scan: Complex(re + C.re,im + C.im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Complex(re + C.re,im + C.im)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: re + C.re:IS-empty: staticOff: 0
	-- Invocation:gen: re + C.re
	-- Invocation:loadOrigin: re + C.re
	-- Invocation:loadOrigin:scan: re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + C.re :E: re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Invocation:loadOrigin:scan: + C.re
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: C.re:IS-empty: staticOff: 0
	-- Invocation:gen: C.re
	-- Invocation:loadOrigin: C.re
	-- Invocation:loadOrigin:scan: C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: re :E: C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- ObjectGenerator:gen: super: im + C.im:IS-empty: staticOff: 0
	-- Invocation:gen: im + C.im
	-- Invocation:loadOrigin: im + C.im
	-- Invocation:loadOrigin:scan: im
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: im
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + C.im :E: im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Invocation:loadOrigin:scan: + C.im
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: C.im:IS-empty: staticOff: 0
	-- Invocation:gen: C.im
	-- Invocation:loadOrigin: C.im
	-- Invocation:loadOrigin:scan: C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: im :E: C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: Complex(re: ? integer,im: ? integer)
	invoke 168 0 Complex
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 res
 L116:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 3 res
	rtn(D)
	end 1

	class display 171
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L117:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('C'):IS-empty: staticOff: 0
	-- Invocation:gen: put('C')
	-- Invocation:loadOrigin: put('C')
	-- Invocation:loadOrigin:scan: put('C')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('C')
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 'C':IS-empty: staticOff: 0
	-- Invocation:gen: 'C'
	-- Invocation:loadOrigin: 'C'
	-- Invocation:loadOrigin:scan: 'C'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 67
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: putint(re):IS-empty: staticOff: 0
	-- Invocation:gen: putint(re)
	-- Invocation:loadOrigin: putint(re)
	-- Invocation:loadOrigin:scan: putint(re)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(re)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: re:IS-empty: staticOff: 0
	-- Invocation:gen: re
	-- Invocation:loadOrigin: re
	-- Invocation:loadOrigin:scan: re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(','):IS-empty: staticOff: 0
	-- Invocation:gen: put(',')
	-- Invocation:loadOrigin: put(',')
	-- Invocation:loadOrigin:scan: put(',')
	-- Function:pushThis: 
	-- Function:loadOrigin: put(',')
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: ',':IS-empty: staticOff: 0
	-- Invocation:gen: ','
	-- Invocation:loadOrigin: ','
	-- Invocation:loadOrigin:scan: ','
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 44
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: putint(im):IS-empty: staticOff: 0
	-- Invocation:gen: putint(im)
	-- Invocation:loadOrigin: putint(im)
	-- Invocation:loadOrigin:scan: putint(im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(im)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: im:IS-empty: staticOff: 0
	-- Invocation:gen: im
	-- Invocation:loadOrigin: im
	-- Invocation:loadOrigin:scan: im
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: im
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(10):IS-empty: staticOff: 0
	-- Invocation:gen: put(10)
	-- Invocation:loadOrigin: put(10)
	-- Invocation:loadOrigin:scan: put(10)
	-- Function:pushThis: 
	-- Function:loadOrigin: put(10)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 10:IS-empty: staticOff: 0
	-- Invocation:gen: 10
	-- Invocation:loadOrigin: 10
	-- Invocation:loadOrigin:scan: 10
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 10
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L118:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class put 174
	pushThis 
	storeg 1 e
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L119:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: rep.%put e %at% pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put e %at% pos
	-- Invocation:loadOrigin: rep.%put e %at% pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %put e %at% pos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %put e %at% pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put e %at% pos
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: e:IS-empty: staticOff: 0
	-- Invocation:gen: e
	-- Invocation:loadOrigin: e
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 175 0 %if%then%%else%#S#175
	rpop
	-- ObjectGenerator:gen: super: res := %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: res := %this Array
	-- Invocation:loadOrigin: res := %this Array
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this Array
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: %this Array
	-- Invocation:loadOrigin: %this Array
	-- Invocation:loadOrigin:scan: %this Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Array
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Array
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 res
 L120:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class get 176
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L121:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos
	-- Invocation:loadOrigin: res := rep.%get pos
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := rep.%get pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos
	-- Invocation:loadOrigin: rep.%get pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %get pos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
	-- ObjectGenerator:gen: super: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 177 0 %if%then%%else%#S#177
	rpop
 L122:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class nxt 178
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L123:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 179 0 %if%then%%else%#S#179
	rpop
 L124:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class prv 180
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L125:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos - 1:IS-empty: staticOff: 0
	pushThis 
	invoke 181 0 %if%then%%else%#S#181
	rpop
 L126:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class forAll 182
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	-- pattern:gen: loop
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L127:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 pos
	-- ObjectGenerator:gen: super: loop:IS-empty: staticOff: 0
	-- Invocation:gen: loop
	-- Invocation:loadOrigin: loop
	-- Invocation:loadOrigin:scan: loop
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: loop
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 183 0 loop
	rpop
 L128:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 184
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L129:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "Array(".print:IS-empty: staticOff: 0
	-- Invocation:gen: "Array(".print
	-- Invocation:loadOrigin: "Array(".print
	-- Invocation:loadOrigin:scan: "Array("
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Array(
	-- next not assign: print :E: "Array("
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: %inner print:IS-empty: staticOff: 0
	-- Invocation:gen: %inner print
	-- Invocation:loadOrigin: %inner print
	-- Invocation:loadOrigin:scan: %inner print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner print
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: "): ".print:IS-empty: staticOff: 0
	-- Invocation:gen: "): ".print
	-- Invocation:loadOrigin: "): ".print
	-- Invocation:loadOrigin:scan: "): "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText ): 
	-- next not assign: print :E: "): "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print:IS-empty: staticOff: 0
	pushThis 
	invoke 185 0 %for%to%%do%#S#185
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
 L130:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class check 187
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L131:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print:IS-empty: staticOff: 0
	-- Invocation:gen: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- Invocation:loadOrigin: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- Invocation:loadOrigin:scan: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: (inx < low) || (inx > upp):IS-empty: staticOff: 0
	-- Invocation:gen: (inx < low) || (inx > upp)
	-- Invocation:loadOrigin: (inx < low) || (inx > upp)
	-- Invocation:loadOrigin:scan: (inx < low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx < low)
	-- Invocation:loadOrigin: inx < low
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: < low :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: < low
	-- BE:loadOrigin:E: < low
	-- next not assign: || (inx > upp) :E: < low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	-- Invocation:loadOrigin:scan: || (inx > upp)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx > upp):IS-empty: staticOff: 0
	-- Invocation:gen: (inx > upp)
	-- Invocation:loadOrigin: (inx > upp)
	-- Invocation:loadOrigin:scan: (inx > upp)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx > upp)
	-- Invocation:loadOrigin: inx > upp
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: > upp :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: > upp
	-- BE:loadOrigin:E: > upp
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: upp:IS-empty: staticOff: 0
	-- Invocation:gen: upp
	-- Invocation:loadOrigin: upp
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Binary:invoke: 
	-- pattern:load: > V: ? integer -> B: ? Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: || B: ? Boolean -> R: ? Boolean
	63
	jmpFalse L133
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 816 0 #S#816
	rpop
 L133:
 L132:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 188
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L134:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: putint(low):IS-empty: staticOff: 0
	-- Invocation:gen: putint(low)
	-- Invocation:loadOrigin: putint(low)
	-- Invocation:loadOrigin:scan: putint(low)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(low)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(':'):IS-empty: staticOff: 0
	-- Invocation:gen: put(':')
	-- Invocation:loadOrigin: put(':')
	-- Invocation:loadOrigin:scan: put(':')
	-- Function:pushThis: 
	-- Function:loadOrigin: put(':')
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: ':':IS-empty: staticOff: 0
	-- Invocation:gen: ':'
	-- Invocation:loadOrigin: ':'
	-- Invocation:loadOrigin:scan: ':'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 58
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: putint(upp):IS-empty: staticOff: 0
	-- Invocation:gen: putint(upp)
	-- Invocation:loadOrigin: putint(upp)
	-- Invocation:loadOrigin:scan: putint(upp)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(upp)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: upp:IS-empty: staticOff: 0
	-- Invocation:gen: upp
	-- Invocation:loadOrigin: upp
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
 L135:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#817 817
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L136:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "range error\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "range error\n".print
	-- Invocation:loadOrigin: "range error\n".print
	-- Invocation:loadOrigin:scan: "range error\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText range error\n
	-- next not assign: print :E: "range error\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
 L137:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class putAt 190
	pushThis 
	storeg 2 exp
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L138:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R.check(inx):IS-empty: staticOff: 0
	-- Invocation:gen: R.check(inx)
	-- Invocation:loadOrigin: R.check(inx)
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: check(inx) :E: R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: check(inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 187 0 check
	rpop
	-- ObjectGenerator:gen: super: rep.%put exp %at% (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put exp %at% (inx - R.low) + 1
	-- Invocation:loadOrigin: rep.%put exp %at% (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %put exp %at% (inx - R.low) + 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %put exp %at% (inx - R.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put exp %at% (inx - R.low) + 1
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: exp:IS-empty: staticOff: 0
	-- Invocation:gen: exp
	-- Invocation:loadOrigin: exp
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 2 exp
	-- name::gen: 
	-- ObjectGenerator:gen: super: (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: (inx - R.low) + 1
	-- Invocation:loadOrigin: (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: (inx - R.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx - R.low)
	-- Invocation:loadOrigin: inx - R.low
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - R.low :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: - R.low
	-- BE:loadOrigin:E: - R.low
	-- next not assign: + 1 :E: - R.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R.low:IS-empty: staticOff: 0
	-- Invocation:gen: R.low
	-- Invocation:loadOrigin: R.low
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: low :E: R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: res := %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: res := %this Array
	-- Invocation:loadOrigin: res := %this Array
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this Array
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: %this Array
	-- Invocation:loadOrigin: %this Array
	-- Invocation:loadOrigin:scan: %this Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Array
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Array
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 res
 L139:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class getAt 191
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L140:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R.check(inx):IS-empty: staticOff: 0
	-- Invocation:gen: R.check(inx)
	-- Invocation:loadOrigin: R.check(inx)
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: check(inx) :E: R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: check(inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 187 0 check
	rpop
	-- ObjectGenerator:gen: super: res := rep.%get (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin: res := rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := rep.%get (inx - R.low) + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin: rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %get (inx - R.low) + 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get (inx - R.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get (inx - R.low) + 1
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: (inx - R.low) + 1
	-- Invocation:loadOrigin: (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: (inx - R.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx - R.low)
	-- Invocation:loadOrigin: inx - R.low
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - R.low :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: - R.low
	-- BE:loadOrigin:E: - R.low
	-- next not assign: + 1 :E: - R.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R.low:IS-empty: staticOff: 0
	-- Invocation:gen: R.low
	-- Invocation:loadOrigin: R.low
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: low :E: R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 res
 L141:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 2 res
	rtn(D)
	end 1

	class print 192
	rstore 2 origin
	allocEventQ
	-- super print
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=192
	pushThis 
	rpushg 2 iOrigin
	topSuper  184
	rtnInner
	DO:
	doEventQ
	mvStack 
 L142:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R.print:IS-empty: staticOff: 0
	-- Invocation:gen: R.print
	-- Invocation:loadOrigin: R.print
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: print :E: R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 188 0 print
	rpop
 L143:
	rtnInner
	end 1

	class putAt 194
	pushThis 
	storeg 3 exp
	pushThis 
	storeg 2 inx2
	pushThis 
	storeg 1 inx1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: repPos
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L144:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1.check(inx1):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx1)
	-- Invocation:loadOrigin: R1.check(inx1)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx1:IS-empty: staticOff: 0
	-- Invocation:gen: inx1
	-- Invocation:loadOrigin: inx1
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 187 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx2:IS-empty: staticOff: 0
	-- Invocation:gen: inx2
	-- Invocation:loadOrigin: inx2
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 187 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (inx1 - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx1 - R1.low)
	-- Invocation:loadOrigin: inx1 - R1.low
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - R1.low :E: inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (1 + inx2 - R2.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: 1 + inx2 - R2.low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: + inx2 - R2.low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: + inx2 - R2.low
	-- BE:loadOrigin:E: + inx2 - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx2 - R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 - R2.low
	-- Invocation:loadOrigin: inx2 - R2.low
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - R2.low :E: inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 4 repPos
	-- ObjectGenerator:gen: super: rep.%put exp %at% repPos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put exp %at% repPos
	-- Invocation:loadOrigin: rep.%put exp %at% repPos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %put exp %at% repPos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %put exp %at% repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put exp %at% repPos
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: exp:IS-empty: staticOff: 0
	-- Invocation:gen: exp
	-- Invocation:loadOrigin: exp
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 3 exp
	-- name::gen: 
	-- ObjectGenerator:gen: super: repPos:IS-empty: staticOff: 0
	-- Invocation:gen: repPos
	-- Invocation:loadOrigin: repPos
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 4 repPos
	xstoreg 1 inx
 L145:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class getAt 195
	pushThis 
	storeg 2 inx2
	pushThis 
	storeg 1 inx1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: repPos
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L146:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1.check(inx1):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx1)
	-- Invocation:loadOrigin: R1.check(inx1)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx1:IS-empty: staticOff: 0
	-- Invocation:gen: inx1
	-- Invocation:loadOrigin: inx1
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 187 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx2:IS-empty: staticOff: 0
	-- Invocation:gen: inx2
	-- Invocation:loadOrigin: inx2
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 187 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (inx1 - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx1 - R1.low)
	-- Invocation:loadOrigin: inx1 - R1.low
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - R1.low :E: inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (1 + inx2 - R2.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: 1 + inx2 - R2.low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: + inx2 - R2.low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: + inx2 - R2.low
	-- BE:loadOrigin:E: + inx2 - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx2 - R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 - R2.low
	-- Invocation:loadOrigin: inx2 - R2.low
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - R2.low :E: inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 4 repPos
	-- ObjectGenerator:gen: super: exp := rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: exp := rep.%get repPos
	-- Invocation:loadOrigin: exp := rep.%get repPos
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := rep.%get repPos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get repPos
	-- Invocation:loadOrigin: rep.%get repPos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %get repPos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get repPos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: repPos:IS-empty: staticOff: 0
	-- Invocation:gen: repPos
	-- Invocation:loadOrigin: repPos
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 4 repPos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 exp
 L147:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: exp
	pushg 3 exp
	rtn(D)
	end 1

	class print 196
	rstore 2 origin
	allocEventQ
	-- super print
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=196
	pushThis 
	rpushg 2 iOrigin
	topSuper  184
	rtnInner
	DO:
	doEventQ
	mvStack 
 L148:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1.print:IS-empty: staticOff: 0
	-- Invocation:gen: R1.print
	-- Invocation:loadOrigin: R1.print
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: print :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 188 0 print
	rpop
	-- ObjectGenerator:gen: super: ",".print:IS-empty: staticOff: 0
	-- Invocation:gen: ",".print
	-- Invocation:loadOrigin: ",".print
	-- Invocation:loadOrigin:scan: ","
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText ,
	-- next not assign: print :E: ","
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: R2.print:IS-empty: staticOff: 0
	-- Invocation:gen: R2.print
	-- Invocation:loadOrigin: R2.print
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: print :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 188 0 print
	rpop
 L149:
	rtnInner
	end 1

	class ForkJoin 230
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: Q
	-- ObjectGenerator:gen: super: ProcessQueue:IS-empty: staticOff: 2
	-- Invocation:gen: ProcessQueue
	-- Invocation:loadOrigin: ProcessQueue
	-- Invocation:loadOrigin:scan: ProcessQueue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ProcessQueue
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 139 2 ProcessQueue
	rpop
	-- ConsRef:gen: M
	-- ObjectGenerator:gen: super: Lock:IS-empty: staticOff: 3
	-- Invocation:gen: Lock
	-- Invocation:loadOrigin: Lock
	-- Invocation:loadOrigin:scan: Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Lock
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 120 3 Lock
	rpop
	-- pattern:gen: run(P: ? BasicProcess)
	-- pattern:gen: AwaitTermination
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L150:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M.init:IS-empty: staticOff: 0
	-- Invocation:gen: M.init
	-- Invocation:loadOrigin: M.init
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: init :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 121 0 init
	rpop
	-- ObjectGenerator:gen: super: %inner ForkJoin:IS-empty: staticOff: 0
	-- Invocation:gen: %inner ForkJoin
	-- Invocation:loadOrigin: %inner ForkJoin
	-- Invocation:loadOrigin:scan: %inner ForkJoin
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner ForkJoin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner ForkJoin
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: AwaitTermination:IS-empty: staticOff: 0
	-- Invocation:gen: AwaitTermination
	-- Invocation:loadOrigin: AwaitTermination
	-- Invocation:loadOrigin:scan: AwaitTermination
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: AwaitTermination
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: AwaitTermination
	invoke 232 0 AwaitTermination
	rpop
 L151:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Semaphore 237
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: cnt
	-- ConsRef:gen: M
	-- ObjectGenerator:gen: super: Lock:IS-empty: staticOff: 2
	-- Invocation:gen: Lock
	-- Invocation:loadOrigin: Lock
	-- Invocation:loadOrigin:scan: Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Lock
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 120 2 Lock
	rpop
	-- ConsRef:gen: Q
	-- ObjectGenerator:gen: super: ProcessQueue:IS-empty: staticOff: 3
	-- Invocation:gen: ProcessQueue
	-- Invocation:loadOrigin: ProcessQueue
	-- Invocation:loadOrigin:scan: ProcessQueue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ProcessQueue
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 139 3 ProcessQueue
	rpop
	-- pattern:gen: init
	-- pattern:gen: wait
	-- pattern:gen: signal
	rtnEventQ 0
	DO:
	mvStack 
 L152:
	-- Include:gen: 
 L153:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Process 243
	rstore 1 origin
	allocEventQ
	-- super BasicProcess
	--  1:126 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=243
	-- Invocation:loadOrigin: BasicProcess
	-- Invocation:loadOrigin:scan: BasicProcess
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: BasicProcess
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  125
	-- pattern:gen: start
	-- vdtAdd: inx=1 descInx=244
	innerA  3
	rtnInner
	DO:
	doEventQ
	mvStack 
 L154:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  3
 L155:
	rtnInner
	end 1

	class Monitor 245
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: mutex
	-- ObjectGenerator:gen: super: Semaphore:IS-empty: staticOff: 2
	-- Invocation:gen: Semaphore
	-- Invocation:loadOrigin: Semaphore
	-- Invocation:loadOrigin:scan: Semaphore
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Semaphore
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Semaphore
	invoke 237 2 Semaphore
	rpop
	-- VarRef:gen: V
	-- pattern:gen: init
	-- pattern:gen: entry
	-- pattern:gen: wait
	rtnEventQ 0
	DO:
	mvStack 
 L156:
	-- Include:gen: 
 L157:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 98
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L158:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: V := %get 0
	-- Invocation:loadOrigin: V := %get 0
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %get 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: %get 0
	-- Invocation:loadOrigin: %get 0
	-- Invocation:loadOrigin:scan: %get 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get 0
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get 0
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L159:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 1 V
	rtn(D)
	end 1

	class + 100
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: L
	-- pattern:gen: doplus
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L160:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := Length:IS-empty: staticOff: 0
	-- Invocation:gen: L := Length
	-- Invocation:loadOrigin: L := Length
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Length:IS-empty: staticOff: 0
	-- Invocation:gen: Length
	-- Invocation:loadOrigin: Length
	-- Invocation:loadOrigin:scan: Length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Length
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
	-- ObjectGenerator:gen: super: doplus:IS-empty: staticOff: 0
	-- Invocation:gen: doplus
	-- Invocation:loadOrigin: doplus
	-- Invocation:loadOrigin:scan: doplus
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: doplus
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: doplus
	invoke 101 0 doplus
	rpop
 L161:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	rpushg 3 V
	rtn(D)
	end 1

	class asLowerCase 104
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 0
	DO:
	mvStack 
 L162:
	-- Include:gen: 
 L163:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: T
	rpushg 2 T
	rtn(D)
	end 1

	class scan 105
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L164:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    current := %get inx
    %inner scan:IS-empty: staticOff: 0
	pushThis 
	invoke 106 0 %for%to%%do%#S#106
	rpop
 L165:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 107
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L166:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    put(%get inx):IS-empty: staticOff: 0
	pushThis 
	invoke 108 0 %for%to%%do%#S#108
	rpop
 L167:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class = 109
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 110 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L168:
	-- Include:gen: 
 L169:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class <= 112
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 113 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L170:
	-- Include:gen: 
 L171:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class RangeList 557
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: int2int(e: ? integer) -> val: ? integer
	-- pattern:gen: intint2int(i1: ? integer,i2: ? integer) -> val: ? integer
	-- pattern:gen: IntList(head: ? integer,tail: ? IntList)
	-- pattern:gen: Range(low: ? integer,upp: ? integer)
	-- pattern:gen: RangeList(head: ? Range,tail: ? RangeList)
	-- VarRef:gen: rl
	-- VarRef:gen: r
	-- VarRef:gen: r1
	-- VarRef:gen: r2
	-- pattern:gen: Array(ndim: ? integer,ranges: ? RangeList)
	-- VarRef:gen: a
	-- VarRef:gen: i
	-- VarRef:gen: indices
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L172:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := Range(0,0):IS-empty: staticOff: 0
	-- Invocation:gen: r := Range(0,0)
	-- Invocation:loadOrigin: r := Range(0,0)
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Range(0,0)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Range(0,0):IS-empty: staticOff: 0
	-- Invocation:gen: Range(0,0)
	-- Invocation:loadOrigin: Range(0,0)
	-- Invocation:loadOrigin:scan: Range(0,0)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Range(0,0)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Function:invoke: 
	-- pattern:load: Range(low: ? integer,upp: ? integer)
	invoke 567 0 Range
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 r
	-- ObjectGenerator:gen: super: r1 := Range(2,3):IS-empty: staticOff: 0
	-- Invocation:gen: r1 := Range(2,3)
	-- Invocation:loadOrigin: r1 := Range(2,3)
	-- Invocation:loadOrigin:scan: r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Range(2,3)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Range(2,3):IS-empty: staticOff: 0
	-- Invocation:gen: Range(2,3)
	-- Invocation:loadOrigin: Range(2,3)
	-- Invocation:loadOrigin:scan: Range(2,3)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Range(2,3)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- Function:invoke: 
	-- pattern:load: Range(low: ? integer,upp: ? integer)
	invoke 567 0 Range
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 r1
	-- ObjectGenerator:gen: super: r2 := Range(4,5):IS-empty: staticOff: 0
	-- Invocation:gen: r2 := Range(4,5)
	-- Invocation:loadOrigin: r2 := Range(4,5)
	-- Invocation:loadOrigin:scan: r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r2
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Range(4,5)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Range(4,5):IS-empty: staticOff: 0
	-- Invocation:gen: Range(4,5)
	-- Invocation:loadOrigin: Range(4,5)
	-- Invocation:loadOrigin:scan: Range(4,5)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Range(4,5)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 0
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	-- ObjectGenerator:gen: super: 5:IS-empty: staticOff: 0
	-- Invocation:gen: 5
	-- Invocation:loadOrigin: 5
	-- Invocation:loadOrigin:scan: 5
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 5
	-- Function:invoke: 
	-- pattern:load: Range(low: ? integer,upp: ? integer)
	invoke 567 0 Range
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 r2
	-- ObjectGenerator:gen: super: putint(r1.low):IS-empty: staticOff: 0
	-- Invocation:gen: putint(r1.low)
	-- Invocation:loadOrigin: putint(r1.low)
	-- Invocation:loadOrigin:scan: putint(r1.low)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(r1.low)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r1.low:IS-empty: staticOff: 0
	-- Invocation:gen: r1.low
	-- Invocation:loadOrigin: r1.low
	-- Invocation:loadOrigin:scan: r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: low :E: r1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 4 r1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: putint(r1.upp):IS-empty: staticOff: 0
	-- Invocation:gen: putint(r1.upp)
	-- Invocation:loadOrigin: putint(r1.upp)
	-- Invocation:loadOrigin:scan: putint(r1.upp)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(r1.upp)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r1.upp:IS-empty: staticOff: 0
	-- Invocation:gen: r1.upp
	-- Invocation:loadOrigin: r1.upp
	-- Invocation:loadOrigin:scan: r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: upp :E: r1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 4 r1
	-- Invocation:loadOrigin:scan: upp
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
	-- ObjectGenerator:gen: super: putint(r2.low):IS-empty: staticOff: 0
	-- Invocation:gen: putint(r2.low)
	-- Invocation:loadOrigin: putint(r2.low)
	-- Invocation:loadOrigin:scan: putint(r2.low)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(r2.low)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r2.low:IS-empty: staticOff: 0
	-- Invocation:gen: r2.low
	-- Invocation:loadOrigin: r2.low
	-- Invocation:loadOrigin:scan: r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: low :E: r2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 5 r2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: putint(r2.upp):IS-empty: staticOff: 0
	-- Invocation:gen: putint(r2.upp)
	-- Invocation:loadOrigin: putint(r2.upp)
	-- Invocation:loadOrigin:scan: putint(r2.upp)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(r2.upp)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r2.upp:IS-empty: staticOff: 0
	-- Invocation:gen: r2.upp
	-- Invocation:loadOrigin: r2.upp
	-- Invocation:loadOrigin:scan: r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: upp :E: r2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 5 r2
	-- Invocation:loadOrigin:scan: upp
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
	-- ObjectGenerator:gen: super: rl := RangeList(r1,RangeList(r2,none)):IS-empty: staticOff: 0
	-- Invocation:gen: rl := RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin: rl := RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin:scan: rl
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rl
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := RangeList(r1,RangeList(r2,none))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: RangeList(r1,RangeList(r2,none)):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin: RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin:scan: RangeList(r1,RangeList(r2,none))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(r1,RangeList(r2,none))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r1:IS-empty: staticOff: 0
	-- Invocation:gen: r1
	-- Invocation:loadOrigin: r1
	-- Invocation:loadOrigin:scan: r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 4 r1
	-- ObjectGenerator:gen: super: RangeList(r2,none):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(r2,none)
	-- Invocation:loadOrigin: RangeList(r2,none)
	-- Invocation:loadOrigin:scan: RangeList(r2,none)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(r2,none)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r2:IS-empty: staticOff: 0
	-- Invocation:gen: r2
	-- Invocation:loadOrigin: r2
	-- Invocation:loadOrigin:scan: r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 5 r2
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 rl
	-- ObjectGenerator:gen: super: a := Array(2,RangeList(r1,RangeList(r2,none))):IS-empty: staticOff: 0
	-- Invocation:gen: a := Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin: a := Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Array(2,RangeList(r1,RangeList(r2,none)))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Array(2,RangeList(r1,RangeList(r2,none))):IS-empty: staticOff: 0
	-- Invocation:gen: Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin: Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin:scan: Array(2,RangeList(r1,RangeList(r2,none)))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Array(2,RangeList(r1,RangeList(r2,none)))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: RangeList(r1,RangeList(r2,none)):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin: RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin:scan: RangeList(r1,RangeList(r2,none))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(r1,RangeList(r2,none))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r1:IS-empty: staticOff: 0
	-- Invocation:gen: r1
	-- Invocation:loadOrigin: r1
	-- Invocation:loadOrigin:scan: r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 4 r1
	-- ObjectGenerator:gen: super: RangeList(r2,none):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(r2,none)
	-- Invocation:loadOrigin: RangeList(r2,none)
	-- Invocation:loadOrigin:scan: RangeList(r2,none)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(r2,none)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r2:IS-empty: staticOff: 0
	-- Invocation:gen: r2
	-- Invocation:loadOrigin: r2
	-- Invocation:loadOrigin:scan: r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 5 r2
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Function:invoke: 
	-- pattern:load: Array(ndim: ? integer,ranges: ? RangeList)
	invoke 578 0 Array
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 6 a
	-- ObjectGenerator:gen: super: a := Array(2,RangeList(r1,RangeList(r2,none))):IS-empty: staticOff: 0
	-- Invocation:gen: a := Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin: a := Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Array(2,RangeList(r1,RangeList(r2,none)))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Array(2,RangeList(r1,RangeList(r2,none))):IS-empty: staticOff: 0
	-- Invocation:gen: Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin: Array(2,RangeList(r1,RangeList(r2,none)))
	-- Invocation:loadOrigin:scan: Array(2,RangeList(r1,RangeList(r2,none)))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Array(2,RangeList(r1,RangeList(r2,none)))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: RangeList(r1,RangeList(r2,none)):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin: RangeList(r1,RangeList(r2,none))
	-- Invocation:loadOrigin:scan: RangeList(r1,RangeList(r2,none))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(r1,RangeList(r2,none))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r1:IS-empty: staticOff: 0
	-- Invocation:gen: r1
	-- Invocation:loadOrigin: r1
	-- Invocation:loadOrigin:scan: r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 4 r1
	-- ObjectGenerator:gen: super: RangeList(r2,none):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(r2,none)
	-- Invocation:loadOrigin: RangeList(r2,none)
	-- Invocation:loadOrigin:scan: RangeList(r2,none)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(r2,none)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: r2:IS-empty: staticOff: 0
	-- Invocation:gen: r2
	-- Invocation:loadOrigin: r2
	-- Invocation:loadOrigin:scan: r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 5 r2
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Function:invoke: 
	-- pattern:load: Array(ndim: ? integer,ranges: ? RangeList)
	invoke 578 0 Array
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 6 a
	-- ObjectGenerator:gen: super: a := Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none))):IS-empty: staticOff: 0
	-- Invocation:gen: a := Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none)))
	-- Invocation:loadOrigin: a := Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none)))
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none)))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none))):IS-empty: staticOff: 0
	-- Invocation:gen: Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none)))
	-- Invocation:loadOrigin: Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none)))
	-- Invocation:loadOrigin:scan: Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none)))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Array(2,RangeList(Range(2,3),RangeList(Range(4,5),none)))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: RangeList(Range(2,3),RangeList(Range(4,5),none)):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(Range(2,3),RangeList(Range(4,5),none))
	-- Invocation:loadOrigin: RangeList(Range(2,3),RangeList(Range(4,5),none))
	-- Invocation:loadOrigin:scan: RangeList(Range(2,3),RangeList(Range(4,5),none))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(Range(2,3),RangeList(Range(4,5),none))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: Range(2,3):IS-empty: staticOff: 0
	-- Invocation:gen: Range(2,3)
	-- Invocation:loadOrigin: Range(2,3)
	-- Invocation:loadOrigin:scan: Range(2,3)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Range(2,3)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- Function:invoke: 
	-- pattern:load: Range(low: ? integer,upp: ? integer)
	invoke 567 0 Range
	-- ObjectGenerator:gen: super: RangeList(Range(4,5),none):IS-empty: staticOff: 0
	-- Invocation:gen: RangeList(Range(4,5),none)
	-- Invocation:loadOrigin: RangeList(Range(4,5),none)
	-- Invocation:loadOrigin:scan: RangeList(Range(4,5),none)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: RangeList(Range(4,5),none)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: Range(4,5):IS-empty: staticOff: 0
	-- Invocation:gen: Range(4,5)
	-- Invocation:loadOrigin: Range(4,5)
	-- Invocation:loadOrigin:scan: Range(4,5)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Range(4,5)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 0
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	-- ObjectGenerator:gen: super: 5:IS-empty: staticOff: 0
	-- Invocation:gen: 5
	-- Invocation:loadOrigin: 5
	-- Invocation:loadOrigin:scan: 5
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 5
	-- Function:invoke: 
	-- pattern:load: Range(low: ? integer,upp: ? integer)
	invoke 567 0 Range
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Function:invoke: 
	-- pattern:load: RangeList(head: ? Range,tail: ? RangeList)
	invoke 570 0 RangeList
	-- Function:invoke: 
	-- pattern:load: Array(ndim: ? integer,ranges: ? RangeList)
	invoke 578 0 Array
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 6 a
	-- ObjectGenerator:gen: super: a.putAtAt(2,4,99):IS-empty: staticOff: 0
	-- Invocation:gen: a.putAtAt(2,4,99)
	-- Invocation:loadOrigin: a.putAtAt(2,4,99)
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: putAtAt(2,4,99) :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 6 a
	-- Invocation:loadOrigin:scan: putAtAt(2,4,99)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 0
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	-- ObjectGenerator:gen: super: 99:IS-empty: staticOff: 0
	-- Invocation:gen: 99
	-- Invocation:loadOrigin: 99
	-- Invocation:loadOrigin:scan: 99
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 99
	-- Function:invoke: 
	-- pattern:load: putAtAt(inx1: ? integer,inx2: ? integer,exp: ? integer)
	invoke 589 0 putAtAt
	rpop
	-- ObjectGenerator:gen: super: putint(a.getAtAt(2,4)):IS-empty: staticOff: 0
	-- Invocation:gen: putint(a.getAtAt(2,4))
	-- Invocation:loadOrigin: putint(a.getAtAt(2,4))
	-- Invocation:loadOrigin:scan: putint(a.getAtAt(2,4))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(a.getAtAt(2,4))
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: a.getAtAt(2,4):IS-empty: staticOff: 0
	-- Invocation:gen: a.getAtAt(2,4)
	-- Invocation:loadOrigin: a.getAtAt(2,4)
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: getAtAt(2,4) :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 6 a
	-- Invocation:loadOrigin:scan: getAtAt(2,4)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 0
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	-- Function:invoke: 
	-- pattern:load: getAtAt(inx1: ? integer,inx2: ? integer) -> exp: ? integer
	invoke 590 0 getAtAt
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
	-- ObjectGenerator:gen: super: indices := IntList(2,IntList(4,none)):IS-empty: staticOff: 0
	-- Invocation:gen: indices := IntList(2,IntList(4,none))
	-- Invocation:loadOrigin: indices := IntList(2,IntList(4,none))
	-- Invocation:loadOrigin:scan: indices
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: indices
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := IntList(2,IntList(4,none))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: IntList(2,IntList(4,none)):IS-empty: staticOff: 0
	-- Invocation:gen: IntList(2,IntList(4,none))
	-- Invocation:loadOrigin: IntList(2,IntList(4,none))
	-- Invocation:loadOrigin:scan: IntList(2,IntList(4,none))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: IntList(2,IntList(4,none))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- ObjectGenerator:gen: super: IntList(4,none):IS-empty: staticOff: 0
	-- Invocation:gen: IntList(4,none)
	-- Invocation:loadOrigin: IntList(4,none)
	-- Invocation:loadOrigin:scan: IntList(4,none)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: IntList(4,none)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 0
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Function:invoke: 
	-- pattern:load: IntList(head: ? integer,tail: ? IntList)
	invoke 560 0 IntList
	-- Function:invoke: 
	-- pattern:load: IntList(head: ? integer,tail: ? IntList)
	invoke 560 0 IntList
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 7 indices
	-- ObjectGenerator:gen: super: a.realPutAt(indices,99):IS-empty: staticOff: 0
	-- Invocation:gen: a.realPutAt(indices,99)
	-- Invocation:loadOrigin: a.realPutAt(indices,99)
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: realPutAt(indices,99) :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 6 a
	-- Invocation:loadOrigin:scan: realPutAt(indices,99)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: indices:IS-empty: staticOff: 0
	-- Invocation:gen: indices
	-- Invocation:loadOrigin: indices
	-- Invocation:loadOrigin:scan: indices
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: indices
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: indices
	rpushg 7 indices
	-- ObjectGenerator:gen: super: 99:IS-empty: staticOff: 0
	-- Invocation:gen: 99
	-- Invocation:loadOrigin: 99
	-- Invocation:loadOrigin:scan: 99
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 99
	-- Function:invoke: 
	-- pattern:load: realPutAt(il: ? IntList,exp: ? integer)
	invoke 591 0 realPutAt
	rpop
	-- ObjectGenerator:gen: super: putint(a.realGetAt(indices)):IS-empty: staticOff: 0
	-- Invocation:gen: putint(a.realGetAt(indices))
	-- Invocation:loadOrigin: putint(a.realGetAt(indices))
	-- Invocation:loadOrigin:scan: putint(a.realGetAt(indices))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(a.realGetAt(indices))
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: a.realGetAt(indices):IS-empty: staticOff: 0
	-- Invocation:gen: a.realGetAt(indices)
	-- Invocation:loadOrigin: a.realGetAt(indices)
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: realGetAt(indices) :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 6 a
	-- Invocation:loadOrigin:scan: realGetAt(indices)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: indices:IS-empty: staticOff: 0
	-- Invocation:gen: indices
	-- Invocation:loadOrigin: indices
	-- Invocation:loadOrigin:scan: indices
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: indices
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: indices
	rpushg 7 indices
	-- Function:invoke: 
	-- pattern:load: realGetAt(il: ? IntList) -> exp: ? integer
	invoke 592 0 realGetAt
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
 L173:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#776 776
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L174:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: body:IS-empty: staticOff: 0
	-- Invocation:gen: body
	-- Invocation:loadOrigin: body
	-- Invocation:loadOrigin:scan: body
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: body
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: body
	sendv 1 body
	rpop
	-- ObjectGenerator:gen: super: inx := inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx := inx + 1
	-- Invocation:loadOrigin: inx := inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := inx + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx + 1
	-- Invocation:loadOrigin: inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 inx
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 81
 L175:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#777 777
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L176:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 84
 L177:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#778 778
	rstore 2 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: i
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L178:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: i := L + 1 - inx:IS-empty: staticOff: 0
	-- Invocation:gen: i := L + 1 - inx
	-- Invocation:loadOrigin: i := L + 1 - inx
	-- Invocation:loadOrigin:scan: i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: i
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := L + 1 - inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L + 1 - inx:IS-empty: staticOff: 0
	-- Invocation:gen: L + 1 - inx
	-- Invocation:loadOrigin: L + 1 - inx
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: + 1 - inx :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- Invocation:loadOrigin:scan: + 1 - inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1 - inx:IS-empty: staticOff: 0
	-- Invocation:gen: 1 - inx
	-- Invocation:loadOrigin: 1 - inx
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: - inx :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: - inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 i
	-- ObjectGenerator:gen: super: put('0' + D.%get i):IS-empty: staticOff: 0
	-- Invocation:gen: put('0' + D.%get i)
	-- Invocation:loadOrigin: put('0' + D.%get i)
	-- Invocation:loadOrigin:scan: put('0' + D.%get i)
	-- Function:pushThis: 
	-- Function:loadOrigin: put('0' + D.%get i)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: '0' + D.%get i:IS-empty: staticOff: 0
	-- Invocation:gen: '0' + D.%get i
	-- Invocation:loadOrigin: '0' + D.%get i
	-- Invocation:loadOrigin:scan: '0'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- next not assign: + D.%get i :E: '0'
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 48
	-- Invocation:loadOrigin:scan: + D.%get i
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: D.%get i:IS-empty: staticOff: 0
	-- Invocation:gen: D.%get i
	-- Invocation:loadOrigin: D.%get i
	-- Invocation:loadOrigin:scan: D
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: D
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: %get i :E: D
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: D
	rpushg 2 D
	-- Invocation:loadOrigin:scan: %get i
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get i
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: i:IS-empty: staticOff: 0
	-- Invocation:gen: i
	-- Invocation:loadOrigin: i
	-- Invocation:loadOrigin:scan: i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: i
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 1 i
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: + V: ? char -> R: ? char
	plus
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L179:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 121
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L180:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := 0:IS-empty: staticOff: 0
	-- Invocation:gen: M := 0
	-- Invocation:loadOrigin: M := 0
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 M
 L181:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class get 122
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: res
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 123 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L182:
	-- Include:gen: 
 L183:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class free 124
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L184:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := 0:IS-empty: staticOff: 0
	-- Invocation:gen: M := 0
	-- Invocation:loadOrigin: M := 0
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 M
	-- ObjectGenerator:gen: super: enable:IS-empty: staticOff: 0
	-- Invocation:gen: enable
	-- Invocation:loadOrigin: enable
	-- Invocation:loadOrigin:scan: enable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: enable
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: enable
	%enable 12
 L185:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class start 126
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L186:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: status := p_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: status := p_status.ACTIVE
	-- Invocation:loadOrigin: status := p_status.ACTIVE
	-- Invocation:loadOrigin:scan: status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: status
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := p_status.ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: p_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: p_status.ACTIVE
	-- Invocation:loadOrigin: p_status.ACTIVE
	-- Invocation:loadOrigin:scan: p_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p_status
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: ACTIVE :E: p_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
 L187:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 128
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 129 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L188:
	-- Include:gen: 
 L189:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class attach 132
	pushThis 
	rstoreg 2 M
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L190:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: main := M:IS-empty: staticOff: 0
	-- Invocation:gen: main := M
	-- Invocation:loadOrigin: main := M
	-- Invocation:loadOrigin:scan: main
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: main
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := M
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: M:IS-empty: staticOff: 0
	-- Invocation:gen: M
	-- Invocation:loadOrigin: M
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	rpushg 2 M
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 main
 L191:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 133
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loopX
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 134 2 loopX
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L192:
	-- Include:gen: 
 L193:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 137
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: S
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L194:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: C1 := Core:IS-empty: staticOff: 0
	-- Invocation:gen: C1 := Core
	-- Invocation:loadOrigin: C1 := Core
	-- Invocation:loadOrigin:scan: C1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 131 0 Core
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 C1
	-- ObjectGenerator:gen: super: fork(C1):IS-empty: staticOff: 0
	-- Invocation:gen: fork(C1)
	-- Invocation:loadOrigin: fork(C1)
	-- Invocation:loadOrigin:scan: fork(C1)
	-- Function:pushThis: 
	-- Function:loadOrigin: fork(C1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: C1:IS-empty: staticOff: 0
	-- Invocation:gen: C1
	-- Invocation:loadOrigin: C1
	-- Invocation:loadOrigin:scan: C1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C1
	rpushg 2 C1
	-- Function:invoke: 
	-- pattern:load: fork(S: ? Object)
	%fork 13
	-- ObjectGenerator:gen: super: C2 := Core:IS-empty: staticOff: 0
	-- Invocation:gen: C2 := Core
	-- Invocation:loadOrigin: C2 := Core
	-- Invocation:loadOrigin:scan: C2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 131 0 Core
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 C2
	-- ObjectGenerator:gen: super: fork(C2):IS-empty: staticOff: 0
	-- Invocation:gen: fork(C2)
	-- Invocation:loadOrigin: fork(C2)
	-- Invocation:loadOrigin:scan: fork(C2)
	-- Function:pushThis: 
	-- Function:loadOrigin: fork(C2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: C2:IS-empty: staticOff: 0
	-- Invocation:gen: C2
	-- Invocation:loadOrigin: C2
	-- Invocation:loadOrigin:scan: C2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C2
	rpushg 3 C2
	-- Function:invoke: 
	-- pattern:load: fork(S: ? Object)
	%fork 13
	-- ObjectGenerator:gen: super: C3 := Core:IS-empty: staticOff: 0
	-- Invocation:gen: C3 := Core
	-- Invocation:loadOrigin: C3 := Core
	-- Invocation:loadOrigin:scan: C3
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C3
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 131 0 Core
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 C3
	-- ObjectGenerator:gen: super: fork(C3):IS-empty: staticOff: 0
	-- Invocation:gen: fork(C3)
	-- Invocation:loadOrigin: fork(C3)
	-- Invocation:loadOrigin:scan: fork(C3)
	-- Function:pushThis: 
	-- Function:loadOrigin: fork(C3)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: C3:IS-empty: staticOff: 0
	-- Invocation:gen: C3
	-- Invocation:loadOrigin: C3
	-- Invocation:loadOrigin:scan: C3
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C3
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C3
	rpushg 4 C3
	-- Function:invoke: 
	-- pattern:load: fork(S: ? Object)
	%fork 13
	-- ObjectGenerator:gen: super: C4 := Core:IS-empty: staticOff: 0
	-- Invocation:gen: C4 := Core
	-- Invocation:loadOrigin: C4 := Core
	-- Invocation:loadOrigin:scan: C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C4
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 131 0 Core
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 C4
	-- ObjectGenerator:gen: super: fork(C4):IS-empty: staticOff: 0
	-- Invocation:gen: fork(C4)
	-- Invocation:loadOrigin: fork(C4)
	-- Invocation:loadOrigin:scan: fork(C4)
	-- Function:pushThis: 
	-- Function:loadOrigin: fork(C4)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: C4:IS-empty: staticOff: 0
	-- Invocation:gen: C4
	-- Invocation:loadOrigin: C4
	-- Invocation:loadOrigin:scan: C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C4
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C4
	rpushg 5 C4
	-- Function:invoke: 
	-- pattern:load: fork(S: ? Object)
	%fork 13
	-- ObjectGenerator:gen: super: S := Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: S := Scheduler
	-- Invocation:loadOrigin: S := Scheduler
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Scheduler
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 127 0 Scheduler
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 S
	-- ObjectGenerator:gen: super: C1.attach(S):IS-empty: staticOff: 0
	-- Invocation:gen: C1.attach(S)
	-- Invocation:loadOrigin: C1.attach(S)
	-- Invocation:loadOrigin:scan: C1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: attach(S) :E: C1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C1
	rpushg 2 C1
	-- Invocation:loadOrigin:scan: attach(S)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: S:IS-empty: staticOff: 0
	-- Invocation:gen: S
	-- Invocation:loadOrigin: S
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 132 0 attach
	rpop
	-- ObjectGenerator:gen: super: S := Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: S := Scheduler
	-- Invocation:loadOrigin: S := Scheduler
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Scheduler
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 127 0 Scheduler
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 S
	-- ObjectGenerator:gen: super: C2.attach(S):IS-empty: staticOff: 0
	-- Invocation:gen: C2.attach(S)
	-- Invocation:loadOrigin: C2.attach(S)
	-- Invocation:loadOrigin:scan: C2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: attach(S) :E: C2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C2
	rpushg 3 C2
	-- Invocation:loadOrigin:scan: attach(S)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: S:IS-empty: staticOff: 0
	-- Invocation:gen: S
	-- Invocation:loadOrigin: S
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 132 0 attach
	rpop
	-- ObjectGenerator:gen: super: S := Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: S := Scheduler
	-- Invocation:loadOrigin: S := Scheduler
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Scheduler
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 127 0 Scheduler
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 S
	-- ObjectGenerator:gen: super: C3.attach(S):IS-empty: staticOff: 0
	-- Invocation:gen: C3.attach(S)
	-- Invocation:loadOrigin: C3.attach(S)
	-- Invocation:loadOrigin:scan: C3
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C3
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: attach(S) :E: C3
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C3
	rpushg 4 C3
	-- Invocation:loadOrigin:scan: attach(S)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: S:IS-empty: staticOff: 0
	-- Invocation:gen: S
	-- Invocation:loadOrigin: S
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 132 0 attach
	rpop
	-- ObjectGenerator:gen: super: C4.attach(Scheduler):IS-empty: staticOff: 0
	-- Invocation:gen: C4.attach(Scheduler)
	-- Invocation:loadOrigin: C4.attach(Scheduler)
	-- Invocation:loadOrigin:scan: C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C4
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: attach(Scheduler) :E: C4
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C4
	rpushg 5 C4
	-- Invocation:loadOrigin:scan: attach(Scheduler)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 127 0 Scheduler
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 132 0 attach
	rpop
 L195:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Element 83
	pushThis 
	rstoreg 2 elm
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: pred
	-- VarRef:gen: succ
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L196:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := %this Element:IS-empty: staticOff: 0
	-- Invocation:gen: res := %this Element
	-- Invocation:loadOrigin: res := %this Element
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this Element
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this Element:IS-empty: staticOff: 0
	-- Invocation:gen: %this Element
	-- Invocation:loadOrigin: %this Element
	-- Invocation:loadOrigin:scan: %this Element
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Element
	-- AdjustOrigin: 0
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Element
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 res
 L197:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 3 res
	rtn(D)
	end 1

	class scan 84
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	-- VarRef:gen: currentElement
	-- pattern:gen: do
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L198:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: currentElement := head:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement := head
	-- Invocation:loadOrigin: currentElement := head
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: do:IS-empty: staticOff: 0
	-- Invocation:gen: do
	-- Invocation:loadOrigin: do
	-- Invocation:loadOrigin:scan: do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: do
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 85 0 do
	rpop
 L199:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scanFromLast 87
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	-- VarRef:gen: currentElement
	-- pattern:gen: do
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L200:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: currentElement := last:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement := last
	-- Invocation:loadOrigin: currentElement := last
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := last
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: last:IS-empty: staticOff: 0
	-- Invocation:gen: last
	-- Invocation:loadOrigin: last
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: do:IS-empty: staticOff: 0
	-- Invocation:gen: do
	-- Invocation:loadOrigin: do
	-- Invocation:loadOrigin:scan: do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: do
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 88 0 do
	rpop
 L201:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class insert 90
	pushThis 
	rstoreg 2 elm
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: E
	-- VarRef:gen: b
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L202:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := ELM <> NONE:IS-empty: staticOff: 0
	-- Invocation:gen: B := ELM <> NONE
	-- Invocation:loadOrigin: B := ELM <> NONE
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := ELM <> NONE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: ELM <> NONE:IS-empty: staticOff: 0
	-- Invocation:gen: ELM <> NONE
	-- Invocation:loadOrigin: ELM <> NONE
	-- Invocation:loadOrigin:scan: ELM
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ELM
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: <> NONE :E: ELM
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Invocation:loadOrigin:scan: <> NONE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: NONE:IS-empty: staticOff: 0
	-- Invocation:gen: NONE
	-- Invocation:loadOrigin: NONE
	-- Invocation:loadOrigin:scan: NONE
	-- Unary:pushThis: 
	-- Unary:loadOrigin: NONE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 b
	-- ObjectGenerator:gen: super: %if B %then% 
    E := Element(elm)
    %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E:IS-empty: staticOff: 0
	-- Invocation:gen: %if B %then% 
    E := Element(elm)
    %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- Invocation:loadOrigin: %if B %then% 
    E := Element(elm)
    %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- Invocation:loadOrigin:scan: %if B %then% 
    E := Element(elm)
    %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if B %then% 
    E := Element(elm)
    %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if B %then% 
    E := Element(elm)
    %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: B:IS-empty: staticOff: 0
	-- Invocation:gen: B
	-- Invocation:loadOrigin: B
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: b
	pushg 1 b
	jmpFalse L204
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 782 0 #S#782
	rpop
 L204:
 L203:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class remove 91
	pushThis 
	rstoreg 2 elm
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L205:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: scan:singular:staticOff: 0
	pushThis 
	invoke 92 0 scan#S#92
	rpop
 L206:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class removeNext 93
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L207:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if last <> none %then% 
    elm := last.elm
    last := last.pred
    %if last <> none %then% 
    last.succ := none %else% 
    head := none:IS-empty: staticOff: 0
	-- Invocation:gen: %if last <> none %then% 
    elm := last.elm
    last := last.pred
    %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- Invocation:loadOrigin: %if last <> none %then% 
    elm := last.elm
    last := last.pred
    %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- Invocation:loadOrigin:scan: %if last <> none %then% 
    elm := last.elm
    last := last.pred
    %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if last <> none %then% 
    elm := last.elm
    last := last.pred
    %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if last <> none %then% 
    elm := last.elm
    last := last.pred
    %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: last <> none:IS-empty: staticOff: 0
	-- Invocation:gen: last <> none
	-- Invocation:loadOrigin: last <> none
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: <> none :E: last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L209
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 786 0 #S#786
	rpop
 L209:
 L208:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: elm
	rpushg 2 elm
	rtn(D)
	end 1

	class isEmpty 94
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L210:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := head = none:IS-empty: staticOff: 0
	-- Invocation:gen: B := head = none
	-- Invocation:loadOrigin: B := head = none
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := head = none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head = none:IS-empty: staticOff: 0
	-- Invocation:gen: head = none
	-- Invocation:loadOrigin: head = none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: = none :E: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: = none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L211:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class clear 95
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L212:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: head := none:IS-empty: staticOff: 0
	-- Invocation:gen: head := none
	-- Invocation:loadOrigin: head := none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 head
	-- ObjectGenerator:gen: super: last := none:IS-empty: staticOff: 0
	-- Invocation:gen: last := none
	-- Invocation:loadOrigin: last := none
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L213:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 140
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L214:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('Q'):IS-empty: staticOff: 0
	-- Invocation:gen: put('Q')
	-- Invocation:loadOrigin: put('Q')
	-- Invocation:loadOrigin:scan: put('Q')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('Q')
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 'Q':IS-empty: staticOff: 0
	-- Invocation:gen: 'Q'
	-- Invocation:loadOrigin: 'Q'
	-- Invocation:loadOrigin:scan: 'Q'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 81
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L215:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry 142
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L216:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L.get:IS-empty: staticOff: 0
	-- Invocation:gen: L.get
	-- Invocation:loadOrigin: L.get
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 122 0 get
	rpop
	-- ObjectGenerator:gen: super: %inner entry:IS-empty: staticOff: 0
	-- Invocation:gen: %inner entry
	-- Invocation:loadOrigin: %inner entry
	-- Invocation:loadOrigin:scan: %inner entry
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner entry
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner entry
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: L.free:IS-empty: staticOff: 0
	-- Invocation:gen: L.free
	-- Invocation:loadOrigin: L.free
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L217:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class add 143
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L218:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 144 0 entry#S#144
	rpop
 L219:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class dcr 145
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L220:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 146 0 entry#S#146
	rpop
 L221:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class running 147
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L222:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 148 0 entry#S#148
	rpop
 L223:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class entry 150
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L224:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L.get:IS-empty: staticOff: 0
	-- Invocation:gen: L.get
	-- Invocation:loadOrigin: L.get
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 122 0 get
	rpop
	-- ObjectGenerator:gen: super: V := V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V := V + 1
	-- Invocation:loadOrigin: V := V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := V + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V + 1
	-- Invocation:loadOrigin: V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + 1 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
	-- ObjectGenerator:gen: super: %if V > 1 %then% 
    put('V'):IS-empty: staticOff: 0
	-- Invocation:gen: %if V > 1 %then% 
    put('V')
	-- Invocation:loadOrigin: %if V > 1 %then% 
    put('V')
	-- Invocation:loadOrigin:scan: %if V > 1 %then% 
    put('V')
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if V > 1 %then% 
    put('V')
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if V > 1 %then% 
    put('V')
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: V > 1:IS-empty: staticOff: 0
	-- Invocation:gen: V > 1
	-- Invocation:loadOrigin: V > 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: > 1 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: > 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: > V: ? integer -> B: ? Boolean
	gt
	jmpFalse L226
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 805 0 #S#805
	rpop
 L226:
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: V := V - 1:IS-empty: staticOff: 0
	-- Invocation:gen: V := V - 1
	-- Invocation:loadOrigin: V := V - 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := V - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: V - 1:IS-empty: staticOff: 0
	-- Invocation:gen: V - 1
	-- Invocation:loadOrigin: V - 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - 1 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
	-- ObjectGenerator:gen: super: L.free:IS-empty: staticOff: 0
	-- Invocation:gen: L.free
	-- Invocation:loadOrigin: L.free
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L225:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 151
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=151
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L227:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := 0:IS-empty: staticOff: 0
	-- Invocation:gen: V := 0
	-- Invocation:loadOrigin: V := 0
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L228:
	rtnInner
	end 1

	class insert 152
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=152
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L229:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: Q.insert(P):IS-empty: staticOff: 0
	-- Invocation:gen: Q.insert(P)
	-- Invocation:loadOrigin: Q.insert(P)
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: insert(P) :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: P:IS-empty: staticOff: 0
	-- Invocation:gen: P
	-- Invocation:loadOrigin: P
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 90 0 insert
	rpop
 L230:
	rtnInner
	end 1

	class removeNext 153
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L231:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 154 0 entry#S#154
	rpop
 L232:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: P
	rpushg 2 P
	rtn(D)
	end 1

	class remove 155
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=155
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L233:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: Q.remove(P):IS-empty: staticOff: 0
	-- Invocation:gen: Q.remove(P)
	-- Invocation:loadOrigin: Q.remove(P)
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: remove(P) :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: remove(P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: P:IS-empty: staticOff: 0
	-- Invocation:gen: P
	-- Invocation:loadOrigin: P
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: remove(elm: ? Object)
	invoke 91 0 remove
	rpop
 L234:
	rtnInner
	end 1

	class isEmpty 156
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L235:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 157 0 entry#S#157
	rpop
 L236:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class display 158
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=158
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L237:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: Q.display:IS-empty: staticOff: 0
	-- Invocation:gen: Q.display
	-- Invocation:loadOrigin: Q.display
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: display :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: display
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: display
	invoke 140 0 display
	rpop
 L238:
	rtnInner
	end 1

	class addWaiting 159
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=159
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L239:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: W := W + 1:IS-empty: staticOff: 0
	-- Invocation:gen: W := W + 1
	-- Invocation:loadOrigin: W := W + 1
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := W + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: W + 1:IS-empty: staticOff: 0
	-- Invocation:gen: W + 1
	-- Invocation:loadOrigin: W + 1
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + 1 :E: W
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 W
 L240:
	rtnInner
	end 1

	class dcrWaiting 160
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=160
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L241:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: W := W - 1:IS-empty: staticOff: 0
	-- Invocation:gen: W := W - 1
	-- Invocation:loadOrigin: W := W - 1
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := W - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: W - 1:IS-empty: staticOff: 0
	-- Invocation:gen: W - 1
	-- Invocation:loadOrigin: W - 1
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - 1 :E: W
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 W
 L242:
	rtnInner
	end 1

	class hasWaiting 161
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L243:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 162 0 entry#S#162
	rpop
 L244:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class init 164
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L245:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L.get:IS-empty: staticOff: 0
	-- Invocation:gen: L.get
	-- Invocation:loadOrigin: L.get
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 122 0 get
	rpop
	-- ObjectGenerator:gen: super: L.init:IS-empty: staticOff: 0
	-- Invocation:gen: L.init
	-- Invocation:loadOrigin: L.init
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: init :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 121 0 init
	rpop
	-- ObjectGenerator:gen: super: L.free:IS-empty: staticOff: 0
	-- Invocation:gen: L.free
	-- Invocation:loadOrigin: L.free
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L246:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 165
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L247:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L.get:IS-empty: staticOff: 0
	-- Invocation:gen: L.get
	-- Invocation:loadOrigin: L.get
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 122 0 get
	rpop
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: L.free:IS-empty: staticOff: 0
	-- Invocation:gen: L.free
	-- Invocation:loadOrigin: L.free
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L248:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#175 175
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- Invocation:loadOrigin:scan: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- ObjectGenerator:gen: super: pos = rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: pos = rep.length
	-- Invocation:loadOrigin: pos = rep.length
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = rep.length :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = rep.length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: rep.length
	-- Invocation:loadOrigin: rep.length
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 55 0 length
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L249:
 L250:
	rtnInner
	end 1

	class %if%then%%else%#S#177 177
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- Invocation:loadOrigin:scan: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- ObjectGenerator:gen: super: pos = rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: pos = rep.length
	-- Invocation:loadOrigin: pos = rep.length
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = rep.length :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = rep.length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: rep.length
	-- Invocation:loadOrigin: rep.length
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 55 0 length
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L251:
 L252:
	rtnInner
	end 1

	class %if%then%%else%#S#179 179
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos + 1
	-- Invocation:loadOrigin:scan: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos + 1
	-- ObjectGenerator:gen: super: pos = noof:IS-empty: staticOff: 0
	-- Invocation:gen: pos = noof
	-- Invocation:loadOrigin: pos = noof
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = noof :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L253:
 L254:
	rtnInner
	end 1

	class %if%then%%else%#S#181 181
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos - 1
	-- Invocation:loadOrigin:scan: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos - 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos - 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos - 1
	-- ObjectGenerator:gen: super: pos = noof:IS-empty: staticOff: 0
	-- Invocation:gen: pos = noof
	-- Invocation:loadOrigin: pos = noof
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = noof :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L255:
 L256:
	rtnInner
	end 1

	class loop 183
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L257:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: current := rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: current := rep.%get pos
	-- Invocation:loadOrigin: current := rep.%get pos
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := rep.%get pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos
	-- Invocation:loadOrigin: rep.%get pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %get pos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 current
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 pos
	-- ObjectGenerator:gen: super: %inner forAll:IS-empty: staticOff: 0
	-- Invocation:gen: %inner forAll
	-- Invocation:loadOrigin: %inner forAll
	-- Invocation:loadOrigin:scan: %inner forAll
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner forAll
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner forAll
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %if pos < noof %then% 
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if pos < noof %then% 
    %restart loop
	-- Invocation:loadOrigin: %if pos < noof %then% 
    %restart loop
	-- Invocation:loadOrigin:scan: %if pos < noof %then% 
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if pos < noof %then% 
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if pos < noof %then% 
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: pos < noof:IS-empty: staticOff: 0
	-- Invocation:gen: pos < noof
	-- Invocation:loadOrigin: pos < noof
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: < noof :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: < noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L259
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 814 0 #S#814
	rpop
 L259:
 L258:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#185 185
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- Invocation:loadOrigin:scan: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: rep.length
	-- Invocation:loadOrigin: rep.length
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 55 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L260:
 L261:
	rtnInner
	end 1

	class #S#816 816
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L262:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "index error in range".print:IS-empty: staticOff: 0
	-- Invocation:gen: "index error in range".print
	-- Invocation:loadOrigin: "index error in range".print
	-- Invocation:loadOrigin:scan: "index error in range"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText index error in range
	-- next not assign: print :E: "index error in range"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
 L263:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class run 231
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L264:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M.get:IS-empty: staticOff: 0
	-- Invocation:gen: M.get
	-- Invocation:loadOrigin: M.get
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: get :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 122 0 get
	rpop
	-- ObjectGenerator:gen: super: Q.insert(P):IS-empty: staticOff: 0
	-- Invocation:gen: Q.insert(P)
	-- Invocation:loadOrigin: Q.insert(P)
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: insert(P) :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: P:IS-empty: staticOff: 0
	-- Invocation:gen: P
	-- Invocation:loadOrigin: P
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 90 0 insert
	rpop
	-- ObjectGenerator:gen: super: SQS.insert(P):IS-empty: staticOff: 0
	-- Invocation:gen: SQS.insert(P)
	-- Invocation:loadOrigin: SQS.insert(P)
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: insert(P) :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: P:IS-empty: staticOff: 0
	-- Invocation:gen: P
	-- Invocation:loadOrigin: P
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 152 0 insert
	rpop
	-- ObjectGenerator:gen: super: M.free:IS-empty: staticOff: 0
	-- Invocation:gen: M.free
	-- Invocation:loadOrigin: M.free
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L265:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class AwaitTermination 232
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 233 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L266:
	-- Include:gen: 
 L267:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 238
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L268:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: cnt := 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt := 1
	-- Invocation:loadOrigin: cnt := 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 cnt
 L269:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class wait 239
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: theActive
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L270:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M.get:IS-empty: staticOff: 0
	-- Invocation:gen: M.get
	-- Invocation:loadOrigin: M.get
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: get :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 122 0 get
	rpop
	-- ObjectGenerator:gen: super: cnt := cnt - 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt := cnt - 1
	-- Invocation:loadOrigin: cnt := cnt - 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := cnt - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: cnt - 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt - 1
	-- Invocation:loadOrigin: cnt - 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - 1 :E: cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 cnt
	-- ObjectGenerator:gen: super: %if cnt < 0 %then% 
    thisCore.main.active.status := P_status.WAITING
    SQS.addWaiting
    Q.insert(thisCore.main.active)
    theActive := thisCore.main.active
    M.free
    theActive.suspend %else% 
    M.free:IS-empty: staticOff: 0
	pushThis 
	invoke 240 0 %if%then%%else%#S#240
	rpop
 L271:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class signal 241
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: P
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L272:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M.get:IS-empty: staticOff: 0
	-- Invocation:gen: M.get
	-- Invocation:loadOrigin: M.get
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: get :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 122 0 get
	rpop
	-- ObjectGenerator:gen: super: cnt := cnt + 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt := cnt + 1
	-- Invocation:loadOrigin: cnt := cnt + 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := cnt + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: cnt + 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt + 1
	-- Invocation:loadOrigin: cnt + 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + 1 :E: cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 cnt
	-- ObjectGenerator:gen: super: %if cnt <= 0 %then% 
    P := Q.removeNext
    P.status := P_status.ACTIVE
    SQS.insert(P)
    SQS.dcrWaiting
    M.free %else% 
    M.free:IS-empty: staticOff: 0
	pushThis 
	invoke 242 0 %if%then%%else%#S#242
	rpop
 L273:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class start 244
	rstore 2 origin
	allocEventQ
	-- super start
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=244
	pushThis 
	rpushg 2 iOrigin
	topSuper  126
	-- VarRef:gen: P
	rtnInner
	DO:
	doEventQ
	mvStack 
 L274:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: P := %this Process:IS-empty: staticOff: 0
	-- Invocation:gen: P := %this Process
	-- Invocation:loadOrigin: P := %this Process
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this Process
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this Process:IS-empty: staticOff: 0
	-- Invocation:gen: %this Process
	-- Invocation:loadOrigin: %this Process
	-- Invocation:loadOrigin:scan: %this Process
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Process
	-- AdjustOrigin: 0
	rpushg 2 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Process
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 P
	-- ObjectGenerator:gen: super: "starting: ".print:IS-empty: staticOff: 0
	-- Invocation:gen: "starting: ".print
	-- Invocation:loadOrigin: "starting: ".print
	-- Invocation:loadOrigin:scan: "starting: "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText starting: 
	-- next not assign: print :E: "starting: "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: id.print:IS-empty: staticOff: 0
	-- Invocation:gen: id.print
	-- Invocation:loadOrigin: id.print
	-- Invocation:loadOrigin:scan: id
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: id
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: print :E: id
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: id
	rpushg 2 id
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 1 origin
	rpushg 8 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
	-- ObjectGenerator:gen: super: SQS.insert(P):IS-empty: staticOff: 0
	-- Invocation:gen: SQS.insert(P)
	-- Invocation:loadOrigin: SQS.insert(P)
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: insert(P) :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: P:IS-empty: staticOff: 0
	-- Invocation:gen: P
	-- Invocation:loadOrigin: P
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 3 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 152 0 insert
	rpop
 L275:
	rtnInner
	end 1

	class init 246
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L276:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: mutex.init:IS-empty: staticOff: 0
	-- Invocation:gen: mutex.init
	-- Invocation:loadOrigin: mutex.init
	-- Invocation:loadOrigin:scan: mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mutex
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: init :E: mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 238 0 init
	rpop
 L277:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry 247
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L278:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: mutex.wait:IS-empty: staticOff: 0
	-- Invocation:gen: mutex.wait
	-- Invocation:loadOrigin: mutex.wait
	-- Invocation:loadOrigin:scan: mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mutex
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: wait :E: mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: wait
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: wait
	invoke 239 0 wait
	rpop
	-- ObjectGenerator:gen: super: V := V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V := V + 1
	-- Invocation:loadOrigin: V := V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := V + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V + 1
	-- Invocation:loadOrigin: V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + 1 :E: V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: mutex.signal:IS-empty: staticOff: 0
	-- Invocation:gen: mutex.signal
	-- Invocation:loadOrigin: mutex.signal
	-- Invocation:loadOrigin:scan: mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mutex
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: signal :E: mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: signal
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: signal
	invoke 241 0 signal
	rpop
 L279:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class wait 248
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: cond
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 249 2 loop
	rpop
	innerA  1
	rtnEventQ 0
	DO:
	mvStack 
 L280:
	-- Include:gen: 
 L281:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doplus 101
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: e
	-- VarRef:gen: i
	-- ConsRef:gen: T
	-- ObjectGenerator:gen: super: Indexed(L + S.length,Integer):IS-empty: staticOff: 2
	-- Invocation:gen: Indexed(L + S.length,Integer)
	-- Invocation:loadOrigin: Indexed(L + S.length,Integer)
	-- Invocation:loadOrigin:scan: Indexed(L + S.length,Integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(L + S.length,Integer)
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: L + S.length:IS-empty: staticOff: 0
	-- Invocation:gen: L + S.length
	-- Invocation:loadOrigin: L + S.length
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + S.length :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Invocation:loadOrigin:scan: + S.length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: S.length:IS-empty: staticOff: 0
	-- Invocation:gen: S.length
	-- Invocation:loadOrigin: S.length
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- ObjectGenerator:gen: super: Integer:IS-empty: staticOff: 0
	-- Invocation:gen: Integer
	-- Invocation:loadOrigin: Integer
	-- Invocation:loadOrigin:scan: Integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: Integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer(W: ? integer)
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L282:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% L %do% 
    e := %get inx
    T.%put e %at% inx:IS-empty: staticOff: 0
	pushThis 
	invoke 102 0 %for%to%%do%#S#102
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i:IS-empty: staticOff: 0
	pushThis 
	invoke 103 0 %for%to%%do%#S#103
	rpop
	-- ObjectGenerator:gen: super: V := T.asString:IS-empty: staticOff: 0
	-- Invocation:gen: V := T.asString
	-- Invocation:loadOrigin: V := T.asString
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := T.asString
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: T.asString:IS-empty: staticOff: 0
	-- Invocation:gen: T.asString
	-- Invocation:loadOrigin: T.asString
	-- Invocation:loadOrigin:scan: T
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: T
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: asString :E: T
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: asString
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: asString -> S: ? Object
	%asString 118
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 V
 L283:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#106 106
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% length %do% 
    current := %get inx
    %inner scan
	-- Invocation:loadOrigin:scan: %for 1 %to% length %do% 
    current := %get inx
    %inner scan
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% length %do% 
    current := %get inx
    %inner scan
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% length %do% 
    current := %get inx
    %inner scan
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: length:IS-empty: staticOff: 0
	-- Invocation:gen: length
	-- Invocation:loadOrigin: length
	-- Invocation:loadOrigin:scan: length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: length
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L284:
 L285:
	rtnInner
	end 1

	class %for%to%%do%#S#108 108
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% length %do% 
    put(%get inx)
	-- Invocation:loadOrigin:scan: %for 1 %to% length %do% 
    put(%get inx)
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% length %do% 
    put(%get inx)
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% length %do% 
    put(%get inx)
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: length:IS-empty: staticOff: 0
	-- Invocation:gen: length
	-- Invocation:loadOrigin: length
	-- Invocation:loadOrigin:scan: length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: length
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L286:
 L287:
	rtnInner
	end 1

	class loop 110
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: c1
	-- VarRef:gen: c2
	-- VarRef:gen: L
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L288:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := length:IS-empty: staticOff: 0
	-- Invocation:gen: L := length
	-- Invocation:loadOrigin: L := length
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: length:IS-empty: staticOff: 0
	-- Invocation:gen: length
	-- Invocation:loadOrigin: length
	-- Invocation:loadOrigin:scan: length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: length
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 L
	-- ObjectGenerator:gen: super: %if L <> S.length %then% 
    %leave loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if L <> S.length %then% 
    %leave loop
	-- Invocation:loadOrigin: %if L <> S.length %then% 
    %leave loop
	-- Invocation:loadOrigin:scan: %if L <> S.length %then% 
    %leave loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if L <> S.length %then% 
    %leave loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if L <> S.length %then% 
    %leave loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: L <> S.length:IS-empty: staticOff: 0
	-- Invocation:gen: L <> S.length
	-- Invocation:loadOrigin: L <> S.length
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: <> S.length :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 3 L
	-- Invocation:loadOrigin:scan: <> S.length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: S.length:IS-empty: staticOff: 0
	-- Invocation:gen: S.length
	-- Invocation:loadOrigin: S.length
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	-- Binary:invoke: 
	-- pattern:load: <> V: ? integer -> B: ? Boolean
	55
	jmpFalse L290
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 792 0 #S#792
	rpop
 L290:
	-- ObjectGenerator:gen: super: B := true:IS-empty: staticOff: 0
	-- Invocation:gen: B := true
	-- Invocation:loadOrigin: B := true
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := true
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: true:IS-empty: staticOff: 0
	-- Invocation:gen: true
	-- Invocation:loadOrigin: true
	-- Invocation:loadOrigin:scan: true
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: true
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: True -> B: ? Boolean
	invoke 24 0 True
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    c1 := %get inx
    c2 := S.%get inx
    %if c1 <> c2 %then% 
    B := false
    %leave loop:IS-empty: staticOff: 0
	pushThis 
	invoke 111 0 %for%to%%do%#S#111
	rpop
 L289:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 113
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: matchEq
	-- VarRef:gen: L
	-- VarRef:gen: L1
	-- VarRef:gen: L2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L291:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L1 := length:IS-empty: staticOff: 0
	-- Invocation:gen: L1 := length
	-- Invocation:loadOrigin: L1 := length
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: length:IS-empty: staticOff: 0
	-- Invocation:gen: length
	-- Invocation:loadOrigin: length
	-- Invocation:loadOrigin:scan: length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: length
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 L1
	-- ObjectGenerator:gen: super: L2 := S.length:IS-empty: staticOff: 0
	-- Invocation:gen: L2 := S.length
	-- Invocation:loadOrigin: L2 := S.length
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := S.length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: S.length:IS-empty: staticOff: 0
	-- Invocation:gen: S.length
	-- Invocation:loadOrigin: S.length
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 L2
	-- ObjectGenerator:gen: super: L := L1:IS-empty: staticOff: 0
	-- Invocation:gen: L := L1
	-- Invocation:loadOrigin: L := L1
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := L1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L1:IS-empty: staticOff: 0
	-- Invocation:gen: L1
	-- Invocation:loadOrigin: L1
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
	-- ObjectGenerator:gen: super: %if L1 < L2 %then% 
    L := L1 %else% 
    L := L2:IS-empty: staticOff: 0
	pushThis 
	invoke 118 0 %if%then%%else%#S#118
	rpop
	-- ObjectGenerator:gen: super: matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: matchEq
	-- Invocation:loadOrigin: matchEq
	-- Invocation:loadOrigin:scan: matchEq
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: matchEq
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: matchEq
	invoke 114 0 matchEq
	rpop
 L292:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class int2int 558
	pushThis 
	storeg 1 e
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L293:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner int2int:IS-empty: staticOff: 0
	-- Invocation:gen: %inner int2int
	-- Invocation:loadOrigin: %inner int2int
	-- Invocation:loadOrigin:scan: %inner int2int
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner int2int
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner int2int
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L294:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: val
	pushg 2 val
	rtn(D)
	end 1

	class intint2int 559
	pushThis 
	storeg 2 i2
	pushThis 
	storeg 1 i1
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L295:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner intint2int:IS-empty: staticOff: 0
	-- Invocation:gen: %inner intint2int
	-- Invocation:loadOrigin: %inner intint2int
	-- Invocation:loadOrigin:scan: %inner intint2int
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner intint2int
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner intint2int
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L296:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: val
	pushg 3 val
	rtn(D)
	end 1

	class IntList 560
	pushThis 
	rstoreg 2 tail
	pushThis 
	storeg 1 head
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: first -> r: ? integer
	-- pattern:gen: second -> r: ? integer
	-- pattern:gen: scan
	-- pattern:gen: length -> len: ? integer
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L297:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner IntList:IS-empty: staticOff: 0
	-- Invocation:gen: %inner IntList
	-- Invocation:loadOrigin: %inner IntList
	-- Invocation:loadOrigin:scan: %inner IntList
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner IntList
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner IntList
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L298:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Range 567
	pushThis 
	storeg 2 upp
	pushThis 
	storeg 1 low
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: noof
	-- ObjectGenerator:gen: super: (upp - low) + 1:IS-empty: staticOff: 3
	-- Invocation:gen: (upp - low) + 1
	-- Invocation:loadOrigin: (upp - low) + 1
	-- Invocation:loadOrigin:scan: (upp - low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (upp - low)
	-- Invocation:loadOrigin: upp - low
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - low :E: upp
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Invocation:loadOrigin:scan: - low
	-- BE:loadOrigin:E: - low
	-- next not assign: + 1 :E: - low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	pushThis 
	storeg 3 noof
	-- pattern:gen: check(inx: ? integer)
	-- pattern:gen: print
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L299:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if noof < 1 %then% 
    "range error\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: %if noof < 1 %then% 
    "range error\n".print
	-- Invocation:loadOrigin: %if noof < 1 %then% 
    "range error\n".print
	-- Invocation:loadOrigin:scan: %if noof < 1 %then% 
    "range error\n".print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if noof < 1 %then% 
    "range error\n".print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if noof < 1 %then% 
    "range error\n".print
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: noof < 1:IS-empty: staticOff: 0
	-- Invocation:gen: noof < 1
	-- Invocation:loadOrigin: noof < 1
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: < 1 :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: < 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L301
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 911 0 #S#911
	rpop
 L301:
 L300:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class RangeList 570
	pushThis 
	rstoreg 3 tail
	pushThis 
	rstoreg 2 head
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: empty -> b: ? boolean
	-- pattern:gen: first -> r: ? Range
	-- pattern:gen: second -> r: ? Range
	-- pattern:gen: scan
	-- pattern:gen: length -> len: ? integer
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L302:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner RangeList:IS-empty: staticOff: 0
	-- Invocation:gen: %inner RangeList
	-- Invocation:loadOrigin: %inner RangeList
	-- Invocation:loadOrigin:scan: %inner RangeList
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner RangeList
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner RangeList
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L303:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Array 578
	pushThis 
	rstoreg 2 ranges
	pushThis 
	storeg 1 ndim
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: R1
	-- VarRef:gen: R2
	-- VarRef:gen: pos
	-- VarRef:gen: noof
	-- VarRef:gen: rep
	-- pattern:gen: put(e: ? integer) -> res: ? Array
	-- pattern:gen: get -> res: ? integer
	-- pattern:gen: nxt -> res: ? integer
	-- pattern:gen: prv -> res: ? integer
	-- pattern:gen: putAt(inx: ? integer,exp: ? integer)
	-- pattern:gen: getAt(inx: ? integer) -> res: ? integer
	-- pattern:gen: putAtAt(inx1: ? integer,inx2: ? integer,exp: ? integer)
	-- pattern:gen: getAtAt(inx1: ? integer,inx2: ? integer) -> exp: ? integer
	-- pattern:gen: realPutAt(il: ? IntList,exp: ? integer)
	-- pattern:gen: realGetAt(il: ? IntList) -> exp: ? integer
	-- pattern:gen: forAll
	-- pattern:gen: forAllIndex
	-- pattern:gen: fill(v: ? integer)
	-- pattern:gen: zeroes
	-- pattern:gen: ones
	-- pattern:gen: sum -> s: ? integer
	-- pattern:gen: iadd(a: ? Array)
	-- pattern:gen: iminus(a: ? Array)
	-- pattern:gen: imult(a: ? Array)
	-- pattern:gen: idiv(a: ? Array)
	-- pattern:gen: equal(a: ? Array) -> b: ? boolean
	-- pattern:gen: countNonZero -> count: ? integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=616
	innerA  2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L304:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1 := ranges.first:IS-empty: staticOff: 0
	-- Invocation:gen: R1 := ranges.first
	-- Invocation:loadOrigin: R1 := ranges.first
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := ranges.first
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: ranges.first:IS-empty: staticOff: 0
	-- Invocation:gen: ranges.first
	-- Invocation:loadOrigin: ranges.first
	-- Invocation:loadOrigin:scan: ranges
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ranges
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: first :E: ranges
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ranges
	rpushg 2 ranges
	-- Invocation:loadOrigin:scan: first
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: first -> r: ? Range
	invoke 572 0 first
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 R1
	-- ObjectGenerator:gen: super: R2 := ranges.second:IS-empty: staticOff: 0
	-- Invocation:gen: R2 := ranges.second
	-- Invocation:loadOrigin: R2 := ranges.second
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := ranges.second
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: ranges.second:IS-empty: staticOff: 0
	-- Invocation:gen: ranges.second
	-- Invocation:loadOrigin: ranges.second
	-- Invocation:loadOrigin:scan: ranges
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ranges
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: second :E: ranges
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ranges
	rpushg 2 ranges
	-- Invocation:loadOrigin:scan: second
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: second -> r: ? Range
	invoke 573 0 second
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 R2
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
	-- ObjectGenerator:gen: super: noof := R1.noof * R2.noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof := R1.noof * R2.noof
	-- Invocation:loadOrigin: noof := R1.noof * R2.noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := R1.noof * R2.noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.noof * R2.noof:IS-empty: staticOff: 0
	-- Invocation:gen: R1.noof * R2.noof
	-- Invocation:loadOrigin: R1.noof * R2.noof
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: noof :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: * R2.noof :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: * R2.noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof:IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof
	-- Invocation:loadOrigin: R2.noof
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 noof
	-- ObjectGenerator:gen: super: rep := Indexed(noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: rep := Indexed(noof,integer)
	-- Invocation:loadOrigin: rep := Indexed(noof,integer)
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Indexed(noof,integer)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Indexed(noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: Indexed(noof,integer)
	-- Invocation:loadOrigin: Indexed(noof,integer)
	-- Invocation:loadOrigin:scan: Indexed(noof,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(noof,integer)
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 3 noof
	-- ObjectGenerator:gen: super: integer:IS-empty: staticOff: 0
	-- Invocation:gen: integer
	-- Invocation:loadOrigin: integer
	-- Invocation:loadOrigin:scan: integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer(W: ? integer)
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 rep
	-- ObjectGenerator:gen: super: putint(ranges.first.low):IS-empty: staticOff: 0
	-- Invocation:gen: putint(ranges.first.low)
	-- Invocation:loadOrigin: putint(ranges.first.low)
	-- Invocation:loadOrigin:scan: putint(ranges.first.low)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(ranges.first.low)
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: ranges.first.low:IS-empty: staticOff: 0
	-- Invocation:gen: ranges.first.low
	-- Invocation:loadOrigin: ranges.first.low
	-- Invocation:loadOrigin:scan: ranges
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ranges
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: first :E: ranges
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ranges
	rpushg 2 ranges
	-- Invocation:loadOrigin:scan: first
	-- next not assign: low :E: first
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: first -> r: ? Range
	invoke 572 0 first
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: "..".print:IS-empty: staticOff: 0
	-- Invocation:gen: "..".print
	-- Invocation:loadOrigin: "..".print
	-- Invocation:loadOrigin:scan: ".."
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText ..
	-- next not assign: print :E: ".."
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: putint(ranges.first.upp):IS-empty: staticOff: 0
	-- Invocation:gen: putint(ranges.first.upp)
	-- Invocation:loadOrigin: putint(ranges.first.upp)
	-- Invocation:loadOrigin:scan: putint(ranges.first.upp)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(ranges.first.upp)
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: ranges.first.upp:IS-empty: staticOff: 0
	-- Invocation:gen: ranges.first.upp
	-- Invocation:loadOrigin: ranges.first.upp
	-- Invocation:loadOrigin:scan: ranges
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ranges
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: first :E: ranges
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ranges
	rpushg 2 ranges
	-- Invocation:loadOrigin:scan: first
	-- next not assign: upp :E: first
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: first -> r: ? Range
	invoke 572 0 first
	-- Invocation:loadOrigin:scan: upp
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
	-- ObjectGenerator:gen: super: putint(ranges.second.low):IS-empty: staticOff: 0
	-- Invocation:gen: putint(ranges.second.low)
	-- Invocation:loadOrigin: putint(ranges.second.low)
	-- Invocation:loadOrigin:scan: putint(ranges.second.low)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(ranges.second.low)
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: ranges.second.low:IS-empty: staticOff: 0
	-- Invocation:gen: ranges.second.low
	-- Invocation:loadOrigin: ranges.second.low
	-- Invocation:loadOrigin:scan: ranges
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ranges
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: second :E: ranges
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ranges
	rpushg 2 ranges
	-- Invocation:loadOrigin:scan: second
	-- next not assign: low :E: second
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: second -> r: ? Range
	invoke 573 0 second
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: "..".print:IS-empty: staticOff: 0
	-- Invocation:gen: "..".print
	-- Invocation:loadOrigin: "..".print
	-- Invocation:loadOrigin:scan: ".."
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText ..
	-- next not assign: print :E: ".."
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: putint(ranges.second.upp):IS-empty: staticOff: 0
	-- Invocation:gen: putint(ranges.second.upp)
	-- Invocation:loadOrigin: putint(ranges.second.upp)
	-- Invocation:loadOrigin:scan: putint(ranges.second.upp)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(ranges.second.upp)
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: ranges.second.upp:IS-empty: staticOff: 0
	-- Invocation:gen: ranges.second.upp
	-- Invocation:loadOrigin: ranges.second.upp
	-- Invocation:loadOrigin:scan: ranges
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ranges
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: second :E: ranges
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ranges
	rpushg 2 ranges
	-- Invocation:loadOrigin:scan: second
	-- next not assign: upp :E: second
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: second -> r: ? Range
	invoke 573 0 second
	-- Invocation:loadOrigin:scan: upp
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
	-- ObjectGenerator:gen: super: %inner Array:IS-empty: staticOff: 0
	-- Invocation:gen: %inner Array
	-- Invocation:loadOrigin: %inner Array
	-- Invocation:loadOrigin:scan: %inner Array
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner Array
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner Array
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  2
	rpopThisObj 
 L305:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 123
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L306:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: disable:IS-empty: staticOff: 0
	-- Invocation:gen: disable
	-- Invocation:loadOrigin: disable
	-- Invocation:loadOrigin:scan: disable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: disable
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: disable
	%disable 11
	-- ObjectGenerator:gen: super: res := 17:IS-empty: staticOff: 0
	-- Invocation:gen: res := 17
	-- Invocation:loadOrigin: res := 17
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 17
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 17:IS-empty: staticOff: 0
	-- Invocation:gen: 17
	-- Invocation:loadOrigin: 17
	-- Invocation:loadOrigin:scan: 17
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 17
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
	-- ObjectGenerator:gen: super: res := M.cmpAndSwap(1):IS-empty: staticOff: 0
	-- Invocation:gen: res := M.cmpAndSwap(1)
	-- Invocation:loadOrigin: res := M.cmpAndSwap(1)
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := M.cmpAndSwap(1)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: M.cmpAndSwap(1):IS-empty: staticOff: 0
	-- Invocation:gen: M.cmpAndSwap(1)
	-- Invocation:loadOrigin: M.cmpAndSwap(1)
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: cmpAndSwap(1) :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushc 2
	-- Invocation:loadOrigin:scan: cmpAndSwap(1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Function:invoke: 
	-- pattern:load: cmpAndSwap(V: ? integer) -> res: ? integer
	swap
	%cmpAndSwap 14
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
	-- ObjectGenerator:gen: super: %if res = 1 %then% 
    enable
    sleep(50)
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if res = 1 %then% 
    enable
    sleep(50)
    %restart loop
	-- Invocation:loadOrigin: %if res = 1 %then% 
    enable
    sleep(50)
    %restart loop
	-- Invocation:loadOrigin:scan: %if res = 1 %then% 
    enable
    sleep(50)
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if res = 1 %then% 
    enable
    sleep(50)
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if res = 1 %then% 
    enable
    sleep(50)
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: res = 1:IS-empty: staticOff: 0
	-- Invocation:gen: res = 1
	-- Invocation:loadOrigin: res = 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: = 1 :E: res
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: res
	pushg 1 res
	-- Invocation:loadOrigin:scan: = 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L308
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 799 0 #S#799
	rpop
 L308:
 L307:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 129
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L309:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inScheduler := 1:IS-empty: staticOff: 0
	-- Invocation:gen: inScheduler := 1
	-- Invocation:loadOrigin: inScheduler := 1
	-- Invocation:loadOrigin:scan: inScheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inScheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 inScheduler
	-- ObjectGenerator:gen: super: active := SQS.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: active := SQS.removeNext
	-- Invocation:loadOrigin: active := SQS.removeNext
	-- Invocation:loadOrigin:scan: active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: active
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := SQS.removeNext
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: SQS.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: SQS.removeNext
	-- Invocation:loadOrigin: SQS.removeNext
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: removeNext :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: removeNext
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: removeNext -> P: ? BasicProcess
	invoke 153 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 active
	-- ObjectGenerator:gen: super: %if active <> none %then% 
    active.status := P_status.ACTIVE
    inScheduler := 0
    active.attach(50)
    inScheduler := 1
    %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active):IS-empty: staticOff: 0
	-- Invocation:gen: %if active <> none %then% 
    active.status := P_status.ACTIVE
    inScheduler := 0
    active.attach(50)
    inScheduler := 1
    %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- Invocation:loadOrigin: %if active <> none %then% 
    active.status := P_status.ACTIVE
    inScheduler := 0
    active.attach(50)
    inScheduler := 1
    %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- Invocation:loadOrigin:scan: %if active <> none %then% 
    active.status := P_status.ACTIVE
    inScheduler := 0
    active.attach(50)
    inScheduler := 1
    %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if active <> none %then% 
    active.status := P_status.ACTIVE
    inScheduler := 0
    active.attach(50)
    inScheduler := 1
    %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if active <> none %then% 
    active.status := P_status.ACTIVE
    inScheduler := 0
    active.attach(50)
    inScheduler := 1
    %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: active <> none:IS-empty: staticOff: 0
	-- Invocation:gen: active <> none
	-- Invocation:loadOrigin: active <> none
	-- Invocation:loadOrigin:scan: active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: active
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: <> none :E: active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L311
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 800 0 #S#800
	rpop
 L311:
	-- ObjectGenerator:gen: super: %if SQS.isEmpty %then% 
    %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
    sch.dcr
    %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop %else% 
    %restart Loop:IS-empty: staticOff: 0
	pushThis 
	invoke 130 0 %if%then%%else%#S#130
	rpop
 L310:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loopX 134
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L312:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if main <> none %then% 
    main.resume %else% 
    sleep(100)
    %restart loopX:IS-empty: staticOff: 0
	pushThis 
	invoke 135 0 %if%then%%else%#S#135
	rpop
 L313:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 85
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 86 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L314:
	-- Include:gen: 
 L315:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 88
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 89 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L316:
	-- Include:gen: 
 L317:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#782 782
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L318:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: E := Element(elm):IS-empty: staticOff: 0
	-- Invocation:gen: E := Element(elm)
	-- Invocation:loadOrigin: E := Element(elm)
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := Element(elm)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Element(elm):IS-empty: staticOff: 0
	-- Invocation:gen: Element(elm)
	-- Invocation:loadOrigin: Element(elm)
	-- Invocation:loadOrigin:scan: Element(elm)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Element(elm)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: elm:IS-empty: staticOff: 0
	-- Invocation:gen: elm
	-- Invocation:loadOrigin: elm
	-- Invocation:loadOrigin:scan: elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elm
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Function:invoke: 
	-- pattern:load: Element(elm: ? Object) -> res: ? Element
	invoke 83 0 Element
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 E
	-- ObjectGenerator:gen: super: %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E:IS-empty: staticOff: 0
	pushThis 
	invoke 783 0 %if%then%%else%#S#783
	rpop
 L319:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scan#S#92 92
	rstore 4 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=92
	-- Invocation:loadOrigin: scan
	-- Invocation:loadOrigin:scan: scan
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: scan
	-- AdjustOrigin: 4
	rpushg 4 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  84
	rtnInner
	DO:
	doEventQ
	mvStack 
 L320:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if elm = current %then% 
    %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none:IS-empty: staticOff: 0
	-- Invocation:gen: %if elm = current %then% 
    %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- Invocation:loadOrigin: %if elm = current %then% 
    %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- Invocation:loadOrigin:scan: %if elm = current %then% 
    %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if elm = current %then% 
    %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if elm = current %then% 
    %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: elm = current:IS-empty: staticOff: 0
	-- Invocation:gen: elm = current
	-- Invocation:loadOrigin: elm = current
	-- Invocation:loadOrigin:scan: elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elm
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- next not assign: = current :E: elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Invocation:loadOrigin:scan: = current
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: current:IS-empty: staticOff: 0
	-- Invocation:gen: current
	-- Invocation:loadOrigin: current
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	rpushg 2 current
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	jmpFalse L322
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 784 0 #S#784
	rpop
 L322:
 L321:
	rtnInner
	end 1

	class #S#786 786
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L323:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: elm := last.elm:IS-empty: staticOff: 0
	-- Invocation:gen: elm := last.elm
	-- Invocation:loadOrigin: elm := last.elm
	-- Invocation:loadOrigin:scan: elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elm
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := last.elm
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: last.elm:IS-empty: staticOff: 0
	-- Invocation:gen: last.elm
	-- Invocation:loadOrigin: last.elm
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: elm :E: last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 elm
	-- ObjectGenerator:gen: super: last := last.pred:IS-empty: staticOff: 0
	-- Invocation:gen: last := last.pred
	-- Invocation:loadOrigin: last := last.pred
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := last.pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: last.pred:IS-empty: staticOff: 0
	-- Invocation:gen: last.pred
	-- Invocation:loadOrigin: last.pred
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: pred :E: last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
	-- ObjectGenerator:gen: super: %if last <> none %then% 
    last.succ := none %else% 
    head := none:IS-empty: staticOff: 0
	pushThis 
	invoke 787 0 %if%then%%else%#S#787
	rpop
 L324:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry#S#144 144
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=144
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  142
	rtnInner
	DO:
	doEventQ
	mvStack 
 L325:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := M + 1:IS-empty: staticOff: 0
	-- Invocation:gen: M := M + 1
	-- Invocation:loadOrigin: M := M + 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := M + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: M + 1:IS-empty: staticOff: 0
	-- Invocation:gen: M + 1
	-- Invocation:loadOrigin: M + 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 M
 L326:
	rtnInner
	end 1

	class entry#S#146 146
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=146
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  142
	rtnInner
	DO:
	doEventQ
	mvStack 
 L327:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := M - 1:IS-empty: staticOff: 0
	-- Invocation:gen: M := M - 1
	-- Invocation:loadOrigin: M := M - 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := M - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: M - 1:IS-empty: staticOff: 0
	-- Invocation:gen: M - 1
	-- Invocation:loadOrigin: M - 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: - 1 :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 M
 L328:
	rtnInner
	end 1

	class entry#S#148 148
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=148
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  142
	rtnInner
	DO:
	doEventQ
	mvStack 
 L329:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := M > 0:IS-empty: staticOff: 0
	-- Invocation:gen: B := M > 0
	-- Invocation:loadOrigin: B := M > 0
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := M > 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: M > 0:IS-empty: staticOff: 0
	-- Invocation:gen: M > 0
	-- Invocation:loadOrigin: M > 0
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: > 0 :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: > 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: > V: ? integer -> B: ? Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L330:
	rtnInner
	end 1

	class #S#805 805
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L331:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('V'):IS-empty: staticOff: 0
	-- Invocation:gen: put('V')
	-- Invocation:loadOrigin: put('V')
	-- Invocation:loadOrigin:scan: put('V')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('V')
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 'V':IS-empty: staticOff: 0
	-- Invocation:gen: 'V'
	-- Invocation:loadOrigin: 'V'
	-- Invocation:loadOrigin:scan: 'V'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 86
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L332:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry#S#154 154
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=154
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L333:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: P := Q.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: P := Q.removeNext
	-- Invocation:loadOrigin: P := Q.removeNext
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := Q.removeNext
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Q.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: Q.removeNext
	-- Invocation:loadOrigin: Q.removeNext
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: removeNext :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: removeNext
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: removeNext -> elm: ? Object
	invoke 93 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 P
 L334:
	rtnInner
	end 1

	class entry#S#157 157
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=157
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L335:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := Q.isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: B := Q.isEmpty
	-- Invocation:loadOrigin: B := Q.isEmpty
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := Q.isEmpty
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Q.isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: Q.isEmpty
	-- Invocation:loadOrigin: Q.isEmpty
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: isEmpty :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: isEmpty
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: isEmpty -> B: ? Boolean
	invoke 94 0 isEmpty
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L336:
	rtnInner
	end 1

	class entry#S#162 162
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=162
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  150
	rtnInner
	DO:
	doEventQ
	mvStack 
 L337:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := W > 0:IS-empty: staticOff: 0
	-- Invocation:gen: B := W > 0
	-- Invocation:loadOrigin: B := W > 0
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := W > 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: W > 0:IS-empty: staticOff: 0
	-- Invocation:gen: W > 0
	-- Invocation:loadOrigin: W > 0
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: > 0 :E: W
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: > 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: > V: ? integer -> B: ? Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L338:
	rtnInner
	end 1

	class thenPart#SB#806 806
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L339:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 pos
 L340:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#807 807
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L341:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 pos
 L342:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#808 808
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L343:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 pos
 L344:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#809 809
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L345:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 pos
 L346:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#810 810
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L347:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: res := 9999999
	-- Invocation:loadOrigin: res := 9999999
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := 9999999
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: 9999999
	-- Invocation:loadOrigin: 9999999
	-- Invocation:loadOrigin:scan: 9999999
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 9999999
	-- OBS! Constant >= 2^16 is not implemented
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L348:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#811 811
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L349:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos + 1
	-- Invocation:loadOrigin: res := rep.%get pos + 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := rep.%get pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos + 1
	-- Invocation:loadOrigin: rep.%get pos + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: %get pos + 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos + 1
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L350:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#812 812
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L351:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: res := 9999999
	-- Invocation:loadOrigin: res := 9999999
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := 9999999
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: 9999999
	-- Invocation:loadOrigin: 9999999
	-- Invocation:loadOrigin:scan: 9999999
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 9999999
	-- OBS! Constant >= 2^16 is not implemented
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L352:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#813 813
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L353:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos - 1
	-- Invocation:loadOrigin: res := rep.%get pos - 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := rep.%get pos - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos - 1
	-- Invocation:loadOrigin: rep.%get pos - 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: %get pos - 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos - 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos - 1
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos - 1
	-- Invocation:loadOrigin: pos - 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: - 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L354:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#814 814
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L355:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 257
 L356:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#815 815
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L357:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: putint(rep.%get inx):IS-empty: staticOff: 0
	-- Invocation:gen: putint(rep.%get inx)
	-- Invocation:loadOrigin: putint(rep.%get inx)
	-- Invocation:loadOrigin:scan: putint(rep.%get inx)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(rep.%get inx)
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get inx
	-- Invocation:loadOrigin: rep.%get inx
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: %get inx :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: ", ".print:IS-empty: staticOff: 0
	-- Invocation:gen: ", ".print
	-- Invocation:loadOrigin: ", ".print
	-- Invocation:loadOrigin:scan: ", "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText , 
	-- next not assign: print :E: ", "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
 L358:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 233
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: P
	-- VarRef:gen: continue
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L359:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(100)
	-- Invocation:loadOrigin: sleep(100)
	-- Invocation:loadOrigin:scan: sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(100)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 100:IS-empty: staticOff: 0
	-- Invocation:gen: 100
	-- Invocation:loadOrigin: 100
	-- Invocation:loadOrigin:scan: 100
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 100
	-- Function:invoke: 
	-- pattern:load: sleep(V: ? integer)
	%sleep 15
	-- ObjectGenerator:gen: super: continue := false:IS-empty: staticOff: 0
	-- Invocation:gen: continue := false
	-- Invocation:loadOrigin: continue := false
	-- Invocation:loadOrigin:scan: continue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: continue
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := false
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: false:IS-empty: staticOff: 0
	-- Invocation:gen: false
	-- Invocation:loadOrigin: false
	-- Invocation:loadOrigin:scan: false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: false
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: False -> B: ? Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 continue
	-- ObjectGenerator:gen: super: Q.scan:singular:staticOff: 0
	pushThis 
	invoke 234 0 scan#S#234
	rpop
	-- ObjectGenerator:gen: super: %if continue %then% 
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if continue %then% 
    %restart loop
	-- Invocation:loadOrigin: %if continue %then% 
    %restart loop
	-- Invocation:loadOrigin:scan: %if continue %then% 
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if continue %then% 
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if continue %then% 
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: continue:IS-empty: staticOff: 0
	-- Invocation:gen: continue
	-- Invocation:loadOrigin: continue
	-- Invocation:loadOrigin:scan: continue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: continue
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: continue
	pushg 1 continue
	jmpFalse L361
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 834 0 #S#834
	rpop
 L361:
	-- ObjectGenerator:gen: super: Q.clear:IS-empty: staticOff: 0
	-- Invocation:gen: Q.clear
	-- Invocation:loadOrigin: Q.clear
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: clear :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: clear
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: clear
	invoke 95 0 clear
	rpop
 L360:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#240 240
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if cnt < 0 %then% 
    thisCore.main.active.status := P_status.WAITING
    SQS.addWaiting
    Q.insert(thisCore.main.active)
    theActive := thisCore.main.active
    M.free
    theActive.suspend %else% 
    M.free
	-- Invocation:loadOrigin:scan: %if cnt < 0 %then% 
    thisCore.main.active.status := P_status.WAITING
    SQS.addWaiting
    Q.insert(thisCore.main.active)
    theActive := thisCore.main.active
    M.free
    theActive.suspend %else% 
    M.free
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if cnt < 0 %then% 
    thisCore.main.active.status := P_status.WAITING
    SQS.addWaiting
    Q.insert(thisCore.main.active)
    theActive := thisCore.main.active
    M.free
    theActive.suspend %else% 
    M.free
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 8 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if cnt < 0 %then% 
    thisCore.main.active.status := P_status.WAITING
    SQS.addWaiting
    Q.insert(thisCore.main.active)
    theActive := thisCore.main.active
    M.free
    theActive.suspend %else% 
    M.free
	-- ObjectGenerator:gen: super: cnt < 0:IS-empty: staticOff: 0
	-- Invocation:gen: cnt < 0
	-- Invocation:loadOrigin: cnt < 0
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: < 0 :E: cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: < 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L362:
 L363:
	rtnInner
	end 1

	class %if%then%%else%#S#242 242
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if cnt <= 0 %then% 
    P := Q.removeNext
    P.status := P_status.ACTIVE
    SQS.insert(P)
    SQS.dcrWaiting
    M.free %else% 
    M.free
	-- Invocation:loadOrigin:scan: %if cnt <= 0 %then% 
    P := Q.removeNext
    P.status := P_status.ACTIVE
    SQS.insert(P)
    SQS.dcrWaiting
    M.free %else% 
    M.free
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if cnt <= 0 %then% 
    P := Q.removeNext
    P.status := P_status.ACTIVE
    SQS.insert(P)
    SQS.dcrWaiting
    M.free %else% 
    M.free
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 8 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if cnt <= 0 %then% 
    P := Q.removeNext
    P.status := P_status.ACTIVE
    SQS.insert(P)
    SQS.dcrWaiting
    M.free %else% 
    M.free
	-- ObjectGenerator:gen: super: cnt <= 0:IS-empty: staticOff: 0
	-- Invocation:gen: cnt <= 0
	-- Invocation:loadOrigin: cnt <= 0
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: <= 0 :E: cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: <= 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: <= V: ? integer -> B: ? Boolean
	52
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L364:
 L365:
	rtnInner
	end 1

	class loop 249
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L366:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner wait:IS-empty: staticOff: 0
	-- Invocation:gen: %inner wait
	-- Invocation:loadOrigin: %inner wait
	-- Invocation:loadOrigin:scan: %inner wait
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner wait
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner wait
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %if cond = false %then% 
    mutex.signal
    mutex.wait
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if cond = false %then% 
    mutex.signal
    mutex.wait
    %restart loop
	-- Invocation:loadOrigin: %if cond = false %then% 
    mutex.signal
    mutex.wait
    %restart loop
	-- Invocation:loadOrigin:scan: %if cond = false %then% 
    mutex.signal
    mutex.wait
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if cond = false %then% 
    mutex.signal
    mutex.wait
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if cond = false %then% 
    mutex.signal
    mutex.wait
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: cond = false:IS-empty: staticOff: 0
	-- Invocation:gen: cond = false
	-- Invocation:loadOrigin: cond = false
	-- Invocation:loadOrigin:scan: cond
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cond
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: = false :E: cond
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cond
	pushg 1 cond
	-- Invocation:loadOrigin:scan: = false
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: false:IS-empty: staticOff: 0
	-- Invocation:gen: false
	-- Invocation:loadOrigin: false
	-- Invocation:loadOrigin:scan: false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: false
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 8 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: False -> B: ? Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: = B: ? Boolean -> R: ? Boolean
	eq
	jmpFalse L368
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 839 0 #S#839
	rpop
 L368:
 L367:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#102 102
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% L %do% 
    e := %get inx
    T.%put e %at% inx
	-- Invocation:loadOrigin:scan: %for 1 %to% L %do% 
    e := %get inx
    T.%put e %at% inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% L %do% 
    e := %get inx
    T.%put e %at% inx
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% L %do% 
    e := %get inx
    T.%put e %at% inx
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: L:IS-empty: staticOff: 0
	-- Invocation:gen: L
	-- Invocation:loadOrigin: L
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L369:
 L370:
	rtnInner
	end 1

	class %for%to%%do%#S#103 103
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i
	-- Invocation:loadOrigin:scan: %for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: S.length:IS-empty: staticOff: 0
	-- Invocation:gen: S.length
	-- Invocation:loadOrigin: S.length
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L371:
 L372:
	rtnInner
	end 1

	class body#SB#790 790
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L373:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: current := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: current := %get inx
	-- Invocation:loadOrigin: current := %get inx
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 current
	-- ObjectGenerator:gen: super: %inner scan:IS-empty: staticOff: 0
	-- Invocation:gen: %inner scan
	-- Invocation:loadOrigin: %inner scan
	-- Invocation:loadOrigin:scan: %inner scan
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner scan
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner scan
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 2 origin
	rpushg 2 origin
	inner  1
	rpopThisObj 
 L374:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#791 791
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L375:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(%get inx):IS-empty: staticOff: 0
	-- Invocation:gen: put(%get inx)
	-- Invocation:loadOrigin: put(%get inx)
	-- Invocation:loadOrigin:scan: put(%get inx)
	-- Function:pushThis: 
	-- Function:loadOrigin: put(%get inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L376:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#792 792
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L377:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %leave loop:IS-empty: staticOff: 0
	-- Invocation:gen: %leave loop
	-- Invocation:loadOrigin: %leave loop
	-- Invocation:loadOrigin:scan: %leave loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave loop
	-- KeyWord:invoke: 
	-- pattern:load: %leave Obj: ? integer
	break 1 289
 L378:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#111 111
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% length %do% 
    c1 := %get inx
    c2 := S.%get inx
    %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- Invocation:loadOrigin:scan: %for 1 %to% length %do% 
    c1 := %get inx
    c2 := S.%get inx
    %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% length %do% 
    c1 := %get inx
    c2 := S.%get inx
    %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% length %do% 
    c1 := %get inx
    c2 := S.%get inx
    %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: length:IS-empty: staticOff: 0
	-- Invocation:gen: length
	-- Invocation:loadOrigin: length
	-- Invocation:loadOrigin:scan: length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: length
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 98 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L379:
 L380:
	rtnInner
	end 1

	class matchEq 114
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx
	-- VarRef:gen: c1
	-- VarRef:gen: c2
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 115 2 loop
	rpop
	-- ConsRef:gen: doit
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 116 3 doit
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L381:
	-- Include:gen: 
 L382:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#118 118
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if L1 < L2 %then% 
    L := L1 %else% 
    L := L2
	-- Invocation:loadOrigin:scan: %if L1 < L2 %then% 
    L := L1 %else% 
    L := L2
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if L1 < L2 %then% 
    L := L1 %else% 
    L := L2
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if L1 < L2 %then% 
    L := L1 %else% 
    L := L2
	-- ObjectGenerator:gen: super: L1 < L2:IS-empty: staticOff: 0
	-- Invocation:gen: L1 < L2
	-- Invocation:loadOrigin: L1 < L2
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 0
	-- next not assign: < L2 :E: L1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Invocation:loadOrigin:scan: < L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L2:IS-empty: staticOff: 0
	-- Invocation:gen: L2
	-- Invocation:loadOrigin: L2
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L383:
 L384:
	rtnInner
	end 1

	class first 561
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L385:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := head:IS-empty: staticOff: 0
	-- Invocation:gen: r := head
	-- Invocation:loadOrigin: r := head
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	pushg 1 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 r
 L386:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: r
	pushg 1 r
	rtn(D)
	end 1

	class second 562
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L387:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := tail.head:IS-empty: staticOff: 0
	-- Invocation:gen: r := tail.head
	-- Invocation:loadOrigin: r := tail.head
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := tail.head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: tail.head:IS-empty: staticOff: 0
	-- Invocation:gen: tail.head
	-- Invocation:loadOrigin: tail.head
	-- Invocation:loadOrigin:scan: tail
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: tail
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: head :E: tail
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: tail
	rpushg 2 tail
	-- Invocation:loadOrigin:scan: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	pushg 1 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 r
 L388:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: r
	pushg 1 r
	rtn(D)
	end 1

	class scan 563
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	-- VarRef:gen: L
	-- pattern:gen: loop
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L389:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := %this IntList:IS-empty: staticOff: 0
	-- Invocation:gen: L := %this IntList
	-- Invocation:loadOrigin: L := %this IntList
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this IntList
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this IntList:IS-empty: staticOff: 0
	-- Invocation:gen: %this IntList
	-- Invocation:loadOrigin: %this IntList
	-- Invocation:loadOrigin:scan: %this IntList
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this IntList
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this IntList
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 L
	-- ObjectGenerator:gen: super: current := head:IS-empty: staticOff: 0
	-- Invocation:gen: current := head
	-- Invocation:loadOrigin: current := head
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	pushg 1 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 current
	-- ObjectGenerator:gen: super: loop:IS-empty: staticOff: 0
	-- Invocation:gen: loop
	-- Invocation:loadOrigin: loop
	-- Invocation:loadOrigin:scan: loop
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: loop
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 564 0 loop
	rpop
 L390:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 565
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L391:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: len := 0:IS-empty: staticOff: 0
	-- Invocation:gen: len := 0
	-- Invocation:loadOrigin: len := 0
	-- Invocation:loadOrigin:scan: len
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: len
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 len
	-- ObjectGenerator:gen: super: scan:singular:staticOff: 0
	pushThis 
	invoke 566 0 scan#S#566
	rpop
 L392:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: len
	pushg 1 len
	rtn(D)
	end 1

	class check 568
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L393:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print:IS-empty: staticOff: 0
	-- Invocation:gen: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- Invocation:loadOrigin: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- Invocation:loadOrigin:scan: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if (inx < low) || (inx > upp) %then% 
    "index error in range".print
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: (inx < low) || (inx > upp):IS-empty: staticOff: 0
	-- Invocation:gen: (inx < low) || (inx > upp)
	-- Invocation:loadOrigin: (inx < low) || (inx > upp)
	-- Invocation:loadOrigin:scan: (inx < low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx < low)
	-- Invocation:loadOrigin: inx < low
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: < low :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: < low
	-- BE:loadOrigin:E: < low
	-- next not assign: || (inx > upp) :E: < low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	-- Invocation:loadOrigin:scan: || (inx > upp)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx > upp):IS-empty: staticOff: 0
	-- Invocation:gen: (inx > upp)
	-- Invocation:loadOrigin: (inx > upp)
	-- Invocation:loadOrigin:scan: (inx > upp)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx > upp)
	-- Invocation:loadOrigin: inx > upp
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: > upp :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: > upp
	-- BE:loadOrigin:E: > upp
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: upp:IS-empty: staticOff: 0
	-- Invocation:gen: upp
	-- Invocation:loadOrigin: upp
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Binary:invoke: 
	-- pattern:load: > V: ? integer -> B: ? Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: || B: ? Boolean -> R: ? Boolean
	63
	jmpFalse L395
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 910 0 #S#910
	rpop
 L395:
 L394:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 569
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L396:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: putint(low):IS-empty: staticOff: 0
	-- Invocation:gen: putint(low)
	-- Invocation:loadOrigin: putint(low)
	-- Invocation:loadOrigin:scan: putint(low)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(low)
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(':'):IS-empty: staticOff: 0
	-- Invocation:gen: put(':')
	-- Invocation:loadOrigin: put(':')
	-- Invocation:loadOrigin:scan: put(':')
	-- Function:pushThis: 
	-- Function:loadOrigin: put(':')
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: ':':IS-empty: staticOff: 0
	-- Invocation:gen: ':'
	-- Invocation:loadOrigin: ':'
	-- Invocation:loadOrigin:scan: ':'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 58
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: putint(upp):IS-empty: staticOff: 0
	-- Invocation:gen: putint(upp)
	-- Invocation:loadOrigin: putint(upp)
	-- Invocation:loadOrigin:scan: putint(upp)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(upp)
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: upp:IS-empty: staticOff: 0
	-- Invocation:gen: upp
	-- Invocation:loadOrigin: upp
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
 L397:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#911 911
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L398:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "range error\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "range error\n".print
	-- Invocation:loadOrigin: "range error\n".print
	-- Invocation:loadOrigin:scan: "range error\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText range error\n
	-- next not assign: print :E: "range error\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
 L399:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class empty 571
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L400:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: b := (head = none):IS-empty: staticOff: 0
	-- Invocation:gen: b := (head = none)
	-- Invocation:loadOrigin: b := (head = none)
	-- Invocation:loadOrigin:scan: b
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: b
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := (head = none)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (head = none):IS-empty: staticOff: 0
	-- Invocation:gen: (head = none)
	-- Invocation:loadOrigin: (head = none)
	-- Invocation:loadOrigin:scan: (head = none)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (head = none)
	-- Invocation:loadOrigin: head = none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: = none :E: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: = none
	-- BE:loadOrigin:E: = none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 b
	-- ObjectGenerator:gen: super: %inner empty:IS-empty: staticOff: 0
	-- Invocation:gen: %inner empty
	-- Invocation:loadOrigin: %inner empty
	-- Invocation:loadOrigin:scan: %inner empty
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner empty
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner empty
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L401:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: b
	pushg 1 b
	rtn(D)
	end 1

	class first 572
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L402:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := head:IS-empty: staticOff: 0
	-- Invocation:gen: r := head
	-- Invocation:loadOrigin: r := head
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 r
 L403:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: r
	rpushg 2 r
	rtn(D)
	end 1

	class second 573
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L404:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := tail.head:IS-empty: staticOff: 0
	-- Invocation:gen: r := tail.head
	-- Invocation:loadOrigin: r := tail.head
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := tail.head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: tail.head:IS-empty: staticOff: 0
	-- Invocation:gen: tail.head
	-- Invocation:loadOrigin: tail.head
	-- Invocation:loadOrigin:scan: tail
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: tail
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: head :E: tail
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: tail
	rpushg 3 tail
	-- Invocation:loadOrigin:scan: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 r
 L405:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: r
	rpushg 2 r
	rtn(D)
	end 1

	class scan 574
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	-- VarRef:gen: L
	-- pattern:gen: loop
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L406:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := %this RangeList:IS-empty: staticOff: 0
	-- Invocation:gen: L := %this RangeList
	-- Invocation:loadOrigin: L := %this RangeList
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this RangeList
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this RangeList:IS-empty: staticOff: 0
	-- Invocation:gen: %this RangeList
	-- Invocation:loadOrigin: %this RangeList
	-- Invocation:loadOrigin:scan: %this RangeList
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this RangeList
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this RangeList
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 L
	-- ObjectGenerator:gen: super: current := head:IS-empty: staticOff: 0
	-- Invocation:gen: current := head
	-- Invocation:loadOrigin: current := head
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 current
	-- ObjectGenerator:gen: super: loop:IS-empty: staticOff: 0
	-- Invocation:gen: loop
	-- Invocation:loadOrigin: loop
	-- Invocation:loadOrigin:scan: loop
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: loop
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 575 0 loop
	rpop
 L407:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 576
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L408:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: len := 0:IS-empty: staticOff: 0
	-- Invocation:gen: len := 0
	-- Invocation:loadOrigin: len := 0
	-- Invocation:loadOrigin:scan: len
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: len
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 len
	-- ObjectGenerator:gen: super: scan:singular:staticOff: 0
	pushThis 
	invoke 577 0 scan#S#577
	rpop
 L409:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: len
	pushg 1 len
	rtn(D)
	end 1

	class put 579
	pushThis 
	storeg 1 e
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L410:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: rep.%put e %at% pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put e %at% pos
	-- Invocation:loadOrigin: rep.%put e %at% pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %put e %at% pos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %put e %at% pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put e %at% pos
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: e:IS-empty: staticOff: 0
	-- Invocation:gen: e
	-- Invocation:loadOrigin: e
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 580 0 %if%then%%else%#S#580
	rpop
	-- ObjectGenerator:gen: super: res := %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: res := %this Array
	-- Invocation:loadOrigin: res := %this Array
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := %this Array
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: %this Array
	-- Invocation:loadOrigin: %this Array
	-- Invocation:loadOrigin:scan: %this Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Array
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Array
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 res
 L411:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class get 581
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L412:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos
	-- Invocation:loadOrigin: res := rep.%get pos
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := rep.%get pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos
	-- Invocation:loadOrigin: rep.%get pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: %get pos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
	-- ObjectGenerator:gen: super: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 582 0 %if%then%%else%#S#582
	rpop
 L413:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class nxt 583
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L414:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = noof %then% 
    res := 999999 %else% 
    res := rep.%get pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 584 0 %if%then%%else%#S#584
	rpop
 L415:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class prv 585
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L416:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = 1 %then% 
    res := 999999 %else% 
    res := rep.%get pos - 1:IS-empty: staticOff: 0
	pushThis 
	invoke 586 0 %if%then%%else%#S#586
	rpop
 L417:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class putAt 587
	pushThis 
	storeg 2 exp
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L418:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if R2 = none %then% 
    R1.check(inx)
    rep.%put exp %at% (inx - R1.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: %if R2 = none %then% 
    R1.check(inx)
    rep.%put exp %at% (inx - R1.low) + 1
	-- Invocation:loadOrigin: %if R2 = none %then% 
    R1.check(inx)
    rep.%put exp %at% (inx - R1.low) + 1
	-- Invocation:loadOrigin:scan: %if R2 = none %then% 
    R1.check(inx)
    rep.%put exp %at% (inx - R1.low) + 1
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if R2 = none %then% 
    R1.check(inx)
    rep.%put exp %at% (inx - R1.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if R2 = none %then% 
    R1.check(inx)
    rep.%put exp %at% (inx - R1.low) + 1
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: R2 = none:IS-empty: staticOff: 0
	-- Invocation:gen: R2 = none
	-- Invocation:loadOrigin: R2 = none
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: = none :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: = none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	jmpFalse L420
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 921 0 #S#921
	rpop
 L420:
 L419:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class getAt 588
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L421:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if R2 = none %then% 
    R1.check(inx)
    res := rep.%get (inx - R1.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: %if R2 = none %then% 
    R1.check(inx)
    res := rep.%get (inx - R1.low) + 1
	-- Invocation:loadOrigin: %if R2 = none %then% 
    R1.check(inx)
    res := rep.%get (inx - R1.low) + 1
	-- Invocation:loadOrigin:scan: %if R2 = none %then% 
    R1.check(inx)
    res := rep.%get (inx - R1.low) + 1
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if R2 = none %then% 
    R1.check(inx)
    res := rep.%get (inx - R1.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if R2 = none %then% 
    R1.check(inx)
    res := rep.%get (inx - R1.low) + 1
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: R2 = none:IS-empty: staticOff: 0
	-- Invocation:gen: R2 = none
	-- Invocation:loadOrigin: R2 = none
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: = none :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: = none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	jmpFalse L423
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 922 0 #S#922
	rpop
 L423:
 L422:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 2 res
	rtn(D)
	end 1

	class putAtAt 589
	pushThis 
	storeg 3 exp
	pushThis 
	storeg 2 inx2
	pushThis 
	storeg 1 inx1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L424:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos:IS-empty: staticOff: 0
	-- Invocation:gen: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- Invocation:loadOrigin: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- Invocation:loadOrigin:scan: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: R2 <> none:IS-empty: staticOff: 0
	-- Invocation:gen: R2 <> none
	-- Invocation:loadOrigin: R2 <> none
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: <> none :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L426
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 923 0 #S#923
	rpop
 L426:
 L425:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class getAtAt 590
	pushThis 
	storeg 2 inx2
	pushThis 
	storeg 1 inx1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L427:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- Invocation:loadOrigin: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- Invocation:loadOrigin:scan: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if R2 <> none %then% 
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: R2 <> none:IS-empty: staticOff: 0
	-- Invocation:gen: R2 <> none
	-- Invocation:loadOrigin: R2 <> none
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: <> none :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L429
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 924 0 #S#924
	rpop
 L429:
 L428:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: exp
	pushg 3 exp
	rtn(D)
	end 1

	class realPutAt 591
	pushThis 
	storeg 1 exp
	pushThis 
	rstoreg 2 il
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx1
	-- VarRef:gen: inx2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L430:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos:IS-empty: staticOff: 0
	-- Invocation:gen: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- Invocation:loadOrigin: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- Invocation:loadOrigin:scan: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    rep.%put exp %at% repPos
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: R2 <> none:IS-empty: staticOff: 0
	-- Invocation:gen: R2 <> none
	-- Invocation:loadOrigin: R2 <> none
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: <> none :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L432
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 925 0 #S#925
	rpop
 L432:
 L431:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class realGetAt 592
	pushThis 
	rstoreg 2 il
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx1
	-- VarRef:gen: inx2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L433:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- Invocation:loadOrigin: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- Invocation:loadOrigin:scan: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if R2 <> none %then% 
    inx1 := il.first
    inx2 := il.second
    R1.check(inx1)
    R2.check(inx2)
    repPos: ? integer
    repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
    exp := rep.%get repPos
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: R2 <> none:IS-empty: staticOff: 0
	-- Invocation:gen: R2 <> none
	-- Invocation:loadOrigin: R2 <> none
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: <> none :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L435
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 926 0 #S#926
	rpop
 L435:
 L434:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: exp
	pushg 1 exp
	rtn(D)
	end 1

	class forAll 593
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	-- pattern:gen: loop
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L436:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
	-- ObjectGenerator:gen: super: loop:IS-empty: staticOff: 0
	-- Invocation:gen: loop
	-- Invocation:loadOrigin: loop
	-- Invocation:loadOrigin:scan: loop
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: loop
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 594 0 loop
	rpop
 L437:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class forAllIndex 595
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx
	-- pattern:gen: loop
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L438:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
	-- ObjectGenerator:gen: super: inx := pos:IS-empty: staticOff: 0
	-- Invocation:gen: inx := pos
	-- Invocation:loadOrigin: inx := pos
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 inx
	-- ObjectGenerator:gen: super: loop:IS-empty: staticOff: 0
	-- Invocation:gen: loop
	-- Invocation:loadOrigin: loop
	-- Invocation:loadOrigin:scan: loop
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: loop
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 596 0 loop
	rpop
 L439:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class fill 597
	pushThis 
	storeg 1 v
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L440:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: forAllIndex:singular:staticOff: 0
	pushThis 
	invoke 598 0 forAllIndex#S#598
	rpop
 L441:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class zeroes 599
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L442:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: fill(0):IS-empty: staticOff: 0
	-- Invocation:gen: fill(0)
	-- Invocation:loadOrigin: fill(0)
	-- Invocation:loadOrigin:scan: fill(0)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: fill(0)
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Function:invoke: 
	-- pattern:load: fill(v: ? integer)
	invoke 597 0 fill
	rpop
 L443:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ones 600
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L444:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: fill(1):IS-empty: staticOff: 0
	-- Invocation:gen: fill(1)
	-- Invocation:loadOrigin: fill(1)
	-- Invocation:loadOrigin:scan: fill(1)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: fill(1)
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Function:invoke: 
	-- pattern:load: fill(v: ? integer)
	invoke 597 0 fill
	rpop
 L445:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class sum 601
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L446:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: s := 0:IS-empty: staticOff: 0
	-- Invocation:gen: s := 0
	-- Invocation:loadOrigin: s := 0
	-- Invocation:loadOrigin:scan: s
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: s
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 s
	-- ObjectGenerator:gen: super: forAll:singular:staticOff: 0
	pushThis 
	invoke 602 0 forAll#S#602
	rpop
 L447:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: s
	pushg 1 s
	rtn(D)
	end 1

	class iadd 603
	pushThis 
	rstoreg 2 a
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L448:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: forAll:singular:staticOff: 0
	pushThis 
	invoke 604 0 forAll#S#604
	rpop
 L449:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class iminus 605
	pushThis 
	rstoreg 2 a
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L450:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: forAll:singular:staticOff: 0
	pushThis 
	invoke 606 0 forAll#S#606
	rpop
 L451:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class imult 607
	pushThis 
	rstoreg 2 a
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L452:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: forAll:singular:staticOff: 0
	pushThis 
	invoke 608 0 forAll#S#608
	rpop
 L453:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class idiv 609
	pushThis 
	rstoreg 2 a
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L454:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: forAll:singular:staticOff: 0
	pushThis 
	invoke 610 0 forAll#S#610
	rpop
 L455:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class equal 611
	pushThis 
	rstoreg 2 a
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L456:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: b := false:IS-empty: staticOff: 0
	-- Invocation:gen: b := false
	-- Invocation:loadOrigin: b := false
	-- Invocation:loadOrigin:scan: b
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: b
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := false
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: false:IS-empty: staticOff: 0
	-- Invocation:gen: false
	-- Invocation:loadOrigin: false
	-- Invocation:loadOrigin:scan: false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: false
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: False -> B: ? Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 b
	-- ObjectGenerator:gen: super: forAll:singular:staticOff: 0
	pushThis 
	invoke 612 0 forAll#S#612
	rpop
 L457:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: b
	pushg 1 b
	rtn(D)
	end 1

	class countNonZero 613
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L458:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: count := 0:IS-empty: staticOff: 0
	-- Invocation:gen: count := 0
	-- Invocation:loadOrigin: count := 0
	-- Invocation:loadOrigin:scan: count
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: count
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 count
	-- ObjectGenerator:gen: super: forAll:singular:staticOff: 0
	pushThis 
	invoke 614 0 forAll#S#614
	rpop
 L459:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: count
	pushg 1 count
	rtn(D)
	end 1

	class print 616
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L460:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "Array(".print:IS-empty: staticOff: 0
	-- Invocation:gen: "Array(".print
	-- Invocation:loadOrigin: "Array(".print
	-- Invocation:loadOrigin:scan: "Array("
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Array(
	-- next not assign: print :E: "Array("
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: %inner print:IS-empty: staticOff: 0
	-- Invocation:gen: %inner print
	-- Invocation:loadOrigin: %inner print
	-- Invocation:loadOrigin:scan: %inner print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner print
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: "): ".print:IS-empty: staticOff: 0
	-- Invocation:gen: "): ".print
	-- Invocation:loadOrigin: "): ".print
	-- Invocation:loadOrigin:scan: "): "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText ): 
	-- next not assign: print :E: "): "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print:IS-empty: staticOff: 0
	pushThis 
	invoke 617 0 %for%to%%do%#S#617
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 66 0 newline
	rpop
 L461:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#799 799
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L462:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: enable:IS-empty: staticOff: 0
	-- Invocation:gen: enable
	-- Invocation:loadOrigin: enable
	-- Invocation:loadOrigin:scan: enable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: enable
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: enable
	%enable 12
	-- ObjectGenerator:gen: super: sleep(50):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(50)
	-- Invocation:loadOrigin: sleep(50)
	-- Invocation:loadOrigin:scan: sleep(50)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(50)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 50:IS-empty: staticOff: 0
	-- Invocation:gen: 50
	-- Invocation:loadOrigin: 50
	-- Invocation:loadOrigin:scan: 50
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 50
	-- Function:invoke: 
	-- pattern:load: sleep(V: ? integer)
	%sleep 15
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 306
 L463:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#800 800
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L464:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: active.status := P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: active.status := P_status.ACTIVE
	-- Invocation:loadOrigin: active.status := P_status.ACTIVE
	-- Invocation:loadOrigin:scan: active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: active
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: status :E: active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: status
	-- Invocation:loadOrigin:scan: := P_status.ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.ACTIVE
	-- Invocation:loadOrigin: P_status.ACTIVE
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: ACTIVE :E: P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
	-- ObjectGenerator:gen: super: inScheduler := 0:IS-empty: staticOff: 0
	-- Invocation:gen: inScheduler := 0
	-- Invocation:loadOrigin: inScheduler := 0
	-- Invocation:loadOrigin:scan: inScheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inScheduler
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 inScheduler
	-- ObjectGenerator:gen: super: active.attach(50):IS-empty: staticOff: 0
	-- Invocation:gen: active.attach(50)
	-- Invocation:loadOrigin: active.attach(50)
	-- Invocation:loadOrigin:scan: active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: active
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: attach(50) :E: active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: attach(50)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 50:IS-empty: staticOff: 0
	-- Invocation:gen: 50
	-- Invocation:loadOrigin: 50
	-- Invocation:loadOrigin:scan: 50
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 50
	-- Function:invoke: 
	-- pattern:load: attach(V: ? integer)
	%attach 10 D
	rpop
	-- ObjectGenerator:gen: super: inScheduler := 1:IS-empty: staticOff: 0
	-- Invocation:gen: inScheduler := 1
	-- Invocation:loadOrigin: inScheduler := 1
	-- Invocation:loadOrigin:scan: inScheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inScheduler
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 inScheduler
	-- ObjectGenerator:gen: super: %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active):IS-empty: staticOff: 0
	-- Invocation:gen: %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- Invocation:loadOrigin: %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- Invocation:loadOrigin:scan: %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if active.status = P_status.ACTIVE %then% 
    SQS.insert(active)
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: active.status = P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: active.status = P_status.ACTIVE
	-- Invocation:loadOrigin: active.status = P_status.ACTIVE
	-- Invocation:loadOrigin:scan: active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: active
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: status :E: active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: status
	-- next not assign: = P_status.ACTIVE :E: status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: status
	pushg 1 status
	-- Invocation:loadOrigin:scan: = P_status.ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.ACTIVE
	-- Invocation:loadOrigin: P_status.ACTIVE
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: ACTIVE :E: P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L466
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 990 0 #S#990
	rpop
 L466:
 L465:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#130 130
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if SQS.isEmpty %then% 
    %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
    sch.dcr
    %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop %else% 
    %restart Loop
	-- Invocation:loadOrigin:scan: %if SQS.isEmpty %then% 
    %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
    sch.dcr
    %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop %else% 
    %restart Loop
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if SQS.isEmpty %then% 
    %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
    sch.dcr
    %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop %else% 
    %restart Loop
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if SQS.isEmpty %then% 
    %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
    sch.dcr
    %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop %else% 
    %restart Loop
	-- ObjectGenerator:gen: super: SQS.isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: SQS.isEmpty
	-- Invocation:loadOrigin: SQS.isEmpty
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: isEmpty :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: isEmpty
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: isEmpty -> B: ? Boolean
	invoke 156 0 isEmpty
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L467:
 L468:
	rtnInner
	end 1

	class %if%then%%else%#S#135 135
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if main <> none %then% 
    main.resume %else% 
    sleep(100)
    %restart loopX
	-- Invocation:loadOrigin:scan: %if main <> none %then% 
    main.resume %else% 
    sleep(100)
    %restart loopX
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if main <> none %then% 
    main.resume %else% 
    sleep(100)
    %restart loopX
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if main <> none %then% 
    main.resume %else% 
    sleep(100)
    %restart loopX
	-- ObjectGenerator:gen: super: main <> none:IS-empty: staticOff: 0
	-- Invocation:gen: main <> none
	-- Invocation:loadOrigin: main <> none
	-- Invocation:loadOrigin:scan: main
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: main
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: <> none :E: main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L469:
 L470:
	rtnInner
	end 1

	class loop 86
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L471:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scan
    currentElement := currentElement.succ
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scan
    currentElement := currentElement.succ
    %restart loop
	-- Invocation:loadOrigin: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scan
    currentElement := currentElement.succ
    %restart loop
	-- Invocation:loadOrigin:scan: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scan
    currentElement := currentElement.succ
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scan
    currentElement := currentElement.succ
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if currentElement <> none %then% 
    current := currentElement.elm
    %inner scan
    currentElement := currentElement.succ
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: currentElement <> none:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement <> none
	-- Invocation:loadOrigin: currentElement <> none
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: <> none :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L473
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 780 0 #S#780
	rpop
 L473:
 L472:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 89
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L474:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scanFromLast
    currentElement := currentElement.pred
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scanFromLast
    currentElement := currentElement.pred
    %restart loop
	-- Invocation:loadOrigin: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scanFromLast
    currentElement := currentElement.pred
    %restart loop
	-- Invocation:loadOrigin:scan: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scanFromLast
    currentElement := currentElement.pred
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if currentElement <> none %then% 
    current := currentElement.elm
    %inner scanFromLast
    currentElement := currentElement.pred
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if currentElement <> none %then% 
    current := currentElement.elm
    %inner scanFromLast
    currentElement := currentElement.pred
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: currentElement <> none:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement <> none
	-- Invocation:loadOrigin: currentElement <> none
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: <> none :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L476
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 781 0 #S#781
	rpop
 L476:
 L475:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#783 783
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- Invocation:loadOrigin:scan: %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if head = none %then% 
    head := E
    last := head %else% 
    E.succ := head
    head.pred := E
    head := E
	-- ObjectGenerator:gen: super: head = none:IS-empty: staticOff: 0
	-- Invocation:gen: head = none
	-- Invocation:loadOrigin: head = none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: = none :E: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: = none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L477:
 L478:
	rtnInner
	end 1

	class #S#784 784
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L479:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none:IS-empty: staticOff: 0
	pushThis 
	invoke 785 0 %if%then%%else%#S#785
	rpop
 L480:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#787 787
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- Invocation:loadOrigin:scan: %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if last <> none %then% 
    last.succ := none %else% 
    head := none
	-- ObjectGenerator:gen: super: last <> none:IS-empty: staticOff: 0
	-- Invocation:gen: last <> none
	-- Invocation:loadOrigin: last <> none
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: <> none :E: last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L481:
 L482:
	rtnInner
	end 1

	class scan#S#234 234
	rstore 4 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=234
	-- Invocation:loadOrigin: Q.scan
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 4
	rpushg 4 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: scan :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: scan
	-- Unary:loadArgs: 
	topSuper  84
	rtnInner
	DO:
	doEventQ
	mvStack 
 L483:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: P := current:IS-empty: staticOff: 0
	-- Invocation:gen: P := current
	-- Invocation:loadOrigin: P := current
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- Invocation:loadOrigin:scan: := current
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: current:IS-empty: staticOff: 0
	-- Invocation:gen: current
	-- Invocation:loadOrigin: current
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	rpushg 2 current
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 P
	-- ObjectGenerator:gen: super: %if P.status <> P_status.TERMINATED %then% 
    continue := true:IS-empty: staticOff: 0
	-- Invocation:gen: %if P.status <> P_status.TERMINATED %then% 
    continue := true
	-- Invocation:loadOrigin: %if P.status <> P_status.TERMINATED %then% 
    continue := true
	-- Invocation:loadOrigin:scan: %if P.status <> P_status.TERMINATED %then% 
    continue := true
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if P.status <> P_status.TERMINATED %then% 
    continue := true
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if P.status <> P_status.TERMINATED %then% 
    continue := true
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: P.status <> P_status.TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: P.status <> P_status.TERMINATED
	-- Invocation:loadOrigin: P.status <> P_status.TERMINATED
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- next not assign: status :E: P
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Invocation:loadOrigin:scan: status
	-- next not assign: <> P_status.TERMINATED :E: status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: status
	pushg 1 status
	-- Invocation:loadOrigin:scan: <> P_status.TERMINATED
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: P_status.TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.TERMINATED
	-- Invocation:loadOrigin: P_status.TERMINATED
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 4 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: TERMINATED :E: P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: TERMINATED
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: TERMINATED
	pushg 3 TERMINATED
	-- Binary:invoke: 
	-- pattern:load: <> V: ? integer -> B: ? Boolean
	55
	jmpFalse L485
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 833 0 #S#833
	rpop
 L485:
 L484:
	rtnInner
	end 1

	class #S#834 834
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L486:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 359
 L487:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#835 835
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L488:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: thisCore.main.active.status := P_status.WAITING:IS-empty: staticOff: 0
	-- Invocation:gen: thisCore.main.active.status := P_status.WAITING
	-- Invocation:loadOrigin: thisCore.main.active.status := P_status.WAITING
	-- Invocation:loadOrigin:scan: thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: thisCore
	%thisCore 17
	-- next not assign: main :E: thisCore
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thisCore -> C: ? core
	-- Invocation:loadOrigin:scan: main
	-- next not assign: active :E: main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: active
	-- next not assign: status :E: active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: status
	-- Invocation:loadOrigin:scan: := P_status.WAITING
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: P_status.WAITING:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.WAITING
	-- Invocation:loadOrigin: P_status.WAITING
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: WAITING :E: P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: WAITING
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: WAITING
	pushg 2 WAITING
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
	-- ObjectGenerator:gen: super: SQS.addWaiting:IS-empty: staticOff: 0
	-- Invocation:gen: SQS.addWaiting
	-- Invocation:loadOrigin: SQS.addWaiting
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: addWaiting :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: addWaiting
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: addWaiting
	invoke 159 0 addWaiting
	rpop
	-- ObjectGenerator:gen: super: Q.insert(thisCore.main.active):IS-empty: staticOff: 0
	-- Invocation:gen: Q.insert(thisCore.main.active)
	-- Invocation:loadOrigin: Q.insert(thisCore.main.active)
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: insert(thisCore.main.active) :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 3 Q
	-- Invocation:loadOrigin:scan: insert(thisCore.main.active)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: thisCore.main.active:IS-empty: staticOff: 0
	-- Invocation:gen: thisCore.main.active
	-- Invocation:loadOrigin: thisCore.main.active
	-- Invocation:loadOrigin:scan: thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: thisCore
	%thisCore 17
	-- next not assign: main :E: thisCore
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thisCore -> C: ? core
	-- Invocation:loadOrigin:scan: main
	-- next not assign: active :E: main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 90 0 insert
	rpop
	-- ObjectGenerator:gen: super: theActive := thisCore.main.active:IS-empty: staticOff: 0
	-- Invocation:gen: theActive := thisCore.main.active
	-- Invocation:loadOrigin: theActive := thisCore.main.active
	-- Invocation:loadOrigin:scan: theActive
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: theActive
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := thisCore.main.active
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: thisCore.main.active:IS-empty: staticOff: 0
	-- Invocation:gen: thisCore.main.active
	-- Invocation:loadOrigin: thisCore.main.active
	-- Invocation:loadOrigin:scan: thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: thisCore
	%thisCore 17
	-- next not assign: main :E: thisCore
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thisCore -> C: ? core
	-- Invocation:loadOrigin:scan: main
	-- next not assign: active :E: main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 theActive
	-- ObjectGenerator:gen: super: M.free:IS-empty: staticOff: 0
	-- Invocation:gen: M.free
	-- Invocation:loadOrigin: M.free
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
	-- ObjectGenerator:gen: super: theActive.suspend:IS-empty: staticOff: 0
	-- Invocation:gen: theActive.suspend
	-- Invocation:loadOrigin: theActive.suspend
	-- Invocation:loadOrigin:scan: theActive
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: theActive
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- next not assign: suspend :E: theActive
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: theActive
	rpushg 2 theActive
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
 L489:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#836 836
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L490:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M.free:IS-empty: staticOff: 0
	-- Invocation:gen: M.free
	-- Invocation:loadOrigin: M.free
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L491:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#837 837
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L492:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: P := Q.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: P := Q.removeNext
	-- Invocation:loadOrigin: P := Q.removeNext
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := Q.removeNext
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: Q.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: Q.removeNext
	-- Invocation:loadOrigin: Q.removeNext
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: removeNext :E: Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 3 Q
	-- Invocation:loadOrigin:scan: removeNext
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: removeNext -> elm: ? Object
	invoke 93 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 P
	-- ObjectGenerator:gen: super: P.status := P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: P.status := P_status.ACTIVE
	-- Invocation:loadOrigin: P.status := P_status.ACTIVE
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- next not assign: status :E: P
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Invocation:loadOrigin:scan: status
	-- Invocation:loadOrigin:scan: := P_status.ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.ACTIVE
	-- Invocation:loadOrigin: P_status.ACTIVE
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: ACTIVE :E: P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
	-- ObjectGenerator:gen: super: SQS.insert(P):IS-empty: staticOff: 0
	-- Invocation:gen: SQS.insert(P)
	-- Invocation:loadOrigin: SQS.insert(P)
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: insert(P) :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: P:IS-empty: staticOff: 0
	-- Invocation:gen: P
	-- Invocation:loadOrigin: P
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 152 0 insert
	rpop
	-- ObjectGenerator:gen: super: SQS.dcrWaiting:IS-empty: staticOff: 0
	-- Invocation:gen: SQS.dcrWaiting
	-- Invocation:loadOrigin: SQS.dcrWaiting
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: dcrWaiting :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: dcrWaiting
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: dcrWaiting
	invoke 160 0 dcrWaiting
	rpop
	-- ObjectGenerator:gen: super: M.free:IS-empty: staticOff: 0
	-- Invocation:gen: M.free
	-- Invocation:loadOrigin: M.free
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L493:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#838 838
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L494:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M.free:IS-empty: staticOff: 0
	-- Invocation:gen: M.free
	-- Invocation:loadOrigin: M.free
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 124 0 free
	rpop
 L495:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#839 839
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L496:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: mutex.signal:IS-empty: staticOff: 0
	-- Invocation:gen: mutex.signal
	-- Invocation:loadOrigin: mutex.signal
	-- Invocation:loadOrigin:scan: mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mutex
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: signal :E: mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: signal
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: signal
	invoke 241 0 signal
	rpop
	-- ObjectGenerator:gen: super: mutex.wait:IS-empty: staticOff: 0
	-- Invocation:gen: mutex.wait
	-- Invocation:loadOrigin: mutex.wait
	-- Invocation:loadOrigin:scan: mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mutex
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: wait :E: mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: wait
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: wait
	invoke 239 0 wait
	rpop
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 366
 L497:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#788 788
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L498:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: e := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: e := %get inx
	-- Invocation:loadOrigin: e := %get inx
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 e
	-- ObjectGenerator:gen: super: T.%put e %at% inx:IS-empty: staticOff: 0
	-- Invocation:gen: T.%put e %at% inx
	-- Invocation:loadOrigin: T.%put e %at% inx
	-- Invocation:loadOrigin:scan: T
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: T
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- next not assign: %put e %at% inx :E: T
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: %put e %at% inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put e %at% inx
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: e:IS-empty: staticOff: 0
	-- Invocation:gen: e
	-- Invocation:loadOrigin: e
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xstoreg 1 inx
 L499:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#789 789
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L500:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: e := S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: e := S.%get inx
	-- Invocation:loadOrigin: e := S.%get inx
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := S.%get inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: S.%get inx
	-- Invocation:loadOrigin: S.%get inx
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 e
	-- ObjectGenerator:gen: super: i := L + inx:IS-empty: staticOff: 0
	-- Invocation:gen: i := L + inx
	-- Invocation:loadOrigin: i := L + inx
	-- Invocation:loadOrigin:scan: i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: i
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := L + inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L + inx:IS-empty: staticOff: 0
	-- Invocation:gen: L + inx
	-- Invocation:loadOrigin: L + inx
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: + inx :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Invocation:loadOrigin:scan: + inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 i
	-- ObjectGenerator:gen: super: T.%put e %at% i:IS-empty: staticOff: 0
	-- Invocation:gen: T.%put e %at% i
	-- Invocation:loadOrigin: T.%put e %at% i
	-- Invocation:loadOrigin:scan: T
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: T
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- next not assign: %put e %at% i :E: T
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: %put e %at% i
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put e %at% i
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: e:IS-empty: staticOff: 0
	-- Invocation:gen: e
	-- Invocation:loadOrigin: e
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- name::gen: 
	-- ObjectGenerator:gen: super: i:IS-empty: staticOff: 0
	-- Invocation:gen: i
	-- Invocation:loadOrigin: i
	-- Invocation:loadOrigin:scan: i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: i
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 2 i
	xstoreg 1 inx
 L501:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#793 793
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L502:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: c1 := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: c1 := %get inx
	-- Invocation:loadOrigin: c1 := %get inx
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 c1
	-- ObjectGenerator:gen: super: c2 := S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: c2 := S.%get inx
	-- Invocation:loadOrigin: c2 := S.%get inx
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := S.%get inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: S.%get inx
	-- Invocation:loadOrigin: S.%get inx
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 c2
	-- ObjectGenerator:gen: super: %if c1 <> c2 %then% 
    B := false
    %leave loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- Invocation:loadOrigin: %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- Invocation:loadOrigin:scan: %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if c1 <> c2 %then% 
    B := false
    %leave loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if c1 <> c2 %then% 
    B := false
    %leave loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: c1 <> c2:IS-empty: staticOff: 0
	-- Invocation:gen: c1 <> c2
	-- Invocation:loadOrigin: c1 <> c2
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- next not assign: <> c2 :E: c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 1 c1
	-- Invocation:loadOrigin:scan: <> c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: c2:IS-empty: staticOff: 0
	-- Invocation:gen: c2
	-- Invocation:loadOrigin: c2
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 2 c2
	-- Binary:invoke: 
	-- pattern:load: <> V: ? char -> B: ? Boolean
	55
	jmpFalse L504
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 989 0 #S#989
	rpop
 L504:
 L503:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 115
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L505:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inx := inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx := inx + 1
	-- Invocation:loadOrigin: inx := inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := inx + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx + 1
	-- Invocation:loadOrigin: inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: + 1 :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 inx
	-- ObjectGenerator:gen: super: c1 := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: c1 := %get inx
	-- Invocation:loadOrigin: c1 := %get inx
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 c1
	-- ObjectGenerator:gen: super: c2 := S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: c2 := S.%get inx
	-- Invocation:loadOrigin: c2 := S.%get inx
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := S.%get inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: S.%get inx
	-- Invocation:loadOrigin: S.%get inx
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 c2
	-- ObjectGenerator:gen: super: %if c1 = c2 %then% 
    %if inx < L %then% %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if c1 = c2 %then% 
    %if inx < L %then% %restart loop
	-- Invocation:loadOrigin: %if c1 = c2 %then% 
    %if inx < L %then% %restart loop
	-- Invocation:loadOrigin:scan: %if c1 = c2 %then% 
    %if inx < L %then% %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if c1 = c2 %then% 
    %if inx < L %then% %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if c1 = c2 %then% 
    %if inx < L %then% %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: c1 = c2:IS-empty: staticOff: 0
	-- Invocation:gen: c1 = c2
	-- Invocation:loadOrigin: c1 = c2
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: = c2 :E: c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: = c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: c2:IS-empty: staticOff: 0
	-- Invocation:gen: c2
	-- Invocation:loadOrigin: c2
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	jmpFalse L507
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 794 0 #S#794
	rpop
 L507:
 L506:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 116
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L508:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq:IS-empty: staticOff: 0
	pushThis 
	invoke 117 0 %if%then%%else%#S#117
	rpop
 L509:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#797 797
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L510:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := L1:IS-empty: staticOff: 0
	-- Invocation:gen: L := L1
	-- Invocation:loadOrigin: L := L1
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := L1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L1:IS-empty: staticOff: 0
	-- Invocation:gen: L1
	-- Invocation:loadOrigin: L1
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
 L511:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#798 798
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L512:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := L2:IS-empty: staticOff: 0
	-- Invocation:gen: L := L2
	-- Invocation:loadOrigin: L := L2
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L2:IS-empty: staticOff: 0
	-- Invocation:gen: L2
	-- Invocation:loadOrigin: L2
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
 L513:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 564
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L514:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner scan:IS-empty: staticOff: 0
	-- Invocation:gen: %inner scan
	-- Invocation:loadOrigin: %inner scan
	-- Invocation:loadOrigin:scan: %inner scan
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner scan
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner scan
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- Invocation:loadOrigin: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- Invocation:loadOrigin:scan: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: L.tail <> none:IS-empty: staticOff: 0
	-- Invocation:gen: L.tail <> none
	-- Invocation:loadOrigin: L.tail <> none
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: tail :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: tail
	-- next not assign: <> none :E: tail
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: tail
	rpushg 2 tail
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L516
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 909 0 #S#909
	rpop
 L516:
 L515:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scan#S#566 566
	rstore 3 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=566
	-- Invocation:loadOrigin: scan
	-- Invocation:loadOrigin:scan: scan
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: scan
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  563
	rtnInner
	DO:
	doEventQ
	mvStack 
 L517:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: len := len + 1:IS-empty: staticOff: 0
	-- Invocation:gen: len := len + 1
	-- Invocation:loadOrigin: len := len + 1
	-- Invocation:loadOrigin:scan: len
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: len
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := len + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: len + 1:IS-empty: staticOff: 0
	-- Invocation:gen: len + 1
	-- Invocation:loadOrigin: len + 1
	-- Invocation:loadOrigin:scan: len
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: len
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 3 origin
	-- next not assign: + 1 :E: len
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: len
	pushg 1 len
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 len
 L518:
	rtnInner
	end 1

	class #S#910 910
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L519:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "index error in range".print:IS-empty: staticOff: 0
	-- Invocation:gen: "index error in range".print
	-- Invocation:loadOrigin: "index error in range".print
	-- Invocation:loadOrigin:scan: "index error in range"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText index error in range
	-- next not assign: print :E: "index error in range"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
 L520:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 575
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L521:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner scan:IS-empty: staticOff: 0
	-- Invocation:gen: %inner scan
	-- Invocation:loadOrigin: %inner scan
	-- Invocation:loadOrigin:scan: %inner scan
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner scan
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner scan
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- Invocation:loadOrigin: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- Invocation:loadOrigin:scan: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if L.tail <> none %then% 
    L := tail
    current := L.head
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: L.tail <> none:IS-empty: staticOff: 0
	-- Invocation:gen: L.tail <> none
	-- Invocation:loadOrigin: L.tail <> none
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: tail :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: tail
	-- next not assign: <> none :E: tail
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: tail
	rpushg 3 tail
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L523
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 912 0 #S#912
	rpop
 L523:
 L522:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scan#S#577 577
	rstore 4 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=577
	-- Invocation:loadOrigin: scan
	-- Invocation:loadOrigin:scan: scan
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: scan
	-- AdjustOrigin: 4
	rpushg 4 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  574
	rtnInner
	DO:
	doEventQ
	mvStack 
 L524:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: len := len + 1:IS-empty: staticOff: 0
	-- Invocation:gen: len := len + 1
	-- Invocation:loadOrigin: len := len + 1
	-- Invocation:loadOrigin:scan: len
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: len
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- Invocation:loadOrigin:scan: := len + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: len + 1:IS-empty: staticOff: 0
	-- Invocation:gen: len + 1
	-- Invocation:loadOrigin: len + 1
	-- Invocation:loadOrigin:scan: len
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: len
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- next not assign: + 1 :E: len
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: len
	pushg 1 len
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 len
 L525:
	rtnInner
	end 1

	class %if%then%%else%#S#580 580
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- Invocation:loadOrigin:scan: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- ObjectGenerator:gen: super: pos = rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: pos = rep.length
	-- Invocation:loadOrigin: pos = rep.length
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = rep.length :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: = rep.length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: rep.length
	-- Invocation:loadOrigin: rep.length
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 55 0 length
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L526:
 L527:
	rtnInner
	end 1

	class %if%then%%else%#S#582 582
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- Invocation:loadOrigin:scan: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1
	-- ObjectGenerator:gen: super: pos = rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: pos = rep.length
	-- Invocation:loadOrigin: pos = rep.length
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = rep.length :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: = rep.length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: rep.length
	-- Invocation:loadOrigin: rep.length
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 55 0 length
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L528:
 L529:
	rtnInner
	end 1

	class %if%then%%else%#S#584 584
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = noof %then% 
    res := 999999 %else% 
    res := rep.%get pos + 1
	-- Invocation:loadOrigin:scan: %if pos = noof %then% 
    res := 999999 %else% 
    res := rep.%get pos + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = noof %then% 
    res := 999999 %else% 
    res := rep.%get pos + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = noof %then% 
    res := 999999 %else% 
    res := rep.%get pos + 1
	-- ObjectGenerator:gen: super: pos = noof:IS-empty: staticOff: 0
	-- Invocation:gen: pos = noof
	-- Invocation:loadOrigin: pos = noof
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = noof :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: = noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L530:
 L531:
	rtnInner
	end 1

	class %if%then%%else%#S#586 586
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if pos = 1 %then% 
    res := 999999 %else% 
    res := rep.%get pos - 1
	-- Invocation:loadOrigin:scan: %if pos = 1 %then% 
    res := 999999 %else% 
    res := rep.%get pos - 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if pos = 1 %then% 
    res := 999999 %else% 
    res := rep.%get pos - 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if pos = 1 %then% 
    res := 999999 %else% 
    res := rep.%get pos - 1
	-- ObjectGenerator:gen: super: pos = 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos = 1
	-- Invocation:loadOrigin: pos = 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: = 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L532:
 L533:
	rtnInner
	end 1

	class #S#921 921
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L534:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1.check(inx):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx)
	-- Invocation:loadOrigin: R1.check(inx)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: rep.%put exp %at% (inx - R1.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put exp %at% (inx - R1.low) + 1
	-- Invocation:loadOrigin: rep.%put exp %at% (inx - R1.low) + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %put exp %at% (inx - R1.low) + 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %put exp %at% (inx - R1.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put exp %at% (inx - R1.low) + 1
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: exp:IS-empty: staticOff: 0
	-- Invocation:gen: exp
	-- Invocation:loadOrigin: exp
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 2 exp
	-- name::gen: 
	-- ObjectGenerator:gen: super: (inx - R1.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: (inx - R1.low) + 1
	-- Invocation:loadOrigin: (inx - R1.low) + 1
	-- Invocation:loadOrigin:scan: (inx - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx - R1.low)
	-- Invocation:loadOrigin: inx - R1.low
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R1.low :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: + 1 :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	xstoreg 1 inx
 L535:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#922 922
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L536:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1.check(inx):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx)
	-- Invocation:loadOrigin: R1.check(inx)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: res := rep.%get (inx - R1.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get (inx - R1.low) + 1
	-- Invocation:loadOrigin: res := rep.%get (inx - R1.low) + 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := rep.%get (inx - R1.low) + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get (inx - R1.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get (inx - R1.low) + 1
	-- Invocation:loadOrigin: rep.%get (inx - R1.low) + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %get (inx - R1.low) + 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get (inx - R1.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get (inx - R1.low) + 1
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (inx - R1.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: (inx - R1.low) + 1
	-- Invocation:loadOrigin: (inx - R1.low) + 1
	-- Invocation:loadOrigin:scan: (inx - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx - R1.low)
	-- Invocation:loadOrigin: inx - R1.low
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R1.low :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: + 1 :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 res
 L537:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#923 923
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: repPos
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L538:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1.check(inx1):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx1)
	-- Invocation:loadOrigin: R1.check(inx1)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx1:IS-empty: staticOff: 0
	-- Invocation:gen: inx1
	-- Invocation:loadOrigin: inx1
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx2:IS-empty: staticOff: 0
	-- Invocation:gen: inx2
	-- Invocation:loadOrigin: inx2
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (inx1 - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx1 - R1.low)
	-- Invocation:loadOrigin: inx1 - R1.low
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R1.low :E: inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (1 + inx2 - R2.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: 1 + inx2 - R2.low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: + inx2 - R2.low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: + inx2 - R2.low
	-- BE:loadOrigin:E: + inx2 - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx2 - R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 - R2.low
	-- Invocation:loadOrigin: inx2 - R2.low
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R2.low :E: inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 repPos
	-- ObjectGenerator:gen: super: rep.%put exp %at% repPos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put exp %at% repPos
	-- Invocation:loadOrigin: rep.%put exp %at% repPos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %put exp %at% repPos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %put exp %at% repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put exp %at% repPos
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: exp:IS-empty: staticOff: 0
	-- Invocation:gen: exp
	-- Invocation:loadOrigin: exp
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 3 exp
	-- name::gen: 
	-- ObjectGenerator:gen: super: repPos:IS-empty: staticOff: 0
	-- Invocation:gen: repPos
	-- Invocation:loadOrigin: repPos
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 1 repPos
	xstoreg 1 inx
 L539:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#924 924
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: repPos
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L540:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: R1.check(inx1):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx1)
	-- Invocation:loadOrigin: R1.check(inx1)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx1:IS-empty: staticOff: 0
	-- Invocation:gen: inx1
	-- Invocation:loadOrigin: inx1
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx2:IS-empty: staticOff: 0
	-- Invocation:gen: inx2
	-- Invocation:loadOrigin: inx2
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (inx1 - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx1 - R1.low)
	-- Invocation:loadOrigin: inx1 - R1.low
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R1.low :E: inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (1 + inx2 - R2.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: 1 + inx2 - R2.low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: + inx2 - R2.low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: + inx2 - R2.low
	-- BE:loadOrigin:E: + inx2 - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx2 - R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 - R2.low
	-- Invocation:loadOrigin: inx2 - R2.low
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R2.low :E: inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 repPos
	-- ObjectGenerator:gen: super: exp := rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: exp := rep.%get repPos
	-- Invocation:loadOrigin: exp := rep.%get repPos
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := rep.%get repPos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get repPos
	-- Invocation:loadOrigin: rep.%get repPos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %get repPos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get repPos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: repPos:IS-empty: staticOff: 0
	-- Invocation:gen: repPos
	-- Invocation:loadOrigin: repPos
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 1 repPos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 exp
 L541:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#925 925
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: repPos
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L542:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inx1 := il.first:IS-empty: staticOff: 0
	-- Invocation:gen: inx1 := il.first
	-- Invocation:loadOrigin: inx1 := il.first
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := il.first
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: il.first:IS-empty: staticOff: 0
	-- Invocation:gen: il.first
	-- Invocation:loadOrigin: il.first
	-- Invocation:loadOrigin:scan: il
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: il
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: first :E: il
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: il
	rpushg 2 il
	-- Invocation:loadOrigin:scan: first
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: first -> r: ? integer
	invoke 561 0 first
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 inx1
	-- ObjectGenerator:gen: super: inx2 := il.second:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 := il.second
	-- Invocation:loadOrigin: inx2 := il.second
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := il.second
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: il.second:IS-empty: staticOff: 0
	-- Invocation:gen: il.second
	-- Invocation:loadOrigin: il.second
	-- Invocation:loadOrigin:scan: il
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: il
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: second :E: il
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: il
	rpushg 2 il
	-- Invocation:loadOrigin:scan: second
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: second -> r: ? integer
	invoke 562 0 second
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 inx2
	-- ObjectGenerator:gen: super: R1.check(inx1):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx1)
	-- Invocation:loadOrigin: R1.check(inx1)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx1:IS-empty: staticOff: 0
	-- Invocation:gen: inx1
	-- Invocation:loadOrigin: inx1
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 2 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx2:IS-empty: staticOff: 0
	-- Invocation:gen: inx2
	-- Invocation:loadOrigin: inx2
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 3 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (inx1 - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx1 - R1.low)
	-- Invocation:loadOrigin: inx1 - R1.low
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R1.low :E: inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 2 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (1 + inx2 - R2.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: 1 + inx2 - R2.low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: + inx2 - R2.low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: + inx2 - R2.low
	-- BE:loadOrigin:E: + inx2 - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx2 - R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 - R2.low
	-- Invocation:loadOrigin: inx2 - R2.low
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R2.low :E: inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 3 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 repPos
	-- ObjectGenerator:gen: super: rep.%put exp %at% repPos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put exp %at% repPos
	-- Invocation:loadOrigin: rep.%put exp %at% repPos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %put exp %at% repPos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %put exp %at% repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put exp %at% repPos
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: exp:IS-empty: staticOff: 0
	-- Invocation:gen: exp
	-- Invocation:loadOrigin: exp
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 1 exp
	-- name::gen: 
	-- ObjectGenerator:gen: super: repPos:IS-empty: staticOff: 0
	-- Invocation:gen: repPos
	-- Invocation:loadOrigin: repPos
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 1 repPos
	xstoreg 1 inx
 L543:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#926 926
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: repPos
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L544:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inx1 := il.first:IS-empty: staticOff: 0
	-- Invocation:gen: inx1 := il.first
	-- Invocation:loadOrigin: inx1 := il.first
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := il.first
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: il.first:IS-empty: staticOff: 0
	-- Invocation:gen: il.first
	-- Invocation:loadOrigin: il.first
	-- Invocation:loadOrigin:scan: il
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: il
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: first :E: il
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: il
	rpushg 2 il
	-- Invocation:loadOrigin:scan: first
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: first -> r: ? integer
	invoke 561 0 first
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 inx1
	-- ObjectGenerator:gen: super: inx2 := il.second:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 := il.second
	-- Invocation:loadOrigin: inx2 := il.second
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := il.second
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: il.second:IS-empty: staticOff: 0
	-- Invocation:gen: il.second
	-- Invocation:loadOrigin: il.second
	-- Invocation:loadOrigin:scan: il
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: il
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: second :E: il
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: il
	rpushg 2 il
	-- Invocation:loadOrigin:scan: second
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: second -> r: ? integer
	invoke 562 0 second
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 inx2
	-- ObjectGenerator:gen: super: R1.check(inx1):IS-empty: staticOff: 0
	-- Invocation:gen: R1.check(inx1)
	-- Invocation:loadOrigin: R1.check(inx1)
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx1:IS-empty: staticOff: 0
	-- Invocation:gen: inx1
	-- Invocation:loadOrigin: inx1
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 2 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: inx2:IS-empty: staticOff: 0
	-- Invocation:gen: inx2
	-- Invocation:loadOrigin: inx2
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 3 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 568 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (inx1 - R1.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (inx1 - R1.low)
	-- Invocation:loadOrigin: inx1 - R1.low
	-- Invocation:loadOrigin:scan: inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R1.low :E: inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 2 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: (1 + inx2 - R2.low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: 1 + inx2 - R2.low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: + inx2 - R2.low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: + inx2 - R2.low
	-- BE:loadOrigin:E: + inx2 - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: inx2 - R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: inx2 - R2.low
	-- Invocation:loadOrigin: inx2 - R2.low
	-- Invocation:loadOrigin:scan: inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: - R2.low :E: inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 3 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 repPos
	-- ObjectGenerator:gen: super: exp := rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: exp := rep.%get repPos
	-- Invocation:loadOrigin: exp := rep.%get repPos
	-- Invocation:loadOrigin:scan: exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: exp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := rep.%get repPos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get repPos
	-- Invocation:loadOrigin: rep.%get repPos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %get repPos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get repPos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: repPos:IS-empty: staticOff: 0
	-- Invocation:gen: repPos
	-- Invocation:loadOrigin: repPos
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 1 repPos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 exp
 L545:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 594
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L546:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: current := rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: current := rep.%get pos
	-- Invocation:loadOrigin: current := rep.%get pos
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := rep.%get pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos
	-- Invocation:loadOrigin: rep.%get pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: %get pos :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 current
	-- ObjectGenerator:gen: super: %inner forAll:IS-empty: staticOff: 0
	-- Invocation:gen: %inner forAll
	-- Invocation:loadOrigin: %inner forAll
	-- Invocation:loadOrigin:scan: %inner forAll
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner forAll
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner forAll
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %if pos < noof %then% 
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if pos < noof %then% 
    %restart loop
	-- Invocation:loadOrigin: %if pos < noof %then% 
    %restart loop
	-- Invocation:loadOrigin:scan: %if pos < noof %then% 
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if pos < noof %then% 
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if pos < noof %then% 
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: pos < noof:IS-empty: staticOff: 0
	-- Invocation:gen: pos < noof
	-- Invocation:loadOrigin: pos < noof
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: < noof :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: < noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L548
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 927 0 #S#927
	rpop
 L548:
 L547:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 596
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L549:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner forAllIndex:IS-empty: staticOff: 0
	-- Invocation:gen: %inner forAllIndex
	-- Invocation:loadOrigin: %inner forAllIndex
	-- Invocation:loadOrigin:scan: %inner forAllIndex
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner forAllIndex
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner forAllIndex
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
	-- ObjectGenerator:gen: super: inx := pos:IS-empty: staticOff: 0
	-- Invocation:gen: inx := pos
	-- Invocation:loadOrigin: inx := pos
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 inx
	-- ObjectGenerator:gen: super: %if pos < noof %then% 
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if pos < noof %then% 
    %restart loop
	-- Invocation:loadOrigin: %if pos < noof %then% 
    %restart loop
	-- Invocation:loadOrigin:scan: %if pos < noof %then% 
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if pos < noof %then% 
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if pos < noof %then% 
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: pos < noof:IS-empty: staticOff: 0
	-- Invocation:gen: pos < noof
	-- Invocation:loadOrigin: pos < noof
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: < noof :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: < noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L551
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 928 0 #S#928
	rpop
 L551:
 L550:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class forAllIndex#S#598 598
	rstore 2 origin
	allocEventQ
	-- super forAllIndex
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=598
	-- Invocation:loadOrigin: forAllIndex
	-- Invocation:loadOrigin:scan: forAllIndex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAllIndex
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  595
	rtnInner
	DO:
	doEventQ
	mvStack 
 L552:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: rep.%put v %at% inx:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put v %at% inx
	-- Invocation:loadOrigin: rep.%put v %at% inx
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: %put v %at% inx :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %put v %at% inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put v %at% inx
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: v:IS-empty: staticOff: 0
	-- Invocation:gen: v
	-- Invocation:loadOrigin: v
	-- Invocation:loadOrigin:scan: v
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: v
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: v
	pushg 1 v
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	xstoreg 1 inx
 L553:
	rtnInner
	end 1

	class forAll#S#602 602
	rstore 2 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=602
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  593
	rtnInner
	DO:
	doEventQ
	mvStack 
 L554:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: s := s + current:IS-empty: staticOff: 0
	-- Invocation:gen: s := s + current
	-- Invocation:loadOrigin: s := s + current
	-- Invocation:loadOrigin:scan: s
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: s
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := s + current
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: s + current:IS-empty: staticOff: 0
	-- Invocation:gen: s + current
	-- Invocation:loadOrigin: s + current
	-- Invocation:loadOrigin:scan: s
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: s
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: + current :E: s
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: s
	pushg 1 s
	-- Invocation:loadOrigin:scan: + current
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: current:IS-empty: staticOff: 0
	-- Invocation:gen: current
	-- Invocation:loadOrigin: current
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	pushg 1 current
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 s
 L555:
	rtnInner
	end 1

	class forAll#S#604 604
	rstore 2 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=604
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  593
	rtnInner
	DO:
	doEventQ
	mvStack 
 L556:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(current + a.get):IS-empty: staticOff: 0
	-- Invocation:gen: put(current + a.get)
	-- Invocation:loadOrigin: put(current + a.get)
	-- Invocation:loadOrigin:scan: put(current + a.get)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: put(current + a.get)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: current + a.get:IS-empty: staticOff: 0
	-- Invocation:gen: current + a.get
	-- Invocation:loadOrigin: current + a.get
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: + a.get :E: current
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	pushg 1 current
	-- Invocation:loadOrigin:scan: + a.get
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: a.get:IS-empty: staticOff: 0
	-- Invocation:gen: a.get
	-- Invocation:loadOrigin: a.get
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: get :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 2 a
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get -> res: ? integer
	invoke 581 0 get
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: put(e: ? integer) -> res: ? Array
	invoke 579 0 put
	rpop
 L557:
	rtnInner
	end 1

	class forAll#S#606 606
	rstore 2 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=606
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  593
	rtnInner
	DO:
	doEventQ
	mvStack 
 L558:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(current - a.get):IS-empty: staticOff: 0
	-- Invocation:gen: put(current - a.get)
	-- Invocation:loadOrigin: put(current - a.get)
	-- Invocation:loadOrigin:scan: put(current - a.get)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: put(current - a.get)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: current - a.get:IS-empty: staticOff: 0
	-- Invocation:gen: current - a.get
	-- Invocation:loadOrigin: current - a.get
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: - a.get :E: current
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	pushg 1 current
	-- Invocation:loadOrigin:scan: - a.get
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: a.get:IS-empty: staticOff: 0
	-- Invocation:gen: a.get
	-- Invocation:loadOrigin: a.get
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: get :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 2 a
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get -> res: ? integer
	invoke 581 0 get
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Function:invoke: 
	-- pattern:load: put(e: ? integer) -> res: ? Array
	invoke 579 0 put
	rpop
 L559:
	rtnInner
	end 1

	class forAll#S#608 608
	rstore 2 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=608
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  593
	rtnInner
	DO:
	doEventQ
	mvStack 
 L560:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(current * a.get):IS-empty: staticOff: 0
	-- Invocation:gen: put(current * a.get)
	-- Invocation:loadOrigin: put(current * a.get)
	-- Invocation:loadOrigin:scan: put(current * a.get)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: put(current * a.get)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: current * a.get:IS-empty: staticOff: 0
	-- Invocation:gen: current * a.get
	-- Invocation:loadOrigin: current * a.get
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: * a.get :E: current
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	pushg 1 current
	-- Invocation:loadOrigin:scan: * a.get
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: a.get:IS-empty: staticOff: 0
	-- Invocation:gen: a.get
	-- Invocation:loadOrigin: a.get
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: get :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 2 a
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get -> res: ? integer
	invoke 581 0 get
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Function:invoke: 
	-- pattern:load: put(e: ? integer) -> res: ? Array
	invoke 579 0 put
	rpop
 L561:
	rtnInner
	end 1

	class forAll#S#610 610
	rstore 2 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=610
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  593
	rtnInner
	DO:
	doEventQ
	mvStack 
 L562:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(current / a.get):IS-empty: staticOff: 0
	-- Invocation:gen: put(current / a.get)
	-- Invocation:loadOrigin: put(current / a.get)
	-- Invocation:loadOrigin:scan: put(current / a.get)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: put(current / a.get)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: current / a.get:IS-empty: staticOff: 0
	-- Invocation:gen: current / a.get
	-- Invocation:loadOrigin: current / a.get
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: / a.get :E: current
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	pushg 1 current
	-- Invocation:loadOrigin:scan: / a.get
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: a.get:IS-empty: staticOff: 0
	-- Invocation:gen: a.get
	-- Invocation:loadOrigin: a.get
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: get :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 2 a
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get -> res: ? integer
	invoke 581 0 get
	-- Binary:invoke: 
	-- pattern:load: / V: ? integer -> R: ? integer
	67
	-- Function:invoke: 
	-- pattern:load: put(e: ? integer) -> res: ? Array
	invoke 579 0 put
	rpop
 L563:
	rtnInner
	end 1

	class forAll#S#612 612
	rstore 2 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=612
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  593
	rtnInner
	DO:
	doEventQ
	mvStack 
 L564:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if get = a.get %then% b := true:IS-empty: staticOff: 0
	-- Invocation:gen: %if get = a.get %then% b := true
	-- Invocation:loadOrigin: %if get = a.get %then% b := true
	-- Invocation:loadOrigin:scan: %if get = a.get %then% b := true
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if get = a.get %then% b := true
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if get = a.get %then% b := true
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: get = a.get:IS-empty: staticOff: 0
	-- Invocation:gen: get = a.get
	-- Invocation:loadOrigin: get = a.get
	-- Invocation:loadOrigin:scan: get
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: get
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: = a.get :E: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get -> res: ? integer
	invoke 581 0 get
	-- Invocation:loadOrigin:scan: = a.get
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: a.get:IS-empty: staticOff: 0
	-- Invocation:gen: a.get
	-- Invocation:loadOrigin: a.get
	-- Invocation:loadOrigin:scan: a
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: a
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: get :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 2 a
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get -> res: ? integer
	invoke 581 0 get
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L566
	-- ObjectGenerator:gen: super: b := true:IS-empty: staticOff: 0
	-- Invocation:gen: b := true
	-- Invocation:loadOrigin: b := true
	-- Invocation:loadOrigin:scan: b
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: b
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := true
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: true:IS-empty: staticOff: 0
	-- Invocation:gen: true
	-- Invocation:loadOrigin: true
	-- Invocation:loadOrigin:scan: true
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: true
	-- AdjustOrigin: 0
	-- on : 6
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: True -> B: ? Boolean
	invoke 24 0 True
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 b
 L566:
 L565:
	rtnInner
	end 1

	class forAll#S#614 614
	rstore 2 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=614
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  593
	rtnInner
	DO:
	doEventQ
	mvStack 
 L567:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if current = 0 %then% 
    count := count %else% 
    count := count + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 615 0 %if%then%%else%#S#615
	rpop
 L568:
	rtnInner
	end 1

	class %for%to%%do%#S#617 617
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- Invocation:loadOrigin:scan: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: rep.length:IS-empty: staticOff: 0
	-- Invocation:gen: rep.length
	-- Invocation:loadOrigin: rep.length
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 55 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L569:
 L570:
	rtnInner
	end 1

	class #S#990 990
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L571:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: SQS.insert(active):IS-empty: staticOff: 0
	-- Invocation:gen: SQS.insert(active)
	-- Invocation:loadOrigin: SQS.insert(active)
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: insert(active) :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(active)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: active:IS-empty: staticOff: 0
	-- Invocation:gen: active
	-- Invocation:loadOrigin: active
	-- Invocation:loadOrigin:scan: active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: active
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 152 0 insert
	rpop
 L572:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#801 801
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L573:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
	-- Invocation:loadOrigin: %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
	-- Invocation:loadOrigin:scan: %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if SQS.hasWaiting %then% 
    sleep(100)
    %restart Loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: SQS.hasWaiting:IS-empty: staticOff: 0
	-- Invocation:gen: SQS.hasWaiting
	-- Invocation:loadOrigin: SQS.hasWaiting
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: hasWaiting :E: SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: hasWaiting
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: hasWaiting -> B: ? boolean
	invoke 161 0 hasWaiting
	jmpFalse L575
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 991 0 #S#991
	rpop
 L575:
	-- ObjectGenerator:gen: super: sch.dcr:IS-empty: staticOff: 0
	-- Invocation:gen: sch.dcr
	-- Invocation:loadOrigin: sch.dcr
	-- Invocation:loadOrigin:scan: sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sch
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: dcr :E: sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: dcr
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: dcr
	invoke 145 0 dcr
	rpop
	-- ObjectGenerator:gen: super: %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop
	-- Invocation:loadOrigin: %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop
	-- Invocation:loadOrigin:scan: %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if sch.running %then% 
    sleep(50)
    sch.add
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: sch.running:IS-empty: staticOff: 0
	-- Invocation:gen: sch.running
	-- Invocation:loadOrigin: sch.running
	-- Invocation:loadOrigin:scan: sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sch
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: running :E: sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: running
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: running -> B: ? Boolean
	invoke 147 0 running
	jmpFalse L576
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 992 0 #S#992
	rpop
 L576:
 L574:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#802 802
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L577:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %restart Loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart Loop
	-- Invocation:loadOrigin: %restart Loop
	-- Invocation:loadOrigin:scan: %restart Loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart Loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart Loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 2 309
 L578:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#803 803
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L579:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: main.resume:IS-empty: staticOff: 0
	-- Invocation:gen: main.resume
	-- Invocation:loadOrigin: main.resume
	-- Invocation:loadOrigin:scan: main
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: main
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: resume :E: main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: resume
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: resume
	call(D)Resume
	rpop
 L580:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#804 804
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L581:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(100)
	-- Invocation:loadOrigin: sleep(100)
	-- Invocation:loadOrigin:scan: sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(100)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 100:IS-empty: staticOff: 0
	-- Invocation:gen: 100
	-- Invocation:loadOrigin: 100
	-- Invocation:loadOrigin:scan: 100
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 100
	-- Function:invoke: 
	-- pattern:load: sleep(V: ? integer)
	%sleep 15
	-- ObjectGenerator:gen: super: %restart loopX:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loopX
	-- Invocation:loadOrigin: %restart loopX
	-- Invocation:loadOrigin:scan: %restart loopX
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loopX
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loopX
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 2 312
 L582:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#780 780
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L583:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: current := currentElement.elm:IS-empty: staticOff: 0
	-- Invocation:gen: current := currentElement.elm
	-- Invocation:loadOrigin: current := currentElement.elm
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := currentElement.elm
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.elm:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.elm
	-- Invocation:loadOrigin: currentElement.elm
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: elm :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 current
	-- ObjectGenerator:gen: super: %inner scan:IS-empty: staticOff: 0
	-- Invocation:gen: %inner scan
	-- Invocation:loadOrigin: %inner scan
	-- Invocation:loadOrigin:scan: %inner scan
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner scan
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner scan
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: currentElement := currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement := currentElement.succ
	-- Invocation:loadOrigin: currentElement := currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := currentElement.succ
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ
	-- Invocation:loadOrigin: currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 471
 L584:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#781 781
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L585:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: current := currentElement.elm:IS-empty: staticOff: 0
	-- Invocation:gen: current := currentElement.elm
	-- Invocation:loadOrigin: current := currentElement.elm
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := currentElement.elm
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.elm:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.elm
	-- Invocation:loadOrigin: currentElement.elm
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: elm :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 current
	-- ObjectGenerator:gen: super: %inner scanFromLast:IS-empty: staticOff: 0
	-- Invocation:gen: %inner scanFromLast
	-- Invocation:loadOrigin: %inner scanFromLast
	-- Invocation:loadOrigin:scan: %inner scanFromLast
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner scanFromLast
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner scanFromLast
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: currentElement := currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement := currentElement.pred
	-- Invocation:loadOrigin: currentElement := currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := currentElement.pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred
	-- Invocation:loadOrigin: currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 474
 L586:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#981 981
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L587:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: head := E:IS-empty: staticOff: 0
	-- Invocation:gen: head := E
	-- Invocation:loadOrigin: head := E
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := E
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: E:IS-empty: staticOff: 0
	-- Invocation:gen: E
	-- Invocation:loadOrigin: E
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: E
	rpushg 3 E
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 head
	-- ObjectGenerator:gen: super: last := head:IS-empty: staticOff: 0
	-- Invocation:gen: last := head
	-- Invocation:loadOrigin: last := head
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L588:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#982 982
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L589:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: E.succ := head:IS-empty: staticOff: 0
	-- Invocation:gen: E.succ := head
	-- Invocation:loadOrigin: E.succ := head
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: succ :E: E
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: E
	rpushg 3 E
	-- Invocation:loadOrigin:scan: succ
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 succ
	-- ObjectGenerator:gen: super: head.pred := E:IS-empty: staticOff: 0
	-- Invocation:gen: head.pred := E
	-- Invocation:loadOrigin: head.pred := E
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: pred :E: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: pred
	-- Invocation:loadOrigin:scan: := E
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: E:IS-empty: staticOff: 0
	-- Invocation:gen: E
	-- Invocation:loadOrigin: E
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: E
	rpushg 3 E
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 pred
	-- ObjectGenerator:gen: super: head := E:IS-empty: staticOff: 0
	-- Invocation:gen: head := E
	-- Invocation:loadOrigin: head := E
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := E
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: E:IS-empty: staticOff: 0
	-- Invocation:gen: E
	-- Invocation:loadOrigin: E
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: E
	rpushg 3 E
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 head
 L590:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#785 785
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- Invocation:loadOrigin:scan: %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 6
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if currentElement.pred <> none %then% 
    currentElement.pred.succ := currentElement.succ
    %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred %else% 
    head := currentElement.succ
    %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- ObjectGenerator:gen: super: currentElement.pred <> none:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred <> none
	-- Invocation:loadOrigin: currentElement.pred <> none
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- next not assign: <> none :E: pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L591:
 L592:
	rtnInner
	end 1

	class thenPart#SB#987 987
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L593:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: last.succ := none:IS-empty: staticOff: 0
	-- Invocation:gen: last.succ := none
	-- Invocation:loadOrigin: last.succ := none
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: succ :E: last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: succ
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 succ
 L594:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#988 988
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L595:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: head := none:IS-empty: staticOff: 0
	-- Invocation:gen: head := none
	-- Invocation:loadOrigin: head := none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 head
 L596:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#833 833
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L597:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: continue := true:IS-empty: staticOff: 0
	-- Invocation:gen: continue := true
	-- Invocation:loadOrigin: continue := true
	-- Invocation:loadOrigin:scan: continue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: continue
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 4 origin
	-- Invocation:loadOrigin:scan: := true
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: true:IS-empty: staticOff: 0
	-- Invocation:gen: true
	-- Invocation:loadOrigin: true
	-- Invocation:loadOrigin:scan: true
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: true
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: True -> B: ? Boolean
	invoke 24 0 True
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 continue
 L598:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#989 989
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L599:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := false:IS-empty: staticOff: 0
	-- Invocation:gen: B := false
	-- Invocation:loadOrigin: B := false
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := false
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: false:IS-empty: staticOff: 0
	-- Invocation:gen: false
	-- Invocation:loadOrigin: false
	-- Invocation:loadOrigin:scan: false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: false
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 1 origin
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: False -> B: ? Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
	-- ObjectGenerator:gen: super: %leave loop:IS-empty: staticOff: 0
	-- Invocation:gen: %leave loop
	-- Invocation:loadOrigin: %leave loop
	-- Invocation:loadOrigin:scan: %leave loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave loop
	-- KeyWord:invoke: 
	-- pattern:load: %leave Obj: ? integer
	break 3 289
 L600:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#794 794
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L601:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if inx < L %then% %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if inx < L %then% %restart loop
	-- Invocation:loadOrigin: %if inx < L %then% %restart loop
	-- Invocation:loadOrigin:scan: %if inx < L %then% %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if inx < L %then% %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if inx < L %then% %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: inx < L:IS-empty: staticOff: 0
	-- Invocation:gen: inx < L
	-- Invocation:loadOrigin: inx < L
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: < L :E: inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: < L
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L:IS-empty: staticOff: 0
	-- Invocation:gen: L
	-- Invocation:loadOrigin: L
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L603
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 505
 L603:
 L602:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#117 117
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq
	-- Invocation:loadOrigin:scan: %if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 6
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq
	-- ObjectGenerator:gen: super: c1 = c2:IS-empty: staticOff: 0
	-- Invocation:gen: c1 = c2
	-- Invocation:loadOrigin: c1 = c2
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: = c2 :E: c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: = c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: c2:IS-empty: staticOff: 0
	-- Invocation:gen: c2
	-- Invocation:loadOrigin: c2
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L604:
 L605:
	rtnInner
	end 1

	class #S#909 909
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L606:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := tail:IS-empty: staticOff: 0
	-- Invocation:gen: L := tail
	-- Invocation:loadOrigin: L := tail
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := tail
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: tail:IS-empty: staticOff: 0
	-- Invocation:gen: tail
	-- Invocation:loadOrigin: tail
	-- Invocation:loadOrigin:scan: tail
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: tail
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: tail
	rpushg 2 tail
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 L
	-- ObjectGenerator:gen: super: current := L.head:IS-empty: staticOff: 0
	-- Invocation:gen: current := L.head
	-- Invocation:loadOrigin: current := L.head
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := L.head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L.head:IS-empty: staticOff: 0
	-- Invocation:gen: L.head
	-- Invocation:loadOrigin: L.head
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: head :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	pushg 1 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 current
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 514
 L607:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#912 912
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L608:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := tail:IS-empty: staticOff: 0
	-- Invocation:gen: L := tail
	-- Invocation:loadOrigin: L := tail
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := tail
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: tail:IS-empty: staticOff: 0
	-- Invocation:gen: tail
	-- Invocation:loadOrigin: tail
	-- Invocation:loadOrigin:scan: tail
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: tail
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: tail
	rpushg 3 tail
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 L
	-- ObjectGenerator:gen: super: current := L.head:IS-empty: staticOff: 0
	-- Invocation:gen: current := L.head
	-- Invocation:loadOrigin: current := L.head
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := L.head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L.head:IS-empty: staticOff: 0
	-- Invocation:gen: L.head
	-- Invocation:loadOrigin: L.head
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: head :E: L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 current
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 521
 L609:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#913 913
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L610:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
 L611:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#914 914
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L612:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
 L613:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#915 915
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L614:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
 L615:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#916 916
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L616:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 pos
 L617:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#917 917
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L618:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := 999999:IS-empty: staticOff: 0
	-- Invocation:gen: res := 999999
	-- Invocation:loadOrigin: res := 999999
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := 999999
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 999999:IS-empty: staticOff: 0
	-- Invocation:gen: 999999
	-- Invocation:loadOrigin: 999999
	-- Invocation:loadOrigin:scan: 999999
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 999999
	-- OBS! Constant >= 2^16 is not implemented
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L619:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#918 918
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L620:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos + 1
	-- Invocation:loadOrigin: res := rep.%get pos + 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := rep.%get pos + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos + 1
	-- Invocation:loadOrigin: rep.%get pos + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: %get pos + 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get pos + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos + 1
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L621:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#919 919
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L622:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := 999999:IS-empty: staticOff: 0
	-- Invocation:gen: res := 999999
	-- Invocation:loadOrigin: res := 999999
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := 999999
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 999999:IS-empty: staticOff: 0
	-- Invocation:gen: 999999
	-- Invocation:loadOrigin: 999999
	-- Invocation:loadOrigin:scan: 999999
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 999999
	-- OBS! Constant >= 2^16 is not implemented
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L623:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#920 920
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L624:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos - 1
	-- Invocation:loadOrigin: res := rep.%get pos - 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: := rep.%get pos - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos - 1
	-- Invocation:loadOrigin: rep.%get pos - 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: %get pos - 1 :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get pos - 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos - 1
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos - 1
	-- Invocation:loadOrigin: pos - 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: - 1 :E: pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 2 pos
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L625:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#927 927
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L626:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 546
 L627:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#928 928
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L628:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 549
 L629:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#615 615
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if current = 0 %then% 
    count := count %else% 
    count := count + 1
	-- Invocation:loadOrigin:scan: %if current = 0 %then% 
    count := count %else% 
    count := count + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if current = 0 %then% 
    count := count %else% 
    count := count + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 6
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if current = 0 %then% 
    count := count %else% 
    count := count + 1
	-- ObjectGenerator:gen: super: current = 0:IS-empty: staticOff: 0
	-- Invocation:gen: current = 0
	-- Invocation:loadOrigin: current = 0
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 0
	-- next not assign: = 0 :E: current
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	pushg 1 current
	-- Invocation:loadOrigin:scan: = 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L630:
 L631:
	rtnInner
	end 1

	class body#SB#931 931
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L632:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: putint(rep.%get inx):IS-empty: staticOff: 0
	-- Invocation:gen: putint(rep.%get inx)
	-- Invocation:loadOrigin: putint(rep.%get inx)
	-- Invocation:loadOrigin:scan: putint(rep.%get inx)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(rep.%get inx)
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: rep.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get inx
	-- Invocation:loadOrigin: rep.%get inx
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: %get inx :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 5 rep
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: ", ".print:IS-empty: staticOff: 0
	-- Invocation:gen: ", ".print
	-- Invocation:loadOrigin: ", ".print
	-- Invocation:loadOrigin:scan: ", "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText , 
	-- next not assign: print :E: ", "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 107 0 print
	rpop
 L633:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#991 991
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L634:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(100)
	-- Invocation:loadOrigin: sleep(100)
	-- Invocation:loadOrigin:scan: sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(100)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 100:IS-empty: staticOff: 0
	-- Invocation:gen: 100
	-- Invocation:loadOrigin: 100
	-- Invocation:loadOrigin:scan: 100
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 100
	-- Function:invoke: 
	-- pattern:load: sleep(V: ? integer)
	%sleep 15
	-- ObjectGenerator:gen: super: %restart Loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart Loop
	-- Invocation:loadOrigin: %restart Loop
	-- Invocation:loadOrigin:scan: %restart Loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart Loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart Loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 3 309
 L635:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#992 992
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L636:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(50):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(50)
	-- Invocation:loadOrigin: sleep(50)
	-- Invocation:loadOrigin:scan: sleep(50)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(50)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: 50:IS-empty: staticOff: 0
	-- Invocation:gen: 50
	-- Invocation:loadOrigin: 50
	-- Invocation:loadOrigin:scan: 50
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 50
	-- Function:invoke: 
	-- pattern:load: sleep(V: ? integer)
	%sleep 15
	-- ObjectGenerator:gen: super: sch.add:IS-empty: staticOff: 0
	-- Invocation:gen: sch.add
	-- Invocation:loadOrigin: sch.add
	-- Invocation:loadOrigin:scan: sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sch
	-- AdjustOrigin: 0
	-- on : 6
	rpushg 1 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: add :E: sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: add
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: add
	invoke 143 0 add
	rpop
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 3 309
 L637:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#983 983
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L638:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: currentElement.pred.succ := currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred.succ := currentElement.succ
	-- Invocation:loadOrigin: currentElement.pred.succ := currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- next not assign: succ :E: pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Invocation:loadOrigin:scan: succ
	-- Invocation:loadOrigin:scan: := currentElement.succ
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ
	-- Invocation:loadOrigin: currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 succ
	-- ObjectGenerator:gen: super: %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred:IS-empty: staticOff: 0
	pushThis 
	invoke 984 0 %if%then%%else%#S#984
	rpop
 L639:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#985 985
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L640:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: head := currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: head := currentElement.succ
	-- Invocation:loadOrigin: head := currentElement.succ
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := currentElement.succ
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ
	-- Invocation:loadOrigin: currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 head
	-- ObjectGenerator:gen: super: %if head <> none %then% 
    head.pred := none %else% 
    last := none:IS-empty: staticOff: 0
	pushThis 
	invoke 986 0 %if%then%%else%#S#986
	rpop
 L641:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#795 795
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L642:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := L1 <= L2:IS-empty: staticOff: 0
	-- Invocation:gen: B := L1 <= L2
	-- Invocation:loadOrigin: B := L1 <= L2
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := L1 <= L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L1 <= L2:IS-empty: staticOff: 0
	-- Invocation:gen: L1 <= L2
	-- Invocation:loadOrigin: L1 <= L2
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: <= L2 :E: L1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Invocation:loadOrigin:scan: <= L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: L2:IS-empty: staticOff: 0
	-- Invocation:gen: L2
	-- Invocation:loadOrigin: L2
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: <= V: ? integer -> B: ? Boolean
	52
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
	-- ObjectGenerator:gen: super: %leave matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: %leave matchEq
	-- Invocation:loadOrigin: %leave matchEq
	-- Invocation:loadOrigin:scan: %leave matchEq
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave matchEq
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave matchEq
	-- KeyWord:invoke: 
	-- pattern:load: %leave Obj: ? integer
	break 3 382
 L643:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#796 796
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L644:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := c1 < c2:IS-empty: staticOff: 0
	-- Invocation:gen: B := c1 < c2
	-- Invocation:loadOrigin: B := c1 < c2
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := c1 < c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: c1 < c2:IS-empty: staticOff: 0
	-- Invocation:gen: c1 < c2
	-- Invocation:loadOrigin: c1 < c2
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: < c2 :E: c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: < c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: c2:IS-empty: staticOff: 0
	-- Invocation:gen: c2
	-- Invocation:loadOrigin: c2
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: < V: ? char -> B: ? Boolean
	51
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
	-- ObjectGenerator:gen: super: %leave matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: %leave matchEq
	-- Invocation:loadOrigin: %leave matchEq
	-- Invocation:loadOrigin:scan: %leave matchEq
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave matchEq
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave matchEq
	-- KeyWord:invoke: 
	-- pattern:load: %leave Obj: ? integer
	break 3 382
 L645:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#929 929
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L646:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: count := count:IS-empty: staticOff: 0
	-- Invocation:gen: count := count
	-- Invocation:loadOrigin: count := count
	-- Invocation:loadOrigin:scan: count
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: count
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := count
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: count:IS-empty: staticOff: 0
	-- Invocation:gen: count
	-- Invocation:loadOrigin: count
	-- Invocation:loadOrigin:scan: count
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: count
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: count
	pushg 1 count
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 count
 L647:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#930 930
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L648:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: count := count + 1:IS-empty: staticOff: 0
	-- Invocation:gen: count := count + 1
	-- Invocation:loadOrigin: count := count + 1
	-- Invocation:loadOrigin:scan: count
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: count
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: := count + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: count + 1:IS-empty: staticOff: 0
	-- Invocation:gen: count + 1
	-- Invocation:loadOrigin: count + 1
	-- Invocation:loadOrigin:scan: count
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: count
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	-- next not assign: + 1 :E: count
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: count
	pushg 1 count
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 count
 L649:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#984 984
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred
	-- Invocation:loadOrigin:scan: %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 8
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if currentElement.succ <> none %then% 
    currentElement.succ.pred := currentElement.pred %else% 
    last := currentElement.pred
	-- ObjectGenerator:gen: super: currentElement.succ <> none:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ <> none
	-- Invocation:loadOrigin: currentElement.succ <> none
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- next not assign: <> none :E: succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L650:
 L651:
	rtnInner
	end 1

	class %if%then%%else%#S#986 986
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- Invocation:loadOrigin:scan: %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 8
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if head <> none %then% 
    head.pred := none %else% 
    last := none
	-- ObjectGenerator:gen: super: head <> none:IS-empty: staticOff: 0
	-- Invocation:gen: head <> none
	-- Invocation:loadOrigin: head <> none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- next not assign: <> none :E: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L652:
 L653:
	rtnInner
	end 1

	class thenPart#SB#1011 1011
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L654:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: currentElement.succ.pred := currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ.pred := currentElement.pred
	-- Invocation:loadOrigin: currentElement.succ.pred := currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- next not assign: pred :E: succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Invocation:loadOrigin:scan: pred
	-- Invocation:loadOrigin:scan: := currentElement.pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred
	-- Invocation:loadOrigin: currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 pred
 L655:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#1012 1012
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L656:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: last := currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: last := currentElement.pred
	-- Invocation:loadOrigin: last := currentElement.pred
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := currentElement.pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred
	-- Invocation:loadOrigin: currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L657:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#1013 1013
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L658:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: head.pred := none:IS-empty: staticOff: 0
	-- Invocation:gen: head.pred := none
	-- Invocation:loadOrigin: head.pred := none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- next not assign: pred :E: head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: pred
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 pred
 L659:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#1014 1014
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L660:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: last := none:IS-empty: staticOff: 0
	-- Invocation:gen: last := none
	-- Invocation:loadOrigin: last := none
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L661:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class main 1016
	pushThis 
	invoke 1 0 BETAworld
	stop
	end 0

	class EventProcessor 1017
	stop

	class ThreadStub 1018
	DO:
	mvStack 
	call(D)ThreadStub
	stop
	-- vdtAdd: inx=1 descInx=778
	-- vdtAdd: inx=1 descInx=806
	-- vdtAdd: inx=2 descInx=807
	-- vdtAdd: inx=1 descInx=808
	-- vdtAdd: inx=2 descInx=809
	-- vdtAdd: inx=1 descInx=810
	-- vdtAdd: inx=2 descInx=811
	-- vdtAdd: inx=1 descInx=812
	-- vdtAdd: inx=2 descInx=813
	-- vdtAdd: inx=1 descInx=815
	-- vdtAdd: inx=1 descInx=790
	-- vdtAdd: inx=1 descInx=791
	-- vdtAdd: inx=1 descInx=835
	-- vdtAdd: inx=2 descInx=836
	-- vdtAdd: inx=1 descInx=837
	-- vdtAdd: inx=2 descInx=838
	-- vdtAdd: inx=1 descInx=788
	-- vdtAdd: inx=1 descInx=789
	-- vdtAdd: inx=1 descInx=793
	-- vdtAdd: inx=1 descInx=797
	-- vdtAdd: inx=2 descInx=798
	-- vdtAdd: inx=1 descInx=801
	-- vdtAdd: inx=2 descInx=802
	-- vdtAdd: inx=1 descInx=803
	-- vdtAdd: inx=2 descInx=804
	-- vdtAdd: inx=1 descInx=981
	-- vdtAdd: inx=2 descInx=982
	-- vdtAdd: inx=1 descInx=987
	-- vdtAdd: inx=2 descInx=988
	-- vdtAdd: inx=1 descInx=913
	-- vdtAdd: inx=2 descInx=914
	-- vdtAdd: inx=1 descInx=915
	-- vdtAdd: inx=2 descInx=916
	-- vdtAdd: inx=1 descInx=917
	-- vdtAdd: inx=2 descInx=918
	-- vdtAdd: inx=1 descInx=919
	-- vdtAdd: inx=2 descInx=920
	-- vdtAdd: inx=1 descInx=931
	-- vdtAdd: inx=1 descInx=983
	-- vdtAdd: inx=2 descInx=985
	-- vdtAdd: inx=1 descInx=795
	-- vdtAdd: inx=2 descInx=796
	-- vdtAdd: inx=1 descInx=929
	-- vdtAdd: inx=2 descInx=930
	-- vdtAdd: inx=1 descInx=1011
	-- vdtAdd: inx=2 descInx=1012
	-- vdtAdd: inx=1 descInx=1013
	-- vdtAdd: inx=2 descInx=1014

Class BETAworld 1 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	pushthis 
6:	saveBETAworld
7:	mvStack
8:	pushthis 
9:	invoke 3 2 1
15:	rpop 
16:	pushthis 
17:	invoke 71 3 1
23:	rpop 
24:	pushthis 
25:	invoke 260 4 1
31:	rpop 
32:	rtnEventQ 0
doE: 
34:	mvStack
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class BETA 3 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class False 23 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 0
13:	storeg 1
15:	rtnEventQ 0
17:	setThisStack
18:	pushthis 
19:	pushg 1
21:	rtn D


Class True 24 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 1
13:	storeg 1
15:	rtnEventQ 0
17:	setThisStack
18:	pushthis 
19:	pushg 1
21:	rtn D


Class Object 33 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	call D
8:	innera 1
10:	rtnEventQ 1
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	innerP 1
17:	popThisObj
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class core 50 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Indexed 52 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	rtnEventQ 0
doE: 
11:	mvStack
12:	rtnEventQ 0
14:	setThisStack
15:	pushthis 
16:	rtn D


Class length 55 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	pushc 0
16:	xpushg 1
18:	storeg 1
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class %if%then%%else% 60 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 61 2 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class _L 61 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushg 1
15:	jmpFalse 26
18:	pushthis 
19:	invoke 775 0 1
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	sendv 2
31:	rpop 
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class cycle 62 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	innerP 1
15:	popThisObj
16:	jmp 12
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class %for%to%%do% 63 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	pushthis 
18:	pushg 1
20:	storeg 3
22:	pushthis 
23:	invoke 64 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class do 64 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 65 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 65 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	pushg 3
17:	pushthis 
18:	rpushg 1
20:	rpushg 1
22:	pushg 2
24:	le
25:	jmpFalse 36
28:	pushthis 
29:	invoke 776 0 1
35:	rpop 
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class newline 66 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 10
12:	%prim put 2
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class putint 67 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	pushthis 
10:	rpushg 1
12:	pushc 20
14:	pushc 0
16:	pushc 1
18:	allocIndexed 52 1
22:	pushthis 
23:	rstoreg 2
25:	rtnEventQ 1
doE: 
27:	doEventQ 
28:	mvStack
29:	pushthis 
30:	pushthis 
31:	pushg 1
33:	pushc 0
35:	lt
36:	storeg 3
38:	pushthis 
39:	pushg 3
41:	jmpFalse 53
44:	pushthis 
45:	pushc 0
47:	pushthis 
48:	pushg 1
50:	-
51:	storeg 1
53:	pushthis 
54:	invoke 68 0 0
60:	rpop 
61:	rtnEventQ 0
63:	setThisStack
64:	pushthis 
65:	rtn D


Class doit 68 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	invoke 69 2 1
13:	rpop 
14:	rtnEventQ 1
doE: 
16:	doEventQ 
17:	mvStack
18:	pushthis 
19:	rpushg 1
21:	pushg 3
23:	jmpFalse 30
26:	pushc 45
28:	%prim put 2
30:	pushthis 
31:	invoke 70 0 1
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class loop 69 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	pushthis 
16:	rpushg 1
18:	rpushg 1
20:	pushg 2
22:	pushc 1
24:	+
25:	storeg 2
27:	pushthis 
28:	rpushg 1
30:	rpushg 1
32:	rpushg 2
34:	pushthis 
35:	rpushg 1
37:	rpushg 1
39:	pushg 1
41:	pushc 10
43:	modd
44:	pushthis 
45:	rpushg 1
47:	rpushg 1
49:	pushg 2
51:	xstoreg 1
53:	pushthis 
54:	rpushg 1
56:	rpushg 1
58:	pushthis 
59:	rpushg 1
61:	rpushg 1
63:	pushg 1
65:	pushc 10
67:	idiv
68:	storeg 1
70:	pushthis 
71:	rpushg 1
73:	rpushg 1
75:	pushg 1
77:	pushc 0
79:	gt 
80:	jmpFalse 91
83:	pushthis 
84:	invoke 777 0 1
90:	rpop 
91:	rtnEventQ 0
93:	setThisStack
94:	pushthis 
95:	rtn D


Class %for%to%%do%#S#70 70 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	pushc 1
14:	pushthis 
15:	rpushg 2
17:	rpushg 1
19:	pushg 2
21:	toSuper 63
enterE: 
24:	rtnInner
doE: 
25:	mvStack
26:	rtnInner


Class LIB 71 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 72 2 1
13:	rpop 
14:	pushthis 
15:	invoke 167 3 1
21:	rpop 
22:	pushthis 
23:	invoke 73 4 1
29:	rpop 
30:	pushthis 
31:	invoke 172 5 1
37:	rpop 
38:	pushthis 
39:	invoke 228 7 1
45:	rpop 
46:	pushthis 
47:	invoke 235 8 1
53:	rpop 
54:	pushthis 
55:	invoke 96 10 1
61:	rpop 
62:	rtnEventQ 0
doE: 
64:	mvStack
65:	rtnEventQ 0
67:	setThisStack
68:	pushthis 
69:	rtn D


Class BasicSystem 72 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Containers 73 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 81 3 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class mQueue 81 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Queue 82 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Element 83 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushthis 
15:	rswap 
16:	rstoreg 3
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rpushg 3
24:	rtn D


Class scan 84 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	pushthis 
14:	rpushg 1
16:	rpushg 2
18:	rswap 
19:	rstoreg 3
21:	pushthis 
22:	invoke 85 0 1
28:	rpop 
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class do 85 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 86 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 86 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 3
17:	pushNone 
18:	57
19:	jmpFalse 30
22:	pushthis 
23:	invoke 780 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class scanFromLast 87 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	pushthis 
14:	rpushg 1
16:	rpushg 3
18:	rswap 
19:	rstoreg 3
21:	pushthis 
22:	invoke 88 0 1
28:	rpop 
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class do 88 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 89 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 89 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 3
17:	pushNone 
18:	57
19:	jmpFalse 30
22:	pushthis 
23:	invoke 781 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class insert 90 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushthis 
15:	rpushg 2
17:	pushNone 
18:	57
19:	storeg 1
21:	pushthis 
22:	pushg 1
24:	jmpFalse 35
27:	pushthis 
28:	invoke 782 0 1
34:	rpop 
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class remove 91 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	invoke 92 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class scan#S#92 92 4
allocE:
1:	rstore 4
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 4
8:	rpushg 1
10:	toSuper 84
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 4
19:	rpushg 2
21:	pushthis 
22:	rpushg 2
24:	req 
25:	jmpFalse 36
28:	pushthis 
29:	invoke 784 0 1
35:	rpop 
36:	rtnInner


Class removeNext 93 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 3
15:	pushNone 
16:	57
17:	jmpFalse 28
20:	pushthis 
21:	invoke 786 0 1
27:	rpop 
28:	rtnEventQ 0
30:	setThisStack
31:	pushthis 
32:	rpushg 2
34:	rtn D


Class isEmpty 94 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 2
16:	pushNone 
17:	req 
18:	storeg 1
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class clear 95 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushNone 
14:	rswap 
15:	rstoreg 2
17:	pushthis 
18:	rpushg 1
20:	pushNone 
21:	rswap 
22:	rstoreg 3
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	rtn D


Class String 96 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class String 97 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	rtnEventQ 0
doE: 
11:	mvStack
12:	rtnEventQ 0
14:	setThisStack
15:	pushthis 
16:	rtn D


Class length 98 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	pushc 0
16:	xpushg 1
18:	storeg 1
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class + 100 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushthis 
15:	rpushg 1
17:	invoke 98 0 0
23:	storeg 1
25:	pushthis 
26:	invoke 101 0 0
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	rpushg 3
39:	rtn D


Class doplus 101 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	rpushg 1
11:	rpushg 1
13:	rpushg 1
15:	pushthis 
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	rpushg 1
23:	rpushg 2
25:	invoke 98 0 0
31:	+
32:	pushc 0
34:	pushc 1
36:	allocIndexed 52 1
40:	pushthis 
41:	rstoreg 2
43:	rtnEventQ 1
doE: 
45:	doEventQ 
46:	mvStack
47:	pushthis 
48:	invoke 102 0 1
54:	rpop 
55:	pushthis 
56:	invoke 103 0 1
62:	rpop 
63:	pushthis 
64:	rpushg 1
66:	pushthis 
67:	rpushg 2
69:26
70:	118
71:	rswap 
72:	rstoreg 3
74:	rtnEventQ 0
76:	setThisStack
77:	pushthis 
78:	rtn D


Class %for%to%%do%#S#102 102 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	pushc 1
18:	pushthis 
19:	rpushg 2
21:	rpushg 1
23:	pushg 1
25:	toSuper 63
enterE: 
28:	rtnInner
doE: 
29:	mvStack
30:	rtnInner


Class %for%to%%do%#S#103 103 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	pushc 1
18:	pushthis 
19:	rpushg 2
21:	rpushg 1
23:	rpushg 2
25:	invoke 98 0 0
31:	toSuper 63
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class asLowerCase 104 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rpushg 2
15:	rtn D


Class scan 105 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	invoke 106 0 1
19:	rpop 
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class %for%to%%do%#S#106 106 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	pushc 1
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	invoke 98 0 0
27:	toSuper 63
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class print 107 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 108 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %for%to%%do%#S#108 108 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	pushc 1
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	invoke 98 0 0
27:	toSuper 63
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class = 109 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 110 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class loop 110 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	invoke 98 0 0
22:	storeg 3
24:	pushthis 
25:	pushg 3
27:	pushthis 
28:	rpushg 1
30:	rpushg 2
32:	invoke 98 0 0
38:	ne 
39:	jmpFalse 50
42:	pushthis 
43:	invoke 792 0 1
49:	rpop 
50:	pushthis 
51:	rpushg 1
53:	pushthis 
54:	rpushg 1
56:	rpushg 1
58:	rpushg 1
60:	rpushg 1
62:	invoke 24 0 0
68:	storeg 1
70:	pushthis 
71:	invoke 111 0 1
77:	rpop 
78:	rtnEventQ 0
80:	setThisStack
81:	pushthis 
82:	rtn D


Class %for%to%%do%#S#111 111 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	pushc 1
18:	pushthis 
19:	rpushg 2
21:	rpushg 1
23:	rpushg 1
25:	invoke 98 0 0
31:	toSuper 63
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class <= 112 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 113 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class loop 113 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	invoke 98 0 0
22:	storeg 2
24:	pushthis 
25:	pushthis 
26:	rpushg 1
28:	rpushg 2
30:	invoke 98 0 0
36:	storeg 3
38:	pushthis 
39:	pushthis 
40:	pushg 2
42:	storeg 1
44:	pushthis 
45:	invoke 118 0 1
51:	rpop 
52:	pushthis 
53:	invoke 114 0 1
59:	rpop 
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class matchEq 114 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 115 2 1
13:	rpop 
14:	pushthis 
15:	invoke 116 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class loop 115 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	pushg 1
18:	pushc 1
20:	+
21:	storeg 1
23:	pushthis 
24:	rpushg 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	rpushg 1
35:	pushthis 
36:	rpushg 1
38:	pushg 1
40:	xpushg 1
42:	storeg 2
44:	pushthis 
45:	rpushg 1
47:	pushthis 
48:	rpushg 1
50:	rpushg 1
52:	rpushg 1
54:	rpushg 2
56:	pushthis 
57:	rpushg 1
59:	pushg 1
61:	xpushg 1
63:	storeg 3
65:	pushthis 
66:	rpushg 1
68:	pushg 2
70:	pushthis 
71:	rpushg 1
73:	pushg 3
75:	eq 
76:	jmpFalse 87
79:	pushthis 
80:	invoke 794 0 1
86:	rpop 
87:	rtnEventQ 0
89:	setThisStack
90:	pushthis 
91:	rtn D


Class doit 116 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 117 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#117 117 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	rpushg 1
20:	pushthis 
21:	rpushg 3
23:	rpushg 1
25:	pushg 2
27:	pushthis 
28:	rpushg 3
30:	rpushg 1
32:	pushg 3
34:	eq 
35:	toSuper 60
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class %if%then%%else%#S#118 118 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	pushthis 
17:	rpushg 3
19:	pushg 2
21:	pushthis 
22:	rpushg 3
24:	pushg 3
26:	lt
27:	toSuper 60
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class BasicSystem 119 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushc 4
8:	pushthis 
9:	storeg 1
11:	pushthis 
12:	invoke 136 2 1
18:	rpop 
19:	pushthis 
20:	invoke 138 3 1
26:	rpop 
27:	pushthis 
28:	invoke 141 4 1
34:	rpop 
35:	pushthis 
36:	invoke 149 5 1
42:	rpop 
43:	pushthis 
44:	invoke 120 6 1
50:	rpop 
51:	pushthis 
52:	invoke 163 7 1
58:	rpop 
59:	innera 1
61:	rtnEventQ 1
doE: 
63:	doEventQ 
64:	mvStack
65:	pushthis 
66:	invoke 166 0 0
72:	rpop 
73:	inner 1
75:	pushthis 
76:	rpushg 2
78:	invoke 137 0 0
84:	rpop 
85:	rtnEventQ 0
87:	setThisStack
88:	pushthis 
89:	rtn D


Class Lock 120 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class init 121 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushc 0
15:	storeg 2
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class get 122 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 123 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 123 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	%prim disable 11
12:	pushthis 
13:	rpushg 1
15:	pushc 17
17:	storeg 1
19:	pushthis 
20:	rpushg 1
22:	pushthis 
23:	rpushg 1
25:	rpushg 1
27:	pushc 2
29:	pushc 1
31:	swap 
32:	%prim cmpAndSwap 14
34:	storeg 1
36:	pushthis 
37:	rpushg 1
39:	pushg 1
41:	pushc 1
43:	eq 
44:	jmpFalse 55
47:	pushthis 
48:	invoke 799 0 1
54:	rpop 
55:	rtnEventQ 0
57:	setThisStack
58:	pushthis 
59:	rtn D


Class free 124 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushc 0
15:	storeg 2
17:	%prim enable 12
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class BasicProcess 125 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	innera 2
11:	rtnEventQ 1
doE: 
13:	doEventQ 
14:	mvStack
15:	pushthis 
16:	susp 
17:	inner 2
19:	pushthis 
20:	pushthis 
21:	rpushg 1
23:	rpushg 3
25:	pushg 3
27:	storeg 1
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class start 126 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	pushthis 
16:	rpushg 1
18:	rpushg 1
20:	rpushg 3
22:	pushg 1
24:	storeg 1
26:	inner 1
28:	rtnEventQ 0
30:	setThisStack
31:	pushthis 
32:	rtn D


Class Scheduler 127 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	susp 
12:	pushthis 
13:	rpushg 1
15:	rpushg 4
17:	invoke 143 0 0
23:	rpop 
24:	pushthis 
25:	invoke 128 0 1
31:	rpop 
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class do 128 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 129 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 129 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	pushc 1
17:	storeg 1
19:	pushthis 
20:	rpushg 1
22:	rpushg 1
24:	pushthis 
25:	rpushg 1
27:	rpushg 1
29:	rpushg 1
31:	rpushg 5
33:	invoke 153 0 0
39:	rswap 
40:	rstoreg 2
42:	pushthis 
43:	rpushg 1
45:	rpushg 1
47:	rpushg 2
49:	pushNone 
50:	57
51:	jmpFalse 62
54:	pushthis 
55:	invoke 800 0 1
61:	rpop 
62:	pushthis 
63:	invoke 130 0 1
69:	rpop 
70:	rtnEventQ 0
72:	setThisStack
73:	pushthis 
74:	rtn D


Class %if%then%%else%#S#130 130 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	rpushg 1
25:	rpushg 1
27:	rpushg 5
29:	invoke 156 0 0
35:	toSuper 60
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class Core 131 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	susp 
12:	pushthis 
13:	invoke 133 0 1
19:	rpop 
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class attach 132 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	rpushg 1
16:	pushthis 
17:	rpushg 2
19:	rswap 
20:	rstoreg 2
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class do 133 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 134 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loopX 134 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 135 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#135 135 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	rpushg 1
25:	rpushg 2
27:	pushNone 
28:	57
29:	toSuper 60
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class cores 136 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class init 137 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	rpushg 1
18:	invoke 131 0 0
24:	rswap 
25:	rstoreg 2
27:	pushthis 
28:	rpushg 1
30:	rpushg 2
32:	%prim fork 13
34:	pushthis 
35:	rpushg 1
37:	pushthis 
38:	rpushg 1
40:	rpushg 1
42:	invoke 131 0 0
48:	rswap 
49:	rstoreg 3
51:	pushthis 
52:	rpushg 1
54:	rpushg 3
56:	%prim fork 13
58:	pushthis 
59:	rpushg 1
61:	pushthis 
62:	rpushg 1
64:	rpushg 1
66:	invoke 131 0 0
72:	rswap 
73:	rstoreg 4
75:	pushthis 
76:	rpushg 1
78:	rpushg 4
80:	%prim fork 13
82:	pushthis 
83:	rpushg 1
85:	pushthis 
86:	rpushg 1
88:	rpushg 1
90:	invoke 131 0 0
96:	rswap 
97:	rstoreg 5
99:	pushthis 
100:	rpushg 1
102:	rpushg 5
104:	%prim fork 13
106:	pushthis 
107:	pushthis 
108:	rpushg 1
110:	rpushg 1
112:	invoke 127 0 0
118:	rswap 
119:	rstoreg 2
121:	pushthis 
122:	rpushg 1
124:	rpushg 2
126:	pushthis 
127:	rpushg 2
129:	invoke 132 0 0
135:	rpop 
136:	pushthis 
137:	pushthis 
138:	rpushg 1
140:	rpushg 1
142:	invoke 127 0 0
148:	rswap 
149:	rstoreg 2
151:	pushthis 
152:	rpushg 1
154:	rpushg 3
156:	pushthis 
157:	rpushg 2
159:	invoke 132 0 0
165:	rpop 
166:	pushthis 
167:	pushthis 
168:	rpushg 1
170:	rpushg 1
172:	invoke 127 0 0
178:	rswap 
179:	rstoreg 2
181:	pushthis 
182:	rpushg 1
184:	rpushg 4
186:	pushthis 
187:	rpushg 2
189:	invoke 132 0 0
195:	rpop 
196:	pushthis 
197:	rpushg 1
199:	rpushg 5
201:	pushthis 
202:	rpushg 1
204:	rpushg 1
206:	invoke 127 0 0
212:	invoke 132 0 0
218:	rpop 
219:	rtnEventQ 0
221:	setThisStack
222:	pushthis 
223:	rtn D


Class P_status 138 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushc 1
8:	pushthis 
9:	storeg 1
11:	pushc 2
13:	pushthis 
14:	storeg 2
16:	pushc 3
18:	pushthis 
19:	storeg 3
21:	rtnEventQ 0
doE: 
23:	mvStack
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	rtn D


Class ProcessQueue 139 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 1
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 3
16:	rpushg 4
18:	rpushg 3
20:	toSuper 82
enterE: 
23:	rtnInner
doE: 
24:	mvStack
25:	rtnInner


Class display 140 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 81
12:	%prim put 2
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class sch 141 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 120 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class entry 142 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	rpushg 2
17:	invoke 122 0 1
23:	rpop 
24:	pushthis 
25:	innerP 1
27:	popThisObj
28:	pushthis 
29:	rpushg 1
31:	rpushg 2
33:	invoke 124 0 0
39:	rpop 
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class add 143 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 144 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class entry#S#144 144 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 142
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	pushthis 
22:	rpushg 2
24:	rpushg 1
26:	pushg 1
28:	pushc 1
30:	+
31:	storeg 1
33:	rtnInner


Class dcr 145 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 146 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class entry#S#146 146 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 142
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	pushthis 
22:	rpushg 2
24:	rpushg 1
26:	pushg 1
28:	pushc 1
30:	-
31:	storeg 1
33:	rtnInner


Class running 147 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 148 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class entry#S#148 148 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 142
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	pushthis 
20:	rpushg 2
22:	rpushg 1
24:	pushg 1
26:	pushc 0
28:	gt 
29:	storeg 1
31:	rtnInner


Class SQS 149 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 139 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 120 3 1
25:	rpop 
26:	rtnEventQ 0
doE: 
28:	mvStack
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class entry 150 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	rpushg 3
17:	invoke 122 0 1
23:	rpop 
24:	pushthis 
25:	rpushg 1
27:	pushthis 
28:	rpushg 1
30:	pushg 1
32:	pushc 1
34:	+
35:	storeg 1
37:	pushthis 
38:	rpushg 1
40:	pushg 1
42:	pushc 1
44:	gt 
45:	jmpFalse 56
48:	pushthis 
49:	invoke 805 0 1
55:	rpop 
56:	inner 1
58:	pushthis 
59:	rpushg 1
61:	pushthis 
62:	rpushg 1
64:	pushg 1
66:	pushc 1
68:	-
69:	storeg 1
71:	pushthis 
72:	rpushg 1
74:	rpushg 3
76:	invoke 124 0 0
82:	rpop 
83:	rtnEventQ 0
85:	setThisStack
86:	pushthis 
87:	rtn D


Class init 151 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 150
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 1
17:	pushc 0
19:	storeg 1
21:	rtnInner


Class insert 152 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 150
enterE: 
14:	rtnInner
doE: 
15:	doEventQ 
16:	mvStack
17:	pushthis 
18:	rpushg 1
20:	rpushg 2
22:	pushthis 
23:	rpushg 2
25:	invoke 90 0 0
31:	rpop 
32:	rtnInner


Class removeNext 153 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 154 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rpushg 2
24:	rtn D


Class entry#S#154 154 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 150
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	pushthis 
20:	rpushg 2
22:	rpushg 1
24:	rpushg 2
26:	invoke 93 0 0
32:	rswap 
33:	rstoreg 2
35:	rtnInner


Class remove 155 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 150
enterE: 
14:	rtnInner
doE: 
15:	doEventQ 
16:	mvStack
17:	pushthis 
18:	rpushg 1
20:	rpushg 2
22:	pushthis 
23:	rpushg 2
25:	invoke 91 0 0
31:	rpop 
32:	rtnInner


Class isEmpty 156 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 157 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class entry#S#157 157 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 150
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	pushthis 
20:	rpushg 2
22:	rpushg 1
24:	rpushg 2
26:	invoke 94 0 0
32:	storeg 1
34:	rtnInner


Class display 158 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 150
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 1
17:	rpushg 2
19:	invoke 140 0 0
25:	rpop 
26:	rtnInner


Class addWaiting 159 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 150
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 1
17:	pushthis 
18:	rpushg 1
20:	pushg 2
22:	pushc 1
24:	+
25:	storeg 2
27:	rtnInner


Class dcrWaiting 160 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 150
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 1
17:	pushthis 
18:	rpushg 1
20:	pushg 2
22:	pushc 1
24:	-
25:	storeg 2
27:	rtnInner


Class hasWaiting 161 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 162 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class entry#S#162 162 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 150
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	pushthis 
20:	rpushg 2
22:	rpushg 1
24:	pushg 2
26:	pushc 0
28:	gt 
29:	storeg 1
31:	rtnInner


Class console 163 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 120 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 164 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 2
15:	invoke 122 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	rpushg 2
27:	invoke 121 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 2
39:	invoke 124 0 0
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class display 165 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	rpushg 2
17:	invoke 122 0 1
23:	rpop 
24:	inner 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 2
31:	invoke 124 0 0
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class init 166 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 5
15:	invoke 151 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class Complex 167 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Complex 168 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 1
11:	mvStack
12:	rtnEventQ 0
doE: 
14:	mvStack
15:	rtnEventQ 0
17:	setThisStack
18:	pushthis 
19:	rtn D


Class + 169 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushthis 
15:	rpushg 1
17:	rpushg 1
19:	pushthis 
20:	rpushg 1
22:	pushg 1
24:	pushthis 
25:	rpushg 2
27:	pushg 1
29:	+
30:	pushthis 
31:	rpushg 1
33:	pushg 2
35:	pushthis 
36:	rpushg 2
38:	pushg 2
40:	+
41:	invoke 168 0 1
47:	rswap 
48:	rstoreg 3
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rpushg 3
56:	rtn D


Class - 170 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushthis 
15:	rpushg 1
17:	rpushg 1
19:	pushthis 
20:	rpushg 1
22:	pushg 1
24:	pushthis 
25:	rpushg 2
27:	pushg 1
29:	+
30:	pushthis 
31:	rpushg 1
33:	pushg 2
35:	pushthis 
36:	rpushg 2
38:	pushg 2
40:	+
41:	invoke 168 0 1
47:	rswap 
48:	rstoreg 3
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rpushg 3
56:	rtn D


Class display 171 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 67
12:	%prim put 2
14:	pushthis 
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	pushthis 
22:	rpushg 1
24:	pushg 1
26:	invoke 67 0 0
32:	rpop 
33:	pushc 44
35:	%prim put 2
37:	pushthis 
38:	rpushg 1
40:	rpushg 1
42:	rpushg 1
44:	pushthis 
45:	rpushg 1
47:	pushg 2
49:	invoke 67 0 0
55:	rpop 
56:	pushc 10
58:	%prim put 2
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class EMC2array 172 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class Array 173 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 2
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	pushc 1
15:	storeg 1
17:	pushthis 
18:	innerP 2
20:	popThisObj
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class put 174 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	rpushg 1
16:	rpushg 2
18:	pushthis 
19:	pushg 1
21:	pushthis 
22:	rpushg 1
24:	pushg 1
26:	xstoreg 1
28:	pushthis 
29:	invoke 175 0 1
35:	rpop 
36:	pushthis 
37:	pushthis 
38:	rpushg 1
40:	rswap 
41:	rstoreg 2
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rpushg 2
49:	rtn D


Class %if%then%%else%#S#175 175 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	pushthis 
15:	rpushg 3
17:	rpushg 1
19:	pushg 1
21:	pushthis 
22:	rpushg 3
24:	rpushg 1
26:	rpushg 2
28:	invoke 55 0 0
34:	eq 
35:	toSuper 60
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class get 176 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 2
16:	pushthis 
17:	rpushg 1
19:	pushg 1
21:	xpushg 1
23:	storeg 1
25:	pushthis 
26:	invoke 177 0 1
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	pushg 1
39:	rtn D


Class %if%then%%else%#S#177 177 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	pushthis 
15:	rpushg 3
17:	rpushg 1
19:	pushg 1
21:	pushthis 
22:	rpushg 3
24:	rpushg 1
26:	rpushg 2
28:	invoke 55 0 0
34:	eq 
35:	toSuper 60
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class nxt 178 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 179 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class %if%then%%else%#S#179 179 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	pushthis 
15:	rpushg 3
17:	rpushg 1
19:	pushg 1
21:	pushthis 
22:	rpushg 3
24:	rpushg 1
26:	pushg 2
28:	eq 
29:	toSuper 60
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class prv 180 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 181 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class %if%then%%else%#S#181 181 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	pushthis 
15:	rpushg 3
17:	rpushg 1
19:	pushg 1
21:	pushthis 
22:	rpushg 3
24:	rpushg 1
26:	pushg 2
28:	eq 
29:	toSuper 60
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class forAll 182 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	pushc 1
17:	storeg 1
19:	pushthis 
20:	invoke 183 0 0
26:	rpop 
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	rtn D


Class loop 183 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	rpushg 1
18:	rpushg 2
20:	pushthis 
21:	rpushg 1
23:	rpushg 1
25:	pushg 1
27:	xpushg 1
29:	storeg 1
31:	pushthis 
32:	rpushg 1
34:	rpushg 1
36:	pushthis 
37:	rpushg 1
39:	rpushg 1
41:	pushg 1
43:	pushc 1
45:	+
46:	storeg 1
48:	pushthis 
49:	rpushg 1
51:	innerP 1
53:	popThisObj
54:	pushthis 
55:	rpushg 1
57:	rpushg 1
59:	pushg 1
61:	pushthis 
62:	rpushg 1
64:	rpushg 1
66:	pushg 2
68:	lt
69:	jmpFalse 80
72:	pushthis 
73:	invoke 814 0 1
79:	rpop 
80:	rtnEventQ 0
82:	setThisStack
83:	pushthis 
84:	rtn D


Class print 184 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushText 1
14:	invoke 107 0 0
20:	rpop 
21:	pushthis 
22:	innerP 1
24:	popThisObj
25:	pushText 8
27:	invoke 107 0 0
33:	rpop 
34:	pushthis 
35:	invoke 185 0 1
41:	rpop 
42:	pushthis 
43:	rpushg 1
45:	rpushg 1
47:	rpushg 1
49:	invoke 66 0 0
55:	rpop 
56:	rtnEventQ 0
58:	setThisStack
59:	pushthis 
60:	rtn D


Class %for%to%%do%#S#185 185 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	pushc 1
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	rpushg 2
23:	invoke 55 0 0
29:	toSuper 63
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class Range 186 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	pushthis 
13:	pushg 2
15:	pushthis 
16:	pushg 1
18:	-
19:	pushc 1
21:	+
22:	pushthis 
23:	storeg 3
25:	rtnEventQ 1
doE: 
27:	doEventQ 
28:	mvStack
29:	pushthis 
30:	pushg 3
32:	pushc 1
34:	lt
35:	jmpFalse 46
38:	pushthis 
39:	invoke 817 0 1
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class check 187 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushg 1
16:	pushthis 
17:	rpushg 1
19:	pushg 1
21:	lt
22:	pushthis 
23:	pushg 1
25:	pushthis 
26:	rpushg 1
28:	pushg 2
30:	gt 
31:	orr
32:	jmpFalse 43
35:	pushthis 
36:	invoke 816 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class print 188 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	pushthis 
18:	rpushg 1
20:	pushg 1
22:	invoke 67 0 0
28:	rpop 
29:	pushc 58
31:	%prim put 2
33:	pushthis 
34:	rpushg 1
36:	rpushg 1
38:	rpushg 1
40:	pushthis 
41:	rpushg 1
43:	pushg 2
45:	invoke 67 0 0
51:	rpop 
52:	rtnEventQ 0
54:	setThisStack
55:	pushthis 
56:	rtn D


Class D1_Array 189 1
allocE:
1:	pushthis 
2:	rstoreg 3
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 173
enterE: 
14:	innera 4
16:	rtnInner
doE: 
17:	doEventQ 
18:	mvStack
19:	pushthis 
20:	pushthis 
21:	rpushg 3
23:	pushg 3
25:	storeg 2
27:	pushthis 
28:	pushthis 
29:	rpushg 1
31:	rpushg 1
33:	pushthis 
34:	pushg 2
36:	pushc 0
38:	pushc 1
40:	allocIndexed 52 1
44:	rswap 
45:	rstoreg 2
47:	pushthis 
48:	innerP 4
50:	popThisObj
51:	rtnInner


Class putAt 190 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 1
19:	rpushg 3
21:	pushthis 
22:	pushg 1
24:	invoke 187 0 0
30:	rpop 
31:	pushthis 
32:	rpushg 1
34:	rpushg 2
36:	pushthis 
37:	pushg 2
39:	pushthis 
40:	pushg 1
42:	pushthis 
43:	rpushg 1
45:	rpushg 3
47:	pushg 1
49:	-
50:	pushc 1
52:	+
53:	xstoreg 1
55:	pushthis 
56:	pushthis 
57:	rpushg 1
59:	rswap 
60:	rstoreg 2
62:	rtnEventQ 0
64:	setThisStack
65:	pushthis 
66:	rpushg 2
68:	rtn D


Class getAt 191 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	rpushg 1
16:	rpushg 3
18:	pushthis 
19:	pushg 1
21:	invoke 187 0 0
27:	rpop 
28:	pushthis 
29:	pushthis 
30:	rpushg 1
32:	rpushg 2
34:	pushthis 
35:	pushg 1
37:	pushthis 
38:	rpushg 1
40:	rpushg 3
42:	pushg 1
44:	-
45:	pushc 1
47:	+
48:	xpushg 1
50:	storeg 2
52:	rtnEventQ 0
54:	setThisStack
55:	pushthis 
56:	pushg 2
58:	rtn D


Class print 192 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 184
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 2
17:	rpushg 3
19:	invoke 188 0 0
25:	rpop 
26:	rtnInner


Class D2_Array 193 1
allocE:
1:	pushthis 
2:	rstoreg 4
4:	pushthis 
5:	rstoreg 3
7:	rstore 1
9:	allocEventQ 0
11:	pushthis 
12:	rpushg 1
14:	toSuper 173
enterE: 
17:	rtnInner
doE: 
18:	doEventQ 
19:	mvStack
20:	pushthis 
21:	pushthis 
22:	rpushg 1
24:	rpushg 1
26:	pushthis 
27:	rpushg 3
29:	pushg 3
31:	pushthis 
32:	rpushg 4
34:	pushg 3
36:	*
37:	pushc 0
39:	pushc 1
41:	allocIndexed 52 1
45:	rswap 
46:	rstoreg 2
48:	pushthis 
49:	pushthis 
50:	rswap 
51:	rstoreg 5
53:	pushText 5
55:	invoke 107 0 0
61:	rpop 
62:	rtnInner


Class putAt 194 1
allocE:
1:	pushthis 
2:	storeg 3
4:	pushthis 
5:	storeg 2
7:	pushthis 
8:	storeg 1
10:	rstore 1
12:	allocEventQ 0
14:	mvStack
15:	rtnEventQ 1
doE: 
17:	doEventQ 
18:	mvStack
19:	pushthis 
20:	rpushg 1
22:	rpushg 3
24:	pushthis 
25:	pushg 1
27:	invoke 187 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 4
39:	pushthis 
40:	pushg 2
42:	invoke 187 0 0
48:	rpop 
49:	pushthis 
50:	pushthis 
51:	pushg 1
53:	pushthis 
54:	rpushg 1
56:	rpushg 3
58:	pushg 1
60:	-
61:	pushthis 
62:	rpushg 1
64:	rpushg 4
66:	pushg 3
68:	pushc 1
70:	pushthis 
71:	pushg 2
73:	pushthis 
74:	rpushg 1
76:	rpushg 4
78:	pushg 1
80:	-
81:	+
82:	+
83:	*
84:	storeg 4
86:	pushthis 
87:	rpushg 1
89:	rpushg 2
91:	pushthis 
92:	pushg 3
94:	pushthis 
95:	pushg 4
97:	xstoreg 1
99:	rtnEventQ 0
101:	setThisStack
102:	pushthis 
103:	rpushg 2
105:	rtn D


Class getAt 195 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 1
19:	rpushg 3
21:	pushthis 
22:	pushg 1
24:	invoke 187 0 0
30:	rpop 
31:	pushthis 
32:	rpushg 1
34:	rpushg 4
36:	pushthis 
37:	pushg 2
39:	invoke 187 0 0
45:	rpop 
46:	pushthis 
47:	pushthis 
48:	pushg 1
50:	pushthis 
51:	rpushg 1
53:	rpushg 3
55:	pushg 1
57:	-
58:	pushthis 
59:	rpushg 1
61:	rpushg 4
63:	pushg 3
65:	pushc 1
67:	pushthis 
68:	pushg 2
70:	pushthis 
71:	rpushg 1
73:	rpushg 4
75:	pushg 1
77:	-
78:	+
79:	+
80:	*
81:	storeg 4
83:	pushthis 
84:	pushthis 
85:	rpushg 1
87:	rpushg 2
89:	pushthis 
90:	pushg 4
92:	xpushg 1
94:	storeg 3
96:	rtnEventQ 0
98:	setThisStack
99:	pushthis 
100:	pushg 3
102:	rtn D


Class print 196 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 184
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 2
17:	rpushg 3
19:	invoke 188 0 0
25:	rpop 
26:	pushText 15
28:	invoke 107 0 0
34:	rpop 
35:	pushthis 
36:	rpushg 2
38:	rpushg 4
40:	invoke 188 0 0
46:	rpop 
47:	rtnInner


Class ForkJoinSystem 228 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class ForkJoinSystem 229 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 119
enterE: 
11:	innera 2
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	innerP 2
19:	popThisObj
20:	rtnInner


Class ForkJoin 230 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 139 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 120 3 1
25:	rpop 
26:	innera 1
28:	rtnEventQ 1
doE: 
30:	doEventQ 
31:	mvStack
32:	pushthis 
33:	rpushg 3
35:	invoke 121 0 0
41:	rpop 
42:	pushthis 
43:	innerP 1
45:	popThisObj
46:	pushthis 
47:	invoke 232 0 1
53:	rpop 
54:	rtnEventQ 0
56:	setThisStack
57:	pushthis 
58:	rtn D


Class run 231 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	rpushg 1
16:	rpushg 3
18:	invoke 122 0 1
24:	rpop 
25:	pushthis 
26:	rpushg 1
28:	rpushg 2
30:	pushthis 
31:	rpushg 2
33:	invoke 90 0 0
39:	rpop 
40:	pushthis 
41:	rpushg 1
43:	rpushg 1
45:	rpushg 5
47:	pushthis 
48:	rpushg 2
50:	invoke 152 0 0
56:	rpop 
57:	pushthis 
58:	rpushg 1
60:	rpushg 3
62:	invoke 124 0 0
68:	rpop 
69:	rtnEventQ 0
71:	setThisStack
72:	pushthis 
73:	rtn D


Class AwaitTermination 232 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 233 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 233 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 100
12:	%prim sleep 15
14:	pushthis 
15:	pushthis 
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	invoke 23 0 0
32:	storeg 1
34:	pushthis 
35:	invoke 234 0 1
41:	rpop 
42:	pushthis 
43:	pushg 1
45:	jmpFalse 56
48:	pushthis 
49:	invoke 834 0 1
55:	rpop 
56:	pushthis 
57:	rpushg 1
59:	rpushg 1
61:	rpushg 2
63:	invoke 95 0 0
69:	rpop 
70:	rtnEventQ 0
72:	setThisStack
73:	pushthis 
74:	rtn D


Class scan#S#234 234 4
allocE:
1:	rstore 4
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 4
8:	rpushg 1
10:	rpushg 1
12:	rpushg 2
14:	toSuper 84
enterE: 
17:	rtnInner
doE: 
18:	doEventQ 
19:	mvStack
20:	pushthis 
21:	rpushg 4
23:	pushthis 
24:	rpushg 2
26:	rswap 
27:	rstoreg 2
29:	pushthis 
30:	rpushg 4
32:	rpushg 2
34:	pushg 1
36:	pushthis 
37:	rpushg 4
39:	rpushg 1
41:	rpushg 1
43:	rpushg 1
45:	rpushg 3
47:	pushg 3
49:	ne 
50:	jmpFalse 61
53:	pushthis 
54:	invoke 833 0 1
60:	rpop 
61:	rtnInner


Class MonitorSystem 235 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	rtnEventQ 0
doE: 
8:	mvStack
9:	rtnEventQ 0
11:	setThisStack
12:	pushthis 
13:	rtn D


Class System 236 8
allocE:
1:	rstore 8
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 8
8:	rpushg 1
10:	rpushg 1
12:	rpushg 3
14:	rpushg 2
16:	toSuper 119
enterE: 
19:	innera 2
21:	rtnInner
doE: 
22:	doEventQ 
23:	mvStack
24:	inner 2
26:	rtnInner


Class Semaphore 237 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 120 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 139 3 1
25:	rpop 
26:	rtnEventQ 0
doE: 
28:	mvStack
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class init 238 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushc 1
15:	storeg 1
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class wait 239 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 2
15:	invoke 122 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	pushthis 
26:	rpushg 1
28:	pushg 1
30:	pushc 1
32:	-
33:	storeg 1
35:	pushthis 
36:	invoke 240 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#240 240 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 8
14:	rpushg 1
16:	pushthis 
17:	rpushg 3
19:	rpushg 1
21:	pushg 1
23:	pushc 0
25:	lt
26:	toSuper 60
enterE: 
29:	rtnInner
doE: 
30:	mvStack
31:	rtnInner


Class signal 241 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 2
15:	invoke 122 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	pushthis 
26:	rpushg 1
28:	pushg 1
30:	pushc 1
32:	+
33:	storeg 1
35:	pushthis 
36:	invoke 242 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#242 242 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 8
14:	rpushg 1
16:	pushthis 
17:	rpushg 3
19:	rpushg 1
21:	pushg 1
23:	pushc 0
25:	le
26:	toSuper 60
enterE: 
29:	rtnInner
doE: 
30:	mvStack
31:	rtnInner


Class Process 243 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 125
enterE: 
11:	innera 3
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	inner 3
18:	rtnInner


Class start 244 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 126
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	pushthis 
16:	rpushg 2
18:	rswap 
19:	rstoreg 3
21:	pushText 5
23:	invoke 107 0 0
29:	rpop 
30:	pushthis 
31:	rpushg 2
33:	rpushg 2
35:	invoke 107 0 0
41:	rpop 
42:	pushthis 
43:	rpushg 2
45:	rpushg 1
47:	rpushg 8
49:	rpushg 1
51:	invoke 66 0 0
57:	rpop 
58:	pushthis 
59:	rpushg 2
61:	rpushg 1
63:	rpushg 5
65:	pushthis 
66:	rpushg 3
68:	invoke 152 0 0
74:	rpop 
75:	rtnInner


Class Monitor 245 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 237 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 246 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 2
15:	invoke 238 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class entry 247 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	rpushg 2
17:	invoke 239 0 0
23:	rpop 
24:	pushthis 
25:	rpushg 1
27:	pushthis 
28:	rpushg 1
30:	pushg 1
32:	pushc 1
34:	+
35:	storeg 1
37:	inner 1
39:	pushthis 
40:	rpushg 1
42:	rpushg 2
44:	invoke 241 0 0
50:	rpop 
51:	rtnEventQ 0
53:	setThisStack
54:	pushthis 
55:	rtn D


Class wait 248 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 249 2 1
13:	rpop 
14:	innera 1
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class loop 249 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	innerP 1
15:	popThisObj
16:	pushthis 
17:	rpushg 1
19:	pushg 1
21:	pushthis 
22:	rpushg 1
24:	rpushg 1
26:	rpushg 1
28:	rpushg 8
30:	rpushg 1
32:	invoke 23 0 0
38:	eq 
39:	jmpFalse 50
42:	pushthis 
43:	invoke 839 0 1
49:	rpop 
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class workspace 260 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 537 19 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class demo 537 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 538 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class ArrayDemos 538 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 557 5 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class RangeList 557 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	pushc 0
14:	pushc 0
16:	invoke 567 0 0
22:	rswap 
23:	rstoreg 3
25:	pushthis 
26:	pushthis 
27:	pushc 2
29:	pushc 3
31:	invoke 567 0 0
37:	rswap 
38:	rstoreg 4
40:	pushthis 
41:	pushthis 
42:	pushc 4
44:	pushc 5
46:	invoke 567 0 0
52:	rswap 
53:	rstoreg 5
55:	pushthis 
56:	rpushg 1
58:	rpushg 1
60:	rpushg 1
62:	pushthis 
63:	rpushg 4
65:	pushg 1
67:	invoke 67 0 0
73:	rpop 
74:	pushthis 
75:	rpushg 1
77:	rpushg 1
79:	rpushg 1
81:	pushthis 
82:	rpushg 4
84:	pushg 2
86:	invoke 67 0 0
92:	rpop 
93:	pushthis 
94:	rpushg 1
96:	rpushg 1
98:	rpushg 1
100:	invoke 66 0 0
106:	rpop 
107:	pushthis 
108:	rpushg 1
110:	rpushg 1
112:	rpushg 1
114:	pushthis 
115:	rpushg 5
117:	pushg 1
119:	invoke 67 0 0
125:	rpop 
126:	pushthis 
127:	rpushg 1
129:	rpushg 1
131:	rpushg 1
133:	pushthis 
134:	rpushg 5
136:	pushg 2
138:	invoke 67 0 0
144:	rpop 
145:	pushthis 
146:	rpushg 1
148:	rpushg 1
150:	rpushg 1
152:	invoke 66 0 0
158:	rpop 
159:	pushthis 
160:	pushthis 
161:	pushthis 
162:	rpushg 4
164:	pushthis 
165:	pushthis 
166:	rpushg 5
168:	pushNone 
169:	invoke 570 0 0
175:	invoke 570 0 0
181:	rswap 
182:	rstoreg 2
184:	pushthis 
185:	pushthis 
186:	pushc 2
188:	pushthis 
189:	pushthis 
190:	rpushg 4
192:	pushthis 
193:	pushthis 
194:	rpushg 5
196:	pushNone 
197:	invoke 570 0 0
203:	invoke 570 0 0
209:	invoke 578 0 0
215:	rswap 
216:	rstoreg 6
218:	pushthis 
219:	pushthis 
220:	pushc 2
222:	pushthis 
223:	pushthis 
224:	rpushg 4
226:	pushthis 
227:	pushthis 
228:	rpushg 5
230:	pushNone 
231:	invoke 570 0 0
237:	invoke 570 0 0
243:	invoke 578 0 0
249:	rswap 
250:	rstoreg 6
252:	pushthis 
253:	pushthis 
254:	pushc 2
256:	pushthis 
257:	pushthis 
258:	pushc 2
260:	pushc 3
262:	invoke 567 0 0
268:	pushthis 
269:	pushthis 
270:	pushc 4
272:	pushc 5
274:	invoke 567 0 0
280:	pushNone 
281:	invoke 570 0 0
287:	invoke 570 0 0
293:	invoke 578 0 0
299:	rswap 
300:	rstoreg 6
302:	pushthis 
303:	rpushg 6
305:	pushc 2
307:	pushc 4
309:	pushc 99
311:	invoke 589 0 0
317:	rpop 
318:	pushthis 
319:	rpushg 1
321:	rpushg 1
323:	rpushg 1
325:	pushthis 
326:	rpushg 6
328:	pushc 2
330:	pushc 4
332:	invoke 590 0 0
338:	invoke 67 0 0
344:	rpop 
345:	pushthis 
346:	rpushg 1
348:	rpushg 1
350:	rpushg 1
352:	invoke 66 0 0
358:	rpop 
359:	pushthis 
360:	pushthis 
361:	pushc 2
363:	pushthis 
364:	pushc 4
366:	pushNone 
367:	invoke 560 0 0
373:	invoke 560 0 0
379:	rswap 
380:	rstoreg 7
382:	pushthis 
383:	rpushg 6
385:	pushthis 
386:	rpushg 7
388:	pushc 99
390:	invoke 591 0 0
396:	rpop 
397:	pushthis 
398:	rpushg 1
400:	rpushg 1
402:	rpushg 1
404:	pushthis 
405:	rpushg 6
407:	pushthis 
408:	rpushg 7
410:	invoke 592 0 0
416:	invoke 67 0 0
422:	rpop 
423:	pushthis 
424:	rpushg 1
426:	rpushg 1
428:	rpushg 1
430:	invoke 66 0 0
436:	rpop 
437:	rtnEventQ 0
439:	setThisStack
440:	pushthis 
441:	rtn D


Class int2int 558 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	innera 1
11:	rtnEventQ 1
doE: 
13:	doEventQ 
14:	mvStack
15:	pushthis 
16:	innerP 1
18:	popThisObj
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	pushg 2
25:	rtn D


Class intint2int 559 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	innera 1
14:	rtnEventQ 1
doE: 
16:	doEventQ 
17:	mvStack
18:	pushthis 
19:	innerP 1
21:	popThisObj
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	pushg 3
28:	rtn D


Class IntList 560 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	innera 1
14:	rtnEventQ 1
doE: 
16:	doEventQ 
17:	mvStack
18:	pushthis 
19:	innerP 1
21:	popThisObj
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class first 561 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	pushg 1
16:	storeg 1
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class second 562 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 2
16:	pushg 1
18:	storeg 1
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class scan 563 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	pushthis 
14:	rpushg 1
16:	rswap 
17:	rstoreg 2
19:	pushthis 
20:	pushthis 
21:	rpushg 1
23:	pushg 1
25:	storeg 1
27:	pushthis 
28:	invoke 564 0 0
34:	rpop 
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class loop 564 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	innerP 1
15:	popThisObj
16:	pushthis 
17:	rpushg 1
19:	rpushg 2
21:	rpushg 2
23:	pushNone 
24:	57
25:	jmpFalse 36
28:	pushthis 
29:	invoke 909 0 1
35:	rpop 
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class length 565 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 0
13:	storeg 1
15:	pushthis 
16:	invoke 566 0 1
22:	rpop 
23:	rtnEventQ 0
25:	setThisStack
26:	pushthis 
27:	pushg 1
29:	rtn D


Class scan#S#566 566 3
allocE:
1:	rstore 3
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	toSuper 563
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 3
19:	pushthis 
20:	rpushg 3
22:	pushg 1
24:	pushc 1
26:	+
27:	storeg 1
29:	rtnInner


Class Range 567 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	pushthis 
13:	pushg 2
15:	pushthis 
16:	pushg 1
18:	-
19:	pushc 1
21:	+
22:	pushthis 
23:	storeg 3
25:	rtnEventQ 1
doE: 
27:	doEventQ 
28:	mvStack
29:	pushthis 
30:	pushg 3
32:	pushc 1
34:	lt
35:	jmpFalse 46
38:	pushthis 
39:	invoke 911 0 1
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class check 568 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushg 1
16:	pushthis 
17:	rpushg 1
19:	pushg 1
21:	lt
22:	pushthis 
23:	pushg 1
25:	pushthis 
26:	rpushg 1
28:	pushg 2
30:	gt 
31:	orr
32:	jmpFalse 43
35:	pushthis 
36:	invoke 910 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class print 569 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	pushthis 
22:	rpushg 1
24:	pushg 1
26:	invoke 67 0 0
32:	rpop 
33:	pushc 58
35:	%prim put 2
37:	pushthis 
38:	rpushg 1
40:	rpushg 1
42:	rpushg 1
44:	rpushg 1
46:	rpushg 1
48:	pushthis 
49:	rpushg 1
51:	pushg 2
53:	invoke 67 0 0
59:	rpop 
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class RangeList 570 1
allocE:
1:	pushthis 
2:	rstoreg 3
4:	pushthis 
5:	rstoreg 2
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	innera 1
14:	rtnEventQ 1
doE: 
16:	doEventQ 
17:	mvStack
18:	pushthis 
19:	innerP 1
21:	popThisObj
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class empty 571 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	pushthis 
14:	rpushg 1
16:	rpushg 2
18:	pushNone 
19:	req 
20:	storeg 1
22:	pushthis 
23:	innerP 1
25:	popThisObj
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	pushg 1
32:	rtn D


Class first 572 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 2
16:	rswap 
17:	rstoreg 2
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rpushg 2
25:	rtn D


Class second 573 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 3
16:	rpushg 2
18:	rswap 
19:	rstoreg 2
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rpushg 2
27:	rtn D


Class scan 574 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	pushthis 
14:	rpushg 1
16:	rswap 
17:	rstoreg 3
19:	pushthis 
20:	pushthis 
21:	rpushg 1
23:	rpushg 2
25:	rswap 
26:	rstoreg 2
28:	pushthis 
29:	invoke 575 0 0
35:	rpop 
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class loop 575 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	innerP 1
15:	popThisObj
16:	pushthis 
17:	rpushg 1
19:	rpushg 3
21:	rpushg 3
23:	pushNone 
24:	57
25:	jmpFalse 36
28:	pushthis 
29:	invoke 912 0 1
35:	rpop 
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class length 576 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 0
13:	storeg 1
15:	pushthis 
16:	invoke 577 0 1
22:	rpop 
23:	rtnEventQ 0
25:	setThisStack
26:	pushthis 
27:	pushg 1
29:	rtn D


Class scan#S#577 577 4
allocE:
1:	rstore 4
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 4
8:	rpushg 1
10:	toSuper 574
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 4
19:	pushthis 
20:	rpushg 4
22:	pushg 1
24:	pushc 1
26:	+
27:	storeg 1
29:	rtnInner


Class Array 578 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	innera 2
14:	rtnEventQ 1
doE: 
16:	doEventQ 
17:	mvStack
18:	pushthis 
19:	pushthis 
20:	rpushg 2
22:	invoke 572 0 0
28:	rswap 
29:	rstoreg 3
31:	pushthis 
32:	pushthis 
33:	rpushg 2
35:	invoke 573 0 0
41:	rswap 
42:	rstoreg 4
44:	pushthis 
45:	pushc 1
47:	storeg 2
49:	pushthis 
50:	pushthis 
51:	rpushg 3
53:	pushg 3
55:	pushthis 
56:	rpushg 4
58:	pushg 3
60:	*
61:	storeg 3
63:	pushthis 
64:	pushthis 
65:	rpushg 1
67:	rpushg 1
69:	rpushg 1
71:	rpushg 1
73:	pushthis 
74:	pushg 3
76:	pushc 0
78:	pushc 1
80:	allocIndexed 52 1
84:	rswap 
85:	rstoreg 5
87:	pushthis 
88:	rpushg 1
90:	rpushg 1
92:	rpushg 1
94:	rpushg 1
96:	pushthis 
97:	rpushg 2
99:	invoke 572 0 0
105:	pushg 1
107:	invoke 67 0 0
113:	rpop 
114:	pushText 1
116:	invoke 107 0 0
122:	rpop 
123:	pushthis 
124:	rpushg 1
126:	rpushg 1
128:	rpushg 1
130:	rpushg 1
132:	pushthis 
133:	rpushg 2
135:	invoke 572 0 0
141:	pushg 2
143:	invoke 67 0 0
149:	rpop 
150:	pushthis 
151:	rpushg 1
153:	rpushg 1
155:	rpushg 1
157:	rpushg 1
159:	invoke 66 0 0
165:	rpop 
166:	pushthis 
167:	rpushg 1
169:	rpushg 1
171:	rpushg 1
173:	rpushg 1
175:	pushthis 
176:	rpushg 2
178:	invoke 573 0 0
184:	pushg 1
186:	invoke 67 0 0
192:	rpop 
193:	pushText 4
195:	invoke 107 0 0
201:	rpop 
202:	pushthis 
203:	rpushg 1
205:	rpushg 1
207:	rpushg 1
209:	rpushg 1
211:	pushthis 
212:	rpushg 2
214:	invoke 573 0 0
220:	pushg 2
222:	invoke 67 0 0
228:	rpop 
229:	pushthis 
230:	rpushg 1
232:	rpushg 1
234:	rpushg 1
236:	rpushg 1
238:	invoke 66 0 0
244:	rpop 
245:	pushthis 
246:	innerP 2
248:	popThisObj
249:	rtnEventQ 0
251:	setThisStack
252:	pushthis 
253:	rtn D


Class put 579 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	rpushg 1
16:	rpushg 5
18:	pushthis 
19:	pushg 1
21:	pushthis 
22:	rpushg 1
24:	pushg 2
26:	xstoreg 1
28:	pushthis 
29:	invoke 580 0 1
35:	rpop 
36:	pushthis 
37:	pushthis 
38:	rpushg 1
40:	rswap 
41:	rstoreg 2
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rpushg 2
49:	rtn D


Class %if%then%%else%#S#580 580 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	pushg 2
25:	pushthis 
26:	rpushg 3
28:	rpushg 1
30:	rpushg 5
32:	invoke 55 0 0
38:	eq 
39:	toSuper 60
enterE: 
42:	rtnInner
doE: 
43:	mvStack
44:	rtnInner


Class get 581 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 1
14:	rpushg 5
16:	pushthis 
17:	rpushg 1
19:	pushg 2
21:	xpushg 1
23:	storeg 1
25:	pushthis 
26:	invoke 582 0 1
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	pushg 1
39:	rtn D


Class %if%then%%else%#S#582 582 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	pushg 2
25:	pushthis 
26:	rpushg 3
28:	rpushg 1
30:	rpushg 5
32:	invoke 55 0 0
38:	eq 
39:	toSuper 60
enterE: 
42:	rtnInner
doE: 
43:	mvStack
44:	rtnInner


Class nxt 583 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 584 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class %if%then%%else%#S#584 584 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	pushg 2
25:	pushthis 
26:	rpushg 3
28:	rpushg 1
30:	pushg 3
32:	eq 
33:	toSuper 60
enterE: 
36:	rtnInner
doE: 
37:	mvStack
38:	rtnInner


Class prv 585 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 586 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class %if%then%%else%#S#586 586 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	pushg 2
25:	pushc 1
27:	eq 
28:	toSuper 60
enterE: 
31:	rtnInner
doE: 
32:	mvStack
33:	rtnInner


Class putAt 587 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 1
19:	rpushg 4
21:	pushNone 
22:	req 
23:	jmpFalse 34
26:	pushthis 
27:	invoke 921 0 1
33:	rpop 
34:	rtnEventQ 0
36:	setThisStack
37:	pushthis 
38:	rtn D


Class getAt 588 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	rpushg 1
16:	rpushg 4
18:	pushNone 
19:	req 
20:	jmpFalse 31
23:	pushthis 
24:	invoke 922 0 1
30:	rpop 
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	pushg 2
37:	rtn D


Class putAtAt 589 1
allocE:
1:	pushthis 
2:	storeg 3
4:	pushthis 
5:	storeg 2
7:	pushthis 
8:	storeg 1
10:	rstore 1
12:	allocEventQ 0
14:	mvStack
15:	rtnEventQ 1
doE: 
17:	doEventQ 
18:	mvStack
19:	pushthis 
20:	rpushg 1
22:	rpushg 4
24:	pushNone 
25:	57
26:	jmpFalse 37
29:	pushthis 
30:	invoke 923 0 1
36:	rpop 
37:	rtnEventQ 0
39:	setThisStack
40:	pushthis 
41:	rtn D


Class getAtAt 590 1
allocE:
1:	pushthis 
2:	storeg 2
4:	pushthis 
5:	storeg 1
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 1
19:	rpushg 4
21:	pushNone 
22:	57
23:	jmpFalse 34
26:	pushthis 
27:	invoke 924 0 1
33:	rpop 
34:	rtnEventQ 0
36:	setThisStack
37:	pushthis 
38:	pushg 3
40:	rtn D


Class realPutAt 591 1
allocE:
1:	pushthis 
2:	storeg 1
4:	pushthis 
5:	rstoreg 2
7:	rstore 1
9:	allocEventQ 0
11:	mvStack
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 1
19:	rpushg 4
21:	pushNone 
22:	57
23:	jmpFalse 34
26:	pushthis 
27:	invoke 925 0 1
33:	rpop 
34:	rtnEventQ 0
36:	setThisStack
37:	pushthis 
38:	rtn D


Class realGetAt 592 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	rpushg 1
16:	rpushg 4
18:	pushNone 
19:	57
20:	jmpFalse 31
23:	pushthis 
24:	invoke 926 0 1
30:	rpop 
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	pushg 1
37:	rtn D


Class forAll 593 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	pushc 1
17:	storeg 2
19:	pushthis 
20:	invoke 594 0 0
26:	rpop 
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	rtn D


Class loop 594 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	rpushg 1
18:	rpushg 5
20:	pushthis 
21:	rpushg 1
23:	rpushg 1
25:	pushg 2
27:	xpushg 1
29:	storeg 1
31:	pushthis 
32:	rpushg 1
34:	innerP 1
36:	popThisObj
37:	pushthis 
38:	rpushg 1
40:	rpushg 1
42:	pushg 2
44:	pushthis 
45:	rpushg 1
47:	rpushg 1
49:	pushg 3
51:	lt
52:	jmpFalse 63
55:	pushthis 
56:	invoke 927 0 1
62:	rpop 
63:	rtnEventQ 0
65:	setThisStack
66:	pushthis 
67:	rtn D


Class forAllIndex 595 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushthis 
13:	rpushg 1
15:	pushc 1
17:	storeg 2
19:	pushthis 
20:	pushthis 
21:	rpushg 1
23:	pushg 2
25:	storeg 1
27:	pushthis 
28:	invoke 596 0 0
34:	rpop 
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class loop 596 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	innerP 1
15:	popThisObj
16:	pushthis 
17:	rpushg 1
19:	rpushg 1
21:	pushthis 
22:	rpushg 1
24:	rpushg 1
26:	pushg 2
28:	pushc 1
30:	+
31:	storeg 2
33:	pushthis 
34:	rpushg 1
36:	pushthis 
37:	rpushg 1
39:	rpushg 1
41:	pushg 2
43:	storeg 1
45:	pushthis 
46:	rpushg 1
48:	rpushg 1
50:	pushg 2
52:	pushthis 
53:	rpushg 1
55:	rpushg 1
57:	pushg 3
59:	lt
60:	jmpFalse 71
63:	pushthis 
64:	invoke 928 0 1
70:	rpop 
71:	rtnEventQ 0
73:	setThisStack
74:	pushthis 
75:	rtn D


Class fill 597 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	invoke 598 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class forAllIndex#S#598 598 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 595
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	rpushg 5
23:	pushthis 
24:	rpushg 2
26:	pushg 1
28:	pushthis 
29:	pushg 1
31:	xstoreg 1
33:	rtnInner


Class zeroes 599 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushc 0
15:	invoke 597 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class ones 600 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushc 1
15:	invoke 597 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class sum 601 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 0
13:	storeg 1
15:	pushthis 
16:	invoke 602 0 1
22:	rpop 
23:	rtnEventQ 0
25:	setThisStack
26:	pushthis 
27:	pushg 1
29:	rtn D


Class forAll#S#602 602 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 593
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	pushthis 
20:	rpushg 2
22:	pushg 1
24:	pushthis 
25:	pushg 1
27:	+
28:	storeg 1
30:	rtnInner


Class iadd 603 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	invoke 604 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class forAll#S#604 604 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 593
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	pushthis 
22:	pushg 1
24:	pushthis 
25:	rpushg 2
27:	rpushg 2
29:	invoke 581 0 0
35:	+
36:	invoke 579 0 0
42:	rpop 
43:	rtnInner


Class iminus 605 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	invoke 606 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class forAll#S#606 606 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 593
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	pushthis 
22:	pushg 1
24:	pushthis 
25:	rpushg 2
27:	rpushg 2
29:	invoke 581 0 0
35:	-
36:	invoke 579 0 0
42:	rpop 
43:	rtnInner


Class imult 607 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	invoke 608 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class forAll#S#608 608 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 593
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	pushthis 
22:	pushg 1
24:	pushthis 
25:	rpushg 2
27:	rpushg 2
29:	invoke 581 0 0
35:	*
36:	invoke 579 0 0
42:	rpop 
43:	rtnInner


Class idiv 609 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	invoke 610 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class forAll#S#610 610 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 593
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	pushthis 
22:	pushg 1
24:	pushthis 
25:	rpushg 2
27:	rpushg 2
29:	invoke 581 0 0
35:	rdiv
36:	invoke 579 0 0
42:	rpop 
43:	rtnInner


Class equal 611 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	mvStack
9:	rtnEventQ 1
doE: 
11:	doEventQ 
12:	mvStack
13:	pushthis 
14:	pushthis 
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	rpushg 1
23:	rpushg 1
25:	invoke 23 0 0
31:	storeg 1
33:	pushthis 
34:	invoke 612 0 1
40:	rpop 
41:	rtnEventQ 0
43:	setThisStack
44:	pushthis 
45:	pushg 1
47:	rtn D


Class forAll#S#612 612 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 593
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	rpushg 2
19:	rpushg 1
21:	invoke 581 0 0
27:	pushthis 
28:	rpushg 2
30:	rpushg 2
32:	invoke 581 0 0
38:	eq 
39:	jmpFalse 66
42:	pushthis 
43:	rpushg 2
45:	pushthis 
46:	rpushg 2
48:	rpushg 1
50:	rpushg 1
52:	rpushg 1
54:	rpushg 1
56:	rpushg 1
58:	invoke 24 0 0
64:	storeg 1
66:	rtnInner


Class countNonZero 613 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 0
13:	storeg 1
15:	pushthis 
16:	invoke 614 0 1
22:	rpop 
23:	rtnEventQ 0
25:	setThisStack
26:	pushthis 
27:	pushg 1
29:	rtn D


Class forAll#S#614 614 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 593
enterE: 
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	invoke 615 0 1
23:	rpop 
24:	rtnInner


Class %if%then%%else%#S#615 615 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	rpushg 1
20:	pushthis 
21:	rpushg 3
23:	pushg 1
25:	pushc 0
27:	eq 
28:	toSuper 60
enterE: 
31:	rtnInner
doE: 
32:	mvStack
33:	rtnInner


Class print 616 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	innera 1
8:	rtnEventQ 1
doE: 
10:	doEventQ 
11:	mvStack
12:	pushText 1
14:	invoke 107 0 0
20:	rpop 
21:	pushthis 
22:	innerP 1
24:	popThisObj
25:	pushText 8
27:	invoke 107 0 0
33:	rpop 
34:	pushthis 
35:	invoke 617 0 1
41:	rpop 
42:	pushthis 
43:	rpushg 1
45:	rpushg 1
47:	rpushg 1
49:	rpushg 1
51:	rpushg 1
53:	invoke 66 0 0
59:	rpop 
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class %for%to%%do%#S#617 617 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushc 1
20:	pushthis 
21:	rpushg 2
23:	rpushg 1
25:	rpushg 5
27:	invoke 55 0 0
33:	toSuper 63
enterE: 
36:	rtnInner
doE: 
37:	mvStack
38:	rtnInner


Class #S#775 775 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	sendv 1
17:	rpop 
18:	break 1 49
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class #S#776 776 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	sendv 1
19:	rpop 
20:	pushthis 
21:	rpushg 1
23:	rpushg 1
25:	rpushg 1
27:	pushthis 
28:	rpushg 1
30:	rpushg 1
32:	rpushg 1
34:	pushg 3
36:	pushc 1
38:	+
39:	storeg 3
41:	break 1 81
45:	rtnEventQ 0
47:	setThisStack
48:	pushthis 
49:	rtn D


Class #S#777 777 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 84
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#778 778 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushthis 
12:	rpushg 2
14:	rpushg 2
16:	rpushg 1
18:	pushg 2
20:	pushc 1
22:	pushthis 
23:	rpushg 2
25:	pushg 3
27:	-
28:	+
29:	storeg 1
31:	pushc 48
33:	pushthis 
34:	rpushg 2
36:	rpushg 2
38:	rpushg 1
40:	rpushg 2
42:	pushthis 
43:	pushg 1
45:	xpushg 1
47:	+
48:	%prim put 2
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class #S#780 780 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	pushthis 
18:	rpushg 1
20:	rpushg 1
22:	rpushg 1
24:	rpushg 3
26:	rpushg 2
28:	rswap 
29:	rstoreg 2
31:	pushthis 
32:	rpushg 1
34:	rpushg 1
36:	rpushg 1
38:	innerP 1
40:	popThisObj
41:	pushthis 
42:	rpushg 1
44:	rpushg 1
46:	rpushg 1
48:	pushthis 
49:	rpushg 1
51:	rpushg 1
53:	rpushg 1
55:	rpushg 3
57:	rpushg 5
59:	rswap 
60:	rstoreg 3
62:	break 1 471
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class #S#781 781 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	pushthis 
18:	rpushg 1
20:	rpushg 1
22:	rpushg 1
24:	rpushg 3
26:	rpushg 2
28:	rswap 
29:	rstoreg 2
31:	pushthis 
32:	rpushg 1
34:	rpushg 1
36:	rpushg 1
38:	innerP 1
40:	popThisObj
41:	pushthis 
42:	rpushg 1
44:	rpushg 1
46:	rpushg 1
48:	pushthis 
49:	rpushg 1
51:	rpushg 1
53:	rpushg 1
55:	rpushg 3
57:	rpushg 4
59:	rswap 
60:	rstoreg 3
62:	break 1 474
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class #S#782 782 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 1
21:	rpushg 2
23:	invoke 83 0 0
29:	rswap 
30:	rstoreg 3
32:	pushthis 
33:	invoke 783 0 1
39:	rpop 
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class %if%then%%else%#S#783 783 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	rpushg 1
25:	rpushg 2
27:	pushNone 
28:	req 
29:	toSuper 60
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class #S#784 784 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 785 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#785 785 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 4
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	rpushg 1
20:	pushthis 
21:	rpushg 3
23:	rpushg 1
25:	rpushg 3
27:	rpushg 4
29:	pushNone 
30:	57
31:	toSuper 60
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class #S#786 786 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	rpushg 1
18:	rpushg 3
20:	rpushg 2
22:	rswap 
23:	rstoreg 2
25:	pushthis 
26:	rpushg 1
28:	rpushg 1
30:	pushthis 
31:	rpushg 1
33:	rpushg 1
35:	rpushg 3
37:	rpushg 4
39:	rswap 
40:	rstoreg 3
42:	pushthis 
43:	invoke 787 0 1
49:	rpop 
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class %if%then%%else%#S#787 787 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 1
23:	rpushg 1
25:	rpushg 3
27:	pushNone 
28:	57
29:	toSuper 60
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class body#SB#788 788 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 2
15:	pushthis 
16:	rpushg 2
18:	rpushg 2
20:	rpushg 1
22:	rpushg 1
24:	pushthis 
25:	rpushg 2
27:	pushg 3
29:	xpushg 1
31:	storeg 1
33:	pushthis 
34:	rpushg 2
36:	rpushg 2
38:	rpushg 2
40:	pushthis 
41:	rpushg 2
43:	rpushg 2
45:	pushg 1
47:	pushthis 
48:	rpushg 2
50:	pushg 3
52:	xstoreg 1
54:	rtnEventQ 0
56:	setThisStack
57:	pushthis 
58:	rtn D


Class body#SB#789 789 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 2
15:	pushthis 
16:	rpushg 2
18:	rpushg 2
20:	rpushg 1
22:	rpushg 2
24:	pushthis 
25:	rpushg 2
27:	pushg 3
29:	xpushg 1
31:	storeg 1
33:	pushthis 
34:	rpushg 2
36:	rpushg 2
38:	pushthis 
39:	rpushg 2
41:	rpushg 2
43:	rpushg 1
45:	pushg 1
47:	pushthis 
48:	rpushg 2
50:	pushg 3
52:	+
53:	storeg 2
55:	pushthis 
56:	rpushg 2
58:	rpushg 2
60:	rpushg 2
62:	pushthis 
63:	rpushg 2
65:	rpushg 2
67:	pushg 1
69:	pushthis 
70:	rpushg 2
72:	rpushg 2
74:	pushg 2
76:	xstoreg 1
78:	rtnEventQ 0
80:	setThisStack
81:	pushthis 
82:	rtn D


Class body#SB#790 790 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 2
15:	pushthis 
16:	rpushg 2
18:	rpushg 2
20:	rpushg 1
22:	pushthis 
23:	rpushg 2
25:	pushg 3
27:	xpushg 1
29:	storeg 1
31:	pushthis 
32:	rpushg 2
34:	rpushg 2
36:	innerP 1
38:	popThisObj
39:	rtnEventQ 0
41:	setThisStack
42:	pushthis 
43:	rtn D


Class body#SB#791 791 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 2
15:	rpushg 1
17:	pushthis 
18:	rpushg 2
20:	pushg 3
22:	xpushg 1
24:	%prim put 2
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class #S#792 792 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 289
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#793 793 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 2
15:	pushthis 
16:	rpushg 2
18:	rpushg 2
20:	rpushg 1
22:	rpushg 1
24:	pushthis 
25:	rpushg 2
27:	pushg 3
29:	xpushg 1
31:	storeg 1
33:	pushthis 
34:	rpushg 2
36:	rpushg 2
38:	pushthis 
39:	rpushg 2
41:	rpushg 2
43:	rpushg 1
45:	rpushg 2
47:	pushthis 
48:	rpushg 2
50:	pushg 3
52:	xpushg 1
54:	storeg 2
56:	pushthis 
57:	rpushg 2
59:	rpushg 2
61:	pushg 1
63:	pushthis 
64:	rpushg 2
66:	rpushg 2
68:	pushg 2
70:	ne 
71:	jmpFalse 82
74:	pushthis 
75:	invoke 989 0 1
81:	rpop 
82:	rtnEventQ 0
84:	setThisStack
85:	pushthis 
86:	rtn D


Class #S#794 794 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	pushg 1
17:	pushthis 
18:	rpushg 1
20:	rpushg 1
22:	rpushg 1
24:	pushg 1
26:	lt
27:	jmpFalse 34
30:	break 1 505
34:	rtnEventQ 0
36:	setThisStack
37:	pushthis 
38:	rtn D


Class thenPart#SB#795 795 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	pushthis 
22:	rpushg 2
24:	rpushg 3
26:	rpushg 1
28:	rpushg 1
30:	pushg 2
32:	pushthis 
33:	rpushg 2
35:	rpushg 3
37:	rpushg 1
39:	rpushg 1
41:	pushg 3
43:	le
44:	storeg 1
46:	break 3 382
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class elsePart#SB#796 796 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	pushthis 
22:	rpushg 2
24:	rpushg 3
26:	rpushg 1
28:	pushg 2
30:	pushthis 
31:	rpushg 2
33:	rpushg 3
35:	rpushg 1
37:	pushg 3
39:	lt
40:	storeg 1
42:	break 3 382
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class thenPart#SB#797 797 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	pushthis 
16:	rpushg 2
18:	rpushg 3
20:	pushg 2
22:	storeg 1
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	rtn D


Class elsePart#SB#798 798 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	pushthis 
16:	rpushg 2
18:	rpushg 3
20:	pushg 3
22:	storeg 1
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	rtn D


Class #S#799 799 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	%prim enable 12
12:	pushc 50
14:	%prim sleep 15
16:	break 1 306
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class #S#800 800 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	rpushg 2
19:	pushthis 
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	rpushg 1
28:	rpushg 3
30:	pushg 1
32:	storeg 1
34:	pushthis 
35:	rpushg 1
37:	rpushg 1
39:	rpushg 1
41:	pushc 0
43:	storeg 1
45:	pushthis 
46:	rpushg 1
48:	rpushg 1
50:	rpushg 1
52:	rpushg 2
54:	pushc 50
56:	%prim attach 10 D
59:	rpop 
60:	pushthis 
61:	rpushg 1
63:	rpushg 1
65:	rpushg 1
67:	pushc 1
69:	storeg 1
71:	pushthis 
72:	rpushg 1
74:	rpushg 1
76:	rpushg 1
78:	rpushg 2
80:	pushg 1
82:	pushthis 
83:	rpushg 1
85:	rpushg 1
87:	rpushg 1
89:	rpushg 1
91:	rpushg 3
93:	pushg 1
95:	eq 
96:	jmpFalse 107
99:	pushthis 
100:	invoke 990 0 1
106:	rpop 
107:	rtnEventQ 0
109:	setThisStack
110:	pushthis 
111:	rtn D


Class thenPart#SB#801 801 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	rpushg 5
23:	invoke 161 0 0
29:	jmpFalse 40
32:	pushthis 
33:	invoke 991 0 1
39:	rpop 
40:	pushthis 
41:	rpushg 2
43:	rpushg 3
45:	rpushg 1
47:	rpushg 1
49:	rpushg 1
51:	rpushg 4
53:	invoke 145 0 0
59:	rpop 
60:	pushthis 
61:	rpushg 2
63:	rpushg 3
65:	rpushg 1
67:	rpushg 1
69:	rpushg 1
71:	rpushg 4
73:	invoke 147 0 0
79:	jmpFalse 90
82:	pushthis 
83:	invoke 992 0 1
89:	rpop 
90:	rtnEventQ 0
92:	setThisStack
93:	pushthis 
94:	rtn D


Class elsePart#SB#802 802 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 2 309
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#803 803 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 1
19:	rpushg 2
21:	call D
23:	rpop 
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	rtn D


Class elsePart#SB#804 804 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 100
12:	%prim sleep 15
14:	break 2 312
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class #S#805 805 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 86
12:	%prim put 2
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#806 806 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushc 1
19:	storeg 1
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class elsePart#SB#807 807 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushthis 
18:	rpushg 2
20:	rpushg 3
22:	rpushg 1
24:	pushg 1
26:	pushc 1
28:	+
29:	storeg 1
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	rtn D


Class thenPart#SB#808 808 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushc 1
19:	storeg 1
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class elsePart#SB#809 809 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushthis 
18:	rpushg 2
20:	rpushg 3
22:	rpushg 1
24:	pushg 1
26:	pushc 1
28:	+
29:	storeg 1
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	rtn D


Class thenPart#SB#810 810 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	storeg 1
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class elsePart#SB#811 811 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	pushthis 
16:	rpushg 2
18:	rpushg 3
20:	rpushg 1
22:	rpushg 2
24:	pushthis 
25:	rpushg 2
27:	rpushg 3
29:	rpushg 1
31:	pushg 1
33:	pushc 1
35:	+
36:	xpushg 1
38:	storeg 1
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class thenPart#SB#812 812 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	storeg 1
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class elsePart#SB#813 813 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	pushthis 
16:	rpushg 2
18:	rpushg 3
20:	rpushg 1
22:	rpushg 2
24:	pushthis 
25:	rpushg 2
27:	rpushg 3
29:	rpushg 1
31:	pushg 1
33:	pushc 1
35:	-
36:	xpushg 1
38:	storeg 1
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class #S#814 814 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 257
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#815 815 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 2
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	pushthis 
22:	rpushg 2
24:	rpushg 2
26:	rpushg 1
28:	rpushg 2
30:	pushthis 
31:	rpushg 2
33:	pushg 3
35:	xpushg 1
37:	invoke 67 0 0
43:	rpop 
44:	pushText 1
46:	invoke 107 0 0
52:	rpop 
53:	rtnEventQ 0
55:	setThisStack
56:	pushthis 
57:	rtn D


Class #S#816 816 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 107 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#817 817 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 107 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#833 833 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 4
15:	pushthis 
16:	rpushg 1
18:	rpushg 4
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	rpushg 1
28:	rpushg 1
30:	invoke 24 0 0
36:	storeg 1
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class #S#834 834 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 359
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#835 835 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	%prim thisCore 17
12:	rpushg 2
14:	rpushg 2
16:	pushthis 
17:	rpushg 2
19:	rpushg 3
21:	rpushg 1
23:	rpushg 1
25:	rpushg 3
27:	pushg 2
29:	storeg 1
31:	pushthis 
32:	rpushg 2
34:	rpushg 3
36:	rpushg 1
38:	rpushg 1
40:	rpushg 5
42:	invoke 159 0 0
48:	rpop 
49:	pushthis 
50:	rpushg 2
52:	rpushg 3
54:	rpushg 1
56:	rpushg 3
58:	%prim thisCore 17
60:	rpushg 2
62:	rpushg 2
64:	invoke 90 0 0
70:	rpop 
71:	pushthis 
72:	rpushg 2
74:	rpushg 3
76:	%prim thisCore 17
78:	rpushg 2
80:	rpushg 2
82:	rswap 
83:	rstoreg 2
85:	pushthis 
86:	rpushg 2
88:	rpushg 3
90:	rpushg 1
92:	rpushg 2
94:	invoke 124 0 0
100:	rpop 
101:	pushthis 
102:	rpushg 2
104:	rpushg 3
106:	rpushg 2
108:	susp 
109:	rtnEventQ 0
111:	setThisStack
112:	pushthis 
113:	rtn D


Class elsePart#SB#836 836 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 2
19:	invoke 124 0 0
25:	rpop 
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class thenPart#SB#837 837 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	pushthis 
16:	rpushg 2
18:	rpushg 3
20:	rpushg 1
22:	rpushg 3
24:	invoke 93 0 0
30:	rswap 
31:	rstoreg 2
33:	pushthis 
34:	rpushg 2
36:	rpushg 3
38:	rpushg 2
40:	pushthis 
41:	rpushg 2
43:	rpushg 3
45:	rpushg 1
47:	rpushg 1
49:	rpushg 3
51:	pushg 1
53:	storeg 1
55:	pushthis 
56:	rpushg 2
58:	rpushg 3
60:	rpushg 1
62:	rpushg 1
64:	rpushg 5
66:	pushthis 
67:	rpushg 2
69:	rpushg 3
71:	rpushg 2
73:	invoke 152 0 0
79:	rpop 
80:	pushthis 
81:	rpushg 2
83:	rpushg 3
85:	rpushg 1
87:	rpushg 1
89:	rpushg 5
91:	invoke 160 0 0
97:	rpop 
98:	pushthis 
99:	rpushg 2
101:	rpushg 3
103:	rpushg 1
105:	rpushg 2
107:	invoke 124 0 0
113:	rpop 
114:	rtnEventQ 0
116:	setThisStack
117:	pushthis 
118:	rtn D


Class elsePart#SB#838 838 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 2
19:	invoke 124 0 0
25:	rpop 
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class #S#839 839 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	rpushg 2
19:	invoke 241 0 0
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	rpushg 2
35:	invoke 239 0 0
41:	rpop 
42:	break 1 366
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class #S#909 909 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	pushthis 
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	rpushg 2
24:	rswap 
25:	rstoreg 2
27:	pushthis 
28:	rpushg 1
30:	rpushg 1
32:	pushthis 
33:	rpushg 1
35:	rpushg 1
37:	rpushg 2
39:	pushg 1
41:	storeg 1
43:	break 1 514
47:	rtnEventQ 0
49:	setThisStack
50:	pushthis 
51:	rtn D


Class #S#910 910 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 107 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#911 911 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 107 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#912 912 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	pushthis 
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	rpushg 3
24:	rswap 
25:	rstoreg 3
27:	pushthis 
28:	rpushg 1
30:	rpushg 1
32:	pushthis 
33:	rpushg 1
35:	rpushg 1
37:	rpushg 3
39:	rpushg 2
41:	rswap 
42:	rstoreg 2
44:	break 1 521
48:	rtnEventQ 0
50:	setThisStack
51:	pushthis 
52:	rtn D


Class thenPart#SB#913 913 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushc 1
19:	storeg 2
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class elsePart#SB#914 914 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushthis 
18:	rpushg 2
20:	rpushg 3
22:	rpushg 1
24:	pushg 2
26:	pushc 1
28:	+
29:	storeg 2
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	rtn D


Class thenPart#SB#915 915 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushc 1
19:	storeg 2
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class elsePart#SB#916 916 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	pushthis 
18:	rpushg 2
20:	rpushg 3
22:	rpushg 1
24:	pushg 2
26:	pushc 1
28:	+
29:	storeg 2
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	rtn D


Class thenPart#SB#917 917 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	storeg 1
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class elsePart#SB#918 918 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	pushthis 
16:	rpushg 2
18:	rpushg 3
20:	rpushg 1
22:	rpushg 5
24:	pushthis 
25:	rpushg 2
27:	rpushg 3
29:	rpushg 1
31:	pushg 2
33:	pushc 1
35:	+
36:	xpushg 1
38:	storeg 1
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class thenPart#SB#919 919 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	storeg 1
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class elsePart#SB#920 920 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	pushthis 
16:	rpushg 2
18:	rpushg 3
20:	rpushg 1
22:	rpushg 5
24:	pushthis 
25:	rpushg 2
27:	rpushg 3
29:	rpushg 1
31:	pushg 2
33:	pushc 1
35:	-
36:	xpushg 1
38:	storeg 1
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class #S#921 921 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 3
17:	pushthis 
18:	rpushg 1
20:	pushg 1
22:	invoke 568 0 0
28:	rpop 
29:	pushthis 
30:	rpushg 1
32:	rpushg 1
34:	rpushg 5
36:	pushthis 
37:	rpushg 1
39:	pushg 2
41:	pushthis 
42:	rpushg 1
44:	pushg 1
46:	pushthis 
47:	rpushg 1
49:	rpushg 1
51:	rpushg 3
53:	pushg 1
55:	-
56:	pushc 1
58:	+
59:	xstoreg 1
61:	rtnEventQ 0
63:	setThisStack
64:	pushthis 
65:	rtn D


Class #S#922 922 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 3
17:	pushthis 
18:	rpushg 1
20:	pushg 1
22:	invoke 568 0 0
28:	rpop 
29:	pushthis 
30:	rpushg 1
32:	pushthis 
33:	rpushg 1
35:	rpushg 1
37:	rpushg 5
39:	pushthis 
40:	rpushg 1
42:	pushg 1
44:	pushthis 
45:	rpushg 1
47:	rpushg 1
49:	rpushg 3
51:	pushg 1
53:	-
54:	pushc 1
56:	+
57:	xpushg 1
59:	storeg 2
61:	rtnEventQ 0
63:	setThisStack
64:	pushthis 
65:	rtn D


Class #S#923 923 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 3
17:	pushthis 
18:	rpushg 1
20:	pushg 1
22:	invoke 568 0 0
28:	rpop 
29:	pushthis 
30:	rpushg 1
32:	rpushg 1
34:	rpushg 4
36:	pushthis 
37:	rpushg 1
39:	pushg 2
41:	invoke 568 0 0
47:	rpop 
48:	pushthis 
49:	pushthis 
50:	rpushg 1
52:	pushg 1
54:	pushthis 
55:	rpushg 1
57:	rpushg 1
59:	rpushg 3
61:	pushg 1
63:	-
64:	pushthis 
65:	rpushg 1
67:	rpushg 1
69:	rpushg 4
71:	pushg 3
73:	pushc 1
75:	pushthis 
76:	rpushg 1
78:	pushg 2
80:	pushthis 
81:	rpushg 1
83:	rpushg 1
85:	rpushg 4
87:	pushg 1
89:	-
90:	+
91:	+
92:	*
93:	storeg 1
95:	pushthis 
96:	rpushg 1
98:	rpushg 1
100:	rpushg 5
102:	pushthis 
103:	rpushg 1
105:	pushg 3
107:	pushthis 
108:	pushg 1
110:	xstoreg 1
112:	rtnEventQ 0
114:	setThisStack
115:	pushthis 
116:	rtn D


Class #S#924 924 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 3
17:	pushthis 
18:	rpushg 1
20:	pushg 1
22:	invoke 568 0 0
28:	rpop 
29:	pushthis 
30:	rpushg 1
32:	rpushg 1
34:	rpushg 4
36:	pushthis 
37:	rpushg 1
39:	pushg 2
41:	invoke 568 0 0
47:	rpop 
48:	pushthis 
49:	pushthis 
50:	rpushg 1
52:	pushg 1
54:	pushthis 
55:	rpushg 1
57:	rpushg 1
59:	rpushg 3
61:	pushg 1
63:	-
64:	pushthis 
65:	rpushg 1
67:	rpushg 1
69:	rpushg 4
71:	pushg 3
73:	pushc 1
75:	pushthis 
76:	rpushg 1
78:	pushg 2
80:	pushthis 
81:	rpushg 1
83:	rpushg 1
85:	rpushg 4
87:	pushg 1
89:	-
90:	+
91:	+
92:	*
93:	storeg 1
95:	pushthis 
96:	rpushg 1
98:	pushthis 
99:	rpushg 1
101:	rpushg 1
103:	rpushg 5
105:	pushthis 
106:	pushg 1
108:	xpushg 1
110:	storeg 3
112:	rtnEventQ 0
114:	setThisStack
115:	pushthis 
116:	rtn D


Class #S#925 925 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	rpushg 2
18:	invoke 561 0 0
24:	storeg 2
26:	pushthis 
27:	rpushg 1
29:	pushthis 
30:	rpushg 1
32:	rpushg 2
34:	invoke 562 0 0
40:	storeg 3
42:	pushthis 
43:	rpushg 1
45:	rpushg 1
47:	rpushg 3
49:	pushthis 
50:	rpushg 1
52:	pushg 2
54:	invoke 568 0 0
60:	rpop 
61:	pushthis 
62:	rpushg 1
64:	rpushg 1
66:	rpushg 4
68:	pushthis 
69:	rpushg 1
71:	pushg 3
73:	invoke 568 0 0
79:	rpop 
80:	pushthis 
81:	pushthis 
82:	rpushg 1
84:	pushg 2
86:	pushthis 
87:	rpushg 1
89:	rpushg 1
91:	rpushg 3
93:	pushg 1
95:	-
96:	pushthis 
97:	rpushg 1
99:	rpushg 1
101:	rpushg 4
103:	pushg 3
105:	pushc 1
107:	pushthis 
108:	rpushg 1
110:	pushg 3
112:	pushthis 
113:	rpushg 1
115:	rpushg 1
117:	rpushg 4
119:	pushg 1
121:	-
122:	+
123:	+
124:	*
125:	storeg 1
127:	pushthis 
128:	rpushg 1
130:	rpushg 1
132:	rpushg 5
134:	pushthis 
135:	rpushg 1
137:	pushg 1
139:	pushthis 
140:	pushg 1
142:	xstoreg 1
144:	rtnEventQ 0
146:	setThisStack
147:	pushthis 
148:	rtn D


Class #S#926 926 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	pushthis 
14:	rpushg 1
16:	rpushg 2
18:	invoke 561 0 0
24:	storeg 2
26:	pushthis 
27:	rpushg 1
29:	pushthis 
30:	rpushg 1
32:	rpushg 2
34:	invoke 562 0 0
40:	storeg 3
42:	pushthis 
43:	rpushg 1
45:	rpushg 1
47:	rpushg 3
49:	pushthis 
50:	rpushg 1
52:	pushg 2
54:	invoke 568 0 0
60:	rpop 
61:	pushthis 
62:	rpushg 1
64:	rpushg 1
66:	rpushg 4
68:	pushthis 
69:	rpushg 1
71:	pushg 3
73:	invoke 568 0 0
79:	rpop 
80:	pushthis 
81:	pushthis 
82:	rpushg 1
84:	pushg 2
86:	pushthis 
87:	rpushg 1
89:	rpushg 1
91:	rpushg 3
93:	pushg 1
95:	-
96:	pushthis 
97:	rpushg 1
99:	rpushg 1
101:	rpushg 4
103:	pushg 3
105:	pushc 1
107:	pushthis 
108:	rpushg 1
110:	pushg 3
112:	pushthis 
113:	rpushg 1
115:	rpushg 1
117:	rpushg 4
119:	pushg 1
121:	-
122:	+
123:	+
124:	*
125:	storeg 1
127:	pushthis 
128:	rpushg 1
130:	pushthis 
131:	rpushg 1
133:	rpushg 1
135:	rpushg 5
137:	pushthis 
138:	pushg 1
140:	xpushg 1
142:	storeg 1
144:	rtnEventQ 0
146:	setThisStack
147:	pushthis 
148:	rtn D


Class #S#927 927 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 546
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class #S#928 928 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 549
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#929 929 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 2
17:	pushthis 
18:	rpushg 2
20:	rpushg 3
22:	rpushg 2
24:	pushg 1
26:	storeg 1
28:	rtnEventQ 0
30:	setThisStack
31:	pushthis 
32:	rtn D


Class elsePart#SB#930 930 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 2
17:	pushthis 
18:	rpushg 2
20:	rpushg 3
22:	rpushg 2
24:	pushg 1
26:	pushc 1
28:	+
29:	storeg 1
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	rtn D


Class body#SB#931 931 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 2
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	rpushg 1
23:	rpushg 1
25:	pushthis 
26:	rpushg 2
28:	rpushg 2
30:	rpushg 1
32:	rpushg 5
34:	pushthis 
35:	rpushg 2
37:	pushg 3
39:	xpushg 1
41:	invoke 67 0 0
47:	rpop 
48:	pushText 1
50:	invoke 107 0 0
56:	rpop 
57:	rtnEventQ 0
59:	setThisStack
60:	pushthis 
61:	rtn D


Class thenPart#SB#981 981 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 1
19:	pushthis 
20:	rpushg 2
22:	rpushg 3
24:	rpushg 1
26:	rpushg 3
28:	rswap 
29:	rstoreg 2
31:	pushthis 
32:	rpushg 2
34:	rpushg 3
36:	rpushg 1
38:	rpushg 1
40:	pushthis 
41:	rpushg 2
43:	rpushg 3
45:	rpushg 1
47:	rpushg 1
49:	rpushg 2
51:	rswap 
52:	rstoreg 3
54:	rtnEventQ 0
56:	setThisStack
57:	pushthis 
58:	rtn D


Class elsePart#SB#982 982 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 3
19:	pushthis 
20:	rpushg 2
22:	rpushg 3
24:	rpushg 1
26:	rpushg 1
28:	rpushg 2
30:	rswap 
31:	rstoreg 5
33:	pushthis 
34:	rpushg 2
36:	rpushg 3
38:	rpushg 1
40:	rpushg 1
42:	rpushg 2
44:	pushthis 
45:	rpushg 2
47:	rpushg 3
49:	rpushg 1
51:	rpushg 3
53:	rswap 
54:	rstoreg 4
56:	pushthis 
57:	rpushg 2
59:	rpushg 3
61:	rpushg 1
63:	rpushg 1
65:	pushthis 
66:	rpushg 2
68:	rpushg 3
70:	rpushg 1
72:	rpushg 3
74:	rswap 
75:	rstoreg 2
77:	rtnEventQ 0
79:	setThisStack
80:	pushthis 
81:	rtn D


Class thenPart#SB#983 983 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 3
19:	rpushg 4
21:	pushthis 
22:	rpushg 2
24:	rpushg 3
26:	rpushg 1
28:	rpushg 3
30:	rpushg 5
32:	rswap 
33:	rstoreg 5
35:	pushthis 
36:	invoke 984 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#984 984 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 1
14:	rpushg 4
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	rpushg 1
24:	pushthis 
25:	rpushg 3
27:	rpushg 2
29:	rpushg 3
31:	rpushg 1
33:	rpushg 3
35:	rpushg 5
37:	pushNone 
38:	57
39:	toSuper 60
enterE: 
42:	rtnInner
doE: 
43:	mvStack
44:	rtnInner


Class elsePart#SB#985 985 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 4
19:	rpushg 1
21:	pushthis 
22:	rpushg 2
24:	rpushg 3
26:	rpushg 1
28:	rpushg 3
30:	rpushg 5
32:	rswap 
33:	rstoreg 2
35:	pushthis 
36:	invoke 986 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#986 986 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 1
14:	rpushg 4
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	rpushg 1
24:	pushthis 
25:	rpushg 3
27:	rpushg 2
29:	rpushg 3
31:	rpushg 1
33:	rpushg 4
35:	rpushg 1
37:	rpushg 2
39:	pushNone 
40:	57
41:	toSuper 60
enterE: 
44:	rtnInner
doE: 
45:	mvStack
46:	rtnInner


Class thenPart#SB#987 987 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 1
19:	rpushg 3
21:	pushNone 
22:	rswap 
23:	rstoreg 5
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class elsePart#SB#988 988 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 1
17:	rpushg 1
19:	pushNone 
20:	rswap 
21:	rstoreg 2
23:	rtnEventQ 0
25:	setThisStack
26:	pushthis 
27:	rtn D


Class #S#989 989 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 2
15:	rpushg 2
17:	rpushg 1
19:	pushthis 
20:	rpushg 1
22:	rpushg 2
24:	rpushg 2
26:	rpushg 1
28:	rpushg 1
30:	rpushg 1
32:	rpushg 1
34:	invoke 23 0 0
40:	storeg 1
42:	break 3 289
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class #S#990 990 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 1
17:	rpushg 1
19:	rpushg 1
21:	rpushg 5
23:	pushthis 
24:	rpushg 1
26:	rpushg 1
28:	rpushg 1
30:	rpushg 1
32:	rpushg 2
34:	invoke 152 0 0
40:	rpop 
41:	rtnEventQ 0
43:	setThisStack
44:	pushthis 
45:	rtn D


Class #S#991 991 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 100
12:	%prim sleep 15
14:	break 3 309
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class #S#992 992 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 50
12:	%prim sleep 15
14:	pushthis 
15:	rpushg 1
17:	rpushg 2
19:	rpushg 3
21:	rpushg 1
23:	rpushg 1
25:	rpushg 1
27:	rpushg 4
29:	invoke 143 0 0
35:	rpop 
36:	break 3 309
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class thenPart#SB#1011 1011 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 2
17:	rpushg 3
19:	rpushg 1
21:	rpushg 3
23:	rpushg 5
25:	pushthis 
26:	rpushg 2
28:	rpushg 3
30:	rpushg 2
32:	rpushg 3
34:	rpushg 1
36:	rpushg 3
38:	rpushg 4
40:	rswap 
41:	rstoreg 4
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class elsePart#SB#1012 1012 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 2
17:	rpushg 3
19:	rpushg 1
21:	rpushg 4
23:	rpushg 1
25:	pushthis 
26:	rpushg 2
28:	rpushg 3
30:	rpushg 2
32:	rpushg 3
34:	rpushg 1
36:	rpushg 3
38:	rpushg 4
40:	rswap 
41:	rstoreg 3
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class thenPart#SB#1013 1013 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 2
17:	rpushg 3
19:	rpushg 1
21:	rpushg 4
23:	rpushg 1
25:	rpushg 2
27:	pushNone 
28:	rswap 
29:	rstoreg 4
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	rtn D


Class elsePart#SB#1014 1014 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	rpushg 2
13:	rpushg 3
15:	rpushg 2
17:	rpushg 3
19:	rpushg 1
21:	rpushg 4
23:	rpushg 1
25:	pushNone 
26:	rswap 
27:	rstoreg 3
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class main 1016 0
allocE:
1:	pushthis 
2:	invoke 1 0 1
8:	stop 


Class EventProcessor 1017 0
allocE:
1:	stop 


Class ThreadStub 1018 0
allocE:
doE: 
1:	mvStack
2:	call D
4:	stop 

