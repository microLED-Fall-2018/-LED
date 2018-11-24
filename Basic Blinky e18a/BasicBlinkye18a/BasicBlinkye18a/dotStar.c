

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
	dsColors[dsRED] = makeColor(1, 255, 0, 0);
	dsColors[dsORANGE] = makeColor(1, 255, 255, 0);
	dsColors[dsYELLOW] = makeColor(1, 128, 255, 0);
	dsColors[dsGREEN] = makeColor(1, 0, 255, 0);
	dsColors[dsCYAN] = makeColor(1, 0, 128, 255);
	dsColors[dsBLUE] = makeColor(1, 0, 0, 255);
	dsColors[dsPURPLE] = makeColor(1, 128, 0, 255);
	dsColors[dsMAGENTA] = makeColor(1, 255, 0, 255);
	dsColors[dsWHITE] = makeColor(1, 255, 255, 255);
	dsColors[dsBLACK] = makeColor(0, 0, 0, 0);
}

void changeDSColor(void* data)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_0, &io);
	
	spi_m_sync_enable(&SPI_0);
	
	io_write(io, (uint8_t *) data, 12);
}