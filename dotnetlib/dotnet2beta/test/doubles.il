// ilasm -exe doubles.il

.assembly extern mscorlib{}
.assembly doubles{}
.module doubles.exe
.class private auto ansi beforefieldinit Class1
       extends [mscorlib]System.Object
{
  .method private hidebysig static void  Main() cil managed
  {
    .entrypoint
    .maxstack  2
    .locals init (float64 d)
    ldc.r8     3.14
    stloc.0
    ldloca.s   d
    ldstr      "g"
    call       instance string [mscorlib]System.Double::ToString(string)
    call       void [mscorlib]System.Console::WriteLine(string)
    ret
  } 

  .method public hidebysig specialname rtspecialname 
          instance void  .ctor() cil managed
  {
    .maxstack  1
    ldarg.0
    call       instance void [mscorlib]System.Object::.ctor()
    ret
  } 

}