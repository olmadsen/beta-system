#include <stdio.h>
#include <dlfcn.h>

int main()
{
  int addr;
  void * self;
  
  self=dlopen(NULL,RTLD_NOW|RTLD_GLOBAL);
  if (!self) {
    fprintf(stderr, "dlopen(NULL) failed\n");
    return;
  }
  fprintf(stderr, "\n");

  addr = (int)dlsym(self, "main");
  if (addr != (int)&main) {
    fprintf(stderr, 
	    "dlsym seems broken: returns 0x%x for main (should be 0x%x)\n",
	    (int)addr,
	    (int)&main);
    if (!addr){
      fprintf(stderr, "dl error: %s\n", dlerror());
    }
    fprintf(stderr,
	    "\nHmmm, lets try dlsym(\"fprintf\") - it's in a dynamic library:\n");
    addr = (int)dlsym(self, "fprintf");
    if (addr != (int)&fprintf) {
      fprintf(stderr, 
	      "No it's completely broken: returns 0x%x for fprintf (should be 0x%x)\n",
	      (int)addr,
	      (int)&fprintf);
      if (!addr){
	fprintf(stderr, "dl error: %s\n", dlerror());
      } 
    } else {
      fprintf(stderr, 
	      "It works for symbols in dynamic libs: returns 0x%x for fprintf\n",
	      (int)addr);
    }
  } else {
    fprintf(stderr, 
	    "dlsym is fine: returns 0x%x for main\n",
	    (int)addr);
  }
  fprintf(stderr, "\n");
  dlclose(self);
  return 0;
}
