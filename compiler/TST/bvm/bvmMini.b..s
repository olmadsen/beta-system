 -- init byte code: /home/olm/beta/r5.5/compiler/TST/bvm/bvmMini.bvm/home/o ...
 component /home/olm/beta/r5.5/compiler/TST/bvm/bvmMini.b..s NoOfDescs: 10
 -- classDef: bvmMiniformId: betaenv descNo: 1 

class bvmMini 1 1 0
 -- classDef:store:origin:
 rstore 1 origin
 mvStack 
 -- desclareField: AAA off: 12
 -- fields.new: "F12" "AAA" "int32" c
 -- desclareField: BBB off: 16
 -- fields.new: "F16" "BBB" "int32" c
 -- genfield:partObj: 
 -- desclareField: X off: 24
 -- fields.new: "F24" "X" "class ['bvmMini']'Fisk'" p
 -- desclareField: w off: 44
 -- fields.new: "F44" "w" "int32" c
 -- desclareField: classField? off: 0
 -- fields.new: "F0" "classField?" "" C
 -- genSuper:before:constructorDef:class ['Object']'Object'
 -- objectSig:no:constructorDef!
 -- genSuperDo:no default super:
 -- before:storeOrigin:B:
 -- genlib_alloc:alloc:staticObj:
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- sytnthlibbody:genAdr: Fisk
 -- sytnthlibbody:genAdr:nameApl: Fisk
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- signaturebody:newInstance:Fisk
 -- doLoadProtoAndAlloc: 13
 -- byteCode_callPrimNo: 1 arg: 85
 -- EmitPrimNo: 1 arg: 85
 -- prim:new:
 invoke new 85 0 1
 -- genlib_alloc:before:asgRefReg: X off: 24
 -- byteCode_doAsgRegAdr:  off: 24
 -- storeRef: X class: class ['bvmMini']'Fisk'
 rstore 24 X
 -- before:endMethod:X
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- genDoMethod:genPtnMethod:before:methodDef: bvmMini descNo: 1
 -- sig.thisMethodDesc:descNo: 1
 -- MethodDef: "bvmMini$cons"  noOfEnterArgs:1  type:1 =vclass descNo: 6 
 --  signature: "static void 'bvmMini'(class ['bvmMini']'BetaObject')" 

class bvmMini$cons 6 1 0
 -- genPtnMethod:KUK:A:
 -- genPtnMethod:KUK:Y:
 -- orgDesc: null
 -- newInstance: org: Object consSig: class ['Object']'Object' descNo: 
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- signaturebody:newInstance:bvmMini
 -- doLoadProtoAndAlloc: 1
 -- byteCode_callPrimNo: 1 arg: 1
 -- EmitPrimNo: 1 arg: 1
 -- prim:new:
 invoke new 1 0 1
 -- genPtnMethod:koks:
 -- callNDX: gJsr, method: Do descNo: 1
 -- void class ['bvmMini']'bvmMini'::'Do'()
 -- byteCode_textOperand_out: "3 bvmMini$Do" 
 -- byteCode_gJsr:doBody:"3 bvmMini$Do" name:""  NDX:D,sig:"3 bvmMini$Do" , ...falsem ..."" 
 invoke bvmMini$Do 3 0 1
 -- genPtnMethod:before:endMethod:D descNo/dn: 6
 -- end-of-mainmethod:
 stop
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- before:genNDX:bvmMini
 -- genDoMethod:before:methodDef; Do innerName: Inner_1
 -- MethodDef: "bvmMini$Do"  noOfEnterArgs:0  type:0 =ptn descNo: 3 
 --  signature: "void 'Do'()" 

class bvmMini$inner_1 4 1 0
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0

class bvmMini$Do 3 1 0
 rstore 1 origin
 mvStack 
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: '!' -> put label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: put
 -- cProcDesc:C: 
 -- asgToCproc:Super: 
 -- bytecodeval:asgToCproc: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: '!'
 -- ExpEval:A: 110 '!' evalKind: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- bytecodeval:asgToCproc:X:
 -- asgToCproc:Super: 
 -- textVal:asgToCproc:C:
 pushc 33
 %put 2
 -- bytecodeval:asgToCproc:Y:
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 117 -> AAA label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: AAA
 -- evbody:AsgToEval:simple: AAA
 -- sytnthlibbody:genAdr: AAA
 -- sytnthlibbody:genAdr:nameApl: AAA
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 117
 -- ExpEval:A: 111 117 evalKind: 
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 pushc 117
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: AAA off:12  ON:0 
 storeg 12 AAA
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 10 -> BBB label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: BBB
 -- evbody:AsgToEval:simple: BBB
 -- sytnthlibbody:genAdr: BBB
 -- sytnthlibbody:genAdr:nameApl: BBB
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 10
 -- ExpEval:A: 111 10 evalKind: 
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 pushc 10
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: BBB off:16  ON:0 
 storeg 16 BBB
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: AAA + BBB -> BBB label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: BBB
 -- evbody:AsgToEval:simple: BBB
 -- sytnthlibbody:genAdr: BBB
 -- sytnthlibbody:genAdr:nameApl: BBB
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: AAA + BBB
 -- ExpEval:A: 89 AAA + BBB evalKind: 
 -- ExpEval:A: 61 AAA evalKind: 
 -- sytnthlibbody:genAdr: AAA
 -- sytnthlibbody:genAdr:nameApl: AAA
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: AAA on:0
 -- address:load: AAA off:12  ON:0 
 pushg 12 AAA
 -- ExpEval:A: 61 BBB evalKind: 
 -- sytnthlibbody:genAdr: BBB
 -- sytnthlibbody:genAdr:nameApl: BBB
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: BBB on:0
 -- address:load: BBB off:16  ON:0 
 pushg 16 BBB
 plus
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: BBB off:16  ON:0 
 storeg 16 BBB
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: fooBar label: 61 55
 -- mkByteCodeCall:A:
 -- bytecodevalbody:mkByteCodeCall:before:genOrgAdrToOrgReg: 
 -- genOrgAdrToOrgReg:before:mch.ldVal:B:
 -- sytnthlibbody:genAdr: fooBar
 -- sytnthlibbody:genAdr:nameApl: fooBar
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- KOKS:A:before:inner:
 -- KOKS:A:after:inner:
 -- bytecodevalbody:mkByteCodecall: betaenv descNo: 12
 -- class: void class ['bvmMini']'bvmMini'::'fooBar'()
 -- class: bvmMini$fooBar
 -- byteCode_textOperand_out: "83 bvmMini$fooBar" 
 -- byteCode_gJsr:doBody:"83 bvmMini$fooBar" name:""  NDX:M,sig:"83 bvmMini ..." , ...falsem ..."" 
 invoke bvmMini$fooBar 83 0 1
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: X label: 61 55
 -- sytnthlibbody:genAdr: X
 -- sytnthlibbody:genAdr:nameApl: X
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_loadRef: 
 -- mstate_loadRef: off: 24
 rpushg 24 X
 -- synthlibbody_body:callEntry:before:gjsr:A: void class ['bvmMini']'Fisk' ...
 -- byteCode_textOperand_out: "87Fisk$Do" 
 -- byteCode_gJsr:doBody:"87Fisk$Do" name:""  NDX:M,sig:"87Fisk$Do" ,isStat ...falsem ..."" 
 invoke Fisk$Do 87 0 1
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 55 -> X.add -> w label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: w
 -- evbody:AsgToEval:simple: w
 -- sytnthlibbody:genAdr: w
 -- sytnthlibbody:genAdr:nameApl: w
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 55 -> X.add
 -- ExpEval:A: 55 55 -> X.add evalKind: 
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: X.add
 -- KUK:C:
 -- bytecodevalbody:mkByteCodeCall:before:genOrgAdrToOrgReg: 
 -- genOrgAdrToOrgReg:before:mch.ldVal:B:
 -- sytnthlibbody:genAdr: X.add
 -- HEST:D: 
 -- sytnthlibbody:genAdr: X
 -- sytnthlibbody:genAdr:nameApl: X
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- HEST:A: 
 -- HEST:G: 
 -- bytecode_loadRef: 
 -- mstate_loadRef: off: 24
 rpushg 24 X
 -- HEST:H: 
 -- KOKS:A:before:inner:
 -- evbody:insert:mkByteCodeCall:inner:
 -- bytecodeval_methodArgs_asgToMethod: 
 -- FISK:B: 
 -- ExpEval:A: 111 55 evalKind: 
 -- FISK:C: 
 pushc 55
 -- FISK:D: 
 -- KOKS:A:after:inner:
 -- bytecodevalbody:mkByteCodecall: betaenv descNo: 14
 -- class: int32 class ['bvmMini']'Fisk'::'add'(int32)
 -- class: Fisk$add
 -- byteCode_textOperand_out: "97 Fisk$add" 
 -- byteCode_gJsr:doBody:"97 Fisk$add" name:""  NDX:M,sig:"97 Fisk$add" ,is ...falsem ..."" 
 invoke Fisk$add 97 0 1
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: w off:44  ON:0 
 storeg 44 w
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 'E' -> put label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: put
 -- cProcDesc:C: 
 -- asgToCproc:Super: 
 -- bytecodeval:asgToCproc: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 'E'
 -- ExpEval:A: 110 'E' evalKind: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- bytecodeval:asgToCproc:X:
 -- asgToCproc:Super: 
 -- textVal:asgToCproc:C:
 pushc 69
 %put 2
 -- bytecodeval:asgToCproc:Y:
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: w -> put label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: put
 -- cProcDesc:C: 
 -- asgToCproc:Super: 
 -- bytecodeval:asgToCproc: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: w
 -- ExpEval:A: 61 w evalKind: 
 -- sytnthlibbody:genAdr: w
 -- sytnthlibbody:genAdr:nameApl: w
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'bvmMini'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: w on:0
 -- address:load: w off:44  ON:0 
 pushg 44 w
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- bytecodeval:asgToCproc:X:
 -- asgToCproc:Super: 
 -- computedVal:asgToCproc:2 isBVM
 -- computedVal:asgToCproc:B:
 %put 2
 -- computedVal:asgToCproc:C:
 -- bytecodeval:asgToCproc:Y:
 -- genDoMethod:before:endMethod:J
 rtnEventQ 0
 setThisStack 
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:2 rTop:10 rTopMax:10
 -- genDoMethod:genPtnMethod:before:methodDef: putText descNo: 3
 -- sig.thisMethodDesc:descNo: 3
 -- MethodDef: "putText$cons"  noOfEnterArgs:1  type:1 =vclass descNo: 20 
 --  signature: "void 'putText'(char[])" 

class putText$cons 20 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- genPtnMethod:KUK:B:
 -- genPtnMethod:newInstanceWithOrigin:X:
 -- genPtnMethod:newInstanceWithOrigin:
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- byteCode_callPrimNo: -2 arg: thisObjHack
 -- EmitPrimNo: -2 arg: thisObjHack
 rpushg 1 TheObj
 -- signaturebody:newInstance:putText
 -- doLoadProtoAndAlloc: 3
 -- byteCode_callPrimNo: 1 arg: 15
 -- EmitPrimNo: 1 arg: 15
 -- prim:new:
 invoke new 15 0 1
 -- genPtnMethod:koks:
 -- bytecode_ldValImpl: Enter on:0
 -- mstate_loadRef: off: 12
 rpushg 12 Enter
 -- genPtnMethod:before:enter:callNDX: void 'putText'(char[])
 -- callNDX: gJsr, method: Enter descNo: 3
 -- void class ['bvmMini']'putText'::'Enter'(char[])
 -- byteCode_textOperand_out: "16 putText$Enter" 
 -- byteCode_gJsr:doBody:"16 putText$Enter" name:""  NDX:N,sig:"16 putText$ ..." , ...falsem ..."" 
 invoke putText$Enter 16 0 1
 -- callNDX: gJsr, method: Do descNo: 3
 -- void class ['bvmMini']'putText'::'Do'()
 -- byteCode_textOperand_out: "17 putText$Do" 
 -- byteCode_gJsr:doBody:"17 putText$Do" name:""  NDX:D,sig:"17 putText$Do" , ...falsem ..."" 
 invoke putText$Do 17 0 1
 -- genPtnMethod:before:endMethod:D descNo/dn: 20
 rtnEventQ 0
 setThisStack 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- genDoMethod:genPtnClass:before:methodDef; putText descNo: 3
 -- MethodDef: "putText$PClass"  noOfEnterArgs:0  type:1 =vclass descNo: 21 
 --  signature: "class ['bvmMini']'putText' 'new$putText'()" 

class putText$PClass 21 1 0
 rstore 1 origin
 mvStack 
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- signaturebody:newInstance:putText
 -- doLoadProtoAndAlloc: 3
 -- byteCode_callPrimNo: 1 arg: 15
 -- EmitPrimNo: 1 arg: 15
 -- prim:new:
 invoke new 15 0 1
 -- before:endMethod:E
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- genDoMethod:genPtnMethod:before:methodDef: text descNo: 4
 -- sig.thisMethodDesc:descNo: 4
 -- MethodDef: "text$cons"  noOfEnterArgs:1  type:1 =vclass descNo: 27 
 --  signature: "char[] 'text'(char[])" 

class text$cons 27 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- genPtnMethod:KUK:B:
 -- genPtnMethod:newInstanceWithOrigin:X:
 -- genPtnMethod:newInstanceWithOrigin:
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- byteCode_callPrimNo: -2 arg: thisObjHack
 -- EmitPrimNo: -2 arg: thisObjHack
 rpushg 1 TheObj
 -- signaturebody:newInstance:text
 -- doLoadProtoAndAlloc: 4
 -- byteCode_callPrimNo: 1 arg: 22
 -- EmitPrimNo: 1 arg: 22
 -- prim:new:
 invoke new 22 0 1
 -- genPtnMethod:koks:
 -- bytecode_ldValImpl: Enter on:0
 -- mstate_loadRef: off: 12
 rpushg 12 Enter
 -- genPtnMethod:before:enter:callNDX: char[] 'text'(char[])
 -- callNDX: gJsr, method: Enter descNo: 4
 -- void class ['bvmMini']'text'::'Enter'(char[])
 -- byteCode_textOperand_out: "23 text$Enter" 
 -- byteCode_gJsr:doBody:"23 text$Enter" name:""  NDX:N,sig:"23 text$Enter" , ...falsem ..."" 
 invoke text$Enter 23 0 1
 -- callNDX: gJsr, method: Exit descNo: 4
 -- char[] class ['bvmMini']'text'::'Exit'()
 -- byteCode_textOperand_out: "26 text$Exit" 
 -- byteCode_gJsr:doBody:"26 text$Exit" name:""  NDX:X,sig:"26 text$Exit" , ...falsem ..."" 
 invoke text$Exit 26 0 1
 -- genPtnMethod:before:endMethod:D descNo/dn: 27
 rtnEventQ 0
 setThisStack 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- genDoMethod:genPtnClass:before:methodDef; text descNo: 4
 -- MethodDef: "text$PClass"  noOfEnterArgs:0  type:1 =vclass descNo: 28 
 --  signature: "class ['bvmMini']'text' 'new$text'()" 

class text$PClass 28 1 0
 rstore 1 origin
 mvStack 
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- signaturebody:newInstance:text
 -- doLoadProtoAndAlloc: 4
 -- byteCode_callPrimNo: 1 arg: 22
 -- EmitPrimNo: 1 arg: 22
 -- prim:new:
 invoke new 22 0 1
 -- before:endMethod:E
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- genDoMethod:genPtnMethod:before:methodDef: fooBar descNo: 12
 -- sig.thisMethodDesc:descNo: 12
 -- MethodDef: "fooBar$cons"  noOfEnterArgs:0  type:1 =vclass descNo: 83 
 --  signature: "void 'fooBar'()" 

class fooBar$cons 83 1 0
 rstore 1 origin
 mvStack 
 -- genPtnMethod:KUK:B:
 -- genPtnMethod:newInstanceWithOrigin:X:
 -- genPtnMethod:newInstanceWithOrigin:
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- byteCode_callPrimNo: -2 arg: thisObjHack
 -- EmitPrimNo: -2 arg: thisObjHack
 rpushg 1 TheObj
 -- signaturebody:newInstance:fooBar
 -- doLoadProtoAndAlloc: 12
 -- byteCode_callPrimNo: 1 arg: 78
 -- EmitPrimNo: 1 arg: 78
 -- prim:new:
 invoke new 78 0 1
 -- genPtnMethod:koks:
 -- callNDX: gJsr, method: Do descNo: 12
 -- void class ['bvmMini']'fooBar'::'Do'()
 -- byteCode_textOperand_out: "80 fooBar$Do" 
 -- byteCode_gJsr:doBody:"80 fooBar$Do" name:""  NDX:D,sig:"80 fooBar$Do" , ...falsem ..."" 
 invoke fooBar$Do 80 0 1
 -- genPtnMethod:before:endMethod:D descNo/dn: 83
 rtnEventQ 0
 setThisStack 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- genDoMethod:genPtnClass:before:methodDef; fooBar descNo: 12
 -- MethodDef: "fooBar$PClass"  noOfEnterArgs:0  type:1 =vclass descNo: 84 
 --  signature: "class ['bvmMini']'fooBar' 'new$fooBar'()" 

class fooBar$PClass 84 1 0
 rstore 1 origin
 mvStack 
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- signaturebody:newInstance:fooBar
 -- doLoadProtoAndAlloc: 12
 -- byteCode_callPrimNo: 1 arg: 78
 -- EmitPrimNo: 1 arg: 78
 -- prim:new:
 invoke new 78 0 1
 -- before:endMethod:E
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- genDoMethod:genPtnMethod:before:methodDef: Fisk descNo: 13
 -- sig.thisMethodDesc:descNo: 13
 -- MethodDef: "Fisk$cons"  noOfEnterArgs:1  type:1 =vclass descNo: 90 
 --  signature: "void 'Fisk'(int32)" 

class Fisk$cons 90 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- genPtnMethod:KUK:B:
 -- genPtnMethod:newInstanceWithOrigin:X:
 -- genPtnMethod:newInstanceWithOrigin:
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- byteCode_callPrimNo: -2 arg: thisObjHack
 -- EmitPrimNo: -2 arg: thisObjHack
 rpushg 1 TheObj
 -- signaturebody:newInstance:Fisk
 -- doLoadProtoAndAlloc: 13
 -- byteCode_callPrimNo: 1 arg: 85
 -- EmitPrimNo: 1 arg: 85
 -- prim:new:
 invoke new 85 0 1
 -- genPtnMethod:koks:
 -- bytecode_ldValImpl: Enter on:0
 -- address:load: Enter off:12  ON:0 
 -- genPtnMethod:before:enter:callNDX: void 'Fisk'(int32)
 -- callNDX: gJsr, method: Enter descNo: 13
 -- void class ['bvmMini']'Fisk'::'Enter'(int32)
 -- byteCode_textOperand_out: "86 Fisk$Enter" 
 -- byteCode_gJsr:doBody:"86 Fisk$Enter" name:""  NDX:N,sig:"86 Fisk$Enter" , ...falsem ..."" 
 invoke Fisk$Enter 86 0 1
 -- callNDX: gJsr, method: Do descNo: 13
 -- void class ['bvmMini']'Fisk'::'Do'()
 -- byteCode_textOperand_out: "87 Fisk$Do" 
 -- byteCode_gJsr:doBody:"87 Fisk$Do" name:""  NDX:D,sig:"87 Fisk$Do" ,isSt ...falsem ..."" 
 invoke Fisk$Do 87 0 1
 -- genPtnMethod:before:endMethod:D descNo/dn: 90
 rtnEventQ 0
 setThisStack 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- genDoMethod:genPtnClass:before:methodDef; Fisk descNo: 13
 -- MethodDef: "Fisk$PClass"  noOfEnterArgs:0  type:1 =vclass descNo: 91 
 --  signature: "class ['bvmMini']'Fisk' 'new$Fisk'()" 

class Fisk$PClass 91 1 0
 rstore 1 origin
 mvStack 
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- signaturebody:newInstance:Fisk
 -- doLoadProtoAndAlloc: 13
 -- byteCode_callPrimNo: 1 arg: 85
 -- EmitPrimNo: 1 arg: 85
 -- prim:new:
 invoke new 85 0 1
 -- before:endMethod:E
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- genDoMethod:I:before:methodDef: text2BetaText_i
 -- MethodDef: "Text2BetaText_i"  noOfEnterArgs:1  type:0 =ptn descNo: 100 
 --  signature: "text 'Text2BetaText'(string)" 

class inner_1 101 1 0
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0

class Text2BetaText 100 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- orgDesc: not null
 -- newInstance: org: bvmMini consSig: class ['bvmMini']'bvmMini' descNo: 1 ...
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- signaturebody:newInstance:text
 -- doLoadProtoAndAlloc: 4
 -- byteCode_callPrimNo: 1 arg: 22
 -- EmitPrimNo: 1 arg: 22
 -- prim:new:
 invoke new 22 0 1
 -- before:endMethod:G
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- endClass: -none-
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- classDef: putTextformId: betaenv descNo: 3 

class putText 15 1 0
 -- classDef:store:origin:
 rstore 1 origin
 mvStack 
 -- desclareField: T off: 12
 -- fields.new: "F12" "T" "char" [
 -- desclareField: classField? off: 0
 -- fields.new: "F0" "classField?" "" C
 -- genSuper:before:constructorDef:class ['bvmMini']'bvmMini'
 -- byteCode_constructorDef: "class ['bvmMini']'bvmMini'" 
 -- genSuperDo:no default super:
 -- before:storeOrigin:B:
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- ExpEval:A: 111 0 evalKind: 
 pushc 0
 -- byteCode_callAlloPrim: AlloVR1char[]
 -- emitPrim: AlloVR1 arg: char[]
 -- byteCode_doAsgRegAdr:  off: 0
 -- storeRef: T class: char[]
 -- before:endMethod:X
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:1 vTopMax:1 rTop:1 rTopMax:1
 -- before:genNDX:putText
 -- genEnterMethod:I:before:methodDef: Enter className: putText
 -- MethodDef: "putText$Enter"  noOfEnterArgs:1  type:2 =enter/do/exit desc ...16 
 --  signature: "void 'Enter'(char[])" 

class putText$Enter 16 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- asgToNelm: 
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:3
 -- lEV:  EV: T
 -- sytnthlibbody:genAdr: T
 -- sytnthlibbody:genAdr:nameApl: T
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'putText'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_loadRef: 
 -- mstate_loadRef: off: 12
 rpushg 12 arg_12
 -- storeRef: T class: char[]
 -- genEnterMethod:before:endMethod:I
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- genDoMethod:before:methodDef; Do innerName: Inner_1
 -- MethodDef: "putText$Do"  noOfEnterArgs:0  type:0 =ptn descNo: 17 
 --  signature: "void 'Do'()" 

class putText$inner_1 18 1 0
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0

class putText$Do 17 1 0
 rstore 1 origin
 mvStack 
 -- genDoMethod:before:endMethod:J
 rtnEventQ 0
 setThisStack 
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- endClass: -none-
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- classDef: textformId: betaenv descNo: 4 

class text 22 1 0
 -- classDef:store:origin:
 rstore 1 origin
 mvStack 
 -- desclareField: T off: 12
 -- fields.new: "F12" "T" "char" [
 -- desclareField: classField? off: 0
 -- fields.new: "F0" "classField?" "" C
 -- genSuper:before:constructorDef:class ['bvmMini']'bvmMini'
 -- byteCode_constructorDef: "class ['bvmMini']'bvmMini'" 
 -- genSuperDo:no default super:
 -- before:storeOrigin:B:
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- ExpEval:A: 111 1 evalKind: 
 pushc 1
 -- byteCode_callAlloPrim: AlloVR1char[]
 -- emitPrim: AlloVR1 arg: char[]
 -- byteCode_doAsgRegAdr:  off: 0
 -- storeRef: T class: char[]
 -- before:endMethod:X
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:1 vTopMax:1 rTop:1 rTopMax:1
 -- before:genNDX:text
 -- genEnterMethod:I:before:methodDef: Enter className: text
 -- MethodDef: "text$Enter"  noOfEnterArgs:1  type:2 =enter/do/exit descNo: ...23 
 --  signature: "void 'Enter'(char[])" 

class text$Enter 23 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- asgToNelm: 
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:3
 -- lEV:  EV: T
 -- sytnthlibbody:genAdr: T
 -- sytnthlibbody:genAdr:nameApl: T
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'text'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_loadRef: 
 -- mstate_loadRef: off: 12
 rpushg 12 arg_12
 -- storeRef: T class: char[]
 -- genEnterMethod:before:endMethod:I
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- genExitMethod:B:before:methodDef: Exit
 -- MethodDef: "text$Exit"  noOfEnterArgs:0  type:2 =enter/do/exit descNo:  ...26 
 --  signature: "char[] 'Exit'()" 

class text$Exit 26 1 0
 rstore 1 origin
 -- exit method
 rtnEventQ 0
 -- Perhaps setThisStack here: 
 -- genExitMethod:beforePushVal:A: 
 -- genExitMethod:beforePushVal:B: 
 -- ExpEval:A: 61 T evalKind: 
 -- genExitMethod:beforePushVal:C: 
 -- sytnthlibbody:genAdr: T
 -- sytnthlibbody:genAdr:nameApl: T
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'text'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: T on:0
 -- address:load: T off:12  ON:0 
 pushg 12 T
 -- emitPrim: CopyVR1 arg: Unknown
 -- genExitMethod:before:endMethod:
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- endClass: -none-
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- classDef: fooBarformId: betaenv descNo: 12 

class fooBar 78 1 0
 -- classDef:store:origin:
 rstore 1 origin
 mvStack 
 -- desclareField: qqq off: 12
 -- fields.new: "F12" "qqq" "int32" c
 -- desclareField: www off: 16
 -- fields.new: "F16" "www" "int32" c
 -- desclareField: classField? off: 0
 -- fields.new: "F0" "classField?" "" C
 -- genSuper:before:constructorDef:class ['bvmMini']'bvmMini'
 -- byteCode_constructorDef: "class ['bvmMini']'bvmMini'" 
 -- genSuperDo:no default super:
 -- before:storeOrigin:B:
 -- before:endMethod:X
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- before:genNDX:fooBar
 -- genDoMethod:before:methodDef; Do innerName: Inner_1
 -- MethodDef: "fooBar$Do"  noOfEnterArgs:0  type:0 =ptn descNo: 80 
 --  signature: "void 'Do'()" 

class fooBar$inner_1 81 1 0
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0

class fooBar$Do 80 1 0
 rstore 1 origin
 mvStack 
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 'A' -> put label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: put
 -- cProcDesc:C: 
 -- asgToCproc:Super: 
 -- bytecodeval:asgToCproc: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 'A'
 -- ExpEval:A: 110 'A' evalKind: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- bytecodeval:asgToCproc:X:
 -- asgToCproc:Super: 
 -- textVal:asgToCproc:C:
 pushc 65
 %put 2
 -- bytecodeval:asgToCproc:Y:
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 312 -> qqq label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: qqq
 -- evbody:AsgToEval:simple: qqq
 -- sytnthlibbody:genAdr: qqq
 -- sytnthlibbody:genAdr:nameApl: qqq
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'fooBar'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 312
 -- ExpEval:A: 111 312 evalKind: 
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 pushc 312
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: qqq off:12  ON:0 
 storeg 12 qqq
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: qqq + www -> www label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: www
 -- evbody:AsgToEval:simple: www
 -- sytnthlibbody:genAdr: www
 -- sytnthlibbody:genAdr:nameApl: www
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'fooBar'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: qqq + www
 -- ExpEval:A: 89 qqq + www evalKind: 
 -- ExpEval:A: 61 qqq evalKind: 
 -- sytnthlibbody:genAdr: qqq
 -- sytnthlibbody:genAdr:nameApl: qqq
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'fooBar'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: qqq on:0
 -- address:load: qqq off:12  ON:0 
 pushg 12 qqq
 -- ExpEval:A: 61 www evalKind: 
 -- sytnthlibbody:genAdr: www
 -- sytnthlibbody:genAdr:nameApl: www
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'fooBar'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: www on:0
 -- address:load: www off:16  ON:0 
 pushg 16 www
 plus
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: www off:16  ON:0 
 storeg 16 www
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 'B' -> put label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: put
 -- cProcDesc:C: 
 -- asgToCproc:Super: 
 -- bytecodeval:asgToCproc: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 'B'
 -- ExpEval:A: 110 'B' evalKind: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- bytecodeval:asgToCproc:X:
 -- asgToCproc:Super: 
 -- textVal:asgToCproc:C:
 pushc 66
 %put 2
 -- bytecodeval:asgToCproc:Y:
 -- genDoMethod:before:endMethod:J
 rtnEventQ 0
 setThisStack 
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:2 rTop:4 rTopMax:4
 -- endClass: -none-
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:2 rTop:4 rTopMax:4
 -- classDef: FiskformId: betaenv descNo: 13 

class Fisk 85 1 0
 -- classDef:store:origin:
 rstore 1 origin
 mvStack 
 -- desclareField: V off: 12
 -- fields.new: "F12" "V" "int32" c
 -- desclareField: W off: 16
 -- fields.new: "F16" "W" "int32" c
 -- desclareField: classField? off: 0
 -- fields.new: "F0" "classField?" "" C
 -- genSuper:before:constructorDef:class ['bvmMini']'bvmMini'
 -- byteCode_constructorDef: "class ['bvmMini']'bvmMini'" 
 -- genSuperDo:no default super:
 -- before:storeOrigin:B:
 -- before:endMethod:X
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- before:genNDX:Fisk
 -- genEnterMethod:I:before:methodDef: Enter className: Fisk
 -- MethodDef: "Fisk$Enter"  noOfEnterArgs:1  type:2 =enter/do/exit descNo: ...86 
 --  signature: "void 'Enter'(int32)" 

class Fisk$Enter 86 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- asgToNelm: 
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: V
 -- evbody:AsgToEval:simple: V
 -- sytnthlibbody:genAdr: V
 -- sytnthlibbody:genAdr:nameApl: V
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: arg_12 on:0
 -- address:load: arg_12 off:12  ON:0 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: V off:12  ON:0 
 storeg 12 V
 -- genEnterMethod:before:endMethod:I
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:-1 vTopMax:0 rTop:1 rTopMax:1
 -- genDoMethod:before:methodDef; Do innerName: Inner_1
 -- MethodDef: "Fisk$Do"  noOfEnterArgs:0  type:0 =ptn descNo: 87 
 --  signature: "void 'Do'()" 

class Fisk$inner_1 88 1 0
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0

class Fisk$Do 87 1 0
 rstore 1 origin
 mvStack 
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 24 -> V label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: V
 -- evbody:AsgToEval:simple: V
 -- sytnthlibbody:genAdr: V
 -- sytnthlibbody:genAdr:nameApl: V
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 24
 -- ExpEval:A: 111 24 evalKind: 
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 pushc 24
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: V off:12  ON:0 
 storeg 12 V
 -- genDoMethod:before:endMethod:J
 rtnEventQ 0
 setThisStack 
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:1 rTop:1 rTopMax:1
 -- genDoMethod:genPtnMethod:before:methodDef: add descNo: 14
 -- sig.thisMethodDesc:descNo: 14
 -- MethodDef: "add$cons"  noOfEnterArgs:1  type:1 =vclass descNo: 97 
 --  signature: "int32 'add'(int32)" 

class add$cons 97 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- genPtnMethod:KUK:B:
 -- genPtnMethod:newInstanceWithOrigin:X:
 -- genPtnMethod:newInstanceWithOrigin:
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: Fisk consSig: class ['bvmMini']'Fisk' descNo: 13
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- byteCode_callPrimNo: -2 arg: thisObjHack
 -- EmitPrimNo: -2 arg: thisObjHack
 rpushg 1 TheObj
 -- signaturebody:newInstance:Fisk$add
 -- doLoadProtoAndAlloc: 14
 -- byteCode_callPrimNo: 1 arg: 92
 -- EmitPrimNo: 1 arg: 92
 -- prim:new:
 invoke new 92 0 1
 -- genPtnMethod:koks:
 -- bytecode_ldValImpl: Enter on:0
 -- address:load: Enter off:12  ON:0 
 -- genPtnMethod:before:enter:callNDX: int32 'add'(int32)
 -- callNDX: gJsr, method: Enter descNo: 14
 -- void class ['bvmMini']'Fisk$add'::'Enter'(int32)
 -- byteCode_textOperand_out: "93 Fisk$add$Enter" 
 -- byteCode_gJsr:doBody:"93 Fisk$add$Enter" name:""  NDX:N,sig:"93 Fisk$ad ..." , ...falsem ..."" 
 invoke Fisk$add$Enter 93 0 1
 -- callNDX: gJsr, method: Do descNo: 14
 -- void class ['bvmMini']'Fisk$add'::'Do'()
 -- byteCode_textOperand_out: "94 Fisk$add$Do" 
 -- byteCode_gJsr:doBody:"94 Fisk$add$Do" name:""  NDX:D,sig:"94 Fisk$add$D ..." , ...falsem ..."" 
 invoke Fisk$add$Do 94 0 1
 -- callNDX: gJsr, method: Exit descNo: 14
 -- int32 class ['bvmMini']'Fisk$add'::'Exit'()
 -- byteCode_textOperand_out: "96 Fisk$add$Exit" 
 -- byteCode_gJsr:doBody:"96 Fisk$add$Exit" name:""  NDX:X,sig:"96 Fisk$add ..." , ...falsem ..."" 
 invoke Fisk$add$Exit 96 0 1
 -- genPtnMethod:before:endMethod:D descNo/dn: 97
 rtnEventQ 0
 setThisStack 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- genDoMethod:genPtnClass:before:methodDef; add descNo: 14
 -- MethodDef: "add$PClass"  noOfEnterArgs:0  type:1 =vclass descNo: 98 
 --  signature: "class ['bvmMini']'Fisk$add' 'new$add'()" 

class add$PClass 98 1 0
 rstore 1 origin
 mvStack 
 -- newInstanceWithOrigin:Q: 
 -- orgDesc: not null
 -- newInstance: org: Fisk consSig: class ['bvmMini']'Fisk' descNo: 13
 -- newThisInstanceQ: 
 -- genlib_bytecode:pushThis:
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- mstate_loadRef: off: 0
 -- signaturebody:newInstance:Fisk$add
 -- doLoadProtoAndAlloc: 14
 -- byteCode_callPrimNo: 1 arg: 92
 -- EmitPrimNo: 1 arg: 92
 -- prim:new:
 invoke new 92 0 1
 -- before:endMethod:E
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- endClass: -none-
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:1 rTopMax:1
 -- classDef: Fisk$addformId: betaenv descNo: 14 

class Fisk$add 92 1 0
 -- classDef:store:origin:
 rstore 1 origin
 mvStack 
 -- desclareField: N off: 12
 -- fields.new: "F12" "N" "int32" c
 -- desclareField: classField? off: 0
 -- fields.new: "F0" "classField?" "" C
 -- genSuper:before:constructorDef:class ['bvmMini']'Fisk'
 -- byteCode_constructorDef: "class ['bvmMini']'Fisk'" 
 -- genSuperDo:no default super:
 -- before:storeOrigin:B:
 -- before:endMethod:X
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- before:genNDX:Fisk$add
 -- genEnterMethod:I:before:methodDef: Enter className: Fisk$add
 -- MethodDef: "Fisk$add$Enter"  noOfEnterArgs:1  type:2 =enter/do/exit des ...93 
 --  signature: "void 'Enter'(int32)" 

class Fisk$add$Enter 93 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- asgToNelm: 
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: N
 -- evbody:AsgToEval:simple: N
 -- sytnthlibbody:genAdr: N
 -- sytnthlibbody:genAdr:nameApl: N
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk$add'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: arg_12 on:0
 -- address:load: arg_12 off:12  ON:0 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: N off:12  ON:0 
 storeg 12 N
 -- genEnterMethod:before:endMethod:I
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:-1 vTopMax:0 rTop:1 rTopMax:1
 -- genDoMethod:before:methodDef; Do innerName: Inner_1
 -- MethodDef: "Fisk$add$Do"  noOfEnterArgs:0  type:0 =ptn descNo: 94 
 --  signature: "void 'Do'()" 

class Fisk$add$inner_1 95 1 0
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0

class Fisk$add$Do 94 1 0
 rstore 1 origin
 mvStack 
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 'C' -> put label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: put
 -- cProcDesc:C: 
 -- asgToCproc:Super: 
 -- bytecodeval:asgToCproc: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 'C'
 -- ExpEval:A: 110 'C' evalKind: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- bytecodeval:asgToCproc:X:
 -- asgToCproc:Super: 
 -- textVal:asgToCproc:C:
 pushc 67
 %put 2
 -- bytecodeval:asgToCproc:Y:
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 15 -> V label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: V
 -- evbody:AsgToEval:simple: V
 -- sytnthlibbody:genAdr: V
 -- sytnthlibbody:genAdr:nameApl: V
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 1
 -- goOrigin:on: 2
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk$add'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 2
 -- bytecode_ldValImpl: this_ on:1
 -- Address:loadOrigin:ON:1 class ['bvmMini']'Fisk$add'
 rpushg 1 origin
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 15
 -- ExpEval:A: 111 15 evalKind: 
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 pushc 15
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: V off:12  ON:0 
 storeg 12 V
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: V + N -> W label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:2
 -- lEV:  EV: W
 -- evbody:AsgToEval:simple: W
 -- sytnthlibbody:genAdr: W
 -- sytnthlibbody:genAdr:nameApl: W
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 1
 -- goOrigin:on: 2
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk$add'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 2
 -- bytecode_ldValImpl: this_ on:1
 -- Address:loadOrigin:ON:1 class ['bvmMini']'Fisk$add'
 rpushg 1 origin
 -- end:goOrigin: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: V + N
 -- ExpEval:A: 89 V + N evalKind: 
 -- ExpEval:A: 61 V evalKind: 
 -- sytnthlibbody:genAdr: V
 -- sytnthlibbody:genAdr:nameApl: V
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 1
 -- goOrigin:on: 2
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk$add'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 2
 -- bytecode_ldValImpl: this_ on:1
 -- Address:loadOrigin:ON:1 class ['bvmMini']'Fisk$add'
 rpushg 1 origin
 -- end:goOrigin: 
 -- bytecode_ldValImpl: V on:0
 -- address:load: V off:12  ON:0 
 pushg 12 V
 -- ExpEval:A: 61 N evalKind: 
 -- sytnthlibbody:genAdr: N
 -- sytnthlibbody:genAdr:nameApl: N
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 0
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk$add'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- bytecode_ldValImpl: N on:0
 -- address:load: N off:12  ON:0 
 pushg 12 N
 plus
 -- bytecodeval_enterArgs_eval:D: 
 -- bytecodeval_enterArgs_eval:E: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- byteCode_stValImpl:doPart
 -- byteCode_stValImpl:doPart:after:A.out
 -- address:store: W off:16  ON:0 
 storeg 16 W
 -- dobody:before:gen:imp:
 -- EvalBody:before:sematt.evCase: 'D' -> put label: 55 55
 -- evbody:assignValToEval:before:sematt.evcase: EV.label61 EV.evalKind:1
 -- lEV:  EV: put
 -- cProcDesc:C: 
 -- asgToCproc:Super: 
 -- bytecodeval:asgToCproc: 
 -- bytecodeval_enterArgs_eval: 
 -- bytecodeval_enterArgs_eval:B: 'D'
 -- ExpEval:A: 110 'D' evalKind: 
 -- bytecodeval_enterArgs_eval:F: 
 -- bytecodeval_enterArgs_eval:I: 
 -- bytecodeval_enterArgs_eval:J: 
 -- bytecodeval:asgToCproc:X:
 -- asgToCproc:Super: 
 -- textVal:asgToCproc:C:
 pushc 68
 %put 2
 -- bytecodeval:asgToCproc:Y:
 -- genDoMethod:before:endMethod:J
 rtnEventQ 0
 setThisStack 
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:2 rTop:4 rTopMax:4
 -- genExitMethod:B:before:methodDef: Exit
 -- MethodDef: "Fisk$add$Exit"  noOfEnterArgs:0  type:2 =enter/do/exit desc ...96 
 --  signature: "int32 'Exit'()" 

class Fisk$add$Exit 96 1 0
 rstore 1 origin
 -- exit method
 rtnEventQ 0
 -- Perhaps setThisStack here: 
 -- genExitMethod:beforePushVal:A: 
 -- genExitMethod:beforePushVal:B: 
 -- ExpEval:A: 61 W evalKind: 
 -- sytnthlibbody:genAdr: W
 -- sytnthlibbody:genAdr:nameApl: W
 -- before:doGoOrigin:
 -- doGorigin:ad.on: 1
 -- goOrigin:on: 2
 -- bytecode_ldValImpl: this_ on:0
 -- Address:loadOrigin:ON:0 class ['bvmMini']'Fisk$add'
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 2
 -- bytecode_ldValImpl: this_ on:1
 -- Address:loadOrigin:ON:1 class ['bvmMini']'Fisk$add'
 rpushg 1 origin
 -- end:goOrigin: 
 -- bytecode_ldValImpl: W on:0
 -- address:load: W off:16  ON:0 
 pushg 16 W
 -- genExitMethod:beforePushVal:C: 
 -- genExitMethod:before:endMethod:
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- endClass: -none-
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- classDef: BetaObjectformId: betaenv descNo: 11 

class BetaObject 71 1 0
 -- classDef:store:origin:
 rstore 1 origin
 mvStack 
 -- desclareField: classField? off: 0
 -- fields.new: "F0" "classField?" "" C
 -- desclareField:  off: 0
 -- fields.new: "F0" "-none-" "class ['']''" c
 -- genSuper:before:constructorDef:class ['bvmMini']'bvmMini'
 -- byteCode_constructorDef: "class ['bvmMini']'bvmMini'" 
 -- genSuperDo:no default super:
 -- before:endMethod:X
 rtnEventQ 0
 setThisStack 
 pushThis 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0
 -- genDoMethod:genPtnMethod:before:methodDef: BetaObject descNo: 11
 -- sig.thisMethodDesc:descNo: 11
 -- MethodDef: "BetaObject$cons"  noOfEnterArgs:1  type:1 =vclass descNo: 76 
 --  signature: "static void 'BetaObject'(class ['bvmMini']'bvmMini')" 

class BetaObject$cons 76 1 0
 rstore 1 origin
 -- hasEnterArgs: 1
 -- genPtnMethod:KUK:A:
 -- genPtnMethod:KUK:X:
 -- newInstance: org: - consSig:  descNo: 
 -- signaturebody:newInstance:BetaObject
 -- doLoadProtoAndAlloc: 11
 -- byteCode_callPrimNo: 1 arg: 71
 -- EmitPrimNo: 1 arg: 71
 -- prim:new:
 invoke new 71 0 1
 -- genPtnMethod:koks:
 -- callNDX: gJsr, method: Do descNo: 11
 -- void class ['bvmMini']'BetaObject'::'Do'()
 -- byteCode_textOperand_out: "73 BetaObject$Do" 
 -- byteCode_gJsr:doBody:"73 BetaObject$Do" name:""  NDX:D,sig:"73 BetaObje ..." , ...falsem ..."" 
 invoke BetaObject$Do 73 0 1
 -- genPtnMethod:before:endMethod:D descNo/dn: 76
 rtnEventQ 0
 setThisStack 
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:-1 rTopMax:0
 -- before:genNDX:BetaObject
 -- genDoMethod:before:methodDef; Do innerName: Inner_1
 -- MethodDef: "BetaObject$Do"  noOfEnterArgs:0  type:0 =ptn descNo: 73 
 --  signature: "void 'Do'()" 

class BetaObject$inner_1 74 1 0
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:0 rTopMax:0

class BetaObject$Do 73 1 0
 rstore 1 origin
 mvStack 
 -- dobody:before:gen:imp:
 -- goOrigin:on: 1
 -- bytecode_ldValImpl: this on:0
 pushThis 
 -- Address:loadOrigin:ON:0 _this_m
 pushThis 
 rpushg 1 origin
 -- goOrigin:before:forLoop:on: 1
 -- end:goOrigin: 
 -- after exeInnerP
 -- byteCode_textOperand_out: "void class ['bvmMini']'BetaObject'::'Inner_1 ..." 
 -- byteCode_gJsr:doBody:"void class ['bvmMini']'BetaObject'::'Inner_1'()" n ..."v ..."   ...M ..., ..."( ..." , ...falsem ..."" 
 invoke void class ['bvmMini']'BetaObject'::'Inner_1' 0 0 1
 -- genDoMethod:before:endMethod:J
 rtnEventQ 0
 setThisStack 
 pushThis 
 rpushg 1 origin
 rtn(D)
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:2 rTopMax:2
 -- endClass: -none-
 end OSDV:1 objSize:100 isIndexed:0  vTop:0 vTopMax:0 rTop:2 rTopMax:2
 -- endcodeseg

Class bvmMini descInx: 1 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	rpushg 1
7:	invoke 85 0 1
13:	rstore 24
15:	rtnEventQ 0
17:	setThisStack
18:	pushthis 
19:	rtn D


Class bvmMini$Do descInx: 3 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushc 33
6:	%prim put 2
8:	pushthis 
9:	rpushg 1
11:	pushc 117
13:	storeg 12
15:	pushthis 
16:	rpushg 1
18:	pushc 10
20:	storeg 16
22:	pushthis 
23:	rpushg 1
25:	pushthis 
26:	rpushg 1
28:	pushg 12
30:	pushthis 
31:	rpushg 1
33:	pushg 16
35:	+
36:	storeg 16
38:	pushthis 
39:	rpushg 1
41:	invoke 83 0 1
47:	pushthis 
48:	rpushg 1
50:	rpushg 24
52:	invoke 87 0 1
58:	pushthis 
59:	rpushg 1
61:	pushthis 
62:	rpushg 1
64:	rpushg 24
66:	pushc 55
68:	invoke 97 0 1
74:	storeg 44
76:	pushc 69
78:	%prim put 2
80:	pushthis 
81:	rpushg 1
83:	pushg 44
85:	%prim put 2
87:	rtnEventQ 0
89:	setThisStack
90:	pushthis 
91:	rpushg 1
93:	rtn D


Class bvmMini$inner_1 descInx: 4 originOff: 1 visibility: 1
allocE:
1:	rtn D


Class bvmMini$cons descInx: 6 originOff: 1 visibility: 1
allocE:
1:	pushthis 
2:	invoke 1 0 1
8:	invoke 3 0 1
14:	stop 
15:	rtn D


Class putText descInx: 15 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	pushc 0
7:	rtnEventQ 0
9:	setThisStack
10:	pushthis 
11:	rtn D


Class putText$Enter descInx: 16 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	rpushg 12
8:	pushthis 
9:	rpushg 1
11:	rtn D


Class putText$Do descInx: 17 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	rtnEventQ 0
6:	setThisStack
7:	pushthis 
8:	rpushg 1
10:	rtn D


Class putText$inner_1 descInx: 18 originOff: 1 visibility: 1
allocE:
1:	rtn D


Class putText$cons descInx: 20 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	invoke 15 0 1
12:	rpushg 12
14:	invoke 16 0 1
20:	invoke 17 0 1
26:	rtnEventQ 0
28:	setThisStack
29:	rtn D


Class putText$PClass descInx: 21 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	invoke 15 0 1
11:	rtnEventQ 0
13:	setThisStack
14:	pushthis 
15:	rtn D


Class text descInx: 22 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	pushc 1
7:	rtnEventQ 0
9:	setThisStack
10:	pushthis 
11:	rtn D


Class text$Enter descInx: 23 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	rpushg 12
8:	pushthis 
9:	rpushg 1
11:	rtn D


Class text$Exit descInx: 26 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	rtnEventQ 0
5:	pushthis 
6:	rpushg 1
8:	pushg 12
10:	rtn D


Class text$cons descInx: 27 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	invoke 22 0 1
12:	rpushg 12
14:	invoke 23 0 1
20:	invoke 26 0 1
26:	rtnEventQ 0
28:	setThisStack
29:	rtn D


Class text$PClass descInx: 28 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	invoke 22 0 1
11:	rtnEventQ 0
13:	setThisStack
14:	pushthis 
15:	rtn D


Class BetaObject descInx: 71 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	rtnEventQ 0
6:	setThisStack
7:	pushthis 
8:	rtn D


Class BetaObject$Do descInx: 73 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	pushthis 
6:	rpushg 1
8:	invoke 0 0 1
14:	rtnEventQ 0
16:	setThisStack
17:	pushthis 
18:	rpushg 1
20:	rtn D


Class BetaObject$inner_1 descInx: 74 originOff: 1 visibility: 1
allocE:
1:	rtn D


Class BetaObject$cons descInx: 76 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	invoke 71 0 1
9:	invoke 73 0 1
15:	rtnEventQ 0
17:	setThisStack
18:	rtn D


Class fooBar descInx: 78 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	rtnEventQ 0
6:	setThisStack
7:	pushthis 
8:	rtn D


Class fooBar$Do descInx: 80 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushc 65
6:	%prim put 2
8:	pushthis 
9:	rpushg 1
11:	pushc2 312
14:	storeg 12
16:	pushthis 
17:	rpushg 1
19:	pushthis 
20:	rpushg 1
22:	pushg 12
24:	pushthis 
25:	rpushg 1
27:	pushg 16
29:	+
30:	storeg 16
32:	pushc 66
34:	%prim put 2
36:	rtnEventQ 0
38:	setThisStack
39:	pushthis 
40:	rpushg 1
42:	rtn D


Class fooBar$inner_1 descInx: 81 originOff: 1 visibility: 1
allocE:
1:	rtn D


Class fooBar$cons descInx: 83 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	rpushg 1
7:	invoke 78 0 1
13:	invoke 80 0 1
19:	rtnEventQ 0
21:	setThisStack
22:	rtn D


Class fooBar$PClass descInx: 84 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	invoke 78 0 1
11:	rtnEventQ 0
13:	setThisStack
14:	pushthis 
15:	rtn D


Class Fisk descInx: 85 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	rtnEventQ 0
6:	setThisStack
7:	pushthis 
8:	rtn D


Class Fisk$Enter descInx: 86 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	storeg 12
8:	pushthis 
9:	rpushg 1
11:	rtn D


Class Fisk$Do descInx: 87 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	rpushg 1
7:	pushc 24
9:	storeg 12
11:	rtnEventQ 0
13:	setThisStack
14:	pushthis 
15:	rpushg 1
17:	rtn D


Class Fisk$inner_1 descInx: 88 originOff: 1 visibility: 1
allocE:
1:	rtn D


Class Fisk$cons descInx: 90 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	invoke 85 0 1
12:	invoke 86 0 1
18:	invoke 87 0 1
24:	rtnEventQ 0
26:	setThisStack
27:	rtn D


Class Fisk$PClass descInx: 91 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	invoke 85 0 1
11:	rtnEventQ 0
13:	setThisStack
14:	pushthis 
15:	rtn D


Class Fisk$add descInx: 92 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	rtnEventQ 0
6:	setThisStack
7:	pushthis 
8:	rtn D


Class Fisk$add$Enter descInx: 93 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	storeg 12
8:	pushthis 
9:	rpushg 1
11:	rtn D


Class Fisk$add$Do descInx: 94 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushc 67
6:	%prim put 2
8:	pushthis 
9:	rpushg 1
11:	rpushg 1
13:	pushc 15
15:	storeg 12
17:	pushthis 
18:	rpushg 1
20:	rpushg 1
22:	pushthis 
23:	rpushg 1
25:	rpushg 1
27:	pushg 12
29:	pushthis 
30:	rpushg 1
32:	pushg 12
34:	+
35:	storeg 16
37:	pushc 68
39:	%prim put 2
41:	rtnEventQ 0
43:	setThisStack
44:	pushthis 
45:	rpushg 1
47:	rtn D


Class Fisk$add$inner_1 descInx: 95 originOff: 1 visibility: 1
allocE:
1:	rtn D


Class Fisk$add$Exit descInx: 96 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	rtnEventQ 0
5:	pushthis 
6:	rpushg 1
8:	rpushg 1
10:	pushg 16
12:	rtn D


Class add$cons descInx: 97 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	rpushg 1
6:	invoke 92 0 1
12:	invoke 93 0 1
18:	invoke 94 0 1
24:	invoke 96 0 1
30:	rtnEventQ 0
32:	setThisStack
33:	rtn D


Class add$PClass descInx: 98 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	mvStack
4:	pushthis 
5:	invoke 92 0 1
11:	rtnEventQ 0
13:	setThisStack
14:	pushthis 
15:	rtn D


Class Text2BetaText descInx: 100 originOff: 1 visibility: 1
allocE:
1:	rstore 1
3:	pushthis 
4:	invoke 22 0 1
10:	rtnEventQ 0
12:	setThisStack
13:	pushthis 
14:	rtn D


Class inner_1 descInx: 101 originOff: 1 visibility: 1
allocE:
1:	rtn D

