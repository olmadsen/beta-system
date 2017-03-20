	-- QBETA
	-- Module:gen: 
	component Comp NoOfDescs: 1179
	-- ConsRef:gen: BETAworld

	class Object 24
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
	invoke 76 3 LIB
	rpop
	-- Module:gen: 
	-- ModuleItem:gen workspace
	-- ConsRef:gen: workspace
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 299 4 workspace
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
	-- pattern:gen: integer
	-- pattern:gen: Boolean
	-- pattern:gen: False -> B: ? Boolean
	-- pattern:gen: True -> B: ? Boolean
	-- pattern:gen: char
	-- pattern:gen: put(ch: ? char)
	-- pattern:gen: _iget -> ch: ? char
	-- pattern:gen: _kbhit -> B: ? Boolean
	-- pattern:gen: Object
	-- pattern:gen: none
	-- pattern:gen: immutable
	-- pattern:gen: inner
	-- pattern:gen: %inner P: ? Object
	-- pattern:gen: %this P: ? Object
	-- pattern:gen: disable
	-- pattern:gen: enable
	-- pattern:gen: fork(S: ? Object)
	-- pattern:gen: sleep(V: ? integer)
	-- pattern:gen: core
	-- pattern:gen: thisCore -> C: ? core
	-- pattern:gen: inSub
	-- pattern:gen: Indexed(range: ? Integer,elm:< Object)
	-- pattern:gen: %if _cond: ? Boolean %then% _thenPart:< Object
	-- pattern:gen: %restart Obj: ? integer
	-- pattern:gen: %leave Obj: ? integer
	-- pattern:gen: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object
	-- pattern:gen: cycle
	-- pattern:gen: %for first: ? integer %to% last: ? integer %do% body:< Object
	-- ConsRef:gen: ascii
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 70 2 ascii
	rpop
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

	class LIB 76
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_dummy
	-- Module:gen: 
	-- ModuleItem:gen BasicIO
	-- ConsRef:gen: BasicIO
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 77 2 BasicIO
	rpop
	-- Module:gen: 
	-- ModuleItem:gen BasicSystem
	-- ConsRef:gen: BasicSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 112 3 BasicSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen Complex
	-- ConsRef:gen: Complex
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 190 4 Complex
	rpop
	-- Module:gen: 
	-- ModuleItem:gen Containers
	-- ConsRef:gen: Containers
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 113 5 Containers
	rpop
	-- Module:gen: 
	-- ModuleItem:gen EMC2array
	-- ConsRef:gen: EMC2array
	-- ObjectGenerator:gen: super: :singular:staticOff: 6
	pushThis 
	invoke 195 6 EMC2array
	rpop
	-- Module:gen: 
	-- ModuleItem:gen ForkJoinSystem
	-- ConsRef:gen: ForkJoinSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 7
	pushThis 
	invoke 220 7 ForkJoinSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen MonitorSystem
	-- ConsRef:gen: MonitorSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 8
	pushThis 
	invoke 227 8 MonitorSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen NonBlockingIO
	-- ConsRef:gen: NonBlockingIO
	-- ObjectGenerator:gen: super: :singular:staticOff: 9
	pushThis 
	invoke 242 9 NonBlockingIO
	rpop
	-- Module:gen: 
	-- ModuleItem:gen Socket
	-- ConsRef:gen: Socket
	-- ObjectGenerator:gen: super: :singular:staticOff: 10
	pushThis 
	invoke 252 10 Socket
	rpop
	-- Module:gen: 
	-- ModuleItem:gen SocketSystem
	-- ConsRef:gen: SocketSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 11
	pushThis 
	invoke 275 11 SocketSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen String
	-- ConsRef:gen: String
	-- ObjectGenerator:gen: super: :singular:staticOff: 12
	pushThis 
	invoke 84 12 String
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

	class workspace 299
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
	invoke 511 4 demo
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
	-- pattern:loadArgs: := V: ? Object:= 0
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

	class True 34
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
	-- pattern:loadArgs: := V: ? Object:= 1
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

	class immutable 46
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L15:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner immutable:IS-empty: staticOff: 0
	-- Invocation:gen: %inner immutable
	-- Invocation:loadOrigin: %inner immutable
	-- Invocation:loadOrigin:scan: %inner immutable
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner immutable
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner immutable
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L16:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class core 53
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: dummy
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

	class Indexed 56
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
 L19:
	-- Include:gen: 
 L20:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else% 64
	pushThis 
	storeg 1 cond
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: ugly_y
	-- ConsRef:gen: _L
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 65 2 _L
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L21:
	-- Include:gen: 
 L22:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class cycle 66
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L23:
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
	jmp L23
 L24:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do% 67
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
 L25:
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
	-- pattern:loadArgs: := V: ? Object:= first
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
	-- VarRef:loadArgs: 
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
	-- pattern:loadArgs: dodo
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 68 0 do
	rpop
 L26:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ascii 70
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: nl
	-- ObjectGenerator:gen: super: 10:IS-empty: staticOff: 1
	-- Invocation:gen: 10
	-- Invocation:loadOrigin: 10
	-- Invocation:loadOrigin:scan: 10
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 10
	pushThis 
	storeg 1 nl
	-- ConsRef:gen: cr
	-- ObjectGenerator:gen: super: 13:IS-empty: staticOff: 2
	-- Invocation:gen: 13
	-- Invocation:loadOrigin: 13
	-- Invocation:loadOrigin:scan: 13
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 13
	pushThis 
	storeg 2 cr
	-- VarRef:gen: newline
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L27:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: newline := cr:IS-empty: staticOff: 0
	-- Invocation:gen: newline := cr
	-- Invocation:loadOrigin: newline := cr
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := cr
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= cr
	-- ObjectGenerator:gen: super: cr:IS-empty: staticOff: 0
	-- Invocation:gen: cr
	-- Invocation:loadOrigin: cr
	-- Invocation:loadOrigin:scan: cr
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cr
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: cr
	pushg 2 cr
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 newline
 L28:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class newline 71
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L29:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(10):IS-empty: staticOff: 0
	-- Invocation:gen: put(10)
	-- Invocation:loadOrigin: put(10)
	-- Invocation:loadOrigin:scan: put(10)
	-- Function:pushThis: 
	-- Function:loadOrigin: put(10)
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(10)
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
 L30:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class putint 72
	pushThis 
	storeg 1 V
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: D
	-- ObjectGenerator:gen: super: Indexed(20,integer):IS-empty: staticOff: 2
	-- Invocation:gen: Indexed(20,integer)
	-- Invocation:loadOrigin: Indexed(20,integer)
	-- Invocation:loadOrigin:scan: Indexed(20,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(20,integer)
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 putint:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)Indexed(20,integer)
	-- ObjectGenerator:gen: super: 20:IS-empty: staticOff: 0
	-- Invocation:gen: 20
	-- Invocation:loadOrigin: 20
	-- Invocation:loadOrigin:scan: 20
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 20
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	-- VarRef:gen: L
	-- VarRef:gen: isNeg
	-- pattern:gen: doit
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L31:
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
	-- pattern:loadArgs: := V: ? Object:= V < 0
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: < 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< 0
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: isNeg
	pushg 3 isNeg
	jmpFalse L33
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
	-- pattern:loadArgs: := V: ? Object:= 0 - V
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
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- V
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L33:
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
	-- pattern:loadArgs: doitdoit
	-- Unary:invoke: 
	-- pattern:load: doit
	invoke 73 0 doit
	rpop
 L32:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicIO 77
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Lock
	-- ConsRef:gen: keyboard
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 83 2 keyboard
	rpop
	-- ConsRef:gen: screen
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 109 3 screen
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

	class BasicSystem 112
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: BasicSystem
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

	class Complex 190
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Complex(re: ? integer,im: ? integer)
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

	class Containers 113
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
	invoke 121 3 mQueue
	rpop
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

	class EMC2array 195
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
 L42:
	-- Include:gen: 
 L43:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ForkJoinSystem 220
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: ForkJoinSystem
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

	class MonitorSystem 227
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: System
	rtnEventQ 0
	DO:
	mvStack 
 L46:
	-- Include:gen: 
 L47:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class NonBlockingIO 242
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: NonBlockingIOSystem
	rtnEventQ 0
	DO:
	mvStack 
 L48:
	-- Include:gen: 
 L49:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Socket 252
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Socket
	rtnEventQ 0
	DO:
	mvStack 
 L50:
	-- Include:gen: 
 L51:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class SocketSystem 275
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: SocketSystem
	rtnEventQ 0
	DO:
	mvStack 
 L52:
	-- Include:gen: 
 L53:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class String 84
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: String
	rtnEventQ 0
	DO:
	mvStack 
 L54:
	-- Include:gen: 
 L55:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class demo 511
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: olsen_nils
	-- Module:gen: 
	-- ModuleItem:gen ArrayDemos
	-- ConsRef:gen: ArrayDemos
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 512 2 ArrayDemos
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
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	rtnEventQ 0
	DO:
	mvStack 
 L56:
	-- Include:gen: 
 L57:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 59
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L58:
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
	-- pattern:loadArgs: := V: ? Object:= %get 0
	-- ObjectGenerator:gen: super: %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: %get 0
	-- Invocation:loadOrigin: %get 0
	-- Invocation:loadOrigin:scan: %get 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get 0
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 length:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get 0
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L59:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class _L 65
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_uglye
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L60:
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
	rpushg 1 _L:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cond
	pushg 1 cond
	jmpFalse L62
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 900 0 #S#900
	rpop
 L62:
	-- ObjectGenerator:gen: super: elsePart:IS-empty: staticOff: 0
	-- Invocation:gen: elsePart
	-- Invocation:loadOrigin: elsePart
	-- Invocation:loadOrigin:scan: elsePart
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elsePart
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 _L:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: elsePartelsePart
	-- Unary:invoke: 
	-- pattern:load: elsePart
	sendv 2 elsePart
	rpop
 L61:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 68
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 69 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L63:
	-- Include:gen: 
 L64:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 73
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 74 2 loop
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L65:
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
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: isNeg
	pushg 3 isNeg
	jmpFalse L67
	-- ObjectGenerator:gen: super: put('-'):IS-empty: staticOff: 0
	-- Invocation:gen: put('-')
	-- Invocation:loadOrigin: put('-')
	-- Invocation:loadOrigin:scan: put('-')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('-')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('-')
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
 L67:
	-- ObjectGenerator:gen: super: %for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i):IS-empty: staticOff: 0
	pushThis 
	invoke 75 0 %for%to%%do%#S#75
	rpop
 L66:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Lock 78
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
 L68:
	-- Include:gen: 
 L69:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class keyboard 83
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: readLine -> M: ? LIB.String.String
	rtnEventQ 0
	DO:
	mvStack 
 L70:
	-- Include:gen: 
 L71:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class screen 109
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
	rpushg 1 screen:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 78 2 Lock
	rpop
	-- pattern:gen: init
	-- pattern:gen: display
	rtnEventQ 0
	DO:
	mvStack 
 L72:
	-- Include:gen: 
 L73:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicSystem 136
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
	invoke 161 2 cores
	rpop
	-- ConsRef:gen: P_status
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 163 3 P_status
	rpop
	-- pattern:gen: ProcessQueue
	-- ConsRef:gen: sch
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 148 4 sch
	rpop
	-- ConsRef:gen: SQS
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 166 5 SQS
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
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 137 6 Lock
	rpop
	-- ConsRef:gen: console
	-- ObjectGenerator:gen: super: :singular:staticOff: 7
	pushThis 
	invoke 180 7 console
	rpop
	-- ConsRef:gen: keyboard
	-- ObjectGenerator:gen: super: BasicProcess("Keyboard"):singular:staticOff: 8
	pushThis 
	invoke 183 8 keyboard
	rpop
	-- pattern:gen: init
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L74:
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
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 189 0 init
	rpop
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- pattern:loadArgs: innerinner
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
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: cores
	rpushg 2 cores
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 162 0 init
	rpop
 L75:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Complex 191
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
 L76:
	-- Include:gen: 
 L77:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class mQueue 121
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Queue
	rtnEventQ 0
	DO:
	mvStack 
 L78:
	-- Include:gen: 
 L79:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Array 196
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
	-- vdtAdd: inx=1 descInx=207
	innerA  2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L80:
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
	-- pattern:loadArgs: := V: ? Object:= 1
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
 L81:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Range 209
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Invocation:loadOrigin:scan: - low
	-- BE:loadOrigin:E: - low
	-- next not assign: + 1 :E: - low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- low
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
 L82:
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
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: < 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< 1
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
	jmpFalse L84
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 947 0 #S#947
	rpop
 L84:
 L83:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class D1_Array 212
	pushThis 
	rstoreg 3 R
	rstore 1 origin
	allocEventQ
	-- super Array
	--  1:207 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=212
	-- Invocation:loadOrigin: Array
	-- Invocation:loadOrigin:scan: Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: ArrayArray
	topSuper  196
	-- pattern:gen: putAt(inx: ? integer,exp: ? integer) -> res: ? Array
	-- pattern:gen: getAt(inx: ? integer) -> res: ? integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=215
	innerA  4
	rtnInner
	DO:
	doEventQ
	mvStack 
 L85:
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
	-- pattern:loadArgs: := V: ? Object:= R.noof
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: noof
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
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
	-- pattern:loadArgs: := V: ? Object:= Indexed(noof,integer)
	-- ObjectGenerator:gen: super: Indexed(noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: Indexed(noof,integer)
	-- Invocation:loadOrigin: Indexed(noof,integer)
	-- Invocation:loadOrigin:scan: Indexed(noof,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(noof,integer)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 D1_Array:origin
	rpushg 1 EMC2array:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)Indexed(noof,integer)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
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
 L86:
	rtnInner
	end 1

	class D2_Array 216
	pushThis 
	rstoreg 4 R2
	pushThis 
	rstoreg 3 R1
	rstore 1 origin
	allocEventQ
	-- super Array
	--  1:207 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=216
	-- Invocation:loadOrigin: Array
	-- Invocation:loadOrigin:scan: Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: ArrayArray
	topSuper  196
	-- pattern:gen: putAt(inx1: ? integer,inx2: ? integer,exp: ? integer) -> res: ? D2_Array
	-- pattern:gen: getAt(inx1: ? integer,inx2: ? integer) -> exp: ? integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=219
	rtnInner
	DO:
	doEventQ
	mvStack 
 L87:
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
	-- pattern:loadArgs: := V: ? Object:= indexed(R1.noof * R2.noof,integer)
	-- ObjectGenerator:gen: super: indexed(R1.noof * R2.noof,integer):IS-empty: staticOff: 0
	-- Invocation:gen: indexed(R1.noof * R2.noof,integer)
	-- Invocation:loadOrigin: indexed(R1.noof * R2.noof,integer)
	-- Invocation:loadOrigin:scan: indexed(R1.noof * R2.noof,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: indexed(R1.noof * R2.noof,integer)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 D2_Array:origin
	rpushg 1 EMC2array:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)indexed(R1.noof * R2.noof,integer)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: * R2.noof :E: noof
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: * R2.noof
	-- Binary:loadArgs: 
	-- pattern:loadArgs: * V: ? integer -> R: ? integer* R2.noof
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: * V: ? integer -> R: ? integer
	66
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
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
	-- pattern:loadArgs: := V: ? Object:= %this D2_Array
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
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L88:
	rtnInner
	end 1

	class ForkJoinSystem 221
	rstore 1 origin
	allocEventQ
	-- super BasicSystem
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=221
	-- Invocation:loadOrigin: BasicSystem
	-- Invocation:loadOrigin:scan: BasicSystem
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: BasicSystem
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: BasicSystemBasicSystem
	topSuper  136
	-- pattern:gen: ForkJoin
	innerA  2
	rtnInner
	DO:
	doEventQ
	mvStack 
 L89:
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
 L90:
	rtnInner
	end 1

	class System 228
	rstore 9 origin
	allocEventQ
	-- super BasicSystem
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=228
	-- Invocation:loadOrigin: LIB.BasicSystem.basicSystem
	-- Invocation:loadOrigin:scan: LIB
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: LIB
	-- AdjustOrigin: 9
	rpushg 9 origin
	-- on : 2
	rpushg 1 MonitorSystem:origin
	rpushg 1 LIB:origin
	-- next not assign: BasicSystem :E: LIB
	-- Unary:loadArgs: 
	-- Module:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: LIB
	rpushg 3 LIB
	-- Invocation:loadOrigin:scan: BasicSystem
	-- next not assign: basicSystem :E: BasicSystem
	-- Unary:loadArgs: 
	-- Module:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: BasicSystem
	rpushg 3 BasicSystem
	-- Invocation:loadOrigin:scan: basicSystem
	-- Unary:loadArgs: 
	-- pattern:loadArgs: BasicSystembasicSystem
	topSuper  136
	-- pattern:gen: Semaphore
	-- pattern:gen: Process
	-- pattern:gen: Monitor
	innerA  2
	rtnInner
	DO:
	doEventQ
	mvStack 
 L91:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- pattern:loadArgs: innerinner
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  2
 L92:
	rtnInner
	end 1

	class NonBlockingIOSystem 243
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: IO_buf
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 244 2 IO_buf
	rpop
	-- ConsRef:gen: reader
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 247 3 reader
	rpop
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L93:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner NonBlockingIOSystem:IS-empty: staticOff: 0
	-- Invocation:gen: %inner NonBlockingIOSystem
	-- Invocation:loadOrigin: %inner NonBlockingIOSystem
	-- Invocation:loadOrigin:scan: %inner NonBlockingIOSystem
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner NonBlockingIOSystem
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner NonBlockingIOSystem
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L94:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Socket 253
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: sockfd
	-- VarRef:gen: portno
	-- pattern:gen: INVALID_SOCKET -> V: ? integer
	-- pattern:gen: hostent
	-- pattern:gen: socketaddr_in
	-- ConsRef:gen: serv_addr
	-- ObjectGenerator:gen: super: socketaddr_in:IS-empty: staticOff: 2
	-- Invocation:gen: socketaddr_in
	-- Invocation:loadOrigin: socketaddr_in
	-- Invocation:loadOrigin:scan: socketaddr_in
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: socketaddr_in
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: socketaddr_insocketaddr_in
	-- Unary:invoke: 
	-- pattern:load: socketaddr_in
	invoke 256 2 socketaddr_in
	rpop
	-- pattern:gen: init(pno: ? integer)
	-- pattern:gen: connect(adr: ? string.String)
	-- pattern:gen: ioctl(cmd: ? integer) -> V: ? integer
	-- pattern:gen: bind
	-- pattern:gen: listen
	-- pattern:gen: accept -> sock: ? Socket
	-- pattern:gen: send(msg: ? String.String) -> V: ? integer
	-- pattern:gen: receive -> msg: ? String.String
	-- pattern:gen: close
	rtnEventQ 0
	DO:
	mvStack 
 L95:
	-- Include:gen: 
 L96:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class SocketSystem 276
	rstore 9 origin
	allocEventQ
	-- super BasicSystem
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=276
	-- Invocation:loadOrigin: LIB.BasicSystem.BasicSystem
	-- Invocation:loadOrigin:scan: LIB
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: LIB
	-- AdjustOrigin: 9
	rpushg 9 origin
	-- on : 2
	rpushg 1 SocketSystem:origin
	rpushg 1 LIB:origin
	-- next not assign: BasicSystem :E: LIB
	-- Unary:loadArgs: 
	-- Module:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: LIB
	rpushg 3 LIB
	-- Invocation:loadOrigin:scan: BasicSystem
	-- next not assign: BasicSystem :E: BasicSystem
	-- Unary:loadArgs: 
	-- Module:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: BasicSystem
	rpushg 3 BasicSystem
	-- Invocation:loadOrigin:scan: BasicSystem
	-- Unary:loadArgs: 
	-- pattern:loadArgs: BasicSystemBasicSystem
	topSuper  136
	-- pattern:gen: Socket
	innerA  2
	rtnInner
	DO:
	doEventQ
	mvStack 
 L97:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "Socket system:\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "Socket system:\n".print
	-- Invocation:loadOrigin: "Socket system:\n".print
	-- Invocation:loadOrigin:scan: "Socket system:\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Socket system:\n
	-- next not assign: print :E: "Socket system:\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
	-- ObjectGenerator:gen: super: %inner SocketSystem:IS-empty: staticOff: 0
	-- Invocation:gen: %inner SocketSystem
	-- Invocation:loadOrigin: %inner SocketSystem
	-- Invocation:loadOrigin:scan: %inner SocketSystem
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner SocketSystem
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner SocketSystem
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  2
	rpopThisObj 
 L98:
	rtnInner
	end 1

	class String 85
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
 L99:
	-- Include:gen: 
 L100:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ArrayDemos 512
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: _xxx
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen Point
	-- ConsRef:gen: Point
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 531 5 Point
	rpop
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
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

	class #S#900 900
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L103:
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
	rpushg 1 #S#900:origin
	rpushg 1 _L:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: thenPartthenPart
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
	break 1 61
 L104:
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
 L105:
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: <= last :E: inx
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Invocation:loadOrigin:scan: <= last
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <= V: ? integer -> B: ? Boolean<= last
	-- ObjectGenerator:gen: super: last:IS-empty: staticOff: 0
	-- Invocation:gen: last
	-- Invocation:loadOrigin: last
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	pushg 2 last
	-- Binary:invoke: 
	-- pattern:load: <= V: ? integer -> B: ? Boolean
	52
	jmpFalse L107
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 901 0 #S#901
	rpop
 L107:
 L106:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 74
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L108:
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
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- Invocation:loadOrigin:scan: := L + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= L + 1
	-- ObjectGenerator:gen: super: L + 1:IS-empty: staticOff: 0
	-- Invocation:gen: L + 1
	-- Invocation:loadOrigin: L + 1
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- next not assign: + 1 :E: L
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- next not assign: %put V /% 10 %at% L :E: D
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: D
	rpushg 2 D
	-- Invocation:loadOrigin:scan: %put V /% 10 %at% L
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put V /% 10 %at% L
	-- ObjectGenerator:gen: super: V /% 10:IS-empty: staticOff: 0
	-- Invocation:gen: V /% 10
	-- Invocation:loadOrigin: V /% 10
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- next not assign: /% 10 :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: /% 10
	-- Binary:loadArgs: 
	-- pattern:loadArgs: /% V: ? integer -> R: ? integer/% 10
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
	-- ObjectGenerator:gen: super: L:IS-empty: staticOff: 0
	-- Invocation:gen: L
	-- Invocation:loadOrigin: L
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
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
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- Invocation:loadOrigin:scan: := V // 10
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= V // 10
	-- ObjectGenerator:gen: super: V // 10:IS-empty: staticOff: 0
	-- Invocation:gen: V // 10
	-- Invocation:loadOrigin: V // 10
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- next not assign: // 10 :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: // 10
	-- Binary:loadArgs: 
	-- pattern:loadArgs: // V: ? integer -> B: ? Integer// 10
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
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- next not assign: > 0 :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: > 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: > V: ? integer -> B: ? Boolean> 0
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
	jmpFalse L110
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 902 0 #S#902
	rpop
 L110:
 L109:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#75 75
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
	rpushg 1 doit:origin
	rpushg 1 putint:origin
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
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	topSuper  67
	rtnInner
	DO:
	mvStack 
 L111:
 L112:
	rtnInner
	end 1

	class init 79
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L113:
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 0
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
 L114:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class get 80
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: res
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 81 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L115:
	-- Include:gen: 
 L116:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class free 82
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L117:
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
	rpushg 1 free:origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 0
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
	-- pattern:loadArgs: enableenable
	-- Unary:invoke: 
	-- pattern:load: enable
	%enable 12
 L118:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class readLine 107
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx
	-- ConsRef:gen: msg
	-- ObjectGenerator:gen: super: Indexed(30,integer):IS-empty: staticOff: 3
	-- Invocation:gen: Indexed(30,integer)
	-- Invocation:loadOrigin: Indexed(30,integer)
	-- Invocation:loadOrigin:scan: Indexed(30,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(30,integer)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 readLine:origin
	rpushg 1 keyboard:origin
	rpushg 1 BasicIO:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)Indexed(30,integer)
	-- ObjectGenerator:gen: super: 30:IS-empty: staticOff: 0
	-- Invocation:gen: 30
	-- Invocation:loadOrigin: 30
	-- Invocation:loadOrigin:scan: 30
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 30
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
	pushThis 
	rstoreg 3 indexed
	-- ConsRef:gen: read
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 108 4 read
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L119:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := msg.asString:IS-empty: staticOff: 0
	-- Invocation:gen: M := msg.asString
	-- Invocation:loadOrigin: M := msg.asString
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := msg.asString
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= msg.asString
	-- ObjectGenerator:gen: super: msg.asString:IS-empty: staticOff: 0
	-- Invocation:gen: msg.asString
	-- Invocation:loadOrigin: msg.asString
	-- Invocation:loadOrigin:scan: msg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: msg
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: asString :E: msg
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: msg
	rpushg 3 msg
	-- Invocation:loadOrigin:scan: asString
	-- Unary:loadArgs: 
	-- pattern:loadArgs: asString -> S: ? ObjectasString
	-- Unary:invoke: 
	-- pattern:load: asString -> S: ? Object
	%asString 118
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 M
 L120:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: M
	rpushg 2 M
	rtn(D)
	end 1

	class init 110
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L121:
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
	rpushg 1 init:origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 80 0 get
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
	rpushg 1 init:origin
	-- next not assign: init :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 79 0 init
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
	rpushg 1 init:origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 82 0 free
	rpop
 L122:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 111
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L123:
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
	rpushg 1 display:origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 80 0 get
	rpop
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- pattern:loadArgs: innerinner
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
	rpushg 1 display:origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 82 0 free
	rpop
 L124:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Lock 137
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
 L125:
	-- Include:gen: 
 L126:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicProcess 142
	pushThis 
	rstoreg 2 id
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: status
	-- pattern:gen: start
	-- vdtAdd: inx=1 descInx=143
	innerA  2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L127:
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
	-- pattern:loadArgs: suspendsuspend
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
	-- pattern:loadArgs: innerinner
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
	-- pattern:loadArgs: := V: ? Object:= P_status.TERMINATED
	-- ObjectGenerator:gen: super: P_status.TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.TERMINATED
	-- Invocation:loadOrigin: P_status.TERMINATED
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 BasicProcess:origin
	-- next not assign: TERMINATED :E: P_status
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: TERMINATED
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: TERMINATED
	pushg 3 TERMINATED
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
 L128:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Scheduler 144
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
 L129:
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
	-- pattern:loadArgs: suspendsuspend
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
	rpushg 1 Scheduler:origin
	-- next not assign: add :E: sch
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: add
	-- Unary:loadArgs: 
	-- pattern:loadArgs: addadd
	-- Unary:invoke: 
	-- pattern:load: add
	invoke 150 0 add
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
	-- pattern:loadArgs: dodo
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 145 0 do
	rpop
 L130:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Core 156
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
 L131:
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
	-- pattern:loadArgs: suspendsuspend
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
	-- pattern:loadArgs: dodo
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 158 0 do
	rpop
 L132:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class cores 161
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
 L133:
	-- Include:gen: 
 L134:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class P_status 163
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
 L135:
	-- Include:gen: 
 L136:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Queue 122
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
 L137:
	-- Include:gen: 
 L138:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ProcessQueue 164
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
	rpushg 1 BasicSystem:origin
	rpushg 1 BasicSystem:origin
	rpushg 1 LIB:origin
	-- next not assign: Containers :E: LIB
	-- Unary:loadArgs: 
	-- Module:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: LIB
	rpushg 3 LIB
	-- Invocation:loadOrigin:scan: Containers
	-- next not assign: mQueue :E: Containers
	-- Unary:loadArgs: 
	-- Module:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: Containers
	rpushg 5 Containers
	-- Invocation:loadOrigin:scan: mQueue
	-- next not assign: Queue :E: mQueue
	-- Unary:loadArgs: 
	-- Module:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: mQueue
	rpushg 3 mQueue
	-- Invocation:loadOrigin:scan: Queue
	-- Unary:loadArgs: 
	-- pattern:loadArgs: QueueQueue
	topSuper  122
	-- pattern:gen: display
	rtnInner
	DO:
	mvStack 
 L139:
	-- Include:gen: 
 L140:
	rtnInner
	end 1

	class sch 148
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
	rpushg 1 sch:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 137 2 Lock
	rpop
	-- VarRef:gen: M
	-- pattern:gen: entry
	-- pattern:gen: add
	-- pattern:gen: dcr
	-- pattern:gen: running -> B: ? Boolean
	rtnEventQ 0
	DO:
	mvStack 
 L141:
	-- Include:gen: 
 L142:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class SQS 166
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
	rpushg 1 SQS:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: ProcessQueueProcessQueue
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 164 2 ProcessQueue
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
	rpushg 1 SQS:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 137 3 Lock
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
 L143:
	-- Include:gen: 
 L144:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class console 180
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
	rpushg 1 console:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 137 2 Lock
	rpop
	-- VarRef:gen: V
	-- pattern:gen: init
	-- pattern:gen: display
	rtnEventQ 0
	DO:
	mvStack 
 L145:
	-- Include:gen: 
 L146:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class keyboard 183
	rstore 1 origin
	allocEventQ
	-- super BasicProcess
	--  1:143 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=183
	-- Invocation:loadOrigin: BasicProcess("Keyboard")
	-- Invocation:loadOrigin:scan: BasicProcess("Keyboard")
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: BasicProcess("Keyboard")
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: BasicProcess(id: ? String)BasicProcess("Keyboard")
	-- ObjectGenerator:gen: super: "Keyboard":IS-empty: staticOff: 0
	-- Invocation:gen: "Keyboard"
	-- Invocation:loadOrigin: "Keyboard"
	-- Invocation:loadOrigin:scan: "Keyboard"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Keyboard
	-- String::loadArgs: 
	-- String::invoke: 
	topSuper  142
	-- ConsRef:gen: B
	-- ObjectGenerator:gen: super: Indexed(100,integer):IS-empty: staticOff: 3
	-- Invocation:gen: Indexed(100,integer)
	-- Invocation:loadOrigin: Indexed(100,integer)
	-- Invocation:loadOrigin:scan: Indexed(100,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(100,integer)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 keyboard:origin
	rpushg 1 BasicSystem:origin
	rpushg 1 BasicSystem:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)Indexed(100,integer)
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
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
	pushThis 
	rstoreg 3 indexed
	-- VarRef:gen: next
	-- VarRef:gen: top
	-- VarRef:gen: echo
	-- pattern:gen: Kscan
	-- pattern:gen: get(caller: ? BasicProcess) -> ch: ? char
	rtnInner
	DO:
	doEventQ
	mvStack 
 L147:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: Kscan:IS-empty: staticOff: 0
	-- Invocation:gen: Kscan
	-- Invocation:loadOrigin: Kscan
	-- Invocation:loadOrigin:scan: Kscan
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Kscan
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: KscanKscan
	-- Unary:invoke: 
	-- pattern:load: Kscan
	invoke 184 0 Kscan
	rpop
 L148:
	rtnInner
	end 1

	class init 189
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L149:
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
	rpushg 1 init:origin
	-- next not assign: init :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 168 0 init
	rpop
 L150:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class + 192
	pushThis 
	rstoreg 2 C
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L151:
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
	-- pattern:loadArgs: := V: ? Object:= Complex(re + C.re,im + C.im)
	-- ObjectGenerator:gen: super: Complex(re + C.re,im + C.im):IS-empty: staticOff: 0
	-- Invocation:gen: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin:scan: Complex(re + C.re,im + C.im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Complex(re + C.re,im + C.im)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 +:origin
	rpushg 1 Complex:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Complex(re: ? integer,im: ? integer)Complex(re + C.re,im + C.im)
	-- ObjectGenerator:gen: super: re + C.re:IS-empty: staticOff: 0
	-- Invocation:gen: re + C.re
	-- Invocation:loadOrigin: re + C.re
	-- Invocation:loadOrigin:scan: re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 +:origin
	-- next not assign: + C.re :E: re
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Invocation:loadOrigin:scan: + C.re
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ C.re
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: re
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 +:origin
	-- next not assign: + C.im :E: im
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Invocation:loadOrigin:scan: + C.im
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ C.im
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: im
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: Complex(re: ? integer,im: ? integer)
	invoke 191 0 Complex
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 res
 L152:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 3 res
	rtn(D)
	end 1

	class - 193
	pushThis 
	rstoreg 2 C
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L153:
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
	-- pattern:loadArgs: := V: ? Object:= Complex(re + C.re,im + C.im)
	-- ObjectGenerator:gen: super: Complex(re + C.re,im + C.im):IS-empty: staticOff: 0
	-- Invocation:gen: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin: Complex(re + C.re,im + C.im)
	-- Invocation:loadOrigin:scan: Complex(re + C.re,im + C.im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Complex(re + C.re,im + C.im)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 -:origin
	rpushg 1 Complex:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Complex(re: ? integer,im: ? integer)Complex(re + C.re,im + C.im)
	-- ObjectGenerator:gen: super: re + C.re:IS-empty: staticOff: 0
	-- Invocation:gen: re + C.re
	-- Invocation:loadOrigin: re + C.re
	-- Invocation:loadOrigin:scan: re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 -:origin
	-- next not assign: + C.re :E: re
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Invocation:loadOrigin:scan: + C.re
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ C.re
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: re
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 -:origin
	-- next not assign: + C.im :E: im
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Invocation:loadOrigin:scan: + C.im
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ C.im
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: im
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: Complex(re: ? integer,im: ? integer)
	invoke 191 0 Complex
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 res
 L154:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 3 res
	rtn(D)
	end 1

	class display 194
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L155:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('C'):IS-empty: staticOff: 0
	-- Invocation:gen: put('C')
	-- Invocation:loadOrigin: put('C')
	-- Invocation:loadOrigin:scan: put('C')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('C')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('C')
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
	rpushg 1 display:origin
	rpushg 1 Complex:origin
	rpushg 1 Complex:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(re)
	-- ObjectGenerator:gen: super: re:IS-empty: staticOff: 0
	-- Invocation:gen: re
	-- Invocation:loadOrigin: re
	-- Invocation:loadOrigin:scan: re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 display:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(','):IS-empty: staticOff: 0
	-- Invocation:gen: put(',')
	-- Invocation:loadOrigin: put(',')
	-- Invocation:loadOrigin:scan: put(',')
	-- Function:pushThis: 
	-- Function:loadOrigin: put(',')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(',')
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
	rpushg 1 display:origin
	rpushg 1 Complex:origin
	rpushg 1 Complex:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(im)
	-- ObjectGenerator:gen: super: im:IS-empty: staticOff: 0
	-- Invocation:gen: im
	-- Invocation:loadOrigin: im
	-- Invocation:loadOrigin:scan: im
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: im
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 display:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(10):IS-empty: staticOff: 0
	-- Invocation:gen: put(10)
	-- Invocation:loadOrigin: put(10)
	-- Invocation:loadOrigin:scan: put(10)
	-- Function:pushThis: 
	-- Function:loadOrigin: put(10)
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(10)
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
 L156:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class put 197
	pushThis 
	storeg 1 e
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L157:
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
	rpushg 1 put:origin
	-- next not assign: %put e %at% pos :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %put e %at% pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put e %at% pos
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 put:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 198 0 %if%then%%else%#S#198
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
	-- pattern:loadArgs: := V: ? Object:= %this Array
	-- ObjectGenerator:gen: super: %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: %this Array
	-- Invocation:loadOrigin: %this Array
	-- Invocation:loadOrigin:scan: %this Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Array
	-- AdjustOrigin: 0
	rpushg 1 put:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Array
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 res
 L158:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class get 199
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L159:
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
	-- pattern:loadArgs: := V: ? Object:= rep.%get pos
	-- ObjectGenerator:gen: super: rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos
	-- Invocation:loadOrigin: rep.%get pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 get:origin
	-- next not assign: %get pos :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 get:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
	-- ObjectGenerator:gen: super: %if pos = rep.length %then% 
    pos := 1 %else% 
    pos := pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 200 0 %if%then%%else%#S#200
	rpop
 L160:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class nxt 201
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L161:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 202 0 %if%then%%else%#S#202
	rpop
 L162:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class prv 203
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L163:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if pos = noof %then% 
    res := 9999999 %else% 
    res := rep.%get pos - 1:IS-empty: staticOff: 0
	pushThis 
	invoke 204 0 %if%then%%else%#S#204
	rpop
 L164:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class forAll 205
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
 L165:
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
	rpushg 1 forAll:origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 1
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
	-- pattern:loadArgs: looploop
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 206 0 loop
	rpop
 L166:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 207
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L167:
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
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
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
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% rep.length %do% 
    putint(rep.%get inx)
    ", ".print:IS-empty: staticOff: 0
	pushThis 
	invoke 208 0 %for%to%%do%#S#208
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
	rpushg 1 print:origin
	rpushg 1 Array:origin
	rpushg 1 EMC2array:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 71 0 newline
	rpop
 L168:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class check 210
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L169:
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: < low
	-- BE:loadOrigin:E: < low
	-- next not assign: || (inx > upp) :E: < low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< low
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 check:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	-- Invocation:loadOrigin:scan: || (inx > upp)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: || B: ? Boolean -> R: ? Boolean|| (inx > upp)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: > upp
	-- BE:loadOrigin:E: > upp
	-- Binary:loadArgs: 
	-- pattern:loadArgs: > V: ? integer -> B: ? Boolean> upp
	-- ObjectGenerator:gen: super: upp:IS-empty: staticOff: 0
	-- Invocation:gen: upp
	-- Invocation:loadOrigin: upp
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 check:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Binary:invoke: 
	-- pattern:load: > V: ? integer -> B: ? Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: || B: ? Boolean -> R: ? Boolean
	63
	jmpFalse L171
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 946 0 #S#946
	rpop
 L171:
 L170:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 211
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L172:
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
	rpushg 1 print:origin
	rpushg 1 Range:origin
	rpushg 1 EMC2array:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(low)
	-- ObjectGenerator:gen: super: low:IS-empty: staticOff: 0
	-- Invocation:gen: low
	-- Invocation:loadOrigin: low
	-- Invocation:loadOrigin:scan: low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 print:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(':'):IS-empty: staticOff: 0
	-- Invocation:gen: put(':')
	-- Invocation:loadOrigin: put(':')
	-- Invocation:loadOrigin:scan: put(':')
	-- Function:pushThis: 
	-- Function:loadOrigin: put(':')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(':')
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
	rpushg 1 print:origin
	rpushg 1 Range:origin
	rpushg 1 EMC2array:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(upp)
	-- ObjectGenerator:gen: super: upp:IS-empty: staticOff: 0
	-- Invocation:gen: upp
	-- Invocation:loadOrigin: upp
	-- Invocation:loadOrigin:scan: upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 print:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
	rpop
 L173:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#947 947
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L174:
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
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L175:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class putAt 213
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
 L176:
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
	rpushg 1 putAt:origin
	-- next not assign: check(inx) :E: R
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: check(inx)
	-- Function:loadArgs: 
	-- pattern:loadArgs: check(inx: ? integer)check(inx)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 210 0 check
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
	rpushg 1 putAt:origin
	-- next not assign: %put exp %at% (inx - R.low) + 1 :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %put exp %at% (inx - R.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put exp %at% (inx - R.low) + 1
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 2 exp
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: - R.low
	-- BE:loadOrigin:E: - R.low
	-- next not assign: + 1 :E: - R.low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- R.low
	-- ObjectGenerator:gen: super: R.low:IS-empty: staticOff: 0
	-- Invocation:gen: R.low
	-- Invocation:loadOrigin: R.low
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 putAt:origin
	-- next not assign: low :E: R
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
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
	-- pattern:loadArgs: := V: ? Object:= %this Array
	-- ObjectGenerator:gen: super: %this Array:IS-empty: staticOff: 0
	-- Invocation:gen: %this Array
	-- Invocation:loadOrigin: %this Array
	-- Invocation:loadOrigin:scan: %this Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Array
	-- AdjustOrigin: 0
	rpushg 1 putAt:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Array
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 res
 L177:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class getAt 214
	pushThis 
	storeg 1 inx
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L178:
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
	rpushg 1 getAt:origin
	-- next not assign: check(inx) :E: R
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: check(inx)
	-- Function:loadArgs: 
	-- pattern:loadArgs: check(inx: ? integer)check(inx)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 210 0 check
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
	-- pattern:loadArgs: := V: ? Object:= rep.%get (inx - R.low) + 1
	-- ObjectGenerator:gen: super: rep.%get (inx - R.low) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin: rep.%get (inx - R.low) + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 getAt:origin
	-- next not assign: %get (inx - R.low) + 1 :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get (inx - R.low) + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get (inx - R.low) + 1
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: - R.low
	-- BE:loadOrigin:E: - R.low
	-- next not assign: + 1 :E: - R.low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- R.low
	-- ObjectGenerator:gen: super: R.low:IS-empty: staticOff: 0
	-- Invocation:gen: R.low
	-- Invocation:loadOrigin: R.low
	-- Invocation:loadOrigin:scan: R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 getAt:origin
	-- next not assign: low :E: R
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 res
 L179:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 2 res
	rtn(D)
	end 1

	class print 215
	rstore 2 origin
	allocEventQ
	-- super print
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=215
	pushThis 
	rpushg 2 iOrigin
	topSuper  207
	rtnInner
	DO:
	doEventQ
	mvStack 
 L180:
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
	rpushg 2 print:origin
	-- next not assign: print :E: R
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 211 0 print
	rpop
 L181:
	rtnInner
	end 1

	class putAt 217
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
 L182:
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
	rpushg 1 putAt:origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- pattern:loadArgs: check(inx: ? integer)check(inx1)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 210 0 check
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
	rpushg 1 putAt:origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- pattern:loadArgs: check(inx: ? integer)check(inx2)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 210 0 check
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
	-- pattern:loadArgs: := V: ? Object:= (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- R1.low
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 putAt:origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: * V: ? integer -> R: ? integer* R2.noof + (1 + inx2 - R2.low)
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 putAt:origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ (1 + inx2 - R2.low)
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
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ inx2 - R2.low
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- R2.low
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 putAt:origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 putAt:origin
	-- next not assign: %put exp %at% repPos :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %put exp %at% repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put exp %at% repPos
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 3 exp
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 4 repPos
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	xstoreg 1 inx
 L183:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 2 res
	rtn(D)
	end 1

	class getAt 218
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
 L184:
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
	rpushg 1 getAt:origin
	-- next not assign: check(inx1) :E: R1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: check(inx1)
	-- Function:loadArgs: 
	-- pattern:loadArgs: check(inx: ? integer)check(inx1)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 210 0 check
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
	rpushg 1 getAt:origin
	-- next not assign: check(inx2) :E: R2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: check(inx2)
	-- Function:loadArgs: 
	-- pattern:loadArgs: check(inx: ? integer)check(inx2)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check(inx: ? integer)
	invoke 210 0 check
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
	-- pattern:loadArgs: := V: ? Object:= (inx1 - R1.low) * R2.noof + (1 + inx2 - R2.low)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: - R1.low
	-- BE:loadOrigin:E: - R1.low
	-- next not assign: * R2.noof + (1 + inx2 - R2.low) :E: - R1.low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- R1.low
	-- ObjectGenerator:gen: super: R1.low:IS-empty: staticOff: 0
	-- Invocation:gen: R1.low
	-- Invocation:loadOrigin: R1.low
	-- Invocation:loadOrigin:scan: R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 getAt:origin
	-- next not assign: low :E: R1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Invocation:loadOrigin:scan: * R2.noof + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: * V: ? integer -> R: ? integer* R2.noof + (1 + inx2 - R2.low)
	-- ObjectGenerator:gen: super: R2.noof + (1 + inx2 - R2.low):IS-empty: staticOff: 0
	-- Invocation:gen: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin: R2.noof + (1 + inx2 - R2.low)
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 getAt:origin
	-- next not assign: noof :E: R2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: noof
	-- next not assign: + (1 + inx2 - R2.low) :E: noof
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: + (1 + inx2 - R2.low)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ (1 + inx2 - R2.low)
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
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ inx2 - R2.low
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: - R2.low
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- R2.low
	-- ObjectGenerator:gen: super: R2.low:IS-empty: staticOff: 0
	-- Invocation:gen: R2.low
	-- Invocation:loadOrigin: R2.low
	-- Invocation:loadOrigin:scan: R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 getAt:origin
	-- next not assign: low :E: R2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: low
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	-- pattern:loadArgs: := V: ? Object:= rep.%get repPos
	-- ObjectGenerator:gen: super: rep.%get repPos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get repPos
	-- Invocation:loadOrigin: rep.%get repPos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 getAt:origin
	-- next not assign: %get repPos :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get repPos
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 4 repPos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 3 exp
 L185:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: exp
	pushg 3 exp
	rtn(D)
	end 1

	class print 219
	rstore 2 origin
	allocEventQ
	-- super print
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=219
	pushThis 
	rpushg 2 iOrigin
	topSuper  207
	rtnInner
	DO:
	doEventQ
	mvStack 
 L186:
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
	rpushg 2 print:origin
	-- next not assign: print :E: R1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 211 0 print
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
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
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
	rpushg 2 print:origin
	-- next not assign: print :E: R2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 211 0 print
	rpop
 L187:
	rtnInner
	end 1

	class ForkJoin 222
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
	rpushg 1 ForkJoin:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: ProcessQueueProcessQueue
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 164 2 ProcessQueue
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
	rpushg 1 ForkJoin:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 137 3 Lock
	rpop
	-- pattern:gen: run(P: ? BasicProcess)
	-- pattern:gen: AwaitTermination
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L188:
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
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 138 0 init
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
	-- pattern:loadArgs: AwaitTerminationAwaitTermination
	-- Unary:invoke: 
	-- pattern:load: AwaitTermination
	invoke 224 0 AwaitTermination
	rpop
 L189:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Semaphore 229
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
	rpushg 1 Semaphore:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 137 2 Lock
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
	rpushg 1 Semaphore:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: ProcessQueueProcessQueue
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 164 3 ProcessQueue
	rpop
	-- pattern:gen: init
	-- pattern:gen: wait
	-- pattern:gen: signal
	rtnEventQ 0
	DO:
	mvStack 
 L190:
	-- Include:gen: 
 L191:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Process 235
	rstore 1 origin
	allocEventQ
	-- super BasicProcess
	--  1:143 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=235
	-- Invocation:loadOrigin: BasicProcess
	-- Invocation:loadOrigin:scan: BasicProcess
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: BasicProcess
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: BasicProcess(id: ? String)BasicProcess
	topSuper  142
	-- pattern:gen: start
	-- vdtAdd: inx=1 descInx=236
	innerA  3
	rtnInner
	DO:
	doEventQ
	mvStack 
 L192:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- pattern:loadArgs: innerinner
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  3
 L193:
	rtnInner
	end 1

	class Monitor 237
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
	rpushg 1 Monitor:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: SemaphoreSemaphore
	-- Unary:invoke: 
	-- pattern:load: Semaphore
	invoke 229 2 Semaphore
	rpop
	-- VarRef:gen: V
	-- pattern:gen: init
	-- pattern:gen: entry
	-- pattern:gen: wait
	rtnEventQ 0
	DO:
	mvStack 
 L194:
	-- Include:gen: 
 L195:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class IO_buf 244
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: status
	-- VarRef:gen: val
	-- VarRef:gen: N
	-- VarRef:gen: ch
	-- pattern:gen: scan
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L196:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: ch := 'a':IS-empty: staticOff: 0
	-- Invocation:gen: ch := 'a'
	-- Invocation:loadOrigin: ch := 'a'
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 'a'
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 'a'
	-- ObjectGenerator:gen: super: 'a':IS-empty: staticOff: 0
	-- Invocation:gen: 'a'
	-- Invocation:loadOrigin: 'a'
	-- Invocation:loadOrigin:scan: 'a'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 97
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 4 ch
 L197:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class reader 247
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: buf
	-- ObjectGenerator:gen: super: Indexed(100,char):IS-empty: staticOff: 2
	-- Invocation:gen: Indexed(100,char)
	-- Invocation:loadOrigin: Indexed(100,char)
	-- Invocation:loadOrigin:scan: Indexed(100,char)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(100,char)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 reader:origin
	rpushg 1 NonBlockingIOSystem:origin
	rpushg 1 NonBlockingIO:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)Indexed(100,char)
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
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	-- VarRef:gen: next
	-- VarRef:gen: top
	-- pattern:gen: get -> ch: ? char
	-- pattern:gen: go
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L198:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('Q'):IS-empty: staticOff: 0
	-- Invocation:gen: put('Q')
	-- Invocation:loadOrigin: put('Q')
	-- Invocation:loadOrigin:scan: put('Q')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('Q')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('Q')
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
	-- ObjectGenerator:gen: super: (%this reader).suspend:IS-empty: staticOff: 0
	-- Invocation:gen: (%this reader).suspend
	-- Invocation:loadOrigin: (%this reader).suspend
	-- Invocation:loadOrigin:scan: (%this reader)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (%this reader)
	-- Invocation:loadOrigin: %this reader
	-- Invocation:loadOrigin:scan: %this reader
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this reader
	-- AdjustOrigin: 0
	-- BE:loadOrigin:E: %this reader
	-- next not assign: suspend :E: %this reader
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this reader
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- pattern:loadArgs: suspendsuspend
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: put('W'):IS-empty: staticOff: 0
	-- Invocation:gen: put('W')
	-- Invocation:loadOrigin: put('W')
	-- Invocation:loadOrigin:scan: put('W')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('W')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('W')
	-- ObjectGenerator:gen: super: 'W':IS-empty: staticOff: 0
	-- Invocation:gen: 'W'
	-- Invocation:loadOrigin: 'W'
	-- Invocation:loadOrigin:scan: 'W'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 87
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: go:IS-empty: staticOff: 0
	-- Invocation:gen: go
	-- Invocation:loadOrigin: go
	-- Invocation:loadOrigin:scan: go
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: go
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: gogo
	-- Unary:invoke: 
	-- pattern:load: go
	invoke 249 0 go
	rpop
 L199:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class INVALID_SOCKET 254
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L200:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := 1:IS-empty: staticOff: 0
	-- Invocation:gen: V := 1
	-- Invocation:loadOrigin: V := 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 1
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
	storeg 1 V
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
	-- pattern:loadArgs: := V: ? Object:= 0 - V
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
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- V
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L201:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 1 V
	rtn(D)
	end 1

	class hostent 255
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: X
	-- ConsRef:gen: Y
	-- ObjectGenerator:gen: super: indexed(10,integer):IS-empty: staticOff: 2
	-- Invocation:gen: indexed(10,integer)
	-- Invocation:loadOrigin: indexed(10,integer)
	-- Invocation:loadOrigin:scan: indexed(10,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: indexed(10,integer)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 hostent:origin
	rpushg 1 Socket:origin
	rpushg 1 Socket:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)indexed(10,integer)
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
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	rtnEventQ 0
	DO:
	mvStack 
 L202:
	-- Include:gen: 
 L203:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class socketaddr_in 256
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: sin_family_port
	-- VarRef:gen: sin_addr
	-- VarRef:gen: sin_zero1
	-- VarRef:gen: sin_zero2
	rtnEventQ 0
	DO:
	mvStack 
 L204:
	-- Include:gen: 
 L205:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 257
	pushThis 
	storeg 1 pno
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: new_socket -> V: ? integer
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L206:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "init socket\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "init socket\n".print
	-- Invocation:loadOrigin: "init socket\n".print
	-- Invocation:loadOrigin:scan: "init socket\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText init socket\n
	-- next not assign: print :E: "init socket\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
	-- ObjectGenerator:gen: super: sockfd := new_socket:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd := new_socket
	-- Invocation:loadOrigin: sockfd := new_socket
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := new_socket
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= new_socket
	-- ObjectGenerator:gen: super: new_socket:IS-empty: staticOff: 0
	-- Invocation:gen: new_socket
	-- Invocation:loadOrigin: new_socket
	-- Invocation:loadOrigin:scan: new_socket
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: new_socket
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: new_socket -> V: ? integernew_socket
	-- Unary:invoke: 
	-- pattern:load: new_socket -> V: ? integer
	invokeExternal 6
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 sockfd
	-- ObjectGenerator:gen: super: %if sockfd = INVALID_SOCKET %then% 
    "INVALID_SOCKET\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: %if sockfd = INVALID_SOCKET %then% 
    "INVALID_SOCKET\n".print
	-- Invocation:loadOrigin: %if sockfd = INVALID_SOCKET %then% 
    "INVALID_SOCKET\n".print
	-- Invocation:loadOrigin:scan: %if sockfd = INVALID_SOCKET %then% 
    "INVALID_SOCKET\n".print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if sockfd = INVALID_SOCKET %then% 
    "INVALID_SOCKET\n".print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if sockfd = INVALID_SOCKET %then% 
    "INVALID_SOCKET\n".print
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: sockfd = INVALID_SOCKET:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd = INVALID_SOCKET
	-- Invocation:loadOrigin: sockfd = INVALID_SOCKET
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- next not assign: = INVALID_SOCKET :E: sockfd
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Invocation:loadOrigin:scan: = INVALID_SOCKET
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= INVALID_SOCKET
	-- ObjectGenerator:gen: super: INVALID_SOCKET:IS-empty: staticOff: 0
	-- Invocation:gen: INVALID_SOCKET
	-- Invocation:loadOrigin: INVALID_SOCKET
	-- Invocation:loadOrigin:scan: INVALID_SOCKET
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: INVALID_SOCKET
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: INVALID_SOCKET -> V: ? integerINVALID_SOCKET
	-- Unary:invoke: 
	-- pattern:load: INVALID_SOCKET -> V: ? integer
	invoke 254 0 INVALID_SOCKET
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L208
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 960 0 #S#960
	rpop
 L208:
	-- ObjectGenerator:gen: super: portno := pno:IS-empty: staticOff: 0
	-- Invocation:gen: portno := pno
	-- Invocation:loadOrigin: portno := pno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := pno
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= pno
	-- ObjectGenerator:gen: super: pno:IS-empty: staticOff: 0
	-- Invocation:gen: pno
	-- Invocation:loadOrigin: pno
	-- Invocation:loadOrigin:scan: pno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pno
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pno
	pushg 1 pno
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 portno
 L207:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class connect 259
	pushThis 
	rstoreg 2 adr
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_connect(S: ? integer,adr: ? String.string,portno: ? integer) -> V: ? integer
	-- VarRef:gen: V
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L209:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_connect(sockfd,adr,portno):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin: V := do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_connect(sockfd,adr,portno)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_connect(sockfd,adr,portno)
	-- ObjectGenerator:gen: super: do_connect(sockfd,adr,portno):IS-empty: staticOff: 0
	-- Invocation:gen: do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin: do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin:scan: do_connect(sockfd,adr,portno)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_connect(sockfd,adr,portno)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_connect(S: ? integer,adr: ? String.string,portno: ? integer) -> V: ? integerdo_connect(sockfd,adr,portno)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 connect:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: adr:IS-empty: staticOff: 0
	-- Invocation:gen: adr
	-- Invocation:loadOrigin: adr
	-- Invocation:loadOrigin:scan: adr
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: adr
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: adr
	rpushg 2 adr
	-- ObjectGenerator:gen: super: portno:IS-empty: staticOff: 0
	-- Invocation:gen: portno
	-- Invocation:loadOrigin: portno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 connect:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: portno
	pushg 2 portno
	-- Function:invoke: 
	-- pattern:load: do_connect(S: ? integer,adr: ? String.string,portno: ? integer) -> V: ? integer
	invokeExternal 7
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L210:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ioctl 261
	pushThis 
	storeg 1 cmd
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_ioctl(S: ? integer,cmd: ? integer) -> res: ? integer
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L211:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_ioctl(sockfd,cmd):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin: V := do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_ioctl(sockfd,cmd)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_ioctl(sockfd,cmd)
	-- ObjectGenerator:gen: super: do_ioctl(sockfd,cmd):IS-empty: staticOff: 0
	-- Invocation:gen: do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin: do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin:scan: do_ioctl(sockfd,cmd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_ioctl(sockfd,cmd)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_ioctl(S: ? integer,cmd: ? integer) -> res: ? integerdo_ioctl(sockfd,cmd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 ioctl:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: cmd:IS-empty: staticOff: 0
	-- Invocation:gen: cmd
	-- Invocation:loadOrigin: cmd
	-- Invocation:loadOrigin:scan: cmd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cmd
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cmd
	pushg 1 cmd
	-- Function:invoke: 
	-- pattern:load: do_ioctl(S: ? integer,cmd: ? integer) -> res: ? integer
	invokeExternal 14
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 V
 L212:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 2 V
	rtn(D)
	end 1

	class bind 263
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_bind(S: ? integer,port: ? integer) -> V: ? integer
	-- VarRef:gen: V
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L213:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_bind(sockfd,portno):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_bind(sockfd,portno)
	-- Invocation:loadOrigin: V := do_bind(sockfd,portno)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_bind(sockfd,portno)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_bind(sockfd,portno)
	-- ObjectGenerator:gen: super: do_bind(sockfd,portno):IS-empty: staticOff: 0
	-- Invocation:gen: do_bind(sockfd,portno)
	-- Invocation:loadOrigin: do_bind(sockfd,portno)
	-- Invocation:loadOrigin:scan: do_bind(sockfd,portno)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_bind(sockfd,portno)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_bind(S: ? integer,port: ? integer) -> V: ? integerdo_bind(sockfd,portno)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 bind:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: portno:IS-empty: staticOff: 0
	-- Invocation:gen: portno
	-- Invocation:loadOrigin: portno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 bind:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: portno
	pushg 2 portno
	-- Function:invoke: 
	-- pattern:load: do_bind(S: ? integer,port: ? integer) -> V: ? integer
	invokeExternal 11
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L214:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class listen 265
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_listen(S: ? integer) -> V: ? integer
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L215:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: do_listen(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: do_listen(sockfd)
	-- Invocation:loadOrigin: do_listen(sockfd)
	-- Invocation:loadOrigin:scan: do_listen(sockfd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_listen(sockfd)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_listen(S: ? integer) -> V: ? integerdo_listen(sockfd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 listen:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Function:invoke: 
	-- pattern:load: do_listen(S: ? integer) -> V: ? integer
	invokeExternal 12
	vpop
	-- ObjectGenerator:gen: super: "Listen\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "Listen\n".print
	-- Invocation:loadOrigin: "Listen\n".print
	-- Invocation:loadOrigin:scan: "Listen\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Listen\n
	-- next not assign: print :E: "Listen\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L216:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class accept 267
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_accept(S: ? integer) -> V: ? integer
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L217:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sock := Socket:IS-empty: staticOff: 0
	-- Invocation:gen: sock := Socket
	-- Invocation:loadOrigin: sock := Socket
	-- Invocation:loadOrigin:scan: sock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sock
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Socket
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Socket
	-- ObjectGenerator:gen: super: Socket:IS-empty: staticOff: 0
	-- Invocation:gen: Socket
	-- Invocation:loadOrigin: Socket
	-- Invocation:loadOrigin:scan: Socket
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Socket
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 accept:origin
	rpushg 1 Socket:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: SocketSocket
	-- Unary:invoke: 
	-- pattern:load: Socket
	invoke 253 0 Socket
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 sock
	-- ObjectGenerator:gen: super: sock.sockfd := do_accept(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: sock.sockfd := do_accept(sockfd)
	-- Invocation:loadOrigin: sock.sockfd := do_accept(sockfd)
	-- Invocation:loadOrigin:scan: sock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sock
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: sockfd :E: sock
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sock
	rpushg 2 sock
	-- Invocation:loadOrigin:scan: sockfd
	-- Invocation:loadOrigin:scan: := do_accept(sockfd)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_accept(sockfd)
	-- ObjectGenerator:gen: super: do_accept(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: do_accept(sockfd)
	-- Invocation:loadOrigin: do_accept(sockfd)
	-- Invocation:loadOrigin:scan: do_accept(sockfd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_accept(sockfd)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_accept(S: ? integer) -> V: ? integerdo_accept(sockfd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 accept:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Function:invoke: 
	-- pattern:load: do_accept(S: ? integer) -> V: ? integer
	invokeExternal 13
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 sockfd
	-- ObjectGenerator:gen: super: sock.portno := portno:IS-empty: staticOff: 0
	-- Invocation:gen: sock.portno := portno
	-- Invocation:loadOrigin: sock.portno := portno
	-- Invocation:loadOrigin:scan: sock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sock
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: portno :E: sock
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sock
	rpushg 2 sock
	-- Invocation:loadOrigin:scan: portno
	-- Invocation:loadOrigin:scan: := portno
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= portno
	-- ObjectGenerator:gen: super: portno:IS-empty: staticOff: 0
	-- Invocation:gen: portno
	-- Invocation:loadOrigin: portno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 accept:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: portno
	pushg 2 portno
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 portno
 L218:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: sock
	rpushg 2 sock
	rtn(D)
	end 1

	class send 269
	pushThis 
	rstoreg 2 msg
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_send(S: ? integer,msg: ? String.string) -> V: ? integer
	-- VarRef:gen: V
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L219:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_send(sockfd,msg):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_send(sockfd,msg)
	-- Invocation:loadOrigin: V := do_send(sockfd,msg)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_send(sockfd,msg)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_send(sockfd,msg)
	-- ObjectGenerator:gen: super: do_send(sockfd,msg):IS-empty: staticOff: 0
	-- Invocation:gen: do_send(sockfd,msg)
	-- Invocation:loadOrigin: do_send(sockfd,msg)
	-- Invocation:loadOrigin:scan: do_send(sockfd,msg)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_send(sockfd,msg)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_send(S: ? integer,msg: ? String.string) -> V: ? integerdo_send(sockfd,msg)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 send:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: msg:IS-empty: staticOff: 0
	-- Invocation:gen: msg
	-- Invocation:loadOrigin: msg
	-- Invocation:loadOrigin:scan: msg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: msg
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: msg
	rpushg 2 msg
	-- Function:invoke: 
	-- pattern:load: do_send(S: ? integer,msg: ? String.string) -> V: ? integer
	invokeExternal 8
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 V
 L220:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 1 V
	rtn(D)
	end 1

	class receive 271
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_rec(S: ? integer) -> msg: ? String.String
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L221:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: msg := do_rec(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: msg := do_rec(sockfd)
	-- Invocation:loadOrigin: msg := do_rec(sockfd)
	-- Invocation:loadOrigin:scan: msg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: msg
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_rec(sockfd)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_rec(sockfd)
	-- ObjectGenerator:gen: super: do_rec(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: do_rec(sockfd)
	-- Invocation:loadOrigin: do_rec(sockfd)
	-- Invocation:loadOrigin:scan: do_rec(sockfd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_rec(sockfd)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_rec(S: ? integer) -> msg: ? String.Stringdo_rec(sockfd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 receive:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Function:invoke: 
	-- pattern:load: do_rec(S: ? integer) -> msg: ? String.String
	invokeExternal 9
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 msg
 L222:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: msg
	rpushg 2 msg
	rtn(D)
	end 1

	class close 273
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_close(S: ? integer)
	rtnEventQ 0
	DO:
	mvStack 
 L223:
	-- Include:gen: 
 L224:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Socket 277
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: sockfd
	-- VarRef:gen: portno
	-- pattern:gen: INVALID_SOCKET -> V: ? integer
	-- pattern:gen: init(pno: ? integer)
	-- pattern:gen: connect(adr: ? string.String)
	-- pattern:gen: ioctl(cmd: ? integer) -> V: ? integer
	-- pattern:gen: bind
	-- pattern:gen: listen
	-- pattern:gen: accept(theCaller: ? BasicProcess) -> sock: ? Socket
	-- pattern:gen: send(msg: ? String.String) -> V: ? integer
	-- pattern:gen: receive(caller: ? BasicProcess) -> msg: ? String.String
	-- pattern:gen: close
	rtnEventQ 0
	DO:
	mvStack 
 L225:
	-- Include:gen: 
 L226:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 86
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L227:
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
	-- pattern:loadArgs: := V: ? Object:= %get 0
	-- ObjectGenerator:gen: super: %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: %get 0
	-- Invocation:loadOrigin: %get 0
	-- Invocation:loadOrigin:scan: %get 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get 0
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 length:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get 0
	-- ObjectGenerator:gen: super: 0:IS-empty: staticOff: 0
	-- Invocation:gen: 0
	-- Invocation:loadOrigin: 0
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L228:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 1 V
	rtn(D)
	end 1

	class + 88
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
 L229:
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
	-- pattern:loadArgs: := V: ? Object:= Length
	-- ObjectGenerator:gen: super: Length:IS-empty: staticOff: 0
	-- Invocation:gen: Length
	-- Invocation:loadOrigin: Length
	-- Invocation:loadOrigin:scan: Length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Length
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 +:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerLength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
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
	-- pattern:loadArgs: doplusdoplus
	-- Unary:invoke: 
	-- pattern:load: doplus
	invoke 89 0 doplus
	rpop
 L230:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	rpushg 3 V
	rtn(D)
	end 1

	class asLowerCase 92
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 0
	DO:
	mvStack 
 L231:
	-- Include:gen: 
 L232:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: T
	rpushg 2 T
	rtn(D)
	end 1

	class scan 93
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: current
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L233:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    current := %get inx
    %inner scan:IS-empty: staticOff: 0
	pushThis 
	invoke 94 0 %for%to%%do%#S#94
	rpop
 L234:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 95
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L235:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    put(%get inx):IS-empty: staticOff: 0
	pushThis 
	invoke 96 0 %for%to%%do%#S#96
	rpop
 L236:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class = 97
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 98 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L237:
	-- Include:gen: 
 L238:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class <= 100
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 101 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L239:
	-- Include:gen: 
 L240:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class Point 531
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Point(x: ? integer,y: ? integer)
	-- VarRef:gen: x
	-- VarRef:gen: y
	-- VarRef:gen: p1
	-- VarRef:gen: p2
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L241:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: y := 2:IS-empty: staticOff: 0
	-- Invocation:gen: y := 2
	-- Invocation:loadOrigin: y := 2
	-- Invocation:loadOrigin:scan: y
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: y
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := 2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 2
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 y
	-- ObjectGenerator:gen: super: x := y:IS-empty: staticOff: 0
	-- Invocation:gen: x := y
	-- Invocation:loadOrigin: x := y
	-- Invocation:loadOrigin:scan: x
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: x
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := y
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= y
	-- ObjectGenerator:gen: super: y:IS-empty: staticOff: 0
	-- Invocation:gen: y
	-- Invocation:loadOrigin: y
	-- Invocation:loadOrigin:scan: y
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: y
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: y
	pushg 2 y
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 x
	-- ObjectGenerator:gen: super: putint(x):IS-empty: staticOff: 0
	-- Invocation:gen: putint(x)
	-- Invocation:loadOrigin: putint(x)
	-- Invocation:loadOrigin:scan: putint(x)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(x)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 Point:origin
	rpushg 1 ArrayDemos:origin
	rpushg 1 demo:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(x)
	-- ObjectGenerator:gen: super: x:IS-empty: staticOff: 0
	-- Invocation:gen: x
	-- Invocation:loadOrigin: x
	-- Invocation:loadOrigin:scan: x
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: x
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: x
	pushg 1 x
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
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
	rpushg 1 Point:origin
	rpushg 1 ArrayDemos:origin
	rpushg 1 demo:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 71 0 newline
	rpop
	-- ObjectGenerator:gen: super: p2 := Point(1,2):IS-empty: staticOff: 0
	-- Invocation:gen: p2 := Point(1,2)
	-- Invocation:loadOrigin: p2 := Point(1,2)
	-- Invocation:loadOrigin:scan: p2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: := Point(1,2) :E: p2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p2
	rpushg 3 p2
	-- Invocation:loadOrigin:scan: := Point(1,2)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := p: ? Point:= Point(1,2)
	-- ObjectGenerator:gen: super: Point(1,2):IS-empty: staticOff: 0
	-- Invocation:gen: Point(1,2)
	-- Invocation:loadOrigin: Point(1,2)
	-- Invocation:loadOrigin:scan: Point(1,2)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Point(1,2)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: Point(x: ? integer,y: ? integer)Point(1,2)
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- Function:invoke: 
	-- pattern:load: Point(x: ? integer,y: ? integer)
	invoke 532 0 Point
	-- Binary:invoke: 
	-- pattern:load: := p: ? Point
	invoke 533 0 :=
	rpop
	-- ObjectGenerator:gen: super: p1 := Point(99,99):IS-empty: staticOff: 0
	-- Invocation:gen: p1 := Point(99,99)
	-- Invocation:loadOrigin: p1 := Point(99,99)
	-- Invocation:loadOrigin:scan: p1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: := Point(99,99) :E: p1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p1
	rpushg 2 p1
	-- Invocation:loadOrigin:scan: := Point(99,99)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := p: ? Point:= Point(99,99)
	-- ObjectGenerator:gen: super: Point(99,99):IS-empty: staticOff: 0
	-- Invocation:gen: Point(99,99)
	-- Invocation:loadOrigin: Point(99,99)
	-- Invocation:loadOrigin:scan: Point(99,99)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Point(99,99)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: Point(x: ? integer,y: ? integer)Point(99,99)
	-- ObjectGenerator:gen: super: 99:IS-empty: staticOff: 0
	-- Invocation:gen: 99
	-- Invocation:loadOrigin: 99
	-- Invocation:loadOrigin:scan: 99
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 99
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
	-- pattern:load: Point(x: ? integer,y: ? integer)
	invoke 532 0 Point
	-- Binary:invoke: 
	-- pattern:load: := p: ? Point
	invoke 533 0 :=
	rpop
	-- ObjectGenerator:gen: super: p1 := p2:IS-empty: staticOff: 0
	-- Invocation:gen: p1 := p2
	-- Invocation:loadOrigin: p1 := p2
	-- Invocation:loadOrigin:scan: p1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: := p2 :E: p1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p1
	rpushg 2 p1
	-- Invocation:loadOrigin:scan: := p2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := p: ? Point:= p2
	-- ObjectGenerator:gen: super: p2:IS-empty: staticOff: 0
	-- Invocation:gen: p2
	-- Invocation:loadOrigin: p2
	-- Invocation:loadOrigin:scan: p2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p2
	rpushg 3 p2
	-- Binary:invoke: 
	-- pattern:load: := p: ? Point
	invoke 533 0 :=
	rpop
	-- ObjectGenerator:gen: super: putint(p1.getx):IS-empty: staticOff: 0
	-- Invocation:gen: putint(p1.getx)
	-- Invocation:loadOrigin: putint(p1.getx)
	-- Invocation:loadOrigin:scan: putint(p1.getx)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(p1.getx)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 Point:origin
	rpushg 1 ArrayDemos:origin
	rpushg 1 demo:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(p1.getx)
	-- ObjectGenerator:gen: super: p1.getx:IS-empty: staticOff: 0
	-- Invocation:gen: p1.getx
	-- Invocation:loadOrigin: p1.getx
	-- Invocation:loadOrigin:scan: p1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: getx :E: p1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p1
	rpushg 2 p1
	-- Invocation:loadOrigin:scan: getx
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getx -> r: ? integergetx
	-- Unary:invoke: 
	-- pattern:load: getx -> r: ? integer
	invoke 534 0 getx
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
	rpop
	-- ObjectGenerator:gen: super: putint(p1.y):IS-empty: staticOff: 0
	-- Invocation:gen: putint(p1.y)
	-- Invocation:loadOrigin: putint(p1.y)
	-- Invocation:loadOrigin:scan: putint(p1.y)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(p1.y)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 Point:origin
	rpushg 1 ArrayDemos:origin
	rpushg 1 demo:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(p1.y)
	-- ObjectGenerator:gen: super: p1.y:IS-empty: staticOff: 0
	-- Invocation:gen: p1.y
	-- Invocation:loadOrigin: p1.y
	-- Invocation:loadOrigin:scan: p1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: y :E: p1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p1
	rpushg 2 p1
	-- Invocation:loadOrigin:scan: y
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: y
	pushg 2 y
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
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
	rpushg 1 Point:origin
	rpushg 1 ArrayDemos:origin
	rpushg 1 demo:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 71 0 newline
	rpop
	-- ObjectGenerator:gen: super: p2 := Point(3,4):IS-empty: staticOff: 0
	-- Invocation:gen: p2 := Point(3,4)
	-- Invocation:loadOrigin: p2 := Point(3,4)
	-- Invocation:loadOrigin:scan: p2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: := Point(3,4) :E: p2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p2
	rpushg 3 p2
	-- Invocation:loadOrigin:scan: := Point(3,4)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := p: ? Point:= Point(3,4)
	-- ObjectGenerator:gen: super: Point(3,4):IS-empty: staticOff: 0
	-- Invocation:gen: Point(3,4)
	-- Invocation:loadOrigin: Point(3,4)
	-- Invocation:loadOrigin:scan: Point(3,4)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Point(3,4)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: Point(x: ? integer,y: ? integer)Point(3,4)
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
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
	-- pattern:load: Point(x: ? integer,y: ? integer)
	invoke 532 0 Point
	-- Binary:invoke: 
	-- pattern:load: := p: ? Point
	invoke 533 0 :=
	rpop
	-- ObjectGenerator:gen: super: p1 := p2:IS-empty: staticOff: 0
	-- Invocation:gen: p1 := p2
	-- Invocation:loadOrigin: p1 := p2
	-- Invocation:loadOrigin:scan: p1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: := p2 :E: p1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p1
	rpushg 2 p1
	-- Invocation:loadOrigin:scan: := p2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := p: ? Point:= p2
	-- ObjectGenerator:gen: super: p2:IS-empty: staticOff: 0
	-- Invocation:gen: p2
	-- Invocation:loadOrigin: p2
	-- Invocation:loadOrigin:scan: p2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p2
	rpushg 3 p2
	-- Binary:invoke: 
	-- pattern:load: := p: ? Point
	invoke 533 0 :=
	rpop
	-- ObjectGenerator:gen: super: putint(p1.x):IS-empty: staticOff: 0
	-- Invocation:gen: putint(p1.x)
	-- Invocation:loadOrigin: putint(p1.x)
	-- Invocation:loadOrigin:scan: putint(p1.x)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(p1.x)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 Point:origin
	rpushg 1 ArrayDemos:origin
	rpushg 1 demo:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(p1.x)
	-- ObjectGenerator:gen: super: p1.x:IS-empty: staticOff: 0
	-- Invocation:gen: p1.x
	-- Invocation:loadOrigin: p1.x
	-- Invocation:loadOrigin:scan: p1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: x :E: p1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p1
	rpushg 2 p1
	-- Invocation:loadOrigin:scan: x
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: x
	pushg 1 x
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
	rpop
	-- ObjectGenerator:gen: super: putint(p1.y):IS-empty: staticOff: 0
	-- Invocation:gen: putint(p1.y)
	-- Invocation:loadOrigin: putint(p1.y)
	-- Invocation:loadOrigin:scan: putint(p1.y)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(p1.y)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 Point:origin
	rpushg 1 ArrayDemos:origin
	rpushg 1 demo:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(p1.y)
	-- ObjectGenerator:gen: super: p1.y:IS-empty: staticOff: 0
	-- Invocation:gen: p1.y
	-- Invocation:loadOrigin: p1.y
	-- Invocation:loadOrigin:scan: p1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: y :E: p1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p1
	rpushg 2 p1
	-- Invocation:loadOrigin:scan: y
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: y
	pushg 2 y
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
	rpop
 L242:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#901 901
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L243:
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
	rpushg 1 #S#901:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: bodybody
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
	rpushg 1 #S#901:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := inx + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= inx + 1
	-- ObjectGenerator:gen: super: inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx + 1
	-- Invocation:loadOrigin: inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#901:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: + 1 :E: inx
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	break 1 105
 L244:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#902 902
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L245:
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
	break 1 108
 L246:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#903 903
	rstore 2 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: i
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L247:
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
	-- pattern:loadArgs: := V: ? Object:= L + 1 - inx
	-- ObjectGenerator:gen: super: L + 1 - inx:IS-empty: staticOff: 0
	-- Invocation:gen: L + 1 - inx
	-- Invocation:loadOrigin: L + 1 - inx
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#903:origin
	rpushg 2 %for%to%%do%#S#75:origin
	rpushg 1 doit:origin
	-- next not assign: + 1 - inx :E: L
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- Invocation:loadOrigin:scan: + 1 - inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1 - inx
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
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#903:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	-- pattern:loadArgs: put(ch: ? char)put('0' + D.%get i)
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
	-- pattern:loadArgs: + V: ? char -> R: ? char+ D.%get i
	-- ObjectGenerator:gen: super: D.%get i:IS-empty: staticOff: 0
	-- Invocation:gen: D.%get i
	-- Invocation:loadOrigin: D.%get i
	-- Invocation:loadOrigin:scan: D
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: D
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#903:origin
	rpushg 2 %for%to%%do%#S#75:origin
	rpushg 1 doit:origin
	-- next not assign: %get i :E: D
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: D
	rpushg 2 D
	-- Invocation:loadOrigin:scan: %get i
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get i
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 1 i
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: + V: ? char -> R: ? char
	plus
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L248:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 81
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L249:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: disable:IS-empty: staticOff: 0
	-- Invocation:gen: disable
	-- Invocation:loadOrigin: disable
	-- Invocation:loadOrigin:scan: disable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: disable
	-- Unary:loadArgs: 
	-- pattern:loadArgs: disabledisable
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := 17
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 17
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := M.cmpAndSwap(1)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= M.cmpAndSwap(1)
	-- ObjectGenerator:gen: super: M.cmpAndSwap(1):IS-empty: staticOff: 0
	-- Invocation:gen: M.cmpAndSwap(1)
	-- Invocation:loadOrigin: M.cmpAndSwap(1)
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 get:origin
	-- next not assign: cmpAndSwap(1) :E: M
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushc 2
	-- Invocation:loadOrigin:scan: cmpAndSwap(1)
	-- Function:loadArgs: 
	-- pattern:loadArgs: cmpAndSwap(V: ? integer) -> res: ? integercmpAndSwap(1)
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
	rpushg 1 loop:origin
	-- next not assign: = 1 :E: res
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: res
	pushg 1 res
	-- Invocation:loadOrigin:scan: = 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 1
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
	jmpFalse L251
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 904 0 #S#904
	rpop
 L251:
 L250:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class read 108
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: ch
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L252:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: ch := _iGet:IS-empty: staticOff: 0
	-- Invocation:gen: ch := _iGet
	-- Invocation:loadOrigin: ch := _iGet
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := _iGet
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= _iGet
	-- ObjectGenerator:gen: super: _iGet:IS-empty: staticOff: 0
	-- Invocation:gen: _iGet
	-- Invocation:loadOrigin: _iGet
	-- Invocation:loadOrigin:scan: _iGet
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: _iGet
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 read:origin
	rpushg 1 readLine:origin
	rpushg 1 keyboard:origin
	rpushg 1 BasicIO:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: _iget -> ch: ? char_iGet
	-- Unary:invoke: 
	-- pattern:load: _iget -> ch: ? char
	invokeExternal 4
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 ch
	-- ObjectGenerator:gen: super: put(ch):IS-empty: staticOff: 0
	-- Invocation:gen: put(ch)
	-- Invocation:loadOrigin: put(ch)
	-- Invocation:loadOrigin:scan: put(ch)
	-- Function:pushThis: 
	-- Function:loadOrigin: put(ch)
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(ch)
	-- ObjectGenerator:gen: super: ch:IS-empty: staticOff: 0
	-- Invocation:gen: ch
	-- Invocation:loadOrigin: ch
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ch
	pushg 1 ch
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: %if ch = 13 %then% 
    %leave read:IS-empty: staticOff: 0
	-- Invocation:gen: %if ch = 13 %then% 
    %leave read
	-- Invocation:loadOrigin: %if ch = 13 %then% 
    %leave read
	-- Invocation:loadOrigin:scan: %if ch = 13 %then% 
    %leave read
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if ch = 13 %then% 
    %leave read
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if ch = 13 %then% 
    %leave read
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: ch = 13:IS-empty: staticOff: 0
	-- Invocation:gen: ch = 13
	-- Invocation:loadOrigin: ch = 13
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: = 13 :E: ch
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ch
	pushg 1 ch
	-- Invocation:loadOrigin:scan: = 13
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? char -> B: ? Boolean= 13
	-- ObjectGenerator:gen: super: 13:IS-empty: staticOff: 0
	-- Invocation:gen: 13
	-- Invocation:loadOrigin: 13
	-- Invocation:loadOrigin:scan: 13
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 13
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	jmpFalse L254
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 916 0 #S#916
	rpop
 L254:
	-- ObjectGenerator:gen: super: inx := inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx := inx + 1
	-- Invocation:loadOrigin: inx := inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 read:origin
	-- Invocation:loadOrigin:scan: := inx + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= inx + 1
	-- ObjectGenerator:gen: super: inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx + 1
	-- Invocation:loadOrigin: inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 read:origin
	-- next not assign: + 1 :E: inx
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	-- ObjectGenerator:gen: super: msg.%put ch %at% inx:IS-empty: staticOff: 0
	-- Invocation:gen: msg.%put ch %at% inx
	-- Invocation:loadOrigin: msg.%put ch %at% inx
	-- Invocation:loadOrigin:scan: msg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: msg
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 read:origin
	-- next not assign: %put ch %at% inx :E: msg
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: msg
	rpushg 3 msg
	-- Invocation:loadOrigin:scan: %put ch %at% inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put ch %at% inx
	-- ObjectGenerator:gen: super: ch:IS-empty: staticOff: 0
	-- Invocation:gen: ch
	-- Invocation:loadOrigin: ch
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ch
	pushg 1 ch
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 read:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: %restart read:IS-empty: staticOff: 0
	-- Invocation:gen: %restart read
	-- Invocation:loadOrigin: %restart read
	-- Invocation:loadOrigin:scan: %restart read
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart read
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart read
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	jmp L252
 L253:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 138
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L255:
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 0
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
 L256:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class get 139
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: res
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 140 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L257:
	-- Include:gen: 
 L258:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class free 141
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L259:
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
	rpushg 1 free:origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 0
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
	-- pattern:loadArgs: enableenable
	-- Unary:invoke: 
	-- pattern:load: enable
	%enable 12
 L260:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class start 143
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L261:
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
	rpushg 1 start:origin
	-- Invocation:loadOrigin:scan: := p_status.ACTIVE
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= p_status.ACTIVE
	-- ObjectGenerator:gen: super: p_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: p_status.ACTIVE
	-- Invocation:loadOrigin: p_status.ACTIVE
	-- Invocation:loadOrigin:scan: p_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p_status
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 start:origin
	rpushg 1 BasicProcess:origin
	-- next not assign: ACTIVE :E: p_status
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
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
	-- pattern:loadArgs: innerinner
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
 L262:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 145
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 146 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L263:
	-- Include:gen: 
 L264:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class attach 157
	pushThis 
	rstoreg 2 M
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L265:
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
	rpushg 1 attach:origin
	-- Invocation:loadOrigin:scan: := M
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= M
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	rpushg 2 M
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 main
 L266:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 158
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loopX
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 159 2 loopX
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L267:
	-- Include:gen: 
 L268:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 162
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: S
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L269:
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Core
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: CoreCore
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 156 0 Core
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
	-- pattern:loadArgs: fork(S: ? Object)fork(C1)
	-- ObjectGenerator:gen: super: C1:IS-empty: staticOff: 0
	-- Invocation:gen: C1
	-- Invocation:loadOrigin: C1
	-- Invocation:loadOrigin:scan: C1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Core
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: CoreCore
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 156 0 Core
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
	-- pattern:loadArgs: fork(S: ? Object)fork(C2)
	-- ObjectGenerator:gen: super: C2:IS-empty: staticOff: 0
	-- Invocation:gen: C2
	-- Invocation:loadOrigin: C2
	-- Invocation:loadOrigin:scan: C2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Core
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: CoreCore
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 156 0 Core
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
	-- pattern:loadArgs: fork(S: ? Object)fork(C3)
	-- ObjectGenerator:gen: super: C3:IS-empty: staticOff: 0
	-- Invocation:gen: C3
	-- Invocation:loadOrigin: C3
	-- Invocation:loadOrigin:scan: C3
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C3
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := Core
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Core
	-- ObjectGenerator:gen: super: Core:IS-empty: staticOff: 0
	-- Invocation:gen: Core
	-- Invocation:loadOrigin: Core
	-- Invocation:loadOrigin:scan: Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: CoreCore
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 156 0 Core
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
	-- pattern:loadArgs: fork(S: ? Object)fork(C4)
	-- ObjectGenerator:gen: super: C4:IS-empty: staticOff: 0
	-- Invocation:gen: C4
	-- Invocation:loadOrigin: C4
	-- Invocation:loadOrigin:scan: C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: C4
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	-- pattern:loadArgs: := V: ? Object:= Scheduler
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: SchedulerScheduler
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 144 0 Scheduler
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
	rpushg 1 init:origin
	-- next not assign: attach(S) :E: C1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C1
	rpushg 2 C1
	-- Invocation:loadOrigin:scan: attach(S)
	-- Function:loadArgs: 
	-- pattern:loadArgs: attach(M: ? Scheduler)attach(S)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 157 0 attach
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
	-- pattern:loadArgs: := V: ? Object:= Scheduler
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: SchedulerScheduler
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 144 0 Scheduler
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
	rpushg 1 init:origin
	-- next not assign: attach(S) :E: C2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C2
	rpushg 3 C2
	-- Invocation:loadOrigin:scan: attach(S)
	-- Function:loadArgs: 
	-- pattern:loadArgs: attach(M: ? Scheduler)attach(S)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 157 0 attach
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
	-- pattern:loadArgs: := V: ? Object:= Scheduler
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: SchedulerScheduler
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 144 0 Scheduler
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
	rpushg 1 init:origin
	-- next not assign: attach(S) :E: C3
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C3
	rpushg 4 C3
	-- Invocation:loadOrigin:scan: attach(S)
	-- Function:loadArgs: 
	-- pattern:loadArgs: attach(M: ? Scheduler)attach(S)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 157 0 attach
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
	rpushg 1 init:origin
	-- next not assign: attach(Scheduler) :E: C4
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C4
	rpushg 5 C4
	-- Invocation:loadOrigin:scan: attach(Scheduler)
	-- Function:loadArgs: 
	-- pattern:loadArgs: attach(M: ? Scheduler)attach(Scheduler)
	-- ObjectGenerator:gen: super: Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: Scheduler
	-- Invocation:loadOrigin: Scheduler
	-- Invocation:loadOrigin:scan: Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 init:origin
	rpushg 1 cores:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: SchedulerScheduler
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 144 0 Scheduler
	-- Function:invoke: 
	-- pattern:load: attach(M: ? Scheduler)
	invoke 157 0 attach
	rpop
 L270:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Element 123
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
 L271:
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
	-- pattern:loadArgs: := V: ? Object:= %this Element
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
 L272:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	rpushg 3 res
	rtn(D)
	end 1

	class scan 124
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
 L273:
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
	-- pattern:loadArgs: := V: ? Object:= head
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 scan:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	-- pattern:loadArgs: dodo
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 125 0 do
	rpop
 L274:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scanFromLast 127
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
 L275:
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
	-- pattern:loadArgs: := V: ? Object:= last
	-- ObjectGenerator:gen: super: last:IS-empty: staticOff: 0
	-- Invocation:gen: last
	-- Invocation:loadOrigin: last
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 scanFromLast:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	-- pattern:loadArgs: dodo
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 128 0 do
	rpop
 L276:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class insert 130
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
 L277:
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
	-- pattern:loadArgs: := V: ? Object:= ELM <> NONE
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Invocation:loadOrigin:scan: <> NONE
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> NONE
	-- ObjectGenerator:gen: super: NONE:IS-empty: staticOff: 0
	-- Invocation:gen: NONE
	-- Invocation:loadOrigin: NONE
	-- Invocation:loadOrigin:scan: NONE
	-- Unary:pushThis: 
	-- Unary:loadOrigin: NONE
	-- Unary:loadArgs: 
	-- pattern:loadArgs: noneNONE
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: b
	pushg 1 b
	jmpFalse L279
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 920 0 #S#920
	rpop
 L279:
 L278:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class remove 131
	pushThis 
	rstoreg 2 elm
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L280:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: scan:singular:staticOff: 0
	pushThis 
	invoke 132 0 scan#S#132
	rpop
 L281:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class removeNext 133
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L282:
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
	rpushg 1 removeNext:origin
	-- next not assign: <> none :E: last
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L284
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 924 0 #S#924
	rpop
 L284:
 L283:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: elm
	rpushg 2 elm
	rtn(D)
	end 1

	class isEmpty 134
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L285:
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
	-- pattern:loadArgs: := V: ? Object:= head = none
	-- ObjectGenerator:gen: super: head = none:IS-empty: staticOff: 0
	-- Invocation:gen: head = none
	-- Invocation:loadOrigin: head = none
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 isEmpty:origin
	-- next not assign: = none :E: head
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: = none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = obj: ? Object -> V: ? Boolean= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L286:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class clear 135
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L287:
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
	rpushg 1 clear:origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
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
	rpushg 1 clear:origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L288:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 165
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L289:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('Q'):IS-empty: staticOff: 0
	-- Invocation:gen: put('Q')
	-- Invocation:loadOrigin: put('Q')
	-- Invocation:loadOrigin:scan: put('Q')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('Q')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('Q')
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
 L290:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry 149
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L291:
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
	rpushg 1 entry:origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 139 0 get
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
	rpushg 1 entry:origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L292:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class add 150
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L293:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 151 0 entry#S#151
	rpop
 L294:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class dcr 152
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L295:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 153 0 entry#S#153
	rpop
 L296:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class running 154
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L297:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 155 0 entry#S#155
	rpop
 L298:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class entry 167
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L299:
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
	rpushg 1 entry:origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 139 0 get
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
	rpushg 1 entry:origin
	-- Invocation:loadOrigin:scan: := V + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= V + 1
	-- ObjectGenerator:gen: super: V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V + 1
	-- Invocation:loadOrigin: V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 entry:origin
	-- next not assign: + 1 :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	rpushg 1 entry:origin
	-- next not assign: > 1 :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: > 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: > V: ? integer -> B: ? Boolean> 1
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
	jmpFalse L301
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 932 0 #S#932
	rpop
 L301:
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- pattern:loadArgs: innerinner
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
	rpushg 1 entry:origin
	-- Invocation:loadOrigin:scan: := V - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= V - 1
	-- ObjectGenerator:gen: super: V - 1:IS-empty: staticOff: 0
	-- Invocation:gen: V - 1
	-- Invocation:loadOrigin: V - 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 entry:origin
	-- next not assign: - 1 :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- 1
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
	rpushg 1 entry:origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L300:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 168
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=168
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L302:
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 0
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
 L303:
	rtnInner
	end 1

	class insert 169
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=169
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L304:
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
	rpushg 1 insert:origin
	-- next not assign: insert(P) :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- pattern:loadArgs: insert(elm: ? Object)insert(P)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 130 0 insert
	rpop
 L305:
	rtnInner
	end 1

	class removeNext 170
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L306:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 171 0 entry#S#171
	rpop
 L307:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: P
	rpushg 2 P
	rtn(D)
	end 1

	class remove 172
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=172
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L308:
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
	rpushg 1 remove:origin
	-- next not assign: remove(P) :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: remove(P)
	-- Function:loadArgs: 
	-- pattern:loadArgs: remove(elm: ? Object)remove(P)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: remove(elm: ? Object)
	invoke 131 0 remove
	rpop
 L309:
	rtnInner
	end 1

	class isEmpty 173
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L310:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 174 0 entry#S#174
	rpop
 L311:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class display 175
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=175
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L312:
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
	rpushg 1 display:origin
	-- next not assign: display :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: display
	-- Unary:loadArgs: 
	-- pattern:loadArgs: displaydisplay
	-- Unary:invoke: 
	-- pattern:load: display
	invoke 165 0 display
	rpop
 L313:
	rtnInner
	end 1

	class addWaiting 176
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=176
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L314:
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
	rpushg 1 addWaiting:origin
	-- Invocation:loadOrigin:scan: := W + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= W + 1
	-- ObjectGenerator:gen: super: W + 1:IS-empty: staticOff: 0
	-- Invocation:gen: W + 1
	-- Invocation:loadOrigin: W + 1
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 addWaiting:origin
	-- next not assign: + 1 :E: W
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
 L315:
	rtnInner
	end 1

	class dcrWaiting 177
	rstore 1 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=177
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L316:
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
	rpushg 1 dcrWaiting:origin
	-- Invocation:loadOrigin:scan: := W - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= W - 1
	-- ObjectGenerator:gen: super: W - 1:IS-empty: staticOff: 0
	-- Invocation:gen: W - 1
	-- Invocation:loadOrigin: W - 1
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 dcrWaiting:origin
	-- next not assign: - 1 :E: W
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- 1
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
 L317:
	rtnInner
	end 1

	class hasWaiting 178
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L318:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: entry:singular:staticOff: 0
	pushThis 
	invoke 179 0 entry#S#179
	rpop
 L319:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class init 181
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L320:
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
	rpushg 1 init:origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 139 0 get
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
	rpushg 1 init:origin
	-- next not assign: init :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 138 0 init
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
	rpushg 1 init:origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L321:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 182
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L322:
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
	rpushg 1 display:origin
	-- next not assign: get :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 139 0 get
	rpop
	-- ObjectGenerator:gen: super: inner:IS-empty: staticOff: 0
	-- Invocation:gen: inner
	-- Invocation:loadOrigin: inner
	-- Invocation:loadOrigin:scan: inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: inner
	-- Unary:loadArgs: 
	-- pattern:loadArgs: innerinner
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
	rpushg 1 display:origin
	-- next not assign: free :E: L
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L323:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Kscan 184
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loopB
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 185 2 loopB
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L324:
	-- Include:gen: 
 L325:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class get 186
	pushThis 
	rstoreg 2 caller
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: waitForChar
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 187 3 waitForChar
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L326:
	-- Include:gen: 
 L327:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: ch
	pushg 1 ch
	rtn(D)
	end 1

	class %if%then%%else%#S#198 198
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
	rpushg 1 put:origin
	rpushg 1 Array:origin
	rpushg 1 EMC2array:origin
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
	rpushg 1 put:origin
	-- next not assign: = rep.length :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = rep.length
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= rep.length
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
	rpushg 1 put:origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> res: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 59 0 length
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L328:
 L329:
	rtnInner
	end 1

	class %if%then%%else%#S#200 200
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
	rpushg 1 get:origin
	rpushg 1 Array:origin
	rpushg 1 EMC2array:origin
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
	rpushg 1 get:origin
	-- next not assign: = rep.length :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = rep.length
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= rep.length
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
	rpushg 1 get:origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> res: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 59 0 length
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L330:
 L331:
	rtnInner
	end 1

	class %if%then%%else%#S#202 202
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
	rpushg 1 nxt:origin
	rpushg 1 Array:origin
	rpushg 1 EMC2array:origin
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
	rpushg 1 nxt:origin
	-- next not assign: = noof :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = noof
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= noof
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
	rpushg 1 nxt:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L332:
 L333:
	rtnInner
	end 1

	class %if%then%%else%#S#204 204
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
	rpushg 1 prv:origin
	rpushg 1 Array:origin
	rpushg 1 EMC2array:origin
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
	rpushg 1 prv:origin
	-- next not assign: = noof :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: = noof
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= noof
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
	rpushg 1 prv:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L334:
 L335:
	rtnInner
	end 1

	class loop 206
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L336:
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := rep.%get pos
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= rep.%get pos
	-- ObjectGenerator:gen: super: rep.%get pos:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos
	-- Invocation:loadOrigin: rep.%get pos
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 forAll:origin
	-- next not assign: %get pos :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos
	-- ObjectGenerator:gen: super: pos:IS-empty: staticOff: 0
	-- Invocation:gen: pos
	-- Invocation:loadOrigin: pos
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 forAll:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
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
	rpushg 1 loop:origin
	rpushg 1 forAll:origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= pos + 1
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 forAll:origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	rpushg 1 loop:origin
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
	rpushg 1 loop:origin
	rpushg 1 forAll:origin
	-- next not assign: < noof :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: < noof
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< noof
	-- ObjectGenerator:gen: super: noof:IS-empty: staticOff: 0
	-- Invocation:gen: noof
	-- Invocation:loadOrigin: noof
	-- Invocation:loadOrigin:scan: noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noof
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 forAll:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L338
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 944 0 #S#944
	rpop
 L338:
 L337:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#208 208
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
	rpushg 1 print:origin
	rpushg 1 Array:origin
	rpushg 1 EMC2array:origin
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
	rpushg 1 print:origin
	-- next not assign: length :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> res: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> res: ? integer
	invoke 59 0 length
	topSuper  67
	rtnInner
	DO:
	mvStack 
 L339:
 L340:
	rtnInner
	end 1

	class #S#946 946
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L341:
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
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L342:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class run 223
	pushThis 
	rstoreg 2 P
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L343:
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
	rpushg 1 run:origin
	-- next not assign: get :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 139 0 get
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
	rpushg 1 run:origin
	-- next not assign: insert(P) :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- pattern:loadArgs: insert(elm: ? Object)insert(P)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 130 0 insert
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
	rpushg 1 run:origin
	rpushg 1 ForkJoin:origin
	-- next not assign: insert(P) :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- pattern:loadArgs: insert(P: ? BasicProcess)insert(P)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 169 0 insert
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
	rpushg 1 run:origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L344:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class AwaitTermination 224
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 225 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L345:
	-- Include:gen: 
 L346:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class init 230
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L347:
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
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 1
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
 L348:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class wait 231
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: theActive
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L349:
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
	rpushg 1 wait:origin
	-- next not assign: get :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 139 0 get
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
	rpushg 1 wait:origin
	-- Invocation:loadOrigin:scan: := cnt - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= cnt - 1
	-- ObjectGenerator:gen: super: cnt - 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt - 1
	-- Invocation:loadOrigin: cnt - 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 wait:origin
	-- next not assign: - 1 :E: cnt
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- 1
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
	invoke 232 0 %if%then%%else%#S#232
	rpop
 L350:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class signal 233
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: P
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L351:
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
	rpushg 1 signal:origin
	-- next not assign: get :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 139 0 get
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
	rpushg 1 signal:origin
	-- Invocation:loadOrigin:scan: := cnt + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= cnt + 1
	-- ObjectGenerator:gen: super: cnt + 1:IS-empty: staticOff: 0
	-- Invocation:gen: cnt + 1
	-- Invocation:loadOrigin: cnt + 1
	-- Invocation:loadOrigin:scan: cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 signal:origin
	-- next not assign: + 1 :E: cnt
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	invoke 234 0 %if%then%%else%#S#234
	rpop
 L352:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class start 236
	rstore 2 origin
	allocEventQ
	-- super start
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=236
	pushThis 
	rpushg 2 iOrigin
	topSuper  143
	-- VarRef:gen: P
	rtnInner
	DO:
	doEventQ
	mvStack 
 L353:
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
	-- pattern:loadArgs: := V: ? Object:= %this Process
	-- ObjectGenerator:gen: super: %this Process:IS-empty: staticOff: 0
	-- Invocation:gen: %this Process
	-- Invocation:loadOrigin: %this Process
	-- Invocation:loadOrigin:scan: %this Process
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this Process
	-- AdjustOrigin: 0
	rpushg 2 start:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this Process
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 P
	-- ObjectGenerator:gen: super: ("starting: " + id + "\n").print:IS-empty: staticOff: 0
	-- Invocation:gen: ("starting: " + id + "\n").print
	-- Invocation:loadOrigin: ("starting: " + id + "\n").print
	-- Invocation:loadOrigin:scan: ("starting: " + id + "\n")
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ("starting: " + id + "\n")
	-- Invocation:loadOrigin: "starting: " + id + "\n"
	-- Invocation:loadOrigin:scan: "starting: "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText starting: 
	-- next not assign: + id + "\n" :E: "starting: "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: + id + "\n"
	-- BE:loadOrigin:E: + id + "\n"
	-- next not assign: print :E: + id + "\n"
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + S: ? String -> V: ? String+ id + "\n"
	-- ObjectGenerator:gen: super: id + "\n":IS-empty: staticOff: 0
	-- Invocation:gen: id + "\n"
	-- Invocation:loadOrigin: id + "\n"
	-- Invocation:loadOrigin:scan: id
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: id
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 start:origin
	-- next not assign: + "\n" :E: id
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: id
	rpushg 2 id
	-- Invocation:loadOrigin:scan: + "\n"
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + S: ? String -> V: ? String+ "\n"
	-- ObjectGenerator:gen: super: "\n":IS-empty: staticOff: 0
	-- Invocation:gen: "\n"
	-- Invocation:loadOrigin: "\n"
	-- Invocation:loadOrigin:scan: "\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText \n
	-- String::loadArgs: 
	-- String::invoke: 
	-- Binary:invoke: 
	-- pattern:load: + S: ? String -> V: ? String
	invoke 88 0 +
	-- Binary:invoke: 
	-- pattern:load: + S: ? String -> V: ? String
	invoke 88 0 +
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
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
	rpushg 2 start:origin
	rpushg 1 Process:origin
	-- next not assign: insert(P) :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- pattern:loadArgs: insert(P: ? BasicProcess)insert(P)
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 3 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 169 0 insert
	rpop
 L354:
	rtnInner
	end 1

	class init 238
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L355:
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
	rpushg 1 init:origin
	-- next not assign: init :E: mutex
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 230 0 init
	rpop
 L356:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry 239
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L357:
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
	rpushg 1 entry:origin
	-- next not assign: wait :E: mutex
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: wait
	-- Unary:loadArgs: 
	-- pattern:loadArgs: waitwait
	-- Unary:invoke: 
	-- pattern:load: wait
	invoke 231 0 wait
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
	rpushg 1 entry:origin
	-- Invocation:loadOrigin:scan: := V + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= V + 1
	-- ObjectGenerator:gen: super: V + 1:IS-empty: staticOff: 0
	-- Invocation:gen: V + 1
	-- Invocation:loadOrigin: V + 1
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 entry:origin
	-- next not assign: + 1 :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	-- pattern:loadArgs: innerinner
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
	rpushg 1 entry:origin
	-- next not assign: signal :E: mutex
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: signal
	-- Unary:loadArgs: 
	-- pattern:loadArgs: signalsignal
	-- Unary:invoke: 
	-- pattern:load: signal
	invoke 233 0 signal
	rpop
 L358:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class wait 240
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: cond
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 241 2 loop
	rpop
	innerA  1
	rtnEventQ 0
	DO:
	mvStack 
 L359:
	-- Include:gen: 
 L360:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scan 245
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L361:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: N := N + 1:IS-empty: staticOff: 0
	-- Invocation:gen: N := N + 1
	-- Invocation:loadOrigin: N := N + 1
	-- Invocation:loadOrigin:scan: N
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: N
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 scan:origin
	-- Invocation:loadOrigin:scan: := N + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= N + 1
	-- ObjectGenerator:gen: super: N + 1:IS-empty: staticOff: 0
	-- Invocation:gen: N + 1
	-- Invocation:loadOrigin: N + 1
	-- Invocation:loadOrigin:scan: N
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: N
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 scan:origin
	-- next not assign: + 1 :E: N
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: N
	pushg 3 N
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	storeg 3 N
	-- ObjectGenerator:gen: super: %if (N /% 4) = 0 %then% 
    status := '?' %else% 
    
    status := '!'
    val := ch
    ch := ch + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 246 0 %if%then%%else%#S#246
	rpop
 L362:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class get 248
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L363:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: next := next + 1:IS-empty: staticOff: 0
	-- Invocation:gen: next := next + 1
	-- Invocation:loadOrigin: next := next + 1
	-- Invocation:loadOrigin:scan: next
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: next
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 get:origin
	-- Invocation:loadOrigin:scan: := next + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= next + 1
	-- ObjectGenerator:gen: super: next + 1:IS-empty: staticOff: 0
	-- Invocation:gen: next + 1
	-- Invocation:loadOrigin: next + 1
	-- Invocation:loadOrigin:scan: next
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: next
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 get:origin
	-- next not assign: + 1 :E: next
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: next
	pushg 1 next
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	storeg 1 next
	-- ObjectGenerator:gen: super: ch := buf.%get next:IS-empty: staticOff: 0
	-- Invocation:gen: ch := buf.%get next
	-- Invocation:loadOrigin: ch := buf.%get next
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := buf.%get next
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= buf.%get next
	-- ObjectGenerator:gen: super: buf.%get next:IS-empty: staticOff: 0
	-- Invocation:gen: buf.%get next
	-- Invocation:loadOrigin: buf.%get next
	-- Invocation:loadOrigin:scan: buf
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: buf
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 get:origin
	-- next not assign: %get next :E: buf
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: buf
	rpushg 2 buf
	-- Invocation:loadOrigin:scan: %get next
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get next
	-- ObjectGenerator:gen: super: next:IS-empty: staticOff: 0
	-- Invocation:gen: next
	-- Invocation:loadOrigin: next
	-- Invocation:loadOrigin:scan: next
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: next
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 get:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: next
	pushg 1 next
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 ch
 L364:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: ch
	pushg 1 ch
	rtn(D)
	end 1

	class go 249
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 250 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L365:
	-- Include:gen: 
 L366:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#960 960
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L367:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "INVALID_SOCKET\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "INVALID_SOCKET\n".print
	-- Invocation:loadOrigin: "INVALID_SOCKET\n".print
	-- Invocation:loadOrigin:scan: "INVALID_SOCKET\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText INVALID_SOCKET\n
	-- next not assign: print :E: "INVALID_SOCKET\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L368:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class INVALID_SOCKET 278
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L369:
	-- Include:gen: 
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
	-- pattern:loadArgs: := V: ? Object:= 0 - V
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
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- V
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Binary:invoke: 
	-- pattern:load: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L370:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 1 V
	rtn(D)
	end 1

	class init 279
	pushThis 
	storeg 1 pno
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: new_socket -> V: ? integer
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L371:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "init socket\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "init socket\n".print
	-- Invocation:loadOrigin: "init socket\n".print
	-- Invocation:loadOrigin:scan: "init socket\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText init socket\n
	-- next not assign: print :E: "init socket\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
	-- ObjectGenerator:gen: super: sockfd := new_socket:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd := new_socket
	-- Invocation:loadOrigin: sockfd := new_socket
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := new_socket
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= new_socket
	-- ObjectGenerator:gen: super: new_socket:IS-empty: staticOff: 0
	-- Invocation:gen: new_socket
	-- Invocation:loadOrigin: new_socket
	-- Invocation:loadOrigin:scan: new_socket
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: new_socket
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: new_socket -> V: ? integernew_socket
	-- Unary:invoke: 
	-- pattern:load: new_socket -> V: ? integer
	invokeExternal 6
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 sockfd
	-- ObjectGenerator:gen: super: %if sockfd = INVALID_SOCKET %then% 
    
    "SocketSystem: INVALID_SOCKET\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: %if sockfd = INVALID_SOCKET %then% 
    
    "SocketSystem: INVALID_SOCKET\n".print
	-- Invocation:loadOrigin: %if sockfd = INVALID_SOCKET %then% 
    
    "SocketSystem: INVALID_SOCKET\n".print
	-- Invocation:loadOrigin:scan: %if sockfd = INVALID_SOCKET %then% 
    
    "SocketSystem: INVALID_SOCKET\n".print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if sockfd = INVALID_SOCKET %then% 
    
    "SocketSystem: INVALID_SOCKET\n".print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if sockfd = INVALID_SOCKET %then% 
    
    "SocketSystem: INVALID_SOCKET\n".print
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: sockfd = INVALID_SOCKET:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd = INVALID_SOCKET
	-- Invocation:loadOrigin: sockfd = INVALID_SOCKET
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- next not assign: = INVALID_SOCKET :E: sockfd
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Invocation:loadOrigin:scan: = INVALID_SOCKET
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= INVALID_SOCKET
	-- ObjectGenerator:gen: super: INVALID_SOCKET:IS-empty: staticOff: 0
	-- Invocation:gen: INVALID_SOCKET
	-- Invocation:loadOrigin: INVALID_SOCKET
	-- Invocation:loadOrigin:scan: INVALID_SOCKET
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: INVALID_SOCKET
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: INVALID_SOCKET -> V: ? integerINVALID_SOCKET
	-- Unary:invoke: 
	-- pattern:load: INVALID_SOCKET -> V: ? integer
	invoke 278 0 INVALID_SOCKET
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L373
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 961 0 #S#961
	rpop
 L373:
	-- ObjectGenerator:gen: super: portno := pno:IS-empty: staticOff: 0
	-- Invocation:gen: portno := pno
	-- Invocation:loadOrigin: portno := pno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Invocation:loadOrigin:scan: := pno
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= pno
	-- ObjectGenerator:gen: super: pno:IS-empty: staticOff: 0
	-- Invocation:gen: pno
	-- Invocation:loadOrigin: pno
	-- Invocation:loadOrigin:scan: pno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pno
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pno
	pushg 1 pno
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 portno
	-- ObjectGenerator:gen: super: ioctl(1):IS-empty: staticOff: 0
	-- Invocation:gen: ioctl(1)
	-- Invocation:loadOrigin: ioctl(1)
	-- Invocation:loadOrigin:scan: ioctl(1)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: ioctl(1)
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 init:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: ioctl(cmd: ? integer) -> V: ? integerioctl(1)
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
	-- pattern:load: ioctl(cmd: ? integer) -> V: ? integer
	invoke 281 0 ioctl
	vpop
 L372:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class connect 283
	pushThis 
	rstoreg 2 adr
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_connect(S: ? integer,adr: ? String.string,portno: ? integer) -> V: ? integer
	-- VarRef:gen: V
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L374:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_connect(sockfd,adr,portno):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin: V := do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_connect(sockfd,adr,portno)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_connect(sockfd,adr,portno)
	-- ObjectGenerator:gen: super: do_connect(sockfd,adr,portno):IS-empty: staticOff: 0
	-- Invocation:gen: do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin: do_connect(sockfd,adr,portno)
	-- Invocation:loadOrigin:scan: do_connect(sockfd,adr,portno)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_connect(sockfd,adr,portno)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_connect(S: ? integer,adr: ? String.string,portno: ? integer) -> V: ? integerdo_connect(sockfd,adr,portno)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 connect:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: adr:IS-empty: staticOff: 0
	-- Invocation:gen: adr
	-- Invocation:loadOrigin: adr
	-- Invocation:loadOrigin:scan: adr
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: adr
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: adr
	rpushg 2 adr
	-- ObjectGenerator:gen: super: portno:IS-empty: staticOff: 0
	-- Invocation:gen: portno
	-- Invocation:loadOrigin: portno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 connect:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: portno
	pushg 2 portno
	-- Function:invoke: 
	-- pattern:load: do_connect(S: ? integer,adr: ? String.string,portno: ? integer) -> V: ? integer
	invokeExternal 7
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L375:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ioctl 281
	pushThis 
	storeg 1 cmd
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_ioctl(S: ? integer,cmd: ? integer) -> res: ? integer
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L376:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_ioctl(sockfd,cmd):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin: V := do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_ioctl(sockfd,cmd)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_ioctl(sockfd,cmd)
	-- ObjectGenerator:gen: super: do_ioctl(sockfd,cmd):IS-empty: staticOff: 0
	-- Invocation:gen: do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin: do_ioctl(sockfd,cmd)
	-- Invocation:loadOrigin:scan: do_ioctl(sockfd,cmd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_ioctl(sockfd,cmd)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_ioctl(S: ? integer,cmd: ? integer) -> res: ? integerdo_ioctl(sockfd,cmd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 ioctl:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: cmd:IS-empty: staticOff: 0
	-- Invocation:gen: cmd
	-- Invocation:loadOrigin: cmd
	-- Invocation:loadOrigin:scan: cmd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: cmd
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cmd
	pushg 1 cmd
	-- Function:invoke: 
	-- pattern:load: do_ioctl(S: ? integer,cmd: ? integer) -> res: ? integer
	invokeExternal 14
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 V
 L377:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 2 V
	rtn(D)
	end 1

	class bind 285
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_bind(S: ? integer,port: ? integer) -> V: ? integer
	-- VarRef:gen: V
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L378:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_bind(sockfd,portno):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_bind(sockfd,portno)
	-- Invocation:loadOrigin: V := do_bind(sockfd,portno)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_bind(sockfd,portno)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_bind(sockfd,portno)
	-- ObjectGenerator:gen: super: do_bind(sockfd,portno):IS-empty: staticOff: 0
	-- Invocation:gen: do_bind(sockfd,portno)
	-- Invocation:loadOrigin: do_bind(sockfd,portno)
	-- Invocation:loadOrigin:scan: do_bind(sockfd,portno)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_bind(sockfd,portno)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_bind(S: ? integer,port: ? integer) -> V: ? integerdo_bind(sockfd,portno)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 bind:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: portno:IS-empty: staticOff: 0
	-- Invocation:gen: portno
	-- Invocation:loadOrigin: portno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 bind:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: portno
	pushg 2 portno
	-- Function:invoke: 
	-- pattern:load: do_bind(S: ? integer,port: ? integer) -> V: ? integer
	invokeExternal 11
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 V
 L379:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class listen 287
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_listen(S: ? integer) -> V: ? integer
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L380:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: do_listen(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: do_listen(sockfd)
	-- Invocation:loadOrigin: do_listen(sockfd)
	-- Invocation:loadOrigin:scan: do_listen(sockfd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_listen(sockfd)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_listen(S: ? integer) -> V: ? integerdo_listen(sockfd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 listen:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Function:invoke: 
	-- pattern:load: do_listen(S: ? integer) -> V: ? integer
	invokeExternal 12
	vpop
	-- ObjectGenerator:gen: super: "Listen\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "Listen\n".print
	-- Invocation:loadOrigin: "Listen\n".print
	-- Invocation:loadOrigin:scan: "Listen\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Listen\n
	-- next not assign: print :E: "Listen\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L381:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class accept 289
	pushThis 
	rstoreg 2 theCaller
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_accept(S: ? integer) -> V: ? integer
	-- VarRef:gen: S
	-- pattern:gen: awaitAccept
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L382:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sock := Socket:IS-empty: staticOff: 0
	-- Invocation:gen: sock := Socket
	-- Invocation:loadOrigin: sock := Socket
	-- Invocation:loadOrigin:scan: sock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sock
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := Socket
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Socket
	-- ObjectGenerator:gen: super: Socket:IS-empty: staticOff: 0
	-- Invocation:gen: Socket
	-- Invocation:loadOrigin: Socket
	-- Invocation:loadOrigin:scan: Socket
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Socket
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 accept:origin
	rpushg 1 Socket:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: SocketSocket
	-- Unary:invoke: 
	-- pattern:load: Socket
	invoke 277 0 Socket
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 sock
	-- ObjectGenerator:gen: super: awaitAccept:IS-empty: staticOff: 0
	-- Invocation:gen: awaitAccept
	-- Invocation:loadOrigin: awaitAccept
	-- Invocation:loadOrigin:scan: awaitAccept
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: awaitAccept
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: awaitAcceptawaitAccept
	-- Unary:invoke: 
	-- pattern:load: awaitAccept
	invoke 291 0 awaitAccept
	rpop
	-- ObjectGenerator:gen: super: sock.sockfd := S:IS-empty: staticOff: 0
	-- Invocation:gen: sock.sockfd := S
	-- Invocation:loadOrigin: sock.sockfd := S
	-- Invocation:loadOrigin:scan: sock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sock
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: sockfd :E: sock
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sock
	rpushg 3 sock
	-- Invocation:loadOrigin:scan: sockfd
	-- Invocation:loadOrigin:scan: := S
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= S
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	pushg 1 S
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 sockfd
	-- ObjectGenerator:gen: super: sock.portno := portno:IS-empty: staticOff: 0
	-- Invocation:gen: sock.portno := portno
	-- Invocation:loadOrigin: sock.portno := portno
	-- Invocation:loadOrigin:scan: sock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sock
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: portno :E: sock
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sock
	rpushg 3 sock
	-- Invocation:loadOrigin:scan: portno
	-- Invocation:loadOrigin:scan: := portno
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= portno
	-- ObjectGenerator:gen: super: portno:IS-empty: staticOff: 0
	-- Invocation:gen: portno
	-- Invocation:loadOrigin: portno
	-- Invocation:loadOrigin:scan: portno
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: portno
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 accept:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: portno
	pushg 2 portno
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 portno
 L383:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: sock
	rpushg 3 sock
	rtn(D)
	end 1

	class send 292
	pushThis 
	rstoreg 2 msg
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_send(S: ? integer,msg: ? String.string) -> V: ? integer
	-- VarRef:gen: V
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L384:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := do_send(sockfd,msg):IS-empty: staticOff: 0
	-- Invocation:gen: V := do_send(sockfd,msg)
	-- Invocation:loadOrigin: V := do_send(sockfd,msg)
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := do_send(sockfd,msg)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_send(sockfd,msg)
	-- ObjectGenerator:gen: super: do_send(sockfd,msg):IS-empty: staticOff: 0
	-- Invocation:gen: do_send(sockfd,msg)
	-- Invocation:loadOrigin: do_send(sockfd,msg)
	-- Invocation:loadOrigin:scan: do_send(sockfd,msg)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_send(sockfd,msg)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_send(S: ? integer,msg: ? String.string) -> V: ? integerdo_send(sockfd,msg)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 send:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- ObjectGenerator:gen: super: msg:IS-empty: staticOff: 0
	-- Invocation:gen: msg
	-- Invocation:loadOrigin: msg
	-- Invocation:loadOrigin:scan: msg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: msg
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: msg
	rpushg 2 msg
	-- Function:invoke: 
	-- pattern:load: do_send(S: ? integer,msg: ? String.string) -> V: ? integer
	invokeExternal 8
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 V
 L385:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 1 V
	rtn(D)
	end 1

	class receive 294
	pushThis 
	rstoreg 2 caller
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_rec(S: ? integer) -> msg: ? String.String
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 296 4 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L386:
	-- Include:gen: 
 L387:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: msg
	rpushg 3 msg
	rtn(D)
	end 1

	class close 297
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: do_close(S: ? integer)
	rtnEventQ 0
	DO:
	mvStack 
 L388:
	-- Include:gen: 
 L389:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doplus 89
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
	rpushg 1 doplus:origin
	rpushg 1 +:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)Indexed(L + S.length,Integer)
	-- ObjectGenerator:gen: super: L + S.length:IS-empty: staticOff: 0
	-- Invocation:gen: L + S.length
	-- Invocation:loadOrigin: L + S.length
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 doplus:origin
	-- next not assign: + S.length :E: L
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Invocation:loadOrigin:scan: + S.length
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ S.length
	-- ObjectGenerator:gen: super: S.length:IS-empty: staticOff: 0
	-- Invocation:gen: S.length
	-- Invocation:loadOrigin: S.length
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 doplus:origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 56 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L390:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% L %do% 
    e := %get inx
    T.%put e %at% inx:IS-empty: staticOff: 0
	pushThis 
	invoke 90 0 %for%to%%do%#S#90
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i:IS-empty: staticOff: 0
	pushThis 
	invoke 91 0 %for%to%%do%#S#91
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
	rpushg 1 doplus:origin
	-- Invocation:loadOrigin:scan: := T.asString
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= T.asString
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
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: asString
	-- Unary:loadArgs: 
	-- pattern:loadArgs: asString -> S: ? ObjectasString
	-- Unary:invoke: 
	-- pattern:load: asString -> S: ? Object
	%asString 118
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 V
 L391:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#94 94
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
	rpushg 1 scan:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
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
	rpushg 1 scan:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
	topSuper  67
	rtnInner
	DO:
	mvStack 
 L392:
 L393:
	rtnInner
	end 1

	class %for%to%%do%#S#96 96
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
	rpushg 1 print:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
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
	rpushg 1 print:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
	topSuper  67
	rtnInner
	DO:
	mvStack 
 L394:
 L395:
	rtnInner
	end 1

	class loop 98
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
 L396:
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
	-- pattern:loadArgs: := V: ? Object:= length
	-- ObjectGenerator:gen: super: length:IS-empty: staticOff: 0
	-- Invocation:gen: length
	-- Invocation:loadOrigin: length
	-- Invocation:loadOrigin:scan: length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: length
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 =:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 3 L
	-- Invocation:loadOrigin:scan: <> S.length
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> V: ? integer -> B: ? Boolean<> S.length
	-- ObjectGenerator:gen: super: S.length:IS-empty: staticOff: 0
	-- Invocation:gen: S.length
	-- Invocation:loadOrigin: S.length
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
	-- Binary:invoke: 
	-- pattern:load: <> V: ? integer -> B: ? Boolean
	55
	jmpFalse L398
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 909 0 #S#909
	rpop
 L398:
	-- ObjectGenerator:gen: super: B := true:IS-empty: staticOff: 0
	-- Invocation:gen: B := true
	-- Invocation:loadOrigin: B := true
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := true
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= true
	-- ObjectGenerator:gen: super: true:IS-empty: staticOff: 0
	-- Invocation:gen: true
	-- Invocation:loadOrigin: true
	-- Invocation:loadOrigin:scan: true
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: true
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 loop:origin
	rpushg 1 =:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: True -> B: ? Booleantrue
	-- Unary:invoke: 
	-- pattern:load: True -> B: ? Boolean
	invoke 34 0 True
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
	invoke 99 0 %for%to%%do%#S#99
	rpop
 L397:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 101
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
 L399:
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
	-- pattern:loadArgs: := V: ? Object:= length
	-- ObjectGenerator:gen: super: length:IS-empty: staticOff: 0
	-- Invocation:gen: length
	-- Invocation:loadOrigin: length
	-- Invocation:loadOrigin:scan: length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: length
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
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
	-- pattern:loadArgs: := V: ? Object:= S.length
	-- ObjectGenerator:gen: super: S.length:IS-empty: staticOff: 0
	-- Invocation:gen: S.length
	-- Invocation:loadOrigin: S.length
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
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
	-- pattern:loadArgs: := V: ? Object:= L1
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
	-- VarRef:loadArgs: 
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
	invoke 106 0 %if%then%%else%#S#106
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
	-- pattern:loadArgs: matchEqmatchEq
	-- Unary:invoke: 
	-- pattern:load: matchEq
	invoke 102 0 matchEq
	rpop
 L400:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Point 532
	pushThis 
	storeg 2 y
	pushThis 
	storeg 1 x
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: := p: ? Point
	-- pattern:gen: getx -> r: ? integer
	rtnEventQ 0
	DO:
	mvStack 
 L401:
	-- Include:gen: 
 L402:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#904 904
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L403:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: enable:IS-empty: staticOff: 0
	-- Invocation:gen: enable
	-- Invocation:loadOrigin: enable
	-- Invocation:loadOrigin:scan: enable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: enable
	-- Unary:loadArgs: 
	-- pattern:loadArgs: enableenable
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
	-- pattern:loadArgs: sleep(V: ? integer)sleep(50)
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
	break 1 249
 L404:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#916 916
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L405:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %leave read:IS-empty: staticOff: 0
	-- Invocation:gen: %leave read
	-- Invocation:loadOrigin: %leave read
	-- Invocation:loadOrigin:scan: %leave read
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave read
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave read
	-- KeyWord:invoke: 
	-- pattern:load: %leave Obj: ? integer
	break 1 253
 L406:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 140
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L407:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: disable:IS-empty: staticOff: 0
	-- Invocation:gen: disable
	-- Invocation:loadOrigin: disable
	-- Invocation:loadOrigin:scan: disable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: disable
	-- Unary:loadArgs: 
	-- pattern:loadArgs: disabledisable
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := 17
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 17
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := M.cmpAndSwap(1)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= M.cmpAndSwap(1)
	-- ObjectGenerator:gen: super: M.cmpAndSwap(1):IS-empty: staticOff: 0
	-- Invocation:gen: M.cmpAndSwap(1)
	-- Invocation:loadOrigin: M.cmpAndSwap(1)
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 get:origin
	-- next not assign: cmpAndSwap(1) :E: M
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushc 2
	-- Invocation:loadOrigin:scan: cmpAndSwap(1)
	-- Function:loadArgs: 
	-- pattern:loadArgs: cmpAndSwap(V: ? integer) -> res: ? integercmpAndSwap(1)
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
	rpushg 1 loop:origin
	-- next not assign: = 1 :E: res
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: res
	pushg 1 res
	-- Invocation:loadOrigin:scan: = 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 1
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
	jmpFalse L409
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 926 0 #S#926
	rpop
 L409:
 L408:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 146
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L410:
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 1
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := SQS.removeNext
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= SQS.removeNext
	-- ObjectGenerator:gen: super: SQS.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: SQS.removeNext
	-- Invocation:loadOrigin: SQS.removeNext
	-- Invocation:loadOrigin:scan: SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: SQS
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: removeNext :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: removeNext
	-- Unary:loadArgs: 
	-- pattern:loadArgs: removeNext -> P: ? BasicProcessremoveNext
	-- Unary:invoke: 
	-- pattern:load: removeNext -> P: ? BasicProcess
	invoke 170 0 removeNext
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: <> none :E: active
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L412
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 927 0 #S#927
	rpop
 L412:
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
	invoke 147 0 %if%then%%else%#S#147
	rpop
 L411:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loopX 159
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L413:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if main <> none %then% 
    main.resume %else% 
    sleep(100)
    %restart loopX:IS-empty: staticOff: 0
	pushThis 
	invoke 160 0 %if%then%%else%#S#160
	rpop
 L414:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 125
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 126 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L415:
	-- Include:gen: 
 L416:
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
 L417:
	-- Include:gen: 
 L418:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#920 920
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L419:
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
	rpushg 1 #S#920:origin
	-- Invocation:loadOrigin:scan: := Element(elm)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Element(elm)
	-- ObjectGenerator:gen: super: Element(elm):IS-empty: staticOff: 0
	-- Invocation:gen: Element(elm)
	-- Invocation:loadOrigin: Element(elm)
	-- Invocation:loadOrigin:scan: Element(elm)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Element(elm)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Element(elm: ? Object) -> res: ? ElementElement(elm)
	-- ObjectGenerator:gen: super: elm:IS-empty: staticOff: 0
	-- Invocation:gen: elm
	-- Invocation:loadOrigin: elm
	-- Invocation:loadOrigin:scan: elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elm
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 #S#920:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Function:invoke: 
	-- pattern:load: Element(elm: ? Object) -> res: ? Element
	invoke 123 0 Element
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
	invoke 921 0 %if%then%%else%#S#921
	rpop
 L420:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class scan#S#132 132
	rstore 4 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=132
	-- Invocation:loadOrigin: scan
	-- Invocation:loadOrigin:scan: scan
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: scan
	-- AdjustOrigin: 4
	rpushg 4 origin
	-- on : 1
	rpushg 1 remove:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: scanscan
	topSuper  124
	rtnInner
	DO:
	doEventQ
	mvStack 
 L421:
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
	rpushg 4 scan#S#132:origin
	-- next not assign: = current :E: elm
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Invocation:loadOrigin:scan: = current
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = obj: ? Object -> V: ? Boolean= current
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	rpushg 2 current
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
	rtnInner
	end 1

	class #S#924 924
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L424:
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
	rpushg 1 #S#924:origin
	-- Invocation:loadOrigin:scan: := last.elm
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= last.elm
	-- ObjectGenerator:gen: super: last.elm:IS-empty: staticOff: 0
	-- Invocation:gen: last.elm
	-- Invocation:loadOrigin: last.elm
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 #S#924:origin
	rpushg 1 removeNext:origin
	-- next not assign: elm :E: last
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: elm
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 #S#924:origin
	rpushg 1 removeNext:origin
	-- Invocation:loadOrigin:scan: := last.pred
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= last.pred
	-- ObjectGenerator:gen: super: last.pred:IS-empty: staticOff: 0
	-- Invocation:gen: last.pred
	-- Invocation:loadOrigin: last.pred
	-- Invocation:loadOrigin:scan: last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 #S#924:origin
	rpushg 1 removeNext:origin
	-- next not assign: pred :E: last
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	invoke 925 0 %if%then%%else%#S#925
	rpop
 L425:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry#S#151 151
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=151
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 add:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  149
	rtnInner
	DO:
	doEventQ
	mvStack 
 L426:
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
	rpushg 2 entry#S#151:origin
	rpushg 1 add:origin
	-- Invocation:loadOrigin:scan: := M + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= M + 1
	-- ObjectGenerator:gen: super: M + 1:IS-empty: staticOff: 0
	-- Invocation:gen: M + 1
	-- Invocation:loadOrigin: M + 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 entry#S#151:origin
	rpushg 1 add:origin
	-- next not assign: + 1 :E: M
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
 L427:
	rtnInner
	end 1

	class entry#S#153 153
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=153
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 dcr:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  149
	rtnInner
	DO:
	doEventQ
	mvStack 
 L428:
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
	rpushg 2 entry#S#153:origin
	rpushg 1 dcr:origin
	-- Invocation:loadOrigin:scan: := M - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= M - 1
	-- ObjectGenerator:gen: super: M - 1:IS-empty: staticOff: 0
	-- Invocation:gen: M - 1
	-- Invocation:loadOrigin: M - 1
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 entry#S#153:origin
	rpushg 1 dcr:origin
	-- next not assign: - 1 :E: M
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- 1
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
 L429:
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
	-- on : 1
	rpushg 1 running:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  149
	rtnInner
	DO:
	doEventQ
	mvStack 
 L430:
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
	rpushg 2 entry#S#155:origin
	-- Invocation:loadOrigin:scan: := M > 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= M > 0
	-- ObjectGenerator:gen: super: M > 0:IS-empty: staticOff: 0
	-- Invocation:gen: M > 0
	-- Invocation:loadOrigin: M > 0
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 entry#S#155:origin
	rpushg 1 running:origin
	-- next not assign: > 0 :E: M
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: > 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: > V: ? integer -> B: ? Boolean> 0
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
 L431:
	rtnInner
	end 1

	class #S#932 932
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L432:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('V'):IS-empty: staticOff: 0
	-- Invocation:gen: put('V')
	-- Invocation:loadOrigin: put('V')
	-- Invocation:loadOrigin:scan: put('V')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('V')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('V')
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
 L433:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class entry#S#171 171
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=171
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 removeNext:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L434:
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
	rpushg 2 entry#S#171:origin
	-- Invocation:loadOrigin:scan: := Q.removeNext
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Q.removeNext
	-- ObjectGenerator:gen: super: Q.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: Q.removeNext
	-- Invocation:loadOrigin: Q.removeNext
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 entry#S#171:origin
	rpushg 1 removeNext:origin
	-- next not assign: removeNext :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: removeNext
	-- Unary:loadArgs: 
	-- pattern:loadArgs: removeNext -> elm: ? ObjectremoveNext
	-- Unary:invoke: 
	-- pattern:load: removeNext -> elm: ? Object
	invoke 133 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 P
 L435:
	rtnInner
	end 1

	class entry#S#174 174
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=174
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 isEmpty:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L436:
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
	rpushg 2 entry#S#174:origin
	-- Invocation:loadOrigin:scan: := Q.isEmpty
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Q.isEmpty
	-- ObjectGenerator:gen: super: Q.isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: Q.isEmpty
	-- Invocation:loadOrigin: Q.isEmpty
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 entry#S#174:origin
	rpushg 1 isEmpty:origin
	-- next not assign: isEmpty :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: isEmpty
	-- Unary:loadArgs: 
	-- pattern:loadArgs: isEmpty -> B: ? BooleanisEmpty
	-- Unary:invoke: 
	-- pattern:load: isEmpty -> B: ? Boolean
	invoke 134 0 isEmpty
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 B
 L437:
	rtnInner
	end 1

	class entry#S#179 179
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=179
	-- Invocation:loadOrigin: entry
	-- Invocation:loadOrigin:scan: entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 hasWaiting:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: entryentry
	topSuper  167
	rtnInner
	DO:
	doEventQ
	mvStack 
 L438:
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
	rpushg 2 entry#S#179:origin
	-- Invocation:loadOrigin:scan: := W > 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= W > 0
	-- ObjectGenerator:gen: super: W > 0:IS-empty: staticOff: 0
	-- Invocation:gen: W > 0
	-- Invocation:loadOrigin: W > 0
	-- Invocation:loadOrigin:scan: W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: W
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 entry#S#179:origin
	rpushg 1 hasWaiting:origin
	-- next not assign: > 0 :E: W
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: > 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: > V: ? integer -> B: ? Boolean> 0
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
 L439:
	rtnInner
	end 1

	class loopB 185
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L440:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if _kbhit %then% 
    top := top + 1
    B.%put _iget %at% top:IS-empty: staticOff: 0
	-- Invocation:gen: %if _kbhit %then% 
    top := top + 1
    B.%put _iget %at% top
	-- Invocation:loadOrigin: %if _kbhit %then% 
    top := top + 1
    B.%put _iget %at% top
	-- Invocation:loadOrigin:scan: %if _kbhit %then% 
    top := top + 1
    B.%put _iget %at% top
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if _kbhit %then% 
    top := top + 1
    B.%put _iget %at% top
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if _kbhit %then% 
    top := top + 1
    B.%put _iget %at% top
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: _kbhit:IS-empty: staticOff: 0
	-- Invocation:gen: _kbhit
	-- Invocation:loadOrigin: _kbhit
	-- Invocation:loadOrigin:scan: _kbhit
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: _kbhit
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 loopB:origin
	rpushg 1 Kscan:origin
	rpushg 1 keyboard:origin
	rpushg 1 BasicSystem:origin
	rpushg 1 BasicSystem:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: _kbhit -> B: ? Boolean_kbhit
	-- Unary:invoke: 
	-- pattern:load: _kbhit -> B: ? Boolean
	invokeExternal 5
	jmpFalse L442
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 933 0 #S#933
	rpop
 L442:
	-- ObjectGenerator:gen: super: keyboard.suspend:IS-empty: staticOff: 0
	-- Invocation:gen: keyboard.suspend
	-- Invocation:loadOrigin: keyboard.suspend
	-- Invocation:loadOrigin:scan: keyboard
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: keyboard
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 loopB:origin
	rpushg 1 Kscan:origin
	rpushg 1 keyboard:origin
	-- next not assign: suspend :E: keyboard
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: keyboard
	rpushg 8 keyboard
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- pattern:loadArgs: suspendsuspend
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: %restart loopB:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loopB
	-- Invocation:loadOrigin: %restart loopB
	-- Invocation:loadOrigin:scan: %restart loopB
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loopB
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loopB
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	jmp L440
 L441:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class waitForChar 187
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L443:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if next < top %then% 
    next := next + 1
    ch := B.%get next %else% 
    caller.suspend
    %restart waitForChar:IS-empty: staticOff: 0
	pushThis 
	invoke 188 0 %if%then%%else%#S#188
	rpop
 L444:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#936 936
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L445:
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
	rpushg 2 thenPart#S#936:origin
	rpushg 3 %if%then%%else%#S#198:origin
	rpushg 1 put:origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 1
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
 L446:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#937 937
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L447:
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
	rpushg 2 elsePart#S#937:origin
	rpushg 3 %if%then%%else%#S#198:origin
	rpushg 1 put:origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= pos + 1
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#937:origin
	rpushg 3 %if%then%%else%#S#198:origin
	rpushg 1 put:origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
 L448:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#938 938
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L449:
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
	rpushg 2 thenPart#S#938:origin
	rpushg 3 %if%then%%else%#S#200:origin
	rpushg 1 get:origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 1
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
 L450:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#939 939
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L451:
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
	rpushg 2 elsePart#S#939:origin
	rpushg 3 %if%then%%else%#S#200:origin
	rpushg 1 get:origin
	-- Invocation:loadOrigin:scan: := pos + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= pos + 1
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#939:origin
	rpushg 3 %if%then%%else%#S#200:origin
	rpushg 1 get:origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
 L452:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#940 940
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L453:
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
	rpushg 2 thenPart#S#940:origin
	rpushg 3 %if%then%%else%#S#202:origin
	-- Invocation:loadOrigin:scan: := 9999999
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 9999999
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
 L454:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#941 941
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L455:
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
	rpushg 2 elsePart#S#941:origin
	rpushg 3 %if%then%%else%#S#202:origin
	-- Invocation:loadOrigin:scan: := rep.%get pos + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= rep.%get pos + 1
	-- ObjectGenerator:gen: super: rep.%get pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos + 1
	-- Invocation:loadOrigin: rep.%get pos + 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#941:origin
	rpushg 3 %if%then%%else%#S#202:origin
	rpushg 1 nxt:origin
	-- next not assign: %get pos + 1 :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos + 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos + 1
	-- ObjectGenerator:gen: super: pos + 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos + 1
	-- Invocation:loadOrigin: pos + 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#941:origin
	rpushg 3 %if%then%%else%#S#202:origin
	rpushg 1 nxt:origin
	-- next not assign: + 1 :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L456:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#942 942
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L457:
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
	rpushg 2 thenPart#S#942:origin
	rpushg 3 %if%then%%else%#S#204:origin
	-- Invocation:loadOrigin:scan: := 9999999
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 9999999
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
 L458:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#943 943
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L459:
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
	rpushg 2 elsePart#S#943:origin
	rpushg 3 %if%then%%else%#S#204:origin
	-- Invocation:loadOrigin:scan: := rep.%get pos - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= rep.%get pos - 1
	-- ObjectGenerator:gen: super: rep.%get pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get pos - 1
	-- Invocation:loadOrigin: rep.%get pos - 1
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#943:origin
	rpushg 3 %if%then%%else%#S#204:origin
	rpushg 1 prv:origin
	-- next not assign: %get pos - 1 :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get pos - 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get pos - 1
	-- ObjectGenerator:gen: super: pos - 1:IS-empty: staticOff: 0
	-- Invocation:gen: pos - 1
	-- Invocation:loadOrigin: pos - 1
	-- Invocation:loadOrigin:scan: pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#943:origin
	rpushg 3 %if%then%%else%#S#204:origin
	rpushg 1 prv:origin
	-- next not assign: - 1 :E: pos
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: - V: ? integer -> R: ? integer- 1
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
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 res
 L460:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#944 944
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L461:
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
	break 1 336
 L462:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#945 945
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L463:
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
	rpushg 2 body#S#945:origin
	rpushg 2 %for%to%%do%#S#208:origin
	rpushg 1 print:origin
	rpushg 1 Array:origin
	rpushg 1 EMC2array:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(rep.%get inx)
	-- ObjectGenerator:gen: super: rep.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get inx
	-- Invocation:loadOrigin: rep.%get inx
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#945:origin
	rpushg 2 %for%to%%do%#S#208:origin
	rpushg 1 print:origin
	-- next not assign: %get inx :E: rep
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#945:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint(V: ? integer)
	invoke 72 0 putint
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
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L464:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 225
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: P
	-- VarRef:gen: continue
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L465:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(100)
	-- Invocation:loadOrigin: sleep(100)
	-- Invocation:loadOrigin:scan: sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(100)
	-- Function:loadArgs: 
	-- pattern:loadArgs: sleep(V: ? integer)sleep(100)
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
	-- pattern:loadArgs: := V: ? Object:= false
	-- ObjectGenerator:gen: super: false:IS-empty: staticOff: 0
	-- Invocation:gen: false
	-- Invocation:loadOrigin: false
	-- Invocation:loadOrigin:scan: false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: false
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 loop:origin
	rpushg 1 AwaitTermination:origin
	rpushg 1 ForkJoin:origin
	rpushg 1 ForkJoinSystem:origin
	rpushg 1 ForkJoinSystem:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: False -> B: ? Booleanfalse
	-- Unary:invoke: 
	-- pattern:load: False -> B: ? Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 continue
	-- ObjectGenerator:gen: super: Q.scan:singular:staticOff: 0
	pushThis 
	invoke 226 0 scan#S#226
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: continue
	pushg 1 continue
	jmpFalse L467
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 950 0 #S#950
	rpop
 L467:
	-- ObjectGenerator:gen: super: Q.clear:IS-empty: staticOff: 0
	-- Invocation:gen: Q.clear
	-- Invocation:loadOrigin: Q.clear
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 AwaitTermination:origin
	-- next not assign: clear :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: clear
	-- Unary:loadArgs: 
	-- pattern:loadArgs: clearclear
	-- Unary:invoke: 
	-- pattern:load: clear
	invoke 135 0 clear
	rpop
 L466:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#232 232
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
	rpushg 1 wait:origin
	rpushg 1 Semaphore:origin
	rpushg 9 System:origin
	rpushg 1 MonitorSystem:origin
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
	rpushg 1 wait:origin
	-- next not assign: < 0 :E: cnt
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: < 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< 0
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
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L468:
 L469:
	rtnInner
	end 1

	class %if%then%%else%#S#234 234
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
	rpushg 1 signal:origin
	rpushg 1 Semaphore:origin
	rpushg 9 System:origin
	rpushg 1 MonitorSystem:origin
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
	rpushg 1 signal:origin
	-- next not assign: <= 0 :E: cnt
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: <= 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <= V: ? integer -> B: ? Boolean<= 0
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
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L470:
 L471:
	rtnInner
	end 1

	class loop 241
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L472:
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
	rpushg 1 loop:origin
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
	rpushg 1 loop:origin
	-- next not assign: = false :E: cond
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cond
	pushg 1 cond
	-- Invocation:loadOrigin:scan: = false
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = B: ? Boolean -> R: ? Boolean= false
	-- ObjectGenerator:gen: super: false:IS-empty: staticOff: 0
	-- Invocation:gen: false
	-- Invocation:loadOrigin: false
	-- Invocation:loadOrigin:scan: false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: false
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 loop:origin
	rpushg 1 wait:origin
	rpushg 1 Monitor:origin
	rpushg 9 System:origin
	rpushg 1 MonitorSystem:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: False -> B: ? Booleanfalse
	-- Unary:invoke: 
	-- pattern:load: False -> B: ? Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: = B: ? Boolean -> R: ? Boolean
	eq
	jmpFalse L474
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 955 0 #S#955
	rpop
 L474:
 L473:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#246 246
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if (N /% 4) = 0 %then% 
    status := '?' %else% 
    
    status := '!'
    val := ch
    ch := ch + 1
	-- Invocation:loadOrigin:scan: %if (N /% 4) = 0 %then% 
    status := '?' %else% 
    
    status := '!'
    val := ch
    ch := ch + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if (N /% 4) = 0 %then% 
    status := '?' %else% 
    
    status := '!'
    val := ch
    ch := ch + 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 4
	rpushg 1 scan:origin
	rpushg 1 IO_buf:origin
	rpushg 1 NonBlockingIOSystem:origin
	rpushg 1 NonBlockingIO:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if (N /% 4) = 0 %then% 
    status := '?' %else% 
    
    status := '!'
    val := ch
    ch := ch + 1
	-- ObjectGenerator:gen: super: (N /% 4) = 0:IS-empty: staticOff: 0
	-- Invocation:gen: (N /% 4) = 0
	-- Invocation:loadOrigin: (N /% 4) = 0
	-- Invocation:loadOrigin:scan: (N /% 4)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (N /% 4)
	-- Invocation:loadOrigin: N /% 4
	-- Invocation:loadOrigin:scan: N
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: N
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 scan:origin
	-- next not assign: /% 4 :E: N
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: N
	pushg 3 N
	-- Invocation:loadOrigin:scan: /% 4
	-- BE:loadOrigin:E: /% 4
	-- next not assign: = 0 :E: /% 4
	-- Binary:loadArgs: 
	-- pattern:loadArgs: /% V: ? integer -> R: ? integer/% 4
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 0
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	-- Binary:invoke: 
	-- pattern:load: /% V: ? integer -> R: ? integer
	69
	-- Invocation:loadOrigin:scan: = 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 0
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
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L475:
 L476:
	rtnInner
	end 1

	class loop 250
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L477:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: IO_buf.scan:IS-empty: staticOff: 0
	-- Invocation:gen: IO_buf.scan
	-- Invocation:loadOrigin: IO_buf.scan
	-- Invocation:loadOrigin:scan: IO_buf
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: IO_buf
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 loop:origin
	rpushg 1 go:origin
	rpushg 1 reader:origin
	-- next not assign: scan :E: IO_buf
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: IO_buf
	rpushg 2 IO_buf
	-- Invocation:loadOrigin:scan: scan
	-- Unary:loadArgs: 
	-- pattern:loadArgs: scanscan
	-- Unary:invoke: 
	-- pattern:load: scan
	invoke 245 0 scan
	rpop
	-- ObjectGenerator:gen: super: %if IO_buf.status = '!' %then% 
    put('!')
    top := top + 1
    buf.%put IO_buf.val %at% top %else% 
    put('?'):IS-empty: staticOff: 0
	pushThis 
	invoke 251 0 %if%then%%else%#S#251
	rpop
	-- ObjectGenerator:gen: super: (%this reader).suspend:IS-empty: staticOff: 0
	-- Invocation:gen: (%this reader).suspend
	-- Invocation:loadOrigin: (%this reader).suspend
	-- Invocation:loadOrigin:scan: (%this reader)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (%this reader)
	-- Invocation:loadOrigin: %this reader
	-- Invocation:loadOrigin:scan: %this reader
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %this reader
	-- AdjustOrigin: 0
	rpushg 1 loop:origin
	rpushg 1 go:origin
	-- BE:loadOrigin:E: %this reader
	-- next not assign: suspend :E: %this reader
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %this P: ? Object%this reader
	-- KeyWord:invoke: 
	-- pattern:load: %this P: ? Object
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- pattern:loadArgs: suspendsuspend
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
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
	jmp L477
 L478:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#961 961
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L479:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "SocketSystem: INVALID_SOCKET\n".print:IS-empty: staticOff: 0
	-- Invocation:gen: "SocketSystem: INVALID_SOCKET\n".print
	-- Invocation:loadOrigin: "SocketSystem: INVALID_SOCKET\n".print
	-- Invocation:loadOrigin:scan: "SocketSystem: INVALID_SOCKET\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText SocketSystem: INVALID_SOCKET\n
	-- next not assign: print :E: "SocketSystem: INVALID_SOCKET\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 95 0 print
	rpop
 L480:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class awaitAccept 291
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L481:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: S := do_accept(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: S := do_accept(sockfd)
	-- Invocation:loadOrigin: S := do_accept(sockfd)
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 awaitAccept:origin
	-- Invocation:loadOrigin:scan: := do_accept(sockfd)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_accept(sockfd)
	-- ObjectGenerator:gen: super: do_accept(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: do_accept(sockfd)
	-- Invocation:loadOrigin: do_accept(sockfd)
	-- Invocation:loadOrigin:scan: do_accept(sockfd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_accept(sockfd)
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 awaitAccept:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_accept(S: ? integer) -> V: ? integerdo_accept(sockfd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 awaitAccept:origin
	rpushg 1 accept:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Function:invoke: 
	-- pattern:load: do_accept(S: ? integer) -> V: ? integer
	invokeExternal 13
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 S
	-- ObjectGenerator:gen: super: %if S = 1 %then% 
    put('.')
    theCaller.suspend
    %restart awaitAccept:IS-empty: staticOff: 0
	-- Invocation:gen: %if S = 1 %then% 
    put('.')
    theCaller.suspend
    %restart awaitAccept
	-- Invocation:loadOrigin: %if S = 1 %then% 
    put('.')
    theCaller.suspend
    %restart awaitAccept
	-- Invocation:loadOrigin:scan: %if S = 1 %then% 
    put('.')
    theCaller.suspend
    %restart awaitAccept
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if S = 1 %then% 
    put('.')
    theCaller.suspend
    %restart awaitAccept
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if S = 1 %then% 
    put('.')
    theCaller.suspend
    %restart awaitAccept
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: S = 1:IS-empty: staticOff: 0
	-- Invocation:gen: S = 1
	-- Invocation:loadOrigin: S = 1
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 awaitAccept:origin
	-- next not assign: = 1 :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	pushg 1 S
	-- Invocation:loadOrigin:scan: = 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 1
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
	jmpFalse L483
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 962 0 #S#962
	rpop
 L483:
 L482:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 296
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L484:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: msg := do_rec(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: msg := do_rec(sockfd)
	-- Invocation:loadOrigin: msg := do_rec(sockfd)
	-- Invocation:loadOrigin:scan: msg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: msg
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := do_rec(sockfd)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= do_rec(sockfd)
	-- ObjectGenerator:gen: super: do_rec(sockfd):IS-empty: staticOff: 0
	-- Invocation:gen: do_rec(sockfd)
	-- Invocation:loadOrigin: do_rec(sockfd)
	-- Invocation:loadOrigin:scan: do_rec(sockfd)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: do_rec(sockfd)
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: do_rec(S: ? integer) -> msg: ? String.Stringdo_rec(sockfd)
	-- ObjectGenerator:gen: super: sockfd:IS-empty: staticOff: 0
	-- Invocation:gen: sockfd
	-- Invocation:loadOrigin: sockfd
	-- Invocation:loadOrigin:scan: sockfd
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sockfd
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 receive:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: sockfd
	pushg 1 sockfd
	-- Function:invoke: 
	-- pattern:load: do_rec(S: ? integer) -> msg: ? String.String
	invokeExternal 9
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 msg
	-- ObjectGenerator:gen: super: %if none = msg %then% 
    put(',')
    caller.suspend
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if none = msg %then% 
    put(',')
    caller.suspend
    %restart loop
	-- Invocation:loadOrigin: %if none = msg %then% 
    put(',')
    caller.suspend
    %restart loop
	-- Invocation:loadOrigin:scan: %if none = msg %then% 
    put(',')
    caller.suspend
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if none = msg %then% 
    put(',')
    caller.suspend
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if none = msg %then% 
    put(',')
    caller.suspend
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: none = msg:IS-empty: staticOff: 0
	-- Invocation:gen: none = msg
	-- Invocation:loadOrigin: none = msg
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- next not assign: = msg :E: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Invocation:loadOrigin:scan: = msg
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = obj: ? Object -> V: ? Boolean= msg
	-- ObjectGenerator:gen: super: msg:IS-empty: staticOff: 0
	-- Invocation:gen: msg
	-- Invocation:loadOrigin: msg
	-- Invocation:loadOrigin:scan: msg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: msg
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: msg
	rpushg 3 msg
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	jmpFalse L486
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 963 0 #S#963
	rpop
 L486:
 L485:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#90 90
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
	rpushg 1 doplus:origin
	rpushg 1 +:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
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
	rpushg 1 doplus:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	topSuper  67
	rtnInner
	DO:
	mvStack 
 L487:
 L488:
	rtnInner
	end 1

	class %for%to%%do%#S#91 91
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
	rpushg 1 doplus:origin
	rpushg 1 +:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
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
	rpushg 1 doplus:origin
	-- next not assign: length :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
	topSuper  67
	rtnInner
	DO:
	mvStack 
 L489:
 L490:
	rtnInner
	end 1

	class body#SB#907 907
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L491:
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
	rpushg 2 body#S#907:origin
	rpushg 2 %for%to%%do%#S#94:origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= %get inx
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#907:origin
	rpushg 2 %for%to%%do%#S#94:origin
	rpushg 1 scan:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#907:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
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
	rpushg 2 body#S#907:origin
	rpushg 2 %for%to%%do%#S#94:origin
	inner  1
	rpopThisObj 
 L492:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#908 908
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L493:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(%get inx):IS-empty: staticOff: 0
	-- Invocation:gen: put(%get inx)
	-- Invocation:loadOrigin: put(%get inx)
	-- Invocation:loadOrigin:scan: put(%get inx)
	-- Function:pushThis: 
	-- Function:loadOrigin: put(%get inx)
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(%get inx)
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#908:origin
	rpushg 2 %for%to%%do%#S#96:origin
	rpushg 1 print:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#908:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L494:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#909 909
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L495:
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
	break 1 397
 L496:
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
	rpushg 1 loop:origin
	rpushg 1 =:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
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
	rpushg 1 loop:origin
	rpushg 1 =:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 86 0 length
	topSuper  67
	rtnInner
	DO:
	mvStack 
 L497:
 L498:
	rtnInner
	end 1

	class matchEq 102
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: inx
	-- VarRef:gen: c1
	-- VarRef:gen: c2
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 103 2 loop
	rpop
	-- ConsRef:gen: doit
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 104 3 doit
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L499:
	-- Include:gen: 
 L500:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#106 106
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
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Invocation:loadOrigin:scan: < L2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< L2
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
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L501:
 L502:
	rtnInner
	end 1

	class := 533
	pushThis 
	rstoreg 2 p
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L503:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: x := p.x:IS-empty: staticOff: 0
	-- Invocation:gen: x := p.x
	-- Invocation:loadOrigin: x := p.x
	-- Invocation:loadOrigin:scan: x
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: x
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 :=:origin
	-- Invocation:loadOrigin:scan: := p.x
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= p.x
	-- ObjectGenerator:gen: super: p.x:IS-empty: staticOff: 0
	-- Invocation:gen: p.x
	-- Invocation:loadOrigin: p.x
	-- Invocation:loadOrigin:scan: p
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: x :E: p
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p
	rpushg 2 p
	-- Invocation:loadOrigin:scan: x
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: x
	pushg 1 x
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 x
	-- ObjectGenerator:gen: super: y := p.y:IS-empty: staticOff: 0
	-- Invocation:gen: y := p.y
	-- Invocation:loadOrigin: y := p.y
	-- Invocation:loadOrigin:scan: y
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: y
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 :=:origin
	-- Invocation:loadOrigin:scan: := p.y
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= p.y
	-- ObjectGenerator:gen: super: p.y:IS-empty: staticOff: 0
	-- Invocation:gen: p.y
	-- Invocation:loadOrigin: p.y
	-- Invocation:loadOrigin:scan: p
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: p
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: y :E: p
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: p
	rpushg 2 p
	-- Invocation:loadOrigin:scan: y
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: y
	pushg 2 y
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 y
 L504:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class getx 534
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L505:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := x:IS-empty: staticOff: 0
	-- Invocation:gen: r := x
	-- Invocation:loadOrigin: r := x
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: := x
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= x
	-- ObjectGenerator:gen: super: x:IS-empty: staticOff: 0
	-- Invocation:gen: x
	-- Invocation:loadOrigin: x
	-- Invocation:loadOrigin:scan: x
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: x
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 getx:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: x
	pushg 1 x
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 r
 L506:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: r
	pushg 1 r
	rtn(D)
	end 1

	class #S#926 926
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L507:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: enable:IS-empty: staticOff: 0
	-- Invocation:gen: enable
	-- Invocation:loadOrigin: enable
	-- Invocation:loadOrigin:scan: enable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: enable
	-- Unary:loadArgs: 
	-- pattern:loadArgs: enableenable
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
	-- pattern:loadArgs: sleep(V: ? integer)sleep(50)
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
	break 1 407
 L508:
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
 L509:
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
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: status :E: active
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: status
	-- Invocation:loadOrigin:scan: := P_status.ACTIVE
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= P_status.ACTIVE
	-- ObjectGenerator:gen: super: P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.ACTIVE
	-- Invocation:loadOrigin: P_status.ACTIVE
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: ACTIVE :E: P_status
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
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
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 0
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
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: attach(50) :E: active
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: attach(50)
	-- Function:loadArgs: 
	-- pattern:loadArgs: attach(V: ? integer)attach(50)
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
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 1
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
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: status :E: active
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: status
	-- next not assign: = P_status.ACTIVE :E: status
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: status
	pushg 1 status
	-- Invocation:loadOrigin:scan: = P_status.ACTIVE
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= P_status.ACTIVE
	-- ObjectGenerator:gen: super: P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.ACTIVE
	-- Invocation:loadOrigin: P_status.ACTIVE
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: ACTIVE :E: P_status
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L511
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 1153 0 #S#1153
	rpop
 L511:
 L510:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#147 147
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	rpushg 1 BasicSystem:origin
	rpushg 1 BasicSystem:origin
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: isEmpty :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: isEmpty
	-- Unary:loadArgs: 
	-- pattern:loadArgs: isEmpty -> B: ? BooleanisEmpty
	-- Unary:invoke: 
	-- pattern:load: isEmpty -> B: ? Boolean
	invoke 173 0 isEmpty
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L512:
 L513:
	rtnInner
	end 1

	class %if%then%%else%#S#160 160
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
	rpushg 1 loopX:origin
	rpushg 1 do:origin
	rpushg 1 Core:origin
	rpushg 1 BasicSystem:origin
	rpushg 1 BasicSystem:origin
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
	rpushg 1 loopX:origin
	rpushg 1 do:origin
	-- next not assign: <> none :E: main
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L514:
 L515:
	rtnInner
	end 1

	class loop 126
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L516:
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: <> none :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L518
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 918 0 #S#918
	rpop
 L518:
 L517:
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
 L519:
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
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: <> none :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	jmpFalse L521
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 919 0 #S#919
	rpop
 L521:
 L520:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#921 921
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
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	rpushg 1 Queue:origin
	rpushg 1 mQueue:origin
	rpushg 1 Containers:origin
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
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- next not assign: = none :E: head
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: = none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = obj: ? Object -> V: ? Boolean= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = obj: ? Object -> V: ? Boolean
	req
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L522:
 L523:
	rtnInner
	end 1

	class #S#922 922
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L524:
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
	invoke 923 0 %if%then%%else%#S#923
	rpop
 L525:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#925 925
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
	rpushg 1 #S#924:origin
	rpushg 1 removeNext:origin
	rpushg 1 Queue:origin
	rpushg 1 mQueue:origin
	rpushg 1 Containers:origin
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
	rpushg 1 #S#924:origin
	rpushg 1 removeNext:origin
	-- next not assign: <> none :E: last
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L526:
 L527:
	rtnInner
	end 1

	class #S#933 933
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L528:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: top := top + 1:IS-empty: staticOff: 0
	-- Invocation:gen: top := top + 1
	-- Invocation:loadOrigin: top := top + 1
	-- Invocation:loadOrigin:scan: top
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: top
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#933:origin
	rpushg 1 loopB:origin
	rpushg 1 Kscan:origin
	-- Invocation:loadOrigin:scan: := top + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= top + 1
	-- ObjectGenerator:gen: super: top + 1:IS-empty: staticOff: 0
	-- Invocation:gen: top + 1
	-- Invocation:loadOrigin: top + 1
	-- Invocation:loadOrigin:scan: top
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: top
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#933:origin
	rpushg 1 loopB:origin
	rpushg 1 Kscan:origin
	-- next not assign: + 1 :E: top
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: top
	pushg 3 top
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	storeg 3 top
	-- ObjectGenerator:gen: super: B.%put _iget %at% top:IS-empty: staticOff: 0
	-- Invocation:gen: B.%put _iget %at% top
	-- Invocation:loadOrigin: B.%put _iget %at% top
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#933:origin
	rpushg 1 loopB:origin
	rpushg 1 Kscan:origin
	-- next not assign: %put _iget %at% top :E: B
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: B
	rpushg 3 B
	-- Invocation:loadOrigin:scan: %put _iget %at% top
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put _iget %at% top
	-- ObjectGenerator:gen: super: _iget:IS-empty: staticOff: 0
	-- Invocation:gen: _iget
	-- Invocation:loadOrigin: _iget
	-- Invocation:loadOrigin:scan: _iget
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: _iget
	-- AdjustOrigin: 0
	-- on : 6
	rpushg 1 #S#933:origin
	rpushg 1 loopB:origin
	rpushg 1 Kscan:origin
	rpushg 1 keyboard:origin
	rpushg 1 BasicSystem:origin
	rpushg 1 BasicSystem:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: _iget -> ch: ? char_iget
	-- Unary:invoke: 
	-- pattern:load: _iget -> ch: ? char
	invokeExternal 4
	-- ObjectGenerator:gen: super: top:IS-empty: staticOff: 0
	-- Invocation:gen: top
	-- Invocation:loadOrigin: top
	-- Invocation:loadOrigin:scan: top
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: top
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#933:origin
	rpushg 1 loopB:origin
	rpushg 1 Kscan:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: top
	pushg 3 top
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	xstoreg 1 inx
 L529:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#188 188
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if next < top %then% 
    next := next + 1
    ch := B.%get next %else% 
    caller.suspend
    %restart waitForChar
	-- Invocation:loadOrigin:scan: %if next < top %then% 
    next := next + 1
    ch := B.%get next %else% 
    caller.suspend
    %restart waitForChar
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if next < top %then% 
    next := next + 1
    ch := B.%get next %else% 
    caller.suspend
    %restart waitForChar
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 waitForChar:origin
	rpushg 1 get:origin
	rpushg 1 keyboard:origin
	rpushg 1 BasicSystem:origin
	rpushg 1 BasicSystem:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if next < top %then% 
    next := next + 1
    ch := B.%get next %else% 
    caller.suspend
    %restart waitForChar
	-- ObjectGenerator:gen: super: next < top:IS-empty: staticOff: 0
	-- Invocation:gen: next < top
	-- Invocation:loadOrigin: next < top
	-- Invocation:loadOrigin:scan: next
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: next
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 waitForChar:origin
	rpushg 1 get:origin
	-- next not assign: < top :E: next
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: next
	pushg 2 next
	-- Invocation:loadOrigin:scan: < top
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< top
	-- ObjectGenerator:gen: super: top:IS-empty: staticOff: 0
	-- Invocation:gen: top
	-- Invocation:loadOrigin: top
	-- Invocation:loadOrigin:scan: top
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: top
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 waitForChar:origin
	rpushg 1 get:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: top
	pushg 3 top
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L530:
 L531:
	rtnInner
	end 1

	class scan#S#226 226
	rstore 4 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=226
	-- Invocation:loadOrigin: Q.scan
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 4
	rpushg 4 origin
	-- on : 2
	rpushg 1 loop:origin
	rpushg 1 AwaitTermination:origin
	-- next not assign: scan :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: scan
	-- Unary:loadArgs: 
	-- pattern:loadArgs: scanscan
	topSuper  124
	rtnInner
	DO:
	doEventQ
	mvStack 
 L532:
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
	rpushg 4 scan#S#226:origin
	-- Invocation:loadOrigin:scan: := current
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= current
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
	-- VarRef:loadArgs: 
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
	rpushg 4 scan#S#226:origin
	-- next not assign: status :E: P
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Invocation:loadOrigin:scan: status
	-- next not assign: <> P_status.TERMINATED :E: status
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: status
	pushg 1 status
	-- Invocation:loadOrigin:scan: <> P_status.TERMINATED
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> V: ? integer -> B: ? Boolean<> P_status.TERMINATED
	-- ObjectGenerator:gen: super: P_status.TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.TERMINATED
	-- Invocation:loadOrigin: P_status.TERMINATED
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 4 scan#S#226:origin
	rpushg 1 loop:origin
	rpushg 1 AwaitTermination:origin
	rpushg 1 ForkJoin:origin
	-- next not assign: TERMINATED :E: P_status
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: TERMINATED
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: TERMINATED
	pushg 3 TERMINATED
	-- Binary:invoke: 
	-- pattern:load: <> V: ? integer -> B: ? Boolean
	55
	jmpFalse L534
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 949 0 #S#949
	rpop
 L534:
 L533:
	rtnInner
	end 1

	class #S#950 950
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L535:
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
	break 1 465
 L536:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#951 951
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L537:
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
	-- pattern:loadArgs: thisCore -> C: ? corethisCore
	-- Unary:invoke: 
	-- pattern:load: thisCore -> C: ? core
	-- Invocation:loadOrigin:scan: main
	-- next not assign: active :E: main
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: active
	-- next not assign: status :E: active
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: status
	-- Invocation:loadOrigin:scan: := P_status.WAITING
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= P_status.WAITING
	-- ObjectGenerator:gen: super: P_status.WAITING:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.WAITING
	-- Invocation:loadOrigin: P_status.WAITING
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#951:origin
	rpushg 3 %if%then%%else%#S#232:origin
	rpushg 1 wait:origin
	rpushg 1 Semaphore:origin
	-- next not assign: WAITING :E: P_status
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: WAITING
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
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
	rpushg 2 thenPart#S#951:origin
	rpushg 3 %if%then%%else%#S#232:origin
	rpushg 1 wait:origin
	rpushg 1 Semaphore:origin
	-- next not assign: addWaiting :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: addWaiting
	-- Unary:loadArgs: 
	-- pattern:loadArgs: addWaitingaddWaiting
	-- Unary:invoke: 
	-- pattern:load: addWaiting
	invoke 176 0 addWaiting
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
	rpushg 2 thenPart#S#951:origin
	rpushg 3 %if%then%%else%#S#232:origin
	rpushg 1 wait:origin
	-- next not assign: insert(thisCore.main.active) :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 3 Q
	-- Invocation:loadOrigin:scan: insert(thisCore.main.active)
	-- Function:loadArgs: 
	-- pattern:loadArgs: insert(elm: ? Object)insert(thisCore.main.active)
	-- ObjectGenerator:gen: super: thisCore.main.active:IS-empty: staticOff: 0
	-- Invocation:gen: thisCore.main.active
	-- Invocation:loadOrigin: thisCore.main.active
	-- Invocation:loadOrigin:scan: thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: thisCore
	%thisCore 17
	-- next not assign: main :E: thisCore
	-- Unary:loadArgs: 
	-- pattern:loadArgs: thisCore -> C: ? corethisCore
	-- Unary:invoke: 
	-- pattern:load: thisCore -> C: ? core
	-- Invocation:loadOrigin:scan: main
	-- next not assign: active :E: main
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: active
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Function:invoke: 
	-- pattern:load: insert(elm: ? Object)
	invoke 130 0 insert
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
	rpushg 2 thenPart#S#951:origin
	rpushg 3 %if%then%%else%#S#232:origin
	-- Invocation:loadOrigin:scan: := thisCore.main.active
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= thisCore.main.active
	-- ObjectGenerator:gen: super: thisCore.main.active:IS-empty: staticOff: 0
	-- Invocation:gen: thisCore.main.active
	-- Invocation:loadOrigin: thisCore.main.active
	-- Invocation:loadOrigin:scan: thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: thisCore
	%thisCore 17
	-- next not assign: main :E: thisCore
	-- Unary:loadArgs: 
	-- pattern:loadArgs: thisCore -> C: ? corethisCore
	-- Unary:invoke: 
	-- pattern:load: thisCore -> C: ? core
	-- Invocation:loadOrigin:scan: main
	-- next not assign: active :E: main
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: active
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 2 thenPart#S#951:origin
	rpushg 3 %if%then%%else%#S#232:origin
	rpushg 1 wait:origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
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
	rpushg 2 thenPart#S#951:origin
	rpushg 3 %if%then%%else%#S#232:origin
	-- next not assign: suspend :E: theActive
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: theActive
	rpushg 2 theActive
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- pattern:loadArgs: suspendsuspend
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
 L538:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#952 952
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L539:
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
	rpushg 2 elsePart#S#952:origin
	rpushg 3 %if%then%%else%#S#232:origin
	rpushg 1 wait:origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L540:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#953 953
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L541:
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
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	-- Invocation:loadOrigin:scan: := Q.removeNext
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= Q.removeNext
	-- ObjectGenerator:gen: super: Q.removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: Q.removeNext
	-- Invocation:loadOrigin: Q.removeNext
	-- Invocation:loadOrigin:scan: Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: Q
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	rpushg 1 signal:origin
	-- next not assign: removeNext :E: Q
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 3 Q
	-- Invocation:loadOrigin:scan: removeNext
	-- Unary:loadArgs: 
	-- pattern:loadArgs: removeNext -> elm: ? ObjectremoveNext
	-- Unary:invoke: 
	-- pattern:load: removeNext -> elm: ? Object
	invoke 133 0 removeNext
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
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	-- next not assign: status :E: P
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Invocation:loadOrigin:scan: status
	-- Invocation:loadOrigin:scan: := P_status.ACTIVE
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= P_status.ACTIVE
	-- ObjectGenerator:gen: super: P_status.ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: P_status.ACTIVE
	-- Invocation:loadOrigin: P_status.ACTIVE
	-- Invocation:loadOrigin:scan: P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	rpushg 1 signal:origin
	rpushg 1 Semaphore:origin
	-- next not assign: ACTIVE :E: P_status
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: ACTIVE
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
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
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	rpushg 1 signal:origin
	rpushg 1 Semaphore:origin
	-- next not assign: insert(P) :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(P)
	-- Function:loadArgs: 
	-- pattern:loadArgs: insert(P: ? BasicProcess)insert(P)
	-- ObjectGenerator:gen: super: P:IS-empty: staticOff: 0
	-- Invocation:gen: P
	-- Invocation:loadOrigin: P
	-- Invocation:loadOrigin:scan: P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: P
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 169 0 insert
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
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	rpushg 1 signal:origin
	rpushg 1 Semaphore:origin
	-- next not assign: dcrWaiting :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: dcrWaiting
	-- Unary:loadArgs: 
	-- pattern:loadArgs: dcrWaitingdcrWaiting
	-- Unary:invoke: 
	-- pattern:load: dcrWaiting
	invoke 177 0 dcrWaiting
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
	rpushg 2 thenPart#S#953:origin
	rpushg 3 %if%then%%else%#S#234:origin
	rpushg 1 signal:origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L542:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#954 954
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L543:
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
	rpushg 2 elsePart#S#954:origin
	rpushg 3 %if%then%%else%#S#234:origin
	rpushg 1 signal:origin
	-- next not assign: free :E: M
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 141 0 free
	rpop
 L544:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#955 955
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L545:
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
	rpushg 1 #S#955:origin
	rpushg 1 loop:origin
	rpushg 1 wait:origin
	-- next not assign: signal :E: mutex
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: signal
	-- Unary:loadArgs: 
	-- pattern:loadArgs: signalsignal
	-- Unary:invoke: 
	-- pattern:load: signal
	invoke 233 0 signal
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
	rpushg 1 #S#955:origin
	rpushg 1 loop:origin
	rpushg 1 wait:origin
	-- next not assign: wait :E: mutex
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: wait
	-- Unary:loadArgs: 
	-- pattern:loadArgs: waitwait
	-- Unary:invoke: 
	-- pattern:load: wait
	invoke 231 0 wait
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
	break 1 472
 L546:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#956 956
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L547:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: status := '?':IS-empty: staticOff: 0
	-- Invocation:gen: status := '?'
	-- Invocation:loadOrigin: status := '?'
	-- Invocation:loadOrigin:scan: status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: status
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 thenPart#S#956:origin
	rpushg 3 %if%then%%else%#S#246:origin
	rpushg 1 scan:origin
	-- Invocation:loadOrigin:scan: := '?'
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= '?'
	-- ObjectGenerator:gen: super: '?':IS-empty: staticOff: 0
	-- Invocation:gen: '?'
	-- Invocation:loadOrigin: '?'
	-- Invocation:loadOrigin:scan: '?'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 63
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
 L548:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#957 957
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L549:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: status := '!':IS-empty: staticOff: 0
	-- Invocation:gen: status := '!'
	-- Invocation:loadOrigin: status := '!'
	-- Invocation:loadOrigin:scan: status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: status
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#957:origin
	rpushg 3 %if%then%%else%#S#246:origin
	rpushg 1 scan:origin
	-- Invocation:loadOrigin:scan: := '!'
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= '!'
	-- ObjectGenerator:gen: super: '!':IS-empty: staticOff: 0
	-- Invocation:gen: '!'
	-- Invocation:loadOrigin: '!'
	-- Invocation:loadOrigin:scan: '!'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 33
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 status
	-- ObjectGenerator:gen: super: val := ch:IS-empty: staticOff: 0
	-- Invocation:gen: val := ch
	-- Invocation:loadOrigin: val := ch
	-- Invocation:loadOrigin:scan: val
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: val
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#957:origin
	rpushg 3 %if%then%%else%#S#246:origin
	rpushg 1 scan:origin
	-- Invocation:loadOrigin:scan: := ch
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= ch
	-- ObjectGenerator:gen: super: ch:IS-empty: staticOff: 0
	-- Invocation:gen: ch
	-- Invocation:loadOrigin: ch
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#957:origin
	rpushg 3 %if%then%%else%#S#246:origin
	rpushg 1 scan:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ch
	pushg 4 ch
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 2 val
	-- ObjectGenerator:gen: super: ch := ch + 1:IS-empty: staticOff: 0
	-- Invocation:gen: ch := ch + 1
	-- Invocation:loadOrigin: ch := ch + 1
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#957:origin
	rpushg 3 %if%then%%else%#S#246:origin
	rpushg 1 scan:origin
	-- Invocation:loadOrigin:scan: := ch + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= ch + 1
	-- ObjectGenerator:gen: super: ch + 1:IS-empty: staticOff: 0
	-- Invocation:gen: ch + 1
	-- Invocation:loadOrigin: ch + 1
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#957:origin
	rpushg 3 %if%then%%else%#S#246:origin
	rpushg 1 scan:origin
	-- next not assign: + 1 :E: ch
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: ch
	pushg 4 ch
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? char -> R: ? char+ 1
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
	-- pattern:load: + V: ? char -> R: ? char
	plus
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 4 ch
 L550:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#251 251
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: %if IO_buf.status = '!' %then% 
    put('!')
    top := top + 1
    buf.%put IO_buf.val %at% top %else% 
    put('?')
	-- Invocation:loadOrigin:scan: %if IO_buf.status = '!' %then% 
    put('!')
    top := top + 1
    buf.%put IO_buf.val %at% top %else% 
    put('?')
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if IO_buf.status = '!' %then% 
    put('!')
    top := top + 1
    buf.%put IO_buf.val %at% top %else% 
    put('?')
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 loop:origin
	rpushg 1 go:origin
	rpushg 1 reader:origin
	rpushg 1 NonBlockingIOSystem:origin
	rpushg 1 NonBlockingIO:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if IO_buf.status = '!' %then% 
    put('!')
    top := top + 1
    buf.%put IO_buf.val %at% top %else% 
    put('?')
	-- ObjectGenerator:gen: super: IO_buf.status = '!':IS-empty: staticOff: 0
	-- Invocation:gen: IO_buf.status = '!'
	-- Invocation:loadOrigin: IO_buf.status = '!'
	-- Invocation:loadOrigin:scan: IO_buf
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: IO_buf
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 loop:origin
	rpushg 1 go:origin
	rpushg 1 reader:origin
	-- next not assign: status :E: IO_buf
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: IO_buf
	rpushg 2 IO_buf
	-- Invocation:loadOrigin:scan: status
	-- next not assign: = '!' :E: status
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: status
	pushg 1 status
	-- Invocation:loadOrigin:scan: = '!'
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? char -> B: ? Boolean= '!'
	-- ObjectGenerator:gen: super: '!':IS-empty: staticOff: 0
	-- Invocation:gen: '!'
	-- Invocation:loadOrigin: '!'
	-- Invocation:loadOrigin:scan: '!'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 33
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L551:
 L552:
	rtnInner
	end 1

	class #S#962 962
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L553:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('.'):IS-empty: staticOff: 0
	-- Invocation:gen: put('.')
	-- Invocation:loadOrigin: put('.')
	-- Invocation:loadOrigin:scan: put('.')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('.')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('.')
	-- ObjectGenerator:gen: super: '.':IS-empty: staticOff: 0
	-- Invocation:gen: '.'
	-- Invocation:loadOrigin: '.'
	-- Invocation:loadOrigin:scan: '.'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 46
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: theCaller.suspend:IS-empty: staticOff: 0
	-- Invocation:gen: theCaller.suspend
	-- Invocation:loadOrigin: theCaller.suspend
	-- Invocation:loadOrigin:scan: theCaller
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: theCaller
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 #S#962:origin
	rpushg 1 awaitAccept:origin
	-- next not assign: suspend :E: theCaller
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: theCaller
	rpushg 2 theCaller
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- pattern:loadArgs: suspendsuspend
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: %restart awaitAccept:IS-empty: staticOff: 0
	-- Invocation:gen: %restart awaitAccept
	-- Invocation:loadOrigin: %restart awaitAccept
	-- Invocation:loadOrigin:scan: %restart awaitAccept
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart awaitAccept
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart awaitAccept
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 1 481
 L554:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#963 963
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L555:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put(','):IS-empty: staticOff: 0
	-- Invocation:gen: put(',')
	-- Invocation:loadOrigin: put(',')
	-- Invocation:loadOrigin:scan: put(',')
	-- Function:pushThis: 
	-- Function:loadOrigin: put(',')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(',')
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
	-- ObjectGenerator:gen: super: caller.suspend:IS-empty: staticOff: 0
	-- Invocation:gen: caller.suspend
	-- Invocation:loadOrigin: caller.suspend
	-- Invocation:loadOrigin:scan: caller
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: caller
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 #S#963:origin
	rpushg 1 loop:origin
	-- next not assign: suspend :E: caller
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: caller
	rpushg 2 caller
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- pattern:loadArgs: suspendsuspend
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
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
	break 1 484
 L556:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#905 905
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L557:
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
	rpushg 2 body#S#905:origin
	rpushg 2 %for%to%%do%#S#90:origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= %get inx
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 body#S#905:origin
	rpushg 2 %for%to%%do%#S#90:origin
	rpushg 1 doplus:origin
	rpushg 1 +:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#905:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
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
	rpushg 2 body#S#905:origin
	rpushg 2 %for%to%%do%#S#90:origin
	-- next not assign: %put e %at% inx :E: T
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: %put e %at% inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put e %at% inx
	-- ObjectGenerator:gen: super: e:IS-empty: staticOff: 0
	-- Invocation:gen: e
	-- Invocation:loadOrigin: e
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 body#S#905:origin
	rpushg 2 %for%to%%do%#S#90:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#905:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	xstoreg 1 inx
 L558:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#906 906
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L559:
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
	rpushg 2 body#S#906:origin
	rpushg 2 %for%to%%do%#S#91:origin
	-- Invocation:loadOrigin:scan: := S.%get inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= S.%get inx
	-- ObjectGenerator:gen: super: S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: S.%get inx
	-- Invocation:loadOrigin: S.%get inx
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#906:origin
	rpushg 2 %for%to%%do%#S#91:origin
	rpushg 1 doplus:origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#906:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
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
	rpushg 2 body#S#906:origin
	rpushg 2 %for%to%%do%#S#91:origin
	-- Invocation:loadOrigin:scan: := L + inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= L + inx
	-- ObjectGenerator:gen: super: L + inx:IS-empty: staticOff: 0
	-- Invocation:gen: L + inx
	-- Invocation:loadOrigin: L + inx
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#906:origin
	rpushg 2 %for%to%%do%#S#91:origin
	rpushg 1 doplus:origin
	-- next not assign: + inx :E: L
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Invocation:loadOrigin:scan: + inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#906:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 2 body#S#906:origin
	rpushg 2 %for%to%%do%#S#91:origin
	-- next not assign: %put e %at% i :E: T
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: %put e %at% i
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put e %at% i
	-- ObjectGenerator:gen: super: e:IS-empty: staticOff: 0
	-- Invocation:gen: e
	-- Invocation:loadOrigin: e
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 body#S#906:origin
	rpushg 2 %for%to%%do%#S#91:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- ObjectGenerator:gen: super: i:IS-empty: staticOff: 0
	-- Invocation:gen: i
	-- Invocation:loadOrigin: i
	-- Invocation:loadOrigin:scan: i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: i
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 body#S#906:origin
	rpushg 2 %for%to%%do%#S#91:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 2 i
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	xstoreg 1 inx
 L560:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#910 910
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L561:
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
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= %get inx
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	rpushg 1 loop:origin
	rpushg 1 =:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#910:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
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
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	-- Invocation:loadOrigin:scan: := S.%get inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= S.%get inx
	-- ObjectGenerator:gen: super: S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: S.%get inx
	-- Invocation:loadOrigin: S.%get inx
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	rpushg 1 loop:origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 body#S#910:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
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
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	-- next not assign: <> c2 :E: c1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 1 c1
	-- Invocation:loadOrigin:scan: <> c2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> V: ? char -> B: ? Boolean<> c2
	-- ObjectGenerator:gen: super: c2:IS-empty: staticOff: 0
	-- Invocation:gen: c2
	-- Invocation:loadOrigin: c2
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 2 c2
	-- Binary:invoke: 
	-- pattern:load: <> V: ? char -> B: ? Boolean
	55
	jmpFalse L563
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 1144 0 #S#1144
	rpop
 L563:
 L562:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 103
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L564:
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := inx + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= inx + 1
	-- ObjectGenerator:gen: super: inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx + 1
	-- Invocation:loadOrigin: inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- next not assign: + 1 :E: inx
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := %get inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= %get inx
	-- ObjectGenerator:gen: super: %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: %get inx
	-- Invocation:loadOrigin: %get inx
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %get inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 loop:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
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
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := S.%get inx
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= S.%get inx
	-- ObjectGenerator:gen: super: S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: S.%get inx
	-- Invocation:loadOrigin: S.%get inx
	-- Invocation:loadOrigin:scan: S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 loop:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: %get inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> ch: ? Char%get inx
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> ch: ? Char
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
	rpushg 1 loop:origin
	-- next not assign: = c2 :E: c1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: = c2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? char -> B: ? Boolean= c2
	-- ObjectGenerator:gen: super: c2:IS-empty: staticOff: 0
	-- Invocation:gen: c2
	-- Invocation:loadOrigin: c2
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 loop:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	jmpFalse L566
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 911 0 #S#911
	rpop
 L566:
 L565:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 104
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L567:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq:IS-empty: staticOff: 0
	pushThis 
	invoke 105 0 %if%then%%else%#S#105
	rpop
 L568:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#914 914
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L569:
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
	rpushg 2 thenPart#S#914:origin
	rpushg 3 %if%then%%else%#S#106:origin
	-- Invocation:loadOrigin:scan: := L1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= L1
	-- ObjectGenerator:gen: super: L1:IS-empty: staticOff: 0
	-- Invocation:gen: L1
	-- Invocation:loadOrigin: L1
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 thenPart#S#914:origin
	rpushg 3 %if%then%%else%#S#106:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
 L570:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#915 915
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L571:
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
	rpushg 2 elsePart#S#915:origin
	rpushg 3 %if%then%%else%#S#106:origin
	-- Invocation:loadOrigin:scan: := L2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= L2
	-- ObjectGenerator:gen: super: L2:IS-empty: staticOff: 0
	-- Invocation:gen: L2
	-- Invocation:loadOrigin: L2
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 elsePart#S#915:origin
	rpushg 3 %if%then%%else%#S#106:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
 L572:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#1153 1153
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L573:
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
	rpushg 1 #S#1153:origin
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: insert(active) :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: insert(active)
	-- Function:loadArgs: 
	-- pattern:loadArgs: insert(P: ? BasicProcess)insert(active)
	-- ObjectGenerator:gen: super: active:IS-empty: staticOff: 0
	-- Invocation:gen: active
	-- Invocation:loadOrigin: active
	-- Invocation:loadOrigin:scan: active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: active
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 #S#1153:origin
	rpushg 1 #S#927:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Function:invoke: 
	-- pattern:load: insert(P: ? BasicProcess)
	invoke 169 0 insert
	rpop
 L574:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#928 928
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L575:
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
	rpushg 2 thenPart#S#928:origin
	rpushg 3 %if%then%%else%#S#147:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: hasWaiting :E: SQS
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: hasWaiting
	-- Unary:loadArgs: 
	-- pattern:loadArgs: hasWaiting -> B: ? booleanhasWaiting
	-- Unary:invoke: 
	-- pattern:load: hasWaiting -> B: ? boolean
	invoke 178 0 hasWaiting
	jmpFalse L577
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 1154 0 #S#1154
	rpop
 L577:
	-- ObjectGenerator:gen: super: sch.dcr:IS-empty: staticOff: 0
	-- Invocation:gen: sch.dcr
	-- Invocation:loadOrigin: sch.dcr
	-- Invocation:loadOrigin:scan: sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: sch
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 thenPart#S#928:origin
	rpushg 3 %if%then%%else%#S#147:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: dcr :E: sch
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: dcr
	-- Unary:loadArgs: 
	-- pattern:loadArgs: dcrdcr
	-- Unary:invoke: 
	-- pattern:load: dcr
	invoke 152 0 dcr
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
	rpushg 2 thenPart#S#928:origin
	rpushg 3 %if%then%%else%#S#147:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: running :E: sch
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: running
	-- Unary:loadArgs: 
	-- pattern:loadArgs: running -> B: ? Booleanrunning
	-- Unary:invoke: 
	-- pattern:load: running -> B: ? Boolean
	invoke 154 0 running
	jmpFalse L578
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 1155 0 #S#1155
	rpop
 L578:
 L576:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#929 929
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L579:
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
	break 2 410
 L580:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#930 930
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L581:
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
	rpushg 2 thenPart#S#930:origin
	rpushg 3 %if%then%%else%#S#160:origin
	rpushg 1 loopX:origin
	rpushg 1 do:origin
	-- next not assign: resume :E: main
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: resume
	-- Unary:loadArgs: 
	-- pattern:loadArgs: resumeresume
	-- Unary:invoke: 
	-- pattern:load: resume
	call(D)Resume
	rpop
 L582:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#931 931
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L583:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(100)
	-- Invocation:loadOrigin: sleep(100)
	-- Invocation:loadOrigin:scan: sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(100)
	-- Function:loadArgs: 
	-- pattern:loadArgs: sleep(V: ? integer)sleep(100)
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
	break 2 413
 L584:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#918 918
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
	rpushg 1 #S#918:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := currentElement.elm
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.elm
	-- ObjectGenerator:gen: super: currentElement.elm:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.elm
	-- Invocation:loadOrigin: currentElement.elm
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#918:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: elm :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: elm
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 #S#918:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
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
	rpushg 1 #S#918:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := currentElement.succ
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.succ
	-- ObjectGenerator:gen: super: currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ
	-- Invocation:loadOrigin: currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#918:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	break 1 516
 L586:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#919 919
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L587:
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
	rpushg 1 #S#919:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := currentElement.elm
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.elm
	-- ObjectGenerator:gen: super: currentElement.elm:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.elm
	-- Invocation:loadOrigin: currentElement.elm
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#919:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: elm :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: elm
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 1 #S#919:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
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
	rpushg 1 #S#919:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Invocation:loadOrigin:scan: := currentElement.pred
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.pred
	-- ObjectGenerator:gen: super: currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred
	-- Invocation:loadOrigin: currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#919:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	break 1 519
 L588:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#1145 1145
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L589:
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
	rpushg 2 thenPart#S#1145:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- Invocation:loadOrigin:scan: := E
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= E
	-- ObjectGenerator:gen: super: E:IS-empty: staticOff: 0
	-- Invocation:gen: E
	-- Invocation:loadOrigin: E
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 thenPart#S#1145:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 2 thenPart#S#1145:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= head
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#1145:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L590:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#1146 1146
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L591:
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
	rpushg 2 elsePart#S#1146:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	-- next not assign: succ :E: E
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: E
	rpushg 3 E
	-- Invocation:loadOrigin:scan: succ
	-- Invocation:loadOrigin:scan: := head
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= head
	-- ObjectGenerator:gen: super: head:IS-empty: staticOff: 0
	-- Invocation:gen: head
	-- Invocation:loadOrigin: head
	-- Invocation:loadOrigin:scan: head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 elsePart#S#1146:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 2 elsePart#S#1146:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- next not assign: pred :E: head
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: pred
	-- Invocation:loadOrigin:scan: := E
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= E
	-- ObjectGenerator:gen: super: E:IS-empty: staticOff: 0
	-- Invocation:gen: E
	-- Invocation:loadOrigin: E
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#1146:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	rpushg 2 elsePart#S#1146:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	rpushg 1 insert:origin
	-- Invocation:loadOrigin:scan: := E
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= E
	-- ObjectGenerator:gen: super: E:IS-empty: staticOff: 0
	-- Invocation:gen: E
	-- Invocation:loadOrigin: E
	-- Invocation:loadOrigin:scan: E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#1146:origin
	rpushg 3 %if%then%%else%#S#921:origin
	rpushg 1 #S#920:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: E
	rpushg 3 E
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 head
 L592:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#923 923
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
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	rpushg 1 Queue:origin
	rpushg 1 mQueue:origin
	rpushg 1 Containers:origin
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
	rpushg 1 #S#922:origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- next not assign: <> none :E: pred
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L593:
 L594:
	rtnInner
	end 1

	class thenPart#SB#1151 1151
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L595:
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
	rpushg 2 thenPart#S#1151:origin
	rpushg 3 %if%then%%else%#S#925:origin
	rpushg 1 #S#924:origin
	rpushg 1 removeNext:origin
	-- next not assign: succ :E: last
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: succ
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 5 succ
 L596:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#1152 1152
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L597:
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
	rpushg 2 elsePart#S#1152:origin
	rpushg 3 %if%then%%else%#S#925:origin
	rpushg 1 #S#924:origin
	rpushg 1 removeNext:origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 head
 L598:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#934 934
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L599:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: next := next + 1:IS-empty: staticOff: 0
	-- Invocation:gen: next := next + 1
	-- Invocation:loadOrigin: next := next + 1
	-- Invocation:loadOrigin:scan: next
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: next
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#934:origin
	rpushg 3 %if%then%%else%#S#188:origin
	rpushg 1 waitForChar:origin
	rpushg 1 get:origin
	-- Invocation:loadOrigin:scan: := next + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= next + 1
	-- ObjectGenerator:gen: super: next + 1:IS-empty: staticOff: 0
	-- Invocation:gen: next + 1
	-- Invocation:loadOrigin: next + 1
	-- Invocation:loadOrigin:scan: next
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: next
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#934:origin
	rpushg 3 %if%then%%else%#S#188:origin
	rpushg 1 waitForChar:origin
	rpushg 1 get:origin
	-- next not assign: + 1 :E: next
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: next
	pushg 2 next
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	storeg 2 next
	-- ObjectGenerator:gen: super: ch := B.%get next:IS-empty: staticOff: 0
	-- Invocation:gen: ch := B.%get next
	-- Invocation:loadOrigin: ch := B.%get next
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 thenPart#S#934:origin
	rpushg 3 %if%then%%else%#S#188:origin
	rpushg 1 waitForChar:origin
	-- Invocation:loadOrigin:scan: := B.%get next
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= B.%get next
	-- ObjectGenerator:gen: super: B.%get next:IS-empty: staticOff: 0
	-- Invocation:gen: B.%get next
	-- Invocation:loadOrigin: B.%get next
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#934:origin
	rpushg 3 %if%then%%else%#S#188:origin
	rpushg 1 waitForChar:origin
	rpushg 1 get:origin
	-- next not assign: %get next :E: B
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: B
	rpushg 3 B
	-- Invocation:loadOrigin:scan: %get next
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get next
	-- ObjectGenerator:gen: super: next:IS-empty: staticOff: 0
	-- Invocation:gen: next
	-- Invocation:loadOrigin: next
	-- Invocation:loadOrigin:scan: next
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: next
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#934:origin
	rpushg 3 %if%then%%else%#S#188:origin
	rpushg 1 waitForChar:origin
	rpushg 1 get:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: next
	pushg 2 next
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 ch
 L600:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#935 935
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L601:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: caller.suspend:IS-empty: staticOff: 0
	-- Invocation:gen: caller.suspend
	-- Invocation:loadOrigin: caller.suspend
	-- Invocation:loadOrigin:scan: caller
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: caller
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#935:origin
	rpushg 3 %if%then%%else%#S#188:origin
	rpushg 1 waitForChar:origin
	-- next not assign: suspend :E: caller
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: caller
	rpushg 2 caller
	-- Invocation:loadOrigin:scan: suspend
	-- Unary:loadArgs: 
	-- pattern:loadArgs: suspendsuspend
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: %restart waitForChar:IS-empty: staticOff: 0
	-- Invocation:gen: %restart waitForChar
	-- Invocation:loadOrigin: %restart waitForChar
	-- Invocation:loadOrigin:scan: %restart waitForChar
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart waitForChar
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart waitForChar
	-- KeyWord:invoke: 
	-- pattern:load: %restart Obj: ? integer
	break 2 443
 L602:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#949 949
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L603:
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
	rpushg 1 #S#949:origin
	rpushg 4 scan#S#226:origin
	-- Invocation:loadOrigin:scan: := true
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= true
	-- ObjectGenerator:gen: super: true:IS-empty: staticOff: 0
	-- Invocation:gen: true
	-- Invocation:loadOrigin: true
	-- Invocation:loadOrigin:scan: true
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: true
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 1 #S#949:origin
	rpushg 4 scan#S#226:origin
	rpushg 1 loop:origin
	rpushg 1 AwaitTermination:origin
	rpushg 1 ForkJoin:origin
	rpushg 1 ForkJoinSystem:origin
	rpushg 1 ForkJoinSystem:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: True -> B: ? Booleantrue
	-- Unary:invoke: 
	-- pattern:load: True -> B: ? Boolean
	invoke 34 0 True
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 continue
 L604:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#958 958
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L605:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('!'):IS-empty: staticOff: 0
	-- Invocation:gen: put('!')
	-- Invocation:loadOrigin: put('!')
	-- Invocation:loadOrigin:scan: put('!')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('!')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('!')
	-- ObjectGenerator:gen: super: '!':IS-empty: staticOff: 0
	-- Invocation:gen: '!'
	-- Invocation:loadOrigin: '!'
	-- Invocation:loadOrigin:scan: '!'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 33
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
	-- ObjectGenerator:gen: super: top := top + 1:IS-empty: staticOff: 0
	-- Invocation:gen: top := top + 1
	-- Invocation:loadOrigin: top := top + 1
	-- Invocation:loadOrigin:scan: top
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: top
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#958:origin
	rpushg 3 %if%then%%else%#S#251:origin
	rpushg 1 loop:origin
	rpushg 1 go:origin
	-- Invocation:loadOrigin:scan: := top + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= top + 1
	-- ObjectGenerator:gen: super: top + 1:IS-empty: staticOff: 0
	-- Invocation:gen: top + 1
	-- Invocation:loadOrigin: top + 1
	-- Invocation:loadOrigin:scan: top
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: top
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#958:origin
	rpushg 3 %if%then%%else%#S#251:origin
	rpushg 1 loop:origin
	rpushg 1 go:origin
	-- next not assign: + 1 :E: top
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: top
	pushg 2 top
	-- Invocation:loadOrigin:scan: + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 1
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
	storeg 2 top
	-- ObjectGenerator:gen: super: buf.%put IO_buf.val %at% top:IS-empty: staticOff: 0
	-- Invocation:gen: buf.%put IO_buf.val %at% top
	-- Invocation:loadOrigin: buf.%put IO_buf.val %at% top
	-- Invocation:loadOrigin:scan: buf
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: buf
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#958:origin
	rpushg 3 %if%then%%else%#S#251:origin
	rpushg 1 loop:origin
	rpushg 1 go:origin
	-- next not assign: %put IO_buf.val %at% top :E: buf
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: buf
	rpushg 2 buf
	-- Invocation:loadOrigin:scan: %put IO_buf.val %at% top
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put IO_buf.val %at% top
	-- ObjectGenerator:gen: super: IO_buf.val:IS-empty: staticOff: 0
	-- Invocation:gen: IO_buf.val
	-- Invocation:loadOrigin: IO_buf.val
	-- Invocation:loadOrigin:scan: IO_buf
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: IO_buf
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 thenPart#S#958:origin
	rpushg 3 %if%then%%else%#S#251:origin
	rpushg 1 loop:origin
	rpushg 1 go:origin
	rpushg 1 reader:origin
	-- next not assign: val :E: IO_buf
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: IO_buf
	rpushg 2 IO_buf
	-- Invocation:loadOrigin:scan: val
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: val
	pushg 2 val
	-- ObjectGenerator:gen: super: top:IS-empty: staticOff: 0
	-- Invocation:gen: top
	-- Invocation:loadOrigin: top
	-- Invocation:loadOrigin:scan: top
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: top
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#958:origin
	rpushg 3 %if%then%%else%#S#251:origin
	rpushg 1 loop:origin
	rpushg 1 go:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: top
	pushg 2 top
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	xstoreg 1 inx
 L606:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#959 959
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L607:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: put('?'):IS-empty: staticOff: 0
	-- Invocation:gen: put('?')
	-- Invocation:loadOrigin: put('?')
	-- Invocation:loadOrigin:scan: put('?')
	-- Function:pushThis: 
	-- Function:loadOrigin: put('?')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put('?')
	-- ObjectGenerator:gen: super: '?':IS-empty: staticOff: 0
	-- Invocation:gen: '?'
	-- Invocation:loadOrigin: '?'
	-- Invocation:loadOrigin:scan: '?'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 63
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L608:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#1144 1144
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L609:
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
	rpushg 1 #S#1144:origin
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := false
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= false
	-- ObjectGenerator:gen: super: false:IS-empty: staticOff: 0
	-- Invocation:gen: false
	-- Invocation:loadOrigin: false
	-- Invocation:loadOrigin:scan: false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: false
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 1 #S#1144:origin
	rpushg 2 body#S#910:origin
	rpushg 2 %for%to%%do%#S#99:origin
	rpushg 1 loop:origin
	rpushg 1 =:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: False -> B: ? Booleanfalse
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
	break 3 397
 L610:
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
 L611:
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
	rpushg 1 #S#911:origin
	rpushg 1 loop:origin
	-- next not assign: < L :E: inx
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: < L
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? integer -> B: ? Boolean< L
	-- ObjectGenerator:gen: super: L:IS-empty: staticOff: 0
	-- Invocation:gen: L
	-- Invocation:loadOrigin: L
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 #S#911:origin
	rpushg 1 loop:origin
	rpushg 1 matchEq:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L613
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
	break 1 564
 L613:
 L612:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#105 105
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
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
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
	rpushg 1 doit:origin
	-- next not assign: = c2 :E: c1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: = c2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? char -> B: ? Boolean= c2
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
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L614:
 L615:
	rtnInner
	end 1

	class #S#1154 1154
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L616:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(100)
	-- Invocation:loadOrigin: sleep(100)
	-- Invocation:loadOrigin:scan: sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(100)
	-- Function:loadArgs: 
	-- pattern:loadArgs: sleep(V: ? integer)sleep(100)
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
	break 3 410
 L617:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#1155 1155
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L618:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: sleep(50):IS-empty: staticOff: 0
	-- Invocation:gen: sleep(50)
	-- Invocation:loadOrigin: sleep(50)
	-- Invocation:loadOrigin:scan: sleep(50)
	-- Function:pushThis: 
	-- Function:loadOrigin: sleep(50)
	-- Function:loadArgs: 
	-- pattern:loadArgs: sleep(V: ? integer)sleep(50)
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
	rpushg 1 #S#1155:origin
	rpushg 2 thenPart#S#928:origin
	rpushg 3 %if%then%%else%#S#147:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	rpushg 1 Scheduler:origin
	-- next not assign: add :E: sch
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: add
	-- Unary:loadArgs: 
	-- pattern:loadArgs: addadd
	-- Unary:invoke: 
	-- pattern:load: add
	invoke 150 0 add
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
	break 3 410
 L619:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#1147 1147
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L620:
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
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- next not assign: succ :E: pred
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Invocation:loadOrigin:scan: succ
	-- Invocation:loadOrigin:scan: := currentElement.succ
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.succ
	-- ObjectGenerator:gen: super: currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ
	-- Invocation:loadOrigin: currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	invoke 1148 0 %if%then%%else%#S#1148
	rpop
 L621:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#1149 1149
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L622:
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
	rpushg 2 elsePart#S#1149:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	-- Invocation:loadOrigin:scan: := currentElement.succ
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.succ
	-- ObjectGenerator:gen: super: currentElement.succ:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.succ
	-- Invocation:loadOrigin: currentElement.succ
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#1149:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	invoke 1150 0 %if%then%%else%#S#1150
	rpop
 L623:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#912 912
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L624:
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
	rpushg 2 thenPart#S#912:origin
	rpushg 3 %if%then%%else%#S#105:origin
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := L1 <= L2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= L1 <= L2
	-- ObjectGenerator:gen: super: L1 <= L2:IS-empty: staticOff: 0
	-- Invocation:gen: L1 <= L2
	-- Invocation:loadOrigin: L1 <= L2
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#912:origin
	rpushg 3 %if%then%%else%#S#105:origin
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	-- next not assign: <= L2 :E: L1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Invocation:loadOrigin:scan: <= L2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <= V: ? integer -> B: ? Boolean<= L2
	-- ObjectGenerator:gen: super: L2:IS-empty: staticOff: 0
	-- Invocation:gen: L2
	-- Invocation:loadOrigin: L2
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 thenPart#S#912:origin
	rpushg 3 %if%then%%else%#S#105:origin
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	break 3 500
 L625:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#913 913
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L626:
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
	rpushg 2 elsePart#S#913:origin
	rpushg 3 %if%then%%else%#S#105:origin
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := c1 < c2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= c1 < c2
	-- ObjectGenerator:gen: super: c1 < c2:IS-empty: staticOff: 0
	-- Invocation:gen: c1 < c2
	-- Invocation:loadOrigin: c1 < c2
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#913:origin
	rpushg 3 %if%then%%else%#S#105:origin
	rpushg 1 doit:origin
	-- next not assign: < c2 :E: c1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: < c2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: < V: ? char -> B: ? Boolean< c2
	-- ObjectGenerator:gen: super: c2:IS-empty: staticOff: 0
	-- Invocation:gen: c2
	-- Invocation:loadOrigin: c2
	-- Invocation:loadOrigin:scan: c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c2
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 elsePart#S#913:origin
	rpushg 3 %if%then%%else%#S#105:origin
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
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
	break 3 500
 L627:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#1148 1148
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
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	rpushg 1 Queue:origin
	rpushg 1 mQueue:origin
	rpushg 1 Containers:origin
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
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- next not assign: <> none :E: succ
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L628:
 L629:
	rtnInner
	end 1

	class %if%then%%else%#S#1150 1150
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
	rpushg 2 elsePart#S#1149:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	rpushg 1 Queue:origin
	rpushg 1 mQueue:origin
	rpushg 1 Containers:origin
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
	rpushg 2 elsePart#S#1149:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	-- next not assign: <> none :E: head
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: <> none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: <> obj: ? Object -> V: ? Boolean<> none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> obj: ? Object -> V: ? Boolean
	rne
	topSuper  64
	rtnInner
	DO:
	mvStack 
 L630:
 L631:
	rtnInner
	end 1

	class thenPart#SB#1175 1175
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L632:
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
	rpushg 2 thenPart#S#1175:origin
	rpushg 3 %if%then%%else%#S#1148:origin
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	-- next not assign: succ :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: succ
	-- next not assign: pred :E: succ
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Invocation:loadOrigin:scan: pred
	-- Invocation:loadOrigin:scan: := currentElement.pred
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.pred
	-- ObjectGenerator:gen: super: currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred
	-- Invocation:loadOrigin: currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 thenPart#S#1175:origin
	rpushg 3 %if%then%%else%#S#1148:origin
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 pred
 L633:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#1176 1176
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L634:
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
	rpushg 2 elsePart#S#1176:origin
	rpushg 3 %if%then%%else%#S#1148:origin
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	-- Invocation:loadOrigin:scan: := currentElement.pred
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= currentElement.pred
	-- ObjectGenerator:gen: super: currentElement.pred:IS-empty: staticOff: 0
	-- Invocation:gen: currentElement.pred
	-- Invocation:loadOrigin: currentElement.pred
	-- Invocation:loadOrigin:scan: currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 elsePart#S#1176:origin
	rpushg 3 %if%then%%else%#S#1148:origin
	rpushg 2 thenPart#S#1147:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	-- next not assign: pred :E: currentElement
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: pred
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L635:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#1177 1177
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L636:
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
	rpushg 2 thenPart#S#1177:origin
	rpushg 3 %if%then%%else%#S#1150:origin
	rpushg 2 elsePart#S#1149:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	-- next not assign: pred :E: head
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: pred
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 4 pred
 L637:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#1178 1178
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L638:
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
	rpushg 2 elsePart#S#1178:origin
	rpushg 3 %if%then%%else%#S#1150:origin
	rpushg 2 elsePart#S#1149:origin
	rpushg 3 %if%then%%else%#S#923:origin
	rpushg 1 #S#922:origin
	rpushg 4 scan#S#132:origin
	rpushg 1 remove:origin
	-- Invocation:loadOrigin:scan: := none
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= none
	-- ObjectGenerator:gen: super: none:IS-empty: staticOff: 0
	-- Invocation:gen: none
	-- Invocation:loadOrigin: none
	-- Invocation:loadOrigin:scan: none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: none
	-- Unary:loadArgs: 
	-- pattern:loadArgs: nonenone
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 3 last
 L639:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class main 1180
	pushThis 
	invoke 1 0 BETAworld
	stop
	end 0

	class EventProcessor 1181
	stop

	class ThreadStub 1182
	DO:
	mvStack 
	call(D)ThreadStub
	stop
	-- vdtAdd: inx=1 descInx=903
	-- vdtAdd: inx=1 descInx=936
	-- vdtAdd: inx=2 descInx=937
	-- vdtAdd: inx=1 descInx=938
	-- vdtAdd: inx=2 descInx=939
	-- vdtAdd: inx=1 descInx=940
	-- vdtAdd: inx=2 descInx=941
	-- vdtAdd: inx=1 descInx=942
	-- vdtAdd: inx=2 descInx=943
	-- vdtAdd: inx=1 descInx=945
	-- vdtAdd: inx=1 descInx=907
	-- vdtAdd: inx=1 descInx=908
	-- vdtAdd: inx=1 descInx=951
	-- vdtAdd: inx=2 descInx=952
	-- vdtAdd: inx=1 descInx=953
	-- vdtAdd: inx=2 descInx=954
	-- vdtAdd: inx=1 descInx=956
	-- vdtAdd: inx=2 descInx=957
	-- vdtAdd: inx=1 descInx=905
	-- vdtAdd: inx=1 descInx=906
	-- vdtAdd: inx=1 descInx=910
	-- vdtAdd: inx=1 descInx=914
	-- vdtAdd: inx=2 descInx=915
	-- vdtAdd: inx=1 descInx=928
	-- vdtAdd: inx=2 descInx=929
	-- vdtAdd: inx=1 descInx=930
	-- vdtAdd: inx=2 descInx=931
	-- vdtAdd: inx=1 descInx=1145
	-- vdtAdd: inx=2 descInx=1146
	-- vdtAdd: inx=1 descInx=1151
	-- vdtAdd: inx=2 descInx=1152
	-- vdtAdd: inx=1 descInx=934
	-- vdtAdd: inx=2 descInx=935
	-- vdtAdd: inx=1 descInx=958
	-- vdtAdd: inx=2 descInx=959
	-- vdtAdd: inx=1 descInx=1147
	-- vdtAdd: inx=2 descInx=1149
	-- vdtAdd: inx=1 descInx=912
	-- vdtAdd: inx=2 descInx=913
	-- vdtAdd: inx=1 descInx=1175
	-- vdtAdd: inx=2 descInx=1176
	-- vdtAdd: inx=1 descInx=1177
	-- vdtAdd: inx=2 descInx=1178

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
17:	invoke 76 3 1
23:	rpop 
24:	pushthis 
25:	invoke 299 4 1
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
6:	pushthis 
7:	invoke 70 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


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


Class Object 24 1
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


Class True 34 1
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


Class immutable 46 1
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
16:	rtnEventQ 0
18:	setThisStack
19:	pushthis 
20:	rtn D


Class core 53 1
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


Class Indexed 56 1
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


Class length 59 1
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


Class %if%then%%else% 64 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 65 2 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class _L 65 1
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
19:	invoke 900 0 1
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	sendv 2
31:	rpop 
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class cycle 66 1
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


Class %for%to%%do% 67 1
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
23:	invoke 68 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class do 68 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 69 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


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
15:	pushg 3
17:	pushthis 
18:	rpushg 1
20:	rpushg 1
22:	pushg 2
24:	le
25:	jmpFalse 36
28:	pushthis 
29:	invoke 901 0 1
35:	rpop 
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class ascii 70 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushc 10
8:	pushthis 
9:	storeg 1
11:	pushc 13
13:	pushthis 
14:	storeg 2
16:	rtnEventQ 1
doE: 
18:	doEventQ 
19:	mvStack
20:	pushthis 
21:	pushthis 
22:	pushg 2
24:	storeg 3
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class newline 71 1
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


Class putint 72 1
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
18:	allocIndexed 56 1
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
54:	invoke 73 0 0
60:	rpop 
61:	rtnEventQ 0
63:	setThisStack
64:	pushthis 
65:	rtn D


Class doit 73 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	invoke 74 2 1
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
31:	invoke 75 0 1
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class loop 74 1
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
84:	invoke 902 0 1
90:	rpop 
91:	rtnEventQ 0
93:	setThisStack
94:	pushthis 
95:	rtn D


Class %for%to%%do%#S#75 75 2
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
21:	toSuper 67
enterE: 
24:	rtnInner
doE: 
25:	mvStack
26:	rtnInner


Class LIB 76 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 77 2 1
13:	rpop 
14:	pushthis 
15:	invoke 112 3 1
21:	rpop 
22:	pushthis 
23:	invoke 190 4 1
29:	rpop 
30:	pushthis 
31:	invoke 113 5 1
37:	rpop 
38:	pushthis 
39:	invoke 195 6 1
45:	rpop 
46:	pushthis 
47:	invoke 220 7 1
53:	rpop 
54:	pushthis 
55:	invoke 227 8 1
61:	rpop 
62:	pushthis 
63:	invoke 242 9 1
69:	rpop 
70:	pushthis 
71:	invoke 252 10 1
77:	rpop 
78:	pushthis 
79:	invoke 275 11 1
85:	rpop 
86:	pushthis 
87:	invoke 84 12 1
93:	rpop 
94:	rtnEventQ 0
doE: 
96:	mvStack
97:	rtnEventQ 0
99:	setThisStack
100:	pushthis 
101:	rtn D


Class BasicIO 77 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 83 2 1
13:	rpop 
14:	pushthis 
15:	invoke 109 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class Lock 78 1
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


Class init 79 1
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


Class get 80 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 81 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 81 1
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
48:	invoke 904 0 1
54:	rpop 
55:	rtnEventQ 0
57:	setThisStack
58:	pushthis 
59:	rtn D


Class free 82 1
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


Class keyboard 83 1
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


Class String 84 1
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


Class String 85 1
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


Class length 86 1
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


Class + 88 1
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
17:	invoke 86 0 0
23:	storeg 1
25:	pushthis 
26:	invoke 89 0 0
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	rpushg 3
39:	rtn D


Class doplus 89 1
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
25:	invoke 86 0 0
31:	+
32:	pushc 0
34:	pushc 1
36:	allocIndexed 56 1
40:	pushthis 
41:	rstoreg 2
43:	rtnEventQ 1
doE: 
45:	doEventQ 
46:	mvStack
47:	pushthis 
48:	invoke 90 0 1
54:	rpop 
55:	pushthis 
56:	invoke 91 0 1
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


Class %for%to%%do%#S#90 90 2
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
25:	toSuper 67
enterE: 
28:	rtnInner
doE: 
29:	mvStack
30:	rtnInner


Class %for%to%%do%#S#91 91 2
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
25:	invoke 86 0 0
31:	toSuper 67
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class asLowerCase 92 1
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


Class scan 93 1
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
13:	invoke 94 0 1
19:	rpop 
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class %for%to%%do%#S#94 94 2
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
21:	invoke 86 0 0
27:	toSuper 67
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class print 95 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 96 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %for%to%%do%#S#96 96 2
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
21:	invoke 86 0 0
27:	toSuper 67
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class = 97 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 98 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class loop 98 1
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
16:	invoke 86 0 0
22:	storeg 3
24:	pushthis 
25:	pushg 3
27:	pushthis 
28:	rpushg 1
30:	rpushg 2
32:	invoke 86 0 0
38:	ne 
39:	jmpFalse 50
42:	pushthis 
43:	invoke 909 0 1
49:	rpop 
50:	pushthis 
51:	rpushg 1
53:	pushthis 
54:	rpushg 1
56:	rpushg 1
58:	rpushg 1
60:	rpushg 1
62:	invoke 34 0 0
68:	storeg 1
70:	pushthis 
71:	invoke 99 0 1
77:	rpop 
78:	rtnEventQ 0
80:	setThisStack
81:	pushthis 
82:	rtn D


Class %for%to%%do%#S#99 99 2
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
25:	invoke 86 0 0
31:	toSuper 67
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class <= 100 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 101 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class loop 101 1
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
16:	invoke 86 0 0
22:	storeg 2
24:	pushthis 
25:	pushthis 
26:	rpushg 1
28:	rpushg 2
30:	invoke 86 0 0
36:	storeg 3
38:	pushthis 
39:	pushthis 
40:	pushg 2
42:	storeg 1
44:	pushthis 
45:	invoke 106 0 1
51:	rpop 
52:	pushthis 
53:	invoke 102 0 1
59:	rpop 
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class matchEq 102 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 103 2 1
13:	rpop 
14:	pushthis 
15:	invoke 104 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class loop 103 1
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
80:	invoke 911 0 1
86:	rpop 
87:	rtnEventQ 0
89:	setThisStack
90:	pushthis 
91:	rtn D


Class doit 104 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 105 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#105 105 3
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
35:	toSuper 64
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class %if%then%%else%#S#106 106 3
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
27:	toSuper 64
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class readLine 107 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	rpushg 1
11:	rpushg 1
13:	pushc 30
15:	pushc 0
17:	pushc 1
19:	allocIndexed 56 1
23:	pushthis 
24:	rstoreg 3
26:	pushthis 
27:	invoke 108 4 1
33:	rpop 
34:	rtnEventQ 1
doE: 
36:	doEventQ 
37:	mvStack
38:	pushthis 
39:	pushthis 
40:	rpushg 3
42:26
43:	118
44:	rswap 
45:	rstoreg 2
47:	rtnEventQ 0
49:	setThisStack
50:	pushthis 
51:	rpushg 2
53:	rtn D


Class read 108 1
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
16:	rpushg 1
18:	rpushg 1
20:	invokeExternal 4 
22:	storeg 1
24:	pushthis 
25:	pushg 1
27:	%prim put 2
29:	pushthis 
30:	pushg 1
32:	pushc 13
34:	eq 
35:	jmpFalse 46
38:	pushthis 
39:	invoke 916 0 1
45:	rpop 
46:	pushthis 
47:	rpushg 1
49:	pushthis 
50:	rpushg 1
52:	pushg 1
54:	pushc 1
56:	+
57:	storeg 1
59:	pushthis 
60:	rpushg 1
62:	rpushg 3
64:	pushthis 
65:	pushg 1
67:	pushthis 
68:	rpushg 1
70:	pushg 1
72:	xstoreg 1
74:	jmp 10
77:	rtnEventQ 0
79:	setThisStack
80:	pushthis 
81:	rtn D


Class screen 109 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 78 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 110 1
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
15:	invoke 80 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	rpushg 2
27:	invoke 79 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 2
39:	invoke 82 0 0
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class display 111 1
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
17:	invoke 80 0 1
23:	rpop 
24:	inner 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 2
31:	invoke 82 0 0
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class BasicSystem 112 1
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


Class Containers 113 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 121 3 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class mQueue 121 1
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


Class Queue 122 1
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


Class Element 123 1
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


Class scan 124 1
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
22:	invoke 125 0 1
28:	rpop 
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class do 125 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 126 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 126 1
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
23:	invoke 918 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class scanFromLast 127 1
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
22:	invoke 128 0 1
28:	rpop 
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


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
15:	rpushg 3
17:	pushNone 
18:	57
19:	jmpFalse 30
22:	pushthis 
23:	invoke 919 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class insert 130 1
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
28:	invoke 920 0 1
34:	rpop 
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class remove 131 1
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
14:	invoke 132 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class scan#S#132 132 4
allocE:
1:	rstore 4
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 4
8:	rpushg 1
10:	toSuper 124
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
29:	invoke 922 0 1
35:	rpop 
36:	rtnInner


Class removeNext 133 1
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
21:	invoke 924 0 1
27:	rpop 
28:	rtnEventQ 0
30:	setThisStack
31:	pushthis 
32:	rpushg 2
34:	rtn D


Class isEmpty 134 1
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


Class clear 135 1
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


Class BasicSystem 136 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushc 4
8:	pushthis 
9:	storeg 1
11:	pushthis 
12:	invoke 161 2 1
18:	rpop 
19:	pushthis 
20:	invoke 163 3 1
26:	rpop 
27:	pushthis 
28:	invoke 148 4 1
34:	rpop 
35:	pushthis 
36:	invoke 166 5 1
42:	rpop 
43:	pushthis 
44:	invoke 137 6 1
50:	rpop 
51:	pushthis 
52:	invoke 180 7 1
58:	rpop 
59:	pushthis 
60:	invoke 183 8 1
66:	rpop 
67:	innera 1
69:	rtnEventQ 1
doE: 
71:	doEventQ 
72:	mvStack
73:	pushthis 
74:	invoke 189 0 0
80:	rpop 
81:	inner 1
83:	pushthis 
84:	rpushg 2
86:	invoke 162 0 0
92:	rpop 
93:	rtnEventQ 0
95:	setThisStack
96:	pushthis 
97:	rtn D


Class Lock 137 1
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


Class init 138 1
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


Class get 139 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 140 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 140 1
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
48:	invoke 926 0 1
54:	rpop 
55:	rtnEventQ 0
57:	setThisStack
58:	pushthis 
59:	rtn D


Class free 141 1
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


Class BasicProcess 142 1
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


Class start 143 1
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


Class Scheduler 144 1
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
17:	invoke 150 0 0
23:	rpop 
24:	pushthis 
25:	invoke 145 0 1
31:	rpop 
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class do 145 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 146 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 146 1
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
33:	invoke 170 0 0
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
55:	invoke 927 0 1
61:	rpop 
62:	pushthis 
63:	invoke 147 0 1
69:	rpop 
70:	rtnEventQ 0
72:	setThisStack
73:	pushthis 
74:	rtn D


Class %if%then%%else%#S#147 147 3
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
29:	invoke 173 0 0
35:	toSuper 64
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class sch 148 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 137 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class entry 149 1
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
17:	invoke 139 0 1
23:	rpop 
24:	pushthis 
25:	innerP 1
27:	popThisObj
28:	pushthis 
29:	rpushg 1
31:	rpushg 2
33:	invoke 141 0 0
39:	rpop 
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class add 150 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 151 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class entry#S#151 151 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 149
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


Class dcr 152 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 153 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class entry#S#153 153 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 149
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


Class running 154 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 155 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class entry#S#155 155 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 149
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


Class Core 156 1
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
13:	invoke 158 0 1
19:	rpop 
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class attach 157 1
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


Class do 158 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 159 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loopX 159 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 160 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#160 160 3
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
29:	toSuper 64
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class cores 161 1
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


Class init 162 1
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
18:	invoke 156 0 0
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
42:	invoke 156 0 0
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
66:	invoke 156 0 0
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
90:	invoke 156 0 0
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
112:	invoke 144 0 0
118:	rswap 
119:	rstoreg 2
121:	pushthis 
122:	rpushg 1
124:	rpushg 2
126:	pushthis 
127:	rpushg 2
129:	invoke 157 0 0
135:	rpop 
136:	pushthis 
137:	pushthis 
138:	rpushg 1
140:	rpushg 1
142:	invoke 144 0 0
148:	rswap 
149:	rstoreg 2
151:	pushthis 
152:	rpushg 1
154:	rpushg 3
156:	pushthis 
157:	rpushg 2
159:	invoke 157 0 0
165:	rpop 
166:	pushthis 
167:	pushthis 
168:	rpushg 1
170:	rpushg 1
172:	invoke 144 0 0
178:	rswap 
179:	rstoreg 2
181:	pushthis 
182:	rpushg 1
184:	rpushg 4
186:	pushthis 
187:	rpushg 2
189:	invoke 157 0 0
195:	rpop 
196:	pushthis 
197:	rpushg 1
199:	rpushg 5
201:	pushthis 
202:	rpushg 1
204:	rpushg 1
206:	invoke 144 0 0
212:	invoke 157 0 0
218:	rpop 
219:	rtnEventQ 0
221:	setThisStack
222:	pushthis 
223:	rtn D


Class P_status 163 1
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


Class ProcessQueue 164 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 1
8:	rpushg 1
10:	rpushg 1
12:	rpushg 1
14:	rpushg 3
16:	rpushg 5
18:	rpushg 3
20:	toSuper 122
enterE: 
23:	rtnInner
doE: 
24:	mvStack
25:	rtnInner


Class display 165 1
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


Class SQS 166 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 164 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 137 3 1
25:	rpop 
26:	rtnEventQ 0
doE: 
28:	mvStack
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class entry 167 1
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
17:	invoke 139 0 1
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
49:	invoke 932 0 1
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
76:	invoke 141 0 0
82:	rpop 
83:	rtnEventQ 0
85:	setThisStack
86:	pushthis 
87:	rtn D


Class init 168 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 167
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


Class insert 169 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 167
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
25:	invoke 130 0 0
31:	rpop 
32:	rtnInner


Class removeNext 170 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 171 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rpushg 2
24:	rtn D


Class entry#S#171 171 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 167
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
26:	invoke 133 0 0
32:	rswap 
33:	rstoreg 2
35:	rtnInner


Class remove 172 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 167
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
25:	invoke 131 0 0
31:	rpop 
32:	rtnInner


Class isEmpty 173 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 174 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class entry#S#174 174 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 167
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
26:	invoke 134 0 0
32:	storeg 1
34:	rtnInner


Class display 175 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 167
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 1
17:	rpushg 2
19:	invoke 165 0 0
25:	rpop 
26:	rtnInner


Class addWaiting 176 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 167
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


Class dcrWaiting 177 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 167
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


Class hasWaiting 178 1
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


Class entry#S#179 179 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 167
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


Class console 180 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 137 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 181 1
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
15:	invoke 139 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	rpushg 2
27:	invoke 138 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 2
39:	invoke 141 0 0
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class display 182 1
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
17:	invoke 139 0 1
23:	rpop 
24:	inner 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 2
31:	invoke 141 0 0
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class keyboard 183 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	pushText 5
10:	toSuper 142
enterE: 
13:	pushthis 
14:	rpushg 1
16:	rpushg 1
18:	rpushg 1
20:	pushc 100
22:	pushc 0
24:	pushc 1
26:	allocIndexed 56 1
30:	pushthis 
31:	rstoreg 3
33:	rtnInner
doE: 
34:	doEventQ 
35:	mvStack
36:	pushthis 
37:	invoke 184 0 1
43:	rpop 
44:	rtnInner


Class Kscan 184 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 185 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loopB 185 1
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
21:	invokeExternal 5 
23:	jmpFalse 34
26:	pushthis 
27:	invoke 933 0 1
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 1
39:	rpushg 1
41:	rpushg 8
43:	susp 
44:	jmp 10
47:	rtnEventQ 0
49:	setThisStack
50:	pushthis 
51:	rtn D


Class get 186 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 187 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class waitForChar 187 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 188 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#188 188 3
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
25:	pushg 2
27:	pushthis 
28:	rpushg 3
30:	rpushg 1
32:	rpushg 1
34:	pushg 3
36:	lt
37:	toSuper 64
enterE: 
40:	rtnInner
doE: 
41:	mvStack
42:	rtnInner


Class init 189 1
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
15:	invoke 168 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class Complex 190 1
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


Class Complex 191 1
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


Class + 192 1
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
41:	invoke 191 0 1
47:	rswap 
48:	rstoreg 3
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rpushg 3
56:	rtn D


Class - 193 1
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
41:	invoke 191 0 1
47:	rswap 
48:	rstoreg 3
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rpushg 3
56:	rtn D


Class display 194 1
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
26:	invoke 72 0 0
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
49:	invoke 72 0 0
55:	rpop 
56:	pushc 10
58:	%prim put 2
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class EMC2array 195 1
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


Class Array 196 1
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


Class put 197 1
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
29:	invoke 198 0 1
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


Class %if%then%%else%#S#198 198 3
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
28:	invoke 59 0 0
34:	eq 
35:	toSuper 64
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class get 199 1
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
26:	invoke 200 0 1
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	pushg 1
39:	rtn D


Class %if%then%%else%#S#200 200 3
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
28:	invoke 59 0 0
34:	eq 
35:	toSuper 64
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class nxt 201 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 202 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class %if%then%%else%#S#202 202 3
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
29:	toSuper 64
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class prv 203 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 204 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class %if%then%%else%#S#204 204 3
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
29:	toSuper 64
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class forAll 205 1
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
20:	invoke 206 0 0
26:	rpop 
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	rtn D


Class loop 206 1
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
73:	invoke 944 0 1
79:	rpop 
80:	rtnEventQ 0
82:	setThisStack
83:	pushthis 
84:	rtn D


Class print 207 1
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
14:	invoke 95 0 0
20:	rpop 
21:	pushthis 
22:	innerP 1
24:	popThisObj
25:	pushText 8
27:	invoke 95 0 0
33:	rpop 
34:	pushthis 
35:	invoke 208 0 1
41:	rpop 
42:	pushthis 
43:	rpushg 1
45:	rpushg 1
47:	rpushg 1
49:	invoke 71 0 0
55:	rpop 
56:	rtnEventQ 0
58:	setThisStack
59:	pushthis 
60:	rtn D


Class %for%to%%do%#S#208 208 2
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
23:	invoke 59 0 0
29:	toSuper 67
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class Range 209 1
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
39:	invoke 947 0 1
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class check 210 1
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
36:	invoke 946 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class print 211 1
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
22:	invoke 72 0 0
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
45:	invoke 72 0 0
51:	rpop 
52:	rtnEventQ 0
54:	setThisStack
55:	pushthis 
56:	rtn D


Class D1_Array 212 1
allocE:
1:	pushthis 
2:	rstoreg 3
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 196
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
40:	allocIndexed 56 1
44:	rswap 
45:	rstoreg 2
47:	pushthis 
48:	innerP 4
50:	popThisObj
51:	rtnInner


Class putAt 213 1
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
24:	invoke 210 0 0
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


Class getAt 214 1
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
21:	invoke 210 0 0
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


Class print 215 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 207
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 2
17:	rpushg 3
19:	invoke 211 0 0
25:	rpop 
26:	rtnInner


Class D2_Array 216 1
allocE:
1:	pushthis 
2:	rstoreg 4
4:	pushthis 
5:	rstoreg 3
7:	rstore 1
9:	allocEventQ 0
11:	pushthis 
12:	rpushg 1
14:	toSuper 196
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
41:	allocIndexed 56 1
45:	rswap 
46:	rstoreg 2
48:	pushthis 
49:	pushthis 
50:	rswap 
51:	rstoreg 5
53:	pushText 5
55:	invoke 95 0 0
61:	rpop 
62:	rtnInner


Class putAt 217 1
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
27:	invoke 210 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 4
39:	pushthis 
40:	pushg 2
42:	invoke 210 0 0
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


Class getAt 218 1
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
24:	invoke 210 0 0
30:	rpop 
31:	pushthis 
32:	rpushg 1
34:	rpushg 4
36:	pushthis 
37:	pushg 2
39:	invoke 210 0 0
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


Class print 219 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 207
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 2
17:	rpushg 3
19:	invoke 211 0 0
25:	rpop 
26:	pushText 15
28:	invoke 95 0 0
34:	rpop 
35:	pushthis 
36:	rpushg 2
38:	rpushg 4
40:	invoke 211 0 0
46:	rpop 
47:	rtnInner


Class ForkJoinSystem 220 1
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


Class ForkJoinSystem 221 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 136
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


Class ForkJoin 222 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 164 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 137 3 1
25:	rpop 
26:	innera 1
28:	rtnEventQ 1
doE: 
30:	doEventQ 
31:	mvStack
32:	pushthis 
33:	rpushg 3
35:	invoke 138 0 0
41:	rpop 
42:	pushthis 
43:	innerP 1
45:	popThisObj
46:	pushthis 
47:	invoke 224 0 1
53:	rpop 
54:	rtnEventQ 0
56:	setThisStack
57:	pushthis 
58:	rtn D


Class run 223 1
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
18:	invoke 139 0 1
24:	rpop 
25:	pushthis 
26:	rpushg 1
28:	rpushg 2
30:	pushthis 
31:	rpushg 2
33:	invoke 130 0 0
39:	rpop 
40:	pushthis 
41:	rpushg 1
43:	rpushg 1
45:	rpushg 5
47:	pushthis 
48:	rpushg 2
50:	invoke 169 0 0
56:	rpop 
57:	pushthis 
58:	rpushg 1
60:	rpushg 3
62:	invoke 141 0 0
68:	rpop 
69:	rtnEventQ 0
71:	setThisStack
72:	pushthis 
73:	rtn D


Class AwaitTermination 224 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 225 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 225 1
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
35:	invoke 226 0 1
41:	rpop 
42:	pushthis 
43:	pushg 1
45:	jmpFalse 56
48:	pushthis 
49:	invoke 950 0 1
55:	rpop 
56:	pushthis 
57:	rpushg 1
59:	rpushg 1
61:	rpushg 2
63:	invoke 135 0 0
69:	rpop 
70:	rtnEventQ 0
72:	setThisStack
73:	pushthis 
74:	rtn D


Class scan#S#226 226 4
allocE:
1:	rstore 4
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 4
8:	rpushg 1
10:	rpushg 1
12:	rpushg 2
14:	toSuper 124
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
54:	invoke 949 0 1
60:	rpop 
61:	rtnInner


Class MonitorSystem 227 1
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


Class System 228 9
allocE:
1:	rstore 9
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 9
8:	rpushg 1
10:	rpushg 1
12:	rpushg 3
14:	rpushg 3
16:	toSuper 136
enterE: 
19:	innera 2
21:	rtnInner
doE: 
22:	doEventQ 
23:	mvStack
24:	inner 2
26:	rtnInner


Class Semaphore 229 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 137 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 164 3 1
25:	rpop 
26:	rtnEventQ 0
doE: 
28:	mvStack
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class init 230 1
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


Class wait 231 1
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
15:	invoke 139 0 1
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
36:	invoke 232 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#232 232 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 9
14:	rpushg 1
16:	pushthis 
17:	rpushg 3
19:	rpushg 1
21:	pushg 1
23:	pushc 0
25:	lt
26:	toSuper 64
enterE: 
29:	rtnInner
doE: 
30:	mvStack
31:	rtnInner


Class signal 233 1
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
15:	invoke 139 0 1
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
36:	invoke 234 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#234 234 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 1
10:	rpushg 1
12:	rpushg 9
14:	rpushg 1
16:	pushthis 
17:	rpushg 3
19:	rpushg 1
21:	pushg 1
23:	pushc 0
25:	le
26:	toSuper 64
enterE: 
29:	rtnInner
doE: 
30:	mvStack
31:	rtnInner


Class Process 235 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 142
enterE: 
11:	innera 3
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	inner 3
18:	rtnInner


Class start 236 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 143
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
23:	pushthis 
24:	rpushg 2
26:	rpushg 2
28:	pushText 16
30:	invoke 88 0 0
36:	invoke 88 0 0
42:	invoke 95 0 0
48:	rpop 
49:	pushthis 
50:	rpushg 2
52:	rpushg 1
54:	rpushg 5
56:	pushthis 
57:	rpushg 3
59:	invoke 169 0 0
65:	rpop 
66:	rtnInner


Class Monitor 237 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 229 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


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
13:	rpushg 2
15:	invoke 230 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class entry 239 1
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
17:	invoke 231 0 0
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
44:	invoke 233 0 0
50:	rpop 
51:	rtnEventQ 0
53:	setThisStack
54:	pushthis 
55:	rtn D


Class wait 240 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 241 2 1
13:	rpop 
14:	innera 1
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class loop 241 1
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
28:	rpushg 9
30:	rpushg 1
32:	invoke 23 0 0
38:	eq 
39:	jmpFalse 50
42:	pushthis 
43:	invoke 955 0 1
49:	rpop 
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class NonBlockingIO 242 1
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


Class NonBlockingIOSystem 243 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	invoke 244 2 1
13:	rpop 
14:	pushthis 
15:	invoke 247 3 1
21:	rpop 
22:	innera 1
24:	rtnEventQ 1
doE: 
26:	doEventQ 
27:	mvStack
28:	pushthis 
29:	innerP 1
31:	popThisObj
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class IO_buf 244 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 97
13:	storeg 4
15:	rtnEventQ 0
17:	setThisStack
18:	pushthis 
19:	rtn D


Class scan 245 1
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
16:	pushg 3
18:	pushc 1
20:	+
21:	storeg 3
23:	pushthis 
24:	invoke 246 0 1
30:	rpop 
31:	rtnEventQ 0
33:	setThisStack
34:	pushthis 
35:	rtn D


Class %if%then%%else%#S#246 246 3
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
19:	rpushg 1
21:	pushg 3
23:	pushc 4
25:	modd
26:	pushc 0
28:	eq 
29:	toSuper 64
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class reader 247 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	rpushg 1
11:	rpushg 1
13:	pushc 100
15:	pushc 0
17:	pushc 1
19:	allocIndexed 56 1
23:	pushthis 
24:	rstoreg 2
26:	rtnEventQ 1
doE: 
28:	doEventQ 
29:	mvStack
30:	pushc 81
32:	%prim put 2
34:	pushthis 
35:	susp 
36:	pushc 87
38:	%prim put 2
40:	pushthis 
41:	invoke 249 0 1
47:	rpop 
48:	rtnEventQ 0
50:	setThisStack
51:	pushthis 
52:	rtn D


Class get 248 1
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
24:	pushthis 
25:	rpushg 1
27:	rpushg 2
29:	pushthis 
30:	rpushg 1
32:	pushg 1
34:	xpushg 1
36:	storeg 1
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	pushg 1
44:	rtn D


Class go 249 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 250 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 250 1
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
19:	invoke 245 0 0
25:	rpop 
26:	pushthis 
27:	invoke 251 0 1
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 1
39:	susp 
40:	jmp 10
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#251 251 3
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
27:	rpushg 2
29:	pushg 1
31:	pushc 33
33:	eq 
34:	toSuper 64
enterE: 
37:	rtnInner
doE: 
38:	mvStack
39:	rtnInner


Class Socket 252 1
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


Class Socket 253 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 256 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class INVALID_SOCKET 254 1
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
15:	pushthis 
16:	pushc 0
18:	pushthis 
19:	pushg 1
21:	-
22:	storeg 1
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	pushg 1
30:	rtn D


Class hostent 255 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	rpushg 1
11:	rpushg 1
13:	pushc 10
15:	pushc 0
17:	pushc 1
19:	allocIndexed 56 1
23:	pushthis 
24:	rstoreg 2
26:	rtnEventQ 0
doE: 
28:	mvStack
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class socketaddr_in 256 1
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


Class init 257 1
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
13:	pushText 1
15:	invoke 95 0 0
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	pushthis 
26:	invokeExternal 6 
28:	storeg 1
30:	pushthis 
31:	rpushg 1
33:	pushg 1
35:	pushthis 
36:	rpushg 1
38:	invoke 254 0 0
44:	eq 
45:	jmpFalse 56
48:	pushthis 
49:	invoke 960 0 1
55:	rpop 
56:	pushthis 
57:	rpushg 1
59:	pushthis 
60:	pushg 1
62:	storeg 2
64:	rtnEventQ 0
66:	setThisStack
67:	pushthis 
68:	rtn D


Class connect 259 1
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
15:	pushthis 
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	rpushg 2
23:	pushthis 
24:	rpushg 1
26:	pushg 2
28:	invokeExternal 7 
30:	storeg 1
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class ioctl 261 1
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
14:	pushthis 
15:	pushthis 
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	pushg 1
23:	invokeExternal 14 
25:	storeg 2
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	pushg 2
33:	rtn D


Class bind 263 1
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
12:	pushthis 
13:	rpushg 1
15:	pushg 1
17:	pushthis 
18:	rpushg 1
20:	pushg 2
22:	invokeExternal 11 
24:	storeg 1
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class listen 265 1
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
16:	invokeExternal 12 
18:	vpop 
19:	pushText 1
21:	invoke 95 0 0
27:	rpop 
28:	rtnEventQ 0
30:	setThisStack
31:	pushthis 
32:	rtn D


Class accept 267 1
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
16:	invoke 253 0 1
22:	rswap 
23:	rstoreg 2
25:	pushthis 
26:	rpushg 2
28:	pushthis 
29:	pushthis 
30:	rpushg 1
32:	pushg 1
34:	invokeExternal 13 
36:	storeg 1
38:	pushthis 
39:	rpushg 2
41:	pushthis 
42:	rpushg 1
44:	pushg 2
46:	storeg 2
48:	rtnEventQ 0
50:	setThisStack
51:	pushthis 
52:	rpushg 2
54:	rtn D


Class send 269 1
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
15:	pushthis 
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	rpushg 2
23:	invokeExternal 8 
25:	storeg 2
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	pushg 1
33:	rtn D


Class receive 271 1
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
12:	pushthis 
13:	rpushg 1
15:	pushg 1
17:	invokeExternal 9 
19:	rswap 
20:	rstoreg 2
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rpushg 2
28:	rtn D


Class close 273 1
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


Class SocketSystem 275 1
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


Class SocketSystem 276 9
allocE:
1:	rstore 9
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 9
8:	rpushg 1
10:	rpushg 1
12:	rpushg 3
14:	rpushg 3
16:	toSuper 136
enterE: 
19:	innera 2
21:	rtnInner
doE: 
22:	doEventQ 
23:	mvStack
24:	pushText 5
26:	invoke 95 0 0
32:	rpop 
33:	pushthis 
34:	innerP 2
36:	popThisObj
37:	rtnInner


Class Socket 277 1
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


Class INVALID_SOCKET 278 1
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
13:	pushthis 
14:	pushg 1
16:	-
17:	storeg 1
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	pushg 1
25:	rtn D


Class init 279 1
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
13:	pushText 1
15:	invoke 95 0 0
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	pushthis 
26:	invokeExternal 6 
28:	storeg 1
30:	pushthis 
31:	rpushg 1
33:	pushg 1
35:	pushthis 
36:	rpushg 1
38:	invoke 278 0 0
44:	eq 
45:	jmpFalse 56
48:	pushthis 
49:	invoke 961 0 1
55:	rpop 
56:	pushthis 
57:	rpushg 1
59:	pushthis 
60:	pushg 1
62:	storeg 2
64:	pushthis 
65:	rpushg 1
67:	pushc 1
69:	invoke 281 0 0
75:	vpop 
76:	rtnEventQ 0
78:	setThisStack
79:	pushthis 
80:	rtn D


Class ioctl 281 1
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
14:	pushthis 
15:	pushthis 
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	pushg 1
23:	invokeExternal 14 
25:	storeg 2
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	pushg 2
33:	rtn D


Class connect 283 1
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
15:	pushthis 
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	rpushg 2
23:	pushthis 
24:	rpushg 1
26:	pushg 2
28:	invokeExternal 7 
30:	storeg 1
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class bind 285 1
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
12:	pushthis 
13:	rpushg 1
15:	pushg 1
17:	pushthis 
18:	rpushg 1
20:	pushg 2
22:	invokeExternal 11 
24:	storeg 1
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class listen 287 1
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
16:	invokeExternal 12 
18:	vpop 
19:	pushText 1
21:	invoke 95 0 0
27:	rpop 
28:	rtnEventQ 0
30:	setThisStack
31:	pushthis 
32:	rtn D


Class accept 289 1
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
19:	invoke 277 0 1
25:	rswap 
26:	rstoreg 3
28:	pushthis 
29:	invoke 291 0 0
35:	rpop 
36:	pushthis 
37:	rpushg 3
39:	pushthis 
40:	pushg 1
42:	storeg 1
44:	pushthis 
45:	rpushg 3
47:	pushthis 
48:	rpushg 1
50:	pushg 2
52:	storeg 2
54:	rtnEventQ 0
56:	setThisStack
57:	pushthis 
58:	rpushg 3
60:	rtn D


Class awaitAccept 291 1
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
16:	pushthis 
17:	rpushg 1
19:	rpushg 1
21:	pushg 1
23:	invokeExternal 13 
25:	storeg 1
27:	pushthis 
28:	rpushg 1
30:	pushg 1
32:	pushc 1
34:	eq 
35:	jmpFalse 46
38:	pushthis 
39:	invoke 962 0 1
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class send 292 1
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
15:	pushthis 
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	rpushg 2
23:	invokeExternal 8 
25:	storeg 2
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	pushg 1
33:	rtn D


Class receive 294 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 296 4 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rpushg 3
26:	rtn D


Class loop 296 1
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
16:	pushthis 
17:	rpushg 1
19:	rpushg 1
21:	pushg 1
23:	invokeExternal 9 
25:	rswap 
26:	rstoreg 3
28:	pushNone 
29:	pushthis 
30:	rpushg 1
32:	rpushg 3
34:	req 
35:	jmpFalse 46
38:	pushthis 
39:	invoke 963 0 1
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class close 297 1
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


Class workspace 299 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 511 4 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class demo 511 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 512 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class ArrayDemos 512 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 531 5 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class Point 531 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushc 2
13:	storeg 2
15:	pushthis 
16:	pushthis 
17:	pushg 2
19:	storeg 1
21:	pushthis 
22:	rpushg 1
24:	rpushg 1
26:	rpushg 1
28:	pushthis 
29:	pushg 1
31:	invoke 72 0 0
37:	rpop 
38:	pushthis 
39:	rpushg 1
41:	rpushg 1
43:	rpushg 1
45:	invoke 71 0 0
51:	rpop 
52:	pushthis 
53:	rpushg 3
55:	pushthis 
56:	pushc 1
58:	pushc 2
60:	invoke 532 0 1
66:	invoke 533 0 0
72:	rpop 
73:	pushthis 
74:	rpushg 2
76:	pushthis 
77:	pushc 99
79:	pushc 99
81:	invoke 532 0 1
87:	invoke 533 0 0
93:	rpop 
94:	pushthis 
95:	rpushg 2
97:	pushthis 
98:	rpushg 3
100:	invoke 533 0 0
106:	rpop 
107:	pushthis 
108:	rpushg 1
110:	rpushg 1
112:	rpushg 1
114:	pushthis 
115:	rpushg 2
117:	invoke 534 0 0
123:	invoke 72 0 0
129:	rpop 
130:	pushthis 
131:	rpushg 1
133:	rpushg 1
135:	rpushg 1
137:	pushthis 
138:	rpushg 2
140:	pushg 2
142:	invoke 72 0 0
148:	rpop 
149:	pushthis 
150:	rpushg 1
152:	rpushg 1
154:	rpushg 1
156:	invoke 71 0 0
162:	rpop 
163:	pushthis 
164:	rpushg 3
166:	pushthis 
167:	pushc 3
169:	pushc 4
171:	invoke 532 0 1
177:	invoke 533 0 0
183:	rpop 
184:	pushthis 
185:	rpushg 2
187:	pushthis 
188:	rpushg 3
190:	invoke 533 0 0
196:	rpop 
197:	pushthis 
198:	rpushg 1
200:	rpushg 1
202:	rpushg 1
204:	pushthis 
205:	rpushg 2
207:	pushg 1
209:	invoke 72 0 0
215:	rpop 
216:	pushthis 
217:	rpushg 1
219:	rpushg 1
221:	rpushg 1
223:	pushthis 
224:	rpushg 2
226:	pushg 2
228:	invoke 72 0 0
234:	rpop 
235:	rtnEventQ 0
237:	setThisStack
238:	pushthis 
239:	rtn D


Class Point 532 1
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


Class := 533 1
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
19:	pushg 1
21:	storeg 1
23:	pushthis 
24:	rpushg 1
26:	pushthis 
27:	rpushg 2
29:	pushg 2
31:	storeg 2
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	rtn D


Class getx 534 1
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


Class #S#900 900 1
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
18:	break 1 61
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class #S#901 901 1
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
41:	break 1 105
45:	rtnEventQ 0
47:	setThisStack
48:	pushthis 
49:	rtn D


Class #S#902 902 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 108
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#903 903 2
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


Class #S#904 904 1
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
16:	break 1 249
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class body#SB#905 905 2
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


Class body#SB#906 906 2
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


Class body#SB#907 907 2
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


Class body#SB#908 908 2
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


Class #S#909 909 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 397
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#910 910 2
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
75:	invoke 1144 0 1
81:	rpop 
82:	rtnEventQ 0
84:	setThisStack
85:	pushthis 
86:	rtn D


Class #S#911 911 1
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
30:	break 1 564
34:	rtnEventQ 0
36:	setThisStack
37:	pushthis 
38:	rtn D


Class thenPart#SB#912 912 2
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
46:	break 3 500
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class elsePart#SB#913 913 2
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
42:	break 3 500
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class thenPart#SB#914 914 2
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


Class elsePart#SB#915 915 2
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


Class #S#916 916 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 253
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class #S#918 918 1
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
62:	break 1 516
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class #S#919 919 1
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
62:	break 1 519
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class #S#920 920 1
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
23:	invoke 123 0 0
29:	rswap 
30:	rstoreg 3
32:	pushthis 
33:	invoke 921 0 1
39:	rpop 
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class %if%then%%else%#S#921 921 3
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
29:	toSuper 64
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


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
11:	invoke 923 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#923 923 3
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
31:	toSuper 64
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


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
43:	invoke 925 0 1
49:	rpop 
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class %if%then%%else%#S#925 925 3
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
29:	toSuper 64
enterE: 
32:	rtnInner
doE: 
33:	mvStack
34:	rtnInner


Class #S#926 926 1
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
16:	break 1 407
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class #S#927 927 1
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
100:	invoke 1153 0 1
106:	rpop 
107:	rtnEventQ 0
109:	setThisStack
110:	pushthis 
111:	rtn D


Class thenPart#SB#928 928 2
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
23:	invoke 178 0 0
29:	jmpFalse 40
32:	pushthis 
33:	invoke 1154 0 1
39:	rpop 
40:	pushthis 
41:	rpushg 2
43:	rpushg 3
45:	rpushg 1
47:	rpushg 1
49:	rpushg 1
51:	rpushg 4
53:	invoke 152 0 0
59:	rpop 
60:	pushthis 
61:	rpushg 2
63:	rpushg 3
65:	rpushg 1
67:	rpushg 1
69:	rpushg 1
71:	rpushg 4
73:	invoke 154 0 0
79:	jmpFalse 90
82:	pushthis 
83:	invoke 1155 0 1
89:	rpop 
90:	rtnEventQ 0
92:	setThisStack
93:	pushthis 
94:	rtn D


Class elsePart#SB#929 929 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 2 410
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#930 930 2
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


Class elsePart#SB#931 931 2
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
14:	break 2 413
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class #S#932 932 1
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


Class #S#933 933 1
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
24:	pushg 3
26:	pushc 1
28:	+
29:	storeg 3
31:	pushthis 
32:	rpushg 1
34:	rpushg 1
36:	rpushg 1
38:	rpushg 3
40:	pushthis 
41:	rpushg 1
43:	rpushg 1
45:	rpushg 1
47:	rpushg 1
49:	rpushg 1
51:	rpushg 1
53:	invokeExternal 4 
55:	pushthis 
56:	rpushg 1
58:	rpushg 1
60:	rpushg 1
62:	pushg 3
64:	xstoreg 1
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class thenPart#SB#934 934 2
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
26:	rpushg 1
28:	pushg 2
30:	pushc 1
32:	+
33:	storeg 2
35:	pushthis 
36:	rpushg 2
38:	rpushg 3
40:	rpushg 1
42:	pushthis 
43:	rpushg 2
45:	rpushg 3
47:	rpushg 1
49:	rpushg 1
51:	rpushg 3
53:	pushthis 
54:	rpushg 2
56:	rpushg 3
58:	rpushg 1
60:	rpushg 1
62:	pushg 2
64:	xpushg 1
66:	storeg 1
68:	rtnEventQ 0
70:	setThisStack
71:	pushthis 
72:	rtn D


Class elsePart#SB#935 935 2
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
19:	susp 
20:	break 2 443
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	rtn D


Class thenPart#SB#936 936 2
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


Class elsePart#SB#937 937 2
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


Class thenPart#SB#938 938 2
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


Class elsePart#SB#939 939 2
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


Class thenPart#SB#940 940 2
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


Class elsePart#SB#941 941 2
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


Class thenPart#SB#942 942 2
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


Class elsePart#SB#943 943 2
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


Class #S#944 944 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 336
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#945 945 2
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
37:	invoke 72 0 0
43:	rpop 
44:	pushText 1
46:	invoke 95 0 0
52:	rpop 
53:	rtnEventQ 0
55:	setThisStack
56:	pushthis 
57:	rtn D


Class #S#946 946 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 95 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#947 947 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 95 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#949 949 1
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
30:	invoke 34 0 0
36:	storeg 1
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class #S#950 950 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 465
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#951 951 2
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
42:	invoke 176 0 0
48:	rpop 
49:	pushthis 
50:	rpushg 2
52:	rpushg 3
54:	rpushg 1
56:	rpushg 3
58:	%prim thisCore 17
60:	rpushg 2
62:	rpushg 2
64:	invoke 130 0 0
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
94:	invoke 141 0 0
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


Class elsePart#SB#952 952 2
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
19:	invoke 141 0 0
25:	rpop 
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class thenPart#SB#953 953 2
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
24:	invoke 133 0 0
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
73:	invoke 169 0 0
79:	rpop 
80:	pushthis 
81:	rpushg 2
83:	rpushg 3
85:	rpushg 1
87:	rpushg 1
89:	rpushg 5
91:	invoke 177 0 0
97:	rpop 
98:	pushthis 
99:	rpushg 2
101:	rpushg 3
103:	rpushg 1
105:	rpushg 2
107:	invoke 141 0 0
113:	rpop 
114:	rtnEventQ 0
116:	setThisStack
117:	pushthis 
118:	rtn D


Class elsePart#SB#954 954 2
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
19:	invoke 141 0 0
25:	rpop 
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class #S#955 955 1
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
19:	invoke 233 0 0
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	rpushg 2
35:	invoke 231 0 0
41:	rpop 
42:	break 1 472
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class thenPart#SB#956 956 2
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
17:	pushc 63
19:	storeg 1
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class elsePart#SB#957 957 2
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
17:	pushc 33
19:	storeg 1
21:	pushthis 
22:	rpushg 2
24:	rpushg 3
26:	rpushg 1
28:	pushthis 
29:	rpushg 2
31:	rpushg 3
33:	rpushg 1
35:	pushg 4
37:	storeg 2
39:	pushthis 
40:	rpushg 2
42:	rpushg 3
44:	rpushg 1
46:	pushthis 
47:	rpushg 2
49:	rpushg 3
51:	rpushg 1
53:	pushg 4
55:	pushc 1
57:	+
58:	storeg 4
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class thenPart#SB#958 958 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 33
12:	%prim put 2
14:	pushthis 
15:	rpushg 2
17:	rpushg 3
19:	rpushg 1
21:	rpushg 1
23:	pushthis 
24:	rpushg 2
26:	rpushg 3
28:	rpushg 1
30:	rpushg 1
32:	pushg 2
34:	pushc 1
36:	+
37:	storeg 2
39:	pushthis 
40:	rpushg 2
42:	rpushg 3
44:	rpushg 1
46:	rpushg 1
48:	rpushg 2
50:	pushthis 
51:	rpushg 2
53:	rpushg 3
55:	rpushg 1
57:	rpushg 1
59:	rpushg 1
61:	rpushg 2
63:	pushg 2
65:	pushthis 
66:	rpushg 2
68:	rpushg 3
70:	rpushg 1
72:	rpushg 1
74:	pushg 2
76:	xstoreg 1
78:	rtnEventQ 0
80:	setThisStack
81:	pushthis 
82:	rtn D


Class elsePart#SB#959 959 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 63
12:	%prim put 2
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class #S#960 960 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 95 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#961 961 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 95 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#962 962 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 46
12:	%prim put 2
14:	pushthis 
15:	rpushg 1
17:	rpushg 1
19:	rpushg 2
21:	susp 
22:	break 1 481
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class #S#963 963 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushc 44
12:	%prim put 2
14:	pushthis 
15:	rpushg 1
17:	rpushg 1
19:	rpushg 2
21:	susp 
22:	break 1 484
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class #S#1144 1144 1
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
42:	break 3 397
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class thenPart#SB#1145 1145 2
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


Class elsePart#SB#1146 1146 2
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


Class thenPart#SB#1147 1147 2
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
36:	invoke 1148 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#1148 1148 3
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
39:	toSuper 64
enterE: 
42:	rtnInner
doE: 
43:	mvStack
44:	rtnInner


Class elsePart#SB#1149 1149 2
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
36:	invoke 1150 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#1150 1150 3
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
41:	toSuper 64
enterE: 
44:	rtnInner
doE: 
45:	mvStack
46:	rtnInner


Class thenPart#SB#1151 1151 2
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


Class elsePart#SB#1152 1152 2
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


Class #S#1153 1153 1
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
34:	invoke 169 0 0
40:	rpop 
41:	rtnEventQ 0
43:	setThisStack
44:	pushthis 
45:	rtn D


Class #S#1154 1154 1
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
14:	break 3 410
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class #S#1155 1155 1
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
29:	invoke 150 0 0
35:	rpop 
36:	break 3 410
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class thenPart#SB#1175 1175 2
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


Class elsePart#SB#1176 1176 2
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


Class thenPart#SB#1177 1177 2
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


Class elsePart#SB#1178 1178 2
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


Class main 1180 0
allocE:
1:	pushthis 
2:	invoke 1 0 1
8:	stop 


Class EventProcessor 1181 0
allocE:
1:	stop 


Class ThreadStub 1182 0
allocE:
doE: 
1:	mvStack
2:	call D
4:	stop 

