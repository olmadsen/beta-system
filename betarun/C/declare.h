#include "define.h"
#include "constant.h"

#ifdef DX200
#  define Cell long
#  define Var( name, type, value) type name = value
#  define Array( name, size, type) type name[size]  = {0}
#else
#  define Cell long
#  define Var( name, type, value) type name = value
#  define Func( typeandname, value) typeandname = value
#  define Array( name, size, type) type name[size]
#endif
