#include <atmel_start.h>

#define PORTA PORT->Group[0]
#define PORTB PORT->Group[1]


static void sendByte(uint8_t);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	PORTA.DIR.reg |= 1 << 3;
	//PORTB.DIR.reg |= 1 << 8;
	PORTA.CTRL.reg  |= 1 << 2;
	PORTA.PINCFG[2].reg |= PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	
	NVIC_SetPriority(SERCOM3_IRQn, 2);
	
	usart_async_enable(&USART_0);

	SERCOM3->USART.INTENSET.reg |= 1 << 0 | 1 << 1;
	
	uint8_t step = 0;
	uint8_t count;
	
	while (1) {
		count = 0;
		
		PORTA.DIR.reg |= 1 << 2;
		PORTA.OUT.reg |= 1 << 2;
		delay_us(100);
		PORTA.DIR.reg &= ~(1 << 2);
		PORTA.OUT.reg &= ~(1 << 2);
		while (PORTA.IN.reg & (1 << 2))
			count++;
		
		delay_us(10);
		
		count += 65;
		
		if (step++ & 8)
			PORTA.OUT.reg |= 1 << 3;
		else
			PORTA.OUT.reg &= ~(1 << 3);
		
		//sendByte((count > 5) ? '0' : '1');
		sendByte(count);
		//sendByte('\n');
		//sendByte('\r');
		
		delay_us(250);
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