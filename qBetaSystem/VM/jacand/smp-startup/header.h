#include <stdint.h>

/**
 * The type of the Broadcom SoC family used on Raspberry Pis.
 * For the full list of Arm machine types, see
 * https://www.arm.linux.org.uk/developer/machines/
 */
#define MACH_TYPE_BCM2708  3138

/**
 * The main program entry point.
 
 * This function is called on core 0 when the other cores have not yet been
 * started. This function should not return. If it does, core 0 will be put
 * to sleep until the processor resets (it may continue to serve interrupts,
 * though). 
 * @param ftbBlob Address of the Flattened Device Tree.
 *        The specification is here:
 *        https://www.devicetree.org/specifications/
 *        And the Linux implementation is here:
 *        https://github.com/torvalds/linux/tree/master/drivers/of
 * @param machType The type of the machine. The list is of
 *        valid values is here:
 *        https://www.arm.linux.org.uk/developer/machines/
 */
void main(void *ftbBlob, unsigned int machType);

/**
 * Start a core (coreNo in {1,2,3}) by executing the provided
 * function with the provided argument. start_core() can only be
 * called on core 0.
 * @param function Function to execute on the core
 * @param argument The argument to give to the function
 * @param coreNo The core to start (1,2 or 3). If a core was already started
 *               this function will have no effect.
 * @return 0 on success, -1 otherwise
 */
int start_core(void (*function)(void*), void *argument, int coreNo);

/**
 * Lock a mutex.
 *
 * The thread will sleep until the lock is available - so DO NOT try
 * to lock a mutex that was already locked by the same thread (unless
 * a different thread has been tasked to unlock it).
 * @param mutex The mutex - (which is a byte location in memory.
 */
void lock_mutex(int8_t *mutex);

/**
 * Unlock a mutex.
 *
 * It is a no-op if the mutex was not locked. Ownership of the lock is
 * NOT checked! 
 * @param mutex The mutex - (which is a byte location in memory.
 */
void unlock_mutex(int8_t *mutex);



void putch(char c);

void putstr(const char *s);

void puthex(int i);

void pinMode(int pin, int mode);

int digitalWrite(int pin, int value);



