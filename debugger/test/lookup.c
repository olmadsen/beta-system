#include <stdio.h>
#include <dlfcn.h>

main()
{
  int addr;
  void * self;
  
  self=dlopen(NULL,RTLD_NOW|RTLD_GLOBAL);
  if (!self) {
    fprintf(stderr, "dlopen(NULL) failed\n");
    return;
  }

  addr = (int)dlsym(self, "main");
  if (addr != (int)&main) {
    fprintf(stderr, 
	    "dlsym seems broken: returns 0x%x for main (should be 0x%x)\n",
	    (int)addr,
	    (int)&main);
  } else {
    fprintf(stderr, 
	    "dlsym is fine: returns 0x%x for main\n",
	    (int)addr);
  }
}
