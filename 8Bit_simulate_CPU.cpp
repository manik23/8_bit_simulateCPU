#include <stdio.h>
#include <cstdint>

/*
Author:
Manik Mahajan
*/

#define MOV 0
#define ADD 1
#define SUB 2
#define BRA 3
#define CMP 4
#define BEQ 5
#define BNE 6
#define EXG 7
#define STP 15


uint8_t PC = 0; //Program counter
uint8_t D0 = 0; //
uint8_t A0 = 0; //
uint8_t CCR = 0; //
uint8_t MAR; //
uint8_t MBR; //
uint8_t IR; //
uint8_t operand; //
uint8_t source; //
uint8_t destination; //

uint8_t amode = 0; //
uint8_t direction = 0; //
uint8_t memory[256]; //
uint8_t  run = 1; //

uint8_t fetchDecodeFSM(void) {
	uint8_t opcode = memory[PC];
	IR = opcode;
	operand = memory[PC + 1];
	amode = opcode & 3;
	opcode >>= 1;
	opcode >>= 1;
	direction = opcode & 1;
	opcode >>= 1;
	opcode >>= 1;
	PC = PC + 2;
	return opcode;

}

void movFSM(void) {
	if (direction) {
		/* memory to register */
		if (amode == 0) {
			D0 = memory[operand];
		}
		else if (amode == 1) {
			D0 = operand;
		}
		else if (amode == 2) {
			D0 = memory[A0 + operand];
		}
		else if (amode == 3) {
			D0 = memory[PC + operand];
		}
	}
	else {
		if (amode == 0) {
			memory[operand] = D0;
		}
		else if (amode == 1) {

		}
		else if (amode == 2) {
			memory[A0 + operand] = D0;
		}
		else if (amode == 3) {
			memory[PC + operand] = D0;
		}
	}

}

void addFSM(void) {

	if (direction) {
		/* memory to register */
		if (amode == 0) {
			D0 = D0 + memory[operand];
		}
		else if (amode == 1) {
			D0 = D0 + operand;
		}
		else if (amode == 2) {
			D0 = D0 + memory[A0 + operand];
		}
		else if (amode == 3) {

			D0 = D0 + memory[PC + operand];
		}

		if (!D0) {
			CCR = 1;
		}

	}
	else {
		/* register to memory */
		if (amode == 0) {
			memory[operand] = memory[operand] +  D0;
			if (!memory[operand]) CCR = 1;
		}
		else if (amode == 2) {
			memory[A0 + operand] = memory[A0 + operand] + D0;
			if (!memory[A0 + operand]) CCR = 1;
		}
		else if (amode == 3) {
			memory[PC + operand] = memory[PC + operand] + D0;
			if (!memory[PC + operand]) CCR = 1;

		}
	}

}

void subFSM(void) {


	if (direction) {
		/* memory to register */
		if (amode == 0) {
			D0 = D0 - memory[operand];
		}
		else if (amode == 1) {
			D0 = D0 - operand;
		}
		else if (amode == 2) {
			D0 = D0 - memory[A0 + operand];
		}
		else if (amode == 3) {

			D0 = D0 - memory[PC + operand];
		}

		if (!D0) {
			CCR = 1;
		}

	}
	else {
		/* register to memory */
		if (amode == 0) {
			memory[operand] = D0 - memory[operand];
			if (!memory[operand]) CCR = 1;
		}
		else if (amode == 2) {
			memory[A0 + operand] = D0 - memory[A0 + operand];
			if (!memory[A0 + operand]) CCR = 1;
		}
		else if (amode == 3) {
			memory[PC + operand] = D0 - memory[PC + operand];
			if (!memory[PC + operand]) CCR = 1;

		}
	}

}

void braFSM(void) {
	if (amode == 1) {
		PC = operand;
	}
	else {
		PC = PC + operand;
	}

}


void cmpFSM(void) {
	if (direction) {
		/* memory to register */
		if (amode == 0) {
			source = memory[operand];
		}
		else if (amode == 1) {
			source = operand;
		}
		else if (amode == 2) {
			source = memory[A0 + operand];
		}
		else if (amode == 3) {
			source = memory[PC + operand];
		}

		MBR = D0 - source;
		if (!MBR) CCR = 1;
		else CCR = 0;
	}
}

void beqFSM(void) {
	if (CCR) {
		if (amode == 1) {
			PC = operand;
		}
		else
		{
			PC = PC + operand;
		}
	}

}
void bneFSM(void) {
	if (!CCR) {
		if (amode == 1) {
			PC = operand;
		}
		else
		{
			PC = PC + operand;
		}
	}

}
void exgFSM(void) {
	uint8_t temp = A0;
	MBR = D0;
	D0 = A0;
	A0 = MBR;

}
void stpFSM(void) {
	run = 0;
}
void load_program(void);
int main(void) {
	load_program();
	// cout << fetchDecodeFSM() << endl;


	while (run) {
		uint8_t opcode = fetchDecodeFSM();

		switch (opcode)
		{

		case MOV: movFSM(); break;
		case ADD: addFSM(); break;
		case SUB: subFSM(); break;
		case BRA: braFSM(); break;
		case CMP: cmpFSM(); break;
		case BEQ: beqFSM(); break;
		case BNE: bneFSM(); break;
		case EXG: exgFSM(); break;
		case STP: stpFSM(); break;
		default : run = 0; break;
		}

	}
	// cout << int(D0) << " " << int(CCR) << endl;
	printf("The Fibonacci numbers are:\n");
	for (int i = 0; i < 9; i++)
		printf("%d ", memory[255 - i]);
}
void load_program(void) {

	// Code Memory segment from 0 to 150



	// /*Code for Fibbonnaci series*/

	// move 255 to D0
	// add 	254 to D0
	// store D0 to 253
	memory[0] = 0b00000100;
	memory[1] = 255;
	memory[2] = 0b00010100;
	memory[3] = 254;
	memory[4] = 0b00000000;
	memory[5] = 253;


	// move 254 to D0
	// add 	253 to D0
	// store D0 to 252
	memory[6] = 0b00000100;
	memory[7] = 254;
	memory[8] = 0b00010100;
	memory[9] = 253;
	memory[10] = 0b00000000;
	memory[11] = 252;

	// move 253 to D0
	// add 252 t0 D0
	// store Do to 251
	memory[12] = 0b00000100;
	memory[13] = 253;
	memory[14] = 0b00010100;
	memory[15] = 252;
	memory[16] = 0b00000000;
	memory[17] = 251;

	// move 252 to D0
	// Add 251 to D0
	// store D0 to 250
	memory[18] = 0b00000100;
	memory[19] = 252;
	memory[20] = 0b00010100;
	memory[21] = 251;
	memory[22] = 0b00000000;
	memory[23] = 250;

	// move 251 to D0
	// Add 250 to D0
	// store D0 to 249
	memory[24] = 0b00000100;
	memory[25] = 251;
	memory[26] = 0b00010100;
	memory[27] = 250;
	memory[28] = 0b00000000;
	memory[29] = 249;


	// move 250 to D0
	// Add 249 to D0
	// store D0 to 248
	memory[30] = 0b00000100;
	memory[31] = 250;
	memory[32] = 0b00010100;
	memory[33] = 249;
	memory[34] = 0b00000000;
	memory[35] = 248;

	// move 249 to D0
	// Add 248 to D0
	// store D0 to 247

	memory[36] = 0b00000100;
	memory[37] = 249;
	memory[38] = 0b00010100;
	memory[39] = 248;
	memory[40] = 0b00000000;
	memory[41] = 247;


	// Terminate Program
	memory[42] = 0b11110000;







	// Data Segment from 255 to 149
	memory[255] = 0;
	memory[254] = 1;



	/* - - - - - - - - - - - - - - - - - - */
	//sample of addition s1 = immediate operand and s2 = indexed memory operand
	// memory[0] = 0b00000101;
	// memory[1] = 0b00000100;
	// memory[2] = 0b00010111;
	// memory[3] = 0b00000001;
	// memory[4] = 0b11110000;
	// memory[5] = 0b00010000;
	/* - - - - - - - - - - - - - - - - - - */




}
