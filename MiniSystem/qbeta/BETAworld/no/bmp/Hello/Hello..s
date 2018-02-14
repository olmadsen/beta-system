	-- QBETA
	-- Module:gen: 
	component Comp NoOfDescs: 142
	-- ConsRef:gen: BETAworld

	class Object 36
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- pattern:gen: := V: ? Object
	-- pattern:gen: = obj: ? Object -> V: ? Boolean
	-- pattern:gen: <> obj: ? Object -> V: ? Boolean
	-- pattern:gen: suspend
	-- pattern:gen: attach(V: ? integer)
	-- pattern:gen: resume
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
	invoke 4 2 BETA
	rpop
	-- Module:gen: 
	-- ModuleItem:gen LIB
	-- ConsRef:gen: LIB
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 77 3 LIB
	rpop
	-- Module:gen: 
	-- ModuleItem:gen no
	-- ConsRef:gen: no
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 113 4 no
	rpop
	-- Module:gen: 
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

	class BETA 4
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
	invoke 71 2 ascii
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

	class LIB 77
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_dummy
	-- Module:gen: 
	-- ModuleItem:gen BasicIO
	-- ConsRef:gen: BasicIO
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 78 2 BasicIO
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
	-- ModuleItem:gen String
	-- ConsRef:gen: String
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 85 3 String
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

	class no 113
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: no_dummy
	-- Module:gen: 
	-- ModuleItem:gen bmp
	-- ConsRef:gen: bmp
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 114 2 bmp
	rpop
	-- Module:gen: 
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

	class False 24
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
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
	-- on : 0
	-- AdjustOrigin: 0
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

	class True 25
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- Signature:gen: 
	-- Arguments:gen: 
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

	class core 54
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
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

	class Indexed 57
	pushThis 
	storeg 1 range
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: range
	-- pattern:gen: elm
	-- vdtAdd: inx=1 descInx=36
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

	class %if%then%%else% 65
	pushThis 
	storeg 1 cond
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: cond
	-- pattern:gen: thenPart
	-- vdtAdd: inx=1 descInx=36
	-- pattern:gen: elsePart
	-- vdtAdd: inx=2 descInx=36
	-- VarRef:gen: ugly_y
	-- ConsRef:gen: _L
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 66 2 _L
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

	class cycle 67
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
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

	class %for%to%%do% 68
	pushThis 
	storeg 2 last
	pushThis 
	storeg 1 first
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: first
	-- VarRef:gen: last
	-- pattern:gen: body
	-- vdtAdd: inx=1 descInx=36
	-- VarRef:gen: inx
	-- pattern:gen: do
	innerA  2
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: dodo
	-- Unary:invoke: 
	-- pattern:load: do
	invoke 69 0 do
	rpop
	-- ObjectGenerator:gen: super: %inner :IS-empty: staticOff: 0
	-- Invocation:gen: %inner 
	-- Invocation:loadOrigin: %inner 
	-- Invocation:loadOrigin:scan: %inner 
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner 
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner 
	-- KeyWord:invoke: 
	-- pattern:load: %inner P: ? Object
	pushThis 
	inner  2
	rpopThisObj 
 L26:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ascii 71
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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

	class newline 72
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
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

	class putint 73
	pushThis 
	storeg 1 V
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: V
	-- ConsRef:gen: D
	-- ObjectGenerator:gen: super: Indexed(20,integer):IS-empty: staticOff: 2
	-- Invocation:gen: Indexed(20,integer)
	-- Invocation:loadOrigin: Indexed(20,integer)
	-- Invocation:loadOrigin:scan: Indexed(20,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(20,integer)
	-- on : 1
	-- AdjustOrigin: 0
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
	allocIndexed 57 StaticRep asObj
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: doitdoit
	-- Unary:invoke: 
	-- pattern:load: doit
	invoke 74 0 doit
	rpop
 L32:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicIO 78
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Lock
	-- ConsRef:gen: keyboard
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 84 2 keyboard
	rpop
	-- ConsRef:gen: screen
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 110 3 screen
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

	class String 85
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: String
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

	class bmp 114
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: bmp_dummy
	-- Module:gen: 
	-- ModuleItem:gen Hello
	-- ConsRef:gen: Hello
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 3 2 Hello
	rpop
	-- Module:gen: 
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

	class length 60
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L40:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: res := %get 0
	-- Invocation:loadOrigin: res := %get 0
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
 L41:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: res
	pushg 1 res
	rtn(D)
	end 1

	class _L 66
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_uglye
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L42:
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 _L:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cond
	pushg 1 cond
	jmpFalse L44
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 118 0 #S#118
	rpop
 L44:
	-- ObjectGenerator:gen: super: elsePart:IS-empty: staticOff: 0
	-- Invocation:gen: elsePart
	-- Invocation:loadOrigin: elsePart
	-- Invocation:loadOrigin:scan: elsePart
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: elsePart
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 _L:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: elsePartelsePart
	-- Unary:invoke: 
	-- pattern:load: elsePart
	sendv 2 elsePart
	rpop
 L43:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 69
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 70 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L45:
	-- Include:gen: 
 L46:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 74
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 75 2 loop
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L47:
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: isNeg
	pushg 3 isNeg
	jmpFalse L49
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
 L49:
	-- ObjectGenerator:gen: super: %for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i):IS-empty: staticOff: 0
	pushThis 
	invoke 76 0 %for%to%%do%#S#76
	rpop
 L48:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Lock 79
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: dummy
	-- VarRef:gen: M
	-- pattern:gen: init
	-- pattern:gen: get
	-- pattern:gen: free
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

	class keyboard 84
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: readLine -> M: ? LIB.String.String
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

	class screen 110
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 screen:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: LockLock
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 79 2 Lock
	rpop
	-- pattern:gen: init
	-- pattern:gen: display
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

	class String 86
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
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
 L56:
	-- Include:gen: 
 L57:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Hello 3
	rstore 1 origin
	allocEventQ
	mvStack 
	-- ConsRef:gen: helloObject
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 115 2 helloObject
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L58:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: helloObject.s.print:IS-empty: staticOff: 0
	-- Invocation:gen: helloObject.s.print
	-- Invocation:loadOrigin: helloObject.s.print
	-- Invocation:loadOrigin:scan: helloObject
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: helloObject
	-- on : 0
	-- AdjustOrigin: 0
	-- next not assign: s :E: helloObject
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: helloObject
	rpushg 2 helloObject
	-- Invocation:loadOrigin:scan: s
	-- next not assign: print :E: s
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: s
	rpushg 2 s
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 96 0 print
	rpop
	-- ObjectGenerator:gen: super: helloObject.print(2):IS-empty: staticOff: 0
	-- Invocation:gen: helloObject.print(2)
	-- Invocation:loadOrigin: helloObject.print(2)
	-- Invocation:loadOrigin:scan: helloObject
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: helloObject
	-- on : 0
	-- AdjustOrigin: 0
	-- next not assign: print(2) :E: helloObject
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: helloObject
	rpushg 2 helloObject
	-- Invocation:loadOrigin:scan: print(2)
	-- Function:loadArgs: 
	-- pattern:loadArgs: print(noOfTimes: ? integer)print(2)
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
	-- pattern:load: print(noOfTimes: ? integer)
	invoke 116 0 print
	rpop
	-- ObjectGenerator:gen: super: "so far so good".print:IS-empty: staticOff: 0
	-- Invocation:gen: "so far so good".print
	-- Invocation:loadOrigin: "so far so good".print
	-- Invocation:loadOrigin:scan: "so far so good"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText so far so good
	-- next not assign: print :E: "so far so good"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 96 0 print
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 Hello:origin
	rpushg 1 bmp:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 72 0 newline
	rpop
	-- ObjectGenerator:gen: super: "was this so good?".print:IS-empty: staticOff: 0
	-- Invocation:gen: "was this so good?".print
	-- Invocation:loadOrigin: "was this so good?".print
	-- Invocation:loadOrigin:scan: "was this so good?"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText was this so good?
	-- next not assign: print :E: "was this so good?"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 96 0 print
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 Hello:origin
	rpushg 1 bmp:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 72 0 newline
	rpop
	-- ObjectGenerator:gen: super: helloObject.s:IS-empty: staticOff: 0
	-- Invocation:gen: helloObject.s
	-- Invocation:loadOrigin: helloObject.s
	-- Invocation:loadOrigin:scan: helloObject
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: helloObject
	-- on : 0
	-- AdjustOrigin: 0
	-- next not assign: s :E: helloObject
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: helloObject
	rpushg 2 helloObject
	-- Invocation:loadOrigin:scan: s
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: s
	rpushg 2 s
	-- ObjectGenerator:gen: super: "hm?".print:IS-empty: staticOff: 0
	-- Invocation:gen: "hm?".print
	-- Invocation:loadOrigin: "hm?".print
	-- Invocation:loadOrigin:scan: "hm?"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText hm?
	-- next not assign: print :E: "hm?"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 96 0 print
	rpop
 L59:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#118 118
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L60:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: thenPart:IS-empty: staticOff: 0
	-- Invocation:gen: thenPart
	-- Invocation:loadOrigin: thenPart
	-- Invocation:loadOrigin:scan: thenPart
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: thenPart
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 #S#118:origin
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
	break 1 43
 L61:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 70
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L62:
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
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
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
	jmpFalse L64
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 119 0 #S#119
	rpop
 L64:
 L63:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 75
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L65:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := L + 1:IS-empty: staticOff: 0
	-- Invocation:gen: L := L + 1
	-- Invocation:loadOrigin: L := L + 1
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 loop:origin
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- integer
	-- basic
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: V := V // 10:IS-empty: staticOff: 0
	-- Invocation:gen: V := V // 10
	-- Invocation:loadOrigin: V := V // 10
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
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
	jmpFalse L67
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 120 0 #S#120
	rpop
 L67:
 L66:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#76 76
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=76
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
	-- on : 2
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 doit:origin
	rpushg 1 putint:origin
	-- Super:sig none
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
	-- on : 1
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L68:
 L69:
	rtnInner
	end 1

	class init 80
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L70:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := 0:IS-empty: staticOff: 0
	-- Invocation:gen: M := 0
	-- Invocation:loadOrigin: M := 0
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- on : 1
	-- AdjustOrigin: 0
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
 L71:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class get 81
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: res
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 82 2 loop
	rpop
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

	class free 83
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L74:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := 0:IS-empty: staticOff: 0
	-- Invocation:gen: M := 0
	-- Invocation:loadOrigin: M := 0
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- on : 1
	-- AdjustOrigin: 0
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
 L75:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class readLine 108
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: inx
	-- ConsRef:gen: msg
	-- ObjectGenerator:gen: super: Indexed(30,integer):IS-empty: staticOff: 3
	-- Invocation:gen: Indexed(30,integer)
	-- Invocation:loadOrigin: Indexed(30,integer)
	-- Invocation:loadOrigin:scan: Indexed(30,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(30,integer)
	-- on : 3
	-- AdjustOrigin: 0
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
	allocIndexed 57 StaticRep asObj
	pushThis 
	rstoreg 3 indexed
	-- ConsRef:gen: read
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 109 4 read
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L76:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: M := msg.asString:IS-empty: staticOff: 0
	-- Invocation:gen: M := msg.asString
	-- Invocation:loadOrigin: M := msg.asString
	-- Invocation:loadOrigin:scan: M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: M
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
 L77:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: M
	rpushg 2 M
	rtn(D)
	end 1

	class init 111
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L78:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L.get:IS-empty: staticOff: 0
	-- Invocation:gen: L.get
	-- Invocation:loadOrigin: L.get
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 81 0 get
	rpop
	-- ObjectGenerator:gen: super: L.init:IS-empty: staticOff: 0
	-- Invocation:gen: L.init
	-- Invocation:loadOrigin: L.init
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 80 0 init
	rpop
	-- ObjectGenerator:gen: super: L.free:IS-empty: staticOff: 0
	-- Invocation:gen: L.free
	-- Invocation:loadOrigin: L.free
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 83 0 free
	rpop
 L79:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 112
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L80:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L.get:IS-empty: staticOff: 0
	-- Invocation:gen: L.get
	-- Invocation:loadOrigin: L.get
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 81 0 get
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
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 83 0 free
	rpop
 L81:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 87
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L82:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: V := %get 0:IS-empty: staticOff: 0
	-- Invocation:gen: V := %get 0
	-- Invocation:loadOrigin: V := %get 0
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
 L83:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	pushg 1 V
	rtn(D)
	end 1

	class + 89
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: S
	-- VarRef:gen: L
	-- pattern:gen: doplus
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L84:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := Length:IS-empty: staticOff: 0
	-- Invocation:gen: L := Length
	-- Invocation:loadOrigin: L := Length
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 +:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerLength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 87 0 length
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
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: doplusdoplus
	-- Unary:invoke: 
	-- pattern:load: doplus
	invoke 90 0 doplus
	rpop
 L85:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: V
	rpushg 3 V
	rtn(D)
	end 1

	class asLowerCase 93
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 0
	DO:
	mvStack 
 L86:
	-- Include:gen: 
 L87:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: T
	rpushg 2 T
	rtn(D)
	end 1

	class scan 94
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: current
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L88:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    current := %get inx
    %inner scan:IS-empty: staticOff: 0
	pushThis 
	invoke 95 0 %for%to%%do%#S#95
	rpop
 L89:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 96
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L90:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    put(%get inx):IS-empty: staticOff: 0
	pushThis 
	invoke 97 0 %for%to%%do%#S#97
	rpop
 L91:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class = 98
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: S
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 99 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L92:
	-- Include:gen: 
 L93:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class <= 101
	pushThis 
	rstoreg 2 S
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: S
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 102 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L94:
	-- Include:gen: 
 L95:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: B
	pushg 1 B
	rtn(D)
	end 1

	class helloObject 115
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: s
	-- pattern:gen: print(noOfTimes: ? integer)
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L96:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: s := "Hello World":IS-empty: staticOff: 0
	-- Invocation:gen: s := "Hello World"
	-- Invocation:loadOrigin: s := "Hello World"
	-- Invocation:loadOrigin:scan: s
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: s
	-- on : 0
	-- AdjustOrigin: 0
	-- Invocation:loadOrigin:scan: := "Hello World"
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= "Hello World"
	-- ObjectGenerator:gen: super: "Hello World":IS-empty: staticOff: 0
	-- Invocation:gen: "Hello World"
	-- Invocation:loadOrigin: "Hello World"
	-- Invocation:loadOrigin:scan: "Hello World"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Hello World
	-- String::loadArgs: 
	-- String::invoke: 
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	rswap
	rstoreg 2 s
	-- ObjectGenerator:gen: super: s.print:IS-empty: staticOff: 0
	-- Invocation:gen: s.print
	-- Invocation:loadOrigin: s.print
	-- Invocation:loadOrigin:scan: s
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: s
	-- on : 0
	-- AdjustOrigin: 0
	-- next not assign: print :E: s
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: s
	rpushg 2 s
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 96 0 print
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 helloObject:origin
	rpushg 1 Hello:origin
	rpushg 1 bmp:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 72 0 newline
	rpop
 L97:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#119 119
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L98:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: body:IS-empty: staticOff: 0
	-- Invocation:gen: body
	-- Invocation:loadOrigin: body
	-- Invocation:loadOrigin:scan: body
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: body
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 #S#119:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 #S#119:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 #S#119:origin
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
	break 1 62
 L99:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#120 120
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L100:
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
	break 1 65
 L101:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#121 121
	rstore 2 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: i
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L102:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: i := L + 1 - inx:IS-empty: staticOff: 0
	-- Invocation:gen: i := L + 1 - inx
	-- Invocation:loadOrigin: i := L + 1 - inx
	-- Invocation:loadOrigin:scan: i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: i
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#121:origin
	rpushg 2 %for%to%%do%#S#76:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#121:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#121:origin
	rpushg 2 %for%to%%do%#S#76:origin
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
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 1 i
	-- KeyWord:invoke: 
	-- pattern:load: %get inx: ? integer -> V: ? integer
	-- integer
	-- value
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: + V: ? char -> R: ? char
	plus
	-- Function:invoke: 
	-- pattern:load: put(ch: ? char)
	%put 2
 L103:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 82
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L104:
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	jmpFalse L106
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 122 0 #S#122
	rpop
 L106:
 L105:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class read 109
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: ch
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L107:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: ch := _iGet:IS-empty: staticOff: 0
	-- Invocation:gen: ch := _iGet
	-- Invocation:loadOrigin: ch := _iGet
	-- Invocation:loadOrigin:scan: ch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ch
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 4
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	jmpFalse L109
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 134 0 #S#134
	rpop
 L109:
	-- ObjectGenerator:gen: super: inx := inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx := inx + 1
	-- Invocation:loadOrigin: inx := inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 read:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- integer
	-- basic
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
	jmp L107
 L108:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doplus 90
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
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
	-- on : 4
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 87 0 length
	-- Binary:invoke: 
	-- pattern:load: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:load: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 57 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L110:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% L %do% 
    e := %get inx
    T.%put e %at% inx:IS-empty: staticOff: 0
	pushThis 
	invoke 91 0 %for%to%%do%#S#91
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% S.length %do% 
    e := S.%get inx
    i := L + inx
    T.%put e %at% i:IS-empty: staticOff: 0
	pushThis 
	invoke 92 0 %for%to%%do%#S#92
	rpop
	-- ObjectGenerator:gen: super: V := T.asString:IS-empty: staticOff: 0
	-- Invocation:gen: V := T.asString
	-- Invocation:loadOrigin: V := T.asString
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
 L111:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#95 95
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=95
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
	-- on : 3
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 scan:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Super:sig none
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
	-- on : 1
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 scan:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 87 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L112:
 L113:
	rtnInner
	end 1

	class %for%to%%do%#S#97 97
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=97
	-- Invocation:loadOrigin: %for 1 %to% length %do% 
    put(%get inx)
	-- Invocation:loadOrigin:scan: %for 1 %to% length %do% 
    put(%get inx)
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% length %do% 
    put(%get inx)
	-- on : 3
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 print:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Super:sig none
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
	-- on : 1
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 print:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 87 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L114:
 L115:
	rtnInner
	end 1

	class loop 99
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
 L116:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := length:IS-empty: staticOff: 0
	-- Invocation:gen: L := length
	-- Invocation:loadOrigin: L := length
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 loop:origin
	rpushg 1 =:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 87 0 length
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 87 0 length
	-- Binary:invoke: 
	-- pattern:load: <> V: ? integer -> B: ? Boolean
	55
	jmpFalse L118
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 127 0 #S#127
	rpop
 L118:
	-- ObjectGenerator:gen: super: B := true:IS-empty: staticOff: 0
	-- Invocation:gen: B := true
	-- Invocation:loadOrigin: B := true
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 1 loop:origin
	rpushg 1 =:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: True -> B: ? Booleantrue
	-- Unary:invoke: 
	-- pattern:load: True -> B: ? Boolean
	invoke 25 0 True
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
	invoke 100 0 %for%to%%do%#S#100
	rpop
 L117:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 102
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
 L119:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L1 := length:IS-empty: staticOff: 0
	-- Invocation:gen: L1 := length
	-- Invocation:loadOrigin: L1 := length
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 87 0 length
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	invoke 87 0 length
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
	-- on : 0
	-- AdjustOrigin: 0
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
	-- on : 0
	-- AdjustOrigin: 0
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
	invoke 107 0 %if%then%%else%#S#107
	rpop
	-- ObjectGenerator:gen: super: matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: matchEq
	-- Invocation:loadOrigin: matchEq
	-- Invocation:loadOrigin:scan: matchEq
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: matchEq
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: matchEqmatchEq
	-- Unary:invoke: 
	-- pattern:load: matchEq
	invoke 103 0 matchEq
	rpop
 L120:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 116
	pushThis 
	storeg 1 noOfTimes
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: noOfTimes
	-- pattern:gen: loop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L121:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: loop:IS-empty: staticOff: 0
	-- Invocation:gen: loop
	-- Invocation:loadOrigin: loop
	-- Invocation:loadOrigin:scan: loop
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: loop
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- pattern:loadArgs: looploop
	-- Unary:invoke: 
	-- pattern:load: loop
	invoke 117 0 loop
	rpop
 L122:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#122 122
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L123:
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
	break 1 104
 L124:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#134 134
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L125:
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
	break 1 108
 L126:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#91 91
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=91
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
	-- on : 4
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 doplus:origin
	rpushg 1 +:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Super:sig none
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
	-- on : 1
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 doplus:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L127:
 L128:
	rtnInner
	end 1

	class %for%to%%do%#S#92 92
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=92
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
	-- on : 4
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 doplus:origin
	rpushg 1 +:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Super:sig none
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
	-- on : 1
	-- AdjustOrigin: 2
	rpushg 2 origin
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
	invoke 87 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L129:
 L130:
	rtnInner
	end 1

	class body#SB#125 125
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L131:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: current := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: current := %get inx
	-- Invocation:loadOrigin: current := %get inx
	-- Invocation:loadOrigin:scan: current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: current
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#125:origin
	rpushg 2 %for%to%%do%#S#95:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#125:origin
	rpushg 2 %for%to%%do%#S#95:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#125:origin
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
	rpushg 2 body#S#125:origin
	rpushg 2 %for%to%%do%#S#95:origin
	inner  1
	rpopThisObj 
 L132:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#126 126
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L133:
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#126:origin
	rpushg 2 %for%to%%do%#S#97:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#126:origin
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
 L134:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#127 127
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L135:
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
	break 1 117
 L136:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#100 100
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=100
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
	-- on : 4
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 loop:origin
	rpushg 1 =:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Super:sig none
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
	-- on : 2
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 loop:origin
	rpushg 1 =:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:load: length -> V: ? integer
	invoke 87 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L137:
 L138:
	rtnInner
	end 1

	class matchEq 103
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: inx
	-- VarRef:gen: c1
	-- VarRef:gen: c2
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 104 2 loop
	rpop
	-- ConsRef:gen: doit
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 105 3 doit
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L139:
	-- Include:gen: 
 L140:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#107 107
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
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
	-- on : 4
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Super:sig none
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
	-- on : 0
	-- AdjustOrigin: 3
	rpushg 3 origin
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
	-- on : 0
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: < V: ? integer -> B: ? Boolean
	51
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L141:
 L142:
	rtnInner
	end 1

	class loop 117
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L143:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if noOfTimes > 0 %then% 
    
    s.print
    newline
    noOfTimes := noOfTimes - 1
    %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %if noOfTimes > 0 %then% 
    
    s.print
    newline
    noOfTimes := noOfTimes - 1
    %restart loop
	-- Invocation:loadOrigin: %if noOfTimes > 0 %then% 
    
    s.print
    newline
    noOfTimes := noOfTimes - 1
    %restart loop
	-- Invocation:loadOrigin:scan: %if noOfTimes > 0 %then% 
    
    s.print
    newline
    noOfTimes := noOfTimes - 1
    %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if noOfTimes > 0 %then% 
    
    s.print
    newline
    noOfTimes := noOfTimes - 1
    %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if noOfTimes > 0 %then% 
    
    s.print
    newline
    noOfTimes := noOfTimes - 1
    %restart loop
	-- KeyWord:invoke: 
	-- pattern:load: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: noOfTimes > 0:IS-empty: staticOff: 0
	-- Invocation:gen: noOfTimes > 0
	-- Invocation:loadOrigin: noOfTimes > 0
	-- Invocation:loadOrigin:scan: noOfTimes
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noOfTimes
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 loop:origin
	-- next not assign: > 0 :E: noOfTimes
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noOfTimes
	pushg 1 noOfTimes
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
	jmpFalse L145
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 135 0 #S#135
	rpop
 L145:
 L144:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#123 123
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L146:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: e := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: e := %get inx
	-- Invocation:loadOrigin: e := %get inx
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#123:origin
	rpushg 2 %for%to%%do%#S#91:origin
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
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 body#S#123:origin
	rpushg 2 %for%to%%do%#S#91:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#123:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#123:origin
	rpushg 2 %for%to%%do%#S#91:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#123:origin
	rpushg 2 %for%to%%do%#S#91:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#123:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- Integer
	-- basic
	xstoreg 1 inx
 L147:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#124 124
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L148:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: e := S.%get inx:IS-empty: staticOff: 0
	-- Invocation:gen: e := S.%get inx
	-- Invocation:loadOrigin: e := S.%get inx
	-- Invocation:loadOrigin:scan: e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: e
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
	rpushg 2 %for%to%%do%#S#92:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
	rpushg 2 %for%to%%do%#S#92:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
	rpushg 2 %for%to%%do%#S#92:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
	rpushg 2 %for%to%%do%#S#92:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
	rpushg 2 %for%to%%do%#S#92:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
	rpushg 2 %for%to%%do%#S#92:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#124:origin
	rpushg 2 %for%to%%do%#S#92:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 2 i
	-- KeyWord:invoke: 
	-- pattern:load: %put V: ? elm %at% inx: ? integer
	-- Integer
	-- basic
	xstoreg 1 inx
 L149:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#128 128
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L150:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: c1 := %get inx:IS-empty: staticOff: 0
	-- Invocation:gen: c1 := %get inx
	-- Invocation:loadOrigin: c1 := %get inx
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
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
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 2 c2
	-- Binary:invoke: 
	-- pattern:load: <> V: ? char -> B: ? Boolean
	55
	jmpFalse L152
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 136 0 #S#136
	rpop
 L152:
 L151:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 104
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L153:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: inx := inx + 1:IS-empty: staticOff: 0
	-- Invocation:gen: inx := inx + 1
	-- Invocation:loadOrigin: inx := inx + 1
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 4
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 3
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
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
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 loop:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	jmpFalse L155
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 129 0 #S#129
	rpop
 L155:
 L154:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 105
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L156:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq:IS-empty: staticOff: 0
	pushThis 
	invoke 106 0 %if%then%%else%#S#106
	rpop
 L157:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#132 132
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L158:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := L1:IS-empty: staticOff: 0
	-- Invocation:gen: L := L1
	-- Invocation:loadOrigin: L := L1
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#132:origin
	rpushg 3 %if%then%%else%#S#107:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#132:origin
	rpushg 3 %if%then%%else%#S#107:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
 L159:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#133 133
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L160:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: L := L2:IS-empty: staticOff: 0
	-- Invocation:gen: L := L2
	-- Invocation:loadOrigin: L := L2
	-- Invocation:loadOrigin:scan: L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 elsePart#S#133:origin
	rpushg 3 %if%then%%else%#S#107:origin
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 elsePart#S#133:origin
	rpushg 3 %if%then%%else%#S#107:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: := V: ? Object
	storeg 1 L
 L161:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#135 135
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L162:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: s.print:IS-empty: staticOff: 0
	-- Invocation:gen: s.print
	-- Invocation:loadOrigin: s.print
	-- Invocation:loadOrigin:scan: s
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: s
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 #S#135:origin
	rpushg 1 loop:origin
	rpushg 1 print:origin
	-- next not assign: print :E: s
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: s
	rpushg 2 s
	-- Invocation:loadOrigin:scan: print
	-- Unary:loadArgs: 
	-- pattern:loadArgs: printprint
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 96 0 print
	rpop
	-- ObjectGenerator:gen: super: newline:IS-empty: staticOff: 0
	-- Invocation:gen: newline
	-- Invocation:loadOrigin: newline
	-- Invocation:loadOrigin:scan: newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: newline
	-- on : 6
	-- AdjustOrigin: 0
	rpushg 1 #S#135:origin
	rpushg 1 loop:origin
	rpushg 1 print:origin
	rpushg 1 helloObject:origin
	rpushg 1 Hello:origin
	rpushg 1 bmp:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:load: newline
	invoke 72 0 newline
	rpop
	-- ObjectGenerator:gen: super: noOfTimes := noOfTimes - 1:IS-empty: staticOff: 0
	-- Invocation:gen: noOfTimes := noOfTimes - 1
	-- Invocation:loadOrigin: noOfTimes := noOfTimes - 1
	-- Invocation:loadOrigin:scan: noOfTimes
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noOfTimes
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 #S#135:origin
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := noOfTimes - 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= noOfTimes - 1
	-- ObjectGenerator:gen: super: noOfTimes - 1:IS-empty: staticOff: 0
	-- Invocation:gen: noOfTimes - 1
	-- Invocation:loadOrigin: noOfTimes - 1
	-- Invocation:loadOrigin:scan: noOfTimes
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: noOfTimes
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 #S#135:origin
	rpushg 1 loop:origin
	-- next not assign: - 1 :E: noOfTimes
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noOfTimes
	pushg 1 noOfTimes
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
	storeg 1 noOfTimes
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
	break 1 143
 L163:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#136 136
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L164:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := false:IS-empty: staticOff: 0
	-- Invocation:gen: B := false
	-- Invocation:loadOrigin: B := false
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 1 #S#136:origin
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
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
	-- on : 7
	-- AdjustOrigin: 0
	rpushg 1 #S#136:origin
	rpushg 2 body#S#128:origin
	rpushg 2 %for%to%%do%#S#100:origin
	rpushg 1 loop:origin
	rpushg 1 =:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: False -> B: ? Booleanfalse
	-- Unary:invoke: 
	-- pattern:load: False -> B: ? Boolean
	invoke 24 0 False
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
	break 3 117
 L165:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#129 129
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L166:
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
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 #S#129:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 #S#129:origin
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
	jmpFalse L168
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
	break 1 153
 L168:
 L167:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#106 106
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
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
	-- on : 6
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Super:sig none
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
	-- on : 1
	-- AdjustOrigin: 3
	rpushg 3 origin
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
	-- on : 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = V: ? char -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L169:
 L170:
	rtnInner
	end 1

	class thenPart#SB#130 130
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L171:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := L1 <= L2:IS-empty: staticOff: 0
	-- Invocation:gen: B := L1 <= L2
	-- Invocation:loadOrigin: B := L1 <= L2
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- on : 5
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#130:origin
	rpushg 3 %if%then%%else%#S#106:origin
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
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#130:origin
	rpushg 3 %if%then%%else%#S#106:origin
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
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#130:origin
	rpushg 3 %if%then%%else%#S#106:origin
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
	break 3 140
 L172:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#131 131
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L173:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := c1 < c2:IS-empty: staticOff: 0
	-- Invocation:gen: B := c1 < c2
	-- Invocation:loadOrigin: B := c1 < c2
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- on : 5
	-- AdjustOrigin: 0
	rpushg 2 elsePart#S#131:origin
	rpushg 3 %if%then%%else%#S#106:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 elsePart#S#131:origin
	rpushg 3 %if%then%%else%#S#106:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 elsePart#S#131:origin
	rpushg 3 %if%then%%else%#S#106:origin
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
	break 3 140
 L174:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class main 143
	pushThis 
	invoke 1 0 BETAworld
	stop
	end 0

	class EventProcessor 144
	stop

	class ThreadStub 145
	DO:
	mvStack 
	call(D)ThreadStub
	stop
	-- vdtAdd: inx=1 descInx=121
	-- vdtAdd: inx=1 descInx=125
	-- vdtAdd: inx=1 descInx=126
	-- vdtAdd: inx=1 descInx=123
	-- vdtAdd: inx=1 descInx=124
	-- vdtAdd: inx=1 descInx=128
	-- vdtAdd: inx=1 descInx=132
	-- vdtAdd: inx=2 descInx=133
	-- vdtAdd: inx=1 descInx=130
	-- vdtAdd: inx=2 descInx=131

Class BETAworld 1 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	pushthis 
6:	saveBETAworld
7:	mvStack
8:	pushthis 
9:	invoke 4 2 1
15:	rpop 
16:	pushthis 
17:	invoke 77 3 1
23:	rpop 
24:	pushthis 
25:	invoke 113 4 1
31:	rpop 
32:	rtnEventQ 0
doE: 
34:	mvStack
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class Hello 3 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	invoke 115 2 1
13:	rpop 
14:	rtnEventQ 1
doE: 
16:	doEventQ 
17:	mvStack
18:	pushthis 
19:	rpushg 2
21:	rpushg 2
23:	invoke 96 0 0
29:	rpop 
30:	pushthis 
31:	rpushg 2
33:	pushc 2
35:	invoke 116 0 0
41:	rpop 
42:	pushText 1
44:	invoke 96 0 0
50:	rpop 
51:	pushthis 
52:	rpushg 1
54:	rpushg 1
56:	invoke 72 0 0
62:	rpop 
63:	pushText 16
65:	invoke 96 0 0
71:	rpop 
72:	pushthis 
73:	rpushg 1
75:	rpushg 1
77:	invoke 72 0 0
83:	rpop 
84:	pushthis 
85:	rpushg 2
87:	rpushg 2
89:	pushText 34
91:	invoke 96 0 0
97:	rpop 
98:	rtnEventQ 0
100:	setThisStack
101:	pushthis 
102:	rtn D


Class BETA 4 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 71 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class False 24 1
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


Class True 25 1
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


Class Object 36 1
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


Class core 54 1
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


Class Indexed 57 1
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


Class length 60 1
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


Class %if%then%%else% 65 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 66 2 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class _L 66 1
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
19:	invoke 118 0 1
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	sendv 2
31:	rpop 
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class cycle 67 1
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


Class %for%to%%do% 68 1
allocE:
1:	pushthis 
2:	storeg 2
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
20:	pushg 1
22:	storeg 3
24:	pushthis 
25:	invoke 69 0 1
31:	rpop 
32:	pushthis 
33:	innerP 2
35:	popThisObj
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class do 69 1
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


Class loop 70 1
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
29:	invoke 119 0 1
35:	rpop 
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class ascii 71 1
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


Class newline 72 1
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


Class putint 73 1
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
18:	allocIndexed 57 1
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
54:	invoke 74 0 0
60:	rpop 
61:	rtnEventQ 0
63:	setThisStack
64:	pushthis 
65:	rtn D


Class doit 74 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	invoke 75 2 1
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
31:	invoke 76 0 1
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class loop 75 1
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
84:	invoke 120 0 1
90:	rpop 
91:	rtnEventQ 0
93:	setThisStack
94:	pushthis 
95:	rtn D


Class %for%to%%do%#S#76 76 2
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
21:	toSuper 68
enterE: 
24:	rtnInner
doE: 
25:	mvStack
26:	rtnInner


Class LIB 77 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 78 2 1
13:	rpop 
14:	pushthis 
15:	invoke 85 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class BasicIO 78 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 84 2 1
13:	rpop 
14:	pushthis 
15:	invoke 110 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class Lock 79 1
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


Class init 80 1
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


Class get 81 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 82 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 82 1
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
48:	invoke 122 0 1
54:	rpop 
55:	rtnEventQ 0
57:	setThisStack
58:	pushthis 
59:	rtn D


Class free 83 1
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


Class keyboard 84 1
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


Class String 86 1
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


Class length 87 1
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


Class + 89 1
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
17:	invoke 87 0 0
23:	storeg 1
25:	pushthis 
26:	invoke 90 0 0
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	rpushg 3
39:	rtn D


Class doplus 90 1
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
25:	invoke 87 0 0
31:	+
32:	pushc 0
34:	pushc 1
36:	allocIndexed 57 1
40:	pushthis 
41:	rstoreg 2
43:	rtnEventQ 1
doE: 
45:	doEventQ 
46:	mvStack
47:	pushthis 
48:	invoke 91 0 1
54:	rpop 
55:	pushthis 
56:	invoke 92 0 1
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
23:	pushg 1
25:	toSuper 68
enterE: 
28:	rtnInner
doE: 
29:	mvStack
30:	rtnInner


Class %for%to%%do%#S#92 92 2
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
25:	invoke 87 0 0
31:	toSuper 68
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class asLowerCase 93 1
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


Class scan 94 1
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
13:	invoke 95 0 1
19:	rpop 
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class %for%to%%do%#S#95 95 2
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
21:	invoke 87 0 0
27:	toSuper 68
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class print 96 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 97 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %for%to%%do%#S#97 97 2
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
21:	invoke 87 0 0
27:	toSuper 68
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class = 98 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 99 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class loop 99 1
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
16:	invoke 87 0 0
22:	storeg 3
24:	pushthis 
25:	pushg 3
27:	pushthis 
28:	rpushg 1
30:	rpushg 2
32:	invoke 87 0 0
38:	ne 
39:	jmpFalse 50
42:	pushthis 
43:	invoke 127 0 1
49:	rpop 
50:	pushthis 
51:	rpushg 1
53:	pushthis 
54:	rpushg 1
56:	rpushg 1
58:	rpushg 1
60:	rpushg 1
62:	invoke 25 0 0
68:	storeg 1
70:	pushthis 
71:	invoke 100 0 1
77:	rpop 
78:	rtnEventQ 0
80:	setThisStack
81:	pushthis 
82:	rtn D


Class %for%to%%do%#S#100 100 2
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
25:	invoke 87 0 0
31:	toSuper 68
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class <= 101 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 102 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class loop 102 1
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
16:	invoke 87 0 0
22:	storeg 2
24:	pushthis 
25:	pushthis 
26:	rpushg 1
28:	rpushg 2
30:	invoke 87 0 0
36:	storeg 3
38:	pushthis 
39:	pushthis 
40:	pushg 2
42:	storeg 1
44:	pushthis 
45:	invoke 107 0 1
51:	rpop 
52:	pushthis 
53:	invoke 103 0 1
59:	rpop 
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


Class matchEq 103 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 104 2 1
13:	rpop 
14:	pushthis 
15:	invoke 105 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class loop 104 1
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
80:	invoke 129 0 1
86:	rpop 
87:	rtnEventQ 0
89:	setThisStack
90:	pushthis 
91:	rtn D


Class doit 105 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 106 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


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
35:	toSuper 65
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class %if%then%%else%#S#107 107 3
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
27:	toSuper 65
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class readLine 108 1
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
19:	allocIndexed 57 1
23:	pushthis 
24:	rstoreg 3
26:	pushthis 
27:	invoke 109 4 1
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


Class read 109 1
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
39:	invoke 134 0 1
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


Class screen 110 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 79 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 111 1
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
15:	invoke 81 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	rpushg 2
27:	invoke 80 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 2
39:	invoke 83 0 0
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class display 112 1
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
17:	invoke 81 0 1
23:	rpop 
24:	inner 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 2
31:	invoke 83 0 0
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class no 113 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 114 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class bmp 114 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 3 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class helloObject 115 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	pushText 1
13:	rswap 
14:	rstoreg 2
16:	pushthis 
17:	rpushg 2
19:	invoke 96 0 0
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	invoke 72 0 0
39:	rpop 
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class print 116 1
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
14:	invoke 117 0 0
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class loop 117 1
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
15:	pushc 0
17:	gt 
18:	jmpFalse 29
21:	pushthis 
22:	invoke 135 0 1
28:	rpop 
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class #S#118 118 1
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
18:	break 1 43
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class #S#119 119 1
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
41:	break 1 62
45:	rtnEventQ 0
47:	setThisStack
48:	pushthis 
49:	rtn D


Class #S#120 120 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 65
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#121 121 2
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


Class #S#122 122 1
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
16:	break 1 104
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class body#SB#123 123 2
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


Class body#SB#124 124 2
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


Class body#SB#125 125 2
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


Class body#SB#126 126 2
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


Class #S#127 127 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 117
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class body#SB#128 128 2
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
75:	invoke 136 0 1
81:	rpop 
82:	rtnEventQ 0
84:	setThisStack
85:	pushthis 
86:	rtn D


Class #S#129 129 1
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
30:	break 1 153
34:	rtnEventQ 0
36:	setThisStack
37:	pushthis 
38:	rtn D


Class thenPart#SB#130 130 2
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
46:	break 3 140
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class elsePart#SB#131 131 2
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
42:	break 3 140
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class thenPart#SB#132 132 2
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


Class elsePart#SB#133 133 2
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


Class #S#134 134 1
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


Class #S#135 135 1
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
19:	invoke 96 0 0
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	rpushg 1
35:	rpushg 1
37:	rpushg 1
39:	invoke 72 0 0
45:	rpop 
46:	pushthis 
47:	rpushg 1
49:	rpushg 1
51:	pushthis 
52:	rpushg 1
54:	rpushg 1
56:	pushg 1
58:	pushc 1
60:	-
61:	storeg 1
63:	break 1 143
67:	rtnEventQ 0
69:	setThisStack
70:	pushthis 
71:	rtn D


Class #S#136 136 1
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
34:	invoke 24 0 0
40:	storeg 1
42:	break 3 117
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class main 143 0
allocE:
1:	pushthis 
2:	invoke 1 0 1
8:	stop 


Class EventProcessor 144 0
allocE:
1:	stop 


Class ThreadStub 145 0
allocE:
doE: 
1:	mvStack
2:	call D
4:	stop 

