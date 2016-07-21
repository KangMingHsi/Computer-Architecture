#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

extern unsigned int reg[32], PC, cycle, Pos;
extern unsigned char iDisk[1024], dDisk[1024];
extern unsigned char *iBuf, *dBuf;
extern FILE *iIm, *dIm, *snap, *err, *report;

unsigned int reg[32], PC, cycle, Pos;
unsigned char iDisk[1024], dDisk[1024];
unsigned char *iBuf, *dBuf;
FILE *iIm, *dIm, *snap, *err, *report;

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

extern HitAndMiss IPageTable, DPageTable, ICache, DCache, ITLB, DTLB;
HitAndMiss IPageTable, DPageTable, ICache, DCache, ITLB, DTLB;

extern initValues init;
initValues init;

extern int iTLBEntry, dTLBEntry, iPTEntry, dPTEntry, iMEMEntry, dMEMEntry;
int iTLBEntry, dTLBEntry, iPTEntry, dPTEntry, iMEMEntry, dMEMEntry;

extern TLB *iTLB, *dTLB;
TLB *iTLB, *dTLB;

extern PageTable *iPT, *dPT;
PageTable *iPT, *dPT;

extern Cache **iCache, **dCache;
Cache **iCache, **dCache;

extern Memory *iMem, *dMem;
Memory *iMem, *dMem;

extern CacheEntry iCacheEntry, dCacheEntry;
CacheEntry iCacheEntry, dCacheEntry;
