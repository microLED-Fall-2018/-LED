/* Useful Notes:
 * beatTimer TCC0 - Keeps track of the beat steps and the steps until next action
 * red/green/bluePWM TC3/4/5- psuedo PWM (thanks adafruit...) that control brightness on led outputs
 */
#include <atmel_start.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequences.h"
#include "dotStar.h"
#include "usbCDC.h"

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

//#define GET_INST_COLOR(color) (color.inst >> 6)
//#define GET_INST_TYPE(color) ((color.inst >> 4) & 0x3)

//#define STEP_TIMER TC4->COUNT16
//#define INTEN_TIMER TC3->COUNT8

/*typedef struct {
	uint8_t inst;
	uint8_t rate;
	uint8_t dur;
	uint8_t bright;
	} instruction;*/
	
typedef struct {
	uint8_t first;
	uint8_t last;
	uint8_t curr;
	} instTracker;
	
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
uint8_t sequenceCurr;
	
instTracker tracker[3]; // Tracks the instructions for each color
uint8_t maxIntensity[3];
uint8_t currIntensity[3];
uint16_t nextAction[3]; // the count the next action should occur on. Should wrap around (say if at 65000 and next in 1000)
uint16_t diffs[3]; // increase over current count for next action
uint16_t countMax;
uint8_t increment[3];
uint8_t direction[3];
uint32_t timeDiffs;
uint8_t presses;
uint8_t modeNum;

uint8_t beatsRemaining[3] = {0, 0, 0};
uint16_t actionsRemaining[3] = {0, 0,0};
uint8_t isOn[3] = {0, 0, 0}; // For sequences, is the instruction currently on?

void populateTracker(instruction[]);
void updateStepsPerBeat(uint16_t);
void processInstruction(instruction);
void nextInstruction(uint8_t);
void flash(uint8_t);
void fade(uint8_t);
void rampUp(uint8_t);
void rampDown(uint8_t);
void (*action[3])(uint8_t);
void testByColor(uint8_t, uint8_t);
void changeMode(uint8_t);
void (*modeZero)();
void incSequence();
void recordBPM();
void modeReport(uint8_t);
void loadSequence();
void resetTC_Counts();
void replaceSequence(uint8_t, instruction*);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	buildColors();
	modeZero = &incSequence;
	
	NVIC_DisableIRQ(TC3_IRQn);
	NVIC_DisableIRQ(TC4_IRQn);
	NVIC_DisableIRQ(TC5_IRQn);
	
	PORTA.DIR.reg &= ~(1 << 7);
	PORTA.OUT.reg &= ~(1 << 7);
	PORTA.PINCFG[7].reg |= PORT_PINCFG_INEN | PORT_PINCFG_PULLEN | PORT_PINCFG_PMUXEN;
	
	REG_GCLK_CLKCTRL = GCLK_CLKCTRL_ID_EIC | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
	REG_PM_APBAMASK |= PM_APBAMASK_EIC;
	EIC->INTENSET.reg	= EIC_INTENSET_EXTINT7;
	EIC->CONFIG[0].reg 	|=  EIC_CONFIG_FILTEN7 | EIC_CONFIG_SENSE7_RISE;
	EIC->CTRL.reg |= EIC_CTRL_ENABLE;
	
	NVIC_EnableIRQ(EIC_IRQn);
	NVIC_SetPriority(EIC_IRQn, 3);
	
	replaceSequence(0, testSeq0);
	replaceSequence(1, testSeq1);
	replaceSequence(2, testSeq2);
	replaceSequence(3, testSeq3);
	replaceSequence(4, testSeq4);
	replaceSequence(5, testSeq5);
	replaceSequence(6, testSeq6);
	replaceSequence(7, testSeq7);
	replaceSequence(8, testSeq8);
	replaceSequence(9, testSeq9);
	
	
/*	memcpy(sequences[0], testSeq0, 200);
	memcpy(sequences[1], testSeq1, 200);
	memcpy(sequences[2], testSeq2, 200);
	memcpy(sequences[3], testSeq3, 200);
	memcpy(sequences[4], testSeq4, 200);
	memcpy(sequences[5], testSeq5, 200);
	memcpy(sequences[6], testSeq6, 200);
	memcpy(sequences[7], testSeq7, 200);
	memcpy(sequences[8], testSeq8, 200);
	memcpy(sequences[9], testSeq9, 200);*/
		
	PORTA.DIR.reg |= 1 << 2;
	PORTA.OUT.reg |= 1 << 2;	
	TCC0->PER.reg = 255;
	TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM | 0x7 << 16;
	
	updateStepsPerBeat(stepsPerBeatTable[bpm]);

	sequenceCurr = 0;
	
	loadSequence();

	
	NVIC_EnableIRQ(TC3_IRQn);
	NVIC_EnableIRQ(TC4_IRQn);
	NVIC_EnableIRQ(TC5_IRQn);

	NVIC_SetPriority(TC3_IRQn, 3);
	NVIC_SetPriority(TC4_IRQn, 3);
	NVIC_SetPriority(TC5_IRQn, 3);
	
	while(1)
	{	
		// Heartbeat
		changeDSColor(&dsColors[dsRED]);		
		delay_ms(500);
		changeDSColor(&dsColors[dsBLUE]);
		delay_ms(500);
	}
}

void loadSequence()
{
	populateTracker(sequences[sequenceCurr]);
	tracker[RED].curr = tracker[RED].first;
	tracker[GREEN].curr = tracker[GREEN].first;
	tracker[BLUE].curr = tracker[BLUE].first;
	
	processInstruction(sequences[sequenceCurr][tracker[RED].curr]);
	processInstruction(sequences[sequenceCurr][tracker[GREEN].curr]);
	processInstruction(sequences[sequenceCurr][tracker[BLUE].curr]);
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

void updateStepsPerBeat(uint16_t counts)
{
	stepsPerBeat = counts;
}

// Processing an Instruction
// 1. Whose instruction is this? (RGB)
// 2. What kind of instruction is this?
// 3. If it's a flash, fade, or ramp, process accordingly 
void processInstruction(instruction inst)
{
	uint8_t color	= (inst.inst >> 6) & 0x3;
	uint8_t whatKind	= (inst.inst >> 4) & 0x3;
	
	if (whatKind == FLASH)
	{
		maxIntensity[color] = inst.bright;
		currIntensity[color] = maxIntensity[color];
		actionsRemaining[color] = (inst.dur * inst.rate) << 1;
		diffs[color] = (stepsPerBeat / inst.rate) >> 1;
		action[color] = &flash;
	}
	else if (whatKind == FADE)
	{
		increment[color] = inst.bright >> 4;
		maxIntensity[color] = increment[color] << 4;
		currIntensity[color] = 0;
		actionsRemaining[color] = (inst.dur * inst.rate) << 5; 
		diffs[color] = (stepsPerBeat / inst.rate) >> 5;
		direction[color] = 1;
		action[color] = &fade;
	}
	else if(whatKind == RAMPUP)
	{
		increment[color] = inst.bright >> 4;
		maxIntensity[color] = increment[color] << 4;
		currIntensity[color] = 0;
		actionsRemaining[color] = (inst.dur * inst.rate) << 4; 
		diffs[color] = (stepsPerBeat / inst.rate) >> 4;
		action[color] = &rampUp;
	}
	else if (whatKind == RAMPDN)
	{
		increment[color] = inst.bright >> 4;
		maxIntensity[color] = increment[color] << 4;
		currIntensity[color] = maxIntensity[color];
		actionsRemaining[color] = (inst.dur * inst.rate) << 4;
		diffs[color] = (stepsPerBeat / inst.rate) >> 4;
		action[color] = &rampDown;
	}
	
	if (color == RED)
		TC3->COUNT16.CC[0].reg = diffs[color];
	else if (color == GREEN)
		TC4->COUNT16.CC[0].reg = diffs[color];
	else if (color == BLUE)
		TC5->COUNT16.CC[0].reg = diffs[color];
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
		direction[color] = 0; // falling
	else if (currIntensity[color] <= 0)
		direction[color] = 1; // rising	
		
	if (direction[color] != 0)
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

void TC3_Handler()
{	
	if (TC3->COUNT16.INTFLAG.reg & TC_INTFLAG_OVF)
	{		
		action[RED](RED);
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
	if (TC4->COUNT16.INTFLAG.reg & TC_INTFLAG_OVF)
	{
		action[GREEN](GREEN);
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
	if (TC5->COUNT16.INTFLAG.reg & TC_INTFLAG_OVF)
	{
		action[BLUE](BLUE);
		if (--actionsRemaining[BLUE] <= 0)
		{
			nextInstruction(BLUE);
			processInstruction(sequences[sequenceCurr][tracker[BLUE].curr]);
		}
	}
	TC5->COUNT16.INTFLAG.reg |= TC_INTFLAG_OVF;
}

void EIC_Handler()
{	
	if (EIC->INTFLAG.reg & 1 << 7)
	{
		uint32_t counter = 0;
		uint8_t tracker = 0;
		while(PORT->Group[0].IN.reg & (1 << 7))
		{
			counter++;
			
			if (counter < 500 && !(tracker & 1))
			{
				changeDSColor(&dsColors[dsBLACK]);
				tracker |= 1;
			}
			else if (counter >= 500 && !(tracker & 2))
			{
				changeDSColor(&dsColors[dsGREEN]);
				tracker |= 2;
			}
			else if (counter >= 1000 && !(tracker & 4))
			{
				changeDSColor(&dsColors[dsPURPLE]);
				tracker |= 4;
			}
			else if (counter >= 1500 && !(tracker & 8))
			{
				changeDSColor(&dsColors[dsRED]);
				tracker |= 8;
			}
			else if (counter >= 2000 && !(tracker & 16))
			{
				changeDSColor(&dsColors[dsBLUE]);
				tracker |= 16;
			}
			delay_ms(1);
		}
		
		delay_ms(10);
		
		switch(tracker)
		{
			case 0x1:
				modeZero();
				break;
			case 0x3:
				changeMode(1);
				break;
			case 0x7:
				changeMode(2);
				break;
			case 0xf:
				changeMode(3);
				break;
			case 0x1f:
				changeMode(4);
				break;
			default:
				break;
		}
		
		EIC->INTFLAG.reg |= 1 << 7;
	}
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

void changeMode(uint8_t mode)
{
	
	switch(mode)
	{
		case 1:
			{
				PORT->Group[0].PINCFG[8].reg |= PORT_PINCFG_PMUXEN;
				PORT->Group[0].PINCFG[9].reg |= PORT_PINCFG_PMUXEN;
				PORT->Group[0].PINCFG[10].reg |= PORT_PINCFG_PMUXEN;
			
				processInstruction(sequences[sequenceCurr][tracker[RED].curr]);
				processInstruction(sequences[sequenceCurr][tracker[GREEN].curr]);
				processInstruction(sequences[sequenceCurr][tracker[BLUE].curr]);
				
				modeZero = &incSequence; 
				
				// Reset all counts to zero
				resetTC_Counts();

				break;
			}
		case 2:
			{
				PORT->Group[0].PINCFG[8].reg &= ~(PORT_PINCFG_PMUXEN);
				PORT->Group[0].PINCFG[9].reg &= ~(PORT_PINCFG_PMUXEN);
				PORT->Group[0].PINCFG[10].reg &= ~(PORT_PINCFG_PMUXEN);
			
				TC3->COUNT16.CC[0].reg = 0 - 1;
				
				modeZero = &recordBPM;
				timeDiffs = 0;
				presses = 0;
				break;
			}
		default:
			break;			
	}
	modeNum = mode;
	
	modeReport(modeNum);
}

void incSequence()
{		
	if (++sequenceCurr == MAXSEQ)
		sequenceCurr = 0;

	loadSequence();
	resetTC_Counts();
	
	char sequenceNum[3];
	char words[100] = "Changing to sequence ";
	
	utoa(sequenceCurr, sequenceNum, 10);
//	serialWriteString(strcat(strcat("Changing to sequence ", sequenceNum), ".\0"));
	serialWriteString(strcat(words, sequenceNum));
	serialWriteString("\r\n");


	return;
}

void recordBPM()
{
	presses += 1;
	// grab current count of TC3
	if (presses == 1) // Just reset the counter to 0.
	{
		TC3->COUNT16.COUNT.reg = 0;
	}
	else if (presses < 5) // Store the count value, and reset to 0.
	{
		TC3->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(0x10);
		while(TC3->COUNT16.STATUS.bit.SYNCBUSY) {}
		timeDiffs += TC3->COUNT16.COUNT.reg;
		TC3->COUNT16.COUNT.reg = 0;
	}
	else // Store value, and process
	{
		TC3->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(0x10);
		while(TC3->COUNT16.STATUS.bit.SYNCBUSY) {}
		timeDiffs += TC3->COUNT16.COUNT.reg;	
		
		updateStepsPerBeat(timeDiffs >> 2);
		changeMode(1);
	}	
	
	return;
}

void resetTC_Counts()
{
	TC3->COUNT16.COUNT.reg = 0;
	TC4->COUNT16.COUNT.reg = 0;
	TC5->COUNT16.COUNT.reg = 0;
}

void modeReport(uint8_t mode)
{
	char modeString[30] = "Changing to mode: ";
	char number[10];
	
	TC3->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(0x18);
	while(TC3->COUNT16.STATUS.bit.SYNCBUSY) {}
	
	strcat(strcat(modeString, utoa(mode, number, 10)), "\r\n");
	
	serialWriteString(modeString);
}

void replaceSequence(uint8_t oldSeq, instruction *newSeq)
{
		memcpy(sequences[oldSeq], newSeq, 200);
}