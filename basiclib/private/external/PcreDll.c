#include <windows.h>

BOOL __stdcall DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved) {
  return TRUE;
}

#include "pcre/pcre.h"
#include "pcre_beta.c"
#include "pcre/maketables.c"
#include "pcre/get.c"
#include "pcre/study.c"
#include "pcre/pcre.c"

