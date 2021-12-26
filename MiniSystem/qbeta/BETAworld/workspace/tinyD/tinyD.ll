;;; Start of LLVM
target triple = "i686-pc-windows-cygnus"
%BETAworld$1 = type {i32*,%BETA$2*,%LIB$8*,%workspace$16*}
%BETA$2 = type {%BETAworld$1*,%ascii$3*}
%ascii$3 = type {%BETA$2*,i32,i32,i32}
%_assign$4 = type {%Value$5*,i32,i32}
%Value$5 = type {}
%char$6 = type {i32}
%universal$7 = type {}
%LIB$8 = type {%BETAworld$1*,i32,%BasicIO$10*,%String$15*}
%integer$9 = type {i32}
%BasicIO$10 = type {%LIB$8*,%keyboard$11*,%screen$12*}
%keyboard$11 = type {%BasicIO$10*}
%screen$12 = type {%BasicIO$10*,%Lock$13*}
%Lock$13 = type {%BasicIO$10*,i32,i32}
%String$14 = type {%LIB$8*}
%String$15 = type {%String$14*}
%workspace$16 = type {%BETAworld$1*,%tinyD$17*}
%tinyD$17 = type {%workspace$16*,i32,%foo$18*,%bar$20*,i32}
%foo$18 = type {%tinyD$17*,i32}
%bar$20 = type {%tinyD$17*,i32}
%_assign$21 = type {%Object$25*,i32}
%put$22 = type {i32}
%fisk$23 = type {%foo$18*,i32,i32}
%fisk$24 = type {%foo$18*,i32,i32}
%Object$25 = type {%BETA$2*}
declare noalias i8* @malloc(i64)
declare noalias i8* @allocIndexed(i32,i32)
declare i32 @puts(i8* nocapture) nounwind
declare i32 @putCh(i32 nocapture) nounwind

@S.Object$25 = private unnamed_addr constant [8 x i8] c"Object\0A\00"
define %Object$25* @Object$25(%Object$25 *%R0){
   %S = getelementptr [8 x i8], [8 x i8]* @S.Object$25, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%Object$25*]
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%Object$25*]
   ret %Object$25 *%R0
}
   ;; vdt: 0,0,0,0

@S.BETAworld$1 = private unnamed_addr constant [11 x i8] c"BETAworld\0A\00"
define %BETAworld$1* @BETAworld$1(%BETAworld$1 *%R0){
   %S = getelementptr [11 x i8], [11 x i8]* @S.BETAworld$1, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%BETAworld$1*]
   ;; saveBETAworld
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%BETAworld$1*]
   ;; invoke: "BETA" ; "BETA"
   %R1 =  tail call i8* @malloc(i64 8)
   %R2 = bitcast i8* %R1 to %BETA$2 *
   ; new %BETA$2
   ;; vTop(0,0)=[] rTop(2,2)=[0:%BETAworld$1*,2:%BETA$2]
   ;; rstoreX "BETA$2" 1
   %R3 = getelementptr %BETA$2, %BETA$2 * %R2, i32 0, i32 0
   store %BETAworld$1* %R0, %BETAworld$1** %R3
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %BETA$2* @BETA$2(%BETA$2 * %R2)
   ;; push return value 2 %BETA$2*
   ;; vTop(0,0)=[] rTop(1,2)=[2:%BETA$2*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%BETAworld$1*]
   ;; invoke: "LIB" ; "LIB"
   %R4 =  tail call i8* @malloc(i64 16)
   %R5 = bitcast i8* %R4 to %LIB$8 *
   ; new %LIB$8
   ;; vTop(0,0)=[] rTop(2,2)=[0:%BETAworld$1*,5:%LIB$8]
   ;; rstoreX "LIB$8" 1
   %R6 = getelementptr %LIB$8, %LIB$8 * %R5, i32 0, i32 0
   store %BETAworld$1* %R0, %BETAworld$1** %R6
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %LIB$8* @LIB$8(%LIB$8 * %R5)
   ;; push return value 5 %LIB$8*
   ;; vTop(0,0)=[] rTop(1,2)=[5:%LIB$8*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%BETAworld$1*]
   ;; invoke: "workspace" ; "workspace"
   %R7 =  tail call i8* @malloc(i64 8)
   %R8 = bitcast i8* %R7 to %workspace$16 *
   ; new %workspace$16
   ;; vTop(0,0)=[] rTop(2,2)=[0:%BETAworld$1*,8:%workspace$16]
   ;; rstoreX "workspace$16" 1
   %R9 = getelementptr %workspace$16, %workspace$16 * %R8, i32 0, i32 0
   store %BETAworld$1* %R0, %BETAworld$1** %R9
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %workspace$16* @workspace$16(%workspace$16 * %R8)
   ;; push return value 8 %workspace$16*
   ;; vTop(0,0)=[] rTop(1,2)=[8:%workspace$16*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%BETAworld$1*]
   ret %BETAworld$1 *%R0
}
   ;; vdt: 0,0,0,0

@S.BETA$2 = private unnamed_addr constant [6 x i8] c"BETA\0A\00"
define %BETA$2* @BETA$2(%BETA$2 *%R0){
   %S = getelementptr [6 x i8], [6 x i8]* @S.BETA$2, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%BETA$2*]
   ;; invoke: "ascii" ; "ascii"
   %R1 =  tail call i8* @malloc(i64 16)
   %R2 = bitcast i8* %R1 to %ascii$3 *
   ; new %ascii$3
   ;; vTop(0,0)=[] rTop(2,2)=[0:%BETA$2*,2:%ascii$3]
   ;; rstoreX "ascii$3" 1
   %R3 = getelementptr %ascii$3, %ascii$3 * %R2, i32 0, i32 0
   store %BETA$2* %R0, %BETA$2** %R3
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %ascii$3* @ascii$3(%ascii$3 * %R2)
   ;; push return value 2 %ascii$3*
   ;; vTop(0,0)=[] rTop(1,2)=[2:%ascii$3*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%BETA$2*]
   ret %BETA$2 *%R0
}
   ;; vdt: 0,0,0,0

@S.ascii$3 = private unnamed_addr constant [7 x i8] c"ascii\0A\00"
define %ascii$3* @ascii$3(%ascii$3 *%R0){
   %S = getelementptr [7 x i8], [7 x i8]* @S.ascii$3, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   %V1 = add i32 0, 10
   ;; pushThis
   ;; vTop(1,1)=[1] rTop(1,1)=[0:%ascii$3*]
   ;; storeg ascii$3 2
   %R2 = getelementptr %ascii$3,%ascii$3 *%R0, i32 0, i32 1
      store i32 %V1, i32* %R2
   %V3 = add i32 0, 13
   ;; pushThis
   ;; vTop(1,1)=[3] rTop(1,1)=[0:%ascii$3*]
   ;; storeg ascii$3 3
   %R4 = getelementptr %ascii$3,%ascii$3 *%R0, i32 0, i32 2
      store i32 %V3, i32* %R4
   br label %L1
L1:
   ;; pushThis
   ;; vTop(0,1)=[] rTop(1,1)=[0:%ascii$3*]
   %V5 = add i32 0, 13
   ;; storeg ascii$3 4
   %R6 = getelementptr %ascii$3,%ascii$3 *%R0, i32 0, i32 3
      store i32 %V5, i32* %R6
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,1)=[] rTop(1,1)=[0:%ascii$3*]
   ret %ascii$3 *%R0
}
   ;; vdt: 0,0,0,0

@S.Value$5 = private unnamed_addr constant [7 x i8] c"Value\0A\00"
define %Value$5* @Value$5(%Value$5 *%R0){
   %S = getelementptr [7 x i8], [7 x i8]* @S.Value$5, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   br label %L1
L1:
   br label %L2
L2:
   ret %Value$5 *%R0
}
   ;; vdt: 0,0,0,0

@S.char$6 = private unnamed_addr constant [6 x i8] c"char\0A\00"
define %char$6* @char$6(%char$6 *%R0){
   %S = getelementptr [6 x i8], [6 x i8]* @S.char$6, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   br label %L1
L1:
   br label %L2
L2:
   ret %char$6 *%R0
}
   ;; vdt: 0,0,0,0

@S.universal$7 = private unnamed_addr constant [11 x i8] c"universal\0A\00"
define %universal$7* @universal$7(%universal$7 *%R0){
   %S = getelementptr [11 x i8], [11 x i8]* @S.universal$7, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   br label %L1
L1:
   br label %L2
L2:
   ret %universal$7 *%R0
}
   ;; vdt: 0,0,0,0

@S._assign$4 = private unnamed_addr constant [9 x i8] c"_assign\0A\00"
define %_assign$4* @_assign$4(%_assign$4 *%R0){
   %S = getelementptr [9 x i8], [9 x i8]* @S._assign$4, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; store originOff originOff
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_assign$4*]
   ret %_assign$4 *%R0
}
   ;; vdt: 0,0,0,0

@S.LIB$8 = private unnamed_addr constant [5 x i8] c"LIB\0A\00"
define %LIB$8* @LIB$8(%LIB$8 *%R0){
   %S = getelementptr [5 x i8], [5 x i8]* @S.LIB$8, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%LIB$8*]
   ;; invoke: "BasicIO" ; "BasicIO"
   %R1 =  tail call i8* @malloc(i64 12)
   %R2 = bitcast i8* %R1 to %BasicIO$10 *
   ; new %BasicIO$10
   ;; vTop(0,0)=[] rTop(2,2)=[0:%LIB$8*,2:%BasicIO$10]
   ;; rstoreX "BasicIO$10" 1
   %R3 = getelementptr %BasicIO$10, %BasicIO$10 * %R2, i32 0, i32 0
   store %LIB$8* %R0, %LIB$8** %R3
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %BasicIO$10* @BasicIO$10(%BasicIO$10 * %R2)
   ;; push return value 2 %BasicIO$10*
   ;; vTop(0,0)=[] rTop(1,2)=[2:%BasicIO$10*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%LIB$8*]
   ;; invoke: "String" ; "String"
   %R4 =  tail call i8* @malloc(i64 4)
   %R5 = bitcast i8* %R4 to %String$14 *
   ; new %String$14
   ;; vTop(0,0)=[] rTop(2,2)=[0:%LIB$8*,5:%String$14]
   ;; rstoreX "String$14" 1
   %R6 = getelementptr %String$14, %String$14 * %R5, i32 0, i32 0
   store %LIB$8* %R0, %LIB$8** %R6
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %String$14* @String$14(%String$14 * %R5)
   ;; push return value 5 %String$14*
   ;; vTop(0,0)=[] rTop(1,2)=[5:%String$14*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%LIB$8*]
   ret %LIB$8 *%R0
}
   ;; vdt: 0,0,0,0

@S.integer$9 = private unnamed_addr constant [9 x i8] c"integer\0A\00"
define %integer$9* @integer$9(%integer$9 *%R0){
   %S = getelementptr [9 x i8], [9 x i8]* @S.integer$9, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   br label %L1
L1:
   br label %L2
L2:
   ret %integer$9 *%R0
}
   ;; vdt: 0,0,0,0

@S.BasicIO$10 = private unnamed_addr constant [9 x i8] c"BasicIO\0A\00"
define %BasicIO$10* @BasicIO$10(%BasicIO$10 *%R0){
   %S = getelementptr [9 x i8], [9 x i8]* @S.BasicIO$10, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%BasicIO$10*]
   ;; invoke: "keyboard" ; "keyboard"
   %R1 =  tail call i8* @malloc(i64 4)
   %R2 = bitcast i8* %R1 to %keyboard$11 *
   ; new %keyboard$11
   ;; vTop(0,0)=[] rTop(2,2)=[0:%BasicIO$10*,2:%keyboard$11]
   ;; rstoreX "keyboard$11" 1
   %R3 = getelementptr %keyboard$11, %keyboard$11 * %R2, i32 0, i32 0
   store %BasicIO$10* %R0, %BasicIO$10** %R3
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %keyboard$11* @keyboard$11(%keyboard$11 * %R2)
   ;; push return value 2 %keyboard$11*
   ;; vTop(0,0)=[] rTop(1,2)=[2:%keyboard$11*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%BasicIO$10*]
   ;; invoke: "screen" ; "screen"
   %R4 =  tail call i8* @malloc(i64 8)
   %R5 = bitcast i8* %R4 to %screen$12 *
   ; new %screen$12
   ;; vTop(0,0)=[] rTop(2,2)=[0:%BasicIO$10*,5:%screen$12]
   ;; rstoreX "screen$12" 1
   %R6 = getelementptr %screen$12, %screen$12 * %R5, i32 0, i32 0
   store %BasicIO$10* %R0, %BasicIO$10** %R6
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %screen$12* @screen$12(%screen$12 * %R5)
   ;; push return value 5 %screen$12*
   ;; vTop(0,0)=[] rTop(1,2)=[5:%screen$12*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%BasicIO$10*]
   ret %BasicIO$10 *%R0
}
   ;; vdt: 0,0,0,0

@S.keyboard$11 = private unnamed_addr constant [10 x i8] c"keyboard\0A\00"
define %keyboard$11* @keyboard$11(%keyboard$11 *%R0){
   %S = getelementptr [10 x i8], [10 x i8]* @S.keyboard$11, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%keyboard$11*]
   ret %keyboard$11 *%R0
}
   ;; vdt: 0,0,0,0

@S.screen$12 = private unnamed_addr constant [8 x i8] c"screen\0A\00"
define %screen$12* @screen$12(%screen$12 *%R0){
   %S = getelementptr [8 x i8], [8 x i8]* @S.screen$12, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%screen$12*]
   ;; rpushg N:BasicIO$10 1 ET:%BasicIO$10* ST:%screen$12*
   %R1 = getelementptr %screen$12, %screen$12*  %R0, i32 0 , i32 0
   %R2 = load %BasicIO$10* , %BasicIO$10** %R1
   ;; invoke: "Lock" ; "Lock"
   %R3 =  tail call i8* @malloc(i64 12)
   %R4 = bitcast i8* %R3 to %Lock$13 *
   ; new %Lock$13
   ;; vTop(0,0)=[] rTop(2,2)=[2:%BasicIO$10*,4:%Lock$13]
   ;; rstoreX "Lock$13" 1
   %R5 = getelementptr %Lock$13, %Lock$13 * %R4, i32 0, i32 0
   store %BasicIO$10* %R2, %BasicIO$10** %R5
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %Lock$13* @Lock$13(%Lock$13 * %R4)
   ;; push return value 4 %Lock$13*
   ;; vTop(0,0)=[] rTop(1,2)=[4:%Lock$13*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%screen$12*]
   ret %screen$12 *%R0
}
   ;; vdt: 0,0,0,0

@S.Lock$13 = private unnamed_addr constant [6 x i8] c"Lock\0A\00"
define %Lock$13* @Lock$13(%Lock$13 *%R0){
   %S = getelementptr [6 x i8], [6 x i8]* @S.Lock$13, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%Lock$13*]
   ret %Lock$13 *%R0
}
   ;; vdt: 0,0,0,0

@S.String$14 = private unnamed_addr constant [8 x i8] c"String\0A\00"
define %String$14* @String$14(%String$14 *%R0){
   %S = getelementptr [8 x i8], [8 x i8]* @S.String$14, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; saveStringOrigin
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%String$14*]
   ret %String$14 *%R0
}
   ;; vdt: 0,0,0,0

@S.String$15 = private unnamed_addr constant [8 x i8] c"String\0A\00"
define %String$15* @String$15(%String$15 *%R0){
   %S = getelementptr [8 x i8], [8 x i8]* @S.String$15, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%String$15*]
   ret %String$15 *%R0
}
   ;; vdt: 0,0,0,0

@S.workspace$16 = private unnamed_addr constant [11 x i8] c"workspace\0A\00"
define %workspace$16* @workspace$16(%workspace$16 *%R0){
   %S = getelementptr [11 x i8], [11 x i8]* @S.workspace$16, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%workspace$16*]
   ;; invoke: "tinyD" ; "tinyD"
   %R1 =  tail call i8* @malloc(i64 20)
   %R2 = bitcast i8* %R1 to %tinyD$17 *
   ; new %tinyD$17
   ;; vTop(0,0)=[] rTop(2,2)=[0:%workspace$16*,2:%tinyD$17]
   ;; rstoreX "tinyD$17" 1
   %R3 = getelementptr %tinyD$17, %tinyD$17 * %R2, i32 0, i32 0
   store %workspace$16* %R0, %workspace$16** %R3
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %tinyD$17* @tinyD$17(%tinyD$17 * %R2)
   ;; push return value 2 %tinyD$17*
   ;; vTop(0,0)=[] rTop(1,2)=[2:%tinyD$17*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%workspace$16*]
   ret %workspace$16 *%R0
}
   ;; vdt: 0,0,0,0

@S.tinyD$17 = private unnamed_addr constant [7 x i8] c"tinyD\0A\00"
define %tinyD$17* @tinyD$17(%tinyD$17 *%R0){
   %S = getelementptr [7 x i8], [7 x i8]* @S.tinyD$17, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%tinyD$17*]
   ;; invoke: "bar" ; "bar"
   %R1 =  tail call i8* @malloc(i64 8)
   %R2 = bitcast i8* %R1 to %bar$20 *
   ; new %bar$20
   ;; vTop(0,0)=[] rTop(2,2)=[0:%tinyD$17*,2:%bar$20]
   ;; rstoreX "bar$20" 1
   %R3 = getelementptr %bar$20, %bar$20 * %R2, i32 0, i32 0
   store %tinyD$17* %R0, %tinyD$17** %R3
   ;; vTop(0,0)=[] rTop(0,2)=[]
   call %bar$20* @bar$20(%bar$20 * %R2)
   ;; push return value 2 %bar$20*
   ;; vTop(0,0)=[] rTop(1,2)=[2:%bar$20*]
   ;; rPop:after: vTop(0,0)=[] rTop(0,2)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,2)=[0:%tinyD$17*]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(2,2)=[0:%tinyD$17*,0:%tinyD$17*]
   ;; invoke: "foo" ; "foo"
   %R4 =  tail call i8* @malloc(i64 8)
   %R5 = bitcast i8* %R4 to %foo$18 *
   ; new %foo$18
   ;; vTop(0,0)=[] rTop(3,3)=[0:%tinyD$17*,0:%tinyD$17*,5:%foo$18]
   ;; rstoreX "foo$18" 1
   %R6 = getelementptr %foo$18, %foo$18 * %R5, i32 0, i32 0
   store %tinyD$17* %R0, %tinyD$17** %R6
   ;; vTop(0,0)=[] rTop(1,3)=[0:%tinyD$17*]
   call %foo$18* @foo$18(%foo$18 * %R5)
   ;; push return value 5 %foo$18*
   ;; vTop(0,0)=[] rTop(2,3)=[0:%tinyD$17*,5:%foo$18*]
   ;; rswap 0
   ;; rstoreg tinyD$17 3
   ;; vTop(0,0)=[] rTop(2,3)=[5:%foo$18*,0:%tinyD$17*]
   %R7 = getelementptr %tinyD$17,%tinyD$17 *%R0, i32 0, i32 2
   ;; types:dst: %foo$18* src: %foo$18*
   ;; vTop(0,0)=[] rTop(2,3)=[5:%foo$18*,0:%tinyD$17*]
   store %foo$18*  %R5, %foo$18* * %R7
   ;; vTop(0,0)=[] rTop(0,3)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,3)=[0:%tinyD$17*]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(2,3)=[0:%tinyD$17*,0:%tinyD$17*]
   ;; invoke: "bar" ; "bar"
   %R8 =  tail call i8* @malloc(i64 8)
   %R9 = bitcast i8* %R8 to %bar$20 *
   ; new %bar$20
   ;; vTop(0,0)=[] rTop(3,3)=[0:%tinyD$17*,0:%tinyD$17*,9:%bar$20]
   ;; rstoreX "bar$20" 1
   %R10 = getelementptr %bar$20, %bar$20 * %R9, i32 0, i32 0
   store %tinyD$17* %R0, %tinyD$17** %R10
   ;; vTop(0,0)=[] rTop(1,3)=[0:%tinyD$17*]
   call %bar$20* @bar$20(%bar$20 * %R9)
   ;; push return value 9 %bar$20*
   ;; vTop(0,0)=[] rTop(2,3)=[0:%tinyD$17*,9:%bar$20*]
   ;; rswap 0
   ;; rstoreg tinyD$17 4
   ;; vTop(0,0)=[] rTop(2,3)=[9:%bar$20*,0:%tinyD$17*]
   %R11 = getelementptr %tinyD$17,%tinyD$17 *%R0, i32 0, i32 3
   ;; types:dst: %bar$20* src: %bar$20*
   ;; vTop(0,0)=[] rTop(2,3)=[9:%bar$20*,0:%tinyD$17*]
   store %bar$20*  %R9, %bar$20* * %R11
   ;; vTop(0,0)=[] rTop(0,3)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,3)=[0:%tinyD$17*]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(2,3)=[0:%tinyD$17*,0:%tinyD$17*]
   ;; rpushg N:tinyD$17 4 ET:%bar$20* ST:%tinyD$17*
   %R12 = getelementptr %tinyD$17, %tinyD$17*  %R0, i32 0 , i32 3
   %R13 = load %bar$20* , %bar$20** %R12
   ;; rswap 0
   ;; rstoreg tinyD$17 3
   ;; vTop(0,0)=[] rTop(2,3)=[13:%bar$20*,0:%tinyD$17*]
   %R14 = getelementptr %tinyD$17,%tinyD$17 *%R0, i32 0, i32 2
   ;; types:dst: %foo$18* src: %bar$20*
   ;; vTop(0,0)=[] rTop(2,3)=[13:%bar$20*,0:%tinyD$17*]
   %R15 = bitcast %bar$20* %R13 to %foo$18*
   ;; vTop(0,0)=[] rTop(2,3)=[13:%bar$20*,0:%tinyD$17*]
   store %foo$18* %R15, %foo$18* * %R14
   ;; vTop(0,0)=[] rTop(0,3)=[]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,3)=[0:%tinyD$17*]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(2,3)=[0:%tinyD$17*,0:%tinyD$17*]
   ;; rpushg N:tinyD$17 3 ET:%foo$18* ST:%tinyD$17*
   %R16 = getelementptr %tinyD$17, %tinyD$17*  %R0, i32 0 , i32 2
   %R17 = load %foo$18* , %foo$18** %R16
   %V18 = add i32 0, 97
   ;; sendv 1 0 fisk
;; vdt: 1 -> descNo, R = alloc(descNo.size), , call descNo proc
   ;; storeg tinyD$17 5
   %R19 = getelementptr %foo$18,%foo$18 *%R17, i32 0, i32 4
      store i32 %V18, i32* %R19
   ;; pushThis
   ;; vTop(0,1)=[] rTop(2,3)=[0:%tinyD$17*,0:%tinyD$17*]
   ;; pushg "tinyD$17" 5
   %R20 = getelementptr %tinyD$17, %tinyD$17*  %R0, i32 0 , i32 4
   %V21 = load i32, i32* %R20
   call i32 @putCh(i32 %V21)

   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,1)=[] rTop(2,3)=[0:%tinyD$17*,0:%tinyD$17*]
   ret %tinyD$17 *%R0
}
   ;; vdt: 0,0,0,0

@S.foo$18 = private unnamed_addr constant [5 x i8] c"foo\0A\00"
define %foo$18* @foo$18(%foo$18 *%R0){
   %S = getelementptr [5 x i8], [5 x i8]* @S.foo$18, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   ;; innerx
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%foo$18*]
   ret %foo$18 *%R0
}
   ;; vdt: 23,0,0,0

@S.fisk$23 = private unnamed_addr constant [6 x i8] c"fisk\0A\00"
define %fisk$23* @fisk$23(%fisk$23 *%R0){
   %S = getelementptr [6 x i8], [6 x i8]* @S.fisk$23, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%fisk$23*]
   ;; pushg "fisk$23" 2
   %R1 = getelementptr %fisk$23, %fisk$23*  %R0, i32 0 , i32 1
   %V2 = load i32, i32* %R1
   call i32 @putCh(i32 %V2)

   ;; pushThis
   ;; vTop(0,1)=[] rTop(1,1)=[0:%fisk$23*]
   ;; pushThis
   ;; vTop(0,1)=[] rTop(1,1)=[0:%fisk$23*]
   ;; pushThis
   ;; vTop(0,1)=[] rTop(2,2)=[0:%fisk$23*,0:%fisk$23*]
   ;; pushg "fisk$23" 2
   %R3 = getelementptr %fisk$23, %fisk$23*  %R0, i32 0 , i32 1
   %V4 = load i32, i32* %R3
   %V5 = add i32 0, 1
   %V6 = add i32 %V4, %V5
   ;; storeg fisk$23 3
   %R7 = getelementptr %fisk$23,%fisk$23 *%R0, i32 0, i32 2
      store i32 %V6, i32* %R7
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,2)=[] rTop(1,2)=[0:%fisk$23*]
   ;; pushg "fisk$23" 3
   %R8 = getelementptr %fisk$23, %fisk$23*  %R0, i32 0 , i32 2
   %V9 = load i32, i32* %R8
   ret %fisk$23 *%R0
}
   ;; vdt: 0,0,0,0

@S.put$22 = private unnamed_addr constant [5 x i8] c"put\0A\00"
define %put$22* @put$22(%put$22 *%R0){
   %S = getelementptr [5 x i8], [5 x i8]* @S.put$22, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%put$22*]
   ret %put$22 *%R0
}
   ;; vdt: 0,0,0,0

@S.bar$20 = private unnamed_addr constant [5 x i8] c"bar\0A\00"
define %bar$20* @bar$20(%bar$20 *%R0){
   %S = getelementptr [5 x i8], [5 x i8]* @S.bar$20, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%bar$20*]
   ;; rpushg N:tinyD$17 1 ET:%tinyD$17* ST:%bar$20*
   %R1 = getelementptr %bar$20, %bar$20*  %R0, i32 0 , i32 0
   %R2 = load %tinyD$17* , %tinyD$17** %R1
   ;; toSuper
   ;; rtnInner
   ret %bar$20 *%R0
   br label %L1
L1:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(2,2)=[2:%tinyD$17*,0:%bar$20*]
   ;; rpushg N:tinyD$17 1 ET:%tinyD$17* ST:%bar$20*
   %R3 = getelementptr %bar$20, %bar$20*  %R0, i32 0 , i32 0
   %R4 = load %tinyD$17* , %tinyD$17** %R3
   %V5 = add i32 0, 117
   ;; storeg tinyD$17 2
   %R6 = getelementptr %tinyD$17,%tinyD$17 *%R4, i32 0, i32 1
      store i32 %V5, i32* %R6
   ;; pushThis
   ;; vTop(0,1)=[] rTop(2,2)=[2:%tinyD$17*,0:%bar$20*]
   %V7 = add i32 0, 118
   ;; storeg bar$20 2
   %R8 = getelementptr %bar$20,%bar$20 *%R0, i32 0, i32 1
      store i32 %V7, i32* %R8
   br label %L2
L2:
   ;; rtnInner
   ret %bar$20 *%R0
}
   ;; vdt: 24,20,0,0

@S.fisk$24 = private unnamed_addr constant [6 x i8] c"fisk\0A\00"
define %fisk$24* @fisk$24(%fisk$24 *%R0){
   %S = getelementptr [6 x i8], [6 x i8]* @S.fisk$24, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%fisk$24*]
   ;; rpushg N:iOrigin 1 ET:%foo$18* ST:%fisk$24*
   %R1 = getelementptr %fisk$24, %fisk$24*  %R0, i32 0 , i32 0
   %R2 = load %foo$18* , %foo$18** %R1
   ;; toSuper
   ;; rtnInner
   ret %fisk$24 *%R0
   br label %L1
L1:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(2,2)=[2:%foo$18*,0:%fisk$24*]
   ;; pushThis
   ;; vTop(0,0)=[] rTop(3,3)=[2:%foo$18*,0:%fisk$24*,0:%fisk$24*]
   ;; pushg "fisk$24" 2
   %R3 = getelementptr %fisk$24, %fisk$24*  %R0, i32 0 , i32 1
   %V4 = load i32, i32* %R3
   %V5 = add i32 0, 1
   %V6 = add i32 %V4, %V5
   ;; storeg fisk$24 2
   %R7 = getelementptr %fisk$24,%fisk$24 *%R0, i32 0, i32 1
      store i32 %V6, i32* %R7
   ;; pushThis
   ;; vTop(0,2)=[] rTop(2,3)=[2:%foo$18*,0:%fisk$24*]
   ;; pushg "fisk$24" 2
   %R8 = getelementptr %fisk$24, %fisk$24*  %R0, i32 0 , i32 1
   %V9 = load i32, i32* %R8
   call i32 @putCh(i32 %V9)

   br label %L2
L2:
   ;; rtnInner
   ret %fisk$24 *%R0
}
   ;; vdt: 24,0,0,0

@S._assign$21 = private unnamed_addr constant [9 x i8] c"_assign\0A\00"
define %_assign$21* @_assign$21(%_assign$21 *%R0){
   %S = getelementptr [9 x i8], [9 x i8]* @S._assign$21, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; rstore origin 1
   br label %L1
L1:
   br label %L2
L2:
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%_assign$21*]
   ret %_assign$21 *%R0
}
   ;; vdt: 0,0,0,0

@S.main$27 = private unnamed_addr constant [6 x i8] c"main\0A\00"
define void @main(i8* %args){
   %S = getelementptr [6 x i8], [6 x i8]* @S.main$27, i64 0, i64 0
   call i32 @puts(i8* %S)
   %V0 = add i32 0, 0
   ;; pushThis
   ;; vTop(0,0)=[] rTop(1,1)=[0:%main$27*]
   ;; invoke: "BETAworld" ; "BETAworld"
   %R1 =  tail call i8* @malloc(i64 16)
   %R2 = bitcast i8* %R1 to %BETAworld$1 *
   ; new %BETAworld$1
   ;; vTop(0,0)=[] rTop(2,2)=[0:%main$27*,2:%BETAworld$1]
   call %BETAworld$1* @BETAworld$1(%BETAworld$1 * %R2)
   ;; push return value 2 %BETAworld$1*
   ;; vTop(0,0)=[] rTop(3,3)=[0:%main$27*,2:%BETAworld$1*,2:%BETAworld$1*]
   ;; stop
   ret void

}
   ;; vdt: 0,0,0,0
