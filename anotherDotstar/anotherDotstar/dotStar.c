

#include "dotStar.h"

// Produces DotStar colors in IRGB
dotStarColor makeColor(uint8_t bright, uint8_t r, uint8_t g, uint8_t b)
{
	dotStarColor retVal =  {0, bright | 0xe0, b, g, r, 0-1};
	return retVal;
}

// Builds the colors for the DotStar
void buildColors()
{
	dsColors[RED] = makeColor(1, 255, 0, 0);
	dsColors[ORANGE] = makeColor(1, 255, 255, 0);
	dsColors[YELLOW] = makeColor(1, 128, 255, 0);
	dsColors[GREEN] = makeColor(1, 0, 255, 0);
	dsColors[CYAN] = makeColor(1, 0, 128, 255);
	dsColors[BLUE] = makeColor(1, 0, 0, 255);
	dsColors[PURPLE] = makeColor(1, 128, 0, 255);
	dsColors[MAGENTA] = makeColor(1, 255, 0, 255);
	dsColors[WHITE] = makeColor(1, 255, 255, 255);
	dsColors[BLACK] = makeColor(0, 0, 0, 0);
}

void changeDSColor(void* data)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_0, &io);
	
	spi_m_sync_enable(&SPI_0);
	
	io_write(io, (uint8_t *) data, 12);
}