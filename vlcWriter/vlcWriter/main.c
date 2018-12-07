#include <atmel_start.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
		
	PORT->Group[0].DIR.reg |= 1 << 6 | 1 << 7;
	PORT->Group[0].OUT.reg |= 1 << 6;
	PORT->Group[0].OUT.reg &= ~(1 << 7);
	
	/* Replace with your application code */
	while (1) {
		
		PORT->Group[0].OUTTGL.reg = 1<< 7;
		
		delay_ms(250);

	}
}
