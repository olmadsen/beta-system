#include <stdio.h>
#include <windows.h>

BOOL __stdcall DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved) {
  return TRUE;
}

void hello(char *who){
  printf("Hello to %s from C world\n", who);
}

void gethello(char **where){
  if (where == NULL) return;
  *where = "Got a hello from C world";
}

