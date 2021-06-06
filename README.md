Using C++ language, simulate an 8-bit CPU having the following specification:
1. Instruction length is 16-bit.
2. Memory is 8-bit and has 256 locations.
3. Data can move from register to memory and vice-versa.
4. Addressing mode:
a. Absolute:
The operand specifies the location of data, memory[operand].
For the branch, the PC can be loaded with PC+operand.
b. Immediate:
The operand provides the operand itself.
For the branch, PC can be loaded with the operand.
c. Indexed:
memory[A0+operand].
For the branch, PC can be loaded with PC+operand.
d. PC relative
memory[PC+operand].
For the branch, PC can be loaded with PC+operand.

The CPU has the following registers:
Data registers: D0
Address register: A0
Program counter: PC
Instruction Register: IR
Memory Address Register: MAR
Memory Buffer Register: MBR
Conditional Code Register: CCR. It consists of only zero flag. It can be set to 1 if the operation’s
result leads to 0. Otherwise, it can be set to 0.
```
Instruction format must like this:
<-----------------------Instruction-------------------> <-------------------------Operand----------------->
7 6 5 4 3 2 1                                           0 7 6 5 4 3 2 1 0

These are the instructions’ opcode:

Instructions Opcode (decimal)
MOV 0
ADD 1
SUB 2
BRA 3
CMP 4
BEQ 5
BNE 6
EXG 7
STP 15

Instructions’ description is given below:
MOV:
The source can be the data register, D0, or memory location. Similarly, the destination can be a memory
location or data register, D0. The movement of the data can be decided by the direction bit in the instruction.
ADD:
If the direction-bit is 0:
Destination = D0 + source,
Then based on the addressing mode, the content of the destination can move to the memory
location
If the direction-bit is 1:
D0 = D0 + source

SUB:
If the direction-bit is 0:
Destination = D0 - source,
Then based on the addressing mode, the content of the destination can move to the memory
location
Opcode

Bit 3 not
used

Direction:
0: Register to memory
1: Memory to register

Addressing mode:
00: Absolute
01: Immediate
10: Indexed
11: PC relative

If the direction-bit is 1:
D0 = D0 - source
BRA:
If the address-mode is 1:
PC=operand
otherwise:
PC = PC + operand

CMP:
MBR = D0 – source
If MBR is 0: CCR=1
Else CCR=0
BEQ:
If CCR is 1
If address-mode is 1: PC = operand
Otherwise: PC = PC + operand
BNE:
If CCR is not 1
If address-mode is 1: PC = operand
Otherwise: PC = PC + operand
EXG:
MBR = D0, D0 = A0, A0 = MBR
STP:
Terminate the program
Define the FSM in the given C++ code’s functions:

Function Marks
fetchDecodeFSM 5
movFSM 5
addFSM 5
subFSM 5
braFSM 3
cmpFSM 3
beqFSM 3
bneFSM 3
stpFSM 1

Test your designed CPU:
Write a program using these instructions (in binary form) in the function load_program(). The program can
calculate the first seven Fibonacci number. The first two Fibonacci numbers are stored in memory location
255 and 254, and the remaining five Fibonacci numbers can be stored in memory location 253 onwards.
```
