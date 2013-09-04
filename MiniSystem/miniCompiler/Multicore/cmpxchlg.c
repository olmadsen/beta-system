#include <windows.h> 
#include <stdio.h>
#include <WinBase.h> // CreateEvent ???
#include <Windows.h>
int cmpxchlg(int *mutex, int old, int new)
    { int ret = 0;
       __asm__("lock cmpxchg %2, %1;"               
               "movl %%eax, %0;"
               : "=q" ( ret ), "=m" ( *mutex ) 
               : "r" ( new ), "m" ( *mutex ), "a" ( old ));
       return ret;
   }
/*
bool_t My_CompareAndSwap(IN int *ptr, IN int old, IN int new)
{
        unsigned char ret;

        / * Note that sete sets a 'byte' not the word * /
        __asm__ __volatile__ (
                "  lock\n"
                "  cmpxchgl %2,%1\n" 
                "  sete %0\n"
                : "=q" (ret), "=m" (*ptr)
                : "r" (new), "m" (*ptr), "a" (old)
                : "memory");

        return ret;
}
*/



  



