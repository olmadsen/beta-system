/*
   ilasm /exe clrproblems.il
*/

.assembly extern mscorlib{}
.assembly clrproblems {}
.module clrproblems.exe

.class public auto ansi beforefieldinit clrproblems
       extends [mscorlib]System.Object
{
  .method public hidebysig static void  Main() cil managed
  {
    .entrypoint
    .maxstack  3
    .try
    {
      // leave.s L 
      br.s L
    } 
    catch [mscorlib]System.Exception 
    {
      pop
      leave.s    L
    }
L:  ldc.i4.1
    newarr     [mscorlib]System.Int32
    .locals init (/*int32[]*/ int32 V_0)
    stloc.0
    ldloc.0
    ldc.i4.0
    ldc.i4.1
    stelem.i4
    ldloc.0
    ldc.i4.0
    ldelem.i4
    call       void [mscorlib]System.Console::WriteLine(int32)
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