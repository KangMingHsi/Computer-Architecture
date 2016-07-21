#include "Var.h"
#include "translate.h"

void getAddr(){
    part1 = iM[IDBuffer.pc], part2 = iM[IDBuffer.pc+1], part3 = iM[IDBuffer.pc+2], part4 = iM[IDBuffer.pc+3];
    part1 = (part1 << 30) >> 6;
    part2 = (part2 << 16);
    part3 = (part3 << 8);

    addr = (part1 + part2 + part3 + part4);
}
void getRs(unsigned int ins, unsigned char *rs){
    *rs = (ins << 6) >> 27;
}
void getRt(unsigned int ins, unsigned char *rt){
    *rt = (ins << 11) >> 27;
}

void getRd(unsigned int ins, unsigned char *rd){
    *rd = (ins << 16) >> 27;
}
void getShamt(unsigned int ins ,unsigned char *shamt){
    *shamt = (ins << 21) >> 27;
}
void getImmediateBoth(unsigned int ins){
    constant = (ins << 16) >> 16;
    constant2 = ins;
    constant2 = constant2 << 16 >> 16;
}
void getPos(){
    signRS = RS >> 31; signCons = constant2 >> 31;
    Pos = RS + constant2;
    signRD = Pos >> 31;
    if(signRS == signCons && signRS != signRD)
        numberOverflow = 1;
}

void Decode(){
    getRs(IDBuffer.instruction, &IDBuffer.rs);
    getRd(IDBuffer.instruction, &IDBuffer.rd);
    getRt(IDBuffer.instruction, &IDBuffer.rt);
    getShamt(IDBuffer.instruction, &IDBuffer.shamt);
}

void bufferCopy(buffer* A, buffer* B){
    A->a = B->a;
    A->b = B->b;
    A->instruction = B->instruction;
    A->opcode = B->opcode;
    A->rd = B->rd;
    A->rs = B->rs;
    A->stall = B->stall;
    A->rt = B->rt;
    A->shamt = B->shamt;
    A->pc = B->pc;
}

void bufferClear(buffer* A){
    A->instruction = 60 << 26;
    A->opcode = 60;
    A->rd = 0;
    A->rt = 0;
    A->rs = 0;
    A->shamt = 0;
    A->stall = 0;
}

int between(unsigned char opcode, unsigned char low, unsigned char up){
    if(opcode >= low && opcode <= up)
        return 1;
    else
        return 0;
}
