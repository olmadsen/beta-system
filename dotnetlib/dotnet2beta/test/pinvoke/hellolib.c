#include <stdio.h>
#include <windows.h>

BOOL __stdcall DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved) {
  return TRUE;
}

void hello(const char *who){
  printf("Hello to %s from C world\n", who);
}

