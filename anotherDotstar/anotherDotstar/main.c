#include <atmel_start.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dotStarColor
{
	uint32_t start;
	uint8_t intensity;
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint32_t end;
}
dotStarColor;

enum dsColor {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, MAGENTA, WHITE, BLACK};
dotStarColor dsColors[10];
	
// Produces DotStar colors in IRGB
dotStarColor makeColor(uint8_t bright, uint8_t r, uint8_t g, uint8_t b)
{
	dotStarColor retVal =  {0, bright | 0xe0, b, g, r, 0-1};
	return retVal;
}

// Builds the colors for the DotStar
void buildColors()
{
	dsColors[RED] = makeColor(25, 255, 0, 0);
	dsColors[ORANGE] = makeColor(25, 255, 255, 0);
	dsColors[YELLOW] = makeColor(25, 128, 255, 0);
	dsColors[GREEN] = makeColor(25, 0, 255, 0);
	dsColors[CYAN] = makeColor(25, 0, 128, 255);
	dsColors[BLUE] = makeColor(25, 0, 0, 255);
	dsColors[PURPLE] = makeColor(25, 128, 0, 255);
	dsColors[MAGENTA] = makeColor(25, 255, 0, 255);
	dsColors[WHITE] = makeColor(25, 255, 255, 255);
	dsColors[BLACK] = makeColor(0, 0, 0, 0);
}
								
dotStarColor dsColors[10];

void flashFast(uint16_t);

uint8_t count;

void changeDSColor(void* data)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_0, &io);
	
	spi_m_sync_enable(&SPI_0);
	
	io_write(io, (uint8_t *) data, 12);
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


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	cdcd_acm_example();
	
	
	
	buildColors();

	
	PORT->Group[0].DIR.reg &= ~(1 << 4);
	PORT->Group[0].PINCFG[4].reg |= PORT_PINCFG_INEN | PORT_PINCFG_PULLEN | PORT_PINCFG_PMUXEN;
	PORT->Group[0].OUT.reg &= ~(1 << 4);
	
	REG_GCLK_CLKCTRL = GCLK_CLKCTRL_ID_EIC | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
	REG_PM_APBAMASK |= PM_APBAMASK_EIC;
	EIC->INTENSET.reg	= EIC_INTENSET_EXTINT4;
	EIC->CONFIG[0].reg 	|=  EIC_CONFIG_FILTEN4 | EIC_CONFIG_SENSE4_RISE;
	EIC->CTRL.reg |= EIC_CTRL_ENABLE;
	
	NVIC_EnableIRQ(EIC_IRQn);
	NVIC_SetPriority(EIC_IRQn, 3);
	
	count = 0;
	
	changeDSColor(&dsColors[BLACK]);
	
	while (1)
	{	
		delay_ms(1000);
		serialWriteString("Ready to go!\r\n");
		PORT->Group[0].OUTTGL.reg = 1 << 23;
		delay_ms(1000);
		serialWriteString("This is a really really really long string, just look at it! This will surely test the mettle of the silly cdc wotsit!\r\n");
	}
}

void flashFast(uint16_t delay)
{
	while(1)
	{
		PORT->Group[0].OUTTGL.reg = 1 << 23;
		delay_ms(delay);
	}
}

void EIC_Handler()
{
	if (EIC->INTFLAG.reg & 1 << 4)
	{
		uint32_t counter = 0;
		uint8_t tracker = 0;
		while(PORT->Group[0].IN.reg & (1 << 4)) 
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
				serialWriteString("Got to section 1"); 
				break;
			case 0x3: 
				serialWriteString("Got to section 2");
				break;
			case 0x7: 					
				serialWriteString("Got to section 3");
				break;
			case 0xf: 					
				serialWriteString("Got to section 4");
				break;
		}
			
		EIC->INTFLAG.reg |= 1 << 4;
	}
}