#include "define.h"

#ifdef DX200
#  define Cell long
#  define Var( name, type, value) extern type name
#  define Array( name, size, type) extern type name[]
#else
#  define Cell long
#  define Var( name, type, value) extern type name
#  define Func( typeandname, value) extern typeandname
#  define Array( name, size, type) extern type name[]
#endif
