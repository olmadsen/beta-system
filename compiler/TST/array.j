Reading .class from array.class.
Magic number: 0xcafebabe, minor_version: 0, major_version: 46.

Constant pool (count: 25):
#1: Methodref class: 7=java.lang.Object name_and_type: 19=<<init> ()void>
#2: Class name: 20="java/lang/String"
#3: Fieldref class: 6=array name_and_type: 21=<S java.lang.String[]>
#4: Fieldref class: 6=array name_and_type: 22=<Q java.lang.Object[]>
#5: Class name: 11="[Ljava/lang/String;"
#6: Class name: 23="array"
#7: Class name: 24="java/lang/Object"
#8: Utf8: "Q"
#9: Utf8: "[Ljava/lang/Object;"
#10: Utf8: "S"
#11: Utf8: "[Ljava/lang/String;"
#12: Utf8: "<init>"
#13: Utf8: "()V"
#14: Utf8: "Code"
#15: Utf8: "LineNumberTable"
#16: Utf8: "go"
#17: Utf8: "SourceFile"
#18: Utf8: "array.java"
#19: NameAndType name: 12=<init>, signature: 13=()void
#20: Utf8: "java/lang/String"
#21: NameAndType name: 10=S, signature: 11=java.lang.String[]
#22: NameAndType name: 8=Q, signature: 9=java.lang.Object[]
#23: Utf8: "array"
#24: Utf8: "java/lang/Object"

Access flags: 0x421 public super abstract
This class: 6=array, super: 7=java.lang.Object
Interfaces (count: 0):

Fields (count: 2):
Field name:"Q" Signature: 9=java.lang.Object[]
Field name:"S" Signature: 11=java.lang.String[]

Methods (count: 2):

Method name:"<init>" public Signature: 13=()void
Attribute "Code", length:41, max_stack:2, max_locals:1, code_length:13
  0: aload_0
  1: invokespecial #1=<Method java.lang.Object.<init> ()void>
  4: aload_0
  5: iconst_3
  6: anewarray #2=<Class java.lang.String>
  9: putfield #3=<Field array.S java.lang.String[]>
 12: return
Attribute "LineNumberTable", length:10, count: 2
  line: 1 at pc: 0
  line: 3 at pc: 4

Method name:"go" public Signature: 13=()void
Attribute "Code", length:52, max_stack:2, max_locals:1, code_length:20
  0: aload_0
  1: aload_0
  2: getfield #3=<Field array.S java.lang.String[]>
  5: putfield #4=<Field array.Q java.lang.Object[]>
  8: aload_0
  9: aload_0
 10: getfield #4=<Field array.Q java.lang.Object[]>
 13: checkcast #5=<Class [Ljava.lang.String;>
 16: putfield #3=<Field array.S java.lang.String[]>
 19: return
Attribute "LineNumberTable", length:14, count: 3
  line: 5 at pc: 0
  line: 6 at pc: 8
  line: 7 at pc: 19

Attributes (count: 1):
Attribute "SourceFile", length:2, #18="array.java"
