/* Useful Notes:
 * beatTimer TCC0 - Keeps track of the beat steps and the steps until next action
 * red/green/bluePWM TC3/4/5- psuedo PWM (thanks adafruit...) that control brightness on led outputs
 */
#include <atmel_start.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sequences.h"
#include "main.h"
#include "dotStar.h"
#include "usbCDC.h"
	
uint8_t bpm = BPM;

uint16_t stepsPerBeat, nextBeat; 
uint8_t beatsCurr = 0;

// Storage for flash sequences
// There are up to 10 sequences which can be 200 instructions long each
//instruction sequences[MAXSEQ][MAXINST];
	
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

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	setupUSBCallbacks();
	
	buildColors();
	
	modeZero = &incSequence;
	
	storeSequence(0, testSeq0);
	
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
		
	PORTA.DIR.reg |= 1 << 2;
	PORTA.OUT.reg |= 1 << 2;	
	TCC0->PER.reg = 255;
	TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM | 0x7 << 16;
	
	setToBPM(bpm);

	currSeqNum = 0;
	retrieveSequence(currSeqNum);

	startSequence();
	
	changeDSColor(&dsColors[RED]);
	
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
	populateTracker(currSeq);
	tracker[RED].curr = tracker[RED].first;
	tracker[GREEN].curr = tracker[GREEN].first;
	tracker[BLUE].curr = tracker[BLUE].first;
	
	processInstruction(currSeq[tracker[RED].curr]);
	processInstruction(currSeq[tracker[GREEN].curr]);
	processInstruction(currSeq[tracker[BLUE].curr]);
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
			processInstruction(currSeq[tracker[RED].curr]);
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
			processInstruction(currSeq[tracker[GREEN].curr]);
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
			processInstruction(currSeq[tracker[BLUE].curr]);
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
			
				processInstruction(currSeq[tracker[RED].curr]);
				processInstruction(currSeq[tracker[GREEN].curr]);
				processInstruction(currSeq[tracker[BLUE].curr]);
				
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
	if (++currSeqNum == MAXSEQ)
		currSeqNum = 0;
		
	retrieveSequence(currSeqNum);

	startSequence();

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

 void replaceSequence(instruction *oldSeq, void *newSeq)
{
	memcpy(oldSeq, newSeq, 200);
}

/*
 * Retrieves sequence 'seqNum' from memory, replaces currSeq
 */
 void retrieveSequence(uint8_t seqNum)
{
	flash_read(&FLASH_INSTANCE, seqStorage[seqNum], (uint8_t *)currSeq, MAXINST * sizeof(instruction));
}

/*
 * Replaces sequence 'seqNum' in memory with sequence 'seq'
 */
 void storeSequence(uint8_t seqNum, instruction *seq)
{
	flash_write(&FLASH_INSTANCE, seqStorage[seqNum], (uint8_t *) seq, MAXINST * sizeof(instruction));
}

void startSequence()
{
	loadSequence();
	resetTC_Counts();
}

void setToBPM(uint8_t bpmValue)
{
	updateStepsPerBeat(stepsPerBeatTable[bpm]);
}