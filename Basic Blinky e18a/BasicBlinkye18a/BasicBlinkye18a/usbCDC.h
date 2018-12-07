#ifndef USBCDC_H_
#define USBCDC_H_

#ifndef ATMEL_START_H_INCLUDED
#include <atmel_start.h>
#endif

void processIncoming(uint8_t*);
void serialWriteString(char[]);
bool doSomethingUseful(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
bool myUsb_device_cb_bulk_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count);
bool myUsb_device_cb_state_c(usb_cdc_control_signal_t state);
void setupUSBCallbacks(void);

char usbd_cdc_buffer[1000];
uint8_t veryBig[10000];

extern void storeSequence(uint8_t, void*);
extern uint8_t currSeqNum;
extern instruction currSeq[200];

typedef struct {
	uint8_t inst;
	uint8_t rate;
	uint8_t dur;
	uint8_t bright;
} instruction;

#endif /* USBCDC_H_ */