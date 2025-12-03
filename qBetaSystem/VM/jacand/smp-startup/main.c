
#include "header.h"

static char coreStartText[] = "\nStarted core ";

static uint8_t startLine = 0;

static volatile int counter = 0;
static volatile uint8_t coreCounter = 0;
static uint8_t counterLock = 0;

// Each core counts to 8*0x1000
static const int blockSize = 0x1000;
static const int blockCount = 8;

static void countJob(int core) {
  for (int count = 0; count < blockCount; count++) {
    for (int i = 0; i < blockSize; i++) {
      lock_mutex(&counterLock);
      counter++;
      unlock_mutex(&counterLock);
    }
    // We lock the counter while printing because this operation is slow
    // and would allow other cores to run ahead
    lock_mutex(&counterLock);
    putstr("Core ");
    putch('0'+core);
    putstr(" counted to: ");
    puthex((count+1)*blockSize);
    putch('\n');
    unlock_mutex(&counterLock);
  }
  lock_mutex(&counterLock);
  putstr("Core ");
  putch('0'+core);
  putstr(" finished\n");
  coreCounter++;
  unlock_mutex(&counterLock);
}


static void startChildCore(void *coreNumber) {
  int core = (int)coreNumber;

  lock_mutex(&counterLock);
  putstr(coreStartText);
  putch('0'+core);
  putch('\n');
  coreCounter ++;
  unlock_mutex(&counterLock);
  lock_mutex(&startLine);
  unlock_mutex(&startLine);

  if (core < 4)  countJob(core);

  while (1) ;
}


void main(void *ftbBlob, unsigned int machType) {

  putstr(coreStartText);
  putch('0');
  putch('\n');
  
  if (machType == MACH_TYPE_BCM2708) {
    putstr("Broadcom BCM270x SoC found\n");
  }

  lock_mutex(&startLine);

  for (int i = 1; i < 4; i++) {
    if (start_core(startChildCore, (void*)i, i)) {
      putstr("Failed startcore ");
      putch('0'+i);
      putch('\n');
    }
  }

  while (coreCounter < 3);

  lock_mutex(&counterLock);
  coreCounter = 0;
  unlock_mutex(&counterLock);
  
  putstr("\nREADY... SET... GO!\n");
  unlock_mutex(&startLine);

  countJob(0);

  while (coreCounter < 4);

  lock_mutex(&counterLock);
  putstr("End result: ");
  puthex(counter);
  putch('\n');
  unlock_mutex(&counterLock);
  
  
  while (1);
}


