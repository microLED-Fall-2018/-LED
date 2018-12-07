#include <atmel_start.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dotStar.h"
#include "usbCDC.h"

void flashFast(uint16_t);

void changeColor(char col[])
{
	
	serialWriteString(col);
	
	if(col[0] == 'r')
		changeDSColor(&dsColors[RED]);
	else if (col[0] == 'b')
		changeDSColor(&dsColors[BLUE]);
	else
		changeDSColor(&dsColors[GREEN]);
}

static bool cdcChangeColor(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
{
	char storeBuf[64];
	char inst[7];
	char close[5];
	char val[2];
	
	cdcdf_acm_read((uint8_t*)storeBuf, count);
	val[0] = storeBuf[6];
	val[1] = '\0';

	strcpy(inst, storeBuf);
	inst[6] = '\0';
	strncpy(close, storeBuf+ (count - 4), 4);
	close[4] = '\0';
	
	if (strcmp(inst, "color:") && strcmp(close, "*end"))
		changeColor(val);

	/* No error. */
	return false;
}

/* bool my_usb_device_cb_bulk_out(const uint8_t ep, const enum usb_xfer_code rc, const uint32_t count)
 {
	cdcdf_acm_read((uint8_t *)usbd_cdc_buffer, count);
	
	
	 
	 return false;
	 };*/

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	cdcd_acm_example();

	
	cdcdf_acm_register_callback(CDCDF_ACM_CB_READ, (FUNC_PTR)cdcChangeColor);

	
	//cdcdf_acm_register_callback(CDCDF_ACM_CB_READ, (FUNC_PTR)cdcChangeColor);
	
	buildColors();
	changeDSColor(&dsColors[BLACK]);
	
	PORT->Group[0].DIR.reg &= ~(1 << 9);
	PORT->Group[0].PINCFG[9].reg |= PORT_PINCFG_INEN | PORT_PINCFG_PULLEN | PORT_PINCFG_PMUXEN;
	PORT->Group[0].OUT.reg &= ~(1 << 9);
	
	REG_GCLK_CLKCTRL = GCLK_CLKCTRL_ID_EIC | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
	REG_PM_APBAMASK  |= PM_APBAMASK_EIC;	
	EIC->INTENSET.reg	= EIC_INTENSET_EXTINT9;
	EIC->CONFIG[1].reg 	|=  EIC_CONFIG_FILTEN1 | EIC_CONFIG_SENSE1_RISE;
	EIC->CTRL.reg |= EIC_CTRL_ENABLE;
	
	NVIC_EnableIRQ(EIC_IRQn);
	NVIC_SetPriority(EIC_IRQn, 9);
	
	PORT->Group[0].OUT.reg |= 1 << 10;
	
	adc_sync_enable_channel(&ADC_0, 6);
	
	while (1)
	{	
		uint8_t buffer[1];
		
		char number[6];
		adc_sync_read_channel(&ADC_0, 6, buffer, 2);
		
		utoa(buffer[0], number, 10);
		serialWriteString(strcat(number,"\r\n\0"));
		
//		PORT->Group[0].OUTTGL.reg = 1 << 10;
		delay_ms(10);
	}
}

void flashFast(uint16_t delay)
{
	while(1)
	{
		PORT->Group[0].OUTTGL.reg = 1 << 10;
		delay_ms(delay);
	}
}

void EIC_Handler()
{	
	if (EIC->INTFLAG.reg & 1 << 9)
	{
		uint32_t counter = 0;
		uint8_t tracker = 0;
		while(PORT->Group[0].IN.reg & (1 << 9)) 
		{
			counter++;
			
			if (counter < 500 && !(tracker & 1))
			{
				changeDSColor(&dsColors[GREEN]);
				tracker |= 1;
			}
			else if (counter >= 500 && !(tracker & 2))
			{
				changeDSColor(&dsColors[BLUE]);
				tracker |= 2;
			}
			else if (counter >= 1000 && !(tracker & 4)) 
			{
				changeDSColor(&dsColors[RED]);
				tracker |= 4;
			}
			else if (counter >= 1500 && !(tracker & 8))
			{
				changeDSColor(&dsColors[PURPLE]);
				tracker |= 8;
			}
			delay_ms(1);
		}
		
		delay_ms(50);
		
		switch(tracker)
		{
			case 0x1:
				serialWriteString("Got to section 1\r\n"); 
				break;
			case 0x3: 
				serialWriteString("Got to section 2\r\n");
				break;
			case 0x7: 					
				serialWriteString("Got to section 3\r\n");
				break;
			case 0xf: 					
				serialWriteString("Got to section 4\r\n");
				break;
		}
			
		EIC->INTFLAG.reg |= 1 << 9;
	}
}