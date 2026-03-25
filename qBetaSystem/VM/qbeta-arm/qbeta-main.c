#include "header.h"
#include <sys/types.h>
#include <errno.h>
#include <reent.h>

extern char _end;     // from linker
extern char _estack;  // define this in linker script!

extern unsigned char BC[];

#include "../interpreter_c.c" 

void putint(int V ) // (ptrdiff_t V)
{ int X; 
  char d[8]; 
  int i; 
  bool isNeg = V < 0;
  if (isNeg) V = -V;
  for (i = 0; i < 8; i++) d[i] = '0';
  for (i = 0; i < 8; i++) {
    d[7 - i] = '0' + V % 10;
    V = V / 10;
  }
  if (isNeg) putch('-');
  for (i = 0; i < 8; i++) {putch(d[i]);}
}

extern int cmpAndSwap(int adr, int old, int new);

void Bfork(void * interpreter, void * B, int coreNo)
{ /*putstr("Bfork: ");
  putint(coreNo);
  putch('\n');*/
  if ((0 < coreNo) && (coreNo < 4)){
      if (start_core(interpreter, B, coreNo)) {
         putstr("Failed startcore ");
         putch('0'+ coreNo );
         putch('\n');
      }
  }else{
    putstr("coreNo not in 1,2,3\n");
  }
}

// 2026-02-17, OLM: added the following dummy declarations to make linker happy
int _close(int file) { return -1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }
int _write(int file, char *ptr, int len) { return len; }
void _exit(int status) { while (1) {} }
int _isatty(int file) { return 1; }
int _fstat(int file, void *st) { return 0; }
void *_sbrk_Q(ptrdiff_t incr) {
    extern char _end;
    static char *heap_end;
    putstr("Invoking _sbrk: ");
    putint(incr);
    putstr("\n");
    if (!heap_end)
        heap_end = &_end;
    char *prev_heap_end = heap_end;
    heap_end += incr;
    putstr("END:_sbrk\n");
    return prev_heap_end;
}

void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    static char *heap_end;
    char *prev_heap_end;
    //putstr("Invoking _sbrk_r: ");
    //putint(incr);
    //putstr("\n");

    if (heap_end == 0)
        heap_end = &_end;

    prev_heap_end = heap_end;

    if (heap_end + incr > &_estack) {
        r->_errno = ENOMEM;
        return (void *) -1;
    }

    heap_end += incr;
    //putstr("END:_sbrk_r\n");
    return prev_heap_end;
}

void main(void *ftbBlob, unsigned int machType) {
  volatile static int X,V;
  static int8_t CL = 0;
  putstr("qBeta main is here\n");
  putstr("Once again!\n");

  putstr("Try lock\n");

  lock_mutex(&CL);
  putstr("Got lock\n");
  unlock_mutex(&CL);
  
  putstr("Try cmpAndSwap\n");
  X = 0;
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 1st!\n");} else {putstr("Did not get lock 1st!\n");}
  putstr("X: ");
  putint(X);
  putch(10);
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 2nd!\n");} else {putstr("Did not get lock 2nd!\n");}
  V = 0;
  X = 0;
  V = cmpAndSwap((int)&X,0,1);
  if (V) {putstr("Got lock 3rd!\n");} else {putstr("Did not get lock 3rd!\n");}
  putstr("Great!\n");
  
  set_descs(BC);  
  run_interpreter(1); // isXB = 1 
  getEvent(true); 
  //putstr("qbeta:main:end\n");
  while (1) ;
}

void exit(int no){
  putstr("qbeta:exit\n");
  while (1) ;
  putstr("qbeta:exit:X\n");
}
