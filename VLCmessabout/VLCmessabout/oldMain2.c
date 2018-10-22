#include <atmel_start.h>

#define PORTA PORT->Group[0]

static void sendByte(uint8_t);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	PORTA.DIR.reg |= 1 << 2 | 1 << 4;
	PORTA.DIR.reg &= ~(1 << 3);
	//PORTA.CTRL.reg  |= 1 << 3;
	PORTA.PINCFG[3].reg |= PORT_PINCFG_INEN;// | PORT_PINCFG_PULLEN;
	//PORTA.PINCFG[4].reg |= PORT_PINCFG_DRVSTR;
	
	NVIC_SetPriority(SERCOM3_IRQn, 2);
	
	usart_async_enable(&USART_0);

	SERCOM3->USART.INTENSET.reg |= 1 << 0 | 1 << 1;
	
	uint8_t step = 0;
	uint8_t count;
	
	PORTA.OUT.reg |= 1 << 4;
//	PORTA.OUT.reg |= 1 << 3;
	
	delay_ms(10);
	
	while (1) {
		count = 0;
		
		//PORTA.DIR.reg |= 1 << 3;
		delay_us(10);
		//PORTA.DIR.reg &= ~(1 << 3);
		PORTA.OUT.reg &= ~(1 << 4);
		while ((PORTA.IN.reg & (1 << 3)))
			count++;
		
		PORTA.OUT.reg |= 1 << 4;
		
		if (step++ & 16)
			PORTA.OUT.reg |= 1 << 2;
		else
			PORTA.OUT.reg &= ~(1 << 2);
		
		//sendByte((count > 65) ? '0' : '1');
		
		//1 << 3 | 1 << 4;
		//PORTA.PINCFG[3].reg |= 0x0;
		//sendByte('\n');
		//sendByte('\r');
		
		//delay_ms(10);
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
