#include <atmel_start.h>
#include "stdlib.h"
#include "string.h"

static void tx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void serialWrite(char string[])
{
	struct io_descriptor *io;
	
	usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, tx_cb_USART_0);
	/*usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_0, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_0, &io);
	usart_async_enable(&USART_0);

	io_write(io, string, strnlen(string, 200));
}

int main(void)
{
	/* Initializes MCU, drivers and middle-ware */
	atmel_start_init();

	/* Replace with your application code */
	while (1) 
	{
		serialWrite("first\r\n");
		delay_ms(1000);
		serialWrite("second\r\n");
		delay_ms(1000);
	}
}
