/*
 * Sequences.h
 *
 * Created: 11/8/2018 9:21:39 AM
 *  Author: techi
 */ 


#ifndef SEQUENCES_H_
#define SEQUENCES_H_

#define ADDR_SEQ_0 0x30001
#define ADDR_SEQ_1 0x30401
#define ADDR_SEQ_2 0x30801
#define ADDR_SEQ_3 0x30c01
#define ADDR_SEQ_4 0x31001
#define ADDR_SEQ_5 0x31401
#define ADDR_SEQ_6 0x31801
#define ADDR_SEQ_7 0x31c01
#define ADDR_SEQ_8 0x32001
#define ADDR_SEQ_9 0x32401

typedef struct {
	uint8_t inst;
	uint8_t rate;
	uint8_t dur;
	uint8_t bright;
} instruction;

uint32_t seqStorage[10] = {ADDR_SEQ_0, ADDR_SEQ_1, ADDR_SEQ_2, ADDR_SEQ_3, ADDR_SEQ_4, ADDR_SEQ_5, ADDR_SEQ_6, ADDR_SEQ_7, ADDR_SEQ_8, ADDR_SEQ_9 };

instruction testSeq0[200] =   {{0x00, 4, 1, 255},
								{0x20, 1, 1, 255},
								{0x11, 8, 1, 255},
								{0x50, 8, 1, 255},
								{0x51, 4, 1, 255},
								{0x80, 2, 1, 255},
								{0x81, 8, 1, 255}};

instruction testSeq1[200] =    {{0x00, 4, 4, 200},
								{0x00, 4, 4, 0}, 
								{0x01, 4, 2, 200},
								{0x40, 4, 2, 0},
								{0x40, 4, 4, 200},
								{0x41, 4, 4, 0},
								{0x80, 4, 6, 0},
								{0x81, 4, 4, 200}};

instruction testSeq2[200] = {{0x21, 1, 4, 200},
							 {0x51, 1, 4, 200},
							 {0x81, 1, 4, 200}};									

instruction testSeq3[200] = {{0x11, 1, 1, 255}, 
							 {0x51, 1, 1, 0}, 
							 {0xb1, 1, 1, 0}};
	
instruction testSeq4[200] = {{0x11, 1, 4, 0},
							 {0x61, 1, 4, 200},
							 {0x91, 1, 4, 0}};

instruction testSeq5[200] = {{0x11, 1, 4, 0},
							 {0x51, 1, 4, 0},
							 {0x91, 1, 4, 200}};
								 
instruction testSeq6[200] = {{0x11, 1, 4, 200},
								{0x51, 1, 4, 200},
								{0x91, 1, 4, 0}};

instruction testSeq7[200] = {{0x11, 1, 4, 0},
								{0x51, 1, 4, 200},
								{0x91, 1, 4, 200}};

instruction testSeq8[200] = {{0x11, 1, 4, 200},
								{0x51, 1, 4, 0},
								{0x91, 1, 4, 200}};

instruction testSeq9[200] = {{0x21, 1, 4, 200},
								{0x51, 1, 4, 200},
								{0x81, 1, 4, 200}};
							
							

	
#endif /* SEQUENCES_H_ */