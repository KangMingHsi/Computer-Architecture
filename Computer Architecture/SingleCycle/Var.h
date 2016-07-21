#include <stdio.h>
#include <stdlib.h>

extern unsigned int reg[32], PC, cycle, Pos;
extern unsigned char iM[1024], dM[1024];
extern unsigned char *iBuf, *dBuf;
extern FILE *iIm, *dIm, *snap, *err;

unsigned int reg[32], PC, cycle, Pos;
unsigned char iM[1024], dM[1024];
unsigned char *iBuf, *dBuf;
FILE *iIm, *dIm, *snap, *err;

extern unsigned int addr;
extern unsigned int part1, part2, part3, part4;
extern unsigned char rs, rt, rd, shamt, func, signRS, signRT, signRD, signCons;
extern unsigned short constant;
extern int constant2, Integeter, RS, RT, flag;
extern int writeMemZero, misalignment, numberOverflow, memOverflow;

unsigned int addr;
unsigned int part1, part2, part3, part4;
unsigned char rs, rt, rd, shamt, func, signRS, signRT, signRD, signCons;
unsigned short constant;
int constant2, Integeter, RS, RT, flag;
int writeMemZero, misalignment, numberOverflow, memOverflow;

