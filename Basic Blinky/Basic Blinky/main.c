/* Useful Notes:
 * Intensity TC3, 8-bit
 * Step	 TC4, 16-bit
 */
#include <atmel_start.h>
#include <string.h>

#define PORTA PORT->Group[0]
#define PORTB PORT->Group[1]

#define BPM 120		// Eventually this will be replaced with a flexible method
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

#define STEP_TIMER TC4->COUNT16
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
	uint8_t next;
	uint8_t curr;
	} instTracker;
	
instruction shortDemo[200] = {  {0x00, 5, 4, 0xff},
								{0x01, 10, 4, 128},
								{0x41, 20, 4, 255},
								{0x80, 3, 4, 255},
								{0x81, 5, 4, 128}};


	
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

uint8_t bpm = 120;

uint16_t stepsPerBeat, nextBeat; 
uint8_t beatsCurr = 0;

// Storage for flash sequences
// There are up to 10 sequences which can be 200 instructions long each
instruction sequences[MAXSEQ][MAXINST];
uint8_t sequenceCurr = 0;
	
instTracker tracker[3]; // Tracks the instructions for each color
uint8_t isOn[3]; // For sequences, is the instruction currently on?
uint8_t intensity[3];
uint16_t nextAction[3]; // the count the next action should occur on. Should wrap around (say if at 65000 and next in 1000)
uint16_t diffs[3]; // increase over current count for next action
uint8_t beatsRemaining[3];

void populateTracker(instruction[]);
void updateStepsPerBeat(uint8_t);
void processInstruction(instruction);
void nextInstruction(uint8_t);
void flash(uint8_t, uint16_t);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	//updateStepsPerBeat(bpm);
	nextBeat = stepsPerBeat;
	
	// For testing only.  Can be removed once working with actual flash sequences
	//memcpy(sequences[0], shortDemo, 200 * sizeof(instruction));
	PORTA.OUT.reg |= 1 << 2 | 1 << 4 | 1 << 5;
	PORTA.DIRSET.reg = 1 << 2 | 1 << 4 | 1 << 5;
		
	populateTracker(shortDemo);
	tracker[RED].curr = tracker[RED].first;
	tracker[GREEN].curr = tracker[GREEN].first;
	tracker[BLUE].curr = tracker[BLUE].first;
	
	processInstruction(shortDemo[tracker[RED].curr]);	
	processInstruction(shortDemo[tracker[GREEN].curr]);
	processInstruction(shortDemo[tracker[BLUE].curr]);
	
	while(1)
	{	
		uint8_t intenCurr = INTEN_TIMER.COUNT.reg;
		uint16_t stepCurr = STEP_TIMER.COUNT.reg;
		
		if (stepCurr >= nextAction[RED])
		{	
			//nextAction[RED] += diffs[RED];
			flash(RED, stepCurr);
		}
		if (stepCurr >= nextAction[GREEN])
		{
			//nextAction[GREEN] += diffs[GREEN];
			flash(GREEN, stepCurr);
		}
		if (stepCurr >= nextAction[BLUE])
		{
			//nextAction[BLUE] += diffs[BLUE];
			flash(BLUE, stepCurr);
		}
		/*
		if (stepCurr == nextBeat)
		{	
			beatsRemaining[RED]--;
			beatsRemaining[GREEN]--;
			beatsRemaining[BLUE]--;
			
			if (beatsRemaining[RED] <= 0)
			{
				nextInstruction(RED);
				processInstruction(sequences[sequenceCurr][tracker[RED].curr]);
			}
			if (beatsRemaining[GREEN] <= 0)
			{
				nextInstruction(GREEN);
				processInstruction(sequences[sequenceCurr][tracker[GREEN].curr]);
			}
			if (beatsRemaining[BLUE] <= 0)
			{
				nextInstruction(BLUE);
				processInstruction(sequences[sequenceCurr][tracker[BLUE].curr]);
			}
		}
		*/
		
		/*if ((intenCurr <= intensity[RED]) && isOn[RED]) 
			PORTA.OUT.reg &= ~(1 << 2);
		else
			PORTA.OUT.reg |= 1 << 2;
			
		if ((intenCurr <= intensity[GREEN]) && isOn[GREEN])
			PORTA.OUT.reg &= ~(1 << 4);
		else
			PORTA.OUT.reg |= 1 << 4;
							
		if ((intenCurr <= intensity[BLUE]) && isOn[BLUE])
			PORTA.OUT.reg &= ~(1 << 5);	
		else
			PORTA.OUT.reg |= 1 << 5;*/

		if (intenCurr <= intensity[RED] && isOn[RED])
			PORTA.OUT.reg &= ~(1 << 2);
		else
			PORTA.OUT.reg |= 1 << 2;

		if (intenCurr <= intensity[GREEN] && isOn[GREEN])
			PORTA.OUT.reg &= ~(1 << 4);
		else
			PORTA.OUT.reg |= 1 << 4;
		
		if (intenCurr <= intensity[BLUE] && isOn[BLUE])
			PORTA.OUT.reg &= ~(1 << 5);
		else
			PORTA.OUT.reg |= 1 << 5;
		
		// Heartbeat
		if (STEP_TIMER.COUNT.reg & 0x1000)
		PORTA.OUT.reg |= 1 << 17;
		else
		PORTA.OUT.reg &= ~(1 << 17);
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

	if (insts[i].inst & 0x01)
		tracker[RED].next = tracker[RED].first;
	else
		tracker[RED].next = tracker[RED].first + 1;
	
	while (count < 3) // 0 - Red, 1 - Green, 2 - Blue
	{
			/*
			PORTA.OUT.reg |= 1 << 2 | 1 << 4 | 1 << 5;
			
			if (count == RED)
			PORTA.OUT.reg &= ~(1 << 2);
			else if (count == GREEN)
			PORTA.OUT.reg = ~(1 << 4);
			else if (count == BLUE)
			PORTA.OUT.reg &= ~(1 << 5);
			else
			PORTA.OUT.reg = 1 << 2 | 1 << 5;
			
			delay_ms(250);
			
			PORTA.OUT.reg |= 1 << 2 | 1 << 4 | 1 << 5;
			
			delay_ms(250);
			*/
		
		// A 1 in the 24th position indicates the last instruction in a color
		if(insts[i++].inst & 0x01)
		{
/*			PORTA.OUT.reg &= ~(1 << 2 | 1 << 4 | 1 << 5);
			delay_ms(250);
			PORTA.OUT.reg |= 1 << 2 | 1 << 4 | 1 << 5;
			delay_ms(250);*/
			
			tracker[count++].last = i - 1;
			
			if (count <= BLUE)
			{
				tracker[count].first = i; // i has already been incremented
				tracker[count].next = tracker[count].first + 1;
			}
		}
	}
}

void updateStepsPerBeat(uint8_t bpm)
{
	stepsPerBeat = stepsPerBeatTable[bpm - 1];
}

// Processing an Instruction
// 1. Who's instruction is this? (RGB)
// 2. What kind of instruction is this?
// 3. If it's a flash, fade, or ramp, process accordingly 
void processInstruction(instruction inst)
{
	uint8_t whichColor	= (inst.inst >> 6) & 0x3;
	uint8_t whatKind	= (inst.inst >> 4) & 0x3;
	
	/*	
	PORTA.OUT.reg |= 1 << 2 | 1 << 4 | 1 << 5;
	
	if (whichColor == RED)
		PORTA.OUT.reg &= ~(1 << 2);
	else if (whichColor == GREEN)
		PORTA.OUT.reg = ~(1 << 4);
	else if (whichColor == BLUE)
		PORTA.OUT.reg &= ~(1 << 5);
	else 
		PORTA.OUT.reg &= ~(1 << 2 | 1 << 4 | 1 << 5);
	
	delay_ms(125);
	
	PORTA.OUT.reg |= 1 << 2 | 1 << 4 | 1 << 5;
	
	delay_ms(125);
	*/

	switch(whatKind)
	{
		case FLASH:
			intensity[whichColor] = inst.bright;
			isOn[whichColor] = 1;
			diffs[whichColor] = stepsPerBeat / (inst.rate >> 1);
			nextAction[whichColor] = STEP_TIMER.COUNT.reg + diffs[whichColor];	
			beatsRemaining[whichColor] = inst.dur;
			break;
		case FADE:
			break;
		case RAMPUP:
			break;
		case RAMPDN:
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

void flash(uint8_t color, uint16_t count)
{
	isOn[color] = !isOn[color];
	nextAction[color] = count + diffs[color];
}

void nextInstruction(uint8_t color)
{
	tracker[color].curr = tracker[color].next;
	
	if (tracker[color].curr == tracker[color].last)
		tracker[color].next = tracker[color].first;
	else
		tracker[color].next = tracker[color].curr + 1;
}