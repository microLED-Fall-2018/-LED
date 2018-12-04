/*
 * usbCDC.c
 *
 * Created: 11/8/2018 4:53:47 AM
 *  Author: techi
 */ 

#include "usbCDC.h"

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