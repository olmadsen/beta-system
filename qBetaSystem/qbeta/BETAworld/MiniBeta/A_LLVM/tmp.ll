   ;;  String:  3 

;; CLASS MiniBeta 13 1 MiniBeta 1

define %MiniBeta$13* @MiniBeta$13(%MiniBeta$13* %R0){
   %V0 = add i32 0, 0
;; rstore  1 origin
   ;; rstore:ignored 
;; DO:
   br label %L1
L1:
   br label %L2
L2:
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%MiniBeta$13*] 
   ;; %MiniBeta$13* 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%MiniBeta$13*]
   ret %MiniBeta$13* %R0   ;; vTop(0,0)=[] rTop(0,1)=[]
}
   ;; vdt:vdtTop: 0 
@vdt_data$MiniBeta$13 = global %vdt_type$MiniBeta$13 {
}

define %vdt_ret$MiniBeta$13* @vdt_alloc$MiniBeta$13(%MiniBeta$1* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$MiniBeta$13
   %R2 = tail call i8* @malloc(i64 32)
   %R3 = bitcast i8* %R2 to %vdt_ret$MiniBeta$13*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %MiniBeta$13 
   ;; alloc %MiniBeta$13
   %R4 = tail call i8* @malloc(i64 192)
   %R5 = bitcast i8* %R4 to %MiniBeta$13*
   ;; store VDT in object
   %R6 = getelementptr %MiniBeta$13, %MiniBeta$13* %R5, i32 0, i32 0
   store %vdt_type$MiniBeta$13* @vdt_data$MiniBeta$13, %vdt_type$MiniBeta$13** %R6
   %R7 = getelementptr %vdt_ret$MiniBeta$13,%vdt_ret$MiniBeta$13* %R3, i32 0, i32 0
   store %MiniBeta$13* %R5, %MiniBeta$13** %R7
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: MiniBeta thisClassOrgDescNo: 1 
   ;; vTop(0,0)=[] rTop(1,1)=[1:%MiniBeta$1*] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%MiniBeta$13] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%MiniBeta$13]
   ;; before:handleOrigins: 13 
   ;; handleOrigins:NEW: MiniBeta 
;; rstoreX 1 MiniBeta$1 isValueObjectOrigin: F
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%MiniBeta$13]
   ;; lookup:  %Object$13*
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%MiniBeta$13]
   %R8 = getelementptr %MiniBeta$1, %MiniBeta$1 * %R5, i32 0, i32 1
   %R9 = bitcast %Object$13** %R8 to %MiniBeta$1**
   store %MiniBeta$1* %R1, %MiniBeta$1** %R9
;; rswap 0
   ;; handleOrigins:END:  
   ;; after:handleOrigins: 13 
   ret %vdt_ret$MiniBeta$13* %R3
}
   ;; ObjStubStackX:gen 

;; CLASS MiniBeta 1 1 Object 13

define %MiniBeta$1* @MiniBeta$1(%MiniBeta$1* %R0){
   %V0 = add i32 0, 0
;; rstore  1 origin
   ;; rstore:ignored 
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%MiniBeta$1*] 
   ;; %MiniBeta$1* 
   ;; saveBETAworld
   ;; saveStringOrigin
   ;; OG:gen: "foo: {      %id "foo";      _put('Q' + 2);      V:< ;         %id "foo:V";         S: var String;         _put('Q' + 4);         inner(V);         ch := 'Q' + 6;  ...}" 
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%MiniBeta$1*] 
   ;; %MiniBeta$1* 
;; invoke A_LLVM 44 2 1
   ;; vTop(0,0)=[] rTop(1,1)=[0:%MiniBeta$1*]
   ;; alloc %A_LLVM$44
   %R1 = tail call i8* @malloc(i64 12)
   %R2 = bitcast i8* %R1 to %A_LLVM$44*
   ;; store VDT in object
   %R3 = getelementptr %A_LLVM$44, %A_LLVM$44* %R2, i32 0, i32 0
   store %vdt_type$A_LLVM$44* @vdt_data$A_LLVM$44, %vdt_type$A_LLVM$44** %R3
   ;; vTop(0,0)=[] rTop(2,2)=[0:%MiniBeta$1*,2:%A_LLVM$44] 
   ;; store:args 
   ;; after:store:args:top: 0 
;; rstoreX 1 A_LLVM$44 isValueObjectOrigin: F
   ;; vTop(0,0)=[] rTop(2,2)=[0:%MiniBeta$1*,2:%A_LLVM$44]
   ;; lookup:  %MiniBeta$1*
   ;; vTop(0,0)=[] rTop(2,2)=[0:%MiniBeta$1*,2:%A_LLVM$44]
   %R4 = getelementptr %A_LLVM$44, %A_LLVM$44 * %R2, i32 0, i32 1
   store %MiniBeta$1* %R0, %MiniBeta$1** %R4
;; rswap 0
   ;; save object: %A_LLVM$44* dstType: %A_LLVM$44*
   %R5 = getelementptr %MiniBeta$1,%MiniBeta$1* %R0, i32 0, i32 2
   store %A_LLVM$44* %R2,  %A_LLVM$44** %R5
   %R6 = call %A_LLVM$44* @A_LLVM$44(%A_LLVM$44 * %R2)
   ;; vTop(0,0)=[] rTop(1,2)=[2:%A_LLVM$44*] 
   %V9 = icmp eq %A_LLVM$44* %R6, %R2
   br i1 %V9, label %normalRtnLab7, label %breakLab8
breakLab8:
   %R10 = bitcast %A_LLVM$44* %R6 to %MiniBeta$1*
   %V11 = icmp eq %MiniBeta$1* %R0, %R10
   br i1 %V11, label %selectBreakLab13, label %contBreakLab12
contBreakLab12:
   ret %MiniBeta$1* %R10
selectBreakLab13:
   %R14 = bitcast %A_LLVM$44* %R6 to [0 x i32]*
   %R15 = getelementptr [0 x i32], [0 x i32]* %R14, i32 0, i32 0
   %V16 = load i32 , i32* %R15
   %R17 = getelementptr %A_LLVM$44,%A_LLVM$44* %R6, i32 0, i32 0
   store %vdt_type$A_LLVM$44* @vdt_data$A_LLVM$44, %vdt_type$A_LLVM$44** %R17
   %V18 = icmp eq i32 1, %V16
   br i1 %V18, label %X19, label %X20
X19:
   br label %L1 ; restart
X20:
   br label %L2 ; leave
normalRtnLab7:

   ;; vTop(0,0)=[] rTop(1,2)=[2:%A_LLVM$44*]
;; rpop 
;; DO:
   br label %L1
L1:
   br label %L2
L2:
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,2)=[0:%MiniBeta$1*] 
   ;; %MiniBeta$1* 
   ;; vTop(0,0)=[] rTop(1,2)=[0:%MiniBeta$1*]
   ret %MiniBeta$1* %R0   ;; vTop(0,0)=[] rTop(0,2)=[]
}
   ;; vdt:vdtTop: 1 1:I
@vdt_data$MiniBeta$1 = global %vdt_type$MiniBeta$1 {
      %MiniBeta$1*(%MiniBeta$1*)* @MiniBeta$1
}

define %vdt_ret$MiniBeta$1* @vdt_alloc$MiniBeta$1(%Object$13* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$MiniBeta$1
   %R22 = tail call i8* @malloc(i64 32)
   %R23 = bitcast i8* %R22 to %vdt_ret$MiniBeta$1*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %MiniBeta$1 
   ;; alloc %MiniBeta$1
   %R24 = tail call i8* @malloc(i64 192)
   %R25 = bitcast i8* %R24 to %MiniBeta$1*
   ;; store VDT in object
   %R26 = getelementptr %MiniBeta$1, %MiniBeta$1* %R25, i32 0, i32 0
   store %vdt_type$MiniBeta$1* @vdt_data$MiniBeta$1, %vdt_type$MiniBeta$1** %R26
   %R27 = getelementptr %vdt_ret$MiniBeta$1,%vdt_ret$MiniBeta$1* %R23, i32 0, i32 0
   store %MiniBeta$1* %R25, %MiniBeta$1** %R27
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: Object thisClassOrgDescNo: 13 
   ;; vTop(0,0)=[] rTop(1,2)=[1:%Object$13*] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%Object$13*,25:%MiniBeta$1] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%Object$13*,25:%MiniBeta$1]
   ;; before:handleOrigins: 1 
   ;; handleOrigins:NEW: MiniBeta 
;; rstoreX 1 MiniBeta$1 isValueObjectOrigin: F
   ;; vTop(0,0)=[] rTop(2,2)=[1:%Object$13*,25:%MiniBeta$1]
   ;; lookup:  %Object$13*
   ;; vTop(0,0)=[] rTop(2,2)=[1:%Object$13*,25:%MiniBeta$1]
   %R28 = getelementptr %MiniBeta$1, %MiniBeta$1 * %R25, i32 0, i32 1
   store %Object$13* %R1, %Object$13** %R28
;; rswap 0
   ;; handleOrigins:END:  
   ;; after:handleOrigins: 1 
   ret %vdt_ret$MiniBeta$1* %R23
}
   ;; ObjStubStackX:gen 

;; CLASS Value 2 0 MiniBeta 1 isValueObj

define %Value$2* @Value$2(%Value$2* %R0, i32 %off){
   %V0 = add i32 0, 0
;; DO:
   br label %L1
L1:
   br label %L2
L2:
   ;; vTop(0,0)=[] rTop(0,0)=[]
   ret %Value$2* %R0   ;; vTop(0,0)=[] rTop(-1,0)=[]
}
   ;; vdt:vdtTop: 3 2:I,4:V,24:V
@vdt_data$Value$2 = global %vdt_type$Value$2 {
      %Value$2*(%Value$2*, i32)* @Value$2,
      %vdt_ret$_equal$4*(%Value$2*)* @vdt_alloc$_equal$4,
      %vdt_ret$_lessequal$24*(%Value$2*)* @vdt_alloc$_lessequal$24
}

define %vdt_ret$Value$2* @vdt_alloc$Value$2(%MiniBeta$1* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$Value$2
   %R2 = tail call i8* @malloc(i64 32)
   %R3 = bitcast i8* %R2 to %vdt_ret$Value$2*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %Value$2 
   ;; alloc %Value$2
   %R4 = tail call i8* @malloc(i64 192)
   %R5 = bitcast i8* %R4 to %Value$2*
   ;; store VDT in object
   %R6 = getelementptr %Value$2, %Value$2* %R5, i32 0, i32 0
   store %vdt_type$Value$2* @vdt_data$Value$2, %vdt_type$Value$2** %R6
   %R7 = getelementptr %vdt_ret$Value$2,%vdt_ret$Value$2* %R3, i32 0, i32 0
   store %Value$2* %R5, %Value$2** %R7
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: MiniBeta thisClassOrgDescNo: 1 
;; rpush:rtop: 0
   ;; vTop(0,0)=[] rTop(0,0)=[] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%Value$2] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%Value$2]
   ;; before:handleOrigins: 2 
   ;; handleOrigins:NEW: Value 
   ;; after:handleOrigins: 2 
   ret %vdt_ret$Value$2* %R3
}
   ;; ObjStubStackX:gen 

;; CLASS String 3 0 MiniBeta 1

define %String$3* @String$3(%String$3* %R0){
   %V0 = add i32 0, 0
;; DO:
   br label %L1
L1:
   br label %L2
L2:
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%String$3*] 
   ;; %String$3* 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%String$3*]
   ret %String$3* %R0   ;; vTop(0,0)=[] rTop(0,1)=[]
}
   ;; vdt:vdtTop: 3 3:I,6:V,25:V
@vdt_data$String$3 = global %vdt_type$String$3 {
      %String$3*(%String$3*)* @String$3,
      %vdt_ret$_equal$6*(%String$3*)* @vdt_alloc$_equal$6,
      %vdt_ret$_lessequal$25*(%String$3*)* @vdt_alloc$_lessequal$25
}

define %vdt_ret$String$3* @vdt_alloc$String$3(%MiniBeta$1* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$String$3
   %R2 = tail call i8* @malloc(i64 32)
   %R3 = bitcast i8* %R2 to %vdt_ret$String$3*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %String$3 
   ;; alloc %String$3
   %R4 = tail call i8* @malloc(i64 192)
   %R5 = bitcast i8* %R4 to %String$3*
   ;; store VDT in object
   %R6 = getelementptr %String$3, %String$3* %R5, i32 0, i32 0
   store %vdt_type$String$3* @vdt_data$String$3, %vdt_type$String$3** %R6
   %R7 = getelementptr %vdt_ret$String$3,%vdt_ret$String$3* %R3, i32 0, i32 0
   store %String$3* %R5, %String$3** %R7
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: MiniBeta thisClassOrgDescNo: 1 
   ;; vTop(0,0)=[] rTop(1,1)=[1:%MiniBeta$1*] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%String$3] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%String$3]
   ;; before:handleOrigins: 3 
   ;; handleOrigins:NEW: String 
   ;; after:handleOrigins: 3 
   ret %vdt_ret$String$3* %R3
}
   ;; ObjStubStackX:gen 
   ;; OG:reAlloc: descNo: 0 21 "%basic 50{   in V: var this(Value);   out B: var boolean;   inner(= )}" 
   ;; OG:reAlloc: descNo: 0 0 "%ID "miniObject"{   %basic 64;   %public}" 

;; CLASS = 4 1 Value 2

define %_equal$4* @_equal$4(%_equal$4* %R0){
   %V0 = add i32 0, 0
;; rstore  1 origin
   ;; rstore:ignored 
;; store 3 origin.valueOff
   ;; store:ignored 
;; store 2 origin.valueOff
   ;; store:ignored 
;; DO:
   br label %L1
L1:
   ;; OG:gen: "inner(= )" 
   ;; OG:before:super.gen: "inner(= )" 
   ;; doNeedOrigin:Ex: "inner(= )" 
   ;; IV:after:computeAdr:superAdj: 0 :Adr:off:0 size:0 isFloat:F isUnitVal:F superAdj:0 isUnique:F isValue:F originIsValue:F:E:"inner(= )":rec:- 
   ;; rec:  "inner(= )" E:  "inner(= )" 
   ;; OI:invoke: "inner(= )" 
   ;; ptn:invoke: "inner" E: "inner(= )" ptnKind: 0 useRtnV: false 
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_equal$4*] 
   ;; %_equal$4* 
;; innerP  2
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_equal$4*]
   %R1 = getelementptr %_equal$4,%_equal$4 *%R0, i32 0, i32 0
%R2 = load %vdt_type$_equal$4*, %vdt_type$_equal$4** %R1
   %R3 = getelementptr %vdt_type$_equal$4,%vdt_type$_equal$4* %R2, i32 0, i32 1
%R4 = load  i8*(i8*)*, i8*(i8*)** %R3
   %V5 = icmp eq i8*(i8*)* %R4, null
   br i1 %V5, label %L6, label %L7
L7:
   ;; inner not null
      %R8 = bitcast %_equal$4* %R0 to i8*
call i8* %R4(i8* %R8)
   br label %L6
L6:
   br label %L2
L2:
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_equal$4*] 
   ;; %_equal$4* 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_equal$4*]
   ret %_equal$4* %R0   ;; vTop(0,0)=[] rTop(0,1)=[]
}
   ;; vdt:vdtTop: 2 4:I,0:I
@vdt_data$_equal$4 = global %vdt_type$_equal$4 {
      %_equal$4*(%_equal$4*)* @_equal$4,
      i8* (i8* )* null
}

define %vdt_ret$_equal$4* @vdt_alloc$_equal$4(%Value$2* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$_equal$4
   %R10 = tail call i8* @malloc(i64 32)
   %R11 = bitcast i8* %R10 to %vdt_ret$_equal$4*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %_equal$4 
   ;; alloc %_equal$4
   %R12 = tail call i8* @malloc(i64 192)
   %R13 = bitcast i8* %R12 to %_equal$4*
   ;; store VDT in object
   %R14 = getelementptr %_equal$4, %_equal$4* %R13, i32 0, i32 0
   store %vdt_type$_equal$4* @vdt_data$_equal$4, %vdt_type$_equal$4** %R14
   %R15 = getelementptr %vdt_ret$_equal$4,%vdt_ret$_equal$4* %R11, i32 0, i32 0
   store %_equal$4* %R13, %_equal$4** %R15
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: Value thisClassOrgDescNo: 2 
   ;; vTop(0,0)=[] rTop(1,1)=[1:%Value$2*] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%Value$2*,13:%_equal$4] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%Value$2*,13:%_equal$4]
   ;; before:handleOrigins: 4 
   ;; handleOrigins:NEW: = 
;; rdouble -1
   ;; vTop(0,0)=[] rTop(2,2)=[1:%Value$2*,13:%_equal$4]
   ;; vTop(0,0)=[] rTop(3,3)=[1:%Value$2*,13:%_equal$4,13:%_equal$4] 
   ;; vTop(0,0)=[] rTop(3,3)=[1:%Value$2*,1:%Value$2*,13:%_equal$4]
;; rstoreX 1 =$6 isValueObjectOrigin: F
   ;; vTop(0,0)=[] rTop(3,3)=[1:%Value$2*,1:%Value$2*,13:%_equal$4]
   ;; lookup:  %Value$2*
   ;; vTop(0,0)=[] rTop(3,3)=[1:%Value$2*,1:%Value$2*,13:%_equal$4]
   %R16 = getelementptr %_equal$6, %_equal$6 * %R13, i32 0, i32 1
   store %Value$2* %R1, %Value$2** %R16
;; rswap 0
   ;; vTop(0,0)=[] rTop(2,3)=[1:%Value$2*,13:%_equal$4]
;; rswap 0
   ;; goOriginAdr:  "" 
   ;; goOriginAdr:isImplSuper: 
   ;; vTop(0,0)=[] rTop(2,3)=[13:%_equal$4,1:%Value$2*]
   ;; OBS! we need the correct off of value object in holder object 
;; pushc 4
   %V17 = add i32 0, 4
;; pushc 4
   %V18 = add i32 0, 4
;; rstoreX 1 =$6 isValueObjectOrigin: T
   ;; vTop(2,2)=[17/0,18/0] rTop(2,3)=[13:%_equal$4,1:%Value$2*]
   ;; lookup:  %Value$2*
   ;; vTop(2,2)=[17/0,18/0] rTop(2,3)=[13:%_equal$4,1:%Value$2*]
   ;; store origin being value object
   %R19 = getelementptr %Value$2,%Value$2 *%R1, i32 0, i32 2
store i32 %V17, i32* %R19
   %R20 = getelementptr %Value$2,%Value$2 *%R1, i32 0, i32 3
store i32 %V18, i32* %R20
   %R21 = getelementptr %_equal$6, %_equal$6 * %R1, i32 0, i32 1
   %R22 = bitcast %Value$2** %R21 to %_equal$4**
   store %_equal$4* %R13, %_equal$4** %R22
;; rswap 0
   ;; handleOrigins:END:  
   ;; after:handleOrigins: 4 
   ret %vdt_ret$_equal$4* %R11
}
   ;; ObjStubStackX:gen 
   ;; OG:reAlloc: descNo: 0 5 "B := length = (V.length){   check: do ;      if (B) :then ;         for(1):to(length):repeat;            if (get(inx) <> V.get(inx)) :then ;       ...}" 
   ;; OG:reAlloc:String: 
   ;; currentDcl:this: 
   ;; reAllocatedOff: "V" 2 
   ;; reAllocatedOff: "B" 3 
   ;; reAllocatedOff: "check" 0 

;; CLASS = 6 1 String 3

define %_equal$6* @_equal$6(%_equal$6* %R0){
   %V0 = add i32 0, 0
   ;; vdtTableCopy: I:1:4 I:2:0
;; rShiftUp  1
   ;;  
call void @notImpl(i32 0)

;; rstore  1 origin
   ;; rstore:ignored 
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_equal$6*] 
   ;; %_equal$6* 
;; rpushg iOrigin 1
   ;; Rtype.rtop: "%_equal$6*" typeInfo[rtop,off]=elmType: "%Value$2*" 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_equal$6*] 
   %R1 = getelementptr %_equal$6,%_equal$6 *%R0, i32 0, i32 1
   %R2 = load %Value$2* , %Value$2** %R1
   ;; vTop(0,0)=[] rTop(1,1)=[2:%Value$2*] 
;; rShiftDown  1
   ;;  
call void @notImpl(i32 0)

;; rstore  1 origin
   ;; rstore:ignored 
;; DO:
   br label %L1
L1:
;; pushThis 
   ;; vTop(0,0)=[] rTop(2,2)=[2:%Value$2*,0:%_equal$6*] 
   ;; %_equal$6* 
   ;; superAdj:E 
   ;; AssignmentStatement:gen: "B := length = (V.length)" right.label: "ObjectGenerator" "length = (V.length)" 
   ;; OG:gen: "length = (V.length)" 
   ;; OG:before:super.gen: "length = (V.length)" 
   ;; doNeedOrigin:Ex: "length" 
;; pushThis 
   ;; vTop(0,0)=[] rTop(3,3)=[2:%Value$2*,0:%_equal$6*,0:%_equal$6*] 
   ;; %_equal$6* 
   ;; superAdj:E 
;; rpushg =$6 1
   ;; Rtype.rtop: "%_equal$6*" typeInfo[rtop,off]=elmType: "%Value$2*" 
   ;; vTop(0,0)=[] rTop(3,3)=[2:%Value$2*,0:%_equal$6*,0:%_equal$6*] 
   %R3 = getelementptr %_equal$6,%_equal$6 *%R0, i32 0, i32 1
   %R4 = load %Value$2* , %Value$2** %R3
   ;; vTop(0,0)=[] rTop(3,3)=[2:%Value$2*,0:%_equal$6*,4:%Value$2*] 
   ;; ptn:loadArgs:E "length" 
   ;; {(ObjectInvocation_Unary; (name: "length"); (Arguments))} 
   ;; args: "" 
   ;; OI:invoke: "length" 
   ;; ptn:invoke: "length" E: "= (V.length)" ptnKind: 0 useRtnV: true 
;; invoke length 7 0 0
   ;; vTop(0,0)=[] rTop(3,3)=[2:%Value$2*,0:%_equal$6*,4:%Value$2*]
   ;; alloc %length$7
   %R5 = tail call i8* @malloc(i64 12)
   %R6 = bitcast i8* %R5 to %length$7*
   ;; store VDT in object
   %R7 = getelementptr %length$7, %length$7* %R6, i32 0, i32 0
   store %vdt_type$length$7* @vdt_data$length$7, %vdt_type$length$7** %R7
   ;; vTop(0,0)=[] rTop(4,4)=[2:%Value$2*,0:%_equal$6*,4:%Value$2*,6:%length$7] 
   ;; store:args 
   ;; after:store:args:top: 0 
;; rstoreX 1 length$7 isValueObjectOrigin: F
   ;; vTop(0,0)=[] rTop(4,4)=[2:%Value$2*,0:%_equal$6*,4:%Value$2*,6:%length$7]
   ;; lookup:  %String$3*
   ;; vTop(0,0)=[] rTop(4,4)=[2:%Value$2*,0:%_equal$6*,4:%Value$2*,6:%length$7]
   %R8 = getelementptr %length$7, %length$7 * %R6, i32 0, i32 1
   %R9 = bitcast %String$3** %R8 to %Value$2**
   store %Value$2* %R4, %Value$2** %R9
;; rswap 0
   %R10 = call %length$7* @length$7(%length$7 * %R6)
   ;; vTop(0,0)=[] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,6:%length$7*] 
   %V13 = icmp eq %length$7* %R10, %R6
   br i1 %V13, label %normalRtnLab11, label %breakLab12
breakLab12:
   %R14 = bitcast %length$7* %R10 to %_equal$6*
   %V15 = icmp eq %_equal$6* %R0, %R14
   br i1 %V15, label %selectBreakLab17, label %contBreakLab16
contBreakLab16:
   ret %_equal$6* %R14
selectBreakLab17:
   %R18 = bitcast %length$7* %R10 to [0 x i32]*
   %R19 = getelementptr [0 x i32], [0 x i32]* %R18, i32 0, i32 0
   %V20 = load i32 , i32* %R19
   %R21 = getelementptr %length$7,%length$7* %R10, i32 0, i32 0
   store %vdt_type$length$7* @vdt_data$length$7, %vdt_type$length$7** %R21
   %V22 = icmp eq i32 1, %V20
   br i1 %V22, label %X23, label %X24
X23:
   br label %L1 ; restart
X24:
   br label %L2 ; leave
normalRtnLab11:

   ;; vTop(0,0)=[] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,6:%length$7*]
;; pushg 2 
   %R25 = getelementptr %length$7,%length$7 *%R6, i32 0, i32 2
   %V26 = load i32, i32* %R25
   ;; IV:after:computeAdr:superAdj: 0 :Adr:off:0 size:0 isFloat:F isUnitVal:F superAdj:0 isUnique:F isValue:F originIsValue:F:E:"= (V.length)":rec:- 
   ;; rec:  "length" E:  "= (V.length)" 
   ;; ptn:loadArgs:E "= (V.length)" 
   ;; {(ObjectInvocation_Binary; (name: "="); (Arguments;  (ObjectGenerator;   (Invocation;    (BracketedExp;     (Invocation;      (ObjectInvocation_Unary;       (name: "V");   ...} 
   ;; args: "(V.length)" 
   ;; E: "ObjectGenerator" (V.length) 
   ;; E.arg: "var" in V: var this(Value) 
   ;; NonVirt: "= (V.length)" 
   ;; ActArg:  "(V.length)" isValue:  false 
   ;; loadArgs:A: "(V.length)" 
   ;; OG:gen: "(V.length)" 
   ;; OG:before:super.gen: "(V.length)" 
   ;; doNeedOrigin:Ex: "(V.length)" 
;; pushThis 
   ;; vTop(1,1)=[26/0] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,0:%_equal$6*] 
   ;; %_equal$6* 
   ;; superAdj:E 
   ;; OI:invoke: "V" 
   ;; DI:invoke: "in V: var this(Value)" 
;; pushc 2
   %V27 = add i32 0, 2
;; pushc 12
   %V28 = add i32 0, 12
   ;; IV:after:computeAdr:superAdj: 0 :Adr:off:0 size:0 isFloat:F isUnitVal:F superAdj:0 isUnique:F isValue:F originIsValue:F:E:"length":rec:- 
   ;; rec:  "V" E:  "length" 
   ;; ptn:loadArgs:E "length" 
   ;; {(ObjectInvocation_Unary; (name: "length"); (Arguments))} 
   ;; args: "" 
   ;; OI:invoke: "length" 
   ;; ptn:invoke: "length" E: "length" ptnKind: 0 useRtnV: true 
;; invoke length 7 0 0
   ;; vTop(3,3)=[26/0,27/0,28/0] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,0:%_equal$6*]
   ;; alloc %length$7
   %R29 = tail call i8* @malloc(i64 12)
   %R30 = bitcast i8* %R29 to %length$7*
   ;; store VDT in object
   %R31 = getelementptr %length$7, %length$7* %R30, i32 0, i32 0
   store %vdt_type$length$7* @vdt_data$length$7, %vdt_type$length$7** %R31
   ;; vTop(3,3)=[26/0,27/0,28/0] rTop(4,4)=[2:%Value$2*,0:%_equal$6*,0:%_equal$6*,30:%length$7] 
   ;; store:args 
   ;; after:store:args:top: 0 
;; rstoreX 1 length$7 isValueObjectOrigin: F
   ;; vTop(3,3)=[26/0,27/0,28/0] rTop(4,4)=[2:%Value$2*,0:%_equal$6*,0:%_equal$6*,30:%length$7]
   ;; lookup:  %String$3*
   ;; vTop(3,3)=[26/0,27/0,28/0] rTop(4,4)=[2:%Value$2*,0:%_equal$6*,0:%_equal$6*,30:%length$7]
   %R32 = getelementptr %length$7, %length$7 * %R30, i32 0, i32 1
   %R33 = bitcast %String$3** %R32 to %_equal$6**
   store %_equal$6* %R0, %_equal$6** %R33
;; rswap 0
   %R34 = call %length$7* @length$7(%length$7 * %R30)
   ;; vTop(3,3)=[26/0,27/0,28/0] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,30:%length$7*] 
   %V37 = icmp eq %length$7* %R34, %R30
   br i1 %V37, label %normalRtnLab35, label %breakLab36
breakLab36:
   %R38 = bitcast %length$7* %R34 to %_equal$6*
   %V39 = icmp eq %_equal$6* %R0, %R38
   br i1 %V39, label %selectBreakLab41, label %contBreakLab40
contBreakLab40:
   ret %_equal$6* %R38
selectBreakLab41:
   %R42 = bitcast %length$7* %R34 to [0 x i32]*
   %R43 = getelementptr [0 x i32], [0 x i32]* %R42, i32 0, i32 0
   %V44 = load i32 , i32* %R43
   %R45 = getelementptr %length$7,%length$7* %R34, i32 0, i32 0
   store %vdt_type$length$7* @vdt_data$length$7, %vdt_type$length$7** %R45
   %V46 = icmp eq i32 1, %V44
   br i1 %V46, label %X47, label %X48
X47:
   br label %L1 ; restart
X48:
   br label %L2 ; leave
normalRtnLab35:

   ;; vTop(3,3)=[26/0,27/0,28/0] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,30:%length$7*]
;; pushg 2 
   %R49 = getelementptr %length$7,%length$7 *%R30, i32 0, i32 2
   %V50 = load i32, i32* %R49
   ;; loadArgs:after:gen: "= (V.length)" 
   ;; end:loadArgs:NonVirt: "= (V.length)" 
   ;; OI:invoke: "= (V.length)" 
   ;; ptn:invoke: "=  " E: "= (V.length)" ptnKind: 1 useRtnV: true 
   %V51 = icmp eq i32 %V28, %V50
;; storeg =$6 3
   %R52 = getelementptr %_equal$6,%_equal$6 *%R0, i32 0, i32 3
   %V53 = zext i1 %V51 to i32
   store i32 %V53, i32* %R52
   ;; OG:gen: "if (B) :then {      for(1):to(length):repeat;         if (get(inx) <> V.get(inx)) :then ;            B := false;            leave(#check);      }" 
;; pushThis 
   ;; vTop(2,4)=[26/0,27/0] rTop(2,4)=[2:%Value$2*,0:%_equal$6*] 
   ;; %_equal$6* 
;; invoke check 14 0 0
   ;; vTop(2,4)=[26/0,27/0] rTop(2,4)=[2:%Value$2*,0:%_equal$6*]
   ;; alloc %check$14
   %R54 = tail call i8* @malloc(i64 8)
   %R55 = bitcast i8* %R54 to %check$14*
   ;; store VDT in object
   %R56 = getelementptr %check$14, %check$14* %R55, i32 0, i32 0
   store %vdt_type$check$14* @vdt_data$check$14, %vdt_type$check$14** %R56
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,55:%check$14] 
   ;; store:args 
   ;; after:store:args:top: 0 
;; rstoreX 1 check$14 isValueObjectOrigin: F
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,55:%check$14]
   ;; lookup:  %_equal$6*
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,0:%_equal$6*,55:%check$14]
   %R57 = getelementptr %check$14, %check$14 * %R55, i32 0, i32 1
   store %_equal$6* %R0, %_equal$6** %R57
;; rswap 0
   %R58 = call %check$14* @check$14(%check$14 * %R55)
   ;; vTop(2,4)=[26/0,27/0] rTop(2,4)=[2:%Value$2*,55:%check$14*] 
   %V61 = icmp eq %check$14* %R58, %R55
   br i1 %V61, label %normalRtnLab59, label %breakLab60
breakLab60:
   %R62 = bitcast %check$14* %R58 to %_equal$6*
   %V63 = icmp eq %_equal$6* %R0, %R62
   br i1 %V63, label %selectBreakLab65, label %contBreakLab64
contBreakLab64:
   ret %_equal$6* %R62
selectBreakLab65:
   %R66 = bitcast %check$14* %R58 to [0 x i32]*
   %R67 = getelementptr [0 x i32], [0 x i32]* %R66, i32 0, i32 0
   %V68 = load i32 , i32* %R67
   %R69 = getelementptr %check$14,%check$14* %R58, i32 0, i32 0
   store %vdt_type$check$14* @vdt_data$check$14, %vdt_type$check$14** %R69
   %V70 = icmp eq i32 1, %V68
   br i1 %V70, label %X71, label %X72
X71:
   br label %L1 ; restart
X72:
   br label %L2 ; leave
normalRtnLab59:

   ;; vTop(2,4)=[26/0,27/0] rTop(2,4)=[2:%Value$2*,55:%check$14*]
;; rpop 
   br label %L2
L2:
;; pushThis 
   ;; vTop(2,4)=[26/0,27/0] rTop(2,4)=[2:%Value$2*,0:%_equal$6*] 
   ;; %_equal$6* 
   ;; vTop(2,4)=[26/0,27/0] rTop(2,4)=[2:%Value$2*,0:%_equal$6*]
   ret %_equal$6* %R0   ;; vTop(2,4)=[26/0,27/0] rTop(1,4)=[2:%Value$2*]
}
   ;; vdt:vdtTop: 2 4:I,6:I
@vdt_data$_equal$6 = global %vdt_type$_equal$6 {
      %_equal$4*(%_equal$4*)* @_equal$4,
      %_equal$6*(%_equal$6*)* @_equal$6
}

define %vdt_ret$_equal$6* @vdt_alloc$_equal$6(%String$3* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$_equal$6
   %R74 = tail call i8* @malloc(i64 32)
   %R75 = bitcast i8* %R74 to %vdt_ret$_equal$6*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %_equal$6 
   ;; alloc %_equal$6
   %R76 = tail call i8* @malloc(i64 192)
   %R77 = bitcast i8* %R76 to %_equal$6*
   ;; store VDT in object
   %R78 = getelementptr %_equal$6, %_equal$6* %R77, i32 0, i32 0
   store %vdt_type$_equal$6* @vdt_data$_equal$6, %vdt_type$_equal$6** %R78
   %R79 = getelementptr %vdt_ret$_equal$6,%vdt_ret$_equal$6* %R75, i32 0, i32 0
   store %_equal$6* %R77, %_equal$6** %R79
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: String thisClassOrgDescNo: 3 
   ;; vTop(2,4)=[26/0,27/0] rTop(2,4)=[2:%Value$2*,1:%String$3*] 
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,1:%String$3*,77:%_equal$6] 
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,1:%String$3*,77:%_equal$6]
   ;; before:handleOrigins: 6 
   ;; handleOrigins:NEW: = 
;; rdouble -1
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,1:%String$3*,77:%_equal$6]
   ;; vTop(2,4)=[26/0,27/0] rTop(4,4)=[2:%Value$2*,1:%String$3*,77:%_equal$6,77:%_equal$6] 
   ;; vTop(2,4)=[26/0,27/0] rTop(4,4)=[2:%Value$2*,1:%String$3*,1:%String$3*,77:%_equal$6]
;; rstoreX 1 =$6 isValueObjectOrigin: F
   ;; vTop(2,4)=[26/0,27/0] rTop(4,4)=[2:%Value$2*,1:%String$3*,1:%String$3*,77:%_equal$6]
   ;; lookup:  %Value$2*
   ;; vTop(2,4)=[26/0,27/0] rTop(4,4)=[2:%Value$2*,1:%String$3*,1:%String$3*,77:%_equal$6]
   %R80 = getelementptr %_equal$6, %_equal$6 * %R77, i32 0, i32 1
   %R81 = bitcast %Value$2** %R80 to %String$3**
   store %String$3* %R1, %String$3** %R81
;; rswap 0
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,1:%String$3*,77:%_equal$6]
;; rswap 0
   ;; goOriginAdr:  "" 
   ;; goOriginAdr:isImplSuper: 
   ;; vTop(2,4)=[26/0,27/0] rTop(3,4)=[2:%Value$2*,77:%_equal$6,1:%String$3*]
   ;; OBS! we need the correct off of value object in holder object 
;; pushc 4
   %V82 = add i32 0, 4
;; pushc 4
   %V83 = add i32 0, 4
;; rstoreX 1 =$6 isValueObjectOrigin: T
   ;; vTop(4,4)=[26/0,27/0,82/0,83/0] rTop(3,4)=[2:%Value$2*,77:%_equal$6,1:%String$3*]
   ;; lookup:  %Value$2*
   ;; vTop(4,4)=[26/0,27/0,82/0,83/0] rTop(3,4)=[2:%Value$2*,77:%_equal$6,1:%String$3*]
   ;; store origin being value object
   %R84 = getelementptr %String$3,%String$3 *%R1, i32 0, i32 2
store i32 %V82, i32* %R84
   %R85 = getelementptr %String$3,%String$3 *%R1, i32 0, i32 3
store i32 %V83, i32* %R85
   %R86 = getelementptr %_equal$6, %_equal$6 * %R1, i32 0, i32 1
   %R87 = bitcast %Value$2** %R86 to %_equal$6**
   store %_equal$6* %R77, %_equal$6** %R87
;; rswap 0
   ;; handleOrigins:END:  
   ;; after:handleOrigins: 6 
   ret %vdt_ret$_equal$6* %R75
}
   ;; ObjStubStackX:gen 

;; CLASS Boolean 10 0 MiniBeta 1 isValueObj

define %Boolean$10* @Boolean$10(%Boolean$10* %R0, i32 %off){
   %V0 = add i32 0, 0
;; DO:
   br label %L1
L1:
   br label %L2
L2:
   ;; vTop(0,0)=[] rTop(0,0)=[]
   ret %Boolean$10* %R0   ;; vTop(0,0)=[] rTop(-1,0)=[]
}
   ;; vdt:vdtTop: 1 10:I
@vdt_data$Boolean$10 = global %vdt_type$Boolean$10 {
      %Boolean$10*(%Boolean$10*, i32)* @Boolean$10
}

define %vdt_ret$Boolean$10* @vdt_alloc$Boolean$10(%MiniBeta$1* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$Boolean$10
   %R2 = tail call i8* @malloc(i64 32)
   %R3 = bitcast i8* %R2 to %vdt_ret$Boolean$10*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %Boolean$10 
   ;; alloc %Boolean$10
   %R4 = tail call i8* @malloc(i64 192)
   %R5 = bitcast i8* %R4 to %Boolean$10*
   ;; store VDT in object
   %R6 = getelementptr %Boolean$10, %Boolean$10* %R5, i32 0, i32 0
   store %vdt_type$Boolean$10* @vdt_data$Boolean$10, %vdt_type$Boolean$10** %R6
   %R7 = getelementptr %vdt_ret$Boolean$10,%vdt_ret$Boolean$10* %R3, i32 0, i32 0
   store %Boolean$10* %R5, %Boolean$10** %R7
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: MiniBeta thisClassOrgDescNo: 1 
;; rpush:rtop: 0
   ;; vTop(0,0)=[] rTop(0,0)=[] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%Boolean$10] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%Boolean$10]
   ;; before:handleOrigins: 10 
   ;; handleOrigins:NEW: Boolean 
   ;; after:handleOrigins: 10 
   ret %vdt_ret$Boolean$10* %R3
}
   ;; ObjStubStackX:gen 

;; CLASS universal 11 0 MiniBeta 1 isValueObj

define %universal$11* @universal$11(%universal$11* %R0, i32 %off){
   %V0 = add i32 0, 0
;; DO:
   br label %L1
L1:
   br label %L2
L2:
   ;; vTop(0,0)=[] rTop(0,0)=[]
   ret %universal$11* %R0   ;; vTop(0,0)=[] rTop(-1,0)=[]
}
   ;; vdt:vdtTop: 1 11:I
@vdt_data$universal$11 = global %vdt_type$universal$11 {
      %universal$11*(%universal$11*, i32)* @universal$11
}

define %vdt_ret$universal$11* @vdt_alloc$universal$11(%MiniBeta$1* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$universal$11
   %R2 = tail call i8* @malloc(i64 32)
   %R3 = bitcast i8* %R2 to %vdt_ret$universal$11*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %universal$11 
   ;; alloc %universal$11
   %R4 = tail call i8* @malloc(i64 192)
   %R5 = bitcast i8* %R4 to %universal$11*
   ;; store VDT in object
   %R6 = getelementptr %universal$11, %universal$11* %R5, i32 0, i32 0
   store %vdt_type$universal$11* @vdt_data$universal$11, %vdt_type$universal$11** %R6
   %R7 = getelementptr %vdt_ret$universal$11,%vdt_ret$universal$11* %R3, i32 0, i32 0
   store %universal$11* %R5, %universal$11** %R7
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: MiniBeta thisClassOrgDescNo: 1 
;; rpush:rtop: 0
   ;; vTop(0,0)=[] rTop(0,0)=[] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%universal$11] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%universal$11]
   ;; before:handleOrigins: 11 
   ;; handleOrigins:NEW: universal 
   ;; after:handleOrigins: 11 
   ret %vdt_ret$universal$11* %R3
}
   ;; ObjStubStackX:gen 

;; CLASS length 7 1 String 3

define %length$7* @length$7(%length$7* %R0){
   %V0 = add i32 0, 0
;; rstore  1 origin
   ;; rstore:ignored 
;; DO:
   br label %L1
L1:
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%length$7*] 
   ;; %length$7* 
   ;; superAdj:E 
   ;; AssignmentStatement:gen: "V := get(0)" right.label: "ObjectGenerator" "get(0)" 
   ;; OG:gen: "get(0)" 
   ;; OG:before:super.gen: "get(0)" 
   ;; doNeedOrigin:Ex: "get(0)" 
;; pushThis 
   ;; vTop(0,0)=[] rTop(2,2)=[0:%length$7*,0:%length$7*] 
   ;; %length$7* 
   ;; superAdj:E 
;; rpushg length$7 1
   ;; Rtype.rtop: "%length$7*" typeInfo[rtop,off]=elmType: "%String$3*" 
   ;; vTop(0,0)=[] rTop(2,2)=[0:%length$7*,0:%length$7*] 
   %R1 = getelementptr %length$7,%length$7 *%R0, i32 0, i32 1
   %R2 = load %String$3* , %String$3** %R1
   ;; vTop(0,0)=[] rTop(2,2)=[0:%length$7*,2:%String$3*] 
   ;; IV:after:computeAdr:superAdj: 0 :Adr:off:0 size:0 isFloat:F isUnitVal:F superAdj:0 isUnique:F isValue:F originIsValue:F:E:"get(0)":rec:- 
   ;; rec:  "get(0)" E:  "get(0)" 
   ;; ptn:loadArgs:E "get(0)" 
   ;; {(ObjectInvocation_KeyWord; (name: "get"); (Arguments;  (name: "get");  (name: "(");  (ObjectGenerator;   (Invocation;    (ConstLiteral 0));   (Items descNo: 0 origDescNo: ...} 
   ;; args: "get(0)" 
   ;; E: "ObjectGenerator" 0 
   ;; E.arg: "var" inx: var integer 
   ;; NonVirt: "get(0)" 
   ;; ActArg:  "0" isValue:  true 
   ;; loadArgs:A: "0" 
   ;; OG:gen: "0" 
   ;; OG:before:super.gen: "0" 
   ;; IV:after:computeAdr:superAdj: 0 
   ;; rec:  "0" E:  "0" 
;; pushc 0
   %V3 = add i32 0, 0
   ;; loadArgs:after:gen: "get(0)" 
   ;; formalArg:isPtn: "inx: var integer" :isBasicVal: true :valueObj: true 
   ;; :actArg: "0" :isBasicVal: true 
   ;; case:B: 0 ObjectGenerator 1 1 1 false true 
   ;; end:loadArgs:NonVirt: "get(0)" 
   ;; OI:invoke: "get(0)" 
   ;; ptn:invoke: "get(inx: var integer)" E: "get(0)" ptnKind: 0 useRtnV: true 
;; xpushg  inx 1 0 1
   ;; vTop(1,1)=[3/0] rTop(2,2)=[0:%length$7*,2:%String$3*]
   %R4 = bitcast %String$3* %R2 to i32*
%V5 = call i32 @arrayLength(i32* %R4)
;; storeg length$7 2
   %R6 = getelementptr %length$7,%length$7 *%R0, i32 0, i32 2
   store i32 %V5, i32* %R6
   br label %L2
L2:
;; pushThis 
   ;; vTop(0,1)=[] rTop(1,2)=[0:%length$7*] 
   ;; %length$7* 
   ;; vTop(0,1)=[] rTop(1,2)=[0:%length$7*]
   ret %length$7* %R0   ;; vTop(0,1)=[] rTop(0,2)=[]
}
   ;; vdt:vdtTop: 1 7:I
@vdt_data$length$7 = global %vdt_type$length$7 {
      %length$7*(%length$7*)* @length$7
}

define %vdt_ret$length$7* @vdt_alloc$length$7(%String$3* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$length$7
   %R8 = tail call i8* @malloc(i64 32)
   %R9 = bitcast i8* %R8 to %vdt_ret$length$7*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %length$7 
   ;; alloc %length$7
   %R10 = tail call i8* @malloc(i64 192)
   %R11 = bitcast i8* %R10 to %length$7*
   ;; store VDT in object
   %R12 = getelementptr %length$7, %length$7* %R11, i32 0, i32 0
   store %vdt_type$length$7* @vdt_data$length$7, %vdt_type$length$7** %R12
   %R13 = getelementptr %vdt_ret$length$7,%vdt_ret$length$7* %R9, i32 0, i32 0
   store %length$7* %R11, %length$7** %R13
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: String thisClassOrgDescNo: 3 
   ;; vTop(0,1)=[] rTop(1,2)=[1:%String$3*] 
   ;; vTop(0,1)=[] rTop(2,2)=[1:%String$3*,11:%length$7] 
   ;; vTop(0,1)=[] rTop(2,2)=[1:%String$3*,11:%length$7]
   ;; before:handleOrigins: 7 
   ;; handleOrigins:NEW: length 
;; rstoreX 1 length$7 isValueObjectOrigin: F
   ;; vTop(0,1)=[] rTop(2,2)=[1:%String$3*,11:%length$7]
   ;; lookup:  %String$3*
   ;; vTop(0,1)=[] rTop(2,2)=[1:%String$3*,11:%length$7]
   %R14 = getelementptr %length$7, %length$7 * %R11, i32 0, i32 1
   store %String$3* %R1, %String$3** %R14
;; rswap 0
   ;; handleOrigins:END:  
   ;; after:handleOrigins: 7 
   ret %vdt_ret$length$7* %R9
}
   ;; ObjStubStackX:gen 

;; CLASS integer 8 0 MiniBeta 1 isValueObj

define %integer$8* @integer$8(%integer$8* %R0, i32 %off){
   %V0 = add i32 0, 0
;; DO:
   br label %L1
L1:
   br label %L2
L2:
   ;; vTop(0,0)=[] rTop(0,0)=[]
   ret %integer$8* %R0   ;; vTop(0,0)=[] rTop(-1,0)=[]
}
   ;; vdt:vdtTop: 1 8:I
@vdt_data$integer$8 = global %vdt_type$integer$8 {
      %integer$8*(%integer$8*, i32)* @integer$8
}

define %vdt_ret$integer$8* @vdt_alloc$integer$8(%MiniBeta$1* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$integer$8
   %R2 = tail call i8* @malloc(i64 32)
   %R3 = bitcast i8* %R2 to %vdt_ret$integer$8*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %integer$8 
   ;; alloc %integer$8
   %R4 = tail call i8* @malloc(i64 192)
   %R5 = bitcast i8* %R4 to %integer$8*
   ;; store VDT in object
   %R6 = getelementptr %integer$8, %integer$8* %R5, i32 0, i32 0
   store %vdt_type$integer$8* @vdt_data$integer$8, %vdt_type$integer$8** %R6
   %R7 = getelementptr %vdt_ret$integer$8,%vdt_ret$integer$8* %R3, i32 0, i32 0
   store %integer$8* %R5, %integer$8** %R7
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: MiniBeta thisClassOrgDescNo: 1 
;; rpush:rtop: 0
   ;; vTop(0,0)=[] rTop(0,0)=[] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%integer$8] 
   ;; vTop(0,0)=[] rTop(1,1)=[5:%integer$8]
   ;; before:handleOrigins: 8 
   ;; handleOrigins:NEW: integer 
   ;; after:handleOrigins: 8 
   ret %vdt_ret$integer$8* %R3
}
   ;; ObjStubStackX:gen 

;; CLASS this 12 1 MiniBeta 1

define %this$12* @this$12(%this$12* %R0){
   %V0 = add i32 0, 0
;; rstore  1 origin
   ;; rstore:ignored 
;; DO:
   br label %L1
L1:
   br label %L2
L2:
;; pushThis 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%this$12*] 
   ;; %this$12* 
   ;; vTop(0,0)=[] rTop(1,1)=[0:%this$12*]
   ret %this$12* %R0   ;; vTop(0,0)=[] rTop(0,1)=[]
}
   ;; vdt:vdtTop: 1 12:I
@vdt_data$this$12 = global %vdt_type$this$12 {
      %this$12*(%this$12*)* @this$12
}

define %vdt_ret$this$12* @vdt_alloc$this$12(%MiniBeta$1* %R1){
   ;; mkVDTalloc:isVstubObject: false 
   ;; alloc %vdt_ret$this$12
   %R2 = tail call i8* @malloc(i64 32)
   %R3 = bitcast i8* %R2 to %vdt_ret$this$12*
   ;; mkVDTalloc:B: 
   ;; vdt_alloc:alloc  %this$12 
   ;; alloc %this$12
   %R4 = tail call i8* @malloc(i64 192)
   %R5 = bitcast i8* %R4 to %this$12*
   ;; store VDT in object
   %R6 = getelementptr %this$12, %this$12* %R5, i32 0, i32 0
   store %vdt_type$this$12* @vdt_data$this$12, %vdt_type$this$12** %R6
   %R7 = getelementptr %vdt_ret$this$12,%vdt_ret$this$12* %R3, i32 0, i32 0
   store %this$12* %R5, %this$12** %R7
   ;; mkVDTalloc:C: 
   ;; thisClassOrgId: MiniBeta thisClassOrgDescNo: 1 
   ;; vTop(0,0)=[] rTop(1,1)=[1:%MiniBeta$1*] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%this$12] 
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%this$12]
   ;; before:handleOrigins: 12 
   ;; handleOrigins:NEW: this 
;; rstoreX 1 this$12 isValueObjectOrigin: F
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%this$12]
   ;; lookup:  %MiniBeta$1*
   ;; vTop(0,0)=[] rTop(2,2)=[1:%MiniBeta$1*,5:%this$12]
   %R8 = getelementptr %this$12, %this$12 * %R5, i32 0, i32 1
   store %MiniBeta$1* %R1, %MiniBeta$1** %R8
;; rswap 0
   ;; handleOrigins:END:  
   ;; after:handleOrigins: 12 
   ret %vdt_ret$this$12* %R3
}
   ;; ObjStubStackX:gen 

;; CLASS check 14 1 = 6

define %check$14* @check$14(%check$14* %R0){
   %V0 = add i32 0, 0
;; rstore  1 origin
   ;; rstore:ignored 
;; DO:
   br label %L1
L1:
   ;; OG:gen: "if (B) :then {   for(1):to(length):repeat;      if (get(inx) <> V.get(inx)) :then ;         B := false;         leave(#check);   }" 
   ;; OG:before:super.gen: "if (B) :then {   for(1):to(length):repeat;      if (get(inx) <> V.get(inx)) :then ;         B := false;         leave(#check);   }" 
