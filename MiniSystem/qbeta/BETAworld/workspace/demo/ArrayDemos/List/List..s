	-- QBETA
	-- Module:gen: 
	component Comp NoOfDescs: 684
	-- ConsRef:gen: (0)BETAworld

	class Object 33
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: := (2)V: ? (2)Object
	-- pattern:gen: = (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	-- pattern:gen: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	-- pattern:gen: suspend
	-- pattern:gen: attach((1)V: ? (2)integer)
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
	-- ObjectGenerator:gen: super: (0)%inner (1)Object:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)Object
	-- Invocation:loadOrigin: (0)%inner (1)Object
	-- Invocation:loadOrigin:scan: (0)%inner (1)Object
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)Object
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)Object
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
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
	-- ModuleItem:gen (0)BETA
	-- ConsRef:gen: (0)BETA
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 3 2 (0)BETA
	rpop
	-- Module:gen: 
	-- ModuleItem:gen (0)LIB
	-- ConsRef:gen: (0)LIB
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 71 3 (0)LIB
	rpop
	-- Module:gen: 
	-- ModuleItem:gen (0)workspace
	-- ConsRef:gen: (0)workspace
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 222 4 (0)workspace
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

	class (0)BETA 3
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: integer((1)W: ? (1)integer)
	-- pattern:gen: Boolean
	-- pattern:gen: False -> (1)B: ? (1)Boolean
	-- pattern:gen: True -> (1)B: ? (1)Boolean
	-- pattern:gen: char
	-- pattern:gen: put((1)ch: ? (1)char)
	-- pattern:gen: Object
	-- pattern:gen: none
	-- pattern:gen: inner
	-- pattern:gen: (0)%inner (2)P: ? (1)Object
	-- pattern:gen: (0)%this (2)P: ? (1)Object
	-- pattern:gen: disable
	-- pattern:gen: enable
	-- pattern:gen: fork((2)S: ? (1)Object)
	-- pattern:gen: sleep((1)V: ? (1)integer)
	-- pattern:gen: core
	-- pattern:gen: thisCore -> (2)C: ? (1)core
	-- pattern:gen: Indexed((1)range: ? (1)Integer,(1)elm:< (1)Object)
	-- pattern:gen: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- pattern:gen: (0)%restart (1)Obj: ? (1)integer
	-- pattern:gen: (0)%leave (1)Obj: ? (1)integer
	-- pattern:gen: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object
	-- pattern:gen: cycle
	-- pattern:gen: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object
	-- pattern:gen: newline
	-- pattern:gen: putint((1)V: ? (1)integer)
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

	class (0)LIB 71
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: x_dummy
	-- Module:gen: 
	-- ModuleItem:gen (0)BasicSystem
	-- ConsRef:gen: (0)BasicSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 72 2 (0)BasicSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen (0)Complex
	-- ConsRef:gen: (0)Complex
	-- ObjectGenerator:gen: super: :singular:staticOff: 3
	pushThis 
	invoke 160 3 (0)Complex
	rpop
	-- Module:gen: 
	-- ModuleItem:gen (0)Containers
	-- ConsRef:gen: (0)Containers
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 73 4 (0)Containers
	rpop
	-- Module:gen: 
	-- ModuleItem:gen (0)EMC2array
	-- ConsRef:gen: (0)EMC2array
	-- ObjectGenerator:gen: super: :singular:staticOff: 5
	pushThis 
	invoke 165 5 (0)EMC2array
	rpop
	-- Module:gen: 
	-- ModuleItem:gen (0)ForkJoinSystem
	-- ConsRef:gen: (0)ForkJoinSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 6
	pushThis 
	invoke 190 6 (0)ForkJoinSystem
	rpop
	-- Module:gen: 
	-- ModuleItem:gen (0)MonitorSystem
	-- ConsRef:gen: (0)MonitorSystem
	-- ObjectGenerator:gen: super: :singular:staticOff: 7
	pushThis 
	invoke 197 7 (0)MonitorSystem
	rpop
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen (0)String
	-- ConsRef:gen: (0)String
	-- ObjectGenerator:gen: super: :singular:staticOff: 9
	pushThis 
	invoke 89 9 (0)String
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

	class (0)workspace 222
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: dummy
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen (0)demo
	-- ConsRef:gen: (0)demo
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 422 4 (0)demo
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
	-- ObjectGenerator:gen: super: (0)B (0):= 0:IS-empty: staticOff: 0
	-- Invocation:gen: (0)B (0):= 0
	-- Invocation:loadOrigin: (0)B (0):= 0
	-- Invocation:loadOrigin:scan: (0)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= 0
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
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (0)B (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)B (0):= 1
	-- Invocation:loadOrigin: (0)B (0):= 1
	-- Invocation:loadOrigin:scan: (0)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
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
	-- pattern:gen: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- pattern:gen: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- pattern:gen: length -> (1)res: ? (2)integer
	-- pattern:gen: asString -> (2)S: ? (2)Object
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
	-- ObjectGenerator:gen: super: (0)%inner (1)cycle:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)cycle
	-- Invocation:loadOrigin: (0)%inner (1)cycle
	-- Invocation:loadOrigin:scan: (0)%inner (1)cycle
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)cycle
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)cycle
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: (0)%restart (1)cycle:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (1)cycle
	-- Invocation:loadOrigin: (0)%restart (1)cycle
	-- Invocation:loadOrigin:scan: (0)%restart (1)cycle
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (1)cycle
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (1)cycle
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
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
	-- ObjectGenerator:gen: super: (0)inx (0):= (0)first:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx (0):= (0)first
	-- Invocation:loadOrigin: (0)inx (0):= (0)first
	-- Invocation:loadOrigin:scan: (0)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)first
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)first:IS-empty: staticOff: 0
	-- Invocation:gen: (0)first
	-- Invocation:loadOrigin: (0)first
	-- Invocation:loadOrigin:scan: (0)first
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)first
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: first
	pushg 1 first
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 3 inx
	-- ObjectGenerator:gen: super: (0)do:IS-empty: staticOff: 0
	-- Invocation:gen: (0)do
	-- Invocation:loadOrigin: (0)do
	-- Invocation:loadOrigin:scan: (0)do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)do
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
	-- ObjectGenerator:gen: super: (1)put(10):IS-empty: staticOff: 0
	-- Invocation:gen: (1)put(10)
	-- Invocation:loadOrigin: (1)put(10)
	-- Invocation:loadOrigin:scan: (1)put(10)
	-- Function:pushThis: 
	-- Function:loadOrigin: (1)put(10)
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
	-- pattern:load: put((1)ch: ? (1)char)
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
	-- ObjectGenerator:gen: super: (1)Indexed(20,(1)Integer):IS-empty: staticOff: 2
	-- Invocation:gen: (1)Indexed(20,(1)Integer)
	-- Invocation:loadOrigin: (1)Indexed(20,(1)Integer)
	-- Invocation:loadOrigin:scan: (1)Indexed(20,(1)Integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (1)Indexed(20,(1)Integer)
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
	-- ObjectGenerator:gen: super: (1)Integer:IS-empty: staticOff: 0
	-- Invocation:gen: (1)Integer
	-- Invocation:loadOrigin: (1)Integer
	-- Invocation:loadOrigin:scan: (1)Integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (1)Integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer((1)W: ? (1)integer)
	-- Function:invoke: 
	-- pattern:load: Indexed((1)range: ? (1)Integer,(1)elm:< (1)Object)
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
	-- ObjectGenerator:gen: super: (0)isNeg (0):= (0)V (0)< 0:IS-empty: staticOff: 0
	-- Invocation:gen: (0)isNeg (0):= (0)V (0)< 0
	-- Invocation:loadOrigin: (0)isNeg (0):= (0)V (0)< 0
	-- Invocation:loadOrigin:scan: (0)isNeg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)isNeg
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)V (0)< 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)V (0)< 0:IS-empty: staticOff: 0
	-- Invocation:gen: (0)V (0)< 0
	-- Invocation:loadOrigin: (0)V (0)< 0
	-- Invocation:loadOrigin:scan: (0)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)V
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)< 0 :E: (0)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)< 0
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
	-- pattern:load: < (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	51
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 3 isNeg
	-- ObjectGenerator:gen: super: (0)%if (0)isNeg (0)%then% (0)V (0):= 0 (0)- (0)V:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (0)isNeg (0)%then% (0)V (0):= 0 (0)- (0)V
	-- Invocation:loadOrigin: (0)%if (0)isNeg (0)%then% (0)V (0):= 0 (0)- (0)V
	-- Invocation:loadOrigin:scan: (0)%if (0)isNeg (0)%then% (0)V (0):= 0 (0)- (0)V
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (0)isNeg (0)%then% (0)V (0):= 0 (0)- (0)V
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (0)isNeg (0)%then% (0)V (0):= 0 (0)- (0)V
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (0)isNeg:IS-empty: staticOff: 0
	-- Invocation:gen: (0)isNeg
	-- Invocation:loadOrigin: (0)isNeg
	-- Invocation:loadOrigin:scan: (0)isNeg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)isNeg
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: isNeg
	pushg 3 isNeg
	jmpFalse L29
	-- ObjectGenerator:gen: super: (0)V (0):= 0 (0)- (0)V:IS-empty: staticOff: 0
	-- Invocation:gen: (0)V (0):= 0 (0)- (0)V
	-- Invocation:loadOrigin: (0)V (0):= 0 (0)- (0)V
	-- Invocation:loadOrigin:scan: (0)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= 0 (0)- (0)V
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 0 (0)- (0)V:IS-empty: staticOff: 0
	-- Invocation:gen: 0 (0)- (0)V
	-- Invocation:loadOrigin: 0 (0)- (0)V
	-- Invocation:loadOrigin:scan: 0
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: (0)- (0)V :E: 0
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 0
	-- Invocation:loadOrigin:scan: (0)- (0)V
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)V:IS-empty: staticOff: 0
	-- Invocation:gen: (0)V
	-- Invocation:loadOrigin: (0)V
	-- Invocation:loadOrigin:scan: (0)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)V
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 V
 L29:
	-- ObjectGenerator:gen: super: (0)doit:IS-empty: staticOff: 0
	-- Invocation:gen: (0)doit
	-- Invocation:loadOrigin: (0)doit
	-- Invocation:loadOrigin:scan: (0)doit
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)doit
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

	class (0)BasicSystem 72
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

	class (0)Complex 160
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Complex((1)re: ? (2)integer,(2)im: ? (2)integer)
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

	class (0)Containers 73
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: xxx
	-- Module:gen: 
	-- ModuleItem:gen (0)mQueue
	-- ConsRef:gen: (0)mQueue
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 74 2 (0)mQueue
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

	class (0)EMC2array 165
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: Array
	-- pattern:gen: Range((1)low: ? (2)integer,(2)upp: ? (2)integer)
	-- pattern:gen: D1_Array((3)R: ? (1)Range,(3)ElmType:< (2)Object)
	-- pattern:gen: D2_Array((3)R1: ? (1)Range,(4)R2: ? (1)Range) -> (5)res: ? (1)D2_array
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

	class (0)ForkJoinSystem 190
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

	class (0)MonitorSystem 197
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

	class (0)String 89
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: String((2)S: ? (1)String)
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

	class (0)demo 422
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: olsen_nils
	-- Module:gen: 
	-- ModuleItem:gen (0)ArrayDemos
	-- ConsRef:gen: (0)ArrayDemos
	-- ObjectGenerator:gen: super: :singular:staticOff: 2
	pushThis 
	invoke 423 2 (0)ArrayDemos
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
	-- ObjectGenerator:gen: super: (0)res (0):= (0)%get 0:IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (0)%get 0
	-- Invocation:loadOrigin: (0)res (0):= (0)%get 0
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)%get 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%get 0:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%get 0
	-- Invocation:loadOrigin: (0)%get 0
	-- Invocation:loadOrigin:scan: (0)%get 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%get 0
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get 0
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
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
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (0)%if (1)cond (0)%then% 
    (2)thenPart
    (0)%leave (2)_L:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)cond (0)%then% 
    (2)thenPart
    (0)%leave (2)_L
	-- Invocation:loadOrigin: (0)%if (1)cond (0)%then% 
    (2)thenPart
    (0)%leave (2)_L
	-- Invocation:loadOrigin:scan: (0)%if (1)cond (0)%then% 
    (2)thenPart
    (0)%leave (2)_L
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)cond (0)%then% 
    (2)thenPart
    (0)%leave (2)_L
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)cond (0)%then% 
    (2)thenPart
    (0)%leave (2)_L
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)cond:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cond
	-- Invocation:loadOrigin: (1)cond
	-- Invocation:loadOrigin:scan: (1)cond
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cond
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
	invoke 524 0 #S#524
	rpop
 L50:
	-- ObjectGenerator:gen: super: (1)elsePart:IS-empty: staticOff: 0
	-- Invocation:gen: (1)elsePart
	-- Invocation:loadOrigin: (1)elsePart
	-- Invocation:loadOrigin:scan: (1)elsePart
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)elsePart
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
	-- ObjectGenerator:gen: super: (0)%if (1)isNeg (0)%then% (2)put('-'):IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)isNeg (0)%then% (2)put('-')
	-- Invocation:loadOrigin: (0)%if (1)isNeg (0)%then% (2)put('-')
	-- Invocation:loadOrigin:scan: (0)%if (1)isNeg (0)%then% (2)put('-')
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)isNeg (0)%then% (2)put('-')
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)isNeg (0)%then% (2)put('-')
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)isNeg:IS-empty: staticOff: 0
	-- Invocation:gen: (1)isNeg
	-- Invocation:loadOrigin: (1)isNeg
	-- Invocation:loadOrigin:scan: (1)isNeg
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)isNeg
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: isNeg
	pushg 3 isNeg
	jmpFalse L55
	-- ObjectGenerator:gen: super: (2)put('-'):IS-empty: staticOff: 0
	-- Invocation:gen: (2)put('-')
	-- Invocation:loadOrigin: (2)put('-')
	-- Invocation:loadOrigin:scan: (2)put('-')
	-- Function:pushThis: 
	-- Function:loadOrigin: (2)put('-')
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
	-- pattern:load: put((1)ch: ? (1)char)
	%put 2
 L55:
	-- ObjectGenerator:gen: super: (0)%for 1 (0)%to% (1)L (0)%do% 
    (1)i: ? (4)integer
    (0)i (0):= (3)L (0)+ 1 (0)- (1)inx
    (4)put('0' (0)+ (3)D.(0)%get (0)i):IS-empty: staticOff: 0
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
	-- pattern:gen: BasicProcess((2)id: ? (2)String)
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
	-- ObjectGenerator:gen: super: (0)Lock:IS-empty: staticOff: 6
	-- Invocation:gen: (0)Lock
	-- Invocation:loadOrigin: (0)Lock
	-- Invocation:loadOrigin:scan: (0)Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)Lock
	-- AdjustOrigin: 0
	-- on : 0
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
	-- ObjectGenerator:gen: super: (0)init:IS-empty: staticOff: 0
	-- Invocation:gen: (0)init
	-- Invocation:loadOrigin: (0)init
	-- Invocation:loadOrigin:scan: (0)init
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)init
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 159 0 init
	rpop
	-- ObjectGenerator:gen: super: (2)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (2)inner
	-- Invocation:loadOrigin: (2)inner
	-- Invocation:loadOrigin:scan: (2)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (2)inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: (0)cores.(0)init:IS-empty: staticOff: 0
	-- Invocation:gen: (0)cores.(0)init
	-- Invocation:loadOrigin: (0)cores.(0)init
	-- Invocation:loadOrigin:scan: (0)cores
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)cores
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)init :E: (0)cores
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: cores
	rpushg 2 cores
	-- Invocation:loadOrigin:scan: (0)init
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
	-- pattern:gen: + (2)C: ? (2)Complex -> (3)res: ? (2)Complex
	-- pattern:gen: - (2)C: ? (2)Complex -> (3)res: ? (2)Complex
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

	class (0)mQueue 74
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
	-- pattern:gen: put((1)e: ? (3)integer) -> (2)res: ? (2)array
	-- pattern:gen: get -> (1)res: ? (3)integer
	-- pattern:gen: nxt -> (1)res: ? (3)integer
	-- pattern:gen: prv -> (1)res: ? (3)integer
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
	-- ObjectGenerator:gen: super: (0)pos (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)pos (0):= 1
	-- Invocation:loadOrigin: (0)pos (0):= 1
	-- Invocation:loadOrigin:scan: (0)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)pos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 pos
	-- ObjectGenerator:gen: super: (0)%inner (1)Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)Array
	-- Invocation:loadOrigin: (0)%inner (1)Array
	-- Invocation:loadOrigin:scan: (0)%inner (1)Array
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)Array
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)Array
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
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
	-- ObjectGenerator:gen: super: ((0)upp (0)- (0)low) (0)+ 1:IS-empty: staticOff: 3
	-- Invocation:gen: ((0)upp (0)- (0)low) (0)+ 1
	-- Invocation:loadOrigin: ((0)upp (0)- (0)low) (0)+ 1
	-- Invocation:loadOrigin:scan: ((0)upp (0)- (0)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)upp (0)- (0)low)
	-- Invocation:loadOrigin: (0)upp (0)- (0)low
	-- Invocation:loadOrigin:scan: (0)upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)upp
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)- (0)low :E: (0)upp
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Invocation:loadOrigin:scan: (0)- (0)low
	-- BE:loadOrigin:E: (0)- (0)low
	-- next not assign: (0)+ 1 :E: (0)- (0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (0)low
	-- Invocation:loadOrigin: (0)low
	-- Invocation:loadOrigin:scan: (0)low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)low
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	pushThis 
	storeg 3 noof
	-- pattern:gen: check((1)inx: ? (3)integer)
	-- pattern:gen: print
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L64:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (0)noof (0)< 1 (0)%then% 
    "range error\n".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (0)noof (0)< 1 (0)%then% 
    "range error\n".(0)print
	-- Invocation:loadOrigin: (0)%if (0)noof (0)< 1 (0)%then% 
    "range error\n".(0)print
	-- Invocation:loadOrigin:scan: (0)%if (0)noof (0)< 1 (0)%then% 
    "range error\n".(0)print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (0)noof (0)< 1 (0)%then% 
    "range error\n".(0)print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (0)noof (0)< 1 (0)%then% 
    "range error\n".(0)print
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (0)noof (0)< 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)noof (0)< 1
	-- Invocation:loadOrigin: (0)noof (0)< 1
	-- Invocation:loadOrigin:scan: (0)noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)noof
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)< 1 :E: (0)noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: (0)< 1
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
	-- pattern:load: < (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	51
	jmpFalse L66
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 565 0 #S#565
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
	-- Invocation:loadOrigin: (0)Array
	-- Invocation:loadOrigin:scan: (0)Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  166
	-- pattern:gen: putAt((1)inx: ? (3)integer,(2)exp: ? (3)integer) -> (2)res: ? (2)Array
	-- pattern:gen: getAt((1)inx: ? (3)integer) -> (2)res: ? (3)integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=185
	innerA  4
	rtnInner
	DO:
	doEventQ
	mvStack 
 L67:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)noof (0):= (0)R.(0)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (0)noof (0):= (0)R.(0)noof
	-- Invocation:loadOrigin: (0)noof (0):= (0)R.(0)noof
	-- Invocation:loadOrigin:scan: (0)noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)noof
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)R.(0)noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)R.(0)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (0)R.(0)noof
	-- Invocation:loadOrigin: (0)R.(0)noof
	-- Invocation:loadOrigin:scan: (0)R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)R
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)noof :E: (0)R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: (0)noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 2 noof
	-- ObjectGenerator:gen: super: (0)rep (0):= (2)Indexed((0)noof,(2)integer):IS-empty: staticOff: 0
	-- Invocation:gen: (0)rep (0):= (2)Indexed((0)noof,(2)integer)
	-- Invocation:loadOrigin: (0)rep (0):= (2)Indexed((0)noof,(2)integer)
	-- Invocation:loadOrigin:scan: (0)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)rep
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)Indexed((0)noof,(2)integer)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Indexed((0)noof,(2)integer):IS-empty: staticOff: 0
	-- Invocation:gen: (2)Indexed((0)noof,(2)integer)
	-- Invocation:loadOrigin: (2)Indexed((0)noof,(2)integer)
	-- Invocation:loadOrigin:scan: (2)Indexed((0)noof,(2)integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (2)Indexed((0)noof,(2)integer)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (0)noof
	-- Invocation:loadOrigin: (0)noof
	-- Invocation:loadOrigin:scan: (0)noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)noof
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- ObjectGenerator:gen: super: (2)integer:IS-empty: staticOff: 0
	-- Invocation:gen: (2)integer
	-- Invocation:loadOrigin: (2)integer
	-- Invocation:loadOrigin:scan: (2)integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (2)integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer((1)W: ? (1)integer)
	-- Function:invoke: 
	-- pattern:load: Indexed((1)range: ? (1)Integer,(1)elm:< (1)Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 rep
	-- ObjectGenerator:gen: super: (0)%inner (1)D1_Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)D1_Array
	-- Invocation:loadOrigin: (0)%inner (1)D1_Array
	-- Invocation:loadOrigin:scan: (0)%inner (1)D1_Array
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)D1_Array
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)D1_Array
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
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
	-- Invocation:loadOrigin: (0)Array
	-- Invocation:loadOrigin:scan: (0)Array
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)Array
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  166
	-- pattern:gen: putAt((1)inx1: ? (3)integer,(2)inx2: ? (3)integer,(3)exp: ? (3)integer) -> (2)res: ? (2)D2_Array
	-- pattern:gen: getAt((1)inx1: ? (3)integer,(2)inx2: ? (3)integer) -> (3)exp: ? (3)integer
	-- pattern:gen: print
	-- vdtAdd: inx=1 descInx=189
	rtnInner
	DO:
	doEventQ
	mvStack 
 L69:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)rep (0):= (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer):IS-empty: staticOff: 0
	-- Invocation:gen: (0)rep (0):= (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer)
	-- Invocation:loadOrigin: (0)rep (0):= (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer)
	-- Invocation:loadOrigin:scan: (0)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)rep
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer):IS-empty: staticOff: 0
	-- Invocation:gen: (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer)
	-- Invocation:loadOrigin: (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer)
	-- Invocation:loadOrigin:scan: (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (2)indexed((0)R1.(0)noof (0)* (0)R2.(0)noof,(2)integer)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)R1.(0)noof (0)* (0)R2.(0)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (0)R1.(0)noof (0)* (0)R2.(0)noof
	-- Invocation:loadOrigin: (0)R1.(0)noof (0)* (0)R2.(0)noof
	-- Invocation:loadOrigin:scan: (0)R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)R1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)noof :E: (0)R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: (0)noof
	-- next not assign: (0)* (0)R2.(0)noof :E: (0)noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: (0)* (0)R2.(0)noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)R2.(0)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (0)R2.(0)noof
	-- Invocation:loadOrigin: (0)R2.(0)noof
	-- Invocation:loadOrigin:scan: (0)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)R2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)noof :E: (0)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Binary:invoke: 
	-- pattern:load: * (1)V: ? (2)integer -> (2)R: ? (2)integer
	66
	-- ObjectGenerator:gen: super: (2)integer:IS-empty: staticOff: 0
	-- Invocation:gen: (2)integer
	-- Invocation:loadOrigin: (2)integer
	-- Invocation:loadOrigin:scan: (2)integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (2)integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer((1)W: ? (1)integer)
	-- Function:invoke: 
	-- pattern:load: Indexed((1)range: ? (1)Integer,(1)elm:< (1)Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 rep
	-- ObjectGenerator:gen: super: (0)res (0):= (0)%this (1)D2_Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (0)%this (1)D2_Array
	-- Invocation:loadOrigin: (0)res (0):= (0)%this (1)D2_Array
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)%this (1)D2_Array
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%this (1)D2_Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%this (1)D2_Array
	-- Invocation:loadOrigin: (0)%this (1)D2_Array
	-- Invocation:loadOrigin:scan: (0)%this (1)D2_Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (1)D2_Array
	-- AdjustOrigin: 0
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (1)D2_Array
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 5 res
	-- ObjectGenerator:gen: super: "D2_array:".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "D2_array:".(0)print
	-- Invocation:loadOrigin: "D2_array:".(0)print
	-- Invocation:loadOrigin:scan: "D2_array:"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText D2_array:
	-- next not assign: (0)print :E: "D2_array:"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
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
	-- Invocation:loadOrigin: (0)BasicSystem
	-- Invocation:loadOrigin:scan: (0)BasicSystem
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)BasicSystem
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
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
	-- ObjectGenerator:gen: super: (0)%inner (1)ForkJoinSystem:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)ForkJoinSystem
	-- Invocation:loadOrigin: (0)%inner (1)ForkJoinSystem
	-- Invocation:loadOrigin:scan: (0)%inner (1)ForkJoinSystem
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)ForkJoinSystem
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)ForkJoinSystem
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
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
	-- Invocation:loadOrigin: (2)LIB.(0)BasicSystem.(0)basicSystem
	-- Invocation:loadOrigin:scan: (2)LIB
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)LIB
	-- AdjustOrigin: 8
	rpushg 8 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)BasicSystem :E: (2)LIB
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: LIB
	rpushg 3 LIB
	-- Invocation:loadOrigin:scan: (0)BasicSystem
	-- next not assign: (0)basicSystem :E: (0)BasicSystem
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: BasicSystem
	rpushg 2 BasicSystem
	-- Invocation:loadOrigin:scan: (0)basicSystem
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
	-- ObjectGenerator:gen: super: (2)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (2)inner
	-- Invocation:loadOrigin: (2)inner
	-- Invocation:loadOrigin:scan: (2)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (2)inner
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
	-- pattern:gen: length -> (1)V: ? (3)integer
	-- pattern:gen: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- pattern:gen: + (2)S: ? (2)String -> (3)V: ? (2)String
	-- pattern:gen: asLowerCase -> (2)T: ? (2)String
	-- pattern:gen: scan
	-- pattern:gen: print
	-- pattern:gen: = (2)S: ? (2)string -> (1)B: ? (3)boolean
	-- pattern:gen: <= (2)S: ? (2)string -> (1)B: ? (3)boolean
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

	class (0)ArrayDemos 423
	rstore 1 origin
	allocEventQ
	mvStack 
	-- VarRef:gen: _xxx
	-- Module:gen: 
	-- Module:gen: 
	-- Module:gen: 
	-- ModuleItem:gen (0)List
	-- ConsRef:gen: (0)List
	-- ObjectGenerator:gen: super: :singular:staticOff: 4
	pushThis 
	invoke 434 4 (0)List
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

	class #S#524 524
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L79:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)thenPart:IS-empty: staticOff: 0
	-- Invocation:gen: (2)thenPart
	-- Invocation:loadOrigin: (2)thenPart
	-- Invocation:loadOrigin:scan: (2)thenPart
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)thenPart
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thenPart
	sendv 1 thenPart
	rpop
	-- ObjectGenerator:gen: super: (0)%leave (2)_L:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%leave (2)_L
	-- Invocation:loadOrigin: (0)%leave (2)_L
	-- Invocation:loadOrigin:scan: (0)%leave (2)_L
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%leave (2)_L
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%leave (1)Obj: ? (1)integer(0)%leave (2)_L
	-- KeyWord:invoke: 
	-- pattern:load: (0)%leave (1)Obj: ? (1)integer
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
	-- ObjectGenerator:gen: super: (0)%if (2)inx (0)<= (2)last (0)%then% 
    (3)body
    (3)inx (0):= (3)inx (0)+ 1
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)inx (0)<= (2)last (0)%then% 
    (3)body
    (3)inx (0):= (3)inx (0)+ 1
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (2)inx (0)<= (2)last (0)%then% 
    (3)body
    (3)inx (0):= (3)inx (0)+ 1
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (2)inx (0)<= (2)last (0)%then% 
    (3)body
    (3)inx (0):= (3)inx (0)+ 1
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)inx (0)<= (2)last (0)%then% 
    (3)body
    (3)inx (0):= (3)inx (0)+ 1
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)inx (0)<= (2)last (0)%then% 
    (3)body
    (3)inx (0):= (3)inx (0)+ 1
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)inx (0)<= (2)last:IS-empty: staticOff: 0
	-- Invocation:gen: (2)inx (0)<= (2)last
	-- Invocation:loadOrigin: (2)inx (0)<= (2)last
	-- Invocation:loadOrigin:scan: (2)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)inx
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)<= (2)last :E: (2)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Invocation:loadOrigin:scan: (0)<= (2)last
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)last:IS-empty: staticOff: 0
	-- Invocation:gen: (2)last
	-- Invocation:loadOrigin: (2)last
	-- Invocation:loadOrigin:scan: (2)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	pushg 2 last
	-- Binary:invoke: 
	-- pattern:load: <= (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	52
	jmpFalse L83
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 525 0 #S#525
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
	-- ObjectGenerator:gen: super: (2)L (0):= (2)L (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)L (0):= (2)L (0)+ 1
	-- Invocation:loadOrigin: (2)L (0):= (2)L (0)+ 1
	-- Invocation:loadOrigin:scan: (2)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)L (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)L (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)L (0)+ 1
	-- Invocation:loadOrigin: (2)L (0)+ 1
	-- Invocation:loadOrigin:scan: (2)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (2)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 2 L
	-- ObjectGenerator:gen: super: (2)D.(0)%put (2)V (0)/% 10 (0)%at% (2)L:IS-empty: staticOff: 0
	-- Invocation:gen: (2)D.(0)%put (2)V (0)/% 10 (0)%at% (2)L
	-- Invocation:loadOrigin: (2)D.(0)%put (2)V (0)/% 10 (0)%at% (2)L
	-- Invocation:loadOrigin:scan: (2)D
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)D
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)%put (2)V (0)/% 10 (0)%at% (2)L :E: (2)D
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: D
	rpushg 2 D
	-- Invocation:loadOrigin:scan: (0)%put (2)V (0)/% 10 (0)%at% (2)L
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put (2)V (0)/% 10 (0)%at% (2)L
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (2)V (0)/% 10:IS-empty: staticOff: 0
	-- Invocation:gen: (2)V (0)/% 10
	-- Invocation:loadOrigin: (2)V (0)/% 10
	-- Invocation:loadOrigin:scan: (2)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)/% 10 :E: (2)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)/% 10
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
	-- pattern:load: /% (1)V: ? (2)integer -> (2)R: ? (2)integer
	69
	-- name::gen: 
	-- ObjectGenerator:gen: super: (2)L:IS-empty: staticOff: 0
	-- Invocation:gen: (2)L
	-- Invocation:loadOrigin: (2)L
	-- Invocation:loadOrigin:scan: (2)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: (2)V (0):= (2)V (0)// 10:IS-empty: staticOff: 0
	-- Invocation:gen: (2)V (0):= (2)V (0)// 10
	-- Invocation:loadOrigin: (2)V (0):= (2)V (0)// 10
	-- Invocation:loadOrigin:scan: (2)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)V (0)// 10
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)V (0)// 10:IS-empty: staticOff: 0
	-- Invocation:gen: (2)V (0)// 10
	-- Invocation:loadOrigin: (2)V (0)// 10
	-- Invocation:loadOrigin:scan: (2)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)// 10 :E: (2)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)// 10
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
	-- pattern:load: // (1)V: ? (2)integer -> (2)B: ? (2)Integer
	68
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 V
	-- ObjectGenerator:gen: super: (0)%if (2)V (0)> 0 (0)%then% 
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)V (0)> 0 (0)%then% 
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (2)V (0)> 0 (0)%then% 
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (2)V (0)> 0 (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)V (0)> 0 (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)V (0)> 0 (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)V (0)> 0:IS-empty: staticOff: 0
	-- Invocation:gen: (2)V (0)> 0
	-- Invocation:loadOrigin: (2)V (0)> 0
	-- Invocation:loadOrigin:scan: (2)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)V
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)> 0 :E: (2)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)> 0
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
	-- pattern:load: > (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	gt
	jmpFalse L86
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 526 0 #S#526
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
	-- Invocation:loadOrigin: (0)%for 1 (0)%to% (1)L (0)%do% 
    (1)i: ? (4)integer
    (0)i (0):= (3)L (0)+ 1 (0)- (1)inx
    (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- Invocation:loadOrigin:scan: (0)%for 1 (0)%to% (1)L (0)%do% 
    (1)i: ? (4)integer
    (0)i (0):= (3)L (0)+ 1 (0)- (1)inx
    (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%for 1 (0)%to% (1)L (0)%do% 
    (1)i: ? (4)integer
    (0)i (0):= (3)L (0)+ 1 (0)- (1)inx
    (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object(0)%for 1 (0)%to% (1)L (0)%do% 
    (1)i: ? (4)integer
    (0)i (0):= (3)L (0)+ 1 (0)- (1)inx
    (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: (1)L:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L
	-- Invocation:loadOrigin: (1)L
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
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
	-- ObjectGenerator:gen: super: ((0)%this (1)BasicProcess).(0)suspend:IS-empty: staticOff: 0
	-- Invocation:gen: ((0)%this (1)BasicProcess).(0)suspend
	-- Invocation:loadOrigin: ((0)%this (1)BasicProcess).(0)suspend
	-- Invocation:loadOrigin:scan: ((0)%this (1)BasicProcess)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)%this (1)BasicProcess)
	-- Invocation:loadOrigin: (0)%this (1)BasicProcess
	-- Invocation:loadOrigin:scan: (0)%this (1)BasicProcess
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (1)BasicProcess
	-- AdjustOrigin: 0
	-- BE:loadOrigin:E: (0)%this (1)BasicProcess
	-- next not assign: (0)suspend :E: (0)%this (1)BasicProcess
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (1)BasicProcess
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Invocation:loadOrigin:scan: (0)suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: (3)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (3)inner
	-- Invocation:loadOrigin: (3)inner
	-- Invocation:loadOrigin:scan: (3)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  2
	-- ObjectGenerator:gen: super: (0)status (0):= (1)P_status.(0)TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: (0)status (0):= (1)P_status.(0)TERMINATED
	-- Invocation:loadOrigin: (0)status (0):= (1)P_status.(0)TERMINATED
	-- Invocation:loadOrigin:scan: (0)status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)status
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)P_status.(0)TERMINATED
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)P_status.(0)TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: (1)P_status.(0)TERMINATED
	-- Invocation:loadOrigin: (1)P_status.(0)TERMINATED
	-- Invocation:loadOrigin:scan: (1)P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)P_status
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)TERMINATED :E: (1)P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: (0)TERMINATED
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: TERMINATED
	pushg 3 TERMINATED
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: ((0)%this (1)Scheduler).(0)suspend:IS-empty: staticOff: 0
	-- Invocation:gen: ((0)%this (1)Scheduler).(0)suspend
	-- Invocation:loadOrigin: ((0)%this (1)Scheduler).(0)suspend
	-- Invocation:loadOrigin:scan: ((0)%this (1)Scheduler)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)%this (1)Scheduler)
	-- Invocation:loadOrigin: (0)%this (1)Scheduler
	-- Invocation:loadOrigin:scan: (0)%this (1)Scheduler
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (1)Scheduler
	-- AdjustOrigin: 0
	-- BE:loadOrigin:E: (0)%this (1)Scheduler
	-- next not assign: (0)suspend :E: (0)%this (1)Scheduler
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (1)Scheduler
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Invocation:loadOrigin:scan: (0)suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: (1)sch.(0)add:IS-empty: staticOff: 0
	-- Invocation:gen: (1)sch.(0)add
	-- Invocation:loadOrigin: (1)sch.(0)add
	-- Invocation:loadOrigin:scan: (1)sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)sch
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)add :E: (1)sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: (0)add
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: add
	invoke 136 0 add
	rpop
	-- ObjectGenerator:gen: super: (0)do:IS-empty: staticOff: 0
	-- Invocation:gen: (0)do
	-- Invocation:loadOrigin: (0)do
	-- Invocation:loadOrigin:scan: (0)do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)do
	-- AdjustOrigin: 0
	-- on : 0
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
	-- pattern:gen: attach((2)M: ? (2)Scheduler)
	-- pattern:gen: do
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L95:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: ((0)%this (1)Core).(0)suspend:IS-empty: staticOff: 0
	-- Invocation:gen: ((0)%this (1)Core).(0)suspend
	-- Invocation:loadOrigin: ((0)%this (1)Core).(0)suspend
	-- Invocation:loadOrigin:scan: ((0)%this (1)Core)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)%this (1)Core)
	-- Invocation:loadOrigin: (0)%this (1)Core
	-- Invocation:loadOrigin:scan: (0)%this (1)Core
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (1)Core
	-- AdjustOrigin: 0
	-- BE:loadOrigin:E: (0)%this (1)Core
	-- next not assign: (0)suspend :E: (0)%this (1)Core
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (1)Core
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Invocation:loadOrigin:scan: (0)suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
	-- ObjectGenerator:gen: super: (0)do:IS-empty: staticOff: 0
	-- Invocation:gen: (0)do
	-- Invocation:loadOrigin: (0)do
	-- Invocation:loadOrigin:scan: (0)do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)do
	-- AdjustOrigin: 0
	-- on : 0
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
	-- pattern:gen: Element((2)elm: ? (4)Object) -> (3)res: ? (1)Element
	-- VarRef:gen: head
	-- VarRef:gen: last
	-- pattern:gen: scan
	-- pattern:gen: scanFromLast
	-- pattern:gen: insert((2)elm: ? (4)Object)
	-- pattern:gen: remove((2)elm: ? (4)Object)
	-- pattern:gen: removeNext -> (2)elm: ? (4)Object
	-- pattern:gen: isEmpty -> (1)B: ? (4)Boolean
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
	-- Invocation:loadOrigin: (3)LIB.(0)Containers.(0)mQueue.(0)Queue
	-- Invocation:loadOrigin:scan: (3)LIB
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)LIB
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)Containers :E: (3)LIB
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: LIB
	rpushg 3 LIB
	-- Invocation:loadOrigin:scan: (0)Containers
	-- next not assign: (0)mQueue :E: (0)Containers
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: Containers
	rpushg 4 Containers
	-- Invocation:loadOrigin:scan: (0)mQueue
	-- next not assign: (0)Queue :E: (0)mQueue
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- Module:load: 
	-- ConsRef:load: mQueue
	rpushg 2 mQueue
	-- Invocation:loadOrigin:scan: (0)Queue
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
	-- ObjectGenerator:gen: super: (1)Lock:IS-empty: staticOff: 2
	-- Invocation:gen: (1)Lock
	-- Invocation:loadOrigin: (1)Lock
	-- Invocation:loadOrigin:scan: (1)Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Lock
	-- AdjustOrigin: 0
	-- on : 1
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
	-- pattern:gen: running -> (1)B: ? (4)Boolean
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
	-- ObjectGenerator:gen: super: (1)ProcessQueue:IS-empty: staticOff: 2
	-- Invocation:gen: (1)ProcessQueue
	-- Invocation:loadOrigin: (1)ProcessQueue
	-- Invocation:loadOrigin:scan: (1)ProcessQueue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)ProcessQueue
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 132 2 ProcessQueue
	rpop
	-- ConsRef:gen: L
	-- ObjectGenerator:gen: super: (1)Lock:IS-empty: staticOff: 3
	-- Invocation:gen: (1)Lock
	-- Invocation:loadOrigin: (1)Lock
	-- Invocation:loadOrigin:scan: (1)Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Lock
	-- AdjustOrigin: 0
	-- on : 1
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
	-- pattern:gen: insert((2)P: ? (2)BasicProcess)
	-- pattern:gen: removeNext -> (2)P: ? (2)BasicProcess
	-- pattern:gen: remove((2)P: ? (2)BasicProcess)
	-- pattern:gen: isEmpty -> (1)B: ? (4)Boolean
	-- pattern:gen: display
	-- pattern:gen: addWaiting
	-- pattern:gen: dcrWaiting
	-- pattern:gen: hasWaiting -> (1)B: ? (4)boolean
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
	-- ObjectGenerator:gen: super: (1)Lock:IS-empty: staticOff: 2
	-- Invocation:gen: (1)Lock
	-- Invocation:loadOrigin: (1)Lock
	-- Invocation:loadOrigin:scan: (1)Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Lock
	-- AdjustOrigin: 0
	-- on : 1
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
	-- ObjectGenerator:gen: super: (1)SQS.(0)init:IS-empty: staticOff: 0
	-- Invocation:gen: (1)SQS.(0)init
	-- Invocation:loadOrigin: (1)SQS.(0)init
	-- Invocation:loadOrigin:scan: (1)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)SQS
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)init :E: (1)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)init
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
	-- ObjectGenerator:gen: super: (0)res (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im):IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin: (0)res (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im):IS-empty: staticOff: 0
	-- Invocation:gen: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin:scan: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)re (0)+ (0)C.(0)re:IS-empty: staticOff: 0
	-- Invocation:gen: (1)re (0)+ (0)C.(0)re
	-- Invocation:loadOrigin: (1)re (0)+ (0)C.(0)re
	-- Invocation:loadOrigin:scan: (1)re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ (0)C.(0)re :E: (1)re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Invocation:loadOrigin:scan: (0)+ (0)C.(0)re
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)C.(0)re:IS-empty: staticOff: 0
	-- Invocation:gen: (0)C.(0)re
	-- Invocation:loadOrigin: (0)C.(0)re
	-- Invocation:loadOrigin:scan: (0)C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)re :E: (0)C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: (0)re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- ObjectGenerator:gen: super: (1)im (0)+ (0)C.(0)im:IS-empty: staticOff: 0
	-- Invocation:gen: (1)im (0)+ (0)C.(0)im
	-- Invocation:loadOrigin: (1)im (0)+ (0)C.(0)im
	-- Invocation:loadOrigin:scan: (1)im
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)im
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ (0)C.(0)im :E: (1)im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Invocation:loadOrigin:scan: (0)+ (0)C.(0)im
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)C.(0)im:IS-empty: staticOff: 0
	-- Invocation:gen: (0)C.(0)im
	-- Invocation:loadOrigin: (0)C.(0)im
	-- Invocation:loadOrigin:scan: (0)C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)im :E: (0)C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: (0)im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Function:invoke: 
	-- pattern:load: Complex((1)re: ? (2)integer,(2)im: ? (2)integer)
	invoke 161 0 Complex
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (0)res (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im):IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin: (0)res (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im):IS-empty: staticOff: 0
	-- Invocation:gen: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Invocation:loadOrigin:scan: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (2)Complex((1)re (0)+ (0)C.(0)re,(1)im (0)+ (0)C.(0)im)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)re (0)+ (0)C.(0)re:IS-empty: staticOff: 0
	-- Invocation:gen: (1)re (0)+ (0)C.(0)re
	-- Invocation:loadOrigin: (1)re (0)+ (0)C.(0)re
	-- Invocation:loadOrigin:scan: (1)re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ (0)C.(0)re :E: (1)re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Invocation:loadOrigin:scan: (0)+ (0)C.(0)re
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)C.(0)re:IS-empty: staticOff: 0
	-- Invocation:gen: (0)C.(0)re
	-- Invocation:loadOrigin: (0)C.(0)re
	-- Invocation:loadOrigin:scan: (0)C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)re :E: (0)C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: (0)re
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- ObjectGenerator:gen: super: (1)im (0)+ (0)C.(0)im:IS-empty: staticOff: 0
	-- Invocation:gen: (1)im (0)+ (0)C.(0)im
	-- Invocation:loadOrigin: (1)im (0)+ (0)C.(0)im
	-- Invocation:loadOrigin:scan: (1)im
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)im
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ (0)C.(0)im :E: (1)im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Invocation:loadOrigin:scan: (0)+ (0)C.(0)im
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)C.(0)im:IS-empty: staticOff: 0
	-- Invocation:gen: (0)C.(0)im
	-- Invocation:loadOrigin: (0)C.(0)im
	-- Invocation:loadOrigin:scan: (0)C
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)C
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)im :E: (0)C
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C
	rpushg 2 C
	-- Invocation:loadOrigin:scan: (0)im
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Function:invoke: 
	-- pattern:load: Complex((1)re: ? (2)integer,(2)im: ? (2)integer)
	invoke 161 0 Complex
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (3)put('C'):IS-empty: staticOff: 0
	-- Invocation:gen: (3)put('C')
	-- Invocation:loadOrigin: (3)put('C')
	-- Invocation:loadOrigin:scan: (3)put('C')
	-- Function:pushThis: 
	-- Function:loadOrigin: (3)put('C')
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
	-- pattern:load: put((1)ch: ? (1)char)
	%put 2
	-- ObjectGenerator:gen: super: (3)putint((1)re):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((1)re)
	-- Invocation:loadOrigin: (3)putint((1)re)
	-- Invocation:loadOrigin:scan: (3)putint((1)re)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((1)re)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)re:IS-empty: staticOff: 0
	-- Invocation:gen: (1)re
	-- Invocation:loadOrigin: (1)re
	-- Invocation:loadOrigin:scan: (1)re
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)re
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: re
	pushg 1 re
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: (3)put(','):IS-empty: staticOff: 0
	-- Invocation:gen: (3)put(',')
	-- Invocation:loadOrigin: (3)put(',')
	-- Invocation:loadOrigin:scan: (3)put(',')
	-- Function:pushThis: 
	-- Function:loadOrigin: (3)put(',')
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
	-- pattern:load: put((1)ch: ? (1)char)
	%put 2
	-- ObjectGenerator:gen: super: (3)putint((1)im):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((1)im)
	-- Invocation:loadOrigin: (3)putint((1)im)
	-- Invocation:loadOrigin:scan: (3)putint((1)im)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((1)im)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)im:IS-empty: staticOff: 0
	-- Invocation:gen: (1)im
	-- Invocation:loadOrigin: (1)im
	-- Invocation:loadOrigin:scan: (1)im
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)im
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: im
	pushg 2 im
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: (3)put(10):IS-empty: staticOff: 0
	-- Invocation:gen: (3)put(10)
	-- Invocation:loadOrigin: (3)put(10)
	-- Invocation:loadOrigin:scan: (3)put(10)
	-- Function:pushThis: 
	-- Function:loadOrigin: (3)put(10)
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
	-- pattern:load: put((1)ch: ? (1)char)
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
	-- ObjectGenerator:gen: super: (1)rep.(0)%put (0)e (0)%at% (1)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)%put (0)e (0)%at% (1)pos
	-- Invocation:loadOrigin: (1)rep.(0)%put (0)e (0)%at% (1)pos
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)%put (0)e (0)%at% (1)pos :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%put (0)e (0)%at% (1)pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put (0)e (0)%at% (1)pos
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (0)e:IS-empty: staticOff: 0
	-- Invocation:gen: (0)e
	-- Invocation:loadOrigin: (0)e
	-- Invocation:loadOrigin:scan: (0)e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)e
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (1)pos
	-- Invocation:loadOrigin: (1)pos
	-- Invocation:loadOrigin:scan: (1)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1:IS-empty: staticOff: 0
	pushThis 
	invoke 168 0 %if%then%%else%#S#168
	rpop
	-- ObjectGenerator:gen: super: (0)res (0):= (0)%this (2)Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (0)%this (2)Array
	-- Invocation:loadOrigin: (0)res (0):= (0)%this (2)Array
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)%this (2)Array
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%this (2)Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%this (2)Array
	-- Invocation:loadOrigin: (0)%this (2)Array
	-- Invocation:loadOrigin:scan: (0)%this (2)Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (2)Array
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (2)Array
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (0)res (0):= (1)rep.(0)%get (1)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (1)rep.(0)%get (1)pos
	-- Invocation:loadOrigin: (0)res (0):= (1)rep.(0)%get (1)pos
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)rep.(0)%get (1)pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)rep.(0)%get (1)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)%get (1)pos
	-- Invocation:loadOrigin: (1)rep.(0)%get (1)pos
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)%get (1)pos :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%get (1)pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get (1)pos
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (1)pos
	-- Invocation:loadOrigin: (1)pos
	-- Invocation:loadOrigin:scan: (1)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 res
	-- ObjectGenerator:gen: super: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1:IS-empty: staticOff: 0
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
	-- ObjectGenerator:gen: super: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1:IS-empty: staticOff: 0
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
	-- ObjectGenerator:gen: super: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1:IS-empty: staticOff: 0
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
	-- ObjectGenerator:gen: super: (1)pos (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)pos (0):= 1
	-- Invocation:loadOrigin: (1)pos (0):= 1
	-- Invocation:loadOrigin:scan: (1)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)pos
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 pos
	-- ObjectGenerator:gen: super: (0)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)loop
	-- Invocation:loadOrigin: (0)loop
	-- Invocation:loadOrigin:scan: (0)loop
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)loop
	-- AdjustOrigin: 0
	-- on : 0
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
	-- ObjectGenerator:gen: super: "Array(".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "Array(".(0)print
	-- Invocation:loadOrigin: "Array(".(0)print
	-- Invocation:loadOrigin:scan: "Array("
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText Array(
	-- next not assign: (0)print :E: "Array("
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: (0)%inner (1)print:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)print
	-- Invocation:loadOrigin: (0)%inner (1)print
	-- Invocation:loadOrigin:scan: (0)%inner (1)print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)print
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: "): ".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "): ".(0)print
	-- Invocation:loadOrigin: "): ".(0)print
	-- Invocation:loadOrigin:scan: "): "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText ): 
	-- next not assign: (0)print :E: "): "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: (0)%for 1 (0)%to% (1)rep.(0)length (0)%do% 
    (5)putint((3)rep.(0)%get (1)inx)
    ", ".(0)print:IS-empty: staticOff: 0
	pushThis 
	invoke 178 0 %for%to%%do%#S#178
	rpop
	-- ObjectGenerator:gen: super: (3)newline:IS-empty: staticOff: 0
	-- Invocation:gen: (3)newline
	-- Invocation:loadOrigin: (3)newline
	-- Invocation:loadOrigin:scan: (3)newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)newline
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
	-- ObjectGenerator:gen: super: (0)%if ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp) (0)%then% 
    "index error in range".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp) (0)%then% 
    "index error in range".(0)print
	-- Invocation:loadOrigin: (0)%if ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp) (0)%then% 
    "index error in range".(0)print
	-- Invocation:loadOrigin:scan: (0)%if ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp) (0)%then% 
    "index error in range".(0)print
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp) (0)%then% 
    "index error in range".(0)print
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp) (0)%then% 
    "index error in range".(0)print
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp):IS-empty: staticOff: 0
	-- Invocation:gen: ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp)
	-- Invocation:loadOrigin: ((0)inx (0)< (1)low) (0)|| ((0)inx (0)> (1)upp)
	-- Invocation:loadOrigin:scan: ((0)inx (0)< (1)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)inx (0)< (1)low)
	-- Invocation:loadOrigin: (0)inx (0)< (1)low
	-- Invocation:loadOrigin:scan: (0)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)< (1)low :E: (0)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: (0)< (1)low
	-- BE:loadOrigin:E: (0)< (1)low
	-- next not assign: (0)|| ((0)inx (0)> (1)upp) :E: (0)< (1)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)low
	-- Invocation:loadOrigin: (1)low
	-- Invocation:loadOrigin:scan: (1)low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: < (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	51
	-- Invocation:loadOrigin:scan: (0)|| ((0)inx (0)> (1)upp)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: ((0)inx (0)> (1)upp):IS-empty: staticOff: 0
	-- Invocation:gen: ((0)inx (0)> (1)upp)
	-- Invocation:loadOrigin: ((0)inx (0)> (1)upp)
	-- Invocation:loadOrigin:scan: ((0)inx (0)> (1)upp)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)inx (0)> (1)upp)
	-- Invocation:loadOrigin: (0)inx (0)> (1)upp
	-- Invocation:loadOrigin:scan: (0)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)> (1)upp :E: (0)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: (0)> (1)upp
	-- BE:loadOrigin:E: (0)> (1)upp
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)upp:IS-empty: staticOff: 0
	-- Invocation:gen: (1)upp
	-- Invocation:loadOrigin: (1)upp
	-- Invocation:loadOrigin:scan: (1)upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Binary:invoke: 
	-- pattern:load: > (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: || (1)B: ? (2)Boolean -> (2)R: ? (2)Boolean
	63
	jmpFalse L133
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 564 0 #S#564
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
	-- ObjectGenerator:gen: super: (3)putint((1)low):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((1)low)
	-- Invocation:loadOrigin: (3)putint((1)low)
	-- Invocation:loadOrigin:scan: (3)putint((1)low)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((1)low)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)low
	-- Invocation:loadOrigin: (1)low
	-- Invocation:loadOrigin:scan: (1)low
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)low
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: (3)put(':'):IS-empty: staticOff: 0
	-- Invocation:gen: (3)put(':')
	-- Invocation:loadOrigin: (3)put(':')
	-- Invocation:loadOrigin:scan: (3)put(':')
	-- Function:pushThis: 
	-- Function:loadOrigin: (3)put(':')
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
	-- pattern:load: put((1)ch: ? (1)char)
	%put 2
	-- ObjectGenerator:gen: super: (3)putint((1)upp):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((1)upp)
	-- Invocation:loadOrigin: (3)putint((1)upp)
	-- Invocation:loadOrigin:scan: (3)putint((1)upp)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((1)upp)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)upp:IS-empty: staticOff: 0
	-- Invocation:gen: (1)upp
	-- Invocation:loadOrigin: (1)upp
	-- Invocation:loadOrigin:scan: (1)upp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)upp
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: upp
	pushg 2 upp
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
 L135:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#565 565
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L136:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "range error\n".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "range error\n".(0)print
	-- Invocation:loadOrigin: "range error\n".(0)print
	-- Invocation:loadOrigin:scan: "range error\n"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText range error\n
	-- next not assign: (0)print :E: "range error\n"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
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
	-- ObjectGenerator:gen: super: (1)R.(0)check((0)inx):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R.(0)check((0)inx)
	-- Invocation:loadOrigin: (1)R.(0)check((0)inx)
	-- Invocation:loadOrigin:scan: (1)R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)check((0)inx) :E: (1)R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: (0)check((0)inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx
	-- Invocation:loadOrigin: (0)inx
	-- Invocation:loadOrigin:scan: (0)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check((1)inx: ? (3)integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: (1)rep.(0)%put (0)exp (0)%at% ((0)inx (0)- (1)R.(0)low) (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)%put (0)exp (0)%at% ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin: (1)rep.(0)%put (0)exp (0)%at% ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)%put (0)exp (0)%at% ((0)inx (0)- (1)R.(0)low) (0)+ 1 :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%put (0)exp (0)%at% ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put (0)exp (0)%at% ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (0)exp:IS-empty: staticOff: 0
	-- Invocation:gen: (0)exp
	-- Invocation:loadOrigin: (0)exp
	-- Invocation:loadOrigin:scan: (0)exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)exp
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 2 exp
	-- name::gen: 
	-- ObjectGenerator:gen: super: ((0)inx (0)- (1)R.(0)low) (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin: ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin:scan: ((0)inx (0)- (1)R.(0)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)inx (0)- (1)R.(0)low)
	-- Invocation:loadOrigin: (0)inx (0)- (1)R.(0)low
	-- Invocation:loadOrigin:scan: (0)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)- (1)R.(0)low :E: (0)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: (0)- (1)R.(0)low
	-- BE:loadOrigin:E: (0)- (1)R.(0)low
	-- next not assign: (0)+ 1 :E: (0)- (1)R.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R.(0)low
	-- Invocation:loadOrigin: (1)R.(0)low
	-- Invocation:loadOrigin:scan: (1)R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)low :E: (1)R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: (0)low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: (0)res (0):= (0)%this (2)Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (0)%this (2)Array
	-- Invocation:loadOrigin: (0)res (0):= (0)%this (2)Array
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)%this (2)Array
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%this (2)Array:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%this (2)Array
	-- Invocation:loadOrigin: (0)%this (2)Array
	-- Invocation:loadOrigin:scan: (0)%this (2)Array
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (2)Array
	-- AdjustOrigin: 0
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (2)Array
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)R.(0)check((0)inx):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R.(0)check((0)inx)
	-- Invocation:loadOrigin: (1)R.(0)check((0)inx)
	-- Invocation:loadOrigin:scan: (1)R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)check((0)inx) :E: (1)R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: (0)check((0)inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx
	-- Invocation:loadOrigin: (0)inx
	-- Invocation:loadOrigin:scan: (0)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Function:invoke: 
	-- pattern:load: check((1)inx: ? (3)integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: (0)res (0):= (1)rep.(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (1)rep.(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin: (0)res (0):= (1)rep.(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)rep.(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)rep.(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin: (1)rep.(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1 :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: ((0)inx (0)- (1)R.(0)low) (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin: ((0)inx (0)- (1)R.(0)low) (0)+ 1
	-- Invocation:loadOrigin:scan: ((0)inx (0)- (1)R.(0)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)inx (0)- (1)R.(0)low)
	-- Invocation:loadOrigin: (0)inx (0)- (1)R.(0)low
	-- Invocation:loadOrigin:scan: (0)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)- (1)R.(0)low :E: (0)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: (0)- (1)R.(0)low
	-- BE:loadOrigin:E: (0)- (1)R.(0)low
	-- next not assign: (0)+ 1 :E: (0)- (1)R.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R.(0)low
	-- Invocation:loadOrigin: (1)R.(0)low
	-- Invocation:loadOrigin:scan: (1)R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)low :E: (1)R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: (0)low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)R.(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R.(0)print
	-- Invocation:loadOrigin: (1)R.(0)print
	-- Invocation:loadOrigin:scan: (1)R
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: (0)print :E: (1)R
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R
	rpushg 3 R
	-- Invocation:loadOrigin:scan: (0)print
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
	-- ObjectGenerator:gen: super: (1)R1.(0)check((0)inx1):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R1.(0)check((0)inx1)
	-- Invocation:loadOrigin: (1)R1.(0)check((0)inx1)
	-- Invocation:loadOrigin:scan: (1)R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)check((0)inx1) :E: (1)R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: (0)check((0)inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx1
	-- Invocation:loadOrigin: (0)inx1
	-- Invocation:loadOrigin:scan: (0)inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check((1)inx: ? (3)integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: (1)R2.(0)check((0)inx2):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R2.(0)check((0)inx2)
	-- Invocation:loadOrigin: (1)R2.(0)check((0)inx2)
	-- Invocation:loadOrigin:scan: (1)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)check((0)inx2) :E: (1)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)check((0)inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx2
	-- Invocation:loadOrigin: (0)inx2
	-- Invocation:loadOrigin:scan: (0)inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check((1)inx: ? (3)integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: (0)repPos (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: (0)repPos (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: (0)repPos (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: (0)repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: ((0)inx1 (0)- (1)R1.(0)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)inx1 (0)- (1)R1.(0)low)
	-- Invocation:loadOrigin: (0)inx1 (0)- (1)R1.(0)low
	-- Invocation:loadOrigin:scan: (0)inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)- (1)R1.(0)low :E: (0)inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: (0)- (1)R1.(0)low
	-- BE:loadOrigin:E: (0)- (1)R1.(0)low
	-- next not assign: (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low) :E: (0)- (1)R1.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R1.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R1.(0)low
	-- Invocation:loadOrigin: (1)R1.(0)low
	-- Invocation:loadOrigin:scan: (1)R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)low :E: (1)R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: (0)low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Invocation:loadOrigin:scan: (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: (1)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)noof :E: (1)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)noof
	-- next not assign: (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low) :E: (0)noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: 1 (0)+ (0)inx2 (0)- (1)R2.(0)low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: (0)+ (0)inx2 (0)- (1)R2.(0)low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: (0)+ (0)inx2 (0)- (1)R2.(0)low
	-- BE:loadOrigin:E: (0)+ (0)inx2 (0)- (1)R2.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx2 (0)- (1)R2.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx2 (0)- (1)R2.(0)low
	-- Invocation:loadOrigin: (0)inx2 (0)- (1)R2.(0)low
	-- Invocation:loadOrigin:scan: (0)inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)- (1)R2.(0)low :E: (0)inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: (0)- (1)R2.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R2.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R2.(0)low
	-- Invocation:loadOrigin: (1)R2.(0)low
	-- Invocation:loadOrigin:scan: (1)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)low :E: (1)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * (1)V: ? (2)integer -> (2)R: ? (2)integer
	66
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 4 repPos
	-- ObjectGenerator:gen: super: (1)rep.(0)%put (0)exp (0)%at% (0)repPos:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)%put (0)exp (0)%at% (0)repPos
	-- Invocation:loadOrigin: (1)rep.(0)%put (0)exp (0)%at% (0)repPos
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)%put (0)exp (0)%at% (0)repPos :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%put (0)exp (0)%at% (0)repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put (0)exp (0)%at% (0)repPos
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (0)exp:IS-empty: staticOff: 0
	-- Invocation:gen: (0)exp
	-- Invocation:loadOrigin: (0)exp
	-- Invocation:loadOrigin:scan: (0)exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)exp
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: exp
	pushg 3 exp
	-- name::gen: 
	-- ObjectGenerator:gen: super: (0)repPos:IS-empty: staticOff: 0
	-- Invocation:gen: (0)repPos
	-- Invocation:loadOrigin: (0)repPos
	-- Invocation:loadOrigin:scan: (0)repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)repPos
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
	-- ObjectGenerator:gen: super: (1)R1.(0)check((0)inx1):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R1.(0)check((0)inx1)
	-- Invocation:loadOrigin: (1)R1.(0)check((0)inx1)
	-- Invocation:loadOrigin:scan: (1)R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)check((0)inx1) :E: (1)R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: (0)check((0)inx1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx1
	-- Invocation:loadOrigin: (0)inx1
	-- Invocation:loadOrigin:scan: (0)inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Function:invoke: 
	-- pattern:load: check((1)inx: ? (3)integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: (1)R2.(0)check((0)inx2):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R2.(0)check((0)inx2)
	-- Invocation:loadOrigin: (1)R2.(0)check((0)inx2)
	-- Invocation:loadOrigin:scan: (1)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)check((0)inx2) :E: (1)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)check((0)inx2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx2
	-- Invocation:loadOrigin: (0)inx2
	-- Invocation:loadOrigin:scan: (0)inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Function:invoke: 
	-- pattern:load: check((1)inx: ? (3)integer)
	invoke 180 0 check
	rpop
	-- ObjectGenerator:gen: super: (0)repPos (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: (0)repPos (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: (0)repPos (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: (0)repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: ((0)inx1 (0)- (1)R1.(0)low) (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: ((0)inx1 (0)- (1)R1.(0)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((0)inx1 (0)- (1)R1.(0)low)
	-- Invocation:loadOrigin: (0)inx1 (0)- (1)R1.(0)low
	-- Invocation:loadOrigin:scan: (0)inx1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)- (1)R1.(0)low :E: (0)inx1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx1
	pushg 1 inx1
	-- Invocation:loadOrigin:scan: (0)- (1)R1.(0)low
	-- BE:loadOrigin:E: (0)- (1)R1.(0)low
	-- next not assign: (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low) :E: (0)- (1)R1.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R1.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R1.(0)low
	-- Invocation:loadOrigin: (1)R1.(0)low
	-- Invocation:loadOrigin:scan: (1)R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)low :E: (1)R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: (0)low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Invocation:loadOrigin:scan: (0)* (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: (1)R2.(0)noof (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: (1)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)noof :E: (1)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)noof
	-- next not assign: (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low) :E: (0)noof
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: noof
	pushg 3 noof
	-- Invocation:loadOrigin:scan: (0)+ (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low):IS-empty: staticOff: 0
	-- Invocation:gen: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin:scan: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: (1 (0)+ (0)inx2 (0)- (1)R2.(0)low)
	-- Invocation:loadOrigin: 1 (0)+ (0)inx2 (0)- (1)R2.(0)low
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: (0)+ (0)inx2 (0)- (1)R2.(0)low :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: (0)+ (0)inx2 (0)- (1)R2.(0)low
	-- BE:loadOrigin:E: (0)+ (0)inx2 (0)- (1)R2.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)inx2 (0)- (1)R2.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (0)inx2 (0)- (1)R2.(0)low
	-- Invocation:loadOrigin: (0)inx2 (0)- (1)R2.(0)low
	-- Invocation:loadOrigin:scan: (0)inx2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)inx2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)- (1)R2.(0)low :E: (0)inx2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx2
	pushg 2 inx2
	-- Invocation:loadOrigin:scan: (0)- (1)R2.(0)low
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)R2.(0)low:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R2.(0)low
	-- Invocation:loadOrigin: (1)R2.(0)low
	-- Invocation:loadOrigin:scan: (1)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)low :E: (1)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)low
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: low
	pushg 1 low
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: * (1)V: ? (2)integer -> (2)R: ? (2)integer
	66
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 4 repPos
	-- ObjectGenerator:gen: super: (0)exp (0):= (1)rep.(0)%get (0)repPos:IS-empty: staticOff: 0
	-- Invocation:gen: (0)exp (0):= (1)rep.(0)%get (0)repPos
	-- Invocation:loadOrigin: (0)exp (0):= (1)rep.(0)%get (0)repPos
	-- Invocation:loadOrigin:scan: (0)exp
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)exp
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)rep.(0)%get (0)repPos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)rep.(0)%get (0)repPos:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)%get (0)repPos
	-- Invocation:loadOrigin: (1)rep.(0)%get (0)repPos
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)%get (0)repPos :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%get (0)repPos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get (0)repPos
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (0)repPos:IS-empty: staticOff: 0
	-- Invocation:gen: (0)repPos
	-- Invocation:loadOrigin: (0)repPos
	-- Invocation:loadOrigin:scan: (0)repPos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)repPos
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: repPos
	pushg 4 repPos
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)R1.(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R1.(0)print
	-- Invocation:loadOrigin: (1)R1.(0)print
	-- Invocation:loadOrigin:scan: (1)R1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: (0)print :E: (1)R1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R1
	rpushg 3 R1
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 181 0 print
	rpop
	-- ObjectGenerator:gen: super: ",".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: ",".(0)print
	-- Invocation:loadOrigin: ",".(0)print
	-- Invocation:loadOrigin:scan: ","
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText ,
	-- next not assign: (0)print :E: ","
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: (1)R2.(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: (1)R2.(0)print
	-- Invocation:loadOrigin: (1)R2.(0)print
	-- Invocation:loadOrigin:scan: (1)R2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)R2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: (0)print :E: (1)R2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: R2
	rpushg 4 R2
	-- Invocation:loadOrigin:scan: (0)print
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
	-- ObjectGenerator:gen: super: (1)ProcessQueue:IS-empty: staticOff: 2
	-- Invocation:gen: (1)ProcessQueue
	-- Invocation:loadOrigin: (1)ProcessQueue
	-- Invocation:loadOrigin:scan: (1)ProcessQueue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)ProcessQueue
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: ProcessQueue
	invoke 132 2 ProcessQueue
	rpop
	-- ConsRef:gen: M
	-- ObjectGenerator:gen: super: (1)Lock:IS-empty: staticOff: 3
	-- Invocation:gen: (1)Lock
	-- Invocation:loadOrigin: (1)Lock
	-- Invocation:loadOrigin:scan: (1)Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Lock
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 3 Lock
	rpop
	-- pattern:gen: run((2)P: ? (2)BasicProcess)
	-- pattern:gen: AwaitTermination
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L150:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)M.(0)init:IS-empty: staticOff: 0
	-- Invocation:gen: (0)M.(0)init
	-- Invocation:loadOrigin: (0)M.(0)init
	-- Invocation:loadOrigin:scan: (0)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)M
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)init :E: (0)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: (0)init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 114 0 init
	rpop
	-- ObjectGenerator:gen: super: (0)%inner (1)ForkJoin:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)ForkJoin
	-- Invocation:loadOrigin: (0)%inner (1)ForkJoin
	-- Invocation:loadOrigin:scan: (0)%inner (1)ForkJoin
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)ForkJoin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)ForkJoin
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: (0)AwaitTermination:IS-empty: staticOff: 0
	-- Invocation:gen: (0)AwaitTermination
	-- Invocation:loadOrigin: (0)AwaitTermination
	-- Invocation:loadOrigin:scan: (0)AwaitTermination
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)AwaitTermination
	-- AdjustOrigin: 0
	-- on : 0
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
	-- ObjectGenerator:gen: super: (1)Lock:IS-empty: staticOff: 2
	-- Invocation:gen: (1)Lock
	-- Invocation:loadOrigin: (1)Lock
	-- Invocation:loadOrigin:scan: (1)Lock
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Lock
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Lock
	invoke 113 2 Lock
	rpop
	-- ConsRef:gen: Q
	-- ObjectGenerator:gen: super: (1)ProcessQueue:IS-empty: staticOff: 3
	-- Invocation:gen: (1)ProcessQueue
	-- Invocation:loadOrigin: (1)ProcessQueue
	-- Invocation:loadOrigin:scan: (1)ProcessQueue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)ProcessQueue
	-- AdjustOrigin: 0
	-- on : 1
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
	-- Invocation:loadOrigin: (0)BasicProcess
	-- Invocation:loadOrigin:scan: (0)BasicProcess
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)BasicProcess
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
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
	-- ObjectGenerator:gen: super: (3)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (3)inner
	-- Invocation:loadOrigin: (3)inner
	-- Invocation:loadOrigin:scan: (3)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)inner
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
	-- ObjectGenerator:gen: super: (1)Semaphore:IS-empty: staticOff: 2
	-- Invocation:gen: (1)Semaphore
	-- Invocation:loadOrigin: (1)Semaphore
	-- Invocation:loadOrigin:scan: (1)Semaphore
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Semaphore
	-- AdjustOrigin: 0
	-- on : 1
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
	-- ObjectGenerator:gen: super: (0)V (0):= (0)%get 0:IS-empty: staticOff: 0
	-- Invocation:gen: (0)V (0):= (0)%get 0
	-- Invocation:loadOrigin: (0)V (0):= (0)%get 0
	-- Invocation:loadOrigin:scan: (0)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)V
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)%get 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%get 0:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%get 0
	-- Invocation:loadOrigin: (0)%get 0
	-- Invocation:loadOrigin:scan: (0)%get 0
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%get 0
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get 0
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
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
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (0)L (0):= (1)Length:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L (0):= (1)Length
	-- Invocation:loadOrigin: (0)L (0):= (1)Length
	-- Invocation:loadOrigin:scan: (0)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)Length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)Length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)Length
	-- Invocation:loadOrigin: (1)Length
	-- Invocation:loadOrigin:scan: (1)Length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Length
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 L
	-- ObjectGenerator:gen: super: (0)doplus:IS-empty: staticOff: 0
	-- Invocation:gen: (0)doplus
	-- Invocation:loadOrigin: (0)doplus
	-- Invocation:loadOrigin:scan: (0)doplus
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)doplus
	-- AdjustOrigin: 0
	-- on : 0
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
	-- ObjectGenerator:gen: super: (0)%for 1 (0)%to% (1)length (0)%do% 
    (2)current (0):= (0)%get (1)inx
    (0)%inner (3)scan:IS-empty: staticOff: 0
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
	-- ObjectGenerator:gen: super: (0)%for 1 (0)%to% (1)length (0)%do% 
    (5)put((0)%get (1)inx):IS-empty: staticOff: 0
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

	class (0)List 434
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: List((1)elmType:< (4)Object,(2)head: ? (0)elmType,(3)tail: ? (1)List)
	-- pattern:gen: RangeList
	-- VarRef:gen: rl
	-- VarRef:gen: emptyRangeList
	-- VarRef:gen: emptyList
	-- pattern:gen: Range((2)r: ? (4)Indexed)
	-- VarRef:gen: r
	-- VarRef:gen: r1
	-- VarRef:gen: r2
	-- pattern:gen: testArray((1)ndim: ? (4)integer,(0)ranges: (1)RangeList)
	-- VarRef:gen: ta
	-- VarRef:gen: i
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L172:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "integerArrayStart1".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "integerArrayStart1".(0)print
	-- Invocation:loadOrigin: "integerArrayStart1".(0)print
	-- Invocation:loadOrigin:scan: "integerArrayStart1"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText integerArrayStart1
	-- next not assign: (0)print :E: "integerArrayStart1"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: (3)newline:IS-empty: staticOff: 0
	-- Invocation:gen: (3)newline
	-- Invocation:loadOrigin: (3)newline
	-- Invocation:loadOrigin:scan: (3)newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)newline
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
	-- ObjectGenerator:gen: super: (0)emptyList (0):= (0)List((3)Object,(3)none,(3)none):IS-empty: staticOff: 0
	-- Invocation:gen: (0)emptyList (0):= (0)List((3)Object,(3)none,(3)none)
	-- Invocation:loadOrigin: (0)emptyList (0):= (0)List((3)Object,(3)none,(3)none)
	-- Invocation:loadOrigin:scan: (0)emptyList
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)emptyList
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)List((3)Object,(3)none,(3)none)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)List((3)Object,(3)none,(3)none):IS-empty: staticOff: 0
	pushThis 
	invoke 626 0 List#S#626
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 4 emptyList
	-- ObjectGenerator:gen: super: (0)r1 (0):= (0)Range((3)Indexed(2,(3)integer)):IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1 (0):= (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin: (0)r1 (0):= (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)Range((3)Indexed(2,(3)integer))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)Range((3)Indexed(2,(3)integer)):IS-empty: staticOff: 0
	-- Invocation:gen: (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin: (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin:scan: (0)Range((3)Indexed(2,(3)integer))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)Range((3)Indexed(2,(3)integer))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (3)Indexed(2,(3)integer):IS-empty: staticOff: 0
	-- Invocation:gen: (3)Indexed(2,(3)integer)
	-- Invocation:loadOrigin: (3)Indexed(2,(3)integer)
	-- Invocation:loadOrigin:scan: (3)Indexed(2,(3)integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)Indexed(2,(3)integer)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
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
	-- ObjectGenerator:gen: super: (3)integer:IS-empty: staticOff: 0
	-- Invocation:gen: (3)integer
	-- Invocation:loadOrigin: (3)integer
	-- Invocation:loadOrigin:scan: (3)integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer((1)W: ? (1)integer)
	-- Function:invoke: 
	-- pattern:load: Indexed((1)range: ? (1)Integer,(1)elm:< (1)Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	-- Function:invoke: 
	-- pattern:load: Range((2)r: ? (4)Indexed)
	invoke 440 0 Range
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 6 r1
	-- ObjectGenerator:gen: super: (0)r2 (0):= (0)Range((3)Indexed(2,(3)integer)):IS-empty: staticOff: 0
	-- Invocation:gen: (0)r2 (0):= (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin: (0)r2 (0):= (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin:scan: (0)r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r2
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)Range((3)Indexed(2,(3)integer))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)Range((3)Indexed(2,(3)integer)):IS-empty: staticOff: 0
	-- Invocation:gen: (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin: (0)Range((3)Indexed(2,(3)integer))
	-- Invocation:loadOrigin:scan: (0)Range((3)Indexed(2,(3)integer))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)Range((3)Indexed(2,(3)integer))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (3)Indexed(2,(3)integer):IS-empty: staticOff: 0
	-- Invocation:gen: (3)Indexed(2,(3)integer)
	-- Invocation:loadOrigin: (3)Indexed(2,(3)integer)
	-- Invocation:loadOrigin:scan: (3)Indexed(2,(3)integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)Indexed(2,(3)integer)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
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
	-- ObjectGenerator:gen: super: (3)integer:IS-empty: staticOff: 0
	-- Invocation:gen: (3)integer
	-- Invocation:loadOrigin: (3)integer
	-- Invocation:loadOrigin:scan: (3)integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer((1)W: ? (1)integer)
	-- Function:invoke: 
	-- pattern:load: Indexed((1)range: ? (1)Integer,(1)elm:< (1)Object)
	pushc 0
	pushc 1
	allocIndexed 52 StaticRep asObj
	-- Function:invoke: 
	-- pattern:load: Range((2)r: ? (4)Indexed)
	invoke 440 0 Range
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 7 r2
	-- ObjectGenerator:gen: super: (0)emptyRangeList (0):= (0)RangeList((0)r1,(0)emptyList):IS-empty: staticOff: 0
	-- Invocation:gen: (0)emptyRangeList (0):= (0)RangeList((0)r1,(0)emptyList)
	-- Invocation:loadOrigin: (0)emptyRangeList (0):= (0)RangeList((0)r1,(0)emptyList)
	-- Invocation:loadOrigin:scan: (0)emptyRangeList
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)emptyRangeList
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)RangeList((0)r1,(0)emptyList)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)RangeList((0)r1,(0)emptyList):IS-empty: staticOff: 0
	-- Invocation:gen: (0)RangeList((0)r1,(0)emptyList)
	-- Invocation:loadOrigin: (0)RangeList((0)r1,(0)emptyList)
	-- Invocation:loadOrigin:scan: (0)RangeList((0)r1,(0)emptyList)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)RangeList((0)r1,(0)emptyList)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1
	-- Invocation:loadOrigin: (0)r1
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 6 r1
	-- ObjectGenerator:gen: super: (0)emptyList:IS-empty: staticOff: 0
	-- Invocation:gen: (0)emptyList
	-- Invocation:loadOrigin: (0)emptyList
	-- Invocation:loadOrigin:scan: (0)emptyList
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)emptyList
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: emptyList
	rpushg 4 emptyList
	-- Function:invoke: 
	-- pattern:load: RangeList
	invoke 438 0 RangeList
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 emptyRangeList
	-- ObjectGenerator:gen: super: "integerArrayStart2".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "integerArrayStart2".(0)print
	-- Invocation:loadOrigin: "integerArrayStart2".(0)print
	-- Invocation:loadOrigin:scan: "integerArrayStart2"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText integerArrayStart2
	-- next not assign: (0)print :E: "integerArrayStart2"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: (3)newline:IS-empty: staticOff: 0
	-- Invocation:gen: (3)newline
	-- Invocation:loadOrigin: (3)newline
	-- Invocation:loadOrigin:scan: (3)newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)newline
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
	-- ObjectGenerator:gen: super: (0)r1.(0)r.(0)%put 2 (0)%at% 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1.(0)r.(0)%put 2 (0)%at% 1
	-- Invocation:loadOrigin: (0)r1.(0)r.(0)%put 2 (0)%at% 1
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 6 r1
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%put 2 (0)%at% 1 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%put 2 (0)%at% 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put 2 (0)%at% 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	-- name::gen: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: (0)r1.(0)r.(0)%put 3 (0)%at% 2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1.(0)r.(0)%put 3 (0)%at% 2
	-- Invocation:loadOrigin: (0)r1.(0)r.(0)%put 3 (0)%at% 2
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 6 r1
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%put 3 (0)%at% 2 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%put 3 (0)%at% 2
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put 3 (0)%at% 2
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 3:IS-empty: staticOff: 0
	-- Invocation:gen: 3
	-- Invocation:loadOrigin: 3
	-- Invocation:loadOrigin:scan: 3
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 3
	-- name::gen: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: (0)r2.(0)r.(0)%put 4 (0)%at% 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r2.(0)r.(0)%put 4 (0)%at% 1
	-- Invocation:loadOrigin: (0)r2.(0)r.(0)%put 4 (0)%at% 1
	-- Invocation:loadOrigin:scan: (0)r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 7 r2
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%put 4 (0)%at% 1 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%put 4 (0)%at% 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put 4 (0)%at% 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 4:IS-empty: staticOff: 0
	-- Invocation:gen: 4
	-- Invocation:loadOrigin: 4
	-- Invocation:loadOrigin:scan: 4
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 4
	-- name::gen: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: (0)r2.(0)r.(0)%put 5 (0)%at% 2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r2.(0)r.(0)%put 5 (0)%at% 2
	-- Invocation:loadOrigin: (0)r2.(0)r.(0)%put 5 (0)%at% 2
	-- Invocation:loadOrigin:scan: (0)r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 7 r2
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%put 5 (0)%at% 2 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%put 5 (0)%at% 2
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put 5 (0)%at% 2
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 5:IS-empty: staticOff: 0
	-- Invocation:gen: 5
	-- Invocation:loadOrigin: 5
	-- Invocation:loadOrigin:scan: 5
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 5
	-- name::gen: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	xstoreg 1 inx
	-- ObjectGenerator:gen: super: (3)putint((0)r1.(0)r.(0)%get 1):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((0)r1.(0)r.(0)%get 1)
	-- Invocation:loadOrigin: (3)putint((0)r1.(0)r.(0)%get 1)
	-- Invocation:loadOrigin:scan: (3)putint((0)r1.(0)r.(0)%get 1)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((0)r1.(0)r.(0)%get 1)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r1.(0)r.(0)%get 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1.(0)r.(0)%get 1
	-- Invocation:loadOrigin: (0)r1.(0)r.(0)%get 1
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 6 r1
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%get 1 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%get 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: (3)putint((0)r1.(0)r.(0)%get 2):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((0)r1.(0)r.(0)%get 2)
	-- Invocation:loadOrigin: (3)putint((0)r1.(0)r.(0)%get 2)
	-- Invocation:loadOrigin:scan: (3)putint((0)r1.(0)r.(0)%get 2)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((0)r1.(0)r.(0)%get 2)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r1.(0)r.(0)%get 2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1.(0)r.(0)%get 2
	-- Invocation:loadOrigin: (0)r1.(0)r.(0)%get 2
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 6 r1
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%get 2 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%get 2
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get 2
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: (3)putint((0)r2.(0)r.(0)%get 1):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((0)r2.(0)r.(0)%get 1)
	-- Invocation:loadOrigin: (3)putint((0)r2.(0)r.(0)%get 1)
	-- Invocation:loadOrigin:scan: (3)putint((0)r2.(0)r.(0)%get 1)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((0)r2.(0)r.(0)%get 1)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r2.(0)r.(0)%get 1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r2.(0)r.(0)%get 1
	-- Invocation:loadOrigin: (0)r2.(0)r.(0)%get 1
	-- Invocation:loadOrigin:scan: (0)r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 7 r2
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%get 1 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%get 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: (3)putint((0)r2.(0)r.(0)%get 2):IS-empty: staticOff: 0
	-- Invocation:gen: (3)putint((0)r2.(0)r.(0)%get 2)
	-- Invocation:loadOrigin: (3)putint((0)r2.(0)r.(0)%get 2)
	-- Invocation:loadOrigin:scan: (3)putint((0)r2.(0)r.(0)%get 2)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (3)putint((0)r2.(0)r.(0)%get 2)
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r2.(0)r.(0)%get 2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r2.(0)r.(0)%get 2
	-- Invocation:loadOrigin: (0)r2.(0)r.(0)%get 2
	-- Invocation:loadOrigin:scan: (0)r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r2
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)r :E: (0)r2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 7 r2
	-- Invocation:loadOrigin:scan: (0)r
	-- next not assign: (0)%get 2 :E: (0)r
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r
	rpushg 2 r
	-- Invocation:loadOrigin:scan: (0)%get 2
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get 2
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: 2:IS-empty: staticOff: 0
	-- Invocation:gen: 2
	-- Invocation:loadOrigin: 2
	-- Invocation:loadOrigin:scan: 2
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 2
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: (0)rl (0):= (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none)):IS-empty: staticOff: 0
	-- Invocation:gen: (0)rl (0):= (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none))
	-- Invocation:loadOrigin: (0)rl (0):= (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none))
	-- Invocation:loadOrigin:scan: (0)rl
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)rl
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none)):IS-empty: staticOff: 0
	-- Invocation:gen: (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none))
	-- Invocation:loadOrigin: (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none))
	-- Invocation:loadOrigin:scan: (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)RangeList((0)r1,(0)RangeList((0)r2,(3)none))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1
	-- Invocation:loadOrigin: (0)r1
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 6 r1
	-- ObjectGenerator:gen: super: (0)RangeList((0)r2,(3)none):IS-empty: staticOff: 0
	-- Invocation:gen: (0)RangeList((0)r2,(3)none)
	-- Invocation:loadOrigin: (0)RangeList((0)r2,(3)none)
	-- Invocation:loadOrigin:scan: (0)RangeList((0)r2,(3)none)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)RangeList((0)r2,(3)none)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r2
	-- Invocation:loadOrigin: (0)r2
	-- Invocation:loadOrigin:scan: (0)r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 7 r2
	-- ObjectGenerator:gen: super: (3)none:IS-empty: staticOff: 0
	-- Invocation:gen: (3)none
	-- Invocation:loadOrigin: (3)none
	-- Invocation:loadOrigin:scan: (3)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Function:invoke: 
	-- pattern:load: RangeList
	invoke 438 0 RangeList
	-- Function:invoke: 
	-- pattern:load: RangeList
	invoke 438 0 RangeList
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 rl
	-- ObjectGenerator:gen: super: (0)ta (0):= (0)testArray(2,(0)rl):IS-empty: staticOff: 0
	-- Invocation:gen: (0)ta (0):= (0)testArray(2,(0)rl)
	-- Invocation:loadOrigin: (0)ta (0):= (0)testArray(2,(0)rl)
	-- Invocation:loadOrigin:scan: (0)ta
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)ta
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)testArray(2,(0)rl)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)testArray(2,(0)rl):IS-empty: staticOff: 0
	-- Invocation:gen: (0)testArray(2,(0)rl)
	-- Invocation:loadOrigin: (0)testArray(2,(0)rl)
	-- Invocation:loadOrigin:scan: (0)testArray(2,(0)rl)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)testArray(2,(0)rl)
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
	-- ObjectGenerator:gen: super: (0)rl:IS-empty: staticOff: 0
	-- Invocation:gen: (0)rl
	-- Invocation:loadOrigin: (0)rl
	-- Invocation:loadOrigin:scan: (0)rl
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)rl
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rl
	rpushg 2 rl
	-- Function:invoke: 
	-- pattern:load: testArray((1)ndim: ? (4)integer,(0)ranges: (1)RangeList)
	invoke 441 0 testArray
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 8 ta
	-- ObjectGenerator:gen: super: (0)ta (0):= (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList))):IS-empty: staticOff: 0
	-- Invocation:gen: (0)ta (0):= (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)))
	-- Invocation:loadOrigin: (0)ta (0):= (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)))
	-- Invocation:loadOrigin:scan: (0)ta
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)ta
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)))
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList))):IS-empty: staticOff: 0
	-- Invocation:gen: (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)))
	-- Invocation:loadOrigin: (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)))
	-- Invocation:loadOrigin:scan: (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)testArray(2,(0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)))
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
	-- ObjectGenerator:gen: super: (0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList)):IS-empty: staticOff: 0
	-- Invocation:gen: (0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList))
	-- Invocation:loadOrigin: (0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList))
	-- Invocation:loadOrigin:scan: (0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList))
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)RangeList((0)r1,(0)RangeList((0)r2,(0)emptyRangeList))
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r1
	-- Invocation:loadOrigin: (0)r1
	-- Invocation:loadOrigin:scan: (0)r1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r1
	rpushg 6 r1
	-- ObjectGenerator:gen: super: (0)RangeList((0)r2,(0)emptyRangeList):IS-empty: staticOff: 0
	-- Invocation:gen: (0)RangeList((0)r2,(0)emptyRangeList)
	-- Invocation:loadOrigin: (0)RangeList((0)r2,(0)emptyRangeList)
	-- Invocation:loadOrigin:scan: (0)RangeList((0)r2,(0)emptyRangeList)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)RangeList((0)r2,(0)emptyRangeList)
	-- AdjustOrigin: 0
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)r2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)r2
	-- Invocation:loadOrigin: (0)r2
	-- Invocation:loadOrigin:scan: (0)r2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)r2
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: r2
	rpushg 7 r2
	-- ObjectGenerator:gen: super: (0)emptyRangeList:IS-empty: staticOff: 0
	-- Invocation:gen: (0)emptyRangeList
	-- Invocation:loadOrigin: (0)emptyRangeList
	-- Invocation:loadOrigin:scan: (0)emptyRangeList
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)emptyRangeList
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: emptyRangeList
	rpushg 3 emptyRangeList
	-- Function:invoke: 
	-- pattern:load: RangeList
	invoke 438 0 RangeList
	-- Function:invoke: 
	-- pattern:load: RangeList
	invoke 438 0 RangeList
	-- Function:invoke: 
	-- pattern:load: testArray((1)ndim: ? (4)integer,(0)ranges: (1)RangeList)
	invoke 441 0 testArray
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 8 ta
 L173:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#525 525
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L174:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)body:IS-empty: staticOff: 0
	-- Invocation:gen: (3)body
	-- Invocation:loadOrigin: (3)body
	-- Invocation:loadOrigin:scan: (3)body
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)body
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
	-- ObjectGenerator:gen: super: (3)inx (0):= (3)inx (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)inx (0):= (3)inx (0)+ 1
	-- Invocation:loadOrigin: (3)inx (0):= (3)inx (0)+ 1
	-- Invocation:loadOrigin:scan: (3)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)inx (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)inx (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)inx (0)+ 1
	-- Invocation:loadOrigin: (3)inx (0)+ 1
	-- Invocation:loadOrigin:scan: (3)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (3)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 3 inx
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 81
 L175:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#526 526
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L176:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 84
 L177:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#527 527
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
	-- ObjectGenerator:gen: super: (0)i (0):= (3)L (0)+ 1 (0)- (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)i (0):= (3)L (0)+ 1 (0)- (1)inx
	-- Invocation:loadOrigin: (0)i (0):= (3)L (0)+ 1 (0)- (1)inx
	-- Invocation:loadOrigin:scan: (0)i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)i
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (3)L (0)+ 1 (0)- (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)L (0)+ 1 (0)- (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (3)L (0)+ 1 (0)- (1)inx
	-- Invocation:loadOrigin: (3)L (0)+ 1 (0)- (1)inx
	-- Invocation:loadOrigin:scan: (3)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 (0)- (1)inx :E: (3)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 2 L
	-- Invocation:loadOrigin:scan: (0)+ 1 (0)- (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: 1 (0)- (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: 1 (0)- (1)inx
	-- Invocation:loadOrigin: 1 (0)- (1)inx
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- next not assign: (0)- (1)inx :E: 1
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- Invocation:loadOrigin:scan: (0)- (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Binary:invoke: 
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 i
	-- ObjectGenerator:gen: super: (4)put('0' (0)+ (3)D.(0)%get (0)i):IS-empty: staticOff: 0
	-- Invocation:gen: (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- Invocation:loadOrigin: (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- Invocation:loadOrigin:scan: (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- Function:pushThis: 
	-- Function:loadOrigin: (4)put('0' (0)+ (3)D.(0)%get (0)i)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: '0' (0)+ (3)D.(0)%get (0)i:IS-empty: staticOff: 0
	-- Invocation:gen: '0' (0)+ (3)D.(0)%get (0)i
	-- Invocation:loadOrigin: '0' (0)+ (3)D.(0)%get (0)i
	-- Invocation:loadOrigin:scan: '0'
	-- Char::pushThis: 
	-- Char::loadOrigin: 
	-- next not assign: (0)+ (3)D.(0)%get (0)i :E: '0'
	-- Char::loadArgs: 
	-- Char::invoke: 
	pushc 48
	-- Invocation:loadOrigin:scan: (0)+ (3)D.(0)%get (0)i
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)D.(0)%get (0)i:IS-empty: staticOff: 0
	-- Invocation:gen: (3)D.(0)%get (0)i
	-- Invocation:loadOrigin: (3)D.(0)%get (0)i
	-- Invocation:loadOrigin:scan: (3)D
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)D
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)%get (0)i :E: (3)D
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: D
	rpushg 2 D
	-- Invocation:loadOrigin:scan: (0)%get (0)i
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get (0)i
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (0)i:IS-empty: staticOff: 0
	-- Invocation:gen: (0)i
	-- Invocation:loadOrigin: (0)i
	-- Invocation:loadOrigin:scan: (0)i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)i
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 1 i
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)char -> (2)R: ? (2)char
	plus
	-- Function:invoke: 
	-- pattern:load: put((1)ch: ? (1)char)
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
	-- ObjectGenerator:gen: super: (1)M (0):= 0:IS-empty: staticOff: 0
	-- Invocation:gen: (1)M (0):= 0
	-- Invocation:loadOrigin: (1)M (0):= 0
	-- Invocation:loadOrigin:scan: (1)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 0
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
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)M (0):= 0:IS-empty: staticOff: 0
	-- Invocation:gen: (1)M (0):= 0
	-- Invocation:loadOrigin: (1)M (0):= 0
	-- Invocation:loadOrigin:scan: (1)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 0
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 2 M
	-- ObjectGenerator:gen: super: (4)enable:IS-empty: staticOff: 0
	-- Invocation:gen: (4)enable
	-- Invocation:loadOrigin: (4)enable
	-- Invocation:loadOrigin:scan: (4)enable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)enable
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
	-- ObjectGenerator:gen: super: (1)status (0):= (2)p_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (1)status (0):= (2)p_status.(0)ACTIVE
	-- Invocation:loadOrigin: (1)status (0):= (2)p_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (1)status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)status
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)p_status.(0)ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)p_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (2)p_status.(0)ACTIVE
	-- Invocation:loadOrigin: (2)p_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (2)p_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)p_status
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)ACTIVE :E: (2)p_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: (0)ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 status
	-- ObjectGenerator:gen: super: (4)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (4)inner
	-- Invocation:loadOrigin: (4)inner
	-- Invocation:loadOrigin:scan: (4)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)inner
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
	-- ObjectGenerator:gen: super: (1)main (0):= (0)M:IS-empty: staticOff: 0
	-- Invocation:gen: (1)main (0):= (0)M
	-- Invocation:loadOrigin: (1)main (0):= (0)M
	-- Invocation:loadOrigin:scan: (1)main
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)main
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (0)M
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)M:IS-empty: staticOff: 0
	-- Invocation:gen: (0)M
	-- Invocation:loadOrigin: (0)M
	-- Invocation:loadOrigin:scan: (0)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)M
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	rpushg 2 M
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)C1 (0):= (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C1 (0):= (2)Core
	-- Invocation:loadOrigin: (1)C1 (0):= (2)Core
	-- Invocation:loadOrigin:scan: (1)C1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Core
	-- Invocation:loadOrigin: (2)Core
	-- Invocation:loadOrigin:scan: (2)Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 C1
	-- ObjectGenerator:gen: super: (4)fork((1)C1):IS-empty: staticOff: 0
	-- Invocation:gen: (4)fork((1)C1)
	-- Invocation:loadOrigin: (4)fork((1)C1)
	-- Invocation:loadOrigin:scan: (4)fork((1)C1)
	-- Function:pushThis: 
	-- Function:loadOrigin: (4)fork((1)C1)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)C1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C1
	-- Invocation:loadOrigin: (1)C1
	-- Invocation:loadOrigin:scan: (1)C1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C1
	rpushg 2 C1
	-- Function:invoke: 
	-- pattern:load: fork((2)S: ? (1)Object)
	%fork 13
	-- ObjectGenerator:gen: super: (1)C2 (0):= (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C2 (0):= (2)Core
	-- Invocation:loadOrigin: (1)C2 (0):= (2)Core
	-- Invocation:loadOrigin:scan: (1)C2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Core
	-- Invocation:loadOrigin: (2)Core
	-- Invocation:loadOrigin:scan: (2)Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 C2
	-- ObjectGenerator:gen: super: (4)fork((1)C2):IS-empty: staticOff: 0
	-- Invocation:gen: (4)fork((1)C2)
	-- Invocation:loadOrigin: (4)fork((1)C2)
	-- Invocation:loadOrigin:scan: (4)fork((1)C2)
	-- Function:pushThis: 
	-- Function:loadOrigin: (4)fork((1)C2)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)C2:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C2
	-- Invocation:loadOrigin: (1)C2
	-- Invocation:loadOrigin:scan: (1)C2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C2
	rpushg 3 C2
	-- Function:invoke: 
	-- pattern:load: fork((2)S: ? (1)Object)
	%fork 13
	-- ObjectGenerator:gen: super: (1)C3 (0):= (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C3 (0):= (2)Core
	-- Invocation:loadOrigin: (1)C3 (0):= (2)Core
	-- Invocation:loadOrigin:scan: (1)C3
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C3
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Core
	-- Invocation:loadOrigin: (2)Core
	-- Invocation:loadOrigin:scan: (2)Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 4 C3
	-- ObjectGenerator:gen: super: (4)fork((1)C3):IS-empty: staticOff: 0
	-- Invocation:gen: (4)fork((1)C3)
	-- Invocation:loadOrigin: (4)fork((1)C3)
	-- Invocation:loadOrigin:scan: (4)fork((1)C3)
	-- Function:pushThis: 
	-- Function:loadOrigin: (4)fork((1)C3)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)C3:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C3
	-- Invocation:loadOrigin: (1)C3
	-- Invocation:loadOrigin:scan: (1)C3
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C3
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C3
	rpushg 4 C3
	-- Function:invoke: 
	-- pattern:load: fork((2)S: ? (1)Object)
	%fork 13
	-- ObjectGenerator:gen: super: (1)C4 (0):= (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C4 (0):= (2)Core
	-- Invocation:loadOrigin: (1)C4 (0):= (2)Core
	-- Invocation:loadOrigin:scan: (1)C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C4
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)Core
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Core:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Core
	-- Invocation:loadOrigin: (2)Core
	-- Invocation:loadOrigin:scan: (2)Core
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Core
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Core
	invoke 124 0 Core
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 5 C4
	-- ObjectGenerator:gen: super: (4)fork((1)C4):IS-empty: staticOff: 0
	-- Invocation:gen: (4)fork((1)C4)
	-- Invocation:loadOrigin: (4)fork((1)C4)
	-- Invocation:loadOrigin:scan: (4)fork((1)C4)
	-- Function:pushThis: 
	-- Function:loadOrigin: (4)fork((1)C4)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)C4:IS-empty: staticOff: 0
	-- Invocation:gen: (1)C4
	-- Invocation:loadOrigin: (1)C4
	-- Invocation:loadOrigin:scan: (1)C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C4
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C4
	rpushg 5 C4
	-- Function:invoke: 
	-- pattern:load: fork((2)S: ? (1)Object)
	%fork 13
	-- ObjectGenerator:gen: super: (0)S (0):= (2)Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: (0)S (0):= (2)Scheduler
	-- Invocation:loadOrigin: (0)S (0):= (2)Scheduler
	-- Invocation:loadOrigin:scan: (0)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)S
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)Scheduler
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Scheduler
	-- Invocation:loadOrigin: (2)Scheduler
	-- Invocation:loadOrigin:scan: (2)Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 S
	-- ObjectGenerator:gen: super: (1)C1.(0)attach((0)S):IS-empty: staticOff: 0
	-- Invocation:gen: (1)C1.(0)attach((0)S)
	-- Invocation:loadOrigin: (1)C1.(0)attach((0)S)
	-- Invocation:loadOrigin:scan: (1)C1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)attach((0)S) :E: (1)C1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C1
	rpushg 2 C1
	-- Invocation:loadOrigin:scan: (0)attach((0)S)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)S:IS-empty: staticOff: 0
	-- Invocation:gen: (0)S
	-- Invocation:loadOrigin: (0)S
	-- Invocation:loadOrigin:scan: (0)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)S
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach((2)M: ? (2)Scheduler)
	invoke 125 0 attach
	rpop
	-- ObjectGenerator:gen: super: (0)S (0):= (2)Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: (0)S (0):= (2)Scheduler
	-- Invocation:loadOrigin: (0)S (0):= (2)Scheduler
	-- Invocation:loadOrigin:scan: (0)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)S
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)Scheduler
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Scheduler
	-- Invocation:loadOrigin: (2)Scheduler
	-- Invocation:loadOrigin:scan: (2)Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 S
	-- ObjectGenerator:gen: super: (1)C2.(0)attach((0)S):IS-empty: staticOff: 0
	-- Invocation:gen: (1)C2.(0)attach((0)S)
	-- Invocation:loadOrigin: (1)C2.(0)attach((0)S)
	-- Invocation:loadOrigin:scan: (1)C2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)attach((0)S) :E: (1)C2
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C2
	rpushg 3 C2
	-- Invocation:loadOrigin:scan: (0)attach((0)S)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)S:IS-empty: staticOff: 0
	-- Invocation:gen: (0)S
	-- Invocation:loadOrigin: (0)S
	-- Invocation:loadOrigin:scan: (0)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)S
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach((2)M: ? (2)Scheduler)
	invoke 125 0 attach
	rpop
	-- ObjectGenerator:gen: super: (0)S (0):= (2)Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: (0)S (0):= (2)Scheduler
	-- Invocation:loadOrigin: (0)S (0):= (2)Scheduler
	-- Invocation:loadOrigin:scan: (0)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)S
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)Scheduler
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Scheduler
	-- Invocation:loadOrigin: (2)Scheduler
	-- Invocation:loadOrigin:scan: (2)Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 S
	-- ObjectGenerator:gen: super: (1)C3.(0)attach((0)S):IS-empty: staticOff: 0
	-- Invocation:gen: (1)C3.(0)attach((0)S)
	-- Invocation:loadOrigin: (1)C3.(0)attach((0)S)
	-- Invocation:loadOrigin:scan: (1)C3
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C3
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)attach((0)S) :E: (1)C3
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C3
	rpushg 4 C3
	-- Invocation:loadOrigin:scan: (0)attach((0)S)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)S:IS-empty: staticOff: 0
	-- Invocation:gen: (0)S
	-- Invocation:loadOrigin: (0)S
	-- Invocation:loadOrigin:scan: (0)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)S
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Function:invoke: 
	-- pattern:load: attach((2)M: ? (2)Scheduler)
	invoke 125 0 attach
	rpop
	-- ObjectGenerator:gen: super: (1)C4.(0)attach((2)Scheduler):IS-empty: staticOff: 0
	-- Invocation:gen: (1)C4.(0)attach((2)Scheduler)
	-- Invocation:loadOrigin: (1)C4.(0)attach((2)Scheduler)
	-- Invocation:loadOrigin:scan: (1)C4
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)C4
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)attach((2)Scheduler) :E: (1)C4
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: C4
	rpushg 5 C4
	-- Invocation:loadOrigin:scan: (0)attach((2)Scheduler)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Scheduler:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Scheduler
	-- Invocation:loadOrigin: (2)Scheduler
	-- Invocation:loadOrigin:scan: (2)Scheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Scheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Scheduler
	invoke 120 0 Scheduler
	-- Function:invoke: 
	-- pattern:load: attach((2)M: ? (2)Scheduler)
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
	-- ObjectGenerator:gen: super: (0)res (0):= (0)%this (1)Element:IS-empty: staticOff: 0
	-- Invocation:gen: (0)res (0):= (0)%this (1)Element
	-- Invocation:loadOrigin: (0)res (0):= (0)%this (1)Element
	-- Invocation:loadOrigin:scan: (0)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)res
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)%this (1)Element
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%this (1)Element:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%this (1)Element
	-- Invocation:loadOrigin: (0)%this (1)Element
	-- Invocation:loadOrigin:scan: (0)%this (1)Element
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (1)Element
	-- AdjustOrigin: 0
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (1)Element
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (0)currentElement (0):= (1)head:IS-empty: staticOff: 0
	-- Invocation:gen: (0)currentElement (0):= (1)head
	-- Invocation:loadOrigin: (0)currentElement (0):= (1)head
	-- Invocation:loadOrigin:scan: (0)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)currentElement
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)head:IS-empty: staticOff: 0
	-- Invocation:gen: (1)head
	-- Invocation:loadOrigin: (1)head
	-- Invocation:loadOrigin:scan: (1)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: (0)do:IS-empty: staticOff: 0
	-- Invocation:gen: (0)do
	-- Invocation:loadOrigin: (0)do
	-- Invocation:loadOrigin:scan: (0)do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)do
	-- AdjustOrigin: 0
	-- on : 0
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
	-- ObjectGenerator:gen: super: (0)currentElement (0):= (1)last:IS-empty: staticOff: 0
	-- Invocation:gen: (0)currentElement (0):= (1)last
	-- Invocation:loadOrigin: (0)currentElement (0):= (1)last
	-- Invocation:loadOrigin:scan: (0)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)currentElement
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)last
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)last:IS-empty: staticOff: 0
	-- Invocation:gen: (1)last
	-- Invocation:loadOrigin: (1)last
	-- Invocation:loadOrigin:scan: (1)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)last
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: (0)do:IS-empty: staticOff: 0
	-- Invocation:gen: (0)do
	-- Invocation:loadOrigin: (0)do
	-- Invocation:loadOrigin:scan: (0)do
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)do
	-- AdjustOrigin: 0
	-- on : 0
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
	-- ObjectGenerator:gen: super: (0)B (0):= (0)ELM (0)<> (4)NONE:IS-empty: staticOff: 0
	-- Invocation:gen: (0)B (0):= (0)ELM (0)<> (4)NONE
	-- Invocation:loadOrigin: (0)B (0):= (0)ELM (0)<> (4)NONE
	-- Invocation:loadOrigin:scan: (0)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)ELM (0)<> (4)NONE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)ELM (0)<> (4)NONE:IS-empty: staticOff: 0
	-- Invocation:gen: (0)ELM (0)<> (4)NONE
	-- Invocation:loadOrigin: (0)ELM (0)<> (4)NONE
	-- Invocation:loadOrigin:scan: (0)ELM
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)ELM
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)<> (4)NONE :E: (0)ELM
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Invocation:loadOrigin:scan: (0)<> (4)NONE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)NONE:IS-empty: staticOff: 0
	-- Invocation:gen: (4)NONE
	-- Invocation:loadOrigin: (4)NONE
	-- Invocation:loadOrigin:scan: (4)NONE
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)NONE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 b
	-- ObjectGenerator:gen: super: (0)%if (0)B (0)%then% 
    (1)E (0):= (2)Element((1)elm)
    (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (0)B (0)%then% 
    (1)E (0):= (2)Element((1)elm)
    (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- Invocation:loadOrigin: (0)%if (0)B (0)%then% 
    (1)E (0):= (2)Element((1)elm)
    (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- Invocation:loadOrigin:scan: (0)%if (0)B (0)%then% 
    (1)E (0):= (2)Element((1)elm)
    (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (0)B (0)%then% 
    (1)E (0):= (2)Element((1)elm)
    (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (0)B (0)%then% 
    (1)E (0):= (2)Element((1)elm)
    (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (0)B:IS-empty: staticOff: 0
	-- Invocation:gen: (0)B
	-- Invocation:loadOrigin: (0)B
	-- Invocation:loadOrigin:scan: (0)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)B
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: b
	pushg 1 b
	jmpFalse L204
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 530 0 #S#530
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
	-- ObjectGenerator:gen: super: (1)scan:singular:staticOff: 0
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
	-- ObjectGenerator:gen: super: (0)%if (1)last (0)<> (4)none (0)%then% 
    (1)elm (0):= (2)last.(0)elm
    (2)last (0):= (2)last.(0)pred
    (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)last (0)<> (4)none (0)%then% 
    (1)elm (0):= (2)last.(0)elm
    (2)last (0):= (2)last.(0)pred
    (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- Invocation:loadOrigin: (0)%if (1)last (0)<> (4)none (0)%then% 
    (1)elm (0):= (2)last.(0)elm
    (2)last (0):= (2)last.(0)pred
    (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- Invocation:loadOrigin:scan: (0)%if (1)last (0)<> (4)none (0)%then% 
    (1)elm (0):= (2)last.(0)elm
    (2)last (0):= (2)last.(0)pred
    (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)last (0)<> (4)none (0)%then% 
    (1)elm (0):= (2)last.(0)elm
    (2)last (0):= (2)last.(0)pred
    (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)last (0)<> (4)none (0)%then% 
    (1)elm (0):= (2)last.(0)elm
    (2)last (0):= (2)last.(0)pred
    (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)last (0)<> (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (1)last (0)<> (4)none
	-- Invocation:loadOrigin: (1)last (0)<> (4)none
	-- Invocation:loadOrigin:scan: (1)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)last
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)<> (4)none :E: (1)last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: (0)<> (4)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (4)none
	-- Invocation:loadOrigin: (4)none
	-- Invocation:loadOrigin:scan: (4)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	jmpFalse L209
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 534 0 #S#534
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
	-- ObjectGenerator:gen: super: (0)B (0):= (1)head (0)= (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (0)B (0):= (1)head (0)= (4)none
	-- Invocation:loadOrigin: (0)B (0):= (1)head (0)= (4)none
	-- Invocation:loadOrigin:scan: (0)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)B
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)head (0)= (4)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)head (0)= (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (1)head (0)= (4)none
	-- Invocation:loadOrigin: (1)head (0)= (4)none
	-- Invocation:loadOrigin:scan: (1)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (4)none :E: (1)head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: (0)= (4)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (4)none
	-- Invocation:loadOrigin: (4)none
	-- Invocation:loadOrigin:scan: (4)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	req
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)head (0):= (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (1)head (0):= (4)none
	-- Invocation:loadOrigin: (1)head (0):= (4)none
	-- Invocation:loadOrigin:scan: (1)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (4)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (4)none
	-- Invocation:loadOrigin: (4)none
	-- Invocation:loadOrigin:scan: (4)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 head
	-- ObjectGenerator:gen: super: (1)last (0):= (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (1)last (0):= (4)none
	-- Invocation:loadOrigin: (1)last (0):= (4)none
	-- Invocation:loadOrigin:scan: (1)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)last
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (4)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)none:IS-empty: staticOff: 0
	-- Invocation:gen: (4)none
	-- Invocation:loadOrigin: (4)none
	-- Invocation:loadOrigin:scan: (4)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (4)put('Q'):IS-empty: staticOff: 0
	-- Invocation:gen: (4)put('Q')
	-- Invocation:loadOrigin: (4)put('Q')
	-- Invocation:loadOrigin:scan: (4)put('Q')
	-- Function:pushThis: 
	-- Function:loadOrigin: (4)put('Q')
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
	-- pattern:load: put((1)ch: ? (1)char)
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
	-- ObjectGenerator:gen: super: (1)L.(0)get:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)get
	-- Invocation:loadOrigin: (1)L.(0)get
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)get :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: (0)get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: (0)%inner (1)entry:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)entry
	-- Invocation:loadOrigin: (0)%inner (1)entry
	-- Invocation:loadOrigin:scan: (0)%inner (1)entry
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)entry
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)entry
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: (1)L.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)free
	-- Invocation:loadOrigin: (1)L.(0)free
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)free :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: (0)free
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
	-- ObjectGenerator:gen: super: (1)entry:singular:staticOff: 0
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
	-- ObjectGenerator:gen: super: (1)entry:singular:staticOff: 0
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
	-- ObjectGenerator:gen: super: (1)entry:singular:staticOff: 0
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
	-- ObjectGenerator:gen: super: (1)L.(0)get:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)get
	-- Invocation:loadOrigin: (1)L.(0)get
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)get :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: (0)get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: (1)V (0):= (1)V (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0):= (1)V (0)+ 1
	-- Invocation:loadOrigin: (1)V (0):= (1)V (0)+ 1
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)V (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)V (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0)+ 1
	-- Invocation:loadOrigin: (1)V (0)+ 1
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (1)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 V
	-- ObjectGenerator:gen: super: (0)%if (1)V (0)> 1 (0)%then% 
    (5)put('V'):IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)V (0)> 1 (0)%then% 
    (5)put('V')
	-- Invocation:loadOrigin: (0)%if (1)V (0)> 1 (0)%then% 
    (5)put('V')
	-- Invocation:loadOrigin:scan: (0)%if (1)V (0)> 1 (0)%then% 
    (5)put('V')
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)V (0)> 1 (0)%then% 
    (5)put('V')
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)V (0)> 1 (0)%then% 
    (5)put('V')
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)V (0)> 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0)> 1
	-- Invocation:loadOrigin: (1)V (0)> 1
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)> 1 :E: (1)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)> 1
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
	-- pattern:load: > (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	gt
	jmpFalse L226
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 553 0 #S#553
	rpop
 L226:
	-- ObjectGenerator:gen: super: (4)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (4)inner
	-- Invocation:loadOrigin: (4)inner
	-- Invocation:loadOrigin:scan: (4)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: (1)V (0):= (1)V (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0):= (1)V (0)- 1
	-- Invocation:loadOrigin: (1)V (0):= (1)V (0)- 1
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)V (0)- 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)V (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0)- 1
	-- Invocation:loadOrigin: (1)V (0)- 1
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)- 1 :E: (1)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)- 1
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
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 V
	-- ObjectGenerator:gen: super: (1)L.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)free
	-- Invocation:loadOrigin: (1)L.(0)free
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)free :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 3 L
	-- Invocation:loadOrigin:scan: (0)free
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
	-- Invocation:loadOrigin: (0)entry
	-- Invocation:loadOrigin:scan: (0)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L227:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)V (0):= 0:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0):= 0
	-- Invocation:loadOrigin: (1)V (0):= 0
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 0
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
	-- pattern:load: := (2)V: ? (2)Object
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
	-- Invocation:loadOrigin: (0)entry
	-- Invocation:loadOrigin:scan: (0)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L229:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)Q.(0)insert((0)P):IS-empty: staticOff: 0
	-- Invocation:gen: (1)Q.(0)insert((0)P)
	-- Invocation:loadOrigin: (1)Q.(0)insert((0)P)
	-- Invocation:loadOrigin:scan: (1)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)insert((0)P) :E: (1)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)insert((0)P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)P:IS-empty: staticOff: 0
	-- Invocation:gen: (0)P
	-- Invocation:loadOrigin: (0)P
	-- Invocation:loadOrigin:scan: (0)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert((2)elm: ? (4)Object)
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
	-- ObjectGenerator:gen: super: (1)entry:singular:staticOff: 0
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
	-- Invocation:loadOrigin: (0)entry
	-- Invocation:loadOrigin:scan: (0)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L233:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)Q.(0)remove((0)P):IS-empty: staticOff: 0
	-- Invocation:gen: (1)Q.(0)remove((0)P)
	-- Invocation:loadOrigin: (1)Q.(0)remove((0)P)
	-- Invocation:loadOrigin:scan: (1)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)remove((0)P) :E: (1)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)remove((0)P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)P:IS-empty: staticOff: 0
	-- Invocation:gen: (0)P
	-- Invocation:loadOrigin: (0)P
	-- Invocation:loadOrigin:scan: (0)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: remove((2)elm: ? (4)Object)
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
	-- ObjectGenerator:gen: super: (1)entry:singular:staticOff: 0
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
	-- Invocation:loadOrigin: (0)entry
	-- Invocation:loadOrigin:scan: (0)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L237:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)Q.(0)display:IS-empty: staticOff: 0
	-- Invocation:gen: (1)Q.(0)display
	-- Invocation:loadOrigin: (1)Q.(0)display
	-- Invocation:loadOrigin:scan: (1)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)display :E: (1)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)display
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
	-- Invocation:loadOrigin: (0)entry
	-- Invocation:loadOrigin:scan: (0)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L239:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)W (0):= (1)W (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)W (0):= (1)W (0)+ 1
	-- Invocation:loadOrigin: (1)W (0):= (1)W (0)+ 1
	-- Invocation:loadOrigin:scan: (1)W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)W (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)W (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)W (0)+ 1
	-- Invocation:loadOrigin: (1)W (0)+ 1
	-- Invocation:loadOrigin:scan: (1)W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (1)W
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- Invocation:loadOrigin: (0)entry
	-- Invocation:loadOrigin:scan: (0)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)entry
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L241:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)W (0):= (1)W (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)W (0):= (1)W (0)- 1
	-- Invocation:loadOrigin: (1)W (0):= (1)W (0)- 1
	-- Invocation:loadOrigin:scan: (1)W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)W (0)- 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)W (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)W (0)- 1
	-- Invocation:loadOrigin: (1)W (0)- 1
	-- Invocation:loadOrigin:scan: (1)W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)W
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)- 1 :E: (1)W
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: (0)- 1
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
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)entry:singular:staticOff: 0
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
	-- ObjectGenerator:gen: super: (1)L.(0)get:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)get
	-- Invocation:loadOrigin: (1)L.(0)get
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)get :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: (0)get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: (1)L.(0)init:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)init
	-- Invocation:loadOrigin: (1)L.(0)init
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)init :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: (0)init
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: init
	invoke 114 0 init
	rpop
	-- ObjectGenerator:gen: super: (1)L.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)free
	-- Invocation:loadOrigin: (1)L.(0)free
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)free :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: (0)free
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
	-- ObjectGenerator:gen: super: (1)L.(0)get:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)get
	-- Invocation:loadOrigin: (1)L.(0)get
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)get :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: (0)get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: (4)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (4)inner
	-- Invocation:loadOrigin: (4)inner
	-- Invocation:loadOrigin:scan: (4)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: (1)L.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L.(0)free
	-- Invocation:loadOrigin: (1)L.(0)free
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)free :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: L
	rpushg 2 L
	-- Invocation:loadOrigin:scan: (0)free
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
	-- Invocation:loadOrigin: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- ObjectGenerator:gen: super: (1)pos (0)= (1)rep.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)pos (0)= (1)rep.(0)length
	-- Invocation:loadOrigin: (1)pos (0)= (1)rep.(0)length
	-- Invocation:loadOrigin:scan: (1)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (1)rep.(0)length :E: (1)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)= (1)rep.(0)length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)rep.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)length
	-- Invocation:loadOrigin: (1)rep.(0)length
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)length :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)res: ? (2)integer
	invoke 55 0 length
	-- Binary:invoke: 
	-- pattern:load: = (1)V: ? (2)integer -> (2)B: ? (2)Boolean
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
	-- Invocation:loadOrigin: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)pos (0)= (1)rep.(0)length (0)%then% 
    (3)pos (0):= 1 (0)%else% 
    (3)pos (0):= (3)pos (0)+ 1
	-- ObjectGenerator:gen: super: (1)pos (0)= (1)rep.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)pos (0)= (1)rep.(0)length
	-- Invocation:loadOrigin: (1)pos (0)= (1)rep.(0)length
	-- Invocation:loadOrigin:scan: (1)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (1)rep.(0)length :E: (1)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)= (1)rep.(0)length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)rep.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)length
	-- Invocation:loadOrigin: (1)rep.(0)length
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)length :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)res: ? (2)integer
	invoke 55 0 length
	-- Binary:invoke: 
	-- pattern:load: = (1)V: ? (2)integer -> (2)B: ? (2)Boolean
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
	-- Invocation:loadOrigin: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1
	-- ObjectGenerator:gen: super: (1)pos (0)= (1)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (1)pos (0)= (1)noof
	-- Invocation:loadOrigin: (1)pos (0)= (1)noof
	-- Invocation:loadOrigin:scan: (1)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (1)noof :E: (1)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)= (1)noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (1)noof
	-- Invocation:loadOrigin: (1)noof
	-- Invocation:loadOrigin:scan: (1)noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)noof
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: = (1)V: ? (2)integer -> (2)B: ? (2)Boolean
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
	-- Invocation:loadOrigin: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1
	-- Invocation:loadOrigin:scan: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)pos (0)= (1)noof (0)%then% 
    (2)res (0):= 9999999 (0)%else% 
    (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1
	-- ObjectGenerator:gen: super: (1)pos (0)= (1)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (1)pos (0)= (1)noof
	-- Invocation:loadOrigin: (1)pos (0)= (1)noof
	-- Invocation:loadOrigin:scan: (1)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)pos
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (1)noof :E: (1)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)= (1)noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (1)noof
	-- Invocation:loadOrigin: (1)noof
	-- Invocation:loadOrigin:scan: (1)noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)noof
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: = (1)V: ? (2)integer -> (2)B: ? (2)Boolean
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
	-- ObjectGenerator:gen: super: (1)current (0):= (2)rep.(0)%get (2)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (1)current (0):= (2)rep.(0)%get (2)pos
	-- Invocation:loadOrigin: (1)current (0):= (2)rep.(0)%get (2)pos
	-- Invocation:loadOrigin:scan: (1)current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)current
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)rep.(0)%get (2)pos
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)rep.(0)%get (2)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (2)rep.(0)%get (2)pos
	-- Invocation:loadOrigin: (2)rep.(0)%get (2)pos
	-- Invocation:loadOrigin:scan: (2)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)rep
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)%get (2)pos :E: (2)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%get (2)pos
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get (2)pos
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (2)pos:IS-empty: staticOff: 0
	-- Invocation:gen: (2)pos
	-- Invocation:loadOrigin: (2)pos
	-- Invocation:loadOrigin:scan: (2)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)pos
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 current
	-- ObjectGenerator:gen: super: (2)pos (0):= (2)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)pos (0):= (2)pos (0)+ 1
	-- Invocation:loadOrigin: (2)pos (0):= (2)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (2)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)pos (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)pos (0)+ 1
	-- Invocation:loadOrigin: (2)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (2)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (2)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 pos
	-- ObjectGenerator:gen: super: (0)%inner (2)forAll:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (2)forAll
	-- Invocation:loadOrigin: (0)%inner (2)forAll
	-- Invocation:loadOrigin:scan: (0)%inner (2)forAll
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (2)forAll
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (2)forAll
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: (0)%if (2)pos (0)< (2)noof (0)%then% 
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)pos (0)< (2)noof (0)%then% 
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (2)pos (0)< (2)noof (0)%then% 
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (2)pos (0)< (2)noof (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)pos (0)< (2)noof (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)pos (0)< (2)noof (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)pos (0)< (2)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (2)pos (0)< (2)noof
	-- Invocation:loadOrigin: (2)pos (0)< (2)noof
	-- Invocation:loadOrigin:scan: (2)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)pos
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)< (2)noof :E: (2)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)< (2)noof
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)noof:IS-empty: staticOff: 0
	-- Invocation:gen: (2)noof
	-- Invocation:loadOrigin: (2)noof
	-- Invocation:loadOrigin:scan: (2)noof
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)noof
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: noof
	pushg 2 noof
	-- Binary:invoke: 
	-- pattern:load: < (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	51
	jmpFalse L259
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 562 0 #S#562
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
	-- Invocation:loadOrigin: (0)%for 1 (0)%to% (1)rep.(0)length (0)%do% 
    (5)putint((3)rep.(0)%get (1)inx)
    ", ".(0)print
	-- Invocation:loadOrigin:scan: (0)%for 1 (0)%to% (1)rep.(0)length (0)%do% 
    (5)putint((3)rep.(0)%get (1)inx)
    ", ".(0)print
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%for 1 (0)%to% (1)rep.(0)length (0)%do% 
    (5)putint((3)rep.(0)%get (1)inx)
    ", ".(0)print
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object(0)%for 1 (0)%to% (1)rep.(0)length (0)%do% 
    (5)putint((3)rep.(0)%get (1)inx)
    ", ".(0)print
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: (1)rep.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)rep.(0)length
	-- Invocation:loadOrigin: (1)rep.(0)length
	-- Invocation:loadOrigin:scan: (1)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)rep
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)length :E: (1)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)res: ? (2)integer
	invoke 55 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L260:
 L261:
	rtnInner
	end 1

	class #S#564 564
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L262:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: "index error in range".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "index error in range".(0)print
	-- Invocation:loadOrigin: "index error in range".(0)print
	-- Invocation:loadOrigin:scan: "index error in range"
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText index error in range
	-- next not assign: (0)print :E: "index error in range"
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
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
	-- ObjectGenerator:gen: super: (1)M.(0)get:IS-empty: staticOff: 0
	-- Invocation:gen: (1)M.(0)get
	-- Invocation:loadOrigin: (1)M.(0)get
	-- Invocation:loadOrigin:scan: (1)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)get :E: (1)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: (0)get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: (1)Q.(0)insert((0)P):IS-empty: staticOff: 0
	-- Invocation:gen: (1)Q.(0)insert((0)P)
	-- Invocation:loadOrigin: (1)Q.(0)insert((0)P)
	-- Invocation:loadOrigin:scan: (1)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Q
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)insert((0)P) :E: (1)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)insert((0)P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)P:IS-empty: staticOff: 0
	-- Invocation:gen: (0)P
	-- Invocation:loadOrigin: (0)P
	-- Invocation:loadOrigin:scan: (0)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert((2)elm: ? (4)Object)
	invoke 83 0 insert
	rpop
	-- ObjectGenerator:gen: super: (2)SQS.(0)insert((0)P):IS-empty: staticOff: 0
	-- Invocation:gen: (2)SQS.(0)insert((0)P)
	-- Invocation:loadOrigin: (2)SQS.(0)insert((0)P)
	-- Invocation:loadOrigin:scan: (2)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)SQS
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)insert((0)P) :E: (2)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)insert((0)P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)P:IS-empty: staticOff: 0
	-- Invocation:gen: (0)P
	-- Invocation:loadOrigin: (0)P
	-- Invocation:loadOrigin:scan: (0)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert((2)P: ? (2)BasicProcess)
	invoke 145 0 insert
	rpop
	-- ObjectGenerator:gen: super: (1)M.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (1)M.(0)free
	-- Invocation:loadOrigin: (1)M.(0)free
	-- Invocation:loadOrigin:scan: (1)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)free :E: (1)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 3 M
	-- Invocation:loadOrigin:scan: (0)free
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
	-- ObjectGenerator:gen: super: (1)cnt (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cnt (0):= 1
	-- Invocation:loadOrigin: (1)cnt (0):= 1
	-- Invocation:loadOrigin:scan: (1)cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
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
	-- ObjectGenerator:gen: super: (1)M.(0)get:IS-empty: staticOff: 0
	-- Invocation:gen: (1)M.(0)get
	-- Invocation:loadOrigin: (1)M.(0)get
	-- Invocation:loadOrigin:scan: (1)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)get :E: (1)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: (0)get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: (1)cnt (0):= (1)cnt (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cnt (0):= (1)cnt (0)- 1
	-- Invocation:loadOrigin: (1)cnt (0):= (1)cnt (0)- 1
	-- Invocation:loadOrigin:scan: (1)cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)cnt (0)- 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)cnt (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cnt (0)- 1
	-- Invocation:loadOrigin: (1)cnt (0)- 1
	-- Invocation:loadOrigin:scan: (1)cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)- 1 :E: (1)cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: (0)- 1
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
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 cnt
	-- ObjectGenerator:gen: super: (0)%if (1)cnt (0)< 0 (0)%then% 
    (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING
    (4)SQS.(0)addWaiting
    (3)Q.(0)insert((6)thisCore.(0)main.(0)active)
    (2)theActive (0):= (6)thisCore.(0)main.(0)active
    (3)M.(0)free
    (2)theActive.(0)suspend (0)%else% 
    (3)M.(0)free:IS-empty: staticOff: 0
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
	-- ObjectGenerator:gen: super: (1)M.(0)get:IS-empty: staticOff: 0
	-- Invocation:gen: (1)M.(0)get
	-- Invocation:loadOrigin: (1)M.(0)get
	-- Invocation:loadOrigin:scan: (1)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)M
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)get :E: (1)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: (0)get
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: get
	invoke 115 0 get
	rpop
	-- ObjectGenerator:gen: super: (1)cnt (0):= (1)cnt (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cnt (0):= (1)cnt (0)+ 1
	-- Invocation:loadOrigin: (1)cnt (0):= (1)cnt (0)+ 1
	-- Invocation:loadOrigin:scan: (1)cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)cnt (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)cnt (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cnt (0)+ 1
	-- Invocation:loadOrigin: (1)cnt (0)+ 1
	-- Invocation:loadOrigin:scan: (1)cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cnt
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (1)cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 cnt
	-- ObjectGenerator:gen: super: (0)%if (1)cnt (0)<= 0 (0)%then% 
    (2)P (0):= (3)Q.(0)removeNext
    (2)P.(0)status (0):= (4)P_status.(0)ACTIVE
    (4)SQS.(0)insert((2)P)
    (4)SQS.(0)dcrWaiting
    (3)M.(0)free (0)%else% 
    (3)M.(0)free:IS-empty: staticOff: 0
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
	-- ObjectGenerator:gen: super: (0)P (0):= (0)%this (2)Process:IS-empty: staticOff: 0
	-- Invocation:gen: (0)P (0):= (0)%this (2)Process
	-- Invocation:loadOrigin: (0)P (0):= (0)%this (2)Process
	-- Invocation:loadOrigin:scan: (0)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)P
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)%this (2)Process
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%this (2)Process:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%this (2)Process
	-- Invocation:loadOrigin: (0)%this (2)Process
	-- Invocation:loadOrigin:scan: (0)%this (2)Process
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%this (2)Process
	-- AdjustOrigin: 0
	rpushg 2 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%this (2)P: ? (1)Object(0)%this (2)Process
	-- KeyWord:invoke: 
	-- pattern:load: (0)%this (2)P: ? (1)Object
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 P
	-- ObjectGenerator:gen: super: "starting: ".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: "starting: ".(0)print
	-- Invocation:loadOrigin: "starting: ".(0)print
	-- Invocation:loadOrigin:scan: "starting: "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText starting: 
	-- next not assign: (0)print :E: "starting: "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: (1)id.(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: (1)id.(0)print
	-- Invocation:loadOrigin: (1)id.(0)print
	-- Invocation:loadOrigin:scan: (1)id
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)id
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- next not assign: (0)print :E: (1)id
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: id
	rpushg 2 id
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
	-- ObjectGenerator:gen: super: (4)newline:IS-empty: staticOff: 0
	-- Invocation:gen: (4)newline
	-- Invocation:loadOrigin: (4)newline
	-- Invocation:loadOrigin:scan: (4)newline
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)newline
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
	-- ObjectGenerator:gen: super: (2)SQS.(0)insert((0)P):IS-empty: staticOff: 0
	-- Invocation:gen: (2)SQS.(0)insert((0)P)
	-- Invocation:loadOrigin: (2)SQS.(0)insert((0)P)
	-- Invocation:loadOrigin:scan: (2)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)SQS
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)insert((0)P) :E: (2)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)insert((0)P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)P:IS-empty: staticOff: 0
	-- Invocation:gen: (0)P
	-- Invocation:loadOrigin: (0)P
	-- Invocation:loadOrigin:scan: (0)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)P
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 3 P
	-- Function:invoke: 
	-- pattern:load: insert((2)P: ? (2)BasicProcess)
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
	-- ObjectGenerator:gen: super: (1)mutex.(0)init:IS-empty: staticOff: 0
	-- Invocation:gen: (1)mutex.(0)init
	-- Invocation:loadOrigin: (1)mutex.(0)init
	-- Invocation:loadOrigin:scan: (1)mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)mutex
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)init :E: (1)mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: (0)init
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
	-- ObjectGenerator:gen: super: (1)mutex.(0)wait:IS-empty: staticOff: 0
	-- Invocation:gen: (1)mutex.(0)wait
	-- Invocation:loadOrigin: (1)mutex.(0)wait
	-- Invocation:loadOrigin:scan: (1)mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)mutex
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)wait :E: (1)mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: (0)wait
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: wait
	invoke 201 0 wait
	rpop
	-- ObjectGenerator:gen: super: (1)V (0):= (1)V (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0):= (1)V (0)+ 1
	-- Invocation:loadOrigin: (1)V (0):= (1)V (0)+ 1
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)V (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)V (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0)+ 1
	-- Invocation:loadOrigin: (1)V (0)+ 1
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (1)V
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: V
	pushg 1 V
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 V
	-- ObjectGenerator:gen: super: (4)inner:IS-empty: staticOff: 0
	-- Invocation:gen: (4)inner
	-- Invocation:loadOrigin: (4)inner
	-- Invocation:loadOrigin:scan: (4)inner
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)inner
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: inner
	inner  1
	-- ObjectGenerator:gen: super: (1)mutex.(0)signal:IS-empty: staticOff: 0
	-- Invocation:gen: (1)mutex.(0)signal
	-- Invocation:loadOrigin: (1)mutex.(0)signal
	-- Invocation:loadOrigin:scan: (1)mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)mutex
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)signal :E: (1)mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: (0)signal
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
	-- ObjectGenerator:gen: super: (4)Indexed((1)L (0)+ (1)S.(0)length,(4)Integer):IS-empty: staticOff: 2
	-- Invocation:gen: (4)Indexed((1)L (0)+ (1)S.(0)length,(4)Integer)
	-- Invocation:loadOrigin: (4)Indexed((1)L (0)+ (1)S.(0)length,(4)Integer)
	-- Invocation:loadOrigin:scan: (4)Indexed((1)L (0)+ (1)S.(0)length,(4)Integer)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (4)Indexed((1)L (0)+ (1)S.(0)length,(4)Integer)
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)L (0)+ (1)S.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L (0)+ (1)S.(0)length
	-- Invocation:loadOrigin: (1)L (0)+ (1)S.(0)length
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ (1)S.(0)length :E: (1)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Invocation:loadOrigin:scan: (0)+ (1)S.(0)length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)S.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)S.(0)length
	-- Invocation:loadOrigin: (1)S.(0)length
	-- Invocation:loadOrigin:scan: (1)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)length :E: (1)S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: (0)length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- ObjectGenerator:gen: super: (4)Integer:IS-empty: staticOff: 0
	-- Invocation:gen: (4)Integer
	-- Invocation:loadOrigin: (4)Integer
	-- Invocation:loadOrigin:scan: (4)Integer
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (4)Integer
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: integer((1)W: ? (1)integer)
	-- Function:invoke: 
	-- pattern:load: Indexed((1)range: ? (1)Integer,(1)elm:< (1)Object)
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
	-- ObjectGenerator:gen: super: (0)%for 1 (0)%to% (1)L (0)%do% 
    (2)e (0):= (0)%get (1)inx
    (2)T.(0)%put (2)e (0)%at% (1)inx:IS-empty: staticOff: 0
	pushThis 
	invoke 95 0 %for%to%%do%#S#95
	rpop
	-- ObjectGenerator:gen: super: (0)%for 1 (0)%to% (1)S.(0)length (0)%do% 
    (2)e (0):= (3)S.(0)%get (1)inx
    (2)i (0):= (3)L (0)+ (1)inx
    (2)T.(0)%put (2)e (0)%at% (2)i:IS-empty: staticOff: 0
	pushThis 
	invoke 96 0 %for%to%%do%#S#96
	rpop
	-- ObjectGenerator:gen: super: (1)V (0):= (0)T.(0)asString:IS-empty: staticOff: 0
	-- Invocation:gen: (1)V (0):= (0)T.(0)asString
	-- Invocation:loadOrigin: (1)V (0):= (0)T.(0)asString
	-- Invocation:loadOrigin:scan: (1)V
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)V
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (0)T.(0)asString
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)T.(0)asString:IS-empty: staticOff: 0
	-- Invocation:gen: (0)T.(0)asString
	-- Invocation:loadOrigin: (0)T.(0)asString
	-- Invocation:loadOrigin:scan: (0)T
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)T
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)asString :E: (0)T
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: (0)asString
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: asString -> (2)S: ? (2)Object
	%asString 118
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
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
	-- Invocation:loadOrigin: (0)%for 1 (0)%to% (1)length (0)%do% 
    (2)current (0):= (0)%get (1)inx
    (0)%inner (3)scan
	-- Invocation:loadOrigin:scan: (0)%for 1 (0)%to% (1)length (0)%do% 
    (2)current (0):= (0)%get (1)inx
    (0)%inner (3)scan
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%for 1 (0)%to% (1)length (0)%do% 
    (2)current (0):= (0)%get (1)inx
    (0)%inner (3)scan
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object(0)%for 1 (0)%to% (1)length (0)%do% 
    (2)current (0):= (0)%get (1)inx
    (0)%inner (3)scan
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: (1)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)length
	-- Invocation:loadOrigin: (1)length
	-- Invocation:loadOrigin:scan: (1)length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)length
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
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
	-- Invocation:loadOrigin: (0)%for 1 (0)%to% (1)length (0)%do% 
    (5)put((0)%get (1)inx)
	-- Invocation:loadOrigin:scan: (0)%for 1 (0)%to% (1)length (0)%do% 
    (5)put((0)%get (1)inx)
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%for 1 (0)%to% (1)length (0)%do% 
    (5)put((0)%get (1)inx)
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object(0)%for 1 (0)%to% (1)length (0)%do% 
    (5)put((0)%get (1)inx)
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: (1)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)length
	-- Invocation:loadOrigin: (1)length
	-- Invocation:loadOrigin:scan: (1)length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)length
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
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
	-- ObjectGenerator:gen: super: (0)L (0):= (2)length:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L (0):= (2)length
	-- Invocation:loadOrigin: (0)L (0):= (2)length
	-- Invocation:loadOrigin:scan: (0)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)length:IS-empty: staticOff: 0
	-- Invocation:gen: (2)length
	-- Invocation:loadOrigin: (2)length
	-- Invocation:loadOrigin:scan: (2)length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)length
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 3 L
	-- ObjectGenerator:gen: super: (0)%if (0)L (0)<> (1)S.(0)length (0)%then% 
    (0)%leave (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (0)L (0)<> (1)S.(0)length (0)%then% 
    (0)%leave (2)loop
	-- Invocation:loadOrigin: (0)%if (0)L (0)<> (1)S.(0)length (0)%then% 
    (0)%leave (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (0)L (0)<> (1)S.(0)length (0)%then% 
    (0)%leave (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (0)L (0)<> (1)S.(0)length (0)%then% 
    (0)%leave (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (0)L (0)<> (1)S.(0)length (0)%then% 
    (0)%leave (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (0)L (0)<> (1)S.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L (0)<> (1)S.(0)length
	-- Invocation:loadOrigin: (0)L (0)<> (1)S.(0)length
	-- Invocation:loadOrigin:scan: (0)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L
	-- AdjustOrigin: 0
	-- on : 0
	-- next not assign: (0)<> (1)S.(0)length :E: (0)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 3 L
	-- Invocation:loadOrigin:scan: (0)<> (1)S.(0)length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)S.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)S.(0)length
	-- Invocation:loadOrigin: (1)S.(0)length
	-- Invocation:loadOrigin:scan: (1)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)length :E: (1)S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: (0)length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:load: <> (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	55
	jmpFalse L290
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 540 0 #S#540
	rpop
 L290:
	-- ObjectGenerator:gen: super: (1)B (0):= (4)true:IS-empty: staticOff: 0
	-- Invocation:gen: (1)B (0):= (4)true
	-- Invocation:loadOrigin: (1)B (0):= (4)true
	-- Invocation:loadOrigin:scan: (1)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (4)true
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)true:IS-empty: staticOff: 0
	-- Invocation:gen: (4)true
	-- Invocation:loadOrigin: (4)true
	-- Invocation:loadOrigin:scan: (4)true
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)true
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: True -> (1)B: ? (1)Boolean
	invoke 24 0 True
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 B
	-- ObjectGenerator:gen: super: (0)%for 1 (0)%to% (2)length (0)%do% 
    (2)c1 (0):= (0)%get (1)inx
    (2)c2 (0):= (3)S.(0)%get (1)inx
    (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop:IS-empty: staticOff: 0
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
	-- ObjectGenerator:gen: super: (0)L1 (0):= (2)length:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L1 (0):= (2)length
	-- Invocation:loadOrigin: (0)L1 (0):= (2)length
	-- Invocation:loadOrigin:scan: (0)L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L1
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (2)length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)length:IS-empty: staticOff: 0
	-- Invocation:gen: (2)length
	-- Invocation:loadOrigin: (2)length
	-- Invocation:loadOrigin:scan: (2)length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)length
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 2 L1
	-- ObjectGenerator:gen: super: (0)L2 (0):= (1)S.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L2 (0):= (1)S.(0)length
	-- Invocation:loadOrigin: (0)L2 (0):= (1)S.(0)length
	-- Invocation:loadOrigin:scan: (0)L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L2
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (1)S.(0)length
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)S.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)S.(0)length
	-- Invocation:loadOrigin: (1)S.(0)length
	-- Invocation:loadOrigin:scan: (1)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)S
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)length :E: (1)S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: (0)length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 3 L2
	-- ObjectGenerator:gen: super: (0)L (0):= (0)L1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L (0):= (0)L1
	-- Invocation:loadOrigin: (0)L (0):= (0)L1
	-- Invocation:loadOrigin:scan: (0)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (0)L1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)L1:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L1
	-- Invocation:loadOrigin: (0)L1
	-- Invocation:loadOrigin:scan: (0)L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L1
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 L
	-- ObjectGenerator:gen: super: (0)%if (0)L1 (0)< (0)L2 (0)%then% 
    (2)L (0):= (2)L1 (0)%else% 
    (2)L (0):= (2)L2:IS-empty: staticOff: 0
	pushThis 
	invoke 111 0 %if%then%%else%#S#111
	rpop
	-- ObjectGenerator:gen: super: (0)matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: (0)matchEq
	-- Invocation:loadOrigin: (0)matchEq
	-- Invocation:loadOrigin:scan: (0)matchEq
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)matchEq
	-- AdjustOrigin: 0
	-- on : 0
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

	class List 436
	pushThis 
	rstoreg 3 tail
	pushThis 
	rstoreg 2 head
	rstore 1 origin
	allocEventQ
	mvStack 
	-- pattern:gen: empty -> (1)b: ? (5)boolean
	rtnEventQ 0
	DO:
	mvStack 
 L293:
	-- Include:gen: 
 L294:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class RangeList 438
	rstore 1 origin
	allocEventQ
	-- super List
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)List((1)Range)
	-- Invocation:loadOrigin:scan: (0)List((1)Range)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)List((1)Range)
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)Range:IS-empty: staticOff: 0
	-- Invocation:gen: (1)Range
	-- Invocation:loadOrigin: (1)Range
	-- Invocation:loadOrigin:scan: (1)Range
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)Range
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Range((2)r: ? (4)Indexed)
	invoke 440 0 Range
	topSuper  436
	innerA  2
	rtnInner
	DO:
	doEventQ
	mvStack 
 L295:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%inner (1)RangeList:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)RangeList
	-- Invocation:loadOrigin: (0)%inner (1)RangeList
	-- Invocation:loadOrigin:scan: (0)%inner (1)RangeList
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)RangeList
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)RangeList
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  2
	rpopThisObj 
 L296:
	rtnInner
	end 1

	class Range 440
	pushThis 
	rstoreg 2 r
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L297:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%inner (1)Range:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)Range
	-- Invocation:loadOrigin: (0)%inner (1)Range
	-- Invocation:loadOrigin:scan: (0)%inner (1)Range
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)Range
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)Range
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  1
	rpopThisObj 
 L298:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class testArray 441
	pushThis 
	pushThis 
	storeg 1 ndim
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
	-- ObjectGenerator:gen: super: (0)%inner (1)testArray:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)testArray
	-- Invocation:loadOrigin: (0)%inner (1)testArray
	-- Invocation:loadOrigin:scan: (0)%inner (1)testArray
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)testArray
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)testArray
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  1
	rpopThisObj 
 L300:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class List#S#626 626
	rstore 1 origin
	allocEventQ
	-- super List
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)List((3)Object,(3)none,(3)none)
	-- Invocation:loadOrigin:scan: (0)List((3)Object,(3)none,(3)none)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (0)List((3)Object,(3)none,(3)none)
	-- AdjustOrigin: 1
	rpushg 1 origin
	-- on : 0
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (3)Object:IS-empty: staticOff: 0
	-- Invocation:gen: (3)Object
	-- Invocation:loadOrigin: (3)Object
	-- Invocation:loadOrigin:scan: (3)Object
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)Object
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: Object
	-- ObjectGenerator:gen: super: (3)none:IS-empty: staticOff: 0
	-- Invocation:gen: (3)none
	-- Invocation:loadOrigin: (3)none
	-- Invocation:loadOrigin:scan: (3)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- ObjectGenerator:gen: super: (3)none:IS-empty: staticOff: 0
	-- Invocation:gen: (3)none
	-- Invocation:loadOrigin: (3)none
	-- Invocation:loadOrigin:scan: (3)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (3)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	topSuper  436
	rtnInner
	DO:
	mvStack 
 L301:
 L302:
	rtnInner
	end 1

	class loop 116
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L303:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)disable:IS-empty: staticOff: 0
	-- Invocation:gen: (5)disable
	-- Invocation:loadOrigin: (5)disable
	-- Invocation:loadOrigin:scan: (5)disable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (5)disable
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: disable
	%disable 11
	-- ObjectGenerator:gen: super: (1)res (0):= 17:IS-empty: staticOff: 0
	-- Invocation:gen: (1)res (0):= 17
	-- Invocation:loadOrigin: (1)res (0):= 17
	-- Invocation:loadOrigin:scan: (1)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)res
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 17
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 res
	-- ObjectGenerator:gen: super: (1)res (0):= (2)M.(0)cmpAndSwap(1):IS-empty: staticOff: 0
	-- Invocation:gen: (1)res (0):= (2)M.(0)cmpAndSwap(1)
	-- Invocation:loadOrigin: (1)res (0):= (2)M.(0)cmpAndSwap(1)
	-- Invocation:loadOrigin:scan: (1)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)res
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)M.(0)cmpAndSwap(1)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)M.(0)cmpAndSwap(1):IS-empty: staticOff: 0
	-- Invocation:gen: (2)M.(0)cmpAndSwap(1)
	-- Invocation:loadOrigin: (2)M.(0)cmpAndSwap(1)
	-- Invocation:loadOrigin:scan: (2)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)cmpAndSwap(1) :E: (2)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushc 2
	-- Invocation:loadOrigin:scan: (0)cmpAndSwap(1)
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
	-- pattern:load: cmpAndSwap((1)V: ? (2)integer) -> (2)res: ? (2)integer
	swap
	%cmpAndSwap 14
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 res
	-- ObjectGenerator:gen: super: (0)%if (1)res (0)= 1 (0)%then% 
    (6)enable
    (6)sleep(50)
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)res (0)= 1 (0)%then% 
    (6)enable
    (6)sleep(50)
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (1)res (0)= 1 (0)%then% 
    (6)enable
    (6)sleep(50)
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (1)res (0)= 1 (0)%then% 
    (6)enable
    (6)sleep(50)
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)res (0)= 1 (0)%then% 
    (6)enable
    (6)sleep(50)
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)res (0)= 1 (0)%then% 
    (6)enable
    (6)sleep(50)
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)res (0)= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)res (0)= 1
	-- Invocation:loadOrigin: (1)res (0)= 1
	-- Invocation:loadOrigin:scan: (1)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)res
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= 1 :E: (1)res
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: res
	pushg 1 res
	-- Invocation:loadOrigin:scan: (0)= 1
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
	-- pattern:load: = (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	eq
	jmpFalse L305
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 547 0 #S#547
	rpop
 L305:
 L304:
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
 L306:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)inScheduler (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)inScheduler (0):= 1
	-- Invocation:loadOrigin: (2)inScheduler (0):= 1
	-- Invocation:loadOrigin:scan: (2)inScheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)inScheduler
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 inScheduler
	-- ObjectGenerator:gen: super: (2)active (0):= (3)SQS.(0)removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: (2)active (0):= (3)SQS.(0)removeNext
	-- Invocation:loadOrigin: (2)active (0):= (3)SQS.(0)removeNext
	-- Invocation:loadOrigin:scan: (2)active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)active
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)SQS.(0)removeNext
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)SQS.(0)removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: (3)SQS.(0)removeNext
	-- Invocation:loadOrigin: (3)SQS.(0)removeNext
	-- Invocation:loadOrigin:scan: (3)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)SQS
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)removeNext :E: (3)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)removeNext
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: removeNext -> (2)P: ? (2)BasicProcess
	invoke 146 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 active
	-- ObjectGenerator:gen: super: (0)%if (2)active (0)<> (5)none (0)%then% 
    (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
    (3)inScheduler (0):= 0
    (3)active.(0)attach(50)
    (3)inScheduler (0):= 1
    (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active):IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)active (0)<> (5)none (0)%then% 
    (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
    (3)inScheduler (0):= 0
    (3)active.(0)attach(50)
    (3)inScheduler (0):= 1
    (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- Invocation:loadOrigin: (0)%if (2)active (0)<> (5)none (0)%then% 
    (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
    (3)inScheduler (0):= 0
    (3)active.(0)attach(50)
    (3)inScheduler (0):= 1
    (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- Invocation:loadOrigin:scan: (0)%if (2)active (0)<> (5)none (0)%then% 
    (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
    (3)inScheduler (0):= 0
    (3)active.(0)attach(50)
    (3)inScheduler (0):= 1
    (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)active (0)<> (5)none (0)%then% 
    (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
    (3)inScheduler (0):= 0
    (3)active.(0)attach(50)
    (3)inScheduler (0):= 1
    (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)active (0)<> (5)none (0)%then% 
    (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
    (3)inScheduler (0):= 0
    (3)active.(0)attach(50)
    (3)inScheduler (0):= 1
    (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)active (0)<> (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (2)active (0)<> (5)none
	-- Invocation:loadOrigin: (2)active (0)<> (5)none
	-- Invocation:loadOrigin:scan: (2)active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)active
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)<> (5)none :E: (2)active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: (0)<> (5)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (5)none
	-- Invocation:loadOrigin: (5)none
	-- Invocation:loadOrigin:scan: (5)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (5)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	jmpFalse L308
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 548 0 #S#548
	rpop
 L308:
	-- ObjectGenerator:gen: super: (0)%if (3)SQS.(0)isEmpty (0)%then% 
    (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
    (5)sch.(0)dcr
    (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop (0)%else% 
    (0)%restart (3)Loop:IS-empty: staticOff: 0
	pushThis 
	invoke 123 0 %if%then%%else%#S#123
	rpop
 L307:
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
 L309:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (2)main (0)<> (5)none (0)%then% 
    (4)main.(0)resume (0)%else% 
    (7)sleep(100)
    (0)%restart (3)loopX:IS-empty: staticOff: 0
	pushThis 
	invoke 128 0 %if%then%%else%#S#128
	rpop
 L310:
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
 L311:
	-- Include:gen: 
 L312:
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
 L313:
	-- Include:gen: 
 L314:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#530 530
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L315:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)E (0):= (2)Element((1)elm):IS-empty: staticOff: 0
	-- Invocation:gen: (1)E (0):= (2)Element((1)elm)
	-- Invocation:loadOrigin: (1)E (0):= (2)Element((1)elm)
	-- Invocation:loadOrigin:scan: (1)E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)E
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)Element((1)elm)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Element((1)elm):IS-empty: staticOff: 0
	-- Invocation:gen: (2)Element((1)elm)
	-- Invocation:loadOrigin: (2)Element((1)elm)
	-- Invocation:loadOrigin:scan: (2)Element((1)elm)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (2)Element((1)elm)
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (1)elm:IS-empty: staticOff: 0
	-- Invocation:gen: (1)elm
	-- Invocation:loadOrigin: (1)elm
	-- Invocation:loadOrigin:scan: (1)elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)elm
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Function:invoke: 
	-- pattern:load: Element((2)elm: ? (4)Object) -> (3)res: ? (1)Element
	invoke 76 0 Element
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 E
	-- ObjectGenerator:gen: super: (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E:IS-empty: staticOff: 0
	pushThis 
	invoke 531 0 %if%then%%else%#S#531
	rpop
 L316:
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
	-- Invocation:loadOrigin: (1)scan
	-- Invocation:loadOrigin:scan: (1)scan
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)scan
	-- AdjustOrigin: 4
	rpushg 4 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  77
	rtnInner
	DO:
	doEventQ
	mvStack 
 L317:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (1)elm (0)= (0)current (0)%then% 
    (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)elm (0)= (0)current (0)%then% 
    (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- Invocation:loadOrigin: (0)%if (1)elm (0)= (0)current (0)%then% 
    (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- Invocation:loadOrigin:scan: (0)%if (1)elm (0)= (0)current (0)%then% 
    (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)elm (0)= (0)current (0)%then% 
    (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)elm (0)= (0)current (0)%then% 
    (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)elm (0)= (0)current:IS-empty: staticOff: 0
	-- Invocation:gen: (1)elm (0)= (0)current
	-- Invocation:loadOrigin: (1)elm (0)= (0)current
	-- Invocation:loadOrigin:scan: (1)elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)elm
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- next not assign: (0)= (0)current :E: (1)elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Invocation:loadOrigin:scan: (0)= (0)current
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)current:IS-empty: staticOff: 0
	-- Invocation:gen: (0)current
	-- Invocation:loadOrigin: (0)current
	-- Invocation:loadOrigin:scan: (0)current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)current
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	rpushg 2 current
	-- Binary:invoke: 
	-- pattern:load: = (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	req
	jmpFalse L319
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 532 0 #S#532
	rpop
 L319:
 L318:
	rtnInner
	end 1

	class #S#534 534
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L320:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)elm (0):= (2)last.(0)elm:IS-empty: staticOff: 0
	-- Invocation:gen: (1)elm (0):= (2)last.(0)elm
	-- Invocation:loadOrigin: (1)elm (0):= (2)last.(0)elm
	-- Invocation:loadOrigin:scan: (1)elm
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)elm
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)last.(0)elm
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)last.(0)elm:IS-empty: staticOff: 0
	-- Invocation:gen: (2)last.(0)elm
	-- Invocation:loadOrigin: (2)last.(0)elm
	-- Invocation:loadOrigin:scan: (2)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)elm :E: (2)last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: (0)elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 elm
	-- ObjectGenerator:gen: super: (2)last (0):= (2)last.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (2)last (0):= (2)last.(0)pred
	-- Invocation:loadOrigin: (2)last (0):= (2)last.(0)pred
	-- Invocation:loadOrigin:scan: (2)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)last.(0)pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)last.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (2)last.(0)pred
	-- Invocation:loadOrigin: (2)last.(0)pred
	-- Invocation:loadOrigin:scan: (2)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)last
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)pred :E: (2)last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: (0)pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 last
	-- ObjectGenerator:gen: super: (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none:IS-empty: staticOff: 0
	pushThis 
	invoke 535 0 %if%then%%else%#S#535
	rpop
 L321:
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
	-- Invocation:loadOrigin: (1)entry
	-- Invocation:loadOrigin:scan: (1)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  135
	rtnInner
	DO:
	doEventQ
	mvStack 
 L322:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)M (0):= (2)M (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)M (0):= (2)M (0)+ 1
	-- Invocation:loadOrigin: (2)M (0):= (2)M (0)+ 1
	-- Invocation:loadOrigin:scan: (2)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)M (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)M (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)M (0)+ 1
	-- Invocation:loadOrigin: (2)M (0)+ 1
	-- Invocation:loadOrigin:scan: (2)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (2)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 M
 L323:
	rtnInner
	end 1

	class entry#S#139 139
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=139
	-- Invocation:loadOrigin: (1)entry
	-- Invocation:loadOrigin:scan: (1)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  135
	rtnInner
	DO:
	doEventQ
	mvStack 
 L324:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)M (0):= (2)M (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)M (0):= (2)M (0)- 1
	-- Invocation:loadOrigin: (2)M (0):= (2)M (0)- 1
	-- Invocation:loadOrigin:scan: (2)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (2)M (0)- 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)M (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)M (0)- 1
	-- Invocation:loadOrigin: (2)M (0)- 1
	-- Invocation:loadOrigin:scan: (2)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)- 1 :E: (2)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: (0)- 1
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
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 M
 L325:
	rtnInner
	end 1

	class entry#S#141 141
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=141
	-- Invocation:loadOrigin: (1)entry
	-- Invocation:loadOrigin:scan: (1)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  135
	rtnInner
	DO:
	doEventQ
	mvStack 
 L326:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)B (0):= (2)M (0)> 0:IS-empty: staticOff: 0
	-- Invocation:gen: (1)B (0):= (2)M (0)> 0
	-- Invocation:loadOrigin: (1)B (0):= (2)M (0)> 0
	-- Invocation:loadOrigin:scan: (1)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (2)M (0)> 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)M (0)> 0:IS-empty: staticOff: 0
	-- Invocation:gen: (2)M (0)> 0
	-- Invocation:loadOrigin: (2)M (0)> 0
	-- Invocation:loadOrigin:scan: (2)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)M
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)> 0 :E: (2)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: M
	pushg 1 M
	-- Invocation:loadOrigin:scan: (0)> 0
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
	-- pattern:load: > (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 B
 L327:
	rtnInner
	end 1

	class #S#553 553
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L328:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)put('V'):IS-empty: staticOff: 0
	-- Invocation:gen: (5)put('V')
	-- Invocation:loadOrigin: (5)put('V')
	-- Invocation:loadOrigin:scan: (5)put('V')
	-- Function:pushThis: 
	-- Function:loadOrigin: (5)put('V')
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
	-- pattern:load: put((1)ch: ? (1)char)
	%put 2
 L329:
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
	-- Invocation:loadOrigin: (1)entry
	-- Invocation:loadOrigin:scan: (1)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L330:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)P (0):= (2)Q.(0)removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: (1)P (0):= (2)Q.(0)removeNext
	-- Invocation:loadOrigin: (1)P (0):= (2)Q.(0)removeNext
	-- Invocation:loadOrigin:scan: (1)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)P
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (2)Q.(0)removeNext
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Q.(0)removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Q.(0)removeNext
	-- Invocation:loadOrigin: (2)Q.(0)removeNext
	-- Invocation:loadOrigin:scan: (2)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)removeNext :E: (2)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)removeNext
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: removeNext -> (2)elm: ? (4)Object
	invoke 86 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 P
 L331:
	rtnInner
	end 1

	class entry#S#150 150
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=150
	-- Invocation:loadOrigin: (1)entry
	-- Invocation:loadOrigin:scan: (1)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L332:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)B (0):= (2)Q.(0)isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: (1)B (0):= (2)Q.(0)isEmpty
	-- Invocation:loadOrigin: (1)B (0):= (2)Q.(0)isEmpty
	-- Invocation:loadOrigin:scan: (1)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (2)Q.(0)isEmpty
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)Q.(0)isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Q.(0)isEmpty
	-- Invocation:loadOrigin: (2)Q.(0)isEmpty
	-- Invocation:loadOrigin:scan: (2)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)isEmpty :E: (2)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)isEmpty
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: isEmpty -> (1)B: ? (4)Boolean
	invoke 87 0 isEmpty
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 B
 L333:
	rtnInner
	end 1

	class entry#S#155 155
	rstore 2 origin
	allocEventQ
	-- super entry
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=155
	-- Invocation:loadOrigin: (1)entry
	-- Invocation:loadOrigin:scan: (1)entry
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)entry
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	topSuper  143
	rtnInner
	DO:
	doEventQ
	mvStack 
 L334:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)B (0):= (2)W (0)> 0:IS-empty: staticOff: 0
	-- Invocation:gen: (1)B (0):= (2)W (0)> 0
	-- Invocation:loadOrigin: (1)B (0):= (2)W (0)> 0
	-- Invocation:loadOrigin:scan: (1)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)B
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (2)W (0)> 0
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)W (0)> 0:IS-empty: staticOff: 0
	-- Invocation:gen: (2)W (0)> 0
	-- Invocation:loadOrigin: (2)W (0)> 0
	-- Invocation:loadOrigin:scan: (2)W
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)W
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)> 0 :E: (2)W
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: W
	pushg 2 W
	-- Invocation:loadOrigin:scan: (0)> 0
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
	-- pattern:load: > (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	gt
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 B
 L335:
	rtnInner
	end 1

	class thenPart#SB#554 554
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L336:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)pos (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0):= 1
	-- Invocation:loadOrigin: (3)pos (0):= 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 pos
 L337:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#555 555
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L338:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)pos (0):= (3)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0):= (3)pos (0)+ 1
	-- Invocation:loadOrigin: (3)pos (0):= (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)pos (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0)+ 1
	-- Invocation:loadOrigin: (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (3)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 pos
 L339:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#556 556
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L340:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)pos (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0):= 1
	-- Invocation:loadOrigin: (3)pos (0):= 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 pos
 L341:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#557 557
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L342:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)pos (0):= (3)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0):= (3)pos (0)+ 1
	-- Invocation:loadOrigin: (3)pos (0):= (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)pos (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0)+ 1
	-- Invocation:loadOrigin: (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (3)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 pos
 L343:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#558 558
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L344:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)res (0):= 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: (2)res (0):= 9999999
	-- Invocation:loadOrigin: (2)res (0):= 9999999
	-- Invocation:loadOrigin:scan: (2)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= 9999999
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 res
 L345:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#559 559
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L346:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1
	-- Invocation:loadOrigin: (2)res (0):= (3)rep.(0)%get (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (2)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= (3)rep.(0)%get (3)pos (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)rep.(0)%get (3)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)rep.(0)%get (3)pos (0)+ 1
	-- Invocation:loadOrigin: (3)rep.(0)%get (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (3)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)%get (3)pos (0)+ 1 :E: (3)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%get (3)pos (0)+ 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get (3)pos (0)+ 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (3)pos (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0)+ 1
	-- Invocation:loadOrigin: (3)pos (0)+ 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (3)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 res
 L347:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#560 560
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L348:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)res (0):= 9999999:IS-empty: staticOff: 0
	-- Invocation:gen: (2)res (0):= 9999999
	-- Invocation:loadOrigin: (2)res (0):= 9999999
	-- Invocation:loadOrigin:scan: (2)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= 9999999
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 res
 L349:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#561 561
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L350:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1
	-- Invocation:loadOrigin: (2)res (0):= (3)rep.(0)%get (3)pos (0)- 1
	-- Invocation:loadOrigin:scan: (2)res
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)res
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= (3)rep.(0)%get (3)pos (0)- 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)rep.(0)%get (3)pos (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)rep.(0)%get (3)pos (0)- 1
	-- Invocation:loadOrigin: (3)rep.(0)%get (3)pos (0)- 1
	-- Invocation:loadOrigin:scan: (3)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)%get (3)pos (0)- 1 :E: (3)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%get (3)pos (0)- 1
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get (3)pos (0)- 1
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (3)pos (0)- 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)pos (0)- 1
	-- Invocation:loadOrigin: (3)pos (0)- 1
	-- Invocation:loadOrigin:scan: (3)pos
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)pos
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)- 1 :E: (3)pos
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pos
	pushg 1 pos
	-- Invocation:loadOrigin:scan: (0)- 1
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
	-- pattern:load: - (1)V: ? (2)integer -> (2)R: ? (2)integer
	minus
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 res
 L351:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#562 562
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L352:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 257
 L353:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#563 563
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L354:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)putint((3)rep.(0)%get (1)inx):IS-empty: staticOff: 0
	-- Invocation:gen: (5)putint((3)rep.(0)%get (1)inx)
	-- Invocation:loadOrigin: (5)putint((3)rep.(0)%get (1)inx)
	-- Invocation:loadOrigin:scan: (5)putint((3)rep.(0)%get (1)inx)
	-- Function:pushThis: 
	pushThis 
	-- Function:loadOrigin: (5)putint((3)rep.(0)%get (1)inx)
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (3)rep.(0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (3)rep.(0)%get (1)inx
	-- Invocation:loadOrigin: (3)rep.(0)%get (1)inx
	-- Invocation:loadOrigin:scan: (3)rep
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)rep
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)%get (1)inx :E: (3)rep
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: rep
	rpushg 2 rep
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (2)integer -> (2)V: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: putint((1)V: ? (1)integer)
	invoke 67 0 putint
	rpop
	-- ObjectGenerator:gen: super: ", ".(0)print:IS-empty: staticOff: 0
	-- Invocation:gen: ", ".(0)print
	-- Invocation:loadOrigin: ", ".(0)print
	-- Invocation:loadOrigin:scan: ", "
	-- String::pushThis: 
	-- String::loadOrigin: 
	pushText , 
	-- next not assign: (0)print :E: ", "
	-- String::loadArgs: 
	-- String::invoke: 
	-- Invocation:loadOrigin:scan: (0)print
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: print
	invoke 100 0 print
	rpop
 L355:
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
 L356:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: (5)sleep(100)
	-- Invocation:loadOrigin: (5)sleep(100)
	-- Invocation:loadOrigin:scan: (5)sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: (5)sleep(100)
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
	-- pattern:load: sleep((1)V: ? (1)integer)
	%sleep 15
	-- ObjectGenerator:gen: super: (0)continue (0):= (5)false:IS-empty: staticOff: 0
	-- Invocation:gen: (0)continue (0):= (5)false
	-- Invocation:loadOrigin: (0)continue (0):= (5)false
	-- Invocation:loadOrigin:scan: (0)continue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)continue
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= (5)false
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)false:IS-empty: staticOff: 0
	-- Invocation:gen: (5)false
	-- Invocation:loadOrigin: (5)false
	-- Invocation:loadOrigin:scan: (5)false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)false
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: False -> (1)B: ? (1)Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 continue
	-- ObjectGenerator:gen: super: (2)Q.(0)scan:singular:staticOff: 0
	pushThis 
	invoke 196 0 scan#S#196
	rpop
	-- ObjectGenerator:gen: super: (0)%if (0)continue (0)%then% 
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (0)continue (0)%then% 
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (0)continue (0)%then% 
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (0)continue (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (0)continue (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (0)continue (0)%then% 
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (0)continue:IS-empty: staticOff: 0
	-- Invocation:gen: (0)continue
	-- Invocation:loadOrigin: (0)continue
	-- Invocation:loadOrigin:scan: (0)continue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)continue
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: continue
	pushg 1 continue
	jmpFalse L358
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 568 0 #S#568
	rpop
 L358:
	-- ObjectGenerator:gen: super: (2)Q.(0)clear:IS-empty: staticOff: 0
	-- Invocation:gen: (2)Q.(0)clear
	-- Invocation:loadOrigin: (2)Q.(0)clear
	-- Invocation:loadOrigin:scan: (2)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Q
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)clear :E: (2)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)clear
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: clear
	invoke 88 0 clear
	rpop
 L357:
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
	-- Invocation:loadOrigin: (0)%if (1)cnt (0)< 0 (0)%then% 
    (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING
    (4)SQS.(0)addWaiting
    (3)Q.(0)insert((6)thisCore.(0)main.(0)active)
    (2)theActive (0):= (6)thisCore.(0)main.(0)active
    (3)M.(0)free
    (2)theActive.(0)suspend (0)%else% 
    (3)M.(0)free
	-- Invocation:loadOrigin:scan: (0)%if (1)cnt (0)< 0 (0)%then% 
    (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING
    (4)SQS.(0)addWaiting
    (3)Q.(0)insert((6)thisCore.(0)main.(0)active)
    (2)theActive (0):= (6)thisCore.(0)main.(0)active
    (3)M.(0)free
    (2)theActive.(0)suspend (0)%else% 
    (3)M.(0)free
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)cnt (0)< 0 (0)%then% 
    (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING
    (4)SQS.(0)addWaiting
    (3)Q.(0)insert((6)thisCore.(0)main.(0)active)
    (2)theActive (0):= (6)thisCore.(0)main.(0)active
    (3)M.(0)free
    (2)theActive.(0)suspend (0)%else% 
    (3)M.(0)free
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 8 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)cnt (0)< 0 (0)%then% 
    (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING
    (4)SQS.(0)addWaiting
    (3)Q.(0)insert((6)thisCore.(0)main.(0)active)
    (2)theActive (0):= (6)thisCore.(0)main.(0)active
    (3)M.(0)free
    (2)theActive.(0)suspend (0)%else% 
    (3)M.(0)free
	-- ObjectGenerator:gen: super: (1)cnt (0)< 0:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cnt (0)< 0
	-- Invocation:loadOrigin: (1)cnt (0)< 0
	-- Invocation:loadOrigin:scan: (1)cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cnt
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)< 0 :E: (1)cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: (0)< 0
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
	-- pattern:load: < (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	51
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L359:
 L360:
	rtnInner
	end 1

	class %if%then%%else%#S#204 204
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (1)cnt (0)<= 0 (0)%then% 
    (2)P (0):= (3)Q.(0)removeNext
    (2)P.(0)status (0):= (4)P_status.(0)ACTIVE
    (4)SQS.(0)insert((2)P)
    (4)SQS.(0)dcrWaiting
    (3)M.(0)free (0)%else% 
    (3)M.(0)free
	-- Invocation:loadOrigin:scan: (0)%if (1)cnt (0)<= 0 (0)%then% 
    (2)P (0):= (3)Q.(0)removeNext
    (2)P.(0)status (0):= (4)P_status.(0)ACTIVE
    (4)SQS.(0)insert((2)P)
    (4)SQS.(0)dcrWaiting
    (3)M.(0)free (0)%else% 
    (3)M.(0)free
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)cnt (0)<= 0 (0)%then% 
    (2)P (0):= (3)Q.(0)removeNext
    (2)P.(0)status (0):= (4)P_status.(0)ACTIVE
    (4)SQS.(0)insert((2)P)
    (4)SQS.(0)dcrWaiting
    (3)M.(0)free (0)%else% 
    (3)M.(0)free
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 8 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)cnt (0)<= 0 (0)%then% 
    (2)P (0):= (3)Q.(0)removeNext
    (2)P.(0)status (0):= (4)P_status.(0)ACTIVE
    (4)SQS.(0)insert((2)P)
    (4)SQS.(0)dcrWaiting
    (3)M.(0)free (0)%else% 
    (3)M.(0)free
	-- ObjectGenerator:gen: super: (1)cnt (0)<= 0:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cnt (0)<= 0
	-- Invocation:loadOrigin: (1)cnt (0)<= 0
	-- Invocation:loadOrigin:scan: (1)cnt
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cnt
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)<= 0 :E: (1)cnt
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cnt
	pushg 1 cnt
	-- Invocation:loadOrigin:scan: (0)<= 0
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
	-- pattern:load: <= (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	52
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L361:
 L362:
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
 L363:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%inner (2)wait:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (2)wait
	-- Invocation:loadOrigin: (0)%inner (2)wait
	-- Invocation:loadOrigin:scan: (0)%inner (2)wait
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (2)wait
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (2)wait
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: (0)%if (1)cond (0)= (5)false (0)%then% 
    (3)mutex.(0)signal
    (3)mutex.(0)wait
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)cond (0)= (5)false (0)%then% 
    (3)mutex.(0)signal
    (3)mutex.(0)wait
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (1)cond (0)= (5)false (0)%then% 
    (3)mutex.(0)signal
    (3)mutex.(0)wait
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (1)cond (0)= (5)false (0)%then% 
    (3)mutex.(0)signal
    (3)mutex.(0)wait
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)cond (0)= (5)false (0)%then% 
    (3)mutex.(0)signal
    (3)mutex.(0)wait
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)cond (0)= (5)false (0)%then% 
    (3)mutex.(0)signal
    (3)mutex.(0)wait
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)cond (0)= (5)false:IS-empty: staticOff: 0
	-- Invocation:gen: (1)cond (0)= (5)false
	-- Invocation:loadOrigin: (1)cond (0)= (5)false
	-- Invocation:loadOrigin:scan: (1)cond
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)cond
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (5)false :E: (1)cond
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: cond
	pushg 1 cond
	-- Invocation:loadOrigin:scan: (0)= (5)false
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)false:IS-empty: staticOff: 0
	-- Invocation:gen: (5)false
	-- Invocation:loadOrigin: (5)false
	-- Invocation:loadOrigin:scan: (5)false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)false
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 8 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: False -> (1)B: ? (1)Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: = (1)B: ? (2)Boolean -> (2)R: ? (2)Boolean
	eq
	jmpFalse L365
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 573 0 #S#573
	rpop
 L365:
 L364:
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
	-- Invocation:loadOrigin: (0)%for 1 (0)%to% (1)L (0)%do% 
    (2)e (0):= (0)%get (1)inx
    (2)T.(0)%put (2)e (0)%at% (1)inx
	-- Invocation:loadOrigin:scan: (0)%for 1 (0)%to% (1)L (0)%do% 
    (2)e (0):= (0)%get (1)inx
    (2)T.(0)%put (2)e (0)%at% (1)inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%for 1 (0)%to% (1)L (0)%do% 
    (2)e (0):= (0)%get (1)inx
    (2)T.(0)%put (2)e (0)%at% (1)inx
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object(0)%for 1 (0)%to% (1)L (0)%do% 
    (2)e (0):= (0)%get (1)inx
    (2)T.(0)%put (2)e (0)%at% (1)inx
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: (1)L:IS-empty: staticOff: 0
	-- Invocation:gen: (1)L
	-- Invocation:loadOrigin: (1)L
	-- Invocation:loadOrigin:scan: (1)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)L
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
 L366:
 L367:
	rtnInner
	end 1

	class %for%to%%do%#S#96 96
	rstore 2 origin
	allocEventQ
	-- super %for%to%%do%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%for 1 (0)%to% (1)S.(0)length (0)%do% 
    (2)e (0):= (3)S.(0)%get (1)inx
    (2)i (0):= (3)L (0)+ (1)inx
    (2)T.(0)%put (2)e (0)%at% (2)i
	-- Invocation:loadOrigin:scan: (0)%for 1 (0)%to% (1)S.(0)length (0)%do% 
    (2)e (0):= (3)S.(0)%get (1)inx
    (2)i (0):= (3)L (0)+ (1)inx
    (2)T.(0)%put (2)e (0)%at% (2)i
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%for 1 (0)%to% (1)S.(0)length (0)%do% 
    (2)e (0):= (3)S.(0)%get (1)inx
    (2)i (0):= (3)L (0)+ (1)inx
    (2)T.(0)%put (2)e (0)%at% (2)i
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object(0)%for 1 (0)%to% (1)S.(0)length (0)%do% 
    (2)e (0):= (3)S.(0)%get (1)inx
    (2)i (0):= (3)L (0)+ (1)inx
    (2)T.(0)%put (2)e (0)%at% (2)i
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: (1)S.(0)length:IS-empty: staticOff: 0
	-- Invocation:gen: (1)S.(0)length
	-- Invocation:loadOrigin: (1)S.(0)length
	-- Invocation:loadOrigin:scan: (1)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)S
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)length :E: (1)S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: (0)length
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L368:
 L369:
	rtnInner
	end 1

	class body#SB#538 538
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L370:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)current (0):= (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (2)current (0):= (0)%get (1)inx
	-- Invocation:loadOrigin: (2)current (0):= (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (2)current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)current
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (0)%get (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%get (1)inx
	-- Invocation:loadOrigin: (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%get (1)inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 current
	-- ObjectGenerator:gen: super: (0)%inner (3)scan:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (3)scan
	-- Invocation:loadOrigin: (0)%inner (3)scan
	-- Invocation:loadOrigin:scan: (0)%inner (3)scan
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (3)scan
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (3)scan
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	rpushg 2 origin
	rpushg 2 origin
	inner  1
	rpopThisObj 
 L371:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#539 539
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L372:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)put((0)%get (1)inx):IS-empty: staticOff: 0
	-- Invocation:gen: (5)put((0)%get (1)inx)
	-- Invocation:loadOrigin: (5)put((0)%get (1)inx)
	-- Invocation:loadOrigin:scan: (5)put((0)%get (1)inx)
	-- Function:pushThis: 
	-- Function:loadOrigin: (5)put((0)%get (1)inx)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%get (1)inx
	-- Invocation:loadOrigin: (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%get (1)inx
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Function:invoke: 
	-- pattern:load: put((1)ch: ? (1)char)
	%put 2
 L373:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#540 540
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L374:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%leave (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%leave (2)loop
	-- Invocation:loadOrigin: (0)%leave (2)loop
	-- Invocation:loadOrigin:scan: (0)%leave (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%leave (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%leave (1)Obj: ? (1)integer(0)%leave (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%leave (1)Obj: ? (1)integer
	break 1 289
 L375:
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
	-- Invocation:loadOrigin: (0)%for 1 (0)%to% (2)length (0)%do% 
    (2)c1 (0):= (0)%get (1)inx
    (2)c2 (0):= (3)S.(0)%get (1)inx
    (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- Invocation:loadOrigin:scan: (0)%for 1 (0)%to% (2)length (0)%do% 
    (2)c1 (0):= (0)%get (1)inx
    (2)c2 (0):= (3)S.(0)%get (1)inx
    (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%for 1 (0)%to% (2)length (0)%do% 
    (2)c1 (0):= (0)%get (1)inx
    (2)c2 (0):= (3)S.(0)%get (1)inx
    (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%for (1)first: ? (1)integer (0)%to% (2)last: ? (1)integer (0)%do% (1)body:< (1)Object(0)%for 1 (0)%to% (2)length (0)%do% 
    (2)c1 (0):= (0)%get (1)inx
    (2)c2 (0):= (3)S.(0)%get (1)inx
    (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- ObjectGenerator:gen: super: 1:IS-empty: staticOff: 0
	-- Invocation:gen: 1
	-- Invocation:loadOrigin: 1
	-- Invocation:loadOrigin:scan: 1
	-- Const::pushThis: 
	-- Const::loadOrigin: 
	-- Const::loadArgs: 
	-- Const::invoke: 
	pushc 1
	-- ObjectGenerator:gen: super: (2)length:IS-empty: staticOff: 0
	-- Invocation:gen: (2)length
	-- Invocation:loadOrigin: (2)length
	-- Invocation:loadOrigin:scan: (2)length
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)length
	-- AdjustOrigin: 2
	rpushg 2 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: length -> (1)V: ? (3)integer
	invoke 91 0 length
	topSuper  63
	rtnInner
	DO:
	mvStack 
 L376:
 L377:
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
 L378:
	-- Include:gen: 
 L379:
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
	-- Invocation:loadOrigin: (0)%if (0)L1 (0)< (0)L2 (0)%then% 
    (2)L (0):= (2)L1 (0)%else% 
    (2)L (0):= (2)L2
	-- Invocation:loadOrigin:scan: (0)%if (0)L1 (0)< (0)L2 (0)%then% 
    (2)L (0):= (2)L1 (0)%else% 
    (2)L (0):= (2)L2
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (0)L1 (0)< (0)L2 (0)%then% 
    (2)L (0):= (2)L1 (0)%else% 
    (2)L (0):= (2)L2
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (0)L1 (0)< (0)L2 (0)%then% 
    (2)L (0):= (2)L1 (0)%else% 
    (2)L (0):= (2)L2
	-- ObjectGenerator:gen: super: (0)L1 (0)< (0)L2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L1 (0)< (0)L2
	-- Invocation:loadOrigin: (0)L1 (0)< (0)L2
	-- Invocation:loadOrigin:scan: (0)L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 0
	-- next not assign: (0)< (0)L2 :E: (0)L1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Invocation:loadOrigin:scan: (0)< (0)L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)L2:IS-empty: staticOff: 0
	-- Invocation:gen: (0)L2
	-- Invocation:loadOrigin: (0)L2
	-- Invocation:loadOrigin:scan: (0)L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)L2
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: < (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	51
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L380:
 L381:
	rtnInner
	end 1

	class empty 437
	rstore 1 origin
	allocEventQ
	mvStack 
	innerA  1
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L382:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)b (0):= ((1)head (0)= (5)none):IS-empty: staticOff: 0
	-- Invocation:gen: (0)b (0):= ((1)head (0)= (5)none)
	-- Invocation:loadOrigin: (0)b (0):= ((1)head (0)= (5)none)
	-- Invocation:loadOrigin:scan: (0)b
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)b
	-- AdjustOrigin: 0
	-- on : 0
	-- Invocation:loadOrigin:scan: (0):= ((1)head (0)= (5)none)
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: ((1)head (0)= (5)none):IS-empty: staticOff: 0
	-- Invocation:gen: ((1)head (0)= (5)none)
	-- Invocation:loadOrigin: ((1)head (0)= (5)none)
	-- Invocation:loadOrigin:scan: ((1)head (0)= (5)none)
	-- BracketedExp:pushThis: 
	-- BracketedExp:loadOrigin: ((1)head (0)= (5)none)
	-- Invocation:loadOrigin: (1)head (0)= (5)none
	-- Invocation:loadOrigin:scan: (1)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)head
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (5)none :E: (1)head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: (0)= (5)none
	-- BE:loadOrigin:E: (0)= (5)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (5)none
	-- Invocation:loadOrigin: (5)none
	-- Invocation:loadOrigin:scan: (5)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (5)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	req
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 b
	-- ObjectGenerator:gen: super: (0)%inner (1)empty:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (1)empty
	-- Invocation:loadOrigin: (0)%inner (1)empty
	-- Invocation:loadOrigin:scan: (0)%inner (1)empty
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (1)empty
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (1)empty
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	inner  1
	rpopThisObj 
 L383:
	rtnEventQ 0
	setThisStack 
	pushThis 
	-- VarRef:load: b
	pushg 1 b
	rtn(D)
	end 1

	class #S#547 547
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L384:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (6)enable:IS-empty: staticOff: 0
	-- Invocation:gen: (6)enable
	-- Invocation:loadOrigin: (6)enable
	-- Invocation:loadOrigin:scan: (6)enable
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (6)enable
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: enable
	%enable 12
	-- ObjectGenerator:gen: super: (6)sleep(50):IS-empty: staticOff: 0
	-- Invocation:gen: (6)sleep(50)
	-- Invocation:loadOrigin: (6)sleep(50)
	-- Invocation:loadOrigin:scan: (6)sleep(50)
	-- Function:pushThis: 
	-- Function:loadOrigin: (6)sleep(50)
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
	-- pattern:load: sleep((1)V: ? (1)integer)
	%sleep 15
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 303
 L385:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#548 548
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L386:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)active.(0)status (0):= (4)P_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin: (3)active.(0)status (0):= (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (3)active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)active
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)status :E: (3)active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: (0)status
	-- Invocation:loadOrigin:scan: (0):= (4)P_status.(0)ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)P_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin: (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (4)P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)ACTIVE :E: (4)P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: (0)ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 status
	-- ObjectGenerator:gen: super: (3)inScheduler (0):= 0:IS-empty: staticOff: 0
	-- Invocation:gen: (3)inScheduler (0):= 0
	-- Invocation:loadOrigin: (3)inScheduler (0):= 0
	-- Invocation:loadOrigin:scan: (3)inScheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)inScheduler
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 0
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 inScheduler
	-- ObjectGenerator:gen: super: (3)active.(0)attach(50):IS-empty: staticOff: 0
	-- Invocation:gen: (3)active.(0)attach(50)
	-- Invocation:loadOrigin: (3)active.(0)attach(50)
	-- Invocation:loadOrigin:scan: (3)active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)active
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)attach(50) :E: (3)active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: (0)attach(50)
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
	-- pattern:load: attach((1)V: ? (2)integer)
	%attach 10 D
	rpop
	-- ObjectGenerator:gen: super: (3)inScheduler (0):= 1:IS-empty: staticOff: 0
	-- Invocation:gen: (3)inScheduler (0):= 1
	-- Invocation:loadOrigin: (3)inScheduler (0):= 1
	-- Invocation:loadOrigin:scan: (3)inScheduler
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)inScheduler
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= 1
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
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 inScheduler
	-- ObjectGenerator:gen: super: (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active):IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- Invocation:loadOrigin: (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- Invocation:loadOrigin:scan: (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (3)active.(0)status (0)= (4)P_status.(0)ACTIVE (0)%then% 
    (5)SQS.(0)insert((4)active)
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (3)active.(0)status (0)= (4)P_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (3)active.(0)status (0)= (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin: (3)active.(0)status (0)= (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (3)active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)active
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)status :E: (3)active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: (0)status
	-- next not assign: (0)= (4)P_status.(0)ACTIVE :E: (0)status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: status
	pushg 1 status
	-- Invocation:loadOrigin:scan: (0)= (4)P_status.(0)ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)P_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin: (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (4)P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)ACTIVE :E: (4)P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: (0)ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: = (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	eq
	jmpFalse L388
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 667 0 #S#667
	rpop
 L388:
 L387:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#123 123
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (3)SQS.(0)isEmpty (0)%then% 
    (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
    (5)sch.(0)dcr
    (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop (0)%else% 
    (0)%restart (3)Loop
	-- Invocation:loadOrigin:scan: (0)%if (3)SQS.(0)isEmpty (0)%then% 
    (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
    (5)sch.(0)dcr
    (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop (0)%else% 
    (0)%restart (3)Loop
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (3)SQS.(0)isEmpty (0)%then% 
    (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
    (5)sch.(0)dcr
    (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop (0)%else% 
    (0)%restart (3)Loop
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (3)SQS.(0)isEmpty (0)%then% 
    (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
    (5)sch.(0)dcr
    (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop (0)%else% 
    (0)%restart (3)Loop
	-- ObjectGenerator:gen: super: (3)SQS.(0)isEmpty:IS-empty: staticOff: 0
	-- Invocation:gen: (3)SQS.(0)isEmpty
	-- Invocation:loadOrigin: (3)SQS.(0)isEmpty
	-- Invocation:loadOrigin:scan: (3)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)SQS
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)isEmpty :E: (3)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)isEmpty
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: isEmpty -> (1)B: ? (4)Boolean
	invoke 149 0 isEmpty
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L389:
 L390:
	rtnInner
	end 1

	class %if%then%%else%#S#128 128
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (2)main (0)<> (5)none (0)%then% 
    (4)main.(0)resume (0)%else% 
    (7)sleep(100)
    (0)%restart (3)loopX
	-- Invocation:loadOrigin:scan: (0)%if (2)main (0)<> (5)none (0)%then% 
    (4)main.(0)resume (0)%else% 
    (7)sleep(100)
    (0)%restart (3)loopX
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (2)main (0)<> (5)none (0)%then% 
    (4)main.(0)resume (0)%else% 
    (7)sleep(100)
    (0)%restart (3)loopX
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (2)main (0)<> (5)none (0)%then% 
    (4)main.(0)resume (0)%else% 
    (7)sleep(100)
    (0)%restart (3)loopX
	-- ObjectGenerator:gen: super: (2)main (0)<> (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (2)main (0)<> (5)none
	-- Invocation:loadOrigin: (2)main (0)<> (5)none
	-- Invocation:loadOrigin:scan: (2)main
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)main
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)<> (5)none :E: (2)main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: (0)<> (5)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (5)none
	-- Invocation:loadOrigin: (5)none
	-- Invocation:loadOrigin:scan: (5)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (5)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L391:
 L392:
	rtnInner
	end 1

	class loop 79
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L393:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scan
    (3)currentElement (0):= (3)currentElement.(0)succ
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scan
    (3)currentElement (0):= (3)currentElement.(0)succ
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scan
    (3)currentElement (0):= (3)currentElement.(0)succ
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scan
    (3)currentElement (0):= (3)currentElement.(0)succ
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scan
    (3)currentElement (0):= (3)currentElement.(0)succ
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scan
    (3)currentElement (0):= (3)currentElement.(0)succ
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)currentElement (0)<> (6)none:IS-empty: staticOff: 0
	-- Invocation:gen: (2)currentElement (0)<> (6)none
	-- Invocation:loadOrigin: (2)currentElement (0)<> (6)none
	-- Invocation:loadOrigin:scan: (2)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)currentElement
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)<> (6)none :E: (2)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)<> (6)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (6)none:IS-empty: staticOff: 0
	-- Invocation:gen: (6)none
	-- Invocation:loadOrigin: (6)none
	-- Invocation:loadOrigin:scan: (6)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (6)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	jmpFalse L395
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 528 0 #S#528
	rpop
 L395:
 L394:
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
 L396:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scanFromLast
    (3)currentElement (0):= (3)currentElement.(0)pred
    (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scanFromLast
    (3)currentElement (0):= (3)currentElement.(0)pred
    (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scanFromLast
    (3)currentElement (0):= (3)currentElement.(0)pred
    (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scanFromLast
    (3)currentElement (0):= (3)currentElement.(0)pred
    (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scanFromLast
    (3)currentElement (0):= (3)currentElement.(0)pred
    (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)currentElement (0)<> (6)none (0)%then% 
    (3)current (0):= (3)currentElement.(0)elm
    (0)%inner (4)scanFromLast
    (3)currentElement (0):= (3)currentElement.(0)pred
    (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)currentElement (0)<> (6)none:IS-empty: staticOff: 0
	-- Invocation:gen: (2)currentElement (0)<> (6)none
	-- Invocation:loadOrigin: (2)currentElement (0)<> (6)none
	-- Invocation:loadOrigin:scan: (2)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)currentElement
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)<> (6)none :E: (2)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)<> (6)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (6)none:IS-empty: staticOff: 0
	-- Invocation:gen: (6)none
	-- Invocation:loadOrigin: (6)none
	-- Invocation:loadOrigin:scan: (6)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (6)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	jmpFalse L398
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 529 0 #S#529
	rpop
 L398:
 L397:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#531 531
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- Invocation:loadOrigin:scan: (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (2)head (0)= (5)none (0)%then% 
    (4)head (0):= (3)E
    (4)last (0):= (4)head (0)%else% 
    (3)E.(0)succ (0):= (4)head
    (4)head.(0)pred (0):= (3)E
    (4)head (0):= (3)E
	-- ObjectGenerator:gen: super: (2)head (0)= (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (2)head (0)= (5)none
	-- Invocation:loadOrigin: (2)head (0)= (5)none
	-- Invocation:loadOrigin:scan: (2)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)head
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)= (5)none :E: (2)head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: (0)= (5)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (5)none
	-- Invocation:loadOrigin: (5)none
	-- Invocation:loadOrigin:scan: (5)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (5)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: = (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	req
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L399:
 L400:
	rtnInner
	end 1

	class #S#532 532
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L401:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none:IS-empty: staticOff: 0
	pushThis 
	invoke 533 0 %if%then%%else%#S#533
	rpop
 L402:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#535 535
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- Invocation:loadOrigin:scan: (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (2)last (0)<> (5)none (0)%then% 
    (4)last.(0)succ (0):= (7)none (0)%else% 
    (4)head (0):= (7)none
	-- ObjectGenerator:gen: super: (2)last (0)<> (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (2)last (0)<> (5)none
	-- Invocation:loadOrigin: (2)last (0)<> (5)none
	-- Invocation:loadOrigin:scan: (2)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)last
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)<> (5)none :E: (2)last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: (0)<> (5)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)none:IS-empty: staticOff: 0
	-- Invocation:gen: (5)none
	-- Invocation:loadOrigin: (5)none
	-- Invocation:loadOrigin:scan: (5)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (5)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L403:
 L404:
	rtnInner
	end 1

	class scan#S#196 196
	rstore 4 origin
	allocEventQ
	-- super scan
	--  1:0 2:0 3:0 4:0
	-- vdtAdd: inx=1 descInx=196
	-- Invocation:loadOrigin: (2)Q.(0)scan
	-- Invocation:loadOrigin:scan: (2)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)Q
	-- AdjustOrigin: 4
	rpushg 4 origin
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)scan :E: (2)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 2 Q
	-- Invocation:loadOrigin:scan: (0)scan
	-- Unary:loadArgs: 
	topSuper  77
	rtnInner
	DO:
	doEventQ
	mvStack 
 L405:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)P (0):= (0)current:IS-empty: staticOff: 0
	-- Invocation:gen: (1)P (0):= (0)current
	-- Invocation:loadOrigin: (1)P (0):= (0)current
	-- Invocation:loadOrigin:scan: (1)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)P
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- Invocation:loadOrigin:scan: (0):= (0)current
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)current:IS-empty: staticOff: 0
	-- Invocation:gen: (0)current
	-- Invocation:loadOrigin: (0)current
	-- Invocation:loadOrigin:scan: (0)current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (0)current
	-- AdjustOrigin: 0
	-- on : 0
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: current
	rpushg 2 current
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 P
	-- ObjectGenerator:gen: super: (0)%if (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED (0)%then% 
    (2)continue (0):= (7)true:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED (0)%then% 
    (2)continue (0):= (7)true
	-- Invocation:loadOrigin: (0)%if (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED (0)%then% 
    (2)continue (0):= (7)true
	-- Invocation:loadOrigin:scan: (0)%if (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED (0)%then% 
    (2)continue (0):= (7)true
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED (0)%then% 
    (2)continue (0):= (7)true
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED (0)%then% 
    (2)continue (0):= (7)true
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED
	-- Invocation:loadOrigin: (1)P.(0)status (0)<> (4)P_status.(0)TERMINATED
	-- Invocation:loadOrigin:scan: (1)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)P
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 4 origin
	-- next not assign: (0)status :E: (1)P
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Invocation:loadOrigin:scan: (0)status
	-- next not assign: (0)<> (4)P_status.(0)TERMINATED :E: (0)status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: status
	pushg 1 status
	-- Invocation:loadOrigin:scan: (0)<> (4)P_status.(0)TERMINATED
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)P_status.(0)TERMINATED:IS-empty: staticOff: 0
	-- Invocation:gen: (4)P_status.(0)TERMINATED
	-- Invocation:loadOrigin: (4)P_status.(0)TERMINATED
	-- Invocation:loadOrigin:scan: (4)P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 4 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)TERMINATED :E: (4)P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: (0)TERMINATED
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: TERMINATED
	pushg 3 TERMINATED
	-- Binary:invoke: 
	-- pattern:load: <> (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	55
	jmpFalse L407
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 567 0 #S#567
	rpop
 L407:
 L406:
	rtnInner
	end 1

	class #S#568 568
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L408:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 356
 L409:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#569 569
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L410:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING:IS-empty: staticOff: 0
	-- Invocation:gen: (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING
	-- Invocation:loadOrigin: (6)thisCore.(0)main.(0)active.(0)status (0):= (4)P_status.(0)WAITING
	-- Invocation:loadOrigin:scan: (6)thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (6)thisCore
	%thisCore 17
	-- next not assign: (0)main :E: (6)thisCore
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thisCore -> (2)C: ? (1)core
	-- Invocation:loadOrigin:scan: (0)main
	-- next not assign: (0)active :E: (0)main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: (0)active
	-- next not assign: (0)status :E: (0)active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Invocation:loadOrigin:scan: (0)status
	-- Invocation:loadOrigin:scan: (0):= (4)P_status.(0)WAITING
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)P_status.(0)WAITING:IS-empty: staticOff: 0
	-- Invocation:gen: (4)P_status.(0)WAITING
	-- Invocation:loadOrigin: (4)P_status.(0)WAITING
	-- Invocation:loadOrigin:scan: (4)P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)WAITING :E: (4)P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: (0)WAITING
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: WAITING
	pushg 2 WAITING
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 status
	-- ObjectGenerator:gen: super: (4)SQS.(0)addWaiting:IS-empty: staticOff: 0
	-- Invocation:gen: (4)SQS.(0)addWaiting
	-- Invocation:loadOrigin: (4)SQS.(0)addWaiting
	-- Invocation:loadOrigin:scan: (4)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)SQS
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)addWaiting :E: (4)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)addWaiting
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: addWaiting
	invoke 152 0 addWaiting
	rpop
	-- ObjectGenerator:gen: super: (3)Q.(0)insert((6)thisCore.(0)main.(0)active):IS-empty: staticOff: 0
	-- Invocation:gen: (3)Q.(0)insert((6)thisCore.(0)main.(0)active)
	-- Invocation:loadOrigin: (3)Q.(0)insert((6)thisCore.(0)main.(0)active)
	-- Invocation:loadOrigin:scan: (3)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)Q
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)insert((6)thisCore.(0)main.(0)active) :E: (3)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 3 Q
	-- Invocation:loadOrigin:scan: (0)insert((6)thisCore.(0)main.(0)active)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (6)thisCore.(0)main.(0)active:IS-empty: staticOff: 0
	-- Invocation:gen: (6)thisCore.(0)main.(0)active
	-- Invocation:loadOrigin: (6)thisCore.(0)main.(0)active
	-- Invocation:loadOrigin:scan: (6)thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (6)thisCore
	%thisCore 17
	-- next not assign: (0)main :E: (6)thisCore
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thisCore -> (2)C: ? (1)core
	-- Invocation:loadOrigin:scan: (0)main
	-- next not assign: (0)active :E: (0)main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: (0)active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Function:invoke: 
	-- pattern:load: insert((2)elm: ? (4)Object)
	invoke 83 0 insert
	rpop
	-- ObjectGenerator:gen: super: (2)theActive (0):= (6)thisCore.(0)main.(0)active:IS-empty: staticOff: 0
	-- Invocation:gen: (2)theActive (0):= (6)thisCore.(0)main.(0)active
	-- Invocation:loadOrigin: (2)theActive (0):= (6)thisCore.(0)main.(0)active
	-- Invocation:loadOrigin:scan: (2)theActive
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)theActive
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= (6)thisCore.(0)main.(0)active
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (6)thisCore.(0)main.(0)active:IS-empty: staticOff: 0
	-- Invocation:gen: (6)thisCore.(0)main.(0)active
	-- Invocation:loadOrigin: (6)thisCore.(0)main.(0)active
	-- Invocation:loadOrigin:scan: (6)thisCore
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (6)thisCore
	%thisCore 17
	-- next not assign: (0)main :E: (6)thisCore
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: thisCore -> (2)C: ? (1)core
	-- Invocation:loadOrigin:scan: (0)main
	-- next not assign: (0)active :E: (0)main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: (0)active
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: active
	rpushg 2 active
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 theActive
	-- ObjectGenerator:gen: super: (3)M.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (3)M.(0)free
	-- Invocation:loadOrigin: (3)M.(0)free
	-- Invocation:loadOrigin:scan: (3)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)free :E: (3)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: (0)free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 117 0 free
	rpop
	-- ObjectGenerator:gen: super: (2)theActive.(0)suspend:IS-empty: staticOff: 0
	-- Invocation:gen: (2)theActive.(0)suspend
	-- Invocation:loadOrigin: (2)theActive.(0)suspend
	-- Invocation:loadOrigin:scan: (2)theActive
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)theActive
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- next not assign: (0)suspend :E: (2)theActive
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: theActive
	rpushg 2 theActive
	-- Invocation:loadOrigin:scan: (0)suspend
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: suspend
	suspend
 L411:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#570 570
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L412:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)M.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (3)M.(0)free
	-- Invocation:loadOrigin: (3)M.(0)free
	-- Invocation:loadOrigin:scan: (3)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)free :E: (3)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: (0)free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 117 0 free
	rpop
 L413:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#571 571
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L414:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)P (0):= (3)Q.(0)removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: (2)P (0):= (3)Q.(0)removeNext
	-- Invocation:loadOrigin: (2)P (0):= (3)Q.(0)removeNext
	-- Invocation:loadOrigin:scan: (2)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)P
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= (3)Q.(0)removeNext
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)Q.(0)removeNext:IS-empty: staticOff: 0
	-- Invocation:gen: (3)Q.(0)removeNext
	-- Invocation:loadOrigin: (3)Q.(0)removeNext
	-- Invocation:loadOrigin:scan: (3)Q
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)Q
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)removeNext :E: (3)Q
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: Q
	rpushg 3 Q
	-- Invocation:loadOrigin:scan: (0)removeNext
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: removeNext -> (2)elm: ? (4)Object
	invoke 86 0 removeNext
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 P
	-- ObjectGenerator:gen: super: (2)P.(0)status (0):= (4)P_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (2)P.(0)status (0):= (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin: (2)P.(0)status (0):= (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (2)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)P
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- next not assign: (0)status :E: (2)P
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Invocation:loadOrigin:scan: (0)status
	-- Invocation:loadOrigin:scan: (0):= (4)P_status.(0)ACTIVE
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)P_status.(0)ACTIVE:IS-empty: staticOff: 0
	-- Invocation:gen: (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin: (4)P_status.(0)ACTIVE
	-- Invocation:loadOrigin:scan: (4)P_status
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)P_status
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)ACTIVE :E: (4)P_status
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: P_status
	rpushg 3 P_status
	-- Invocation:loadOrigin:scan: (0)ACTIVE
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: ACTIVE
	pushg 1 ACTIVE
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 status
	-- ObjectGenerator:gen: super: (4)SQS.(0)insert((2)P):IS-empty: staticOff: 0
	-- Invocation:gen: (4)SQS.(0)insert((2)P)
	-- Invocation:loadOrigin: (4)SQS.(0)insert((2)P)
	-- Invocation:loadOrigin:scan: (4)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)SQS
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)insert((2)P) :E: (4)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)insert((2)P)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (2)P:IS-empty: staticOff: 0
	-- Invocation:gen: (2)P
	-- Invocation:loadOrigin: (2)P
	-- Invocation:loadOrigin:scan: (2)P
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)P
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: P
	rpushg 2 P
	-- Function:invoke: 
	-- pattern:load: insert((2)P: ? (2)BasicProcess)
	invoke 145 0 insert
	rpop
	-- ObjectGenerator:gen: super: (4)SQS.(0)dcrWaiting:IS-empty: staticOff: 0
	-- Invocation:gen: (4)SQS.(0)dcrWaiting
	-- Invocation:loadOrigin: (4)SQS.(0)dcrWaiting
	-- Invocation:loadOrigin:scan: (4)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)SQS
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)dcrWaiting :E: (4)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)dcrWaiting
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: dcrWaiting
	invoke 153 0 dcrWaiting
	rpop
	-- ObjectGenerator:gen: super: (3)M.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (3)M.(0)free
	-- Invocation:loadOrigin: (3)M.(0)free
	-- Invocation:loadOrigin:scan: (3)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)free :E: (3)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: (0)free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 117 0 free
	rpop
 L415:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#572 572
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L416:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)M.(0)free:IS-empty: staticOff: 0
	-- Invocation:gen: (3)M.(0)free
	-- Invocation:loadOrigin: (3)M.(0)free
	-- Invocation:loadOrigin:scan: (3)M
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)M
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)free :E: (3)M
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: M
	rpushg 2 M
	-- Invocation:loadOrigin:scan: (0)free
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: free
	invoke 117 0 free
	rpop
 L417:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#573 573
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L418:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)mutex.(0)signal:IS-empty: staticOff: 0
	-- Invocation:gen: (3)mutex.(0)signal
	-- Invocation:loadOrigin: (3)mutex.(0)signal
	-- Invocation:loadOrigin:scan: (3)mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)mutex
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)signal :E: (3)mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: (0)signal
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: signal
	invoke 203 0 signal
	rpop
	-- ObjectGenerator:gen: super: (3)mutex.(0)wait:IS-empty: staticOff: 0
	-- Invocation:gen: (3)mutex.(0)wait
	-- Invocation:loadOrigin: (3)mutex.(0)wait
	-- Invocation:loadOrigin:scan: (3)mutex
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)mutex
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)wait :E: (3)mutex
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: mutex
	rpushg 2 mutex
	-- Invocation:loadOrigin:scan: (0)wait
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: wait
	invoke 201 0 wait
	rpop
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 363
 L419:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#536 536
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L420:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)e (0):= (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (2)e (0):= (0)%get (1)inx
	-- Invocation:loadOrigin: (2)e (0):= (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (2)e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (0)%get (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%get (1)inx
	-- Invocation:loadOrigin: (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%get (1)inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 e
	-- ObjectGenerator:gen: super: (2)T.(0)%put (2)e (0)%at% (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (2)T.(0)%put (2)e (0)%at% (1)inx
	-- Invocation:loadOrigin: (2)T.(0)%put (2)e (0)%at% (1)inx
	-- Invocation:loadOrigin:scan: (2)T
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)T
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- next not assign: (0)%put (2)e (0)%at% (1)inx :E: (2)T
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: (0)%put (2)e (0)%at% (1)inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put (2)e (0)%at% (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (2)e:IS-empty: staticOff: 0
	-- Invocation:gen: (2)e
	-- Invocation:loadOrigin: (2)e
	-- Invocation:loadOrigin:scan: (2)e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xstoreg 1 inx
 L421:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#537 537
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L422:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)e (0):= (3)S.(0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (2)e (0):= (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin: (2)e (0):= (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin:scan: (2)e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (3)S.(0)%get (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)S.(0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin: (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin:scan: (3)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)%get (1)inx :E: (3)S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 e
	-- ObjectGenerator:gen: super: (2)i (0):= (3)L (0)+ (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (2)i (0):= (3)L (0)+ (1)inx
	-- Invocation:loadOrigin: (2)i (0):= (3)L (0)+ (1)inx
	-- Invocation:loadOrigin:scan: (2)i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)i
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (3)L (0)+ (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)L (0)+ (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (3)L (0)+ (1)inx
	-- Invocation:loadOrigin: (3)L (0)+ (1)inx
	-- Invocation:loadOrigin:scan: (3)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)L
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)+ (1)inx :E: (3)L
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L
	pushg 1 L
	-- Invocation:loadOrigin:scan: (0)+ (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	-- Binary:invoke: 
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 2 i
	-- ObjectGenerator:gen: super: (2)T.(0)%put (2)e (0)%at% (2)i:IS-empty: staticOff: 0
	-- Invocation:gen: (2)T.(0)%put (2)e (0)%at% (2)i
	-- Invocation:loadOrigin: (2)T.(0)%put (2)e (0)%at% (2)i
	-- Invocation:loadOrigin:scan: (2)T
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)T
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- next not assign: (0)%put (2)e (0)%at% (2)i :E: (2)T
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: T
	rpushg 2 T
	-- Invocation:loadOrigin:scan: (0)%put (2)e (0)%at% (2)i
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer(0)%put (2)e (0)%at% (2)i
	-- KeyWord:invoke: 
	-- pattern:load: (0)%put (2)V: ? (1)elm (0)%at% (1)inx: ? (2)integer
	-- name::gen: 
	-- ObjectGenerator:gen: super: (2)e:IS-empty: staticOff: 0
	-- Invocation:gen: (2)e
	-- Invocation:loadOrigin: (2)e
	-- Invocation:loadOrigin:scan: (2)e
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)e
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: e
	pushg 1 e
	-- name::gen: 
	-- ObjectGenerator:gen: super: (2)i:IS-empty: staticOff: 0
	-- Invocation:gen: (2)i
	-- Invocation:loadOrigin: (2)i
	-- Invocation:loadOrigin:scan: (2)i
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)i
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: i
	pushg 2 i
	xstoreg 1 inx
 L423:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class body#SB#541 541
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L424:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)c1 (0):= (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (2)c1 (0):= (0)%get (1)inx
	-- Invocation:loadOrigin: (2)c1 (0):= (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (2)c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)c1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (0)%get (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%get (1)inx
	-- Invocation:loadOrigin: (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%get (1)inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 c1
	-- ObjectGenerator:gen: super: (2)c2 (0):= (3)S.(0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (2)c2 (0):= (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin: (2)c2 (0):= (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin:scan: (2)c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)c2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Invocation:loadOrigin:scan: (0):= (3)S.(0)%get (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)S.(0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin: (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin:scan: (3)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- next not assign: (0)%get (1)inx :E: (3)S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 3 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 2 c2
	-- ObjectGenerator:gen: super: (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- Invocation:loadOrigin: (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- Invocation:loadOrigin:scan: (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)c1 (0)<> (2)c2 (0)%then% 
    (4)B (0):= (7)false
    (0)%leave (4)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)c1 (0)<> (2)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (2)c1 (0)<> (2)c2
	-- Invocation:loadOrigin: (2)c1 (0)<> (2)c2
	-- Invocation:loadOrigin:scan: (2)c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)c1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- next not assign: (0)<> (2)c2 :E: (2)c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 1 c1
	-- Invocation:loadOrigin:scan: (0)<> (2)c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (2)c2
	-- Invocation:loadOrigin: (2)c2
	-- Invocation:loadOrigin:scan: (2)c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)c2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 2 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 2 c2
	-- Binary:invoke: 
	-- pattern:load: <> (1)V: ? (2)char -> (2)B: ? (2)Boolean
	55
	jmpFalse L426
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 666 0 #S#666
	rpop
 L426:
 L425:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class loop 108
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L427:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (1)inx (0):= (1)inx (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx (0):= (1)inx (0)+ 1
	-- Invocation:loadOrigin: (1)inx (0):= (1)inx (0)+ 1
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (1)inx (0)+ 1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)inx (0)+ 1:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx (0)+ 1
	-- Invocation:loadOrigin: (1)inx (0)+ 1
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)+ 1 :E: (1)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: (0)+ 1
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
	-- pattern:load: + (1)V: ? (2)integer -> (2)R: ? (2)integer
	plus
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 inx
	-- ObjectGenerator:gen: super: (1)c1 (0):= (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)c1 (0):= (0)%get (1)inx
	-- Invocation:loadOrigin: (1)c1 (0):= (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (1)c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)c1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (0)%get (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%get (1)inx
	-- Invocation:loadOrigin: (0)%get (1)inx
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%get (1)inx
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 2 c1
	-- ObjectGenerator:gen: super: (1)c2 (0):= (3)S.(0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)c2 (0):= (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin: (1)c2 (0):= (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin:scan: (1)c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)c2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)S.(0)%get (1)inx
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)S.(0)%get (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin: (3)S.(0)%get (1)inx
	-- Invocation:loadOrigin:scan: (3)S
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)S
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)%get (1)inx :E: (3)S
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: S
	rpushg 2 S
	-- Invocation:loadOrigin:scan: (0)%get (1)inx
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char(0)%get (1)inx
	-- KeyWord:invoke: 
	-- pattern:load: (0)%get (1)inx: ? (3)integer -> (2)ch: ? (3)Char
	-- name::gen: 
	-- ObjectGenerator:gen: super: (1)inx:IS-empty: staticOff: 0
	-- Invocation:gen: (1)inx
	-- Invocation:loadOrigin: (1)inx
	-- Invocation:loadOrigin:scan: (1)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)inx
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	xpushg 1 inx
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 3 c2
	-- ObjectGenerator:gen: super: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (1)c1 (0)= (1)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (1)c1 (0)= (1)c2
	-- Invocation:loadOrigin: (1)c1 (0)= (1)c2
	-- Invocation:loadOrigin:scan: (1)c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)c1
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (1)c2 :E: (1)c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: (0)= (1)c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (1)c2
	-- Invocation:loadOrigin: (1)c2
	-- Invocation:loadOrigin:scan: (1)c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)c2
	-- AdjustOrigin: 0
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = (1)V: ? (2)char -> (2)B: ? (2)Boolean
	eq
	jmpFalse L429
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 542 0 #S#542
	rpop
 L429:
 L428:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class doit 109
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L430:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (5)B (0):= (4)L1 (0)<= (4)L2
    (0)%leave (4)matchEq (0)%else% 
    (5)B (0):= (3)c1 (0)< (3)c2
    (0)%leave (4)matchEq:IS-empty: staticOff: 0
	pushThis 
	invoke 110 0 %if%then%%else%#S#110
	rpop
 L431:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#545 545
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L432:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)L (0):= (2)L1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)L (0):= (2)L1
	-- Invocation:loadOrigin: (2)L (0):= (2)L1
	-- Invocation:loadOrigin:scan: (2)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= (2)L1
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)L1:IS-empty: staticOff: 0
	-- Invocation:gen: (2)L1
	-- Invocation:loadOrigin: (2)L1
	-- Invocation:loadOrigin:scan: (2)L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)L1
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 L
 L433:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#546 546
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L434:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)L (0):= (2)L2:IS-empty: staticOff: 0
	-- Invocation:gen: (2)L (0):= (2)L2
	-- Invocation:loadOrigin: (2)L (0):= (2)L2
	-- Invocation:loadOrigin:scan: (2)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)L
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Invocation:loadOrigin:scan: (0):= (2)L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (2)L2:IS-empty: staticOff: 0
	-- Invocation:gen: (2)L2
	-- Invocation:loadOrigin: (2)L2
	-- Invocation:loadOrigin:scan: (2)L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)L2
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 2 origin
	rpushg 3 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L2
	pushg 3 L2
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 L
 L435:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#667 667
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L436:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)SQS.(0)insert((4)active):IS-empty: staticOff: 0
	-- Invocation:gen: (5)SQS.(0)insert((4)active)
	-- Invocation:loadOrigin: (5)SQS.(0)insert((4)active)
	-- Invocation:loadOrigin:scan: (5)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)SQS
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)insert((4)active) :E: (5)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)insert((4)active)
	-- Function:loadArgs: 
	-- ObjectGenerator:gen: super: (4)active:IS-empty: staticOff: 0
	-- Invocation:gen: (4)active
	-- Invocation:loadOrigin: (4)active
	-- Invocation:loadOrigin:scan: (4)active
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)active
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
	-- pattern:load: insert((2)P: ? (2)BasicProcess)
	invoke 145 0 insert
	rpop
 L437:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#549 549
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L438:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
	-- Invocation:loadOrigin: (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
	-- Invocation:loadOrigin:scan: (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (5)SQS.(0)hasWaiting (0)%then% 
    (8)sleep(100)
    (0)%restart (4)Loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (5)SQS.(0)hasWaiting:IS-empty: staticOff: 0
	-- Invocation:gen: (5)SQS.(0)hasWaiting
	-- Invocation:loadOrigin: (5)SQS.(0)hasWaiting
	-- Invocation:loadOrigin:scan: (5)SQS
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)SQS
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)hasWaiting :E: (5)SQS
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: SQS
	rpushg 5 SQS
	-- Invocation:loadOrigin:scan: (0)hasWaiting
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: hasWaiting -> (1)B: ? (4)boolean
	invoke 154 0 hasWaiting
	jmpFalse L440
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 668 0 #S#668
	rpop
 L440:
	-- ObjectGenerator:gen: super: (5)sch.(0)dcr:IS-empty: staticOff: 0
	-- Invocation:gen: (5)sch.(0)dcr
	-- Invocation:loadOrigin: (5)sch.(0)dcr
	-- Invocation:loadOrigin:scan: (5)sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)sch
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)dcr :E: (5)sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: (0)dcr
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: dcr
	invoke 138 0 dcr
	rpop
	-- ObjectGenerator:gen: super: (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop
	-- Invocation:loadOrigin: (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop
	-- Invocation:loadOrigin:scan: (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (5)sch.(0)running (0)%then% 
    (8)sleep(50)
    (6)sch.(0)add
    (0)%restart (4)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (5)sch.(0)running:IS-empty: staticOff: 0
	-- Invocation:gen: (5)sch.(0)running
	-- Invocation:loadOrigin: (5)sch.(0)running
	-- Invocation:loadOrigin:scan: (5)sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)sch
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)running :E: (5)sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: (0)running
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: running -> (1)B: ? (4)Boolean
	invoke 140 0 running
	jmpFalse L441
	-- ObjectGenerator:gen: super: :singular:staticOff: 0
	pushThis 
	invoke 669 0 #S#669
	rpop
 L441:
 L439:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#550 550
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L442:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%restart (3)Loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (3)Loop
	-- Invocation:loadOrigin: (0)%restart (3)Loop
	-- Invocation:loadOrigin:scan: (0)%restart (3)Loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (3)Loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (3)Loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 2 306
 L443:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#551 551
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L444:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (4)main.(0)resume:IS-empty: staticOff: 0
	-- Invocation:gen: (4)main.(0)resume
	-- Invocation:loadOrigin: (4)main.(0)resume
	-- Invocation:loadOrigin:scan: (4)main
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)main
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)resume :E: (4)main
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: main
	rpushg 2 main
	-- Invocation:loadOrigin:scan: (0)resume
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: resume
	call(D)Resume
	rpop
 L445:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#552 552
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L446:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (7)sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: (7)sleep(100)
	-- Invocation:loadOrigin: (7)sleep(100)
	-- Invocation:loadOrigin:scan: (7)sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: (7)sleep(100)
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
	-- pattern:load: sleep((1)V: ? (1)integer)
	%sleep 15
	-- ObjectGenerator:gen: super: (0)%restart (3)loopX:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (3)loopX
	-- Invocation:loadOrigin: (0)%restart (3)loopX
	-- Invocation:loadOrigin:scan: (0)%restart (3)loopX
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (3)loopX
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (3)loopX
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 2 309
 L447:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#528 528
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L448:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)current (0):= (3)currentElement.(0)elm:IS-empty: staticOff: 0
	-- Invocation:gen: (3)current (0):= (3)currentElement.(0)elm
	-- Invocation:loadOrigin: (3)current (0):= (3)currentElement.(0)elm
	-- Invocation:loadOrigin:scan: (3)current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)current
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)currentElement.(0)elm
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)currentElement.(0)elm:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)elm
	-- Invocation:loadOrigin: (3)currentElement.(0)elm
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)elm :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 current
	-- ObjectGenerator:gen: super: (0)%inner (4)scan:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (4)scan
	-- Invocation:loadOrigin: (0)%inner (4)scan
	-- Invocation:loadOrigin:scan: (0)%inner (4)scan
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (4)scan
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (4)scan
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: (3)currentElement (0):= (3)currentElement.(0)succ:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement (0):= (3)currentElement.(0)succ
	-- Invocation:loadOrigin: (3)currentElement (0):= (3)currentElement.(0)succ
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)currentElement.(0)succ
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)currentElement.(0)succ:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)succ
	-- Invocation:loadOrigin: (3)currentElement.(0)succ
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)succ :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 393
 L449:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#529 529
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L450:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)current (0):= (3)currentElement.(0)elm:IS-empty: staticOff: 0
	-- Invocation:gen: (3)current (0):= (3)currentElement.(0)elm
	-- Invocation:loadOrigin: (3)current (0):= (3)currentElement.(0)elm
	-- Invocation:loadOrigin:scan: (3)current
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)current
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)currentElement.(0)elm
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)currentElement.(0)elm:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)elm
	-- Invocation:loadOrigin: (3)currentElement.(0)elm
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)elm :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)elm
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: elm
	rpushg 2 elm
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 current
	-- ObjectGenerator:gen: super: (0)%inner (4)scanFromLast:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%inner (4)scanFromLast
	-- Invocation:loadOrigin: (0)%inner (4)scanFromLast
	-- Invocation:loadOrigin:scan: (0)%inner (4)scanFromLast
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%inner (4)scanFromLast
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%inner (2)P: ? (1)Object(0)%inner (4)scanFromLast
	-- KeyWord:invoke: 
	-- pattern:load: (0)%inner (2)P: ? (1)Object
	pushThis 
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	inner  1
	rpopThisObj 
	-- ObjectGenerator:gen: super: (3)currentElement (0):= (3)currentElement.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement (0):= (3)currentElement.(0)pred
	-- Invocation:loadOrigin: (3)currentElement (0):= (3)currentElement.(0)pred
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)currentElement.(0)pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)currentElement.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)pred
	-- Invocation:loadOrigin: (3)currentElement.(0)pred
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)pred :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 currentElement
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 396
 L451:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#658 658
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L452:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (4)head (0):= (3)E:IS-empty: staticOff: 0
	-- Invocation:gen: (4)head (0):= (3)E
	-- Invocation:loadOrigin: (4)head (0):= (3)E
	-- Invocation:loadOrigin:scan: (4)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)E
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)E:IS-empty: staticOff: 0
	-- Invocation:gen: (3)E
	-- Invocation:loadOrigin: (3)E
	-- Invocation:loadOrigin:scan: (3)E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)E
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
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 head
	-- ObjectGenerator:gen: super: (4)last (0):= (4)head:IS-empty: staticOff: 0
	-- Invocation:gen: (4)last (0):= (4)head
	-- Invocation:loadOrigin: (4)last (0):= (4)head
	-- Invocation:loadOrigin:scan: (4)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)last
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (4)head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)head:IS-empty: staticOff: 0
	-- Invocation:gen: (4)head
	-- Invocation:loadOrigin: (4)head
	-- Invocation:loadOrigin:scan: (4)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)head
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
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 last
 L453:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#659 659
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L454:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)E.(0)succ (0):= (4)head:IS-empty: staticOff: 0
	-- Invocation:gen: (3)E.(0)succ (0):= (4)head
	-- Invocation:loadOrigin: (3)E.(0)succ (0):= (4)head
	-- Invocation:loadOrigin:scan: (3)E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)E
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)succ :E: (3)E
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: E
	rpushg 3 E
	-- Invocation:loadOrigin:scan: (0)succ
	-- Invocation:loadOrigin:scan: (0):= (4)head
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)head:IS-empty: staticOff: 0
	-- Invocation:gen: (4)head
	-- Invocation:loadOrigin: (4)head
	-- Invocation:loadOrigin:scan: (4)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)head
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
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 5 succ
	-- ObjectGenerator:gen: super: (4)head.(0)pred (0):= (3)E:IS-empty: staticOff: 0
	-- Invocation:gen: (4)head.(0)pred (0):= (3)E
	-- Invocation:loadOrigin: (4)head.(0)pred (0):= (3)E
	-- Invocation:loadOrigin:scan: (4)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)pred :E: (4)head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: (0)pred
	-- Invocation:loadOrigin:scan: (0):= (3)E
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)E:IS-empty: staticOff: 0
	-- Invocation:gen: (3)E
	-- Invocation:loadOrigin: (3)E
	-- Invocation:loadOrigin:scan: (3)E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)E
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
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 4 pred
	-- ObjectGenerator:gen: super: (4)head (0):= (3)E:IS-empty: staticOff: 0
	-- Invocation:gen: (4)head (0):= (3)E
	-- Invocation:loadOrigin: (4)head (0):= (3)E
	-- Invocation:loadOrigin:scan: (4)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)E
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)E:IS-empty: staticOff: 0
	-- Invocation:gen: (3)E
	-- Invocation:loadOrigin: (3)E
	-- Invocation:loadOrigin:scan: (3)E
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)E
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
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 head
 L455:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#533 533
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- Invocation:loadOrigin:scan: (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
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
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)currentElement.(0)pred (0)<> (6)none (0)%then% 
    (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
    (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred (0)%else% 
    (5)head (0):= (3)currentElement.(0)succ
    (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- ObjectGenerator:gen: super: (1)currentElement.(0)pred (0)<> (6)none:IS-empty: staticOff: 0
	-- Invocation:gen: (1)currentElement.(0)pred (0)<> (6)none
	-- Invocation:loadOrigin: (1)currentElement.(0)pred (0)<> (6)none
	-- Invocation:loadOrigin:scan: (1)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)currentElement
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)pred :E: (1)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)pred
	-- next not assign: (0)<> (6)none :E: (0)pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Invocation:loadOrigin:scan: (0)<> (6)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (6)none:IS-empty: staticOff: 0
	-- Invocation:gen: (6)none
	-- Invocation:loadOrigin: (6)none
	-- Invocation:loadOrigin:scan: (6)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (6)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L456:
 L457:
	rtnInner
	end 1

	class thenPart#SB#664 664
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L458:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (4)last.(0)succ (0):= (7)none:IS-empty: staticOff: 0
	-- Invocation:gen: (4)last.(0)succ (0):= (7)none
	-- Invocation:loadOrigin: (4)last.(0)succ (0):= (7)none
	-- Invocation:loadOrigin:scan: (4)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)last
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)succ :E: (4)last
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: last
	rpushg 3 last
	-- Invocation:loadOrigin:scan: (0)succ
	-- Invocation:loadOrigin:scan: (0):= (7)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (7)none:IS-empty: staticOff: 0
	-- Invocation:gen: (7)none
	-- Invocation:loadOrigin: (7)none
	-- Invocation:loadOrigin:scan: (7)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (7)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 5 succ
 L459:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#665 665
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L460:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (4)head (0):= (7)none:IS-empty: staticOff: 0
	-- Invocation:gen: (4)head (0):= (7)none
	-- Invocation:loadOrigin: (4)head (0):= (7)none
	-- Invocation:loadOrigin:scan: (4)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)head
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (7)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (7)none:IS-empty: staticOff: 0
	-- Invocation:gen: (7)none
	-- Invocation:loadOrigin: (7)none
	-- Invocation:loadOrigin:scan: (7)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (7)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 head
 L461:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#567 567
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L462:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (2)continue (0):= (7)true:IS-empty: staticOff: 0
	-- Invocation:gen: (2)continue (0):= (7)true
	-- Invocation:loadOrigin: (2)continue (0):= (7)true
	-- Invocation:loadOrigin:scan: (2)continue
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)continue
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 4 origin
	-- Invocation:loadOrigin:scan: (0):= (7)true
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (7)true:IS-empty: staticOff: 0
	-- Invocation:gen: (7)true
	-- Invocation:loadOrigin: (7)true
	-- Invocation:loadOrigin:scan: (7)true
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (7)true
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
	-- pattern:load: True -> (1)B: ? (1)Boolean
	invoke 24 0 True
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 continue
 L463:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#666 666
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L464:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (4)B (0):= (7)false:IS-empty: staticOff: 0
	-- Invocation:gen: (4)B (0):= (7)false
	-- Invocation:loadOrigin: (4)B (0):= (7)false
	-- Invocation:loadOrigin:scan: (4)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)B
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 1 origin
	rpushg 2 origin
	rpushg 2 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (7)false
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (7)false:IS-empty: staticOff: 0
	-- Invocation:gen: (7)false
	-- Invocation:loadOrigin: (7)false
	-- Invocation:loadOrigin:scan: (7)false
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (7)false
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
	-- pattern:load: False -> (1)B: ? (1)Boolean
	invoke 23 0 False
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 B
	-- ObjectGenerator:gen: super: (0)%leave (4)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%leave (4)loop
	-- Invocation:loadOrigin: (0)%leave (4)loop
	-- Invocation:loadOrigin:scan: (0)%leave (4)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%leave (4)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%leave (1)Obj: ? (1)integer(0)%leave (4)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%leave (1)Obj: ? (1)integer
	break 3 289
 L465:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#542 542
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L466:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object(0)%if (2)inx (0)< (3)L (0)%then% (0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%if (1)_cond: ? (0)Boolean (0)%then% (1)_thenPart:< (0)Object
	-- ObjectGenerator:gen: super: (2)inx (0)< (3)L:IS-empty: staticOff: 0
	-- Invocation:gen: (2)inx (0)< (3)L
	-- Invocation:loadOrigin: (2)inx (0)< (3)L
	-- Invocation:loadOrigin:scan: (2)inx
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (2)inx
	-- AdjustOrigin: 0
	-- on : 2
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)< (3)L :E: (2)inx
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: inx
	pushg 1 inx
	-- Invocation:loadOrigin:scan: (0)< (3)L
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)L:IS-empty: staticOff: 0
	-- Invocation:gen: (3)L
	-- Invocation:loadOrigin: (3)L
	-- Invocation:loadOrigin:scan: (3)L
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)L
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
	-- pattern:load: < (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	51
	jmpFalse L468
	-- ObjectGenerator:gen: super: (0)%restart (2)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (2)loop
	-- Invocation:loadOrigin: (0)%restart (2)loop
	-- Invocation:loadOrigin:scan: (0)%restart (2)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (2)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (2)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 1 427
 L468:
 L467:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#110 110
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (5)B (0):= (4)L1 (0)<= (4)L2
    (0)%leave (4)matchEq (0)%else% 
    (5)B (0):= (3)c1 (0)< (3)c2
    (0)%leave (4)matchEq
	-- Invocation:loadOrigin:scan: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (5)B (0):= (4)L1 (0)<= (4)L2
    (0)%leave (4)matchEq (0)%else% 
    (5)B (0):= (3)c1 (0)< (3)c2
    (0)%leave (4)matchEq
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (5)B (0):= (4)L1 (0)<= (4)L2
    (0)%leave (4)matchEq (0)%else% 
    (5)B (0):= (3)c1 (0)< (3)c2
    (0)%leave (4)matchEq
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
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (1)c1 (0)= (1)c2 (0)%then% 
    (5)B (0):= (4)L1 (0)<= (4)L2
    (0)%leave (4)matchEq (0)%else% 
    (5)B (0):= (3)c1 (0)< (3)c2
    (0)%leave (4)matchEq
	-- ObjectGenerator:gen: super: (1)c1 (0)= (1)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (1)c1 (0)= (1)c2
	-- Invocation:loadOrigin: (1)c1 (0)= (1)c2
	-- Invocation:loadOrigin:scan: (1)c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)c1
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- next not assign: (0)= (1)c2 :E: (1)c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: (0)= (1)c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (1)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (1)c2
	-- Invocation:loadOrigin: (1)c2
	-- Invocation:loadOrigin:scan: (1)c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (1)c2
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 1
	rpushg 1 origin
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c2
	pushg 3 c2
	-- Binary:invoke: 
	-- pattern:load: = (1)V: ? (2)char -> (2)B: ? (2)Boolean
	eq
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L469:
 L470:
	rtnInner
	end 1

	class #S#668 668
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L471:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (8)sleep(100):IS-empty: staticOff: 0
	-- Invocation:gen: (8)sleep(100)
	-- Invocation:loadOrigin: (8)sleep(100)
	-- Invocation:loadOrigin:scan: (8)sleep(100)
	-- Function:pushThis: 
	-- Function:loadOrigin: (8)sleep(100)
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
	-- pattern:load: sleep((1)V: ? (1)integer)
	%sleep 15
	-- ObjectGenerator:gen: super: (0)%restart (4)Loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (4)Loop
	-- Invocation:loadOrigin: (0)%restart (4)Loop
	-- Invocation:loadOrigin:scan: (0)%restart (4)Loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (4)Loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (4)Loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 3 306
 L472:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class #S#669 669
	rstore 1 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L473:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (8)sleep(50):IS-empty: staticOff: 0
	-- Invocation:gen: (8)sleep(50)
	-- Invocation:loadOrigin: (8)sleep(50)
	-- Invocation:loadOrigin:scan: (8)sleep(50)
	-- Function:pushThis: 
	-- Function:loadOrigin: (8)sleep(50)
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
	-- pattern:load: sleep((1)V: ? (1)integer)
	%sleep 15
	-- ObjectGenerator:gen: super: (6)sch.(0)add:IS-empty: staticOff: 0
	-- Invocation:gen: (6)sch.(0)add
	-- Invocation:loadOrigin: (6)sch.(0)add
	-- Invocation:loadOrigin:scan: (6)sch
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (6)sch
	-- AdjustOrigin: 0
	-- on : 6
	rpushg 1 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)add :E: (6)sch
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- ConsRef:load: sch
	rpushg 4 sch
	-- Invocation:loadOrigin:scan: (0)add
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: add
	invoke 136 0 add
	rpop
	-- ObjectGenerator:gen: super: (0)%restart (4)loop:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%restart (4)loop
	-- Invocation:loadOrigin: (0)%restart (4)loop
	-- Invocation:loadOrigin:scan: (0)%restart (4)loop
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%restart (4)loop
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%restart (1)Obj: ? (1)integer(0)%restart (4)loop
	-- KeyWord:invoke: 
	-- pattern:load: (0)%restart (1)Obj: ? (1)integer
	break 3 306
 L474:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#660 660
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L475:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
	-- Invocation:loadOrigin: (3)currentElement.(0)pred.(0)succ (0):= (3)currentElement.(0)succ
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)pred :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)pred
	-- next not assign: (0)succ :E: (0)pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Invocation:loadOrigin:scan: (0)succ
	-- Invocation:loadOrigin:scan: (0):= (3)currentElement.(0)succ
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)currentElement.(0)succ:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)succ
	-- Invocation:loadOrigin: (3)currentElement.(0)succ
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)succ :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 5 succ
	-- ObjectGenerator:gen: super: (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred:IS-empty: staticOff: 0
	pushThis 
	invoke 661 0 %if%then%%else%#S#661
	rpop
 L476:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#662 662
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L477:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)head (0):= (3)currentElement.(0)succ:IS-empty: staticOff: 0
	-- Invocation:gen: (5)head (0):= (3)currentElement.(0)succ
	-- Invocation:loadOrigin: (5)head (0):= (3)currentElement.(0)succ
	-- Invocation:loadOrigin:scan: (5)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)head
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)currentElement.(0)succ
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)currentElement.(0)succ:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)succ
	-- Invocation:loadOrigin: (3)currentElement.(0)succ
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)succ :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 2 head
	-- ObjectGenerator:gen: super: (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none:IS-empty: staticOff: 0
	pushThis 
	invoke 663 0 %if%then%%else%#S#663
	rpop
 L478:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#543 543
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L479:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)B (0):= (4)L1 (0)<= (4)L2:IS-empty: staticOff: 0
	-- Invocation:gen: (5)B (0):= (4)L1 (0)<= (4)L2
	-- Invocation:loadOrigin: (5)B (0):= (4)L1 (0)<= (4)L2
	-- Invocation:loadOrigin:scan: (5)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)B
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (4)L1 (0)<= (4)L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)L1 (0)<= (4)L2:IS-empty: staticOff: 0
	-- Invocation:gen: (4)L1 (0)<= (4)L2
	-- Invocation:loadOrigin: (4)L1 (0)<= (4)L2
	-- Invocation:loadOrigin:scan: (4)L1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)L1
	-- AdjustOrigin: 0
	-- on : 4
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	-- next not assign: (0)<= (4)L2 :E: (4)L1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: L1
	pushg 2 L1
	-- Invocation:loadOrigin:scan: (0)<= (4)L2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (4)L2:IS-empty: staticOff: 0
	-- Invocation:gen: (4)L2
	-- Invocation:loadOrigin: (4)L2
	-- Invocation:loadOrigin:scan: (4)L2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (4)L2
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
	-- pattern:load: <= (1)V: ? (2)integer -> (2)B: ? (2)Boolean
	52
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 B
	-- ObjectGenerator:gen: super: (0)%leave (4)matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%leave (4)matchEq
	-- Invocation:loadOrigin: (0)%leave (4)matchEq
	-- Invocation:loadOrigin:scan: (0)%leave (4)matchEq
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%leave (4)matchEq
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%leave (1)Obj: ? (1)integer(0)%leave (4)matchEq
	-- KeyWord:invoke: 
	-- pattern:load: (0)%leave (1)Obj: ? (1)integer
	break 3 379
 L480:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#544 544
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L481:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)B (0):= (3)c1 (0)< (3)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (5)B (0):= (3)c1 (0)< (3)c2
	-- Invocation:loadOrigin: (5)B (0):= (3)c1 (0)< (3)c2
	-- Invocation:loadOrigin:scan: (5)B
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)B
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 1 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (3)c1 (0)< (3)c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)c1 (0)< (3)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (3)c1 (0)< (3)c2
	-- Invocation:loadOrigin: (3)c1 (0)< (3)c2
	-- Invocation:loadOrigin:scan: (3)c1
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)c1
	-- AdjustOrigin: 0
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)< (3)c2 :E: (3)c1
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: c1
	pushg 2 c1
	-- Invocation:loadOrigin:scan: (0)< (3)c2
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (3)c2:IS-empty: staticOff: 0
	-- Invocation:gen: (3)c2
	-- Invocation:loadOrigin: (3)c2
	-- Invocation:loadOrigin:scan: (3)c2
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)c2
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
	-- pattern:load: < (1)V: ? (2)char -> (2)B: ? (2)Boolean
	51
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	storeg 1 B
	-- ObjectGenerator:gen: super: (0)%leave (4)matchEq:IS-empty: staticOff: 0
	-- Invocation:gen: (0)%leave (4)matchEq
	-- Invocation:loadOrigin: (0)%leave (4)matchEq
	-- Invocation:loadOrigin:scan: (0)%leave (4)matchEq
	-- KeyWord:pushThis: 
	-- KeyWord:loadOrigin: (0)%leave (4)matchEq
	-- KeyWord:loadArgs: 
	-- pattern:loadArgs: (0)%leave (1)Obj: ? (1)integer(0)%leave (4)matchEq
	-- KeyWord:invoke: 
	-- pattern:load: (0)%leave (1)Obj: ? (1)integer
	break 3 379
 L482:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class %if%then%%else%#S#661 661
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred
	-- Invocation:loadOrigin:scan: (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred
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
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (3)currentElement.(0)succ (0)<> (8)none (0)%then% 
    (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred (0)%else% 
    (7)last (0):= (5)currentElement.(0)pred
	-- ObjectGenerator:gen: super: (3)currentElement.(0)succ (0)<> (8)none:IS-empty: staticOff: 0
	-- Invocation:gen: (3)currentElement.(0)succ (0)<> (8)none
	-- Invocation:loadOrigin: (3)currentElement.(0)succ (0)<> (8)none
	-- Invocation:loadOrigin:scan: (3)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (3)currentElement
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 3
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)succ :E: (3)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)succ
	-- next not assign: (0)<> (8)none :E: (0)succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Invocation:loadOrigin:scan: (0)<> (8)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (8)none:IS-empty: staticOff: 0
	-- Invocation:gen: (8)none
	-- Invocation:loadOrigin: (8)none
	-- Invocation:loadOrigin:scan: (8)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (8)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L483:
 L484:
	rtnInner
	end 1

	class %if%then%%else%#S#663 663
	rstore 3 origin
	allocEventQ
	-- super %if%then%%else%
	--  1:0 2:0 3:0 4:0
	-- Invocation:loadOrigin: (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- Invocation:loadOrigin:scan: (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- KeyWord:pushThis: 
	pushThis 
	-- KeyWord:loadOrigin: (0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
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
	-- pattern:loadArgs: (0)%if (1)cond: ? (1)Boolean (0)%then% (1)thenPart:< (1)Object (0)%else% (2)elsePart:< (1)Object(0)%if (5)head (0)<> (8)none (0)%then% 
    (7)head.(0)pred (0):= (10)none (0)%else% 
    (7)last (0):= (10)none
	-- ObjectGenerator:gen: super: (5)head (0)<> (8)none:IS-empty: staticOff: 0
	-- Invocation:gen: (5)head (0)<> (8)none
	-- Invocation:loadOrigin: (5)head (0)<> (8)none
	-- Invocation:loadOrigin:scan: (5)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)head
	-- AdjustOrigin: 3
	rpushg 3 origin
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- next not assign: (0)<> (8)none :E: (5)head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: (0)<> (8)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (8)none:IS-empty: staticOff: 0
	-- Invocation:gen: (8)none
	-- Invocation:loadOrigin: (8)none
	-- Invocation:loadOrigin:scan: (8)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (8)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: <> (2)obj: ? (2)Object -> (1)V: ? (2)Boolean
	rne
	topSuper  60
	rtnInner
	DO:
	mvStack 
 L485:
 L486:
	rtnInner
	end 1

	class thenPart#SB#680 680
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L487:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred
	-- Invocation:loadOrigin: (5)currentElement.(0)succ.(0)pred (0):= (5)currentElement.(0)pred
	-- Invocation:loadOrigin:scan: (5)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)succ :E: (5)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)succ
	-- next not assign: (0)pred :E: (0)succ
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: succ
	rpushg 5 succ
	-- Invocation:loadOrigin:scan: (0)pred
	-- Invocation:loadOrigin:scan: (0):= (5)currentElement.(0)pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)currentElement.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (5)currentElement.(0)pred
	-- Invocation:loadOrigin: (5)currentElement.(0)pred
	-- Invocation:loadOrigin:scan: (5)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)pred :E: (5)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 4 pred
 L488:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#681 681
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L489:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (7)last (0):= (5)currentElement.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (7)last (0):= (5)currentElement.(0)pred
	-- Invocation:loadOrigin: (7)last (0):= (5)currentElement.(0)pred
	-- Invocation:loadOrigin:scan: (7)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (7)last
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (5)currentElement.(0)pred
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (5)currentElement.(0)pred:IS-empty: staticOff: 0
	-- Invocation:gen: (5)currentElement.(0)pred
	-- Invocation:loadOrigin: (5)currentElement.(0)pred
	-- Invocation:loadOrigin:scan: (5)currentElement
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (5)currentElement
	-- AdjustOrigin: 0
	-- on : 5
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	-- next not assign: (0)pred :E: (5)currentElement
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: currentElement
	rpushg 3 currentElement
	-- Invocation:loadOrigin:scan: (0)pred
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: pred
	rpushg 4 pred
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 last
 L490:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class thenPart#SB#682 682
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L491:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (7)head.(0)pred (0):= (10)none:IS-empty: staticOff: 0
	-- Invocation:gen: (7)head.(0)pred (0):= (10)none
	-- Invocation:loadOrigin: (7)head.(0)pred (0):= (10)none
	-- Invocation:loadOrigin:scan: (7)head
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (7)head
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- next not assign: (0)pred :E: (7)head
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- VarRef:load: head
	rpushg 2 head
	-- Invocation:loadOrigin:scan: (0)pred
	-- Invocation:loadOrigin:scan: (0):= (10)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (10)none:IS-empty: staticOff: 0
	-- Invocation:gen: (10)none
	-- Invocation:loadOrigin: (10)none
	-- Invocation:loadOrigin:scan: (10)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (10)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 4 pred
 L492:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class elsePart#SB#683 683
	rstore 2 origin
	allocEventQ
	mvStack 
	rtnEventQ 1
	DO:
	doEventQ
	mvStack 
 L493:
	-- Include:gen: 
	-- ObjectGenerator:gen: super: (7)last (0):= (10)none:IS-empty: staticOff: 0
	-- Invocation:gen: (7)last (0):= (10)none
	-- Invocation:loadOrigin: (7)last (0):= (10)none
	-- Invocation:loadOrigin:scan: (7)last
	-- Unary:pushThis: 
	pushThis 
	-- Unary:loadOrigin: (7)last
	-- AdjustOrigin: 0
	-- on : 7
	rpushg 2 origin
	rpushg 3 origin
	rpushg 2 origin
	rpushg 3 origin
	rpushg 1 origin
	rpushg 4 origin
	rpushg 1 origin
	-- Invocation:loadOrigin:scan: (0):= (10)none
	-- Binary:loadArgs: 
	-- ObjectGenerator:gen: super: (10)none:IS-empty: staticOff: 0
	-- Invocation:gen: (10)none
	-- Invocation:loadOrigin: (10)none
	-- Invocation:loadOrigin:scan: (10)none
	-- Unary:pushThis: 
	-- Unary:loadOrigin: (10)none
	-- Unary:loadArgs: 
	-- Unary:invoke: 
	-- pattern:load: none
	pushNone
	-- Binary:invoke: 
	-- pattern:load: := (2)V: ? (2)Object
	rswap
	rstoreg 3 last
 L494:
	rtnEventQ 0
	setThisStack 
	pushThis 
	rtn(D)
	end 1

	class main 685
	pushThis 
	invoke 1 0 BETAworld
	stop
	end 0

	class EventProcessor 686
	stop

	class ThreadStub 687
	DO:
	mvStack 
	call(D)ThreadStub
	stop
	-- vdtAdd: inx=1 descInx=527
	-- vdtAdd: inx=1 descInx=554
	-- vdtAdd: inx=2 descInx=555
	-- vdtAdd: inx=1 descInx=556
	-- vdtAdd: inx=2 descInx=557
	-- vdtAdd: inx=1 descInx=558
	-- vdtAdd: inx=2 descInx=559
	-- vdtAdd: inx=1 descInx=560
	-- vdtAdd: inx=2 descInx=561
	-- vdtAdd: inx=1 descInx=563
	-- vdtAdd: inx=1 descInx=538
	-- vdtAdd: inx=1 descInx=539
	-- vdtAdd: inx=1 descInx=569
	-- vdtAdd: inx=2 descInx=570
	-- vdtAdd: inx=1 descInx=571
	-- vdtAdd: inx=2 descInx=572
	-- vdtAdd: inx=1 descInx=536
	-- vdtAdd: inx=1 descInx=537
	-- vdtAdd: inx=1 descInx=541
	-- vdtAdd: inx=1 descInx=545
	-- vdtAdd: inx=2 descInx=546
	-- vdtAdd: inx=1 descInx=549
	-- vdtAdd: inx=2 descInx=550
	-- vdtAdd: inx=1 descInx=551
	-- vdtAdd: inx=2 descInx=552
	-- vdtAdd: inx=1 descInx=658
	-- vdtAdd: inx=2 descInx=659
	-- vdtAdd: inx=1 descInx=664
	-- vdtAdd: inx=2 descInx=665
	-- vdtAdd: inx=1 descInx=660
	-- vdtAdd: inx=2 descInx=662
	-- vdtAdd: inx=1 descInx=543
	-- vdtAdd: inx=2 descInx=544
	-- vdtAdd: inx=1 descInx=680
	-- vdtAdd: inx=2 descInx=681
	-- vdtAdd: inx=1 descInx=682
	-- vdtAdd: inx=2 descInx=683

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
25:	invoke 222 4 1
31:	rpop 
32:	rtnEventQ 0
doE: 
34:	mvStack
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class (0)BETA 3 1
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
19:	invoke 524 0 1
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
29:	invoke 525 0 1
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
84:	invoke 526 0 1
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


Class (0)LIB 71 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 72 2 1
13:	rpop 
14:	pushthis 
15:	invoke 160 3 1
21:	rpop 
22:	pushthis 
23:	invoke 73 4 1
29:	rpop 
30:	pushthis 
31:	invoke 165 5 1
37:	rpop 
38:	pushthis 
39:	invoke 190 6 1
45:	rpop 
46:	pushthis 
47:	invoke 197 7 1
53:	rpop 
54:	pushthis 
55:	invoke 89 9 1
61:	rpop 
62:	rtnEventQ 0
doE: 
64:	mvStack
65:	rtnEventQ 0
67:	setThisStack
68:	pushthis 
69:	rtn D


Class (0)BasicSystem 72 1
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


Class (0)Containers 73 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 74 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class (0)mQueue 74 1
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


Class Queue 75 1
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


Class Element 76 1
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


Class scan 77 1
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
22:	invoke 78 0 1
28:	rpop 
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class do 78 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 79 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


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
15:	rpushg 3
17:	pushNone 
18:	57
19:	jmpFalse 30
22:	pushthis 
23:	invoke 528 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class scanFromLast 80 1
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
22:	invoke 81 0 1
28:	rpop 
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class do 81 1
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
10:	pushthis 
11:	rpushg 1
13:	rpushg 1
15:	rpushg 3
17:	pushNone 
18:	57
19:	jmpFalse 30
22:	pushthis 
23:	invoke 529 0 1
29:	rpop 
30:	rtnEventQ 0
32:	setThisStack
33:	pushthis 
34:	rtn D


Class insert 83 1
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
28:	invoke 530 0 1
34:	rpop 
35:	rtnEventQ 0
37:	setThisStack
38:	pushthis 
39:	rtn D


Class remove 84 1
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
14:	invoke 85 0 1
20:	rpop 
21:	rtnEventQ 0
23:	setThisStack
24:	pushthis 
25:	rtn D


Class scan#S#85 85 4
allocE:
1:	rstore 4
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 4
8:	rpushg 1
10:	toSuper 77
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
29:	invoke 532 0 1
35:	rpop 
36:	rtnInner


Class removeNext 86 1
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
21:	invoke 534 0 1
27:	rpop 
28:	rtnEventQ 0
30:	setThisStack
31:	pushthis 
32:	rpushg 2
34:	rtn D


Class isEmpty 87 1
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


Class clear 88 1
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


Class (0)String 89 1
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
36:	allocIndexed 52 1
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
25:	toSuper 63
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
31:	toSuper 63
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
27:	toSuper 63
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
27:	toSuper 63
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
43:	invoke 540 0 1
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
31:	toSuper 63
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
39:	pushthis 
40:	pushg 2
42:	storeg 1
44:	pushthis 
45:	invoke 111 0 1
51:	rpop 
52:	pushthis 
53:	invoke 107 0 1
59:	rpop 
60:	rtnEventQ 0
62:	setThisStack
63:	pushthis 
64:	rtn D


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
22:	rtnEventQ 0
doE: 
24:	mvStack
25:	rtnEventQ 0
27:	setThisStack
28:	pushthis 
29:	rtn D


Class loop 108 1
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
80:	invoke 542 0 1
86:	rpop 
87:	rtnEventQ 0
89:	setThisStack
90:	pushthis 
91:	rtn D


Class doit 109 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 110 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#110 110 3
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


Class BasicSystem 112 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushc 4
8:	pushthis 
9:	storeg 1
11:	pushthis 
12:	invoke 129 2 1
18:	rpop 
19:	pushthis 
20:	invoke 131 3 1
26:	rpop 
27:	pushthis 
28:	invoke 134 4 1
34:	rpop 
35:	pushthis 
36:	invoke 142 5 1
42:	rpop 
43:	pushthis 
44:	invoke 113 6 1
50:	rpop 
51:	pushthis 
52:	invoke 156 7 1
58:	rpop 
59:	innera 1
61:	rtnEventQ 1
doE: 
63:	doEventQ 
64:	mvStack
65:	pushthis 
66:	invoke 159 0 0
72:	rpop 
73:	inner 1
75:	pushthis 
76:	rpushg 2
78:	invoke 130 0 0
84:	rpop 
85:	rtnEventQ 0
87:	setThisStack
88:	pushthis 
89:	rtn D


Class Lock 113 1
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


Class init 114 1
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


Class get 115 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 116 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 116 1
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
48:	invoke 547 0 1
54:	rpop 
55:	rtnEventQ 0
57:	setThisStack
58:	pushthis 
59:	rtn D


Class free 117 1
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


Class BasicProcess 118 1
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


Class start 119 1
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


Class Scheduler 120 1
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
17:	invoke 136 0 0
23:	rpop 
24:	pushthis 
25:	invoke 121 0 1
31:	rpop 
32:	rtnEventQ 0
34:	setThisStack
35:	pushthis 
36:	rtn D


Class do 121 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 122 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 122 1
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
33:	invoke 146 0 0
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
55:	invoke 548 0 1
61:	rpop 
62:	pushthis 
63:	invoke 123 0 1
69:	rpop 
70:	rtnEventQ 0
72:	setThisStack
73:	pushthis 
74:	rtn D


Class %if%then%%else%#S#123 123 3
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
29:	invoke 149 0 0
35:	toSuper 60
enterE: 
38:	rtnInner
doE: 
39:	mvStack
40:	rtnInner


Class Core 124 1
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
13:	invoke 126 0 1
19:	rpop 
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class attach 125 1
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


Class do 126 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 127 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loopX 127 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 128 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#128 128 3
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


Class cores 129 1
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


Class init 130 1
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
18:	invoke 124 0 0
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
42:	invoke 124 0 0
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
66:	invoke 124 0 0
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
90:	invoke 124 0 0
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
112:	invoke 120 0 0
118:	rswap 
119:	rstoreg 2
121:	pushthis 
122:	rpushg 1
124:	rpushg 2
126:	pushthis 
127:	rpushg 2
129:	invoke 125 0 0
135:	rpop 
136:	pushthis 
137:	pushthis 
138:	rpushg 1
140:	rpushg 1
142:	invoke 120 0 0
148:	rswap 
149:	rstoreg 2
151:	pushthis 
152:	rpushg 1
154:	rpushg 3
156:	pushthis 
157:	rpushg 2
159:	invoke 125 0 0
165:	rpop 
166:	pushthis 
167:	pushthis 
168:	rpushg 1
170:	rpushg 1
172:	invoke 120 0 0
178:	rswap 
179:	rstoreg 2
181:	pushthis 
182:	rpushg 1
184:	rpushg 4
186:	pushthis 
187:	rpushg 2
189:	invoke 125 0 0
195:	rpop 
196:	pushthis 
197:	rpushg 1
199:	rpushg 5
201:	pushthis 
202:	rpushg 1
204:	rpushg 1
206:	invoke 120 0 0
212:	invoke 125 0 0
218:	rpop 
219:	rtnEventQ 0
221:	setThisStack
222:	pushthis 
223:	rtn D


Class P_status 131 1
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


Class ProcessQueue 132 1
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
18:	rpushg 2
20:	toSuper 75
enterE: 
23:	rtnInner
doE: 
24:	mvStack
25:	rtnInner


Class display 133 1
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


Class sch 134 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 113 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class entry 135 1
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
17:	invoke 115 0 1
23:	rpop 
24:	pushthis 
25:	innerP 1
27:	popThisObj
28:	pushthis 
29:	rpushg 1
31:	rpushg 2
33:	invoke 117 0 0
39:	rpop 
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class add 136 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 137 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class entry#S#137 137 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 135
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


Class dcr 138 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 139 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class entry#S#139 139 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 135
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


Class running 140 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 141 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class entry#S#141 141 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 135
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


Class SQS 142 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 132 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 113 3 1
25:	rpop 
26:	rtnEventQ 0
doE: 
28:	mvStack
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class entry 143 1
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
17:	invoke 115 0 1
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
49:	invoke 553 0 1
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
76:	invoke 117 0 0
82:	rpop 
83:	rtnEventQ 0
85:	setThisStack
86:	pushthis 
87:	rtn D


Class init 144 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 143
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


Class insert 145 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 143
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
25:	invoke 83 0 0
31:	rpop 
32:	rtnInner


Class removeNext 146 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 147 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rpushg 2
24:	rtn D


Class entry#S#147 147 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 143
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
26:	invoke 86 0 0
32:	rswap 
33:	rstoreg 2
35:	rtnInner


Class remove 148 1
allocE:
1:	pushthis 
2:	rstoreg 2
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 143
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
25:	invoke 84 0 0
31:	rpop 
32:	rtnInner


Class isEmpty 149 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 150 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class entry#S#150 150 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	rpushg 1
10:	toSuper 143
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
26:	invoke 87 0 0
32:	storeg 1
34:	rtnInner


Class display 151 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 143
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 1
17:	rpushg 2
19:	invoke 133 0 0
25:	rpop 
26:	rtnInner


Class addWaiting 152 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 143
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


Class dcrWaiting 153 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 143
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


Class hasWaiting 154 1
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
10:	toSuper 143
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


Class console 156 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 113 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 157 1
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
15:	invoke 115 0 1
21:	rpop 
22:	pushthis 
23:	rpushg 1
25:	rpushg 2
27:	invoke 114 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 2
39:	invoke 117 0 0
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class display 158 1
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
17:	invoke 115 0 1
23:	rpop 
24:	inner 1
26:	pushthis 
27:	rpushg 1
29:	rpushg 2
31:	invoke 117 0 0
37:	rpop 
38:	rtnEventQ 0
40:	setThisStack
41:	pushthis 
42:	rtn D


Class init 159 1
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
15:	invoke 144 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class (0)Complex 160 1
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


Class Complex 161 1
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


Class + 162 1
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
41:	invoke 161 0 1
47:	rswap 
48:	rstoreg 3
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rpushg 3
56:	rtn D


Class - 163 1
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
41:	invoke 161 0 1
47:	rswap 
48:	rstoreg 3
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rpushg 3
56:	rtn D


Class display 164 1
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


Class (0)EMC2array 165 1
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


Class Array 166 1
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


Class put 167 1
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
29:	invoke 168 0 1
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


Class %if%then%%else%#S#168 168 3
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


Class get 169 1
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
26:	invoke 170 0 1
32:	rpop 
33:	rtnEventQ 0
35:	setThisStack
36:	pushthis 
37:	pushg 1
39:	rtn D


Class %if%then%%else%#S#170 170 3
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


Class nxt 171 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 172 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	pushg 1
24:	rtn D


Class %if%then%%else%#S#172 172 3
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


Class prv 173 1
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


Class %if%then%%else%#S#174 174 3
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


Class forAll 175 1
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
20:	invoke 176 0 0
26:	rpop 
27:	rtnEventQ 0
29:	setThisStack
30:	pushthis 
31:	rtn D


Class loop 176 1
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
73:	invoke 562 0 1
79:	rpop 
80:	rtnEventQ 0
82:	setThisStack
83:	pushthis 
84:	rtn D


Class print 177 1
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
14:	invoke 100 0 0
20:	rpop 
21:	pushthis 
22:	innerP 1
24:	popThisObj
25:	pushText 8
27:	invoke 100 0 0
33:	rpop 
34:	pushthis 
35:	invoke 178 0 1
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


Class %for%to%%do%#S#178 178 2
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


Class Range 179 1
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
39:	invoke 565 0 1
45:	rpop 
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class check 180 1
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
36:	invoke 564 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class print 181 1
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


Class D1_Array 182 1
allocE:
1:	pushthis 
2:	rstoreg 3
4:	rstore 1
6:	allocEventQ 0
8:	pushthis 
9:	rpushg 1
11:	toSuper 166
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


Class putAt 183 1
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
24:	invoke 180 0 0
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


Class getAt 184 1
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
21:	invoke 180 0 0
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


Class print 185 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 177
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 2
17:	rpushg 3
19:	invoke 181 0 0
25:	rpop 
26:	rtnInner


Class D2_Array 186 1
allocE:
1:	pushthis 
2:	rstoreg 4
4:	pushthis 
5:	rstoreg 3
7:	rstore 1
9:	allocEventQ 0
11:	pushthis 
12:	rpushg 1
14:	toSuper 166
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
55:	invoke 100 0 0
61:	rpop 
62:	rtnInner


Class putAt 187 1
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
27:	invoke 180 0 0
33:	rpop 
34:	pushthis 
35:	rpushg 1
37:	rpushg 4
39:	pushthis 
40:	pushg 2
42:	invoke 180 0 0
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


Class getAt 188 1
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
24:	invoke 180 0 0
30:	rpop 
31:	pushthis 
32:	rpushg 1
34:	rpushg 4
36:	pushthis 
37:	pushg 2
39:	invoke 180 0 0
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


Class print 189 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 177
enterE: 
11:	rtnInner
doE: 
12:	doEventQ 
13:	mvStack
14:	pushthis 
15:	rpushg 2
17:	rpushg 3
19:	invoke 181 0 0
25:	rpop 
26:	pushText 15
28:	invoke 100 0 0
34:	rpop 
35:	pushthis 
36:	rpushg 2
38:	rpushg 4
40:	invoke 181 0 0
46:	rpop 
47:	rtnInner


Class (0)ForkJoinSystem 190 1
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


Class ForkJoinSystem 191 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 112
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


Class ForkJoin 192 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 132 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 113 3 1
25:	rpop 
26:	innera 1
28:	rtnEventQ 1
doE: 
30:	doEventQ 
31:	mvStack
32:	pushthis 
33:	rpushg 3
35:	invoke 114 0 0
41:	rpop 
42:	pushthis 
43:	innerP 1
45:	popThisObj
46:	pushthis 
47:	invoke 194 0 1
53:	rpop 
54:	rtnEventQ 0
56:	setThisStack
57:	pushthis 
58:	rtn D


Class run 193 1
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
18:	invoke 115 0 1
24:	rpop 
25:	pushthis 
26:	rpushg 1
28:	rpushg 2
30:	pushthis 
31:	rpushg 2
33:	invoke 83 0 0
39:	rpop 
40:	pushthis 
41:	rpushg 1
43:	rpushg 1
45:	rpushg 5
47:	pushthis 
48:	rpushg 2
50:	invoke 145 0 0
56:	rpop 
57:	pushthis 
58:	rpushg 1
60:	rpushg 3
62:	invoke 117 0 0
68:	rpop 
69:	rtnEventQ 0
71:	setThisStack
72:	pushthis 
73:	rtn D


Class AwaitTermination 194 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 195 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class loop 195 1
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
35:	invoke 196 0 1
41:	rpop 
42:	pushthis 
43:	pushg 1
45:	jmpFalse 56
48:	pushthis 
49:	invoke 568 0 1
55:	rpop 
56:	pushthis 
57:	rpushg 1
59:	rpushg 1
61:	rpushg 2
63:	invoke 88 0 0
69:	rpop 
70:	rtnEventQ 0
72:	setThisStack
73:	pushthis 
74:	rtn D


Class scan#S#196 196 4
allocE:
1:	rstore 4
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 4
8:	rpushg 1
10:	rpushg 1
12:	rpushg 2
14:	toSuper 77
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
54:	invoke 567 0 1
60:	rpop 
61:	rtnInner


Class (0)MonitorSystem 197 1
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


Class System 198 8
allocE:
1:	rstore 8
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 8
8:	rpushg 1
10:	rpushg 1
12:	rpushg 3
14:	rpushg 2
16:	toSuper 112
enterE: 
19:	innera 2
21:	rtnInner
doE: 
22:	doEventQ 
23:	mvStack
24:	inner 2
26:	rtnInner


Class Semaphore 199 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 113 2 1
15:	rpop 
16:	pushthis 
17:	rpushg 1
19:	invoke 132 3 1
25:	rpop 
26:	rtnEventQ 0
doE: 
28:	mvStack
29:	rtnEventQ 0
31:	setThisStack
32:	pushthis 
33:	rtn D


Class init 200 1
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


Class wait 201 1
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
15:	invoke 115 0 1
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
36:	invoke 202 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#202 202 3
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


Class signal 203 1
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
15:	invoke 115 0 1
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
36:	invoke 204 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#204 204 3
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


Class Process 205 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	toSuper 118
enterE: 
11:	innera 3
13:	rtnInner
doE: 
14:	doEventQ 
15:	mvStack
16:	inner 3
18:	rtnInner


Class start 206 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 2
8:	toSuper 119
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
23:	invoke 100 0 0
29:	rpop 
30:	pushthis 
31:	rpushg 2
33:	rpushg 2
35:	invoke 100 0 0
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
68:	invoke 145 0 0
74:	rpop 
75:	rtnInner


Class Monitor 207 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	rpushg 1
9:	invoke 199 2 1
15:	rpop 
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class init 208 1
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
15:	invoke 200 0 0
21:	rpop 
22:	rtnEventQ 0
24:	setThisStack
25:	pushthis 
26:	rtn D


Class entry 209 1
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
17:	invoke 201 0 0
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
44:	invoke 203 0 0
50:	rpop 
51:	rtnEventQ 0
53:	setThisStack
54:	pushthis 
55:	rtn D


Class wait 210 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 211 2 1
13:	rpop 
14:	innera 1
16:	rtnEventQ 0
doE: 
18:	mvStack
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class loop 211 1
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
43:	invoke 573 0 1
49:	rpop 
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class (0)workspace 222 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 422 4 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class (0)demo 422 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 423 2 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class (0)ArrayDemos 423 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	mvStack
6:	pushthis 
7:	invoke 434 4 1
13:	rpop 
14:	rtnEventQ 0
doE: 
16:	mvStack
17:	rtnEventQ 0
19:	setThisStack
20:	pushthis 
21:	rtn D


Class (0)List 434 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 100 0 0
18:	rpop 
19:	pushthis 
20:	rpushg 1
22:	rpushg 1
24:	rpushg 1
26:	invoke 66 0 0
32:	rpop 
33:	pushthis 
34:	pushthis 
35:	invoke 626 0 1
41:	rswap 
42:	rstoreg 4
44:	pushthis 
45:	pushthis 
46:	pushthis 
47:	rpushg 1
49:	rpushg 1
51:	rpushg 1
53:	pushc 2
55:	pushc 0
57:	pushc 1
59:	allocIndexed 52 1
63:	invoke 440 0 0
69:	rswap 
70:	rstoreg 6
72:	pushthis 
73:	pushthis 
74:	pushthis 
75:	rpushg 1
77:	rpushg 1
79:	rpushg 1
81:	pushc 2
83:	pushc 0
85:	pushc 1
87:	allocIndexed 52 1
91:	invoke 440 0 0
97:	rswap 
98:	rstoreg 7
100:	pushthis 
101:	pushthis 
102:	pushthis 
103:	rpushg 6
105:	pushthis 
106:	rpushg 4
108:	invoke 438 0 0
114:	rswap 
115:	rstoreg 3
117:	pushText 20
119:	invoke 100 0 0
125:	rpop 
126:	pushthis 
127:	rpushg 1
129:	rpushg 1
131:	rpushg 1
133:	invoke 66 0 0
139:	rpop 
140:	pushthis 
141:	rpushg 6
143:	rpushg 2
145:	pushc 2
147:	pushc 1
149:	xstoreg 1
151:	pushthis 
152:	rpushg 6
154:	rpushg 2
156:	pushc 3
158:	pushc 2
160:	xstoreg 1
162:	pushthis 
163:	rpushg 7
165:	rpushg 2
167:	pushc 4
169:	pushc 1
171:	xstoreg 1
173:	pushthis 
174:	rpushg 7
176:	rpushg 2
178:	pushc 5
180:	pushc 2
182:	xstoreg 1
184:	pushthis 
185:	rpushg 1
187:	rpushg 1
189:	rpushg 1
191:	pushthis 
192:	rpushg 6
194:	rpushg 2
196:	pushc 1
198:	xpushg 1
200:	invoke 67 0 0
206:	rpop 
207:	pushthis 
208:	rpushg 1
210:	rpushg 1
212:	rpushg 1
214:	pushthis 
215:	rpushg 6
217:	rpushg 2
219:	pushc 2
221:	xpushg 1
223:	invoke 67 0 0
229:	rpop 
230:	pushthis 
231:	rpushg 1
233:	rpushg 1
235:	rpushg 1
237:	pushthis 
238:	rpushg 7
240:	rpushg 2
242:	pushc 1
244:	xpushg 1
246:	invoke 67 0 0
252:	rpop 
253:	pushthis 
254:	rpushg 1
256:	rpushg 1
258:	rpushg 1
260:	pushthis 
261:	rpushg 7
263:	rpushg 2
265:	pushc 2
267:	xpushg 1
269:	invoke 67 0 0
275:	rpop 
276:	pushthis 
277:	pushthis 
278:	pushthis 
279:	rpushg 6
281:	pushthis 
282:	pushthis 
283:	rpushg 7
285:	pushNone 
286:	invoke 438 0 0
292:	invoke 438 0 0
298:	rswap 
299:	rstoreg 2
301:	pushthis 
302:	pushthis 
303:	pushc 2
305:	pushthis 
306:	rpushg 2
308:	invoke 441 0 0
314:	rswap 
315:	rstoreg 8
317:	pushthis 
318:	pushthis 
319:	pushc 2
321:	pushthis 
322:	pushthis 
323:	rpushg 6
325:	pushthis 
326:	pushthis 
327:	rpushg 7
329:	pushthis 
330:	rpushg 3
332:	invoke 438 0 0
338:	invoke 438 0 0
344:	invoke 441 0 0
350:	rswap 
351:	rstoreg 8
353:	rtnEventQ 0
355:	setThisStack
356:	pushthis 
357:	rtn D


Class List 436 1
allocE:
1:	pushthis 
2:	rstoreg 3
4:	pushthis 
5:	rstoreg 2
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


Class empty 437 1
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


Class RangeList 438 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	pushthis 
6:	rpushg 1
8:	pushthis 
9:	rpushg 1
11:	rpushg 1
13:	invoke 440 0 0
19:	toSuper 436
enterE: 
22:	innera 2
24:	rtnInner
doE: 
25:	doEventQ 
26:	mvStack
27:	pushthis 
28:	innerP 2
30:	popThisObj
31:	rtnInner


Class Range 440 1
allocE:
1:	pushthis 
2:	rstoreg 2
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


Class testArray 441 1
allocE:
1:	pushthis 
2:	pushthis 
3:	storeg 1
5:	rstore 1
7:	allocEventQ 0
9:	mvStack
10:	innera 1
12:	rtnEventQ 1
doE: 
14:	doEventQ 
15:	mvStack
16:	pushthis 
17:	innerP 1
19:	popThisObj
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class #S#524 524 1
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


Class #S#525 525 1
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


Class #S#526 526 1
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


Class body#SB#527 527 2
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


Class #S#528 528 1
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
62:	break 1 393
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class #S#529 529 1
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
62:	break 1 396
66:	rtnEventQ 0
68:	setThisStack
69:	pushthis 
70:	rtn D


Class #S#530 530 1
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
23:	invoke 76 0 0
29:	rswap 
30:	rstoreg 3
32:	pushthis 
33:	invoke 531 0 1
39:	rpop 
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class %if%then%%else%#S#531 531 3
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


Class #S#532 532 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushthis 
11:	invoke 533 0 1
17:	rpop 
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class %if%then%%else%#S#533 533 3
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


Class #S#534 534 1
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
43:	invoke 535 0 1
49:	rpop 
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class %if%then%%else%#S#535 535 3
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


Class body#SB#536 536 2
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


Class body#SB#537 537 2
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


Class body#SB#538 538 2
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


Class body#SB#539 539 2
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


Class #S#540 540 1
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


Class body#SB#541 541 2
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
75:	invoke 666 0 1
81:	rpop 
82:	rtnEventQ 0
84:	setThisStack
85:	pushthis 
86:	rtn D


Class #S#542 542 1
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
30:	break 1 427
34:	rtnEventQ 0
36:	setThisStack
37:	pushthis 
38:	rtn D


Class thenPart#SB#543 543 2
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
46:	break 3 379
50:	rtnEventQ 0
52:	setThisStack
53:	pushthis 
54:	rtn D


Class elsePart#SB#544 544 2
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
42:	break 3 379
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class thenPart#SB#545 545 2
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


Class elsePart#SB#546 546 2
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


Class #S#547 547 1
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
16:	break 1 303
20:	rtnEventQ 0
22:	setThisStack
23:	pushthis 
24:	rtn D


Class #S#548 548 1
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
100:	invoke 667 0 1
106:	rpop 
107:	rtnEventQ 0
109:	setThisStack
110:	pushthis 
111:	rtn D


Class thenPart#SB#549 549 2
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
23:	invoke 154 0 0
29:	jmpFalse 40
32:	pushthis 
33:	invoke 668 0 1
39:	rpop 
40:	pushthis 
41:	rpushg 2
43:	rpushg 3
45:	rpushg 1
47:	rpushg 1
49:	rpushg 1
51:	rpushg 4
53:	invoke 138 0 0
59:	rpop 
60:	pushthis 
61:	rpushg 2
63:	rpushg 3
65:	rpushg 1
67:	rpushg 1
69:	rpushg 1
71:	rpushg 4
73:	invoke 140 0 0
79:	jmpFalse 90
82:	pushthis 
83:	invoke 669 0 1
89:	rpop 
90:	rtnEventQ 0
92:	setThisStack
93:	pushthis 
94:	rtn D


Class elsePart#SB#550 550 2
allocE:
1:	rstore 2
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 2 306
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#551 551 2
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


Class elsePart#SB#552 552 2
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
14:	break 2 309
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class #S#553 553 1
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


Class thenPart#SB#554 554 2
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


Class elsePart#SB#555 555 2
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


Class thenPart#SB#556 556 2
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


Class elsePart#SB#557 557 2
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


Class thenPart#SB#558 558 2
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


Class elsePart#SB#559 559 2
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


Class thenPart#SB#560 560 2
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


Class elsePart#SB#561 561 2
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


Class #S#562 562 1
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


Class body#SB#563 563 2
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
46:	invoke 100 0 0
52:	rpop 
53:	rtnEventQ 0
55:	setThisStack
56:	pushthis 
57:	rtn D


Class #S#564 564 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 100 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#565 565 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	pushText 1
12:	invoke 100 0 0
18:	rpop 
19:	rtnEventQ 0
21:	setThisStack
22:	pushthis 
23:	rtn D


Class #S#567 567 1
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


Class #S#568 568 1
allocE:
1:	rstore 1
3:	allocEventQ 0
5:	mvStack
6:	rtnEventQ 1
doE: 
8:	doEventQ 
9:	mvStack
10:	break 1 356
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rtn D


Class thenPart#SB#569 569 2
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
42:	invoke 152 0 0
48:	rpop 
49:	pushthis 
50:	rpushg 2
52:	rpushg 3
54:	rpushg 1
56:	rpushg 3
58:	%prim thisCore 17
60:	rpushg 2
62:	rpushg 2
64:	invoke 83 0 0
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
94:	invoke 117 0 0
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


Class elsePart#SB#570 570 2
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
19:	invoke 117 0 0
25:	rpop 
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class thenPart#SB#571 571 2
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
24:	invoke 86 0 0
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
73:	invoke 145 0 0
79:	rpop 
80:	pushthis 
81:	rpushg 2
83:	rpushg 3
85:	rpushg 1
87:	rpushg 1
89:	rpushg 5
91:	invoke 153 0 0
97:	rpop 
98:	pushthis 
99:	rpushg 2
101:	rpushg 3
103:	rpushg 1
105:	rpushg 2
107:	invoke 117 0 0
113:	rpop 
114:	rtnEventQ 0
116:	setThisStack
117:	pushthis 
118:	rtn D


Class elsePart#SB#572 572 2
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
19:	invoke 117 0 0
25:	rpop 
26:	rtnEventQ 0
28:	setThisStack
29:	pushthis 
30:	rtn D


Class #S#573 573 1
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
19:	invoke 203 0 0
25:	rpop 
26:	pushthis 
27:	rpushg 1
29:	rpushg 1
31:	rpushg 1
33:	rpushg 2
35:	invoke 201 0 0
41:	rpop 
42:	break 1 363
46:	rtnEventQ 0
48:	setThisStack
49:	pushthis 
50:	rtn D


Class List#S#626 626 1
allocE:
1:	rstore 1
3:	allocEventQ 1
5:	pushthis 
6:	rpushg 1
8:	pushNone 
9:	pushNone 
10:	toSuper 436
enterE: 
13:	rtnInner
doE: 
14:	mvStack
15:	rtnInner


Class thenPart#SB#658 658 2
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


Class elsePart#SB#659 659 2
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


Class thenPart#SB#660 660 2
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
36:	invoke 661 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#661 661 3
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


Class elsePart#SB#662 662 2
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
36:	invoke 663 0 1
42:	rpop 
43:	rtnEventQ 0
45:	setThisStack
46:	pushthis 
47:	rtn D


Class %if%then%%else%#S#663 663 3
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


Class thenPart#SB#664 664 2
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


Class elsePart#SB#665 665 2
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


Class #S#666 666 1
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


Class #S#667 667 1
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
34:	invoke 145 0 0
40:	rpop 
41:	rtnEventQ 0
43:	setThisStack
44:	pushthis 
45:	rtn D


Class #S#668 668 1
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
14:	break 3 306
18:	rtnEventQ 0
20:	setThisStack
21:	pushthis 
22:	rtn D


Class #S#669 669 1
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
29:	invoke 136 0 0
35:	rpop 
36:	break 3 306
40:	rtnEventQ 0
42:	setThisStack
43:	pushthis 
44:	rtn D


Class thenPart#SB#680 680 2
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


Class elsePart#SB#681 681 2
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


Class thenPart#SB#682 682 2
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


Class elsePart#SB#683 683 2
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


Class main 685 0
allocE:
1:	pushthis 
2:	invoke 1 0 1
8:	stop 


Class EventProcessor 686 0
allocE:
1:	stop 


Class ThreadStub 687 0
allocE:
doE: 
1:	mvStack
2:	call D
4:	stop 

