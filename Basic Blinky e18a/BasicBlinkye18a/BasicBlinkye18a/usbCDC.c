/*
 * usbCDC.c
 *
 * Created: 11/8/2018 4:53:47 AM
 *  Author: techi
 */ 

#include "usbCDC.h"

void processIncoming(uint8_t *instPtr)
{
	char instType[5];
	uint16_t valsChaged = 0;
	instPtr = (uint8_t *)strstr((char *)instPtr, "*"); // Skip any potential initial garbage
	
	while (instPtr[0] != '\0')
	{
		uint8_t currInst[200 * 4];

		int currInstLength = (uint8_t *)strstr((char *)instPtr, "*END") - instPtr - 4;
		
		memcpy(instType, instPtr, 4);
		instPtr += 4;
		
		if (strstr(instType, "*000"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(0, (instruction *)currInst);
			
			valsChaged |= 1 << 0;
		}
		else if (strstr(instType, "*111"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(1,  (instruction *)currInst);
			
			valsChaged |= 1 << 1;
		}
		else if (strstr(instType, "*222"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(2,  (instruction *)currInst);
			
			valsChaged |= 1 << 2;
		}
		else if (strstr(instType, "*333"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(3,  (instruction *)currInst);
			
			valsChaged |= 1 << 3;
		}
		else if (strstr(instType, "*444"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(4,  (instruction *)currInst);
			
			valsChaged |= 1 << 4;
		}
		else if (strstr(instType, "*555"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(5,  (instruction *)currInst);
			
			valsChaged |= 1 << 5;
		}
		else if (strstr(instType, "*666"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(6,  (instruction *)currInst);
			
			valsChaged |= 1 << 6;
		}
		else if (strstr(instType, "*777"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(7,  (instruction *)currInst);
			
			valsChaged |= 1 << 7;
		}
		else if (strstr(instType, "*888"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(8,  (instruction *)currInst);
			
			valsChaged |= 1 << 8;
		}
		else if (strstr(instType, "*999"))
		{
			memcpy(currInst, instPtr, currInstLength);
			storeSequence(9,  (instruction *)currInst);
			
			valsChaged |= 1 << 9;
		}
		else if (strstr(instType, "*PVW"))
		{
			memcpy(currInst, instPtr, currInstLength);
		}
		else if (strstr(instType, "*BP"))
		{
			setToBPM((uint8_t)instType[3]);
		}
		else
		{
			PORT->Group[0].OUTTGL.reg = 1 << 10;
			delay_ms(200);
		}

		instPtr += currInstLength + 4;
		if (valsChaged & 1 << currSeqNum)
		{
			memcpy(currSeq, currInst, sizeof(currSeq));
		}
	}
}

// Write a string out over the USB CDC (up to 1000 characters)
void serialWriteString(char string[])
{
	uint32_t length = strnlen(string, 1000);
	int i = 0;
	uint8_t newString[1000];
	while(string[i] != 0)
	{
		newString[i] = (unsigned char)string[i];
		i++;
	}
	
	//cdcdf_acm_write((uint8_t *)usbd_cdc_buffer, count); // example
	cdcdf_acm_write((uint8_t*)newString, length);
}

bool doSomethingUseful(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	
	cdcdf_acm_write((uint8_t *)usbd_cdc_buffer, count);
	
	//flash_write(&FLASH_INSTANCE, 0x7000, (uint8_t *)usbd_cdc_buffer, 5);
	
	strcat((char*)veryBig, (char*)usbd_cdc_buffer);
	
	uint8_t *endMarker = (uint8_t *)strstr((char *)veryBig, "*END*END");
	
	if (endMarker)
	{
		uint16_t instLength = endMarker - veryBig;
		veryBig[instLength + 4] = '\0'; // Removes second *END, all should instructions match
		
		processIncoming(veryBig);
		memset(veryBig,0,sizeof(veryBig));
	}

	// No error.
	return false;
}

bool myUsb_device_cb_bulk_in(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	/* Echo data. */
	cdcdf_acm_read((uint8_t *)usbd_cdc_buffer, sizeof(usbd_cdc_buffer));

	/* No error. */
	return false;
}

bool myUsb_device_cb_state_c(usb_cdc_control_signal_t state)
{
	//if (state.rs232.DTR) {
	
	/* Callbacks must be registered after endpoint allocation */
	cdcdf_acm_register_callback(CDCDF_ACM_CB_READ, (FUNC_PTR)doSomethingUseful);
	cdcdf_acm_register_callback(CDCDF_ACM_CB_WRITE, (FUNC_PTR)myUsb_device_cb_bulk_in);
	
	/* Start Rx */
	cdcdf_acm_read((uint8_t *)usbd_cdc_buffer, sizeof(usbd_cdc_buffer));
	//}

	/* No error. */
	return false;
}

void setupUSBCallbacks(void)
{
	while (!cdcdf_acm_is_enabled()) {
		// wait cdc acm to be installed
	};

	cdcdf_acm_register_callback(CDCDF_ACM_CB_STATE_C, (FUNC_PTR)myUsb_device_cb_state_c);
}