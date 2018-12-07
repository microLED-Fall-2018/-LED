/*
 * main.h
 *
 * Created: 12/6/2018 10:03:04 AM
 *  Author: techi
 */ 


#ifndef MAIN_H_
#define MAIN_H_

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

void populateTracker(instruction[]);
void updateStepsPerBeat(uint16_t);
void setToBPM(uint8_t);
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
void replaceSequence(instruction*, instruction*);
void retrieveSequence(uint8_t);
void storeSequence(uint8_t, void*);
void startSequence();

static instruction currSeq[MAXINST];
static uint8_t currSeqNum;
#endif /* MAIN_H_ */