#include <atmel_start.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void readVLC()
{
	PORT->Group[0].DIR.reg &= ~(1 << 9);
	PORT->Group[0].OUT.reg |= (1 << 9);
	delay_us(10);
	PORT->Group[0].OUT.reg &= ~(1 << 9);
	PORT->Group[0].DIR.reg &= ~(1 << 9);
	delay_us(10);

	adc_sync_read_channel(&ADC_0, 0, &buffer, 2);
}*/
	struct io_descriptor *io;
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);
	
	adc_sync_enable_channel(&ADC_0, 0);
	
	
	PORT->Group[0].DIR.reg |= 1 << 8;
	PORT->Group[0].DIR.reg &= ~(1 << 9);
	
	TC3->COUNT16.INTENSET.reg |= TC_INTENSET_OVF;
	TC3->COUNT16.CC[0].reg = 250;
	
	PORT->Group[0].OUT.reg &= ~(1 << 9 | 1 << 8);
	PORT->Group[0].PINCFG[7].reg |= PORT_PINCFG_INEN;
	
	//NVIC_EnableIRQ(TC3_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);
	ADC->INTENSET.bit.RESRDY = 1;
	
	/* Replace with your application code */
	while (1) {
		
/*		uint8_t bufValue[10];
		
		uint8_t numberThing = buffer[0];
		
		utoa(numberThing, (char *)bufValue, 10);
		strcat(bufValue, "\r\n\0");
		
		io_write(io, (uint8_t*)bufValue, 6);
		
		delay_ms(10);*/
	}
}

void ADC_Handler()
{
	if (ADC->INTFLAG.bit.RESRDY)
	{
		uint8_t bufValue[10];
		uint8_t buffer;
		
		adc_sync_read_channel(&ADC_0, 0, &buffer, 1);
		
		utoa(buffer, (char *)bufValue, 10);
		strcat(bufValue, "\r\n\0");
				
		io_write(io, (uint8_t*)bufValue, 6);
				
		delay_ms(10);
		
		ADC->INTFLAG.reg |= ADC_INTFLAG_RESRDY;
	}
}

/*void TC3_Handler()
{
	if (TC3->COUNT16.INTFLAG.reg & TC_INTFLAG_OVF)
	{
		readVLC(buffer);
		
		TC3->COUNT16.INTFLAG.reg |= TC_INTFLAG_OVF;
	}
}*/