	-- QBETA
	-- Module:gen: 
	component Comp NoOfDescs: 195
	-- ConsRef:gen: BETAworld

	class Object 36 1
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
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L2:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BETAworld 1 1
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
	invoke 81 3 LIB
	rpop
	-- Module:gen: 
	-- ModuleItem:gen no
	-- ConsRef:gen: no
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 118 4 no
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

	class BETA 4 1
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
	-- pattern:gen: switch(V: ? integer)
	-- pattern:gen: %xswitch V: ? integer
	-- ConsRef:gen: ascii
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 75 2 ascii
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

	class LIB 81 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_dummy
	-- Module:gen: 
	-- ModuleItem:gen BasicIO
	-- ConsRef:gen: BasicIO
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 82 2 BasicIO
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
	-- ModuleItem:gen String
	-- ConsRef:gen: String
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 89 3 String
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

	class no 118 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: no_dummy
	-- Module:gen: 
	-- ModuleItem:gen bmp
	-- ConsRef:gen: bmp
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 119 2 bmp
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

	class False 24 1
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
	-- pattern:invoke: := V: ? Object
	storeg 1 B
 L12:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: B
	pushg 1 B
	rtn(D)
	end 1

	class True 25 1
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
	-- pattern:invoke: := V: ? Object
	storeg 1 B
 L14:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: B
	pushg 1 B
	rtn(D)
	end 1

	class immutable 46 1
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
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L16:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class core 54 1
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

	class Indexed 57 1
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

	class %if%then%%else% 65 1
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

	class cycle 67 1
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
	-- pattern:invoke: %inner P: ? Object
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
	-- pattern:invoke: %restart Obj: ? integer
	jmp L23
 L24:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do% 68 1
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
	-- VarRef:invoke: first
	pushg 1 first
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: do
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
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	inner  2
	rpopThisObj 
 L26:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class switch 71 1
	pushThis 
	storeg 1 V
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: V
	-- pattern:gen: case(x: ? integer)
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L27:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner switch:IS-empty: staticOff: 0
	-- Invocation:gen: %inner switch
	-- Invocation:loadOrigin: %inner switch
	-- Invocation:loadOrigin:scan: %inner switch
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner switch
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner switch
	-- KeyWord:invoke: 
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L28:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %xswitch 73 1
	pushThis 
	storeg 1 V
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: V
	-- pattern:gen: %scase x: ? integer
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L29:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner %xswitch :IS-empty: staticOff: 0
	-- Invocation:gen: %inner %xswitch 
	-- Invocation:loadOrigin: %inner %xswitch 
	-- Invocation:loadOrigin:scan: %inner %xswitch 
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner %xswitch 
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner %xswitch 
	-- KeyWord:invoke: 
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	inner  1
	rpopThisObj 
 L30:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class ascii 75 1
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
 L31:
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
	-- ConsRef:invoke: cr
	pushg 2 cr
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 newline
 L32:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class newline 76 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L33:
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
	-- pattern:invoke: put(ch: ? char)
	%put 2
 L34:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class putint 77 1
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
	-- pattern:invoke: Indexed(range: ? Integer,elm:< Object)
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
 L35:
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
	-- VarRef:invoke: V
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
	-- pattern:invoke: < V: ? integer -> B: ? Boolean
	51
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: isNeg
	pushg 3 isNeg
	jmpFalse L37
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
	-- VarRef:invoke: V
	pushg 1 V
	-- Binary:invoke: 
	-- pattern:invoke: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 V
 L37:
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
	-- pattern:invoke: doit
	invoke 78 0 doit
	rpop
 L36:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class BasicIO 82 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Lock
	-- ConsRef:gen: keyboard
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 88 2 keyboard
	rpop
	-- ConsRef:gen: screen
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 115 3 screen
	rpop
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

	class String 89 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: String
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

	class bmp 119 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: bmp_dummy
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen Program1
	-- ConsRef:gen: Program1
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 3 2 Program1
	rpop
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
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

	class length 60 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L44:
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
	-- pattern:invoke: %get inx: ? integer -> V: ? integer
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 res
 L45:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: res
	pushg 1 res
	rtn(D)
	end 1

	class _L 66 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_uglye
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L46:
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: cond
	pushg 1 cond
	jmpFalse L48
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 131 0 #S#131
	rpop
 L48:
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
	-- pattern:invoke: elsePart
	sendv 2 elsePart
	rpop
 L47:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class do 69 1
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
 L49:
	-- Include:gen: 
 L50:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class case 72 1
	pushThis 
	storeg 1 x
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: x
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L51:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if V = x %then% 
    %inner case
    %leave switch:IS-empty: staticOff: 0
	-- Invocation:gen: %if V = x %then% 
    %inner case
    %leave switch
	-- Invocation:loadOrigin: %if V = x %then% 
    %inner case
    %leave switch
	-- Invocation:loadOrigin:scan: %if V = x %then% 
    %inner case
    %leave switch
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if V = x %then% 
    %inner case
    %leave switch
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if V = x %then% 
    %inner case
    %leave switch
	-- KeyWord:invoke: 
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: V = x:IS-empty: staticOff: 0
	-- Invocation:gen: V = x
	-- Invocation:loadOrigin: V = x
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 case:origin
	-- next not assign: = x :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: = x
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= x
	-- ObjectGenerator:gen: super: x:IS-empty: staticOff: 0
	-- Invocation:gen: x
	-- Invocation:loadOrigin: x
	-- Invocation:loadOrigin:scan: x
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: x
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: x
	pushg 1 x
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L53
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 133 0 #S#133
	rpop
 L53:
 L52:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %scase 74 1
	pushThis 
	storeg 1 x
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: x
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L54:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if V = x %then% 
    %inner %scase 
    %leave %xswitch :IS-empty: staticOff: 0
	-- Invocation:gen: %if V = x %then% 
    %inner %scase 
    %leave %xswitch 
	-- Invocation:loadOrigin: %if V = x %then% 
    %inner %scase 
    %leave %xswitch 
	-- Invocation:loadOrigin:scan: %if V = x %then% 
    %inner %scase 
    %leave %xswitch 
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if V = x %then% 
    %inner %scase 
    %leave %xswitch 
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if V = x %then% 
    %inner %scase 
    %leave %xswitch 
	-- KeyWord:invoke: 
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: V = x:IS-empty: staticOff: 0
	-- Invocation:gen: V = x
	-- Invocation:loadOrigin: V = x
	-- Invocation:loadOrigin:scan: V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: V
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 %scase:origin
	-- next not assign: = x :E: V
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: = x
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= x
	-- ObjectGenerator:gen: super: x:IS-empty: staticOff: 0
	-- Invocation:gen: x
	-- Invocation:loadOrigin: x
	-- Invocation:loadOrigin:scan: x
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: x
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: x
	pushg 1 x
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L56
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 134 0 #S#134
	rpop
 L56:
 L55:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 78 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 79 2 loop
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L57:
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: isNeg
	pushg 3 isNeg
	jmpFalse L59
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
	-- pattern:invoke: put(ch: ? char)
	%put 2
 L59:
	-- ObjectGenerator:gen: super: %for 1 %to% L %do% 
    i: ? integer
    i := L + 1 - inx
    put('0' + D.%get i):IS-empty: staticOff: 0
	pushThis 
	invoke 80 0 %for%to%%do%#S#80
	rpop
 L58:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Lock 83 1
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
 L60:
	-- Include:gen: 
 L61:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class keyboard 88 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: readLine -> M: ? LIB.String.String
	rtnEventQ 0
	DO:
	mvStack 
 L62:
	-- Include:gen: 
 L63:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class screen 115 1
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
	-- pattern:invoke: Lock
	invoke 83 2 Lock
	rpop
	-- pattern:gen: init
	-- pattern:gen: display
	rtnEventQ 0
	DO:
	mvStack 
 L64:
	-- Include:gen: 
 L65:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class String 90 1
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
 L66:
	-- Include:gen: 
 L67:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class Program1 3 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: mood
	-- pattern:gen: Array(range: ? integer)
	-- pattern:gen: tilfeldigx(min: ? integer,max: ? integer) -> r: ? Integer
	-- pattern:gen: tilfeldig(min: ? integer,max: ? integer) -> r: ? Integer
	-- ConsRef:gen: antall
	-- ObjectGenerator:gen: super: Array(6):IS-empty: staticOff: 2
	-- Invocation:gen: Array(6)
	-- Invocation:loadOrigin: Array(6)
	-- Invocation:loadOrigin:scan: Array(6)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Array(6)
	-- on : 0
	-- AdjustOrigin: 0
	-- Function:loadArgs: 
	-- pattern:loadArgs: Array(range: ? integer)Array(6)
	-- ObjectGenerator:gen: super: 6:IS-empty: staticOff: 0
	-- Invocation:gen: 6
	-- Invocation:loadOrigin: 6
	-- Invocation:loadOrigin:scan: 6
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 6
	-- Function:invoke: 
	-- pattern:invoke: Array(range: ? integer)
	invoke 120 2 Array
	rpop
	-- VarRef:gen: eyes
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L68:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: mood := 0:IS-empty: staticOff: 0
	-- Invocation:gen: mood := 0
	-- Invocation:loadOrigin: mood := 0
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
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
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
	-- ObjectGenerator:gen: super: %for 1 %to% 6 %do% 
    antall.put(inx) := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 128 0 %for%to%%do%#S#128
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% 1000 %do% 
    
    eyes := tilfeldig(1,6)
    antall.put(eyes) := antall.get(eyes) + 1:IS-empty: staticOff: 0
	pushThis 
	invoke 129 0 %for%to%%do%#S#129
	rpop
	-- ObjectGenerator:gen: super: %for 1 %to% 6 %do% 
    putint(antall.get(inx))
    put(' '):IS-empty: staticOff: 0
	pushThis 
	invoke 130 0 %for%to%%do%#S#130
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
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: newlinenewline
	-- Unary:invoke: 
	-- pattern:invoke: newline
	invoke 76 0 newline
	rpop
 L69:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#131 131 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L70:
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
	rpushg 1 #S#131:origin
	rpushg 1 _L:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: thenPartthenPart
	-- Unary:invoke: 
	-- pattern:invoke: thenPart
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
	-- pattern:invoke: %leave Obj: ? integer
	break 1 47
 L71:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 70 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L72:
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: inx
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
	-- VarRef:invoke: last
	pushg 2 last
	-- Binary:invoke: 
	-- pattern:invoke: <= V: ? integer -> B: ? Boolean
	52
	jmpFalse L74
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 132 0 #S#132
	rpop
 L74:
 L73:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#133 133 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L75:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner case:IS-empty: staticOff: 0
	-- Invocation:gen: %inner case
	-- Invocation:loadOrigin: %inner case
	-- Invocation:loadOrigin:scan: %inner case
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner case
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner case
	-- KeyWord:invoke: 
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	rpushg 1 #S#133:origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %leave switch:IS-empty: staticOff: 0
	-- Invocation:gen: %leave switch
	-- Invocation:loadOrigin: %leave switch
	-- Invocation:loadOrigin:scan: %leave switch
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave switch
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave switch
	-- KeyWord:invoke: 
	-- pattern:invoke: %leave Obj: ? integer
	break 2 28
 L76:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#134 134 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L77:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %inner %scase :IS-empty: staticOff: 0
	-- Invocation:gen: %inner %scase 
	-- Invocation:loadOrigin: %inner %scase 
	-- Invocation:loadOrigin:scan: %inner %scase 
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %inner %scase 
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %inner P: ? Object%inner %scase 
	-- KeyWord:invoke: 
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	rpushg 1 #S#134:origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: %leave %xswitch :IS-empty: staticOff: 0
	-- Invocation:gen: %leave %xswitch 
	-- Invocation:loadOrigin: %leave %xswitch 
	-- Invocation:loadOrigin:scan: %leave %xswitch 
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %leave %xswitch 
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %leave Obj: ? integer%leave %xswitch 
	-- KeyWord:invoke: 
	-- pattern:invoke: %leave Obj: ? integer
	break 2 30
 L78:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 79 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L79:
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
	-- VarRef:invoke: L
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- ConsRef:invoke: D
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
	-- VarRef:invoke: V
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
	-- pattern:invoke: /% V: ? integer -> R: ? integer
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
	-- VarRef:invoke: L
	pushg 2 L
	-- KeyWord:invoke: 
	-- pattern:invoke: %put V: ? elm %at% inx: ? integer
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
	-- VarRef:invoke: V
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
	-- pattern:invoke: // V: ? integer -> B: ? Integer
	68
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: V
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
	-- pattern:invoke: > V: ? integer -> B: ? Boolean
	gt
	jmpFalse L81
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 135 0 #S#135
	rpop
 L81:
 L80:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#80 80 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=80
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
	-- VarRef:invoke: L
	pushg 2 L
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L82:
 L83:
	rtnInner
	end 1

	class init 84 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L84:
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
	-- pattern:invoke: := V: ? Object
	storeg 2 M
 L85:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class get 85 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: res
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 86 2 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L86:
	-- Include:gen: 
 L87:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class free 87 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L88:
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
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: enable
	%enable 12
 L89:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class readLine 113 1
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
	-- pattern:invoke: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 57 StaticRep asObj
	pushThis 
	rstoreg 3 indexed
	-- ConsRef:gen: read
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 114 4 read
	rpop
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L90:
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
	-- ConsRef:invoke: msg
	rpushg 3 msg
	-- Invocation:loadOrigin:scan: asString
	-- Unary:loadArgs: 
	-- pattern:loadArgs: asString -> S: ? ObjectasString
	-- Unary:invoke: 
	-- pattern:invoke: asString -> S: ? Object
	%asString 118
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	rswap
	rstoreg 2 M
 L91:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: M
	rpushg 2 M
	rtn(D)
	end 1

	class init 116 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L92:
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
	-- ConsRef:invoke: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:invoke: get
	invoke 85 0 get
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
	-- ConsRef:invoke: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: init
	-- Unary:loadArgs: 
	-- pattern:loadArgs: initinit
	-- Unary:invoke: 
	-- pattern:invoke: init
	invoke 84 0 init
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
	-- ConsRef:invoke: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:invoke: free
	invoke 87 0 free
	rpop
 L93:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class display 117 1
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
 L94:
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
	-- ConsRef:invoke: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: get
	-- Unary:loadArgs: 
	-- pattern:loadArgs: getget
	-- Unary:invoke: 
	-- pattern:invoke: get
	invoke 85 0 get
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
	-- pattern:invoke: inner
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
	-- ConsRef:invoke: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: free
	-- Unary:loadArgs: 
	-- pattern:loadArgs: freefree
	-- Unary:invoke: 
	-- pattern:invoke: free
	invoke 87 0 free
	rpop
 L95:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class length 91 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L96:
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
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 V
 L97:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: V
	pushg 1 V
	rtn(D)
	end 1

	class + 93 1
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
 L98:
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
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: doplus
	invoke 94 0 doplus
	rpop
 L99:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: V
	rpushg 3 V
	rtn(D)
	end 1

	class asLowerCase 97 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 0
	DO:
	mvStack 
 L100:
	-- Include:gen: 
 L101:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: T
	rpushg 2 T
	rtn(D)
	end 1

	class scan 98 1
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
 L102:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    current := %get inx
    %inner scan:IS-empty: staticOff: 0
	pushThis 
	invoke 99 0 %for%to%%do%#S#99
	rpop
 L103:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class print 100 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L104:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %for 1 %to% length %do% 
    put(%get inx):IS-empty: staticOff: 0
	pushThis 
	invoke 101 0 %for%to%%do%#S#101
	rpop
 L105:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class = 102 1
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
	invoke 103 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L106:
	-- Include:gen: 
 L107:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: B
	pushg 1 B
	rtn(D)
	end 1

	class <= 105 1
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
	invoke 106 3 loop
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L108:
	-- Include:gen: 
 L109:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: B
	pushg 1 B
	rtn(D)
	end 1

	class Array 120 1
	pushThis 
	storeg 1 range
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: range
	-- ConsRef:gen: rep
	-- ObjectGenerator:gen: super: Indexed(range,integer):IS-empty: staticOff: 2
	-- Invocation:gen: Indexed(range,integer)
	-- Invocation:loadOrigin: Indexed(range,integer)
	-- Invocation:loadOrigin:scan: Indexed(range,integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: Indexed(range,integer)
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 Array:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: Indexed(range: ? Integer,elm:< Object)Indexed(range,integer)
	-- ObjectGenerator:gen: super: range:IS-empty: staticOff: 0
	-- Invocation:gen: range
	-- Invocation:loadOrigin: range
	-- Invocation:loadOrigin:scan: range
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: range
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: range
	pushg 1 range
	-- Function:invoke: 
	-- pattern:invoke: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 57 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	-- pattern:gen: put(ix: ? integer)
	-- pattern:gen: get(ix: ? integer) -> res: ? integer
	rtnEventQ 0
	DO:
	mvStack 
 L110:
	-- Include:gen: 
 L111:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class tilfeldigx 124 1
	pushThis 
	storeg 2 max
	pushThis 
	storeg 1 min
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: min
	-- VarRef:gen: max
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L112:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 125 0 %if%then%%else%#S#125
	rpop
 L113:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: r
	pushg 3 r
	rtn(D)
	end 1

	class tilfeldig 126 1
	pushThis 
	storeg 2 max
	pushThis 
	storeg 1 min
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: min
	-- VarRef:gen: max
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L114:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 127 0 %if%then%%else%#S#127
	rpop
 L115:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: r
	pushg 3 r
	rtn(D)
	end 1

	class %for%to%%do%#S#128 128 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=128
	-- Invocation:loadOrigin: %for 1 %to% 6 %do% 
    antall.put(inx) := 0
	-- Invocation:loadOrigin:scan: %for 1 %to% 6 %do% 
    antall.put(inx) := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% 6 %do% 
    antall.put(inx) := 0
	-- on : 2
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% 6 %do% 
    antall.put(inx) := 0
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: 6:IS-empty: staticOff: 0
	-- Invocation:gen: 6
	-- Invocation:loadOrigin: 6
	-- Invocation:loadOrigin:scan: 6
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 6
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L116:
 L117:
	rtnInner
	end 1

	class %for%to%%do%#S#129 129 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=129
	-- Invocation:loadOrigin: %for 1 %to% 1000 %do% 
    
    eyes := tilfeldig(1,6)
    antall.put(eyes) := antall.get(eyes) + 1
	-- Invocation:loadOrigin:scan: %for 1 %to% 1000 %do% 
    
    eyes := tilfeldig(1,6)
    antall.put(eyes) := antall.get(eyes) + 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% 1000 %do% 
    
    eyes := tilfeldig(1,6)
    antall.put(eyes) := antall.get(eyes) + 1
	-- on : 2
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% 1000 %do% 
    
    eyes := tilfeldig(1,6)
    antall.put(eyes) := antall.get(eyes) + 1
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: 1000:IS-empty: staticOff: 0
	-- Invocation:gen: 1000
	-- Invocation:loadOrigin: 1000
	-- Invocation:loadOrigin:scan: 1000
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1000
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L118:
 L119:
	rtnInner
	end 1

	class %for%to%%do%#S#130 130 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=130
	-- Invocation:loadOrigin: %for 1 %to% 6 %do% 
    putint(antall.get(inx))
    put(' ')
	-- Invocation:loadOrigin:scan: %for 1 %to% 6 %do% 
    putint(antall.get(inx))
    put(' ')
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %for 1 %to% 6 %do% 
    putint(antall.get(inx))
    put(' ')
	-- on : 2
	-- AdjustOrigin: 2
	rpushg 2 origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %for first: ? integer %to% last: ? integer %do% body:< Object%for 1 %to% 6 %do% 
    putint(antall.get(inx))
    put(' ')
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: 6:IS-empty: staticOff: 0
	-- Invocation:gen: 6
	-- Invocation:loadOrigin: 6
	-- Invocation:loadOrigin:scan: 6
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 6
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L120:
 L121:
	rtnInner
	end 1

	class #S#132 132 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L122:
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
	rpushg 1 #S#132:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: bodybody
	-- Unary:invoke: 
	-- pattern:invoke: body
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
	rpushg 1 #S#132:origin
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
	rpushg 1 #S#132:origin
	rpushg 1 loop:origin
	rpushg 1 do:origin
	-- next not assign: + 1 :E: inx
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %restart Obj: ? integer
	break 1 72
 L123:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#135 135 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L124:
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
	-- pattern:invoke: %restart Obj: ? integer
	break 1 79
 L125:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#136 136 2
	rstore 2 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: i
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L126:
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
	rpushg 2 body#S#136:origin
	rpushg 2 %for%to%%do%#S#80:origin
	rpushg 1 doit:origin
	-- next not assign: + 1 - inx :E: L
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L
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
	rpushg 2 body#S#136:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- Binary:invoke: 
	-- pattern:invoke: - V: ? integer -> R: ? integer
	minus
	-- Binary:invoke: 
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	rpushg 2 body#S#136:origin
	rpushg 2 %for%to%%do%#S#80:origin
	rpushg 1 doit:origin
	-- next not assign: %get i :E: D
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: D
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
	-- VarRef:invoke: i
	pushg 1 i
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> V: ? integer
	-- integer
	-- value
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: + V: ? char -> R: ? char
	plus
	-- Function:invoke: 
	-- pattern:invoke: put(ch: ? char)
	%put 2
 L127:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 86 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L128:
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
	-- pattern:invoke: disable
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
	-- pattern:invoke: := V: ? Object
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
	-- VarRef:invoke: M
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
	-- pattern:invoke: cmpAndSwap(V: ? integer) -> res: ? integer
	swap
	%cmpAndSwap 14
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: res
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L130
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 137 0 #S#137
	rpop
 L130:
 L129:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class read 114 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: ch
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L131:
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
	-- pattern:invoke: _iget -> ch: ? char
	invokeExternal 4
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- VarRef:invoke: ch
	pushg 1 ch
	-- Function:invoke: 
	-- pattern:invoke: put(ch: ? char)
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: ch
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
	-- pattern:invoke: = V: ? char -> B: ? Boolean
	eq
	jmpFalse L133
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 151 0 #S#151
	rpop
 L133:
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
	-- VarRef:invoke: inx
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- ConsRef:invoke: msg
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
	-- VarRef:invoke: ch
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
	-- VarRef:invoke: inx
	pushg 1 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %put V: ? elm %at% inx: ? integer
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
	-- pattern:invoke: %restart Obj: ? integer
	jmp L131
 L132:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doplus 94 1
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
	-- VarRef:invoke: L
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
	-- VarRef:invoke: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Function:invoke: 
	-- pattern:invoke: Indexed(range: ? Integer,elm:< Object)
	pushc 0
	pushc 1
	allocIndexed 57 StaticRep asObj
	pushThis 
	rstoreg 2 indexed
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L134:
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
	-- ConsRef:invoke: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: asString
	-- Unary:loadArgs: 
	-- pattern:loadArgs: asString -> S: ? ObjectasString
	-- Unary:invoke: 
	-- pattern:invoke: asString -> S: ? Object
	%asString 118
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	rswap
	rstoreg 3 V
 L135:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#99 99 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=99
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
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L136:
 L137:
	rtnInner
	end 1

	class %for%to%%do%#S#101 101 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=101
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
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L138:
 L139:
	rtnInner
	end 1

	class loop 103 1
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
 L140:
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
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: L
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
	-- VarRef:invoke: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:invoke: <> V: ? integer -> B: ? Boolean
	55
	jmpFalse L142
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 142 0 #S#142
	rpop
 L142:
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
	-- pattern:invoke: True -> B: ? Boolean
	invoke 25 0 True
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
 L141:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 106 1
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
 L143:
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
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- VarRef:invoke: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 L2
	-- ObjectGenerator:gen: super: %if L1 < L2 %then% 
    L := L1 %else% 
    L := L2:IS-empty: staticOff: 0
	pushThis 
	invoke 112 0 %if%then%%else%#S#112
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
	-- pattern:invoke: matchEq
	invoke 107 0 matchEq
	rpop
 L144:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class put 121 1
	pushThis 
	storeg 1 ix
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: ix
	-- pattern:gen: := V: ? integer
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

	class get 123 1
	pushThis 
	storeg 1 ix
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: ix
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L147:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: res := rep.%get ix:IS-empty: staticOff: 0
	-- Invocation:gen: res := rep.%get ix
	-- Invocation:loadOrigin: res := rep.%get ix
	-- Invocation:loadOrigin:scan: res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: res
	-- on : 0
	-- AdjustOrigin: 0
	-- Invocation:loadOrigin:scan: := rep.%get ix
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= rep.%get ix
	-- ObjectGenerator:gen: super: rep.%get ix:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%get ix
	-- Invocation:loadOrigin: rep.%get ix
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 get:origin
	-- next not assign: %get ix :E: rep
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %get ix
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %get inx: ? integer -> V: ? integer%get ix
	-- ObjectGenerator:gen: super: ix:IS-empty: staticOff: 0
	-- Invocation:gen: ix
	-- Invocation:loadOrigin: ix
	-- Invocation:loadOrigin:scan: ix
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ix
	-- on : 0
	-- AdjustOrigin: 0
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: ix
	pushg 1 ix
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> V: ? integer
	-- integer
	-- value
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 2 res
 L148:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:invoke: res
	pushg 2 res
	rtn(D)
	end 1

	class %if%then%%else%#S#125 125 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- on : 3
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 1 tilfeldigx:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 0:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 0
	-- Invocation:loadOrigin: mood = 0
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: = 0 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L149:
 L150:
	rtnInner
	end 1

	class %if%then%%else%#S#127 127 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- on : 3
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 1 tilfeldig:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 0 %then% 
    r := 1
    mood := mood + 1 %else% 
    %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 0:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 0
	-- Invocation:loadOrigin: mood = 0
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 1 tilfeldig:origin
	-- next not assign: = 0 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L151:
 L152:
	rtnInner
	end 1

	class body#SB#158 158 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L153:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: antall.put(inx) := 0:IS-empty: staticOff: 0
	-- Invocation:gen: antall.put(inx) := 0
	-- Invocation:loadOrigin: antall.put(inx) := 0
	-- Invocation:loadOrigin:scan: antall
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: antall
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#158:origin
	rpushg 2 %for%to%%do%#S#128:origin
	-- next not assign: put(inx) :E: antall
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: antall
	rpushg 2 antall
	-- Invocation:loadOrigin:scan: put(inx)
	-- next not assign: := 0 :E: put(inx)
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ix: ? integer)put(inx)
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#158:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- Function:invoke: 
	-- pattern:invoke: put(ix: ? integer)
	invoke 121 0 put
	-- Invocation:loadOrigin:scan: := 0
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? integer:= 0
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
	-- pattern:invoke: := V: ? integer
	invoke 122 0 :=
	rpop
 L154:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#159 159 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L155:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: eyes := tilfeldig(1,6):IS-empty: staticOff: 0
	-- Invocation:gen: eyes := tilfeldig(1,6)
	-- Invocation:loadOrigin: eyes := tilfeldig(1,6)
	-- Invocation:loadOrigin:scan: eyes
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: eyes
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#159:origin
	rpushg 2 %for%to%%do%#S#129:origin
	-- Invocation:loadOrigin:scan: := tilfeldig(1,6)
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= tilfeldig(1,6)
	-- ObjectGenerator:gen: super: tilfeldig(1,6):IS-empty: staticOff: 0
	-- Invocation:gen: tilfeldig(1,6)
	-- Invocation:loadOrigin: tilfeldig(1,6)
	-- Invocation:loadOrigin:scan: tilfeldig(1,6)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: tilfeldig(1,6)
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#159:origin
	rpushg 2 %for%to%%do%#S#129:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: tilfeldig(min: ? integer,max: ? integer) -> r: ? Integertilfeldig(1,6)
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: 6:IS-empty: staticOff: 0
	-- Invocation:gen: 6
	-- Invocation:loadOrigin: 6
	-- Invocation:loadOrigin:scan: 6
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 6
	-- Function:invoke: 
	-- pattern:invoke: tilfeldig(min: ? integer,max: ? integer) -> r: ? Integer
	invoke 126 0 tilfeldig
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 2 eyes
	-- ObjectGenerator:gen: super: antall.put(eyes) := antall.get(eyes) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: antall.put(eyes) := antall.get(eyes) + 1
	-- Invocation:loadOrigin: antall.put(eyes) := antall.get(eyes) + 1
	-- Invocation:loadOrigin:scan: antall
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: antall
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#159:origin
	rpushg 2 %for%to%%do%#S#129:origin
	-- next not assign: put(eyes) :E: antall
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: antall
	rpushg 2 antall
	-- Invocation:loadOrigin:scan: put(eyes)
	-- next not assign: := antall.get(eyes) + 1 :E: put(eyes)
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ix: ? integer)put(eyes)
	-- ObjectGenerator:gen: super: eyes:IS-empty: staticOff: 0
	-- Invocation:gen: eyes
	-- Invocation:loadOrigin: eyes
	-- Invocation:loadOrigin:scan: eyes
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: eyes
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#159:origin
	rpushg 2 %for%to%%do%#S#129:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: eyes
	pushg 2 eyes
	-- Function:invoke: 
	-- pattern:invoke: put(ix: ? integer)
	invoke 121 0 put
	-- Invocation:loadOrigin:scan: := antall.get(eyes) + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? integer:= antall.get(eyes) + 1
	-- ObjectGenerator:gen: super: antall.get(eyes) + 1:IS-empty: staticOff: 0
	-- Invocation:gen: antall.get(eyes) + 1
	-- Invocation:loadOrigin: antall.get(eyes) + 1
	-- Invocation:loadOrigin:scan: antall
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: antall
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#159:origin
	rpushg 2 %for%to%%do%#S#129:origin
	-- next not assign: get(eyes) :E: antall
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: antall
	rpushg 2 antall
	-- Invocation:loadOrigin:scan: get(eyes)
	-- next not assign: + 1 :E: get(eyes)
	-- Function:loadArgs: 
	-- pattern:loadArgs: get(ix: ? integer) -> res: ? integerget(eyes)
	-- ObjectGenerator:gen: super: eyes:IS-empty: staticOff: 0
	-- Invocation:gen: eyes
	-- Invocation:loadOrigin: eyes
	-- Invocation:loadOrigin:scan: eyes
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: eyes
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#159:origin
	rpushg 2 %for%to%%do%#S#129:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: eyes
	pushg 2 eyes
	-- Function:invoke: 
	-- pattern:invoke: get(ix: ? integer) -> res: ? integer
	invoke 123 0 get
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? integer
	invoke 122 0 :=
	rpop
 L156:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#160 160 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L157:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: putint(antall.get(inx)):IS-empty: staticOff: 0
	-- Invocation:gen: putint(antall.get(inx))
	-- Invocation:loadOrigin: putint(antall.get(inx))
	-- Invocation:loadOrigin:scan: putint(antall.get(inx))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: putint(antall.get(inx))
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 body#S#160:origin
	rpushg 2 %for%to%%do%#S#130:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Function:loadArgs: 
	-- pattern:loadArgs: putint(V: ? integer)putint(antall.get(inx))
	-- ObjectGenerator:gen: super: antall.get(inx):IS-empty: staticOff: 0
	-- Invocation:gen: antall.get(inx)
	-- Invocation:loadOrigin: antall.get(inx)
	-- Invocation:loadOrigin:scan: antall
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: antall
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#160:origin
	rpushg 2 %for%to%%do%#S#130:origin
	-- next not assign: get(inx) :E: antall
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: antall
	rpushg 2 antall
	-- Invocation:loadOrigin:scan: get(inx)
	-- Function:loadArgs: 
	-- pattern:loadArgs: get(ix: ? integer) -> res: ? integerget(inx)
	-- ObjectGenerator:gen: super: inx:IS-empty: staticOff: 0
	-- Invocation:gen: inx
	-- Invocation:loadOrigin: inx
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 2 body#S#160:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- Function:invoke: 
	-- pattern:invoke: get(ix: ? integer) -> res: ? integer
	invoke 123 0 get
	-- Function:invoke: 
	-- pattern:invoke: putint(V: ? integer)
	invoke 77 0 putint
	rpop
	-- ObjectGenerator:gen: super: put(' '):IS-empty: staticOff: 0
	-- Invocation:gen: put(' ')
	-- Invocation:loadOrigin: put(' ')
	-- Invocation:loadOrigin:scan: put(' ')
	-- Function:pushThis: 
	-- Function:loadOrigin: put(' ')
	-- Function:loadArgs: 
	-- pattern:loadArgs: put(ch: ? char)put(' ')
	-- ObjectGenerator:gen: super: ' ':IS-empty: staticOff: 0
	-- Invocation:gen: ' '
	-- Invocation:loadOrigin: ' '
	-- Invocation:loadOrigin:scan: ' '
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 32
	-- Function:invoke: 
	-- pattern:invoke: put(ch: ? char)
	%put 2
 L158:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#137 137 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L159:
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
	-- pattern:invoke: enable
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
	-- pattern:invoke: sleep(V: ? integer)
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
	-- pattern:invoke: %restart Obj: ? integer
	break 1 128
 L160:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#151 151 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L161:
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
	-- pattern:invoke: %leave Obj: ? integer
	break 1 132
 L162:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#95 95 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=95
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
	-- VarRef:invoke: L
	pushg 1 L
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L163:
 L164:
	rtnInner
	end 1

	class %for%to%%do%#S#96 96 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=96
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
	-- VarRef:invoke: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: length
	-- Unary:loadArgs: 
	-- pattern:loadArgs: length -> V: ? integerlength
	-- Unary:invoke: 
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L165:
 L166:
	rtnInner
	end 1

	class body#SB#140 140 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L167:
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
	rpushg 2 body#S#140:origin
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
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 body#S#140:origin
	rpushg 2 %for%to%%do%#S#99:origin
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
	rpushg 2 body#S#140:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %inner P: ? Object
	pushThis 
	rpushg 2 body#S#140:origin
	rpushg 2 %for%to%%do%#S#99:origin
	inner  1
	rpopThisObj 
 L168:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#141 141 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L169:
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
	rpushg 2 body#S#141:origin
	rpushg 2 %for%to%%do%#S#101:origin
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
	rpushg 2 body#S#141:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:invoke: put(ch: ? char)
	%put 2
 L170:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#142 142 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L171:
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
	-- pattern:invoke: %leave Obj: ? integer
	break 1 141
 L172:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %for%to%%do%#S#104 104 2
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:36 2:0 3:0 4:0
	-- vdtAdd: inx=2 descInx=104
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
	-- pattern:invoke: length -> V: ? integer
	invoke 91 0 length
	topSuper  68
	rtnInner
	DO:
	mvStack 
 L173:
 L174:
	rtnInner
	end 1

	class matchEq 107 1
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: inx
	-- VarRef:gen: c1
	-- VarRef:gen: c2
	-- ConsRef:gen: isEmpty
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 108 2 isEmpty
	rpop
	-- ConsRef:gen: loop
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 109 3 loop
	rpop
	-- ConsRef:gen: doit
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 110 4 doit
	rpop
	rtnEventQ 0
	DO:
	mvStack 
 L175:
	-- Include:gen: 
 L176:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#112 112 3
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
	-- VarRef:invoke: L1
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
	-- VarRef:invoke: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:invoke: < V: ? integer -> B: ? Boolean
	51
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L177:
 L178:
	rtnInner
	end 1

	class := 122 1
	pushThis 
	storeg 1 V
	rstore 1 origin
	allocEventQ
	mvStack 
	-- Signature:gen: 
	-- Arguments:gen: 
	-- VarRef:gen: V
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L179:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: rep.%put V %at% ix:IS-empty: staticOff: 0
	-- Invocation:gen: rep.%put V %at% ix
	-- Invocation:loadOrigin: rep.%put V %at% ix
	-- Invocation:loadOrigin:scan: rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: rep
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 :=:origin
	rpushg 1 put:origin
	-- next not assign: %put V %at% ix :E: rep
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: %put V %at% ix
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %put V: ? elm %at% inx: ? integer%put V %at% ix
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
	-- VarRef:invoke: V
	pushg 1 V
	-- ObjectGenerator:gen: super: ix:IS-empty: staticOff: 0
	-- Invocation:gen: ix
	-- Invocation:loadOrigin: ix
	-- Invocation:loadOrigin:scan: ix
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: ix
	-- on : 1
	-- AdjustOrigin: 0
	rpushg 1 :=:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: ix
	pushg 1 ix
	-- KeyWord:invoke: 
	-- pattern:invoke: %put V: ? elm %at% inx: ? integer
	-- integer
	-- basic
	xstoreg 1 inx
 L180:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#152 152 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L181:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 1:IS-empty: staticOff: 0
	-- Invocation:gen: r := 1
	-- Invocation:loadOrigin: r := 1
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#152:origin
	rpushg 3 %if%then%%else%#S#125:origin
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
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#152:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#152:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L182:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#153 153 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L183:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 154 0 %if%then%%else%#S#154
	rpop
 L184:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#155 155 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L185:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 1:IS-empty: staticOff: 0
	-- Invocation:gen: r := 1
	-- Invocation:loadOrigin: r := 1
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#155:origin
	rpushg 3 %if%then%%else%#S#127:origin
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
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#155:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#155:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L186:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#156 156 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L187:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 157 0 %if%then%%else%#S#157
	rpop
 L188:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#138 138 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L189:
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
	rpushg 2 body#S#138:origin
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
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 body#S#138:origin
	rpushg 2 %for%to%%do%#S#95:origin
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
	rpushg 2 body#S#138:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	rpushg 2 body#S#138:origin
	rpushg 2 %for%to%%do%#S#95:origin
	-- next not assign: %put e %at% inx :E: T
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: T
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
	rpushg 2 body#S#138:origin
	rpushg 2 %for%to%%do%#S#95:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: e
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
	rpushg 2 body#S#138:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %put V: ? elm %at% inx: ? integer
	-- Integer
	-- basic
	xstoreg 1 inx
 L190:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#139 139 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L191:
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
	rpushg 2 body#S#139:origin
	rpushg 2 %for%to%%do%#S#96:origin
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
	rpushg 2 body#S#139:origin
	rpushg 2 %for%to%%do%#S#96:origin
	rpushg 1 doplus:origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: S
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
	rpushg 2 body#S#139:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	rpushg 2 body#S#139:origin
	rpushg 2 %for%to%%do%#S#96:origin
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
	rpushg 2 body#S#139:origin
	rpushg 2 %for%to%%do%#S#96:origin
	rpushg 1 doplus:origin
	-- next not assign: + inx :E: L
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L
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
	rpushg 2 body#S#139:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- Binary:invoke: 
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	rpushg 2 body#S#139:origin
	rpushg 2 %for%to%%do%#S#96:origin
	-- next not assign: %put e %at% i :E: T
	-- Unary:loadArgs: 
	-- ConsRef:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:invoke: T
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
	rpushg 2 body#S#139:origin
	rpushg 2 %for%to%%do%#S#96:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: e
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
	rpushg 2 body#S#139:origin
	rpushg 2 %for%to%%do%#S#96:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: i
	pushg 2 i
	-- KeyWord:invoke: 
	-- pattern:invoke: %put V: ? elm %at% inx: ? integer
	-- Integer
	-- basic
	xstoreg 1 inx
 L192:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#143 143 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L193:
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
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
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
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
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
	rpushg 2 body#S#143:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
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
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
	rpushg 1 loop:origin
	-- next not assign: %get inx :E: S
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: S
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
	rpushg 2 body#S#143:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
	pushg 3 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: c1 <> c2:IS-empty: staticOff: 0
	-- Invocation:gen: c1 <> c2
	-- Invocation:loadOrigin: c1 <> c2
	-- Invocation:loadOrigin:scan: c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: c1
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
	-- next not assign: <> c2 :E: c1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: c1
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
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: c2
	pushg 2 c2
	-- Binary:invoke: 
	-- pattern:invoke: <> V: ? char -> B: ? Boolean
	55
	jmpFalse L195
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 161 0 #S#161
	rpop
 L195:
 L194:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class isEmpty 108 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L196:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if L1 = 0 %then% 
    B := L1 = L2
    %leave matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: %if L1 = 0 %then% 
    B := L1 = L2
    %leave matchEq
	-- Invocation:loadOrigin: %if L1 = 0 %then% 
    B := L1 = L2
    %leave matchEq
	-- Invocation:loadOrigin:scan: %if L1 = 0 %then% 
    B := L1 = L2
    %leave matchEq
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if L1 = 0 %then% 
    B := L1 = L2
    %leave matchEq
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if L1 = 0 %then% 
    B := L1 = L2
    %leave matchEq
	-- KeyWord:invoke: 
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: L1 = 0:IS-empty: staticOff: 0
	-- Invocation:gen: L1 = 0
	-- Invocation:loadOrigin: L1 = 0
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 isEmpty:origin
	rpushg 1 matchEq:origin
	-- next not assign: = 0 :E: L1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L1
	pushg 2 L1
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L198
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 144 0 #S#144
	rpop
 L198:
	-- ObjectGenerator:gen: super: %if L2 = 0 %then% 
    B := true
    %leave matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: %if L2 = 0 %then% 
    B := true
    %leave matchEq
	-- Invocation:loadOrigin: %if L2 = 0 %then% 
    B := true
    %leave matchEq
	-- Invocation:loadOrigin:scan: %if L2 = 0 %then% 
    B := true
    %leave matchEq
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if L2 = 0 %then% 
    B := true
    %leave matchEq
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if L2 = 0 %then% 
    B := true
    %leave matchEq
	-- KeyWord:invoke: 
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: L2 = 0:IS-empty: staticOff: 0
	-- Invocation:gen: L2 = 0
	-- Invocation:loadOrigin: L2 = 0
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 isEmpty:origin
	rpushg 1 matchEq:origin
	-- next not assign: = 0 :E: L2
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L2
	pushg 3 L2
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L199
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 145 0 #S#145
	rpop
 L199:
 L197:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 109 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L200:
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
	-- VarRef:invoke: inx
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- VarRef:invoke: inx
	pushg 1 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- VarRef:invoke: S
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
	-- VarRef:invoke: inx
	pushg 1 inx
	-- KeyWord:invoke: 
	-- pattern:invoke: %get inx: ? integer -> ch: ? Char
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
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
	-- VarRef:invoke: c1
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
	-- VarRef:invoke: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? char -> B: ? Boolean
	eq
	jmpFalse L202
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 146 0 #S#146
	rpop
 L202:
 L201:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 110 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L203:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if c1 = c2 %then% 
    B := L1 <= L2
    %leave matchEq %else% 
    B := c1 < c2
    %leave matchEq:IS-empty: staticOff: 0
	pushThis 
	invoke 111 0 %if%then%%else%#S#111
	rpop
 L204:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#149 149 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L205:
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
	rpushg 2 thenPart#S#149:origin
	rpushg 3 %if%then%%else%#S#112:origin
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
	rpushg 2 thenPart#S#149:origin
	rpushg 3 %if%then%%else%#S#112:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L1
	pushg 2 L1
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 L
 L206:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#150 150 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L207:
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
	rpushg 2 elsePart#S#150:origin
	rpushg 3 %if%then%%else%#S#112:origin
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
	rpushg 2 elsePart#S#150:origin
	rpushg 3 %if%then%%else%#S#112:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 L
 L208:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#154 154 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- on : 5
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 1 %then% 
    
    r := min + min
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 1
	-- Invocation:loadOrigin: mood = 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 3
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: = 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L209:
 L210:
	rtnInner
	end 1

	class %if%then%%else%#S#157 157 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- on : 5
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 1 %then% 
    r := 2
    mood := mood + 1 %else% 
    %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 1
	-- Invocation:loadOrigin: mood = 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 3
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: = 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L211:
 L212:
	rtnInner
	end 1

	class #S#161 161 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L213:
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
	rpushg 1 #S#161:origin
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
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
	rpushg 1 #S#161:origin
	rpushg 2 body#S#143:origin
	rpushg 2 %for%to%%do%#S#104:origin
	rpushg 1 loop:origin
	rpushg 1 =:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: False -> B: ? Booleanfalse
	-- Unary:invoke: 
	-- pattern:invoke: False -> B: ? Boolean
	invoke 24 0 False
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %leave Obj: ? integer
	break 3 141
 L214:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#144 144 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L215:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := L1 = L2:IS-empty: staticOff: 0
	-- Invocation:gen: B := L1 = L2
	-- Invocation:loadOrigin: B := L1 = L2
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 1 #S#144:origin
	rpushg 1 isEmpty:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	-- Invocation:loadOrigin:scan: := L1 = L2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= L1 = L2
	-- ObjectGenerator:gen: super: L1 = L2:IS-empty: staticOff: 0
	-- Invocation:gen: L1 = L2
	-- Invocation:loadOrigin: L1 = L2
	-- Invocation:loadOrigin:scan: L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L1
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 #S#144:origin
	rpushg 1 isEmpty:origin
	rpushg 1 matchEq:origin
	-- next not assign: = L2 :E: L1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L1
	pushg 2 L1
	-- Invocation:loadOrigin:scan: = L2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= L2
	-- ObjectGenerator:gen: super: L2:IS-empty: staticOff: 0
	-- Invocation:gen: L2
	-- Invocation:loadOrigin: L2
	-- Invocation:loadOrigin:scan: L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: L2
	-- on : 3
	-- AdjustOrigin: 0
	rpushg 1 #S#144:origin
	rpushg 1 isEmpty:origin
	rpushg 1 matchEq:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %leave Obj: ? integer
	break 2 176
 L216:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#145 145 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L217:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: B := true:IS-empty: staticOff: 0
	-- Invocation:gen: B := true
	-- Invocation:loadOrigin: B := true
	-- Invocation:loadOrigin:scan: B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: B
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 1 #S#145:origin
	rpushg 1 isEmpty:origin
	rpushg 1 matchEq:origin
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
	-- on : 7
	-- AdjustOrigin: 0
	rpushg 1 #S#145:origin
	rpushg 1 isEmpty:origin
	rpushg 1 matchEq:origin
	rpushg 1 loop:origin
	rpushg 1 <=:origin
	rpushg 1 String:origin
	rpushg 1 String:origin
	-- Unary:loadArgs: 
	-- pattern:loadArgs: True -> B: ? Booleantrue
	-- Unary:invoke: 
	-- pattern:invoke: True -> B: ? Boolean
	invoke 25 0 True
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %leave Obj: ? integer
	break 2 176
 L218:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#146 146 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L219:
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
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: inx < L:IS-empty: staticOff: 0
	-- Invocation:gen: inx < L
	-- Invocation:loadOrigin: inx < L
	-- Invocation:loadOrigin:scan: inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: inx
	-- on : 2
	-- AdjustOrigin: 0
	rpushg 1 #S#146:origin
	rpushg 1 loop:origin
	-- next not assign: < L :E: inx
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: inx
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
	rpushg 1 #S#146:origin
	rpushg 1 loop:origin
	rpushg 1 matchEq:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L
	pushg 1 L
	-- Binary:invoke: 
	-- pattern:invoke: < V: ? integer -> B: ? Boolean
	51
	jmpFalse L221
	-- ObjectGenerator:gen: super: %restart loop:IS-empty: staticOff: 0
	-- Invocation:gen: %restart loop
	-- Invocation:loadOrigin: %restart loop
	-- Invocation:loadOrigin:scan: %restart loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %restart loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %restart Obj: ? integer%restart loop
	-- KeyWord:invoke: 
	-- pattern:invoke: %restart Obj: ? integer
	break 1 200
 L221:
 L220:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#111 111 3
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
	-- VarRef:invoke: c1
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
	-- VarRef:invoke: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? char -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L222:
 L223:
	rtnInner
	end 1

	class thenPart#SB#162 162 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L224:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := min + min:IS-empty: staticOff: 0
	-- Invocation:gen: r := min + min
	-- Invocation:loadOrigin: r := min + min
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#162:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- Invocation:loadOrigin:scan: := min + min
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= min + min
	-- ObjectGenerator:gen: super: min + min:IS-empty: staticOff: 0
	-- Invocation:gen: min + min
	-- Invocation:loadOrigin: min + min
	-- Invocation:loadOrigin:scan: min
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: min
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#162:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- next not assign: + min :E: min
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: min
	pushg 1 min
	-- Invocation:loadOrigin:scan: + min
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ min
	-- ObjectGenerator:gen: super: min:IS-empty: staticOff: 0
	-- Invocation:gen: min
	-- Invocation:loadOrigin: min
	-- Invocation:loadOrigin:scan: min
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: min
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#162:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: min
	pushg 1 min
	-- Binary:invoke: 
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 5
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#162:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 5
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#162:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L225:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#163 163 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L226:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 164 0 %if%then%%else%#S#164
	rpop
 L227:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#165 165 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L228:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 2:IS-empty: staticOff: 0
	-- Invocation:gen: r := 2
	-- Invocation:loadOrigin: r := 2
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 4
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#165:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
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
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 5
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#165:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 5
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#165:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L229:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#166 166 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L230:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 167 0 %if%then%%else%#S#167
	rpop
 L231:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#147 147 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L232:
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
	rpushg 2 thenPart#S#147:origin
	rpushg 3 %if%then%%else%#S#111:origin
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
	rpushg 2 thenPart#S#147:origin
	rpushg 3 %if%then%%else%#S#111:origin
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	-- next not assign: <= L2 :E: L1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L1
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
	rpushg 2 thenPart#S#147:origin
	rpushg 3 %if%then%%else%#S#111:origin
	rpushg 1 doit:origin
	rpushg 1 matchEq:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:invoke: <= V: ? integer -> B: ? Boolean
	52
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %leave Obj: ? integer
	break 3 176
 L233:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#148 148 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L234:
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
	rpushg 2 elsePart#S#148:origin
	rpushg 3 %if%then%%else%#S#111:origin
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
	rpushg 2 elsePart#S#148:origin
	rpushg 3 %if%then%%else%#S#111:origin
	rpushg 1 doit:origin
	-- next not assign: < c2 :E: c1
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: c1
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
	rpushg 2 elsePart#S#148:origin
	rpushg 3 %if%then%%else%#S#111:origin
	rpushg 1 doit:origin
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:invoke: < V: ? char -> B: ? Boolean
	51
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
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
	-- pattern:invoke: %leave Obj: ? integer
	break 3 176
 L235:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#164 164 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- on : 7
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 2 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 2:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 2
	-- Invocation:loadOrigin: mood = 2
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 5
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: = 2 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 2
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L236:
 L237:
	rtnInner
	end 1

	class %if%then%%else%#S#167 167 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- on : 7
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 2 %then% 
    r := 3
    mood := mood + 1 %else% 
    %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 2:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 2
	-- Invocation:loadOrigin: mood = 2
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 5
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: = 2 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 2
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L238:
 L239:
	rtnInner
	end 1

	class thenPart#SB#168 168 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L240:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := min + 3:IS-empty: staticOff: 0
	-- Invocation:gen: r := min + 3
	-- Invocation:loadOrigin: r := min + 3
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 6
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#168:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- Invocation:loadOrigin:scan: := min + 3
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= min + 3
	-- ObjectGenerator:gen: super: min + 3:IS-empty: staticOff: 0
	-- Invocation:gen: min + 3
	-- Invocation:loadOrigin: min + 3
	-- Invocation:loadOrigin:scan: min
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: min
	-- on : 6
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#168:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- next not assign: + 3 :E: min
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: min
	pushg 1 min
	-- Invocation:loadOrigin:scan: + 3
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 3
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- Binary:invoke: 
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 7
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#168:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 7
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#168:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L241:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#169 169 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L242:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 170 0 %if%then%%else%#S#170
	rpop
 L243:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#171 171 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L244:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 3:IS-empty: staticOff: 0
	-- Invocation:gen: r := 3
	-- Invocation:loadOrigin: r := 3
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 6
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#171:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	-- Invocation:loadOrigin:scan: := 3
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 3
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 7
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#171:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 7
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#171:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L245:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#172 172 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L246:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 173 0 %if%then%%else%#S#173
	rpop
 L247:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#170 170 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- on : 9
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 3 %then% 
    
    r := min + 3
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 3:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 3
	-- Invocation:loadOrigin: mood = 3
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 7
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: = 3 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 3
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 3
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L248:
 L249:
	rtnInner
	end 1

	class %if%then%%else%#S#173 173 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- on : 9
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 3 %then% 
    r := 4
    mood := mood + 1 %else% 
    %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 3:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 3
	-- Invocation:loadOrigin: mood = 3
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 7
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: = 3 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 3
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 3
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L250:
 L251:
	rtnInner
	end 1

	class thenPart#SB#174 174 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L252:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := min + 3:IS-empty: staticOff: 0
	-- Invocation:gen: r := min + 3
	-- Invocation:loadOrigin: r := min + 3
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 8
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#174:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- Invocation:loadOrigin:scan: := min + 3
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= min + 3
	-- ObjectGenerator:gen: super: min + 3:IS-empty: staticOff: 0
	-- Invocation:gen: min + 3
	-- Invocation:loadOrigin: min + 3
	-- Invocation:loadOrigin:scan: min
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: min
	-- on : 8
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#174:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- next not assign: + 3 :E: min
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: min
	pushg 1 min
	-- Invocation:loadOrigin:scan: + 3
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 3
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- Binary:invoke: 
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 9
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#174:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 9
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#174:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L253:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#175 175 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L254:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 176 0 %if%then%%else%#S#176
	rpop
 L255:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#177 177 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L256:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 4:IS-empty: staticOff: 0
	-- Invocation:gen: r := 4
	-- Invocation:loadOrigin: r := 4
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 8
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#177:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	-- Invocation:loadOrigin:scan: := 4
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 4
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
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 9
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#177:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 9
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#177:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L257:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#178 178 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L258:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 179 0 %if%then%%else%#S#179
	rpop
 L259:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#176 176 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- on : 11
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 4 %then% 
    
    r := min + 2
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 4:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 4
	-- Invocation:loadOrigin: mood = 4
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 9
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: = 4 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 4
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 4
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L260:
 L261:
	rtnInner
	end 1

	class %if%then%%else%#S#179 179 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- on : 11
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 4 %then% 
    r := 5
    mood := mood + 1 %else% 
    %if mood = 5 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 4:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 4
	-- Invocation:loadOrigin: mood = 4
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 9
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: = 4 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 4
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 4
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
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L262:
 L263:
	rtnInner
	end 1

	class thenPart#SB#180 180 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L264:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := min + 2:IS-empty: staticOff: 0
	-- Invocation:gen: r := min + 2
	-- Invocation:loadOrigin: r := min + 2
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 10
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#180:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- Invocation:loadOrigin:scan: := min + 2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= min + 2
	-- ObjectGenerator:gen: super: min + 2:IS-empty: staticOff: 0
	-- Invocation:gen: min + 2
	-- Invocation:loadOrigin: min + 2
	-- Invocation:loadOrigin:scan: min
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: min
	-- on : 10
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#180:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- next not assign: + 2 :E: min
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: min
	pushg 1 min
	-- Invocation:loadOrigin:scan: + 2
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 2
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 11
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#180:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 11
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#180:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L265:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#181 181 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L266:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	pushThis 
	invoke 182 0 %if%then%%else%#S#182
	rpop
 L267:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#183 183 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L268:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 5:IS-empty: staticOff: 0
	-- Invocation:gen: r := 5
	-- Invocation:loadOrigin: r := 5
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 10
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#183:origin
	rpushg 3 %if%then%%else%#S#179:origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	-- Invocation:loadOrigin:scan: := 5
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 5
	-- ObjectGenerator:gen: super: 5:IS-empty: staticOff: 0
	-- Invocation:gen: 5
	-- Invocation:loadOrigin: 5
	-- Invocation:loadOrigin:scan: 5
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 5
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 11
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#183:origin
	rpushg 3 %if%then%%else%#S#179:origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 11
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#183:origin
	rpushg 3 %if%then%%else%#S#179:origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L269:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#184 184 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L270:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 5 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	-- Invocation:gen: %if mood = 5 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin: %if mood = 5 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if mood = 5 %then% 
    r := 6
    mood := 0
	-- KeyWord:invoke: 
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: mood = 5:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 5
	-- Invocation:loadOrigin: mood = 5
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 11
	-- AdjustOrigin: 0
	rpushg 2 elsePart#S#184:origin
	rpushg 3 %if%then%%else%#S#179:origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
	-- next not assign: = 5 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 5
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 5
	-- ObjectGenerator:gen: super: 5:IS-empty: staticOff: 0
	-- Invocation:gen: 5
	-- Invocation:loadOrigin: 5
	-- Invocation:loadOrigin:scan: 5
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 5
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L272
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 187 0 #S#187
	rpop
 L272:
 L271:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#182 182 3
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:36 2:36 3:0 4:0
	-- Invocation:loadOrigin: %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: %if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- on : 13
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	rpushg 1 Program1:origin
	rpushg 1 bmp:origin
	-- Super:sig none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if cond: ? Boolean %then% thenPart:< Object %else% elsePart:< Object%if mood = 5 %then% 
    
    r := min + 4
    mood := mood + 1 %else% 
    %if mood = 6 %then% 
    r := 6
    mood := 0
	-- ObjectGenerator:gen: super: mood = 5:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 5
	-- Invocation:loadOrigin: mood = 5
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 11
	-- AdjustOrigin: 3
	rpushg 3 origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: = 5 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 5
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 5
	-- ObjectGenerator:gen: super: 5:IS-empty: staticOff: 0
	-- Invocation:gen: 5
	-- Invocation:loadOrigin: 5
	-- Invocation:loadOrigin:scan: 5
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 5
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	topSuper  65
	rtnInner
	DO:
	mvStack 
 L273:
 L274:
	rtnInner
	end 1

	class #S#187 187 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L275:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 6:IS-empty: staticOff: 0
	-- Invocation:gen: r := 6
	-- Invocation:loadOrigin: r := 6
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 11
	-- AdjustOrigin: 0
	rpushg 1 #S#187:origin
	rpushg 2 elsePart#S#184:origin
	rpushg 3 %if%then%%else%#S#179:origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	-- Invocation:loadOrigin:scan: := 6
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 6
	-- ObjectGenerator:gen: super: 6:IS-empty: staticOff: 0
	-- Invocation:gen: 6
	-- Invocation:loadOrigin: 6
	-- Invocation:loadOrigin:scan: 6
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 6
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := 0:IS-empty: staticOff: 0
	-- Invocation:gen: mood := 0
	-- Invocation:loadOrigin: mood := 0
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 12
	-- AdjustOrigin: 0
	rpushg 1 #S#187:origin
	rpushg 2 elsePart#S#184:origin
	rpushg 3 %if%then%%else%#S#179:origin
	rpushg 2 elsePart#S#178:origin
	rpushg 3 %if%then%%else%#S#173:origin
	rpushg 2 elsePart#S#172:origin
	rpushg 3 %if%then%%else%#S#167:origin
	rpushg 2 elsePart#S#166:origin
	rpushg 3 %if%then%%else%#S#157:origin
	rpushg 2 elsePart#S#156:origin
	rpushg 3 %if%then%%else%#S#127:origin
	rpushg 1 tilfeldig:origin
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
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L276:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#185 185 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L277:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := min + 4:IS-empty: staticOff: 0
	-- Invocation:gen: r := min + 4
	-- Invocation:loadOrigin: r := min + 4
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 12
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#185:origin
	rpushg 3 %if%then%%else%#S#182:origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- Invocation:loadOrigin:scan: := min + 4
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= min + 4
	-- ObjectGenerator:gen: super: min + 4:IS-empty: staticOff: 0
	-- Invocation:gen: min + 4
	-- Invocation:loadOrigin: min + 4
	-- Invocation:loadOrigin:scan: min
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: min
	-- on : 12
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#185:origin
	rpushg 3 %if%then%%else%#S#182:origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- next not assign: + 4 :E: min
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: min
	pushg 1 min
	-- Invocation:loadOrigin:scan: + 4
	-- Binary:loadArgs: 
	-- pattern:loadArgs: + V: ? integer -> R: ? integer+ 4
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood := mood + 1
	-- Invocation:loadOrigin: mood := mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 13
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#185:origin
	rpushg 3 %if%then%%else%#S#182:origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- Invocation:loadOrigin:scan: := mood + 1
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= mood + 1
	-- ObjectGenerator:gen: super: mood + 1:IS-empty: staticOff: 0
	-- Invocation:gen: mood + 1
	-- Invocation:loadOrigin: mood + 1
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 13
	-- AdjustOrigin: 0
	rpushg 2 thenPart#S#185:origin
	rpushg 3 %if%then%%else%#S#182:origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: + 1 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
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
	-- pattern:invoke: + V: ? integer -> R: ? integer
	plus
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L278:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#186 186 2
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L279:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: %if mood = 6 %then% 
    r := 6
    mood := 0:IS-empty: staticOff: 0
	-- Invocation:gen: %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin: %if mood = 6 %then% 
    r := 6
    mood := 0
	-- Invocation:loadOrigin:scan: %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: %if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: %if _cond: ? Boolean %then% _thenPart:< Object%if mood = 6 %then% 
    r := 6
    mood := 0
	-- KeyWord:invoke: 
	-- pattern:invoke: %if _cond: ? Boolean %then% _thenPart:< Object
	-- ObjectGenerator:gen: super: mood = 6:IS-empty: staticOff: 0
	-- Invocation:gen: mood = 6
	-- Invocation:loadOrigin: mood = 6
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 13
	-- AdjustOrigin: 0
	rpushg 2 elsePart#S#186:origin
	rpushg 3 %if%then%%else%#S#182:origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
	-- next not assign: = 6 :E: mood
	-- Unary:loadArgs: 
	-- VarRef:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:invoke: mood
	pushg 1 mood
	-- Invocation:loadOrigin:scan: = 6
	-- Binary:loadArgs: 
	-- pattern:loadArgs: = V: ? integer -> B: ? Boolean= 6
	-- ObjectGenerator:gen: super: 6:IS-empty: staticOff: 0
	-- Invocation:gen: 6
	-- Invocation:loadOrigin: 6
	-- Invocation:loadOrigin:scan: 6
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 6
	-- Binary:invoke: 
	-- pattern:invoke: = V: ? integer -> B: ? Boolean
	eq
	jmpFalse L281
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 188 0 #S#188
	rpop
 L281:
 L280:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#188 188 1
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L282:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: r := 6:IS-empty: staticOff: 0
	-- Invocation:gen: r := 6
	-- Invocation:loadOrigin: r := 6
	-- Invocation:loadOrigin:scan: r
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: r
	-- on : 13
	-- AdjustOrigin: 0
	rpushg 1 #S#188:origin
	rpushg 2 elsePart#S#186:origin
	rpushg 3 %if%then%%else%#S#182:origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	-- Invocation:loadOrigin:scan: := 6
	-- Binary:loadArgs: 
	-- pattern:loadArgs: := V: ? Object:= 6
	-- ObjectGenerator:gen: super: 6:IS-empty: staticOff: 0
	-- Invocation:gen: 6
	-- Invocation:loadOrigin: 6
	-- Invocation:loadOrigin:scan: 6
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 6
	-- Binary:invoke: 
	-- pattern:invoke: := V: ? Object
	storeg 3 r
	-- ObjectGenerator:gen: super: mood := 0:IS-empty: staticOff: 0
	-- Invocation:gen: mood := 0
	-- Invocation:loadOrigin: mood := 0
	-- Invocation:loadOrigin:scan: mood
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: mood
	-- on : 14
	-- AdjustOrigin: 0
	rpushg 1 #S#188:origin
	rpushg 2 elsePart#S#186:origin
	rpushg 3 %if%then%%else%#S#182:origin
	rpushg 2 elsePart#S#181:origin
	rpushg 3 %if%then%%else%#S#176:origin
	rpushg 2 elsePart#S#175:origin
	rpushg 3 %if%then%%else%#S#170:origin
	rpushg 2 elsePart#S#169:origin
	rpushg 3 %if%then%%else%#S#164:origin
	rpushg 2 elsePart#S#163:origin
	rpushg 3 %if%then%%else%#S#154:origin
	rpushg 2 elsePart#S#153:origin
	rpushg 3 %if%then%%else%#S#125:origin
	rpushg 1 tilfeldigx:origin
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
	-- pattern:invoke: := V: ? Object
	storeg 1 mood
 L283:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class main 196 0
	pushThis 
	invoke 1 0 BETAworld
	stop
	end 0

	class EventProcessor 197 0
	stop

	class ThreadStub 198 0
	DO:
	mvStack 
	call(D)ThreadStub
	stop
	-- vdtAdd: inx=1 descInx=136
	-- vdtAdd: inx=1 descInx=158
	-- vdtAdd: inx=1 descInx=159
	-- vdtAdd: inx=1 descInx=160
	-- vdtAdd: inx=1 descInx=140
	-- vdtAdd: inx=1 descInx=141
	-- vdtAdd: inx=1 descInx=152
	-- vdtAdd: inx=2 descInx=153
	-- vdtAdd: inx=1 descInx=155
	-- vdtAdd: inx=2 descInx=156
	-- vdtAdd: inx=1 descInx=138
	-- vdtAdd: inx=1 descInx=139
	-- vdtAdd: inx=1 descInx=143
	-- vdtAdd: inx=1 descInx=149
	-- vdtAdd: inx=2 descInx=150
	-- vdtAdd: inx=1 descInx=162
	-- vdtAdd: inx=2 descInx=163
	-- vdtAdd: inx=1 descInx=165
	-- vdtAdd: inx=2 descInx=166
	-- vdtAdd: inx=1 descInx=147
	-- vdtAdd: inx=2 descInx=148
	-- vdtAdd: inx=1 descInx=168
	-- vdtAdd: inx=2 descInx=169
	-- vdtAdd: inx=1 descInx=171
	-- vdtAdd: inx=2 descInx=172
	-- vdtAdd: inx=1 descInx=174
	-- vdtAdd: inx=2 descInx=175
	-- vdtAdd: inx=1 descInx=177
	-- vdtAdd: inx=2 descInx=178
	-- vdtAdd: inx=1 descInx=180
	-- vdtAdd: inx=2 descInx=181
	-- vdtAdd: inx=1 descInx=183
	-- vdtAdd: inx=2 descInx=184
	-- vdtAdd: inx=1 descInx=185
	-- vdtAdd: inx=2 descInx=186

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
17:	invoke 81 3 1
23:	rpop 
24:	pushthis 
25:	invoke 118 4 1
31:	rpop 
32:	rtnEventQ 0
doE: 
34:	mvStack
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class Program1 3 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	pushc 6
9:	invoke 120 2 1
15:	rpop 
16:	rtnEventQ 1
doE: 
18:	doEventQ 
19:	mvStack
20:	pushthis 
21:	pushc 0
23:	storeg 1
25:	pushthis 
26:	invoke 128 0 1
32:	rpop 
33:	pushthis 
34:	invoke 129 0 1
40:	rpop 
41:	pushthis 
42:	invoke 130 0 1
48:	rpop 
49:	pushthis 
50:	rpushg 1
52:	rpushg 1
54:	invoke 76 0 0
60:	rpop 
61:	rtnEventQ 0
63:	setThisStack
64:	pushthis 
65:	rtn D


Class BETA 4 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 75 2 1
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
19:	invoke 131 0 1
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
29:	invoke 132 0 1
35:	rpop 
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class switch 71 1
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
23:	rtn D


Class case 72 1
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
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	pushg 1
23:	eq 
24:	jmpFalse 35
27:	pushthis 
28:	invoke 133 0 1
34:	rpop 
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class %xswitch 73 1
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
23:	rtn D


Class %scase 74 1
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
16:	rpushg 1
18:	pushg 1
20:	pushthis 
21:	pushg 1
23:	eq 
24:	jmpFalse 35
27:	pushthis 
28:	invoke 134 0 1
34:	rpop 
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class ascii 75 1
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


Class newline 76 1
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


Class putint 77 1
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
54:	invoke 78 0 0
60:	rpop 
61:	rtnEventQ 0
63:	setThisStack
64:	pushthis 
65:	rtn D


Class doit 78 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	invoke 79 2 1
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
31:	invoke 80 0 1
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class loop 79 1
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
84:	invoke 135 0 1
90:	rpop 
91:	rtnEventQ 0
93:	setThisStack
94:	pushthis 
95:	rtn D


Class %for%to%%do%#S#80 80 2
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


Class LIB 81 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 82 2 1
13:	rpop 
14:	pushthis 
15:	invoke 89 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class BasicIO 82 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 88 2 1
13:	rpop 
14:	pushthis 
15:	invoke 115 3 1
21:	rpop 
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class Lock 83 1
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


Class init 84 1
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


Class get 85 1
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
48:	invoke 137 0 1
54:	rpop 
55:	rtnEventQ 0
57:	setThisStack
58:	pushthis 
59:	rtn D


Class free 87 1
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


Class keyboard 88 1
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


Class String 89 1
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


Class String 90 1
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


Class length 91 1
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


Class + 93 1
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
17:	invoke 91 0 0
23:	storeg 1
25:	pushthis 
26:	invoke 94 0 0
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	rpushg 3
39:	rtn D


Class doplus 94 1
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
25:	invoke 91 0 0
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
48:	invoke 95 0 1
54:	rpop 
55:	pushthis 
56:	invoke 96 0 1
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


Class %for%to%%do%#S#95 95 2
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


Class %for%to%%do%#S#96 96 2
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
25:	invoke 91 0 0
31:	toSuper 68
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class asLowerCase 97 1
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


Class scan 98 1
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
13:	invoke 99 0 1
19:	rpop 
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class %for%to%%do%#S#99 99 2
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
21:	invoke 91 0 0
27:	toSuper 68
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class print 100 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 101 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %for%to%%do%#S#101 101 2
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
21:	invoke 91 0 0
27:	toSuper 68
enterE: 
30:	rtnInner
doE: 
31:	mvStack
32:	rtnInner


Class = 102 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 103 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


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
11:	pushthis 
12:	rpushg 1
14:	rpushg 1
16:	invoke 91 0 0
22:	storeg 3
24:	pushthis 
25:	pushg 3
27:	pushthis 
28:	rpushg 1
30:	rpushg 2
32:	invoke 91 0 0
38:	ne 
39:	jmpFalse 50
42:	pushthis 
43:	invoke 142 0 1
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
71:	invoke 104 0 1
77:	rpop 
78:	rtnEventQ 0
80:	setThisStack
81:	pushthis 
82:	rtn D


Class %for%to%%do%#S#104 104 2
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
25:	invoke 91 0 0
31:	toSuper 68
enterE: 
34:	rtnInner
doE: 
35:	mvStack
36:	rtnInner


Class <= 105 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	invoke 106 3 1
16:	rpop 
17:	rtnEventQ 0
doE: 
19:	mvStack
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	pushg 1
26:	rtn D


Class loop 106 1
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
16:	invoke 91 0 0
22:	storeg 2
24:	pushthis 
25:	pushthis 
26:	rpushg 1
28:	rpushg 2
30:	invoke 91 0 0
36:	storeg 3
38:	pushthis 
39:	invoke 112 0 1
45:	rpop 
46:	pushthis 
47:	invoke 107 0 1
53:	rpop 
54:	rtnEventQ 0
56:	setThisStack
57:	pushthis 
58:	rtn D


Class matchEq 107 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 108 2 1
13:	rpop 
14:	pushthis 
15:	invoke 109 3 1
21:	rpop 
22:	pushthis 
23:	invoke 110 4 1
29:	rpop 
30:	rtnEventQ 0
doE: 
32:	mvStack
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	rtn D


Class isEmpty 108 1
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
15:	pushg 2
17:	pushc 0
19:	eq 
20:	jmpFalse 31
23:	pushthis 
24:	invoke 144 0 1
30:	rpop 
31:	pushthis 
32:	rpushg 1
34:	rpushg 1
36:	pushg 3
38:	pushc 0
40:	eq 
41:	jmpFalse 52
44:	pushthis 
45:	invoke 145 0 1
51:	rpop 
52:	rtnEventQ 0
54:	setThisStack
55:	pushthis 
56:	rtn D


Class loop 109 1
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
80:	invoke 146 0 1
86:	rpop 
87:	rtnEventQ 0
89:	setThisStack
90:	pushthis 
91:	rtn D


Class doit 110 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 111 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#111 111 3
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


Class %if%then%%else%#S#112 112 3
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


Class readLine 113 1
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
27:	invoke 114 4 1
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


Class read 114 1
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
39:	invoke 151 0 1
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


Class screen 115 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 83 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 116 1
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
15:	invoke 85 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	rpushg 2
27:	invoke 84 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 2
39:	invoke 87 0 0
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class display 117 1
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
17:	invoke 85 0 1
23:	rpop 
24:	inner 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 2
31:	invoke 87 0 0
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class no 118 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 119 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class bmp 119 1
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


Class Array 120 1
allocE:
1:	pushthis 
2:	storeg 1
4:	rstore 1
6:	allocEventQ 1
8:	mvStack
9:	pushthis 
10:	rpushg 1
12:	rpushg 1
14:	rpushg 1
16:	pushthis 
17:	pushg 1
19:	pushc 0
21:	pushc 1
23:	allocIndexed 57 1
27:	pushthis 
28:	rstoreg 2
30:	rtnEventQ 0
doE: 
32:	mvStack
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	rtn D


Class put 121 1
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


Class := 122 1
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
16:	rpushg 1
18:	rpushg 2
20:	pushthis 
21:	pushg 1
23:	pushthis 
24:	rpushg 1
26:	pushg 1
28:	xstoreg 1
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class get 123 1
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
15:	rpushg 1
17:	rpushg 2
19:	pushthis 
20:	pushg 1
22:	xpushg 1
24:	storeg 2
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	pushg 2
32:	rtn D


Class tilfeldigx 124 1
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
17:	invoke 125 0 1
23:	rpop 
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	pushg 3
30:	rtn D


Class %if%then%%else%#S#125 125 3
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
21:	pushc 0
23:	eq 
24:	toSuper 65
enterE: 
27:	rtnInner
doE: 
28:	mvStack
29:	rtnInner


Class tilfeldig 126 1
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
17:	invoke 127 0 1
23:	rpop 
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	pushg 3
30:	rtn D


Class %if%then%%else%#S#127 127 3
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
21:	pushc 0
23:	eq 
24:	toSuper 65
enterE: 
27:	rtnInner
doE: 
28:	mvStack
29:	rtnInner


Class %for%to%%do%#S#128 128 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	pushc 1
14:	pushc 6
16:	toSuper 68
enterE: 
19:	rtnInner
doE: 
20:	mvStack
21:	rtnInner


Class %for%to%%do%#S#129 129 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	pushc 1
14:	pushc2 1000
17:	toSuper 68
enterE: 
20:	rtnInner
doE: 
21:	mvStack
22:	rtnInner


Class %for%to%%do%#S#130 130 2
allocE:
1:	rstore 2
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	rpushg 1
12:	pushc 1
14:	pushc 6
16:	toSuper 68
enterE: 
19:	rtnInner
doE: 
20:	mvStack
21:	rtnInner


Class #S#131 131 1
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
18:	break 1 47 66
24:	rtnEventQ 0
26:	setThisStack
27:	pushthis 
28:	rtn D


Class #S#132 132 1
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
41:	break 1 72 70
47:	rtnEventQ 0
49:	setThisStack
50:	pushthis 
51:	rtn D


Class #S#133 133 1
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
16:	break 2 28 71
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class #S#134 134 1
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
16:	break 2 30 73
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class #S#135 135 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 79 79
16:	rtnEventQ 0
18:	setThisStack
19:	pushthis 
20:	rtn D


Class body#SB#136 136 2
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


Class #S#137 137 1
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
16:	break 1 128 86
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class body#SB#138 138 2
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


Class body#SB#139 139 2
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


Class body#SB#140 140 2
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


Class body#SB#141 141 2
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


Class #S#142 142 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 141 103
16:	rtnEventQ 0
18:	setThisStack
19:	pushthis 
20:	rtn D


Class body#SB#143 143 2
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
75:	invoke 161 0 1
81:	rpop 
82:	rtnEventQ 0
84:	setThisStack
85:	pushthis 
86:	rtn D


Class #S#144 144 1
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
19:	pushthis 
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	pushg 2
28:	pushthis 
29:	rpushg 1
31:	rpushg 1
33:	rpushg 1
35:	pushg 3
37:	eq 
38:	storeg 1
40:	break 2 176 107
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class #S#145 145 1
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
19:	pushthis 
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	rpushg 1
28:	rpushg 1
30:	rpushg 1
32:	rpushg 1
34:	invoke 25 0 0
40:	storeg 1
42:	break 2 176 107
48:	rtnEventQ 0
50:	setThisStack
51:	pushthis 
52:	rtn D


Class #S#146 146 1
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
27:	jmpFalse 36
30:	break 1 200 109
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rtn D


Class thenPart#SB#147 147 2
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
46:	break 3 176 107
52:	rtnEventQ 0
54:	setThisStack
55:	pushthis 
56:	rtn D


Class elsePart#SB#148 148 2
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
42:	break 3 176 107
48:	rtnEventQ 0
50:	setThisStack
51:	pushthis 
52:	rtn D


Class thenPart#SB#149 149 2
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


Class elsePart#SB#150 150 2
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


Class #S#151 151 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 132 114
16:	rtnEventQ 0
18:	setThisStack
19:	pushthis 
20:	rtn D


Class thenPart#SB#152 152 2
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
15:	pushc 1
17:	storeg 3
19:	pushthis 
20:	rpushg 2
22:	rpushg 3
24:	rpushg 1
26:	pushthis 
27:	rpushg 2
29:	rpushg 3
31:	rpushg 1
33:	pushg 1
35:	pushc 1
37:	+
38:	storeg 1
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class elsePart#SB#153 153 2
allocE:
1:	rstore 2
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
22:	rtn D


Class %if%then%%else%#S#154 154 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 2
23:	rpushg 3
25:	rpushg 1
27:	pushg 1
29:	pushc 1
31:	eq 
32:	toSuper 65
enterE: 
35:	rtnInner
doE: 
36:	mvStack
37:	rtnInner


Class thenPart#SB#155 155 2
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
15:	pushc 1
17:	storeg 3
19:	pushthis 
20:	rpushg 2
22:	rpushg 3
24:	rpushg 1
26:	pushthis 
27:	rpushg 2
29:	rpushg 3
31:	rpushg 1
33:	pushg 1
35:	pushc 1
37:	+
38:	storeg 1
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class elsePart#SB#156 156 2
allocE:
1:	rstore 2
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
22:	rtn D


Class %if%then%%else%#S#157 157 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 1
14:	rpushg 1
16:	rpushg 1
18:	pushthis 
19:	rpushg 3
21:	rpushg 2
23:	rpushg 3
25:	rpushg 1
27:	pushg 1
29:	pushc 1
31:	eq 
32:	toSuper 65
enterE: 
35:	rtnInner
doE: 
36:	mvStack
37:	rtnInner


Class body#SB#158 158 2
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
15:	rpushg 2
17:	pushthis 
18:	rpushg 2
20:	pushg 3
22:	invoke 121 0 1
28:	pushc 0
30:	invoke 122 0 0
36:	rpop 
37:	rtnEventQ 0
39:	setThisStack
40:	pushthis 
41:	rtn D


Class body#SB#159 159 2
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
20:	pushc 1
22:	pushc 6
24:	invoke 126 0 0
30:	storeg 2
32:	pushthis 
33:	rpushg 2
35:	rpushg 2
37:	rpushg 2
39:	pushthis 
40:	rpushg 2
42:	rpushg 2
44:	pushg 2
46:	invoke 121 0 1
52:	pushthis 
53:	rpushg 2
55:	rpushg 2
57:	rpushg 2
59:	pushthis 
60:	rpushg 2
62:	rpushg 2
64:	pushg 2
66:	invoke 123 0 0
72:	pushc 1
74:	+
75:	invoke 122 0 0
81:	rpop 
82:	rtnEventQ 0
84:	setThisStack
85:	pushthis 
86:	rtn D


Class body#SB#160 160 2
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
19:	pushthis 
20:	rpushg 2
22:	rpushg 2
24:	rpushg 2
26:	pushthis 
27:	rpushg 2
29:	pushg 3
31:	invoke 123 0 0
37:	invoke 77 0 0
43:	rpop 
44:	pushc 32
46:	%prim put 2
48:	rtnEventQ 0
50:	setThisStack
51:	pushthis 
52:	rtn D


Class #S#161 161 1
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
42:	break 3 141 103
48:	rtnEventQ 0
50:	setThisStack
51:	pushthis 
52:	rtn D


Class thenPart#SB#162 162 2
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
19:	pushthis 
20:	rpushg 2
22:	rpushg 3
24:	rpushg 2
26:	rpushg 3
28:	pushg 1
30:	pushthis 
31:	rpushg 2
33:	rpushg 3
35:	rpushg 2
37:	rpushg 3
39:	pushg 1
41:	+
42:	storeg 3
44:	pushthis 
45:	rpushg 2
47:	rpushg 3
49:	rpushg 2
51:	rpushg 3
53:	rpushg 1
55:	pushthis 
56:	rpushg 2
58:	rpushg 3
60:	rpushg 2
62:	rpushg 3
64:	rpushg 1
66:	pushg 1
68:	pushc 1
70:	+
71:	storeg 1
73:	rtnEventQ 0
75:	setThisStack
76:	pushthis 
77:	rtn D


Class elsePart#SB#163 163 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 164 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#164 164 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 2
14:	rpushg 3
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	pushthis 
23:	rpushg 3
25:	rpushg 2
27:	rpushg 3
29:	rpushg 2
31:	rpushg 3
33:	rpushg 1
35:	pushg 1
37:	pushc 2
39:	eq 
40:	toSuper 65
enterE: 
43:	rtnInner
doE: 
44:	mvStack
45:	rtnInner


Class thenPart#SB#165 165 2
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
19:	pushc 2
21:	storeg 3
23:	pushthis 
24:	rpushg 2
26:	rpushg 3
28:	rpushg 2
30:	rpushg 3
32:	rpushg 1
34:	pushthis 
35:	rpushg 2
37:	rpushg 3
39:	rpushg 2
41:	rpushg 3
43:	rpushg 1
45:	pushg 1
47:	pushc 1
49:	+
50:	storeg 1
52:	rtnEventQ 0
54:	setThisStack
55:	pushthis 
56:	rtn D


Class elsePart#SB#166 166 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 167 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#167 167 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 2
14:	rpushg 3
16:	rpushg 1
18:	rpushg 1
20:	rpushg 1
22:	pushthis 
23:	rpushg 3
25:	rpushg 2
27:	rpushg 3
29:	rpushg 2
31:	rpushg 3
33:	rpushg 1
35:	pushg 1
37:	pushc 2
39:	eq 
40:	toSuper 65
enterE: 
43:	rtnInner
doE: 
44:	mvStack
45:	rtnInner


Class thenPart#SB#168 168 2
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
19:	rpushg 2
21:	rpushg 3
23:	pushthis 
24:	rpushg 2
26:	rpushg 3
28:	rpushg 2
30:	rpushg 3
32:	rpushg 2
34:	rpushg 3
36:	pushg 1
38:	pushc 3
40:	+
41:	storeg 3
43:	pushthis 
44:	rpushg 2
46:	rpushg 3
48:	rpushg 2
50:	rpushg 3
52:	rpushg 2
54:	rpushg 3
56:	rpushg 1
58:	pushthis 
59:	rpushg 2
61:	rpushg 3
63:	rpushg 2
65:	rpushg 3
67:	rpushg 2
69:	rpushg 3
71:	rpushg 1
73:	pushg 1
75:	pushc 1
77:	+
78:	storeg 1
80:	rtnEventQ 0
82:	setThisStack
83:	pushthis 
84:	rtn D


Class elsePart#SB#169 169 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 170 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#170 170 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 2
14:	rpushg 3
16:	rpushg 2
18:	rpushg 3
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	pushthis 
27:	rpushg 3
29:	rpushg 2
31:	rpushg 3
33:	rpushg 2
35:	rpushg 3
37:	rpushg 2
39:	rpushg 3
41:	rpushg 1
43:	pushg 1
45:	pushc 3
47:	eq 
48:	toSuper 65
enterE: 
51:	rtnInner
doE: 
52:	mvStack
53:	rtnInner


Class thenPart#SB#171 171 2
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
19:	rpushg 2
21:	rpushg 3
23:	pushc 3
25:	storeg 3
27:	pushthis 
28:	rpushg 2
30:	rpushg 3
32:	rpushg 2
34:	rpushg 3
36:	rpushg 2
38:	rpushg 3
40:	rpushg 1
42:	pushthis 
43:	rpushg 2
45:	rpushg 3
47:	rpushg 2
49:	rpushg 3
51:	rpushg 2
53:	rpushg 3
55:	rpushg 1
57:	pushg 1
59:	pushc 1
61:	+
62:	storeg 1
64:	rtnEventQ 0
66:	setThisStack
67:	pushthis 
68:	rtn D


Class elsePart#SB#172 172 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 173 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#173 173 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 2
14:	rpushg 3
16:	rpushg 2
18:	rpushg 3
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	pushthis 
27:	rpushg 3
29:	rpushg 2
31:	rpushg 3
33:	rpushg 2
35:	rpushg 3
37:	rpushg 2
39:	rpushg 3
41:	rpushg 1
43:	pushg 1
45:	pushc 3
47:	eq 
48:	toSuper 65
enterE: 
51:	rtnInner
doE: 
52:	mvStack
53:	rtnInner


Class thenPart#SB#174 174 2
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
19:	rpushg 2
21:	rpushg 3
23:	rpushg 2
25:	rpushg 3
27:	pushthis 
28:	rpushg 2
30:	rpushg 3
32:	rpushg 2
34:	rpushg 3
36:	rpushg 2
38:	rpushg 3
40:	rpushg 2
42:	rpushg 3
44:	pushg 1
46:	pushc 3
48:	+
49:	storeg 3
51:	pushthis 
52:	rpushg 2
54:	rpushg 3
56:	rpushg 2
58:	rpushg 3
60:	rpushg 2
62:	rpushg 3
64:	rpushg 2
66:	rpushg 3
68:	rpushg 1
70:	pushthis 
71:	rpushg 2
73:	rpushg 3
75:	rpushg 2
77:	rpushg 3
79:	rpushg 2
81:	rpushg 3
83:	rpushg 2
85:	rpushg 3
87:	rpushg 1
89:	pushg 1
91:	pushc 1
93:	+
94:	storeg 1
96:	rtnEventQ 0
98:	setThisStack
99:	pushthis 
100:	rtn D


Class elsePart#SB#175 175 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 176 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#176 176 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 2
14:	rpushg 3
16:	rpushg 2
18:	rpushg 3
20:	rpushg 2
22:	rpushg 3
24:	rpushg 1
26:	rpushg 1
28:	rpushg 1
30:	pushthis 
31:	rpushg 3
33:	rpushg 2
35:	rpushg 3
37:	rpushg 2
39:	rpushg 3
41:	rpushg 2
43:	rpushg 3
45:	rpushg 2
47:	rpushg 3
49:	rpushg 1
51:	pushg 1
53:	pushc 4
55:	eq 
56:	toSuper 65
enterE: 
59:	rtnInner
doE: 
60:	mvStack
61:	rtnInner


Class thenPart#SB#177 177 2
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
19:	rpushg 2
21:	rpushg 3
23:	rpushg 2
25:	rpushg 3
27:	pushc 4
29:	storeg 3
31:	pushthis 
32:	rpushg 2
34:	rpushg 3
36:	rpushg 2
38:	rpushg 3
40:	rpushg 2
42:	rpushg 3
44:	rpushg 2
46:	rpushg 3
48:	rpushg 1
50:	pushthis 
51:	rpushg 2
53:	rpushg 3
55:	rpushg 2
57:	rpushg 3
59:	rpushg 2
61:	rpushg 3
63:	rpushg 2
65:	rpushg 3
67:	rpushg 1
69:	pushg 1
71:	pushc 1
73:	+
74:	storeg 1
76:	rtnEventQ 0
78:	setThisStack
79:	pushthis 
80:	rtn D


Class elsePart#SB#178 178 2
allocE:
1:	rstore 2
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
22:	rtn D


Class %if%then%%else%#S#179 179 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 2
14:	rpushg 3
16:	rpushg 2
18:	rpushg 3
20:	rpushg 2
22:	rpushg 3
24:	rpushg 1
26:	rpushg 1
28:	rpushg 1
30:	pushthis 
31:	rpushg 3
33:	rpushg 2
35:	rpushg 3
37:	rpushg 2
39:	rpushg 3
41:	rpushg 2
43:	rpushg 3
45:	rpushg 2
47:	rpushg 3
49:	rpushg 1
51:	pushg 1
53:	pushc 4
55:	eq 
56:	toSuper 65
enterE: 
59:	rtnInner
doE: 
60:	mvStack
61:	rtnInner


Class thenPart#SB#180 180 2
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
19:	rpushg 2
21:	rpushg 3
23:	rpushg 2
25:	rpushg 3
27:	rpushg 2
29:	rpushg 3
31:	pushthis 
32:	rpushg 2
34:	rpushg 3
36:	rpushg 2
38:	rpushg 3
40:	rpushg 2
42:	rpushg 3
44:	rpushg 2
46:	rpushg 3
48:	rpushg 2
50:	rpushg 3
52:	pushg 1
54:	pushc 2
56:	+
57:	storeg 3
59:	pushthis 
60:	rpushg 2
62:	rpushg 3
64:	rpushg 2
66:	rpushg 3
68:	rpushg 2
70:	rpushg 3
72:	rpushg 2
74:	rpushg 3
76:	rpushg 2
78:	rpushg 3
80:	rpushg 1
82:	pushthis 
83:	rpushg 2
85:	rpushg 3
87:	rpushg 2
89:	rpushg 3
91:	rpushg 2
93:	rpushg 3
95:	rpushg 2
97:	rpushg 3
99:	rpushg 2
101:	rpushg 3
103:	rpushg 1
105:	pushg 1
107:	pushc 1
109:	+
110:	storeg 1
112:	rtnEventQ 0
114:	setThisStack
115:	pushthis 
116:	rtn D


Class elsePart#SB#181 181 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 182 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#182 182 3
allocE:
1:	rstore 3
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 3
8:	rpushg 2
10:	rpushg 3
12:	rpushg 2
14:	rpushg 3
16:	rpushg 2
18:	rpushg 3
20:	rpushg 2
22:	rpushg 3
24:	rpushg 2
26:	rpushg 3
28:	rpushg 1
30:	rpushg 1
32:	rpushg 1
34:	pushthis 
35:	rpushg 3
37:	rpushg 2
39:	rpushg 3
41:	rpushg 2
43:	rpushg 3
45:	rpushg 2
47:	rpushg 3
49:	rpushg 2
51:	rpushg 3
53:	rpushg 2
55:	rpushg 3
57:	rpushg 1
59:	pushg 1
61:	pushc 5
63:	eq 
64:	toSuper 65
enterE: 
67:	rtnInner
doE: 
68:	mvStack
69:	rtnInner


Class thenPart#SB#183 183 2
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
19:	rpushg 2
21:	rpushg 3
23:	rpushg 2
25:	rpushg 3
27:	rpushg 2
29:	rpushg 3
31:	pushc 5
33:	storeg 3
35:	pushthis 
36:	rpushg 2
38:	rpushg 3
40:	rpushg 2
42:	rpushg 3
44:	rpushg 2
46:	rpushg 3
48:	rpushg 2
50:	rpushg 3
52:	rpushg 2
54:	rpushg 3
56:	rpushg 1
58:	pushthis 
59:	rpushg 2
61:	rpushg 3
63:	rpushg 2
65:	rpushg 3
67:	rpushg 2
69:	rpushg 3
71:	rpushg 2
73:	rpushg 3
75:	rpushg 2
77:	rpushg 3
79:	rpushg 1
81:	pushg 1
83:	pushc 1
85:	+
86:	storeg 1
88:	rtnEventQ 0
90:	setThisStack
91:	pushthis 
92:	rtn D


Class elsePart#SB#184 184 2
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
19:	rpushg 2
21:	rpushg 3
23:	rpushg 2
25:	rpushg 3
27:	rpushg 2
29:	rpushg 3
31:	rpushg 1
33:	pushg 1
35:	pushc 5
37:	eq 
38:	jmpFalse 49
41:	pushthis 
42:	invoke 187 0 1
48:	rpop 
49:	rtnEventQ 0
51:	setThisStack
52:	pushthis 
53:	rtn D


Class thenPart#SB#185 185 2
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
19:	rpushg 2
21:	rpushg 3
23:	rpushg 2
25:	rpushg 3
27:	rpushg 2
29:	rpushg 3
31:	rpushg 2
33:	rpushg 3
35:	pushthis 
36:	rpushg 2
38:	rpushg 3
40:	rpushg 2
42:	rpushg 3
44:	rpushg 2
46:	rpushg 3
48:	rpushg 2
50:	rpushg 3
52:	rpushg 2
54:	rpushg 3
56:	rpushg 2
58:	rpushg 3
60:	pushg 1
62:	pushc 4
64:	+
65:	storeg 3
67:	pushthis 
68:	rpushg 2
70:	rpushg 3
72:	rpushg 2
74:	rpushg 3
76:	rpushg 2
78:	rpushg 3
80:	rpushg 2
82:	rpushg 3
84:	rpushg 2
86:	rpushg 3
88:	rpushg 2
90:	rpushg 3
92:	rpushg 1
94:	pushthis 
95:	rpushg 2
97:	rpushg 3
99:	rpushg 2
101:	rpushg 3
103:	rpushg 2
105:	rpushg 3
107:	rpushg 2
109:	rpushg 3
111:	rpushg 2
113:	rpushg 3
115:	rpushg 2
117:	rpushg 3
119:	rpushg 1
121:	pushg 1
123:	pushc 1
125:	+
126:	storeg 1
128:	rtnEventQ 0
130:	setThisStack
131:	pushthis 
132:	rtn D


Class elsePart#SB#186 186 2
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
19:	rpushg 2
21:	rpushg 3
23:	rpushg 2
25:	rpushg 3
27:	rpushg 2
29:	rpushg 3
31:	rpushg 2
33:	rpushg 3
35:	rpushg 1
37:	pushg 1
39:	pushc 6
41:	eq 
42:	jmpFalse 53
45:	pushthis 
46:	invoke 188 0 1
52:	rpop 
53:	rtnEventQ 0
55:	setThisStack
56:	pushthis 
57:	rtn D


Class #S#187 187 1
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
15:	rpushg 3
17:	rpushg 2
19:	rpushg 3
21:	rpushg 2
23:	rpushg 3
25:	rpushg 2
27:	rpushg 3
29:	rpushg 2
31:	rpushg 3
33:	pushc 6
35:	storeg 3
37:	pushthis 
38:	rpushg 1
40:	rpushg 2
42:	rpushg 3
44:	rpushg 2
46:	rpushg 3
48:	rpushg 2
50:	rpushg 3
52:	rpushg 2
54:	rpushg 3
56:	rpushg 2
58:	rpushg 3
60:	rpushg 1
62:	pushc 0
64:	storeg 1
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class #S#188 188 1
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
15:	rpushg 3
17:	rpushg 2
19:	rpushg 3
21:	rpushg 2
23:	rpushg 3
25:	rpushg 2
27:	rpushg 3
29:	rpushg 2
31:	rpushg 3
33:	rpushg 2
35:	rpushg 3
37:	pushc 6
39:	storeg 3
41:	pushthis 
42:	rpushg 1
44:	rpushg 2
46:	rpushg 3
48:	rpushg 2
50:	rpushg 3
52:	rpushg 2
54:	rpushg 3
56:	rpushg 2
58:	rpushg 3
60:	rpushg 2
62:	rpushg 3
64:	rpushg 2
66:	rpushg 3
68:	rpushg 1
70:	pushc 0
72:	storeg 1
74:	rtnEventQ 0
76:	setThisStack
77:	pushthis 
78:	rtn D


Class main 196 0
allocE:
1:	pushthis 
2:	invoke 1 0 1
8:	stop 


Class EventProcessor 197 0
allocE:
1:	stop 


Class ThreadStub 198 0
allocE:
doE: 
1:	mvStack
2:	call D
4:	stop 

