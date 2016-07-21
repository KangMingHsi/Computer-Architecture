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

extern unsigned int addr, constant, isFlush, isStall;
extern unsigned int part1, part2, part3, part4;
extern unsigned char shamtEX, func, signRS, signRT, signRD, signCons;
extern int constant2, Integeter, RS, RT, flag;
extern int writeMemZero, misalignment, numberOverflow, memOverflow;

unsigned int addr, constant, isFlush, isStall;
unsigned int part1, part2, part3, part4;
unsigned char shamtEX, func, signRS, signRT, signRD, signCons;
int constant2, Integeter, RS, RT, flag;
int writeMemZero, misalignment, numberOverflow, memOverflow;

extern unsigned int type, tmpEX, tmpMEM, printValue, printPlace, newPC;
extern unsigned char rs, rt, flush;

unsigned int type, tmpEX, tmpMEM, printValue, printPlace, newPC;
unsigned char rs, rt, flush;

typedef struct buffer{
    unsigned int instruction, a, b, pc;
    unsigned char opcode, stall, rs, rt, rd, shamt;
    char out[6];
}buffer;

typedef struct forwarding{
    unsigned char forwardingRs_ID, forwardingRt_ID, forwardingRs_EX, forwardingRt_EX;

}forwarding;

extern forwarding Forwarding;
forwarding Forwarding;

extern buffer IFBuffer, IDBuffer, EXBuffer, MEMBuffer, WBBuffer;
buffer IFBuffer, IDBuffer, EXBuffer, MEMBuffer, WBBuffer;
