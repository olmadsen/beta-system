#include "define.h"
#include "constant.h"

#define Cell long
#define Var( name, type, value) type name = value
#define Func( typeandname, value) typeandname = value
#define Array( name, size, type) type name[size]
#define Struct( name, type, v1, v2, v3, v4) type name = { v1, v2, v3, v4 }
