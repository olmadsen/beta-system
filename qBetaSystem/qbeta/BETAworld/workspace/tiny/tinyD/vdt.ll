target triple = "i686-pc-windows-cygnus"
%tinyD$17 = type {i32}
declare noalias i8* @malloc(i64)
declare i32 @putCh(i32 nocapture) nounwind

%foo$18 = type {%vdt_type$foo$18*,%tinyD$17*,i32}

;;--------------------
;; class: foo$18, virtual: fisk$24, off: 0
;; class: foo$18, virtual: hest$26, off: 1
%vdt_type$foo$18 = type {%vdt_ret$fisk$24*()* }

@vdt_data$foo$18 = global %vdt_type$foo$18 {
    %vdt_ret$fisk$24*()* @vdt_alloc$fisk$24
}

%vdt_ret$fisk$24 = type{%fisk$24*,%fisk$24*(%fisk$24*)*}

define %vdt_ret$fisk$24* @vdt_alloc$fisk$24(){
   %R1 = tail call i8* @malloc(i64 8) ;; sizeof(fisk$24))
   %R2 = bitcast i8* %R1 to %fisk$24 *
   %R3 = tail call i8* @malloc(i64 4) ;; sizeof(%vdt_return$fisk$24))
   %R4 = bitcast i8* %R3 to %vdt_ret$fisk$24 *
   %1 = getelementptr %vdt_ret$fisk$24, %vdt_ret$fisk$24* %R4, i32 0, i32 0
   store %fisk$24 * %R2,  %fisk$24 ** %1
   %2 = getelementptr %vdt_ret$fisk$24, %vdt_ret$fisk$24* %R4, i32 0, i32 1
   store  %fisk$24*(%fisk$24*)* @fisk$24, %fisk$24*(%fisk$24*)** %2
   ret %vdt_ret$fisk$24* %R4
}

define %foo$18* @foo$18(%foo$18 *%R0){
   ;; store VDT in %R0[0]
   %R1 = getelementptr %foo$18, %foo$18* %R0, i32 0, i32 0
   store %vdt_type$foo$18* @vdt_data$foo$18, %vdt_type$foo$18** %R1
   ret %foo$18 *%R0
}

;; ----------------------
%fisk$24 = type{i32}
define %fisk$24* @fisk$24(%fisk$24 *%R0){
   call i32 @putCh(i32 98)
   call i32 @putCh(i32 10)
   ret %fisk$24* %R0
}

define void @main(){
   call i32 @putCh(i32 97)
   %R0 = alloca  %fisk$24
   call %fisk$24* @fisk$24(%fisk$24 *%R0)

   ;; lookup in vdt[0]  
   %3 = getelementptr %vdt_type$foo$18, %vdt_type$foo$18* @vdt_data$foo$18 , i32 0, i32 0
   %4 = load %vdt_ret$fisk$24*()*, %vdt_ret$fisk$24*()** %3
   
   ;; call @vdt_alloc$fisk$24
   %5 = call  %vdt_ret$fisk$24* %4()
   %6 = getelementptr %vdt_ret$fisk$24, %vdt_ret$fisk$24* %5, i32 0, i32 1
   %7 = load %fisk$24*(%fisk$24*)*, %fisk$24*(%fisk$24*)** %6
   %8 = getelementptr %vdt_ret$fisk$24, %vdt_ret$fisk$24* %5, i32 0, i32 0
   %9 = load %fisk$24*, %fisk$24** %8
   call i32 @putCh(i32 99)
   call i32 @putCh(i32 10)
   %12 = call %fisk$24* %7(%fisk$24* %9)
   
  ret void
}
