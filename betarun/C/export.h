#include "define.h"

#define Cell long
#define Var( name, type, value) extern type name
#define UVar( name, type) extern type name
#define Func( typeandname, value) extern typeandname
#define Array( name, size, type) extern type name[]
#define Struct( name, type, v1, v2, v3, v4) extern type name
