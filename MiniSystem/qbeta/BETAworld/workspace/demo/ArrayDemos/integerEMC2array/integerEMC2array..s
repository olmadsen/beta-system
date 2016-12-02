	-- QBETA
	-- Module:gen: 
	component Comp NoOfDescs: 734
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
	invoke 222 4 workspace
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
	invoke 160 3 Complex
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
	invoke 165 5 EMC2array
	rpop
	-- Module:gen: 
	-- ModuleItem:gen ForkJoinSystem
	-- ConsRef:gen: ForkJoinSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 6
	pushThis 
	invoke 190 6 ForkJoinSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen MonitorSystem
	-- ConsRef:gen: MonitorSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 7
	pushThis 
	invoke 197 7 MonitorSystem
	rpop
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen String
	-- ConsRef:gen: String
	-- ObjectGenerator:gen: super: :singular:staticOff: 9
	pushThis 
	invoke 89 9 String
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

	class workspace 222
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: dummy
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen demo
	-- ConsRef:gen: demo
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 422 4 demo
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

	class Complex 160
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
	-- ModuleItem:gen mQueue
	-- ConsRef:gen: mQueue
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 74 2 mQueue
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

	class EMC2array 165
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

	class ForkJoinSystem 190
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

	class MonitorSystem 197
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

	class String 89
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

	class demo 422
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: olsen_nils
	-- Module:gen: 
	-- ModuleItem:gen ArrayDemos
	-- ConsRef:gen: ArrayDemos
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 423 2 ArrayDemos
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cond
	pushg 1 cond
	jmpFalse L50
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 552 0 #S#552
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

	class BasicSystem 112
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
	invoke 129 2 cores
	rpop
	-- ConsRef:gen: P_status
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 131 3 P_status
	rpop
	-- pattern:gen: ProcessQueue
	-- ConsRef:gen: sch
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 134 4 sch
	rpop
	-- ConsRef:gen: SQS
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 142 5 SQS
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 6 Lock
	rpop
	-- ConsRef:gen: console
	-- ObjectGenerator:gen: super: :singular:staticOff: 7
	pushThis 
	invoke 156 7 console
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 159 0 init
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
	-- next not assign: init :E: cores
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: cores
	rpushg 2 cores
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 130 0 init
	rpop
 L57:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Complex 161
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

	class mQueue 74
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

	class Array 166
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
	-- vdtAdd: inx=1 descInx=177
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

	class Range 179
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
	invoke 593 0 #S#593
	rpop
 L66:
 L65:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class D1_Array 182
	pushThis 
	rstoreg 3 R
	rstore 1 origin
	allocEventQ
	-- super Array
	--  1:177 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=182
	-- Invocation:loadOrigin: Array
	-- Invocation:loadOrigin:scan: Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  166
	-- pattern:gen: putAt(inx: ? integer,exp: ? integer) -> res: ? Array
	-- pattern:gen: getAt(inx: ? integer) -> res: ? integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=185
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

	class D2_Array 186
	pushThis 
	rstoreg 4 R2
	pushThis 
	rstoreg 3 R1
	rstore 1 origin
	allocEventQ
	-- super Array
	--  1:177 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=186
	-- Invocation:loadOrigin: Array
	-- Invocation:loadOrigin:scan: Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  166
	-- pattern:gen: putAt(inx1: ? integer,inx2: ? integer,exp: ? integer) -> res: ? D2_Array
	-- pattern:gen: getAt(inx1: ? integer,inx2: ? integer) -> exp: ? integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=189
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
	invoke 100 0 print
	rpop
 L70:
	rtnInner
	end 1

	class ForkJoinSystem 191
	rstore 1 origin
	allocEventQ
	-- super BasicSystem
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=191
	-- Invocation:loadOrigin: BasicSystem
	-- Invocation:loadOrigin:scan: BasicSystem
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: BasicSystem
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  112
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

	class System 198
	rstore 8 origin
	allocEventQ
	-- super BasicSystem
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=198
	-- Invocation:loadOrigin: LIB.BasicSystem.basicSystem
	-- Invocation:loadOrigin:scan: LIB
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: LIB
	-- AdjustOrigin: 8
	rpushg 8 origin
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
	topSuper  112
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

	class String 90
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

	class ArrayDemos 423
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: _xxx
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen integerEMC2array
	-- ConsRef:gen: integerEMC2array
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 450 5 integerEMC2array
	rpop
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

	class #S#552 552
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
	invoke 553 0 #S#553
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
	invoke 554 0 #S#554
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

	class Lock 113
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

	class BasicProcess 118
	pushThis 
	rstoreg 2 id
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: status
	-- pattern:gen: start
	-- vdtAdd: inx=1 descInx=119
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

	class Scheduler 120
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
	invoke 136 0 add
	rpop
	-- ObjectGenerator:gen: super: do:IS-empty: staticOff: 0
	-- Invocation:gen: do
	-- Invocation:loadOrigin: do
	-- Invocation:loadOrigin:scan: do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: do
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 121 0 do
	rpop
 L94:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Core 124
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 126 0 do
	rpop
 L96:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class cores 129
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

	class P_status 131
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

	class Queue 75
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

	class ProcessQueue 132
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
	rpushg 2 mQueue
	-- Invocation:loadOrigin:scan: Queue
	-- Unary:loadArgs: 
	topSuper  75
	-- pattern:gen: display
	rtnInner
	DO:
	mvStack 
 L103:
	-- Include:gen: 
 L104:
	rtnInner
	end 1

	class sch 134
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 2 Lock
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

	class SQS 142
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 132 2 ProcessQueue
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 3 Lock
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

	class console 156
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 2 Lock
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

	class init 159
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
	invoke 144 0 init
	rpop
 L112:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class + 162
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
	invoke 161 0 Complex
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

	class - 163
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
	invoke 161 0 Complex
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

	class display 164
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

	class put 167
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
	invoke 168 0 %if%then%%else%#S#168
	rpop
	-- ObjectGenerator:gen: super: res := %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: res := %this Array
	-- Invocation:loadOrigin: res := %this Array
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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

	class get 169
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
	invoke 170 0 %if%then%%else%#S#170
	rpop
 L122:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class nxt 171
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
	invoke 172 0 %if%then%%else%#S#172
	rpop
 L124:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class prv 173
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
	invoke 174 0 %if%then%%else%#S#174
	rpop
 L126:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class forAll 175
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 176 0 loop
	rpop
 L128:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 177
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
	invoke 100 0 print
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
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print:IS-empty: staticOff: 0
	pushThis 
	invoke 178 0 %for%to%%do%#S#178
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
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

	class check 180
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
	invoke 592 0 #S#592
	rpop
 L133:
 L132:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 181
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

	class #S#593 593
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
	invoke 100 0 print
	rpop
 L137:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class putAt 183
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: rep.%put exp %at% (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put exp %at% (inx - R.low) + 1
	-- Invocation:loadOrigin: rep.%put exp %at% (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
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

	class getAt 184
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: res := rep.%get (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin: res := rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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

	class print 185
	rstore 2 origin
	allocEventQ
	-- super print
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=185
	pushThis 
	rpushg 2 iOrigin
	topSuper  177
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
	invoke 181 0 print
	rpop
 L143:
	rtnInner
	end 1

	class putAt 187
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
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

	class getAt 188
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: R2.check(inx2):IS-empty: staticOff: 0
	-- Invocation:gen: R2.check(inx2)
	-- Invocation:loadOrigin: R2.check(inx2)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: repPos := (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: repPos
	-- AdjustOrigin: 0
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

	class print 189
	rstore 2 origin
	allocEventQ
	-- super print
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=189
	pushThis 
	rpushg 2 iOrigin
	topSuper  177
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
	invoke 181 0 print
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
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: R2.print:IS-empty: staticOff: 0
	-- Invocation:gen: R2.print
	-- Invocation:loadOrigin: R2.print
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
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
	invoke 181 0 print
	rpop
 L149:
	rtnInner
	end 1

	class ForkJoin 192
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 132 2 ProcessQueue
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 3 Lock
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
	-- next not assign: init :E: M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 114 0 init
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: AwaitTermination
	invoke 194 0 AwaitTermination
	rpop
 L151:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Semaphore 199
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 2 Lock
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 132 3 ProcessQueue
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

	class Process 205
	rstore 1 origin
	allocEventQ
	-- super BasicProcess
	--  1:119 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=205
	-- Invocation:loadOrigin: BasicProcess
	-- Invocation:loadOrigin:scan: BasicProcess
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: BasicProcess
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  118
	-- pattern:gen: start
	-- vdtAdd: inx=1 descInx=206
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

	class Monitor 207
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Semaphore
	invoke 199 2 Semaphore
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

	class length 91
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

	class + 93
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 91 0 length
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: doplus
	invoke 94 0 doplus
	rpop
 L161:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	rpushg 3 V
	rtn(D)
	end 1

	class asLowerCase 97
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

	class scan 98
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
	invoke 99 0 %for%to%%do%#S#99
	rpop
 L165:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 100
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
	invoke 101 0 %for%to%%do%#S#101
	rpop
 L167:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class = 102
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 103 3 loop
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

	class <= 105
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 106 3 loop
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

	class integerEMC2array 450
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Array
	rtnEventQ 0
	DO:
	mvStack 
 L172:
	-- Include:gen: 
 L173:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#553 553
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

	class #S#554 554
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

	class body#SB#555 555
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

	class init 114
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

	class get 115
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: res
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 116 2 loop
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

	class free 117
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

	class start 119
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

	class do 121
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 122 2 loop
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

	class attach 125
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

	class do 126
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loopX
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 127 2 loopX
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

	class init 130
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 125 0 attach
	rpop
	-- ObjectGenerator:gen: super: S := Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: S := Scheduler
	-- Invocation:loadOrigin: S := Scheduler
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 125 0 attach
	rpop
	-- ObjectGenerator:gen: super: S := Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: S := Scheduler
	-- Invocation:loadOrigin: S := Scheduler
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 125 0 attach
	rpop
	-- ObjectGenerator:gen: super: C4.attach(Scheduler):IS-empty: staticOff: 0
	-- Invocation:gen: C4.attach(Scheduler)
	-- Invocation:loadOrigin: C4.attach(Scheduler)
	-- Invocation:loadOrigin:scan: C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C4
	-- AdjustOrigin: 0
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 125 0 attach
	rpop
 L195:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Element 76
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

	class scan 77
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 78 0 do
	rpop
 L199:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scanFromLast 80
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 81 0 do
	rpop
 L201:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class insert 83
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: b
	pushg 1 b
	jmpFalse L204
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 558 0 #S#558
	rpop
 L204:
 L203:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class remove 84
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
	invoke 85 0 scan#S#85
	rpop
 L206:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class removeNext 86
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
	invoke 562 0 #S#562
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

	class isEmpty 87
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

	class clear 88
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

	class display 133
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

	class entry 135
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
	invoke 115 0 get
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
	invoke 117 0 free
	rpop
 L217:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class add 136
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
	invoke 137 0 entry#S#137
	rpop
 L219:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class dcr 138
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
	invoke 139 0 entry#S#139
	rpop
 L221:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class running 140
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
	invoke 141 0 entry#S#141
	rpop
 L223:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class entry 143
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
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: V := V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V := V + 1
	-- Invocation:loadOrigin: V := V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
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
	invoke 581 0 #S#581
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
	invoke 117 0 free
	rpop
 L225:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 144
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=144
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
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

	class insert 145
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=145
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 83 0 insert
	rpop
 L230:
	rtnInner
	end 1

	class removeNext 146
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
	invoke 147 0 entry#S#147
	rpop
 L232:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: P
	rpushg 2 P
	rtn(D)
	end 1

	class remove 148
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=148
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: remove(elm: ? Object)
	invoke 84 0 remove
	rpop
 L234:
	rtnInner
	end 1

	class isEmpty 149
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
	invoke 150 0 entry#S#150
	rpop
 L236:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class display 151
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
	-- Unary:loadArgs: 
	topSuper  143
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
	invoke 133 0 display
	rpop
 L238:
	rtnInner
	end 1

	class addWaiting 152
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
	-- Unary:loadArgs: 
	topSuper  143
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

	class dcrWaiting 153
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=153
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
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

	class hasWaiting 154
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
	invoke 155 0 entry#S#155
	rpop
 L244:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class init 157
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
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: L.init:IS-empty: staticOff: 0
	-- Invocation:gen: L.init
	-- Invocation:loadOrigin: L.init
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
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
	invoke 114 0 init
	rpop
	-- ObjectGenerator:gen: super: L.free:IS-empty: staticOff: 0
	-- Invocation:gen: L.free
	-- Invocation:loadOrigin: L.free
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
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
	invoke 117 0 free
	rpop
 L246:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 158
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
	invoke 115 0 get
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
	invoke 117 0 free
	rpop
 L248:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#168 168
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

	class %if%then%%else%#S#170 170
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

	class %if%then%%else%#S#172 172
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

	class %if%then%%else%#S#174 174
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

	class loop 176
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
	invoke 590 0 #S#590
	rpop
 L259:
 L258:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#178 178
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

	class #S#592 592
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
	invoke 100 0 print
	rpop
 L263:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class run 193
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
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: Q.insert(P):IS-empty: staticOff: 0
	-- Invocation:gen: Q.insert(P)
	-- Invocation:loadOrigin: Q.insert(P)
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 83 0 insert
	rpop
	-- ObjectGenerator:gen: super: SQS.insert(P):IS-empty: staticOff: 0
	-- Invocation:gen: SQS.insert(P)
	-- Invocation:loadOrigin: SQS.insert(P)
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 145 0 insert
	rpop
	-- ObjectGenerator:gen: super: M.free:IS-empty: staticOff: 0
	-- Invocation:gen: M.free
	-- Invocation:loadOrigin: M.free
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
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
	invoke 117 0 free
	rpop
 L265:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class AwaitTermination 194
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 195 2 loop
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

	class init 200
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

	class wait 201
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
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: cnt := cnt - 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt := cnt - 1
	-- Invocation:loadOrigin: cnt := cnt - 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
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
	invoke 202 0 %if%then%%else%#S#202
	rpop
 L271:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class signal 203
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
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: cnt := cnt + 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt := cnt + 1
	-- Invocation:loadOrigin: cnt := cnt + 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
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
	invoke 204 0 %if%then%%else%#S#204
	rpop
 L273:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class start 206
	rstore 2 origin
	allocEventQ
	-- super start
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=206
	pushThis 
	rpushg 2 iOrigin
	topSuper  119
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
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: id.print:IS-empty: staticOff: 0
	-- Invocation:gen: id.print
	-- Invocation:loadOrigin: id.print
	-- Invocation:loadOrigin:scan: id
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: id
	-- AdjustOrigin: 0
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
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 3 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 145 0 insert
	rpop
 L275:
	rtnInner
	end 1

	class init 208
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
	invoke 200 0 init
	rpop
 L277:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry 209
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
	invoke 201 0 wait
	rpop
	-- ObjectGenerator:gen: super: V := V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V := V + 1
	-- Invocation:loadOrigin: V := V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
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
	invoke 203 0 signal
	rpop
 L279:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class wait 210
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: cond
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 211 2 loop
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

	class doplus 94
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
	invoke 91 0 length
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
	invoke 95 0 %for%to%%do%#S#95
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i:IS-empty: staticOff: 0
	pushThis 
	invoke 96 0 %for%to%%do%#S#96
	rpop
	-- ObjectGenerator:gen: super: V := T.asString:IS-empty: staticOff: 0
	-- Invocation:gen: V := T.asString
	-- Invocation:loadOrigin: V := T.asString
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
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

	class %for%to%%do%#S#99 99
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 91 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L284:
 L285:
	rtnInner
	end 1

	class %for%to%%do%#S#101 101
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 91 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L286:
 L287:
	rtnInner
	end 1

	class loop 103
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 91 0 length
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
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:load: <> V: ? integer -> B: ? Boolean
	55
	jmpFalse L290
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 568 0 #S#568
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
	invoke 104 0 %for%to%%do%#S#104
	rpop
 L289:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 106
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 91 0 length
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
	invoke 91 0 length
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
	invoke 111 0 %if%then%%else%#S#111
	rpop
	-- ObjectGenerator:gen: super: matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: matchEq
	-- Invocation:loadOrigin: matchEq
	-- Invocation:loadOrigin:scan: matchEq
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: matchEq
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: matchEq
	invoke 107 0 matchEq
	rpop
 L292:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Array 451
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: pos
	-- VarRef:gen: noof
	-- VarRef:gen: rep
	-- pattern:gen: put(e: ? integer) -> res: ? Array
	-- pattern:gen: get -> res: ? integer
	-- pattern:gen: nxt -> res: ? integer
	-- pattern:gen: prv -> res: ? integer
	-- pattern:gen: forAll
	-- pattern:gen: forAllIndex
	-- pattern:gen: fill(v: ? integer)
	-- pattern:gen: sum -> s: ? integer
	-- pattern:gen: iadd(a: ? Array)
	-- pattern:gen: equal(a: ? Array) -> b: ? boolean
	-- pattern:gen: greaterThan(a: ? Array) -> b: ? boolean
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L293:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
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
 L294:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 116
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L295:
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
	jmpFalse L297
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 575 0 #S#575
	rpop
 L297:
 L296:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 122
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L298:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inScheduler := 1:IS-empty: staticOff: 0
	-- Invocation:gen: inScheduler := 1
	-- Invocation:loadOrigin: inScheduler := 1
	-- Invocation:loadOrigin:scan: inScheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inScheduler
	-- AdjustOrigin: 0
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
	invoke 146 0 removeNext
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
	jmpFalse L300
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 576 0 #S#576
	rpop
 L300:
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
	invoke 123 0 %if%then%%else%#S#123
	rpop
 L299:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loopX 127
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L301:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if main <> none %then% 
    main.resume %else% 
    sleep(100)
    %restart loopX:IS-empty: staticOff: 0
	pushThis 
	invoke 128 0 %if%then%%else%#S#128
	rpop
 L302:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 78
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 79 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L303:
	-- Include:gen: 
 L304:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 81
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 82 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L305:
	-- Include:gen: 
 L306:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#558 558
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L307:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: E := Element(elm):IS-empty: staticOff: 0
	-- Invocation:gen: E := Element(elm)
	-- Invocation:loadOrigin: E := Element(elm)
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Function:invoke: 
	-- pattern:load: Element(elm: ? Object) -> res: ? Element
	invoke 76 0 Element
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
	invoke 559 0 %if%then%%else%#S#559
	rpop
 L308:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scan#S#85 85
	rstore 4 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=85
	-- Invocation:loadOrigin: scan
	-- Invocation:loadOrigin:scan: scan
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: scan
	-- AdjustOrigin: 4
	rpushg 4 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  77
	rtnInner
	DO:
	doEventQ
	mvStack 
 L309:
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	rpushg 2 current
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	jmpFalse L311
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 560 0 #S#560
	rpop
 L311:
 L310:
	rtnInner
	end 1

	class #S#562 562
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L312:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: elm := last.elm:IS-empty: staticOff: 0
	-- Invocation:gen: elm := last.elm
	-- Invocation:loadOrigin: elm := last.elm
	-- Invocation:loadOrigin:scan: elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elm
	-- AdjustOrigin: 0
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
	invoke 563 0 %if%then%%else%#S#563
	rpop
 L313:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry#S#137 137
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=137
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  135
	rtnInner
	DO:
	doEventQ
	mvStack 
 L314:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := M + 1:IS-empty: staticOff: 0
	-- Invocation:gen: M := M + 1
	-- Invocation:loadOrigin: M := M + 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
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
 L315:
	rtnInner
	end 1

	class entry#S#139 139
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=139
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  135
	rtnInner
	DO:
	doEventQ
	mvStack 
 L316:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := M - 1:IS-empty: staticOff: 0
	-- Invocation:gen: M := M - 1
	-- Invocation:loadOrigin: M := M - 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
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
 L317:
	rtnInner
	end 1

	class entry#S#141 141
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=141
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  135
	rtnInner
	DO:
	doEventQ
	mvStack 
 L318:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := M > 0:IS-empty: staticOff: 0
	-- Invocation:gen: B := M > 0
	-- Invocation:loadOrigin: B := M > 0
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
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
 L319:
	rtnInner
	end 1

	class #S#581 581
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L320:
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
 L321:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry#S#147 147
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=147
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L322:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: P := Q.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: P := Q.removeNext
	-- Invocation:loadOrigin: P := Q.removeNext
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
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
	invoke 86 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 P
 L323:
	rtnInner
	end 1

	class entry#S#150 150
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=150
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L324:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := Q.isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: B := Q.isEmpty
	-- Invocation:loadOrigin: B := Q.isEmpty
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
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
	invoke 87 0 isEmpty
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L325:
	rtnInner
	end 1

	class entry#S#155 155
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=155
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L326:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := W > 0:IS-empty: staticOff: 0
	-- Invocation:gen: B := W > 0
	-- Invocation:loadOrigin: B := W > 0
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
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
 L327:
	rtnInner
	end 1

	class thenPart#SB#582 582
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L328:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
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
 L329:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#583 583
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L330:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
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
 L331:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#584 584
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L332:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
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
 L333:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#585 585
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L334:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := pos + 1
	-- Invocation:loadOrigin: pos := pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
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
 L335:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#586 586
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L336:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: res := 9999999
	-- Invocation:loadOrigin: res := 9999999
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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
 L337:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#587 587
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L338:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos + 1
	-- Invocation:loadOrigin: res := rep.%get pos + 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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
 L339:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#588 588
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L340:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: res := 9999999
	-- Invocation:loadOrigin: res := 9999999
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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
 L341:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#589 589
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L342:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos - 1
	-- Invocation:loadOrigin: res := rep.%get pos - 1
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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
 L343:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#590 590
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L344:
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
 L345:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#591 591
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L346:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: putint(rep.%get inx):IS-empty: staticOff: 0
	-- Invocation:gen: putint(rep.%get inx)
	-- Invocation:loadOrigin: putint(rep.%get inx)
	-- Invocation:loadOrigin:scan: putint(rep.%get inx)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(rep.%get inx)
	-- AdjustOrigin: 0
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
	invoke 100 0 print
	rpop
 L347:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 195
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: P
	-- VarRef:gen: continue
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L348:
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
	invoke 196 0 scan#S#196
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: continue
	pushg 1 continue
	jmpFalse L350
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 596 0 #S#596
	rpop
 L350:
	-- ObjectGenerator:gen: super: Q.clear:IS-empty: staticOff: 0
	-- Invocation:gen: Q.clear
	-- Invocation:loadOrigin: Q.clear
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
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
	invoke 88 0 clear
	rpop
 L349:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#202 202
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
 L351:
 L352:
	rtnInner
	end 1

	class %if%then%%else%#S#204 204
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
 L353:
 L354:
	rtnInner
	end 1

	class loop 211
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L355:
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
	jmpFalse L357
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 601 0 #S#601
	rpop
 L357:
 L356:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#95 95
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L358:
 L359:
	rtnInner
	end 1

	class %for%to%%do%#S#96 96
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
	invoke 91 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L360:
 L361:
	rtnInner
	end 1

	class body#SB#566 566
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L362:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: current := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: current := %get inx
	-- Invocation:loadOrigin: current := %get inx
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- AdjustOrigin: 0
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
 L363:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#567 567
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L364:
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
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L365:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#568 568
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L366:
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
 L367:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#104 104
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
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 91 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L368:
 L369:
	rtnInner
	end 1

	class matchEq 107
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx
	-- VarRef:gen: c1
	-- VarRef:gen: c2
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 108 2 loop
	rpop
	-- ConsRef:gen: doit
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 109 3 doit
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L370:
	-- Include:gen: 
 L371:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#111 111
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
 L372:
 L373:
	rtnInner
	end 1

	class put 452
	pushThis 
	storeg 1 e
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L374:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: rep.%put e %at% pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put e %at% pos
	-- Invocation:loadOrigin: rep.%put e %at% pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
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
	invoke 453 0 %if%then%%else%#S#453
	rpop
	-- ObjectGenerator:gen: super: res := %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: res := %this Array
	-- Invocation:loadOrigin: res := %this Array
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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
 L375:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class get 454
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L376:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get pos
	-- Invocation:loadOrigin: res := rep.%get pos
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- AdjustOrigin: 0
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
	invoke 455 0 %if%then%%else%#S#455
	rpop
 L377:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class nxt 456
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L378:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = noof %then% 
    res := 999999 %else% 
    res := rep.%get pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 457 0 %if%then%%else%#S#457
	rpop
 L379:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class prv 458
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L380:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = 1 %then% 
    res := 999999 %else% 
    res := rep.%get pos - 1:IS-empty: staticOff: 0
	pushThis 
	invoke 459 0 %if%then%%else%#S#459
	rpop
 L381:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class forAll 460
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
 L382:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 461 0 loop
	rpop
 L383:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class forAllIndex 462
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
 L384:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: pos := 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos := 1
	-- Invocation:loadOrigin: pos := 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
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
	-- ObjectGenerator:gen: super: inx := pos:IS-empty: staticOff: 0
	-- Invocation:gen: inx := pos
	-- Invocation:loadOrigin: inx := pos
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
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
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 463 0 loop
	rpop
 L385:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class fill 464
	pushThis 
	storeg 2 v
	rstore 1 origin
	allocEventQ
	-- super forAllIndex
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=464
	-- Invocation:loadOrigin: forAllIndex
	-- Invocation:loadOrigin:scan: forAllIndex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAllIndex
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  462
	rtnInner
	DO:
	doEventQ
	mvStack 
 L386:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: rep.%put v %at% inx:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put v %at% inx
	-- Invocation:loadOrigin: rep.%put v %at% inx
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- next not assign: %put v %at% inx :E: rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
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
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: v
	pushg 2 v
	-- name::gen: 
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	xstoreg 1 inx
 L387:
	rtnInner
	end 1

	class sum 465
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L388:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: s := 0:IS-empty: staticOff: 0
	-- Invocation:gen: s := 0
	-- Invocation:loadOrigin: s := 0
	-- Invocation:loadOrigin:scan: s
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: s
	-- AdjustOrigin: 0
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
	invoke 466 0 forAll#S#466
	rpop
 L389:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: s
	pushg 1 s
	rtn(D)
	end 1

	class iadd 467
	pushThis 
	rstoreg 2 a
	rstore 1 origin
	allocEventQ
	-- super forAll
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=467
	-- Invocation:loadOrigin: forAll
	-- Invocation:loadOrigin:scan: forAll
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: forAll
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  460
	rtnInner
	DO:
	doEventQ
	mvStack 
 L390:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(current + a.get):IS-empty: staticOff: 0
	-- Invocation:gen: put(current + a.get)
	-- Invocation:loadOrigin: put(current + a.get)
	-- Invocation:loadOrigin:scan: put(current + a.get)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: put(current + a.get)
	-- AdjustOrigin: 0
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
	-- next not assign: get :E: a
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: a
	rpushg 2 a
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get -> res: ? integer
	invoke 454 0 get
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: put(e: ? integer) -> res: ? Array
	invoke 452 0 put
	rpop
 L391:
	rtnInner
	end 1

	class equal 468
	pushThis 
	rstoreg 2 a
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L392:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: b := false:IS-empty: staticOff: 0
	-- Invocation:gen: b := false
	-- Invocation:loadOrigin: b := false
	-- Invocation:loadOrigin:scan: b
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: b
	-- AdjustOrigin: 0
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
	invoke 469 0 forAll#S#469
	rpop
 L393:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: b
	pushg 1 b
	rtn(D)
	end 1

	class greaterThan 0
