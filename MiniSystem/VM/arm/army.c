
#include <stdbool.h>
#include "../mailbox.h"
#define MB_CHANNEL_TAGS 8
unsigned int mailbox_read(channel c) {
	// Kolla att giltig kanal
	if ((c < 0) || (c > 9) || (c == 7)) {
		return 0;
	}
	
	volatile unsigned int* box = (unsigned int*) MAILBOX_BASE;
	volatile unsigned int* status = box + STATUS_OFFSET;
	unsigned int data;
	
	while (1) {
		while ((*status & 0x40000000) != 0) {}
		
		data = *box;
		if ((data & c) == c) {
			break;
		}
	}
	
	return data & 0xFFFFFFF0;
}

int mailbox_write(channel c, unsigned int msg) {
	// Kolla att giltig kanal
	if ((c < 0) || (c > 9) || (c == 7)){
		return 0;
	}
	// Kolla att 4 minst signifikanta bitar är 0
	if ((msg & 0xF) != 0){
		return 0;
	}
	
	volatile unsigned int* box = (unsigned int*) MAILBOX_BASE;
	volatile unsigned int* status = box + STATUS_OFFSET;
	volatile unsigned int* write = box + WRITE_OFFSET;
	
	// Vänta tills mest signifikanta biten är 0.
	// Då är mailboxen redo att ta emot meddelande.
	while ((*status & 0x80000000) != 0) {}
	
	*write = msg | c;

	return 1;
}

void* mailbox_ARM_to_VC(void* ptr) {
  return ptr  + 0x40000000;
}
#define uint32_t unsigned int
uint32_t __attribute__((aligned(16))) mailbox_message[8] ={32,0,0x38041,8,0,130,1,0};

void set_PI3LED(bool on) {
  /*
	mailbox_message[0] = sizeof(mailbox_message);
	mailbox_message[1] = 0;
	mailbox_message[2] = 0x38041;
	mailbox_message[3] = 8;
	mailbox_message[4] = 0; // was 8
	mailbox_message[5] = 130;
	mailbox_message[6] = (uint32_t)on;
	mailbox_message[7] = 0;
  */
	mailbox_write(MB_CHANNEL_TAGS, (unsigned int)mailbox_ARM_to_VC(&mailbox_message[0]));
}

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{ bool state = false;
  int i,cnt;
  //set_PI3LED((bool)1);
  while (1){
    set_PI3LED((bool)1);
    for (i=0; i <= 5000000;i++){ cnt = cnt + 1;};
    //set_PI3LED((bool)0);
    //if (state) {state = false;} else {state = true;};
    for (i=0; i <= 5000000;i++) { cnt = cnt + 1;};
  }

}

void exit(int no){
  while (1) ;
}
