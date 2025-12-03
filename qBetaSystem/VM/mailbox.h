// constants from
// https://fosdem.org/2017/schedule/event/programming_rpi3/attachments/slides/1475/export/events/attachments/programming_rpi3/slides/1475/bare_metal_rpi3.pdf
#define IO_BASE		0x3F000000

//*********************************************
#ifndef MAILBOX_H
#define MAILBOX_H

#define MAILBOX_BASE (IO_BASE + 0xB880)
#define STATUS_OFFSET 0x18
#define WRITE_OFFSET 0x20


typedef enum {
	POWER_MANAGEMENT = 0,
	FRAMEBUFFER = 1,
	VIRUTAL_UART = 2,
	VCHIQ = 3,
	LEDS = 4,
	BUTTONS = 5,
	TOUCH_SCREEN = 6,
	PROPERTY_TAGS1 = 8,
	PROPERTY_TAGS2 = 9
} channel;


#endif
