
#ifndef DOTSTAR_H_
#define DOTSTAR_H_

#ifndef ATMEL_START_H_INCLUDED
#include <atmel_start.h>
#endif

enum dsColor {dsRED, dsORANGE, dsYELLOW, dsGREEN, dsCYAN, dsBLUE, dsPURPLE, dsMAGENTA, dsWHITE, dsBLACK};

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


dotStarColor dsColors[10];

dotStarColor makeColor(uint8_t, uint8_t, uint8_t, uint8_t);
void buildColors();
void changeDSColor(void*);

#endif /* DOTSTAR_H_ */