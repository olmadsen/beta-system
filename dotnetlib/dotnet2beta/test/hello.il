// Minimal Hello World in IL.
// Compilation:
//   ilasm -nologo -exe hello.il

.assembly extern mscorlib {}
.assembly hello { .ver 0:0:0:0 }
.class public Hello extends [mscorlib]System.Object
{
  .method public static void  Main(string[] args) cil managed
  {
    .entrypoint
    .maxstack  1
    ldstr      "Hello, World!"
    call       void [mscorlib]System.Console::WriteLine(string)
    ret
  } 

}