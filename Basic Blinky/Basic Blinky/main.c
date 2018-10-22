/* Useful Notes:
 * beatTimer TCC0 - Keeps track of the beat steps and the steps until next action
 * red/green/bluePWM TC3/4/5- psuedo PWM (thanks adafruit...) that control brightness on led outputs
 * neoPixel TCC1 - Another psuedo PWM for neopixel control.
 */
#include <atmel_start.h>

#define PORTA PORT->Group[0]
#define PORTB PORT->Group[1]

#define BPM 40		// Eventually this will be replaced with a flexible method
#define MAXINST 200	// Maximum number of instructions/sequence
#define MAXSEQ 10
#define RED 0
#define GREEN 1
#define BLUE 2
#define FLASH 0
#define FADE 1
#define RAMPUP 2
#define RAMPDN 3

#define GET_INST_COLOR(color) (color.inst >> 6)
#define GET_INST_TYPE(color) ((color.inst >> 4) & 0x3)

//#define STEP_TIMER TC4->COUNT16
#define INTEN_TIMER TC3->COUNT8

typedef struct {
	uint8_t inst;
	uint8_t rate;
	uint8_t dur;
	uint8_t bright;
	} instruction;
	
typedef struct {
	uint8_t first;
	uint8_t last;
	uint8_t curr;
	} instTracker;
	
instruction shortDemo[200] =   {{0x00, 4, 1, 255},
								{0x21, 4, 1, 255}, 
								{0x41, 8, 1, 200},
								{0x81, 16, 1, 128}};


								/*{{0x00, 4, 4, 200},
								{0x00, 4, 4, 0}, 
								{0x01, 4, 2, 200},
								{0x40, 4, 2, 0},
								{0x40, 4, 4, 200},
								{0x41, 4, 4, 0},
								{0x80, 4, 6, 0},
								{0x81, 4, 4, 200}};*/
/* Steps per beat lookup Table
 * A quick table to find the number of steps/beat in bpm
 * Works for 10-256 bpm
 * Anything below 10 will be returned as if it was 10 (> 65535)
 */
uint16_t stepsPerBeatTable[256] = {	60000,	60000,	60000,	60000,	60000,	60000,	60000,	60000,	60000,	60000,	54545,	50000,	46154,	42857,	40000,	37500,
									35294,	33333,	31579,	30000,	28571,	27273,	26087,	25000,	24000,	23077,	22222,	21429,	20690,	20000,	19355,	18750,
									18182,	17647,	17143,	16667,	16216,	15789,	15385,	15000,	14634,	14286,	13953,	13636,	13333,	13043,	12766,	12500,
									12245,	12000,	11765,	11538,	11321,	11111,	10909,	10714,	10526,	10345,	10169,	10000,	9836,	9677,	9524,	9375,
									9231,	9091,	8955,	8824,	8696,	8571,	8451,	8333,	8219,	8108,	8000,	7895,	7792,	7692,	7595,	7500,
									7407,	7317,	7229,	7143,	7059,	6977,	6897,	6818,	6742,	6667,	6593,	6522,	6452,	6383,	6316,	6250,
									6186,	6122,	6061,	6000,	5941,	5882,	5825,	5769,	5714,	5660,	5607,	5556,	5505,	5455,	5405,	5357,
									5310,	5263,	5217,	5172,	5128,	5085,	5042,	5000,	4959,	4918,	4878,	4839,	4800,	4762,	4724,	4688,
									4651,	4615,	4580,	4545,	4511,	4478,	4444,	4412,	4380,	4348,	4317,	4286,	4255,	4225,	4196,	4167,
									4138,	4110,	4082,	4054,	4027,	4000,	3974,	3947,	3922,	3896,	3871,	3846,	3822,	3797,	3774,	3750,
									3727,	3704,	3681,	3659,	3636,	3614,	3593,	3571,	3550,	3529,	3509,	3488,	3468,	3448,	3429,	3409,
									3390,	3371,	3352,	3333,	3315,	3297,	3279,	3261,	3243,	3226,	3209,	3191,	3175,	3158,	3141,	3125,
									3109,	3093,	3077,	3061,	3046,	3030,	3015,	3000,	2985,	2970,	2956,	2941,	2927,	2913,	2899,	2885,
									2871,	2857,	2844,	2830,	2817,	2804,	2791,	2778,	2765,	2752,	2740,	2727,	2715,	2703,	2691,	2679,
									2667,	2655,	2643,	2632,	2620,	2609,	2597,	2586,	2575,	2564,	2553,	2542,	2532,	2521,	2510,	2500,
									2490,	2479,	2469,	2459,	2449,	2439,	2429,	2419,	2410,	2400,	2390,	2381,	2372,	2362,	2353,	2344};

uint8_t bpm = BPM;

uint16_t stepsPerBeat, nextBeat; 
uint8_t beatsCurr = 0;

// Storage for flash sequences
// There are up to 10 sequences which can be 200 instructions long each
instruction sequences[MAXSEQ][MAXINST];
uint8_t sequenceCurr = 0;
	
instTracker tracker[3]; // Tracks the instructions for each color
uint8_t maxIntensity[3];
uint8_t currIntensity[3];
uint16_t nextAction[3]; // the count the next action should occur on. Should wrap around (say if at 65000 and next in 1000)
uint16_t diffs[3]; // increase over current count for next action
uint16_t countMax;
uint8_t increment[3];
uint8_t direction;
uint8_t firstTime = 0;

uint8_t beatsRemaining[3] = {0, 0, 0};
uint16_t actionsRemaining[3] = {0, 0,0};
uint8_t isOn[3] = {0, 0, 0}; // For sequences, is the instruction currently on?

void populateTracker(instruction[]);
void updateStepsPerBeat(uint8_t);
void processInstruction(instruction);
void nextInstruction(uint8_t);
void flash(uint8_t);
void fade(uint8_t);
void rampUp(uint8_t);
void rampDown(uint8_t);
void (*action)(uint8_t);//, uint16_t);
void testByColor(uint8_t, uint8_t);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	NVIC_DisableIRQ(TC3_IRQn);
	NVIC_DisableIRQ(TC4_IRQn);
	NVIC_DisableIRQ(TC5_IRQn);
	
	// For testing, instantiate sequence 0 with short Demo
	int i;
	for (i = 0; i < 200; i++)
		sequences[sequenceCurr][i] = shortDemo[i];
	
	updateStepsPerBeat(bpm);
	
	TCC0->PER.reg = 255;
	TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM | 0x7 << 16;

	populateTracker(sequences[sequenceCurr]);
	tracker[RED].curr = tracker[RED].first;
	tracker[GREEN].curr = tracker[GREEN].first;
	tracker[BLUE].curr = tracker[BLUE].first;
	
	processInstruction(sequences[sequenceCurr][tracker[RED].curr]);	
	processInstruction(sequences[sequenceCurr][tracker[GREEN].curr]);
	processInstruction(sequences[sequenceCurr][tracker[BLUE].curr]);
	
	TCC0->CC[RED].reg = currIntensity[RED];
	TCC0->CC[GREEN].reg = currIntensity[GREEN];
	TCC0->CC[BLUE].reg = currIntensity[BLUE];
	
	NVIC_EnableIRQ(TC3_IRQn);
	NVIC_EnableIRQ(TC4_IRQn);
	NVIC_EnableIRQ(TC5_IRQn);

	NVIC_SetPriority(TC3_IRQn, 2);
	NVIC_SetPriority(TC4_IRQn, 2);
	NVIC_SetPriority(TC5_IRQn, 2);

	while(1)
	{	
		// Heartbeat
		PORTA.OUTTGL.reg = 1 << 17;		
		delay_ms(100);
	}
}

/*
 * Populates the tracker
 * Figures out where sections of flash sequence begin and end.
 * That is, where red ends, and green begins. Then green to blue
 */
void populateTracker(instruction insts[200])
{
	int8_t i = 0;
	int8_t count = RED;
	
	tracker[RED].first = 0;
	tracker[RED].curr = tracker[RED].first;
	
	while (count < 3) // 0 - Red, 1 - Green, 2 - Blue
	{
		PORTA.OUT.reg |= 1 << 2 | 1 << 4 | 1 << 5;
			
		// A 1 in the 24th position indicates the last instruction in a color
		if(insts[i++].inst & 0x01)
		{
			
			tracker[count++].last = i - 1;
			
			if (count <= BLUE)
			{
				tracker[count].first = i; // i has already been incremented
			}
		}
	}
}

void updateStepsPerBeat(uint8_t bpm)
{
	stepsPerBeat = stepsPerBeatTable[bpm - 1];
}

// Processing an Instruction
// 1. Whose instruction is this? (RGB)
// 2. What kind of instruction is this?
// 3. If it's a flash, fade, or ramp, process accordingly 
void processInstruction(instruction inst)
{
	uint8_t color	= (inst.inst >> 6) & 0x3;
	uint8_t whatKind	= (inst.inst >> 4) & 0x3;
	
	switch(whatKind)
	{
		case FLASH:
			maxIntensity[color] = inst.bright;
			currIntensity[color] = maxIntensity[color];
			actionsRemaining[color] = (inst.dur * inst.rate) << 1;
			diffs[color] = (stepsPerBeat / inst.rate) >> 1;
			action = &flash;
			break;
		case FADE:
			increment[color] = inst.bright >> 4;
			maxIntensity[color] = increment[color] << 4;
			currIntensity[color] = 0;
			actionsRemaining[color] = (inst.dur * inst.rate) << 4; // x16x2 = x32 = << 5
			diffs[color] = (stepsPerBeat / inst.rate) >> 4;
			direction = 1;
			action = &fade;
			break;
		case RAMPUP:
			increment[color] = inst.bright >> 4;
			maxIntensity[color] = increment[color] << 4;
			currIntensity[color] = 0;
			actionsRemaining[color] = (inst.dur * inst.rate) << 4; // x16x2 = x32 = << 5
			diffs[color] = (stepsPerBeat / inst.rate) >> 4;
			action = &rampUp;
			break;
		case RAMPDN:
			increment[color] = inst.bright >> 4;
			maxIntensity[color] = increment[color] << 4;
			currIntensity[color] = maxIntensity[color];
			actionsRemaining[color] = (inst.dur * inst.rate) << 4; // x16x2 = x32 = << 5
			diffs[color] = (stepsPerBeat / inst.rate) >> 4;
			action = &rampDown;
			break;
		default:
			while(1) // Error state
			{
				PORTA.OUTTGL.reg = 1 << 2 | 1 << 4 | 1 << 5;
				delay_ms(500);
			}
			break;
	}
	switch(color)
	{
	case RED:
		TC3->COUNT16.CC[0].reg = diffs[color];
		break;
	case GREEN:
		TC4->COUNT16.CC[0].reg = diffs[color];
		break;
	case BLUE:
		TC5->COUNT16.CC[0].reg = diffs[color];
		break;
	default:
		while(1) // Error state
		{
			PORTA.OUTTGL.reg = 1 << 2 | 1 << 4 | 1 << 5;
			delay_ms(500);
		}
		break;
	}
}

void flash(uint8_t color)
{
	currIntensity[color] = (currIntensity[color] == maxIntensity[color]) ? 0 : maxIntensity[color];		
	
	TCC0->CC[color].reg = currIntensity[color];
	
}

void fade(uint8_t color)
{
	// If we hit the max intensity or zero, change direction
	// Otherwise direction stays the same.
	if (currIntensity[color] >= maxIntensity[color])
		direction = 0; // falling
	else if (currIntensity[color] <= 0)
		direction = 1; // rising	
		
	if (direction != 0)
		currIntensity[color] += increment[color];
	else
		currIntensity[color] -= increment[color];
		
	TCC0->CC[color].reg = currIntensity[color];
}

void rampUp(uint8_t color)
{
	if (currIntensity[color] >= maxIntensity[color])
		currIntensity[color] = 0;
	else
		currIntensity[color] += increment[color];
		
	TCC0->CC[color].reg = currIntensity[color];
}

void rampDown(uint8_t color)
{
	if (currIntensity[color] <= 0)
		currIntensity[color] = maxIntensity[color];
	else
		currIntensity[color] -= increment[color];
		
	TCC0->CC[color].reg = currIntensity[color];
}

void nextInstruction(uint8_t color)
{
	if (tracker[color].curr == tracker[color].last)
		tracker[color].curr = tracker[color].first;
	else
		tracker[color].curr = tracker[color].curr + 1;
}

/*
	// End of period, turn everything back on.
	if (TCC0->INTFLAG.reg & TCC_INTFLAG_OVF)
	{
		if (currIntensity[RED] != 0)
			PORTA.OUT.reg &= ~(1 << 2);
		if (currIntensity[GREEN] != 0)
			PORTA.OUT.reg &= ~(1 << 4);
		if (currIntensity[BLUE] != 0)
			PORTA.OUT.reg &= ~(1 << 5);
			
		TCC0->CC[RED].reg = currIntensity[RED];
		TCC0->CC[GREEN].reg = currIntensity[GREEN];
		TCC0->CC[BLUE].reg = currIntensity[BLUE];
			
		TCC0->INTFLAG.reg |= TCC_INTFLAG_OVF | TCC_INTFLAG_MC0 | TCC_INTFLAG_MC1 | TCC_INTFLAG_MC2;
		return;
	}
	else
	{	
		// End of pulse width, turn elements off.
		if ((TCC0->INTFLAG.reg & TCC_INTFLAG_MC0) | (TCC0->INTFLAG.reg & TCC_INTFLAG_MC1) | (TCC0->INTFLAG.reg & TCC_INTFLAG_MC2))
		{
			uint8_t count = TCC0->COUNT.reg >> 4;
			
			if (count >= currIntensity[RED])
				PORTA.OUT.reg |= 1 << 2;
			
			if (count >= currIntensity[GREEN])
				PORTA.OUT.reg |= 1 << 4;
				
			if (count >= currIntensity[BLUE])
				PORTA.OUT.reg |= 1 << 5;
			
			TCC0->INTFLAG.reg |= TCC_INTFLAG_MC0 | TCC_INTFLAG_MC1 | TCC_INTFLAG_MC2;
		}
	}
}*/

void TC3_Handler()
{	
	if (TC3->COUNT8.INTFLAG.reg & TC_INTFLAG_OVF)
	{	
		action(RED);
		if (--actionsRemaining[RED] <= 0)
		{			
			nextInstruction(RED);
			processInstruction(sequences[sequenceCurr][tracker[RED].curr]);
		}
	}
	
	TC3->COUNT16.INTFLAG.reg |= TC_INTFLAG_OVF;
}

void TC4_Handler()
{
	if (TC4->COUNT8.INTFLAG.reg & TC_INTFLAG_OVF)
	{
		action(GREEN);
		if (--actionsRemaining[GREEN] <= 0)
		{
			nextInstruction(GREEN);
			processInstruction(sequences[sequenceCurr][tracker[GREEN].curr]);
		}
	}
	TC4->COUNT16.INTFLAG.reg |= TC_INTFLAG_OVF;
}

void TC5_Handler()
{
	if (TC5->COUNT8.INTFLAG.reg & TC_INTFLAG_OVF)
	{
		action(BLUE);
		if (--actionsRemaining[BLUE] <= 0)
		{
			nextInstruction(BLUE);
			processInstruction(sequences[sequenceCurr][tracker[BLUE].curr]);
		}
	}
	TC5->COUNT16.INTFLAG.reg |= TC_INTFLAG_OVF;
}

void testByColor(uint8_t color, uint8_t val)
{
	switch(color)
	{
		case RED:
			if (val != 0)
				PORTA.OUT.reg &= ~(1<<2);
			else
				PORTA.OUT.reg |= 1<<2;
			break;
		case GREEN:
			if (val != 0)
				PORTA.OUT.reg &= ~(1<<4);
			else
				PORTA.OUT.reg |= 1<<4;
				break;
		case BLUE:
			if (val != 0)
				PORTA.OUT.reg &= ~(1<<5);
			else
				PORTA.OUT.reg |= 1<<5;
				break;
		default:
			break;
	}
}