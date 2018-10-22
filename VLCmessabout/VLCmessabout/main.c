#include <atmel_start.h>

#define PORTA PORT->Group[0]


static void sendByte(uint8_t);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	PORTA.DIR.reg |= 1 << 2 | 1 << 4 | 1 << 5;
	
	//PORTA.CTRL.reg  |= 1 << 3;
	PORTA.PINCFG[3].reg |= PORT_PINCFG_PMUXEN;//PORT_PINCFG_INEN;// | PORT_PINCFG_PULLEN;
	PORTA.PMUX[1].reg |= PINMUX_PA03B_ADC_AIN1;
	
	NVIC_SetPriority(SERCOM3_IRQn, 2);
	
	usart_async_enable(&USART_0);

	SERCOM3->USART.INTENSET.reg |= 1 << 0 | 1 << 1;
	
	uint8_t step = 0;
	uint8_t count = 0;
	
	while (1) 
	{
		if (PORTA.IN.reg & 1 << 3)
		{	
			PORTA.OUT.reg |= 1 << 4;
			PORTA.OUT.reg &= ~(1 << 5);
		}
		else
		{
			PORTA.OUT.reg |= 1 << 5;
			PORTA.OUT.reg &= ~(1 << 4);
		}
		
		if (count++ & 128)
			PORTA.OUT.reg |= 1 << 2;
		else
			PORTA.OUT.reg &= ~(1 << 2);
		
		delay_ms(1);
	}
}

static void sendByte(uint8_t data)
{
	/* 
	 * Wait until the DRE register is set
	 * Then write the byte to the data register
	 * Then wait until the TXC register is set.
	 */
	while((SERCOM3->USART.INTFLAG.reg & 1) == 0){}
	SERCOM3->USART.DATA.reg = (data & 0xff);
	while((SERCOM3->USART.INTFLAG.reg & (1 << 1))==0){}
	
}